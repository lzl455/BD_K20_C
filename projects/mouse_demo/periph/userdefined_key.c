/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: UserDefined_Key.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "om_driver.h"

#include "main.h"
#include "main_24g.h"

#include "hid_process.h"
#include "userdefined_key.h"
#include "key_code_define.h"
#include "flash_process.h"

#include "matrix_key.h"
#include "matrix_key_tbl_win.h"
#include "matrix_key_tbl_win_fn.h"
#include "matrix_key_tbl_mac.h"
#include "matrix_key_tbl_mac_fn.h"

//-----------------------------------------------------------------------------;
//常量定义区
//

//----------------------------------------------------------------------------
//变量定义区
//
bool                            bfire_key_status;
bool                            bcom_fire_status;
bool                            bsniper_key_press;
bool                            bsniper_key_add_sub;
bool                            bkey_break_or_realse;

uint16_t                        special_key;
uint16_t                        special_key_bak;

unsigned char                   define_key_status;
unsigned char                   define_key_ctrl;

unsigned char                   define_key_fifo[128];
unsigned char                   define_key_flag;

unsigned char                   decode_data_l;
unsigned char                   decode_data_h;

unsigned char                   decode_data_l_n;
unsigned char                   decode_data_h_n;

unsigned int                    com_key_length;
unsigned int                    com_key_addr_back;
unsigned int                    com_key_addr;
unsigned char                   cmd_hong_count;
unsigned char                   com_key_index;

uint16_t                        key_delay_count;
uint32_t                        key_delay_rtc_value;

unsigned char                   multi_data_tmp_l;
unsigned char                   multi_data_tmp_h;
unsigned char                   tmp_std_key[22];

uint32_t                        press_bt0_time_count;
uint32_t                        press_bt1_time_count;
uint32_t                        press_bt2_time_count;
uint32_t                        press_24g_time_count;
uint32_t                        default_time_count;

//-----------------------------------------------------------------------------
//表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;
extern bool flash_read(unsigned int addr, unsigned int length);


/******************************************************************************
* 函数名称: key_decode_exfun()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void __attribute__((noinline)) key_decode_exfun(void)
{
    uint32_t conn_rtc_value = drv_rtc_read(OM_RTC);
    switch(decode_data_l&0x0F)
    {
        case iKEY_DEFAULT&0x0F:
            special_key |= bdelault_press;
            if(0==(special_key_bak&bdelault_press_bak))
            {
                special_key_bak |= bdelault_press_bak;
                default_time_count = conn_rtc_value;

            }
            else
            {
                if(mMS_TO_TICK(2000) < (conn_rtc_value-default_time_count))
                {
                    OM_RCC->USB_CTRL = 0;           // disconnect
                    logo_off();

                    flash_erase(iKEY_MODE0_BANK);
                    flash_erase(iKEY_MODE1_BANK);
                    flash_erase(iKEY_MODE2_BANK);
                    flash_erase(iKEY_MODE3_BANK);

                    flash_erase(iCFG_BANK);
                    flash_erase(iFLASH_STATUS_BANK);
                    flash_erase(iFLASH_CFG_DPI_BANK);

                    flash_erase(iFLASH_BLE_ID_BANK);
                    flash_erase(iFLASH_BLE_ID_BANK_BAK);

                    for(uint8_t i=0; i<3; i++)
                    {
                        drv_wdt_keep_alive(OM_WDT);
                        hint_led_status = (bled_hint_mode|bled_num|bled_caps|bled_win_lock);
                        led_status_hint();
                        delayus(250000);
                        hint_led_status = bled_hint_mode;
                        led_status_hint();
                        delayus(250000);
                    }

                    device_type = iDEVICE_TYPE_BT0;
                    memset(flash_fifo, 0xFF, 64);
                    flash_fifo[0x00+0] = iBLE_ID_TPYE;
                    flash_fifo[0x00+1] = (ble_id[0]+1);
                    flash_fifo[0x00+2] = (ble_id[1]+1);
                    flash_fifo[0x00+3] = (ble_id[2]+1);
                    flash_write_ble_addr(0x1D0);
                    delayus(2000);

                    NVIC_SystemReset();
                }
            }
            break;
        case iKEY_ALT_TAB&0x0F:
            if(define_key_flag & bkey_decode_end)
            {
                key_ctrl_ex |= bcom_ctrl_status;
                return;
            }
            else
            {
                key_ctrl_ex &= ~bcom_ctrl_long;
                key_ctrl_ex |= (bcom_ctrl_en|bcom_ctrl_status);
                ctrl_key_value = 0x04;
                std_key_value = iSTD_TAB;
                com_ctrl_index = 0;
            }
            define_key_ctrl |= bdefine_key_send;

            break;
        case iKEY_CMD_TAB&0x0F:
            if(define_key_flag & bkey_decode_end)
            {
                key_ctrl_ex |= bcom_ctrl_status;
                return;
            }
            else
            {
                key_ctrl_ex &= ~bcom_ctrl_long;
                key_ctrl_ex |= (bcom_ctrl_en|bcom_ctrl_status);
                ctrl_key_value = 0x08;
                std_key_value = iSTD_TAB;
                com_ctrl_index = 0;
            }
            define_key_ctrl |= bdefine_key_send;
            break;

        case iKEY_CTRL_SPACE&0x0F:
            if(define_key_flag & bkey_decode_end)
            {
                key_ctrl_ex |= bcom_ctrl_status;
                return;
            }
            else
            {
                key_ctrl_ex &= ~bcom_ctrl_long;
                key_ctrl_ex |= (bcom_ctrl_en|bcom_ctrl_status);
                ctrl_key_value = 0x01;
                std_key_value = iSTD_SPACE;
                com_ctrl_index = 0;
            }
            define_key_ctrl |= bdefine_key_send;

            break;
        case iKEY_CMD_SPACE&0x0F:
            if(define_key_flag & bkey_decode_end)
            {
                return;
            }
            else
            {
                key_ctrl_ex |= (bcom_ctrl_en|bcom_ctrl_long);
                ctrl_key_value = 0x08;
                std_key_value = iSTD_SPACE;
                com_ctrl_index = 0;
            }
            define_key_ctrl |= bdefine_key_send;

            break;
        case iKEY_DESK_MAC&0x0F:
            if(define_key_flag & bkey_decode_end)
            {
                return;
            }
            else
            {
                if(0==(key_ctrl_ex&bdesk_mac))
                {
                    key_ctrl_ex |= bdesk_mac;
                    desk_mac_index = 0;
                }
            }
            define_key_ctrl |= bdefine_key_send;

            break;
    }
}

/******************************************************************************
* 函数名称: define_key_decode()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
__RAM_CODE void key_decode(void)
{
    unsigned char i, j, key_index;
    unsigned int length;
	unsigned char const *pRom;
    unsigned char loop_count = 0;

    key_ctrl |= bkey_decode_valid;

    define_key_flag = define_key_flag_n;
    define_key_ctrl &= ~bdefine_key_send;

    key_index = (decode_index<<1);
    if(key_ctrl&bfn_key_status)
    {
		if(iKEY_INDEX_FN != decode_index)
	    {
		    if(iNORMAL_MATRIX == key_fn_status[decode_index])
			    goto normal_matrix_tbl;
            key_fn_status[decode_index] = iFN_MATRIX;
	    }
fn_matrix_tbl:
        if(key_ctrl&bwin_mac_sataus)
        {
		    decode_data_l = matrixkey_win_fn_tbl[key_index++];
            decode_data_h = matrixkey_win_fn_tbl[key_index];
        }
        else
        {
		    decode_data_l = matrixkey_mac_fn_tbl[key_index++];
            decode_data_h = matrixkey_mac_fn_tbl[key_index];
        }
    }
    else
    {
		if(iKEY_INDEX_FN != decode_index)
	    {
            if(iFN_MATRIX == key_fn_status[decode_index])
				goto fn_matrix_tbl;
            key_fn_status[decode_index] = iNORMAL_MATRIX;
		}
normal_matrix_tbl:
        if(key_ctrl&bwin_mac_sataus)
        {
            decode_data_l = matrixkey_win_tbl[key_index++];
            decode_data_h = matrixkey_win_tbl[key_index];
        }
        else
        {
            decode_data_l = matrixkey_mac_tbl[key_index++];
            decode_data_h = matrixkey_mac_tbl[key_index];
        }
    }

    if(iDEF_COM == (decode_data_h&iDEF_COM_MASK))
    {
        if((0 == (define_key_ctrl&bcom_decode_ing))
		    ||(0xFF == com_key_index))
        {
            if(0==(define_key_flag&bdefine_key_press))
            {
                key_ctrl &= ~bkey_decode_valid;
                return;
            }
            define_key_ctrl |= bcom_decode_ing;
            com_key_index = decode_index;
        }
        else
        {
            if(decode_index !=com_key_index)
            {
                key_ctrl &= ~bkey_decode_valid;
                return;
            }
            else
            {
                if(0==(define_key_flag & bkey_decode_end))
                {
                    decode_data_l = decode_data_l_n;
                    decode_data_h = decode_data_h_n;
                }
            }
        }
    }

define_key_decode_begin:
    if(iKEY_TYPE_INVALID == decode_data_h)
    {
        if(define_key_flag&bdefine_key_com)
        {
            bkey_break_or_realse = 1;
            define_key_ctrl &= ~bcom_decode_ing;
        }
        define_key_flag &= ~bkey_decode;
        return;
    }

    if(iKEY_TYPE_STD == (decode_data_h & iKEY_STD_MASK))
    {                                           // 标准按键
        if(define_key_flag & bkey_decode_end)
        {
            if(0==(define_key_flag&bdefine_key_press))
            {
                if(0 == (define_key_flag&bdefine_key_com))
                {
                    key_ctrl &= ~bkey_press;
                    goto std_key_decode_1;
                }
            }
            else
                goto std_key_decode_0;
        }
        else
        {
std_key_decode_0:
            if(decode_data_h&bkey_code_b13)
                key_ctrl |= bkey_press;
            else
                key_ctrl &= ~bkey_press;

std_key_decode_1:
            if(key_ctrl&bkey_press)
            {
                if(decode_data_h&bkey_code_b12)
                    modifier_key_tmp |= (decode_data_h&0x0F);
                else
                    modifier_key_tmp |= ((decode_data_h&0x0F)<<4);
            }

            if((key_ctrl&bwin_mac_sataus) && (key_ctrl&bwin_lock_status))
            {
                modifier_key_tmp&= 0x77;
                if(iSTD_APP == decode_data_l)
                    key_ctrl &= ~bkey_press;
            }
    
            if(0 != decode_data_l)
            {
                i = ((decode_data_l>>3)+7);
                j = (0x01<<(decode_data_l&0x07));
                if(key_ctrl&bkey_press)
                {                                   // 按下
                    if(key_data_tmp[i] & j)
                        goto define_decode_end;
                    if(decode_data_l == key_data_tmp[1])
                        goto define_decode_end;
                    if(decode_data_l == key_data_tmp[2])
                        goto define_decode_end;
                    if(decode_data_l == key_data_tmp[3])
                        goto define_decode_end;
                    if(decode_data_l == key_data_tmp[4])
                        goto define_decode_end;
                    if(decode_data_l == key_data_tmp[5])
                        goto define_decode_end;

                    if(0 == key_data_tmp[1])
                        key_data_tmp[1] = decode_data_l;
                    else if(0 == key_data_tmp[2])
                        key_data_tmp[2] = decode_data_l;
                    else if(0 == key_data_tmp[3])
                        key_data_tmp[3] = decode_data_l;
                    else if(0 == key_data_tmp[4])
                        key_data_tmp[4] = decode_data_l;
                    else if(0 == key_data_tmp[5])
                        key_data_tmp[5] = decode_data_l;
                    else
					{
					    if(0x78>decode_data_l)
                            key_data_tmp[i] |= j;
					}
                }
                else
                {                                   // 松开
//PB2 = 0;
                    if(decode_data_l == key_data_tmp[1])
                        key_data_tmp[1] = 0;
                    if(decode_data_l == key_data_tmp[2])
                        key_data_tmp[2] = 0;
                    if(decode_data_l == key_data_tmp[3])
                        key_data_tmp[3] = 0;
                    if(decode_data_l == key_data_tmp[4])
                        key_data_tmp[4] = 0;
                    if(decode_data_l == key_data_tmp[5])
                        key_data_tmp[5] = 0;
                    else
					{
					    if(0x78>decode_data_l)
                            key_data_tmp[i] &= ~j;
					}
                }
            }
        }
        define_key_ctrl |= bdefine_key_send;
    }
    else if(iKEY_TYPE_MMK == (decode_data_h & iKEY_TYPE_MASK))
    {                                           // 多媒体按键
        if(define_key_flag & bkey_decode_end)
        {
            if(0==(define_key_flag&bdefine_key_press))
            {
                multi_data_tmp_l = 0;
                multi_data_tmp_h = 0;
            }
            else
            {
                multi_data_tmp_l = decode_data_l;
                multi_data_tmp_h = (decode_data_h & (~iKEY_MMK_MASK));
                return;
            }
        }
        else
        {
            multi_data_tmp_l = decode_data_l;
            multi_data_tmp_h = (decode_data_h & (~iKEY_MMK_MASK));
        }
        define_key_ctrl |= bdefine_key_send;
    }
    else if(iKEY_TYPE_EX == (decode_data_h & iKEY_TYPE_MASK))
    { // 0x4X
        if(0==(decode_data_h&bkey_code_b11))
        { // 0x40~0x47
            switch(decode_data_h&0x0F)
            {
                case iKEY_TYPE_MOUSE&0x07:      // 0x41 鼠标按键
                    if(define_key_flag & bkey_decode_end)
                    {
                        if(0==(define_key_flag&bdefine_key_press))
                        {
                            mouse_data_key &= (~(decode_data_l&0x7F));
                        }
                        else
                            return;
                    }
                    else
                    {
                        if(decode_data_l&bkey_code_b7)
                            mouse_data_key |= (decode_data_l&0x7F);
                        else
                            mouse_data_key &= (~(decode_data_l&0x7F));
                    }

                    m_data_flag |= bmouse_data_send;
                    define_key_flag |= bdefine_key_send;
                    m_tx_count = 4;
                    break;
                case iKEY_TYPE_WHEEL&0x07:      // 0x42 鼠标滚轮
                    if(define_key_flag & bkey_decode_end)
                    {
                        return;
                    }
                    else
                    {
                        mouse_data_z = decode_data_l;
                        m_data_flag |= bmouse_data_send;
                        m_tx_count = 4;
                    }
                    break;
            }
        }
        else
        { // 0x48~0x4F
            switch(decode_data_h&0x07)
            {
// 0x48 特殊按键
                case iKEY_TYPE_SPECIAL&0x07: 
                    if(define_key_flag&bdefine_key_com)
                    {
                        define_key_flag &= ~bkey_decode;
                        define_key_ctrl &= ~bcom_decode_ing;
                        return;
                    }

                    if(0==(define_key_flag&bdefine_key_press))
                        return;
                    key_ctrl_ex &= ~bkey_all_realse;
                    /*if(iDEF_SYS_CTRL == (decode_data_l & iKEY_SPECIAL_MASK))
                    {

                    }
                    else*/ if(iLED_CTRL == (decode_data_l & iKEY_SPECIAL_MASK))
                    {
                        switch(decode_data_l&0x0F)
                        {
                            case iLED_BRIGHT_SUB&0x0F:
                                special_key |= bkey_light_dn;
                                if((0==(special_key_bak&bkey_light_dn_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_light_dn_bak;
                                    if(led_light_lev > iLED_LEV_MIN)
                                    {
                                        led_light_lev--;
                                        hid_ctrl_reg |= bdevice_status_change;
                                        key_ctrl |= bfn_save_cfg;
                                    }
                                    else
                                    {
                                        if(0 == hint_time_count)
                                            hint_time_count = 0x37;
                                    }
                                }
                                break;
                            case iLED_BRIGHT_ADD&0x0F:
                                special_key |= bkey_light_up;
                                if((0==(special_key_bak&bkey_light_up_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_light_up_bak;
                                    if(led_light_lev < iLED_LEV_MAX)
                                    {
                                        led_light_lev++;
                                        hid_ctrl_reg |= bdevice_status_change;
                                        key_ctrl |= bfn_save_cfg;
                                    }
                                    else
                                    {
                                        led_light_lev = iLED_LEV_MAX;
                                        if(0 == hint_time_count)
                                            hint_time_count = 0x37;
                                    }
                                }
                                break;

                            case iLED_MODE_CYC_ADD&0x0F:
                                special_key |= bkey_mode_cyc;
                                if((0==(special_key_bak&bkey_mode_cyc_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_mode_cyc_bak;
                                    led_cur_mode++;
                                    if(iMODE_LED_MAX<led_cur_mode)
                                        led_cur_mode = iMODE_LED_ON;
                                    hid_ctrl_reg |= bdevice_status_change;
                                    key_ctrl |= bfn_save_status;
                                }
                                break;
                            case iLED_SPEED_SUB&0x0F:
                                special_key |= bkey_speed_dn;
                                if((0==(special_key_bak&bkey_speed_dn_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_speed_dn_bak;
                                    if(iSPEED_LEV_MAX > led_speed_lev)
                                    {
                                        led_speed_lev++;
                                        hid_ctrl_reg |= bdevice_status_change;
                                        key_ctrl |= bfn_save_cfg;
                                    }
                                    else
                                    {
                                        if(0 == hint_time_count)
                                            hint_time_count = 0x37;
                                    }
                                }
                                break;
                            case iLED_SPEED_ADD&0x0F:
                                special_key |= bkey_speed_up;
                                if((0==(special_key_bak&bkey_speed_up_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_speed_up_bak;
                                    if(led_speed_lev > iSPEED_LEV_MIN)
                                    {
                                        led_speed_lev--;
                                        hid_ctrl_reg |= bdevice_status_change;
                                        key_ctrl |= bfn_save_cfg;
                                    }
                                    else
                                    {
                                        if(0 == hint_time_count)
                                            hint_time_count = 0x37;
                                    }
                                }
                                break;
//                            case iLED_DIR_L_R&0x0F:
//                                if(bled_run_dir)
//                                {
//                                    bled_run_dir = 0;
//                                }
//                                break;
//                            case iLED_DIR_R_L&0x0F:
//                                if(!bled_run_dir)
//                                {
//                                    bled_run_dir = 1;
//                                }
//                                break;
                            case iLED_OFF&0x0F:
							    special_key |= bled_off;
                                if(0==(special_key_bak&bled_off_back))
                                {
                                    special_key_bak |= bled_off_back;
                                    bled_bright_en = !bled_bright_en;
                                    key_ctrl |= bfn_save_status;
                                    exled_rtc_count=0;
                                }
                                break;
                            case iLED_RGB_SWTICH&0x0F:
                                special_key |= bkey_rgb_cyc;
                                if((0==(special_key_bak&bkey_rgb_cyc_bak)) && (true==bled_bright_en))
                                {
                                    special_key_bak |= bkey_rgb_cyc_bak;

                                    led_rgb_index++;
                                    led_rgb_index &= 0x07;
                                    key_ctrl |= bfn_save_cfg;
                                }
                                break;
                        }
                    }
                    else if(iKEY_MODE_SWITCH == (decode_data_l & iKEY_SPECIAL_MASK))
                    {
                        uint32_t conn_rtc_value = drv_rtc_read(OM_RTC);
                        switch(decode_data_l&0x0F)
                        {
                            case iMODE_KEY_FN&0x0F:
                                special_key |= bfn_press;

                                break;
                            case iMODE_KEY_USB&0x0F:

                                break;
                            case iMODE_KEY_BT0&0x0F:
                                if(iDEVICE_TYPE_BT2 < device_type)
                                    break;

                                device_key |= bkey_bt0_press;
                                if(0==(device_key_bak&bkey_bt0_press_bak))
                                {
                                    device_key_bak |= bkey_bt0_press_bak;
                                    press_bt0_time_count = conn_rtc_value;
                                
                                    if(iDEVICE_TYPE_BT0 != device_type)
                                    {
                                        device_type = iDEVICE_TYPE_BT0;
                                        bt_index = iDEVICE_TYPE_BT0;
                                        key_ctrl &= ~bwin_mac_sataus;
                                        if(sys_mode&(1<<(device_type&0x07)))
                                            key_ctrl |= bwin_mac_sataus;
                                        flash_save_status();
                                        delayus(10000);
                                        NVIC_SystemReset();
                                    }
                                }
                                else
                                {
                                    if(mMS_TO_TICK(3000) < (conn_rtc_value-press_bt0_time_count))
                                    {
                                        if(0 == (ble_24g_ctrl&bom6239_conning))
                                        {
                                            OM_PMU->SW_RSVD1 |= RSVD1_RF_CONN_EN;
                                            NVIC_SystemReset();
                                        }
                                    }
                                }

                                break;
                            case iMODE_KEY_BT1&0x0F:
                                if(iDEVICE_TYPE_BT2 < device_type)
                                    break;

                                device_key |= bkey_bt1_press;
                                if(0==(device_key_bak&bkey_bt1_press_bak))
                                {
                                    device_key_bak |= bkey_bt1_press_bak;
                                    press_bt1_time_count = conn_rtc_value;
                                
                                    if(iDEVICE_TYPE_BT1 != device_type)
                                    {
                                        device_type = iDEVICE_TYPE_BT1;
                                        bt_index = iDEVICE_TYPE_BT1;
                                        key_ctrl &= ~bwin_mac_sataus;
                                        if(sys_mode&(1<<(device_type&0x07)))
                                            key_ctrl |= bwin_mac_sataus;
                                        flash_save_status();
                                        delayus(10000);
                                        NVIC_SystemReset();
                                    }
                                }
                                else
                                {
                                    if(mMS_TO_TICK(3000) < (conn_rtc_value-press_bt1_time_count))
                                    {
                                        if(0 == (ble_24g_ctrl&bom6239_conning))
                                        {
                                            OM_PMU->SW_RSVD1 |= RSVD1_RF_CONN_EN;
                                            NVIC_SystemReset();
                                        }
                                    }
                                }

                                break;
                            case iMODE_KEY_BT2&0x0F:
                                if(iDEVICE_TYPE_BT2 < device_type)
                                    break;

                                device_key |= bkey_bt2_press;
                                if(0==(device_key_bak&bkey_bt2_press_bak))
                                {
                                    device_key_bak |= bkey_bt2_press_bak;
                                    press_bt2_time_count = conn_rtc_value;

                                    if(iDEVICE_TYPE_BT2 != device_type)
                                    {
                                        device_type = iDEVICE_TYPE_BT2;
                                        bt_index = iDEVICE_TYPE_BT2;
                                        key_ctrl &= ~bwin_mac_sataus;
                                        if(sys_mode&(1<<(device_type&0x07)))
                                            key_ctrl |= bwin_mac_sataus;
                                        flash_save_status();
                                        delayus(10000);
                                        NVIC_SystemReset();
                                    }
                                }
                                else
                                {
                                    if(mMS_TO_TICK(3000) < (conn_rtc_value-press_bt2_time_count))
                                    {
                                        if(0 == (ble_24g_ctrl&bom6239_conning))
                                        {
                                            OM_PMU->SW_RSVD1 |= RSVD1_RF_CONN_EN;
                                            NVIC_SystemReset();
                                        }
                                    }
                                }

                                break;
                            case iMODE_KEY_24G&0x0F:
                                if(iDEVICE_TYPE_24G != device_type)
                                    break;

                                device_key |= bkey_24g_press;
                                if(0==(device_key_bak&bkey_24g_press_bak))
                                {
                                    device_key_bak |= bkey_24g_press_bak;
                                    press_24g_time_count = conn_rtc_value;

//                                    if(iDEVICE_TYPE_24G != device_type)
//                                    {
//                                        device_type = iDEVICE_TYPE_24G;
//                                        bt_index = iDEVICE_TYPE_24G;

//                                        flash_save_status();
//                                        NVIC_SystemReset();
//                                    }
                                }
                                else
                                {
                                    if(mMS_TO_TICK(3000) < (conn_rtc_value-press_24g_time_count))
                                    {
                                        if(iMCU_MODE_NO_DONGLE == work_mode)
                                        {
                                            if(iRF_MODE_CONNECT != rf_mode_type)
                                            {
                                                mMCU_MODE_NORMAL;
                                                rf_mode_convert(iRF_MODE_CONNECT);
                                            }
                                        }
                                    }
                                }

                                break;
                            case iKEY_WIN&0x0F:
                                if(0==(key_ctrl&bwin_mac_sataus))
                                {
                                    key_ctrl |= bwin_mac_sataus;;
                                    key_ctrl |= bfn_save_status;
                                }
                                if(0 == hint_time_count)
                                    hint_time_count = 0x37;

                                break;
                            case iKEY_MAC&0x0F:
                                if(0!=(key_ctrl&bwin_mac_sataus))
                                {
                                    key_ctrl &= ~bwin_mac_sataus;;
                                    key_ctrl |= bfn_save_status;
                                }
                                if(0 == hint_time_count)
                                    hint_time_count = 0x37;

                                break;
//                            case iKEY_WIN_MAC&0x0F:
//							    special_key |= bkey_win_mac;
//								if(0 == (special_key_bak&bkey_win_mac_bak))
//							    {
//								    special_key_bak |= bkey_win_mac_bak;
//                                    key_ctrl ^= bwin_mac_sataus;
//                                    key_ctrl |= bfn_save_status;
//								}

//                                break;
                            case iKEY_WIN_LOCK&0x0F:
                                special_key |= bwin_lock;
                                if(0!=(key_ctrl&bwin_mac_sataus))
                                {
                                    if(0==(special_key_bak&bwin_lock_bak))
                                    {
                                        special_key_bak |= bwin_lock_bak;
                                        key_ctrl ^= bwin_lock_status;
                                        //key_ctrl |= bfn_save_status;  // WIN LOCK掉电不保存
                                    }
                                }
                                break;
                            case iKEY_DIR_LOCK&0x0F:

                                break;
                            case iKEY_WHEEL&0x0F:
                                wheel_status |= bwheel_press;

                                break;
                        }
                    }
                    else if(iKEY_EX_FUN == (decode_data_l & iKEY_SPECIAL_MASK))
                    {
                        key_decode_exfun();
                    }

                    break;
                default:
                    define_key_flag &= ~bkey_decode;
                    define_key_ctrl &= ~bdefine_key_send;
                    break;
            }
        }
    }
    else if(iDEFINE_CMD_TRANSFER == (decode_data_h&iKEY_TRANSFER_MASK))
    {
        length = ((decode_data_l&0xFE) | ((decode_data_h&0x07)<<8));
        i = (decode_data_h&iTRANSFER_MASK);
        if(iTRANSFER_KEY_STATUS == i)
        {                                   // 按键状态转移
            if(define_key_flag&bdefine_key_press)
            {
                if(decode_data_l&(1<<0))    // 负向偏移
                    com_key_addr -= length;
                else                        // 正向偏移
                    com_key_addr += length;
            }
        }
        else if(iTRANSFER_TIMES == i)
        {                                   // 次数转移                
            if(0 == cmd_hong_count)
            {
                if(decode_data_l&(1<<0))    // 负向偏移
                    com_key_addr -= length;
                else                        // 正向偏移
                    com_key_addr += length;
            }
            else if(1 != cmd_hong_count)
            {
                if(decode_data_l&(1<<0))    // 负向偏移
                    com_key_addr -= length;
                else                        // 正向偏移
                    com_key_addr += length;
                cmd_hong_count--;
            }
        }
        else
        {
            define_key_ctrl &= ~bdefine_key_send;
        }
    }
    else if(iDEF_DELAY == (decode_data_h&iDEF_DELAY_MASK))
    {
        if(0==(define_key_flag&bdefine_key_com))
        {
            define_key_flag &= ~bkey_decode;
            return;                             // 延时只会出现在组合按键中
        }

        if(define_key_flag&bdefine_delay_flag)
        {
            key_delay_count = (((drv_rtc_read(OM_RTC)-key_delay_rtc_value)>>6)&0xFFFF);
            if(key_delay_count >= (((decode_data_h&0x3F)<<8)|decode_data_l))
            {                                   // 延时完毕
                define_key_flag &= ~bdefine_delay_flag;
            }
            else
            {
                if((define_key_flag&bcom_key_realse_did) && (0==(define_key_flag&bdefine_key_press)))
                {                               // 延时时间内按键可松开, 加载松开处理
                    bkey_break_or_realse = 1;
                    define_key_flag &= ~bdefine_delay_flag;
                    cmd_hong_count = 1;
                    define_key_flag &= ~bcom_key_realse_did;
                    com_key_addr = ((com_key_addr_back + com_key_length)-2);

                    goto define_key_get_data;
                }
                else if(define_key_status&bkey_status_change)
                {
                    define_key_status &= ~bkey_status_change;
                    bkey_break_or_realse = 1;
                    cmd_hong_count = 1;
                    com_key_addr = ((com_key_addr_back + com_key_length)-2);
                    goto define_key_get_data;
                }
                else
                {
                    return;
                }
            }
        }
        else
        {
            define_key_flag |= bdefine_delay_flag;
            key_delay_count = 0;
            key_delay_rtc_value = drv_rtc_read(OM_RTC);

            return;
        }
    }
    else if(iDEF_COM == (decode_data_h&iDEF_COM_MASK))
    {
        if(0 != (define_key_flag&bkey_decode_end)) 
            return;

        com_key_addr = (((decode_data_h&0x3F)<<8) | (decode_data_l&0xFE));
        com_key_addr_back =  (com_key_addr+0x10);

        flash_read(com_key_addr, 4);
        if(0x5A != flash_fifo[0])
            return;

        define_key_flag |= bdefine_key_com;
        cmd_hong_count = flash_fifo[1];

        com_key_length = ((flash_fifo[2]&0xFE)|(flash_fifo[3]<<8));

        define_key_ctrl &= ~bcom_key_break;
        if(0 != (flash_fifo[2] & (1<<0)))
            define_key_ctrl |= bcom_key_break;            

        define_key_flag &= ~bcom_key_realse_did;
        if(decode_data_l&(1<<0))                // 松开处理
            define_key_flag |= bcom_key_realse_did;

        com_key_addr += 0x10;
    }
define_decode_end:

    if(define_key_flag&bdefine_key_com)         // 组合按键
    {
        if(com_key_addr >= (com_key_length + com_key_addr_back))
        {
            define_key_flag |= bkey_decode_end;
            define_key_ctrl &= ~bcom_decode_ing;
            define_key_ctrl &= ~bcom_key_break;
            bkey_break_or_realse = 1;
        }
        else
        {
            if((define_key_flag&bcom_key_realse_did) && (0==(define_key_flag&bdefine_key_press)))
            {                                   // 松开处理, 加载松开处理
                define_key_flag &= ~bdefine_delay_flag;
                cmd_hong_count = 1;
                define_key_flag &= ~bcom_key_realse_did;
                com_key_addr = ((com_key_addr_back+com_key_length)-2);
                bkey_break_or_realse = 1;
            }

            if(define_key_status&bkey_status_change)
            {                                   // 状态变化
                com_key_addr = ((com_key_addr_back + com_key_length)-2);
                define_key_status &= ~bkey_status_change;
                bkey_break_or_realse = 1;
                cmd_hong_count = 1;
            }
define_key_get_data:
            flash_read(com_key_addr, 2);

            decode_data_l = flash_fifo[0];
            decode_data_h = flash_fifo[1];
            com_key_addr += 2;

            if(0==(define_key_ctrl&bdefine_key_send))
            {
                loop_count++;
                if(8 <= loop_count)
                {                               // 防止按键解码死循环
                    define_key_flag = 0;
                    define_key_flag |= bkey_decode_end;
                    define_key_ctrl &= ~bcom_decode_ing;
                    define_key_ctrl &= ~bcom_key_break;
                }
                else
                {
                    goto define_key_decode_begin;   //组合按键模式下，解码新的数据
                }
            }
        }
    }
    else
    {
        define_key_flag |= bkey_decode_end;
    }
}
