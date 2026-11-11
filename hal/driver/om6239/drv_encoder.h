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
 * @file     drv_encoder.h
 * @brief    ENCODER Driver
 * @date     23. May 2024
 * @author   OnMicro SW Team
 *
 * @defgroup ENCODER ENCODER
 * @ingroup  HAL_Driver
 * @brief    ENCODER Driver.
 * @details  ENCODER Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_ENCODER_H
#define __DRV_ENCODER_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_ENCODER)
#include "om_driver.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup encoder_debounce_time_t ENCODER pinmux select type
 * @{
 */
typedef enum {
    ENCODER_PINMUX_SEL_IO_00_01    = 0U,   /**< ENCODER pinmux select: WHEELB=GPIO00, WHEELA=GPIO01 */
    ENCODER_PINMUX_SEL_IO_05_06    = 1U,   /**< ENCODER pinmux select: WHEELB=GPIO05, WHEELA=GPIO06 */
    ENCODER_PINMUX_SEL_IO_20_21    = 2U,   /**< ENCODER pinmux select: WHEELB=GPIO16, WHEELA=GPIO17 */
    ENCODER_PINMUX_SEL_IO_24_25    = 3U,   /**< ENCODER pinmux select: WHEELB=GPIO20, WHEELA=GPIO21 */
} encoder_pinmux_sel_t;
/**
 * @}
 */

/**
 * @defgroup encoder_debounce_time_t ENCODER debounce time type
 * @{
 */
typedef enum {
    ENCODER_DEBOUNCE_TIME_0        = 0U,   /**< ENCODER debounce time 0 */
    ENCODER_DEBOUNCE_TIME_62D5US   = 1U,   /**< ENCODER debounce time 62.5us */
    ENCODER_DEBOUNCE_TIME_125US    = 2U,   /**< ENCODER debounce time 125us */
    ENCODER_DEBOUNCE_TIME_187US    = 3U,   /**< ENCODER debounce time 187us */
    ENCODER_DEBOUNCE_TIME_250US    = 4U,   /**< ENCODER debounce time 250us */
    ENCODER_DEBOUNCE_TIME_312D5US  = 5U,   /**< ENCODER debounce time 312.5us */
    ENCODER_DEBOUNCE_TIME_375US    = 6U,   /**< ENCODER debounce time 375us */
    ENCODER_DEBOUNCE_TIME_437D5US  = 7U,   /**< ENCODER debounce time 437.5us */
    ENCODER_DEBOUNCE_TIME_500US    = 8U,   /**< ENCODER debounce time 500us */
    ENCODER_DEBOUNCE_TIME_562D5US  = 9U,   /**< ENCODER debounce time 562.5us */
    ENCODER_DEBOUNCE_TIME_625US    = 10U,  /**< ENCODER debounce time 625us */
    ENCODER_DEBOUNCE_TIME_687D5US  = 11U,  /**< ENCODER debounce time 687.5us */
    ENCODER_DEBOUNCE_TIME_750US    = 12U,  /**< ENCODER debounce time 750us */
    ENCODER_DEBOUNCE_TIME_812D5US  = 13U,  /**< ENCODER debounce time 812.5us */
    ENCODER_DEBOUNCE_TIME_875US    = 14U,  /**< ENCODER debounce time 875us */
    ENCODER_DEBOUNCE_TIME_1MS      = 15U,  /**< ENCODER debounce time 1ms */
} encoder_debounce_time_t;
/**
 * @}
 */

/**
 * @defgroup encoder_debounce_time_t ENCODER pinmux select type
 * @{
 */
typedef enum {
    ENCODER_MODE_0    = 0U,   /**< ENCODER WHEELA invert disable, WHEELB invert disable */
    ENCODER_MODE_1    = 1U,   /**< ENCODER WHEELA invert enable, WHEELB invert disable */
    ENCODER_MODE_2    = 2U,   /**< ENCODER WHEELA invert disable, WHEELB invert enable */
    ENCODER_MODE_3    = 3U,   /**< ENCODER WHEELA invert enable, WHEELB invert enable */
} encoder_mode_t;
/**
 * @}
 */

/**
 * @defgroup encoder_control_t DRV_ENCODER control type
 * @{
 */
typedef enum {
    ENCODER_CONTROL_START            = 1U,     /**< Start encoder */
    ENCODER_CONTROL_STOP             = 2U,     /**< Stop encoder */
    ENCODER_CONTROL_READ_WHEEL_DATA  = 3U,     /**< Read wheel data */
    ENCODER_CONTROL_WAKEUP_EN        = 4U,     /**< Wakeup enable */
    ENCODER_CONTROL_WAKEUP_DISABLE   = 5U,     /**< Wakeup disenable */
    ENCODER_CONTROL_READ_WHEEL_VALID = 6U,     /**< Wheel data valid flag */
} encoder_control_t;
/**
 * @}
 */

/**
 * @brief DRV_ENCODER configuration init stucture
 * @{
 */
typedef struct {
    encoder_pinmux_sel_t    pinmux_sel;      /**< ENCODER pinmux select , see @ref encoder_pinmux_sel_t */
    encoder_debounce_time_t debounce_time;   /**< ENCODER debounce time, see @ref encoder_debounce_time_t */
    encoder_mode_t          mode;            /**< ENCODER WHEELA&WHEELB invert enable or disable */
} encoder_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Control ENCODER interface
 *
 * @param om_encoder     The ENCODER device address
 * @param control        The control operation type, see @ref encoder_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - ENCODER_CONTROL_STOP              Stop encoder
 *                       - ENCODER_CONTROL_READ_WHEEL_DATA   Read wheel data
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
__STATIC_FORCEINLINE void *drv_encoder_control(OM_ENCODER_Type *om_encoder, encoder_control_t control, void *argu)
{
    uint32_t ret;

    ret = (uint32_t)OM_ERROR_OK;

    switch (control) {
        case ENCODER_CONTROL_START:
            om_encoder->EN |= ENCODER_EN_ENCODER_EN_MASK;
            break;
        case ENCODER_CONTROL_STOP:
            om_encoder->EN &= ~ENCODER_EN_ENCODER_EN_MASK;
            break;
        case ENCODER_CONTROL_READ_WHEEL_DATA:
            ret = om_encoder->CNT;
            break;
        case ENCODER_CONTROL_WAKEUP_EN:
            om_encoder->EN |= ENCODER_EN_WAKEUP_EN_MASK;
            break;
        case ENCODER_CONTROL_WAKEUP_DISABLE:
            om_encoder->EN &= ~ENCODER_EN_WAKEUP_EN_MASK;
            break;
        case ENCODER_CONTROL_READ_WHEEL_VALID:
                ret = om_encoder->VALID;
            break;
        default:
            break;
    }

    return (void *)ret;
}

/**
 *******************************************************************************
 * @brief Initialize the ENCODER with parameters in encoder_config_t
 *
 * @param om_encoder        The ENCODER device address
 * @param config            The configuration structure pointer, see @ref encoder_config_t
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern void drv_encoder_init(void);

/**
 *******************************************************************************
 * @brief  encoder start by interrupt
 *
 * @param om_encoder   The ENCODER device address
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_encoder_read_int(OM_ENCODER_Type *om_encoder);

#if (RTE_ENCODER_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register interrupt service routine callback for specified ENCODER device interrupt
 *
 * @param om_encoder        The ENCODER device address
 * @param isr_cb          The event callback function, see @ref drv_isr_callback_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_encoder_register_isr_callback(OM_ENCODER_Type *om_encoder, drv_isr_callback_t isr_cb);
#endif /* (RTE_ENCODER_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The ENCODER interrupt service routine function, should be called in ENCODER IRQHandler
 *
 * @param om_encoder           The ENCODER device address
 *
 * @return None
 *******************************************************************************
 */
extern void drv_encoder_isr(OM_ENCODER_Type *om_encoder);


#ifdef __cplusplus
}
#endif
#endif  /* (RTE_ENCODER) */

#endif  /* __DRV_ENCODER_H */

/** @} */
