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
 * @file     drv_cortex.c
 * @brief    cortex driver
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
#if (RTE_CORTEX_SYSTICK)
#include <stddef.h>
#include "om_device.h"
#include "drv_common.h"
#include "drv_cortex.h"


/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_SYSTICK_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t      isr_cb;
} cortex_env_t;
#endif


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_SYSTICK_REGISTER_CALLBACK)
static cortex_env_t cortex_env = {
    .isr_cb       = NULL,
};
#endif


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
void drv_systick_init(const systick_config_t *config)
{
    #if !(RTE_CORTEX_SYSTICK_DELAY)
    if (config != NULL) {
        OM_ASSERT((config->reload_val <= 0xFFFFFFUL) && config->reload_val);

        // 1. config systick
        SysTick->CTRL = 0U;
        SysTick->VAL  = 0UL;  /* Load the SysTick Counter Value */
        SysTick->LOAD = config->reload_val;  /* set reload register */
        // 4. start/stop systick
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | ((config->irq_enable) ? SysTick_CTRL_TICKINT_Msk : 0U);
        NVIC_ClearPendingIRQ(SysTick_IRQn);
        if (config->irq_enable) {
            NVIC_EnableIRQ(SysTick_IRQn);
            NVIC_SetPriority(SysTick_IRQn, RTE_SYSTICK_IRQ_PRIORITY);
        } else {
            NVIC_DisableIRQ(SysTick_IRQn);
        }
    }
    #endif  /* (RTE_CORTEX_SYSTICK_DELAY) */
}

#if (RTE_CORTEX_SYSTICK_DELAY)
void drv_systick_delay_cycles(uint32_t cycles)
{
    OM_ASSERT(cycles < (SysTick_LOAD_RELOAD_Msk + 1U));

    uint32_t start_val = SysTick->VAL;
    while (((start_val - SysTick->VAL) & SysTick_VAL_CURRENT_Msk) < cycles);
}

void drv_systick_delay_us(uint32_t us)
{
    uint32_t delay_us;
    uint32_t cycles;

    while (us) {
        delay_us = (us >= 250U * 1000U) ? (250U *1000) : us;
        us -= delay_us;
        cycles = DRV_SYSTICK_US_2_CYCLES_CEIL(delay_us);
        drv_systick_delay_cycles(cycles);
    }
}

void drv_systick_delay_ms(uint32_t ms)
{
    uint32_t delay_ms;
    uint32_t cycles;

    while (ms) {
        delay_ms = (ms >= 250U) ? (250U) : ms;
        ms -= delay_ms;
        cycles = DRV_SYSTICK_MS_2_CYCLES_CEIL(delay_ms);
        drv_systick_delay_cycles(cycles);
    }
}
#endif /* (RTE_CORTEX_SYSTICK_DELAY) */

#if (RTE_SYSTICK_REGISTER_CALLBACK)
void drv_systick_register_isr_callback(drv_isr_callback_t isr_cb)
{
    cortex_env.isr_cb = isr_cb;
}
#endif /* RTE_SYSTICK_REGISTER_CALLBACK */

__WEAK void drv_systick_isr_callback(void)
{
    #if (RTE_SYSTICK_REGISTER_CALLBACK)
    /* Check whether periodic callback functions need to be run */
    if (cortex_env.isr_cb != NULL) {
        (void)cortex_env.isr_cb((void*)SysTick, DRV_EVENT_SYSTICK, NULL, NULL);
    }
    #endif /* (RTE_SYSTICK_REGISTER_CALLBACK) */
}

void drv_systick_isr(void)
{
    drv_systick_isr_callback();
}

#endif  /* (RTE_CORTEX_SYSTICK) */

/** @} */
