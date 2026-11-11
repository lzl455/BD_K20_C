/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: UserDefined_Key.h
*
* 功能说明: 
* 修改说明:
*******************************************************************************/
#ifndef _USERDEFINED_KEY_H_
#define _USERDEFINED_KEY_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//

//-----------------------------------------------------------------------------;
//配置区
//

//=============================================================================;
// 外部定义内部引用区
//=============================================================================;

//=============================================================================;
// 外部寄存器引用
//
extern bool                     bkey_break_or_realse;

extern unsigned char            define_key_status;
//{
    #define bkey_status_change  (1<<0)
//}

extern unsigned char        define_key_ctrl;
//{
    #define bdefine_key_send    (1<<7)
    #define bdpi_fast_change    (1<<6)
    #define bmouse_key_press    (1<<5)
    #define bcom_decode_ing     (1<<4)
    #define bcom_key_break      (1<<3)
//}

extern uint8_t                  decode_data_l;
//{
    #define bkey_code_b7        (1<<7)
    #define bkey_code_b6        udecode_data_l.BIT.b6
    #define bkey_code_b5        udecode_data_l.BIT.b5
    #define bkey_code_b4        udecode_data_l.BIT.b4
    #define bkey_code_b3        udecode_data_l.BIT.b3
    #define bkey_code_b2        udecode_data_l.BIT.b2
    #define bkey_code_b1        udecode_data_l.BIT.b1
    #define bkey_code_b0        udecode_data_l.BIT.b0
//}
extern uint8_t                  decode_data_h;
//{
    #define bkey_code_b15       udecode_data_h.BIT.b7
    #define bkey_code_b14       udecode_data_h.BIT.b6
    #define bkey_code_b13       (1<<5)
    #define bkey_code_b12       (1<<4)
    #define bkey_code_b11       (1<<3)
    #define bkey_code_b10       udecode_data_h.BIT.b2
    #define bkey_code_b9        udecode_data_h.BIT.b1
    #define bkey_code_b8        udecode_data_h.BIT.b0
//}

extern unsigned char            define_key_fifo[];
extern unsigned char            com_key_index;

#define define_key_flag_n       define_key_fifo[decode_index]

extern unsigned char            define_key_flag;
//{
    #define bcom_key_realse_did (1<<6)
    #define bdefine_delay_flag  (1<<5)
    #define bdefine_key_com     (1<<4)
    #define bkb_led_back        (1<<3)
    #define bdefine_key_press   (1<<2)
    #define bkey_decode_end     (1<<1)
    #define bkey_decode         (1<<0)
//}
//=============================================================================;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部引用区
//=============================================================================;

//=============================================================================;
// 寄存器引用
//

//=============================================================================;
// 函数引用
//
extern void define_key_process(void);

#endif
