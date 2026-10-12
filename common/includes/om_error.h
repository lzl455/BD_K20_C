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
 * @file     om_error.h
 * @brief    OnMicro error codes define
 * @date     19. May 2020
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    templete
 * @details  templete, templete for .h header file
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __OM_ERROR_H
#define __OM_ERROR_H


/*******************************************************************************
 * TYPEDEFS
 */
typedef enum {
    OM_ERROR_OK                      =  0,
    OM_ERROR_UNSPECIFIC              =  1,
    OM_ERROR_BUSY                    =  2,
    OM_ERROR_TIMEOUT                 =  3,
    OM_ERROR_UNSUPPORTED             =  4,
    OM_ERROR_PARAMETER               =  5,
    OM_ERROR_RESOURCES               =  6,
    OM_ERROR_PERMISSION              =  7,
    OM_ERROR_OUT_OF_RANGE            =  8,      /* parameter out of range */
    OM_ERROR_ALIGN                   =  9,      /* memory align */
    OM_ERROR_STATUS                  =  10,
    OM_ERROR_VERIFY                  =  11,
    OM_ERROR_FAIL                    =  12,
    OM_ERROR_HARDWARE                =  13,

    OM_ERROR_MAX                     = 0xFFFFFFFFU,
} om_error_t;

#endif  /* __OM_ERROR_H */


/** @} */
