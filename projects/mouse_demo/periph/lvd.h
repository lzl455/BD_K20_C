/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: led.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LVD_H_
#define _LVD_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 配置常量定义区
//
#define iLOW_POWER              10               //

//----------------------------------------------
// 去抖常量定义
//
#define iLVD_DITHER_COUNT_VALUE 8              // LVD检测去抖次数

#define	POF_LVD_PIN_P23         0
#define	POF_LVD_PIN_P33         1
#define	POF_LVD_PIN_VBUS        2
#define	POF_LVD_PIN_VDD         3
#if (1)
#define	POF_THRESHOLD_0_90V     0x000
#define	POF_THRESHOLD_0_95V		0x010
#define	POF_THRESHOLD_1_00V		0x020
#define	POF_THRESHOLD_1_05V		0x030
#define	POF_THRESHOLD_1_10V		0x040
#define	POF_THRESHOLD_1_15V		0x050
#define	POF_THRESHOLD_1_20V		0x060
#define	POF_THRESHOLD_1_25V		0x070
#define	POF_THRESHOLD_1_30V		0x080
#define	POF_THRESHOLD_1_35V		0x090
#define	POF_THRESHOLD_1_40V		0x0A0
#define	POF_THRESHOLD_1_45V		0x0B0
#else
#define	POF_THRESHOLD_0_90V     
#define	POF_THRESHOLD_0_95V		0x000
#define	POF_THRESHOLD_1_00V		0x010
#define	POF_THRESHOLD_1_05V		0x020
#define	POF_THRESHOLD_1_10V		0x030
#define	POF_THRESHOLD_1_15V		0x040
#define	POF_THRESHOLD_1_20V		0x050
#define	POF_THRESHOLD_1_25V		0x060
#define	POF_THRESHOLD_1_30V		0x070
#define	POF_THRESHOLD_1_35V		0x080
#define	POF_THRESHOLD_1_40V		0x090
#define	POF_THRESHOLD_1_45V		0x0A0
#endif

#define	POF_THRESHOLD_1_70V		0x0C0
#define	POF_THRESHOLD_1_75V		0x0D0
#define	POF_THRESHOLD_1_80V		0x0E0
#define	POF_THRESHOLD_1_90V		0x0F0
#define	POF_THRESHOLD_2_00V		0x100
#define	POF_THRESHOLD_2_10V		0x110
#define	POF_THRESHOLD_2_20V		0x120
#define	POF_THRESHOLD_2_30V		0x130
#define	POF_THRESHOLD_2_40V		0x140
#define	POF_THRESHOLD_2_50V		0x150
#define	POF_THRESHOLD_2_60V		0x160
#define	POF_THRESHOLD_2_70V		0x170
#define	POF_THRESHOLD_2_80V		0x180
#define	POF_THRESHOLD_2_90V		0x190
#define	POF_THRESHOLD_3_00V		0x1A0

//----------------------------------------------
// A3版本
//
#define	POF_THRESHOLD_0_900V    0x000
#define	POF_THRESHOLD_0_925V    0x010
#define	POF_THRESHOLD_0_950V	0x020
#define	POF_THRESHOLD_0_975V	0x030
#define	POF_THRESHOLD_1_000V	0x040
#define	POF_THRESHOLD_1_025V	0x050

#define	POF_THRESHOLD_1_050V	0x060

#define	POF_THRESHOLD_1_075V	0x070
#define	POF_THRESHOLD_1_100V	0x080
#define	POF_THRESHOLD_1_125V	0x090
#define	POF_THRESHOLD_1_150V	0x0A0
#define	POF_THRESHOLD_1_175V	0x0B0
#define	POF_THRESHOLD_1_200V	0x0C0

#define	POF_THRESHOLD_1_225V	0x0D0

#define	POF_THRESHOLD_1_250V	0x0E0
#define	POF_THRESHOLD_1_275V	0x0F0
#define	POF_THRESHOLD_1_300V	0x100
#define	POF_THRESHOLD_1_325V	0x110
#define	POF_THRESHOLD_1_350V	0x120
#define	POF_THRESHOLD_1_375V	0x130

#define	POF_THRESHOLD_1_400V	0x140

#define	POF_THRESHOLD_1_425V	0x150
#define	POF_THRESHOLD_1_450V	0x160
#define	POF_THRESHOLD_1_475V	0x170
#define	POF_THRESHOLD_1_500V	0x180
#define	POF_THRESHOLD_1_525V	0x190
#define	POF_THRESHOLD_1_550V	0x1A0
//
//----------------------------------------------

#define	POF_THRESHOLD_1		    0x0D0
#define	POF_THRESHOLD_2		    0x060
#define	POF_THRESHOLD_3		    0x140
//----------------------------------------------
//
#define	iOM6239_A3_0	        0x0A18
#define	iOM6239_A3_1	        0x0B18
//----------------------------------------------
//
//              A2版本    1M下拉 2M上拉
// VALUE < 3                    0%
// VALUE < 4                    5%
// VALUE < 5                    10%
// VALUE < 6                    20%
// VALUE < 7                    30%
// VALUE < 8                    45%
// VALUE < 9                    65%
// VALUE < A                    80%
// A< VALUE                     100%

#define	iLVD_0_VALUE            0x03
#define	iLVD_90_VALUE           0x09
#define	iLVD_100_VALUE          0x0A
//---------------------------------------------
//
//              A3版本 YFK   620k下拉 1M上拉
// VALUE < 7                    0%
// VALUE < 8                    5%
// VALUE < 9                    10%
// VALUE < A                    25%
// VALUE < B                    50%
// VALUE < C                    75%
// C< VALUE                     100%

#define	iLVD_0_VALUE_A3         (0x08-1)
#define	iLVD_90_VALUE_A3        (0x13-1)
#define	iLVD_100_VALUE_A3       (0x14-1)

//-----------------------------------------------------------------------------;
// 配置区
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
// 内部定义外部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern unsigned char       bat_status; // led当前亮灭指示标志位 1:亮 0:灭
//{
    #define blvd_power_on   (1<<7)
    #define bcharging       (1<<6)
    #define bcharge_ok      (1<<5)
    #define bbat_count      (1<<4)
    #define blvd_status_3   (1<<3)
    #define blvd_status_2   (1<<2)
    #define blvd_status_1   (1<<1)
    #define blvd_status_0   (1<<0)
//}
extern bool                 bbat_update;
extern unsigned char        bat_value;
extern uint8_t              lvd_scan_count;

//-----------------------------------------------------------------------------;
// 函数引用
//
extern void usb_5v_check(void);

extern void bat_init(void);
extern unsigned char bat_voltage_check(void);
extern void led_hint_process(void);
//
//-----------------------------------------------------------------------------;
#endif