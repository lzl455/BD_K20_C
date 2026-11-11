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
 * @file     drv_uart.c
 * @brief    uart driver
 * @date     18. Sep 2023
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_UART0)
#include <stddef.h>
#include "om_driver.h"


/*******************************************************************************
 * MACRO
 */
#define UART_FIFO_THRESHOLD   1
#define UART_FIFO_BUFF_SIZE   8


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @brief DRV_UART environment structure
 */
typedef struct {
    #if (RTE_UART_REGISTER_CALLBACK)
    drv_isr_callback_t          isr_cb;
    #endif /* (RTE_UART_REGISTER_CALLBACK) */
    uint8_t                    *tx_buf;            /**< Pointer to out data buffer, system to peripheral direction */
    uint8_t                    *rx_buf;            /**< Pointer to in data buffer */
    uint8_t                     tx_num;            /**< Total number of data to be send */
    uint8_t                     tx_cnt;            /**< Count of data sent*/
    uint8_t                     rx_num;            /**< Total number of data to be received, peripheral to system direction */
    uint8_t                     rx_cnt;            /**< Count of data received, peripheral to system direction */
} uart_env_t;


/*******************************************************************************
 * CONST & VARIABLES
 */
extern uint32_t SystemCoreClock;
#if (RTE_UART0)
static uart_env_t uart_env = {
    #if (RTE_UART_REGISTER_CALLBACK)
    .isr_cb         = NULL,
    #endif /* (RTE_UART_REGISTER_CALLBACK) */
    .tx_num         = 0,
    .tx_cnt         = 0,
    .tx_buf         = NULL,
    .rx_num         = 0,
    .rx_cnt         = 0,
    .rx_buf         = NULL,
};

#endif  /* RTE_UART0 */


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_uart_init(OM_UART_Type *om_uart, const uart_config_t *config)
{
    if ((om_uart == NULL) || (config == NULL) || (config->baudrate == 0)) {
        return OM_ERROR_PARAMETER;
    }

    drv_uart_control(om_uart, UART_CONTROL_CLK_ENABLE, NULL);
    drv_uart_control(om_uart, UART_CONTROL_RESET, NULL);
    #if (CONFIG_OM6236)
    drv_pmu_uart_pin_reuse(PMU_UART_PIN_SEL_TX, 1);
    drv_pmu_uart_pin_reuse(PMU_UART_PIN_SEL_RX, 1);
    #endif
    #if (CONFIG_OM6239)
    drv_pmu_uart_select(PMU_UART_SEL_IO_04_06);
    #endif
    /* Set Baudrate */
    om_uart->SMOD = 1;
    om_uart->SREL = (1 << 10) - (SystemCoreClock + (4 * config->baudrate)) / (8 * config->baudrate);
    /* Set word length, stop 1-bit, parity 0-bit */
    om_uart->SCON |= ((config->word_length << SCON_SM_POS) + SCON_REN_MASK
                    + SCON_TX_FIFO_EN_MASK + SCON_RX_FIFO_EN_MASK);
    register_set(&(om_uart->FIFO_TH), MASK_2REG(FIFO_TH_TX, UART_FIFO_THRESHOLD,
                                                FIFO_TH_RX, UART_FIFO_THRESHOLD));
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn, RTE_UART0_IRQ_PRIORITY);
    NVIC_EnableIRQ(UART0_IRQn);

    return OM_ERROR_OK;
}

om_error_t drv_uart_read(OM_UART_Type *om_uart, uint8_t *data, uint8_t num, uint32_t timeout_ms)
{
    om_error_t error = OM_ERROR_OK;

    for (uint8_t i = 0; i < num; i++) {
        /* Wait for RX data ready */
        while(om_uart->FIFO_ST & FIFO_ST_RX_FIFO_EMPTY_MASK);
        data[i] = om_uart->SBUF;
        DRV_WAIT_MS_UNTIL_TO((om_uart->INTR_STATUS & RX_BUSY_MASK), timeout_ms, error);
        if (error != OM_ERROR_OK) {
            return error;
        }
    }
    return error;
}

om_error_t drv_uart_read_int(OM_UART_Type *om_uart, uint8_t *data, uint8_t num)
{
    /* Save Rx buffer, number and rx_cnt */
    uart_env.rx_buf = data;
    uart_env.rx_num = num;
    uart_env.rx_cnt = 0;
    /* Enable Rx FIFO interrupt */
    OM_CRITICAL_BEGIN();
    register_set1(&om_uart->INTR_MASK, INTR_RX_FIFO_INT_MASK);
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

om_error_t drv_uart_write(OM_UART_Type *om_uart, uint8_t *data, uint8_t num, uint32_t timeout_ms)
{
    om_error_t error = OM_ERROR_OK;

    for (uint8_t i = 0; i < num; i++) {
        while(om_uart->FIFO_ST & FIFO_ST_TX_FIFO_FULL_MASK);
        om_uart->SBUF = data[i];
        DRV_WAIT_MS_UNTIL_TO((om_uart->INTR_STATUS & TX_BUSY_MASK), timeout_ms, error);
        if (error != OM_ERROR_OK) {
            return error;
        }
    }
    return error;
}

om_error_t drv_uart_write_int(OM_UART_Type *om_uart, uint8_t *data, uint8_t num)
{
    /* Save Tx buffer, number and tx_cnt */
    uart_env.tx_buf = data;
    uart_env.tx_num = num;
    uart_env.tx_cnt = 0;

    if (om_uart->FIFO_ST & FIFO_ST_TX_FIFO_FULL_MASK) {
        return OM_ERROR_FAIL;
    }
    OM_CRITICAL_BEGIN();
    /* Transmit data first */
    om_uart->SBUF = uart_env.tx_buf[uart_env.tx_cnt];
    uart_env.tx_cnt++;
    /* Enable Tx FIFO interrupt */
    register_set1(&om_uart->INTR_MASK, INTR_TX_FIFO_INT_MASK);
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

void *drv_uart_control(OM_UART_Type *om_uart, uart_control_t control, void *argu)
{
    switch (control) {
        case UART_CONTROL_RESET:
            #if (RTE_UART0)
            if ((uint32_t)om_uart == (uint32_t)OM_UART0) {
                DRV_RCC_RESET(RCC_RST_UART0);
                break;
            }
            #endif  /* (RTE_UART0) */
            break;
        case UART_CONTROL_CLK_DISABLE:
            #if (RTE_UART0)
            if ((uint32_t)om_uart == (uint32_t)OM_UART0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_UART0, 0U);
                break;
            }
            #endif  /* (RTE_UART0) */
            break;
        case UART_CONTROL_CLK_ENABLE:
            #if (RTE_UART0)
            if ((uint32_t)om_uart == (uint32_t)OM_UART0) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_UART0, 1U);
                break;
            }
            #endif  /* (RTE_UART0) */
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#if (RTE_UART_REGISTER_CALLBACK)
void drv_uart_register_isr_callback(OM_UART_Type *om_uart, drv_isr_callback_t isr_cb)
{
    uart_env.isr_cb = isr_cb;
}
#endif /* (RTE_UART_REGISTER_CALLBACK) */

__WEAK void drv_uart_isr_callback(OM_UART_Type *om_uart, drv_event_t event, uint8_t *data, uint8_t num)
{
    #if (RTE_UART_REGISTER_CALLBACK)
    if (uart_env.isr_cb != NULL) {
        uart_env.isr_cb(om_uart, event, data, (void *)(uint32_t)num);
    }
    #endif /* (RTE_UART_REGISTER_CALLBACK) */
}

__WEAK void drv_uart_isr(OM_UART_Type *om_uart)
{
    if ((om_uart->INTR_MASK & INTR_RX_FIFO_INT_MASK) && (om_uart->INTR_STATUS & RX_FIFO_CROSS_TH_MASK)) {
        /* Clear receive interrupt*/
        om_uart->INTR_STATUS = RX_FIFO_CROSS_TH_MASK;
        /* Rx interrupt is enabled and Rx data is ready */
        /* When rx_num is 0, uart will automatically receive data as long as
           interrupt triggered, and interrupt will not be closed.
           When rx_num is not 0, uart will receive data with expected length */
        if (uart_env.rx_num == 0) {
            uint8_t rx_buf[UART_FIFO_BUFF_SIZE];
            uint8_t cnt = 0;
            while ((!(om_uart->FIFO_ST & FIFO_ST_RX_FIFO_EMPTY_MASK)) && (cnt < sizeof(rx_buf))) {
                rx_buf[cnt++] = om_uart->SBUF;
            }
            /* Callback */
            drv_uart_isr_callback(om_uart, DRV_EVENT_COMMON_READ_COMPLETED, rx_buf, cnt);
        } else {
            while ((om_uart->FIFO_ST & FIFO_ST_RX_FIFO_EMPTY_MASK) == 0) {
                uart_env.rx_buf[uart_env.rx_cnt] = om_uart->SBUF;
                uart_env.rx_cnt++;
                if (uart_env.rx_cnt == uart_env.rx_num) {
                    /* Disable Rx interrupt */
                    om_uart->INTR_MASK &= ~INTR_RX_FIFO_INT_MASK;
                    /* Callback */
                    drv_uart_isr_callback(om_uart, DRV_EVENT_COMMON_READ_COMPLETED, uart_env.rx_buf, uart_env.rx_cnt);
                    break;
                }
            }
        }
    }
    if ((om_uart->INTR_MASK & INTR_TX_FIFO_INT_MASK) && (om_uart->INTR_STATUS & TX_FIFO_CROSS_TH_MASK)) {
        /* Clear transmit fifo interrupt*/
        om_uart->INTR_STATUS = TX_FIFO_CROSS_TH_MASK;
        while ((om_uart->FIFO_ST & FIFO_ST_TX_FIFO_FULL_MASK) == 0) {
            if (uart_env.tx_num == uart_env.tx_cnt) {
                /* All bytes are transmitted */
                /* Disable Tx interrupt first */
                om_uart->INTR_MASK &= ~INTR_TX_FIFO_INT_MASK;
                /* wait all tx_data transmit completed */
                while(om_uart->INTR_STATUS & TX_BUSY_MASK);
                /* Callback */
                drv_uart_isr_callback(om_uart, DRV_EVENT_COMMON_WRITE_COMPLETED, uart_env.tx_buf, uart_env.tx_cnt);
                break;
            } else {
                /* Continue byte transmit */
                om_uart->SBUF = uart_env.tx_buf[uart_env.tx_cnt];
                uart_env.tx_cnt++;
            }
        }
    }
}


#endif  /* (RTE_UART0) */


/** @} */
