/*******************************************************************************
* Copyright (c) 2012, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: matrix_key.c
* 文件描述: 矩阵处理程序
*
*******************************************************************************/
#include <string.h>
#include "om_driver.h"
#include "main.h"
#include "mouse.h"
#include "main_24g.h"

#include "matrix_key.h"
#include "hid_process.h"
#include "usb_cfg_info.h"
#include "flash_process.h"
#include "key_code_define.h"

//----------------------------------------------------------------------------;
//常量定义
//
extern void key_decode(void);

//----------------------------------------------------------------------------;
//变量定义
//
uint16_t                        key_ctrl;
uint16_t                        key_ctrl_ex;

uint8_t                         key_temp_flag;
uint8_t                         key_temp_flag_1;
uint8_t                         ukey_temp_delay;
uint8_t                         device_key;
uint8_t                         device_key_bak;

//unsigned char                   std_key_count;  // 按下按键的个数
uint8_t                         matrix_status[iMATRIX_COL_NUM];
uint8_t                         key_fn_status[128];

uint8_t                         gKeyScan_bak[iMATRIX_COL_NUM];
uint8_t                         device_type_bak;

uint8_t                         decode_index;
uint8_t                         col_index;

uint8_t                         ctrl_key_value;
uint8_t                         std_key_value;
uint8_t                         com_ctrl_index;

uint8_t                         desk_mac_index;

//******************************************************************************
// 查表获取 数值中1的个数
unsigned char const get_1_count[256] =
{
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

uint8_t const key_delay_tbl[4] = {
    0x20,
    0x40,
    0x80,
    0xFE,
};

uint8_t const desk_mac[] = {
//----------------------------------------------0x110
    (iLEFT_GUI&0x0F),           iSTD_NULL,  iSTD_NULL,  iSTD_NULL, 
    (iLEFT_GUI|iLEFT_ALT)&0x0F, iSTD_NULL,  iSTD_NULL,  iSTD_NULL, 
    (iLEFT_GUI|iLEFT_ALT)&0x0F, iSTD_H,     iSTD_NULL,  iSTD_NULL, 
    (iLEFT_GUI|iLEFT_ALT)&0x0F, iSTD_H,     iSTD_M,     iSTD_NULL, 
    (iLEFT_GUI|iLEFT_ALT)&0x0F, iSTD_H,     iSTD_NULL,  iSTD_NULL, 
    (iLEFT_GUI|iLEFT_ALT)&0x0F, iSTD_NULL,  iSTD_NULL,  iSTD_NULL, 
    0x00,                       iSTD_NULL,  iSTD_NULL,  iSTD_NULL, 
};

/******************************************************************************
* 函数名称: void key_process(void)
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void __attribute__((noinline)) key_process(void)
{
    uint8_t i, temp_bit;

    if(0==(key_ctrl&bwin_mac_sataus))
    {                                           // mac系统，按键交换
        temp_bit = modifier_key_tmp;
        modifier_key_tmp &= 0x33;
        if(temp_bit&(1<<7))
            modifier_key_tmp |= 0x40;
        if(temp_bit&(1<<6))
            modifier_key_tmp |= 0x80;
        if(temp_bit&(1<<2))
            modifier_key_tmp |= 0x08;
        if(temp_bit&(1<<3))
            modifier_key_tmp |= 0x04;
    }
    if(key_ctrl_ex&bcom_ctrl_en)
	{
	    if(10 > com_ctrl_index)
		{
		    tmp_std_key[0] |= ctrl_key_value;
		}
		else if(20 > com_ctrl_index)
		{
		    tmp_std_key[0] |= ctrl_key_value;
            tmp_std_key[1] = std_key_value;
		}
		else if(250 > com_ctrl_index)
		{
		    tmp_std_key[0] |= ctrl_key_value;
            if(key_ctrl_ex&bcom_ctrl_long)
                tmp_std_key[1] = std_key_value;
            else
                tmp_std_key[1] = 0;
		}
        else if(250 <= com_ctrl_index)
		{
		    tmp_std_key[0] |= ctrl_key_value;
            tmp_std_key[1] = 0;
		    if(key_ctrl_ex&bcom_ctrl_status)
				com_ctrl_index = 0;
			else
		        key_ctrl_ex &= ~bcom_ctrl_en;
		}

		com_ctrl_index++;
        if(iDEVICE_TYPE_BT2 >= device_type)
            com_ctrl_index++;
	}

    if(0 != (key_ctrl_ex&bdesk_mac))
    {
        if(0==(desk_mac_index&0x03))
        {
            i = desk_mac_index;

            tmp_std_key[0] = desk_mac[i++];
            tmp_std_key[1] = desk_mac[i++];
            tmp_std_key[2] = desk_mac[i++];
        }

        desk_mac_index++;
        if(sizeof(desk_mac) <= desk_mac_index)
            key_ctrl_ex &= ~bdesk_mac;
    }

    for(i=0; i<6; i++)
    {
        if(key_data_tmp[i] != std_key[i])
        {
            memcpy(std_key, tmp_std_key, 6);

            key_tx_count = 8;
            m_data_flag |= bstd_kb_data_send;
            return;
        }
    }

    for(i=7; i<22; i++)
    {
        if(tmp_std_key[i] != std_key[i])
        {
            memcpy(std_key+7, tmp_std_key+7, 15);
            key_ex_tx_count = 8;
            m_data_flag |= bstd_ex_data_send;
            return;
        }
    }

    if(multi_data_tmp_l != mmk_data_l)
    {
        if(0==(m_data_flag & bmmk_data_send))
        {
            mmk_data_l = multi_data_tmp_l;
            mmk_data_h = multi_data_tmp_h;
            m_data_flag |= bmmk_data_send;
            mmk_tx_count = 8;
        }
    }
}

/******************************************************************************
* 函数名称: mode_swtich_init
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void mode_swtich_init(void)
{
	memset(std_key, 0x00, 22);

    mmk_data_l = 0;
    mmk_data_h = 0;

    m_data_flag |= (bmouse_data_send|bstd_kb_data_send|bmmk_data_send);
}

/******************************************************************************
* 函数名称: matrixkey_value
* 功能描述: 矩阵按键扫描
* 输入参数:
* 输出参数:
* 说    明: 为提高时间效率,赋值等操作不采用循环模式
******************************************************************************/
__RAM_CODE void matrixkey_value(void)
{
    unsigned char i, x;

    special_key = 0;

    modifier_key_tmp = 0;
    multi_data_tmp_l = 0;
    multi_data_tmp_h = 0;

    key_ctrl &= ~bkey_press_status;

    decode_index = 0;
    for(col_index=3; col_index<18; col_index++)
    {
        key_temp_flag_1 = (gKeyScan_bak[col_index] ^ matrix_status[col_index]);
        gKeyScan_bak[col_index] = matrix_status[col_index];

        key_temp_flag = gKeyScan_bak[col_index];
// 0
        if(0!=key_temp_flag)
            key_ctrl |= bkey_press_status;

        x=0x01;
        for(i=0; i<iMATRIX_ROW_NUM; i++)
        {
            if(0 == (define_key_flag_n&bkey_decode))
            {
                if(key_temp_flag_1&x)
                {                               // 按键有变化
                    goto define_key_process;
                }
                else
                {
			        if(decode_index == com_key_index)
				        com_key_index = 0xFF;
                }
            }
            else
            {
                if(key_temp_flag_1&x)
                {                               // 有变化
define_key_process:
                    if(key_temp_flag&x)
                    {
                        define_key_flag_n = (bdefine_key_press|bkey_decode);
                        key_ctrl |= bkey_press_status;

                        if(define_key_ctrl & bcom_key_break)
                        {                       // 按键可打断
                            define_key_ctrl &= ~bcom_key_break;
                            define_key_status |= bkey_status_change;
                        }
                    }
                    else
                    {
                        define_key_flag_n &= ~bdefine_key_press;
                    }
                }

                key_decode();
                if(key_ctrl&bkey_decode_valid)
                {
                    if((define_key_flag&bkey_decode_end)
			    	    && (0==(define_key_flag&bdefine_key_press)))
                    {
                        define_key_flag = 0;
                    }
                    define_key_flag_n = define_key_flag;
                    if(define_key_flag&bdefine_key_com)
                    {
                        decode_data_l_n = decode_data_l;
                        decode_data_h_n = decode_data_h;
                    }
                }
                if(0==(key_temp_flag&x))
			        key_fn_status[decode_index] = iNULL_MATRIX;
            }
            
            x<<=1;
            decode_index++;
        }
    }

    if(bkey_break_or_realse)
    {
        bkey_break_or_realse = 0;

	    memset(key_data_tmp, 0x00, 22);
    }
	else
	{
	    if((0==(key_ctrl&bkey_press_status)) && (0 == (define_key_ctrl&bcom_decode_ing)))
		{
            multi_data_tmp_l = 0;
            multi_data_tmp_l = 0;
	        memset(key_data_tmp, 0x00, 22);
		}
	}

// 按键去抖处理_END
    device_key_bak &= device_key;
    special_key_bak &= special_key;

    if(special_key&bfn_press)
    {
        key_ctrl |= bfn_key_status;
    }
    else
    {
        if(key_ctrl&bfn_key_status)
        {
            key_ctrl &= ~bfn_key_status;
            if(key_ctrl&bfn_save_status)
            {
                key_ctrl &= ~bfn_save_status;
                bsave_status = true;
            }

            if(key_ctrl&bfn_save_cfg)
            {
                key_ctrl &= ~bfn_save_cfg;
                bsave_cfg_dpi = true;
            }
        }
    }
}

uint8_t const matrixkey_c_tbl[] = {
    8, 10,  6,  7, 14, 13, 12, 11, 
   15,  9,  0, 16, 17,  0,  0,  0,
};

#define  DELAY

__RAM_CODE void ctrl_54e_inpull(void)
{
    OM_CRITICAL_BEGIN();
    KEY_EX_LOW;
    delayus(1);
    KEY_EX_HIGH;
    OM_CRITICAL_END();
}

void scan_key(void)
{
    mLED_VDD_DIS;
    MATRX_ALL_IN;
    ctrl_54e_inpull();
    delayus(10);

    MATRX_C1_LOW;
    mDELAY_R;
    matrix_status[1] = MATRIX_RAW;
    MATRX_C1_HIGH;

    MATRX_C2_LOW;
    mDELAY_R;
    matrix_status[2] = MATRIX_RAW;
    MATRX_C2_HIGH;

    MATRX_C3_LOW;
    mDELAY_R;
    matrix_status[3] = MATRIX_RAW;
    MATRX_C3_HIGH;

    MATRX_C4_LOW;
    mDELAY_R;
    matrix_status[4] = MATRIX_RAW;
    MATRX_C4_HIGH;

    MATRX_C5_LOW;
    mDELAY_R;
    matrix_status[5] = MATRIX_RAW;
    MATRX_C5_HIGH;

    MATRX_C18_LOW;
    mDELAY_R;
    matrix_status[18] = MATRIX_RAW;
    MATRX_C18_HIGH;

    MATRX_C19_LOW;
    mDELAY_R;
    matrix_status[19] = MATRIX_RAW;
    MATRX_C19_HIGH;
    mDELAY_R;

    KEY_EX_TOGGLE;
    mDELAY_EX;
    for(uint8_t i=0; i<13; i++)
    {
        mDELAY_EX;
        matrix_status[matrixkey_c_tbl[i]] = MATRIX_RAW;
        KEY_EX_TOGGLE;
    }
    KEY_EX_HIGH;
}

/******************************************************************************
* 函数名称: matrixkey_scan
* 功能描述: 矩阵按键扫描
* 输入参数:
* 输出参数:
* 说    明: 为提高时间效率,赋值等操作不采用循环模式
******************************************************************************/
__RAM_CODE void matrixkey_scan(void)
{
    unsigned char i,j,k,m,key_temp[22];

    device_key = 0;
    special_key = 0;
    key_ctrl_ex &= ~(bgost_key|bcom_ctrl_status);
    wheel_status &= ~bwheel_press;

    modifier_key_tmp = 0;
    multi_data_tmp_l = 0;
    multi_data_tmp_h = 0;

    scan_key();
    if(iDEVICE_TYPE_USB == device_type)
    {
        led_status_hint();
    }
    else
    {
        if(0==(ble_24g_ctrl&bom6239_sync_ing))
            led_status_hint();
    }

    k = 0;
    for(i=0; i<iMATRIX_COL_NUM; i++)
    {
        if(0 != matrix_status[i])
        {
            key_temp[k] = matrix_status[i];
            k++;
        }
    }

    if((0!=k) && (0==(key_ctrl&bkey_press_status)))
    {
        key_ctrl |= bkey_press_status;
    }

    for(j=0; j<k; j++)
    {
        i = key_temp[j];

        if(2 <= get_1_count[i])
        {
            key_temp[j] = 0;
            for(m=0; m<k; m++)
            {
                if(0 != (key_temp[m]&i))
                {
                    key_ctrl_ex |= bgost_key;
                    return;
                }
            }
            key_temp[j] = i;
        }
    }

    matrix_status[4] &= 0x2F;
    if(matrix_status[3]&(1<<0))
        matrix_status[4] |= (1<<4);
    if(matrix_status[3]&(1<<1))
        matrix_status[4] |= (1<<6);
    if(matrix_status[3]&(1<<2))
        matrix_status[4] |= (1<<7);

    matrix_status[5] &= 0xC7;
    if(matrix_status[2]&(1<<0))
        matrix_status[5] |= (1<<3);
    if(matrix_status[2]&(1<<1))
        matrix_status[5] |= (1<<4);
    if(matrix_status[2]&(1<<5))
        matrix_status[5] |= (1<<5);

    if(matrix_status[18]&(1<<0))
        matrix_status[7] |= (1<<2);
    if(matrix_status[18]&(1<<1))
        matrix_status[7] |= (1<<7);
    if(matrix_status[18]&(1<<4))
        matrix_status[8] |= (1<<3);

    if(matrix_status[19]&(1<<0))
        matrix_status[12] |= (1<<2);
    if(matrix_status[19]&(1<<1))
        matrix_status[12] |= (1<<7);
    if(matrix_status[19]&(1<<3))
        matrix_status[13] |= (1<<2);
    if(matrix_status[19]&(1<<4))
        matrix_status[14] |= (1<<2);
    if(matrix_status[19]&(1<<6))
        matrix_status[17] |= (1<<4);

    if(matrix_status[1]&(1<<0))
        matrix_status[0] |= (1<<7);
    matrix_status[3] = matrix_status[0];

    matrixkey_value();
    key_process();
}

extern void                 hi5_usb_init(void);
extern void                 usb_disconnect(void);

static bool b5v_check_in;
static uint32_t usb_io_status, mode_swtich_time;

extern bool busb_valid;

#define iMODE_24G           0
#define iMODE_BLE           1
#define iMODE_USB           2

/******************************************************************************
* 函数名称: scan_mode_swtich()
* 功能描述: 模式切换
* 输入参数:
* 输出参数: 无
* 说    明: 手动模式切换的时候，usb切换到其他状态，采用复位处理，其他模式切换到USB，采用直接切换
******************************************************************************/
void scan_mode_swtich(uint8_t type)
{
    static uint8_t mode_status;
    uint8_t i,j, mode_status_bak;

    j = 4;
    mMODE_PULL_DOWN;
    delayus(20);
    if(0 == MODE_DATA)
        j--;
    mMODE_PULL_UP;
    delayus(20);
    if(0 != MODE_DATA)
        j++;
    mMODE_PULL_DOWN;

    if(4 > j)
        mode_status_bak = iMODE_BLE;
    else if(4 < j)
        mode_status_bak = iMODE_24G;
    else
        mode_status_bak = iMODE_USB;

    if(mode_status != mode_status_bak)
    {
        mode_status = mode_status_bak;
        if(iMODE_CHECK_POWERUP != type)
            return;
    }

//mode_status = iMODE_USB;
    if(iMODE_BLE == mode_status)
    {
        if(iMODE_CHECK_POWERUP != type)
        {
            if(bt_index != device_type)
            {
                if(iDEVICE_TYPE_BT2<bt_index)
                    bt_index = iDEVICE_TYPE_BT0;

                OM_PMU->SW_RSVD1 &= ~PMU_SW_RSVD1_RF_MDOE_MASK;
                OM_PMU->SW_RSVD1 |= bt_index;
                NVIC_SystemReset();
            }
        }
        else
        {
            device_type = bt_index;
        }
    }
    else if(iMODE_24G == mode_status)
    {                                           // 下拉 24g
        if(iMODE_CHECK_POWERUP != type)
        {
            if(iDEVICE_TYPE_24G != device_type)
                NVIC_SystemReset();
        }
        else
        {
            device_type = iDEVICE_TYPE_24G;
        }
    }
    else //if(iMODE_USB == mode_status)
    {                                           // 浮空 usb
        if(iMODE_CHECK_POWERUP != type)
        {
            if(iDEVICE_TYPE_USB != device_type)
                NVIC_SystemReset();
        }
        else
        {
            device_type = iDEVICE_TYPE_USB;
        }
    }
}

