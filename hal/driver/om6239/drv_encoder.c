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
 * @file     drv_encoder.c
 * @brief    encoder driver
 * @date     23. May 2024
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
#if (RTE_ENCODER)
#include <stddef.h>
#include "drv_encoder.h"


/*******************************************************************************
 * TYPEDEFS
 */
#if (RTE_ENCODER_REGISTER_CALLBACK)
typedef struct {
    drv_isr_callback_t    isr_cb;
} encoder_env_t;
#endif /* (RTE_ENCODER_REGISTER_CALLBACK) */


/*******************************************************************************
 * CONST & VARIABLES
 */
#if (RTE_ENCODER_REGISTER_CALLBACK)
static encoder_env_t encoder_env = {
    .isr_cb       = NULL,
};
#endif /* (RTE_ENCODER_REGISTER_CALLBACK) */


/*******************************************************************************
 * PUBLIC FUNCTIONS
    encoder_config_t config = {
        .pinmux_sel      = ENCODER_PINMUX_SEL_IO_00_01,
        .debounce_time   = ENCODER_DEBOUNCE_TIME_250US,
        .mode            = ENCODER_MODE_0,
    };
 */
void drv_encoder_init(void)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_ENCODER, 1U);
    NVIC_ClearPendingIRQ(ENCODER_IRQn);
    NVIC_SetPriority(ENCODER_IRQn, RTE_ENCODER_IRQ_PRIORITY);
    NVIC_EnableIRQ(ENCODER_IRQn);
    // config debounce time
    OM_ENCODER->SAM = ENCODER_DEBOUNCE_TIME_250US;
    OM_ENCODER->MODE = (ENCODER_MODE_0 << ENCODER_MODE_WHEELA_POS);
    // pinmux select、enable wakeup
    // ENCODER_PINMUX_SEL_IO_00_01 ENCODER_PINMUX_SEL_IO_20_21 ENCODER_PINMUX_SEL_IO_24_25
    register_set(&(OM_ENCODER->EN), MASK_2REG(ENCODER_EN_PINMUX_SEL,  ENCODER_PINMUX_SEL_IO_20_21,
                                              ENCODER_EN_WAKEUP_EN,   0));
}

om_error_t drv_encoder_read_int(OM_ENCODER_Type *om_encoder)
{
    om_encoder->EN |= (ENCODER_EN_INTERRUPT_EN_MASK + ENCODER_EN_ENCODER_EN_MASK);

    return OM_ERROR_OK;
}

#if (RTE_ENCODER_REGISTER_CALLBACK)
void drv_encoder_register_isr_callback(OM_ENCODER_Type *om_encoder, drv_isr_callback_t isr_cb)
{
    encoder_env.isr_cb = isr_cb;
}
#endif /* (RTE_ENCODER_REGISTER_CALLBACK) */


#endif  /* (RTE_ENCODER) */

/** @} */
