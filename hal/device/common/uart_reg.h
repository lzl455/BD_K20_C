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
 * @file     uart_reg.h
 * @brief    UART Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    UART Registers for OnMicro OM62xx
 * @details  UART Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __UART_REG_H
#define __UART_REG_H


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
    __IO uint32_t INTR_STATUS;
    __IO uint32_t INTR_MASK;
    __IO uint32_t SCON;
    __IO uint32_t SMOD;
    __IO uint32_t SREL;
    __IO uint32_t SBUF;
    __IO uint32_t FIFO_TH;
    __IO uint32_t FIFO_ST;
} OM_UART_Type;


/*******************************************************************************
 * MACROS
 */
/* INTR_STATUS register */
#define RX_INT_STATUS_POS            (0)
#define RX_INT_STATUS_MASK           (1u << RX_INT_STATUS_POS)
#define TX_INT_STATUS_POS            (1)
#define TX_INT_STATUS_MASK           (1u << TX_INT_STATUS_POS)
#define RX_BUSY_POS                  (2)
#define RX_BUSY_MASK                 (1u << RX_BUSY_POS)
#define TX_BUSY_POS                  (3)
#define TX_BUSY_MASK                 (1u << TX_BUSY_POS)
#define RX_FIFO_CROSS_TH_POS         (4)
#define RX_FIFO_CROSS_TH_MASK        (1u << RX_FIFO_CROSS_TH_POS)
#define TX_FIFO_CROSS_TH_POS         (5)
#define TX_FIFO_CROSS_TH_MASK        (1u << TX_FIFO_CROSS_TH_POS)

/* INTR_MASK registers */
#define INTR_RX_POS                  (0)
#define INTR_RX_MASK                 (1u << INTR_RX_POS)
#define INTR_TX_POS                  (1)
#define INTR_TX_MASK                 (1u << INTR_TX_POS)
#define INTR_RX_FIFO_INT_POS         (4)
#define INTR_RX_FIFO_INT_MASK        (1u << INTR_RX_FIFO_INT_POS)
#define INTR_TX_FIFO_INT_POS         (5)
#define INTR_TX_FIFO_INT_MASK        (1u << INTR_TX_FIFO_INT_POS)

/* SCON register */
#define SCON_REN_POS                 (2)
#define SCON_REN_MASK                (1u << SCON_REN_POS)
#define SCON_SM2_POS                 (3)
#define SCON_SM2_MASK                (1u << SCON_SM2_POS)
#define SCON_SM_POS                  (4)
#define SCON_SM_MASK                 (0x3 << SCON_SM_POS)
#define SCON_SM_MODE0_MASK           (0x1u << SCON_SM_POS)
#define SCON_SM_MODE1_MASK           SCON_SM_MASK
#define SCON_RX_FIFO_EN_POS          (6)
#define SCON_RX_FIFO_EN_MASK         (1u << SCON_RX_FIFO_EN_POS)
#define SCON_TX_FIFO_EN_POS          (7)
#define SCON_TX_FIFO_EN_MASK         (1u << SCON_TX_FIFO_EN_POS)

/* FIFO_TH register */
#if (CONFIG_OM6236)
#define FIFO_TH_RX_POS               (0)
#define FIFO_TH_RX_MASK              (0xFu << FIFO_TH_RX_POS)
#define FIFO_TH_TX_POS               (4)
#define FIFO_TH_TX_MASK              (0xFu << FIFO_TH_TX_POS)
#endif
#if (CONFIG_OM6239)
#define FIFO_TH_RX_POS               (0)
#define FIFO_TH_RX_MASK              (0x1Fu << FIFO_TH_RX_POS)
#define FIFO_TH_TX_POS               (5)
#define FIFO_TH_TX_MASK              (0x1Fu << FIFO_TH_TX_POS)
#endif

/* FIFO_ST register */
#define FIFO_ST_RX_FIFO_EMPTY_POS    (0)
#define FIFO_ST_RX_FIFO_EMPTY_MASK   (1u << FIFO_ST_RX_FIFO_EMPTY_POS)
#define FIFO_ST_TX_FIFO_FULL_POS     (1)
#define FIFO_ST_TX_FIFO_FULL_MASK    (1u << FIFO_ST_TX_FIFO_FULL_POS)
#if (CONFIG_OM6236)
#define FIFO_ST_RX_FIFO_CNT_POS      (8)
#define FIFO_ST_RX_FIFO_CNT_MASK     (0xFu << FIFO_ST_RX_FIFO_CNT_POS)
#define FIFO_ST_TX_FIFO_CNT_POS      (12)
#define FIFO_ST_TX_FIFO_CNT_MASK     (0xFu << FIFO_ST_TX_FIFO_CNT_POS)
#endif
#if (CONFIG_OM6239)
#define FIFO_ST_RX_FIFO_CNT_POS      (8)
#define FIFO_ST_RX_FIFO_CNT_MASK     (0x1Fu << FIFO_ST_RX_FIFO_CNT_POS)
#define FIFO_ST_TX_FIFO_CNT_POS      (13)
#define FIFO_ST_TX_FIFO_CNT_MASK     (0x1Fu << FIFO_ST_TX_FIFO_CNT_POS)
#endif

#ifdef __cplusplus
}
#endif


#endif  /* __UART_REG_H */


/** @} */
