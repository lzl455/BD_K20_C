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
 * @file     drv_gpio.h
 * @brief    GPIO Driver
 * @date     18. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup GPIO GPIO
 * @ingroup  HAL_Driver
 * @brief    GPIO Driver
 * @details  GPIO Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_GPIO0)

#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * MACROS
 */
#define GPIO_MASK(gpio_idx)   (1U << (gpio_idx))
#define GPIOA_PIN_NUMBER      32U


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup GPIO Mask: bit field for gpio, 1 indicates valid, 0 indicates invalid
 * @{
 */
typedef uint32_t gpio_mask_t;
/**
 * @}
 */

/**
 * @defgroup gpio_trig_t GPIO trigger type
 * @{
 */
typedef enum {
    GPIO_TRIG_NONE           = 0U,  /**< GPIO trigger None         */
    GPIO_TRIG_RISING_EDGE    = 1U,  /**< GPIO rising edge trigger  */
    GPIO_TRIG_FALLING_EDGE   = 2U,  /**< GPIO falling edge trigger */
    GPIO_TRIG_BOTH_EDGE      = 3U,  /**< GPIO both edge trigger    */
    GPIO_TRIG_LOW_LEVEL      = 4U,  /**< GPIO low level trigger    */
    GPIO_TRIG_HIGH_LEVEL     = 5U,  /**< GPIO high level trigger   */
} gpio_trig_t;
/**
 * @}
 */

/**
 * @defgroup gpio_dir_t GPIO direction type
 * @{
 */
typedef enum {
    GPIO_DIR_OUTPUT   = 0U,  /**< GPIO direction output */
    GPIO_DIR_INPUT    = 1U,  /**< GPIO direction input  */
} gpio_dir_t;
/**
 * @}
 */

/**
 * @defgroup gpio_control_t GPIO control type
 * @{
 */
typedef enum {
    GPIO_CONTROL_CLK_DISABLE       = 0U,    /**< Disable GPIO clock, argu is NULL, return OM_ERROR_OK */
    GPIO_CONTROL_CLK_ENABLE        = 1U,    /**< Enable GPIO clock, argu is NULL, return OM_ERROR_OK */
    GPIO_CONTROL_RESET             = 2U,    /**< Reset GPIO, argu is NULL, return OM_ERROR_OK */
} gpio_control_t;
/**
 * @}
 */

/**
 * @brief DRV_GPIO configuration init stucture
 * @{
 */
typedef struct {
    OM_GPIO_Type        *om_gpio;        /**< Pointer to GPIO */
    uint8_t              gpio_idx;   /**< Peripheral to be connected to the selected pins,range[0,15] */
    gpio_trig_t          trig : 3;       /**< GPIO trigger type, see @ref gpio_trig_t */
    gpio_dir_t           dir : 1;        /**< GPIO direction type, see @ref gpio_dir_t */
    uint8_t              out_val : 1;    /**< Used when dir config as output, range in [0, 1] */
} gpio_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Set GPIO direction
 *
 * @param[in] om_gpio        Pointer to GPIO
 * @param[in] gpio_mask      GPIO pin mask
 * @param[in] dir            GPIO direction
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_gpio_set_dir(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, gpio_dir_t dir)
{
    if (dir == GPIO_DIR_OUTPUT) {
        om_gpio->OUTENSET = gpio_mask;
    } else {
        om_gpio->OUTENCLR = gpio_mask;
    }
}

/**
 *******************************************************************************
 * @brief Get GPIO direction
 *
 * @param om_gpio        Pointer to GPIO
 * @param gpio_mask      GPIO pin mask
 *
 * @return GPIO direction
 *******************************************************************************
 */
__STATIC_FORCEINLINE gpio_dir_t drv_gpio_get_dir(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{
    if (om_gpio->OUTENSET & gpio_mask) {
        return GPIO_DIR_OUTPUT;
    } else {
        return GPIO_DIR_INPUT;
    }
}

/**
 *******************************************************************************
 * @brief Read the specified port pin input
 *
 * @param om_gpio        Pointer to GPIO
 * @param gpio_mask      GPIO pin mask
 *
 * @return The input port pin state: 0 is low level, 1 is high level
 *******************************************************************************
 */
__STATIC_FORCEINLINE uint32_t drv_gpio_read(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{
    return (om_gpio->DATA & gpio_mask);
}

/**
 *******************************************************************************
 * @brief Write the specified GPIO pin output
 *
 * @param om_gpio    Pointer to GPIO
 * @param gpio_mask  GPIO pin mask
 * @param val        specifies the value to be written to the selected bit, value is 0 or 1
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_gpio_write(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, uint8_t val)
{
    #if ((CONFIG_OM6236) || (CONFIG_OM6239))
    if(val) {
        om_gpio->DATAOUTSET = gpio_mask;
    } else {
        om_gpio->DATAOUTCLR = gpio_mask;
    }
    #else
    OM_CRITICAL_BEGIN();
    if(val) {
        om_gpio->DATAOUT |= gpio_mask;
    } else {
        om_gpio->DATAOUT &= ~gpio_mask;
    }
    OM_CRITICAL_END();
    #endif
}

/**
 *******************************************************************************
 * @brief Toggle a pin logical state
 *
 * @param om_gpio Pointer to GPIO
 * @param gpio_mask GPIO pin mask
 *
 * @return None
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_gpio_toggle(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{
    //OM_CRITICAL_BEGIN();
    om_gpio->DATAOUT ^= gpio_mask;
    //OM_CRITICAL_END();
}

/**
 *******************************************************************************
 * @brief Read GPIO port input
 *
 * @param[in] om_gpio        Pointer to GPIO
 *
 * @return GPIO port value
 *******************************************************************************
 */
__STATIC_FORCEINLINE uint32_t drv_gpio_port_read(OM_GPIO_Type *om_gpio)
{
    return om_gpio->DATA;
}

/**
 *******************************************************************************
 * @brief Write GPIO port output
 *
 * @param om_gpio        Pointer to GPIO
 * @param port_val       GPIO port value
 *******************************************************************************
 */
__STATIC_FORCEINLINE void drv_gpio_port_write(OM_GPIO_Type *om_gpio, uint32_t port_val)
{
    om_gpio->DATAOUT = port_val;
}

/**
 *******************************************************************************
 * @brief GPIO initialization
 *
 * @param gpio_config      Configuration for GPIO
 * @param gpio_config_num  Configuration number for GPIO
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_gpio_init(const gpio_config_t *gpio_config, uint32_t gpio_config_num);

/**
 *******************************************************************************
 * @brief Set GPIO pin trigger type
 *
 * @param om_gpio Pointer to GPIO
 * @param gpio_mask GPIO pin mask
 * @param trig gpio trigger type, see @ref gpio_trig_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_gpio_set_trig(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, gpio_trig_t trig);

/**
 *******************************************************************************
 * @brief Control GPIO interface.
 *
 * @param[in] om_gpio        Pointer to GPIO port, Donot GPIO_CONTROL_CLK_DISABLE if using sleep
 * @param[in] control        Operation
 * @param[in] argu           Not used, always set NULL
 *
 * @return                   Control status, always return OM_ERROR_OK
 *******************************************************************************
 */
extern void *drv_gpio_control(OM_GPIO_Type *om_gpio, gpio_control_t control, void *argu);

#if (RTE_GPIO0_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register event callback for GPIO interrupt
 *
 * @param isr_cb Pointer to callback
 *
 * @return None
 *******************************************************************************
 */
extern void drv_gpio_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* (RTE_GPIO0_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief Handle GPIO interrupt request.
 *
 * @param om_gpio Pointer to GPIO
 *
 * @return None
 *******************************************************************************
 */
extern void drv_gpio_isr(OM_GPIO_Type *om_gpio);

#ifdef  __cplusplus
}
#endif

#endif /* (RTE_GPIO0) */

#endif  /* __DRV_GPIO_H */

/** @} */
