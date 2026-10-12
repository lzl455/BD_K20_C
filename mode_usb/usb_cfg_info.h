/*******************************************************************************
* Copyright (c) 2012, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: USB_Cfg_Info.h
* 文件描述: USB库文件配置头文件
* 版    本: V1.0.0
* 作    者: 易谦
* 日    期: 2022/3/18
*******************************************************************************/
#ifndef _USB_CFG_INFO_
#define _USB_CFG_INFO_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define iREPORT_ID_MOUSE        0x02
#define iREPORT_ID_MULTIM_KEY   0x01
#define iREPORT_ID_KB_KEY       0x05
#define iREPORT_ID_CUSTOMER_DATA 0x0E

//每个Endpoint的FIFO的size
#define USB_EP0_FIFO_SIZE        0x020
#define USB_EP1_FIFO_SIZE        0x008
#define USB_EP2_FIFO_SIZE        0x020
#define USB_EP3_FIFO_SIZE        0x040

// Define device states
#define DEV_ATTACHED            0x00            // Device is in Attached State
#define DEV_POWERED             0x01            // Device is in Powered State
#define DEV_DEFAULT             0x02            // Device is in Default State
#define DEV_ADDRESS             0x03            // Device is in Addressed State
#define DEV_CONFIGURED          0x04            // Device is in Configured State
#define DEV_SUSPENDED           0x05            // Device is in Suspended State

// Define Endpoint States
#define EP_IDLE                 0x00            // This signifies Endpoint Idle State
#define EP_TX                   0x01            // Endpoint Transmit State
#define EP_RX                   0x02            // Endpoint Receive State
#define EP_HALT                 0x03            // Endpoint Halt State (return stalls)
#define EP_STALL                0x04
#define EP_ADDRESS              0x05

//-----------------------------------------------------------------------------;
//配置区
//

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//

//-----------------------------------------------------------------------------;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部部引用区                                                        ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern bool                     busb_mouse_in_en;
extern bool                     bkey_mode_change;

extern unsigned char            usb_ctrl_flag;
//{
    #define bep1_ep2_enable     (1<<5)
    #define bapple              (1<<4)

    #define busb_report_set     (1<<3)
    #define busb_suspend_resume (1<<2)
    #define bwakeup_usb_enable  (1<<1)
    #define bsleep_eable        (1<<0)
//}

extern unsigned char            g_USB_Ep_Status[4];
extern unsigned char            g_USB_State;

//-----------------------------------------------------------------------------;
// 函数引用
//
extern void usb_data_process(void);
//
//----------------------------------------------------------------------------;

#endif

