/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: logo_mode.c
*
* 功能说明: 灯效模式分发. 全部灯效已重新设计并统一由 led_effect.c 实现,
*           本文件保留模式入口、方向标志与按键位置表 (led_logo_tbl.h).
*******************************************************************************/
#include <string.h>
#include "om_driver.h"

#include "main.h"
#include "led.h"
#include "led_logo_tbl.h"
#include "led_effect.h"

//-----------------------------------------------------------------------------;
// 变量定义区
//
bool                            bled_run_dir;           // 灯效方向: 0 左→右, 1 右→左

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

void clr_rgb(void)
{
    memset(pwm_rgb_tbl, 0x00, iLED_MAX*3);
    memset(pwm_rgb_hr, 0x00, sizeof(uint16_t)*iLED_MAX*3);
}

/******************************************************************************
* 函数名称: logo_mode_init
* 功能描述: 切换到 mode 时初始化灯效状态
******************************************************************************/
void logo_mode_init(uint8_t mode)
{
    led_process_index = 0;
    rgb_index = 0;
    led_effect_init(mode);
}

/******************************************************************************
* 函数名称: logo_mode_run
* 功能描述: 推进一帧
******************************************************************************/
void logo_mode_run(uint8_t mode)
{
    if(mode > iMODE_LED_MAX)
    {                                           // Flash / 上位机给出非法值: 回到柔光
        led_cur_mode = iMODE_LED_SOFT_ON;
        return;
    }
    led_effect_run(mode);
}
