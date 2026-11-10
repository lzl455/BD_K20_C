/*******************************************************************************
* 文件名称: led_effect.c
*
* 功能说明: 灯效扩展 —— 输出管线 / 帧同步 / 按键事件 / 新增灯效
*
*   数值约定: pwm_rgb_tbl 中每个通道为 0..iPWM_MAX(64) 的"感知亮度",
*             由 led_output_transform() 统一做 gamma + 档位 + 淡入淡出 后输出 0..255.
*             所有灯效内部的亮度系数 lev 均为 0..256 (256 = 100%).
*******************************************************************************/
#include <string.h>
#include "om_driver.h"

#include "main.h"
#include "led.h"
#include "led_effect.h"

//-----------------------------------------------------------------------------;
// 外部引用
//
extern bool                     bled_run_dir;           // logo_mode.c
extern unsigned char    const   led_single_table[];     // led_logo_tbl.h: 按键 -> 灯位置(0..6, 7=无)
extern unsigned char    const   rgb_en_tbl[];           // led_logo_tbl.h: 颜色序号 -> RGB 位掩码

//-----------------------------------------------------------------------------;
// 输出管线 —— 以下数据会在 RAM 代码 (USB SOF 中断) 中访问, 不能放 const(flash)
//
static uint16_t                 led_gamma_tbl[iPWM_MAX+1] = {  // round(256*(v/64)^2.2), 0..256
       0,   0,   0,   0,   1,   1,   1,   2,   3,   3,   4,   5,   6,   8,   9,  11,
      12,  14,  16,  18,  20,  22,  24,  27,  30,  32,  35,  38,  42,  45,  48,  52,
      56,  60,  64,  68,  72,  77,  81,  86,  91,  96, 101, 107, 112, 118, 124, 130,
     136, 142, 149, 155, 162, 169, 176, 183, 191, 198, 206, 214, 222, 230, 239, 247,
     256,
};
// 亮度档位 -> 系数(0..256), 与原 drv_ledc_write 的移位方案最大值一致: 32/64/128/255
static uint16_t                 led_level_scale[iLED_LEV_MAX+1] = {0, 32, 64, 128, 256};

// 高精度 gamma: round(65535*(v/64)^2.2), 输入 0..4096 时在相邻两项间线性插值
static uint16_t                 led_gamma_hr_tbl[iPWM_MAX+1] = {
         0,     7,    32,    78,   147,   240,   359,   504,
       676,   875,  1104,  1361,  1648,  1966,  2314,  2693,
      3104,  3547,  4022,  4530,  5072,  5646,  6255,  6897,
      7574,  8286,  9033,  9815, 10632, 11486, 12375, 13301,
     14263, 15262, 16298, 17371, 18482, 19630, 20816, 22040,
     23303, 24604, 25943, 27322, 28739, 30196, 31692, 33227,
     34802, 36417, 38072, 39768, 41503, 43280, 45097, 46954,
     48853, 50793, 52774, 54796, 56860, 58966, 61114, 63303,
     65535,
};

uint16_t                        led_master_fade = 256;
uint32_t                        led_now_rtc;

uint16_t                        pwm_rgb_hr[iLED_MAX][3];
volatile bool                   bled_hr_frame;

static uint16_t                 led_fade_target = 256;
static uint32_t                 led_frame_rtc;
static uint32_t                 led_idle_rtc;
static bool                     bled_idle_inited;
static bool                     fx_force_full;          // 提醒类灯效: 忽略闲置调暗

//-----------------------------------------------------------------------------;
// 按键事件队列 (单生产者 matrixkey_value / 单消费者 logo_process)
//
#define iLED_KEY_Q_LEN          8                       // 必须为 2 的幂
static volatile uint8_t         led_key_q[iLED_KEY_Q_LEN];
static volatile uint8_t         led_key_q_wr;
static volatile uint8_t         led_key_q_rd;
static volatile bool            bled_key_activity;

#define iLED_POS_NONE           0xFF

//-----------------------------------------------------------------------------;
// 模式循环顺序 (Fn 切换键 / 滚轮切换)
// 只影响"按键循环"的顺序与可选范围, 不影响模式编号 (上位机/Flash 兼容).
// 如需办公优先, 可改为:
//   iMODE_LED_SOFT_ON, iMODE_LED_SOFT_BREATH, iMODE_LED_CANDLE, iMODE_LED_POMODORO,
//   iMODE_LED_RIPPLE,  iMODE_LED_ON, iMODE_LED_BREATH, ...
// 爆闪 (iMODE_LED_BS) 已移出按键循环: 互补色高频交替闪烁, 不适合办公且对光敏人群不友好;
// 上位机仍可直接设置该模式. 若当前模式不在表中, 按键切换会回到表中第一项.
//
static const uint8_t            led_mode_cycle_tbl[] = {
    iMODE_LED_ON,       iMODE_LED_BREATH,   iMODE_LED_SNAKE,    iMODE_LED_NHJB,
    iMODE_LED_LG_L_R,   iMODE_LED_STAR,     iMODE_LED_SBZL,
    iMODE_LED_QCNH,     iMODE_LED_LHTW,     iMODE_LED_DXTW,     iMODE_LED_SXTW,
    iMODE_LED_TXTW,     iMODE_LED_FXTW,     iMODE_LED_JG,
    iMODE_LED_SOFT_ON,  iMODE_LED_SOFT_BREATH, iMODE_LED_RAINBOW, iMODE_LED_AURORA,
    iMODE_LED_METEOR,   iMODE_LED_CANDLE,   iMODE_LED_POMODORO, iMODE_LED_RIPPLE,
};

//-----------------------------------------------------------------------------;
// 配色: 与 led_rgb_index 一一对应 (0红 1绿 2蓝 3紫 4黄 5青 6白 7全彩)
// 新灯效使用更柔和的调色: 黄偏暖, 白为 ~3000K 暖白, 更适合办公
//
static const uint8_t            fx_palette[8][3] = {    // R, G, B (0..64)
    {64,  0,  0},
    { 0, 64,  0},
    { 0,  0, 64},
    {44,  0, 64},
    {64, 46,  0},
    { 0, 60, 64},
    {64, 46, 28},
    {64, 46, 28},
};
static const uint8_t            fx_pal_hue[8] = {  0,  85, 170, 200,  32, 128,  24,   0};
static const uint8_t            fx_pal_sat[8] = {255, 255, 255, 255, 255, 255, 120, 255};

static const uint8_t            fx_sin_tbl[256] = {     // round(127.5+127.5*sin(2πi/256))
    128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,
    176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,
    218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,
    245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,
    255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,
    245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,
    218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,
    176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,
    128,124,121,118,115,112,109,106,103,100, 97, 93, 90, 88, 85, 82,
     79, 76, 73, 70, 67, 65, 62, 59, 57, 54, 52, 49, 47, 44, 42, 40,
     37, 35, 33, 31, 29, 27, 25, 23, 21, 20, 18, 17, 15, 14, 12, 11,
     10,  9,  7,  6,  5,  5,  4,  3,  2,  2,  1,  1,  1,  0,  0,  0,
      0,  0,  0,  0,  1,  1,  1,  2,  2,  3,  4,  5,  5,  6,  7,  9,
     10, 11, 12, 14, 15, 17, 18, 20, 21, 23, 25, 27, 29, 31, 33, 35,
     37, 40, 42, 44, 47, 49, 52, 54, 57, 59, 62, 65, 67, 70, 73, 76,
     79, 82, 85, 88, 90, 93, 97,100,103,106,109,112,115,118,121,124,
};

//-----------------------------------------------------------------------------;
// 灯效运行状态 (切换模式时清零)
//
typedef struct {
    int16_t                     pos;                    // 中心位置 (8.8, 单位: 灯)
    uint16_t                    rad;                    // 半径 (8.8)
    uint16_t                    life;                   // 剩余亮度 0..256
    uint8_t                     hue;
} fx_ripple_t;

#define iFX_RIPPLE_NUM          4

static uint32_t                 fx_cnt;
static uint32_t                 fx_rtc0;
static uint16_t                 fx_ph1, fx_ph2, fx_ph3; // 8.8 相位
static int16_t                  fx_pos;
static uint8_t                  fx_state;
static uint8_t                  fx_hue[iLED_MAX];
static uint16_t                 fx_lv[iLED_MAX];
static uint16_t                 fx_tg[iLED_MAX];
static fx_ripple_t              fx_rp[iFX_RIPPLE_NUM];
static uint16_t                 fx_rand_state = 0xACE1;

//=============================================================================;
// 输出管线                                                                     ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_output_transform
* 功能描述: pwm_rgb_tbl(0..64) -> LEDC 数据(0..255)
* 说    明: 由 drv_ledc_write() 在临界区内调用, 只访问 RAM.
*           LED_GAMMA_EN=0 且主亮度=256 时, 输出与原移位方案完全一致.
******************************************************************************/
__RAM_CODE void led_output_transform(const uint8_t *src, uint8_t *dst)
{
    uint8_t  i, v;
    uint32_t scale, o;

    i = (uint8_t)led_light_lev;
    if(i > iLED_LEV_MAX)
        i = iLED_LEV_MAX;
    scale = led_level_scale[i];
#if LED_FADE_EN
    scale = (scale * led_master_fade) >> 8;
#endif

    if(bled_hr_frame)
    {                                                   // 高精度路径 (12bit 输入)
        const uint16_t *hr = &pwm_rgb_hr[0][0];
        uint32_t x, idx, frac, g;

        for(i=0; i<iLED_MAX*3; i++)
        {
            x = hr[i];
            if(x > iLED_HR_MAX)
                x = iLED_HR_MAX;
#if LED_GAMMA_EN
            idx  = x >> 6;
            frac = x & 0x3F;
            g = led_gamma_hr_tbl[idx];
            if(idx < iPWM_MAX)
                g += ((led_gamma_hr_tbl[idx+1] - g) * frac) >> 6;
#else
            g = x << 4;                                 // 0..65536
#endif
            o = (g * scale + 32768) >> 16;
            if((0 == o) && (0 != x) && (0 != scale))
                o = 1;
            if(o > 0xFF)
                o = 0xFF;
            dst[i] = (uint8_t)o;
        }
        return;
    }

    for(i=0; i<iLED_MAX*3; i++)
    {
        v = src[i];
        if(v > iPWM_MAX)
            v = iPWM_MAX;
#if LED_GAMMA_EN
        o = led_gamma_tbl[v];
#else
        o = ((uint32_t)v << 2);                         // 0..256
#endif
        o = (o * scale) >> 8;
#if LED_GAMMA_EN
        if((0 == o) && (0 != v) && (0 != scale))
            o = 1;                                      // 低档位下保留暗部 (拖尾不至于直接消失)
#endif
        if(o > 0xFF)
            o = 0xFF;
        dst[i] = (uint8_t)o;
    }
}

/******************************************************************************
* 函数名称: led_master_update
* 功能描述: 每次 logo_process 调用一次: 记录时间, 处理闲置调暗
******************************************************************************/
void led_master_update(uint32_t now)
{
    led_now_rtc = now;

    if((false == bled_idle_inited) || bled_key_activity)
    {
        bled_idle_inited = true;
        bled_key_activity = false;
        led_idle_rtc = now;
    }

    led_fade_target = 256;
#if LED_IDLE_DIM_SEC
    if((false == fx_force_full)
        && ((now - led_idle_rtc) > ((uint32_t)LED_IDLE_DIM_SEC * iLED_RTC_HZ)))
    {
        led_fade_target = LED_IDLE_DIM_LEVEL;
    }
#endif
}

void led_master_restart(uint32_t now)
{
    led_frame_rtc = now;
    led_idle_rtc = now;                                 // 开灯/切换模式视为一次操作
#if LED_FADE_EN
    led_master_fade = 0;
#endif
}

/******************************************************************************
* 函数名称: led_frame_steps
* 功能描述: 根据 RTC 计算本次要推进的帧数, 使各连接模式下速度一致
******************************************************************************/
uint8_t led_frame_steps(uint32_t now)
{
#if LED_FRAME_SYNC_EN
    uint32_t diff = now - led_frame_rtc;
    uint8_t  n = 0;

    if(diff > ((uint32_t)iLED_FRAME_TICK * iLED_FRAME_CATCHUP_MAX * 4))
    {                                                   // 休眠唤醒 / 长时间未调用: 重新同步
        led_frame_rtc = now;
        return 1;
    }
    while((diff >= iLED_FRAME_TICK) && (n < iLED_FRAME_CATCHUP_MAX))
    {
        diff -= iLED_FRAME_TICK;
        led_frame_rtc += iLED_FRAME_TICK;
        n++;
    }
    if(diff >= iLED_FRAME_TICK)
        led_frame_rtc = now;                            // 仍然落后: 丢弃多余帧
    return n;
#else
    (void)now;
    return 1;
#endif
}

void led_master_step(void)
{
#if LED_FADE_EN
    if(led_master_fade < led_fade_target)
    {
        led_master_fade += iLED_FADE_IN_STEP;
        if(led_master_fade > led_fade_target)
            led_master_fade = led_fade_target;
    }
    else if(led_master_fade > led_fade_target)
    {
        if(led_master_fade >= (led_fade_target + iLED_FADE_OUT_STEP))
            led_master_fade -= iLED_FADE_OUT_STEP;
        else
            led_master_fade = led_fade_target;
    }
#endif
}

//=============================================================================;
// 按键事件                                                                     ;
//=============================================================================;

__RAM_CODE void led_key_press_hook(uint8_t key_index)
{
    uint8_t wr  = led_key_q_wr;
    uint8_t nxt = (uint8_t)((wr + 1) & (iLED_KEY_Q_LEN - 1));

    bled_key_activity = true;
    if(nxt != led_key_q_rd)
    {
        led_key_q[wr] = key_index;
        led_key_q_wr = nxt;
    }
}

static void fx_key_flush(void)
{
    led_key_q_rd = led_key_q_wr;
}

/* 取出一个按键事件, 转换为灯位置 0..iLED_MAX-1, 无对应位置返回 iLED_POS_NONE */
static bool fx_key_pop(uint8_t *led_pos)
{
    uint8_t rd = led_key_q_rd;
    uint8_t k, p;

    if(rd == led_key_q_wr)
        return false;
    k = led_key_q[rd];
    led_key_q_rd = (uint8_t)((rd + 1) & (iLED_KEY_Q_LEN - 1));

    p = (k < 128) ? led_single_table[k] : 7;
    if(p >= 7)
    {
        *led_pos = iLED_POS_NONE;
        return true;
    }
    // 表中位置为 0..6 (7 档), 映射到 0..iLED_MAX-1
    p = (uint8_t)((p * (iLED_MAX - 1) + 3) / 6);
#if LED_KEYPOS_REVERSE
    p = (uint8_t)(iLED_MAX - 1 - p);
#endif
    *led_pos = p;
    return true;
}

//=============================================================================;
// 模式循环                                                                     ;
//=============================================================================;

uint8_t led_mode_next(uint8_t mode)
{
    uint8_t i;
    const uint8_t n = (uint8_t)sizeof(led_mode_cycle_tbl);

    for(i=0; i<n; i++)
    {
        if(led_mode_cycle_tbl[i] == mode)
            return led_mode_cycle_tbl[(i + 1) % n];
    }
    return led_mode_cycle_tbl[0];
}

//=============================================================================;
// 绘制工具                                                                     ;
//=============================================================================;

static uint8_t fx_sin8(uint8_t x)
{
    return fx_sin_tbl[x];
}

static uint8_t fx_rand8(void)
{
    uint16_t s = fx_rand_state;                         // xorshift16 (7,9,8)
    s ^= (uint16_t)(s << 7);
    s ^= (uint16_t)(s >> 9);
    s ^= (uint16_t)(s << 8);
    fx_rand_state = s;
    return (uint8_t)(s ^ (s >> 8));
}

static uint8_t fx_spd(void)
{
    return (led_speed_lev > iSPEED_LEV_MAX) ? (uint8_t)iSPEED_LEV_MAX : (uint8_t)led_speed_lev;
}

static bool fx_multi(void)
{
    return (iRGB_QICAI == (led_rgb_index & 0x07));
}

static const uint8_t *fx_pal(void)
{
    return fx_palette[led_rgb_index & 0x07];
}

/* 逻辑位置 -> 物理灯序号, 跟随 bled_run_dir */
static uint8_t fx_idx(uint8_t k)
{
    return bled_run_dir ? (uint8_t)(iLED_MAX - 1 - k) : k;
}

/* HSV -> RGB, h/s: 0..255, v: 0..64 */
static void fx_hsv(uint8_t h, uint8_t s, uint8_t v, uint8_t *rgb)
{
    uint8_t region, rem, p, q, t;

    if(0 == s)
    {
        rgb[0] = rgb[1] = rgb[2] = v;
        return;
    }
    region = h / 43;
    rem    = (uint8_t)((h - region * 43) * 6);
    p = (uint8_t)((v * (255 - s)) >> 8);
    q = (uint8_t)((v * (255 - ((s * rem) >> 8))) >> 8);
    t = (uint8_t)((v * (255 - ((s * (255 - rem)) >> 8))) >> 8);

    switch(region)
    {
        case 0:  rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
        case 1:  rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
        case 2:  rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
        case 3:  rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
        case 4:  rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
        default: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
    }
}

/* 写入一颗灯: rgb(0..64) * lev(0..256) */
static void fx_put(uint8_t i, const uint8_t *rgb, uint16_t lev)
{
    if(lev > 256)
        lev = 256;
    pwm_rgb_tbl[i][iR_INDEX] = (uint8_t)((rgb[0] * lev) >> 8);
    pwm_rgb_tbl[i][iG_INDEX] = (uint8_t)((rgb[1] * lev) >> 8);
    pwm_rgb_tbl[i][iB_INDEX] = (uint8_t)((rgb[2] * lev) >> 8);
}

/* 叠加一颗灯 (饱和到 iPWM_MAX) */
static void fx_add(uint8_t i, const uint8_t *rgb, uint16_t lev)
{
    static const uint8_t ch[3] = {iR_INDEX, iG_INDEX, iB_INDEX};
    uint8_t c;
    uint16_t v;

    if(lev > 256)
        lev = 256;
    for(c=0; c<3; c++)
    {
        v = (uint16_t)(pwm_rgb_tbl[i][ch[c]] + ((rgb[c] * lev) >> 8));
        pwm_rgb_tbl[i][ch[c]] = (uint8_t)((v > iPWM_MAX) ? iPWM_MAX : v);
    }
}

/* 单色模式下取色: 全彩时返回 hue 对应的颜色 */
static void fx_color(uint8_t hue, uint8_t sat, uint8_t *rgb)
{
    if(fx_multi())
        fx_hsv(hue, sat, iPWM_MAX, rgb);
    else
        memcpy(rgb, fx_pal(), 3);
}

//=============================================================================;
// 灯效实现                                                                     ;
//=============================================================================;

/******************************************************************************
* 流光 (重写, 去抖动): 亮度波沿灯条流动, 波长 4 颗灯; 全彩时每颗灯在最暗处换色
*   原实现的抖动来源及对应处理:
*   1. 内部只有 0..64 共 65 级, gamma 后高亮区一级 ≈ 9/255  -> 写 12bit 高精度缓冲
*   2. 用"跳帧"降速, 亮度每 2~5 帧才变一次, 形成可见台阶  -> 相位按 RTC 时间连续推进
*   3. 三角波在波峰处突然折返                              -> 升余弦波, 首尾平滑
*   4. 波谷完全熄灭再点亮, 且在此瞬间切换颜色              -> 保留 ~12% 感知亮度底光,
*                                                            颜色在波谷附近交叉渐变
*   周期 (速度档位): 1 / 2 / 3 / 4 / 5 秒, 与原实现在 USB 下的速度一致
******************************************************************************/
static const uint16_t           fx_lg_cos_tbl[65] = {   // round(65535*(1-cos(πi/64))/2)
         0,    39,   158,   355,   630,   982,  1411,  1915,
      2494,  3146,  3869,  4662,  5522,  6448,  7438,  8488,
      9597, 10762, 11980, 13248, 14563, 15922, 17321, 18758,
     20228, 21728, 23256, 24806, 26375, 27960, 29556, 31160,
     32767, 34375, 35979, 37575, 39160, 40729, 42279, 43807,
     45307, 46777, 48214, 49613, 50972, 52287, 53555, 54773,
     55938, 57047, 58097, 59087, 60013, 60873, 61666, 62389,
     63041, 63620, 64124, 64553, 64905, 65180, 65377, 65496,
     65535,
};
static const uint16_t           fx_lg_inc[5] = {512, 256, 171, 128, 102};   // 2^24 / 周期tick
#define iFX_LG_FLOOR            492                     // 底光 ≈ 12% (感知亮度)
#define iFX_LG_XFADE            6554                    // 波谷两侧 10% 周期内交叉换色
#define iFX_LG_COLORS           7                       // 全彩颜色序列: rgb_en_tbl 1..7

static uint32_t                 fx_lg_acc;              // 周期内相位 (2^24 = 1 周期)
static uint32_t                 fx_lg_cyc;              // 已完成的周期数
static uint32_t                 fx_lg_rtc;

/* 升余弦: p(0..65535) -> 0..65535, p=0 为波谷, p=32768 为波峰 */
static uint16_t fx_lg_wave(uint16_t p)
{
    uint32_t q = (p >= 0x8000) ? (0x10000UL - p) : p;   // 对称折叠到 0..0x8000
    uint32_t idx = q >> 9, frac = q & 0x1FF;
    uint32_t y = fx_lg_cos_tbl[idx];

    if(idx < 64)
        y += ((fx_lg_cos_tbl[idx+1] - y) * frac) >> 9;
    return (uint16_t)y;
}

/* 全彩颜色序列: RGB 位掩码 1..7 = 红 绿 黄 蓝 紫 青 白 */
static uint8_t fx_lg_mask(uint32_t n)
{
    return (uint8_t)(1 + (n % iFX_LG_COLORS));
}

static void fx_liuguang(void)
{
    uint32_t dt, b, wa, wb, cyc, ch;
    int32_t  p32;
    uint16_t p;
    uint8_t  k, c, ma, mb, phys;
    static const uint8_t bit[3] = {iPWM_R, iPWM_G, iPWM_B};
    static const uint8_t idx[3] = {iR_INDEX, iG_INDEX, iB_INDEX};

    dt = led_now_rtc - fx_lg_rtc;
    fx_lg_rtc = led_now_rtc;
    if(dt > 65536)
        dt = 65536;                                     // 休眠唤醒等长间隔: 最多前进 2s
    fx_lg_acc += dt * fx_lg_inc[fx_spd()];
    fx_lg_cyc += fx_lg_acc >> 24;
    fx_lg_acc &= 0xFFFFFF;

    for(k=0; k<iLED_MAX; k++)
    {
        // 第 k 颗灯滞后 1/4 周期 -> 波向序号增大方向流动
        p32 = (int32_t)(fx_lg_acc >> 8) - (int32_t)k * 16384;
        cyc = fx_lg_cyc + (uint32_t)(p32 >> 16);        // p32 为负时借位 (算术右移)
        p   = (uint16_t)(p32 & 0xFFFF);

        b = iFX_LG_FLOOR + (((uint32_t)(iLED_HR_MAX - iFX_LG_FLOOR) * fx_lg_wave(p)) >> 16);

        if(fx_multi())
        {
            // 波谷附近从上一个颜色渐变到下一个颜色, 颜色序列各灯错开 1 位
            if(p < iFX_LG_XFADE)
            {
                ma = fx_lg_mask(cyc + k - 1);
                mb = fx_lg_mask(cyc + k);
                wb = 32768 + ((uint32_t)p * 32768) / iFX_LG_XFADE;
            }
            else if(p > (0x10000 - iFX_LG_XFADE))
            {
                ma = fx_lg_mask(cyc + k);
                mb = fx_lg_mask(cyc + k + 1);
                wb = ((uint32_t)(p - (0x10000 - iFX_LG_XFADE)) * 32768) / iFX_LG_XFADE;
            }
            else
            {
                ma = mb = fx_lg_mask(cyc + k);
                wb = 0;
            }
        }
        else
        {
            ma = mb = rgb_en_tbl[led_rgb_index & 0x0F];
            wb = 0;
        }
        wa = 65536 - wb;

        phys = bled_run_dir ? (uint8_t)(iLED_MAX - 1 - k) : k;
        for(c=0; c<3; c++)
        {
            ch = ((ma & bit[c]) ? wa : 0) + ((mb & bit[c]) ? wb : 0);    // 0..65536
            pwm_rgb_hr[phys][idx[c]] = (uint16_t)((b * ch) >> 16);
            pwm_rgb_tbl[phys][idx[c]] = (uint8_t)(pwm_rgb_hr[phys][idx[c]] >> 6);
        }
    }
    bled_hr_frame = true;
}

/******************************************************************************
* 激光 (按键响应): 按到哪颗灯亮哪颗, 并向两侧轻微扩散后渐隐
*   全彩: 颜色随位置变化 (左→右彩虹)
******************************************************************************/
static const uint8_t            fx_jg_shift[5] = {4, 5, 5, 6, 6};   // 衰减速度

static void fx_jiguang(void)
{
    uint8_t p, k, rgb[3];

    while(fx_key_pop(&p))
    {
        if(iLED_POS_NONE == p)
        {
            fx_lv[iLED_MAX/2 - 1] = 256;
            fx_lv[iLED_MAX/2] = 256;
            continue;
        }
        fx_lv[p] = 256;
        if((p > 0) && (fx_lv[p-1] < 128))
            fx_lv[p-1] = 128;
        if((p < iLED_MAX-1) && (fx_lv[p+1] < 128))
            fx_lv[p+1] = 128;
    }

    for(k=0; k<iLED_MAX; k++)
    {
        fx_color((uint8_t)(k * 32), 255, rgb);
        fx_put(k, rgb, fx_lv[k]);
        if(fx_lv[k])
        {
            uint16_t d = (uint16_t)((fx_lv[k] >> fx_jg_shift[fx_spd()]) + 1);
            fx_lv[k] = (fx_lv[k] > d) ? (uint16_t)(fx_lv[k] - d) : 0;
        }
    }
}

/******************************************************************************
* 办公柔光: 静态单色 (白=暖白)
*   全彩: 粉彩渐变, 以几十秒~数分钟一圈的速度极慢流动, 几乎察觉不到变化
******************************************************************************/
static const uint8_t            fx_soft_div[5] = {24, 48, 96, 160, 240};

static void fx_soft_on(void)
{
    uint8_t k, rgb[3];

    if(!fx_multi())
    {
        for(k=0; k<iLED_MAX; k++)
            fx_put(k, fx_pal(), 256);
        return;
    }

    if(++fx_cnt >= fx_soft_div[fx_spd()])
    {
        fx_cnt = 0;
        fx_ph1++;
    }
    for(k=0; k<iLED_MAX; k++)
    {
        fx_hsv((uint8_t)(fx_ph1 + k * 20), 150, iPWM_MAX, rgb);
        fx_put(fx_idx(k), rgb, 256);
    }
}

/******************************************************************************
* 柔和呼吸: 正弦曲线, 最暗 ~22% 不熄灭; 周期 3 / 4.5 / 6 / 8 / 10 秒
*   全彩: 每次呼吸到最暗时换一个颜色
******************************************************************************/
static const uint16_t           fx_breath_inc[5] = {171, 114, 85, 64, 51};
#define iFX_BREATH_FLOOR        56

static void fx_soft_breath(void)
{
    uint16_t prev = fx_ph1;
    uint16_t lev;
    uint8_t  k, rgb[3];

    fx_ph1 = (uint16_t)(fx_ph1 + fx_breath_inc[fx_spd()]);
    if(fx_ph1 < prev)
        fx_hue[0] = (uint8_t)(fx_hue[0] + 36);

    lev = (uint16_t)(iFX_BREATH_FLOOR
        + ((fx_sin8((uint8_t)((fx_ph1 >> 8) + 192)) * (256 - iFX_BREATH_FLOOR)) >> 8));

    fx_color(fx_hue[0], 210, rgb);
    for(k=0; k<iLED_MAX; k++)
        fx_put(k, rgb, lev);
}

/******************************************************************************
* 彩虹流动: 平滑 HSV 彩虹, 一圈 2 / 3.5 / 5 / 8 / 12 秒
*   单色: 同色亮度波沿灯条流动
******************************************************************************/
static const uint16_t           fx_rainbow_inc[5] = {256, 146, 102, 64, 43};

static void fx_rainbow(void)
{
    uint8_t k, h0, rgb[3];

    fx_ph1 = (uint16_t)(fx_ph1 + fx_rainbow_inc[fx_spd()]);
    h0 = (uint8_t)(fx_ph1 >> 8);

    for(k=0; k<iLED_MAX; k++)
    {
        if(fx_multi())
        {
            fx_hsv((uint8_t)(h0 - k * 24), 255, iPWM_MAX, rgb);
            fx_put(fx_idx(k), rgb, 256);
        }
        else
        {
            fx_put(fx_idx(k), fx_pal(),
                (uint16_t)(64 + ((fx_sin8((uint8_t)(h0 - k * 40)) * 192) >> 8)));
        }
    }
}

/******************************************************************************
* 极光: 两路不同速度/方向的正弦波叠加形成"光幕", 第三路极慢的波让色调
*       在 绿 -> 青 -> 蓝紫 之间漂移; 单色: 在所选颜色附近 ±色相 漂移
******************************************************************************/
static const uint8_t            fx_aurora_inc[5] = {96, 72, 52, 36, 26};

static void fx_aurora(void)
{
    uint8_t  k, w1, w2, hue, sat, base, rgb[3];
    uint16_t inc = fx_aurora_inc[fx_spd()];
    uint16_t lev;

    fx_ph1 = (uint16_t)(fx_ph1 + inc);
    fx_ph2 = (uint16_t)(fx_ph2 + ((inc * 3) / 5));
    fx_ph3 = (uint16_t)(fx_ph3 + ((inc / 8) ? (inc / 8) : 1));

    base = (uint8_t)(96 + ((fx_sin8((uint8_t)(fx_ph3 >> 8)) * 100) >> 8));

    for(k=0; k<iLED_MAX; k++)
    {
        w1 = fx_sin8((uint8_t)((fx_ph1 >> 8) + k * 28));
        w2 = fx_sin8((uint8_t)((fx_ph2 >> 8) - k * 45 + 64));

        if(fx_multi())
        {
            hue = (uint8_t)(base + (((int16_t)w1 - 128) * 40) / 256);
            sat = 230;
        }
        else
        {
            hue = (uint8_t)(fx_pal_hue[led_rgb_index & 0x07] + (((int16_t)w1 - 128) * 16) / 256);
            sat = fx_pal_sat[led_rgb_index & 0x07];
        }
        fx_hsv(hue, sat, iPWM_MAX, rgb);

        lev = (uint16_t)((w2 * (96 + ((w1 * 160) >> 8))) >> 8);
        lev = (uint16_t)(40 + ((lev * 216) >> 8));
        fx_put(fx_idx(k), rgb, lev);
    }
}

/******************************************************************************
* 流星: 头部以亚像素精度平滑移动, 拖尾按平方曲线渐隐, 头部近白;
*       每颗流星之间随机间隔, 全彩时每颗换色
******************************************************************************/
static const uint8_t            fx_meteor_inc[5] = {28, 21, 15, 11, 8};
#define iFX_METEOR_TAIL         (4*256)

static void fx_meteor(void)
{
    uint8_t  k, rgb[3];
    int16_t  d;
    uint16_t lev, x;

    if(fx_cnt)
    {
        fx_cnt--;
        clr_rgb();
        return;
    }

    fx_pos = (int16_t)(fx_pos + fx_meteor_inc[fx_spd()]);
    if(fx_pos > (int16_t)(iLED_MAX * 256 + iFX_METEOR_TAIL))
    {
        fx_pos = -256;
        fx_cnt = 20 + (fx_rand8() & 0x3F);
        fx_hue[0] = (uint8_t)(fx_hue[0] + 40 + (fx_rand8() & 0x3F));
    }

    for(k=0; k<iLED_MAX; k++)
    {
        d = (int16_t)(fx_pos - k * 256);
        if(d <= -256)
            lev = 0;
        else if(d < 0)
            lev = (uint16_t)(256 + d);                  // 头部前沿抗锯齿
        else if(d < iFX_METEOR_TAIL)
        {
            x = (uint16_t)(iFX_METEOR_TAIL - d);
            lev = (uint16_t)(((uint32_t)x * x) >> 12);  // 平方衰减拖尾
        }
        else
            lev = 0;

        if(fx_multi())
            fx_hsv((uint8_t)(fx_hue[0] + (d >> 6)), (d < 256) ? 110 : 255, iPWM_MAX, rgb);
        else
            memcpy(rgb, fx_pal(), 3);
        fx_put(fx_idx(k), rgb, lev);
    }
}

/******************************************************************************
* 烛光: 每颗灯随机游走的目标亮度 + 一阶平滑, 偶尔整体"被风吹"变暗;
*       全彩/白: 琥珀色烛光 (亮时略偏黄, 暗时偏红); 其它: 用所选颜色微闪
******************************************************************************/
static const uint8_t            fx_candle_prob[5] = {80, 52, 34, 22, 14};

static void fx_candle(void)
{
    uint8_t k, rgb[3];
    int16_t diff;
    bool    amber = fx_multi() || (6 == (led_rgb_index & 0x07));

    if((0 == fx_rand8()) && (fx_rand8() < 96))
    {
        for(k=0; k<iLED_MAX; k++)
            fx_tg[k] = (uint16_t)(90 + (fx_rand8() & 0x3F));
    }

    for(k=0; k<iLED_MAX; k++)
    {
        if(fx_rand8() < fx_candle_prob[fx_spd()])
            fx_tg[k] = (uint16_t)(150 + (fx_rand8() % 107));

        diff = (int16_t)(fx_tg[k] - fx_lv[k]);
        fx_lv[k] = (uint16_t)(fx_lv[k] + diff / 8);

        if(amber)
        {
            rgb[0] = iPWM_MAX;
            rgb[1] = (uint8_t)(10 + ((fx_lv[k] * 16) >> 8));
            rgb[2] = (uint8_t)(fx_lv[k] >> 7);
        }
        else
            memcpy(rgb, fx_pal(), 3);
        fx_put(k, rgb, fx_lv[k]);
    }
}

/******************************************************************************
* 番茄专注:
*   专注 -> 灯条从一端逐渐填满, 当前灯缓慢呼吸 (全彩: 绿 -> 黄 -> 橙 随进度变化)
*   到点 -> 绿色柔和脉冲 3 次 -> 休息 (绿色, 灯条逐渐减少)
*   休息结束 -> 暖白脉冲 3 次 -> 等待 (暖白慢呼吸), 按任意键开始下一个番茄
*   时长由"速度"档位选择 (专注/休息, 分钟): 15/5, 25/5(默认), 30/5, 45/10, 60/10
* 注意: 无线模式下设备休眠时灯会关闭, 但计时基于 RTC 不受影响
******************************************************************************/
enum {
    iPOMO_FOCUS = 0,
    iPOMO_ALERT_BREAK,
    iPOMO_BREAK,
    iPOMO_ALERT_DONE,
    iPOMO_WAIT,
};
static const uint8_t            fx_pomo_focus_min[5] = {15, 25, 30, 45, 60};
static const uint8_t            fx_pomo_break_min[5] = { 5,  5,  5, 10, 10};
#define iFX_POMO_ALERT_FRAMES   (3*128)                 // 3 次脉冲, 每次 ~1s
#define iFX_HUE_GREEN           96

static void fx_pomodoro(void)
{
    uint8_t  k, full, frac, p, rgb[3];
    uint16_t lev, breathe, prog;
    uint32_t el, total;
    bool     key = false;

    while(fx_key_pop(&p))
        key = true;

    el = led_now_rtc - fx_rtc0;
    switch(fx_state)
    {
        case iPOMO_FOCUS:
        case iPOMO_BREAK:
            if(iPOMO_FOCUS == fx_state)
                total = (uint32_t)fx_pomo_focus_min[fx_spd()] * 60 * iLED_RTC_HZ;
            else
                total = (uint32_t)fx_pomo_break_min[fx_spd()] * 60 * iLED_RTC_HZ;

            if(el >= total)
            {
                fx_state++;
                fx_cnt = 0;
                fx_force_full = true;
                break;
            }
            prog = (uint16_t)(el / (total / (iLED_MAX * 256)));
            if(prog > (iLED_MAX * 256 - 1))
                prog = iLED_MAX * 256 - 1;
            full = (uint8_t)(prog >> 8);
            frac = (uint8_t)(prog & 0xFF);

            fx_ph1 = (uint16_t)(fx_ph1 + 64);           // 4s 呼吸
            breathe = (uint16_t)(200 + ((fx_sin8((uint8_t)(fx_ph1 >> 8)) * 56) >> 8));

            for(k=0; k<iLED_MAX; k++)
            {
                if(iPOMO_FOCUS == fx_state)
                {
                    fx_color((uint8_t)(iFX_HUE_GREEN - k * 12), 230, rgb);
                    if(k < full)
                        lev = 176;                      // 已完成
                    else if(k == full)
                        lev = (uint16_t)(24 + ((frac * (breathe - 24)) >> 8));
                    else
                        lev = 14;                       // 未完成: 微弱底光显示轨道
                }
                else
                {
                    fx_hsv(iFX_HUE_GREEN, 230, iPWM_MAX, rgb);
                    if(k > full)
                        lev = breathe;                  // 剩余休息时间
                    else if(k == full)
                        lev = (uint16_t)(((256 - frac) * breathe) >> 8);
                    else
                        lev = 0;
                }
                fx_put(fx_idx(k), rgb, lev);
            }
            break;

        case iPOMO_ALERT_BREAK:
        case iPOMO_ALERT_DONE:
            fx_cnt++;
            lev = fx_sin8((uint8_t)((fx_cnt << 1) + 192));
            if(iPOMO_ALERT_BREAK == fx_state)
                fx_hsv(iFX_HUE_GREEN, 230, iPWM_MAX, rgb);
            else
                memcpy(rgb, fx_palette[6], 3);
            for(k=0; k<iLED_MAX; k++)
                fx_put(k, rgb, lev);

            if((fx_cnt >= iFX_POMO_ALERT_FRAMES) || key)
            {
                fx_state++;
                fx_rtc0 = led_now_rtc;
                fx_force_full = false;
                fx_ph1 = 0;
            }
            break;

        default: // iPOMO_WAIT
            if(key)
            {
                fx_state = iPOMO_FOCUS;
                fx_rtc0 = led_now_rtc;
                fx_ph1 = 0;
                break;
            }
            fx_ph1 = (uint16_t)(fx_ph1 + 43);           // 6s 慢呼吸
            lev = (uint16_t)(26 + ((fx_sin8((uint8_t)((fx_ph1 >> 8) + 192)) * 64) >> 8));
            for(k=0; k<iLED_MAX; k++)
                fx_put(k, fx_palette[6], lev);
            break;
    }
}

/******************************************************************************
* 打字涟漪: 从按键对应位置向两侧扩散的光环, 最多 4 个同时存在;
*           平时保持 ~8% 底光, 全彩时每个涟漪随机颜色
******************************************************************************/
static const uint8_t            fx_ripple_spd[5]   = {40, 32, 26, 20, 16};
static const uint8_t            fx_ripple_decay[5] = { 5,  4,  3,  3,  2};
#define iFX_RIPPLE_W            384                     // 环宽 1.5 颗灯
#define iFX_RIPPLE_BASE         20                      // 底光

static void fx_ripple(void)
{
    uint8_t     p, k, j, rgb[3];
    int16_t     d, diff;
    uint16_t    lev;
    fx_ripple_t *r;

    while(fx_key_pop(&p))
    {
        r = &fx_rp[fx_cnt++ & (iFX_RIPPLE_NUM - 1)];
        r->pos  = (int16_t)((iLED_POS_NONE == p) ? ((iLED_MAX - 1) * 128) : (p * 256));
        r->rad  = 0;
        r->life = 256;
        r->hue  = fx_rand8();
    }

    fx_ph1 = (uint16_t)(fx_ph1 + 8);
    fx_color((uint8_t)(fx_ph1 >> 8), 120, rgb);
    for(k=0; k<iLED_MAX; k++)
        fx_put(k, rgb, iFX_RIPPLE_BASE);

    for(j=0; j<iFX_RIPPLE_NUM; j++)
    {
        r = &fx_rp[j];
        if(0 == r->life)
            continue;

        fx_color(r->hue, 255, rgb);
        for(k=0; k<iLED_MAX; k++)
        {
            d = (int16_t)(k * 256 - r->pos);
            if(d < 0)
                d = (int16_t)-d;
            diff = (int16_t)(d - (int16_t)r->rad);
            if(diff < 0)
                diff = (int16_t)-diff;
            if(diff < iFX_RIPPLE_W)
            {
                lev = (uint16_t)(((uint32_t)(iFX_RIPPLE_W - diff) * 256) / iFX_RIPPLE_W);
                lev = (uint16_t)((lev * r->life) >> 8);
                fx_add(k, rgb, lev);
            }
        }

        r->rad = (uint16_t)(r->rad + fx_ripple_spd[fx_spd()]);
        r->life = (r->life > fx_ripple_decay[fx_spd()])
                ? (uint16_t)(r->life - fx_ripple_decay[fx_spd()]) : 0;
        if(r->rad > (iLED_MAX * 256 + iFX_RIPPLE_W))
            r->life = 0;
    }
}

//=============================================================================;
// 入口                                                                         ;
//=============================================================================;

void led_effect_init(uint8_t mode)
{
    uint8_t k;

    clr_rgb();
    fx_cnt = 0;
    fx_ph1 = fx_ph2 = fx_ph3 = 0;
    fx_pos = -256;
    fx_state = 0;
    fx_rtc0 = led_now_rtc;
    fx_force_full = false;
    memset(fx_hue, 0, sizeof(fx_hue));
    memset(fx_lv, 0, sizeof(fx_lv));
    memset(fx_tg, 0, sizeof(fx_tg));
    memset(fx_rp, 0, sizeof(fx_rp));
    fx_key_flush();
    fx_lg_acc = 0;
    fx_lg_cyc = iFX_LG_COLORS * 1000;                   // 留出余量, 各灯错开相位后周期数不会小于 0
    fx_lg_rtc = led_now_rtc;

    fx_rand_state ^= (uint16_t)led_now_rtc;
    if(0 == fx_rand_state)
        fx_rand_state = 0xACE1;

    if(iMODE_LED_CANDLE == mode)
    {
        for(k=0; k<iLED_MAX; k++)
            fx_lv[k] = fx_tg[k] = 200;
    }
    else if(iMODE_LED_METEOR == mode)
    {
        fx_hue[0] = fx_rand8();
    }
}

void led_effect_run(uint8_t mode)
{
    switch(mode)
    {
        case iMODE_LED_LG_L_R:      fx_liuguang();      break;
        case iMODE_LED_JG:          fx_jiguang();       break;
        case iMODE_LED_SOFT_ON:     fx_soft_on();       break;
        case iMODE_LED_SOFT_BREATH: fx_soft_breath();   break;
        case iMODE_LED_RAINBOW:     fx_rainbow();       break;
        case iMODE_LED_AURORA:      fx_aurora();        break;
        case iMODE_LED_METEOR:      fx_meteor();        break;
        case iMODE_LED_CANDLE:      fx_candle();        break;
        case iMODE_LED_POMODORO:    fx_pomodoro();      break;
        case iMODE_LED_RIPPLE:      fx_ripple();        break;
        default:
            fx_key_flush();
            clr_rgb();
            break;
    }
}
