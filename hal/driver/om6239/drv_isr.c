/* ----------------------------------------------------------------------------
 * Copyright (c) 2020-2030 OnMicro Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of OnMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -------------------------------------------------------------------------- */

/**
 * @file     drv_irq.c
 * @brief    interrupt service routine
 * @date     05. Aug 2023
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_ISR)
#include <stdint.h>
#include <stddef.h>
#include "om_driver.h"
#include "mouse.h"
#include "ex2_app_mouse.h"
#include "ex2_api.h"
#include "main.h"
#include "main_24g.h"

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
extern ms_sleep_level_t ms_sleep_level;

extern bool ll_conn_sleep_prologue(void);
extern void RTC_IRQHandler_24G(void);

bool   bperiph_int;
extern bool bargb_valid;

//----------------------------------------------------------------------------
//表格定义区
//

//============================================================================;
// 代码区                                                                     ;
//============================================================================;

__RAM_CODE void RTC_IRQHandler(void)
{
    uint32_t int_status;

    int_status = OM_RTC->INTSTAT;
    OM_RTC->INTRAWSTAT = int_status;                // clear status

    if(iDEVICE_TYPE_24G == device_type)
    {
        if (DRV_EVENT_RTC_ALARM0 & int_status)
        {
            RTC_IRQHandler_24G();
        }
    }
    else if(iDEVICE_TYPE_BT2 >= device_type)
    {
        if (DRV_EVENT_RTC_ALARM0 & int_status)
        {
//(TIMER_PIN);
            drv_rtc_isr_callback();
//gpio_toggle(TIMER_PIN);
        }
    }
}

extern uint8_t  ble_interval;
extern bool  bscan_sensor_en;
extern void ll_conn_isr(uint8_t status);
extern void ll_adv_isr(uint8_t status);

__RAM_CODE void RF_IRQHandler(void)
{
    rf_irq_status = drv_rf_get_and_clear_irq_status();
    if(iDEVICE_TYPE_BT2 >= device_type)
    {
        drv_wdt_keep_alive(OM_WDT);
        if(EXE_LINK_STATE_CONN==exe_stk_state)
            ll_conn_isr(rf_irq_status);
        else if(EXE_LINK_STATE_ADV==exe_stk_state)
            ll_adv_isr(rf_irq_status);
    }
}

void WAKEUP_GPIO0_IRQHandler(void)
{
    //drv_gpio_isr(OM_GPIO0);
    uint32_t int_status;

    int_status = OM_GPIO0->INTSTATUS;
    OM_GPIO0->INTSTATUS = int_status;
    /* Clear pin wakeup interrupt in PMU module, otherwise reach here again. */
    drv_pmu_clear_wakeup();
    bperiph_int =1;

    if(iDEVICE_TYPE_BT2 >= device_type)
    {
    /* Clear pin wakeup interrupt in PMU module, otherwise reach here again. */
        if(ms_sleep_level == MS_SLEEP_LEVEL1) {
            ms_sleep_level = MS_SLEEP_LEVEL0;
            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL0);
            exled_rtc_count=0;

            ex2_app_mouse_scan();
            ll_conn_sleep_prologue();
            ex2_ll_set_next_polling_time(0);
        }
    }
}

void TIMER0_IRQHandler(void)
{
    #if (RTE_TIMER0)
    drv_timer_isr(OM_TIMER0);
    #endif /* (RTE_TIMER0) */
}

void UART0_IRQHandler(void)
{
    #if (RTE_UART0)
    drv_uart_isr(OM_UART0);
    #endif /* (RTE_UART0) */
}

void SysTick_Handler(void)
{
    #if (RTE_CORTEX_SYSTICK)
    drv_systick_isr();
    #endif /* RTE_CORTEX_SYSTICK */
}

void AES128_IRQHandler(void)
{
    #if (RTE_AES128)
    drv_aes128_isr(OM_AES128);
    #endif /* (RTE_AES128) */
}

void WDT_IRQHandler(void)
{
    #if (RTE_WDT)
    drv_wdt_isr(OM_WDT);
    #endif /* RTE_WDT */
}

void SENSCAN_IRQHandler(void)
{
    #if (RTE_SENSCAN)
    drv_senscan_isr(OM_SENSCAN);
    #endif /* RTE_SENSCAN */
}

void LEDC_IRQHandler(void)
{
    #if (RTE_LEDC)
    drv_ledc_isr(OM_LEDC);
    #endif /* RTE_LEDC */
}

void ENCODER_IRQHandler(void)
{
    if (OM_ENCODER->VALID & ENCODER_VALID_CNT_MASK) {
        if(OM_ENCODER->CNT & 0x08) {
            wheel_data = 0xf0|OM_ENCODER->CNT;
        } else {
            wheel_data = OM_ENCODER->CNT&0x0f;
        }

        bperiph_int =1;
        if(iDEVICE_TYPE_BT2 >= device_type)
        {
            if(ms_sleep_level == MS_SLEEP_LEVEL1) {
                ms_sleep_level = MS_SLEEP_LEVEL0;
                mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL0);

                ex2_app_mouse_scan();
                ll_conn_sleep_prologue();
                ex2_ll_set_next_polling_time(0);
            }
        }
    }
}

#endif  /* (RTE_ISR) */


/** @} */
