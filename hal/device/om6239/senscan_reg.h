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
 * @file     senscan_reg.h
 * @brief    SENSCAN Register define
 * @date     22. May 2024
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    SENSCAN Registers for OnMicro OM62xx
 * @details  SENSCAN Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __SENSCAN_REG_H
#define __SENSCAN_REG_H


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
     __IO uint32_t CSR;                      //0x00
     __IO uint32_t ISR;                      //0x04
     __IO uint32_t IER;                      //0x08
     union {
          uint32_t ADDR_REG[7];
          struct {
               __IO uint32_t IDADDR;        //0x0C
               __IO uint32_t ID;            //0x10
               __IO uint32_t MOADDR;        //0x14
               __IO uint32_t XADDR;         //0x18
               __IO uint32_t YADDR;         //0x1C
               __IO uint32_t HADDR1;        //0x20
               __IO uint32_t HADDR2;        //0x24
          };
     };
     __I  uint32_t X_DATA;                  //0x28
     __I  uint32_t Y_DATA;                  //0x2C
     __IO uint32_t TR;                      //0x30
     __IO uint32_t TNS;                     //0x34
     __IO uint32_t SCAN_FREQ;               //0x38
     __IO uint32_t RESYNC;                  //0x3C
     __IO uint32_t CFG_CSR;                 //0x40
     __IO uint32_t CFG_ADDR;                //0x44
     __IO uint32_t CFG_DATA;                //0x48
} OM_SENSCAN_Type;


/*******************************************************************************
 * MACROS
 */
/* CSR register */
#define SENSACN_CSR_SCAN_EN_POS             (0U)
#define SENSACN_CSR_SCAN_EN_MASK            (1U << SENSACN_CSR_SCAN_EN_POS)
#define SENSACN_CSR_SCAN_STOP_POS           (1U)
#define SENSACN_CSR_SCAN_STOP_MASK          (1U << SENSACN_CSR_SCAN_STOP_POS)
#define SENSACN_CSR_DATA_VALID_POS          (2U)
#define SENSACN_CSR_DATA_VALID_MASK         (1U << SENSACN_CSR_DATA_VALID_POS)
#define SENSACN_CSR_SCAN_MODE_POS           (3U)
#define SENSACN_CSR_SCAN_MODE_MASK          (1U << SENSACN_CSR_SCAN_MODE_POS)
#define SENSACN_CSR_DELTAXY_REV_POS         (4U)
#define SENSACN_CSR_DELTAXY_REV_MASK        (1U << SENSACN_CSR_DELTAXY_REV_POS)
#define SENSACN_CSR_DATA_FORMAT_POS         (5U)
#define SENSACN_CSR_DATA_FORMAT_8BIT        (0U << SENSACN_CSR_DATA_FORMAT_POS)
#define SENSACN_CSR_DATA_FORMAT_12BIT       (1U << SENSACN_CSR_DATA_FORMAT_POS)
#define SENSACN_CSR_DATA_FORMAT_16BIT       (2U << SENSACN_CSR_DATA_FORMAT_POS)
#define SENSACN_CSR_DATA_FORMAT_MASK        (3U << SENSACN_CSR_DATA_FORMAT_POS)
#define SENSACN_CSR_RESYNC_FLAG_POS         (7U)
#define SENSACN_CSR_RESYNC_FLAG_MASK        (1U << SENSACN_CSR_RESYNC_FLAG_POS)
#define SENSACN_CSR_SPI_MODE_POS            (8U)
#define SENSACN_CSR_SPI_MODE_MASK           (1U << SENSACN_CSR_SPI_MODE_POS)
#define SENSACN_CSR_SPI_CLK_SEL_POS         (9U)
#define SENSACN_CSR_SPI_CLK_SEL_MASK        (1U << SENSACN_CSR_SPI_CLK_SEL_POS)
#define SENSACN_CSR_DELTA_CLR_POS           (10U)
#define SENSACN_CSR_DELTA_CLR_MASK          (1U << SENSACN_CSR_DELTA_CLR_POS)
#define SENSACN_CSR_SCAN_BUSY_POS           (11U)
#define SENSACN_CSR_SCAN_BUSY_MASK          (1U << SENSACN_CSR_SCAN_BUSY_POS)
#define SENSACN_CSR_WAKE_EN_POS             (16U)
#define SENSACN_CSR_WAKE_EN_MASK            (1U << SENSACN_CSR_WAKE_EN_POS)

/* ISR register */
#define SENSACN_ISR_SCAN_DONE_POS             (0U)
#define SENSACN_ISR_SCAN_DONE_MASK            (1U << SENSACN_CSR_SCAN_EN_POS)
#define SENSACN_ISR_2_WIRE_RESYNC_START_POS   (1U)
#define SENSACN_ISR_2_WIRE_RESYNC_START_MASK  (1U << SENSACN_ISR_2_WIRE_RESYNC_START_POS)
#define SENSACN_ISR_2_WIRE_RESYNC_DONE_POS    (2U)
#define SENSACN_ISR_2_WIRE_RESYNC_DONE_MASK   (1U << SENSACN_ISR_2_WIRE_RESYNC_DONE_POS)
#define SENSACN_ISR_SCAN_RESYNC_POS           (3U)
#define SENSACN_ISR_SCAN_RESYNC_MASK          (1U << SENSACN_ISR_SCAN_RESYNC_POS)
#define SENSACN_ISR_CFG_WR_DONE_POS           (4U)
#define SENSACN_ISR_CFG_WR_DONE_MASK          (1U << SENSACN_ISR_CFG_WR_DONE_POS)

/* IER register */
#define SENSACN_IER_SCAN_DONE_POS             (0U)
#define SENSACN_IER_SCAN_DONE_MASK            (1U << SENSACN_IER_SCAN_DONE_POS)
#define SENSACN_IER_2_WIRE_RESYNC_START_POS   (1U)
#define SENSACN_IER_2_WIRE_RESYNC_START_MASK  (1U << SENSACN_IER_2_WIRE_RESYNC_START_POS)
#define SENSACN_IER_2_WIRE_RESYNC_DONE_POS    (2U)
#define SENSACN_IER_2_WIRE_RESYNC_DONE_MASK   (1U << SENSACN_IER_2_WIRE_RESYNC_DONE_POS)
#define SENSACN_IER_SCAN_RESYNC_POS           (3U)
#define SENSACN_IER_SCAN_RESYNC_MASK          (1U << SENSACN_IER_SCAN_RESYNC_POS)
#define SENSACN_IER_CFG_DONE_EN_POS           (4U)
#define SENSACN_IER_CFG_DONE_EN_MASK          (1U << SENSACN_IER_CFG_DONE_EN_POS)

/* TR register */
#define SENSACN_IR_TSRAD_TIM_POS            (0U)
#define SENSACN_IR_TSRAD_TIM_MASK           (0x0FU << SENSACN_IR_TSRAD_TIM_POS)
#define SENSACN_IR_TSRR_TIM_POS             (4U)
#define SENSACN_IR_TSRR_TIM_MASK            (0x0FU << SENSACN_IR_TSRR_TIM_POS)

/* TNS register */
#define SENSACN_TNS_TSN_TIM_POS             (0U)
#define SENSACN_TNS_TSN_TIM_MASK            (0x0FU << SENSACN_TNS_TSN_TIM_POS)
#define SENSACN_TNS_TNS_TIM_POS             (4U)
#define SENSACN_TNS_TNS_TIM_MASK            (0x0FU << SENSACN_TNS_TNS_TIM_POS)

/* RESYNC register */
#define SENSACN_RESYNC_T_RESYNC_POS          (0U)
#define SENSACN_RESYNC_T_RESYNC_MASK         (0x1FU << SENSACN_RESYNC_T_RESYNC_POS)
#define SENSACN_RESYNC_T_WDT_POS             (8U)
#define SENSACN_RESYNC_T_WDT_MASK            (0x1FU << SENSACN_RESYNC_T_WDT_POS)

/* CFG_CSR register */
#define SENSACN_CFG_CSR_EN_POS                    (0U)
#define SENSACN_CFG_CSR_EN_MASK                   (1U << SENSACN_CFG_CSR_EN_POS)
#define SENSACN_CFG_CSR_START_POS                 (4U)
#define SENSACN_CFG_CSR_START_MASK                (1U << SENSACN_CFG_CSR_START_POS)
#define SENSACN_CFG_CSR_DIR_POS                   (6U)
#define SENSACN_CFG_CSR_DIR_MASK                  (1U << SENSACN_CFG_CSR_DIR_POS)
#define SENSACN_CFG_CSR_2_WIRE_RESYNC_START_POS   (7U)
#define SENSACN_CFG_CSR_2_WIRE_RESYNC_START_MASK  (1U << SENSACN_CFG_CSR_2_WIRE_RESYNC_START_POS)

#ifdef __cplusplus
}
#endif


#endif  /* __SENSCAN_REG_H */


/** @} */
