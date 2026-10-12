/**     __  ___     _              ____
 *   ___\ \/ / |__ | | ___  __   _|___ \
 *  / _ \\  /| '_ \| |/ _ \ \ \ / / __) |
 * |  __//  \| |_) | |  __/  \ V / / __/
 *  \___/_/\_\_.__/|_|\___|   \_/ |_____|
 *
 * @file ex2_hal_om62xx.c
 * @brief exBLE v2 port layer for om62xx + non-os.
 * @author onmicro
 * @date 2021/11
 */

#include <string.h>
#include "om_driver.h"
#include "evt.h"
#include "ex2_hal.h"
#include "mouse.h"
#include "main.h"

/* 中断优先级不能高于RF_IRQn */
#define OM_GPIO_GPIO0_IRQ_PRIORITY 3
#define OM_RTC_IRQ_PRIORITY 3
#if !defined(OM_RF_BLE_IRQ_PRIORITY)
#define OM_RF_BLE_IRQ_PRIORITY 0
#endif

/**
 * @brief   Initialize platform real-timer.
 */
void rtc_init(void)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RTC, 1);
    if (!(OM_RTC->CR & RTC_CR_TIMER_EN_MASK)) {
        drv_rtc_init(OM_RTC);
    }
    if(iDEVICE_TYPE_24G == device_type)
    {
        /* enable the interrupt of alarm as rtimer. */
        drv_rtc_control(OM_RTC, RTC_CONTROL_ALARM0_INT_EN, NULL);
    }
}

void ex2_hal_init(void)
{
    /* RTC is BLE clock. */
    rtc_init();

    /* exBLE v1 is poll driven. */
    /* exBLE v2 is interrupt driven. */
    NVIC_SetPriority(RF_IRQn, OM_RF_BLE_IRQ_PRIORITY);
    NVIC_EnableIRQ(RF_IRQn);
    /* alarm2rf requires it. */
    NVIC_SetPriority(RTC_IRQn, OM_RTC_IRQ_PRIORITY);
    NVIC_EnableIRQ(RTC_IRQn);
    /* Save NVIC registers. */
    __enable_irq();
}

void ex2_hal_uninit(void)
{
    OM_CRITICAL_BEGIN();
    NVIC_ClearPendingIRQ(RF_IRQn);
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_DisableIRQ(RF_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RF, 0);
    drv_rtc_control(OM_RTC, RTC_CONTROL_DISABLE_TIME, NULL);
    OM_CRITICAL_END();
}


/** @} */
