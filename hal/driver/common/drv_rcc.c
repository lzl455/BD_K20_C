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
 * @file     drv_rcc.c
 * @brief    rcc driver
 * @date     16. Sep 2023
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
#if (RTE_RCC)
#include <stddef.h>
#include "drv_rcc.h"


/*******************************************************************************
 * CONST & VARIABLES
 */

uint32_t SystemCoreClock;

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
void drv_rcc_init(void)
{
#if (16000000UL == SYS_CLK)
    /* set sys clock divider */
    OM_RCC->CLKCTRL = RCC_DIV_CLK_SEL_1;
    /* sysclk is coming from osc16m */
    OM_RCC->SYSCLK_SEL = RCC_SYS_CLK_SEL_OSC16M;
    SystemCoreClock = 16000000UL / (1u << OM_RCC->CLKCTRL);
     drv_pmu_syspll_ctrl(PMU_PLL_CTRL_STOP);
#else
    /* set sys clock divider */
    OM_RCC->CLKCTRL = RCC_DIV_CLK_SEL_1;
    /* start syspll */
    drv_pmu_syspll_ctrl(PMU_PLL_CTRL_START);
    OM_RCC->SYSCLK_SEL = RCC_SYS_CLK_SEL_PLL48M;
    SystemCoreClock = 48000000UL / (1u << OM_RCC->CLKCTRL);
#endif

    #if (CONFIG_OM6229)
    /* set opt clock divider */
    OM_RCC->OTP_CLKCTRL = rcc_config->div_clk_otp;
    #endif
    /* Set divder parameter of sflash controller */
    register_set(&(OM_RCC->FLASH_CLKCTRL), RCC_FLASH_CLKCTRL_CLKDIV_MASK, 0);
}

uint32_t drv_rcc_clock_get(rcc_clk_t _dev_type)
{
    uint32_t rtn_clk = 0;

    switch (_dev_type) {
        case RCC_CLK_RF:
        case RCC_CLK_TIMER0:
        case RCC_CLK_UART0:
        case RCC_CLK_GPIO0:
        case RCC_CLK_SWD:
        case RCC_CLK_AES128:
        case RCC_CLK_ANA:
        case RCC_CLK_PWM:
            rtn_clk = SYS_CLK;
            break;
        case RCC_CLK_WDT:
            if (drv_pmu_power_get(PMU_POWER_ID_RTC32K)) {
                rtn_clk = 32000UL;
            } else {
                rtn_clk = 0UL;
            }
            break;
        #if (CONFIG_OM6229)
        case RCC_CLK_OTP:
            rtn_clk = SYS_CLK / OM_RCC->OTP_CLKCTRL;
            break;
        case RCC_CLK_RTC:
            rtn_clk = 32000UL;
            break;
        #endif
        #if (CONFIG_OM6239)
        case RCC_CLK_ENCODER:
        case RCC_CLK_SENSCAN:
            if (drv_pmu_power_get(PMU_POWER_ID_RTC2M)) {
                rtn_clk = 2000000UL;
            } else {
                rtn_clk = 0UL;
            }
            break;
        case RCC_CLK_LEDC:
            rtn_clk = 48000000UL;
            break;
        case RCC_CLK_RTC:
            if (OM_PMU->CLK32K_SEL & PMU_CLK32K_SEL_RTC2M_EN_MASK) {
                if (drv_pmu_power_get(PMU_POWER_ID_RTC2M)) {
                    rtn_clk = 2000000UL;
                } else {
                    rtn_clk = 0UL;
                }
            } else {
                if (drv_pmu_power_get(PMU_POWER_ID_RTC32K)) {
                    rtn_clk = 32000UL;
                } else {
                    rtn_clk = 0UL;
                }
            }
            break;
        #endif
        case RCC_CLK_FLASH:
            rtn_clk = SYS_CLK / (OM_RCC->FLASH_CLKCTRL & RCC_FLASH_CLKCTRL_CLKDIV_MASK);
            break;
        default : break;
    }

    return rtn_clk;
}

#endif  /* (RTE_RCC) */

/** @} */
