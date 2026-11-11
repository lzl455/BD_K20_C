/**     __  ___     _              ____
 *   ___\ \/ / |__ | | ___  __   _|___ \
 *  / _ \\  /| '_ \| |/ _ \ \ \ / / __) |
 * |  __//  \| |_) | |  __/  \ V / / __/
 *  \___/_/\_\_.__/|_|\___|   \_/ |_____|
 *
 * @file ex2_profile_hid_mouse.c
 * @brief exBLE v2 Profile layer, including DIS, BAS, HIDS, OTA for mouse.
 * @author onmicro
 * @date 2020/02
 */

#include <stdint.h>
#include <stdbool.h>
#include "ex2_api.h"
#include "ex2_app_mouse.h"
#include "mouse.h"

/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/
extern uint8_t  kb_led_status;

/* GAP ---------------------------------------------------------------------- */
/* Peripheral Preferred Connection Parameters @ref ex2_gap_ppcp_t */
ex2_gap_ppcp_t ex2_gap_ppcp_value = {
    .interval_min = 6,    /* IntervalMin=6*1.25=7.5ms */
    .interval_max = 6,    /* IntervalMax=9*1.25=11.25ms */
    .latency = 44,        /* Latency=44 */
    .timeout = 216,       /* Timeout=216*10ms=2s */
};

/* GATT --------------------------------------------------------------------- */
#if (PROFILE_SIG_GATT)
static uint16_t _gatt_service_changed_value[4] = {0};
static uint16_t _gatt_service_changed_cccd_value = 0;
#endif  /* (PROFILE_SIG_GATT) */

/* DIS profile -------------------------------------------------------------- */
#if (PROFILE_SIG_DIS)
#define FW_VERSION_ID(major, minor)         (((major) << 8) + (minor))
static const ble_dis_pnp_t _dis_pnp_value = {
    .vid_source = BLE_DIS_VID_SORUCE_USB,
    .vid        = 0x32C2,                       // 蓝牙VID
    .pid        = 0x0029,                       // 蓝牙PID
    .prod_ver   = FW_VERSION_ID(1, 0),
};
#endif  /* (PROFILE_SIG_DIS) */

/* BAS profile -------------------------------------------------------------- */
#if (PROFILE_SIG_BAS)
static uint8_t _bas_bat_lvl_value = 100;
static uint16_t _bas_cccd_value;

/**
 * @brief 发送电池电量notification data至手机。
 * @note BAS profile调用att_tx_notification()来发送该notification data.
 *
 * @param [in] level - Battery level in percentage [0~100].
 * @return true for success, false for no space in tx queue or notification is not enabled.
 */
bool profile_bas_tx_notification(uint8_t level)
{
    _bas_bat_lvl_value = level;
    _bas_cccd_value=0x01;
    if (_bas_cccd_value & 0x01/*notify*/) {
        return ex2_att_tx_notification(ATT_HANDLE_BAS_BAT_LVL_CV, &level, 1);
    }
    return false;
}
#endif  /* (PROFILE_SIG_BAS) */

/* HIDS profile ------------------------------------------------------------- */
#if (PROFILE_SIG_HIDS)
///HID input/output report ID.
typedef enum {
    HID_REPORT_ID_MOUSE_INPUT             = 1,   /* Mouse input report ID */
    HID_REPORT_ID_CONSUMER_CONTROL_INPUT  = 2,   /* Consumer Control input report ID */
    HID_REPORT_ID_KEYBOARD_INPUT          = 3,   /* Keyboard input report ID */
    HID_REPORT_ID_BITMAP_KB_INPUT         = 4,   /* BITMAP Keyboard input report ID */
} hid_report_id_t;

// Protocol Mode values
static ble_hid_protocol_mode_t _hid_protocol_mode_value = BLE_HID_PROTOCOL_MODE_REPORT;
static uint16_t _hid_cccd_value;

// Information Flags
static const ble_hid_info_t _hid_info_value = {
    .bcdHID = 0x111,   // bcdHID (USB HID version)
    .bCountryCode = 0,
    .RemoteWake = 0,
    .NormallyConnectable = 1,
};

#if (PROFILE_HID_MOUSE)
///u8Button, s8X, s8Y, s8Wheel
static uint8_t hid_mouse_report_value[6];
#endif

#if (PROFILE_HID_CONSUMER_CONTROL)
///consumer control bitmap value
static uint8_t hid_consumer_control_report_value[2];
#endif

#if (PROFILE_HID_KEYBOARD)
///keyboard key code
static uint8_t hid_keyboard_in_report_value[8];
static uint8_t bitmap_keyboard_report_value[15];
uint8_t hid_keyboard_out_report_value;
#endif

static const uint8_t _hid_report_map_value[] = {
#if (PROFILE_HID_KEYBOARD)
    0x05, 0x01,                       /* Usage Page (Generic Desktop)*/
    0x09, 0x06,                       /* Usage (Keyboard)*/
    0xA1, 0x01,                       /* Collection (Application)*/
    0x85, HID_REPORT_ID_KEYBOARD_INPUT,   /*     Report ID (3) */
    0x05, 0x07,                       /*     Usage Page (Key Codes)*/
    0x19, 0xe0,                       /*     Usage Minimum (KeyBoard Left Control)*/
    0x29, 0xe7,                       /*     Usage Maximum (KeyBoard Right GUI)*/
    0x15, 0x00,                       /*     Logical Minimum (0)*/
    0x25, 0x01,                       /*     Logical Maximum (1)*/
    0x75, 0x01,                       /*     Report Size (1)*/
    0x95, 0x08,                       /*     Report Count (8)*/
    0x81, 0x02,                       /*     Input (Data, Variable, Absolute)*/
    0x95, 0x01,                       /*     Report Count (1)*/
    0x75, 0x08,                       /*     Report Size (8)*/
    0x81, 0x01,                       /*     Input (Constant) reserved byte(1)*/

    0x05, 0x07,                          /*     Usage Page (Key Codes)*/
    0x95, 0x05,                          /*     Report Count (5)*/
    0x75, 0x01,                          /*     Report Size (1)*/
    0x05, 0x08,                          /*     Usage Page (LEDs)*/
    0x19, 0x01,                          /*     Usage Minimum (Num Lock)*/
    0x29, 0x05,                          /*     Usage Maximum (Kana)*/
    0x91, 0x02,                          /*     Output (Data, Variable, Absolute)*/
    0x95, 0x01,                          /*     Report Count (1)*/
    0x75, 0x03,                          /*     Report Size (3)*/
    0x91, 0x01,                          /*     Output (Constant) reserved byte(1)*/

    0x95, 0x06,                          /*     Report Count (6)*/
    0x75, 0x08,                          /*     Report Size (8)*/
    0x15, 0x00,                          /*     Logical Minimum (0)*/
    0x25, 0xff,                          /*     Logical Maximum (255)*/
    0x05, 0x07,                          /*     Usage Page (Key codes)*/
    0x19, 0x00,                          /*     Usage Minimum (0)*/
    0x29, 0xFF,                          /*     Usage Maximum (101)*/
    0x81, 0x00,                          /*     Input (Data, Array) Key array(6 bytes)*/
    0xC0,                                /* End Collection (Application)*/
#endif

#if (PROFILE_HID_CONSUMER_CONTROL)
    0x05 , 0x0C,                      /* USAGE_PAGE (Consumer Devices)*/
    0x09 , 0x01,                      /* USAGE (Consumer Control)*/
    0xA1 , 0x01,                      /* COLLECTION (Application)*/
    0x85 , HID_REPORT_ID_CONSUMER_CONTROL_INPUT,   /*    REPORT_ID (2)*/
    0x15 , 0x00,                      /*    LOGICAL_MINIMUM (0)*/
    0x26 , 0xff, 0x03,                /*    LOGICAL_MAXIMUM (0x03ff)*/
    0x19 , 0x00,                      /*    Usage Minimum (Unassigned)*/
    0x2A , 0xff, 0x03,                /*    Usage Maximum (0x03ff)*/
    0x75 , 0x10,                      /*    REPORT_SIZE (16)*/
    0x95 , 0x01,                      /*    REPORT_COUNT (1)*/
    0x81 , 0x00,                      /*    INPUT (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)*/
    0xC0 ,                            /* END_COLLECTION*/
#endif

#if (PROFILE_HID_BITMAP_KEYBOARD)
    0x05, 0x01,                       /* Usage Page (Generic Desktop)   */                                                      
    0x09, 0x06,                       /* Usage (Keyboard)    */                                                                 
    0xA1, 0x01,                       /* Collection (Application) */                                                            
    0x85, HID_REPORT_ID_BITMAP_KB_INPUT,                       /*     Report ID (4)  */                                                                  
    0x05, 0x07,                       /*     Usage Page (Keyboard/Keypad) */                                                    
    0x19, 0x00,                       /*     Usage Minimum (Undefined)  */                                                      
    0x29, 0x77,                       /*     Usage Maximum (Keyboard Select) */                                                 
    0x15, 0x00,                       /*     Logical Minimum (0)  */                                                            
    0x25, 0x01,                       /*     Logical Maximum (1)  */                                                            
    0x95, 0x78,                       /*     Report Count (120)   */                                                            
    0x75, 0x01,                       /*     Report Size (1)  */                                                                
    0x81, 0x02,                       /*     Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit) */                                     
    0xC0,                             /* End Collection */
#endif

#if (PROFILE_HID_MOUSE)
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,        // Usage (Mouse)
    0xA1, 0x01,        // Collection (Application)
    0x85, HID_REPORT_ID_MOUSE_INPUT, //   Report ID (2)
    0x09, 0x01,        //   Usage (Pointer)
    0xA1, 0x00,        //   Collection (Physical)
    0x05, 0x09,        //     Usage Page (Button)
    0x19, 0x01,        //     Usage Minimum (0x01)
    0x29, 0x08,        //     Usage Maximum (0x08)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x95, 0x08,        //     Report Count (8)
    0x75, 0x01,        //     Report Size (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,        //     Usage (X)
    0x09, 0x31,        //     Usage (Y)
    0x16, 0x01, 0xF8,  //     Logical Minimum (-2047)
    0x26, 0xFF, 0x07,  //     Logical Maximum (2047)
    0x75, 0x0C,        //     Report Size (12)
    0x95, 0x02,        //     Report Count (2)
    0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x38,        //     Usage (Wheel)
    0x15, 0x81,        //     Logical Minimum (-127)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0C,        //     Usage Page (Consumer)
    0x0A, 0x38, 0x02,  //     Usage (AC Pan)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0xC0,              // End Collection
#endif
};

/**
 * @brief send HID notification data to host
 * @note HID profile call att_tx_notification() to send HID notification data.
 *
 * @return true for success, false for no space in tx queue or notification is not enabled.
 */
bool ex2_hid_tx_notification_mouse(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= MOUSE_DATA_IN_TXQ_MAX_NUM)
    {
        return ex2_att_tx_notification(ATT_HANDLE_HID_MOUSE_REPORT_CV, buf, 6);
    }
    else
        return false;
}

bool ex2_hid_tx_notification_keyboard(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= MOUSE_DATA_IN_TXQ_MAX_NUM)
        return ex2_att_tx_notification(ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CV, buf, 8);
    else
        return false;
}

uint8_t ex2_hid_rx_command_keyboard(void)
{
    return kb_led_status;
}

bool ex2_hid_tx_notification_bitmap_kb(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= MOUSE_DATA_IN_TXQ_MAX_NUM)
        return ex2_att_tx_notification(ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CV, buf, 15);
    else
        return false;
}

bool ex2_hid_tx_notification_consumer_control(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= MOUSE_DATA_IN_TXQ_MAX_NUM)
    {
        return ex2_att_tx_notification(ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CV, buf, 2);
    }
    else
        return false;
}

void hid_notification_enable(uint16_t hid_cccd)
{
    _hid_cccd_value = hid_cccd;
    _bas_cccd_value = hid_cccd;
}

uint16_t hid_notification_is_enabled(void)
{
    return _hid_cccd_value & 0x01;
}

att_error_code_t hid_control_point_write(uint16_t offset, uint8_t *payload, uint16_t len)
{
    ble_hid_ctrl_point_t ctrl_point;
    ctrl_point = payload[0];
    // TODO:
    return ATT_ERR_NO_ERROR;
}

#endif /* #if (PROFILE_SIG_HIDS) */

/* VENDOR OTA profile ------------------------------------------------------- */
#if (PROFILE_VENDOR_OTA)
#define _UUID128_IDX_CHAR_OTA_DATA  1
const uint8_t ex2_profile_uuids_set_vendor[][16] = {
    {0x11, 0x19, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00},
    {0x12, 0x2B, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00},
};

uint8_t vendor_ota_data_value[20];
static uint16_t _vendor_ota_cccd_value;
#endif  /* (PROFILE_VENDOR_OTA) */

const exe_att_ent_t ex2_tbl_gatt_database[] = {
    /* The total number of ATT handlers. */
    EX2_ATT_DEFINE(0, 0, 0, 0, ATT_HANDLE_END-1, 0),

    /* Generic Access PS: DevName CD,CV; Appearance CD,CV; PPCP CD,CV. */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_SERVICE_PRIMARY,                EX2_ATT_VALUE_TYPE_DATA, 2,                          BLE_UUID_GAP,               EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                 EX2_ATT_VALUE_TYPE_DATA, 1,                          BLE_CHAR_PROP_READ,         EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_GAP_CHARACTERISTIC_DEVICE_NAME, EX2_ATT_VALUE_TYPE_PTR,  MOUSE_NAME_MAX_LEN,         bt_kb_name,                 EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                 EX2_ATT_VALUE_TYPE_DATA, 1,                          BLE_CHAR_PROP_READ,         EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_GAP_CHARACTERISTIC_APPEARANCE,  EX2_ATT_VALUE_TYPE_DATA, 2,                          BLE_APPEARANCE_HID_KEYBOARD, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                 EX2_ATT_VALUE_TYPE_DATA, 1,                          BLE_CHAR_PROP_READ,         EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_GAP_CHARACTERISTIC_PPCP,        EX2_ATT_VALUE_TYPE_PTR,  sizeof(ex2_gap_ppcp_value), &ex2_gap_ppcp_value,        EX2_ATT_PER_READ),

    #if (PROFILE_SIG_GATT)
    /* Generic Attribute PS: SCC CD,CV,CCCD. */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_SERVICE_PRIMARY,                     EX2_ATT_VALUE_TYPE_DATA, 2, BLE_UUID_GATT,                       EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                      EX2_ATT_VALUE_TYPE_DATA, 1, BLE_CHAR_PROP_INDICATE,              EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED, EX2_ATT_VALUE_TYPE_PTR,  4, &_gatt_service_changed_value[0],     EX2_ATT_PER_READ | EX2_ATT_PER_WRITE),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG,       EX2_ATT_VALUE_TYPE_PTR,  2, &_gatt_service_changed_cccd_value,   EX2_ATT_PER_READ | EX2_ATT_PER_WRITE),
    #endif

    #if (PROFILE_SIG_DIS)
    /* Device Information PS: PnP CD,CV. */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_SERVICE_PRIMARY,  EX2_ATT_VALUE_TYPE_DATA, 2,                     BLE_UUID_DEVICE_INFORMATION_SERVICE, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,   EX2_ATT_VALUE_TYPE_DATA, 1,                     BLE_CHAR_PROP_READ,                  EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_PNP_ID_CHAR,      EX2_ATT_VALUE_TYPE_PTR, sizeof(ble_dis_pnp_t),  &_dis_pnp_value,                     EX2_ATT_PER_READ),
    #endif

    #if (PROFILE_SIG_BAS)
    /* Battery PS: BatteryLevel's CD,CV,CCCD. */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_SERVICE_PRIMARY,               EX2_ATT_VALUE_TYPE_DATA, 2, BLE_UUID_BATTERY_SERVICE,                  EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1, BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_BATTERY_LEVEL_CHAR,            EX2_ATT_VALUE_TYPE_PTR,  1, &_bas_bat_lvl_value,                       EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2, &_bas_cccd_value,                          EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    #endif

    #if (PROFILE_SIG_HIDS)
    /* Human Interface Device PS: ProtocolMode CD,CV; */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_SERVICE_PRIMARY,    EX2_ATT_VALUE_TYPE_DATA, 2, BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE,              EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,     EX2_ATT_VALUE_TYPE_DATA, 1, BLE_CHAR_PROP_READ | BLE_CHAR_PROP_WRITE_WITHOUT_RSP, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_PROTOCOL_MODE_CHAR, EX2_ATT_VALUE_TYPE_PTR,  1, &_hid_protocol_mode_value,                            EX2_ATT_PER_READ | EX2_ATT_PER_WRITE),

    #if (PROFILE_HID_MOUSE)
    #if (EXE_HOGP_PTS == 1)
    /* boot Mouse input report CD,CV,CCCD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                  BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR,  EX2_ATT_VALUE_TYPE_PTR,  sizeof(hid_mouse_report_value),     &hid_mouse_report_value[0],                                               EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                                  &_hid_cccd_value,                                                         EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    #endif

    /* Mouse's CD,CV,CCCD,RRD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                               BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_CHAR,                   EX2_ATT_VALUE_TYPE_PTR,  sizeof(hid_mouse_report_value),  &hid_mouse_report_value[0],                                               EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                               &_hid_cccd_value,                                                         EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_REF_DESCR,              EX2_ATT_VALUE_TYPE_DATA, sizeof(ble_hid_report_ref_t),    BLE_HID_REPORT_REF(HID_REPORT_ID_MOUSE_INPUT, BLE_HID_REPORT_TYPE_INPUT), EX2_ATT_PER_READ),
    #endif

    #if (PROFILE_HID_CONSUMER_CONTROL)
    /* Consum's CD,CV,CCCD,RRD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                          BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                           EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_CHAR,                   EX2_ATT_VALUE_TYPE_PTR,  sizeof(hid_consumer_control_report_value),  &hid_consumer_control_report_value[0],                                               EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                                          &_hid_cccd_value,                                                                    EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_REF_DESCR,              EX2_ATT_VALUE_TYPE_DATA, sizeof(ble_hid_report_ref_t),               BLE_HID_REPORT_REF(HID_REPORT_ID_CONSUMER_CONTROL_INPUT, BLE_HID_REPORT_TYPE_INPUT), EX2_ATT_PER_READ),
    #endif

    #if (PROFILE_HID_KEYBOARD)
    #if (EXE_HOGP_PTS == 1)
    /* boot keyboard input report CD,CV,CCCD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                        BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                   EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B,BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR,EX2_ATT_VALUE_TYPE_PTR,  sizeof(hid_keyboard_in_report_value),     &hid_keyboard_in_report_value[0],                                            EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                                        &_hid_cccd_value,                                                            EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),

    /* boot keyboard output report CD,CV*/
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                 EX2_ATT_VALUE_TYPE_DATA, 1,                                       BLE_CHAR_PROP_READ | BLE_CHAR_PROP_WRITE | BLE_CHAR_PROP_WRITE_WITHOUT_RSP,  EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B,BLE_UUID_BOOT_KEYBOARD_OUTPUT_REPORT_CHAR,EX2_ATT_VALUE_TYPE_PTR, 1,                                  &hid_keyboard_out_report_value,                                              EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    #endif

    /* keyboard's CD,CV,CCCD,RRD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                        BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                   EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_CHAR,                   EX2_ATT_VALUE_TYPE_PTR,  sizeof(hid_keyboard_in_report_value),     &hid_keyboard_in_report_value[0],                                            EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                                        &_hid_cccd_value,                                                            EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_REF_DESCR,              EX2_ATT_VALUE_TYPE_DATA, sizeof(ble_hid_report_ref_t),             BLE_HID_REPORT_REF(HID_REPORT_ID_KEYBOARD_INPUT, BLE_HID_REPORT_TYPE_INPUT), EX2_ATT_PER_READ),

    /* keyboard's CD,CV,CCCD,RRD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                  BLE_CHAR_PROP_READ | BLE_CHAR_PROP_WRITE | BLE_CHAR_PROP_WRITE_WITHOUT_RSP,    EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_CHAR,                   EX2_ATT_VALUE_TYPE_PTR,  1,                                  &hid_keyboard_out_report_value,                                                        EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_REF_DESCR,              EX2_ATT_VALUE_TYPE_DATA, sizeof(ble_hid_report_ref_t),       BLE_HID_REPORT_REF(HID_REPORT_ID_KEYBOARD_INPUT, BLE_HID_REPORT_TYPE_OUTPUT),  EX2_ATT_PER_READ),
#endif

    #if (PROFILE_HID_BITMAP_KEYBOARD)
    /* bitmap keyboard's CD,CV,CCCD,RRD */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                                  BLE_CHAR_PROP_READ | BLE_CHAR_PROP_NOTIFY,                                   EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_CHAR,                   EX2_ATT_VALUE_TYPE_PTR,  sizeof(bitmap_keyboard_report_value),  &bitmap_keyboard_report_value[0],                                               EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                                  &_hid_cccd_value,                                                            EX2_ATT_PER_READ | EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_REF_DESCR,              EX2_ATT_VALUE_TYPE_DATA, sizeof(ble_hid_report_ref_t),       BLE_HID_REPORT_REF(HID_REPORT_ID_BITMAP_KB_INPUT, BLE_HID_REPORT_TYPE_INPUT), EX2_ATT_PER_READ),
    #endif

    /* ReportMap's CD,CV */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,   EX2_ATT_VALUE_TYPE_DATA, 1,                             BLE_CHAR_PROP_READ,        EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_REPORT_MAP_CHAR,  EX2_ATT_VALUE_TYPE_PTR,  sizeof(_hid_report_map_value), &_hid_report_map_value[0], EX2_ATT_PER_READ | EX2_ATT_PER_ENCRYPT),

    /* HID Information's CD,CV */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,        EX2_ATT_VALUE_TYPE_DATA, 1,                        BLE_CHAR_PROP_READ,  EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_HID_INFORMATION_CHAR,  EX2_ATT_VALUE_TYPE_PTR,  sizeof(ble_hid_info_t),   &_hid_info_value,    EX2_ATT_PER_READ | EX2_ATT_PER_ENCRYPT),
    /* HID ControlPoint's CD,CV */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_CHARACTERISTIC,         EX2_ATT_VALUE_TYPE_DATA, 1,  BLE_CHAR_PROP_WRITE_WITHOUT_RSP, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B, BLE_UUID_HID_CONTROL_POINT_CHAR, EX2_ATT_VALUE_TYPE_FUNC, 1,  hid_control_point_write,         EX2_ATT_PER_WRITE | EX2_ATT_PER_ENCRYPT),
    #endif /* PROFILE_SIG_HIDS */

    #if (PROFILE_VENDOR_OTA)
    /* Vendor OTA PS: RW's CD,CV,CCCD. */
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B,  BLE_UUID_SERVICE_PRIMARY,               EX2_ATT_VALUE_TYPE_PTR,  16,                            &ex2_profile_uuids_set_vendor[0],                                            EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B,  BLE_UUID_CHARACTERISTIC,                EX2_ATT_VALUE_TYPE_DATA, 1,                             BLE_CHAR_PROP_READ | BLE_CHAR_PROP_WRITE_WITHOUT_RSP | BLE_CHAR_PROP_NOTIFY, EX2_ATT_PER_READ),
    EX2_ATT_DEFINE(EX2_UUID_LEN_16B, _UUID128_IDX_CHAR_OTA_DATA,             EX2_ATT_VALUE_TYPE_PTR,  sizeof(vendor_ota_data_value), &vendor_ota_data_value[0],                                                   EX2_ATT_PER_READ | EX2_ATT_PER_WRITE),
    EX2_ATT_DEFINE(EX2_UUID_LEN_2B,  BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG, EX2_ATT_VALUE_TYPE_PTR,  2,                             &_vendor_ota_cccd_value,                                                     EX2_ATT_PER_READ),
    #endif
};

