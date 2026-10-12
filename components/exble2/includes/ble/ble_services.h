/**     __  ___     _              ____
 *   ___\ \/ / |__ | | ___  __   _|___ \
 *  / _ \\  /| '_ \| |/ _ \ \ \ / / __) |
 * |  __//  \| |_) | |  __/  \ V / / __/
 *  \___/_/\_\_.__/|_|\___|   \_/ |_____|
 *
 * @file ex2_api.h
 * @brief exBLE v2 stack public APIs.
 * @author onmicro
 * @date 2021/12
 */

#ifndef __BLE_SERVICES_H
#define __BLE_SERVICES_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include "om_device.h"


/*******************************************************************************
 * TYPEDEFS & MACROS
 */
/**
  * @brief ble_cccd_t  BLE Clent Characteristic Configuration Descriptor type
  * @{
  */
typedef uint16_t ble_cccd_t;
/**
 * @}
 */

/* Device Infomation Service */
/**
  * @brief ble_dis_vid_source_t  Designates Vendor ID is which organization assigned
  * @{
  */
typedef enum {
    BLE_DIS_VID_SOURCE_SIG     = 0x01,    /**< Bluetooth-SIG assigned Device ID Vendor ID value from Assigned Number document */
    BLE_DIS_VID_SORUCE_USB     = 0x02,    /**< USB Implementer's Forum assigned Vendor ID value */
} ble_dis_vid_source_t;
/**
 * @}
 */

/**
  * @brief ble_dis_pnp_t PnP_ID characteristic is a set of values that Used for Device ID, which is unique for this device. 
  * @{
  */
typedef struct __PACKED {
    ble_dis_vid_source_t  vid_source;   /**< Vendor ID source */
    uint16_t              vid;          /**< Vendor ID */
    uint16_t              pid;          /**< Product ID, used distinguish different products */
    uint16_t              prod_ver;     /**< Product version */
} ble_dis_pnp_t;
/**
 * @}
 */

/* HID Service */
/**
  * @brief ble_hid_protocol_mode_t The Protocol Mode characteristic for HID services
  * @{
  */
typedef enum {
    BLE_HID_PROTOCOL_MODE_BOOL   = 0,    /**< Boot Protocol Mode */
    BLE_HID_PROTOCOL_MODE_REPORT = 1,    /**< Report Protocol Mode */
} ble_hid_protocol_mode_t;
/**
 * @}
 */

/**
  * @brief ble_hid_report_type_t  Report Type values
  * @{
  */
typedef enum {
    BLE_HID_REPORT_TYPE_INPUT        = 1,    /**< Input Report */
    BLE_HID_REPORT_TYPE_OUTPUT       = 2,    /**< Output Report */
    BLE_HID_REPORT_TYPE_FEATURE      = 3,    /**< Feature Report */
} ble_hid_report_type_t;
/**
 * @}
 */

/**
 *******************************************************************************
 * @brief  Report Reference attribute value
 *
 * @param  _report_id    [0x01-0xFF] 1Byte, shall be nonzero in a Report Reference
 *                       characteristic descriptor where there is more than one 
 *                       instance of the Report characteristic for any given Report Type
 *
 * @param  _report_type  Indicate the type of Report characteristic value and set
 *                       to the appropriate value, see @ble_hid_report_type_t
 *
 * @param  ret           return value, Report reference
 *******************************************************************************
 */
#define BLE_HID_REPORT_REF(_report_id, _report_type)   (((_report_id) & 0xFFU) + (((_report_type) & 0xFFU) << 8))

/**
  * @brief ble_hid_report_ref_t  HID report reference
  * @{
  */
typedef struct {
    uint8_t               report_id;
    ble_hid_report_type_t report_type; 
} ble_hid_report_ref_t;
/**
 * @}
 */

/**
  * @brief ble_hid_info_t  HID Information characteristic value
  * @{
  */
typedef struct {
    uint16_t bcdHID;                     /**< 16bit unsigned integer representing version number of base USB HID Spec. implemented by HID Device */
    uint8_t  bCountryCode;               /**< 8bit integer identifying country HID Device hardware is localized. Most Hardware is not localized(value 0) */
    uint8_t  RemoteWake : 1;             /**< boolean value indicating whether HID device is capable of sending a wake-signal to a HID Host */
    uint8_t  NormallyConnectable : 1;    /**< boolean value indicating whether HID Device will be advertising when bonding but not connected */
} ble_hid_info_t;
/**
 * @}
 */

/**
  * @brief ble_hid_state_t  HID Control Point characteristic value
  * @{
  */
typedef enum {
    BLE_HID_CTRL_POINT_ENTER_SUSPEND  = 0,  /**< Informs HID device is entering the Suspend State */
    BLE_HID_CTRL_POINT_EXIT_SUSPEND   = 1,  /**< Informs HID device is exiting the Suspend State */
} ble_hid_ctrl_point_t;
/**
 * @}
 */

#endif  /* __BLE_SERVICES_H */


/** @} */
