/* ----------------------------------------------------------------------------
 * Copyright (c) 2020-2030 OnMicro Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of OnMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -------------------------------------------------------------------------- */

/**
 * @file     keyboard.h
 * @brief    keyboard
 * @date     20. Aug 2024
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


#ifndef __KEYBOARD_H
#define __KEYBOARD_H


/*******************************************************************************
 * INCLUDES
 */
// #include "key_io.h"


/*******************************************************************************
 * MACROS
 */
/* 借用不用的中断向量表存储同步字（SVC_Handler之后）*/
#define CFG_START_SYNC_WORD_ADDR            0x30

#define KEYBOARD_NAME_MAX_LEN         11U


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @brief HID keyboard button codes.
 */
typedef enum {
    HID_KBD_CODE_A = 4,
    HID_KBD_CODE_B = 5,
    HID_KBD_CODE_C = 6,
    HID_KBD_CODE_D = 7,
    HID_KBD_CODE_E = 8,
    HID_KBD_CODE_F = 9,
    HID_KBD_CODE_G = 10,
    HID_KBD_CODE_H = 11,
    HID_KBD_CODE_I = 12,
    HID_KBD_CODE_J = 13,
    HID_KBD_CODE_K = 14,
    HID_KBD_CODE_L = 15,
    HID_KBD_CODE_M = 16,
    HID_KBD_CODE_N = 17,
    HID_KBD_CODE_O = 18,
    HID_KBD_CODE_P = 19,
    HID_KBD_CODE_Q = 20,
    HID_KBD_CODE_R = 21,
    HID_KBD_CODE_S = 22,
    HID_KBD_CODE_T = 23,
    HID_KBD_CODE_U = 24,
    HID_KBD_CODE_V = 25,
    HID_KBD_CODE_W = 26,
    HID_KBD_CODE_X = 27,
    HID_KBD_CODE_Y = 28,
    HID_KBD_CODE_Z = 29,
    HID_KBD_CODE_1 = 30,
    HID_KBD_CODE_2 = 31,
    HID_KBD_CODE_3 = 32,
    HID_KBD_CODE_4 = 33,
    HID_KBD_CODE_5 = 34,
    HID_KBD_CODE_6 = 35,
    HID_KBD_CODE_7 = 36,
    HID_KBD_CODE_8 = 37,
    HID_KBD_CODE_9 = 38,
    HID_KBD_CODE_0 = 39,
    HID_KBD_CODE_ENTER = 40,
    HID_KBD_CODE_ESC = 41,
    HID_KBD_CODE_BACKSPACE = 42,
    HID_KBD_CODE_TAB = 43,
    HID_KBD_CODE_SPACE = 44,
    HID_KBD_CODE_MINUS = 45,
    HID_KBD_CODE_EQUAL = 46,
    HID_KBD_CODE_LEFTBRACE = 47,
    HID_KBD_CODE_RIGHTBRACE = 48,
    HID_KBD_CODE_BACKSLASH = 49,
    HID_KBD_CODE_HASH = 50, /* Non-US # and ~ */
    HID_KBD_CODE_SEMICOLON = 51,
    HID_KBD_CODE_APOSTROPHE = 52,
    HID_KBD_CODE_GRAVE = 53,
    HID_KBD_CODE_COMMA = 54,
    HID_KBD_CODE_DOT = 55,
    HID_KBD_CODE_SLASH = 56,
    HID_KBD_CODE_CAPSLOCK = 57,
    HID_KBD_CODE_F1 = 58,
    HID_KBD_CODE_F2 = 59,
    HID_KBD_CODE_F3 = 60,
    HID_KBD_CODE_F4 = 61,
    HID_KBD_CODE_F5 = 62,
    HID_KBD_CODE_F6 = 63,
    HID_KBD_CODE_F7 = 64,
    HID_KBD_CODE_F8 = 65,
    HID_KBD_CODE_F9 = 66,
    HID_KBD_CODE_F10 = 67,
    HID_KBD_CODE_F11 = 68,
    HID_KBD_CODE_F12 = 69,
    HID_KBD_CODE_SYSRQ = 70, /* PRINTSCREEN */
    HID_KBD_CODE_SCROLLLOCK = 71,
    HID_KBD_CODE_PAUSE = 72,
    HID_KBD_CODE_INSERT = 73,
    HID_KBD_CODE_HOME = 74,
    HID_KBD_CODE_PAGEUP = 75,
    HID_KBD_CODE_DELETE = 76,
    HID_KBD_CODE_END = 77,
    HID_KBD_CODE_PAGEDOWN = 78,
    HID_KBD_CODE_RIGHT = 79,
    HID_KBD_CODE_LEFT = 80,
    HID_KBD_CODE_DOWN = 81,
    HID_KBD_CODE_UP = 82,
    HID_KBD_CODE_NUMLOCK = 83,
    HID_KBD_CODE_KPSLASH = 84,    /* NUMPAD DIVIDE */
    HID_KBD_CODE_KPASTERISK = 85, /* NUMPAD MULTIPLY */
    HID_KBD_CODE_KPMINUS = 86,
    HID_KBD_CODE_KPPLUS = 87,
    HID_KBD_CODE_KPENTER = 88,
    HID_KBD_CODE_KP_1 = 89,
    HID_KBD_CODE_KP_2 = 90,
    HID_KBD_CODE_KP_3 = 91,
    HID_KBD_CODE_KP_4 = 92,
    HID_KBD_CODE_KP_5 = 93,
    HID_KBD_CODE_KP_6 = 94,
    HID_KBD_CODE_KP_7 = 95,
    HID_KBD_CODE_KP_8 = 96,
    HID_KBD_CODE_KP_9 = 97,
    HID_KBD_CODE_KP_0 = 98,
} hid_kbd_code_t;

/**
 * @brief HID keyboard modifiers.
 */
typedef enum {
    HID_KBD_MODIFIER_NONE        = 0x00,
    HID_KBD_MODIFIER_LEFT_CTRL   = 0x01,
    HID_KBD_MODIFIER_LEFT_SHIFT  = 0x02,
    HID_KBD_MODIFIER_LEFT_ALT    = 0x04,
    HID_KBD_MODIFIER_LEFT_UI     = 0x08,
    HID_KBD_MODIFIER_RIGHT_CTRL  = 0x10,
    HID_KBD_MODIFIER_RIGHT_SHIFT = 0x20,
    HID_KBD_MODIFIER_RIGHT_ALT   = 0x40,
    HID_KBD_MODIFIER_RIGHT_UI    = 0x80,
} hid_kbd_modifier_t;

/**************************广播态目前处理逻辑***********************************
1.上电，先发5秒钟快广播尝试回连，用以确保配对过换电池不用重新配对，未回连成功开始
   发送Swift广播3.5S， 后切到可发现广播广播3分钟。
2、配对完成后，PMU寄存器BLE模式里面写入值，之后正常进入深度休眠/master主动断开/
slave主动断开都快广播5s(interval 5ms), 慢广播60s不可发现广播。
*******************************************************************************/
typedef enum {
    KEYBOARD_LE_STATE_ADV        = 0,  /* 可发现广播，未配对状态使用 */
    KEYBOARD_LE_STATE_ADV_SWIFT  = 1,  /* 可发现Swift广播，未配对状态使用，鼠标弹窗 */
    KEYBOARD_LE_STATE_DISCONN_ADV= 2,  /* 不可发现广播，慢广播 */
    KEYBOARD_LE_STATE_DISCONN    = 3,  /* 不可发现广播，断开后快广播，快速回连 */
    KEYBOARD_LE_STATE_STOP       = 4,  /* 超时后停止广播 */
} keyboard_adv_state_t;


/*******************************************************************************
 * CONST & VARIABLES
 */
extern const char keyboard_name[KEYBOARD_NAME_MAX_LEN];
extern uint8_t keyboard_bd_addr[];

/*******************************************************************************
 * EXTERN FUNCTIONS
 */
extern void keyboard_rf_init(void);

extern void keyboard_bsp_init(void);

extern uint8_t keyboard_get_sleep_level(void);

extern void keyboard_set_sleep_level(uint8_t level);

extern void app_ble_evt_dispatch(uint32_t events);

extern void ex2_app_keyboard_broadcast_fsm(void);

#endif  /* __KEYBOARD_H */
