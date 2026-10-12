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
 * @file     evt.c
 * @brief    event
 * @date     01. April 2020
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
#include <stddef.h>
#include <string.h>
#include "om_error.h"
#include "evt.h"
#include "om_common.h"
#include "om_driver.h"


/*******************************************************************************
 * TYPEDEFS
 */
/// environment structure
typedef struct {
    /// Event field
    volatile uint32_t field;
    /// Callback table
    evt_callback_t callback[EVT_TYPE_NUM];
} evt_env_t;


/*******************************************************************************
 * GLOBAL VARIABLES
 */
/// environment
static evt_env_t evt_env = {
    .field    = 0U,
    .callback = {0U},
};


/*******************************************************************************
 * EXPORTED FUNCTION DEFINITIONS
 */
/**
 *******************************************************************************
 * @brief  evt init
 *******************************************************************************
 **/
void evt_init(void)
{
    memset(&evt_env, 0, sizeof(evt_env));
}

/**
 *******************************************************************************
 * @brief  evt callback set
 *
 * @param[in] evt_type  event type
 * @param[in] callback  callback
 *
 * @return
 *******************************************************************************
 **/
void evt_callback_register(evt_type_t evt_type, evt_callback_t callback)
{
    OM_ASSERT(evt_type < EVT_TYPE_NUM);
    evt_env.callback[evt_type] = callback;
}

/**
 *******************************************************************************
 * @brief  evt set
 *
 * @param[in] evt_type  event type
 *******************************************************************************
 **/
void evt_set(evt_type_t evt_type)
{
    OM_ASSERT(evt_type < EVT_TYPE_NUM);

    OM_CRITICAL_BEGIN();
    evt_env.field |= (1 << evt_type);
    OM_CRITICAL_END();
}

/**
 *******************************************************************************
 * @brief  evt clear
 *
 * @param[in] evt_type  event type
 *******************************************************************************
 **/
void evt_clear(evt_type_t evt_type)
{
    OM_ASSERT(evt_type < EVT_TYPE_NUM);

    OM_CRITICAL_BEGIN();
    evt_env.field &= ~(1u << evt_type);
    OM_CRITICAL_END();
}

/**
 *******************************************************************************
 * @brief  evt get
 *
 * @param[in] evt_type  event type
 *
 * @return is on ?
 *******************************************************************************
 **/
uint8_t evt_get(evt_type_t evt_type)
{
    uint8_t state;

    OM_ASSERT(evt_type < EVT_TYPE_NUM);

    OM_CRITICAL_BEGIN();
    state = (evt_env.field >> evt_type) & 1;
    OM_CRITICAL_END();

    return state;
}

/**
 *******************************************************************************
 * @brief  evt get all
 *
 * @return
 *******************************************************************************
 **/
uint32_t evt_get_all(void)
{
    return evt_env.field;
}

/**
 *******************************************************************************
 * @brief  evt flush
 *******************************************************************************
 **/
void evt_flush(void)
{
    evt_env.field = 0;
}

/**
 *******************************************************************************
 * @brief  evt schedule
 *******************************************************************************
 **/
void evt_schedule(void)
{
    // Get the volatile value
    uint32_t field = evt_env.field;

    while (field) { // Compiler is assumed to optimize with loop inversion
        // Find highest priority event set
        uint32_t hdl = 31 - __CLZ(field);

        evt_clear(hdl);
        if(evt_env.callback[hdl] != NULL) {
            // Execute corresponding handler
            (evt_env.callback[hdl])();
        } else {
            OM_ASSERT(0);
        }

        // Update the volatile value
        field = evt_env.field;
    }
}

/**
 *******************************************************************************
 * @brief  evt schedule once
 *
 * @return  not schedule event
 *******************************************************************************
 **/
uint32_t evt_schedule_once(void)
{
    // Get the volatile value
    uint32_t field = evt_env.field;

    if (field) { // Compiler is assumed to optimize with loop inversion
        // Find highest priority event set
        uint8_t hdl = 31 - (uint8_t) __CLZ(field);

        if(evt_env.callback[hdl] != NULL) {
            // Execute corresponding handler
            (evt_env.callback[hdl])();
        } else {
            OM_ASSERT(0);
        }

        // Update the volatile value
        field = evt_env.field;
    }

    return field;
}


/** @} */
