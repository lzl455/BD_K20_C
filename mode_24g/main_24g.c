/*******************************************************************************
* Copyright (c) 2016, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: Main.c
*
* 功能说明: 主函数处理程序
* 修改说明:
*******************************************************************************/
#include "main_24g.h"

//-----------------------------------------------------------------------------;
// 变量定义
//

//-----------------------------------------------------------------------------;
// 变量定义
//
bool                        b24g_nromal;

volatile uint32_t           rtc_reload_value;
unsigned char               dat_24g_0[32];
unsigned char               dat_24g_1[32];

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

extern void rtc_init(void);
extern void ex2_hal_uninit(void);

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
void mouse_24g_init(void)
{
    mouse_periph_wakeup_enable(WAKEUP_ALL_DISABLE);

    drv_rf24g_init();
    rf_mode_convert(iRF_MODE_SYNC);
    rtc_init();

    NVIC_EnableIRQ(RTC_IRQn);
    rtc_reload_value = drv_rtc_read(OM_RTC) + iTICK_INIT_VALUE;
    drv_rtc_set_alarm0(rtc_reload_value);

    __enable_irq();
}

/******************************************************************************
* 函数名称: main_24g()
* 功能描述:
* 说    明:
******************************************************************************/
int main_24g(void)
{
    while(1)
    {
        if(0 != (sys_ctrl&bscan_flag))
        {
            matrixkey_scan();

            drv_wdt_keep_alive(OM_WDT);
            sys_ctrl &= ~bscan_flag;
            if(iRF_MODE_NORMAL == rf_mode_type)
            {
                wheel_scan();
                if(ble_sleep_1_time_tbl[sleep_time_24g&0x07] < (drv_rtc_read(OM_RTC)-rtc_init_value))
                {
                    sleep_process();
                }
            }
            else
            {
                device_led_process();
                led_hint_process();
                logo_process();
                sleep_process();
            }
        }

        switch(rf_mode_type)
        {
            case iRF_MODE_CONNECT:
                rf_connect_process();

                break;
            case iRF_MODE_SYNC:
                rf_sync_process();

                break;
            case iRF_MODE_NORMAL:
                rf_nromal_process();

                break;
        }

        scan_mode_swtich(iMODE_CHECK_DELAY);
        if(true == bmode_swtich_valid)
        {
            rf_mode_convert(iRF_MODE_NONE);
            ex2_hal_uninit();
            break;              // 切换模式，返回主程序
        }
    }

    return 1;
}

/******************************************************************************
* 函数名称: RTC_IRQHandler_24G
* 功能描述: 24G模式RTC中断
* 输入参数:
* 输出参数:
* 说    明: 无
******************************************************************************/
__RAM_CODE void RTC_IRQHandler_24G(void)
{
    switch(work_mode&0x03)
    {
        case iMCU_MODE_NORMAL:
            sys_tick_count++;
            if(iRF_MODE_NORMAL == rf_mode_type)
            {
                uint32_t i;
                while (!OM_RTC->CNT_VALID);
                i = OM_RTC->CNT;
                rtc_reload_value += iTICK_INIT_VALUE;
                while(1)
                {
                    if(rtc_reload_value >= (i+5))
                        break;
                    rtc_reload_value += iTICK_INIT_VALUE;
                    if(0 == (sys_tick_count&0x01))
                    {
                        freq_index++;
                        rf_work_mode = iRF_WORK_TX0;
                    }
                    sys_tick_count++;
                }
                while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
                OM_RTC->ALARM0 = rtc_reload_value;

                freq_index++;
                freq_index&=0x1F;
                rf_work_mode = iRF_WORK_TX0;
                if(1 == (freq_index&0x03))
                {
                    rf_rsp_time_count++;
                    if((iRF_RSP_CYCLE_COUNT <= rf_rsp_time_count))
                        rf_ctrl_reg |= brf_data_rx;
                }

                sys_ctrl |= bscan_flag;
            }
            else
            {
                while (!OM_RTC->CNT_VALID);
                rtc_reload_value = OM_RTC->CNT + iTICK_INIT_VALUE_EX;
                while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
                OM_RTC->ALARM0 = rtc_reload_value;

                rf_work_mode = iRF_WORK_TX0;
                sys_ctrl |= bscan_flag;
            }
            if(0 == (sys_tick_count&0x01))
                drv_ledc_write();

            break;
        case iMCU_MODE_SLEEP:
            while (!OM_RTC->CNT_VALID);
            rtc_reload_value = OM_RTC->CNT + iTICK_INIT_SLEEP;
            while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
            OM_RTC->ALARM0 = rtc_reload_value;

            sys_ctrl |= bscan_flag;

            break;
        default:
            while (!OM_RTC->CNT_VALID);
            rtc_reload_value = (OM_RTC->CNT+iTICK_INIT_VALUE_EX);
            while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
            OM_RTC->ALARM0 = rtc_reload_value;

            sys_tick_count++;
            sys_ctrl |= bscan_flag;
            break;
    }
}

/** @} */

