/*******************************************************************************
* 文件名称: led_effect.h
*
* 功能说明: 灯效扩展
*   1. 输出管线: gamma 校正 + 亮度档位 + 主亮度淡入淡出 + 闲置自动调暗
*   2. 帧同步  : 以 RTC 为基准的固定帧率, USB / 2.4G / BLE 下灯效速度一致
*   3. 按键事件: 供 激光 / 打字涟漪 / 番茄专注 等响应式灯效使用
*   4. 新增灯效: 见 led.h 中 iMODE_LED_SOFT_ON ~ iMODE_LED_RIPPLE
*******************************************************************************/
#ifndef _LED_EFFECT_H_
#define _LED_EFFECT_H_

#include <stdint.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------;
// 配置开关 (改为 0 即可退回旧行为, 也可在 Keil 的 Define 中覆盖)
//
#ifndef LED_GAMMA_EN
#define LED_GAMMA_EN            1       // 输出 gamma 2.2 校正 (渐变更顺滑, 低亮度不发灰)
#endif
#ifndef LED_FRAME_SYNC_EN
#define LED_FRAME_SYNC_EN       1       // 固定帧率 (0 = 旧行为: 每调用一次 logo_process 走一帧)
#endif
#ifndef LED_FADE_EN
#define LED_FADE_EN             1       // 切换模式 / 开灯时 ~250ms 淡入
#endif
#ifndef LED_IDLE_DIM_SEC
#define LED_IDLE_DIM_SEC        120     // 无按键 N 秒后自动调暗, 0 = 关闭
#endif
#ifndef LED_IDLE_DIM_LEVEL
#define LED_IDLE_DIM_LEVEL      64      // 调暗后的主亮度 (0..256), 64 = 25%
#endif
#ifndef LED_KEYPOS_REVERSE
#define LED_KEYPOS_REVERSE      0       // 按键位置 -> 灯位置 左右镜像 (视灯条实际排布调整)
#endif

//-----------------------------------------------------------------------------;
// 时间参数
//
#define iLED_RTC_HZ             32768UL // RTC 计数频率, 与 mMS_TO_TICK() 一致
#define iLED_FRAME_TICK         256     // 一帧 = 256 tick ≈ 7.8ms (≈128fps, 与原 USB 下的调用频率一致)
#define iLED_FRAME_CATCHUP_MAX  3       // 调用间隔较长时, 单次最多补 3 帧
#define iLED_FADE_IN_STEP       8       // 淡入: 每帧 +8/256  -> 约 250ms
#define iLED_FADE_OUT_STEP      1       // 调暗: 每帧 -1/256  -> 约 1.5s

//-----------------------------------------------------------------------------;
// 外部接口
//
extern uint16_t                 led_master_fade;    // 当前主亮度 0..256
extern uint32_t                 led_now_rtc;

// 高精度帧缓冲: 每通道 0..iLED_HR_MAX (12bit 感知亮度), 由需要细腻渐变的灯效写入.
// bled_hr_frame = true 时输出管线改用该缓冲, 避免 0..64 只有 65 级造成的台阶/抖动.
#define iLED_HR_MAX             4096
extern uint16_t                 pwm_rgb_hr[][3];
extern volatile bool            bled_hr_frame;

// 输出管线: pwm_rgb_tbl(0..64) -> LEDC 数据(0..255), 由 drv_ledc_write() 调用 (RAM 代码)
extern void led_output_transform(const uint8_t *src, uint8_t *dst);

// 每次 logo_process 调用: 更新时间/闲置状态
extern void led_master_update(uint32_t now);
// 切换模式或重新开灯: 重置帧时钟并从 0 淡入
extern void led_master_restart(uint32_t now);
// 计算本次应推进的帧数
extern uint8_t led_frame_steps(uint32_t now);
// 每帧调用: 推进主亮度淡入淡出
extern void led_master_step(void);

// 按键按下钩子 (在 matrixkey_value() 中按键按下沿调用, RAM 代码, 仅写 RAM)
extern void led_key_press_hook(uint8_t key_index);

// 模式循环: Fn 切换 / 滚轮切换 统一使用, 顺序由 led_mode_cycle_tbl 决定
extern uint8_t led_mode_next(uint8_t mode);

// 新增灯效入口
extern void led_effect_init(uint8_t mode);
extern void led_effect_run(uint8_t mode);

#endif
