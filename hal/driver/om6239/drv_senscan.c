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
 * @file     drv_senscan.c
 * @brief    senscan driver
 * @date     1. Nov 2023
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
#if (RTE_SENSCAN)
#include <stddef.h>
#include "drv_senscan.h"
#include "mouse.h"
#include "main.h"
#include "time_delay.h"

/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_SENSCAN_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t    isr_cb;
} senscan_env_t;
#endif /* (RTE_SENSCAN_REGISTER_CALLBACK) */

#define mSENSOR_SCK_OUT         OM_GPIO0->OUTENSET = (1<<SENSOR_SCLK_PIN)
#define mSENSOR_SCK_IN          OM_GPIO0->OUTENCLR = (1<<SENSOR_SCLK_PIN)

#define mSENSOR_SDIO_OUT        OM_GPIO0->OUTENSET = (1<<SENSOR_SDIO_PIN)
#define mSENSOR_SDIO_IN         OM_GPIO0->OUTENCLR = (1<<SENSOR_SDIO_PIN)

#define mSENSOR_SCK_H           OM_GPIO0->DATAOUTSET = GPIO_MASK(SENSOR_SCLK_PIN)
#define mSENSOR_SCK_L           OM_GPIO0->DATAOUTCLR = GPIO_MASK(SENSOR_SCLK_PIN)
#define mSENSOR_SDIO_H          OM_GPIO0->DATAOUTSET = GPIO_MASK(SENSOR_SDIO_PIN)
#define mSENSOR_SDIO_L          OM_GPIO0->DATAOUTCLR = GPIO_MASK(SENSOR_SDIO_PIN)
#define mSENSOR_SDIO            (OM_GPIO0->DATA & (1<<SENSOR_SDIO_PIN))

/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_SENSCAN_REGISTER_CALLBACK)
static senscan_env_t senscan_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_SENSCAN_REGISTER_CALLBACK) */

//----------------------------------------------------------------------------
// Sensor相关定义
//
//----------------------------------------------
// ADDR_REG

uint8_t         const       sensor_init_tbl[] =
{
    0x00,           // SENSCAN_IDADDR
    0x30,           // SENSCAN_ID
    0x02,           // SENSCAN_MOADDR
    0x03,           // SENSCAN_XADDR
    0x04,           // SENSCAN_YADDR
    0x12,           // SENSCAN_HADDR1
    0xFF,           // SENSCAN_HADDR2
};
//----------------------------------------------
// TR
#define iT_SRAD                 1
#define iT_SRR                  0
//----------------------------------------------
// TNS
#define iT_SCLK_NCS             0
#define iT_NCS_SCLK             0

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
void drv_senscan_init(void)
{
    // Enable senscan clk
    drv_senscan_control(OM_SENSCAN, SENSCAN_CONTROL_CLK_ENABLE, NULL);
    NVIC_ClearPendingIRQ(SENSCAN_IRQn);
    NVIC_SetPriority(SENSCAN_IRQn, RTE_SENSCAN_IRQ_PRIORITY);
    NVIC_EnableIRQ(SENSCAN_IRQn);

    // Config senser addr and id
    for (uint32_t i = 0; i < 7; i++) {
        OM_SENSCAN->ADDR_REG[i] = sensor_init_tbl[i];
    }
//----------------------------------------------
// CSR
    // Config mode、scan_step、data format and deltaxy_rev
    register_set(&(OM_SENSCAN->CSR), MASK_6REG(SENSACN_CSR_SCAN_MODE,       SENSCAN_SCAN_MODE_CONTINUOUS,
                                               SENSACN_CSR_DATA_FORMAT,     SENSCAN_DATA_FORMAT_8BIT,
                                               SENSACN_CSR_DELTAXY_REV,     SENSCAN_DELTAXY_REV_4_7BIT,
                                               SENSACN_CSR_SPI_MODE,        SENSCAN_SPI_MODE_2_WIRE,
                                               SENSACN_CSR_SPI_CLK_SEL,     1U,
                                               SENSACN_CSR_WAKE_EN,         1U));
    // Config scan time, scan time = (scan_freq+1)ms
    OM_SENSCAN->SCAN_FREQ = mSEN_SCAN_US(2500);
    // Config resync time
    register_set(&(OM_SENSCAN->RESYNC), MASK_2REG(SENSACN_RESYNC_T_RESYNC,  SENSCAN_RESYNC_LOW_TIME_1MS,
                                                  SENSACN_RESYNC_T_WDT,     SENSCAN_RESYNC_HIGH_TIME_32MS));
    OM_SENSCAN->TR = (iT_SRR << SENSACN_IR_TSRR_TIM_POS) | iT_SRAD;
    OM_SENSCAN->TNS = (iT_NCS_SCLK << SENSACN_TNS_TNS_TIM_POS) | iT_SCLK_NCS;
}

om_error_t drv_senscan_start(OM_SENSCAN_Type *om_senscan, uint32_t *x_data, uint32_t *y_data)
{
    if (om_senscan == NULL) {
        return OM_ERROR_PARAMETER;
    }

    if (om_senscan->CSR & SENSACN_CSR_DATA_VALID_MASK) {
        *x_data = om_senscan->X_DATA;
        *y_data = om_senscan->Y_DATA;
    } else {
        *x_data = 0;
        *y_data = 0;
    }

    return OM_ERROR_OK;
}

om_error_t drv_senscan_start_int(OM_SENSCAN_Type *om_senscan)
{
    if (om_senscan == NULL) {
        return OM_ERROR_PARAMETER;
    }
    // Enable all interrupt
    om_senscan->IER = SENSACN_IER_SCAN_DONE_MASK | SENSACN_IER_SCAN_RESYNC_MASK;

    return OM_ERROR_OK;
}

bool  bscan_sensor_en;

void drv_senscan_begin(void)
{

}

void drv_senscan_stop(void)
{
    uint8_t i;

    if(bscan_sensor_en)
    {
        bscan_sensor_en = 0;
        register_set1(&(OM_SENSCAN->CSR), SENSACN_CSR_SCAN_STOP_MASK);
        for(i=0; i<250; i++)
        {
            if(0==(OM_SENSCAN->CSR & SENSACN_CSR_SCAN_EN_MASK))
                break;
            delayus(150);
        }
    }
}

void sensor_w_sck(uint8_t sensor_data)
{    
    mSENSOR_SCK_OUT;
    mSENSOR_SDIO_H;
    for(uint8_t i=0; i<8; i++)
    {
        mSENSOR_SCK_L;
        mSENSOR_SDIO_OUT;
        if(sensor_data&(1<<7))
            mSENSOR_SDIO_H;
        else
            mSENSOR_SDIO_L;
        __NOP();__NOP();
        mSENSOR_SCK_H;
        sensor_data<<=1;
        __NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();
    }
    mSENSOR_SDIO_IN;
}

void drv_senscan_write(uint8_t sensor_addr, uint8_t  sensor_data)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_SENSCAN, 0U);
    OM_CRITICAL_BEGIN();
    sensor_w_sck(sensor_addr|0x80);
    delayus(5);
    sensor_w_sck(sensor_data);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_SENSCAN, 1U);
    OM_CRITICAL_END();
}

uint8_t drv_senscan_read(uint8_t sensor_addr)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_SENSCAN, 1U);
    OM_SENSCAN->CFG_ADDR = sensor_addr;
    OM_SENSCAN->CFG_CSR = (OM_SENSCAN->CFG_CSR | (SENSACN_CFG_CSR_EN_MASK + SENSACN_CFG_CSR_START_MASK)) & ~SENSACN_CFG_CSR_DIR_MASK;
    while(OM_SENSCAN->CFG_CSR & SENSACN_CFG_CSR_START_MASK);

    return OM_SENSCAN->CFG_DATA;
}

void drv_senscan_mode_select(OM_SENSCAN_Type *om_senscan, senscan_mode_t mode)
{
    switch (mode) {
        case SENSCAN_MODE_SCAN:
            om_senscan->CFG_CSR &= ~SENSACN_CFG_CSR_EN_MASK;
            break;
        case SENSCAN_MODE_CONFIG:
            om_senscan->CSR |= SENSACN_CSR_SCAN_STOP_MASK;
            while(om_senscan->CSR & SENSACN_CSR_SCAN_STOP_MASK);
            om_senscan->CFG_CSR |= SENSACN_CFG_CSR_EN_MASK;
            break;
        default:
            break;
    }
}

void drv_senscan_2wire_resync(void)
{
    drv_senscan_mode_select(OM_SENSCAN, SENSCAN_MODE_CONFIG);
    OM_SENSCAN->CFG_CSR |= SENSACN_CFG_CSR_2_WIRE_RESYNC_START_MASK;
    while(!(OM_SENSCAN->ISR & SENSACN_ISR_2_WIRE_RESYNC_DONE_MASK));
    OM_SENSCAN->ISR |= SENSACN_ISR_2_WIRE_RESYNC_DONE_MASK;
}

void *drv_senscan_control(OM_SENSCAN_Type *om_senscan, senscan_control_t control, void *argu)
{
    switch (control) {
        case SENSCAN_CONTROL_RESET:
            if ((uint32_t)om_senscan == (uint32_t)OM_SENSCAN) {
                DRV_RCC_RESET(RCC_RST_SENSCAN);
                break;
            }
            break;
        case SENSCAN_CONTROL_CLK_DISABLE:
            if ((uint32_t)om_senscan == (uint32_t)OM_SENSCAN) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_SENSCAN, 0U);
                break;
            }
            break;
        case SENSCAN_CONTROL_CLK_ENABLE:
            if ((uint32_t)om_senscan == (uint32_t)OM_SENSCAN) {
                DRV_RCC_CLOCK_ENABLE(RCC_CLK_SENSCAN, 1U);
                break;
            }
            break;
        case SENSCAN_CONTROL_SET_SCAN_FREQ:
            om_senscan->SCAN_FREQ = (uint32_t)argu;
            break;
        case SENSCAN_CONTROL_CLEAR_DELTAXY_DATA:
            om_senscan->CSR |= SENSACN_CSR_DELTA_CLR_MASK;
            break;
        case SENSCAN_CONTROL_WAKEUP_EN:
            om_senscan->CSR |= SENSACN_CSR_WAKE_EN_MASK;
            break;
        case SENSCAN_CONTROL_WAKEUP_DISABLE:
            om_senscan->CSR &= ~SENSACN_CSR_WAKE_EN_MASK;
            break;
        case SENSCAN_CONTROL_SCAN_EN:
            om_senscan->CSR |= SENSACN_CSR_SCAN_EN_MASK;
            break;
        case SENSCAN_CONTROL_SCAN_MODE_SEL:
            if((uint32_t)argu == SENSCAN_SCAN_MODE_SINGLE) {
                om_senscan->CSR &= ~SENSACN_CSR_SCAN_MODE_MASK;
            } else {
                om_senscan->CSR |= SENSACN_CSR_SCAN_MODE_MASK;
            }                
            break;
        default:
            break;
    }

    return (void *)OM_ERROR_OK;
}

#endif  /* (RTE_SENSCAN) */

/** @} */
