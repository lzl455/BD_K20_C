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
 * @file     drv_ledc.c
 * @brief    ledc driver
 * @date     23. May 2024
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
#include <string.h>
#include "RTE_driver.h"
#if (RTE_LEDC)
#include <stddef.h>
#include "drv_ledc.h"
#include "led.h"
#include "main.h"

/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_LEDC_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t    isr_cb;
} ledc_env_t;
#endif /* (RTE_LEDC_REGISTER_CALLBACK) */


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_LEDC_REGISTER_CALLBACK)
static ledc_env_t ledc_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_LEDC_REGISTER_CALLBACK) */


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_ledc_init(OM_LEDC_Type *om_ledc, ledc_config_t *config)
{
    if ((om_ledc == NULL) || (config == NULL)) {
        return OM_ERROR_PARAMETER;
    }

    drv_pmu_ledc_sel(PMU_LEDC_SEL_IO_01);

    DRV_RCC_CLOCK_ENABLE(RCC_CLK_LEDC, 1U);
    NVIC_ClearPendingIRQ(LEDC_IRQn);
    NVIC_SetPriority(LEDC_IRQn, RTE_LEDC_IRQ_PRIORITY);
    NVIC_DisableIRQ(LEDC_IRQn);
    // config timing
    om_ledc->SIG_TIM = (config->long_pulse_cycles << LEDC_SIG_TIM_TL_POS) | config->short_pulse_cycles;
    om_ledc->RST_TIM = config->reset_cycles;

    return OM_ERROR_OK;
}
extern void uart_tx(unsigned char data);
extern bool bargb_valid;

#if (iLED_GAMMA_EN)
// gamma 2.0 校正表: 输入 0~iPWM_MAX(64) -> 输出 0~255，非0输入至少输出1
// 放在RAM(非const)，flash擦写期间中断里调用也可正常访问
static uint8_t led_gamma_tbl[iPWM_MAX+1] =
{
      0,  1,  1,  1,  1,  2,  2,  3,  4,  5,  6,  8,  9, 11, 12, 14,
     16, 18, 20, 22, 25, 27, 30, 33, 36, 39, 42, 45, 49, 52, 56, 60,
     64, 68, 72, 76, 81, 85, 90, 95,100,105,110,115,121,126,132,138,
    143,149,156,162,168,175,182,188,195,202,209,217,224,232,239,247,
    255,
};
#endif

__RAM_CODE om_error_t drv_ledc_write()
{
    __ALIGNED(4) static uint8_t pwm_temp[iLED_MAX*3];

    if(false == bargb_valid)
        return OM_ERROR_OK;
OM_CRITICAL_BEGIN();
    memcpy(pwm_temp, pwm_rgb_tbl, iLED_MAX*3);

#if (iLED_GAMMA_EN)
    {                                           // 亮度档位: LEV4满幅 LEV3 1/2 LEV2 1/4 LEV1 1/8，与原线性档位最大值一致
        uint8_t shift = 0;
        if(iLED_LEV_3 == led_light_lev)
            shift = 1;
        else if(iLED_LEV_2 == led_light_lev)
            shift = 2;
        else if(iLED_LEV_1 == led_light_lev)
            shift = 3;
        for(uint8_t i=0; i<iLED_MAX*3; i++)
        {
            uint8_t v = pwm_temp[i];
            if(0 == v)
                continue;
            if(iPWM_MAX < v)
                v = iPWM_MAX;
            v = (led_gamma_tbl[v] >> shift);
            pwm_temp[i] = (0 == v) ? 1 : v;
        }
    }
#else
    if(iLED_LEV_4 == led_light_lev)
    {
        for(uint8_t i=0; i<iLED_MAX*3; i++)
        {
            if(iPWM_MAX <= pwm_temp[i])
                pwm_temp[i] = 0xFF;
            else
                pwm_temp[i] <<= 2;
        }
    }
    else if(iLED_LEV_3 == led_light_lev)
    {
        for(uint8_t i=0; i<iLED_MAX*3; i++)
            pwm_temp[i] <<= 1;
    }
    else if(iLED_LEV_1 == led_light_lev)
    {
        for(uint8_t i=0; i<iLED_MAX*3; i++)
            pwm_temp[i] >>= 1;
    }
#endif

    OM_LEDC->DMA_CTL = ((uint32_t)pwm_temp << LEDC_DMA_CTL_DMA_ADDR_POS) | (LEDC_DMA_CTL_DMA_LEN_MASK & (iLED_MAX*3));
    // enable ledc
    OM_LEDC->CR |= LEDC_CR_ENABLE_MASK;
OM_CRITICAL_END();

    return OM_ERROR_OK;
}

om_error_t drv_ledc_write_int(OM_LEDC_Type    *om_ledc,
                              uint8_t         *data,
                              uint16_t         data_len)
{
    om_ledc->DMA_CTL = ((uint32_t)data << LEDC_DMA_CTL_DMA_ADDR_POS) | (LEDC_DMA_CTL_DMA_LEN_MASK & data_len);
    // enable ledc and interrupt
    om_ledc->CR |= (LEDC_CR_INT_ENABLE_MASK + LEDC_CR_ENABLE_MASK);

    return OM_ERROR_OK;
}

#if (RTE_LEDC_REGISTER_CALLBACK)
void drv_ledc_register_isr_callback(OM_LEDC_Type *om_ledc, drv_isr_callback_t isr_cb)
{
    ledc_env.isr_cb = isr_cb;
}
#endif /* (RTE_LEDC_REGISTER_CALLBACK) */

__WEAK void drv_ledc_isr_callback(OM_LEDC_Type *om_ledc, drv_event_t event)
{
    #if (RTE_LEDC_REGISTER_CALLBACK)
    if (ledc_env.isr_cb != NULL) {
        ledc_env.isr_cb(om_ledc, event, NULL, NULL);
    }
    #endif /* (RTE_LEDC_REGISTER_CALLBACK) */
}

void drv_ledc_isr(OM_LEDC_Type *om_ledc)
{
    if (om_ledc->CR & LEDC_CR_INT_RAW_STATUS_MASK) {
        om_ledc->CR |= LEDC_CR_INT_RAW_STATUS_MASK;
        drv_ledc_isr_callback((void *)om_ledc, DRV_EVENT_COMMON_GENERAL);
    }
}


#endif  /* (RTE_LEDC) */

/** @} */
