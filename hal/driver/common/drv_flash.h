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
 * @file     drv_flash.h
 * @brief    FLASH Driver
 * @date     16. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup FLASH FLASH
 * @ingroup  HAL_Driver
 * @brief    FLASH Driver.
 * @details  FLASH Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_FLASH)
#include "om_driver.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup flash_erase_t FLASH erase type
 * @{
 */
typedef enum {
    FLASH_ERASE_PAGE       = FLASH_CMD_PAGE_ERASE,
    FLASH_ERASE_SECTOR     = FLASH_CMD_SECTOR_ERASE,
    FLASH_ERASE_BLOCK_32K  = FLASH_CMD_BLOCK_ERASE_32K,
    FLASH_ERASE_BLOCK_64K  = FLASH_CMD_BLOCK_ERASE_64k,
    FLASH_ERASE_CHIP       = FLASH_CMD_CHIP_ERASE,
} flash_erase_t;
/**
 * @}
 */

/**
 * @defgroup flash_xip_opcode_t DRV_FLASH read mode type
 * @{
 */
typedef enum {
    RCC_XIP_OPCODE_FREAD  = FLASH_CMD_FREAD,   /**< Fast read */
    RCC_XIP_OPCODE_DREAD  = FLASH_CMD_DREAD,   /**< Dual output Read */
    RCC_XIP_OPCODE_2READ  = FLASH_CMD_2READ,   /**< 2x I/O Read */
    RCC_XIP_OPCODE_QREAD  = FLASH_CMD_QREAD,   /**< Quad output Read */
    RCC_XIP_OPCODE_4READ  = FLASH_CMD_4READ,   /**< 4x I/O Read */
} flash_xip_opcode_t;
/**
 * @}
 */

/**
  * @brief DRV_FLASH configuration init structure
  * @{
  */
typedef struct {
    uint8_t             flash_dly_cycle;     /**< The number of the half cycle of high frequency (XOHI or SYSPLL),range in[0,3] */
    flash_xip_opcode_t  xip_opcode;          /**< Set 1/2/4 wire mode when XIP in sflash, see @ref rcc_xip_opcode_t type */
} flash_config_t;
/**
  * @}
  */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief                          Initialize the FLASH_CTRL controller for FLASH device
 *
 * @param flash_config             The FLASH configuration structure, see @ref flash_config_t
 *
 * @return                         status, see@ref om_error_t
 *******************************************************************************
 */
extern __RAM_CODE om_error_t drv_flash_init(void);

/**
 *******************************************************************************
 * @brief                          Read data from FLASH
 *
 * @param om_flash                 The FLASH_CTRL controller address,pointer to FLASH_CTRL peripheral
 * @param offset_addr                 Flash address to program
 * @param data                     The data pointer of the data to be read from external device
 * @param data_len                 The date length in words
 *
 * @return                         status, see@ref om_error_t
 *******************************************************************************
 */
extern __RAM_CODE om_error_t drv_flash_read(uint32_t      offset_addr,
                                            uint8_t            *data,
                                            uint32_t         data_len);
/**
 *******************************************************************************
 * @brief                          Write data to FLASH DATA,.
 *                                 Note: Internal fixation supports 4-wire writing.
 * @param offset_addr                 Flash address to program
 * @param data                     The data pointer of the data to be write to external device
 * @param data_len                 The date length in words
 *
 * @return                         status, see@ref om_error_t
 *******************************************************************************
 */
extern __RAM_CODE om_error_t drv_flash_write(uint32_t         offset_addr,
                                             uint8_t               *data,
                                             uint32_t            data_len);
/**
 *******************************************************************************
 * @brief                          Erase FLASH DATA
 * @param offset_addr                 Flash base address to be erased, aligned to erase_type size
 * @param erase_type               The erase size, see @ref flash_erase_t
 *
 * @return                         status, see@ref om_error_t
 *******************************************************************************
 */
extern __RAM_CODE om_error_t drv_flash_erase(uint32_t         offset_addr,
                                             flash_erase_t     erase_type);
/**
 *******************************************************************************
 * @brief                          The FLASH enters low power mode
 *
 * @return                         None
 *******************************************************************************
 */
extern __RAM_CODE void drv_flash_enter_deeppowerdown(void);

/**
 *******************************************************************************
 * @brief                          The FLASH exits low power mode
 *
 * @return                         None
 *******************************************************************************
 */
extern __RAM_CODE void drv_flash_exit_deeppowerdown(void);

#ifdef __cplusplus
}
#endif
#endif  /* (RTE_FLASH) */

#endif  /* __DRV_FLASH_H */

/** @} */
