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
 * @file     drv_common.h
 * @brief    DRIVER_COMMON
 * @date     03. April 2020
 * @author   OnMicro SW Team
 *
 * @defgroup DRIVER_COMMON DRIVER_COMMON
 * @ingroup  Peripheral
 * @brief    COMMON Typedefs For Driver
 * @details  COMMON Typedefs For Driver
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


#ifndef __DRV_COMMON_H
#define __DRV_COMMON_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#include <stdint.h>


#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * MACROS
 */
/**
 * @brief  peripheral driver timeout max delay
 */
#define DRV_MAX_DELAY                0xFFFFFFFFU


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @brief    General peripheral driver event
 */
typedef enum {
    /// [0-15]： driver common event: [0-3] common error event, [4-8] common event
    DRV_EVENT_COMMON_NONE                           = 0,
    DRV_EVENT_COMMON_ERROR                          = (1U << 0),                /**< Common error */
    DRV_EVENT_COMMON_ABORT                          = (1U << 1),                /**< Abort transmit/receive/read/write event */

    DRV_EVENT_COMMON_GENERAL                        = (1U << 4),                /**< used for General event */
    DRV_EVENT_COMMON_WRITE_COMPLETED                = (1U << 5),                /**< write completed, from system to peripheral direction */
    DRV_EVENT_COMMON_READ_COMPLETED                 = (1U << 6),                /**< read completed, from peripheral to system direction */
    DRV_EVENT_COMMON_READ_WRITE_COMPLETED           = (1U << 5) + (1U << 6),    /**< read and write completed, such as SPI peripheral */
    DRV_EVENT_COMMON_RX_OVERFLOW                    = (1U << 7),                /**< Received FIFO overflow event */
    DRV_EVENT_COMMON_DMA2PERIPH_COMPLETED           = (1U << 8),                /**< system DMA to peripheral completed event, from system fo peripheral direction */

    /// [16-32]: driver private event, example: DRV_EVENT_PPP_xxx
    /// ADC
    DRV_EVENT_ADC_EOC                               = (1U << 16),
    DRV_EVENT_ADC_FIFO_HALF                         = (1U << 17),
    DRV_EVENT_ADC_FIFO_FULL                         = (1U << 18),
    DRV_EVENT_ADC_FIFO_OVERFLOW                     = (1U << 19),

    // I2C
    DRV_EVENT_I2C_TRANS                             = (1U << 16),

    // SysTick
    DRV_EVENT_SYSTICK                               = (1U << 16),

    // RTC
    DRV_EVENT_RTC_TICK                               = (1U << 0),
    DRV_EVENT_RTC_ALARM0                             = (1U << 1),
    DRV_EVENT_RTC_ALARM1                             = (1U << 2),

    // TIMER
    DRV_EVENT_LOW_TIMER_OVERFLOW_FLAG                = (1U << 0),
    DRV_EVENT_HIGH_TIMER_OVERFLOW_FLAG               = (1U << 1),

    // SENSCAN
    DRV_EVENT_SENSCAN_SCAN_DONE                      = (1U << 0),
    DRV_EVENT_SENSCAN_RESYNC_START                   = (1U << 1),
    DRV_EVENT_SENSCAN_RESYNC_DONE                    = (1U << 2),
    DRV_EVENT_SENSCAN_RESYNC_SCAN                    = (1U << 3),
    DRV_EVENT_SENSCAN_CFG_DONE                       = (1U << 4),
} drv_event_t;

/**
 * @brief general driver isr event callback prototype
 *
 * @note  om_reg: peripheral registers base(GPDMA channel base for gpdma peripheral)
 */
typedef void(*drv_isr_callback_t)(void *om_reg, drv_event_t event, void *param0, void *param1);

/**
 * @brief General peripheral driver environment
 */
typedef struct {
    drv_isr_callback_t           isr_cb;            /**< isr event callback */
    uint16_t                     tx_num;            /**< Total number of data to be send */
    uint16_t                     tx_cnt;            /**< Count of data sent*/
    uint8_t                     *tx_buf;            /**< Pointer to out data buffer, system to peripheral direction */
    uint16_t                     rx_num;            /**< Total number of data to be received, peripheral to system direction */
    uint16_t                     rx_cnt;            /**< Count of data received, peripheral to system direction */
    uint8_t                     *rx_buf;            /**< Pointer to in data buffer  */
} drv_env_t;

/**
 * @brief peripheral resource description
 */
typedef struct {
    uint32_t                     cap;               /**< capabilities               */
    void                        *reg;               /**< peripheral registers base  */
    void                        *env;               /**< peripheral environment     */
} drv_resource_t;


#ifdef __cplusplus
}
#endif

#endif  /* __DRV_COMMON_H */


/** @} */
