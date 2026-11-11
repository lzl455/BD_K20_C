/*******************************************************************************
* Copyright (c) 2016, SHENZHEN HUNTERSUN Co.,LTD.
* All rights reserved.
*
* 文件名称: HID_Process.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include <string.h>
#include "main_usb.h"

//-----------------------------------------------------------------------------;
// 变量定义
//
bool                        bjump_boot;
bool                        bkey_mode_change;

volatile unsigned char      hid_ctrl_reg;
unsigned char               in_report_data[32];
unsigned char               out_report_data[32];
unsigned char               dpi_index;
unsigned int                check_sum;

extern void hid_cmd_fcc_test(void);

//----------------------------------------------------------------------------—;
//表格定义区
//
extern uint8_t const key_delay_tbl[];

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

void clear_in_fifo(void)
{
	memset(in_report_data, 0x00, 32);
}

/******************************************************************************
* 函数名称: hid_write_read_err
* 功能描述: HID读写错误处理
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hid_write_read_err(void)
{
    //in_report_data[0] = out_report_data[0];
    in_report_data[1] = out_report_data[1];
    in_report_data[2] = iNAK;
    in_report_data[3] = 0;
    in_report_data[4] = 0;
    in_report_data[5] = 0;
    in_report_data[6] = 0;
    in_report_data[7] = 0;

    m_data_flag |= bhid_data_send;
}

/******************************************************************************
* 函数名称: checksum_check
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void checksum_check(unsigned int length, unsigned char *ptr)
{
    unsigned int i;

    if(0 != (length&0x01))
    {
        hid_ctrl_reg |= bhid_cmd_err;
        return;
    }

	check_sum = 0xFA21;
	for(i=0; i<length; i+=2)
	{
		check_sum += (ptr[i] | (ptr[i+1]<<8));
	}
}

/******************************************************************************
* 函数名称: flash_ctrl
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明: 下载程序到flash采用缓存的机制，先下载到缓存，再下发命令下载到flash，
            可以有效提高下载速度
******************************************************************************/
void flash_ctrl(void)
{
    unsigned int addr, length;
    unsigned char j, x;
    unsigned char err_id;

    err_id = iID_OK;
    switch(out_report_data[1]&iHID_CMD_KEY_CFG_MASK)
    {
        case iHID_CMD_W_FLASH:                  // 鼠标配置信息写flash
            length = out_report_data[4];
            if(0==out_report_data[4])
                length = 256;
            if((0xA5 != out_report_data[5]))
            {                                   // 长度错误
                err_id = iID_LENGTH_ERR;
                hid_ctrl_reg |= bhid_cmd_err;
            }
            else
            {
                checksum_check(length, flash_fifo);
                if((out_report_data[6] != (check_sum&0xFF))
				    ||(out_report_data[7] != ((check_sum>>8)&0xFF)))
                {                               // CS错误
                    err_id = iID_CS_ERR;
                    hid_ctrl_reg |= bhid_cmd_err;
                }
            }

            addr = ((out_report_data[3]<<8)|out_report_data[2]);
            if(iCFG_MAX_LENGHT < addr)
            {                                   // 地址错误
                err_id = iID_ADDR_ERR;
                hid_ctrl_reg |= bhid_cmd_err;
            }

            if(0==(hid_ctrl_reg&bhid_cmd_err))
            {
                flash_write(addr, length);
                if(0!=(hid_ctrl_reg&bhid_cmd_err))
                    err_id = iID_W_FLASH_ERR;
            }

            clear_in_fifo();
            in_report_data[0] = iHID_CMD_HANDLE;
            in_report_data[1] = iHID_CMD_W_FLASH|iHID_CMD_SYS_CTRL;
            in_report_data[2] = ((addr>>0)&0xFF);
            in_report_data[3] = ((addr>>8)&0xFF);
            in_report_data[4] = out_report_data[4];
            in_report_data[5] = iACK;
            if(0!=(hid_ctrl_reg&bhid_cmd_err))
                in_report_data[5] = iNAK;
            in_report_data[7] = err_id;

            m_data_flag |= bhid_data_send;
            break;
        case iHID_CMD_W_FIFO:
            clear_in_fifo();

            in_report_data[0] = iHID_CMD_HANDLE;
            in_report_data[1] = iHID_CMD_W_FIFO|iHID_CMD_SYS_CTRL;
            in_report_data[2] = out_report_data[2];
            in_report_data[3] = out_report_data[3];
            if((28>=out_report_data[3]) && ((out_report_data[3]+out_report_data[2])<=iPAGE_LENGHT))
            {
                j = out_report_data[2];
                for(x=0; x<out_report_data[3]; x++)
                {
                    flash_fifo[j++] = out_report_data[x+4];
                }

                j = out_report_data[2];
                for(x=0; x<out_report_data[3]; x++)
                {
                    in_report_data[4+x] = flash_fifo[j++];
                    if(in_report_data[4+x] != out_report_data[4+x])
                    {
                        in_report_data[3] |= 0x80;
                    }
                }
            }
            else
            {
                in_report_data[3] |= 0x80;
            }
            m_data_flag |= bhid_data_send;

            break;
        case iHID_CMD_R_FLASH:
            in_report_data[0] = iHID_CMD_HANDLE;
            in_report_data[1] = iHID_CMD_R_FLASH|iHID_CMD_SYS_CTRL;
            in_report_data[2] = out_report_data[2];
            in_report_data[3] = out_report_data[3];

            addr = ((out_report_data[3]<<8) | out_report_data[2]);
            length = out_report_data[4];
            if(0==out_report_data[4])
                length = 256;

            if(iFLASH_MAX_LENGHT < (addr+length))
            {
                hid_ctrl_reg |= bhid_cmd_err;
            }
            else
            {
               if(length > iFLASH_R_MAX_SIZE)
                {
                    length = (length-iFLASH_R_MAX_SIZE);
                    j = iFLASH_R_MAX_SIZE;
                }
                else
                {
                    j = length;
                    length = 0;
                }
	            flash_read(addr, j);
                memcpy(in_report_data+5, flash_fifo, j);

                if(length != 0x00)
                {
                    addr += j;
                    out_report_data[2] = (addr&0xFF);
                    out_report_data[3] = ((addr>>8)&0xFF);

                    out_report_data[4] = (length&0xFF);
                    hid_ctrl_reg |= bhid_data_process;
                }
            }
            in_report_data[4] = j;
            if(0!=(hid_ctrl_reg&bhid_cmd_err))
                in_report_data[4] |= 0x80;
            m_data_flag |= bhid_data_send;

            break;
         case iHID_CMD_E_FLASH: // 擦除FLASH
            in_report_data[0] = iHID_CMD_HANDLE;
            in_report_data[1] = iHID_CMD_E_FLASH|iHID_CMD_SYS_CTRL;
            in_report_data[2] = out_report_data[2];
            in_report_data[3] = ~out_report_data[3];
            in_report_data[4] = iACK;

            if((out_report_data[2] == in_report_data[3])
                && (iFLASH_BANK_MAX > out_report_data[2])
                && (0x55 == out_report_data[4])
                && (0xAA == out_report_data[5]))
            {
                flash_erase(out_report_data[2]);
            }

            m_data_flag |= bhid_data_send;
            break;
    }
}

/******************************************************************************
* 函数名称: hid_get_fw_mode_info
* 功能描述: 获取程序版本信息
* 输入参数: 无
* 输出参数: 无
* 说    明: 获取程序版本信息
******************************************************************************/
void hid_get_fw_mode_info(void)
{
    clear_in_fifo();
    in_report_data[0] = iHID_CMD_HANDLE;
    in_report_data[1] = iHID_CMD_MODE_INFO;

    in_report_data[2] = (key_mode&0x03);        // 当前按键模式
    in_report_data[3] = 0x00;                   // dongle信息，有线模式无效
    in_report_data[4] = report_dpi[0];
    in_report_data[5] = report_dpi[1];
    in_report_data[6] = report_dpi[2];
    in_report_data[7] = report_dpi[3];

    in_report_data[0x08] = (led_cur_mode&0x1F);
    if(true == bled_bright_en)
        in_report_data[0x08] |= (1<<6);

    in_report_data[0x09] = 0;
    in_report_data[0x0A] = (led_light_lev&0x07);
    in_report_data[0x0A] |= ((led_speed_lev<<4)&0x70);

    in_report_data[0x0B] = (led_rgb_index&0x07);

    in_report_data[0x0C] = sleep_time_24g;
    in_report_data[0x0D] = sleep_time_ble;
    in_report_data[0x0E] = ((adv_cfg_value>>0)&0xFF);
    in_report_data[0x0F] = ((adv_cfg_value>>8)&0xFF);

    in_report_data[0x17] = 0;
    in_report_data[0x18] = 0;
    in_report_data[0x19] = sys_mode;
    in_report_data[0x1A] = kb_bd_addr[0];
    in_report_data[0x1B] = kb_bd_addr[1];
    in_report_data[0x1C] = kb_bd_addr[2];
    in_report_data[0x1D] = kb_bd_addr[3];
    in_report_data[0x1E] = kb_bd_addr[4];
    in_report_data[0x1F] = kb_bd_addr[5];

    m_data_flag |= bhid_data_send;
}

/******************************************************************************
* 函数名称: HIDDataProcess
* 功能描述: 处理HID数据
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
__attribute__((noinline)) void hid_process(void)
{
    unsigned char i;

    if(0==(m_data_flag & bhid_data_send))
    {
        if(hid_ctrl_reg&bdevice_status_change)
        {
            hid_ctrl_reg &= ~bdevice_status_change;
            hid_get_fw_mode_info();
            return;
        }
    }

    if(hid_ctrl_reg & bhid_data_process)
    {
        hid_ctrl_reg &= ~bhid_data_process;

        if(iHID_CMD_HANDLE != out_report_data[0])
            return;

        hid_ctrl_reg &= ~bhid_cmd_err;

        if(iHID_CMD_FCC == out_report_data[1])
        {
            hid_cmd_fcc_test();
            return;
        }

        if(iHID_CMD_SYS_CTRL == (out_report_data[1]&iHID_CMD_MASK))
        {                                       // 系统控制命令
//gpio_toggle(TIMER_PIN);
            if(iHID_CMD_KEY_CFG == (out_report_data[1]&0xFC))
            {
                flash_ctrl();
            }
            else if(iHID_CMD_CFG_INFO == (out_report_data[1]&iHID_CMD_KEY_CFG_MASK))
            {
                clear_in_fifo();
                in_report_data[0x00] = iHID_CMD_HANDLE;
                in_report_data[0x01] = iHID_CMD_SYS_CTRL|iHID_CMD_CFG_INFO;
                in_report_data[0x02] = 0x0F;
                in_report_data[0x03] = (256>>2);
                in_report_data[0x04] = ((iKEY_CFG_ADDR_0>>0)&0xFF);
                in_report_data[0x05] = ((iKEY_CFG_ADDR_0>>8)&0xFF);
                in_report_data[0x06] = ((iKEY_CFG_LENGHT_0>>0)&0xFF);
                in_report_data[0x07] = ((iKEY_CFG_LENGHT_0>>8)&0xFF);
                in_report_data[0x08] = ((iKEY_CFG_ADDR_1>>0)&0xFF);
                in_report_data[0x09] = ((iKEY_CFG_ADDR_1>>8)&0xFF);
                in_report_data[0x0A] = ((iKEY_CFG_LENGHT_1>>0)&0xFF);
                in_report_data[0x0B] = ((iKEY_CFG_LENGHT_1>>8)&0xFF);
                in_report_data[0x0C] = ((iKEY_CFG_ADDR_2>>0)&0xFF);
                in_report_data[0x0D] = ((iKEY_CFG_ADDR_2>>8)&0xFF);
                in_report_data[0x0E] = ((iKEY_CFG_LENGHT_2>>0)&0xFF);
                in_report_data[0x0F] = ((iKEY_CFG_LENGHT_2>>8)&0xFF);

                in_report_data[0x10] = ((iKEY_CFG_ADDR_3>>0)&0xFF);
                in_report_data[0x11] = ((iKEY_CFG_ADDR_3>>8)&0xFF);
                in_report_data[0x12] = ((iKEY_CFG_LENGHT_3>>0)&0xFF);
                in_report_data[0x13] = ((iKEY_CFG_LENGHT_3>>8)&0xFF);

                in_report_data[0x14] = ((iLED_CFG_BASE_ADDR>>0)&0xFF);
                in_report_data[0x15] = ((iLED_CFG_BASE_ADDR>>8)&0xFF);
                in_report_data[0x16] = ((iLED_CFG_MAX_LENGHT>>0)&0xFF);
                in_report_data[0x17] = ((iLED_CFG_MAX_LENGHT>>8)&0xFF);

				checksum_check(30, in_report_data);
                in_report_data[0x1E] = ((check_sum>>0)&0xFF);
                in_report_data[0x1F] = ((check_sum>>8)&0xFF);

                m_data_flag |= bhid_data_send;
            }
            else if(iHID_CMD_ISP == (out_report_data[1]&iHID_CMD_KEY_CFG_MASK))
            {
                if((0x55 == out_report_data[2])
                    && (0xAA == out_report_data[3])
                    && (0x00 == out_report_data[4])
                    && (0xFF == out_report_data[5]))
                {
				    bjump_boot = true;
					clear_in_fifo();
					in_report_data[0x00] = iHID_CMD_HANDLE;
					in_report_data[0x01] = iHID_CMD_SYS_CTRL|iHID_CMD_ISP;
					in_report_data[0x02] = 0x01;
                    m_data_flag |= bhid_data_send;
                }
            }
            else if(iHID_CMD_RESET == (out_report_data[1]&iHID_CMD_KEY_CFG_MASK))
            {
                if(iDEVICE_TYPE_24G == device_type)
                {
                    if(0 != (OM_PMU->SW_RSVD1&PMU_SW_RSVD1_RESET))
                    {
                        hid_get_fw_mode_info();
                        return;
                    }
                    OM_PMU->SW_RSVD1 |= PMU_SW_RSVD1_RESET;
                }

                if((0x55 == out_report_data[2])
                    && (0xAA == out_report_data[3]))
                {
                    delayus(5000);
                    OM_RCC->USB_CTRL = 0;           // disconnect

                    flash_erase(iKEY_MODE0_BANK);
                    flash_erase(iKEY_MODE1_BANK);
                    flash_erase(iKEY_MODE2_BANK);
                    flash_erase(iKEY_MODE3_BANK);

                    flash_erase(iCFG_BANK);
                    flash_erase(iFLASH_STATUS_BANK);
                    flash_erase(iFLASH_CFG_DPI_BANK);

                    laod_defaut_status();
                    device_type = bt_index;
                    flash_save_status();

                    delayus(10000);
                    NVIC_SystemReset();
                }
                else
                {
                    hid_cmd_fcc_test();
                }
            }
            else
            {
                hid_write_read_err();
            }
        }
        else if(iHID_CMD_DEVICE_STATUS == (out_report_data[1]&iHID_CMD_MASK))
        {
            if(iHID_CMD_MODE_INFO == out_report_data[1])
            {
//----------------------------------------------
// 模式配置
                if(out_report_data[2]&(1<<7))
                {
                    laod_flash_cfg();
                }
                if(out_report_data[2]&(1<<5))
                {                               // 设置当前模式
                    if((out_report_data[2]&0x03) != key_mode)
                    {
                        key_mode = (out_report_data[2]&0x03);
                        bkey_mode_change = true;
                        bsave_status = true;
                    }
                }
//----------------------------------------------
// 设置高级配置
                if(out_report_data[2]&(1<<6))
                {                               // 
                    if(out_report_data[0x0C] != sleep_time_24g)
                    {
                        sleep_time_24g = out_report_data[0x0C];
                        bsave_cfg_dpi = true;
                    }
                    if(out_report_data[0x0D] != sleep_time_ble)
                    {
                        sleep_time_ble = out_report_data[0x0D];
                        bsave_cfg_dpi = true;
                    }

                    if(((out_report_data[0x0F]<<8)|out_report_data[0x0E]) != adv_cfg_value)
                    {
                        adv_cfg_value = ((out_report_data[0x0F]<<8)|out_report_data[0x0E]);

                        mouse_lod_set = ((out_report_data[0x0E]>>0)&0x03);
                        key_delay_set = key_delay_tbl[((out_report_data[0x0E]>>2)&0x03)];
                        bsave_cfg_dpi = true;
                    }
                }
//----------------------------------------------
// DPI配置
//                if(out_report_data[3]&(1<<0))
//                {                               // 设置当前DPI
//                    if((out_report_data[4]&0x07) != (report_dpi[0]&0x07))
//                    {
//                        report_dpi[0] &= 0xF8;
//                        report_dpi[0] |= (out_report_data[4]&0x07);
//                        bsave_status = true;
//                    }
//                }
//                if(out_report_data[3]&(1<<1))
//                {                               // 设置当前DPI
//                    if((out_report_data[5]&0x07) != (report_dpi[1]&0x07))
//                    {
//                        report_dpi[1] &= 0xF8;
//                        report_dpi[1] |= (out_report_data[5]&0x07);
//                        bsave_status = true;
//                    }
//                }
//                if(out_report_data[3]&(1<<2))
//                {                               // 设置当前DPI
//                    if((out_report_data[6]&0x07) != (report_dpi[2]&0x07))
//                    {
//                        report_dpi[2] &= 0xF8;
//                        report_dpi[2] |= (out_report_data[6]&0x07);
//                        bsave_status = true;
//                    }
//                }
//                if(out_report_data[3]&(1<<3))
//                {                               // 设置当前DPI
//                    if((out_report_data[7]&0x07) != (report_dpi[3]&0x07))
//                    {
//                        report_dpi[3] &= 0xF8;
//                        report_dpi[3] |= (out_report_data[7]&0x07);
//                        bsave_status = true;
//                    }
//                }
//----------------------------------------------
// 报告率配置
                if(out_report_data[3]&(1<<4))
                {                               //
                    if((out_report_data[4]&0xF0) != report_dpi[0])
                    {
                        report_dpi[0] &= 0x0F;
                        report_dpi[0] |= (out_report_data[4]&0xF0);
                        bsave_status = true;
                    }
                }
                if(out_report_data[3]&(1<<5))
                {                               //
                    if((out_report_data[5]&0xF0) != report_dpi[1])
                    {
                        report_dpi[1] &= 0x0F;
                        report_dpi[1] |= (out_report_data[5]&0xF0);
                        bsave_status = true;
                    }
                }
                if(out_report_data[3]&(1<<6))
                {                               //
                    if((out_report_data[6]&0xF0) != report_dpi[2])
                    {
                        report_dpi[2] &= 0x0F;
                        report_dpi[2] |= (out_report_data[6]&0xF0);
                        bsave_status = true;
                    }
                }
                if(out_report_data[3]&(1<<7))
                {                               //
                    if((out_report_data[6]&0xF0) != report_dpi[2])
                    {
                        report_dpi[3] &= 0x0F;
                        report_dpi[3] |= (out_report_data[7]&0xF0);
                        bsave_status = true;
                    }
                }
                report_24g = ((report_dpi[0]>>4)&0x03);
                if(adv_cfg_value&iPOWER_LOW)
                    report_24g = iREPORT_125;
                report_usb = ((report_dpi[0]>>6)&0x03);

//----------------------------------------------
// 灯光配置
                if(out_report_data[8]&(1<<7))
                {				                // 设置模式
					if((iMODE_LED_MAX >= (out_report_data[8]&0x1F))
					    &&(led_cur_mode != (out_report_data[8]&0x1F)))
                    {
					    led_cur_mode = (out_report_data[8]&0x1F);
                        bsave_status = true;
					}

                    if(out_report_data[8]&(1<<6))
                    {
                        if(false == bled_bright_en)
                        {
                            bled_bright_en = true;
                            bsave_status = true;
                        }
                    }
                    else
                    {
                        if(true == bled_bright_en)
                        {
                            bled_bright_en = false;
                            bsave_status = true;
                        }
                    }
				}
                if(out_report_data[0x0A]&(1<<3))
                {				                // led亮度
                    if(((out_report_data[10])&0x07) != led_light_lev)
                    {
                        led_light_lev = (out_report_data[0x0A]&0x07);
                        bsave_cfg_dpi = true;
                    }
				}
                if(out_report_data[0x0A]&(1<<7))
                {				                // led速度
                    if(((out_report_data[0x0A]>>4)&0x07) != led_speed_lev)
                    {
                        led_speed_lev = ((out_report_data[0x0A]>>4)&0x07);
                        bsave_cfg_dpi = true;
                    }
				}
                if(out_report_data[0x0B]&(1<<3))
                {				                // rgb颜色
                    if((out_report_data[0x0B]&0x07) != led_rgb_index)
                    {
                        led_rgb_index = (out_report_data[0x0B]&0x07);
                        led_mode_bak = iLOGO_INVALID;
                        bsave_cfg_dpi = true;
                    }
				}

                hid_get_fw_mode_info();
                m_data_flag |= bhid_data_send;
            }
            else if(iHID_CMD_DEVICE_INFO == out_report_data[1])
            {
                clear_in_fifo();
                in_report_data[0x00] = iHID_CMD_HANDLE;
                in_report_data[0x01] = iHID_CMD_DEVICE_STATUS|iHID_CMD_DEVICE_INFO;

                memcpy(flash_fifo, (uint8_t *)0x00000010, 16);
                in_report_data[0x0E] = flash_fifo[3];
                in_report_data[0x0F] = flash_fifo[2];
                in_report_data[0x10] = flash_fifo[1];
                in_report_data[0x11] = flash_fifo[0];
                memcpy(in_report_data+0x12, flash_fifo+4, 12);

                m_data_flag |= bhid_data_send;
            }
            else if(iHID_CMD_DPI_CTRL == out_report_data[1])
            {
                clear_in_fifo();
                in_report_data[0x00] = iHID_CMD_HANDLE;
                in_report_data[0x01] = iHID_CMD_DEVICE_STATUS|iHID_CMD_DPI_CTRL;

                m_data_flag |= bhid_data_send;
            }
            else if(iHID_CMD_DEF_KEY == out_report_data[1])
            {
                clear_in_fifo();
                in_report_data[0x00] = iHID_CMD_HANDLE;
                in_report_data[0x01] = iHID_CMD_DEVICE_STATUS|iHID_CMD_DEF_KEY;

                memcpy(in_report_data+0x02, def_key_dat, 24);
                memcpy(in_report_data+26, para_cfg_dat, 5);

                m_data_flag |= bhid_data_send;
            }
            else
            {
                hid_write_read_err();
            }
        }
        else
        {
            hid_write_read_err();
        }
    }
}
