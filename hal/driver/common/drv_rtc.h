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
 * @file     drv_rtc.h
 * @brief    RTC Driver
 * @date     23. Sep 2023
 * @author   OnMicro SW Team
 *
 * @defgroup RTC RTC
 * @ingroup  HAL_Driver
 * @brief    RTC Driver.
 * @details  RTC Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_RTC_H
#define __DRV_RTC_H

/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_RTC)
#include "drv_cortex.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup rtc_ctrl_t DRV_RTC alarm type
 * @{
 */
typedef enum {
    RTC_ALARM_0    = 0U,     /**< ALARM0 */
    RTC_ALARM_1    = 1U,     /**< ALARM1 */
    RTC_ALARM_2    = 2U,     /**< ALARM2 */
} rtc_alarm_t;
/**
 * @}
 */

/**
 * @defgroup rtc_control_t DRV_RTC control type
 * @{
 */
typedef enum {
    RTC_CONTROL_WAIT_TIME_SYNCED    = 1U,     /**< Poll wait for HW sync between high/low frequency clock domains */
    RTC_CONTROL_TICK_INT_EN         = 2U,     /**< Enable systick interrupt of RTC module */
    RTC_CONTROL_ALARM0_INT_EN       = 3U,     /**< Enable alarm interrupt of RTC module */
    RTC_CONTROL_ALARM1_INT_EN       = 4U,     /**< Enable alarm1 (alarm2rf) interrupt of RTC module */
    RTC_CONTROL_SET_ALARM0          = 5U,     /**< Set the alarm value, and RTC module will raise alarm once reach it */
    RTC_CONTROL_SET_ALARM1          = 6U,     /**< Set the alarm1 value, and RTC module will raise alarm once reach it */
    RTC_CONTROL_SET_ALARM2          = 7U,     /**< Set the alarm2 value, and RTC module will raise alarm once reach it */
    RTC_CONTROL_IS_TICK             = 8U,     /**< Check whether the systick interrupt occurs */
    RTC_CONTROL_IS_ALARMED          = 9U,     /**< Check whether the alarm interrupt occurs */
    RTC_CONTROL_IS_ON               = 10U,    /**< Check RTC module whether is on */
    RTC_CONTROL_DISABLE_TIME        = 11U,    /**< Disable the time counter of RTC module */
    RTC_CONTROL_GET_ALARM0          = 12U,    /**< Get ALARM0 cnt */
    RTC_CONTROL_GET_ALARM1          = 13U,    /**< Get ALARM1 cnt */
    RTC_CONTROL_GET_ALARM2          = 14U,    /**< Get ALARM2 cnt */
    RTC_CONTROL_TICK_INT_DISABLE    = 15U,    /**< Disable systick interrupt of RTC module */
    RTC_CONTROL_ALARM1_RF_DISABLE   = 16U,    /**< Disable alarm1 for RF and as general alarm use */
    RTC_CONTROL_ALARM0_INT_DIS      = 17U,    /**< Disable alarm interrupt of RTC module */
} rtc_control_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Control RTC interface
 *
 * @param om_rtc         The RTC device address
 * @param control        The control operation type, see @ref rtc_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - RTC_CONTROL_WAIT_TIME_SYNCED      Poll wait for HW sync between high/low frequency clock domains
 *                       - RTC_CONTROL_TICK_INT_EN           Enable systick interrupt of RTC module
 *                       - RTC_CONTROL_ALARM0_INT_EN         Enable alarm interrupt of RTC module
 *                       - RTC_CONTROL_ALARM1_INT_EN         Enable alarm1 (alarm2rf) interrupt of RTC module
 *                       - RTC_CONTROL_SET_ALARM0            Set the alarm value, and RTC module will raise alarm once reach it
 *                       - RTC_CONTROL_SET_ALARM1            Set the alarm1 value, and RTC module will raise alarm once reach it
 *                       - RTC_CONTROL_SET_ALARM2            Set the alarm2 value, and RTC module will raise alarm once reach it
 *                       - RTC_CONTROL_IS_TICK               Check whether the systick interrupt occurs
 *                       - RTC_CONTROL_IS_ALARMED            Check whether the alarm interrupt occurs
 *                       - RTC_CONTROL_IS_ON                 Check RTC module whether is on
 *                       - RTC_CONTROL_DISABLE_TIME          Disable the time counter of RTC module
 *                       - RTC_CONTROL_ALARM0_INT_DIS        Disable alarm interrupt of RTC module
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
__STATIC_FORCEINLINE void *drv_rtc_control(OM_RTC_Type *om_rtc, rtc_control_t control, void *argu)
{
    uint32_t ret;

    ret = (uint32_t)OM_ERROR_OK;

    OM_CRITICAL_BEGIN();
    switch (control) {
        case RTC_CONTROL_WAIT_TIME_SYNCED:
            while (!om_rtc->CNT_VALID);
            break;
        case RTC_CONTROL_TICK_INT_EN:
            om_rtc->INTMASK |= RTC_INTMASK_TICK_INTRAW_STATUS_MASK;
            break;
        case RTC_CONTROL_ALARM0_INT_EN:
            om_rtc->INTMASK |= RTC_INTMASK_ALARM0_INTRAW_STATUS_MASK;
            break;
        case RTC_CONTROL_ALARM1_INT_EN:
            om_rtc->INTMASK |= RTC_INTMASK_ALARM1_INTRAW_STATUS_MASK;
            break;
        case RTC_CONTROL_SET_ALARM0:
            while (0 == (om_rtc->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
            om_rtc->ALARM0 = (uint32_t)argu;
            break;
        case RTC_CONTROL_SET_ALARM1:
            while (0 == (om_rtc->CR & RTC_CR_ALARM1_WRITE_STATUS_MASK));
            om_rtc->ALARM1 = (uint32_t)argu;
            break;
        case RTC_CONTROL_SET_ALARM2:
            while (0 == (om_rtc->CR & RTC_CR_ALARM2_WRITE_STATUS_MASK));
            om_rtc->ALARM2 = (uint32_t)argu;
            break;
        case RTC_CONTROL_IS_TICK:
            if (om_rtc->INTSTAT & RTC_INTSTAT_TICK_INT_STATUS_MASK) {
                om_rtc->INTRAWSTAT = RTC_INTRAWSTAT_TICK_INTRAW_STATUS_MASK;
                ret = 1U;
            } else {
                ret = 0U;
            }
            break;
        case RTC_CONTROL_IS_ALARMED:
            if (om_rtc->INTSTAT & RTC_INTSTAT_ALARM0_INT_STATUS_MASK) {
                om_rtc->INTRAWSTAT = RTC_INTRAWSTAT_ALARM0_INTRAW_STATUS_MASK;
                ret = 1U;
            } else {
                ret = 0U;
            }
            break;
        case RTC_CONTROL_IS_ON:
            ret = (om_rtc->CR & RTC_CR_TIMER_EN_MASK) ? 1U : 0U;
            break;
        case RTC_CONTROL_DISABLE_TIME:
            while (0 == (om_rtc->CR & RTC_CR_CR_WRITE_STATUS_MASK));
            om_rtc->CR = 0;
            om_rtc->INTMASK = 0;
            break;
        case RTC_CONTROL_GET_ALARM0:
            ret = om_rtc->ALARM0;
            break;
        case RTC_CONTROL_GET_ALARM1:
            ret = om_rtc->ALARM1;
            break;
        case RTC_CONTROL_GET_ALARM2:
            ret = om_rtc->ALARM2;
            break;
        case RTC_CONTROL_TICK_INT_DISABLE:
            om_rtc->INTMASK &= ~RTC_INTMASK_TICK_INTRAW_STATUS_MASK;
            break;
        case RTC_CONTROL_ALARM1_RF_DISABLE:
            om_rtc->WKRF_CR = 0;
            break;
        case RTC_CONTROL_ALARM0_INT_DIS:
            om_rtc->INTMASK &= ~RTC_INTMASK_ALARM0_INTRAW_STATUS_MASK;
            break;
        default:
            break;
    }
    OM_CRITICAL_END();

    return (void *)ret;
}

/**
 *******************************************************************************
 * @brief RTC initialization
 *
 * @param om_rtc Pointer to RTC
 *
 * @return status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_rtc_init(OM_RTC_Type *om_rtc);

/**
 *******************************************************************************
 * @brief RTC initialization
 *
 * @param om_rtc Pointer to RTC
 * @param alarm alarm type, see @ref rtc_alarm_t
 * @param time the alarm time
 *
 * @return None
 *******************************************************************************
 */
extern void drv_rtc_set_alarm(OM_RTC_Type *om_rtc, rtc_alarm_t alarm, uint32_t time);

/**
 *******************************************************************************
 * @brief Set the tick which is periodically generated in RTC module
 *
 * @param om_rtc Pointer to RTC
 * @param hz tick frequency, hz = 1000000/us
 *
 * @return None
 *******************************************************************************
 */
extern void drv_rtc_set_tick_hz(int hz);

/**
 *******************************************************************************
 * @brief Poll wait clocks at 32000Hz
 *
 * @param om_rtc Pointer to RTC
 * @param clocks the delta time to wait: unit 1/32 milliseconds
 *
 * @return None
 *******************************************************************************
 */
extern void drv_rtc_wait_clocks(OM_RTC_Type *om_rtc, uint32_t clocks);

/**
 *******************************************************************************
 * @brief Read RTC counter
 *
 * @param om_rtc Pointer to RTC
 *
 * @return RTC counter
 *******************************************************************************
 */
extern uint32_t drv_rtc_read(OM_RTC_Type *om_rtc);

#if (RTE_RTC_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register event callback for RTC interrupt
 *
 * @param isr_cb Pointer to callback
 *
 * @return None
 *******************************************************************************
 */
extern void drv_rtc_register_isr_callback(drv_isr_callback_t isr_cb);
#endif /* (RTE_RTC_REGISTER_CALLBACK) */

/**
 *******************************************************************************
 * @brief The interrupt callback for RTC driver. It is a weak function. User should define
 *        their own callback in user file, other than modify it in the RTC driver.
 *
 * @param om_rtc The RTC device address
 * @param event    The driver event, which could be the combination of fallowing events
 *                 @arg DRV_EVENT_RTC_TICK:       tick
 *                 @arg DRV_EVENT_RTC_ALARM0:     alarm
 *                 @arg DRV_EVENT_RTC_ALARM1:     alarm1
 *
 * @return None
 *******************************************************************************
 */
extern void drv_rtc_isr_callback(void);

extern void pnc_rtc_set_alarm(uint32_t time);
extern void drv_rtc_set_alarm0(uint32_t time);

#ifdef __cplusplus
}
#endif

#endif  /* (RTE_RTC) */

#endif  /* __DRV_RTC_H */

/** @} */
