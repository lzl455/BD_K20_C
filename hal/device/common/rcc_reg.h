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
 * @file     rcc_reg.h
 * @brief    RCC Register define
 * @date     16. Sep 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    RCC_Registers for OnMicro OM62xx
 * @details  RCC Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __RCC_REG_H
#define __RCC_REG_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include "../common/common_reg.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
    __IO uint32_t CLKCTRL;
    __IO uint32_t CLKGATE;
    __IO uint32_t RSTCTRL;
    __IO uint32_t M0CALIB;
    __IO uint32_t SYSCLK_SEL;
    #if (CONFIG_OM6229)
    __IO uint32_t OTP_CLKCTRL;
    #endif
    #if (CONFIG_OM6239)
    __IO uint32_t rsv_x14;
    #endif
    __IO uint32_t FLASH_CLKCTRL; //SF->CONFIGURATION_0
    __IO uint32_t FLASH_READ_OPCODE; //SF->READ_OPCODE_REG
    __IO uint32_t FLASH_OFFSET;
    __IO uint32_t USB_CTRL;
    __IO uint32_t USB_WK_INT_CLR;
    __IO uint32_t USB_WK_SIG_SEL;
    __IO uint32_t USB_WK_CLK_SEL;
} OM_RCC_Type;


/*******************************************************************************
 * MACROS
 */
/* CLKCTRL register */
#define RCC_CLK_CTRL_SYS_CLK_DIV_POS                (0U)
#define RCC_CLK_CTRL_SYS_CLK_DIV_0_MASK             (0x00U << RCC_CLK_CTRL_SYS_CLK_DIV_POS)
#define RCC_CLK_CTRL_SYS_CLK_DIV_1_MASK             (0x01U << RCC_CLK_CTRL_SYS_CLK_DIV_POS)

/* CLKGATE register */
#if (CONFIG_OM6239)
#define RCC_DEV_CLK_GATE_LEDC_CLK_GATE_POS          (0U)
#define RCC_DEV_CLK_GATE_LEDC_CLK_GATE_MASK         (0x01U << RCC_DEV_CLK_GATE_LEDC_CLK_GATE_POS)
#else
#define RCC_DEV_CLK_GATE_OTP_CLK_GATE_POS           (0U)
#define RCC_DEV_CLK_GATE_OTP_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_OTP_CLK_GATE_POS)
#endif
#define RCC_DEV_CLK_GATE_FLASH_CLK_GATE_POS         (1U)
#define RCC_DEV_CLK_GATE_FLASH_CLK_GATE_MASK        (0x01U << RCC_DEV_CLK_GATE_FLASH_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_RF_CLK_GATE_POS            (2U)
#define RCC_DEV_CLK_GATE_RF_CLK_GATE_MASK           (0x01U << RCC_DEV_CLK_GATE_RF_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_USB_CLK_GATE_POS           (3U)
#define RCC_DEV_CLK_GATE_USB_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_USB_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_TIMER_CLK_GATE_POS         (4U)
#define RCC_DEV_CLK_GATE_TIMER_CLK_GATE_MASK        (0x01U << RCC_DEV_CLK_GATE_TIMER_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_UART_CLK_GATE_POS          (5U)
#define RCC_DEV_CLK_GATE_UART_CLK_GATE_MASK         (0x01U << RCC_DEV_CLK_GATE_UART_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_GPIO_CLK_GATE_POS          (6U)
#define RCC_DEV_CLK_GATE_GPIO_CLK_GATE_MASK         (0x01U << RCC_DEV_CLK_GATE_GPIO_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_SWD_CLK_GATE_POS           (7U)
#define RCC_DEV_CLK_GATE_SWD_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_SWD_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_AES_CLK_GATE_POS           (8U)
#define RCC_DEV_CLK_GATE_AES_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_AES_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_ANA_CLK_GATE_POS           (9U)
#define RCC_DEV_CLK_GATE_ANA_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_ANA_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_RTC_CLK_GATE_POS           (10U)
#define RCC_DEV_CLK_GATE_RTC_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_RTC_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_WDT_CLK_GATE_POS           (11U)
#define RCC_DEV_CLK_GATE_WDT_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_WDT_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_PWM_CLK_GATE_POS           (12U)
#define RCC_DEV_CLK_GATE_PWM_CLK_GATE_MASK          (0x01U << RCC_DEV_CLK_GATE_PWM_CLK_GATE_POS)
#if (CONFIG_OM6239)
#define RCC_DEV_CLK_GATE_ENCODER_CLK_GATE_POS       (13U)
#define RCC_DEV_CLK_GATE_ENCODER_CLK_GATE_MASK      (0x01U << RCC_DEV_CLK_GATE_ENCODER_CLK_GATE_POS)
#define RCC_DEV_CLK_GATE_SENSOR_CLK_GATE_POS        (14U)
#define RCC_DEV_CLK_GATE_SENSOR_CLK_GATE_MASK       (0x01U << RCC_DEV_CLK_GATE_SENSOR_CLK_GATE_POS)
#endif

/* RSTCTRL register */
#define RCC_DEV_RST_CTRL_RESET_POS                   (0U)
#define RCC_DEV_RST_CTRL_POWERON_RESET_MASK          (0x00U << RCC_DEV_RST_CTRL_RESET_POS)
#define RCC_DEV_RST_CTRL_WATCHDOG_RESET_MASK         (0x01U << RCC_DEV_RST_CTRL_RESET_POS)
#define RCC_DEV_RST_CTRL_SOFT_RESET_MASK             (0x02U << RCC_DEV_RST_CTRL_RESET_POS)
#define RCC_DEV_RST_CTRL_DEEPSLEEP_RESET_MASK        (0x03U << RCC_DEV_RST_CTRL_RESET_POS)
#define RCC_DEV_RST_CTRL_STANDBY_RESET_MASK          (0x04U << RCC_DEV_RST_CTRL_RESET_POS)
#define RCC_DEV_RST_CTRL_RF_FSM_RESET_POS            (4U)
#define RCC_DEV_RST_CTRL_RF_FSM_RESET_MASK           (0x01U << RCC_DEV_RST_CTRL_RF_FSM_RESET_POS)
#define RCC_DEV_RST_CTRL_RF_RESET_POS                (5U)
#define RCC_DEV_RST_CTRL_RF_RESET_MASK               (0x01U << RCC_DEV_RST_CTRL_RF_RESET_POS)
#define RCC_DEV_RST_CTRL_USB_RESET_POS               (6U)
#define RCC_DEV_RST_CTRL_USB_RESET_MASK              (0x01U << RCC_DEV_RST_CTRL_USB_RESET_POS)
#define RCC_DEV_RST_CTRL_FLASH_RESET_POS             (6U)
#define RCC_DEV_RST_CTRL_FLASH_RESET_MASK            (0x01U << RCC_DEV_RST_CTRL_FLASH_RESET_POS)
#define RCC_DEV_RST_CTRL_TIMER_RESET_POS             (8U)
#define RCC_DEV_RST_CTRL_TIMER_RESET_MASK            (0x01U << RCC_DEV_RST_CTRL_TIMER_RESET_POS)
#if (CONFIG_OM6239)
#define RCC_DEV_RST_CTRL_GPIO_RESET_POS              (9U)
#define RCC_DEV_RST_CTRL_GPIO_RESET_MASK             (0x01U << RCC_DEV_RST_CTRL_GPIO_RESET_POS)
#endif
#define RCC_DEV_RST_CTRL_AES_RESET_POS               (10U)
#define RCC_DEV_RST_CTRL_AES_RESET_MASK              (0x01U << RCC_DEV_RST_CTRL_AES_RESET_POS)
#define RCC_DEV_RST_CTRL_OSC_RESET_POS               (11U)
#define RCC_DEV_RST_CTRL_OSC_RESET_MASK              (0x01U << RCC_DEV_RST_CTRL_OSC_RESET_POS)
#define RCC_DEV_RST_CTRL_UART_RESET_POS              (12U)
#define RCC_DEV_RST_CTRL_UART_RESET_MASK             (0x01U << RCC_DEV_RST_CTRL_UART_RESET_POS)
#define RCC_DEV_RST_CTRL_PWM_RESET_POS               (13U)
#define RCC_DEV_RST_CTRL_PWM_RESET_MASK              (0x01U << RCC_DEV_RST_CTRL_PWM_RESET_POS)
#if (CONFIG_OM6239)
#define RCC_DEV_RST_CTRL_LEDC_RESET_POS              (14U)
#define RCC_DEV_RST_CTRL_LEDC_RESET_MASK             (0x01U << RCC_DEV_RST_CTRL_LEDC_RESET_POS)
#define RCC_DEV_RST_CTRL_ENCODER_RESET_POS           (15U)
#define RCC_DEV_RST_CTRL_ENCODER_RESET_MASK          (0x01U << RCC_DEV_RST_CTRL_ENCODER_RESET_POS)
#define RCC_DEV_RST_CTRL_SENSCAN_RESET_POS           (16U)
#define RCC_DEV_RST_CTRL_SENSCAN_RESET_MASK          (0x01U << RCC_DEV_RST_CTRL_SENSCAN_RESET_POS)
#endif

/* M0CALIB register */
#define RCC_CORTEX_M0_STCALIB_POS                    (24U)
#define RCC_CORTEX_M0_STCALIB_OSC16M_MASK            (0x01U << RCC_CORTEX_M0_STCALIB_POS)

/* SYSCLK_SEL register */
#define RCC_SYS_CLK_SEL_POS                          (0U)
#define RCC_SYS_CLK_SEL_OSC16M_MASK                  (0x00U << RCC_SYS_CLK_SEL_POS)
#define RCC_SYS_CLK_SEL_PLL48M_MASK                  (0x01U << RCC_SYS_CLK_SEL_POS)

/* FLASH_CLKCTRL register */
#define RCC_FLASH_CLKCTRL_CLKDIV_POS                   (0U)
#define RCC_FLASH_CLKCTRL_CLKDIV_MASK                  (0xFFU << RCC_FLASH_CLKCTRL_CLKDIV_POS)
#define RCC_FLASH_CLKCTRL_DLY_SAMPLE_POS               (8U)
#define RCC_FLASH_CLKCTRL_DLY_SAMPLE_MASK              (0x03U << RCC_FLASH_CLKCTRL_CLKDIV_POS)
#define RCC_FLASH_CLKCTRL_FALL_EDGE_DLY_SAMPLE_POS     (10U)
#define RCC_FLASH_CLKCTRL_FALL_EDGE_DLY_SAMPLE_MASK    (0x01U << RCC_FLASH_CLKCTRL_CLKDIV_POS)

/* FLASH_READ_OPCODE register */
#define RCC_FLASH_READ_OPCDE_POS                        (16U)
#define RCC_FLASH_READ_OPCDE_VECTKEY                    (0x6666U << RCC_FLASH_READ_OPCDE_POS)

#ifdef __cplusplus
}
#endif


#endif  /* __RCC_REG_H */


/** @} */
