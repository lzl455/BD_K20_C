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
 * @file     drv_rtc.c
 * @brief    rtc driver
 * @date     23. Sep 2023
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
#if (RTE_RTC)
#include <stddef.h>
#include "om_driver.h"

/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_RTC_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t   isr_cb;
} rtc_env_t;
#endif /* (RTE_RTC_REGISTER_CALLBACK) */


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_RTC_REGISTER_CALLBACK)
static rtc_env_t rtc_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_RTC_REGISTER_CALLBACK) */


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_rtc_init(OM_RTC_Type *om_rtc)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RTC, 1U);
    while (0 == (OM_RTC->CR & RTC_CR_CR_WRITE_STATUS_MASK));
    /* ALARM0_WAKEUP_EN  must be 1, otherwise Alarm  cannot wakeup from Stop1+ mode. */
    /* ALARM1_WAKEUP_EN must be 1, otherwise Alarm1 cannot wakeup from Stop1+ mode. */
    /* CR_TICK_WAKEUP_EN must be 1, otherwise Tick  cannot wakeup from Stop1+ mode. */
    OM_RTC->CR |= (RTC_CR_TIMER_EN_MASK | RTC_CR_ALARM1_WAKEUP_EN_MASK | RTC_CR_ALARM0_WAKEUP_EN_MASK);
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_SetPriority(RTC_IRQn, RTE_RTC_IRQ_PRIORITY);
    NVIC_EnableIRQ(RTC_IRQn);

    return OM_ERROR_OK;
}

void drv_rtc_set_alarm(OM_RTC_Type *om_rtc, rtc_alarm_t alarm, uint32_t time)
{
    while (0 == (OM_RTC->CR & RTC_CR_ALARMx_WRITE_STATUS_MASK(alarm)));
    switch (alarm) {
        case RTC_ALARM_0:
            OM_RTC->ALARM0 = time;
            break;
        case RTC_ALARM_1:
            OM_RTC->ALARM1 = time;
            break;
        case RTC_ALARM_2:
            OM_RTC->ALARM2 = time;
            break;
        default:
            OM_ASSERT(0U);
            break;
    }
}

void drv_rtc_set_tick_hz(int hz)
{
    while (0 == (OM_RTC->CR & RTC_CR_TICK_WRITE_STATUS_MASK));
    if(hz == 0) {
        OM_RTC->TICK = 0;
    } else {
        OM_RTC->TICK = drv_rcc_clock_get(RCC_CLK_RTC) / (uint32_t)hz;
    }
}

void drv_rtc_wait_clocks(OM_RTC_Type *om_rtc, uint32_t clocks)
{
    uint32_t now, start = om_rtc->CNT;
    uint32_t delta;
    do {
        now = om_rtc->CNT;
        delta = ((now - start) > 0xFFFFFFFF/2) ? start-now : now-start;
    } while (delta < clocks);
}

__RAM_CODE uint32_t drv_rtc_read(OM_RTC_Type *om_rtc)
{
    uint32_t rtc_cnt;

    OM_CRITICAL_BEGIN();
    while (!OM_RTC->CNT_VALID);
    rtc_cnt = (OM_RTC->CNT);
    OM_CRITICAL_END();

    return rtc_cnt;
}

#if (RTE_RTC_REGISTER_CALLBACK)
void drv_rtc_register_isr_callback(drv_isr_callback_t isr_cb)
{
    rtc_env.isr_cb = isr_cb;
}
#endif /* (RTE_RTC_REGISTER_CALLBACK) */

__WEAK void drv_rtc_isr_callback(void)
{
    #if (RTE_RTC_REGISTER_CALLBACK)
    if (rtc_env.isr_cb != NULL) {
        rtc_env.isr_cb(om_rtc, event, (void* )(om_rtc->CNT), NULL);
    }
    #endif /* (RTE_RTC_REGISTER_CALLBACK) */
}

void drv_rtc_set_alarm0(uint32_t time)
{
  while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
  OM_RTC->ALARM0 = time;
}

#endif  /* (RTE_RTC) */

/** @} */
