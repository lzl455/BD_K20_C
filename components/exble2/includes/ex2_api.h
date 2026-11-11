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

#ifndef __EX2_API_H__
#define __EX2_API_H__

#include <stdint.h>
#include <stdbool.h>
#include "core_ble.h"
#include "ble/ble_services.h"
#include "om_device.h"


/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/
/**< Maximum ATT MTU. */
#define EXE_ATT_MTU_SIZE                23
/**< Maximum length of data (in bytes) that can be transmitted over ATT read/write/notification in exBLE. */
#define EXE_ATT_PAYLOAD_LEN_MAX         (EXE_ATT_MTU_SIZE - 3)

/**< BLE tick is based on OM62xx's sleep timer. */
#if defined(CONFIG_OM6229) || defined(CONFIG_OM6236) || defined(CONFIG_OM6239)
#define BLE_TICK_HZ                     32000
#define BLE_TICK_MAX                    0xFFFFFFFFU
/**
 * @brief The translation from time to BLE tick at fine frequency.
 * @param [in] us,ms,sec - The time in us,ms,sec.
 * @return the BLE tick.
 */
//#define EX2_US_TO_TICK(us)              ((BLE_TICK_HZ / 1000 * (us) / 1000) + 0)
#define EX2_US_TO_TICK(us)              ((us)>>5)
#define EX2_MS_TO_TICK(ms)              ((ms)<<5)
#define EX2_1D25MS_TO_TICK(v)           ((v) * 40)
#define EX2_TICK_TO_US(tick)            ((tick) * 3125 / 100)
#define EX2_TICK_TO_MS(tick)            ((tick) * 3125 / 1000 / 100)
#define EX2_TICK_TO_1D25MS(tick)        ((tick) * 3125 / 1250 / 100)
#define EX2_TICK_TO_SUP_TIMEOUT(tick)   ((tick) * 3125 / 100 / 1000/*us to ms*/ / 10/*spec timeout*10 */)
#else
#error "BLE TICK not defined in selectd platform"
#endif

/**
 * Checks whether the given time is older than the reference (occurs before in time).
 *
 * @verbatim
 -----------|---------------------|-----------> t
            t1                    t2
            time                  reference

 TIME_OLDER_THAN(t1, t2) => true
 TIME_OLDER_THAN(t2, t1) => false
 @endverbatim
 */
#define EX2_TIME_OLDER_THAN(time, ref) (bool)(((uint32_t) (time)) - ((uint32_t) (ref)) > (BLE_TICK_MAX >> 1))

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/
/* 协议栈分广播态和连接态。*/
typedef enum {
    EXE_LINK_STATE_STANDBY = 0U,
    EXE_LINK_STATE_ADV     = 1U,
    EXE_LINK_STATE_CONN    = 2U,
    EXE_LINK_STATE_SCAN    = 3U,
    EXE_LINK_STATE_INIT    = 4U,
    #if (CONFIG_EX2_DTM_TEST)
    EXE_LINK_STATE_DTM     = 5U,
    #endif
} exe_stk_state_t;

/* 协议栈用户层事件。*/
#define EX2_EVENT_APP_SCAN_REQ                     (1U << 0)    /**< Generated after received SCAN_REQ 接收到扫描请求 */
#define EX2_EVENT_APP_CONNECT_IND                  (1U << 1)    /**< Generated after received CONNECTION_IND 接收到连接请求 */
#define EX2_EVENT_APP_CONN_TIMEOUT                 (1U << 2)    /**< Connection Timeout event 连接超时事件*/
#define EX2_EVENT_APP_CONNECT_UPD                  (1U << 3)    /**< Connnection Update: received LL_CONNECTION_UPDATE_IND 连接参数更新*/
#define EX2_EVENT_APP_RECONNECT                    (1U << 4)    /**< Reconnect event: Slave prepare transmit LL_START_ENC_REQ when no pairing process occured */
#define EX2_EVENT_APP_ADV_EVENT_DONE               (1U << 5)    /**< End of an Advertising 广播结束*/
#define EX2_EVENT_APP_MASTER_TERMINATED            (1U << 6)    /**< master proactive terminated connection event 主机主动终止的连接事件*/
#define EX2_EVENT_APP_PAIR_COMPLETED               (1U << 7)    /**< Pair completed: Generated after SMP key distribution 配对完成：在SMP密钥分发后生成*/
#define EX2_EVENT_APP_ADV_TIMEOUT                  (1U << 8)    /**< ADV Timeout event: Generated when ADV timeout ADV超时事件：在ADV超时时生成*/
#define EX2_EVENT_APP_SLAVE_TERMINATED             (1U << 9)    /**< slave proactive terminated connection event */
#define EX2_EVENT_APP_USER_DATA_VALID              (1U << 10)   /**< User Data commit to tx queue */
#define EX2_EVENT_APP_GATT_DISCOVERY_COMPLETED     (1U << 11)   /**< GATT Discovery completed: generated at PrimaryService/Relationship Discovery procedure timeout */
#define EX2_EVENT_APP_VERSION_EXCHANGE             (1U << 12)   /**< Receive a version exchange packet */
#define EX2_EVENT_APP_PAIR_TIMEOUT                 (1U << 13)   /**< SMP pair flow timeout */
#define EX2_EVENT_APP_CONN_SLAVE                   (1U << 31)   /**< CONN as SLAVE enent: Generated as a connection event */

/* 协议栈用户层事件回调函数类型。*/
typedef void (*ex2_evt_app_handler_t)(uint32_t events);

/**
 *******************************************************************************
 * @brief      Read/write ATT handler function
 * @note       Convert value field in ex2_att_ent_t as callback ex2_att_app_handler_t.
 *
 * @param      offset   Read/Write from offset in value field in ex2_att_ent_t
 * @param      payload  Pointer to read/write
 * @param      len      The number read/write in bytes. len shall litter than value_len minus offset
 *
 * @return              Application error code defined by a higher layer specification,
 *                      shall rang in [0x80, 0xFF]
 *******************************************************************************
 */
typedef att_error_code_t (*ex2_att_app_handler_t)(uint16_t offset, uint8_t *payload, uint16_t len);

/**
 * @defgroup ex2_uuid_len_t UUID length
 * @{
 */
typedef enum {
    EX2_UUID_LEN_2B      = 0,
    EX2_UUID_LEN_16B     = 1,
} ex2_uuid_len_t;
/**
 * @}
 */

/**
 * @defgroup ex2_att_value_type_t ATT value type
 * @{
 */
typedef enum {
    EX2_ATT_VALUE_TYPE_DATA = 0,
    EX2_ATT_VALUE_TYPE_PTR  = 1,
    EX2_ATT_VALUE_TYPE_FUNC = 2,
} ex2_att_value_type_t;
/**
 * @}
 */

/* ex2_att_perimission define */
#define EX2_ATT_PER_READ         (1U << 0)
#define EX2_ATT_PER_WRITE        (1U << 1)
#define EX2_ATT_PER_AUTHEN       (1U << 2)
#define EX2_ATT_PER_ENCRYPT      (1U << 3)

/* ATT属性表项。*/
typedef struct {
    uint8_t   rsvd        : 1; /// rsvd
    uint8_t   uuid_len    : 1; /// The length of Attribute UUID: 2 is UUID16, 16 is UUID128. see @ex2_uuid_len_t
    uint8_t   permission  : 4; /// access/authentication/secure permission, bit0: readable; bit1:writeable; bit2:authentication; bit3:secure
    uint8_t   value_type  : 2; /// value type, see @ex2_att_value_type_t
    uint8_t   value_len;       /// The length of Attribute Value.
    uint16_t  uuid_idx;        /// The index to UUID16 or UUID128: PS, CD, SCCD, CCCD;
    uint32_t  value;           /// The pointer to Attribute Value: ServiceUUID for PS; {CharProp, CharValueHandle, CharUUID} for CD; SCC's Value; CCC value; DevName; Appearance; PPCP; PnP IDs; Bat level; HID Report Map; HID Report Value etc
} exe_att_ent_t;
/**
 * @}
 */

#define EX2_ATT_DEFINE(_uuid_len, _uuid_idx, _value_type, _value_len, _value, _permission)  \
    {                                                                                       \
        .rsvd       = 0,                                                                    \
        .uuid_len   = (_uuid_len),                                                          \
        .uuid_idx   = (_uuid_idx),                                                          \
        .value_type = (_value_type),                                                        \
        .value_len  = (_value_len),                                                         \
        .value      = (uint32_t)(_value),                                                   \
        .permission = (_permission),                                                        \
    }

/**
 * @defgroup ex2_gap_ppcp_t Peripheral Preferred Connection Parameters Characteristic
 * @{
 */
typedef struct {
    uint16_t interval_min;  /*<<< Defines minimum value for the connection interval in 1.25ms */
    uint16_t interval_max;  /*<<< Defines maximum value for the connection interval in 1.25ms */
    uint16_t latency;       /*<<< Defines the slave latency parameter */
    uint16_t timeout;       /*<<< Defines connection timeout parameter in 10ms */
} ex2_gap_ppcp_t;
/**
 * @}
 */


typedef struct ex2_data {
    uint8_t *data;       ///< 数据指针
    uint8_t len;         ///< 数据长度
} ex2_data_t;

/*===========================================================================*/
/* Global variables.                                                         */
/*===========================================================================*/
/* 协议栈内部状态：0-广播态  1-连接态  @ref exe_stk_state_t. */
extern exe_stk_state_t exe_stk_state;

/* profile database, defined by user */
extern const exe_att_ent_t ex2_tbl_gatt_database[] __WEAK;
/* profile 128bit uuid sets table, defined by user */
extern const uint8_t ex2_profile_uuids_set_vendor[][16] __WEAK;


/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/
/**
 * @brief 初始化exBLE v2协议栈。
 */
void ex2_stk_init(const uint8_t *bd_addr);

/**
 * @brief register ex2 event app handler
 */
void ex2_stk_register_app_evt_handler(ex2_evt_app_handler_t evt_app_hander);

/**
 * @brief 初始化exBLE v2协议栈。
 */
void ex2_stk_uninit(void);

/**
 * @brief 从发送队列取出一个USB数据，向USB主机发送。
 */
uint8_t *ex2_stk_txq_dequeue(void);

/**
 * @brief exBLE v2协议栈唤醒。
 * @note  仅用于nonOS模型，从Standby+低功耗模式掉电式唤醒后调用。
 */
void ex2_stk_wakeup(void);

/**
 * @brief exBLE v2协议栈调度。
 * @note  仅用于nonOS模型，从WFI醒来后调用。
 */
void ex2_stk_process(void);

/**
 * @brief 用户中断导致提前唤醒，协议栈的连接态需要预处理。
 * @note 用户的中断处理程序里，如果有数据提交给协议栈，则最后要调用本API。
 * @return true如果BLE将提前收发, 否则false.
 */
bool ex2_stk_interrupt(void);

/**
 * @brief Get ex2 sleep duration
 *
 * @return Sleep duration in 32K ticks.
 */
uint32_t ex2_stk_sleep_duration_get(void);

/**
 * @brief Get ex2 tx queue number
 *
 * @return the number of tx queue.
 */

uint8_t ex2_stk_get_txq_num(void);
uint8_t ex2_stk_get_rxq_num(void);

/**
 * @brief 获得当前的连接事件计数。
 * @note 断开连接时获得的连接事件计数，用户层可用于改善手机兼容性。
 * @return Connection Event Counter.
 */
uint16_t ex2_ll_get_conn_event_counter(void);

/**
 * @brief 获得当前的连接间隔，以RTC 32kHz时钟为单位。
 * @return Connection Interval in tick.
 */
uint32_t ex2_ll_get_conn_interval_tick(void);

/**
 * @brief 设备侧主动发起连接参数更新。
 * @note 仅仅在连接态下调用才起作用。
 *
 * @param [in] interval_min - Defines minimum value for the connection interval in 1.25ms.
 *        [in] interval_max - Defines maximum value for the connection interval in 1.25ms.
 *        [in] latency      - Defines the slave latency parameter.
 *        [in] timeout      - Defines connection timeout parameter in 10ms.
 * @return true for success, false for no space in tx queue.
 */
bool ex2_l2cap_update_conn_para(const ex2_gap_ppcp_t *ppcp);

/**
 * @brief 设备侧主动发起基于LE Credit的L2CAP连接。
 * @note 仅仅在连接态下调用才起作用。
 * @note 仅仅用于BQB PTS认证。
 *
 * @param [in] psm  - LE Protocol/Service Multiplexer: Object Transfer Service 0x0025.
 *        [in] scid - Source Channel ID: dynamically allocated in [0x0040-0xFFFF].
 * @return true for success, false for no space in tx queue.
 */
bool ex2_l2cap_create_le_conn(uint16_t psm, uint16_t scid);

/**
 * @brief 禁止latency，以提高连接可靠性和数据带宽。
 * @note API, called by ota_att_handler() etc.
 */
void ex2_gap_disable_latency(void);

/**
 * @brief 允许latency，以减少射频收发的次数，降低功耗。
 * @note 该API只是允许latency，射频收发次数是否真的减少还取决别的因素。
 */
void ex2_gap_enable_latency(void);

/**
 * @brief 进入广播模式，同时应用指定的广播参数。
 *
 * @param [in] adv_pkt         - 广播数据包内容，不包含FLags(3 Byte)
 * @param [in] adv_pkt_len     - 广播数据包长度，不包含Flags(3 Byte),最大长度为37-6-3 = 28 Byte
 * @param [in] adv_interval_ms - 广播事件间隔，单位ms
 *                               0表示保持原有广播事件间隔。
 * @param [in] adv_pkt_len     - 广播包长度，单位byte
 *                               0表示保持原有广播包长度。
 * @param [in] is_disc         - 是否可被发现，true可被发现，用于初始配对；
 *                                            false不可被发现，用于回连。
 * @return false 当前广播事件进行中，放弃应用新的广播参数
 *         true  成功进入指定的广播模式
 */
bool ex2_gap_set_broadcast_mode(const ex2_data_t *adv_pkt, const ex2_data_t *adv_rsp_pkt, uint8_t is_disc, int adv_interval_ms, uint32_t adv_timeout_ms);

/**
 * @brief Slave主动中止连接。
 * @note 断开连接原因错误码0x13: Remote User Terminated Connection
 */
void ex2_gap_disconnectd(void);

/**
 * @brief 使能SMP配对。
 * @note 拍照器和键鼠需要与手机配对后绑定。
 *       数传可以不用使能绑定功能。
 */
extern void ex2_smp_enable_bond(void);

/**
 * @brief 将ATT notify数据压入发送队列。
 * @note  len最多20字节。
 *
 * @param [in] handle - ATT Handle.
 * @param [in] p_data - ATT Value of notification.
 * @param [in] len    - The length of ATT value, maximum 20-byte.
 * @return 0 for failure, !0 for the actual length of ATT value.
 */
uint8_t ex2_att_tx_notification(uint16_t handle, uint8_t *p_data, int len);

/**
 * @brief 将ATT indicate数据压入发送队列。
 * @note  len最多20字节。
 *
 * @param [in] handle - ATT Handle.
 * @param [in] p_data - ATT Value of indication.
 * @param [in] len    - The length of ATT value, maximum 20-byte.
 * @return 0 for failure, !0 for the actual length of ATT value.
 */
uint8_t ex2_att_tx_indication(uint16_t handle, uint8_t *p_data, int len);

/**
 * @brief 收到ATT_Execute_Write_Request命令后,放弃或执行写操作。
 * @note
 *
 * @param [in] handle   - ATT Handle.
 * @param [in] write_en - excute wirte or not.
 *                        0x00 – Cancel all prepared writes
 *                        0x01 – Immediately write all pending prepared values
 *
 * @return None.
 */
void ex2_att_execute_write_callback(uint16_t handle, bool write_en);

/**
 * @brief 收到ATT_Handle_Value_Confirmation命令后,执行此回调函数。
 * @note
 *
 * @param [in] handle   - ATT Handle.
 *
 * @return None.
 */
void ex2_att_indication_confirm_callback(uint16_t handle);

/**
 * @brief ATT PrimaryService/Relationship/Characteristic Discovery Completed timeout, unit in RTC ticks
 * @note  This is weak symbol, default timeout is 1s
 *
 * @return None.
 */
uint32_t ex2_att_discovery_completed_timeout_get(void);

/**
 * @brief 启动下一次扫描外设的时间，在RTC Alarm0中断中调用。系统会在下个连接事件点之后产生中断。
 *
 * @param [in] sync_latency   - 0：latency使能后射频不起来，每个连接inteval会产生一次RTC Alarm0中断。
 *                            - 1：这个timer和射频同步。
 */
void ex2_ll_set_next_polling_time(bool sync_latency);

/**
 * @brief 启动扫描外设的timer，在每个连接inteval会产生一次RTC Alarm0中断，用于和射频同步扫描外设.
 * @return none.
 */
void ex2_ll_polling_time_start(void);

/**
 * @brief 停止扫描外设的timer。
 * @return none.
 */
void ex2_ll_polling_time_stop(void);

/****以下几个函数为虚函数，当协议栈中状态发生变化后会上报相关事件及参数，如需获取重新定义即可********/

/**
 * @brief 收到广播包，向应用层报告，例如connect indication包。
 *
 * @param [in] adv_pkt   - pointer to complete adviser packet.
 * @return return true.
 */
bool ex2_ll_hci_report_adv_packet(uint8_t *adv_pkt);

/**
 * @brief 参数更新完成。
 *
 * @param [in] buf   - new connect parameter , the data struct define as follows.
 *                  typedef struct ll_conn_param {        
 *                      uint32_t tick_winsize;  //接收ind后，参数更新时，接收窗口的大小。
 *                      uint32_t tick_winoff;   //接收ind后，参数更新时，第1包的接收窗口的偏移量。
 *                      uint32_t tick_interval; //连接间隔，单位tick.
 *                      uint32_t tick_timeout;  //连接超时参数，单位tick.
 *                      uint16_t latency;       //连接延迟参数，保持连接可跳过的包数。
 *                      uint16_t instance;      //连接事件计数，接收ind后初值为0；参数更新时，达到指定值后才正式更新参数。
 *                      uint8_t chn_map[5];     //可用频道索引列表：1=Used 0=Unused。
 *                  } ll_conn_param_t;
 * @return none.
 */
void ex2_ll_hci_connect_param_update_complete(uint8_t *buf);

/**
 * @brief 收到加密请求包。
 *
 * @param [in] param   - pointer to complete encrypt request packet.
 * @return return true.
 */
bool ex2_ll_hci_rx_enc_req_process(uint8_t *param);

/**
 * @brief 加密完成，加密链路建立。
 * @return none.
 */
bool ex2_ll_hci_ev_encrypt_chg(void);

/**
 * @brief 收到ATT_Execute_Write_Request命令后,放弃或执行写操作。
 * @note
 *
 * @param [in] handle   - ATT Handle.
 * @param [in] write_en - excute wirte or not.
 *                        0x00 – Cancel all prepared writes
 *                        0x01 – Immediately write all pending prepared values
 *
 * @return None.
 */
void ex2_att_execute_write_callback(uint16_t handle, bool write_en);

/**
 * @brief 收到ATT_Handle_Value_Confirmation命令后,执行此回调函数。
 * @note
 *
 * @param [in] handle   - ATT Handle.
 *
 * @return None.
 */
void ex2_att_indication_confirm_callback(uint16_t handle);

#endif  /* __EX2_API_H__ */
