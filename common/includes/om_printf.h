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
 * @file     om_printf.h
 * @brief
 * @date     29. Sept 2021
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    Tiny printf, sprintf and (v)snprintf implementation
 * @details  Optimized for speed on embedded systems with a very limited resources
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __OM_PRINTF_H
#define __OM_PRINTF_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 * MACROS
 */
// disable support for the floating point type (%f)
#define PRINTF_DISABLE_SUPPORT_FLOAT

// disable support for exponential floating point notation (%e/%g)
// default: activated
#define PRINTF_DISABLE_SUPPORT_EXPONENTIAL

// disable support for the long long types (%llu or %p)
// default: activated
#define PRINTF_DISABLE_SUPPORT_LONG_LONG

// disable support for the ptrdiff_t type (%t)
// ptrdiff_t is normally defined in <stddef.h> as long or long long type
// default: activated
#define PRINTF_DISABLE_SUPPORT_PTRDIFF_T



/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *
 * This function is declared here only. You have to write your custom implementation somewhere
 * \param character Character to output
 */
/**
 *******************************************************************************
 * @brief Output a character to a custom device like UART, used by the printf() function
 *
 * @param[in] character      Character to output
 *
 *******************************************************************************
 */
extern void om_putchar(char character);

/**
 *******************************************************************************
 * @brief Tiny printf implementation
 *
 * @param[in] format      A string that specifies the format of the output
 *
 * @return: The number of characters that are written into the array, not counting the terminating null character
 *******************************************************************************
 */
extern int om_printf(const char* format, ...);

/**
 *******************************************************************************
 * @brief Tiny sprintf implementation
 *
 * @param[in] buffer      A pointer to the buffer where to store the formatted string. MUST be big enough to store the output!
 * @param[in] format      A string that specifies the format of the output
 *
 * @return: The number of characters that are written into the buffer, not counting the terminating null character
 *******************************************************************************
 */
extern int om_sprintf(char* buffer, const char* format, ...);

/**
 *******************************************************************************
 * @brief Tiny snprintf implementation
 *
 * @param[in] buffer      A pointer to the buffer where to store the formatted string.
 * @param[in] count       The maximum number of characters to store in the buffer, including a terminating null character
 * @param[in] format      A string that specifies the format of the output
 *
 * @return: The number of characters that COULD have been written into the buffer, not counting the terminating
 *          null character. A value equal or larger than count indicates truncation. Only when the returned value
 *          is non-negative and less than count, the string has been completely written.
 *******************************************************************************
 */
extern int om_snprintf(char* buffer, size_t count, const char* format, ...);

/**
 *******************************************************************************
 * @brief Tiny vsnprintf implementation
 *
 * @param[in] buffer      A pointer to the buffer where to store the formatted string.
 * @param[in] count       The maximum number of characters to store in the buffer, including a terminating null character
 * @param[in] format      A string that specifies the format of the output
 * @param[in] va          A value identifying a variable arguments list
 *
 * @return: The number of characters that COULD have been written into the buffer, not counting the terminating
 *          null character. A value equal or larger than count indicates truncation. Only when the returned value
 *          is non-negative and less than count, the string has been completely written.
 *******************************************************************************
 */
extern int om_vsnprintf(char* buffer, size_t count, const char* format, va_list va);

/**
 *******************************************************************************
 * @brief Tiny vsnprintf implementation
 *
 * @param[in] format      A string that specifies the format of the output
 * @param[in] va          A value identifying a variable arguments list
 *
 * @return: The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 *******************************************************************************
 */
extern int om_vprintf(const char* format, va_list va);

/**
 * printf with output function
 * You may use this as dynamic alternative to printf() with its fixed _putchar() output
 * \param out An output function which takes one character and an argument pointer
 * \param arg An argument pointer for user data passed to output function
 * \param format A string that specifies the format of the output
 * \return The number of characters that are sent to the output function, not counting the terminating null character
 */
/**
 *******************************************************************************
 * @brief Printf with output function
 *        You may use this as dynamic alternative to printf() with its fixed _putchar() output
 *
 * @param[in] out         An output function which takes one character and an argument pointer
 * @param[in] arg         An argument pointer for user data passed to output function
 * @param[in] format      A string that specifies the format of the output
 *
 * @return: The number of characters that are sent to the output function, not counting the terminating null character
 *******************************************************************************
 */
extern int om_fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);

#if (CONFIG_OM_PRINTF)
#define OM_PRINTF(...)                          om_printf(__VA_ARGS__)
#else
#define OM_PRINTF(...)
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __OM_PRINTF_H */


/** @} */
