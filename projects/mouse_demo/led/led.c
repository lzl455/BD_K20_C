/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: led.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include <string.h>
#include "om_driver.h"

#include "main.h"
#include "lvd.h"
#include "led.h"
#include "exLed.h"

#include "flash.h"
#include "flash_process.h"
#include "usb_cfg_info.h"
#include "matrix_key.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
bool                            bdevice_led_status;
bool                            bled_bright_en;
bool                            bback_led_status;
bool                            bargb_valid;

uint8_t                         gtemp_i;
uint8_t                         gtemp_j;
uint8_t                         gtemp_x;

uint8_t                         device_conn_index=0;
uint8_t                         device_hint_count;

uint8_t                         led_hint_mode;
uint8_t                         led_mode_bak;

uint8_t                         logo_hint_time_count;
uint8_t                         rgb_enable;

uint8_t                         pwm_value;
uint8_t                         pwm_count;

uint8_t                         nhjb_led_index;

uint16_t                        flash_on_time;
uint16_t                        flash_off_time;
uint32_t                        led_delay_count;


uint16_t                        led_ctrl_reg;
uint16_t                        led_status_reg;
uint8_t                         led_use_flag;

uint8_t                         led_cur_mode;
uint8_t                         led_pre_mode;
enum speed_level                led_speed_lev;
unsigned char                   led_rgb_index;
unsigned char                   pwm_value;
enum led_level                  led_light_lev;

uint8_t                         pwm_time_count;
uint16_t                        delay_time_count;
uint8_t                         rgb_index;
uint8_t                         led_process_index;
uint8_t                         hint_time_count;

__ALIGNED(4) uint8_t            pwm_rgb_tbl[iLED_MAX][3];

uint8_t                         pwm_duty_array_0[0x10];
uint8_t                         pwm_duty_array_1[0x10];
uint8_t                         pwm_duty_array_2[0x10];
uint8_t                         pwm_duty_array_3[0x10];

uint32_t                        exled_rtc_count=0;

extern bool                     b24g_nromal;

//=============================================================================;
// 代码区                                                                       ;
//=============================================================================;

/*******************************************************************************
* 函数名称: ledc_init()
* 功能描述:
* 输入参数： 无
* 输出参数： 无
* 说    明:
*******************************************************************************/
void ledc_init(void)
{
    ledc_config_t config = {
        .reset_cycles         = 100,
        .long_pulse_cycles    = 28,
        .short_pulse_cycles   = 14,
    };
    drv_ledc_init(OM_LEDC, &config);
    bargb_valid = true;
}

/******************************************************************************
* 函数名称: led_status_hint
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_status_hint(void)
{
    mLED_VDD_DIS;
	if(hint_led_status&bled_hint_mode)
    {
        if(hint_led_status&bled_num)
        {
            mLED_NUM_LOW;
        }
        else
        {
            mLED_NUM_HIGH;
        }
        if(hint_led_status&bled_caps)
        {
            mLED_CAPS_LOW;
        }
        else
        {
            mLED_CAPS_HIGH;
        }
        if(hint_led_status&bled_win_lock)
        {
            mLED_WIN_LOW;
        }
        else
        {
            mLED_WIN_HIGH;
        }

        if(0==(hint_led_status&(bled_num|bled_caps|bled_win_lock)))
            return;
    }
    else
    {
        if(kb_led_status&bnum_lock)
        {
            mLED_NUM_LOW;
        }
        else
        {
            mLED_NUM_HIGH;
        }

        if(kb_led_status&bcaps_lock)
        {
            mLED_CAPS_LOW;
        }
        else
        {
            mLED_CAPS_HIGH;
        }

        if((key_ctrl&bwin_mac_sataus) && (key_ctrl&bwin_lock_status))
        {
            mLED_WIN_LOW;
        }
        else
        {
            mLED_WIN_HIGH;
        }
    }
    mLED_VDD_EN;
}

/*******************************************************************************
* 函数名称: device_led_on()
* 功能描述:
* 输入参数： 无
* 输出参数： 无
* 说    明:
*******************************************************************************/
void device_led_on(void)
{
    exled &= ~(bled_K3|bled_K6|bled_K7);

    if(iDEVICE_TYPE_BT0 == device_type)
        exled |= bled_K6;
    else if(iDEVICE_TYPE_BT1 == device_type)
        exled |= bled_K7;
    else if(iDEVICE_TYPE_24G == device_type)
        exled |= bled_K3;
}

/*******************************************************************************
* 函数名称: device_led_off()
* 功能描述:
* 输入参数： 无
* 输出参数： 无
* 说    明:
*******************************************************************************/
void device_led_off(void)
{
    exled &= ~(bled_K3|bled_K6|bled_K7);
}

void logo_off(void)
{
    bargb_valid = false;

    DRV_RCC_CLOCK_ENABLE(RCC_CLK_LEDC, 0U);
    OM_GPIO0->DATAOUTSET = (1<<ARGB_OUT_PIN);
    if(0xFF != exio_ctrl)
    {
        exled_rtc_count=0;
        exio_ctrl = 0xFF;
    }
}

void clr_rgb(void)
{
    memset(pwm_rgb_tbl, 0x00, iLED_MAX*3);
}

void rgb_pwm0_w(void)
{
    if(rgb_enable&iPWM_R)
         pwm_rgb_tbl[gtemp_j][iR_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iR_INDEX] = 0;
    if(rgb_enable&iPWM_G)
         pwm_rgb_tbl[gtemp_j][iG_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iG_INDEX] = 0;
    if(rgb_enable&iPWM_B)
         pwm_rgb_tbl[gtemp_j][iB_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iB_INDEX] = 0;          
}

void rgb_w_max(void)
{
    if(rgb_enable&iPWM_R)
        pwm_rgb_tbl[gtemp_j][iR_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iR_INDEX] = 0;
    if(rgb_enable&iPWM_G)
        pwm_rgb_tbl[gtemp_j][iG_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iG_INDEX] = 0;
    if(rgb_enable&iPWM_B)
        pwm_rgb_tbl[gtemp_j][iB_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iB_INDEX] = 0;
}

extern void key_into_fcc_test(void);

/******************************************************************************
* 函数名称: logo_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void device_led_process(void)
{
//-----------------------------------------------------------------------------
// 模式提示
//
    if(0 != hint_time_count)
    {
        hint_led_status |= bled_hint_mode;
        if(0 != (hint_time_count&0x08))
        {
            bdevice_led_status = true;
            hint_led_status |= (bled_num|bled_caps|bled_win_lock);
        }
        else
        {
            hint_led_status &= ~(bled_num|bled_caps|bled_win_lock);
        }

        hint_time_count--;
        if(2>hint_time_count)
        {
            hint_time_count = 0;
            hint_led_status = 0x00;
        }

        return;
    }

    rtc_cur_value = drv_rtc_read(OM_RTC);
    if(iDEVICE_TYPE_USB != device_type)
    {
        if(ble_24g_ctrl & bom6239_conning)
        {
            if(0 == device_conn_index)
            {
                device_conn_index++;
                led_delay_count = rtc_cur_value;
            }
            else if(1 == device_conn_index)
            {
                if(ble_24g_ctrl&bom6239_conn_ok)
                {
                    device_conn_index++;
                    led_delay_count = rtc_cur_value;
                    device_hint_count = 0;
                }

                key_into_fcc_test();
                if(false == bdevice_led_status)
                {
                    device_led_off();
                    if(mMS_TO_TICK(250) < (rtc_cur_value - led_delay_count))
                    {
                        exled_rtc_count=0;
                        bdevice_led_status = true;
                        led_delay_count = rtc_cur_value;
                    }
                }
                else
                {
                    device_led_on();
                    if(mMS_TO_TICK(250) < (rtc_cur_value - led_delay_count))
                    {
                        exled_rtc_count=0;
                        bdevice_led_status = false;
                        led_delay_count = rtc_cur_value;
                    }
                }
            }
            else if(2 == device_conn_index)
            {
                device_conn_index = 0;
                ble_24g_ctrl &= ~bom6239_conning;
            }
            return;
        }
        else if(ble_24g_ctrl&bom6239_sync_ing)
        {
            if(true == b24g_nromal)
                return;

            if(0 == device_conn_index)
            {
                device_conn_index++;
                led_delay_count = rtc_cur_value;
            }
            else if(1 == device_conn_index)
            {
                if(ble_24g_ctrl&bom6239_sync_ok)
                {
                    device_conn_index++;
                    led_delay_count = rtc_cur_value;
                    device_hint_count = 0;
                }

                if(false == bdevice_led_status)
                {
                    device_led_off();
                    if(mMS_TO_TICK(1000) < (rtc_cur_value - led_delay_count))
                    {
                        exled_rtc_count=0;
                        bdevice_led_status = true;
                        led_delay_count = rtc_cur_value;
                    }
                }
                else
                {
                    device_led_on();
                    if(mMS_TO_TICK(1000) < (rtc_cur_value - led_delay_count))
                    {
                        exled_rtc_count=0;
                        bdevice_led_status = false;
                        led_delay_count = rtc_cur_value;
                    }
                }
            }
            else if(2 == device_conn_index)
            {
                device_conn_index = 0;
                ble_24g_ctrl &= ~bom6239_sync_ing;
            }
            return;
        }

        device_led_on();
        device_conn_index = 0;
    }
    else
    {
        device_led_off();
        if(0 != (usb_ctrl_flag&busb_suspend_resume))
            return;
    }
}

/******************************************************************************
* 函数名称: logo_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void logo_process(void)
{
    uint8_t i;
    uint32_t rtc_temp;

    rtc_temp = drv_rtc_read(OM_RTC);
    if((mMS_TO_TICK(500) < (rtc_temp-exled_rtc_count))||(0 == exled_rtc_count))
    {
        exled_rtc_count = rtc_temp;
        exLogo_send();
    }

    if(true==bsave_status)
    {
        bsave_status = false;
        flash_save_status();
    }
    if(true==bsave_cfg_dpi)
    {
        bsave_cfg_dpi = false;
        flash_save_cfg_dpi();
    }
    if(iDEVICE_TYPE_24G == device_type)
    {
        if(true==bflash_ctrl)
            return;
    }

    if(iDEVICE_TYPE_USB == device_type)
    {
        if(0 != (usb_ctrl_flag&busb_suspend_resume))
        {
            logo_off();
            return;
        }
    }
    else
    {
        if(ble_24g_ctrl&bom6239_sync_ing)
        {
            logo_off();
            return;
        }
    }

    if((false == bled_bright_en) || (iLED_LEV_MIN==led_light_lev) || (iLOW_POWER>=bat_value))
    {
        clr_rgb();
        logo_off();
        return;
    }

    if(false==bargb_valid)
    {
        ledc_init();
        OM_GPIO0->DATAOUTCLR = (1<<ARGB_OUT_PIN);
    }
    if(0 != exio_ctrl)
    {
        exio_ctrl = 0;
        exled_rtc_count=0;
    }

    if(led_pre_mode != led_cur_mode)
    {
        led_pre_mode = led_cur_mode;

        led_process_index = 0;
        rgb_index = 0;

        clr_rgb();
        memset(pwm_duty_array_0, 0x00, 16);
        memset(pwm_duty_array_1, 0x00, 16);
        memset(pwm_duty_array_2, 0x00, 16);
        memset(pwm_duty_array_3, 0x00, 16);

        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:

                break;
            case iMODE_LED_ON:

                break;
            case iMODE_LED_BREATH:
                pwm_time_count = 0;
                delay_time_count = 0xFF;
                rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];

                break;
            case iMODE_LED_SNAKE:
                snake_led_index = 4;
                pwm_duty_array_0[4] = ((iPWM_MAX*4)/4);

                break;
            case iMODE_LED_NHJB:
                delay_time_count = 0;
                pwm_duty_array_0[0] = iPWM_MAX;
                pwm_duty_array_0[1] = 0x00;
                pwm_duty_array_0[2] = 0x00;

                break;
            case iMODE_LED_LG_L_R:
                delay_time_count = 0;
                led_status_reg = 0xCCCC;

                for(i=0; i<iLED_MAX; i++)
                {
                    pwm_duty_array_0[i] = led_liuguang_l_r_tbl[i];
                    pwm_duty_array_1[i] = led_liuguang_rgb_tbl[i];
                }

                break;
            case iMODE_LED_STAR:
                delay_time_count = 0;
                snake_led_index = 0xFF;
                lfsr_value = 0x55AA;
                break;
            case iMODE_LED_SBZL:
                for(i=0; i<iLED_MAX; i++)
                {
                    pwm_duty_array_0[i] = sbzl_r_tbl[iLED_MAX-1-i];
                    pwm_duty_array_1[i] = sbzl_g_tbl[iLED_MAX-1-i];
                    pwm_duty_array_2[i] = sbzl_b_tbl[iLED_MAX-1-i];
                    pwm_duty_array_3[i] = sbzl_ctrl_tbl[iLED_MAX-1-i];
                }
                break;
            case iMODE_LED_BS:
                break;
            case iMODE_LED_QCNH:
                break;
            case iMODE_LED_LHTW:
                break;
            case iMODE_LED_DXTW:
                snake_led_index = 3;
                pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
                break;
            case iMODE_LED_SXTW:
                snake_led_index = 3;
                pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
                bback_led_status = 0;
                break;
            case iMODE_LED_TXTW:
            case iMODE_LED_FXTW:
                snake_led_index = 3;
                pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
                break;
            case iMODE_LED_JG:
                led_use_flag = 0;
                break;
        }
    }
    else
    {
        //bled_hint_ing = 1;

        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:
                break;
            case iMODE_LED_ON:
                led_mode_on();
                break;
            case iMODE_LED_BREATH:
                led_mode_breath();
                break;
            case iMODE_LED_SNAKE:
                led_mode_snake();
                break;
            case iMODE_LED_NHJB:
                led_mode_nhjb();
                break;
            case iMODE_LED_LG_L_R:
                led_mode_liuguang();
                break;
            case iMODE_LED_STAR:
                led_mode_star();
                break;
            case iMODE_LED_SBZL:
                led_mode_sbzl();
                break;
            case iMODE_LED_BS:
                led_mode_baoshan();
                break;
            case iMODE_LED_QCNH:
                led_mode_qcnh();
                break;
            case iMODE_LED_LHTW:
                led_mode_lhtw();
                break;
            case iMODE_LED_DXTW:
                led_mode_dxtw();
                break;
            case iMODE_LED_SXTW:
                led_mode_sxtw();
                break;
            case iMODE_LED_TXTW:
            case iMODE_LED_FXTW:
                led_mode_txtw();
                break;
        }
    }
}
