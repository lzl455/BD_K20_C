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
 * @file     wdt_reg.h
 * @brief    WDT Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    WDT Registers for OnMicro OM62xx
 * @details  WDT Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __WDT_REG_H
#define __WDT_REG_H


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
    __IO uint32_t CR;
    __IO uint32_t SV;
} OM_WDT_Type;

/*******************************************************************************
 * MACROS
 */
/* CR register */
#define WDT_CR_SLP_WDT_STOP_POS                  (0)
#define WDT_CR_SLP_WDT_STOP_MASK                 (1u << WDT_CR_SLP_WDT_STOP_POS)
#define WDT_CR_DBG_WDT_STOP_POS                  (1)
#define WDT_CR_DBG_WDT_STOP_MASK                 (1u << WDT_CR_DBG_WDT_STOP_POS)
#define WDT_CR_INT_MASK_POS                      (2)
#define WDT_CR_INT_MASK_MASK                     (1u << WDT_CR_INT_MASK_POS)
#define WDT_CR_INT_STATUS_POS                    (30)
#define WDT_CR_INT_STATUS_MASK                   (1u << WDT_CR_INT_STATUS_POS)
#define WDT_CR_SYNC_FLAG_POS                     (31)
#define WDT_CR_SYNC_FLAG_MASK                    (1u << WDT_CR_SYNC_FLAG_POS)

/* SV register*/
#define WDT_SV_WDT_START_VALUE_POS               (0)
#define WDT_SV_WDT_START_VALUE_MASK              (0xFFFFFF << WDT_SV_WDT_START_VALUE_POS)
#define WDT_SV_WDT_VECT_KEY_POS                  (24)
#define WDT_SV_WDT_VECT_KEY_MASK                 (0xFF << WDT_SV_WDT_VECT_KEY_POS)
#define WDT_SV_SYNC_FLAG_POS                     (31)
#define WDT_SV_SYNC_FLAG_MASK                    (1u << WDT_SV_SYNC_FLAG_POS)


#ifdef __cplusplus
}
#endif


#endif  /* __WDT_REG_H */


/** @} */
