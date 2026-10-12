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
 * @file     drv_timer.c
 * @brief    timer driver
 * @date     18. Sep 2023
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
#if (RTE_TIMER0)
#include <stddef.h>
#include "om_driver.h"


/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_TIMER0_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t   isr_cb;
} timer_env_t;
#endif /* (RTE_TIMER0_REGISTER_CALLBACK) */


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_TIMER0_REGISTER_CALLBACK)
static timer_env_t timer_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_TIMER0_REGISTER_CALLBACK) */


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_timer_init(OM_TIMER_Type *om_timer, const timer_config_t *config)
{
    uint32_t temp;
    if ((om_timer == NULL) || (config == NULL)) {
        return OM_ERROR_PARAMETER;
    }

    // Enable clock
    drv_timer_control(om_timer, TIMER_CONTROL_CLK_ENABLE, NULL);
    // Config timer mode
    om_timer->TMOD = config->mode;
    // Config pre scaler
    om_timer->TDIV = config->pre_scaler;
    // Config timer
    temp = ((SystemCoreClock / (om_timer->TDIV + 1) / 1000U) * (config->time / 1000U) );
    switch (om_timer->TMOD) {
        case TIMER_MODE_0:
            if (temp > 0xFFFFFFU) {
                return OM_ERROR_PARAMETER;
            }
            om_timer->TL0 = 0xFFFFU - (temp & 0xFU);
            om_timer->TH0 = 0xFFFFU - (temp >> 8U);
            break;
        case TIMER_MODE_1:
            om_timer->TL0 = 0xFFFFU - (temp & 0xFFFFU);
            om_timer->TH0 = 0xFFFFU - (temp >> 16U);
            break;
        case TIMER_MODE_2:
        case TIMER_MODE_3:
            if (temp > 0xFFFFU) {
                return OM_ERROR_PARAMETER;
            }
            om_timer->TL0 = 0xFFFFU - temp;
            om_timer->TH0 = 0xFFFFU - temp;
            break;
        default : break;
    }
    // Config interrupt
    register_set(&(om_timer->TINTMASK), MASK_2REG(TIMER_TINTMASK_TF0_MASK, config->tl_int_en,
                                                  TIMER_TINTMASK_TF1_MASK, config->th_int_en));
    NVIC_ClearPendingIRQ(TIMER0_IRQn);
    NVIC_SetPriority(TIMER0_IRQn, RTE_TIMER0_IRQ_PRIORITY);
    NVIC_EnableIRQ(TIMER0_IRQn);

    return OM_ERROR_OK;
}

om_error_t drv_timer_start(OM_TIMER_Type *om_timer, timer_type_t timer)
{
    if (om_timer == NULL) {
        return OM_ERROR_PARAMETER;
    }

    register_set1(&(om_timer->TCON), TIMER_TCON_TRn_CTRL_MASK(timer));
    return OM_ERROR_OK;
}

om_error_t drv_timer_stop(OM_TIMER_Type *om_timer, timer_type_t timer)
{
    if (om_timer == NULL) {
        return OM_ERROR_PARAMETER;
    }

    register_set0(&(om_timer->TCON), TIMER_TCON_TRn_CTRL_MASK(timer));
    return OM_ERROR_OK;
}

void *drv_timer_control(OM_TIMER_Type *om_timer, timer_control_t control, void *argu)
{
    switch (control) {
        case TIMER_CONTROL_RESET:
            #if (RTE_TIMER0)
            if ((uint32_t)om_timer == (uint32_t)OM_TIMER0) {
                DRV_RCC_RESET(RCC_RST_TIMER0);
                break;
            }
            #endif  /* (RTE_TIMER0) */
            break;
        case TIMER_CONTROL_CLK_DISABLE:
            #if (RTE_TIMER0)
            if ((uint32_t)om_timer == (uint32_t)OM_TIMER0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_TIMER0, 0U);
                break;
            }
            #endif  /* (RTE_TIMER0) */
            break;

        case TIMER_CONTROL_CLK_ENABLE:
            #if (RTE_TIMER0)
            if ((uint32_t)om_timer == (uint32_t)OM_TIMER0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_TIMER0, 1U);
                break;
            }
            #endif  /* (RTE_TIMER0) */
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#if (RTE_TIMER0_REGISTER_CALLBACK)
void drv_timer_register_isr_callback(drv_isr_callback_t isr_cb)
{
    timer_env.isr_cb = isr_cb;
}
#endif /* (RTE_TIMER0_REGISTER_CALLBACK) */

__WEAK void drv_timer_isr_callback(OM_TIMER_Type *om_timer, drv_event_t event)
{
    #if (RTE_TIMER0_REGISTER_CALLBACK)
    if (timer_env.isr_cb != NULL) {
        timer_env.isr_cb(om_timer, event, NULL, NULL);
    }
    #endif /* (RTE_TIMER0_REGISTER_CALLBACK) */
}

void drv_timer_isr(OM_TIMER_Type *om_timer)
{
    drv_event_t event = DRV_EVENT_COMMON_NONE;
    uint32_t if_reg = om_timer->TINT;
    uint32_t ie_reg = om_timer->TINTMASK;
    uint32_t int_val = 0;

    int_val = (if_reg & ie_reg);
    if (int_val) {
        // clear status
        om_timer->TINT |= int_val;
        event = (drv_event_t)int_val;
    }
    drv_timer_isr_callback((void *)(om_timer), event);
}

#endif  /* (RTE_TIMER0) */


/** @} */
