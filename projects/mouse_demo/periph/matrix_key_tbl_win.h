/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
*
* 文件名称: _MATRIX_KEY_TBL_
*
* 功能说明: 班达K20 矩阵键值表(WIN层) 逻辑15列(C0~C14) x 8行(R0~R7)
*           物理矩阵仍为18列(硬件走线不变), 由 matrixkey_scan() 软件移位
*           将物理C15~C17的4个修饰键并入C0后再进入解码:
*             Shift-L C15R1->C0R1, Shift-R C15R2->C0R2,
*             Win-L   C16R1->C0R3, Win-R   C17R2->C0R5
*           仅保留标准键 + Fn键, 其余键位(电源/媒体/网络/模式类)已剔除
*           表索引: decode_index = 列号C x 8 + 行号R, 每键2字节(键值, 类型)
* 修改说明: 基于硬件矩阵表 2026-11-07 生成, 软件移位压缩版
*******************************************************************************/
#ifndef _MATRIX_KEY_WIN_TBL_
#define _MATRIX_KEY_WIN_TBL_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 正常矩阵表
//

// WIN键值表
unsigned char           const   matrixkey_win_tbl[] =
{
// C0
    iSTD_PAUSE,         iKEY_TYPE_STD|iKEY_PRESS,                           // R0 Pause
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,               // R1 Shift-L <-软件移位 C15R1
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,              // R2 Shift-R <-软件移位 C15R2
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_GUI,                 // R3 Win-L   <-软件移位 C16R1
    iLED_OFF,           iKEY_TYPE_SPECIAL,                                  // R4 Ctrl-R
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_GUI,                // R5 Win-R   <-软件移位 C17R2
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,                // R6 Ctrl-L
    iSTD_F5,            iKEY_TYPE_STD|iKEY_PRESS,                           // R7 F5

// C1
    iSTD_Q,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_TAB,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_A,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ESCAPE,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Z,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MUTE_L,        iKEY_TYPE_MMK|iMMK_MUTE_H,                          // R5 (原表空)
    iSTD_WAVE,          iKEY_TYPE_STD|iKEY_PRESS,                           // R6 ` ~
    iSTD_1,             iKEY_TYPE_STD|iKEY_PRESS,

// C2
    iSTD_W,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_CAPITAL,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_S,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R3 (原表空)
    iSTD_X,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R5 (原表空)
    iSTD_F1,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_2,             iKEY_TYPE_STD|iKEY_PRESS,

// C3
    iSTD_E,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F3,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_D,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F4,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_C,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R5 (原表空)
    iSTD_F2,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_3,             iKEY_TYPE_STD|iKEY_PRESS,

// C4
    iSTD_R,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_T,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_G,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_V,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_B,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_5,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_4,             iKEY_TYPE_STD|iKEY_PRESS,

// C5
    iSTD_U,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Y,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_J,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_H,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_M,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_N,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_6,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_7,             iKEY_TYPE_STD|iKEY_PRESS,

// C6
    iSTD_I,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_RIGHT,   iKEY_TYPE_STD|iKEY_PRESS,                   // R1 ] }
    iSTD_K,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F6,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_COMMA,         iKEY_TYPE_STD|iKEY_PRESS,                           // R4 , <
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R5 (原表空)
    iSTD_ADD,           iKEY_TYPE_STD|iKEY_PRESS,                           // R6 = +
    iSTD_8,             iKEY_TYPE_STD|iKEY_PRESS,

// C7
    iSTD_O,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F7,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_L,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R3 原表空
    iSTD_FULLSTOP,      iKEY_TYPE_STD|iKEY_PRESS,                           // R4 . >
    iSTD_APP,           iKEY_TYPE_STD|iKEY_PRESS,                                 // R5 (原表空)
    iSTD_F8,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_9,             iKEY_TYPE_STD|iKEY_PRESS,

// C8
    iSTD_P,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_LEFT,    iKEY_TYPE_STD|iKEY_PRESS,                   // R1 [ {
    iSTD_SEMICOLON,     iKEY_TYPE_STD|iKEY_PRESS,                           // R2 ; :
    iSTD_QUOTATION_SIGN,    iKEY_TYPE_STD|iKEY_PRESS,                       // R3 ' "
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R4 (原表空)
    iSTD_SLASH,         iKEY_TYPE_STD|iKEY_PRESS,                           // R5 / ?
    iSTD_SUBTRACT,      iKEY_TYPE_STD|iKEY_PRESS,                           // R6 - _
    iSTD_0,             iKEY_TYPE_STD|iKEY_PRESS,

// C9
    iSTD_SCROLL,        iKEY_TYPE_STD|iKEY_PRESS,                           // R0 Scroll
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R1 (原表空)
    iMODE_KEY_FN,       iKEY_TYPE_SPECIAL,                                  // R2 Fn
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_ALT,                 // R3 Alt-L
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R4 (原表空)
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,                // R5 Alt-R
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R6 (原表空)
    iSTD_SNAPSHOT,      iKEY_TYPE_STD|iKEY_PRESS,                           // R7 Print

// C10
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R0 (原表空)
    iSTD_BACKSPACE,     iKEY_TYPE_STD|iKEY_PRESS,                           // R1 Back
    iSTD_BACKSLASH,     iKEY_TYPE_STD|iKEY_PRESS,                           // R2 \ |
    iSTD_F11,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ENTER,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F12,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F9,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F10,           iKEY_TYPE_STD|iKEY_PRESS,

// C11
    iSTD_NUMPAD7,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD4,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD1,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SPACE,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMLOCK,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DOWN,          iKEY_TYPE_STD|iKEY_PRESS,                           // R5 ↓
    iSTD_DELETE,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R7 (原表空)

// C12
    iSTD_NUMPAD8,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD5,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD2,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD0,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_DIVIDE, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_RIGHT,         iKEY_TYPE_STD|iKEY_PRESS,                           // R5 →
    iSTD_INSERT,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R7 (原表空)

// C13
    iSTD_NUMPAD9,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD6,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD3,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_FULLSTOP,   iKEY_TYPE_STD|iKEY_PRESS,                       // R3 . (k)
    iSTD_NUMPAD_MULTIPLY,   iKEY_TYPE_STD|iKEY_PRESS,                       // R4 * (k)
    iSTD_NUMPAD_SUBTRACT,   iKEY_TYPE_STD|iKEY_PRESS,                       // R5 - (k)
    iSTD_PAGEUP,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEDOWN,      iKEY_TYPE_STD|iKEY_PRESS,

// C14
    iSTD_NUMPAD_ADD,    iKEY_TYPE_STD|iKEY_PRESS,                           // R0 + (k)
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R1 (原表空)
    iSTD_NUMPAD_ENTER,  iKEY_TYPE_STD|iKEY_PRESS,                           // R2 Enter(k)
    iSTD_UP,            iKEY_TYPE_STD|iKEY_PRESS,                           // R3 ↑
    iSTD_NULL,          iKEY_TYPE_INVALID,                                  // R4 (原表空)
    iSTD_LEFT,          iKEY_TYPE_STD|iKEY_PRESS,                           // R5 ←
    iSTD_HOME,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_END,           iKEY_TYPE_STD|iKEY_PRESS,
};
//-----------------------------------------------------------------------------;

#endif
