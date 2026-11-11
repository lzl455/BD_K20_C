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
 * @file     ledc_reg.h
 * @brief    LEDC Register define
 * @date     22. May 2024
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    LEDC Registers for OnMicro OM62xx
 * @details  LEDC Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __LEDC_REG_H
#define __LEDC_REG_H


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
     __IO uint32_t SIG_TIM;
     __IO uint32_t RST_TIM;
     __IO uint32_t DMA_CTL;
} OM_LEDC_Type;


/*******************************************************************************
 * MACROS
 */
/* CR register */
#define LEDC_CR_ENABLE_POS                 (0U)
#define LEDC_CR_ENABLE_MASK                (1U << LEDC_CR_ENABLE_POS)
#define LEDC_CR_INT_ENABLE_POS             (8U)
#define LEDC_CR_INT_ENABLE_MASK            (1U << LEDC_CR_INT_ENABLE_POS)
#define LEDC_CR_INT_RAW_STATUS_POS         (16U)
#define LEDC_CR_INT_RAW_STATUS_MASK        (1U << LEDC_CR_INT_RAW_STATUS_POS)

/* SIG_TIM register */
#define LEDC_SIG_TIM_TS_POS                 (0U)
#define LEDC_SIG_TIM_TS_MASK                (0xFFFFU << LEDC_SIG_TIM_TS_POS)
#define LEDC_SIG_TIM_TL_POS                 (16U)
#define LEDC_SIG_TIM_TL_MASK                (0xFFFFU << LEDC_SIG_TIM_TL_POS)

/* DMA_CTL register */
#define LEDC_DMA_CTL_DMA_LEN_POS            (0U)
#define LEDC_DMA_CTL_DMA_LEN_MASK           (0x3FFFU << LEDC_DMA_CTL_DMA_LEN_POS)
#define LEDC_DMA_CTL_DMA_ADDR_POS           (16U)
#define LEDC_DMA_CTL_DMA_ADDR_MASK          (0x3FFFU << LEDC_DMA_CTL_DMA_ADDR_POS)
#ifdef __cplusplus
}
#endif


#endif  /* __LEDC_REG_H */


/** @} */
