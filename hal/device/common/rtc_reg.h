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
 * @file     rtc_reg.h
 * @brief    RTC Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    RTC Registers for OnMicro OM62xx
 * @details  RTC Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __RTC_REG_H
#define __RTC_REG_H


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
    __IO uint32_t CR;
    __I  uint32_t INTSTAT;
    __IO uint32_t INTRAWSTAT;
    __IO uint32_t INTMASK;
    __IO uint32_t TICK;
    __IO uint32_t ALARM0;
    __IO uint32_t CNT;
    __I  uint32_t CNT_VALID;
    __I  uint32_t CLKN_SYNC;
    __I  uint32_t CLKN_VALID;
    __IO uint32_t ALARM1;
    __IO uint32_t ALARM2;
    __IO uint32_t WKRF_CR;
} OM_RTC_Type;


/*******************************************************************************
 * MACROS
 */
/* CR register */
#define RTC_CR_TIMER_EN_POS                      (0)
#define RTC_CR_TIMER_EN_MASK                     (1u << RTC_CR_TIMER_EN_POS)
#define RTC_CR_TICK_DIS_POS                      (1)
#define RTC_CR_TICK_DIS_MASK                     (1u << RTC_CR_TICK_DIS_POS)
#define RTC_CR_ALARM0_DIS_POS                    (2)
#define RTC_CR_ALARM0_DIS_MASK                   (1u << RTC_CR_ALARM0_DIS_POS)
#define RTC_CR_ALARM1_DIS_POS                    (3)
#define RTC_CR_ALARM1_DIS_MASK                   (1u << RTC_CR_ALARM1_DIS_POS)
#define RTC_CR_TICK_WAKEUP_EN_POS                (4)
#define RTC_CR_TICK_WAKEUP_EN_MASK               (1u << RTC_CR_TICK_WAKEUP_EN_POS)
#define RTC_CR_ALARM0_WAKEUP_EN_POS              (5)
#define RTC_CR_ALARM0_WAKEUP_EN_MASK             (1u << RTC_CR_ALARM0_WAKEUP_EN_POS)
#define RTC_CR_ALARM1_WAKEUP_EN_POS              (6)
#define RTC_CR_ALARM1_WAKEUP_EN_MASK             (1u << RTC_CR_ALARM1_WAKEUP_EN_POS)
#define RTC_CR_CR_WRITE_STATUS_POS               (8)
#define RTC_CR_CR_WRITE_STATUS_MASK              (1u << RTC_CR_CR_WRITE_STATUS_POS)
#define RTC_CR_TICK_WRITE_STATUS_POS             (9)
#define RTC_CR_TICK_WRITE_STATUS_MASK            (1u << RTC_CR_TICK_WRITE_STATUS_POS)
#define RTC_CR_ALARM0_WRITE_STATUS_POS           (10)
#define RTC_CR_ALARM0_WRITE_STATUS_MASK          (1u << RTC_CR_ALARM0_WRITE_STATUS_POS)
#define RTC_CR_ALARM1_WRITE_STATUS_POS           (11)
#define RTC_CR_ALARM1_WRITE_STATUS_MASK          (1u << RTC_CR_ALARM1_WRITE_STATUS_POS)
#define RTC_CR_ALARM2_WRITE_STATUS_POS           (12)
#define RTC_CR_ALARM2_WRITE_STATUS_MASK          (1u << RTC_CR_ALARM2_WRITE_STATUS_POS)
#define RTC_CR_ALARMx_WRITE_STATUS_POS(x)        (10 + (x))
#define RTC_CR_ALARMx_WRITE_STATUS_MASK(x)       (1u << RTC_CR_ALARMx_WRITE_STATUS_POS(x))

/* INTSTAT register */
#define RTC_INTSTAT_TICK_INT_STATUS_POS           (0)
#define RTC_INTSTAT_TICK_INT_STATUS_MASK          (1u << RTC_INTSTAT_TICK_INT_STATUS_POS)
#define RTC_INTSTAT_ALARM0_INT_STATUS_POS         (1)
#define RTC_INTSTAT_ALARM0_INT_STATUS_MASK        (1u << RTC_INTSTAT_ALARM0_INT_STATUS_POS)
#define RTC_INTSTAT_ALARM1_INT_STATUS_POS         (2)
#define RTC_INTSTAT_ALARM1_INT_STATUS_MASK        (1u << RTC_INTSTAT_ALARM1_INT_STATUS_POS)
#define RTC_INTSTAT_INT_STATUS_POS(x)             (x)
#define RTC_INTSTAT_INT_STATUS_MASK(x)            (1u << RTC_INTSTAT_INT_STATUS_POS(x))

/* INTRAWSTAT register */
#define RTC_INTRAWSTAT_TICK_INTRAW_STATUS_POS     (0)
#define RTC_INTRAWSTAT_TICK_INTRAW_STATUS_MASK    (1u << RTC_INTRAWSTAT_TICK_INTRAW_STATUS_POS)
#define RTC_INTRAWSTAT_ALARM0_INTRAW_STATUS_POS   (1)
#define RTC_INTRAWSTAT_ALARM0_INTRAW_STATUS_MASK  (1u << RTC_INTRAWSTAT_ALARM0_INTRAW_STATUS_POS)
#define RTC_INTRAWSTAT_ALARM1_INTRAW_STATUS_POS   (2)
#define RTC_INTRAWSTAT_ALARM1_INTRAW_STATUS_MASK  (1u << RTC_INTRAWSTAT_ALARM1_INTRAW_STATUS_POS)

/* INTMASK register */
#define RTC_INTMASK_TICK_INTRAW_STATUS_POS     (0)
#define RTC_INTMASK_TICK_INTRAW_STATUS_MASK    (1u << RTC_INTMASK_TICK_INTRAW_STATUS_POS)
#define RTC_INTMASK_ALARM0_INTRAW_STATUS_POS   (1)
#define RTC_INTMASK_ALARM0_INTRAW_STATUS_MASK  (1u << RTC_INTMASK_ALARM0_INTRAW_STATUS_POS)
#define RTC_INTMASK_ALARM1_INTRAW_STATUS_POS   (2)
#define RTC_INTMASK_ALARM1_INTRAW_STATUS_MASK  (1u << RTC_INTMASK_ALARM1_INTRAW_STATUS_POS)

#ifdef __cplusplus
}
#endif


#endif  /* __RTC_REG_H */


/** @} */
