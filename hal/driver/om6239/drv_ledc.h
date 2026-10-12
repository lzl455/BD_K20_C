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
 * @file     drv_ledc.h
 * @brief    LEDC Driver
 * @date     23. May 2024
 * @author   OnMicro SW Team
 *
 * @defgroup LEDC LEDC
 * @ingroup  HAL_Driver
 * @brief    LEDC Driver.
 * @details  LEDC Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_LEDC_H
#define __DRV_LEDC_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_LEDC)
#include "om_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @brief DRV_LEDC configuration init stucture
 * @{
 */
typedef struct {
    uint32_t reset_cycles;       /**< LEDC reset low time, present reset_cycles+1 cycles, unit is 1/48 us */
    uint16_t long_pulse_cycles;  /**< LEDC long pulse time, present long_pulse_cycles+1 cycles, unit is 1/48 us */
    uint16_t short_pulse_cycles; /**< LEDC short pulse time, present short_pulse_cycles+1 cycles, unit is 1/48 us */
} ledc_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Initialize the LEDC with parameters in ledc_config_t
 *
 * @param om_ledc        The LEDC device address
 * @param config            The configuration structure pointer, see @ref ledc_config_t
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_ledc_init(OM_LEDC_Type *om_ledc, ledc_config_t *config);

/**
 *******************************************************************************
 * @brief  ledc write by polling
 *
 * @param om_ledc   The LEDC device address
 * @param data      The data pointer of the data to be write to dma
 * @param data_len  The date length in bytes, and data_len < 512
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_ledc_write();

/**
 *******************************************************************************
 * @brief  ledc write by interrupt
 *
 * @param om_ledc   The LEDC device address
 * @param data      The data pointer of the data to be write to dma
 * @param data_len  The date length in bytes, and data_len < 512
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_ledc_write_int(OM_LEDC_Type *om_ledc, uint8_t *data, uint16_t data_len);

#if (RTE_LEDC_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register interrupt service routine callback for specified LEDC device interrupt
 *
 * @param om_ledc        The LEDC device address
 * @param isr_cb          The event callback function, see @ref drv_isr_callback_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_ledc_register_isr_callback(OM_LEDC_Type *om_ledc, drv_isr_callback_t isr_cb);
#endif /* (RTE_LEDC_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for LEDC driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the LEDC driver.
 *
 * @param om_ledc           The LEDC device address
 * @param event             The driver event, which could be DRV_EVENT_COMMON_GENERAL
 *
 * @return None
 *******************************************************************************
 */
extern void drv_ledc_isr_callback(OM_LEDC_Type *om_ledc, drv_event_t event);

/**
 *******************************************************************************
 * @brief The LEDC interrupt service routine function, should be called in LEDC IRQHandler
 *
 * @param om_ledc           The LEDC device address
 *
 * @return None
 *******************************************************************************
 */
extern void drv_ledc_isr(OM_LEDC_Type *om_ledc);


#ifdef __cplusplus
}
#endif
#endif  /* (RTE_LEDC) */

#endif  /* __DRV_LEDC_H */

/** @} */
