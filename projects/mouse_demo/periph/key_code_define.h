/*******************************************************************************
* Copyright (c) 2013, SHENZHEN OM Co.,LTD.
* All rights reserved.
*
* 文件名称: key_code_define.h
* 文件描述:
*******************************************************************************/
#ifndef _KEY_CODE_DEFINE_H_
#define _KEY_CODE_DEFINE_H_

//=============================================================================//
//常量定义                                                                     //
//=============================================================================//

//-----------------------------------------------------------------------------;
// 按键类型
//
#define iKEY_STD_MASK           0xC0
#define iKEY_TRANSFER_MASK      0xE0
#define iDEF_DELAY_MASK         0xE0
#define iKEY_TYPE_MASK          0xF0

#define iKEY_TYPE_STD           0x00
#define iKEY_TYPE_EX            0x40
//{
    #define iKEY_TYPE_SYS       0x40
    #define iKEY_TYPE_MOUSE     0x41
    #define iKEY_TYPE_WHEEL     0x42
    #define iKEY_TYPE_FIRE      0x43
    #define iDEF_MOUSE_X        0x44
    #define iDEF_MOUSE_Y        0x45

    #define iKEY_TYPE_SPECIAL   0x48
    //{
      #define iKEY_SPECIAL_MASK 0xF0

      #define iDEF_SYS_CTRL     0x00
      //{
        #define iDEF_DPI_SUB      0x00
        #define iDEF_DPI_ADD      0x01
        #define iDEF_DPI_CYC_ADD  0x02
        #define iDEF_MODE_SUB     0x03
        #define iDEF_MODE_ADD     0x04
        #define iDEF_MODE_CYC_ADD 0x05
        #define iDEF_REPORT_SUB   0x06
        #define iDEF_REPORT_ADD   0x07
        #define iDEF_REPORT_CYC_ADD 0x08
        #define iDEF_LOCK_KEY     0x09          // 锁键
        #define iDEF_SNIPER_ADD   0x0A          // 狙击键
        #define iDEF_SNIPER_SUM   0x0B          // 狙击键
        #define iDEF_RUNNING_FIRE 0x0C          // 组合连发键
      //}
      #define iLED_CTRL           0x10
      //{
        #define iLED_BRIGHT_SUB   0x10          //-------------------
        #define iLED_BRIGHT_ADD   0x11          //
        #define iLED_BRIGHT_CYC_ADD 0x12        //
        #define iLED_MODE_SUB     0x13          //   背
        #define iLED_MODE_ADD     0x14          //   光
        #define iLED_MODE_CYC_ADD 0x15          //   控
        #define iLED_SPEED_SUB    0x16          //   制
        #define iLED_SPEED_ADD    0x17          //
        #define iLED_SPEED_CYC_ADD 0x18         //
        #define iLED_DIR_L_R      0x19          //
        #define iLED_DIR_R_L      0x1A          //
        #define iLED_DIR_CYC      0x1B          //-------------------

        #define iLED_OFF          0x1C
        #define iLED_RGB_SWTICH   0x1D
      //}
      #define iFLANK_CTRL         0x20
      //{
        #define iFLANK_LIGHT_SUB  0x20          //-------------------
        #define iFLANK_LIGHT_ADD  0x21          //
        #define iFLANK_LIGHT_CYC_ADD 0x22       //  侧
        #define iFLANK_MODE_SUB   0x23          //  灯
        #define iFLANK_MODE_ADD   0x24          //  控
        #define iFLANK_MODE_CYC_ADD 0x25        //  制
        #define iFLANK_SPEED_SUB  0x26         //
        #define iFLANK_SPEED_ADD  0x27         //
        #define iFLANK_SPEED_CYC_ADD 0x28       //-------------------
        #define iFLANK_OFF        0x29
        #define iFLANK_RGB_SWTICH 0x2A
      //}
      #define iKEY_MODE_SWITCH    0x30
      //{
        #define iMODE_KEY_FN      0x30
        #define iMODE_KEY_USB     0x31
        #define iMODE_KEY_BT0     0x32
        #define iMODE_KEY_BT1     0x33
        #define iMODE_KEY_BT2     0x34
        #define iMODE_KEY_24G     0x35
        #define iKEY_CTRL_PRESS   0x36
        #define iKEY_CTRL_REALSE  0x37

        #define iKEY_FN_LOCK      0x38
        #define iKEY_WIN          0x39
        #define iKEY_MAC          0x3A
        #define iKEY_WIN_MAC      0x3B
        #define iKEY_WIN_LOCK     0x3C
        #define iKEY_DIR_LOCK     0x3E
        #define iKEY_WHEEL        0x3F
      //}
      #define iKEY_EX_FUN         0x40
      //{
        #define iKEY_DEFAULT      0x40
        #define iKEY_ALT_TAB      0x41
        #define iKEY_CMD_TAB      0x42
        #define iKEY_CTRL_SPACE   0x43
        #define iKEY_CMD_SPACE    0x44
        #define iKEY_DESK_MAC     0x45
      //}
    //}
//}
#define iKEY_TYPE_MMK           0x50
//{
    #define iKEY_MMK_MASK       0xF0
//}
#define iDEFINE_CMD_TRANSFER    0x60
//{
    #define iTRANSFER_MASK      0x18
    #define iTRANSFER_KEY_STATUS 0x08
    #define iTRANSFER_TIMES     0x10
//}
#define iDEF_DELAY              0xC0
#define iDEF_COM                0x80
//{
    #define iDEF_COM_MASK       0xC0

    #define iREALSE_NO_DID      0               // 松开不处理
    #define iREALSE_DID         1               // 松开处理

    #define iDIS_KEY_BREAK      0               // 按键不可打断
    #define iEN_KEY_BREAK       1               // 按键可打断
//}
#define iKEY_TYPE_INVALID       0xFF
//{
    #define iINVALID_KEY 0xFF
//}
//-----------------------------------------------------------------------------;
// 系统键键值
//
#define iSYS_POWER                      0x01
#define iSYS_SLEEP                      0x02
#define iSYS_WAKEUP                     0x04

//-----------------------------------------------------------------------------;
// 标准键键值
//
#define iSTD_NULL                       0x00
#define iSTD_KEY                        0x00
#define iFUNTION_KEY                    0x01
#define iDIR_SW_KEY                     0x02
#define iKEY_PRESS                      0x20
#define iKEY_REALSE                     0x00
                                        
#define iSTD_ALL                        0x00
#define iSTD_A                          0x04
#define iSTD_B                          0x05
#define iSTD_C                          0x06
#define iSTD_D                          0x07
#define iSTD_E                          0x08
#define iSTD_F                          0x09
#define iSTD_G                          0x0A
#define iSTD_H                          0x0B
#define iSTD_I                          0x0C
#define iSTD_J                          0x0D
#define iSTD_K                          0x0E
#define iSTD_L                          0x0F
#define iSTD_M                          0x10
#define iSTD_N                          0x11
#define iSTD_O                          0x12
#define iSTD_P                          0x13
#define iSTD_Q                          0x14
#define iSTD_R                          0x15
#define iSTD_S                          0x16
#define iSTD_T                          0x17
#define iSTD_U                          0x18
#define iSTD_V                          0x19
#define iSTD_W                          0x1A
#define iSTD_X                          0x1B
#define iSTD_Y                          0x1C
#define iSTD_Z                          0x1D
#define iSTD_1                          0x1E
#define iSTD_2                          0x1F
#define iSTD_3                          0x20
#define iSTD_4                          0x21
#define iSTD_5                          0x22
#define iSTD_6                          0x23
#define iSTD_7                          0x24
#define iSTD_8                          0x25
#define iSTD_9                          0x26
#define iSTD_0                          0x27
#define iSTD_ENTER                      0x28    // Enter
#define iSTD_RETURN                     0x28    // Enter

#define iSTD_ESCAPE                     0x29    // Escape
#define iSTD_BACKSPACE                  0x2A    // Backspace
#define iSTD_TAB                        0x2B
#define iSTD_SPACE                      0x2C
#define iSTD_SUBTRACT                   0x2D    // - _
#define iSTD_ADD                        0x2E    // = +
#define iSTD_SQUARE_BRACKET_LEFT        0x2F    // [ {
#define iSTD_SQUARE_BRACKET_RIGHT       0x30    // ] }
#define iSTD_BACKSLASH                  0x31    // \ |  
#define iSTD_EUROPE1                    0x32    // Europe 1 (Note 2) // K42
#define iSTD_SEMICOLON                  0x33    // ; :
#define iSTD_QUOTATION_SIGN             0x34    // ' "
#define iSTD_WAVE                       0x35    // ` ~
#define iSTD_COMMA                      0x36    // , <
#define iSTD_FULLSTOP                   0x37    // . >
#define iSTD_SLASH                      0x38    // / ?
#define iSTD_CAPITAL                    0x39    // Caps Lock
#define iSTD_F1                         0x3A
#define iSTD_F2                         0x3B
#define iSTD_F3                         0x3C
#define iSTD_F4                         0x3D
#define iSTD_F5                         0x3E
#define iSTD_F6                         0x3F
#define iSTD_F7                         0x40
#define iSTD_F8                         0x41
#define iSTD_F9                         0x42
#define iSTD_F10                        0x43
#define iSTD_F11                        0x44
#define iSTD_F12                        0x45
#define iSTD_SNAPSHOT                   0x46    // Print Screen
#define iSTD_SCROLL                     0x47    // Scroll Lock
#define iSTD_CANCEL                     0x48    // Break
#define iSTD_PAUSE                      0x48
#define iSTD_INSERT                     0x49
#define iSTD_HOME                       0x4A
#define iSTD_PAGEUP                     0x4B
#define iSTD_DELETE                     0x4C
#define iSTD_END                        0x4D
#define iSTD_PAGEDOWN                   0x4E
#define iSTD_RIGHT                      0x4F
#define iSTD_LEFT                       0x50
#define iSTD_DOWN                       0x51
#define iSTD_UP                         0x52
#define iSTD_NUMLOCK                    0x53
#define iSTD_NUMPAD_DIVIDE              0x54    // Keypad /
#define iSTD_NUMPAD_MULTIPLY            0x55    // Keypad *
#define iSTD_NUMPAD_SUBTRACT            0x56    // Keypad -
#define iSTD_NUMPAD_ADD                 0x57    // Keypad +
#define iSTD_NUMPAD_ENTER               0x58    // Keypad Enter
#define iSTD_NUMPAD1                    0x59
#define iSTD_NUMPAD2                    0x5A
#define iSTD_NUMPAD3                    0x5B
#define iSTD_NUMPAD4                    0x5C
#define iSTD_NUMPAD5                    0x5D
#define iSTD_NUMPAD6                    0x5E
#define iSTD_NUMPAD7                    0x5F
#define iSTD_NUMPAD8                    0x60
#define iSTD_NUMPAD9                    0x61
#define iSTD_NUMPAD0                    0x62
#define iSTD_NUMPAD_FULLSTOP            0x63    // Keypad . Delete
#define iSTD_QUROPE2                    0x64    // Europe 2 (Note 2)  // K45
#define iSTD_APP                        0x65
#define iSTD_KEYBOARD_POWER             0x66
#define iSTD_NUMPAD_EQUAL_SIGN          0x67    // Keypad =
#define iSTD_F13                        0x68
#define iSTD_F14                        0x69
#define iSTD_F15                        0x6A
#define iSTD_F16                        0x6B
#define iSTD_F17                        0x6C
#define iSTD_F18                        0x6D
#define iSTD_F19                        0x6E
#define iSTD_F20                        0x6F
#define iSTD_F21                        0x70
#define iSTD_F22                        0x71
#define iSTD_F23                        0x72
#define iSTD_F24                        0x73
#define iSTD_KEYBOARD_EXECUTE                    0x74
#define iSTD_KEYBOARD_HELP                       0x75
#define iSTD_KEYBOARD_MENU                       0x76
#define iSTD_KEYBOARD_SELECT                     0x77
#define iSTD_KEYBOARD_STOP                       0x78
#define iSTD_KEYBOARD_AGAIN                      0x79
#define iSTD_KEYBOARD_UNDO                       0x7A
#define iSTD_KEYBOARD_CUT                        0x7B
#define iSTD_KEYBOARD_COPY                       0x7C
#define iSTD_KEYBOARD_PASTE                      0x7D
#define iSTD_KEYBOARD_FIND                       0x7E
#define iSTD_KEYBOARD_MUTE                       0x7F
#define iSTD_KEYBOARD_VOLUMEUP                   0x80
#define iSTD_KEYBOARD_VOLUMEDOWN                 0x81
#define iSTD_KEYBOARD_CAPITAL                    0x82
#define iSTD_KEYBOARD_NUMLOCK                    0x83
#define iSTD_KEYBOARD_SCROLL                     0x84
#define iSTD_KEYBOARD_NUMPAD_COMMA               0x85 // k107
#define iSTD_KEYBOARD_QUEAL_SIGN                 0x86
#define iSTD_KEYBOARD_RO                         0x87 // K56
#define iSTD_KEYBOARD_KATAKANA_HIRAGANA          0x88 // K133  ROMA
#define iSTD_KEYBOARD_YEN                        0x89 // k14
#define iSTD_KEYBOARD_HENKAN                     0x8A // k132  CHG
#define iSTD_KEYBOARD_MUHENKAN                   0x8B // k131  N-CHG
#define iSTD_KEYBOARD_PC9800_COMMA               0x8C
#define iSTD_KEYBOARD_INTL7                      0x8D
#define iSTD_KEYBOARD_INTL8                      0x8E
#define iSTD_KEYBOARD_INTL9                      0x8F
#define iSTD_KEYBOARD_LANG1                      0x90 // K151 KR
#define iSTD_KEYBOARD_LANG2                      0x91 // K150 KL
#define iSTD_KEYBOARD_LANG3                      0x92
#define iSTD_KEYBOARD_LANG4                      0x93
#define iSTD_KEYBOARD_LANG5                      0x94
#define iSTD_KEYBOARD_LANG6                      0x95
#define iSTD_KEYBOARD_LANG7                      0x96
#define iSTD_KEYBOARD_LANG8                      0x97
#define iSTD_KEYBOARD_LANG9                      0x98
#define iSTD_KEYBOARD_ALTERNATE_ERASE            0x99
#define iSTD_KEYBOARD_SYSREQ                     0x9A
#define iSTD_KEYBOARD_CANCEL                     0x9B
#define iSTD_KEYBOARD_CLEAR                      0x9C
#define iSTD_KEYBOARD_PRIOR                      0x9D
#define iSTD_KEYBOARD_RETURN                     0x9E
#define iSTD_KEYBOARD_SEPARATOR                  0x9F
#define iSTD_KEYBOARD_OUT                        0xA0
#define iSTD_KEYBOARD_OPER                       0xA1
#define iSTD_KEYBOARD_CLEAR_AGAIN                0xA2
#define iSTD_KEYBOARD_CRSEL_PROPS                0xA3
#define iSTD_KEYBOARD_EXSEL                      0xA4

//-----------------------------------------------------------------------------;
// 多功能键值
//
#define iLEFT_CTRL                      0x11
#define iLEFT_SHIFT                     0x12
#define iLEFT_ALT                       0x14
#define iLEFT_GUI                       0x18    //左windows
#define iRIGHT_CTRL                     0x01
#define iRIGHT_SHIFT                    0x02
#define iRIGHT_ALT                      0x04
#define iRIGHT_GUI                      0x08    //右windows

//-----------------------------------------------------------------------------;
// 多媒体键键值
//
#define iMMK_IOS_SIRI_H         0x00
#define iMMK_IOS_SIRI_L         0xCF

#define iMMK_BRIGHT_ADD_H       0x00
#define iMMK_BRIGHT_ADD_L       0x6F
#define iMMK_BRIGHT_SUM_H       0x00
#define iMMK_BRIGHT_SUM_L       0x70

#define iMMK_NEXT_TRACK_H       0x00
#define iMMK_NEXT_TRACK_L       0xB5
#define iMMK_PREV_TRACK_H       0x00
#define iMMK_PREV_TRACK_L       0xB6
#define iMMK_STOP_H             0x00
#define iMMK_STOP_L             0xB7
#define iMMK_PLAY_PAUSE_H       0x00
#define iMMK_PLAY_PAUSE_L       0xCD
#define iMMK_MUTE_H             0x00
#define iMMK_MUTE_L             0xE2
#define iMMK_BASS_BOOST_H       0x00
#define iMMK_BASS_BOOST_L       0xE5
#define iMMK_LOUDNESS_H         0x00
#define iMMK_LOUDNESS_L         0xE7
#define iMMK_VOLUMEUP_H         0x00
#define iMMK_VOLUMEUP_L         0xE9
#define iMMK_VOLUMEDOWN_H       0x00
#define iMMK_VOLUMEDOWN_L       0xEA
#define iMMK_BASS_UP_H          0x01
#define iMMK_BASS_UP_L          0x52
#define iMMK_BASS_DOWN_H        0x01
#define iMMK_BASS_DOWN_L        0x53
#define iMMK_TREBLE_UP_H        0x01
#define iMMK_TREBLE_UP_L        0x54
#define iMMK_TREBLE_DOWN_H      0x01
#define iMMK_TREBLE_DOWN_L      0x55
#define iMMK_MEDIA_SELECT_H     0x01
#define iMMK_MEDIA_SELECT_L     0x83
#define iMMK_MAIL_H             0x01
#define iMMK_MAIL_L             0x8A
#define iMMK_CALCULATOR_H       0x01
#define iMMK_CALCULATOR_L       0x92
#define iMMK_MY_COMPUTER_H      0x01
#define iMMK_MY_COMPUTER_L      0x94
#define iMMK_WWW_SEARCH_H       0x02
#define iMMK_WWW_SEARCH_L       0x21
#define iMMK_WWW_HOME_H         0x02
#define iMMK_WWW_HOME_L         0x23
#define iMMK_WWW_BACK_H         0x02
#define iMMK_WWW_BACK_L         0x24
#define iMMK_WWW_FORWARD_H      0x02
#define iMMK_WWW_FORWARD_L      0x25
#define iMMK_WWW_STOP_H         0x02
#define iMMK_WWW_STOP_L         0x26
#define iMMK_WWW_REFRESH_H      0x02
#define iMMK_WWW_REFRESH_L      0x27
#define iMMK_WWW_FAVORITES_H    0x02
#define iMMK_WWW_FAVORITES_L    0x2A
//
//-----------------------------------------------------------------------------;

#endif
