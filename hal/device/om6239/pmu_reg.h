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
 * @file     pmu_reg.h
 * @brief    PMU Register define
 * @date     05 Aug 2023
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    PWM_Registers for OnMicro OM6239
 * @details  PMU Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __PMU_REG_H
#define __PMU_REG_H


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
    __IO uint32_t BOOT_MODE;                 //0x00
    __IO uint32_t CLK32K_SEL;                //0x04
    __IO uint32_t CLKLP_CTRL;                //0x08
    __IO uint32_t ANA_CTRL;                  //0x0c
    __IO uint32_t LPMS;                      //0x10
    __IO uint32_t WKINT_CLR;                 //0x14
    __IO uint32_t PLL_CTRL;                  //0x18
    __IO uint32_t PLL_CTRL1;                 //0x1c
    __IO uint32_t rsv_x20;                   //0x20
    __IO uint32_t DELAY_CTRL;                //0x24
    __IO uint32_t PINMUX_SEL;                //0x28
    __IO uint32_t RF_DEBUG;                  //0x2c
    __IO uint32_t FLASH_PWR_CMD;             //0x30
    __IO uint32_t rsv_x34_x3c[3];            //0x34-0x3C
    __IO uint32_t PAD_WK_CTRL;               //0x40
    __IO uint32_t PAD_WK_CTRL_1;             //0x44
    __IO uint32_t PAD_BUF_EN;                //0x48
    __IO uint32_t PAD_PD_CTRL;               //0x4c
    __IO uint32_t PAD_PU_CTRL;               //0x50
    __IO uint32_t PAD_PU_CTRL_1;             //0x54
    __IO uint32_t PAD_DRV_CTRL;              //0x58
    __IO uint32_t PAD_DRV_CTRL_1;            //0x5c
    __IO uint32_t rsv_x60_x68[3];               //0x60-0x68
    union {
        __IO uint32_t SW_RSVD0;              //0x6c
        __IO uint32_t CPU_CONTEXT_ADDR;
    };
    __IO uint32_t SW_RSVD1;                  //0x70     // 状态信息
    __IO uint32_t SW_RSVD2;                  //0x74     // 2.4G同步字
    __IO uint32_t SW_RSVD3;                  //0x78
    __IO uint32_t SW_RSVD4;                  //0x7c
    __IO uint32_t SW_RSVD5;                  //0x80
    __IO uint32_t SW_RSVD6;                  //0x84
    __IO uint32_t SW_RSVD7;                  //0x88     // boot识别
} OM_PMU_Type;


/*******************************************************************************
 * MACROS
 */
/* PMU BOOT_MODE register */
#define PMU_BOOT_MODE_BOOT_MODE_POS             0
#define PMU_BOOT_MODE_BOOT_FROM_FLASH_MASK      0U
#define PMU_BOOT_MODE_BOOT_FROM_SRAM_MASK       1U

/* PMU CLK32K_SEL register */
#define PMU_CLK32K_SEL_RTC2M_EN_POS             0
#define PMU_CLK32K_SEL_RTC2M_EN_MASK           (0x1u << PMU_CLK32K_SEL_RTC2M_EN_POS)
#define PMU_CLK32K_SEL_RTC32K_RDY_POS           16
#define PMU_CLK32K_SEL_RTC32K_RDY_MASK         (0x1u << PMU_CLK32K_SEL_RTC32K_RDY_POS)

/* PMU CLKLP_CTRL register */
#define PMU_CLKLP_CTRL_RTC32K_EN_POS            2
#define PMU_CLKLP_CTRL_RTC32K_EN_MASK          (0x1u << PMU_CLKLP_CTRL_RTC32K_EN_POS)
#define PMU_CLKLP_CTRL_RTC2M_EN_POS             4
#define PMU_CLKLP_CTRL_RTC2M_EN_MASK           (0x1u << PMU_CLKLP_CTRL_RTC2M_EN_POS)

/* PMU LPMS register */
#define PMU_LPMS_LOW_PWR_MODE_EN_POS            0
#define PMU_LPMS_LOW_PWR_MODE_EN_MASK          (0x7U << PMU_LPMS_LOW_PWR_MODE_EN_POS)
#define PMU_LPMS_LOW_PWR_MODE_EN_STANDBY_MASK  (0x3U << PMU_LPMS_LOW_PWR_MODE_EN_POS)
#define PMU_LPMS_KEEP_SRAM_EN_POS               3 //obsoleted, since RAM in retention domain
#define PMU_LPMS_KEEP_SRAM_EN_MASK             (0x1U << PMU_LPMS_KEEP_SRAM_EN_POS)
#define PMU_LPMS_PLL_CTRL_EN_POS                4 //obsoleted, since hw auto resumes PLL
#define PMU_LPMS_PLL_CTRL_EN_MASK              (0x1U << PMU_LPMS_PLL_CTRL_EN_POS)
#define PMU_LPMS_SF_PWR_CTRL_EN_POS             5
#define PMU_LPMS_SF_PWR_CTRL_EN_MASK           (0x1U << PMU_LPMS_SF_PWR_CTRL_EN_POS)

/* PMU WKINT_CLR register */
#define PMU_WKINT_CLR_WK_INT_CLR_POS            0
#define PMU_WKINT_CLR_WK_INT_CLR_MASK          (0x1U << PMU_WKINT_CLR_WK_INT_CLR_POS)
#define PMU_WKINT_CLR_WK_SRC_POS                1
#define PMU_WKINT_CLR_PIN_WK_MASK              (0x1u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_RTC_WK_MASK              (0x2u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_RTC_TICK_WK_MASK         (0x4u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_RTC_ALARM_WK_MASK        (0x8u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_RTC_ALARM1_WK_MASK       (0x10u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_WDT_WK_MASK              (0x20u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_VBUS_DET_WK_MASK         (0x40u << PMU_WKINT_CLR_WK_SRC_POS)
#define PMU_WKINT_CLR_ANY_WK_MASK              (0x7Fu << PMU_WKINT_CLR_WK_SRC_POS)

/* PMU PLL_CTRL register */
#define PMU_PLL_CTRL_PLL_EN_POS                 0
#define PMU_PLL_CTRL_PLL_EN_MASK               (0x1U << PMU_PLL_CTRL_PLL_EN_POS)
#define PMU_PLL_CTRL_PLL_RDY_POS                1
#define PMU_PLL_CTRL_PLL_RDY_MASK              (0x1U << PMU_PLL_CTRL_PLL_RDY_POS)

/* PMU PLL_CTRL1 register */
#define PMU_PLL_CTRL1_PLL_PD_PLL_48M_REG_POS    0
#define PMU_PLL_CTRL1_PLL_PD_PLL_48M_REG_MASK  (0x1U << PMU_PLL_CTRL1_PLL_PD_PLL_48M_REG_POS)
#define PMU_PLL_CTRL1_PLL_PD_PLL_48M_MN_POS     1
#define PMU_PLL_CTRL1_PLL_PD_PLL_48M_MN_MASK   (0x1U << PMU_PLL_CTRL1_PLL_PD_PLL_48M_MN_POS)
#define PMU_PLL_CTRL1_PLL_PLL_48M_ICP_POS       2
#define PMU_PLL_CTRL1_PLL_PLL_48M_ICP_MASK     (0x7U << PMU_PLL_CTRL1_PLL_PLL_48M_ICP_POS)
#define PMU_PLL_CTRL1_PLL_PLL_48M_RSTN_POS      5
#define PMU_PLL_CTRL1_PLL_PLL_48M_RSTN_MASK    (0x7U << PMU_PLL_CTRL1_PLL_PLL_48M_RSTN_POS)

/* PMU PAD_PD_CTRL register */
#define PAD_PD_CTRL_PADn_POS(n)                 (n)
#define PAD_PD_CTRL_PADn_PULL_DOWN(n)           (1u << PAD_PD_CTRL_PADn_POS(n))

/* PMU PAD_PU_CTRL register */
#define PAD_PU_CTRL_PADn_POS(n)                 ((n) * 2)
#define PAD_PU_CTRL_PADn_PULL_UP_30K(n)         (2u << PAD_PU_CTRL_PADn_POS(n))
#define PAD_PU_CTRL_PADn_PULL_UP_150K(n)        (1u << PAD_PU_CTRL_PADn_POS(n))
/* only pin 4/5/6/7 pull up resistance is 2M when PU_CTRL set to 01b */
#define PAD_PU_CTRL_PADn_PULL_UP_2M(n)          (1u << PAD_PU_CTRL_PADn_POS(n))
#define PAD_PU_CTRL_PADn_PULL_UP_MASK(n)        (3u << PAD_PU_CTRL_PADn_POS(n))

/* PMU PAD_WK_CTRL register */
#define PAD_WK_CTRL_PADn_POS(n)                 (n)
#define PAD_WK_CTRL_PADn_WKUP_EN(n)             (1u << ((n) * 2 + 1))
#define PAD_WK_CTRL_PADn_WKUP_FALL_EN(n)        (1u << ((n) * 2))

/* PMU PAD_DRV_CTRL register */
#define PAD_DRV_CTRL_PADn_SPEED_POS(n)          ((n) * 2)
#define PAD_DRV_CTRL_PADn_SPEED_LEVEL_0(n)      (0u << PAD_DRV_CTRL_PADn_SPEED_POS(n))
#define PAD_DRV_CTRL_PADn_SPEED_LEVEL_1(n)      (1u << PAD_DRV_CTRL_PADn_SPEED_POS(n))
#define PAD_DRV_CTRL_PADn_SPEED_LEVEL_2(n)      (2u << PAD_DRV_CTRL_PADn_SPEED_POS(n))
#define PAD_DRV_CTRL_PADn_SPEED_LEVEL_3(n)      (3u << PAD_DRV_CTRL_PADn_SPEED_POS(n))

/* PMU SW_RSVD register */
#define PMU_SW_RSVD_RF_MDOE_POS                  0U
#define PMU_SW_RSVD_RF_MDOE_MASK                (0x0FU << 0)

/* PMU PINMUX_SEL register */
#define PMU_PINMUX_SEL_UART_SEL_POS                 0
#define PMU_PINMUX_SEL_UART_SEL_MASK               (0x3u << PMU_PINMUX_SEL_UART_SEL_POS)
#define PMU_PINMUX_SEL_LEDC_SEL_POS                 4
#define PMU_PINMUX_SEL_LEDC_SEL_MASK               (0x3u << PMU_PINMUX_SEL_LEDC_SEL_POS)

#define PMU_SW_RSVD1_RF_MDOE_MASK                0x00000007
//{
//    #define RSVD1_MDOE_BLE                      iDEVICE_TYPE_BLE
//    #define RSVD1_MDOE_BT0                      iDEVICE_TYPE_BT0
//    #define RSVD1_MDOE_BT1                      iDEVICE_TYPE_BT1
//    #define RSVD1_MDOE_BT2                      iDEVICE_TYPE_BT2
//    #define RSVD1_MDOE_24G                      iDEVICE_TYPE_24G
//    #define RSVD1_MDOE_USB                      iDEVICE_TYPE_IDLE

    #define RSVD1_RF_CONN_EN                     (1<<3)
//}
#define PMU_SW_RSVD1_DPI_MASK                    0x00000070

#define PMU_SW_RSVD1_SENSOR_MASK                 0x0000FF00
#define PMU_SW_RSVD1_DPI_BASE_MASK               0x00FF0000
#define PMU_SW_RSVD1_SENSOR_INFO_MASK            0x0F000000
#define PMU_SW_RSVD1_RESET                       0x10000000
#define PMU_SW_RSVD1_POWER_OFF                   0x20000000


#ifdef __cplusplus
}
#endif


#endif  /* __PMU_REG_H */


/** @} */
