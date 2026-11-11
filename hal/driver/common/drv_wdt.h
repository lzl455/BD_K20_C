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
 * @file     drv_wdt.h
 * @brief    WDT Driver
 * @date     23. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup WDT WDT
 * @ingroup  HAL_Driver
 * @brief    WDT Driver.
 * @details  WDT Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_WDT_H
#define __DRV_WDT_H

/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_WDT)
#include "om_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup wdt_control_t DRV_WDT control type
 * @{
 */
typedef enum {
    WDT_CONTROL_CLK_DISABLE     = 0U,     /**< Disable WDT clock */
    WDT_CONTROL_CLK_ENABLE      = 1U,     /**< Enable WDT clock */
    WDT_CONTROL_FEED            = 2U,     /**< Set watchdog timeout value */
    WDT_CONTROL_STOP_ON_DEBUG   = 3U,     /**< Set watchdog stop mode on debug */
    WDT_CONTROL_STOP_ON_SLEEP   = 4U,     /**< Set watchdog stop mode on sleep */
    WDT_CONTROL_INT_ENABLE      = 5U,     /**< Enable watchdog interrupt */
    WDT_CONTROL_INT_DISABLE     = 6U,     /**< Disable watchdog interrupt */
} wdt_control_t;
/**
 * @}
 */

/**
 * @brief DRV_WDT configuration init stucture
 * @{
 */
typedef struct {
    uint32_t       timeout_ms; /**< watchdog timeout value at 32000Hz, range in [1ms, 524288ms] */
} wdt_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Control WDT interface
 *
 * @param om_wdt    The WDT device address
 * @param control        The control operation type, see @ref wdt_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - WDT_CONTROL_CLK_DISABLE    Disable WDT clock,argu=NULL
 *                       - WDT_CONTROL_CLK_ENABLE     Enable WDT clock,argu=NULL
 *                       - WDT_CONTROL_FEED           Set watchdog timeout value, range in [0, 0xFFFFFF], timeout = (argu + 1) / 32000 seconds
 *                       - WDT_CONTROL_STOP_ON_DEBUG  Set watchdog stop mode on debug, argu is [0, 1]
 *                       - WDT_CONTROL_STOP_ON_SLEEP  Set watchdog stop mode on sleep, argu is [0, 1]
 *                       - WDT_CONTROL_INT_ENABLE     Enable watchdog interrupt, argu is NULL
 *                       - WDT_CONTROL_INT_DISABLE    Disable watchdog interrupt, argu is NULL
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
extern void *drv_wdt_control(OM_WDT_Type *om_wdt, wdt_control_t control, void *argu);

/**
 *******************************************************************************
 * @brief WDT initialization
 *
 * @param om_wdt Pointer to WDT
 * @param config Configuration for WDT
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_wdt_init(OM_WDT_Type *om_wdt);

/**
 *******************************************************************************
 * @brief Feed watchdog
 *
 * @param om_wdt Pointer to WDT
 *
 * @return None
 *******************************************************************************
 */
extern void drv_wdt_keep_alive(OM_WDT_Type *om_wdt);

#if (RTE_WDT_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register event callback for WDT interrupt
 *
 * @param isr_cb Pointer to callback
 *
 * @return None
 *******************************************************************************
 */
extern void drv_wdt_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* (RTE_WDT_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for WDT driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the WDT driver.
 *
 * @param om_wdt The WDT device address
 * @param event The driver event, which could be DRV_EVENT_COMMON_GENERAL
 *
 * @return None
 *******************************************************************************
 */
extern void drv_wdt_isr_callback(OM_WDT_Type *om_wdt, drv_event_t event);

/**
 *******************************************************************************
 * @brief Handle WDT interrupt request.
 *
 * @param om_wdt Pointer to WDT
 *
 * @return None
 *******************************************************************************
 */
extern void drv_wdt_isr(OM_WDT_Type *om_wdt);


#ifdef __cplusplus
}
#endif

#endif  /* (RTE_WDT) */

#endif  /* __DRV_WDT_H */

/** @} */
