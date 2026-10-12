/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: Main.h
*
* 功能说明: 主函数头文件
* 修改说明:
*******************************************************************************/
#ifndef _MAIN_24G_H_
#define _MAIN_24G_H_

//----------------------------------------------------------------------------;
// 外部头文件引用
//
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "om_driver.h"

#include "main.h"

#include "matrix_key.h"
#include "led.h"
#include "lvd.h"
#include "wheel.h"

#include "sleep.h"
#include "userdefined_key.h"
#include "time_delay.h"

#include "flash.h"
#include "flash_process.h"

#include "rf_hardware.h"
#include "rf_protocol.h"
#include "rf_data_process.h"

//=============================================================================;
// 配置引用区                                                                   ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define iTICK_INIT_VALUE        mRTC_US(4000)
#define iTICK_INIT_VALUE_EX     mRTC_US(4050)   // 在非连接情况下故意错开时序
#define iTICK_INIT_SLEEP        mRTC_US(16000)  //

#define iOUT_RX_END             (mRTC_US(2650))

#define iRF_TX_MAX              (mRTC_US(2500))

#define iRF_RX_VALUE            (mRTC_US(500))

#define iTCC_SYNC_ADJUST        6
#define iTCC_RSP_ADJUST         6
//
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------;
// 配置常量定义区
//
#define iMCU_MODE_MASK          3

#define iMCU_MODE_NORMAL        0
#define iMCU_MODE_SLEEP         1
#define iMCU_MODE_NO_DONGLE     2
#define iMCU_MODE_PD            3

//-----------------------------------------------------------------------------;
// 配置区
//
extern unsigned char            in_report_data[];
extern unsigned char            out_report_data[];
extern uint32_t                 adv_interval_ms;

/*******************************************************************************

*******************************************************************************/
#define mMCU_MODE_NORMAL        {work_mode = iMCU_MODE_NORMAL;}
#define mMCU_MODE_SLEEP         {work_mode = iMCU_MODE_SLEEP;}
#define mMCU_MODE_NO_DONGLE     {work_mode = iMCU_MODE_NO_DONGLE;}
#define mMCU_MODE_PD            {work_mode = iMCU_MODE_PD;}

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
// 内部定义外部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern bool                 b24g_nromal;

extern uint16_t             rf_ctrl_reg;
//{
  #define brf_freq_swtich       (1<<15)
  #define brf_rx_status         (1<<14)
  #define brf_tx_status         (1<<13)
  #define brf_work_status       (1<<12)

  #define brf_cmd_tx            (1<<10)
  #define brf_sync_result       (1<<9)
  #define brf_sync_end          (1<<8)

  #define brf_conn_null         (1<<7)
  #define bsearch_dongle        (1<<6)
  #define brf_sync_time         (1<<5)
  #define brf_sync_status       (1<<4)
  #define brf_data_tx           (1<<3)
  #define brf_data_rx           (1<<2)
  #define brf_mode_1            (1<<1)
  #define brf_mode_0            (1<<0)
//}

extern volatile uint8_t     rf_work_mode;
//{
    #define iRF_WORK_TX0    0
    #define iRF_WORK_TX1    1
    #define iRF_WORK_RX     2
    #define iRF_WORK_IDLE   3
//}

extern unsigned char        dat_24g_0[];
extern unsigned char        dat_24g_1[];

extern uint8_t              rf_data_fifo[32];

#define rf_lenght           dat_24g_0[20]
#define freq_index          dat_24g_0[21]
#define rf_rsp_time_count   dat_24g_0[22]
#define rf_rsp_fail_count   dat_24g_0[23]

#define requst_cmd          dat_24g_0[24]
#define rf_irq_status       dat_24g_0[25]
#define rf_mode_type        dat_24g_0[26]

#define work_mode           dat_24g_0[27]

#define freq_hop            dat_24g_1     // 16Byte
//{
    #define freq_sync_0     dat_24g_1[0]
    #define freq_sync_1     dat_24g_1[1]
//}
#define key_data_1          dat_24g_1[16]
#define mouse_x_1           dat_24g_1[17]
#define mouse_y_1           dat_24g_1[18]
#define mouse_xy_1          dat_24g_1[19]

#define key_data_2          dat_24g_1[20]
#define mouse_x_2           dat_24g_1[21]
#define mouse_y_2           dat_24g_1[22]
#define mouse_xy_2          dat_24g_1[23]

#define mouse_x_3           dat_24g_1[24]
#define mouse_y_3           dat_24g_1[25]
#define mouse_xy_3          dat_24g_1[26]
#define mouse_z             dat_24g_1[27]

#define rf_data_length      dat_24g_1[28]
#define pkt_press_count     dat_24g_1[29]

#define rsp_freq            dat_24g_1[30]
#define tx0_freq            dat_24g_1[31]

#define connect_time_count  adv_interval_ms
#define sync_time_count     adv_interval_ms

extern unsigned int         sync_word;
extern volatile uint32_t    rtc_reload_value;


//-----------------------------------------------------------------------------;
// 函数引用
//
extern void mouse_24g_init(void);
extern int main_24g(void);
//
//-----------------------------------------------------------------------------;
#endif
