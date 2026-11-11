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
 * @file     om_ringbuff.h
 * @brief
 * @date     05. June 2020
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    template
 * @details  template, template for .h header file
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


#ifndef __OM_RING_BUFF_H
#define __OM_RING_BUFF_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include <stddef.h>

#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
    uint8_t              *buf;          // pointer to ring buffer
    uint16_t              size;         // ring buffer size
    uint16_t              wptr;         // write pointer of the ring buffer
    uint16_t              rptr;         // read pointer of the ring buffer
    uint16_t              overflow_cnt; // overflow count
} ring_buff_t;


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 *  @brief Initialized a ring buffer
 *
 * @param[in]   rb     Pointer to the handler of ring buffer
 * @param[in]   buf    Pointer to a ring buffer
 * @param[in]   size   Size of ring buffer
 *
 *******************************************************************************
 */
extern void om_ringbuff_init(ring_buff_t *rb, uint8_t *buf, uint16_t size);

/**
 *******************************************************************************
 *  @brief Write one byte to ring buffer
 *
 * @param[in]   rb     Pointer to the handler of ring buffer
 * @param[in]   data   Pointer to in data
 *
 * @return             Actual length into ring buffer
 *
 *******************************************************************************
 */
extern uint8_t om_ringbuff_write_byte(ring_buff_t *rb, uint8_t data);

/**
 *******************************************************************************
 * @brief Write some byte to ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 * @param[in] data     Pointer to in data
 * @param[in] length   Expected length into ring buffer
 *
 * @return             Actual length in ring buffer
 *
 *******************************************************************************
 */
extern uint16_t om_ringbuff_write(ring_buff_t *rb, const uint8_t *data, uint16_t length);

/**
 *******************************************************************************
 * @brief Read 1 byte from ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 * @param[in] data     Pointer to out data
 *
 * @return             Actual length out from ring buffer
 *
 *******************************************************************************
 */
extern uint8_t om_ringbuff_read_byte(ring_buff_t *rb, uint8_t *data);

/**
 *******************************************************************************
 * @brief Read n bytes from ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 * @param[in] data     Out data
 * @param[in] length   Expected read data length
 *
 * @return             Actual length out from ring buffer
 *
 *******************************************************************************
 */
extern uint16_t om_ringbuff_read(ring_buff_t *rb, uint8_t *data, uint16_t length);

/**
 *******************************************************************************
 * @brief Get bytes in ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 *
 * @return             Length in ring buffer
 *
 *******************************************************************************
 */
extern uint16_t om_ringbuff_get_count(ring_buff_t *rb);

/**
 *******************************************************************************
 * @brief Get overflow count in ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 *
 * @return             Overflow count
 *
 *******************************************************************************
 */
extern uint16_t om_ringbuff_read_overflow(ring_buff_t *rb);

/**
 *******************************************************************************
 * @brief Clear overflow count in ring buffer
 *
 * @param[in] rb       Pointer to the handler of ring buffer
 *
 *******************************************************************************
 */
extern void om_ringbuff_clear_overflow(ring_buff_t *rb);

#ifdef  __cplusplus
}
#endif

#endif  /* __OM_RING_BUFF_H */


/** @} */

