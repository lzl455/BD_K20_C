/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: wheel.c
*
* 功能说明: 滚轮扫描处理
* 修改说明:
*******************************************************************************/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "om_driver.h"

#include "main.h"
#include "wheel.h"
#include "led.h"

#include "key_code_define.h"
#include "flash_process.h"
#include "hid_process.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
bool                        bwheel_mode_swtich;
uint8_t                     wheel_status;
uint32_t                    wheel_press_time_count;

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/*******************************************************************************
* 函数名称: wheel_scan()
* 功能描述: 滚轮扫描处理
* 输入参数：无
* 输出参数：无
* 说    明:
*******************************************************************************/
void wheel_scan(void)
{
    if(OM_ENCODER->VALID&ENCODER_VALID_CNT_MASK)
    {
        wheel_data = OM_ENCODER->CNT;
        if(wheel_data & 0x08)
            wheel_data |= 0xf0;
        else
            wheel_data &= 0x0f;
    }

    rtc_cur_value = drv_rtc_read(OM_RTC);
    if(0==(wheel_status&bwheel_press))
    {
        bwheel_mode_swtich = false;
        if(0!=(wheel_status&bwheel_press_bak))
        {
            wheel_status &= ~bwheel_press_bak;

            if(mMS_TO_TICK(1000) > (rtc_cur_value - wheel_press_time_count))
            {
                wheel_press_time_count = 0;
                if(0 ==(wheel_status&bwheel_mode))
                {
                    mmk_data_l = iMMK_MUTE_L;
                    mmk_data_h = iMMK_MUTE_H;

                    m_data_flag |= bmmk_data_send;
                    mmk_tx_count = 8;
                }
                else
                {
                    led_cur_mode++;
                    if(iMODE_LED_MAX<led_cur_mode)
                        led_cur_mode = iMODE_LED_ON;
                    bsave_status = true;
                }
            }
        }
    }
    else
    {
        if(0==(wheel_status&bwheel_press_bak))
        {
            wheel_status |= bwheel_press_bak;
            wheel_press_time_count = rtc_cur_value;
        }
        else
        {
            if(mMS_TO_TICK(3000) < (rtc_cur_value - wheel_press_time_count))
            {
                if(false == bwheel_mode_swtich)
                {
                    bwheel_mode_swtich = true;
                    wheel_status ^= bwheel_mode;
                    bsave_status = true;

                    if(0 == hint_time_count)
                        hint_time_count = 0x37;
                }
		    }
        }
    }

    if(0 != wheel_data)
	{
        if(0 ==(wheel_status&bwheel_mode))
        {
            if(0==(m_data_flag&bmmk_data_send))
            {
                if(0!=(wheel_data&(1<<7)))
                {
                    mmk_data_l = iMMK_VOLUMEDOWN_L;
                    mmk_data_h = iMMK_VOLUMEDOWN_H;
                    wheel_data++;
                }
                else
                {
                     mmk_data_l = iMMK_VOLUMEUP_L;
                     mmk_data_h = iMMK_VOLUMEUP_H;
                     wheel_data--;
                }
                m_data_flag |= bmmk_data_send;
                mmk_tx_count = 8;
            }
        }
        else
        {
            if(false==bled_bright_en)
			{
            	wheel_data = 0;
    			return;
			}

            if(0!=(wheel_data&(1<<7)))
            {
                if(led_light_lev > iLED_LEV_MIN)
                {
                    led_light_lev--;
                    hid_ctrl_reg |= bdevice_status_change;
                    bsave_status = true;
                }
                else
                {
                    if(0 == hint_time_count)
                        hint_time_count = 0x37;
                }
            }
            else
            {
                if(led_light_lev < iLED_LEV_MAX)
                {
                    led_light_lev++;
                    hid_ctrl_reg |= bdevice_status_change;
                    bsave_status = true;
                }
                else
                {
                    led_light_lev = iLED_LEV_MAX;
                    if(0 == hint_time_count)
                        hint_time_count = 0x37;
                }
            }

            wheel_data = 0;
        }
    }
}
