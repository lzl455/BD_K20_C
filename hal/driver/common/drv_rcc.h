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
 * @file     drv_rcc.h
 * @brief    RCC Driver
 * @date     16. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup RCC RCC
 * @ingroup  HAL_Driver
 * @brief    RCC Driver.
 * @details  RCC Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_RCC_H
#define __DRV_RCC_H

/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_RCC)
#include "om_driver.h"


#ifdef __cplusplus
extern "C"
{
#endif

//#define SYS_CLK 16000000UL
//#define SYS_CLK 24000000UL
#define SYS_CLK 48000000UL

/*******************************************************************************
 * CONST & VARIABLES
 */
extern uint32_t SystemCoreClock;


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup rcc_sys_clk_sel_t DRV_RCC system clock selection type
 * @{
 */
typedef enum {
    RCC_SYS_CLK_SEL_OSC16M     = 0U,       /**< Select OSC 16M as the system clock */
    RCC_SYS_CLK_SEL_PLL48M     = 1U,       /**< Select PLL 48M as the system clock */
} rcc_sys_clk_sel_t;
/**
 * @}
 */

/**
 * @defgroup rcc_div_clk_sel_t DRV_RCC division clock selection type
 * @{
 */
typedef enum {
    RCC_DIV_CLK_SEL_1    = 0U,         /**< The frequency division clock selects SRC CLK's 1 frequency division */
    RCC_DIV_CLK_SEL_2    = 1U,         /**< The frequency division clock selects SRC CLK's 2 frequency division */
    RCC_DIV_CLK_SEL_4    = 2U,         /**< The frequency division clock selects SRC CLK's 4 frequency division */
    RCC_DIV_CLK_SEL_8    = 3U,         /**< The frequency division clock selects SRC CLK's 8 frequency division */
    RCC_DIV_CLK_SEL_16   = 4U,         /**< The frequency division clock selects SRC CLK's 16 frequency division */
    RCC_DIV_CLK_SEL_32   = 5U,         /**< The frequency division clock selects SRC CLK's 32 frequency division */
    RCC_DIV_CLK_SEL_64   = 6U,         /**< The frequency division clock selects SRC CLK's 64 frequency division */
    RCC_DIV_CLK_SEL_128  = 7U,         /**< The frequency division clock selects SRC CLK's 128 frequency division */
} rcc_div_clk_sel_t;
/**
 * @}
 */

/**
 * @defgroup rcc_clk_t DRV_RCC peripheral clock gating selection
 * @{
 */
typedef enum {
    #if (CONFIG_OM6239)
    RCC_CLK_LEDC       = RCC_DEV_CLK_GATE_LEDC_CLK_GATE_MASK,      /**< Defines module clock gating for LEDC */
    #else
    RCC_CLK_OTP        = RCC_DEV_CLK_GATE_OTP_CLK_GATE_MASK,       /**< Defines module clock gating for OTP */
    #endif
    RCC_CLK_FLASH      = RCC_DEV_CLK_GATE_FLASH_CLK_GATE_MASK,     /**< Defines module clock gating for FLASH */
    RCC_CLK_RF         = RCC_DEV_CLK_GATE_RF_CLK_GATE_MASK,        /**< Defines module clock gating for RF */
    RCC_CLK_USB        = RCC_DEV_CLK_GATE_USB_CLK_GATE_MASK,       /**< Defines module clock gating for USB */
    RCC_CLK_TIMER0     = RCC_DEV_CLK_GATE_TIMER_CLK_GATE_MASK,     /**< Defines module clock gating for TIMER */
    RCC_CLK_UART0      = RCC_DEV_CLK_GATE_UART_CLK_GATE_MASK,      /**< Defines module clock gating for UART */
    RCC_CLK_GPIO0      = RCC_DEV_CLK_GATE_GPIO_CLK_GATE_MASK,      /**< Defines module clock gating for GPIO */
    RCC_CLK_SWD        = RCC_DEV_CLK_GATE_SWD_CLK_GATE_MASK,       /**< Defines module clock gating for SWD */
    RCC_CLK_AES128     = RCC_DEV_CLK_GATE_AES_CLK_GATE_MASK,       /**< Defines module clock gating for AES */
    RCC_CLK_ANA        = RCC_DEV_CLK_GATE_ANA_CLK_GATE_MASK,       /**< Defines module clock gating for ANA */
    RCC_CLK_RTC        = RCC_DEV_CLK_GATE_RTC_CLK_GATE_MASK,       /**< Defines module clock gating for RTC */
    RCC_CLK_WDT        = RCC_DEV_CLK_GATE_WDT_CLK_GATE_MASK,       /**< Defines module clock gating for WDT */
    RCC_CLK_PWM        = RCC_DEV_CLK_GATE_PWM_CLK_GATE_MASK,       /**< Defines module clock gating for PWM */
    #if (CONFIG_OM6239)
    RCC_CLK_ENCODER    = RCC_DEV_CLK_GATE_ENCODER_CLK_GATE_MASK,   /**< Defines module clock gating for ENCODER */
    RCC_CLK_SENSCAN    = RCC_DEV_CLK_GATE_SENSOR_CLK_GATE_MASK,    /**< Defines module clock gating for SENSOR */
    #endif
} rcc_clk_t;
/**
 * @}
 */

/**
 * @defgroup rcc_rst_t DRV_RCC peripheral clock gating selection
 * @{
 */
typedef enum {
    RCC_RST_RF_FSM      = RCC_DEV_RST_CTRL_RF_FSM_RESET_MASK,       /**< Defines module RESET for RF_FSM */
    RCC_RST_RF          = RCC_DEV_RST_CTRL_RF_RESET_MASK,           /**< Defines module RESET for RF */
    RCC_RST_USB         = RCC_DEV_RST_CTRL_USB_RESET_MASK,          /**< Defines module RESET for USB */
    #if (CONFIG_OM6239)
    RCC_RST_GPIO0       = RCC_DEV_RST_CTRL_GPIO_RESET_MASK,         /**< Defines module RESET for GPIO */
    #endif
    RCC_RST_FLASH       = RCC_DEV_RST_CTRL_FLASH_RESET_MASK,        /**< Defines module RESET for FLASH */
    RCC_RST_TIMER0      = RCC_DEV_RST_CTRL_TIMER_RESET_MASK,        /**< Defines module RESET for TIMER */
    RCC_RST_AES128      = RCC_DEV_RST_CTRL_AES_RESET_MASK,          /**< Defines module RESET for AES */
    RCC_RST_OSC         = RCC_DEV_RST_CTRL_OSC_RESET_MASK,          /**< Defines module RESET for RCOSC32K calibration */
    RCC_RST_UART0       = RCC_DEV_RST_CTRL_UART_RESET_MASK,         /**< Defines module RESET for UART */
    RCC_RST_PWM         = RCC_DEV_RST_CTRL_PWM_RESET_MASK,          /**< Defines module RESET for PWM */
    #if (CONFIG_OM6239)
    RCC_RST_LEDC        = RCC_DEV_RST_CTRL_LEDC_RESET_MASK,         /**< Defines module RESET for LEDC */
    RCC_RST_ENCODER     = RCC_DEV_RST_CTRL_ENCODER_RESET_MASK,      /**< Defines module RESET for ENCODER */
    RCC_RST_SENSCAN     = RCC_DEV_RST_CTRL_SENSCAN_RESET_MASK,      /**< Defines module RESET for SENSOR */
    #endif
} rcc_rst_t;
/**
 * @}
 */

/**
 * @defgroup rcc_rst_type_t DRV_RCC cpu reset type
 * @{
 */
typedef enum {
    RCC_RST_TYPE_POWER_ON       = 0U,          /**< Defines cpu RESET by power on */
    RCC_RST_TYPE_WATCH_DOG      = 1U,          /**< Defines cpu RESET by watch dog */
    RCC_RST_TYPE_SOFT           = 2U,          /**< Defines cpu RESET by soft */
    RCC_RST_TYPE_DEEP_SLEEP     = 3U,          /**< Defines cpu RESET by deep sleep */
    RCC_RST_TYPE_DEEP_STAND_BY  = 4U,          /**< Defines cpu RESET by stand by */
} rcc_rst_type_t;
/**
 * @}
 */

#if (CONFIG_OM6239)
/**
 * @defgroup rcc_rtc_clk_source_t DRV_RTC rtc clock source
 * @{
 */
typedef enum {
    RCC_RTC_CLK_SOURCE_32K   = 0U,
    RCC_RTC_CLK_SOURCE_2M    = 1U,
} rcc_rtc_clk_source_t;
/**
 * @}
 */
#endif

/**
 * @brief DRV_RCC configuration structure
 */
typedef struct {
    rcc_sys_clk_sel_t   sys_clk_sel;         /**< SYS_CLK selection of the RCC module, see @ref rcc_sys_clk_sel_t type */
    rcc_div_clk_sel_t   div_clk_sel;         /**< DIV_CLK selection of the RCC module, see @ref rcc_div_clk_sel_t type */
    uint8_t             div_clk_flash;       /**< FLASH_DIV_CLK selection of the RCC module, range in[0,254] & even value */
    #if (CONFIG_OM6229)
    uint8_t             div_clk_otp;         /**< OPT_DIV_CLK selection of the RCC module, range in[0,31] */
    #endif
} rcc_config_t;
/**
 * @}
 */


/*******************************************************************************
 * MACROS
 */
/**
 *******************************************************************************
 * @brief  Enable or disable the peripheral clock.
 *         After reset, the peripheral clock (used for registers read/write access)
 *         maybe is disabled and the application software has to enable this clock
 *         before using it.
 *
 * @param  _rcc_clk_type rcc type, see @ref rcc_clk_t
 * @param  enable    0 is disable, 1 is enable
 *
 *******************************************************************************
 */
#define DRV_RCC_CLOCK_ENABLE(_rcc_clk_type, enable)                       \
    do {                                                                  \
        (enable) ? (OM_RCC->CLKGATE |= (_rcc_clk_type)) :                 \
                   (OM_RCC->CLKGATE &= ~(_rcc_clk_type));                 \
    } while(0)

/**
 *******************************************************************************
 * @brief  Reset the peripheral clock.
 *
 * @param  _rcc_rst_type rcc type, see @ref rcc_rst_t
 *
 *******************************************************************************
 */
#define DRV_RCC_RESET(_rcc_rst_type)                                 \
    do {                                                             \
        OM_RCC->RSTCTRL = _rcc_rst_type;                             \
    } while(0)


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief   Get CPU reset source
 *
 * @return  The CPU reset source, see @ref rcc_rst_type_t
 *******************************************************************************
 */
__STATIC_FORCEINLINE rcc_rst_type_t drv_rcc_get_reset(void)
{
    return (rcc_rst_type_t)(OM_RCC->RSTCTRL & 0x07);
}

/**
 *******************************************************************************
 * @brief               Initialization the RCC according to the specified configuration
 *
 * @param rcc_config    Configuration init structure pointer for RCC
 *
 * @return              status, see@ref om_error_t
 *******************************************************************************
 */
extern void drv_rcc_init(void);

/**
 *******************************************************************************
 * @brief                       Obtain the current system clock frequency.
 *
 * @param _dev_type             The peripheral module that you want to obtain the clock,
 *                              see @ref rcc_clk_t.
 *
 * @return                      uint32_t, Clock value
 *******************************************************************************
 */
extern uint32_t drv_rcc_clock_get(rcc_clk_t _dev_type);


#if (CONFIG_OM6239)
/**
 *******************************************************************************
 * @brief Set rtc clk source
 *
 * @param rtc_clk_source rtc clk source type, see @ref rcc_rtc_clk_source_t
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_rcc_rtc_clock_source_set(rcc_rtc_clk_source_t rtc_clk_source)
{
    OM_PMU->CLK32K_SEL = (rtc_clk_source ==  RCC_RTC_CLK_SOURCE_2M) ? PMU_CLK32K_SEL_RTC2M_EN_MASK : 0U;
}
#endif

#ifdef __cplusplus
}
#endif
#endif  /* (RTE_RCC) */

#endif  /* __DRV_RCC_H */

/** @} */
