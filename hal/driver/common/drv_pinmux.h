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
 * @file     drv_pinmux.h
 * @brief    PINMUX Driver
 * @date     16. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup PINMUX PINMUX
 * @ingroup  HAL_Driver
 * @brief    PINMUX Driver.
 * @details  PINMUX Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_PINMUX_H
#define __DRV_PINMUX_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_PINMUX)


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup pin_func_t PINMUX func type
 * @{
 */
typedef enum {
    PIN_FUNC_GPIO     = 0U,  /**< GPIO        */
    PIN_FUNC_REUSE    = 1U,  /**< Other func  */
} pin_func_t;
/**
 * @}
 */

/**
 * @brief DRV_PINMUX configuration init stucture
 * @{
 */
typedef struct {
    uint8_t                      dig_pad : 4;
    pmu_pin_mode_t               mode : 2;
    pmu_pin_driver_current_t     drv : 2;
    pin_func_t                   func : 1;
} pin_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief PIN initialization
 *
 * @param pin_cfg      Configuration for PIN
 * @param pin_cfg_num  Configuration number for PIN
 *******************************************************************************
 */
extern void drv_pinmux_init(const pin_config_t *pin_cfg, uint32_t pin_cfg_num);

#ifdef __cplusplus
}
#endif

#endif  /* (RTE_PINMUX) */

#endif  /* __DRV_PINMUX_H */

/** @} */
