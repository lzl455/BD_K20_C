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
 * @file     drv_aes128.h
 * @brief    AES128 Driver
 * @date     23. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup AES128 AES128
 * @ingroup  HAL_Driver
 * @brief    AES128 Driver.
 * @details  AES128 Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_AES128_H
#define __DRV_AES128_H

/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_AES128)

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup aes128_is_little_endian_t DRV_AES128 big or little endian type
 * @{
 */
typedef enum {
    AES128_NOT_LITTLE_ENDIAN      = 0U,     /**< key and data use big endian */
    AES128_IS_LITTLE_ENDIAN       = 3U,     /**< key and data use little endian */
} aes128_is_little_endian_t;
/**
 * @}
 */

/**
 * @defgroup aes128_control_t DRV_AES128 control type
 * @{
 */
typedef enum {
    AES128_CONTROL_LITTLE_ENDIAN       = 0U,     /**< Set aes128 key and data use little endian */
    AES128_CONTROL_BIG_ENDIAN          = 1U,     /**< Set aes128 key and data use big endian */
    AES128_CONTROL_SET_KEY             = 2U,     /**< Set aes128 key */
    AES128_CONTROL_CLK_DISABLE         = 3U,     /**< Disable AES128 clock */
    AES128_CONTROL_CLK_ENABLE          = 4U,     /**< Enable AES128 clock */
    AES128_CONTROL_RESET               = 5U,     /**< Reset AES128 */
} aes128_control_t;
/**
 * @}
 */

/**
 * @brief DRV_AES128 configuration structure
 */
typedef struct {
    uint8_t      is_little_endian;   /**< Key and data little-endian and big-endian selected,
                                          0 is big-endian 3 is little-endian */
} aes128_config_t;


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Control AES128 interface
 *
 * @param om_aes128      The AES128 device address
 * @param control        The control operation type, see @ref aes128_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - AES128_CONTROL_LITTLE_ENDIAN         AES key and data use little endian,argu=NULL
 *                       - AES128_CONTROL_BIG_ENDIAN            AES key and data use big endian,argu=NULL
 *                       - AES128_CONTROL_SET_KEY               AES set key, argu is pointed to key
 *                       - AES128_CONTROL_CLK_DISABLE           Disable AES128 clock,argu=NULL
 *                       - AES128_CONTROL_CLK_ENABLE            Enable AES128 clock,argu=NULL
 *                       - AES128_CONTROL_RESET                 Reset AES128, argu=NULL
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
extern void *drv_aes128_control(OM_AES128_Type *om_aes128, aes128_control_t control, void *argu);

/**
 *******************************************************************************
 * @brief Initialize the AES128 with parameters in aes_config_t
 *
 * @param om_aes128         The AES128 device address
 * @param config            The configuration structure pointer, see @ref aes_config_t
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_aes128_init(OM_AES128_Type *om_aes128, const aes128_config_t *config);

/**
 *******************************************************************************
 * @brief AES128 encrypt in polling mode
 *
 * @param om_aes128     The AES128 device address
 * @param key[4]           key
 * @param input[4]         plaintext
 * @param output[4]        ciphertext
 *
 * @return              status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_aes128_encrypt(OM_AES128_Type   *om_aes128,
                                     uint32_t          key[4],
                                     uint32_t          input[4],
                                     uint32_t          output[4]);

/**
 *******************************************************************************
 * @brief AES128 encrypt in polling mode
 *
 * @param om_aes128  The AES128 device address
 * @param plain_cipher[4]  plaintext and ciphertext
 *******************************************************************************
 */
extern void drv_aes128_cryp(OM_AES128_Type *om_aes128, uint32_t plain_cipher[4]);

/**
 *******************************************************************************
 * @brief AES128 encrypt in interrupt mode
 *
 * @param om_aes128     The AES128 device address
 * @param key[4]        key
 * @param input[4]      plaintext
 * @param output[4]     ciphertext
 *
 * @return              status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_aes128_encrypt_int(OM_AES128_Type *om_aes128,
                                         uint32_t          key[4],
                                         uint32_t          input[4],
                                         uint32_t          output[4]);

#if (RTE_AES128_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register event callback for AES128 interrupt
 *
 * @param isr_cb Pointer to callback
 *
 * @return None
 *******************************************************************************
 */
extern void drv_aes128_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* (RTE_AES128_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for AES128 driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the AES128 driver
 *
 * @param om_aes128       The AES128 device address
 * @param event           The driver event, which could be DRV_EVENT_COMMON_GENERAL
 * @param output          AES128 output ciphertext
 * @param encrypt_length  Encrypt data length in word
 *
 * @return None
 *******************************************************************************
 */
extern void drv_aes128_isr_callback(OM_AES128_Type *om_aes128, drv_event_t event, uint32_t* output, uint8_t encrypt_length);

/**
 *******************************************************************************
 * @brief Handle AES128 interrupt request.
 *
 * @param om_aes128 Pointer to AES128
 *
 * @return None
 *******************************************************************************
 */
extern void drv_aes128_isr(OM_AES128_Type *om_aes128);

#ifdef __cplusplus
}
#endif
#endif  /* (RTE_AES128) */

#endif  /* __DRV_AES128_H */

/** @} */
