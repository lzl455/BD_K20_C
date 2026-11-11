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
 * @file     om_mem.h
 * @brief    memory heap manager
 * @date     12 Feb. 2022
 * @author   OnMicro SW Team
 *
 * @defgroup DOC DOC
 * @ingroup  DOCUMENT
 * @brief    memory heap manager
 * @details  memory heap manager
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __OM_MEM_H
#define __OM_MEM_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief  Initialize memory block
 *
 * @param[in] heap_addr   Memory heap, need align to 4 Byte
 * @param[in] size        Size of the memory block, in bytes, need to align to 4 Byte
 *
 * @return                None
 *******************************************************************************
 */
extern void om_mem_init(uint32_t heap_addr, uint32_t size);

/**
 *******************************************************************************
 * @brief  Allocates a block of size bytes from the memory heap
 *
 * @param[in] heap_addr   Memory heap, need align to 4 Byte
 * @param[in] size        Size of the memory block, in bytes
 *
 * @return                Return a pointer to the beginning of the block
 *******************************************************************************
 */
extern void *om_mem_malloc(uint32_t heap_addr, uint32_t size);

/**
 *******************************************************************************
 * @brief  Deallocate memory block from initied memory heap
 *
 * @param[in] heap_addr   Memory heap, need align to 4 Byte
 * @param[in] mem         Pointer to a memory block previously allocated with malloc/calloc
 *******************************************************************************
 */
extern void om_mem_free(uint32_t heap_addr, void *mem);

/**
 *******************************************************************************
 * @brief  Callocate memory block
 *
 * @param[in] heap_addr   Memory heap, need align to 4 Byte
 * @param[in] num         Number of chunk
 * @param[in] size        size of chunk
 *
 * @return                Return a pointer to the beginning of the block
 *******************************************************************************
 */
extern void *om_mem_calloc(uint32_t heap_addr, uint8_t num, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif  /* __OM_MEM_H */


/** @} */
