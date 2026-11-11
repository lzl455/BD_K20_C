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
 * @file     drv_pwm.c
 * @brief    pwm driver
 * @date     06. Oct 2023
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
#if (RTE_PWM)
#include <stddef.h>
#include "drv_pwm.h"

/*******************************************************************************
 * MACROS
 */
#define PWM_CHANNEL_MAX        8


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_pwm_init(OM_PWM_Type *om_pwm, const pwm_config_t *config)
{
    if ((om_pwm == NULL) || (config == NULL)) {
        return OM_ERROR_PARAMETER;
    }

    drv_pwm_control(om_pwm, PWM_CONTROL_CLK_ENABLE, NULL);
    om_pwm->PWMPRD = config->period;
    om_pwm->PWMDIV = config->pre_scale;

    return OM_ERROR_OK;
}

om_error_t drv_pwm_channel_config(OM_PWM_Type *om_pwm, const pwm_channel_config_t *channel_config)
{
    uint8_t ch_mask;

    if ((om_pwm == NULL) || (channel_config == NULL)) {
        return OM_ERROR_PARAMETER;
    }

    ch_mask = channel_config->channel;
    for (uint8_t ch = 0U; ch < PWM_CHANNEL_MAX; ch++) {
        if ((ch_mask >> ch) & 1U) {
            register_set(&(om_pwm->PWMCR0), PWM_PWMCR0_CHANNELn_INITIAL_CTL_MASK(ch), (channel_config->initial_level << ch));
            register_set(&(om_pwm->PWMCR1), PWM_PWMCR1_CHANNELn_ACTIVE_CTL_MASK(ch), (channel_config->active_level << ch));
            om_pwm->PWMDC[ch] = channel_config->inactive_width;
        }
    }

    return OM_ERROR_OK;
}

om_error_t drv_pwm_start(OM_PWM_Type *om_pwm, pwm_channel_t channel)
{
    if (om_pwm == NULL) {
        return OM_ERROR_PARAMETER;
    }
    register_set1(&(om_pwm->PWMCON), channel);
    return OM_ERROR_OK;
}

om_error_t drv_pwm_stop(OM_PWM_Type *om_pwm, pwm_channel_t channel)
{
    if (om_pwm == NULL) {
        return OM_ERROR_PARAMETER;
    }
    register_set0(&(om_pwm->PWMCON), channel);
    return OM_ERROR_OK;
}

void *drv_pwm_control(OM_PWM_Type *om_pwm, pwm_control_t control, void *argu)
{
    switch (control) {
        case PWM_CONTROL_RESET:
            if ((uint32_t)om_pwm == (uint32_t)OM_PWM) {
                DRV_RCC_RESET(RCC_RST_PWM);
                break;
            }
            break;
        case PWM_CONTROL_CLK_DISABLE:
            if ((uint32_t)om_pwm == (uint32_t)OM_PWM) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_PWM, 0U);
                break;
            }
            break;
        case PWM_CONTROL_CLK_ENABLE:
            if ((uint32_t)om_pwm == (uint32_t)OM_PWM) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_PWM, 1U);
                break;
            }
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#endif  /* (RTE_PWM) */

/** @} */
