/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _LED_TBL_
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_LOGO_TBL_
#define _LED_LOGO_TBL_
#include "led.h"

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define NULL_0                  127
#define NULL_1                  126
#define NULL_2                  125
#define NULL_3                  124
#define NULL_4                  123
#define NULL_5                  122
#define NULL_6                  121
#define NULL_7                  120

//-----------------------------------------------------------------------------;
//配置区
//
#define RGB_COLOR_MAX         8
#define RGB_COLOR_INIT        7

unsigned char       const   rgb_en_tbl[]={
    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,
    iPWM_R|iPWM_G|iPWM_B,

    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,
    iPWM_R|iPWM_G|iPWM_B,

    0x0F,
};

unsigned char       const       led_single_table[] =
{
// C2
    4,//iSTD_V,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_5,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_F5,            iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    5,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_ALT,
    5,//iSTD_Z,             iKEY_TYPE_STD|iKEY_PRESS,               //
    6,//iSTD_1,             iKEY_TYPE_STD|iKEY_PRESS,               //
    3,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,    //
// C3
    1,//iSTD_RETURN,        iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_6,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_F6,            iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_C,             iKEY_TYPE_STD|iKEY_PRESS,               //
    5,//iSTD_3,             iKEY_TYPE_STD|iKEY_PRESS,               //
    6,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,
    5,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL,   //
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
// C4
    5,//iSTD_F,             iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_F3,            iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_PAUSE,         iKEY_TYPE_STD|iKEY_PRESS,
    1,//iMMK_VOLUMEUP_L,    iKEY_TYPE_MMK | iMMK_VOLUMEUP_H,
    0,//iMMK_VOLUMEDOWN_L,  iKEY_TYPE_MMK | iMMK_VOLUMEDOWN_H,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    6,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,
    7,//iMMK_MAIL_L,        iKEY_TYPE_MMK | iMMK_MAIL_H,
// C5
    6,//iSTD_EUROPE1,       iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_4,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_SPACE,         iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_GUI,
    7,//iMMK_WWW_HOME_L,    iKEY_TYPE_MMK | iMMK_WWW_HOME_H,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
// C6
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    4,//iSTD_F4,            iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_A,             iKEY_TYPE_STD|iKEY_PRESS,
    0,//iMMK_CALCULATOR_L,  iKEY_TYPE_MMK | iMMK_CALCULATOR_H,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    2,//iSTD_APP,           iKEY_TYPE_STD|iKEY_PRESS,
// C7
    3,//iSTD_F7,            iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_WAVE,          iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_S,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_Y,             iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_P,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_7,             iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
// C8
    3,//iSTD_F8,            iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SUBTRACT,      iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_TAB,           iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_U,             iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SQUARE_BRACKET_LEFT, iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_8,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_H,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_N,             iKEY_TYPE_STD|iKEY_PRESS,
// C9
    2,//iSTD_F9,            iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_ADD,           iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_D,             iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_I,             iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SQUARE_BRACKET_RIGHT, iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_9,             iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_QUOTATION_SIGN, iKEY_TYPE_STD|iKEY_PRESS,
    2,//iMODE_KEY_FN,       iKEY_TYPE_SPECIAL,
// C10
    2,//iSTD_F11,           iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_F1,            iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_W,             iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SNAPSHOT,      iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_HOME,          iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_DELETE,        iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_INSERT,        iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_FULLSTOP,      iKEY_TYPE_STD|iKEY_PRESS,
// C11
    1,//iSTD_F12,           iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_L,             iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_E,             iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_SCROLL,        iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_END,           iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_PAGEUP,        iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_PAGEDOWN,      iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SLASH,         iKEY_TYPE_STD|iKEY_PRESS,
// C12
    2,//iSTD_F10,           iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_F2,            iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_Q,             iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_O,             iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_BACKSLASH,     iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_0,             iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_QUROPE2,       iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_COMMA,         iKEY_TYPE_STD|iKEY_PRESS,
// C13
    2,//iSTD_APP,           iKEY_TYPE_STD|iKEY_PRESS,
    2,//iSTD_SEMICOLON,     iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_UP,            iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_NUMLOCK,       iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_NUMPAD7,       iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_NUMPAD4,       iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_NUMPAD1,       iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
// C14
    6,//iSTD_ESCAPE,        iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_K,             iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_LEFT,          iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD_DIVIDE, iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD8,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD5,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD2,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD0,       iKEY_TYPE_STD|iKEY_PRESS,
// C15
    5,//iSTD_R,             iKEY_TYPE_STD|iKEY_PRESS,
    3,//iSTD_J,             iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_DOWN,          iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD_MULTIPLY, iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD9,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD6,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD3,       iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD_FULLSTOP, iKEY_TYPE_STD|iKEY_PRESS,
// C16
    4,//iSTD_T,             iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_BACKSPACE,     iKEY_TYPE_STD|iKEY_PRESS,
    1,//iSTD_RIGHT,         iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD_SUBTRACT, iKEY_TYPE_STD|iKEY_PRESS,
    0,//iSTD_NUMPAD_ADD,    iKEY_TYPE_STD|iKEY_PRESS,
    7,//iSTD_NULL,          iKEY_TYPE_INVALID,
    0,//iSTD_NUMPAD_ENTER,  iKEY_TYPE_STD|iKEY_PRESS,
    6,//iSTD_CAPITAL,       iKEY_TYPE_STD|iKEY_PRESS,
// C17
    5,//iSTD_X,             iKEY_TYPE_STD|iKEY_PRESS,
    5,//iSTD_2,             iKEY_TYPE_STD|iKEY_PRESS,
    4,//iSTD_G,             iKEY_TYPE_STD|iKEY_PRESS, //
    4,//iSTD_B,             iKEY_TYPE_STD|iKEY_PRESS, //
    3,//iSTD_M,             iKEY_TYPE_STD|iKEY_PRESS, //
    2,//iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,
    0,//iMMK_MUTE_L,        iKEY_TYPE_MMK | iMMK_MUTE_H,
    0,//iSTD_NULL,          iKEY_TYPE_INVALID,
};

unsigned char       const       led_liuguang_l_r_tbl[]={
    63, 32,  0, 32, 63, 32,  0, 32, 63, 32,  0, 32,63, 32, 0, 32,
};
unsigned char       const       led_liuguang_rgb_tbl[]={
      1,  2,  3,  4,  6,  7,  1,  2,  3,  4,  6,  7,  1,  2, 3,  4,
};

unsigned char       const   sbzl_r_tbl[]={
 60, 40, 20,  0,  0,  0,  0, 20, 40, 60, 40, 20,  0,  0,  0,  0,};
unsigned char       const   sbzl_g_tbl[]={
  0, 20, 40, 60, 40, 20,  0,  0,  0,  0, 20, 40, 60, 40, 20,  0,};
unsigned char       const   sbzl_b_tbl[]={
  0,  0,  0,  0, 20, 40, 60, 40, 20,  0,  0,  0,  0, 20, 40, 60,};
unsigned char       const   sbzl_ctrl_tbl[]={
  0,  0,  0,  1,  1,  1,  2,  2,  2,  0,  0,  0,  1,  1,  1,  2,};

//-----------------------------------------------------------------------------;

#endif



