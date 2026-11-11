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
 * @file     encoder_reg.h
 * @brief    ENCODER Register define
 * @date     22. May 2024
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    ENCODER Registers for OnMicro OM62xx
 * @details  ENCODER Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __ENCODER_REG_H
#define __ENCODER_REG_H


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
     __IO uint32_t EN;
     __IO uint32_t CNT;
     __IO uint32_t MODE;
     __IO uint32_t SAM;
     __IO uint32_t DBG;
     __IO uint32_t VALID;
} OM_ENCODER_Type;


/*******************************************************************************
 * MACROS
 */
/* EN register */
#define ENCODER_EN_ENCODER_EN_POS              (0U)
#define ENCODER_EN_ENCODER_EN_MASK             (1U << ENCODER_EN_ENCODER_EN_POS)
#define ENCODER_EN_INTERRUPT_EN_POS            (1U)
#define ENCODER_EN_INTERRUPT_EN_MASK           (1U << ENCODER_EN_INTERRUPT_EN_POS)
#define ENCODER_EN_WAKEUP_EN_POS               (2U)
#define ENCODER_EN_WAKEUP_EN_MASK              (1U << ENCODER_EN_WAKEUP_EN_POS)
#define ENCODER_EN_PINMUX_SEL_POS              (16U)
#define ENCODER_EN_PINMUX_SEL_MASK             (3U << ENCODER_EN_PINMUX_SEL_POS)

/* MODE register */
#define ENCODER_MODE_WHEELA_POS                  (2U)
#define ENCODER_MODE_WHEELA_MASK                 (1U << ENCODER_MODE_WHEELA_POS)
#define ENCODER_MODE_WHEELB_POS                  (3U)
#define ENCODER_MODE_WHEELB_MASK                 (1U << ENCODER_MODE_WHEELB_POS)

/* MODE register */
#define ENCODER_SRAM_DEBOUNCE_TIME_POS         (0U)
#define ENCODER_SRAM_DEBOUNCE_TIME_MASK        (0x0FU << ENCODER_SRAM_DEBOUNCE_TIME_POS)

/* DBG register */
#define ENCODER_DBG_WHEEL_DATA_SOURCE_POS      (0U)
#define ENCODER_DBG_WHEEL_DATA_SOURCE_MASK     (0x0FU << ENCODER_DBG_WHEEL_DATA_SOURCE_POS)
#define ENCODER_DBG_BPRE_AB_STATUS_POS         (4U)
#define ENCODER_DBG_BPRE_AB_STATUS_MASK        (1U << ENCODER_DBG_BPRE_AB_STATUS_POS)
#define ENCODER_DBG_BPRE_AB_NO_STATUS_POS      (5U)
#define ENCODER_DBG_BPRE_AB_NO_STATUS_MASK     (1U << ENCODER_DBG_BPRE_AB_NO_STATUS_POS)
#define ENCODER_DBG_BNO_STATUS_VALID_POS       (6U)
#define ENCODER_DBG_BNO_STATUS_VALID_MASK      (1U << ENCODER_DBG_BNO_STATUS_VALID_POS)
#define ENCODER_DBG_BCURR_B_STATUS_VALID_POS   (7U)
#define ENCODER_DBG_BCURR_B_STATUS_VALID_MASK  (1U << ENCODER_DBG_BCURR_B_STATUS_VALID_POS)
#define ENCODER_DBG_BCURR_A_STATUS_VALID_POS   (8U)
#define ENCODER_DBG_BCURR_A_STATUS_VALID_MASK  (1U << ENCODER_DBG_BCURR_A_STATUS_VALID_POS)

/* VALID register */
#define ENCODER_VALID_CNT_POS         (0U)
#define ENCODER_VALID_CNT_MASK        (0x01U << ENCODER_VALID_CNT_POS)

#ifdef __cplusplus
}
#endif


#endif  /* __ENCODER_REG_H */


/** @} */
