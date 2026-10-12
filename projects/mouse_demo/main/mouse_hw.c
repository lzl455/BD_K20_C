/* ----------------------------------------------------------------------------
 * Copyright (c) 2020-2030 OnMicro Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of OnMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -------------------------------------------------------------------------- */

/**
 * @file     mouse_sw.c
 * @brief    ble mouse sensor & wheel scan use io simulate by hardware
 * @date     20 JUN 2024
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

/*******************************************************************************
 * INCLUDES
 */
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "om_driver.h"
#include "ex2_app_mouse.h"
#include "mouse.h"
#include "ex2_api.h"
#include "ex2_hal.h"
#include "main.h"
#include "led.h"
#include "lvd.h"
#include "wheel.h"
#include "exLed.h"

#include "matrix_key.h"
#include "flash_process.h"
#include "userdefined_key.h"
#include "time_delay.h"

#include "usb_cfg_info.h"

/*******************************************************************************
 * CONST & VARIABLES
 */
 ms_sleep_level_t ms_sleep_level = MS_SLEEP_LEVEL0;
//-----------------------------------------------------------------------------
// BT5.4 KB-1
//
const char                  bt_kb_name_tbl_bt0[MOUSE_NAME_MAX_LEN] ="AUSDOM K98Pro BT1";
const char                  bt_kb_name_tbl_bt1[MOUSE_NAME_MAX_LEN] ="AUSDOM K98Pro BT2";
const char                  bt_kb_name_tbl_bt2[MOUSE_NAME_MAX_LEN] ="AUSDOM K98Pro BT3";

char                        bt_kb_name[MOUSE_NAME_MAX_LEN];

uint8_t                     ble_interval;

extern bool                 bperiph_int;
extern uint32_t             adv_interval_ms;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
pmu_lpm_t pm_checker_callback(void)
{
    if(ms_sleep_level < MS_SLEEP_LEVEL2) {
        if(MS_SLEEP_LEVEL0 == ms_sleep_level)
        {                                       // 此处根据实际情况设置，有PWM，ARGB等不同外设，休眠状态会有差异
            if(true==bargb_valid)
                return PMU_LPM_IDLE;
            if(0 != OM_RTC->TICK)
                return PMU_LPM_IDLE;
        }

        /* 距离下次唤醒时间剩余300us， 不进入休眠, 否则进入休眠 */
        if ((ex2_stk_sleep_duration_get() > 10))
            return PMU_LPM_STOP1;           // PWM没有打开，可以进入STOP1
    }
    else
    {
        if(0 == (bat_status&bcharging))
        {
            ex2_stk_uninit();
            //进入深睡眠前需要存一些配置信息(如dpi、模式、地址等)到HS_PMU->SCRATCH, 醒来后可通过OM_CPM->RSTCTRL判断复位原因决定广播还是回连。

            logo_off();                         // 此处休眠不同外设情况下处理有差异
            exled_ctrl = 0x02;
            exLogo_send();

            drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_STOP, NULL);
            DRV_RCC_CLOCK_ENABLE(RCC_CLK_ENCODER, 0U);
            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL2);
            drv_pmu_set_low_power_mode(PMU_LPM_DEEP_SLEEP);
            while(1);        
        }
        else
            {                                   // 充电状态不进人休眠
            if(bperiph_int)
                NVIC_SystemReset();

            if((ex2_stk_sleep_duration_get() > 10))
            {
                if(0x00000000 == OM_PWM->PWMCON)
                    return PMU_LPM_STOP1;           // PWM没有打开，可以进入STOP1
                else
                    return PMU_LPM_IDLE;
            }
        }
    }

    return PMU_LPM_IDLE;
}

extern bool ex2_hid_tx_notification_mouse(uint8_t *buf);
extern bool ex2_hid_tx_notification_keyboard(uint8_t *buf);
extern bool ex2_hid_tx_notification_bitmap_kb(uint8_t *buf);
extern bool ex2_hid_tx_notification_consumer_control(uint8_t *buf);
extern bool profile_bas_tx_notification(uint8_t level);
extern  uint8_t hid_keyboard_out_report_value;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
__RAM_CODE uint8_t ex2_app_mouse_scan(void)
{
    uint8_t temp_buff[8];

    if (!hid_notification_is_enabled()) {
        return 0;
    }

    ble_24g_ctrl |= bom6239_sync_ok;

    if(MS_SLEEP_LEVEL0 == ms_sleep_level)
    {
        matrixkey_scan();
        wheel_scan();
        logo_process();

        drv_ledc_write();                       // ARGB每个周期调用一次写数据处理

        lvd_scan_count++;
        if(0==(lvd_scan_count&0x01))
            device_led_process();               // 15ms
        else
            led_hint_process();
    }
    else
    {
        logo_off();
        led_hint_process();
        exLogo_send();
    }
	scan_mode_swtich(iMODE_CHECK_DELAY);

    kb_led_status = hid_keyboard_out_report_value;
    if(0!=(m_data_flag&bstd_kb_data_send))
    {
        temp_buff[0] = std_key[0];
        temp_buff[1] = 0;
        memcpy(temp_buff+2, std_key+1, 6);
        if(true == ex2_hid_tx_notification_keyboard(temp_buff))
        {
            rtc_init_value = drv_rtc_read(OM_RTC);
            m_data_flag &= ~bstd_kb_data_send;
            key_tx_count = 0;
        }
        return 1;
    }
    else if(0!=(m_data_flag&bmmk_data_send))
    {
        temp_buff[0] = mmk_data_l;
        temp_buff[1] = mmk_data_h;
        if(true == ex2_hid_tx_notification_consumer_control(temp_buff))
        {
            rtc_init_value = drv_rtc_read(OM_RTC);
            m_data_flag &= ~bmmk_data_send;
            mmk_tx_count = 0;
        }
        return 1;
    }
    else if(0!=(m_data_flag&bstd_ex_data_send))
    {
        if(true == ex2_hid_tx_notification_bitmap_kb(std_key+7))
        {
            rtc_init_value = drv_rtc_read(OM_RTC);
            m_data_flag &= ~bstd_ex_data_send;
            key_ex_tx_count = 0;
        }
        return 1;
    }
    else if(false != bbat_update)
    {
        if(true == profile_bas_tx_notification(bat_value))
            bbat_update=false;
        return 1;
    }
    else if(0!=m_tx_count)
    {                                           /* 未扫描到数据 */
        temp_buff[0] = mouse_data_key&0x1F;       // button
        temp_buff[1] = ((mouse_x>>0)&0xFF);       // x
        temp_buff[2] = (((mouse_x>>8)&0x0F)|((mouse_y<<4)&0xF0)); // y
        temp_buff[3] = ((mouse_y>>4)&0xFF);       //
        temp_buff[4] = mouse_data_z;              // wheel
        temp_buff[5] = 0;                         //til
        if(true == ex2_hid_tx_notification_mouse(temp_buff))
        {
            rtc_init_value = drv_rtc_read(OM_RTC);
            m_data_flag &=~(bmouse_data_send);
            mouse_x = 0;
            mouse_y = 0;
            mouse_data_z = 0;
            m_tx_count = 0;
            return 1;
        }
    }
    else
    {
        if(true == bsave_ble_id)
        {
            bsave_ble_id = false;
            flash_save_ble_addr();
        }
    }
    return 0;
}

extern ex2_gap_ppcp_t       ex2_gap_ppcp_value;
extern mouse_adv_state_t    mouse_state;
extern bool                 bscan_sensor_en;

extern uint16_t ll_ctrl_get_peer_company_id(void);
extern void stk_notify_event_app(uint32_t evt);

/*********************************************************************
 * LOCAL FUNCTIONS
 */
void app_ble_evt_dispatch(uint32_t events)
{
    static uint32_t connect_start_time = 0; /* work around intel bluetooth bug */
    if (events & EX2_EVENT_APP_CONNECT_IND) {
        mouse_periph_wakeup_enable(WAKEUP_ALL_DISABLE);
        drv_rf_set_tx_power(DRV_RF_PA_PWR_0dBm);
        /* stop polling the peripheral*/
        ex2_ll_polling_time_stop();
        connect_start_time = 0;
    }
    if (events & (EX2_EVENT_APP_SLAVE_TERMINATED)) {
        uint8_t bda[6];
        drv_ble_get_bda(bda);
        /* reset rtc & rf module */
        ex2_hal_uninit();
        /* Avoid conn activites during ms delay. */
        __disable_irq();
        ex2_stk_init(bda);
        mouse_state = MOUSE_LE_STATE_DISCONN;
        ex2_app_mouse_broadcast_fsm();

        __enable_irq();
    }
    if (events & EX2_EVENT_APP_CONN_TIMEOUT) {
        __disable_irq();
        NVIC_SystemReset();
    }

    if(events & EX2_EVENT_APP_MASTER_TERMINATED) {
        ms_sleep_level=MS_SLEEP_LEVEL2;
    }
    if (events & (EX2_EVENT_APP_PAIR_COMPLETED | EX2_EVENT_APP_RECONNECT)) {
        if (events & EX2_EVENT_APP_RECONNECT) {
            hid_notification_enable(1);
        }
    }
    if (events & EX2_EVENT_APP_VERSION_EXCHANGE) {
        if(ll_ctrl_get_peer_company_id() == 0x0002/* Intel */) {  /* work around intel bluetooth bug */
            connect_start_time = drv_rtc_read(OM_RTC);
        }
    }
    if (events & EX2_EVENT_APP_CONN_SLAVE) {
        if (!(OM_RTC->INTMASK & RTC_INTMASK_ALARM0_INTRAW_STATUS_MASK)) {
            if (hid_notification_is_enabled())
            {
                ex2_l2cap_update_conn_para(&ex2_gap_ppcp_value);
                ex2_ll_polling_time_start();
                drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_WAKEUP_DISABLE, NULL);
                drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_START, NULL);
                exled_rtc_count=0;
                exio_ctrl = 0;

                if(ble_24g_ctrl&bom6239_conning)
                {
                    ble_24g_ctrl |= bom6239_conn_ok;
                    bsave_ble_id = true;
                }
            }
        }
        if(connect_start_time) { /* work around intel bluetooth bug */
            if (EX2_TIME_OLDER_THAN(connect_start_time+EX2_MS_TO_TICK(5000), drv_rtc_read(OM_RTC))) {
                if(!hid_notification_is_enabled()) {
                    connect_start_time = 0;
                    stk_notify_event_app(EX2_EVENT_APP_CONN_TIMEOUT);
                }
            }
        }
    }
    if (events & EX2_EVENT_APP_ADV_TIMEOUT) {
        if(mouse_state == MOUSE_LE_STATE_STOP) { /* 广播一直没有master连接，超时进入deepsleep*/
            ms_sleep_level = MS_SLEEP_LEVEL2;
        } else {
            ex2_app_mouse_broadcast_fsm();
        }
    }

    if(events & EX2_EVENT_APP_ADV_EVENT_DONE) { /* 一个广播事件结束 */
        sys_tick_count += adv_interval_ms;
        ble_24g_ctrl |= bom6239_sync_ing;
        matrixkey_scan();
        scan_mode_swtich(iMODE_CHECK_DELAY);
        logo_off();
        logo_process();
        device_led_process();
    }
}

/*********************************************************************
 * LOCAL FUNCTIONS
 */

__RAM_CODE void drv_rtc_isr_callback(void)
{
    uint32_t rtc_count;

    rtc_count = drv_rtc_read(OM_RTC);
    if(!rtc_init_value)
    {
        rtc_init_value = rtc_count;
    }

    if(MS_SLEEP_LEVEL2 == ms_sleep_level)
    {
        while (0 == (OM_RTC->CR & RTC_CR_ALARM0_WRITE_STATUS_MASK));
        OM_RTC->ALARM0 = (rtc_count + mMS_TO_TICK(16));
        led_hint_process();
        return;
    }

    if (hid_notification_is_enabled())
    {
        switch (ms_sleep_level)
        {
            case MS_SLEEP_LEVEL0:
                if(ble_sleep_1_time_tbl[sleep_time_ble&0x07] > (rtc_count-rtc_init_value))
                {
                    ex2_ll_set_next_polling_time(0);
                }
                else
                {
                    rtc_init_value = rtc_count;
                    ms_sleep_level = MS_SLEEP_LEVEL1;
                    mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL1);

                    logo_off();
                    ex2_ll_set_next_polling_time(1);
                }
                sys_tick_count += 8;

                break;
            case MS_SLEEP_LEVEL1:
                if(ble_sleep_2_time_tbl[(sleep_time_ble>>4)&0x07] > (rtc_count-rtc_init_value))
                {
                    ex2_ll_set_next_polling_time(1);
                }
                else
                {
                    rtc_init_value = rtc_count;
                    ex2_ll_set_next_polling_time(0);
                    ms_sleep_level = MS_SLEEP_LEVEL2;
                }
                sys_tick_count += 300;

                break;
            default:
                break;
        }
    }

    if(ex2_app_mouse_scan())
    {
        if(MS_SLEEP_LEVEL0 != ms_sleep_level)
        {
            ms_sleep_level = MS_SLEEP_LEVEL0;
            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL0);
            exled_rtc_count=0;
        }

        ex2_stk_interrupt();
    }
}
