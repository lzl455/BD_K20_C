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
 * @file     drv_flash.c
 * @brief    flash driver
 * @date     18. Oct 2023
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
#if (RTE_FLASH)
#include <stddef.h>
#include "drv_flash.h"

/*******************************************************************************
 * MACROS
 */
#define FLASH_CS_SLECT     0
#define FLASH_DIR_READ     1
#define FLASH_DIR_WRITE    2

#define FLASH_FRAME_CONFIG(data_bytes, cmd_bit, addr_bits, dummy_bit, cs, dir)             \
                ((data_bytes & 0x1FF) << FLASH_COMMAND_DATA_BYTES_NUM_POS)        |        \
                ((cmd_bit & 0x0F)     << FLASH_COMMAND_CMD_BITS_NUM_POS)          |        \
                ((addr_bits & 0x3F)   << FLASH_COMMAND_ADDR_BITS_NUM_POS)         |        \
                ((dummy_bit & 0x1F)   << FLASH_COMMAND_DUMMY_BITS_NUM_POS)        |        \
                ((cs & 0x01)          << FLASH_COMMAND_KEEP_CS_POS)               |        \
                ((dir & 0x03)         << FLASH_COMMAND_WR_POS)                             \

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
__RAM_CODE static void flash_prepare(uint32_t cmd_d, uint32_t buf)
{
    /* Clear the pending interrupt. */
    OM_FLASH->RAW_INTR_STATUS   = OM_FLASH->RAW_INTR_STATUS;
    /* Start flash controller. */
    OM_FLASH->COMMAND_DATA0_REG = cmd_d;
    OM_FLASH->ADDRESS_REG       = buf;
}

__RAM_CODE static void flash_start(uint32_t cmd_fmt)
{
    OM_FLASH->COMMAND = cmd_fmt;
    /* Wait done. */
    while (OM_FLASH->RAW_INTR_STATUS == 0);
    OM_FLASH->RAW_INTR_STATUS = OM_FLASH->RAW_INTR_STATUS;
}

__RAM_CODE static void flash_command_send(uint8_t flash_cmd)
{
    uint32_t cmd_fmt;

    flash_prepare(flash_cmd << 24U, 0);
    cmd_fmt = FLASH_FRAME_CONFIG(0, 8, 0, 0, FLASH_CS_SLECT, FLASH_DIR_WRITE);
    flash_start(cmd_fmt);
}

__RAM_CODE static void flash_read_status(uint32_t* status)
{
    uint32_t cmd_fmt;

    flash_prepare(FLASH_CMD_READ_STATUS_LOW << 24U, (uint32_t)status);
    cmd_fmt = FLASH_FRAME_CONFIG(1, 8, 0, 0, FLASH_CS_SLECT, FLASH_DIR_READ);
    flash_start(cmd_fmt);
}

__RAM_CODE static void flash_write_status(uint32_t status)
{
    uint32_t cmd_fmt, sr;

    flash_command_send(FLASH_CMD_WRITE_EN);
    flash_prepare(FLASH_CMD_WRITE_STATUS << 24u, (uint32_t)&status);
    cmd_fmt = FLASH_FRAME_CONFIG(1, 8, 0, 0, FLASH_CS_SLECT, FLASH_DIR_WRITE);
    flash_start(cmd_fmt);
    do {
        flash_read_status(&sr);
    } while(SFLASH_SR_WIP & sr);
}

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
om_error_t drv_flash_init(void)
{
    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_FLASH, 1U);
    /* Set the clock delay parameter of sflash controller */
    register_set(&(OM_RCC->FLASH_CLKCTRL), MASK_2REG(RCC_FLASH_CLKCTRL_FALL_EDGE_DLY_SAMPLE,  1U,
                                                     RCC_FLASH_CLKCTRL_DLY_SAMPLE,            1U));

    /* Set 1/2/4 wire mode when XIP in sflash */
    OM_RCC->FLASH_READ_OPCODE = RCC_FLASH_READ_OPCDE_VECTKEY | RCC_XIP_OPCODE_FREAD;
    /* Enable write protect (memory:1M bit, protect range: last 1/2) */
    flash_write_status(0);
    /* Exit the critical section code segment */
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

om_error_t drv_flash_read(uint32_t      offset_addr,
                          uint8_t          *data,
                          uint32_t         data_len)
{
    uint32_t cmd_d, cmd_fmt;

    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    cmd_d = (FLASH_CMD_FREAD << 24U) | (offset_addr & 0xffffff);
    flash_prepare(cmd_d, (uint32_t)data);
    cmd_fmt = FLASH_FRAME_CONFIG(data_len, 8, 24, 8, FLASH_CS_SLECT, FLASH_DIR_READ);
    flash_start(cmd_fmt);
    /* Exit the critical section code segment */
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

om_error_t drv_flash_write(uint32_t         offset_addr,
                           uint8_t             *data,
                           uint32_t            data_len)
{
    uint32_t cmd_d, status, cmd_fmt;

    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    flash_command_send(FLASH_CMD_WRITE_EN);
    cmd_d = (FLASH_CMD_PAGE_PROGRAM << 24U) | (offset_addr & 0xffffff);
    flash_prepare(cmd_d, (uint32_t)data);
    cmd_fmt = FLASH_FRAME_CONFIG(data_len, 8, 24, 0, FLASH_CS_SLECT, FLASH_DIR_WRITE);
    flash_start(cmd_fmt);
    do {
        flash_read_status(&status);
    } while(SFLASH_SR_WIP & status);
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

om_error_t drv_flash_erase(uint32_t         offset_addr,
                           flash_erase_t     erase_type)
{
    uint32_t cmd_d, cmd_fmt, status;

    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    flash_command_send(FLASH_CMD_WRITE_EN);
    cmd_d = (erase_type << 24U) | (offset_addr & 0xffffff);
    flash_prepare(cmd_d, 0);
    cmd_fmt = FLASH_FRAME_CONFIG(0, 8, 24, 0, FLASH_CS_SLECT, FLASH_DIR_WRITE);
    flash_start(cmd_fmt);
    do {
        flash_read_status(&status);
    } while(SFLASH_SR_WIP & status);
    /* Exit the critical section code segment */
    OM_CRITICAL_END();

    return OM_ERROR_OK;
}

void drv_flash_enter_deeppowerdown(void)
{
    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    /* send FLASH_CMD_DEEP_POWER_DOWN_ENTER command */
    flash_command_send(FLASH_CMD_DEEP_POWER_DOWN_ENTER);
    /* Exit the critical section code segment */
    OM_CRITICAL_END();
}

void drv_flash_exit_deeppowerdown(void)
{
    /* The following code enters the critical section */
    OM_CRITICAL_BEGIN();
    /* send FLASH_CMD_DEEP_POWER_DOWN_EXIT command */
    flash_command_send(FLASH_CMD_DEEP_POWER_DOWN_EXIT);
    /* Exit the critical section code segment */
    OM_CRITICAL_END();
}
#endif  /* (RTE_FLASH) */

/** @} */
