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
 * @file     om_common.h
 * @brief    OM_COMMON
 * @date     03. April 2020
 * @author   OnMicro SW Team
 *
 * @defgroup OM_COMMON OM_COMMON
 * @ingroup  common
 * @brief    COMMON Typedefs
 * @details  COMMON Typedefs
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


#ifndef __OM_COMMON_H
#define __OM_COMMON_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>


#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * MACROS
 */
/**
 *******************************************************************************
 * @brief  The OM_ASSERT macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls om_assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 *         If expr is true, it returns no value.
 * @return None
 *******************************************************************************
 */
#if (CONFIG_OM_ASSERT)
#define OM_ASSERT(expr)   ((expr) ? (void)0U : om_assert_failed((uint8_t *)__FILE__, __LINE__))
#define OM_ASSERT_WHILE(cond, expr)                                            \
    if ((unsigned)(cond)) {                                                    \
        ((expr) ? (void)0U : om_assert_failed((uint8_t *)__FILE__, __LINE__)); \
    }

extern void om_assert_failed(uint8_t *file, uint32_t line);
#else
#define OM_ASSERT(expr)                 ((void)0U)
#define OM_ASSERT_WHILE(cond, expr)     ((void)0U)
#endif  /* (CONFIG_OM_ASSERT) */


#ifdef __cplusplus
}
#endif

#endif  /* __OM_COMMON_H */


/** @} */
