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
 * @file     PWM_reg.h
 * @brief    PWM Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    PWM Registers for OnMicro OM62xx
 * @details  PWM Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __PWM_REG_H
#define __PWM_REG_H


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
    __IO uint32_t PWMCON;
    __IO uint32_t PWMCR0;
    __IO uint32_t PWMCR1;
    __IO uint32_t PWMDIV;
    __IO uint32_t PWMPRD;
    union {
        __IO uint32_t PWMDC[8];
        struct {
            __IO uint32_t PWMDC0;
            __IO uint32_t PWMDC1;
            __IO uint32_t PWMDC2;
            __IO uint32_t PWMDC3;
            __IO uint32_t PWMDC4;
            __IO uint32_t PWMDC5;
            __IO uint32_t PWMDC6;
            __IO uint32_t PWMDC7;
        };
    };
} OM_PWM_Type;


/*******************************************************************************
 * MACROS
 */
/* PWMCON register */
#define PWM_PWMCON_CHANNELn_EN_POS(n)              (n)
#define PWM_PWMCON_CHANNELn_EN_MASK(n)             (1u << PWM_PWMCON_CHANNELn_EN_POS(n))

/* PWMCR0 register */
#define PWM_PWMCR0_CHANNELn_INITIAL_CTL_POS(n)     (n)
#define PWM_PWMCR0_CHANNELn_INITIAL_CTL_MASK(n)    (1u << PWM_PWMCR0_CHANNELn_INITIAL_CTL_POS(n))

/* PWMCR1 register */
#define PWM_PWMCR1_CHANNELn_ACTIVE_CTL_POS(n)      (n)
#define PWM_PWMCR1_CHANNELn_ACTIVE_CTL_MASK(n)     (1u << PWM_PWMCR1_CHANNELn_ACTIVE_CTL_POS(n))

#ifdef __cplusplus
}
#endif


#endif  /* __PWM_REG_H */


/** @} */
