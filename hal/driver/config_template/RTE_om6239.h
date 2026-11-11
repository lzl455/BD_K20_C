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
 * @file     RTE_OM6239.h
 * @brief    RTE device for OM6239
 * @date     23. Nov. 2022
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    template
 * @details  RTE device for OM6239
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_OM6239_H
#define __RTE_OM6239_H

// <o.0> RTE_SYSTICK_REGISTER_CALLBACK
#define RTE_SYSTICK_REGISTER_CALLBACK                  0
// <o.0> RTE_CORTEX_SYSTICK
#define RTE_CORTEX_SYSTICK                             1
// <o.0> RTE_CORTEX_SYSTICK_DELAY
#define RTE_CORTEX_SYSTICK_DELAY                       1
// <o.0> RTE_CORTEX_SYSTICK_TIMEOUT
#define RTE_CORTEX_SYSTICK_TIMEOUT                     1
//   <o.0..1> RTE_SYSTICK_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_SYSTICK_IRQ_PRIORITY                       2

// <o.0> RTE_RCC
#define RTE_RCC                                        1

// <o.0> RTE_ISR
#define RTE_ISR                                        1

// <o.0> RTE_GPIO0_REGISTER_CALLBACK
#define RTE_GPIO0_REGISTER_CALLBACK                    0
// <o.0> RTE_GPIO0
#define RTE_GPIO0                                      1
//   <o.0..1> RTE_GPIO0_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_GPIO0_IRQ_PRIORITY                         2

// <o.0> RTE_UART_REGISTER_CALLBACK
#define RTE_UART_REGISTER_CALLBACK                     1
// <o.0> RTE_UART0
#define RTE_UART0                                      1
//   <o.0..1> RTE_UART0_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_UART0_IRQ_PRIORITY                         2

// <o.0> RTE_WDT_REGISTER_CALLBACK
#define RTE_WDT_REGISTER_CALLBACK                      0
// <o.0> RTE_WDT
#define RTE_WDT                                        1
//   <o.0..1> RTE_WDT_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_WDT_IRQ_PRIORITY                           2

// <o.0> RTE_TIMER0
#define RTE_TIMER0                                     1
// <o.0> RTE_TIMER0_REGISTER_CALLBACK
#define RTE_TIMER0_REGISTER_CALLBACK                   0
//   <o.0..1> RTE_TIMER0_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_TIMER0_IRQ_PRIORITY                        2

// <o.0> RTE_PM
#define RTE_PM                                         1

// <o.0> RTE_PMU
#define RTE_PMU                                        1

// <o.0> RTE_AES128
#define RTE_AES128                                     1
// <o.0> RTE_AES128_REGISTER_CALLBACK
#define RTE_AES128_REGISTER_CALLBACK                   0
//   <o.0..1> RTE_AES128_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_AES128_IRQ_PRIORITY                        2

// <o.0> RTE_RTC
#define RTE_RTC                                        1
// <o.0> RTE_RTC_REGISTER_CALLBACK
#define RTE_RTC_REGISTER_CALLBACK                      0
//   <o.0..1> RTE_RTC_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_RTC_IRQ_PRIORITY                           2

// <o.0> RTE_PWM
#define RTE_PWM                                        1

// <o.0> RTE_FLASH
#define RTE_FLASH                                      1
//   <o.0..1> RTE_FLASH_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_FLASH_IRQ_PRIORITY                         2

// <o.0> RTE_RF
#define RTE_RF                                         1
//   <o.0..1> RTE_RF_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_RF_IRQ_PRIORITY                            1
//   <o.0..1> RTE_RF_DMA_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_RF_DMA_IRQ_PRIORITY                        2

// <o.0> RTE_ICACHE
#define RTE_ICACHE                                     1

// <o.0> RTE_USB
#define RTE_USB                                        1
//   <o.0..1> RTE_USB_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_USB_IRQ_PRIORITY                           2
//   <o.0..1> RTE_USB_WK_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_USB_WK_IRQ_PRIORITY                        2

// <o.0> RTE_SENSCAN
#define RTE_SENSCAN                                    1
//   <o.0..1> RTE_SENSCAN_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_SENSCAN_IRQ_PRIORITY                       2

// <o.0> RTE_ENCODER
#define RTE_ENCODER                                    1
//   <o.0..1> RTE_ENCODER_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_ENCODER_IRQ_PRIORITY                       2

// <o.0> RTE_LEDC
#define RTE_LEDC                                       1
//   <o.0..1> RTE_LEDC_IRQ_PRIORITY
//     <0=>0   <1=>1   <2=>2   <3=>3
#define RTE_LEDC_IRQ_PRIORITY                          2

#endif  /* __RTE_OM6239_H */


/** @} */
