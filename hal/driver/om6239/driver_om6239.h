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
 * @file     driver_om6239.h
 * @brief    OM6239 Driver
 * @date     05. Aug 2023
 * @author   OnMicro SW Team
 *
 * @defgroup DRIVER DRIVER
 * @ingroup  Peripheral
 * @brief    OM6239 Driver
 * @details  OM6239 Driver
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRIVER_OM6239_H
#define __DRIVER_OM6239_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#include "om_error.h"
#include "om_compiler.h"
#include "om_common.h"

#include "../common/drv_utils.h"
#include "../common/drv_common.h"
#include "../common/drv_cortex.h"
#include "../common/drv_gpio.h"
#include "../common/drv_rtc.h"
#include "../common/drv_aes128.h"
#include "../common/drv_timer.h"
#include "../common/drv_pwm.h"
#include "../common/drv_rf.h"
#include "../common/drv_icache.h"
#include "../common/drv_flash.h"
#include "../common/drv_wdt.h"
#include "../common/drv_uart.h"
#include "../common/drv_rcc.h"

#include "drv_pmu.h"
#include "../common/drv_pinmux.h"
#include "drv_senscan.h"
#include "drv_ledc.h"
#include "drv_encoder.h"
#include "drv_dynamic_load.h"

// common peripheral
#if (RTE_CORTEX_SYSTICK_DELAY)
// Use SysTick for delay, at 48MHz, the max delay is 0xFFFFFF / 48MHz = 349ms
#define DRV_DELAY_CYCLES(cycles)        drv_systick_delay_cycles(cycles)
#define DRV_DELAY_US(us)                drv_systick_delay_us(us)
#define DRV_DELAY_MS(ms)                drv_systick_delay_ms(ms)
#else
//#error "Delay functions are undefined"
//#define DRV_DELAY_CYCLES(cycles)
//#define DRV_DELAY_US(us)
//#define DRV_DELAY_MS(ms)
#endif

#if (RTE_CORTEX_SYSTICK_TIMEOUT)
#define DRV_WAIT_MS_UNTIL_TO(wait_val, to_ms, ret)  DRV_SYSTICK_WAIT_MS_UNTIL_TO(wait_val, to_ms, ret)
#define DRV_WAIT_US_UNTIL_TO(wait_val, to_us, ret)  DRV_SYSTICK_WAIT_US_UNTIL_TO(wait_val, to_us, ret)
#else
//#warning "Timeout functions are undefined"
//#define DRV_WAIT_MS_UNTIL_TO(wait_val, to_ms, ret)  {while (wait_val); ret = DRV_ERROR_OK;}
//#define DRV_WAIT_US_UNTIL_TO(wait_val, to_us, ret)  {while (wait_val); ret = DRV_ERROR_OK;}
#endif

#endif  /* __DRIVER_OM6239_H */


/** @} */
