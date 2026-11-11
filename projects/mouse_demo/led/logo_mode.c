/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
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
#include "led.h"
#include "led_logo_tbl.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//

#define iLFSR_MULTINOMIAL       0xF521

bool                            bled_run_dir;

uint16_t                        lfsr_value;
uint8_t                         start_dec_count;
uint8_t                         snake_led_index;

//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_hint_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_mode_on(void)
{
    rgb_enable = rgb_en_tbl[led_rgb_index&0x07];
    for(gtemp_j=0; gtemp_j<iLED_MAX; gtemp_j++)
    {
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = rgb_en_tbl[gtemp_j&0x07];
        rgb_w_max();
    }
}

/******************************************************************************
* 函数名称: led_hint_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_mode_breath(void)
{
    unsigned char i;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

    i = pwm_time_count;
    if(!bback_led_status)
    {
        if(pwm_time_count >= iPWM_MAX)
            pwm_value = 0;
        else
            pwm_value = (iPWM_MAX - i);
    }
    else
    {
        if(pwm_time_count >= iPWM_MAX)
            pwm_value = iPWM_MAX;
        else
            pwm_value = i;
    }

    if(pwm_time_count == iPWM_MAX)   // 最亮和最暗的时间加长
    {
        pwm_time_count = 0;
        bback_led_status = !bback_led_status;
        if(bback_led_status)
            rgb_index++;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x07];

    for(i=0; i<iLED_MAX; i++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = ((rgb_index+i)&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        if(rgb_enable&iPWM_R)
            pwm_rgb_tbl[i][iR_INDEX] = pwm_value;
        else
            pwm_rgb_tbl[i][iR_INDEX] = 0;
        if(rgb_enable&iPWM_G)
            pwm_rgb_tbl[i][iG_INDEX] = pwm_value;
        else
            pwm_rgb_tbl[i][iG_INDEX] = 0;
        if(rgb_enable&iPWM_B)
            pwm_rgb_tbl[i][iB_INDEX] = pwm_value;
        else
            pwm_rgb_tbl[i][iB_INDEX] = 0;
    }

    pwm_time_count++;
}

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_snake(void)
{
    unsigned char x, y ,k;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

	if(!bled_run_dir)
    {
	    if(iLED_SNAKE <= snake_led_index)
		    snake_led_index = 0;

	    k = snake_led_index;
	    y = k;
	    x = --pwm_duty_array_0[y];

	    if(((iPWM_SNAKE_MAX*3)/4)>=x)
        {
	    	snake_led_index++;
            if(iLED_SNAKE<=snake_led_index)
                snake_led_index = 0;
            pwm_duty_array_0[y] = ((iPWM_SNAKE_MAX*3)/4);
            y = snake_led_index;
            pwm_duty_array_0[y] = iPWM_SNAKE_MAX;
        }
	    x = pwm_duty_array_0[k];
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_SNAKE-1);
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*1)/4);

	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_SNAKE-1);
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*2)/4);

	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_SNAKE-1);
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*3)/4);
    }
    else
    {
	    if(iLED_SNAKE <= snake_led_index)
		    snake_led_index = iLED_SNAKE-1;

	    k = snake_led_index;
	    y = k;
	    x = --pwm_duty_array_0[y];

	    if(((iPWM_SNAKE_MAX*3)/4)>=x)
        {
	    	snake_led_index--;
            if(iLED_SNAKE<=snake_led_index)
		        snake_led_index = iLED_SNAKE-1;
            pwm_duty_array_0[y] = ((iPWM_SNAKE_MAX*3)/4);
            y = snake_led_index;
            pwm_duty_array_0[y] = iPWM_SNAKE_MAX;
        }
	    x = pwm_duty_array_0[k];
        
	    k++;
	    if(iLED_SNAKE <= k)
	        k = 0;
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*1)/4);

	    k++;
	    if(iLED_SNAKE <= k)
	        k = 0;
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*2)/4);

	    k++;
	    if(iLED_SNAKE <= k)
	        k = 0;
	    y = k;
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*3)/4);
    }
    
    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(gtemp_x = 0; gtemp_x<iLED_NUM_MAX; gtemp_x++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = (gtemp_x&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        gtemp_j = gtemp_x;
        rgb_pwm0_w();
    }
}

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_nhjb(void)
{
    unsigned char i;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

    if(0 == led_process_index)
    {
        pwm_duty_array_0[1]++;
        if(iPWM_MAX <= pwm_duty_array_0[1])
            led_process_index++;
    }
    else if(1 == led_process_index)
    {
        pwm_duty_array_0[0]--;
        if(0 == pwm_duty_array_0[0])
            led_process_index++;
    }
    else if(2 == led_process_index)
    {
        pwm_duty_array_0[2]++;
        if(iPWM_MAX <= pwm_duty_array_0[2])
            led_process_index++;
    }
    else if(3 == led_process_index)
    {
        pwm_duty_array_0[1]--;
        if(0 == pwm_duty_array_0[1])
            led_process_index++;
    }
    else if(4 == led_process_index)
    {
        pwm_duty_array_0[0]++;
        if(iPWM_MAX <= pwm_duty_array_0[0])
            led_process_index++;
    }
    else //if(5 == led_process_index)
    {
        pwm_duty_array_0[2]--;
        if(0 == pwm_duty_array_0[2])
            led_process_index = 0;
    }

    for(i=0; i<iLED_MAX; i++)
    {
        pwm_rgb_tbl[i][0] = pwm_duty_array_0[iR_INDEX];
        pwm_rgb_tbl[i][1] = pwm_duty_array_0[iG_INDEX];
        pwm_rgb_tbl[i][2] = pwm_duty_array_0[iB_INDEX];
    }
}

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

void led_mode_liuguang(void)
{
    unsigned char i, k;
    uint16_t x;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

    x = 0x01;
    for(i=0; i<iLED_MAX; i++)
    {
        if(led_status_reg & x)
        {
            pwm_duty_array_0[i]++;
            if(iPWM_MAX <= pwm_duty_array_0[i])
            {
                led_status_reg &= ~x;
            }
        }
        else
        {
            pwm_duty_array_0[i]--;
            if(0 == pwm_duty_array_0[i])
            {
                pwm_duty_array_1[i]++;
                if(7 < pwm_duty_array_1[i])
                    pwm_duty_array_1[i]=1;
                led_status_reg |= x;
            }
        }
        x <<= 1;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];

    for(k=0; k<iLED_MAX; k++)
    {
        if(bled_run_dir)
        {
            gtemp_j = pwm_duty_array_0[k];
            if(iRGB_QICAI == led_rgb_index)
                rgb_enable = pwm_duty_array_1[k];
        }
        else
        {
            gtemp_j = pwm_duty_array_0[iLED_MAX-1-k];
            if(iRGB_QICAI == led_rgb_index)
                rgb_enable = pwm_duty_array_1[iLED_MAX-1-k];
        }

        if(rgb_enable&iPWM_R)
            pwm_rgb_tbl[k][iR_INDEX] = gtemp_j;
        else
            pwm_rgb_tbl[k][iR_INDEX] = 0;
        if(rgb_enable&iPWM_G)
            pwm_rgb_tbl[k][iG_INDEX] = gtemp_j;
        else
            pwm_rgb_tbl[k][iG_INDEX] = 0;
        if(rgb_enable&iPWM_B)
            pwm_rgb_tbl[k][iB_INDEX] = gtemp_j;
        else
            pwm_rgb_tbl[k][iB_INDEX] = 0;
    }
}

unsigned char       const   start_dec_delay[]={
    25,
    50,
    100,
    150,
};

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_star(void)
{
    unsigned char i, j;
    
    delay_time_count++;
    i = start_dec_delay[led_speed_lev&0x03];
    if(i > delay_time_count)
    {
        start_dec_count++;
        if(led_speed_lev>start_dec_count)
        {
            start_dec_count++;
            return;
        }
        start_dec_count = 0;

        rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
        for(i=0; i<iLED_MAX; i++)
        {
            if(0 != pwm_duty_array_0[i])
            {
                pwm_duty_array_0[i]--;

                if(iRGB_QICAI <= led_rgb_index)
                    rgb_enable = (pwm_duty_array_1[i]&0x0F);

                if(rgb_enable&iPWM_R)
                    pwm_rgb_tbl[i][iR_INDEX] = pwm_duty_array_0[i];
                else
                    pwm_rgb_tbl[i][iR_INDEX] = 0;
                if(rgb_enable&iPWM_G)
                    pwm_rgb_tbl[i][iG_INDEX] = pwm_duty_array_0[i];
                else
                    pwm_rgb_tbl[i][iG_INDEX] = 0;
                if(rgb_enable&iPWM_B)
                    pwm_rgb_tbl[i][iB_INDEX] = pwm_duty_array_0[i];
                else
                    pwm_rgb_tbl[i][iB_INDEX] = 0;          
            }
            else
            {
                pwm_rgb_tbl[i][iR_INDEX] = 0;
                pwm_rgb_tbl[i][iG_INDEX] = 0;
                pwm_rgb_tbl[i][iB_INDEX] = 0;
            }
        }
        
        return;
    }

    delay_time_count = 0;

    lfsr_value = lfsr_value>>1;
    if(lfsr_value & 0x01)
        lfsr_value ^= iLFSR_MULTINOMIAL;

    j = ((lfsr_value+(lfsr_value>>8))&0x07);

    pwm_duty_array_0[j] = iPWM_MAX;
    pwm_duty_array_1[j] = ((lfsr_value>>8)&0x07);
    if(0==pwm_duty_array_1[j])
        pwm_duty_array_1[j] = 1;
}

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_sbzl(void)
{
    if(led_speed_lev > delay_time_count)
    {
        delay_time_count++;
        return;
    }
    delay_time_count = 0;

    for(gtemp_x=0; gtemp_x<iLED_MAX; gtemp_x++)
    {
        if(0 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_0[gtemp_x]--;
            pwm_duty_array_1[gtemp_x]=iPWM_MAX-pwm_duty_array_0[gtemp_x];
            if(0 == pwm_duty_array_0[gtemp_x])
                pwm_duty_array_3[gtemp_x]++;
        }
        else if(1 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_1[gtemp_x]--;
            pwm_duty_array_2[gtemp_x]=iPWM_MAX-pwm_duty_array_1[gtemp_x];
            if(0 == pwm_duty_array_1[gtemp_x])
                pwm_duty_array_3[gtemp_x]++;
        }
        else //if(2 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_2[gtemp_x]--;
            pwm_duty_array_0[gtemp_x]=iPWM_MAX-pwm_duty_array_2[gtemp_x];
            if(0 == pwm_duty_array_2[gtemp_x])
                pwm_duty_array_3[gtemp_x]=0;
        }
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    if(!bled_run_dir)
    {
        for(gtemp_x = 0; gtemp_x<iLED_MAX; gtemp_x++)
        {
            if(rgb_enable&iPWM_R)
               pwm_rgb_tbl[gtemp_x][iR_INDEX] = pwm_duty_array_0[gtemp_x];
           else
               pwm_rgb_tbl[gtemp_x][iR_INDEX] = 0;
            if(rgb_enable&iPWM_G)
               pwm_rgb_tbl[gtemp_x][iG_INDEX] = pwm_duty_array_1[gtemp_x];
           else
               pwm_rgb_tbl[gtemp_x][iG_INDEX] = 0;
            if(rgb_enable&iPWM_B)
               pwm_rgb_tbl[gtemp_x][iB_INDEX] = pwm_duty_array_2[gtemp_x];
           else
               pwm_rgb_tbl[gtemp_x][iB_INDEX] = 0;
        }
    }
    else
    {
        for(gtemp_x = 0; gtemp_x<iLED_MAX; gtemp_x++)
        {
            if(rgb_enable&iPWM_R)
                pwm_rgb_tbl[gtemp_x][iR_INDEX] = pwm_duty_array_0[iLED_MAX-1-gtemp_x];
            else
                pwm_rgb_tbl[gtemp_x][iR_INDEX] = 0;
            if(rgb_enable&iPWM_G)
                pwm_rgb_tbl[gtemp_x][iG_INDEX] = pwm_duty_array_1[iLED_MAX-1-gtemp_x];
            else
                pwm_rgb_tbl[gtemp_x][iG_INDEX] = 0;
            if(rgb_enable&iPWM_B)
                pwm_rgb_tbl[gtemp_x][iB_INDEX] = pwm_duty_array_2[iLED_MAX-1-gtemp_x];
            else
                pwm_rgb_tbl[gtemp_x][iB_INDEX] = 0;    
        }
    }
}

unsigned int       const   bs_dec_delay[8]={
    50,
    100,
    150,
    300,
};

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_baoshan(void)
{
    delay_time_count++;
    if(bs_dec_delay[led_speed_lev&0x03] > delay_time_count)
        return;

    delay_time_count = 0;
    clr_rgb();

	if(0 == led_process_index)
	{
	    if(iRGB_QICAI != led_rgb_index)
            rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
        else
            rgb_enable = rgb_en_tbl[rgb_index&0x0F];
	    gtemp_j = 0;
	    rgb_w_max();
	    gtemp_j = 2;
	    rgb_w_max();
	    gtemp_j = 4;
	    rgb_w_max();
	    gtemp_j = 6;
	    rgb_w_max();

        led_process_index++;
    }
    else if(1 == led_process_index)
	{
	    if(iRGB_QICAI != led_rgb_index)
            rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
        else
            rgb_enable = rgb_en_tbl[rgb_index&0x0F];
	    gtemp_j = 1;
	    rgb_w_max();
	    gtemp_j = 3;
	    rgb_w_max();
	    gtemp_j = 5;
	    rgb_w_max();
	    gtemp_j = 7;
	    rgb_w_max();

        led_process_index++;
    }
	else if(2 == led_process_index)
	{
	    if(iRGB_QICAI != led_rgb_index)
            rgb_enable = ~rgb_en_tbl[led_rgb_index&0x0F];
        else
            rgb_enable = ~rgb_en_tbl[rgb_index&0x0F];
        if(0==(rgb_enable&0x07))
            rgb_enable = 0x01;

	    gtemp_j = 0;
	    rgb_w_max();
	    gtemp_j = 2;
	    rgb_w_max();
	    gtemp_j = 4;
	    rgb_w_max();
	    gtemp_j = 6;
	    rgb_w_max();

        led_process_index++;
    }
    else //if(3 == led_process_index)
	{
	    if(iRGB_QICAI != led_rgb_index)
            rgb_enable = ~rgb_en_tbl[led_rgb_index&0x0F];
        else
            rgb_enable = ~rgb_en_tbl[rgb_index&0x0F];
        if(0==(rgb_enable&0x07))
            rgb_enable = 0x01;
	    gtemp_j = 1;
	    rgb_w_max();
	    gtemp_j = 3;
	    rgb_w_max();
	    gtemp_j = 5;
	    rgb_w_max();
	    gtemp_j = 7;
	    rgb_w_max();

        led_process_index=0;
        rgb_index++;
        if(7<=rgb_index)
            rgb_index = 0;
    }
}

unsigned char       const   qcnh_en_tbl[]={
    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,

    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,
    iPWM_R,
    iPWM_G,
};
unsigned int       const   qcnh_dec_delay[]={
    50,
    100,
    150,
    200,
};
/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_qcnh(void)
{
    unsigned char i;

    delay_time_count++;
    if(qcnh_dec_delay[led_speed_lev&0x03] > delay_time_count)
        return;

    delay_time_count = 0;
    clr_rgb();

    for(i = 0; i<iLED_MAX; i++)
    {
        rgb_enable = qcnh_en_tbl[(rgb_index+i)&0x0F];

	    gtemp_j = i;
	    rgb_w_max();
    }

    rgb_index++;
    if(7<=rgb_index)
        rgb_index = 0;
}

unsigned int       const   lhtw_dec_delay[]={
    10,
    20,
    30,
    40,
};
/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_lhtw(void)
{
    unsigned char i;

    delay_time_count++;
    if(lhtw_dec_delay[led_speed_lev&0x03] > delay_time_count)
        return;

    delay_time_count = 0;

    if(!bback_led_status)
    {
        for(i=0; i<led_process_index; i++)
        {
            rgb_enable = qcnh_en_tbl[i];
	        gtemp_j = i;
	        rgb_w_max();
        }
        led_process_index++;
        if(iLED_MAX < led_process_index)
            bback_led_status = 1;
    }
    else
    {
        for(i=led_process_index; i<iLED_MAX; i++)
        {
            rgb_enable = qcnh_en_tbl[i];
            pwm_rgb_tbl[i][iR_INDEX] = 0;
            pwm_rgb_tbl[i][iG_INDEX] = 0;
            pwm_rgb_tbl[i][iB_INDEX] = 0;
        }

        if(0 != led_process_index)
            led_process_index--;
        else
            bback_led_status = 0;
    }
}

/******************************************************************************
* 函数名称: led_mode_dxtw
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_dxtw(void)
{
    unsigned char x;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

	snake_led_index &= 0x0F;
    x = --pwm_duty_array_0[snake_led_index];
    if(((iPWM_SNAKE_MAX*3)/4)>x)
    {
    	snake_led_index++;
        if(iLED_DXTW<=snake_led_index)
        {
            snake_led_index = 3;
            pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
            return;
        }
        pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
    }
    x = pwm_duty_array_0[snake_led_index];
    pwm_duty_array_0[snake_led_index-1] = x-((iPWM_SNAKE_MAX*1)/4);
    pwm_duty_array_0[snake_led_index-2] = x-((iPWM_SNAKE_MAX*2)/4);
    pwm_duty_array_0[snake_led_index-3] = x-((iPWM_SNAKE_MAX*3)/4);

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(gtemp_x=5; gtemp_x<(iLED_MAX+5); gtemp_x++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = (gtemp_x&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        gtemp_j = (gtemp_x-5);
        rgb_pwm0_w();
    }
}

/******************************************************************************
* 函数名称: led_mode_dxtw
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_sxtw(void)
{
    unsigned char x;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

	snake_led_index &= 0x0F;
    if(!bback_led_status)
    {
        x = --pwm_duty_array_0[snake_led_index];
        if(((iPWM_SNAKE_MAX*3)/4)>x)
        {
        	snake_led_index++;
            if(iLED_DXTW<=snake_led_index)
            {
                snake_led_index = (iLED_DXTW-4);
                pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
                bback_led_status = 1;
                return;
            }
            pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
        }
        x = pwm_duty_array_0[snake_led_index];
        pwm_duty_array_0[snake_led_index-1] = x-((iPWM_SNAKE_MAX*1)/4);
        pwm_duty_array_0[snake_led_index-2] = x-((iPWM_SNAKE_MAX*2)/4);
        pwm_duty_array_0[snake_led_index-3] = x-((iPWM_SNAKE_MAX*3)/4);
    }
    else
    {
        x = --pwm_duty_array_0[snake_led_index];
        if(((iPWM_SNAKE_MAX*3)/4)>x)
        {
            if(0 != snake_led_index)
            {
        	    snake_led_index--;
            }
            else
            {
                snake_led_index = 3;
                pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
                bback_led_status = 0;
                return;
            }
            pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
        }
        x = pwm_duty_array_0[snake_led_index];
        pwm_duty_array_0[snake_led_index+1] = x-((iPWM_SNAKE_MAX*1)/4);
        pwm_duty_array_0[snake_led_index+2] = x-((iPWM_SNAKE_MAX*2)/4);
        pwm_duty_array_0[snake_led_index+3] = x-((iPWM_SNAKE_MAX*3)/4);
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(gtemp_x=5; gtemp_x<(iLED_MAX+5); gtemp_x++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = (gtemp_x&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        gtemp_j = (gtemp_x-5);
        rgb_pwm0_w();
    }
}
/******************************************************************************
* 函数名称: led_mode_dxtw
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_txtw(void)
{
    unsigned char x;

    if(led_speed_lev>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;

	snake_led_index &= 0x0F;
    x = --pwm_duty_array_0[snake_led_index];
    if(((iPWM_SNAKE_MAX*3)/4)>x)
    {
    	snake_led_index++;
        if(iLED_TXTW<=snake_led_index)
        {
            snake_led_index = 3;
            pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
            return;
        }
        pwm_duty_array_0[snake_led_index] = iPWM_SNAKE_MAX;
    }
    x = pwm_duty_array_0[snake_led_index];
    pwm_duty_array_0[snake_led_index-1] = x-((iPWM_SNAKE_MAX*1)/4);
    pwm_duty_array_0[snake_led_index-2] = x-((iPWM_SNAKE_MAX*2)/4);
    pwm_duty_array_0[snake_led_index-3] = x-((iPWM_SNAKE_MAX*3)/4);

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];

    if(iMODE_LED_TXTW == led_cur_mode)
    {
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x01;
        gtemp_x = 4;
        gtemp_j = 0;
        rgb_pwm0_w();
        gtemp_j = 7;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x02;
        gtemp_x = 5;
        gtemp_j = 1;
        rgb_pwm0_w();
        gtemp_j = 6;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x04;
        gtemp_x = 6;
        gtemp_j = 2;
        rgb_pwm0_w();
        gtemp_j = 5;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x03;
        gtemp_x = 7;
        gtemp_j = 3;
        rgb_pwm0_w();
        gtemp_j = 4;
        rgb_pwm0_w();
    }
    else if(iMODE_LED_FXTW == led_cur_mode)
    {
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x01;
        gtemp_x = 7;
        gtemp_j = 0;
        rgb_pwm0_w();
        gtemp_j = 7;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x02;
        gtemp_x = 6;
        gtemp_j = 1;
        rgb_pwm0_w();
        gtemp_j = 6;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x04;
        gtemp_x = 5;
        gtemp_j = 2;
        rgb_pwm0_w();
        gtemp_j = 5;
        rgb_pwm0_w();
    
        if(iRGB_QICAI == led_rgb_index)
            rgb_enable = 0x03;
        gtemp_x = 4;
        gtemp_j = 3;
        rgb_pwm0_w();
        gtemp_j = 4;
        rgb_pwm0_w();
    }
}
