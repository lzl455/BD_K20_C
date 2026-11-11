/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.c
*
* 功能说明:
* 修改说明:
POFCON bit(7~4):低电压门限值设置位。
				0000:0.8v			0001:0.9v			0010:1.0v
				0011:1.1v			0100:1.2v			0101:1.4v
				0110:1.7v			0111:1.8v			1000:1.9v
				1001:2.0v			1010:2.1v			1011:2.2v
				1100:2.4v			1101:2.7v
POFCON bit(3):POF使能位，1为使能，0为不使能。
POFCON bit(2~1):LVD检测脚设置。00对应P00，01对应P05，10对应P07，11对应P13。
POFCON bit(0):低电压指示标志位，低于门限值时为低电平，否则为高电平。
*******************************************************************************/
#include "om_driver.h"
#include "main.h"
#include "led.h"
#include "exLed.h"
#include "lvd.h"
#include "time_delay.h"
#include "flash_process.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//
#define iLED_0                      0x3F
#define iLED_1                      0x06
#define iLED_2                      0x5B
#define iLED_3                      0x4F
#define iLED_4                      0x66
#define iLED_5                      0x6D
#define iLED_6                      0x7D
#define iLED_7                      0x07
#define iLED_8                      0x7F
#define iLED_9                      0x6F

#define	mPOF_ENABLE     		OM_POF->POFCON |= 0x08
#define	mPOF_DISABLE     		OM_POF->POFCON &= ~0x08

#define	mPOF_WARM_READ     		(OM_POF->POFCON & 0x01)

//-----------------------------------------------------------------------------;
// 变量定义区
//
uint8_t                         bat_status;
uint8_t                         lvd_value;          // lvd检测值
uint8_t                         bat_value;          // 百分比值

bool                            bkey_bat_update;
bool                            bbat_update;
bool                            bbat_check_scan;
bool                            bcharging_bak;

uint8_t                         lvd_scan_count;
uint16_t                        bat_power_delay;
uint16_t                        led_hint_time_count;
uint16_t                        power_off_time_count;
unsigned char                   charge_ok_delay_count;

uint32_t                        lvd_hint_time_count;
uint32_t                        charge_time_count;
uint16_t                        threshold;

//-----------------------------------------------------------------------------;
// 表格定义区
//
unsigned char const led_no_tbl[] = {
    iLED_0,
    iLED_1,
    iLED_2,
    iLED_3,
    iLED_4,
    iLED_5,
    iLED_6,
    iLED_7,
    iLED_8,
    iLED_9,
};

//----------------------------------------------
// 锂电池：上拉2M，下拉1M
//
unsigned char           const    bat_li_value_tbl[] =
{
    0,
    5,
    10,
    20,
    40,
    60,
    80,
    100,
};

unsigned char           const    bat_li_value_a3_tbl[] =
{
    0,                  // 0
    5,                  // 1
    10,                 // 2
    15,                 // 3
    20,                 // 4
    30,                 // 5
    40,                 // 6
    50,                 // 7
    60,                 // 8
    70,                 // 9
    80,                 // 10
    90,                 // 11
    100,                // 12
    100,
    100,
    100,
};

#define mPOF_SET                 {OM_POF->POFCON &= ~0x1F0;\
                                    OM_POF->POFCON |= threshold;}

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: bat_voltage_check
* 功能描述: 检测电池节数
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
__RAM_CODE void lvd_check(void)
{
    unsigned char i;

    for(i=0; i<7; i++)
    {
        mPOF_SET;
        mPOF_ENABLE;
        delayus(5);
        if(0 != mPOF_WARM_READ)
            break;
        if(0 == threshold)
            break;
        threshold -= 0x10;
    }
}

/******************************************************************************
* 函数名称: bat_voltage_check
* 功能描述: 检测电池节数
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
__RAM_CODE unsigned char bat_voltage_check(void)
{
    unsigned char i;

    // POF_LVD_PIN_P23   POF_LVD_PIN_P33   POF_LVD_PIN_VBUS   POF_LVD_PIN_VDD
	OM_POF->POFCON &= ~0x0E;
	OM_POF->POFCON |= (POF_LVD_PIN_P33 << 1);

    threshold = POF_THRESHOLD_1_225V;
    mPOF_SET;
	mPOF_ENABLE;
    delayus(8);
    if(0 != mPOF_WARM_READ)
    {                                           // 大于 1.225v
        threshold = POF_THRESHOLD_1_400V;
        mPOF_SET;
        mPOF_ENABLE;
        delayus(8);
        if(0 != mPOF_WARM_READ)
        {                                       // 大于 1.400v
            threshold = POF_THRESHOLD_1_550V;
            lvd_check();
        }
        else
        {                                       // 小于 1.400v
            threshold = POF_THRESHOLD_1_400V;
            lvd_check();
        }
    }
    else
    {                                           // 小于 1.225v
        threshold = POF_THRESHOLD_1_050V;
        mPOF_SET;
        mPOF_ENABLE;
        delayus(8);                             // A2 1.20v   A3 1.050v
        if(0 != mPOF_WARM_READ)
        {                                       // 大于 1.050v
            threshold = POF_THRESHOLD_1_225V;
            lvd_check();
        }
        else
        {                                       // 小于 1.050v
            threshold = POF_THRESHOLD_1_050V;
            lvd_check();
        }
    }
    mPOF_DISABLE;

    i = ((threshold>>4)+1);
    return i;
}

/******************************************************************************
* 函数名称: bat_init
* 功能描述: 检测电池节数
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void bat_init(void)
{
    bat_status |= blvd_power_on;
    charge_time_count = 0;
}

/******************************************************************************
* 函数名称: bat_level_cal
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
__RAM_CODE uint8_t bat_level_cal(uint8_t bat_level)
{
    if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
    {
        if(iLVD_0_VALUE_A3>=bat_level)
            bat_level = 0;
        else if(iLVD_100_VALUE_A3<=bat_level)
            bat_level = 100;
        else
            bat_level = bat_li_value_a3_tbl[(bat_level-iLVD_0_VALUE_A3)&0x0F];
    }
    else
    {
        if(iLVD_0_VALUE>=bat_level)
            bat_level = 0;
        else if(iLVD_100_VALUE<=bat_level)
            bat_level = 100;
        else
            bat_level = bat_li_value_tbl[(bat_level-iLVD_0_VALUE)&0x07];
    }

    return bat_level;
}

/******************************************************************************
* 函数名称: bat_check
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
__RAM_CODE void bat_check(void)
{
    uint8_t bat_dat, bat_temp;

    bat_status &= ~(bcharge_ok|bcharging);
    if(0 != USB_5V_PIN)
        bat_status |= bcharging;
    if(0 != CHR_OK_PIN)
        bat_status |= bcharge_ok;

    bat_dat = bat_voltage_check();

    if(0 != (bat_status&blvd_power_on))
    {
        if(0x1F == (bat_status&0x1F))
        {                                       // 存储的是无效值，加载当前值
            if(1000>sys_tick_count)
                return;
            bat_status &= 0xE0;
            bat_status |= bat_dat;
            bsave_status = true;
            bbat_update = true;
        }
        bat_status &= ~blvd_power_on;

        lvd_value = (bat_status&0x1F);
        bat_value = bat_level_cal(lvd_value);
        return;
    }

    if(0 != (bat_status&bcharging))
    {                                           // 充电中
        if(bat_dat > lvd_value)
        {
            bat_power_delay++;
            if(0 != (bat_status&bcharge_ok))
            {                                   // 充电完成
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value = iLVD_100_VALUE_A3;
                else
                    lvd_value = iLVD_100_VALUE;

                if(100 != bat_value)
                {
                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = 100;
                    bsave_status = true;
                    bbat_update = true;
                }
            }
            else if((5*64) < bat_power_delay)
            {
                bat_power_delay=0;

                uint8_t lvd_value_temp;
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value_temp = iLVD_90_VALUE_A3;
                else
                    lvd_value_temp = iLVD_90_VALUE;

                if(lvd_value_temp>lvd_value)
                {
                    lvd_value++;

                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = bat_level_cal(lvd_value);
                    bsave_status = true;
                    bbat_update = true;
                }
            }
        }
    }
    else
    {
        if(bat_dat < lvd_value)
        {
            bat_power_delay++;
            if((5*64) < bat_power_delay)
            {
                bat_power_delay=0;

                uint8_t lvd_value_temp;
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value_temp = iLVD_0_VALUE_A3;
                else
                    lvd_value_temp = iLVD_0_VALUE;

                if(lvd_value_temp < lvd_value)
                {
                    lvd_value--;

                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = bat_level_cal(lvd_value);
                    bsave_status = true;
                    bbat_update = true;
                }
            }
        }
    }
}

/******************************************************************************
* 函数名称: led_hint_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_hint_process(void)
{
    uint8_t i;

    rtc_cur_value = drv_rtc_read(OM_RTC);
    bat_check();
    if(0 != (bat_status&blvd_power_on))
        return;

    exled &= 0xFFE00000;
    if(100 == bat_value)
    {
        exled |= (0x000BFFBF);
    }
    else
    {
        i = led_no_tbl[bat_value/10];
        exled |= i;
        if(i&(1<<4))
            exled |= bled_1_E;

        i = led_no_tbl[bat_value%10];
        if(i&(1<<0))
            exled |= bled_2_A;
        if(i&(1<<1))
            exled |= bled_2_B;
        if(i&(1<<2))
            exled |= bled_2_C;
        if(i&(1<<3))
            exled |= bled_2_D;
        if(i&(1<<4))
            exled |= bled_2_E;
        if(i&(1<<5))
            exled |= bled_2_F;
        if(i&(1<<6))
            exled |= bled_2_G;
    }

    exled |= bled_K5;    // %

    if(0 == (bat_status&bcharging))
    {
	    exled &= ~bled_K4;
        if(iLOW_POWER >= bat_value)
        {
            if(exled&bled_K2)
            {
                exled |= bled_K2;
                if(mMS_TO_TICK(500) < (rtc_cur_value - lvd_hint_time_count))
                {
                    exled &= ~bled_K2;
                    lvd_hint_time_count = rtc_cur_value;
                    exled_rtc_count=0;
                }
            }
            else
            {
                exled &= ~bled_K2;
                if(mMS_TO_TICK(1500) < (rtc_cur_value - lvd_hint_time_count))
                {
                    exled |= bled_K2;
                    lvd_hint_time_count = rtc_cur_value;
                    exled_rtc_count=0;
                }
            }

            if(0<bat_value)
			    return;

		    power_off_time_count++;				// 时间单位16ms
            if(600 > power_off_time_count)		// 10s
			    return;

            logo_off();
            exled_ctrl = 0x02;
            exLogo_send();

            OM_PMU->SW_RSVD1 |= PMU_SW_RSVD1_POWER_OFF;
            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL2);
            drv_pmu_set_low_power_mode(PMU_LPM_DEEP_SLEEP);
        }
        else
        {
            lvd_hint_time_count = 0;
            power_off_time_count = 0;
	        exled &= ~bled_K2;
        }
    }
    else
    {
	    exled &= ~bled_K2;
        lvd_hint_time_count = 0;
        if(0 != (bat_status&bcharge_ok))
		{									// 充电完成
            if(0!=charge_ok_delay_count)
            {
                charge_ok_delay_count--;
                return;
            }

            power_off_time_count = 0;
            exled &= ~bled_K4;
        }
        else
        {									// 充电中
            exled |= bled_K4;
            charge_ok_delay_count = 200;
        }
    }
}
