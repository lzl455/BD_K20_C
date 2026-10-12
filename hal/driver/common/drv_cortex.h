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
 * @file     drv_intc.h
 * @brief    OM62xx Interrupt controller driver
 * @date     07. Aug 2023
 * @author   OnMicro SW Team
 *
 * @defgroup DRIVER DRIVER
 * @ingroup  Peripheral
 * @brief    OM62xx Driver
 * @details  OM62xx Driver
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_CORTEX_H
#define __DRV_CORTEX_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#include <stdbool.h>
#include "om_device.h"
#include "drv_common.h"
#include "om_error.h"
#include "om_common.h"
#include "drv_rcc.h"


/*******************************************************************************
 * MACROS
 */
/**
 * @defgroup DRV_CORTEX_MACROS DRV_CORTEX Private Macros
 * @{
 */
/**
 * @brief disable global interrupt for enter critical code
 */
#define OM_CRITICAL_BEGIN()                                                    \
    do {                                                                       \
        /*lint -save -e578 */                                                  \
        uint32_t _primask = __get_PRIMASK();                                   \
        /*lint –restore */                                                     \
        __disable_irq();

/**
 * @brief  restore global interrupt for exit critical code
 */
#define OM_CRITICAL_END()                                                      \
        if (!_primask) {                                                       \
            __enable_irq();                                                    \
        }                                                                      \
    } while(0)

#if (RTE_CORTEX_SYSTICK)
extern uint32_t SystemCoreClock;
/* Calculation of ceil value for cycles */
#define DRV_SYSTICK_US_2_CYCLES_CEIL(us)     ((SYS_CLK + 999999U)/ 1000U / 1000U * (us))
/* Calculation of round value for cycles */
#define DRV_SYSTICK_US_2_CYCLES_ROUND(us)    ((SYS_CLK + 500000U) / 1000U / 1000U * (us))
/* Calculation of floor value for cycles */
#define DRV_SYSTICK_US_2_CYCLES_FLOOR(us)    (SYS_CLK / 1000U / 1000U * (us))

/* Calculation of ceil value for cycles */
#define DRV_SYSTICK_MS_2_CYCLES_CEIL(ms)     ((SYS_CLK + 999U)/ 1000U * (ms))
/* Calculation of round value for cycles */
#define DRV_SYSTICK_MS_2_CYCLES_ROUND(ms)    ((SYS_CLK + 500U)/ 1000U * (ms))
/* Calculation of floor value for cycles */
#define DRV_SYSTICK_MS_2_CYCLES_FLOOR(ms)    (SYS_CLK / 1000U * (ms))

#if (RTE_CORTEX_SYSTICK_TIMEOUT)
/**
 *******************************************************************************
 * @brief  continuous check wait_val using systick.
 *
 * @param  wait_val wait value
 * @param  to_ms timeout value in ms, 0 in case of return immediately with timeout status
 * @param  ret return value, it will return OM_ERROR_OK in to_ms, else return OM_ERROR_TIMEOUT
 *******************************************************************************
 */
#define DRV_SYSTICK_WAIT_MS_UNTIL_TO(wait_val, to_ms, ret)                          \
    do {                                                                            \
        uint32_t to;                                                                \
        ret = OM_ERROR_OK;                                                          \
        to = (uint32_t)(to_ms);                                                     \
        if (to != DRV_MAX_DELAY) {                                                  \
            uint32_t start = 0, target = 0;                                         \
            uint32_t check_to;                                                      \
            uint32_t calc_en = 1U;     /* calc systick start and target */          \
            while (wait_val) {                                                      \
                if (calc_en) {                                                      \
                    start = SysTick->VAL;                                           \
                    check_to = (to >= 250U) ? 250U : to;                            \
                    to -= check_to;                                                 \
                    target = DRV_SYSTICK_MS_2_CYCLES_CEIL(check_to);                \
                    calc_en = 0U;                                                   \
                }                                                                   \
                if (((start - SysTick->VAL) & SysTick_VAL_CURRENT_Msk) >= target) { \
                    if (to) {                                                       \
                        calc_en = 1U;                                               \
                        continue;                                                   \
                    } else {                                                        \
                        ret = OM_ERROR_TIMEOUT;                                     \
                        break;                                                      \
                    }                                                               \
                }                                                                   \
            }                                                                       \
        } else {                                                                    \
            while (wait_val);                                                       \
        }                                                                           \
    } while(0)

/**
 *******************************************************************************
 * @brief  continuous check wait_val using systick
 *
 * @param  wait_val wait value
 * @param  to_us timeout value in us, 0 in case of return immediately with timeout status
 * @param  ret return value, it will return OM_ERROR_OK in to_ms, else return OM_ERROR_TIMEOUT
 *******************************************************************************
 */
#define DRV_SYSTICK_WAIT_US_UNTIL_TO(wait_val, to_us, ret)                          \
    do {                                                                            \
        uint32_t to;                                                                \
        ret = OM_ERROR_OK;                                                          \
        to = (uint32_t)(to_us);                                                     \
        if (to != DRV_MAX_DELAY) {                                                  \
            uint32_t start = 0, target = 0;                                         \
            uint32_t check_to;                                                      \
            uint32_t calc_en = 1U;     /* calc systick start and target */          \
            while (wait_val) {                                                      \
                if (calc_en) {                                                      \
                    start = SysTick->VAL;                                           \
                    check_to = (to >= 250U*1000) ? 250U*1000 : to;                  \
                    to -= check_to;                                                 \
                    target = DRV_SYSTICK_US_2_CYCLES_CEIL(check_to);                \
                    calc_en = 0U;                                                   \
                }                                                                   \
                if (((start - SysTick->VAL) & SysTick_VAL_CURRENT_Msk) >= target) { \
                    if (to) {                                                       \
                        calc_en = 1U;                                               \
                        continue;                                                   \
                    } else {                                                        \
                        ret = OM_ERROR_TIMEOUT;                                     \
                        break;                                                      \
                    }                                                               \
                }                                                                   \
            }                                                                       \
        } else {                                                                    \
            while (wait_val);                                                       \
        }                                                                           \
    } while(0)
#endif /* (RTE_CORTEX_SYSTICK_TIMEOUT) */
/**
 * @}
 */


/*******************************************************************************
 * TYPEDEFS
 */
/**
  * @brief DRV_SYSTICK configuration init structure
  * @{
  */
typedef struct {
    uint32_t reload_val;     /**< systick reload value, range in (1, 0xFFFFFF] */
    uint8_t  irq_enable;     /**< enable systick IRQ when drv_systick_init */
} systick_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief                  Initialization the SysTick module
 *
 * @param config           The SYSTICK configuration structure, see @ref systick_config_t.
 *******************************************************************************
 */
extern void drv_systick_init(const systick_config_t *config);

#if (RTE_CORTEX_SYSTICK_DELAY)
/**
 *******************************************************************************
 * @brief                   Using SysTick module for cycles delay.
 *
 * @param cycles            The number of cycles to be delayed.
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_delay_cycles(uint32_t cycles);

/**
 *******************************************************************************
 * @brief                   Using SysTick module for us delay.
 *
 * @param us                The number of us to be delayed.
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_delay_us(uint32_t us);

/**
 *******************************************************************************
 * @brief                   Using SysTick module for ms delay.
 *
 * @param ms                The number of ms to be delayed.
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_delay_ms(uint32_t ms);
#endif /* (RTE_CORTEX_SYSTICK_DELAY) */

#if (RTE_SYSTICK_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief                   Register the interrupt callback function for the SysTick module.
 *
 * @param isr_cb            The entry address of the callback function.
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* RTE_SYSTICK_REGISTER_CALLBACK */

/**
 *******************************************************************************
 * @brief                   The interrupt callback for SYSTICK driver. It is a weak function. User should define
 *                          their own callback in user file, other than modify it in the SYSTICK driver.
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_isr_callback(void);

/**
 *******************************************************************************
 * @brief                   The SysTick interrupt handling module.
 *
 * @param                   None
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_systick_isr(void);

#endif /* (RTE_CORTEX_SYSTICK) */


#ifdef  __cplusplus
}
#endif

#endif  /* __DRV_CORTEX_H */


/** @} */
