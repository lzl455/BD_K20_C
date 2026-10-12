/*******************************************************************************
* Copyright (c) 2013, SHENZHEN OM Co.,LTD.
* All rights reserved.
*
* 文件名称: main.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>
#include <stdbool.h>

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//----------------------------------------------------------------------------;
// 通用类型定义
//
#define P00     (8*0+0)         /* PWM / WHB */
#define P01     (8*0+1)         /* PWM / WHA */
#define P02     (8*0+2)         /* D- */
#define P03     (8*0+3)         /* D+ */
#define P04     (8*0+4)         /* UART TX */
#define P05     (8*0+5)        
#define P06     (8*0+6)         /* UART RX */
#define P07     (8*0+7)

#define P10     (8*1+0) 
#define P11     (8*1+1)         /* UART RX */
#define P12     (8*1+2)         /* UART TX */
#define P13     (8*1+3)
#define P14     (8*1+4)         /* FLASH */
#define P15     (8*1+5)         /* FLASH */
#define P16     (8*1+6)         /* FLASH */
#define P17     (8*1+7)         /* FLASH */

#define P20     (8*2+0)
#define P21     (8*2+1)         
#define P22     (8*2+2)         /* TCK */
#define P23     (8*2+3) 
#define P24     (8*2+4)
#define P25     (8*2+5)         /* TMS */
#define P26     (8*2+6)
#define P27     (8*2+7)

#define P30     (8*3+0)
#define P31     (8*3+1)
#define P32     (8*3+2)
#define P33     (8*3+3)
#define P34     (8*3+4)
#define P35     (8*3+5)        
#define P36     (8*3+6)
#define P37     (8*3+7)         /* BOOT */

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define RC_CLK        3200UL
//#define RC_CLK      2000000UL
#if(2000000UL == RTC)
#define mRTC_US(x)              (x*2L)   //
#else
#define mRTC_US(x)              ((x*4L) / 125L) //
#endif

#define APP_ENABLE    1                         // 0：disable；1：enable

#define RF_RATE       RF_RATE_2MHz
//{
    #define RF_RATE_1MHz      (1<<6)
    #define RF_RATE_2MHz      (0<<6)
//}
#define RF_PROTOCOL   RF_PROTOCOL_OLD
//{
    #define RF_PROTOCOL_OLD   (0<<5)
    #define RF_PROTOCOL_NEW   (1<<5)
//}
#define RF_CONN             RF_CONN_EN
//{
    #define RF_CONN_EN      1
    #define RF_CONN_DIS     0
//}

#define iSCRATCH_BOOT_POWER 0x550A5500
#define iAPP_INTO_BOOT      0x55AA55AA

//----------------------------------------------------------------------------;
// 通用类型定义
//
//----------------------------------------------
// 矩阵IO
//
#define KEY_R0_PIN              P04
#define KEY_R1_PIN              P05
#define KEY_R2_PIN              P06
#define KEY_R3_PIN              P07
#define KEY_R4_PIN              P10
#define KEY_R5_PIN              P11
#define KEY_R6_PIN              P12
#define KEY_R7_PIN              P13
#define MATRIX_RAW              ((~(OM_GPIO0->DATA)>>4)&0xFF)

#define mDELAY_R                delayus(10)
#define mDELAY_EX               delayus(10)
#define mR_OUT_H                //{OM_GPIO0->DATAOUTSET = 0x00000FF0;\
                                 //OM_GPIO0->OUTENSET = 0x00000FF0;\
                                 //OM_GPIO0->OUTENCLR = 0x00000FF0;}
//----------------------------------------------
// 扩展IO翻转顺序 PA7-PA6-PA4-PA3-PA2-PB0-PB1-PB2-PB3-PB4-PB5-PA0-PA1
//
#define KEY_C1_PIN              P25
#define KEY_C2_PIN              P26
#define KEY_C3_PIN              P27
#define KEY_C4_PIN              P30
#define KEY_C5_PIN              P31

#define KEY_C18_PIN             P24
#define KEY_C19_PIN             P22

#define KEY_EX_LOW              {OM_GPIO0->DATAOUTCLR = (1u<<P32);}
#define KEY_EX_HIGH             {OM_GPIO0->DATAOUTSET = (1u<<P32);}
#define KEY_EX_TOGGLE           {OM_GPIO0->DATAOUT   ^= (1u<<P32);}

#define MATRX_C1_LOW            {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C1_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C1_PIN);}
#define MATRX_C2_LOW            {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C2_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C2_PIN);}
#define MATRX_C3_LOW            {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C3_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C3_PIN);}
#define MATRX_C4_LOW            {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C4_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C4_PIN);}
#define MATRX_C5_LOW            {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C5_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C5_PIN);}

#define MATRX_C18_LOW           {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C18_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C18_PIN);}
#define MATRX_C19_LOW           {OM_GPIO0->DATAOUTCLR = (1u<<KEY_C19_PIN); OM_GPIO0->OUTENSET = (1u<<KEY_C19_PIN);}

#define MATRX_ALL_LOW           {OM_GPIO0->DATAOUTCLR = ((1u<<KEY_C19_PIN)|(1u<<KEY_C18_PIN)|(1u<<KEY_C5_PIN)|\
                                                        (1u<<KEY_C1_PIN)|(1u<<KEY_C2_PIN)|(1u<<KEY_C3_PIN)|(1u<<KEY_C4_PIN));\
                                 OM_GPIO0->OUTENSET = ((1u<<KEY_C19_PIN)|(1u<<KEY_C18_PIN)|(1u<<KEY_C5_PIN)|\
                                                        (1u<<KEY_C1_PIN)|(1u<<KEY_C2_PIN)|(1u<<KEY_C3_PIN)|(1u<<KEY_C4_PIN));}

#define MATRX_C1_HIGH           {OM_GPIO0->DATAOUTSET = (1u<<KEY_C1_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C1_PIN);}
#define MATRX_C2_HIGH           {OM_GPIO0->DATAOUTSET = (1u<<KEY_C2_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C2_PIN);}
#define MATRX_C3_HIGH           {OM_GPIO0->DATAOUTSET = (1u<<KEY_C3_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C3_PIN);}
#define MATRX_C4_HIGH           {OM_GPIO0->DATAOUTSET = (1u<<KEY_C4_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C4_PIN);}
#define MATRX_C5_HIGH           {OM_GPIO0->DATAOUTSET = (1u<<KEY_C5_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C5_PIN);}

#define MATRX_C18_HIGH          {OM_GPIO0->DATAOUTSET = (1u<<KEY_C18_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C18_PIN);}
#define MATRX_C19_HIGH          {OM_GPIO0->DATAOUTSET = (1u<<KEY_C19_PIN); OM_GPIO0->OUTENCLR = (1u<<KEY_C19_PIN);}

#define MATRX_ALL_IN            {OM_GPIO0->OUTENCLR = 0x03F40000;}
#define MATRX_ALL_OUT           {OM_GPIO0->OUTENSET = 0x03F40000;}
//
//----------------------------------------------
// LED
//
#define ARGB_OUT_PIN            (0*8+1)
//#define ARGB_OFF_PIN            (0*8+0)
#define UART_54E_PIN            (0*8+0)

#define VED_VDD_PIN             (2*8+3)

#define mLED_VDD_DIS            {OM_GPIO0->DATAOUTCLR = (1u<<VED_VDD_PIN);OM_GPIO0->OUTENSET = (1u<<VED_VDD_PIN);}
#define mLED_NUM_LOW            MATRX_C18_LOW
#define mLED_CAPS_LOW           MATRX_C2_LOW
#define mLED_WIN_LOW            MATRX_C1_LOW

#define mLED_VDD_EN             {OM_GPIO0->DATAOUTSET = (1u<<VED_VDD_PIN);OM_GPIO0->OUTENSET = (1u<<VED_VDD_PIN);}
#define mLED_NUM_HIGH           MATRX_C18_HIGH
#define mLED_CAPS_HIGH          MATRX_C2_HIGH
#define mLED_WIN_HIGH           MATRX_C1_HIGH
//
//----------------------------------------------
// 电源其他
//
#define CHR_OK_PIN              (OM_GPIO0->DATA & (1<<(3*8+5)))
#define USB_5V_PIN              (OM_GPIO0->DATA & (1<<(3*8+4)))
#define LVD_PIN_MASK             (1<<(3*8+3))

#define MODE_PIN                (3*8+6)
#define MODE_DATA               (OM_GPIO0->DATA & (1<<MODE_PIN))

#define mMODE_PULL_UP            OM_PMU->PAD_PU_CTRL_1 |= (2<<((MODE_PIN-16)*2));\
                                 OM_PMU->PAD_PD_CTRL &= ~(1<<(MODE_PIN))
#define mMODE_PULL_DOWN          OM_PMU->PAD_PD_CTRL |= (1<<(MODE_PIN));\
                                 OM_PMU->PAD_PU_CTRL_1 &= ~(3<<((MODE_PIN-16)*2))

#define USB_DN_PIN              (0*8+2)
#define USB_DP_PIN              (0*8+3)

#define WHA_A_PIN               (2*8+0)
#define WHA_B_PIN               (2*8+1)
//
//----------------------------------------------
// 调试IO
//
#define TIMER_PIN               (3*8+4)

#define CE_PIN                  (3*8+4)
#define IRQ_PIN                 (3*8+4)

#define UART_PIN                (3*8+6)
//
//----------------------------------------------------------------------------;

//----------------------------------------------------------------------------;
// 项目ID定义区 项目立项的时候分配的项目ID
//
#define iPROJECT_ID_H           0x073
#define iPROJECT_ID_L           0x0003

#define iPROJECT_ID_0           (iPROJECT_ID_L&0xFF)
#define iPROJECT_ID_1           ((iPROJECT_ID_L>>8)&0xFF)
#define iPROJECT_ID_2           (iPROJECT_ID_H&0xFF)
#define iPROJECT_ID_3           ((iPROJECT_ID_H>>8)&0xFF)

//----------------------------------------------------------------------------;
// 程序版本定义区 程序版本升级编号
//
#define iVERSION_ID_L           (0x80|RF_RATE|RF_PROTOCOL|0x02)
#define iVERSION_ID_H           iPROJECT_ID_0

#define iAPP_ID_H               0x02
//
//-----------------------------------------------------------------------------

#define gpio_toggle(pin)        OM_GPIO0->DATAOUT ^= (1u << pin)
#define mMS_TO_TICK(ms)         ((ms)<<5)
#define mSEN_SCAN_US(us)        ((us/ 250) - 1)

//-----------------------------------------------------------------------------;
// 唤醒配置
//
#define WAKEUP_BTN_MASK        0x01
#define WAKEUP_SENSOR_MASK     0x02
#define WAKEUP_WHEEL_MASK      0x04
#define WAKEUP_ALL_ENABLE      0x07
#define WAKEUP_ALL_DISABLE     0x00
#define WAKEUP_SLEEP_LEVEL0    (WAKEUP_ALL_DISABLE)
#define WAKEUP_SLEEP_LEVEL1    (WAKEUP_ALL_ENABLE)
#define WAKEUP_SLEEP_LEVEL2    (WAKEUP_BTN_MASK)

/**
 * @brief  Wireless Mouse RF Modes.
 */
typedef enum {
    iDEVICE_TYPE_BLE  = 1U,   /*<<< EX2_BLE mode */
    iDEVICE_TYPE_BT0  = 0U,   /*<<< EX2_BLE mode */
    iDEVICE_TYPE_BT1  = 1U,   /*<<< EX2_BLE mode */
    iDEVICE_TYPE_BT2  = 2U,   /*<<< EX2_BLE mode */
    iDEVICE_TYPE_24G  = 3U,   /*<<< OnMicro 2.4G proprietary protocol */
    iDEVICE_TYPE_USB  = 4U,
    iDEVICE_TYPE_ERR  = 5U,
} device_type_t;

//-----------------------------------------------------------------------------;
// 外部引用寄存器
//
extern bool                     brf_rate;
extern bool                     bmode_swtich_valid;

extern volatile uint8_t         ble_24g_ctrl;
//{
    #define bom6239_sync_ok (1<<3)              // 连接标志 0:没有连接;1：连接上
    #define bom6239_sync_ing (1<<2)             // 同步状态 0:没有回连；1：同步中
    #define bom6239_conn_ok (1<<1)              // 对码状态
    #define bom6239_conning (1<<0)              // 对码状态
//}

extern volatile unsigned char   sys_ctrl;
//{
    #define bmcu_reset      (1<<3)
    #define bscan_flag      (1<<2)
//}
extern uint8_t                  sys_type;
//{
    #define iSYS_IOS            3
    #define iSYS_AND            2
    #define iSYS_MAC            1
    #define iSYS_WIN            0
//}
extern device_type_t            device_type;
extern device_type_t            bt_index;

extern volatile uint32_t        sys_tick_count;
extern uint32_t                 rtc_init_value;
extern uint32_t                 rtc_cur_value;
extern uint32_t                 rtc_temp_value;

extern uint8_t                  wheel_data;
extern uint8_t                  m_tx_count;
extern uint8_t                  key_tx_count;
extern uint8_t                  key_ex_tx_count;
extern uint8_t                  mmk_tx_count;
extern uint8_t                  def_tx_count;

//----------------------------------------------
// 鼠标键盘数据寄存器
//
extern uint8_t                  m_data_flag;
//{
    #define bhid_data_send      (1<<4)
    #define bstd_ex_data_send   (1<<3)
    #define bmmk_data_send      (1<<2)
    #define bstd_kb_data_send   (1<<1)
    #define bmouse_data_send    (1<<0)
//}
extern uint8_t                  hint_led_status;
//{
    #define bled_hint_mode      (1<<7)

    #define bled_win_lock       (1<<2)
    #define bled_caps           (1<<1)
    #define bled_num            (1<<0)
//}

extern uint8_t                  kb_led_status;
//{
    #define bscroll_lock        (1<<2)
    #define bcaps_lock          (1<<1)
    #define bnum_lock           (1<<0)
//}

extern uint8_t                  mouse_data_key;
extern uint16_t                 mouse_x;
extern uint16_t                 mouse_y;
extern uint8_t                  mouse_data_z;
// 键盘寄存器
extern unsigned char            std_key[];
#define std_kb_data             std_key           // 按键数据
//{
    #define std_kb_data_modifier std_key[0]
    #define std_kb_data_key1    std_key[1]
    #define std_kb_data_key2    std_key[2]
    #define std_kb_data_key3    std_key[3]
    #define std_kb_data_key4    std_key[4]
    #define std_kb_data_key5    std_key[5]
    #define std_kb_data_key6    std_key[6]
//}
// 多媒体寄存器
extern uint8_t                  mmk_data_l;
extern uint8_t                  mmk_data_h;
extern uint8_t                  kb_bd_addr[];

extern uint32_t const           ble_sleep_1_time_tbl[];
extern uint32_t const           ble_sleep_2_time_tbl[];

//----------------------------------------------------------------------------;
// 通用类型定义
//
extern void mouse_periph_wakeup_enable(uint8_t mask);


#endif  /* __MOUSE_H */
