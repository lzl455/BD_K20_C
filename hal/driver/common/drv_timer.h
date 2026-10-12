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
 * @file     drv_timer.h
 * @brief    TIMER Driver
 * @date     18. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup TIMER TIMER
 * @ingroup  HAL_Driver
 * @brief    TIMER Driver
 * @details  TIMER Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_TIMER0)

#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup timer_control_t TIMER control type
 * @{
 */
typedef enum {
    TIMER_CONTROL_RESET             = 0U,    /**< Reset TIMER. argu with NULL, return OM_ERROR_OK */
    TIMER_CONTROL_CLK_DISABLE       = 1U,    /**< Disable TIMER clock. argu with NULL, return OM_ERROR_OK */
    TIMER_CONTROL_CLK_ENABLE        = 2U,    /**< Enable TIMER clock. argu with NULL, return OM_ERROR_OK  */
} timer_control_t;
/**
 * @}
 */

/**
 * @defgroup timer_mode_t TIMER mode type
 * @{
 */
typedef enum {
    TIMER_MODE_0      = 0U,  /**< 24-bit counter/timer */
    TIMER_MODE_1      = 1U,  /**< 32-bit counter/timer */
    TIMER_MODE_2      = 2U,  /**< 16-bit auto-reload timer */
    TIMER_MODE_3      = 3U,  /**< two 16-bit counters/timers */
} timer_mode_t;
/**
 * @}
 */

/**
 * @defgroup timer_type_t TIMER type
 * @{
 */
typedef enum {
    TIMER_TYPE_LOW   = 0U,  /**< Low timer */
    TIMER_TYPE_HIGH  = 1U,  /**< High timer */
} timer_type_t;
/**
 * @}
 */

/**
 * @brief DRV_TIMER configuration init stucture
 * @{
 */
typedef struct {
    timer_mode_t     mode;          /**< Timer mode, see @ref timer_mode_t */
    uint8_t          pre_scaler;    /**< divider for timer clock,range in[0, 63] */
    uint8_t          tl_int_en;     /**< low timer interrupt enable or disable configuration */
    uint8_t          th_int_en;     /**< high timer interrupt enable or disable configuration */
    uint32_t         time;          /**< set time, unit is microsecond */
} timer_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief TIMER initialization
 *
 * @param om_timer     The TIMER device address
 * @param config       Configuration for TIMER, see@ref timer_config_t
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_timer_init(OM_TIMER_Type *om_timer, const timer_config_t *config);

/**
 *******************************************************************************
 * @brief  start TIMER
 *
 * @param om_timer     The TIMER device address
 * @param timer        which timer, see @ref timer_type_t
 *
 * @return status, see @ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_timer_start(OM_TIMER_Type *om_timer, timer_type_t timer);

/**
 *******************************************************************************
 * @brief  stop TIMER
 *
 * @param om_timer     The TIMER device address
 * @param timer        which timer, see @ref timer_type_t
 *
 * @return status, see @ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_timer_stop(OM_TIMER_Type *om_timer, timer_type_t timer);

/**
 *******************************************************************************
 * @brief Control TIMER interface.
 *
 * @param[in] om_timer       Pointer to TIMER
 * @param[in] control        Operation
 * @param[in] argu           Operation argument
 *
 * @return status:           Control status
 *******************************************************************************
 */
extern void *drv_timer_control(OM_TIMER_Type *om_timer, timer_control_t control, void *argu);

#if (RTE_TIMER0_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register event callback for TIMER interrupt
 *
 * @param isr_cb Pointer to callback
 *
 * @return None
 *******************************************************************************
 */
extern void drv_timer_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* (RTE_TIMER0_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for TIMER driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the TIMER driver.
 *
 * @param om_timer The TIMER device address
 * @param event    The driver event, which could be the combination of fallowing events
 *                 @arg DRV_EVENT_LOW_TIMER_OVERFLOW_FLAG:       Low Timer overflow
 *                 @arg DRV_EVENT_HIGH_TIMER_OVERFLOW_FLAG:      high Timer overflow
 *
 * @return None
 *******************************************************************************
 */
extern void drv_timer_isr_callback(OM_TIMER_Type *om_timer, drv_event_t event);

/**
 *******************************************************************************
 * @brief Handle TIMER interrupt request.
 *
 * @param om_timer Pointer to TIMER
 *
 * @return None
 *******************************************************************************
 */
extern void drv_timer_isr(OM_TIMER_Type *om_timer);

#ifdef  __cplusplus
}
#endif

#endif /* (RTE_TIMER0) */

#endif  /* __DRV_TIMER_H */

/** @} */
