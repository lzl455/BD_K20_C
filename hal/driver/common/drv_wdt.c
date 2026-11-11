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
 * @file     drv_wdt.c
 * @brief    wdt driver
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
#if (RTE_WDT)
#include <stddef.h>
#include "drv_wdt.h"


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
    #if (RTE_WDT_REGISTER_CALLBACK)
    drv_isr_callback_t   isr_cb;
    #endif /* (RTE_WDT_REGISTER_CALLBACK) */
    uint32_t             start_value;
} wdt_env_t;


/*******************************************************************************
 * CONST & VARIABLES
 */
static wdt_env_t wdt_env = {
    #if (RTE_WDT_REGISTER_CALLBACK)
    .isr_cb       = NULL,
    #endif /* (RTE_WDT_REGISTER_CALLBACK) */
    .start_value  = 0,
};


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_wdt_init(OM_WDT_Type *om_wdt)
{
    drv_wdt_control(om_wdt, WDT_CONTROL_CLK_ENABLE, NULL);

    om_wdt->CR = WDT_CR_SLP_WDT_STOP_MASK | WDT_CR_DBG_WDT_STOP_MASK;
    while(om_wdt->CR & WDT_CR_SYNC_FLAG_MASK);
    wdt_env.start_value = 10000 * 32 - 1;
    om_wdt->SV = (0xA5000000 | wdt_env.start_value);
    while(om_wdt->SV & WDT_SV_SYNC_FLAG_MASK);

    NVIC_ClearPendingIRQ(WDT_IRQn);
    NVIC_SetPriority(WDT_IRQn, RTE_WDT_IRQ_PRIORITY);
    NVIC_DisableIRQ(WDT_IRQn);

    return OM_ERROR_OK;
}

void drv_wdt_keep_alive(OM_WDT_Type *om_wdt)
{
    om_wdt->SV = (0xA5000000 | wdt_env.start_value);
}

void *drv_wdt_control(OM_WDT_Type *om_wdt, wdt_control_t control, void *argu)
{
    switch (control) {
        case WDT_CONTROL_CLK_DISABLE:
            if ((uint32_t)om_wdt == (uint32_t)OM_WDT) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_WDT, 0U);
                break;
            }
            break;
        case WDT_CONTROL_CLK_ENABLE:
            if ((uint32_t)om_wdt == (uint32_t)OM_WDT) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_WDT, 1U);
                break;
            }
            break;
        case WDT_CONTROL_FEED:
            OM_WDT->SV = (0xA5000000 | (uint32_t)argu);
            break;
        case WDT_CONTROL_STOP_ON_DEBUG:
            if (argu) {
                OM_WDT->CR |= WDT_CR_DBG_WDT_STOP_MASK;
            } else {
                OM_WDT->CR &= ~WDT_CR_DBG_WDT_STOP_MASK;
            }
            while(om_wdt->CR & WDT_CR_SYNC_FLAG_MASK);
            break;
        case WDT_CONTROL_STOP_ON_SLEEP:
            if (argu) {
                OM_WDT->CR |= WDT_CR_SLP_WDT_STOP_MASK;
            } else {
                OM_WDT->CR &= ~WDT_CR_SLP_WDT_STOP_MASK;
            }
            while(om_wdt->CR & WDT_CR_SYNC_FLAG_MASK);
            break;
        case WDT_CONTROL_INT_ENABLE:
            OM_WDT->CR &= ~WDT_CR_INT_MASK_MASK;
            while(om_wdt->CR & WDT_CR_SYNC_FLAG_MASK);
            break;
        case WDT_CONTROL_INT_DISABLE:
            OM_WDT->CR |= WDT_CR_INT_MASK_MASK;
            while(om_wdt->CR & WDT_CR_SYNC_FLAG_MASK);
            break;
    }

    return (void *)OM_ERROR_OK;
}

#if (RTE_WDT_REGISTER_CALLBACK)
void drv_wdt_register_isr_callback(drv_isr_callback_t isr_cb)
{
    wdt_env.isr_cb = isr_cb;
}
#endif /* (RTE_WDT_REGISTER_CALLBACK) */

__WEAK void drv_wdt_isr_callback(OM_WDT_Type *om_wdt, drv_event_t event)
{
    #if (RTE_WDT_REGISTER_CALLBACK)
    if (wdt_env.isr_cb != NULL) {
        wdt_env.isr_cb(om_wdt, event, NULL, NULL);
    }
    #endif /* (RTE_WDT_REGISTER_CALLBACK) */
}

void drv_wdt_isr(OM_WDT_Type *om_wdt)
{
    // read and self clear
    if (om_wdt->CR & WDT_CR_INT_STATUS_MASK) {
        drv_wdt_isr_callback((void *)(om_wdt), DRV_EVENT_COMMON_GENERAL);
    }
}

#endif  /* (RTE_WDT) */

/** @} */
