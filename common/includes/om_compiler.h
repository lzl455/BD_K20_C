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
 * @file     om_compiler.h
 * @brief
 * @date     15. Nov 2022
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    template
 * @details  template, template for .h header file
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


#ifndef __OM_COMPILER_H
#define __OM_COMPILER_H


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * MACROS
 */
// Lock code/data/bss to RAM/PSRAM/OFLASH for different Compiler
#if defined(__ARMCC_VERSION)    /* ARMCLANG Compiler */
#define __RAM_CODE              __attribute((used, section("RAM_CODE"), noinline))     /* used for function,  placed code into ram                 */
#define __RAM_CODES(s)          __attribute((used, section("RAM_CODE."s), noinline))   /* used for function,  placed code into ram                 */
#define __RAM_RODATA            __attribute((used, section("RAM_RODATA")))             /* used for const variable, placed rodata into ram          */
#define __RAM_RODATAS(s)        __attribute((used, section("RAM_RODATA."s)))           /* used for const variable, placed rodata into ram          */
#define __RAM_RWDATAS(s)        __attribute((used, section("RAM_RWDATA."s)))           /* used for variable, placed rodata into ram                */
#define __RAM_ZIDATAS(s)        __attribute((used, section("RAM_ZIDATA."s)))           /* used for variable, placed data into uninit section       */

#elif defined ( __GNUC__ )      /* GNU compiler */
#define __RAM_CODE              __attribute((used, section(".ram_code"), noinline))
#define __RAM_CODES(s)          __attribute((used, section(".ram_code."s), noinline))
#define __RAM_RODATA            __attribute((used, section(".ram_rodata")))
#define __RAM_RODATAS(s)        __attribute((used, section(".ram_rodata."s)))
#define __RAM_RWDATAS(s)        __attribute((used, section(".ram_rwdata."s)))
#define __RAM_ZIDATAS(S)        __attribute((used, section(".ram_zidata."s)))

#elif defined ( __ICCARM__ )    /* IAR compiler */
#define __RAM_CODE              /*_Pragma("location=\".ram_code\"")*/ __ramfunc
#define __RAM_CODES(s)          /*_Pragma("location=\".ram_code\"")*/ __ramfunc
#define __RAM_RODATA            _Pragma("location=\".ram_rodata\"")
#define __RAM_RODATAS(s)        _Pragma("location=\".ram_rodata\"")
#define __RAM_DATA_NON_INIT     _Pragma("location=\".ram_data_non_init\"")
#else
#error Donot Support Compiler!
#endif


#ifdef __cplusplus
extern "C"
}
#endif

#endif  /*  __OM_COMPILER_H */


/** @} */
