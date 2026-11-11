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
 * @file     drv_uart.h
 * @brief    UART Driver
 * @date     18. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup UART UART
 * @ingroup  HAL_Driver
 * @brief    UART Driver
 * @details  UART Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_UART_H
#define __DRV_UART_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_UART0)
#include "om_device.h"

#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup uart_control_t UART control type
 * @{
 */
typedef enum {
    UART_CONTROL_RESET             = 0U,    /**< Reset UART. argu with NULL, return OM_ERROR_OK */
    UART_CONTROL_CLK_DISABLE       = 1U,    /**< Disable UART clock. argu with NULL, return OM_ERROR_OK */
    UART_CONTROL_CLK_ENABLE        = 2U,    /**< Enable UART clock. argu with NULL, return OM_ERROR_OK  */
} uart_control_t;
/**
 * @}
 */

/**
 * @defgroup uart_word_length_t UART word length type
 * @{
 */
typedef enum uart_word_length {
    UART_WORD_LENGTH_8  = 1U,       /**< 8 bits in a word */
    UART_WORD_LENGTH_9  = 3U,       /**< 9 bits in a word */
} uart_word_length_t;
/**
 * @}
 */

/**
 * @brief DRV_UART configuration init structure
 * @{
 */
typedef struct uart_config {
    uint32_t                    baudrate;       /**< UART baudrate */
    uart_word_length_t          word_length;    /**< UART word length, see @ref uart_word_length_t */
} uart_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Initialize the UART with parameters in uart_config_t
 *
 * @param om_uart           The UART device address
 * @param config            The configuration structure pointer, see @ref uart_config_t
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_uart_init(OM_UART_Type *om_uart, const uart_config_t *config);

/**
 *******************************************************************************
 * @brief UART read data
 *
 * @param om_uart           The UART device address
 * @param data              The data pointer of the data to be read
 * @param num               The number of data to be read
 * @param timeout_ms        The timeout in ms for each read operation
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_uart_read(OM_UART_Type *om_uart, uint8_t *data, uint8_t num, uint32_t timeout_ms);

/**
 *******************************************************************************
 * @brief UART read data with interrupt enabled
 *
 * @param om_uart           The UART device address
 * @param data              The data pointer of the data to be read
 * @param num               The number of data to be read
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_uart_read_int(OM_UART_Type *om_uart, uint8_t *data, uint8_t num);

/**
 *******************************************************************************
 * @brief UART write data
 *
 * @param om_uart           The UART device address
 * @param data              The data pointer of the data to be write
 * @param num               The number of data to be write
 * @param timeout_ms        The timeout in ms for each write operation
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_uart_write(OM_UART_Type *om_uart, uint8_t *data, uint8_t num, uint32_t timeout_ms);

/**
 *******************************************************************************
 * @brief UART write data with interrupt enabled
 *
 * @param om_uart           The UART device address
 * @param data              The data pointer of the data to be write
 * @param num               The number of data to be write
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_uart_write_int(OM_UART_Type *om_uart, uint8_t *data, uint8_t num);

/**
 *******************************************************************************
 * @brief Control UART interface.
 *
 * @param[in] om_uart       Pointer to UART
 * @param[in] control        Operation
 * @param[in] argu           Operation argument
 *
 * @return status:           Control status
 *******************************************************************************
 */
extern void *drv_uart_control(OM_UART_Type *om_uart, uart_control_t control, void *argu);

/**
 *******************************************************************************
 * @brief The UART interrupt service routine function, should be called in UART IRQHandler
 *
 * @param om_uart           The UART device address
 *
 * @return None
 *******************************************************************************
 */
extern void drv_uart_isr(OM_UART_Type *om_uart);

#if (RTE_UART_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register interrupt service routine callback for specified UART device interrupt
 *
 * @param om_uart           The UART device address
 * @param isr_cb            The event callback function, see @ref drv_isr_callback_t, in which
 *                          param0 is the data pointer of data to be read and write, param1 is
 *                          the data buffer valid data count
 *
 * @return None
 *******************************************************************************
 */
extern void drv_uart_register_isr_callback(OM_UART_Type *om_uart, drv_isr_callback_t isr_cb);
#endif /* (RTE_UART_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for UART driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the UART driver.
 *
 * @param om_uart           The UART device address
 * @param event             The driver event, which could be the combination of fallowing events
 *                          @arg DRV_EVENT_COMMON_WRITE_COMPLETED:      write completed
 *                          @arg DRV_EVENT_COMMON_READ_COMPLETED:       read completed
 * @param data              The data pointer of data to be read or write
 * @param num               The data buffer valid data count
 *
 * @return None
 *******************************************************************************
 */
extern void drv_uart_isr_callback(OM_UART_Type *om_uart, drv_event_t event, uint8_t *data, uint8_t num);


#ifdef  __cplusplus
}
#endif

#endif /* (RTE_UART0) */

#endif  /* __DRV_UART_H */

/** @} */
