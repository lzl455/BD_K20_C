/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: Flash_process.h
*
* 功能说明: 
* 修改说明:
*******************************************************************************/
#ifndef _FLASH_PROCESS_H_
#define _FLASH_PROCESS_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//=============================================================================;
// 配置常量定义区
//
#define iCFG_BASE_ADDR          0x0000B000
//
//----------------------------------------------
// 按键数据区域
//
#define iKEY_MODE0_ADDR         (256*0)
#define iKEY_MODE1_ADDR         (256*4)
#define iKEY_MODE2_ADDR         (256*8)
#define iKEY_MODE3_ADDR         (256*12)
//{
    #define iKEY_DATA_CS_ADDR     31
//}
//
#define iKEY_MODE0_BANK         0
#define iKEY_MODE1_BANK         4
#define iKEY_MODE2_BANK         8
#define iKEY_MODE3_BANK         12
//
//----------------------------------------------
// LED相关配置数据区域
//
#define iCFG_BANK               (16)
#define iCFG_BANK_ADDR          (256*16)
//{
    #define iCFG_DATA_TYPE_VALULE 0x01
    
    #define iCFG_LED_PARA_ADDR    0x50

    #define iCFG_DATA_TYPE_ADDR   255
    #define iCFG_DATA_CS_ADDR     254
//}
//----------------------------------------------
// 状态数据区域
//
#define iFLASH_STATUS_BANK      17
#define iSTATUS_BANK_ADDR       (256*17)
//{
    #define iSTATUS_DATA_TYPE   0x01

    #define iREPORT_ADDR        0x01
    //{
        #define iREPORT_125     0
        #define iREPORT_250     1
        #define iREPORT_500     2
        #define iREPORT_1000    3
    //}
//}
//----------------------------------------------
// 系统配置数据区域
//
#define iFLASH_CFG_DPI_BANK    18
#define iFLASH_CFG_DPI_ADDR    (256*18)
//{
    #define iCFG_DPI_TYPE       0x02

    #define iSLEEP_TIME_24G     0x01
    #define iSLEEP_TIME_BLE     0x02
    #define iSYS_CFG_ADDR       0x04
//}

//----------------------------------------------
// BLE通道地址区域
//
#define iFLASH_BLE_ID_BANK      22
#define iFLASH_BLE_ID_BANK_BAK  23
#define iFLASH_BLE_ID_ADDR      (256*22+0x00)
#define iFLASH_BLE_ID_ADDR_BAK_0 (256*22+0x30)
#define iFLASH_BLE_ID_ADDR_BAK_1 (256*23+0x00)
#define iFLASH_BLE_ID_ADDR_BAK_2 (256*23+0x30)
//{
    #define iBLE_ID_TPYE        0xA6
    #define iBLE_ID_0_INDEX     1
    #define iBLE_ID_1_INDEX     2
    #define iBLE_ID_2_INDEX     3

    #define iBLE_ID_CHECKSUM    7
//}
#define iFLASH_BLE_ROLL_ADDR    (256*23+0xD0)

//=============================================================================;
// 配置区                                                              
//
/*******************************************************************************
 Flash地址分配
*******************************************************************************/

#define flash_mode_bank         flash_bank5
#define iFLASH_MODE_BANK        iFLASH_BANK5
#define iFLASH_MODE_ADDR        iFLASH_BANK5_ADDR
//{
    #define iDPI_LED_ADDR       0xA0
    #define iMODE_LED_ADDR      0xE0
//}

#define flash_cfg_bank          flash_bank6
#define iFLASH_CFG_BANK         iFLASH_BANK6
#define iFLASH_CFG_ADDR         iFLASH_BANK6_ADDR
//{
    #define iMODE_CFG_ADDR      0x80
    //{
        #define iX_MUL_DIV      0
        #define iY_MUL_DIV      1
        #define iREPORT_ASS     2
        #define iFIRE_KEY_DELAY 3
        #define iLED_SLEEP_TIME 4
        #define iPWM_VALUE      5
        #define iDPI_SNIPER_0   6
        #define iDPI_SNIPER_1   7
        #define iWHEEL_DPI      8
        #define iWHEEL_REPORT   9
        #define iWHEEL_ACC      10
    //}
    #define iMODE_ASS_ADDR      0xD5
    #define iCFG_SENSOE         0xD7
    #define iDPI_VALUE_ADDR     0xD8
//}

//=============================================================================;
// 外部定义内部引用区
//=============================================================================;

//=============================================================================;
// 外部寄存器引用
//

//=============================================================================;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部引用区
//=============================================================================;
enum key_mod
{
    iKEY_MODE_MIN=0,
    iKEY_MODE_0 = 0,
    iKEY_MODE_1 = 1,
    iKEY_MODE_2 = 2,
    iKEY_MODE_3 = 3,
    iKEY_MODE_MAX = 3,
};

//=============================================================================;
// 内部寄存器引用
//
extern bool                     bsave_status;
extern bool                     bsave_cfg_dpi;
extern bool                     bsave_ble_id;
extern bool                     bsave_mode;

extern unsigned char            device_status_base;
extern uint8_t                  flash_fifo[];

extern uint8_t                  def_key_dat[];
extern uint8_t                  def_key_fn_dat[];

extern uint8_t                  para_cfg_dat[];
//{
    #define iDPI_SNIPE_ADD      2
    #define iDPI_SNIPE_SUM      3
    #define iKEY_CTRL_DELAY     4
//}
extern uint8_t                  report_dpi[];
extern uint8_t                  ble_id[];

extern uint8_t                  key_mode;

extern uint8_t                  sleep_time_24g;
extern uint8_t                  sleep_time_ble;
extern uint8_t                  report_usb;
extern uint8_t                  report_24g;
extern uint8_t                  sys_mode;

extern uint8_t                  mouse_lod_set;
extern uint8_t                  key_delay_set;
extern uint16_t                 adv_cfg_value;
//{
    #define iMOTION_WAKEUP      0x80
    #define iXY_OPTIMIZE        0x40
    #define iPOWER_LOW          0x20
    #define iDELAY_MIN          0x10
    #define iKEY_REALSE_DELAY   0x0C
//}

extern uint8_t                  device_status_base;
extern uint8_t                  sys_cfg_base;

//=============================================================================;
// 内部函数引用
//
extern void laod_defaut_status(void);
extern void laod_mouse_status(void);
extern void laod_cfg_dpi(void);

extern void laod_flash_cfg(void);

extern void flash_save_status(void);
extern void flash_save_cfg_dpi(void);

extern void flash_load_ble_addr(void);
extern void flash_save_ble_addr(void);

#endif
