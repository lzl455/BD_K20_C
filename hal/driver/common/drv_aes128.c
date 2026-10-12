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
 * @file     drv_aes128.c
 * @brief    aes128 driver
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
#if (RTE_AES128)
#include <stddef.h>
#include <string.h>
#include "om_driver.h"


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @brief DRV_AES128 environment structure
 */
typedef struct aes128_env {
    #if (RTE_AES128_REGISTER_CALLBACK)
    drv_isr_callback_t     isr_cb;
    #endif /* (RTE_AES128_REGISTER_CALLBACK) */
    uint32_t              *output;       /**< plain_cipher */
} aes128_env_t;


/*******************************************************************************
 * CONST & VARIABLES
 */
static aes128_env_t aes128_env = {
    #if (RTE_AES128_REGISTER_CALLBACK)
    .isr_cb            = NULL,
    #endif /* (RTE_AES128_REGISTER_CALLBACK) */
    .output            = NULL,
};


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_aes128_init(OM_AES128_Type *om_aes128, const aes128_config_t *config)
{
    if ((om_aes128 == NULL) || (config == NULL)) {
        return OM_ERROR_PARAMETER;
    }

    drv_aes128_control(om_aes128, AES128_CONTROL_CLK_ENABLE, NULL);
    NVIC_ClearPendingIRQ(AES128_IRQn);
    NVIC_SetPriority(AES128_IRQn, RTE_AES128_IRQ_PRIORITY);
    NVIC_EnableIRQ(AES128_IRQn);
    om_aes128->SWAP = config->is_little_endian;

    return OM_ERROR_OK;
}

om_error_t drv_aes128_encrypt(OM_AES128_Type   *om_aes128,
                              uint32_t          key[4],
                              uint32_t          input[4],
                              uint32_t          output[4])
{
    uint8_t i;
    if (om_aes128 == NULL) {
        return OM_ERROR_PARAMETER;
    }

    for (i = 0U; i < 4U; i++) {
        om_aes128->KEY[i] = key[i];
        om_aes128->DATA[i] = input[i];
    }
    /* start encrypt */
    om_aes128->CTRL = 1;
    /* Encrypt time is 1us @16MHz. */
    while (om_aes128->INT == 0);
    om_aes128->INT = 1; // w1c
    for (i = 0U; i < 4U; i++) {
        output[i] = om_aes128->DATA[i];
    }

    return OM_ERROR_OK;
}

void drv_aes128_cryp(OM_AES128_Type *om_aes128, uint32_t plain_cipher[4])
{
    uint8_t i;
    for (i = 0U; i < 4U; i++) {
        om_aes128->DATA[i] = plain_cipher[i];
    }
    om_aes128->CTRL = 1;
    /* Encrypt time is 1us @16MHz. */
    while (om_aes128->INT == 0);
    om_aes128->INT = 1; // w1c
    for (i = 0U; i < 4U; i++) {
        plain_cipher[i] = om_aes128->DATA[i];
    }
}

om_error_t drv_aes128_encrypt_int(OM_AES128_Type   *om_aes128,
                                  uint32_t          key[4],
                                  uint32_t          input[4],
                                  uint32_t          output[4])
{
    uint8_t i;
    if (om_aes128 == NULL) {
        return OM_ERROR_PARAMETER;
    }

    aes128_env.output = output;

    for (i = 0U; i < 4U; i++) {
        om_aes128->KEY[i] = key[i];
        om_aes128->DATA[i] = input[i];
    }
    /* enable interrupt */
    om_aes128->INTMASK = 1;
    /* start encrypt */
    om_aes128->CTRL = 1;

    return OM_ERROR_OK;
}

void *drv_aes128_control(OM_AES128_Type *om_aes128, aes128_control_t control, void *argu)
{
    switch (control) {
        case AES128_CONTROL_LITTLE_ENDIAN:
            om_aes128->SWAP = AES128_SWAP_KEY_SWAP_MASK | AES128_SWAP_DATA_SWAP_MASK;
            break;
        case AES128_CONTROL_BIG_ENDIAN:
            om_aes128->SWAP = 0U;
            break;
        case AES128_CONTROL_SET_KEY: {
            uint32_t key[4];

            memcpy(key, argu, 16);
            for (uint8_t i = 0U; i < 4U; i++) {
                om_aes128->KEY[i] = key[i];
            }
            break;
        }
        case AES128_CONTROL_CLK_DISABLE:
            if ((uint32_t)om_aes128 == (uint32_t)OM_AES128) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_AES128, 0U);
                break;
            }
            break;
        case AES128_CONTROL_CLK_ENABLE:
            if ((uint32_t)om_aes128 == (uint32_t)OM_AES128) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_AES128, 1U);
                break;
            }
            break;
        case AES128_CONTROL_RESET:
            if ((uint32_t)om_aes128 == (uint32_t)OM_AES128) {
                DRV_RCC_RESET(RCC_RST_AES128);
                break;
            }
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#if (RTE_AES128_REGISTER_CALLBACK)
void drv_aes128_register_isr_callback(drv_isr_callback_t isr_cb)
{
    aes128_env.isr_cb = isr_cb;
}
#endif /* (RTE_AES128_REGISTER_CALLBACK) */

__WEAK void drv_aes128_isr_callback(OM_AES128_Type *om_aes128, drv_event_t event, uint32_t* output, uint8_t encrypt_length)
{
    #if (RTE_AES128_REGISTER_CALLBACK)
    if (aes128_env.isr_cb != NULL) {
        aes128_env.isr_cb(om_aes128, event, (void *)output, (void *)(uint32_t)encrypt_length);
    }
    #endif /* (RTE_AES128_REGISTER_CALLBACK) */
}

void drv_aes128_isr(OM_AES128_Type *om_aes128)
{
    uint16_t i;

    if (om_aes128->INT) {
        /* clear status */
        om_aes128->INT = 1;
        /* disable interrupt */
        om_aes128->INTMASK = 0;
        for (i = 0U; i < 4U; i++) {
            aes128_env.output[i] = om_aes128->DATA[i];
        }
        drv_aes128_isr_callback((void *)(om_aes128), DRV_EVENT_COMMON_GENERAL, aes128_env.output, 4);
    }
}


#endif  /* (RTE_AES128) */

/** @} */
