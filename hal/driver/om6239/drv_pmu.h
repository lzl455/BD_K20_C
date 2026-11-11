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
 * @file     drv_pmu.h
 * @brief    PMU Driver
 * @date     22. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup PMU PMU
 * @ingroup  HAL_Driver
 * @brief    PMU Driver.
 * @details  PMU Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_PMU_H
#define __DRV_PMU_H

/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_PMU)
#include "om_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup pmu_power_id_t DRV_PMU power ID
 * @{
 */
typedef enum {
    PMU_POWER_ID_RTC32K      = 0U,
    PMU_POWER_ID_RTC2M       = 1U,
} pmu_power_id_t;
/**
 * @}
 */

/**
 * @defgroup pmu_power_t DRV_PMU power control type
 * @{
 */
typedef enum {
    PMU_POWER_DOWN     = 0U,     /**< PMU power down */
    PMU_POWER_ON       = 1U,     /**< PMU power on */
    PMU_POWER_UNKNOWN  = 2U,     /**< PMU power unkown, unknown power id */
} pmu_power_t;
/**
 * @}
 */

/**
 * @defgroup pmu_pll_ctrl_t DRV_PMU pll control type
 * @{
 */
typedef enum {
    PMU_PLL_CTRL_STOP     = 0U,     /**< PMU control pll stop */
    PMU_PLL_CTRL_START    = 1U,     /**< PMU control pll start */
    PMU_PLL_CTRL_RESET    = 2U,     /**< PMU control pll reset */
} pmu_pll_ctrl_t;
/**
 * @}
 */

/**
 * @defgroup pmu_wakeup_src_t DRV_PMU wakeup source type
 * @{
 */
typedef enum {
    PMU_WAKEUP_SRC_IO          = 1u << 0,   /**< wakeup by IO */
    PMU_WAKEUP_SRC_RTC         = 1u << 1,   /**< wakeup by RTC */
    PMU_WAKEUP_SRC_RTC_TICK    = 1u << 2,   /**< wakeup by RTC TICK */
    PMU_WAKEUP_SRC_RTC_ALARM   = 1u << 3,   /**< wakeup by RTC ALARM */
    PMU_WAKEUP_SRC_RTC_ALARM1  = 1u << 4,   /**< wakeup by RTC ALARM1 */
    PMU_WAKEUP_SRC_WDT         = 1u << 5,   /**< wakeup by WDT */
    PMU_WAKEUP_SRC_VBUS_DET    = 1u << 6,   /**< wakeup by VBUS DET */
} pmu_wakeup_src_t;
/**
 * @}
 */

/**
 * @defgroup pmu_power_mode_t DRV_PMU OTP mode type
 * @{
 */
typedef enum {
    PMU_POWER_MODE_KEEP      = 0U,     /**< keep on manage */
    PMU_POWER_MODE_AUTO      = 1U,     /**< Automatically manage */
} pmu_power_mode_t;
/**
 * @}
 */

/**
 * @defgroup pmu_dev_id_t DRV_PMU OTP type
 * @{
 */
typedef enum {
    PMU_DEV_ID_FLASH_POWER    = 0U,     /**< FLASH POWER */
} pmu_dev_id_t;
/**
 * @}
 */

/**
 * @defgroup pmu_lpms_level_t DRV_PMU low power mode
 * @{
 */
typedef enum {
    PMU_LPM_IDLE            = 0U,     /**< All modules are alive, but CPU clock is gating */
    PMU_LPM_STOP0           = 1U,     /**< All clocks off except RCOSC32K and XTAL; WKUP pin, RTC event, WDT reset and RF interrupt can wakeup */
    PMU_LPM_STOP1           = 2U,     /**< All clocks off except XTAL; WKUP pin, RTC event, WDT reset can wakeup */
    PMU_LPM_STANDBY         = 3U,     /**< All clocks off except XTAL; WKUP pin, RTC event, WDT reset can wakeup */
    PMU_LPM_RETENTION       = 4U,     /**< All clocks off; WKUP pin can wakeup */
    PMU_LPM_DEEP_SLEEP      = 5U,     /**< All clocks off; WKUP pin can wakeup */
    PMU_LPM_ACTIVE          = 6U,     /**< All modules are alive, and CPU clock is not gating */
} pmu_lpm_t;
/**
 * @}
 */

/**
 * @defgroup pmu_pin_mode_t PMU pin mode type
 * @{
 */
typedef enum {
    PMU_PIN_MODE_PP       = 0U,  /**< Push–pull output */
    PMU_PIN_MODE_FLOAT    = 1U,  /**< Input Floating Mode */
    PMU_PIN_MODE_PU       = 2U,  /**< pull up input */
    PMU_PIN_MODE_PD       = 3U,  /**< pull down input */
} pmu_pin_mode_t;
/**
 * @}
 */

/**
 * @defgroup pmu_pin_driver_current_t PMU pin output speed type
 * @{
 */
typedef enum {
    PMU_PIN_DRIVER_CURRENT_8MA     = 0U,  /**< PMU pin driver current is 8mA */
    PMU_PIN_DRIVER_CURRENT_24MA    = 1U,  /**< PMU pin driver current is 24mA */
    PMU_PIN_DRIVER_CURRENT_32MA    = 2U,  /**< PMU pin driver current is 32mA */
    PMU_PIN_DRIVER_CURRENT_48MA    = 3U,  /**< PMU pin driver current is 48mA */
} pmu_pin_driver_current_t;
/**
 * @}
 */

/**
 * @defgroup gpio_wakeup_t PMU pin wakeup type
 * @{
 */
typedef enum {
    PMU_PIN_WAKEUP_TYPE_DISABLE = 0U,  /**< PMU pin no wakeup       */
    PMU_PIN_WAKEUP_TYPE_RISE    = 1U,  /**< PMU pin rising wakeup   */
    PMU_PIN_WAKEUP_TYPE_FALL    = 2U,  /**< PMU pin FALLING wakeup  */
} pmu_pin_wakeup_type_t;
/**
 * @}
 */

/**
 * @defgroup pmu_uart_sel_t PMU uart select
 * @{
 */
typedef enum {
    PMU_UART_SEL_IO_04_06  = 0U,  /**< PMU uart select GPIO04(TX) and GPIO06(RX) */
    PMU_UART_SEL_IO_09_10  = 1U,  /**< PMU uart select GPIO10(TX) and GPIO09(RX) */
    PMU_UART_SEL_IO_18_21  = 2U,  /**< PMU uart select GPIO21(TX) and GPIO18(RX) */
} pmu_uart_sel_t;
/**
 * @}
 */

/**
 * @defgroup pmu_ledc_sel_t PMU ledc select
 * @{
 */
typedef enum {
    PMU_LEDC_SEL_IO_01   = 0U,  /**< PMU ledc select GPIO01 */
    PMU_LEDC_SEL_IO_05   = 1U,  /**< PMU ledc select GPIO05 */
    PMU_LEDC_SEL_IO_17   = 2U,  /**< PMU ledc select GPIO17 */
    PMU_LEDC_SEL_IO_27   = 3U,  /**< PMU ledc select GPIO27 */
} pmu_ledc_sel_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Check the wakeup source from low power by IO and/or RTC
 *
 * @return PMU wakeup source type, see @ref pmu_wakeup_src_t
 *******************************************************************************
 */
__STATIC_FORCEINLINE pmu_wakeup_src_t drv_pmu_get_wakeup_src(void)
{
    return (pmu_wakeup_src_t)((OM_PMU->WKINT_CLR & PMU_WKINT_CLR_ANY_WK_MASK) >> PMU_WKINT_CLR_WK_SRC_POS);
}

/**
 *******************************************************************************
 * @brief Clear wakeup source from low power by IO
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_pmu_clear_wakeup(void)
{
    OM_PMU->WKINT_CLR = PMU_WKINT_CLR_WK_INT_CLR_MASK;
}

/**
 *******************************************************************************
 * @brief Get the current level of low power mode
 *
 * @return LPM level
 *******************************************************************************
 */
__STATIC_FORCEINLINE uint8_t drv_pmu_get_low_power_mode(void)
{
    return OM_PMU->LPMS & PMU_LPMS_LOW_PWR_MODE_EN_MASK;
}

/**
 *******************************************************************************
 * @brief Enable/Disable RAM retention
 *
 * @param en enable is 1,disable is 0
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_pmu_ram_retention_ctrl(uint8_t en)
{
    if (en) {
        /* OM6229: SRAM power domain is merged into SYS(RR) domain on 2021/11/29. */
        OM_PMU->LPMS |= PMU_LPMS_KEEP_SRAM_EN_MASK;
    } else {
        OM_PMU->LPMS &= ~PMU_LPMS_KEEP_SRAM_EN_MASK;
    }
}

/**
 *******************************************************************************
 * @brief PMU control uart select
 *
 * @param uart_sel uart type, see @ref pmu_uart_sel_t
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_pmu_uart_select(pmu_uart_sel_t uart_sel)
{
    register_set(&(OM_PMU->PINMUX_SEL), PMU_PINMUX_SEL_UART_SEL_MASK, uart_sel);
}

/**
 *******************************************************************************
 * @brief PMU control ledc select
 *
 * @param uart_sel ledc type, see @ref pmu_ledc_sel_t
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_pmu_ledc_sel(pmu_ledc_sel_t ledc_sel)
{
    register_set(&(OM_PMU->PINMUX_SEL), PMU_PINMUX_SEL_LEDC_SEL_MASK, ledc_sel << PMU_PINMUX_SEL_LEDC_SEL_POS);
}

/**
 *******************************************************************************
 * @brief PMU control system PLL
 *
 * @param syspll_ctrl syspll control type, see @ref pmu_pll_ctrl_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_pmu_syspll_ctrl(pmu_pll_ctrl_t syspll_ctrl);

/**
 *******************************************************************************
 * @brief Set PMU power
 *
 * @param power_id    power id
 * @param power       power state
 *
 * @return None
 *******************************************************************************
 */
extern void drv_pmu_power_set(pmu_power_id_t power_id, pmu_power_t power);

/**
 *******************************************************************************
 * @brief Get PMU power
 *
 * @param power_id    power id
 *
 * @return power      power state
 *******************************************************************************
 */
extern pmu_power_t drv_pmu_power_get(pmu_power_id_t power_id);

/**
 *******************************************************************************
 * @brief PMU otp cs/power mode select
 *
 * @param dev_id device id, see @ref pmu_dev_id_t
 * @param power_mode Keep on or Automatically manage otp cs/power, see @ref pmu_power_mode_t
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_pmu_power_mode_select(pmu_dev_id_t dev_id, pmu_power_mode_t power_mode);

/**
 *******************************************************************************
 * @brief Set the specific level of low power mode
 *
 * @param level low power mode, see @ref pmu_lpms_t
 *
 * @return None
 *******************************************************************************
 */
extern __RAM_CODE void drv_pmu_set_low_power_mode(pmu_lpm_t level);

/**
 *******************************************************************************
 * @brief Check whether CPU can resume to the previous execution point from low power (standby or RR only)
 *
 * @return true or false
 *******************************************************************************
 */
extern bool drv_pmu_can_pop_cpu(void);

/**
 *******************************************************************************
 * @brief Set pin mode
 *
 * @param pin_idx pin idx, range in[0, 31]
 * @param mode  pin mode
 *******************************************************************************
 **/
extern void drv_pmu_pin_mode_set(uint8_t pin_idx, pmu_pin_mode_t mode);

/**
 *******************************************************************************
 * @brief Set gpio driven current
 *
 * @param pin_idx  pin idx, range in[0, 15]
 * @param driven  current driven (Large driven current should be push-pull output)
 *******************************************************************************
 **/
extern void drv_pmu_pin_driven_current_set(uint8_t pin_idx, pmu_pin_driver_current_t driven);

/**
 *******************************************************************************
 * @brief pmu gpio wakeup pin setup
 *
 * @param pin_idx  pin idx, range in[0, 31]
 * @param trigger_type  wakeup trigger type
 *******************************************************************************
 **/
extern void drv_pmu_wakeup_pin_set(uint8_t pin_idx, pmu_pin_wakeup_type_t trigger_type);

extern void drv_pmu_rf_mode_set(uint8_t rf_mode);
extern uint8_t drv_pmu_rf_mode_get(void);


#ifdef __cplusplus
}
#endif
#endif  /* (RTE_PMU) */

#endif  /* __DRV_PMU_H */

/** @} */
