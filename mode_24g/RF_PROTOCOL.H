/*******************************************************************************
* Copyright (c) 2016, SHENZHEN HUNTERSUN Co.,LTD.
* All rights reserved.
*
* 文件名称: RF_Procotrl.h
* 文件描述: RF协议头文件

* 修改说明:
*******************************************************************************/
#ifndef _RF_PROTOCOL_H_
#define _RF_PROTOCOL_H_

//=============================================================================//
//常量定义                                                                     //
//=============================================================================//

//------------------------------------------------------------------------------
//设备类型
//
#define iRF_TYPE_MOUSE          0x40            // 鼠标
#define iRF_TYPE_KB             0x80            // 鼠标
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//RF数据类型
//
//----------------------------------------------
// dongle
//
#define iRF_TYPE_MASK           0xF0

#define iRF_D_TYPE_WAKEUP       0x01            // 挂起同步数据类型

//----------------------------------------------
// mouse
//
#define iRF_M_TYPE_CONN_RSP     0x08            // 对码应答数据类型
#define iRF_M_TYPE_CONN_RSP_1   0x67            // 对码应答数据类型
#define iRF_M_TYPE_REQUST       0x60            //

//----------------------------------------------
// kb
//
#define iRF_K_TYPE_CONN_RSP     0x09            // 对码应答数据类型
#define iRF_K_TYPE_CONN_RSP_1   0x69            // 对码应答数据类型
#define iRF_K_TYPE_RECORD       0x90            //
#define iRF_K_TYPE_PRESS        0x80            //
#define iRF_K_TYPE_KB           0x80            //
//{
    #define iRF_K_OTHER_MASK    0xE0            //

    #define iRF_K_OTHER_MMK     0x20            //
    #define iRF_K_OTHER_SYS     0x40            //
    #define iRF_K_OTHER_FN      0x41            //
    #define iRF_K_OTHER_MOUSE   0x60            //
//}
#define iRF_K_TYPE_KB_EX        0x80            //
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// RF数据包长度定义
//
#define iRF_D_LENGTH_CONN       9
#define iRF_D_LENGTH_SYNC       2
#define iRF_D_LENGTH_RSP        4
#define iRF_D_LENGTH_WAKEUP     1
#define iRF_D_LENGTH_REQUST     9               // 鼠标数据长度

//----------------------------------------------
// 共用
//
#define iRF_LENGTH_SERACH_M     8               // 单鼠标搜索数据
#define iRF_LENGTH_SERACH_MK    11              // 键鼠搜索数据
#define iRF_LENGTH_CONN_RSP     10              // 对码应答数据长度
#define iRF_LENGTH_CONN_RSP_EX  16              //
#define iRF_MK_LENGTH_8B        8               // 鼠标数据长度
#define iRF_MK_LENGTH_9B        9               //
#define iRF_MK_LENGTH_10B       10              //

//----------------------------------------------
// RF数据包长度定义
//
#define iRF_M_LENGTH_MOUSE      13              // 鼠标数据长度
//----------------------------------------------
// RF数据包长度定义
//
#define iRF_K_LENGTH_STD        8               //
#define iRF_K_LENGTH_EX         16              //
#define iRF_K_LENGTH_OTHER      3               //
#define iRF_K_LENGTH_PRESS      1               //
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//RF工作模式
//
#define iRF_MODE_NONE           0x00        // RF不工作模式
#define iRF_MODE_CONNECT        0x01        // RF对码工作模式
#define iRF_MODE_SYNC           0x02        // RF同步工作模式
#define iRF_MODE_NORMAL         0x03        // RF正常工作模式

#define iRF_MODE_MASK           0x03
//
//------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// RF同步、应答时间定义
//
#define iRF_SYNC_TIME_SHORT     17
#define iRF_SYNC_TIME_LONG      66

#define iRF_RSP_CYCLE_COUNT     8
#define iRF_RSP_CYCLE_COUNT_MIX 4

#define iRF_LOST_PACKET_COUNT   16
//
//------------------------------------------------------------------------------

/*******************************************************************************
 RF工作频点
*******************************************************************************/
// 无效同步字
#define iINVALID_SYNC_WORD      0xFFC2CC5A
#define iINVALID_SYNC_WORD_0    ((iINVALID_SYNC_WORD >> 0) & 0xFF)
#define iINVALID_SYNC_WORD_1    ((iINVALID_SYNC_WORD >> 8) & 0xFF)
#define iINVALID_SYNC_WORD_2    ((iINVALID_SYNC_WORD >> 16) & 0xFF)
#define iINVALID_SYNC_WORD_3    ((iINVALID_SYNC_WORD >> 24) & 0xFF)

// 对码同步字
#define iCONNECT_SYNC_WORD      0xFFC6E594
#define iCONNECT_SYNC_WORD_0    ((iCONNECT_SYNC_WORD >> 0) & 0xFF)
#define iCONNECT_SYNC_WORD_1    ((iCONNECT_SYNC_WORD >> 8) & 0xFF)
#define iCONNECT_SYNC_WORD_2    ((iCONNECT_SYNC_WORD >> 16) & 0xFF)
#define iCONNECT_SYNC_WORD_3    ((iCONNECT_SYNC_WORD >> 24) & 0xFF)

// 搜索同步字
#define iSEARCH_SYNC_WORD       0xFFC36562
#define iSEARCH_SYNC_WORD_0     ((iSEARCH_SYNC_WORD >> 0) & 0xFF)
#define iSEARCH_SYNC_WORD_1     ((iSEARCH_SYNC_WORD >> 8) & 0xFF)
#define iSEARCH_SYNC_WORD_2     ((iSEARCH_SYNC_WORD >> 16) & 0xFF)
#define iSEARCH_SYNC_WORD_3     ((iSEARCH_SYNC_WORD >> 24) & 0xFF)

// 广播同步字
#define iRADIO_SYNC_WORD        0xFFC72B25
#define iRADIO_SYNC_WORD_0      ((iRADIO_SYNC_WORD >> 0) & 0xFF)
#define iRADIO_SYNC_WORD_1      ((iRADIO_SYNC_WORD >> 8) & 0xFF)
#define iRADIO_SYNC_WORD_2      ((iRADIO_SYNC_WORD >> 16) & 0xFF)
#define iRADIO_SYNC_WORD_3      ((iRADIO_SYNC_WORD >> 24) & 0xFF)

// 同步字0
#define iDONGLE_PIPE            0x02
#define iMOUSE_PIPE             0x08
#define iKB_PIPE                0x09
// 同步字0
#define iMOUSE_PIPE_NO          0x00
#define iKB_PIPE_NO             0x02

// 对码频点
#define iCONNECT_FREQ_0         (2402 - 2400)
#define iCONNECT_FREQ_1         (2482 - 2400)
#define iCONNECT_FREQ_0_1MHz    (2406 - 2400)
#define iCONNECT_FREQ_1_1MHz    (2476 - 2400)

// 搜索频点
#define iSEARCH_FREQ            (2482 - 2400)
#define iSEARCH_FREQ_1MHz       (2472 - 2400)

// 频点基数
#define iFREQ_VALUE_MAX         (2480-2400)
#define iFREQ_VALUE_MIN         (2402-2400)
#define iFREQ_SUM_VALUE         23
#define iFREQ_COUNT             16          // 16个跳频频点，2个同步频点
//
//------------------------------------------------------------------------------

//=============================================================================;
// 外部定义内部引用区
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//

//-----------------------------------------------------------------------------;
// 外部函数引用
//
//=============================================================================;
// 内部定义外部引用区
//=============================================================================;

//=============================================================================;
// 内部寄存器引用
//
//

//-----------------------------------------------------------------------------;
// 内部函数引用
//
extern void rf_device_info(void);
extern void rf_normal_mode_sleep(void);

extern void rf_connect_process(void);
extern void rf_sync_process(void);
extern void rf_nromal_process(void);

extern void rf_mode_convert(unsigned char mode);

//
//------------------------------------------------------------------------------

#endif

