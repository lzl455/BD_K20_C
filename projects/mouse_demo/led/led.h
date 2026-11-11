/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: led.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_H_
#define _LED_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 配置区
//
#define iLED_SNAKE              (8)
#define iLED_DXTW               16
#define iLED_TXTW               11

#define iLED_CFG_POWER_ON       0
#define iLED_CFG_SENSOR_ERR     1
#define iLED_CFG_CONNECT_ING    2
#define iLED_CFG_CONNECT_OK     3
#define iLED_CFG_DPI_CHANGE     4
#define iLED_CFG_REPROT_CHANGE  5
#define iLED_CFG_CHAR_ING       6
#define iLED_CFG_CHAR_OK        7
#define iLED_CFG_OFF            8
#define iLED_CFG_IDLE           9

#define iPWM_R                  0x01
#define iPWM_G                  0x02
#define iPWM_B                  0x04
#define iPWM_RGB                0x07
#define iPWM_W                  0x0F

#define iPWM_MAX                64
#define iPWM_SNAKE_MAX          64
#define iRGB_QICAI              7

#define iR_INDEX                0x01
#define iG_INDEX                0x00
#define iB_INDEX                0x02

//-----------------------------------------------------------------------------;
// 配置区
//
#define iLED_NUM_MAX         	(8)
#define iLED_MAX         	    (8)

enum led_level
{
    iLED_LEV_MIN=0,// 最暗
    iLED_LEV_0 = 0,
    iLED_LEV_1 = 1,
    iLED_LEV_2 = 2,
    iLED_LEV_3 = 3,
    iLED_LEV_4 = 4,
    iLED_LEV_MAX = 4,	// 最亮
};

enum speed_level
{
    iSPEED_LEV_MIN = 0,
    iSPEED_LEV_1 = 0,
    iSPEED_LEV_2 = 1,
    iSPEED_LEV_3 = 2,
    iSPEED_LEV_4 = 3,
    iSPEED_LEV_5 = 4,
    iSPEED_LEV_MAX = 4,
};

typedef enum {
    iMODE_LED_OFF       =0,
    iMODE_LED_ON        =1,                     // 常亮
    iMODE_LED_BREATH    =2,                     // 呼吸
    iMODE_LED_SNAKE     =3,                     // 
    iMODE_LED_NHJB      =4,                     // 霓虹渐变
    iMODE_LED_LG_L_R    =5,                     // 流光
    iMODE_LED_STAR      =6,                     // 繁星点点
    iMODE_LED_SBZL      =7,                     // 随波逐流
    iMODE_LED_BS        =8,                     // 爆闪
    iMODE_LED_QCNH      =9,                     // 七彩霓虹
    iMODE_LED_LHTW      =10,                    // 来回拖尾
    iMODE_LED_DXTW      =11,                    // 单向拖尾
    iMODE_LED_SXTW      =12,                    // 双向拖尾
    iMODE_LED_TXTW      =13,                    // 对向拖尾
    iMODE_LED_FXTW      =14,                    // 反向拖尾
    iMODE_LED_JG        =15,                    // 激光

    iMODE_LED_MAX       =15,
    iMODE_LED_INVALID   =16,
    iLOGO_INVALID   = 0x0F,
} logo_mode_t;

//=============================================================================;
// 外部定义内部引用区                                                           ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//

//-----------------------------------------------------------------------------;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern bool                     blogo_status;
extern bool                     bled_bright_en;
extern bool                     bback_led_status;
extern bool                     bargb_valid;

extern uint8_t                  gtemp_i;
extern uint8_t                  gtemp_j;
extern uint8_t                  gtemp_x;

extern uint8_t                  led_hint_mode;
extern uint8_t                  led_cur_mode;
extern uint8_t                  led_mode_bak;

extern uint8_t                  logo_hint_time_count;
extern uint8_t                  logo_hint_on_time;
extern uint8_t                  logo_hint_off_time;

extern uint8_t                  rgb_enable;

extern uint16_t                 led_ctrl_reg;
extern uint16_t                 led_status_reg;
extern uint8_t                  led_use_flag;

extern uint8_t                  led_cur_mode;
extern uint8_t                  led_pre_mode;
extern enum speed_level         led_speed_lev;
extern unsigned char            led_rgb_index;
extern unsigned char            pwm_value;
extern enum led_level           led_light_lev;

extern uint16_t                 lfsr_value;
extern uint8_t                  start_dec_count;
extern uint8_t                  snake_led_index;

extern uint8_t                  pwm_time_count;
extern uint16_t                 delay_time_count;
extern uint8_t                  rgb_index;
extern uint8_t                  led_process_index;
extern uint8_t                  hint_time_count;
extern uint32_t                 exled_rtc_count;

extern uint8_t                  pwm_rgb_tbl[iLED_MAX][3];

extern uint8_t                  pwm_duty_array_0[];
extern uint8_t                  pwm_duty_array_1[];
extern uint8_t                  pwm_duty_array_2[];
extern uint8_t                  pwm_duty_array_3[];

extern unsigned char    const   rgb_en_tbl[];

extern unsigned char    const   led_liuguang_l_r_tbl[];
extern unsigned char    const   led_liuguang_rgb_tbl[];
extern unsigned char    const   sbzl_r_tbl[];
extern unsigned char    const   sbzl_g_tbl[];
extern unsigned char    const   sbzl_b_tbl[];
extern unsigned char    const   sbzl_ctrl_tbl[];


//-----------------------------------------------------------------------------;
// 函数引用
//
extern void ledc_init(void);
extern void led_status_hint(void);

extern void logo_off(void);
extern void device_led_on(void);
extern void device_led_off(void);

extern void device_led_process(void);
extern void logo_process(void);

extern void clr_rgb(void);
extern void rgb_pwm0_w(void);
extern void rgb_w_max(void);

extern void led_mode_on(void);
extern void led_mode_breath(void);
extern void led_mode_snake(void);
extern void led_mode_nhjb(void);
extern void led_mode_liuguang(void);
extern void led_mode_star(void);
extern void led_mode_sbzl(void);

extern void led_mode_baoshan(void);
extern void led_mode_qcnh(void);
extern void led_mode_lhtw(void);
extern void led_mode_dxtw(void);
extern void led_mode_sxtw(void);
extern void led_mode_txtw(void);
//
//-----------------------------------------------------------------------------;
#endif