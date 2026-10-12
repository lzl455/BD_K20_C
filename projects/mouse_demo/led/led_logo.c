/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include "..\defines.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
USBD_U16                        uled_ctrl_reg;
USBD_U8                         uled_status_reg;
USBD_U8                         uled_use_flag;

enum led_mod                    led_cur_mode;
enum led_mod                    led_pre_mode;
enum speed_level                led_speed_lev;
unsigned char                   led_rgb_index;
unsigned char                   pwm_value;
enum led_level                  led_light_lev;

unsigned char                   pwm_time_count;
unsigned int                    delay_time_count;
unsigned int                    mode_swtich_time_count;
USBD_U8                         urgb_enable;
unsigned char                   rgb_index;
unsigned char                   led_process_index;

unsigned char                   save_flash_delay;
unsigned char                   save_6621d_delay;

unsigned char                   pwm_duty_array_0[0x10];
unsigned char                   pwm_duty_array_1[0x10];
unsigned char                   pwm_duty_array_2[0x10];
unsigned char                   pwm_duty_array_3[0x10];
unsigned char                   pwm_duty_array_4[0x10];
unsigned char                   pwm_duty_array_5[0x10];
unsigned char                   pwm_duty_array_6[0x10];
unsigned char                   pwm_duty_array_7[0x10];

unsigned char                   pwm_duty_array_x[8];

//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: pwm2_init
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void RGBMgr_Config(void)
{

}
