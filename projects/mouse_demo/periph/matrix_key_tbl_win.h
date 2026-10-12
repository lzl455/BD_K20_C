/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _MATRIX_KEY_TBL_
*
* 功能说明:
* 修改说明:
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
/*
    // C0
    iSTD_TAB,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_WAVE,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F7,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Y,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_END,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_7,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SEMICOLON,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
// C1
    iSTD_CAPITAL,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
// C2
    iSTD_X,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_2,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,   //
    iMMK_MUTE_L,        iKEY_TYPE_MMK | iMMK_MUTE_H,
    iSTD_NULL,          iKEY_TYPE_INVALID,
// C3
    iSTD_F,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F1,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F5,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
*/
// C0
    iSTD_TAB,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_WAVE,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F7,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Y,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_END,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_7,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SEMICOLON,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_CAPITAL,       iKEY_TYPE_STD|iKEY_PRESS,       // C1 R7

// C4
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,    //
    iSTD_U,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F6,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F2,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F,             iKEY_TYPE_STD|iKEY_PRESS,       // C3 R0
    iSTD_ENTER,         iKEY_TYPE_STD|iKEY_PRESS,               //
    iSTD_F1,            iKEY_TYPE_STD|iKEY_PRESS,       // C3 R1
    iSTD_F5,            iKEY_TYPE_STD|iKEY_PRESS,       // C3 R2
// C5
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,    //
    iSTD_K,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_P,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_X,             iKEY_TYPE_STD|iKEY_PRESS,      // C2 R0
    iSTD_2,             iKEY_TYPE_STD|iKEY_PRESS,      // C2 R1
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,// C2 R5
    iSTD_ESCAPE,        iKEY_TYPE_STD|iKEY_PRESS,
    iKEY_WHEEL,         iKEY_TYPE_SPECIAL,
// C6
    iSTD_APP,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_G,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_UP,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_LEFT,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DOWN,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_M,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_ALT,    //
    iSTD_RIGHT,         iKEY_TYPE_STD|iKEY_PRESS,
// C7
    iSTD_T,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F3,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Z,             iKEY_TYPE_STD|iKEY_PRESS,           // C18 R0
    iSTD_NUMPAD_SUBTRACT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_ADD,    iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_NUMPAD_COMMA, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_ENTER,  iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_1,             iKEY_TYPE_STD|iKEY_PRESS,           // C18 R1
// C8
    iSTD_D,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ADD,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F9,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,// C18 R4

    iSTD_SQUARE_BRACKET_RIGHT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_9,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_QUOTATION_SIGN, iKEY_TYPE_STD|iKEY_PRESS,
    iMODE_KEY_FN,       iKEY_TYPE_SPECIAL,
// C9
    iSTD_S,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SUBTRACT,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F8,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_4,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_LEFT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_8,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_INSERT,        iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_N,             iKEY_TYPE_STD|iKEY_PRESS,
// C10
    iSTD_W,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_BACKSPACE,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F11,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SNAPSHOT,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_HOME,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DELETE,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_H,             iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_FULLSTOP,      iKEY_TYPE_STD|iKEY_PRESS,
// C11
    iSTD_Q,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_J,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F10,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_YEN,  iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_BACKSLASH,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_0,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEDOWN,      iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_COMMA,         iKEY_TYPE_STD|iKEY_PRESS,
// C12
    iSTD_B,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_SUBTRACT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_C,             iKEY_TYPE_STD|iKEY_PRESS,           // C19 R0
    iSTD_NUMLOCK,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD7,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD4,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD1,       iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_3,             iKEY_TYPE_STD|iKEY_PRESS,           // C19 R1
// C13
    iSTD_V,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_5,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_VOLUMEUP_L,    iKEY_TYPE_MMK | iMMK_VOLUMEUP_H,    // C19 R3
    iSTD_NUMPAD_DIVIDE, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD8,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD5,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD2,       iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_NUMPAD0,       iKEY_TYPE_STD|iKEY_PRESS,
// C14
    iSTD_R,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_6,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_VOLUMEDOWN_L,  iKEY_TYPE_MMK | iMMK_VOLUMEDOWN_H,  // C19 R4
    iSTD_NUMPAD_MULTIPLY, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD9,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD6,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD3,       iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_NUMPAD_FULLSTOP, iKEY_TYPE_STD|iKEY_PRESS,
// C15
    iSTD_E,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_L,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F12,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SCROLL,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAUSE,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEUP,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_EUROPE1,       iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_SLASH,         iKEY_TYPE_STD|iKEY_PRESS,
// C16
    iSTD_A,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F4,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_O,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_CALCULATOR_L,  iKEY_TYPE_MMK | iMMK_CALCULATOR_H,
    iSTD_QUROPE2,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_LANG1, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_LANG2, iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_GUI,
// C17
    iSTD_SPACE,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_I,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_RO,   iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_GUI,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL, // C19 R6
    iSTD_KEYBOARD_MUHENKAN, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_KEYBOARD_HENKAN, iKEY_TYPE_STD|iKEY_PRESS,    //
    iSTD_KEYBOARD_KATAKANA_HIRAGANA, iKEY_TYPE_STD|iKEY_PRESS,
/*// C18
    iSTD_Z,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_1,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,
// C19
    iSTD_C,             iKEY_TYPE_STD|iKEY_PRESS,           // C19 R0
    iSTD_3,             iKEY_TYPE_STD|iKEY_PRESS,           // C19 R1
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iMMK_VOLUMEUP_L,    iKEY_TYPE_MMK | iMMK_VOLUMEUP_H,    // C19 R3
    iMMK_VOLUMEDOWN_L,  iKEY_TYPE_MMK | iMMK_VOLUMEDOWN_H,  // C19 R4
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL, // C19 R6
    iSTD_NULL,          iKEY_TYPE_INVALID,*/
};
//-----------------------------------------------------------------------------;

#endif
