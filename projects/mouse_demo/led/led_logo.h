/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_LOGO_H_
#define _LED_LOGO_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;
#define iLED_SNAKE              (8)
#define iLED_DXTW               16
#define iLED_TXTW               11

//-----------------------------------------------------------------------------;
// 配置常量定义区
//
#define iPWM_R                  0x01
#define iPWM_G                  0x02
#define iPWM_B                  0x04
#define iPWM_W                  0x0F

#define iRGB_INVLAID            0xFF

#define iPWM_MAX                255
#define iPWM_SNAKE_MAX          252
#define iRGB_INDEX_MAX          6
#define iRGB_QICAI              6

//-----------------------------------------------------------------------------;
//配置区
//
#define PWM0                    PWM2_0PL
#define PWM1                    PWM2_0NL
#define PWM2                    PWM2_1PL
#define PWM3                    PWM2_1NL
#define PWM4                    PWM2_2PL
#define PWM5                    PWM2_2NL

//-----------------------------------------------------------------------------;
// 配置区
//
enum led_mod
{
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
};
enum led_level
{
    iLED_LEV_MIN=0,             // 最暗
    iLED_LEV_0 = 0,
    iLED_LEV_1 = 1,
    iLED_LEV_2 = 2,
    iLED_LEV_3 = 3,
    iLED_LEV_4 = 4,
    iLED_LEV_MAX = 4,           // 最亮
};

enum speed_level
{
    iSPEED_LEV_MIN = 0,
    iSPEED_LEV_1 = 0,
    iSPEED_LEV_2 = 1,
    iSPEED_LEV_3 = 2,
    iSPEED_LEV_4 = 3,
    iSPEED_LEV_MAX = 3,
};

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//
//-----------------------------------------------------------------------------;
// 外部函数引用
//

extern unsigned char    const   led_liuguang_l_r_tbl[];
extern unsigned char    const   led_liuguang_rgb_tbl[];
//=============================================================================;
// 内部定义外部引用区      
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern USBD_U16                 uled_ctrl_reg;
//{
    #define led_ctrl_reg        uled_ctrl_reg.u16

    #define bsave_flash_bak     uled_ctrl_reg.BIT.b15
    #define bled_hint_ing       uled_ctrl_reg.BIT.b13
    #define bled_run_dir        uled_ctrl_reg.BIT.b11 // 方向：0：左→右；1：右→左；
    #define brgb_bright_en      uled_ctrl_reg.BIT.b10
    #define bsave_flash         uled_ctrl_reg.BIT.b8
    #define bsave_6621d         uled_ctrl_reg.BIT.b7
    #define bdelay_time         uled_ctrl_reg.BIT.b6
    #define bled_mode_jg        uled_ctrl_reg.BIT.b5
    #define bmode_swtich_hint   uled_ctrl_reg.BIT.b4
    #define bback_led_off       uled_ctrl_reg.BIT.b3
    #define bled_mode_single    uled_ctrl_reg.BIT.b2
    #define bback_led_status    uled_ctrl_reg.BIT.b0
//}
extern USBD_U8                  urgb_enable;
//{
    #define rgb_enable          urgb_enable.u8
    #define bw_enable           urgb_enable.BIT.b3
    #define bb_enable           urgb_enable.BIT.b2
    #define bg_enable           urgb_enable.BIT.b1
    #define br_enable           urgb_enable.BIT.b0
//}
extern USBD_U8                  uled_status_reg;
//{
    #define led_status_reg      uled_status_reg.u8

    #define bled7_status        uled_status_reg.BIT.b7
    #define bled6_status        uled_status_reg.BIT.b6
    #define bled5_status        uled_status_reg.BIT.b5
    #define bled4_status        uled_status_reg.BIT.b4
    #define bled3_status        uled_status_reg.BIT.b3
    #define bled2_status        uled_status_reg.BIT.b2
    #define bled1_status        uled_status_reg.BIT.b1
    #define bled0_status        uled_status_reg.BIT.b0
//}
extern USBD_U8                  uled_use_flag;
//{
    #define led_use_flag        uled_use_flag.u8

    #define bled_7_idle         uled_use_flag.BIT.b7
    #define bled_6_idle         uled_use_flag.BIT.b6
    #define bled_5_idle         uled_use_flag.BIT.b5
    #define bled_4_idle         uled_use_flag.BIT.b4
    #define bled_3_idle         uled_use_flag.BIT.b3
    #define bled_2_idle         uled_use_flag.BIT.b2
    #define bled_1_idle         uled_use_flag.BIT.b1
    #define bled_0_idle         uled_use_flag.BIT.b0
//}


extern unsigned char            pwm_value;

extern unsigned char            pwm_time_count;
extern unsigned int             delay_time_count;
extern unsigned char            rgb_index;

extern enum led_mod             led_cur_mode;
extern enum led_mod             led_pre_mode;
extern enum led_level           led_light_lev;
extern enum speed_level         led_speed_lev;
extern unsigned char            led_rgb_index;
extern unsigned char            led_scan_count;

extern unsigned char            pwm_r_array[];
extern unsigned char            pwm_g_array[];
extern unsigned char            pwm_b_array[];

extern unsigned char            pwm_duty_array_0[];
extern unsigned char            pwm_duty_array_1[];
extern unsigned char            pwm_duty_array_2[];
extern unsigned char            pwm_duty_array_3[];
extern unsigned char            pwm_duty_array_4[];
extern unsigned char            pwm_duty_array_5[];
extern unsigned char            pwm_duty_array_6[];
extern unsigned char            pwm_duty_array_7[];

extern unsigned char            pwm_duty_array_x[];
extern unsigned char            snake_led_index;
extern unsigned char            led_process_index;
extern unsigned int             lfsr_value;
extern unsigned char            save_flash_delay;
extern unsigned char            save_6621d_delay;

extern unsigned char const      led_single_table[];


extern unsigned char    const   rgb_en_tbl[];
//-----------------------------------------------------------------------------;
// 函数引用
//

/*******************************************************************************
 led_process: 
*******************************************************************************/
extern void RGBMgr_Config(void);

extern void led_process(void);
extern void device_led_off(void);
extern void win_mac_hint(void);
extern void led_hint(void);
#define clr_all_rgb     clr_rgb

extern void clr_rgb(void);
extern void led_control(void);
extern void rgb_pwm0_w(void);
extern void rgb_w_max(void);

extern void led_mode_on(void);
extern void led_mode_breath(void);
extern void led_mode_snake(void);
extern void led_mode_nhjb(void);
extern void led_mode_liuguang(void);
extern void led_mode_star(void);
extern void led_mode_baoshan(void);
extern void led_mode_qcnh(void);
extern void led_mode_lhtw(void);
extern void led_mode_dxtw(void);
extern void led_mode_sxtw(void);
extern void led_mode_txtw(void);
extern void led_mode_jg_init(unsigned char led_c);
extern void led_mode_jiguang(void);



extern void led_mode_sbzl(void);
//
//-----------------------------------------------------------------------------;
#endif
