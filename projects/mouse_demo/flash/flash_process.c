/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: Flash_process.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "om_driver.h"
#include "led.h"
#include "lvd.h"

#include "main.h"
#include "flash.h"
#include "flash_process.h"
#include "matrix_key.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
bool                        bsave_status;
bool                        bsave_cfg_dpi;
bool                        bsave_ble_id;

__ALIGNED(4) uint8_t        flash_fifo[256];
__ALIGNED(4) uint8_t        def_key_dat[256];
__ALIGNED(4) uint8_t        def_key_fn_dat[256];

uint8_t                     para_cfg_dat[5];
uint8_t                     report_dpi[4];
uint8_t                     ble_id[4];

uint8_t                     key_mode;

uint8_t                     sleep_time_24g;
uint8_t                     sleep_time_ble;
uint8_t                     report_usb;
uint8_t                     report_24g;
uint8_t                     mouse_lod_set;
uint8_t                     key_delay_set;
uint8_t                     sys_mode;

uint16_t                    adv_cfg_value;

uint8_t                     device_status_base;
uint8_t                     cfg_dpi_base;

//----------------------------------------------------------------------------
//表格定义区
//
unsigned char const default_cfg_tbl[] =
{
    0xFF,           // X灵敏度
    0xFF,           // Y灵敏度
    0xFF,           // 狙击DPI+
    0xFF,           // 狙击DPI-
    0x01,           // 组合连发延时
    0xFF,           // 保留
    0xFF,           // 保留
    0xFF,           // 保留
//----------------------------------------------
    0xF3,0x00,0x11,0x00,0xFF,0x00,0x00,0xFF,    // 火力键LED 红色狂闪
//----------------------------------------------
// 0x10
    0xE2,0x08,0x22,0x00,0xFF,0x00,0x00,0xFF,    // DPI0 LED 红色闪4次
    0xE2,0x08,0x22,0x00,0x00,0xFF,0x00,0xFF,    // DPI1 LED 绿色闪4次
    0xE2,0x08,0x22,0x00,0x00,0x00,0xFF,0xFF,    // DPI2 LED 蓝色闪4次
    0xE2,0x08,0x22,0x00,0xFF,0x00,0xFF,0xFF,    // DPI3 LED 紫色闪4次
    0xE2,0x08,0x22,0x00,0xFF,0xFF,0x00,0xFF,    // DPI4 LED 橙色闪4次
    0xE2,0x08,0x22,0x00,0x00,0xFF,0xFF,0xFF,    // DPI5 LED 青色闪4次
    0xE2,0x08,0x22,0x00,0xFF,0xFF,0xFF,0xFF,    // DPI6 LED 白色闪4次
    0xE2,0x08,0x22,0x00,0xFF,0x3F,0x7F,0xFF,    // DPI7 LED 黄色闪4次
//----------------------------------------------
// 0x50
    0xF2,0x00,0x22,0x00,0xFF,0xFF,0xFF,0xFF,    // 闪烁
    0xF3,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,    // 呼吸
    0xF4,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,    // 霓虹

//----------------------------------------------
};

uint32_t            const    ble_sleep_1_time_tbl[] =
{
    mMS_TO_TICK(10*1000),                       // 10s
    mMS_TO_TICK(30*1000),                       // 30s
    mMS_TO_TICK(60*1000),                       // 60s
    mMS_TO_TICK(120*1000),                      // 2min
    mMS_TO_TICK(180*1000),                      // 3min
    mMS_TO_TICK(300*1000),                      // 5min
    mMS_TO_TICK(600*1000),                      // 10min
    mMS_TO_TICK(600*1000),                      // 10min
};

uint32_t             const    ble_sleep_2_time_tbl[] =
{
    mMS_TO_TICK(5*60*1000),                     // 5min
    mMS_TO_TICK(10*60*1000),                    // 10min
    mMS_TO_TICK(15*60*1000),                    // 15min
    mMS_TO_TICK(20*60*1000),                    // 20min
    mMS_TO_TICK(30*60*1000),                    // 30min
    mMS_TO_TICK(40*60*1000),                    // 40min
    mMS_TO_TICK(60*60*1000),                    // 60min
    mMS_TO_TICK(60*60*1000),                    // 60min
};

//============================================================================;
// 代码区                                                                     ;
//============================================================================;

/*******************************************************************************
* 函数名称: checksum_flash()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
unsigned char checksum_flash(unsigned char lenght, unsigned char *ptr)
{
    unsigned char i, check;

    check = 0x5A;
    for(i=0; i<lenght; i++)
        check ^= ptr[i];

    return check;
}

/*******************************************************************************
* 函数名称: laod_mouse_status()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
void laod_defaut_status(void)
{
    key_mode = iKEY_MODE_0;

    report_dpi[0] = ((iREPORT_250<<6)|(iREPORT_250<<4)|2); // usb:250Hz;24g:250Hz;
    report_dpi[1] = ((iREPORT_250<<6)|(iREPORT_250<<4)|2); // usb:250Hz;24g:250Hz;
    report_dpi[2] = ((iREPORT_250<<6)|(iREPORT_250<<4)|2); // usb:250Hz;24g:250Hz;
    sys_mode = 0x1F;

    bat_status |= 0x1F;
    report_24g = iREPORT_250;
    report_usb = iREPORT_250;

    key_ctrl &= ~bwin_lock_status;
    key_ctrl |= bwin_mac_sataus;

    led_cur_mode = iMODE_LED_SBZL;
    bled_bright_en = true;
}

/*******************************************************************************
* 函数名称: laod_mouse_status()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
void laod_mouse_status(void)
{
    uint8_t i;
//----------------------------------------------
// 读取状态数据 鼠标自身状态：当前DPI，LED模式灯
//
    flash_read(iSTATUS_BANK_ADDR, 256);
    device_status_base = 0xF8;
    i = 0xF8;
    while(1)
    {
        if(iSTATUS_DATA_TYPE == (flash_fifo[i+0]))
        {
            device_status_base = i;

            key_mode = (flash_fifo[i+6]&0x03);
            bt_index = ((flash_fifo[i+6]>>2)&0x03);
            //device_type = ((flash_fifo[i+6]>>4)&0x07);  // 按键切换模式情况下才能打开 ！！！！！！！！
            bat_status &= 0xE0;
            bat_status |= (flash_fifo[i+7]&0x1F);
            key_ctrl &= ~bwin_lock_status;
            if(0!=(flash_fifo[i+7]&(1<<5)))
                key_ctrl |= bwin_lock_status;

            report_dpi[0] = flash_fifo[i+1];
            //report_dpi[1] = flash_fifo[i+2];
            //report_dpi[2] = flash_fifo[i+3];
            sys_mode = flash_fifo[i+4];

            key_ctrl &= ~bwin_mac_sataus;
            if(sys_mode&(1<<(device_type&0x07)))
                key_ctrl |= bwin_mac_sataus;

            led_cur_mode = (flash_fifo[i+5]&0x1F);
            bled_bright_en = false;
            if(flash_fifo[i+5]&(1<<7))
                bled_bright_en = true;

            report_24g = ((report_dpi[0]>>4)&0x03);
            report_usb = ((report_dpi[0]>>6)&0x03);
            if(0 == i)
                break;
        }
        else
        {
            if(0xF8 == i)
            {
                laod_defaut_status();
                bt_index = iDEVICE_TYPE_BT0;
                //device_type = iDEVICE_TYPE_BT0;  // 按键切换模式情况下才能打开 ！！！！！！！！
            }
            break;
        }

        i -= 0x08;
    }
}

/*******************************************************************************
* 函数名称: laod_cfg_dpi()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
void laod_cfg_dpi(void)
{
    uint8_t i;
//----------------------------------------------
// 系统配置数据 APP下发的相关配置数据
//
    flash_read(iFLASH_CFG_DPI_ADDR, 256);
    cfg_dpi_base = 0xF0;
    i = 0xF0;
    while(1)
    {
        if(iCFG_DPI_TYPE == (flash_fifo[i+0]))
        {
            cfg_dpi_base = i;
            led_light_lev = (flash_fifo[i+1]&0x07);
            led_speed_lev = ((flash_fifo[i+1]>>4)&0x07);

            led_rgb_index = (flash_fifo[i+2]&0x07);

            sleep_time_24g = flash_fifo[i+3];
            sleep_time_ble = flash_fifo[i+4];
            adv_cfg_value = ((flash_fifo[i+6]<<8)|flash_fifo[i+5]);

            mouse_lod_set = ((flash_fifo[i+5]>>0)&0x03);
            if(0 == i)
                break;
        }
        else
        {
            if(0xF0 == i)
            {
                led_light_lev = iLED_LEV_3;
                led_speed_lev = iSPEED_LEV_2;
                led_rgb_index = iPWM_RGB;           // 全彩

                sleep_time_24g = 0x25;              // 24g：1分钟一级休眠，10分钟深度休眠
                sleep_time_ble = 0x25;              // ble：1分钟一级休眠，10分钟深度休眠

                adv_cfg_value = 0x0001;
                mouse_lod_set = 1;                  // 静默高度
                key_delay_set = 0;                  // 去抖延时
            }
            break;
        }

        i -= 0x10;
    }
}

extern unsigned char    const   matrixkey_win_tbl[];
extern unsigned char    const   matrixkey_win_fn_tbl[];

/*******************************************************************************
* 函数名称: laod_mode_data()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
void laod_flash_cfg(void)
{
    uint8_t i;

    drv_flash_init();

    laod_mouse_status();
    laod_cfg_dpi();
//----------------------------------------------------------------------------
// WIN MODE
//
//    flash_read(iKEY_MODE0_ADDR+255, 1);
//    if(0xA5 != flash_fifo[0])
//    {
//        memset(flash_fifo, 0xFF, 255);
//        memcpy(flash_fifo, matrixkey_win_tbl, 250);
//        flash_fifo[255] = 0xA5;

//        flash_erase(iKEY_MODE0_BANK);
//        flash_write(iKEY_MODE0_ADDR, 256);
//    }

    //if(iSYS_WIN == sys_type)
        //memcpy(def_key_dat, flash_fifo, 250);
        memcpy(def_key_dat, matrixkey_win_tbl, 250);
//----------------------------------------------------------------------------
// WIN FN MODE
//    flash_read(iKEY_MODE1_ADDR+255, 1);
//    if(0xA5 != flash_fifo[0])
//    {
//        memset(flash_fifo, 0xFF, 255);
//        memcpy(flash_fifo, matrixkey_win_fn_tbl, 250);
//        flash_fifo[255] = 0xA5;

//        flash_erase(iKEY_MODE1_BANK);
//        flash_write(iKEY_MODE1_ADDR, 256);
//    }

    //if(iSYS_WIN == sys_type)
        //memcpy(def_key_fn_dat, flash_fifo, 250);
        memcpy(def_key_fn_dat, matrixkey_win_fn_tbl, 250);

////----------------------------------------------------------------------------
//// MAC MODE
////
//    flash_read(iKEY_MODE2_ADDR, 32);
//    if(flash_fifo[iKEY_DATA_CS_ADDR] != checksum_flash(31, flash_fifo))
//    {
//        memset(flash_fifo, 0xFF, 31);
//        memcpy(flash_fifo, default_key_tbl, sizeof(default_key_tbl));
//        flash_fifo[iKEY_DATA_CS_ADDR] = checksum_flash(31, flash_fifo);

//        flash_erase(iKEY_MODE2_BANK);
//        flash_write(iKEY_MODE2_ADDR, 32);
//    }
//    if(iKEY_MODE_2 == key_mode)
//        memcpy(def_key_dat, flash_fifo, 24);
////----------------------------------------------------------------------------
//// MAC FN MODE
////
//    flash_read(iKEY_MODE3_ADDR, 32);
//    if(flash_fifo[iKEY_DATA_CS_ADDR] != checksum_flash(31, flash_fifo))
//    {
//        memset(flash_fifo, 0xFF, 31);
//        memcpy(flash_fifo, default_key_tbl, sizeof(default_key_tbl));
//        flash_fifo[iKEY_DATA_CS_ADDR] = checksum_flash(31, flash_fifo);

//        flash_erase(iKEY_MODE3_BANK);
//        flash_write(iKEY_MODE3_ADDR, 32);
//    }
//    if(iKEY_MODE_3 == key_mode)
//        memcpy(def_key_dat, flash_fifo, 24);
//
//----------------------------------------------
// 读取配置
//
    flash_read(iCFG_BANK_ADDR, 256);
    if(iCFG_DATA_TYPE_VALULE != flash_fifo[iCFG_DATA_TYPE_ADDR])
    {
        memset(flash_fifo, 0xFF, 254);
        memcpy(flash_fifo, default_cfg_tbl, sizeof(default_cfg_tbl));
        flash_fifo[iCFG_DATA_CS_ADDR] = checksum_flash(254, flash_fifo);
        flash_fifo[iCFG_DATA_TYPE_ADDR] = iCFG_DATA_TYPE_VALULE;

        flash_erase(iCFG_BANK);
        flash_write(iCFG_BANK_ADDR, 256);
    }
    memcpy(para_cfg_dat, flash_fifo, 5);
}

extern bool bkey_mode_change;

/*******************************************************************************
* 函数名称: flash_save_mode_dpi()
* 功能描述:
* 输入参数: index
* 输出参数: 无
* 说    明:
*******************************************************************************/
__attribute__((noinline)) void flash_save_status(void)
{
    uint8_t i, dat_temp[8];

    dat_temp[0] = iSTATUS_DATA_TYPE;
    dat_temp[1] = report_dpi[0];
    dat_temp[2] = report_dpi[1];
    dat_temp[3] = report_dpi[2];

    sys_mode &= ~(1<<(device_type&0x07));
    if(key_ctrl&bwin_mac_sataus)
        sys_mode |= (1<<(device_type&0x07));
    dat_temp[4] = sys_mode;

    dat_temp[5] = (led_cur_mode&0x1F);
    if(true == bled_bright_en)
        dat_temp[5] |= (1<<7);
    dat_temp[6] = (key_mode&0x03);
    dat_temp[6] |= ((bt_index<<2)&0x0C);
    dat_temp[6] |= ((device_type<<4)&0x70);
    dat_temp[7] = (bat_status&0x1F);
    if(key_ctrl&bwin_lock_status)
        dat_temp[7] |= (1<<5);

    flash_read(iSTATUS_BANK_ADDR, 256);
    for(i=1; i<8; i++)
    {
        if(dat_temp[i] != flash_fifo[device_status_base + i])
        {
            goto flash_save_device_status;
        }
    }
    return;

flash_save_device_status:
    device_status_base = 0xF8;
    while(1)
    {
        for(i=0; i<8; i++)
        {
            if(0xFF != flash_fifo[device_status_base+i])
            {
                goto device_status_null_bank;
            }
        }
flash_save_device_status_begin:
        OM_CRITICAL_BEGIN();
        memcpy(flash_fifo, dat_temp, 8);
        flash_write(iSTATUS_BANK_ADDR+device_status_base, 8);

        if(true == bkey_mode_change)
            laod_flash_cfg();
        else
            laod_mouse_status();
        OM_CRITICAL_END();

        bkey_mode_change = false;
        return;

device_status_null_bank:
        if(0x00 == device_status_base)
        {
            OM_CRITICAL_BEGIN();
            flash_erase(iFLASH_STATUS_BANK);
            OM_CRITICAL_END();
            device_status_base = 0xF8;
            goto flash_save_device_status_begin;
        }
        device_status_base -= 8;
    }
}

/*******************************************************************************
* 函数名称: flash_save_mode_dpi()
* 功能描述:
* 输入参数: index
* 输出参数: 无
* 说    明:
*******************************************************************************/
__attribute__((noinline)) void flash_save_cfg_dpi(void)
{
    bool bflash_erase=false;
    uint8_t i, dat_temp[16];

    dat_temp[0] = iCFG_DPI_TYPE;
    dat_temp[1] = (led_light_lev&0x07);
    dat_temp[1] |= ((led_speed_lev<<4)&0x70);
    dat_temp[2] = (led_rgb_index&0x07);

    dat_temp[3] = sleep_time_24g;
    dat_temp[4] = sleep_time_ble;
    dat_temp[5] = ((adv_cfg_value>>0)&0xFF);
    dat_temp[6] = ((adv_cfg_value>>8)&0xFF);
    dat_temp[7] = 0xFF;

    flash_read(iFLASH_CFG_DPI_ADDR, 256);
    for(i=1; i<16; i++)
    {
        if(dat_temp[i] != flash_fifo[cfg_dpi_base + i])
        {
            goto flash_save_cfg_dpi;
        }
    }
    return;

flash_save_cfg_dpi:
    cfg_dpi_base = 0xF0;
    while(1)
    {
        for(i=0; i<16; i++)
        {
            if(0xFF != flash_fifo[cfg_dpi_base+i])
            {
                goto m_id_check_none_bank;
            }
        }
flash_save_cfg_dpi_begin:
        memcpy(flash_fifo, dat_temp, 16);
        flash_write(iFLASH_CFG_DPI_ADDR+cfg_dpi_base, 16);

        laod_cfg_dpi();
        return;

m_id_check_none_bank:
        if(0x00 == cfg_dpi_base)
        {
            flash_erase(iFLASH_CFG_DPI_BANK);
            cfg_dpi_base = 0xF0;
            goto flash_save_cfg_dpi_begin;
        }
        cfg_dpi_base -= 16;
    }
}

/*******************************************************************************
* 函数名称: flash_save_mode_dpi()
* 功能描述:
* 输入参数: index
* 输出参数: 无
* 说    明:
*******************************************************************************/
__attribute__((noinline)) void flash_load_ble_addr(void)
{
//----------------------------------------------
// 读取BLE ID
//
    flash_read(iFLASH_BLE_ID_ADDR, 8);
    if(iBLE_ID_TPYE == flash_fifo[0])
    {
        if(flash_fifo[7] == checksum_flash(7, flash_fifo))
        {
            ble_id[0] = flash_fifo[iBLE_ID_0_INDEX];
            ble_id[1] = flash_fifo[iBLE_ID_1_INDEX];
            ble_id[2] = flash_fifo[iBLE_ID_2_INDEX];

            return;
        }
    }

    flash_read(iFLASH_BLE_ID_ADDR_BAK_0, 8);
    if(iBLE_ID_TPYE == flash_fifo[0])
    {
        if(flash_fifo[7] == checksum_flash(7, flash_fifo))
        {
            ble_id[0] = flash_fifo[iBLE_ID_0_INDEX];
            ble_id[1] = flash_fifo[iBLE_ID_1_INDEX];
            ble_id[2] = flash_fifo[iBLE_ID_2_INDEX];

            return;
        }
    }

    flash_read(iFLASH_BLE_ID_ADDR_BAK_1, 8);
    if(iBLE_ID_TPYE == flash_fifo[0])
    {
        if(flash_fifo[7] == checksum_flash(7, flash_fifo))
        {
            ble_id[0] = flash_fifo[iBLE_ID_0_INDEX];
            ble_id[1] = flash_fifo[iBLE_ID_1_INDEX];
            ble_id[2] = flash_fifo[iBLE_ID_2_INDEX];

            return;
        }
    }

    flash_read(iFLASH_BLE_ID_ADDR_BAK_2, 8);
    if(iBLE_ID_TPYE == flash_fifo[0])
    {
        if(flash_fifo[7] == checksum_flash(7, flash_fifo))
        {
            ble_id[0] = flash_fifo[iBLE_ID_0_INDEX];
            ble_id[1] = flash_fifo[iBLE_ID_1_INDEX];
            ble_id[2] = flash_fifo[iBLE_ID_2_INDEX];

            return;
        }
    }

    ble_id[0] = 0xFF;
    ble_id[1] = 0xFF;
    ble_id[2] = 0xFF;
}

/*******************************************************************************
* 函数名称: flash_save_mode_dpi()
* 功能描述:
* 输入参数: index
* 输出参数: 无
* 说    明:
*******************************************************************************/
__attribute__((noinline)) void flash_save_ble_addr(void)
{
    if(iDEVICE_TYPE_BT2 < device_type)
        return;                                 // 非BLE模式不存储ID

    memset(flash_fifo, 0xFF, 64);
    flash_fifo[0x00+0] = iBLE_ID_TPYE;
    flash_fifo[0x00+1] = ble_id[0];
    flash_fifo[0x00+2] = ble_id[1];
    flash_fifo[0x00+3] = ble_id[2];
    flash_fifo[0x00+7] = checksum_flash(7, flash_fifo);

    flash_fifo[0x30+0] = iBLE_ID_TPYE;
    flash_fifo[0x30+1] = ble_id[0];
    flash_fifo[0x30+2] = ble_id[1];
    flash_fifo[0x30+3] = ble_id[2];
    flash_fifo[0x30+7] = flash_fifo[7];

    flash_erase(iFLASH_BLE_ID_BANK);
    flash_write_ble_addr(0x000);

    flash_erase(iFLASH_BLE_ID_BANK_BAK);
    flash_write_ble_addr(0x100);
    flash_load_ble_addr();
}
