#ifndef __EX2_APP_MOUSE_H__
#define __EX2_APP_MOUSE_H__


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Profile built-in support. */
#define PROFILE_SIG_GATT               1 //macOS
#define PROFILE_SIG_DIS                1
#define PROFILE_SIG_BAS                1 //Redmi4X
#define PROFILE_SIG_HIDS               1
#define PROFILE_VENDOR_OTA             0
#define PROFILE_HID_MOUSE              1
#define PROFILE_HID_CONSUMER_CONTROL   1
#define PROFILE_HID_KEYBOARD           1
#define PROFILE_HID_BITMAP_KEYBOARD    1 /* È«ÎÞ³å¼üÅÌ */ 

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/
/**
 * @brief Abbr. in ATT database.
 * PS:  Primary Service, its value ={ServiceUUID}
 *  CD:  Char Declaration, its value ={Char Properties, Char Value Handle, Char UUID}
 *   CV:   Char Value
 *   CCCD: Client Char Config Descriptor, its value CCC=[notification | indication]
 *   RRD:  Report Reference Descriptor,   its value RR={Report ID, Report Type[in|out]}
 */
typedef enum {
    ATT_HANDLE_BEGIN = 0,

    /* Generic Access. */
    ATT_HANDLE_GAP_PS,              //1800
    ATT_HANDLE_GAP_DEVNAME_CD,      //2A00: Read
    ATT_HANDLE_GAP_DEVNAME_CV,      //utf8s
    ATT_HANDLE_GAP_APPEARANCE_CD,   //2A01: Read
    ATT_HANDLE_GAP_APPEARANCE_CV,
    ATT_HANDLE_GAP_PPCP_CD,         //2A04: Read
    ATT_HANDLE_GAP_PPCP_CV,

    #if (PROFILE_SIG_GATT)
    /* Generic Attribute. */
    ATT_HANDLE_GATT_PS,            // 1801
    ATT_HANDLE_GATT_SCC_CD,        //2A05: Indicate
    ATT_HANDLE_GATT_SCC_CV,
    ATT_HANDLE_GATT_SCC_CCCD,      //2902: CCC
    #endif

    #if (PROFILE_SIG_DIS)
    /* Device Information. */
    ATT_HANDLE_DIS_PS,            //180A
    ATT_HANDLE_DIS_PNP_CD,        //2A50: Read
    ATT_HANDLE_DIS_PNP_CV,
    #endif

    #if (PROFILE_SIG_BAS)
    /* Battery. */
    ATT_HANDLE_BAS_PS,            //1812
    ATT_HANDLE_BAS_BAT_LVL_CD,    //2A19: Read | Notify
    ATT_HANDLE_BAS_BAT_LVL_CV,
    ATT_HANDLE_BAS_BAT_LVL_CCCD,  //2902: CCC
    #endif

    #if (PROFILE_SIG_HIDS)
    /* Human Interface Device. */
    ATT_HANDLE_HID_PS,                  //1812
    ATT_HANDLE_HID_PROTOCOL_MODE_CD,    //2A4E: Read | Write_noRSP
    ATT_HANDLE_HID_PROTOCOL_MODE_CV,

    #if (PROFILE_HID_MOUSE)
    #if (EXE_HOGP_PTS == 1)
    ATT_HANDLE_HID_BOOT_MOUSE_IN_REPORT_CD,     //2A33: Read | Notify
    ATT_HANDLE_HID_BOOT_MOUSE_IN_REPORT_CV,
    ATT_HANDLE_HID_BOOT_MOUSE_IN_REPORT_CCD,    //2902: CCC
    #endif

    ATT_HANDLE_HID_MOUSE_REPORT_CD,         //2A4D: Read | Notify
    ATT_HANDLE_HID_MOUSE_REPORT_CV,
    ATT_HANDLE_HID_MOUSE_REPORT_CCD,        //2902: CCC
    ATT_HANDLE_HID_MOUSE_REPORT_RRD,        //2908: ReportID + ReportType=in
    #endif

    #if (PROFILE_HID_CONSUMER_CONTROL)
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CD,     //2A4D: Read | Notify
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CV,
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CCD,    //2902: CCC
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_RRD,    //2908: ReportID + ReportType=in
    #endif

    #if (PROFILE_HID_KEYBOARD)
    #if (EXE_HOGP_PTS == 1)
    ATT_HANDLE_HID_BOOT_KB_IN_REPORT_CD,     //2A22: Read | Notify
    ATT_HANDLE_HID_BOOT_KB_IN_REPORT_CV,
    ATT_HANDLE_HID_BOOT_KB_IN_REPORT_CCD,    //2902: CCC
    ATT_HANDLE_HID_BOOT_KB_OUT_REPORT_CD,    //2A32: Read | Notify
    ATT_HANDLE_HID_BOOT_KB_OUT_REPORT_CV,
    #endif

    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CD,     //2A4D: Read | Notify
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CV,
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CCD,    //2902: CCC
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_RRD,    //2908: ReportID + ReportType=in

    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_CD,     //2A4D: Read | Write | Write_noRSP
    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_CV,
    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_RRD,    //2908: ReportID + ReportType=out
    #endif

    #if (PROFILE_HID_BITMAP_KEYBOARD)
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CD,     //2A4D: Read | Notify
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CV,
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CCD,    //2902: CCC
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_RRD,    //2908: ReportID + ReportType=in
    #endif

    ATT_HANDLE_HID_REPORT_MAP_CD,         //2A4B: Read
    ATT_HANDLE_HID_REPORT_MAP_CV,         //USB HID Usage Tables

    ATT_HANDLE_HID_INFORMATION_CD,        //2A4A: Read
    ATT_HANDLE_HID_INFORMATION_CV,        //USB HID version,country,flags

    ATT_HANDLE_HID_CONTROL_POINT_CD,      //2A4C: Write_noRSP
    ATT_HANDLE_HID_CONTROL_POINT_CV,
    #endif /* PROFILE_SIG_HIDS */

    #if (PROFILE_VENDOR_OTA)
    /* Vendor OTA Service. */
    ATT_HANDLE_VENDOR_OTA_PS, //UUID128
    ATT_HANDLE_OTA_RW_CD,     //Vendor: Read | Write_noRSP | Notify
    ATT_HANDLE_OTA_RW_CV,
    ATT_HANDLE_OTA_RW_CCCD,   //2902: CCC
    #endif

    ATT_HANDLE_END,
} att_handles_set_t;

/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Init EX2 stack and profile for mouse project
 *
 * @param is_paird  The ble device is paired
 *
 * @return          None
 *******************************************************************************
 */
extern void ex2_app_mouse_ble_init(void);

/**
 *******************************************************************************
 * @brief Enable HID notification, and disable latency when notification
 *
 * @param hid_cccd   hid cccd value
 * 
 * @return           None
 *******************************************************************************
 */
extern void hid_notification_enable(uint16_t hid_cccd);

/**
 *******************************************************************************
 * @brief check HID notification settings
 *
 * @return HID CCC value
 *******************************************************************************
 */
extern uint16_t hid_notification_is_enabled(void);

/**
 *******************************************************************************
 * @brief scan button/sensor/wheel
 *
 * @return return 1 if have data to report
 *******************************************************************************
 */
extern uint8_t ex2_app_mouse_scan(void);

#ifdef __cplusplus
}
#endif

#endif  /* __EX2_APP_MOUSE_H__ */

/** @} */
