/*******************************************************************************
* Copyright (c) 2016, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: Main.c
*
* 功能说明: 主函数处理程序
* 修改说明:
*******************************************************************************/
#include "main.h"
#include "main_usb.h"
#include "matrix_key.h"
#include "exLed.h"

//-----------------------------------------------------------------------------;
// 变量定义
//

//-----------------------------------------------------------------------------;
// 变量定义
//
bool                        busb_valid;
uint32_t                    device_scan_time;
uint32_t                    logo_scan_time;
uint32_t                    sleep_into_work_rtc;

extern bool                 bperiph_int;
extern unsigned char        sof_count;

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

extern void                 hi5_usb_init(void);
extern void                 usb_sleep(void);

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
void mouse_usb_init(void)
{
    hi5_usb_init();

    mouse_periph_wakeup_enable(WAKEUP_ALL_DISABLE);
    __enable_irq();
    sleep_into_work_rtc = drv_rtc_read(OM_RTC);
    busb_valid = false;
    drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_WAKEUP_DISABLE, NULL);
    drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_START, NULL);
}

/******************************************************************************
* 函数名称: main_24g()
* 功能描述:
* 说    明:
******************************************************************************/
int main_usb(void)
{
    device_scan_time = drv_rtc_read(OM_RTC);
    logo_scan_time = drv_rtc_read(OM_RTC);
    while(1)
    {
        if(0 != (sys_ctrl&bscan_flag))
        {
            matrixkey_scan();
            wheel_scan();

            drv_wdt_keep_alive(OM_WDT);
            if(mMS_TO_TICK(15) < (drv_rtc_read(OM_RTC)-device_scan_time))
            {
                device_scan_time = drv_rtc_read(OM_RTC);
                device_led_process();
                led_hint_process();
            }

            if(mMS_TO_TICK(7) < (drv_rtc_read(OM_RTC)-logo_scan_time))
            {
                logo_scan_time = drv_rtc_read(OM_RTC);
                logo_process();
            }

            sys_ctrl &= ~bscan_flag;
        }
        else
        {
            delayus(20);
        }

        scan_mode_swtich(iMODE_CHECK_DELAY);
        if(0 == (usb_ctrl_flag&busb_suspend_resume))
        {
            uint32_t rtc_temp;

            OM_CRITICAL_BEGIN();
            rtc_temp = drv_rtc_read(OM_RTC);
            if(mMS_TO_TICK(5000) < (rtc_temp-sleep_into_work_rtc))
            {
                usb_ctrl_flag &= bwakeup_usb_enable;
                usb_ctrl_flag |= busb_suspend_resume;
            }
            OM_CRITICAL_END();

            if(true ==busb_valid)
            {
                hid_process();
                usb_data_process();
            }
            else
            {
                sys_tick_count++;
                delayus(2000);
                sys_ctrl |= bscan_flag;
            }
        }
        else
        {
            if(3000<sys_tick_count)
                usb_sleep();
            else
            {
                sys_tick_count++;
                delayus(2000);
                sys_ctrl |= bscan_flag;
            }
        }
    }

    return 1;
}

/******************************************************************************
* 函数名称: usb_sleep()
* 功能描述:
* 说    明:
******************************************************************************/
void usb_sleep(void)
{
    if(0 == (usb_ctrl_flag&bsleep_eable))
    {
        usb_ctrl_flag &= ~busb_suspend_resume;
        return;
    }

    logo_off();
    mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL2);
    mLED_VDD_DIS;
    exled_ctrl = 0x02;
    exLogo_send();

    if(0 == (usb_ctrl_flag & bwakeup_usb_enable))
    {                                       // 不可唤醒
        for(uint8_t i=0; i<250; i++)
        {
            delayus(5000);
            drv_wdt_keep_alive(OM_WDT);
            scan_mode_swtich(iMODE_CHECK_NO_DELAY);

            if(0==(usb_ctrl_flag&busb_suspend_resume))
                goto usb_wakeup_process;
        }

usb_sleep_diswakeup:
        while(1)
        {
            bperiph_int = 0;
            if(0!=(usb_ctrl_flag&busb_suspend_resume))
                drv_pmu_set_low_power_mode(PMU_LPM_STOP1);
            if(0==(usb_ctrl_flag&busb_suspend_resume))
                break;

            for(uint8_t i=0; i<250; i++)
            {
                drv_wdt_keep_alive(OM_WDT);
                delayus(2000);
                if(bperiph_int)
                    scan_mode_swtich(iMODE_CHECK_NO_DELAY);

                if(0==(usb_ctrl_flag&busb_suspend_resume))
                    break;
            }
        }
    }
    else
    {                                       // 可唤醒
        while(1)
        {
            bperiph_int = 0;
            if(0!=(usb_ctrl_flag&busb_suspend_resume))
                drv_pmu_set_low_power_mode(PMU_LPM_STOP1);

            drv_wdt_keep_alive(OM_WDT);
            if(bperiph_int)
            {
                bperiph_int = 0;
                delayus(5000);
                scan_mode_swtich(iMODE_CHECK_NO_DELAY);

                // Wakeup the USB controller via remote pin
                OM_USB->POWER |= USB_POWER_RESUME;
                delayus(10000);
                OM_USB->POWER &= ~USB_POWER_RESUME;

                usb_ctrl_flag &= ~busb_suspend_resume;
            }
            if(0 == (usb_ctrl_flag&busb_suspend_resume))
            {
                break;
            }
        }
    }

usb_wakeup_process:
    mouse_periph_wakeup_enable(WAKEUP_ALL_DISABLE);
    sleep_into_work_rtc = drv_rtc_read(OM_RTC);
    exled_rtc_count=0;
    exio_ctrl = 0;
}

/** @} */

