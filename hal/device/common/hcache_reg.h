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
 * @file     hcache_reg.h
 * @brief    ICACHE Register define
 * @date     18. Oct 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    ICACHE Registers for OnMicro OM62xx
 * @details  ICACHE Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __ICACHE_REG_H
#define __ICACHE_REG_H


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
     __I  uint32_t TYPE;
     __IO uint32_t CONFIG;
     __IO uint32_t CTRL;
     __IO uint32_t STATUS;
          uint32_t RESERVE0[4];
     __IO uint32_t MAINT0;
     __IO uint32_t MAINT1;
     __IO uint32_t MON_CONFIG;
     __IO uint32_t MON_EN;
     __IO uint32_t MON_CTRL;
     __IO uint32_t MON_STATUS;
} OM_ICACHE_Type;


/*******************************************************************************
 * MACROS
 */
#define ICACHE_CONFIG_GCLKDIS_MASK   (1u << 0)
#define ICACHE_CTRL_CEN_MASK         (1u << 0)
#define ICACHE_STATUS_CSTS_MASK      (1u << 0)
#define ICACHE_MAINT0_INVALL_MASK    (1u << 0)


#ifdef __cplusplus
}
#endif


#endif  /* __ICACHE_REG_H */


/** @} */
