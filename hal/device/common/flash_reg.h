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
 * @file     sf_reg.h
 * @brief    FLASH Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    FLASH Registers for OnMicro OM62xx
 * @details  FLASH Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __FLASH_REG_H
#define __FLASH_REG_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include "../common/common_reg.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
    __I  uint32_t INTR_STATUS;
    __IO uint32_t RAW_INTR_STATUS;
    __IO uint32_t INTR_MASK;
    __IO uint32_t COMMAND;
    __IO uint32_t COMMAND_DATA0_REG;
    __IO uint32_t COMMAND_DATA1_REG;
    __IO uint32_t ADDRESS_REG;
    __IO uint32_t READ_OPCODE_REG; /* shadow in CPM->FLASH_READ_OPCODE */
    __IO uint32_t CONFIGURATION_0; /* shadow in CPM->FLASH_CLKCTRL */
    __IO uint32_t CONFIGURATION_1;
    __IO uint32_t WP_HOLD_REG;
} OM_FLASH_Type;


/*******************************************************************************
 * MACROS
 */
/* COMMAND register */
#define FLASH_COMMAND_WR_POS                          (0U)
#define FLASH_COMMAND_WR_MASK                         (0x03U << FLASH_COMMAND_WR_POS)
#define FLASH_COMMAND_READ_MASK                       (0x01U << FLASH_COMMAND_WR_POS)
#define FLASH_COMMAND_WRITE_MASK                      (0x02U << FLASH_COMMAND_WR_POS)
#define FLASH_COMMAND_KEEP_CS_POS                     (2U)
#define FLASH_COMMAND_KEEP_CS_MASK                    (0x01U << FLASH_COMMAND_KEEP_CS_POS)
#define FLASH_COMMAND_CMD_BITS_NUM_POS                (4U)
#define FLASH_COMMAND_CMD_BITS_NUM_MASK               (0x0FU << FLASH_COMMAND_CMD_BITS_NUM_POS)
#define FLASH_COMMAND_ADDR_BITS_NUM_POS               (8U)
#define FLASH_COMMAND_ADDR_BITS_NUM_MASK              (0x3FU << FLASH_COMMAND_ADDR_BITS_NUM_POS)
#define FLASH_COMMAND_DUMMY_BITS_NUM_POS              (15U)
#define FLASH_COMMAND_DUMMY_BITS_NUM_MASK             (0x1FU << FLASH_COMMAND_DUMMY_BITS_NUM_POS)
#define FLASH_COMMAND_DATA_BYTES_NUM_POS              (20U)
#define FLASH_COMMAND_DATA_BYTES_NUM_MASK             (0x1FFU << FLASH_COMMAND_DATA_BYTES_NUM_POS)

/* CONFIGURATION_0 register */
#define FLASH_CONFIGURATION_0_CLOCK_DIV_POS           (0U)
#define FLASH_CONFIGURATION_0_CLOCK_DIV_MASK          (0x0FU << FLASH_CONFIGURATION_0_CLOCK_DIV_POS)
#define FLASH_CONFIGURATION_0_DLY_SAMPLE_POS          (8U)
#define FLASH_CONFIGURATION_0_DLY_SAMPLE_MASK         (0x03U << FLASH_CONFIGURATION_0_DLY_SAMPLE_POS)
#define FLASH_CONFIGURATION_0_FE_DLY_SAMPLE_POS       (10U)
#define FLASH_CONFIGURATION_0_FE_DLY_SAMPLE_MASK      (0x01U << FLASH_CONFIGURATION_0_FE_DLY_SAMPLE_POS)

/* CONFIGURATION_1 register */
#define FLASH_CONFIGURATION_1_CMD_WIDTH_POS           (0U)
#define FLASH_CONFIGURATION_1_CMD_WIDTH_MASK          (0x03U << FLASH_CONFIGURATION_1_CMD_WIDTH_POS)
#define FLASH_CONFIGURATION_1_ADDR_WIDTH_POS          (4U)
#define FLASH_CONFIGURATION_1_ADDR_WIDTH_MASK         (0x03U << FLASH_CONFIGURATION_1_ADDR_WIDTH_POS)
#define FLASH_CONFIGURATION_1_DATA_WIDTH_POS          (8U)
#define FLASH_CONFIGURATION_1_DATA_WIDTH_MASK         (0x03U << FLASH_CONFIGURATION_1_DATA_WIDTH_POS)

/* SPI Flash Commands listing. */
#define FLASH_CMD_FREAD                  0x0Bu        /* Fast Read */
#define FLASH_CMD_READ                   0x03u        /* Read (low power) */
#define FLASH_CMD_DREAD                  0x3Bu        /* Dual output Read */
#define FLASH_CMD_2READ                  0xBBu        /* 2x I/O Read */
#define FLASH_CMD_QREAD                  0x6Bu        /* Quad output Read */
#define FLASH_CMD_4READ                  0xEBu        /* 4x I/O Read */

#define FLASH_CMD_PAGE_PROGRAM           0x02u        /* Page Program */
#define FLASH_CMD_PAGE_ERASE             0x81u        /* Page Erase, Puya/TH/XTX only */
#define FLASH_CMD_SECTOR_ERASE           0x20u        /* Sector Erase in 4KB */
#define FLASH_CMD_BLOCK_ERASE_32K        0x52u        /* Block Erase in 32KB */
#define FLASH_CMD_BLOCK_ERASE_64k        0xD8u        /* Block Erase in 64KB */
#define FLASH_CMD_CHIP_ERASE             0xC7u        /* Chip Erase */

#define FLASH_CMD_WRITE_DIS              0x04u        /* Write Disable */
#define FLASH_CMD_WRITE_EN               0x06u        /* Write Enable */
#define FLASH_CMD_READ_STATUS_LOW        0x05u        /* Read Status Register */
#define FLASH_CMD_READ_STATUS_HIGH       0x35u        /* Read Status Register high byte */
#define FLASH_CMD_WRITE_STATUS           0x01u        /* Write Status Register */

#define FLASH_CMD_READ_JEDEC_ID          0x9Fu        /* Read JEDEC ID */
#define FLASH_CMD_DEEP_POWER_DOWN_ENTER  0xB9u        /* Enter Deep Power-down mode */
#define FLASH_CMD_DEEP_POWER_DOWN_EXIT   0xABu        /* Release Deep Power-down mode */
#define FLASH_CMD_READ_UNIQUE_ID         0x4Bu        /* Read Unique ID, Puya/TH/XTX only */

/* Status Register in NVM. */
#define SFLASH_SR_WIP                   (1u << 0)    /* Write in progress */
#define SFLASH_SR_WEL                   (1u << 1)    /* Write enable latch */
#define	SFLASH_SR_BP0                   (1u << 2)    /* Block protect 0 */
#define	SFLASH_SR_BP1                   (1u << 3)    /* Block protect 1 */
#define	SFLASH_SR_BP2                   (1u << 4)    /* Block protect 2 */
#define	SFLASH_SR_SRP0                  (1u << 7)    /* SR write protect */
#define	SFLASH_SR_SRP1                  (1u << 8)    /* SR write protect */
#define SFLASH_SR_QE                    (1u << 9)    /* Quad enable */
#define SFLASH_SR_LB1                   (1u << 11)   /* OTP */
#define SFLASH_SR_LB2                   (1u << 12)   /* OTP */
#define SFLASH_SR_LB3                   (1u << 13)   /* OTP */
#define SFLASH_SR_CMP                   (1u << 14)   /* conjunction BPx */


#ifdef __cplusplus
}
#endif


#endif  /* __FLASH_REG_H */


/** @} */
