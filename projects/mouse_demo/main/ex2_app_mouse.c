/**     __  ___     _              ____
 *   ___\ \/ / |__ | | ___  __   _|___ \
 *  / _ \\  /| '_ \| |/ _ \ \ \ / / __) |
 * |  __//  \| |_) | |  __/  \ V / / __/
 *  \___/_/\_\_.__/|_|\___|   \_/ |_____|
 *
 * @file ex2_app_mouse.c
 * @brief exBLE v2 dual-mode mouse product demo.
 * @author onmicro
 * @date 2021/11
 */

/*******************************************************************************
 * INCLUDES
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* exBLE */
#include "ex2_api.h"
#include "ex2_hal.h"
#include "om_driver.h"

#include "ex2_app_mouse.h"
#include "evt.h"
#include "main.h"
#include "mouse.h"

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * CONST & VARIABLES
 */
mouse_adv_state_t mouse_state = MOUSE_LE_STATE_ADV;

/* Peripheral Preferred Connection Parameters @ref ex2_gap_ppcp_t */
extern ex2_gap_ppcp_t ex2_gap_ppcp_value;

extern const char               bt_kb_name_tbl_bt0[MOUSE_NAME_MAX_LEN];
extern const char               bt_kb_name_tbl_bt1[MOUSE_NAME_MAX_LEN];
extern const char               bt_kb_name_tbl_bt2[MOUSE_NAME_MAX_LEN];

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
static bool ex2_app_mouse_broadcast_enable(uint32_t adv_interval_ms, uint32_t adv_timeout_ms, bool is_disc, bool swift_en)
{
    uint8_t adv_ind_len = 0;
    ex2_data_t adv_pkt;
    ex2_data_t adv_rsp_pkt;

    /* ADV_IND.AdvData */
    uint8_t adv_ind[37] = {
        ///Flags: BLE limited discoverable mode and BR/EDR not supported
        0x02, 0x01, BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE,
        ///Complete list of service class UUIDs: HID
        0x03, 0x03, 0x12, 0x18,
        ///Apperance: Keyboard
        0x03, 0x19, 0xC1, 0x03,
        ///Complete Local Name in 11 bytes always.
        (0 + 1), 0x09,
    };

    /* ADV_IND.response */
    uint8_t adv_response[MOUSE_NAME_MAX_LEN] = {
        ///Complete Local Name in 11 bytes always.
        (0 + 1), 0x09,
    };

    if(iDEVICE_TYPE_BT2 == device_type)
        memcpy(bt_kb_name, bt_kb_name_tbl_bt2, sizeof(bt_kb_name_tbl_bt2));
    else if(iDEVICE_TYPE_BT1 == device_type)
        memcpy(bt_kb_name, bt_kb_name_tbl_bt1, sizeof(bt_kb_name_tbl_bt1));
    else //if(iDEVICE_TYPE_BT0 == device_type)
        memcpy(bt_kb_name, bt_kb_name_tbl_bt0, sizeof(bt_kb_name_tbl_bt0));

    /// Complete Local Name.
    if(strlen(bt_kb_name_tbl_bt0) <= 11) {  //如果名字小于等于11，直接放在adv_ind， 否则放在scan response中
        adv_ind[11] = strlen(bt_kb_name) + 1U;
        memcpy(adv_ind+13, bt_kb_name, adv_ind[11] - 1U);

        adv_ind_len = 11 + adv_ind[11] + 1U;  // 11 = 3(Flags) + 4 (HID UUID) + 4(Apperance); NameLength
        adv_rsp_pkt.len = 0;
    } else {
        adv_ind_len = 11;
        adv_response[0] = strlen(bt_kb_name) + 1U;
        memcpy(adv_response+2, bt_kb_name, strlen(bt_kb_name));
        adv_rsp_pkt.len = adv_response[0]+1;
        adv_rsp_pkt.data = adv_response;
    }

    /// swift
    if (swift_en) {
        /// Manufacturer Specific Data: Swift
        const char swift_flag[] = {0x06, 0xFF, 0x06, 0x00, 0x03, 0x00, 0x80};
        memcpy(&adv_ind[adv_ind_len], swift_flag, sizeof(swift_flag));
        adv_ind_len += sizeof(swift_flag);
    }

    if(!is_disc){
        adv_ind[2] = BLE_GAP_ADV_FLAGS_LE_ONLY_NON_DISC_MODE;
        adv_ind_len = 3;
    }
    adv_pkt.data = adv_ind;
    adv_pkt.len  = adv_ind_len;

    hid_notification_enable(0);
    return ex2_gap_set_broadcast_mode(&adv_pkt, &adv_rsp_pkt, is_disc, adv_interval_ms, adv_timeout_ms);
}

uint32_t adv_interval_ms;

//------------------------------------------------------------------------------
// 注意，休眠与配置时间在此函数设置，由于定时有误差，时间最好实际验证
//
void ex2_app_mouse_broadcast_fsm(void)
{                                               // 广播状态机
    bool is_disc;
    bool swift_en;
    uint32_t adv_timeout_ms;
    bool adv_en;

    ble_24g_ctrl &= ~bom6239_sync_ok;
    adv_en = true;
    switch (mouse_state) {
        case MOUSE_LE_STATE_ADV:
            mouse_state = MOUSE_LE_STATE_STOP;
            /* Enter swift adv for pair w/ Manufacture field at 100ms advInterval. Stop adv in 180 seconds. */
            adv_interval_ms = 20;
            adv_timeout_ms = 55*1000;
            is_disc = true;
            swift_en = true;
            break;
        case MOUSE_LE_STATE_STOP:
            adv_en = false;
            break;
        case MOUSE_LE_STATE_ADV_SWIFT:
            mouse_state = MOUSE_LE_STATE_ADV;
            /* Advertise w/o Manufacture field for swift before 3.5 seconds. */
            /* Enter normal(advInterval=10ms) adv and discoverable mode for pair 3.5s timeout. */
            adv_interval_ms = 10;
            adv_timeout_ms = 3500;
            is_disc = true;
            swift_en = false;
            break;
        case MOUSE_LE_STATE_DISCONN:
            mouse_state = MOUSE_LE_STATE_DISCONN_ADV;
            /* Enter fast(advInterval=5ms) adv and non-discoverable, connectable mode for connect-back. Stop connect-back in 10 seconds */
            adv_interval_ms = 5;
            adv_timeout_ms = 5*1000;
            is_disc = false;
            swift_en = false;
            break;
        case MOUSE_LE_STATE_DISCONN_ADV:
            mouse_state = MOUSE_LE_STATE_STOP;
            /* Enter slow(advInterval=100ms) adv and non-discoverable, connectable mode for connect-back. Stop connect-back in 60 seconds */
            adv_interval_ms = 20;
            adv_timeout_ms = 5*1000;
            is_disc = false;
            swift_en = false;
            break;
        default:
            adv_en = false;
            break;
    }

    if (adv_en) {
        ex2_app_mouse_broadcast_enable(adv_interval_ms, adv_timeout_ms, is_disc, swift_en);
    }
}

extern uint8_t              kb_bd_addr[];
extern ms_sleep_level_t     ms_sleep_level;

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
void ex2_app_mouse_ble_init(void)
{
    adv_interval_ms = 0;
    ms_sleep_level = MS_SLEEP_LEVEL0;

    evt_callback_register(EVT_TYPE_BLE, ex2_stk_process);
    /* Part B, 1.3.2.1 Static device address */
    kb_bd_addr[5] |= 0xc0;
    ex2_stk_init(kb_bd_addr);
    ex2_stk_register_app_evt_handler(app_ble_evt_dispatch);
    ex2_smp_enable_bond();

    if(ble_24g_ctrl&bom6239_conning)
    {
        drv_rf_set_tx_power(DRV_RF_PA_PWR_0dBm);
        mouse_state = MOUSE_LE_STATE_ADV_SWIFT;
    }
    else
        {                                           // 目前设置为5dbm功率，若对距离有要求就设置为8dbm
        drv_rf_set_tx_power(DRV_RF_PA_PWR_5dBm);
        mouse_state = MOUSE_LE_STATE_DISCONN;
    }

    ex2_app_mouse_broadcast_fsm();
}


/** @} */
