/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: flash.c
*
* 功能说明: Flash底层写入与擦除处理
* 修改说明:
*******************************************************************************/
#include <string.h>
#include "om_driver.h"
#include "mouse.h"
#include "main.h"
#include "flash_process.h"

//-----------------------------------------------------------------------------;
// 变量定义
//
#define iFLASH_PAGE_SIZE        (256)
#define iFLASH_PAGE_W_MAX       (256*22)
#define iFLASH_PAGE_R_MAX       (256*24)

#define iFLASH_ADDR_START       0x0001B000
#define iFLASH_ADDR_END         (iFLASH_ADDR_START+(256*22))

#define iFLASH_BLE_ID_ABS_ADDR  0x0000C600
#define iFLASH_BLE_ID_ABS_ADDR_BAK 0x0000C700

bool                            bflash_ctrl;

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/*******************************************************************************
* 函数名称: flash_program
* 功能描述: flash数据写入
* 输入参数: addrh\addrl：E2地址；dat：写入数据的地址指针
* 输出参数: 无
* 说    明: 需要外部应用确保写入的地址内数据为空,
            bflash_program_err不能做为写入成功的判断，在写入非8byte数据的时候，
            有可能前面的数据不是想要写入的数据，而引起写错误标志位置位
*******************************************************************************/
bool flash_write(unsigned int addr, unsigned int length)
{
    __ALIGNED(4) uint8_t flash_temp[128];
    uint16_t i, j;

    if((iFLASH_PAGE_W_MAX<addr)||(iFLASH_PAGE_SIZE<length))
        return false;

    if(128<length)
        j = 128;
    else
        j = length;

    drv_flash_read(iFLASH_ADDR_START+addr, flash_temp, j);
    for(i=0; i<j; i++)
    {
        if(flash_temp[i] != flash_fifo[i])
        {
            drv_flash_write(iFLASH_ADDR_START+addr, flash_fifo, length);
            bflash_ctrl = true;
            return true;
        }
    }

    if(128<length)
    {
        j = length-128;
        drv_flash_read(iFLASH_ADDR_START+addr+128, flash_temp, j);
        for(i=0; i<j; i++)
        {
            if(flash_temp[i] != flash_fifo[i+128])
            {
                drv_flash_write(iFLASH_ADDR_START+addr, flash_fifo, length);
                bflash_ctrl = true;
                return true;
            }
        }
    }
    return true;
}

/*******************************************************************************
* 函数名称: flash_program
* 功能描述: flash数据写入
* 输入参数: addrh\addrl：E2地址；dat：写入数据的地址指针
* 输出参数: 无
* 说    明: 需要外部应用确保写入的地址内数据为空,
            bflash_program_err不能做为写入成功的判断，在写入非8byte数据的时候，
            有可能前面的数据不是想要写入的数据，而引起写错误标志位置位
*******************************************************************************/
bool flash_write_ble_addr(unsigned int addr)
{
    if(512<addr)
        return false;

    if(iDEVICE_TYPE_BT2 < device_type)
        return false;                                 // 非BLE模式不存储ID

    drv_flash_write(iFLASH_ADDR_END+addr, flash_fifo, 64);
    bflash_ctrl = true;
    return true;
}

/*******************************************************************************
* 函数名称: flash_erase
* 功能描述: flash擦除
* 输入参数: bank:Bank序号,0-6有效
* 输出参数: 无
* 说    明:
*******************************************************************************/
bool flash_read(unsigned int addr, unsigned int length)
{
    if(256<length)
        return false;

    if (addr >= iFLASH_PAGE_R_MAX)
        return false;

    drv_flash_read(iFLASH_ADDR_START+addr, flash_fifo, length);

    return true;
}

/*******************************************************************************
* 函数名称: flash_erase
* 功能描述: flash擦除
* 输入参数: bank:Bank序号,0-23有效
* 输出参数: 无
* 说    明:
*******************************************************************************/
bool flash_erase(unsigned char bank)
{
    __ALIGNED(4) uint8_t flash_temp[128];

    if((24 < bank))
        return false;

    drv_flash_read(iFLASH_ADDR_START+(bank<<8), flash_temp, 128);
    unsigned char i=0;
    do
    {
        if(0xFF != flash_temp[i++])
            goto flash_erase_process;
        if(128==i)
            break;
    }
    while(1);

    drv_flash_read(iFLASH_ADDR_START+(bank<<8)+128, flash_temp, 128);
    i=0;
    do
    {
        if(0xFF != flash_temp[i++])
            goto flash_erase_process;
        if(128==i)
            return true;
    }
    while(1);

flash_erase_process:
	drv_flash_erase(iFLASH_ADDR_START+(bank<<8), FLASH_ERASE_PAGE); // 擦除256字节，9ms
    bflash_ctrl = true;
    return true;
}

