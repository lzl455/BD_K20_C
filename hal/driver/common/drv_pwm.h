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
 * @file     drv_pwm.h
 * @brief    PWM Driver
 * @date     06. Oct 2023
 * @author   OnMicro SW Team
 *
 * @defgroup PWM PWM
 * @ingroup  HAL_Driver
 * @brief    PWM Driver.
 * @details  PWM Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_PWM_H
#define __DRV_PWM_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_PWM)
#include "om_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup pwm_pre_scale_t PWM pre_scale factor type
 * @{
 */
typedef enum {
    PWM_PRE_SCALE_1   = 0U,  /**< PWM frequency pre_scale factor is 1/1 clock */
    PWM_PRE_SCALE_2   = 1U,  /**< PWM frequency pre_scale factor is 1/2 clock */
    PWM_PRE_SCALE_8   = 2U,  /**< PWM frequency pre_scale factor is 1/8 clock */
    PWM_PRE_SCALE_32  = 3U,  /**< PWM frequency pre_scale factor is 1/32 clock */
} pwm_pre_scale_t;
/**
 * @}
 */

/**
 * @defgroup pwm_channel_t PWM channel type
 * @{
 */
typedef enum {
    PWM_CHANNEL0     = 1U << 0,  /**< PWM channel 0 */
    PWM_CHANNEL1     = 1U << 1,  /**< PWM channel 1 */
    PWM_CHANNEL2     = 1U << 2,  /**< PWM channel 2 */
    PWM_CHANNEL3     = 1U << 3,  /**< PWM channel 3 */
    PWM_CHANNEL4     = 1U << 4,  /**< PWM channel 4 */
    PWM_CHANNEL5     = 1U << 5,  /**< PWM channel 5 */
} pwm_channel_t;
/**
 * @}
 */

/**
 * @brief DRV_PWM Channel configuration stucture
 * @{
 */
typedef struct {
    uint8_t              output_en;       /**< The PWM channel output enable or disable configuration */
    pwm_channel_t        channel;         /**< The PWM channel, see @ref pwm_channel_t */
    uint8_t              initial_level;   /**< The PWM initial level selected, non-active level(0) or active level(1) */
    uint8_t              active_level;    /**< The PWM active level selected, low active(0) or high active(1) */
    uint16_t             inactive_width;  /**< The PWM inactive level width, range in[0, 4095] */
} pwm_channel_config_t;
/**
 * @}
 */

/**
 * @defgroup pwm_control_t DRV_PWM control type
 * @{
 */
typedef enum {
    PWM_CONTROL_RESET               = 0U,     /**< Reset PWM */
    PWM_CONTROL_CLK_DISABLE         = 1U,     /**< Disable PWM clock */
    PWM_CONTROL_CLK_ENABLE          = 2U,     /**< Enable PWM clock */
} pwm_control_t;
/**
 * @}
 */

/**
 * @brief DRV_PWM configuration init stucture
 * @{
 */
typedef struct {
    uint16_t          period;    /**< PWM period, range in[1, 4095] */
    pwm_pre_scale_t   pre_scale; /**< PWM pre_scale factor, see @ref pwm_pre_scale_t */
} pwm_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief PWM initialization
 *
 * @param om_pwm   The PWM device address
 * @param config   Configuration for PWM
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_pwm_init(OM_PWM_Type *om_pwm, const pwm_config_t *config);

/**
 *******************************************************************************
 * @brief PWM channel config
 *
 * @param om_pwm           The PWM device address
 * @param channel_config   Configuration for PWM channel
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_pwm_channel_config(OM_PWM_Type *om_pwm, const pwm_channel_config_t *channel_config);

/**
 *******************************************************************************
 * @brief  start specific pwm channel
 *
 * @param om_pwm    The PWM device address
 * @param channel   The PWM channel, see @ref pwm_channel_t
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_pwm_start(OM_PWM_Type *om_pwm, pwm_channel_t channel);

/**
 *******************************************************************************
 * @brief  stop specific pwm channel
 *
 * @param om_pwm   The PWM device address
 * @param channel  The PWM channel, see @ref pwm_channel_t
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_pwm_stop(OM_PWM_Type *om_pwm, pwm_channel_t channel);

/**
 *******************************************************************************
 * @brief Control PWM interface
 *
 * @param om_pwm      The PWM device address
 * @param control        The control operation type, see @ref pwm_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - PWM_CONTROL_CLK_DISABLE           Disable PWM clock,argu=NULL
 *                       - PWM_CONTROL_CLK_ENABLE            Enable PWM clock,argu=NULL
 *                       - PWM_CONTROL_RESET                 Reset PWM, argu=NULL
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
extern void *drv_pwm_control(OM_PWM_Type *om_pwm, pwm_control_t control, void *argu);

#ifdef __cplusplus
}
#endif

#endif  /* (RTE_PWM) */

#endif  /* __DRV_PWM_H */

/** @} */
