/*******************************************************************************
* Copyright (c) 2012, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: sleep.c
* 功能说明:
* 修改说明: 无
*******************************************************************************/
#include "main_24g.h"
#include "exLed.h"

//-----------------------------------------------------------------------------;
// 常量定义区                                   // 定义只有函数内部使用的常量
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
extern bool                 bperiph_int;

//----------------------------------------------------------------------------;
// 表格定义区

/******************************************************************************
* 函数名称: sleep_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明: 无
******************************************************************************/
void sleep_process(void)
{
    uint8_t i;
    uint32_t rtc_value;
    static uint8_t no_dongle_time_count;

    switch(work_mode)
    {
        case iMCU_MODE_NORMAL:
            if(iRF_MODE_NORMAL == rf_mode_type)
            {                               // RF正常模式,检测是否进入休眠
                mRF_CE_LOW_IDLE;
                delayus(250);
                mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL1);
                drv_pmu_clear_wakeup();
                mMCU_MODE_SLEEP;

                sys_ctrl |= bscan_flag;
                bperiph_int = 0;
                device_led_off();

                while(1)
                {
                    drv_pmu_set_low_power_mode(PMU_LPM_STOP1);
                    drv_wdt_keep_alive(OM_WDT);
                    if(bperiph_int)
                        break;

                    led_hint_process();
                    if(0 == (bat_status&bcharging))
                    {
                        goto MCU_MODE_PD_PRPCESS;
                    }
                }

                rf_ctrl_reg |= (brf_sync_time|brf_sync_status);
                mMCU_MODE_NORMAL;
                mouse_24g_init();
            }
            else if(iRF_MODE_SYNC == rf_mode_type)
            {
                if((rf_ctrl_reg & brf_sync_end)
                    &&(0==(rf_ctrl_reg & brf_sync_result)))
                {
                    mMCU_MODE_NO_DONGLE;
                    no_dongle_time_count = 0;
                    b24g_nromal = false;
                    ble_24g_ctrl |= bom6239_sync_ing;
                }
            }

            break;
        case iMCU_MODE_NO_DONGLE:
            if(rf_ctrl_reg & brf_sync_end)
            {
                if(rf_ctrl_reg & brf_sync_result)
                {
                    rf_ctrl_reg |= brf_sync_time;
                    rf_mode_convert(iRF_MODE_SYNC);
                }
                else
                {
                    if(bkey_24g_press == (device_key&bkey_24g_press))
                        return;

                    rf_ctrl_reg &= ~(brf_sync_time|brf_sync_status);

                    mouse_periph_wakeup_enable(WAKEUP_ALL_DISABLE);
                    logo_off();
                    key_tx_count = 0;
                    mmk_tx_count = 0;
                    rtc_value = drv_rtc_read(OM_RTC);
                    do
                    {
                        rf_normal_mode_sleep();
                        drv_wdt_keep_alive(OM_WDT);

                        i++;
                        if(3==(i&0x07))
                        {
                            led_hint_process();
                        }
                        else if(1==(i&0x01))
                        {
                            device_led_process();
                        }
                        else if(0==(i&0x07))
                        {
                            scan_mode_swtich(iMODE_CHECK_NO_DELAY);
                            if(true == bmode_swtich_valid)
                                return;
                            logo_process();
                        }
                        matrixkey_scan();
                        if((0!=key_tx_count)||(0!=mmk_tx_count))
                        {
                            no_dongle_time_count=0;
                            rf_ctrl_reg |= (brf_sync_time|brf_sync_status);
                            break;
                        }

                        if(iDEFAULT_NO_DONGLE_MODE_TIME > no_dongle_time_count)
                        {
                            if(mMS_TO_TICK(950) < (drv_rtc_read(OM_RTC)-rtc_value))
                                break;
                        }
                        else
                        {
                            if(0 == (bat_status&bcharging))
                                break;
                        }
                    }
                    while(1);

                    no_dongle_time_count++;
                    if(iDEFAULT_NO_DONGLE_MODE_TIME < no_dongle_time_count)
                    {
                        if(0 == (bat_status&bcharging))
                            goto MCU_MODE_PD_PRPCESS;
                    }

                    mouse_24g_init();
                    sys_ctrl |= bscan_flag;
                }
            }
            break;
        default:                                // iMCU_MODE_PD:
MCU_MODE_PD_PRPCESS:
            logo_off();
            exled_ctrl = 0x02;
            exLogo_send();

            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL2);
            drv_pmu_set_low_power_mode(PMU_LPM_DEEP_SLEEP);
            while(1);
            break;
    }
}
