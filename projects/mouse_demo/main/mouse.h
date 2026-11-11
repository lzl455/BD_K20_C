#ifndef __MOUSE_H
#define __MOUSE_H

typedef enum {
    MS_SLEEP_LEVEL0  = 0U,    /*<<< latency enable, sensor scan every interval */
    MS_SLEEP_LEVEL1  = 1U,    /*<<< latency enable, sensor scan sync as latency */
    MS_SLEEP_LEVEL2  = 2U,    /*<<< disconnect, only pin can wakeup */
} ms_sleep_level_t;

/**************************广播态目前处理逻辑***********************************
1.上电，先发5秒钟快广播尝试回连，用以确保配对过换电池不用重新配对，未回连成功开始
   发送Swift广播3.5S， 后切到可发现广播广播3分钟。
2、配对完成后，PMU寄存器BLE模式里面写入值，之后正常进入深度休眠/master主动断开/
slave主动断开都快广播5s(interval 5ms), 慢广播60s不可发现广播。
*******************************************************************************/
typedef enum {
    MOUSE_LE_STATE_ADV        = 0,  /* 可发现广播，未配对状态使用 */
    MOUSE_LE_STATE_ADV_SWIFT  = 1,  /* 可发现Swift广播，未配对状态使用，鼠标弹窗 */
    MOUSE_LE_STATE_DISCONN_ADV= 2,  /* 不可发现广播，慢广播 */
    MOUSE_LE_STATE_DISCONN    = 3,  /* 不可发现广播，断开后快广播，快速回连 */
    MOUSE_LE_STATE_STOP       = 4,  /* 超时后停止广播 */
} mouse_adv_state_t;

/* tx queue中缓存的最大数据包数目 */
#define  MOUSE_DATA_IN_TXQ_MAX_NUM  (3)

/* 鼠标没有数据1分钟内，每个interval MCU起来正常扫描外设，射频每个latency时间点工作一次 */
/* 鼠标没有数据1分钟到10分钟，每个latency时间点射频工作一次，MCU扫描一次外设 */
#define  MOUSE_ENTER_SLEEP_TIME_MINUTE         (60)
#define  MOUSE_ENTER_SLEEP_LEVEL2_TIME_COUNT   (10)

/* 借用不用的中断向量表存储同步字（SVC_Handler之后）*/
#define CFG_FW_ID_ADDR                      0x10
#define CFG_START_SYNC_WORD_ADDR            0x30

#define MOUSE_NAME_MAX_LEN         29U
extern char bt_kb_name[MOUSE_NAME_MAX_LEN];

extern void ex2_app_mouse_init(void);
extern void app_ble_evt_dispatch(uint32_t events);
extern void ex2_app_mouse_broadcast_fsm(void);

#endif  /* __MOUSE_H */
