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
 * @file     drv_pmu.c
 * @brief    pmu driver
 * @date     22. Sep 2023
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
#if (RTE_PMU)
#include "om_driver.h"
#include "main.h"

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
void drv_pmu_init(void)
{
    // TODO
}

void drv_pmu_syspll_ctrl(pmu_pll_ctrl_t syspll_ctrl)
{
    switch (syspll_ctrl) {
        case PMU_PLL_CTRL_START:
            OM_PMU->PLL_CTRL = PMU_PLL_CTRL_PLL_EN_MASK;
            while (!(OM_PMU->PLL_CTRL & PMU_PLL_CTRL_PLL_RDY_MASK));
            OM_PMU->LPMS |= PMU_LPMS_PLL_CTRL_EN_MASK;
            break;
        case PMU_PLL_CTRL_STOP:
            OM_PMU->LPMS &= ~PMU_LPMS_PLL_CTRL_EN_MASK;
            OM_PMU->PLL_CTRL = 0;
            break;
        case PMU_PLL_CTRL_RESET:
            /* pll_48m_rstn=0->1 */
            OM_PMU->PLL_CTRL1 &= ~PMU_PLL_CTRL1_PLL_PLL_48M_RSTN_MASK;
            OM_PMU->PLL_CTRL1 |= PMU_PLL_CTRL1_PLL_PLL_48M_RSTN_MASK;
            break;
        default:
            OM_ASSERT(0U);
            break;
    }
}

void drv_pmu_power_set(pmu_power_id_t power_id, pmu_power_t power)
{
    switch (power_id) {
        case PMU_POWER_ID_RTC32K:
            if (power == PMU_POWER_ON) {
                OM_PMU->CLKLP_CTRL |= PMU_CLKLP_CTRL_RTC32K_EN_MASK;
            } else {
                OM_PMU->CLKLP_CTRL &= ~PMU_CLKLP_CTRL_RTC32K_EN_MASK;
            }
            break;
        case PMU_POWER_ID_RTC2M:
            if (power == PMU_POWER_ON) {
                OM_PMU->CLKLP_CTRL |= PMU_CLKLP_CTRL_RTC2M_EN_MASK;
            } else {
                OM_PMU->CLKLP_CTRL &= ~PMU_CLKLP_CTRL_RTC2M_EN_MASK;
            }
            break;
        default:
            break;
    }
}

pmu_power_t drv_pmu_power_get(pmu_power_id_t power_id)
{
    switch (power_id) {
        case PMU_POWER_ID_RTC32K:
            return (OM_PMU->CLKLP_CTRL & PMU_CLKLP_CTRL_RTC32K_EN_MASK) ? PMU_POWER_ON : PMU_POWER_DOWN;
        case PMU_POWER_ID_RTC2M:
            return (OM_PMU->CLKLP_CTRL & PMU_CLKLP_CTRL_RTC2M_EN_MASK) ? PMU_POWER_ON : PMU_POWER_DOWN;
        default:
            return PMU_POWER_UNKNOWN;
    }
}

om_error_t drv_pmu_power_mode_select(pmu_dev_id_t dev_id, pmu_power_mode_t power_mode)
{
    om_error_t error = OM_ERROR_OK;

    switch (dev_id) {
        case PMU_DEV_ID_FLASH_POWER:
            if (power_mode == PMU_POWER_MODE_KEEP) {
                /* HW will keep power switch on, and enter/exit sflash's deep sleep with SPI command 0xB9/0xAB. */
                OM_PMU->LPMS |= PMU_LPMS_SF_PWR_CTRL_EN_MASK;
                OM_PMU->FLASH_PWR_CMD = 0xABB9;
            } else {
                /* HW will automatically turn off/on power switch to flash when enter/exit low power mode. */
                OM_PMU->LPMS &= ~PMU_LPMS_SF_PWR_CTRL_EN_MASK;
            }
            break;
        default:
            OM_ASSERT(0U);
            break;
    }

    return error;
}

extern void delayus(unsigned int time);

__RAM_CODE void drv_pmu_set_low_power_mode(pmu_lpm_t lpm)
{
    uint32_t lpms;

    switch (lpm) {
        case PMU_LPM_IDLE:
            __WFI();
            break;
        case PMU_LPM_ACTIVE:
            break;
        default:
            do {
                /*
                * If the SEVONPEND (Send-Event-On-Pend) feature is enabed,
                * a new pending interrupt (even if disabled) will be an event.
                */
                SCB->SCR = SCB_SCR_SEVONPEND_Msk | SCB_SCR_SLEEPDEEP_Msk;
                lpms = OM_PMU->LPMS;
                OM_PMU->LPMS = (lpms & (~PMU_LPMS_LOW_PWR_MODE_EN_MASK)) | (uint32_t)lpm;
                if (lpm == PMU_LPM_DEEP_SLEEP) {
                    OM_PMU->PAD_PU_CTRL = 0x00AAAA00;
                    OM_PMU->PAD_PU_CTRL_1 = 0x08000005;
                    OM_PMU->PAD_PD_CTRL = 0x1000000C;
                    OM_PMU->PAD_BUF_EN &= ~(1<<MODE_PIN);

                    OM_GPIO0->DATAOUT  = 0xF800FFF3;
                    OM_GPIO0->OUTENSET = 0x07FC0003;
                    OM_GPIO0->OUTENCLR = ~0x07FC0003;
                    delayus(3000);

                    OM_RCC->CLKGATE = 0x0742;
                    __NOP();__NOP();__NOP();__NOP();
                    __WFI();
                    return;
                } else {
                    __WFI();
                    SCB->SCR = 0U;
                }
            } while(0);
            break;
    }
//OM_GPIO0->DATAOUT &= ~(1<<5);
}

bool drv_pmu_can_pop_cpu(void)
{
    uint8_t level = drv_pmu_get_low_power_mode();
    if (PMU_LPMS_LOW_PWR_MODE_EN_STANDBY_MASK == level) {
        return OM_PMU->WKINT_CLR & PMU_WKINT_CLR_ANY_WK_MASK ? true : false;
    }
    return false;
}

void drv_pmu_pin_mode_set(uint8_t pin_idx, pmu_pin_mode_t mode)
{
    uint32_t pad_up_ctrl;
    uint8_t pin_idx_mod_16 = pin_idx % 16;

    if (pin_idx < 16) {
        pad_up_ctrl = OM_PMU->PAD_PU_CTRL;
    } else if((pin_idx > 15) & (pin_idx < 32)) {
        pad_up_ctrl = OM_PMU->PAD_PU_CTRL_1;
    }

    switch (mode) {
        case PMU_PIN_MODE_FLOAT:
            pad_up_ctrl &= ~PAD_PU_CTRL_PADn_PULL_UP_MASK(pin_idx_mod_16);
            OM_PMU->PAD_PD_CTRL &= ~PAD_PD_CTRL_PADn_PULL_DOWN(pin_idx);
            break;
        case PMU_PIN_MODE_PU:
            OM_PMU->PAD_PD_CTRL &= ~PAD_PD_CTRL_PADn_PULL_DOWN(pin_idx);
            pad_up_ctrl &= ~PAD_PU_CTRL_PADn_PULL_UP_MASK(pin_idx_mod_16);
            pad_up_ctrl |= PAD_PU_CTRL_PADn_PULL_UP_150K(pin_idx_mod_16);
            break;
        case PMU_PIN_MODE_PD:
            pad_up_ctrl &= ~PAD_PU_CTRL_PADn_PULL_UP_MASK(pin_idx_mod_16);
            OM_PMU->PAD_PD_CTRL |= PAD_PD_CTRL_PADn_PULL_DOWN(pin_idx);
            break;
        default:
            break;
    }

    if (pin_idx < 16) {
        OM_PMU->PAD_PU_CTRL = pad_up_ctrl;
    } else if((pin_idx > 15) & (pin_idx < 32)) {
        OM_PMU->PAD_PU_CTRL_1 = pad_up_ctrl;
    }

}

void drv_pmu_pin_driven_current_set(uint8_t pin_idx, pmu_pin_driver_current_t driven)
{
    if (pin_idx < 16) {
        OM_PMU->PAD_DRV_CTRL = (driven << PAD_DRV_CTRL_PADn_SPEED_POS(pin_idx)) |
                                    (OM_PMU->PAD_DRV_CTRL & ~PAD_DRV_CTRL_PADn_SPEED_LEVEL_3(pin_idx));
    } else {
        OM_PMU->PAD_DRV_CTRL_1 = (driven << PAD_DRV_CTRL_PADn_SPEED_POS(pin_idx - 16)) |
                                    (OM_PMU->PAD_DRV_CTRL_1 & ~PAD_DRV_CTRL_PADn_SPEED_LEVEL_3(pin_idx - 16));
    }
}

void drv_pmu_wakeup_pin_set(uint8_t pin_idx, pmu_pin_wakeup_type_t trigger_type)
{
    uint32_t pad_wk_ctrl;
    uint8_t pin_idx_mod_16 = pin_idx % 16;

    if (pin_idx < 16) {
        pad_wk_ctrl = OM_PMU->PAD_WK_CTRL;
    } else if((pin_idx > 15) & (pin_idx < 32)) {
        pad_wk_ctrl = OM_PMU->PAD_WK_CTRL_1;
    }

    switch (trigger_type) {
        case PMU_PIN_WAKEUP_TYPE_RISE:
            // rise edge wakeup enable
            pad_wk_ctrl |= PAD_WK_CTRL_PADn_WKUP_EN(pin_idx_mod_16);
            pad_wk_ctrl &= ~PAD_WK_CTRL_PADn_WKUP_FALL_EN(pin_idx_mod_16);
            break;
        case PMU_PIN_WAKEUP_TYPE_FALL:
            // fall edge wakeup enable
            pad_wk_ctrl |= PAD_WK_CTRL_PADn_WKUP_EN(pin_idx_mod_16);
            pad_wk_ctrl |= PAD_WK_CTRL_PADn_WKUP_FALL_EN(pin_idx_mod_16);

            break;
        case PMU_PIN_WAKEUP_TYPE_DISABLE:
            pad_wk_ctrl &= ~PAD_WK_CTRL_PADn_WKUP_EN(pin_idx_mod_16);
            break;
        default:
            break;
    }
    if (pin_idx < 16) {
        OM_PMU->PAD_WK_CTRL = pad_wk_ctrl;
    } else if((pin_idx > 15) & (pin_idx < 32)) {
        OM_PMU->PAD_WK_CTRL_1 = pad_wk_ctrl;
    }

}

void drv_pmu_rf_mode_set(uint8_t rf_mode)
{
    OM_PMU->SW_RSVD1 = (OM_PMU->SW_RSVD1 & (~PMU_SW_RSVD_RF_MDOE_MASK)) | rf_mode;
}

uint8_t drv_pmu_rf_mode_get(void)
{
    return (OM_PMU->SW_RSVD1 & PMU_SW_RSVD_RF_MDOE_MASK);
}


#endif  /* (RTE_PMU) */

/** @} */
