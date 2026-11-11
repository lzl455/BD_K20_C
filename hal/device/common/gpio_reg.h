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
 * @file     gpio_reg.h
 * @brief    GPIO Register define
 * @date     11. Sep 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    GPIO Registers for OnMicro OM62xx
 * @details  GPIO Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __GPIO_REG_H
#define __GPIO_REG_H


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
    __IO uint32_t DATA;                           // offset: 0x00
    __IO uint32_t DATAOUT;                        // offset: 0x04
    #if (CONFIG_OM6229)
         uint32_t rsv_x08_x0c[2];                 // offset: 0x08-0x0C
    #else
    __IO uint32_t DATAOUTSET;                     // offset: 0x08
    __IO uint32_t DATAOUTCLR;                     // offset: 0x0C
    #endif
    __IO uint32_t OUTENSET;                       // offset: 0x10
    __IO uint32_t OUTENCLR;                       // offset: 0x14
         uint32_t rsv_x18_x1c[2];                 // offset: 0x18-0x1C
    __IO uint32_t INTENSET;                       // offset: 0x20
    __IO uint32_t INTENCLR;                       // offset: 0x24
    __IO uint32_t INTTYPE0SET;                    // offset: 0x28
    __IO uint32_t INTTYPE0CLR;                    // offset: 0x2C
    __IO uint32_t INTPOLSET;                      // offset: 0x30
    __IO uint32_t INTPOLCLR;                      // offset: 0x34
    __IO uint32_t INTSTATUS;                      // offset: 0x38
    __IO uint32_t rsv_x3c;                        // offset: 0x3C
    __IO uint32_t INTTYPE1SET;                    // offset: 0x40
    __IO uint32_t INTTYPE1CLR;                    // offset: 0x44
    #if (CONFIG_OM6229)
         uint8_t  rsv_x48_xfff[0x1000-0x0048];    // offset: 0x48-0x1000
    __IO uint32_t MASKLOWBYTE[0x100];
    __IO uint32_t MASKHIGHBYTE[0x100];
    #endif
} OM_GPIO_Type;


/*******************************************************************************
 * MACROS
 */
#define PAD_TRIG_WK_FALL_POS          1
#define PAD_TRIG_WK_FALL_MASK        (1u << PAD_TRIG_WK_FALL_POS)
#define PAD_TRIG_WK_EN_POS            0
#define PAD_TRIG_WK_EN_MASK          (1u << PAD_TRIG_WK_EN_POS)


#ifdef __cplusplus
}
#endif


#endif  /* __GPIO_REG_H */


/** @} */
