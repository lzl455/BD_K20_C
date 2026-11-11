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
 * @file     drv_icache.h
 * @brief    ICACHE Driver
 * @date     06. Oct 2023
 * @author   OnMicro SW Team
 *
 * @defgroup ICACHE ICACHE
 * @ingroup  HAL_Driver
 * @brief    ICACHE Driver.
 * @details  ICACHE Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_ICACHE_H
#define __DRV_ICACHE_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_ICACHE)
#include "om_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup icache_monitor_mode_t DRV_ICACHE monitor mode type
 * @{
 */
typedef enum {
    ICACHE_MONITOR_MODE_CYCLE     = 0U,   /**< cycle */
    ICACHE_MONITOR_MODE_INSN_HIT  = 1U,   /**< insn hit */
    ICACHE_MONITOR_MODE_DATA_HIT  = 2U,   /**< data hit */
} icache_monitor_mode_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Get the statistics count of AHB cache monitor
 *
 * @return The statistics count for cycle or insn hit or data hit
 *******************************************************************************
 */
__STATIC_FORCEINLINE uint32_t get_icache_get_monitor_count(void)
{
    return OM_ICACHE->MON_STATUS;
}

/**
 *******************************************************************************
 * @brief Enable AHB Cache controller
 *******************************************************************************
 */
__STATIC_INLINE void drv_icache_enable(void)
{
    OM_ICACHE->CONFIG = 0;
    OM_ICACHE->CTRL = ICACHE_CTRL_CEN_MASK;
    while ((OM_ICACHE->STATUS & ICACHE_STATUS_CSTS_MASK) == 0);
}

/**
 *******************************************************************************
 * @brief Disable AHB Cache controller
 *******************************************************************************
 */
__STATIC_INLINE void drv_icache_disable(void)
{
    OM_ICACHE->CONFIG = ICACHE_CONFIG_GCLKDIS_MASK;
    OM_ICACHE->CTRL = 0;
    while ((OM_ICACHE->STATUS & ICACHE_STATUS_CSTS_MASK) != 0);
}

/**
 *******************************************************************************
 * @brief Invalidate all cache lines of AHB cache
 *******************************************************************************
 */
__STATIC_INLINE void drv_icache_inv_all(void)
{
    /* Invalidate cache lines. */
    OM_ICACHE->MAINT0 = ICACHE_MAINT0_INVALL_MASK;
    /* Reset counter register */
    OM_ICACHE->MON_CTRL = 1;
}

/**
 *******************************************************************************
 * @brief Enable AHB cache monitor and set monitor mode or Disable AHB cache monitor
 *
 * @param monitor_en  enable(1) or disable(0) cache monitor
 * @param monitor_mode monitor mode, see @ref icache_monitor_mode_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_icache_monitor_ctrl(uint8_t monitor_en, icache_monitor_mode_t monitor_mode);


#ifdef __cplusplus
}
#endif

#endif  /* (RTE_ICACHE) */

#endif  /* __DRV_ICACHE_H */

/** @} */
