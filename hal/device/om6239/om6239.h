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
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    om6239 device descriptor
 * @details  om6239 device descriptor
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __OM6239_H
#define __OM6239_H


#ifdef __cplusplus
extern "C" {
#endif

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
typedef enum IRQn {
    /******  Cortex-M0 Processor Exceptions Numbers ***************************/
    NonMaskableInt_IRQn = -14,      /**< 2 Non Maskable Interrupt           */
    HardFault_IRQn      = -13,      /**< 3 Cortex-M0 Hard Fault Interrupt   */
    SVCall_IRQn         = -5,       /**< 11 Cortex-M0 SV Call Interrupt     */
    PendSV_IRQn         = -2,       /**< 14 Cortex-M0 Pend SV Interrupt     */
    SysTick_IRQn        = -1,       /**< 15 Cortex-M0 System Tick Interrupt */

    /******  device specific Interrupt Numbers ********************************/
    RTC_IRQn            = 0,       /**< 16 RTC_IRQn  Interrupt             */
    USB_IRQn            = 1,
    USB_WK_IRQn         = 2,
    RF_IRQn             = 3,       /**< 17 RF_IRQn Interrupt               */
    WAKEUP_GPIO0_IRQn   = 4,       /**< 18 WAKEUP/GPIO0_IRQn Interrupt     */
    TIMER0_IRQn         = 5,       /**< 19 TIMER0_IRQn Interrupt           */
    VBUS_IRQn           = 6,
    WDT_IRQn            = 7,
    SF0_IRQn            = 8,
    ENCODER_IRQn        = 9,
    RF_DMA_IRQn         = 10,       /**< 21 RF DMA Interrupt                */
    AES128_IRQn         = 11,       /**< 22 AES Interrupt                   */
    UART0_IRQn          = 12,       /**< 23 UART0 Interrupt                 */
    SENSCAN_IRQn        = 13,
    LEDC_IRQn           = 14,
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */
/* Start of section using anonymous unions and disabling warnings */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

#define __CM0_REV                 0x0000U   /* Core revision r0p0 */
#define __MPU_PRESENT             0U        /* no MPU present */
#define __VTOR_PRESENT            0U        /* no VTOR present */
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */


#include "core_cm0.h"
#include "../common/common_reg.h"
#include "../common/aes128_reg.h"
#include "../common/rf_reg.h"
#include "../common/rtc_reg.h"
#include "../common/timer_reg.h"
#include "../common/pwm_reg.h"
#include "../common/usb_reg.h"
#include "../common/hcache_reg.h"
#include "../common/flash_reg.h"
#include "../common/rcc_reg.h"
#include "../common/uart_reg.h"
#include "../common/wdt_reg.h"
#include "../common/gpio_reg.h"
#include "../common/pof_reg.h"

#include "pmu_reg.h"
#include "senscan_reg.h"
#include "encoder_reg.h"
#include "ledc_reg.h"

/* Memory base address */
#define SRAM0_BASE                   0x20000000 /*!< SRAM base address in the alias region */
#define SRAM0_SIZE                   0x3000
#define FLASH_MEM_BASE               0x00800000

#define FLASH_BASE                   0x53000000
#define PMU_BASE                     0x40000000
#define AES128_BASE                  0x40000100
#define RTC_BASE                     0x40000200
#define UART0_BASE                   0x40000300
#define TIMER_BASE                   0x40000500
#define RCC_BASE                     0x40000600
#define WDT_BASE                     0x40000700
#define PWM_BASE                     0x40000800
#define POF_BASE                     0x40000900
#define USB_BASE                     0x41000000
#define RF_BASE                      0x42000000
#define GPIO0_BASE                   0x43000000
#define ICACHE_BASE                  0x40000400
#define LEDC_BASE                    0x40000A00
#define ENCODER_BASE                 0x40000B00
#define SENSCAN_BASE                 0x40000C00

#define OM_RTC                       ((OM_RTC_Type *) RTC_BASE)
#define OM_WDT                       ((OM_WDT_Type *) WDT_BASE)
#define OM_RCC                       ((OM_RCC_Type *) RCC_BASE)
#define OM_PMU                       ((OM_PMU_Type *) PMU_BASE)
#define OM_GPIO0                     ((OM_GPIO_Type *) GPIO0_BASE)
#define OM_UART0                     ((OM_UART_Type *) UART0_BASE)
#define OM_AES128                    ((OM_AES128_Type *) AES128_BASE)
#define OM_RF                        ((OM_RF_Type *) RF_BASE)
#define OM_TIMER0                    ((OM_TIMER_Type *) TIMER_BASE)
#define OM_PWM                       ((OM_PWM_Type *) PWM_BASE)
#define OM_POF                       ((OM_POF_Type *) POF_BASE)
#define OM_FLASH                     ((OM_FLASH_Type *) FLASH_BASE)
#define OM_ICACHE                    ((OM_ICACHE_Type *) ICACHE_BASE)
#define OM_USB                       ((OM_USB_Type *) USB_BASE)
#define OM_LEDC                      ((OM_LEDC_Type *) LEDC_BASE)
#define OM_ENCODER                   ((OM_ENCODER_Type *) ENCODER_BASE)
#define OM_SENSCAN                   ((OM_SENSCAN_Type *) SENSCAN_BASE)

/* End of section using anonymous unions and disabling warnings */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __OM6239_H */


/** @} */
