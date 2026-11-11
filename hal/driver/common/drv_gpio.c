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
 * @file     drv_gpio.c
 * @brief    gpio driver
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
#if (RTE_GPIO0)
#include <stddef.h>
#include "om_driver.h"


/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_GPIO0_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t   isr_cb;
} gpio_env_t;
#endif /* (RTE_GPIO0_REGISTER_CALLBACK) */


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_GPIO0_REGISTER_CALLBACK)
static gpio_env_t gpio_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_GPIO0_REGISTER_CALLBACK) */


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_gpio_init(const gpio_config_t *gpio_config, uint32_t gpio_config_num)
{
    if (gpio_config == NULL) {
        return OM_ERROR_PARAMETER;
    }

    drv_gpio_control(OM_GPIO0, GPIO_CONTROL_CLK_ENABLE, NULL);
    drv_gpio_control(OM_GPIO0, GPIO_CONTROL_RESET, NULL);
    NVIC_ClearPendingIRQ(WAKEUP_GPIO0_IRQn);
    NVIC_SetPriority(WAKEUP_GPIO0_IRQn, RTE_GPIO0_IRQ_PRIORITY);
    NVIC_EnableIRQ(WAKEUP_GPIO0_IRQn);

    for (uint32_t i = 0; i < gpio_config_num; ++i) {
        if(gpio_config[i].om_gpio) {
            drv_gpio_set_dir(gpio_config[i].om_gpio, GPIO_MASK(gpio_config[i].gpio_idx), gpio_config[i].dir);

            if (gpio_config[i].dir == GPIO_DIR_OUTPUT) {
                drv_gpio_write(gpio_config[i].om_gpio, GPIO_MASK(gpio_config[i].gpio_idx), gpio_config[i].out_val);
            } else {
                drv_gpio_set_trig(gpio_config[i].om_gpio, GPIO_MASK(gpio_config[i].gpio_idx), (gpio_config[i].trig));
            }
        }
    }
    return OM_ERROR_OK;
}

void drv_gpio_set_trig(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, gpio_trig_t trig)
{
    switch (trig) {
        case GPIO_TRIG_NONE:
            om_gpio->INTENCLR    = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            break;
        case GPIO_TRIG_RISING_EDGE:
            om_gpio->INTTYPE1CLR = gpio_mask;
            om_gpio->INTTYPE0SET = gpio_mask;
            om_gpio->INTPOLSET   = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            om_gpio->INTENSET    = gpio_mask;
            break;
        case GPIO_TRIG_FALLING_EDGE:
            om_gpio->INTTYPE1CLR = gpio_mask;
            om_gpio->INTTYPE0SET = gpio_mask;
            om_gpio->INTPOLCLR   = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            om_gpio->INTENSET    = gpio_mask;
            break;
        case GPIO_TRIG_BOTH_EDGE:
            om_gpio->INTTYPE0SET = gpio_mask;
            om_gpio->INTTYPE1SET = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            om_gpio->INTENSET    = gpio_mask;
            break;
        case GPIO_TRIG_HIGH_LEVEL:
            om_gpio->INTTYPE1CLR = gpio_mask;
            om_gpio->INTTYPE0CLR = gpio_mask;
            om_gpio->INTPOLSET   = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            om_gpio->INTENSET    = gpio_mask;
            break;
        case GPIO_TRIG_LOW_LEVEL:
            om_gpio->INTTYPE1CLR = gpio_mask;
            om_gpio->INTTYPE0CLR = gpio_mask;
            om_gpio->INTPOLCLR   = gpio_mask;
            om_gpio->INTSTATUS   = gpio_mask;
            om_gpio->INTENSET    = gpio_mask;
            break;
        default:
            break;
    }
}

void *drv_gpio_control(OM_GPIO_Type *om_gpio, gpio_control_t control, void *argu)
{
    switch (control) {
        case GPIO_CONTROL_CLK_DISABLE:
            #if (RTE_GPIO0)
            if ((uint32_t)om_gpio == (uint32_t)OM_GPIO0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_GPIO0, 0U);
                break;
            }
            #endif  /* (RTE_GPIO0) */
            break;
        case GPIO_CONTROL_CLK_ENABLE:
            #if (RTE_GPIO0)
            if ((uint32_t)om_gpio == (uint32_t)OM_GPIO0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_GPIO0, 1U);
                break;
            }
            #endif  /* (RTE_GPIO0) */
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#if (RTE_GPIO0_REGISTER_CALLBACK)
void drv_gpio_register_isr_callback(drv_isr_callback_t isr_cb)
{
    gpio_env.isr_cb = isr_cb;
}
#endif /* (RTE_GPIO0_REGISTER_CALLBACK) */

#endif  /* (RTE_GPIO0) */


/** @} */
