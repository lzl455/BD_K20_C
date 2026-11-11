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
 * @file     rf_reg.h
 * @brief    RF Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    RF Registers for OnMicro OM62xx
 * @details  RF Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __RF_REG_H
#define __RF_REG_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include "common_reg.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
    __I  uint32_t DMA_INT;            // offset: 0x00
    __IO uint32_t DMA_INT_RAW;        // offset: 0x04
    __IO uint32_t DMA_INT_MASK;       // offset: 0x08
    __IO uint32_t DMA_CMD;            // offset: 0x0C
    __IO uint32_t DMA_ADDR;           // offset: 0x10
    __IO uint32_t RFCE;               // offset: 0x14
    __I  uint32_t RX_PW;              // offset: 0x18
    __IO uint32_t rsv1C;              // offset: 0x1C
    __IO uint32_t DFIFO_EN;           // offset: 0x20
    __IO uint32_t CE_PULSE;           // offset: 0x24
    /* since 2022/03/28. */
    __IO uint32_t ABORT;              // offset: 0x28
    __IO uint32_t rsv2c[5];           // offset: 0x2C-0x3c
    __IO uint32_t CONFIG;             // offset: 0x40
    __IO uint32_t EN_AA;              // offset: 0x44
    __IO uint32_t EN_RXADDR;          // offset: 0x48
    __IO uint32_t SETUP_RETR;         // offset: 0x4c
    __IO uint32_t RF_CH;              // offset: 0x50
    __IO uint32_t RF_SETUP;           // offset: 0x54
    __IO uint32_t RF_STATUS;          // offset: 0x58
    __IO uint32_t RSSI;               // offset: 0x5c
    union {
        __IO uint32_t RX_ADDR_P0;     // offset: 0x60
        __IO uint32_t ACCESS_ADDR;
    };
    __IO uint32_t RX_ADDR_P0_H;       // offset: 0x64
    __IO uint32_t RX_ADDR_P1;         // offset: 0x68
    union {
        __IO uint32_t RX_ADDR_P2;     // offset: 0x6c
        __IO uint32_t BLE_CTL;
    };
    union {
        __IO uint32_t TX_ADDR;        // offset: 0x70
        __IO uint32_t TX_ADVA;
    };
    union {
        __IO uint32_t TX_ADDR_H;      // offset: 0x74
        __IO uint32_t TX_ADVA_H;
    };
    union {
        __IO uint32_t RX_PW_PIPE[3];  // offset: 0x78-0x80
        __IO uint32_t TX_HEADER[3];
    };
    __I  uint32_t FIFO_STATUS;        // offset: 0x84
    __IO uint32_t DYNPD;              // offset: 0x88
    __IO uint32_t FEATURE;            // offset: 0x8c
    __IO uint32_t SETUP_V;            // offset: 0x90
    __IO uint32_t PRE_GURD;           // offset: 0x94
    __I  uint32_t RX_ADVA;            // offset: 0x98
    __I  uint32_t RX_ADVA_H;          // offset: 0x9c
    __I  uint32_t RX_HEADER[3];       // offset: 0xa0-0xa8
    __I  uint32_t RX_STATUS[3];       // offset: 0xac-0xb4
    __I  uint32_t DFIFO_STATUS;       // offset: 0xB8
    __IO uint32_t SETUP_DELAY;        // offset: 0xBC
    __IO uint32_t CRC_INIT;           // offset: 0xC0
    __IO uint32_t LINE;               // offset: 0xC4
    __IO uint32_t PLL_CTL0;           // offset: 0xC8
    __IO uint32_t PLL_CTL1;           // offset: 0xCC
    __IO uint32_t CAL_CTL;            // offset: 0xD0
    __IO uint32_t STATE;              // offset: 0xD4
    __IO uint32_t CHAN;               // offset: 0xD8
    __IO uint32_t FDEV;               // offset: 0xDC
    __IO uint32_t DAC_RANGE;          // offset: 0xE0
    __IO uint32_t CTUNING;            // offset: 0xE4
    __IO uint32_t FTUNING;            // offset: 0xE8
    __IO uint32_t RX_CTRL;            // offset: 0xEC
    __IO uint32_t rvF0;               // offset: 0xF0
    __IO uint32_t FAGC_CTRL_1;        // offset: 0xF4
    __IO uint32_t DOC_DACI;           // offset: 0xF8
    __IO uint32_t DOC_DACQ;           // offset: 0xFC
    __IO uint32_t AGC_CTRL;           // offset: 0x100
    __IO uint32_t AGC_GAIN;           // offset: 0x104
    __IO uint32_t RF_IVGEN;           // offset: 0x108
    __IO uint32_t TEST_PKDET;         // offset: 0x10C
    __IO uint32_t rsv110;             // offset: 0x110
    __IO uint32_t WHITELIST0;         // offset: 0x114
    __IO uint32_t WHITELIST0_H;       // offset: 0x118
    __IO uint32_t WHITELIST1;         // offset: 0x11C
    __IO uint32_t WHITELIST1_H;       // offset: 0x120
    __IO uint32_t WHITELIST_CR;       // offset: 0x124
    __IO uint32_t OBSERVE_TX;         // offset: 0x128
    /* OM6236 */
    __IO uint32_t RX_CFO_EST;         // offset: 0x12C
    __IO uint32_t RX_DBG_CTRL;        // offset: 0x130
} OM_RF_Type;


/* RX_STATUS register */
#define RF_RX_STATUS_SYNC_ERR_POS       0U
#define RF_RX_STATUS_SYNC_ERR_MASK     (1U << 0)
#define RF_RX_STATUS_TYPE_ERR_POS       1U
#define RF_RX_STATUS_TYPE_ERR_MASK     (1U << 1)
#define RF_RX_STATUS_LEN_ERR_POS        2U
#define RF_RX_STATUS_LEN_ERR_MASK      (1U << 2)
#define RF_RX_STATUS_CRC_ERR_POS        3U
#define RF_RX_STATUS_CRC_ERR_MASK      (1U << 3)
#define RF_RX_STATUS_NESN_ERR_POS       4U
#define RF_RX_STATUS_NESN_ERR_MASK     (1U << 4)
#define RF_RX_STATUS_SN_ERR_POS         5U
#define RF_RX_STATUS_SN_ERR_MASK       (1U << 5)
#define RF_RX_STATUS_LAST_EMPTY_POS     6U
#define RF_RX_STATUS_LAST_EMPTY_MASK   (1U << 6)

#ifdef __cplusplus
}
#endif


#endif  /* __RF_REG_H */


/** @} */
