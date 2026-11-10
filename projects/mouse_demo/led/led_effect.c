/*******************************************************************************
* 文件名称: led_effect.c
*
* 功能说明: 灯效引擎 —— 输出管线 / 帧同步 / 按键事件 / 主题色板 / 全部灯效
*
*   设计定位: 桌搭颜值. 8 种"颜色"即 8 套主题色板, 所有灯效都从当前色板取色,
*             任意 灯效 x 主题 的组合都是协调的配色.
*
*   数值约定:
*     - 画布 fx_cv / 输出 pwm_rgb_hr: 每通道 0..iLED_HR_MAX(4096) 的感知亮度 (12bit)
*     - 亮度系数 lev: 0..4096
*     - 相位 / 色板位置: 0..65535 为一整圈
*     - 位置 x: 8.8 定点, 单位为"颗灯", 0 = 第 0 颗灯中心
*   输出由 led_output_transform() 统一做 gamma + 档位 + 淡入淡出.
*   目标芯片为 Cortex-M0 (无硬件除法), 每帧计算量控制在数千指令内.
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
// 若当前模式不在表中, 按键切换会回到表中第一项.
//
static const uint8_t            led_mode_cycle_tbl[] = {
    iMODE_LED_GLAZE,    iMODE_LED_TIDE,     iMODE_LED_TWIN,     iMODE_LED_SHIFT,
    iMODE_LED_FLOW,     iMODE_LED_STARDUST, iMODE_LED_WATER,    iMODE_LED_HEART,
    iMODE_LED_NEON,     iMODE_LED_PENDULUM, iMODE_LED_SHOWER,   iMODE_LED_COLLIDE,
    iMODE_LED_BLOOM,    iMODE_LED_CURTAIN,  iMODE_LED_AFTERGLOW,iMODE_LED_SOFT_ON,
    iMODE_LED_LAVA,     iMODE_LED_BAND,     iMODE_LED_AURORA,   iMODE_LED_FIREFLY,
    iMODE_LED_FIRE,     iMODE_LED_POMODORO, iMODE_LED_RIPPLE,
};

//=============================================================================;
// 主题色板                                                                     ;
//=============================================================================;
// led_rgb_index 0..7 对应 8 套主题, 色相与原"颜色"一致, 上位机的颜色名可沿用:
//   0 红 -> 落日   1 绿 -> 抹茶   2 蓝 -> 海盐   3 紫 -> 星云
//   4 黄 -> 琥珀   5 青 -> 薄荷苏打   6 白 -> 月光   7 全彩 -> 幻彩
// 每套 6 个色标, 等距循环排列 (末尾接回开头), 数值为 sRGB (与 gamma 2.2 输出对应),
// 可以直接用设计稿里的色值替换.
//
#define iFX_THEME_STOPS         6
#define iFX_STOP                10923                   // 相邻色标间距 = 65536/6
#define iFX_THEME_SPECTRUM      7
#define iFX_THEME_MOON          6

static const uint8_t            fx_theme[8][iFX_THEME_STOPS][3] = {
    {{0xC2,0x18,0x5B},{0xFF,0x2E,0x63},{0xFF,0x5E,0x3A},{0xFF,0x9A,0x3C},{0xFF,0xC9,0x3C},{0xFF,0x7A,0x5C}}, // 落日
    {{0x0B,0x6E,0x4F},{0x2E,0x9E,0x5B},{0x7B,0xC9,0x50},{0xC5,0xE8,0x6C},{0x8F,0xD6,0x94},{0x3F,0xA7,0x96}}, // 抹茶
    {{0x0B,0x2D,0x7A},{0x15,0x65,0xC0},{0x00,0xA6,0xD6},{0x6E,0xE7,0xF9},{0x2E,0x86,0xDE},{0x1B,0x3F,0xA0}}, // 海盐
    {{0x3A,0x0C,0xA3},{0x72,0x09,0xB7},{0xB5,0x17,0x9E},{0xF7,0x25,0x85},{0x7B,0x2C,0xBF},{0x43,0x61,0xEE}}, // 星云
    {{0xE8,0x5D,0x04},{0xFF,0x8C,0x1A},{0xFF,0xB3,0x47},{0xFF,0xD2,0x7F},{0xFF,0xA6,0x2B},{0xFF,0x73,0x00}}, // 琥珀
    {{0x00,0xD1,0xB2},{0x5E,0xF2,0xD6},{0xB8,0xF2,0xE6},{0xA0,0xC4,0xFF},{0xBD,0xB2,0xFF},{0x48,0xD1,0xCC}}, // 薄荷苏打
    {{0xFF,0xD9,0xA8},{0xFF,0xE9,0xCF},{0xF4,0xF1,0xFF},{0xDC,0xE6,0xFF},{0xFF,0xF2,0xE0},{0xFF,0xCF,0x94}}, // 月光
    {{0xFF,0x00,0x00},{0xFF,0xFF,0x00},{0x00,0xFF,0x00},{0x00,0xFF,0xFF},{0x00,0x00,0xFF},{0xFF,0x00,0xFF}}, // 幻彩
};
// 每套主题的"主色"位置 (纯色类灯效使用)
static const uint16_t           fx_theme_main[8] = {
    2*iFX_STOP, 2*iFX_STOP, 2*iFX_STOP, 1*iFX_STOP, 2*iFX_STOP, 1*iFX_STOP, 0, 0,
};
// 篝火专用色: 暗红 -> 橙 -> 金 -> 近白 (非循环)
static const uint8_t            fx_fire_tbl[6][3] = {
    {0x30,0x02,0x00},{0x8A,0x0E,0x00},{0xE0,0x30,0x00},{0xFF,0x6E,0x00},{0xFF,0xB0,0x20},{0xFF,0xE8,0xA8},
};
static const uint8_t            fx_firefly_rgb[3] = {0xC8,0xFF,0x3C};   // 幻彩主题下的萤火黄绿

// 升余弦半周期表: round(65535*(1-cos(πi/64))/2)
static const uint16_t           fx_cos_tbl[65] = {
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

// 速度档位倍率 (x/128): 第 2 档 (默认) = 1.0x
static const uint8_t            fx_speed_mul[iSPEED_LEV_MAX+1] = {181, 128, 90, 64, 45};

//=============================================================================;
// 灯效运行状态 (切换模式时清零)                                                ;
//=============================================================================;
typedef struct {
    uint16_t                    r, g, b;                // 0..4096
} fx_rgb_t;

typedef struct {                                        // 粒子: 流星 / 萤火虫 / 熔岩
    int16_t                     x;                      // 位置 8.8
    int16_t                     v;                      // 速度
    uint16_t                    ph;                     // 相位
    uint16_t                    t;                      // 计时 / 亮度
    uint8_t                     c;                      // 色板位置 (高 8 位)
    uint8_t                     a;                      // 激活
} fx_pt_t;

typedef struct {                                        // 打字涟漪
    int16_t                     pos;
    uint16_t                    rad;
    uint16_t                    life;
    uint8_t                     c;
} fx_ripple_t;

#define iFX_PT_NUM              3
#define iFX_RIPPLE_NUM          4
#define iFX_INTRO_FRAMES        200                     // 开机动画 ~1.6s
#define iFX_XFADE_STEP          6                       // 切换模式交叉渐变 ~0.33s

static uint16_t                 fx_cv[iLED_MAX][3];     // 画布 (逻辑灯序, R G B)
static uint16_t                 fx_tmp[iLED_MAX][3];    // 本帧新绘制的内容 (用于拖尾合成)
static uint16_t                 fx_xf_from[iLED_MAX][3];// 交叉渐变起点 (物理灯序, 输出格式)
static uint16_t                 fx_xf;                  // 交叉渐变剩余权重 0..256
static uint8_t                  fx_intro;               // 开机动画剩余帧
static bool                     fx_intro_done;

static uint32_t                 fx_rtc0;
static uint16_t                 fx_ph[3];
static uint16_t                 fx_col;                 // 色板漂移位置
static uint16_t                 fx_t;                   // 阶段计时 (帧)
static uint16_t                 fx_t2;
static uint8_t                  fx_state;
static uint16_t                 fx_a[iLED_MAX];
static uint16_t                 fx_b[iLED_MAX];
static uint8_t                  fx_c[iLED_MAX];
static fx_pt_t                  fx_pt[iFX_PT_NUM];
static fx_ripple_t              fx_rp[iFX_RIPPLE_NUM];
static uint16_t                 fx_rand_state = 0xACE1;

//=============================================================================;
// 输出管线                                                                     ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_output_transform
* 功能描述: 画面 -> LEDC 数据(0..255)
* 说    明: 由 drv_ledc_write() 在临界区内调用, 只访问 RAM.
*           bled_hr_frame 时读 pwm_rgb_hr (12bit), 否则读 pwm_rgb_tbl (0..64);
*           后者在 LED_GAMMA_EN=0 且主亮度=256 时与原移位方案完全一致.
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
            o = 1;                                      // 低档位下保留暗部
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

/* 开灯 / 唤醒: 从黑淡入 */
void led_master_restart(uint32_t now)
{
    led_frame_resync(now);
#if LED_FADE_EN
    led_master_fade = 0;
#endif
}

/* 切换模式: 只重置帧时钟 (画面由交叉渐变过渡, 不闪黑) */
void led_frame_resync(uint32_t now)
{
    led_frame_rtc = now;
    led_idle_rtc = now;                                 // 视为一次操作
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
// 基础工具                                                                     ;
//=============================================================================;

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

static uint8_t fx_theme_idx(void)
{
    return (uint8_t)(led_rgb_index & 0x07);
}

/* 按速度档位缩放的每帧增量 (至少为 1) */
static uint16_t fx_k(uint16_t base)
{
    uint32_t v = ((uint32_t)base * fx_speed_mul[fx_spd()]) >> 7;
    return (uint16_t)(v ? v : 1);
}

/* 按速度档位缩放的持续帧数 */
static uint16_t fx_dur(uint16_t base)
{
    return (uint16_t)(((uint32_t)base * 128) / fx_speed_mul[fx_spd()]);
}

static uint16_t fx_abs16(int32_t v)
{
    return (uint16_t)((v < 0) ? -v : v);
}

/* 升余弦: p=0 为 0, p=32768 为 65535, 一圈平滑起伏 */
static uint16_t fx_wave(uint16_t p)
{
    uint32_t q = (p >= 0x8000) ? (0x10000UL - p) : p;
    uint32_t idx = q >> 9, frac = q & 0x1FF;
    uint32_t y = fx_cos_tbl[idx];

    if(idx < 64)
        y += ((fx_cos_tbl[idx+1] - y) * frac) >> 9;
    return (uint16_t)y;
}

/* 正弦: 返回 -32767..32767 */
static int32_t fx_sin16(uint16_t p)
{
    return 32767 - (int32_t)fx_wave((uint16_t)(p - 16384));
}

/* 单次凸包: x 落在 [start, start+width) 内时返回 0..65535..0, 否则 0 */
static uint16_t fx_bump(uint16_t x, uint16_t start, uint16_t width)
{
    uint16_t d = (uint16_t)(x - start);
    if(d >= width)
        return 0;
    return fx_wave((uint16_t)(((uint32_t)d << 16) / width));
}

/* 缓动: t 0..256 */
static uint16_t fx_ease_out(uint16_t t)
{
    uint32_t u = 256 - t;
    return (uint16_t)(256 - ((u * u) >> 8));
}
static uint16_t fx_ease_in(uint16_t t)
{
    return (uint16_t)(((uint32_t)t * t) >> 8);
}
static uint16_t fx_ease_io(uint16_t t)
{
    return (uint16_t)(fx_wave((uint16_t)(t << 7)) >> 8);
}

//=============================================================================;
// 颜色                                                                         ;
//=============================================================================;

static void fx_lerp_stops(const uint8_t *a, const uint8_t *b, uint16_t f, fx_rgb_t *c)
{
    uint32_t r = (uint32_t)a[0] * (256 - f) + (uint32_t)b[0] * f;  // 0..65280
    uint32_t g = (uint32_t)a[1] * (256 - f) + (uint32_t)b[1] * f;
    uint32_t bl= (uint32_t)a[2] * (256 - f) + (uint32_t)b[2] * f;
    c->r = (uint16_t)((r  >> 4) + (r  >> 12));          // 0..4095
    c->g = (uint16_t)((g  >> 4) + (g  >> 12));
    c->b = (uint16_t)((bl >> 4) + (bl >> 12));
}

/* 当前主题色板取色, pos 0..65535 循环 */
static void fx_pal(uint16_t pos, fx_rgb_t *c)
{
    const uint8_t (*p)[3] = fx_theme[fx_theme_idx()];
    uint32_t x = (uint32_t)pos * iFX_THEME_STOPS;
    uint8_t  s = (uint8_t)(x >> 16);
    uint8_t  n = (uint8_t)((s + 1 >= iFX_THEME_STOPS) ? 0 : s + 1);

    fx_lerp_stops(p[s], p[n], (uint16_t)((x >> 8) & 0xFF), c);
}

static uint16_t fx_main(void)
{
    return fx_theme_main[fx_theme_idx()];
}

/* 向白色混合, amt 0..256 */
static void fx_white(fx_rgb_t *c, uint16_t amt)
{
    if(amt > 256)
        amt = 256;
    c->r = (uint16_t)(c->r + (((uint32_t)(iLED_HR_MAX - c->r) * amt) >> 8));
    c->g = (uint16_t)(c->g + (((uint32_t)(iLED_HR_MAX - c->g) * amt) >> 8));
    c->b = (uint16_t)(c->b + (((uint32_t)(iLED_HR_MAX - c->b) * amt) >> 8));
}

static void fx_mix(const fx_rgb_t *a, const fx_rgb_t *b, uint16_t t, fx_rgb_t *c)
{
    c->r = (uint16_t)(((uint32_t)a->r * (256 - t) + (uint32_t)b->r * t) >> 8);
    c->g = (uint16_t)(((uint32_t)a->g * (256 - t) + (uint32_t)b->g * t) >> 8);
    c->b = (uint16_t)(((uint32_t)a->b * (256 - t) + (uint32_t)b->b * t) >> 8);
}

//=============================================================================;
// 画布                                                                         ;
//=============================================================================;

/* 写一颗灯: 颜色 * lev(0..4096) */
static void fx_set(uint8_t k, const fx_rgb_t *c, uint16_t lev)
{
    fx_cv[k][0] = (uint16_t)(((uint32_t)c->r * lev) >> 12);
    fx_cv[k][1] = (uint16_t)(((uint32_t)c->g * lev) >> 12);
    fx_cv[k][2] = (uint16_t)(((uint32_t)c->b * lev) >> 12);
}

/* 叠加到指定缓冲 (不在此处截断, 提交时统一截断) */
static void fx_add_to(uint16_t (*buf)[3], uint8_t k, const fx_rgb_t *c, uint16_t lev)
{
    uint32_t v;
    v = buf[k][0] + (((uint32_t)c->r * lev) >> 12); buf[k][0] = (uint16_t)((v > 0xFFFF) ? 0xFFFF : v);
    v = buf[k][1] + (((uint32_t)c->g * lev) >> 12); buf[k][1] = (uint16_t)((v > 0xFFFF) ? 0xFFFF : v);
    v = buf[k][2] + (((uint32_t)c->b * lev) >> 12); buf[k][2] = (uint16_t)((v > 0xFFFF) ? 0xFFFF : v);
}

/* 在亚像素位置 x(8.8) 画一个半径 r(8.8) 的柔边光点, 叠加到 buf */
static void fx_splat(uint16_t (*buf)[3], int32_t x, uint16_t r, const fx_rgb_t *c, uint16_t lev)
{
    uint8_t  k;
    uint32_t d, t, u, f;

    for(k=0; k<iLED_MAX; k++)
    {
        d = fx_abs16((int32_t)k * 256 - x);
        if(d >= r)
            continue;
        t = (d << 8) / r;                               // 0..255
        u = 256 - ((t * t) >> 8);                       // 1 - t^2
        f = (u * u) >> 4;                               // (1 - t^2)^2, 0..4096
        fx_add_to(buf, k, c, (uint16_t)((f * lev) >> 12));
    }
}

/* 画布整体衰减 (拖尾), keep 0..256 */
static void fx_cv_keep(uint16_t keep)
{
    uint8_t i;
    uint16_t *p = &fx_cv[0][0];
    for(i=0; i<iLED_MAX*3; i++)
        p[i] = (uint16_t)(((uint32_t)p[i] * keep) >> 8);
}

/* 本帧内容与拖尾合成: 取较亮者 */
static void fx_merge_max(void)
{
    uint8_t i;
    uint16_t *p = &fx_cv[0][0], *q = &fx_tmp[0][0];
    for(i=0; i<iLED_MAX*3; i++)
    {
        if(q[i] > p[i])
            p[i] = q[i];
        q[i] = 0;
    }
}

static void fx_tmp_to_cv(void)
{
    memcpy(fx_cv, fx_tmp, sizeof(fx_cv));
    memset(fx_tmp, 0, sizeof(fx_tmp));
}

/* 画布 -> 输出缓冲: 方向镜像 + 交叉渐变 + 截断 */
static void fx_commit(void)
{
    static const uint8_t ch[3] = {iR_INDEX, iG_INDEX, iB_INDEX};
    uint8_t  k, c, phys;
    uint32_t v;

    for(k=0; k<iLED_MAX; k++)
    {
        phys = bled_run_dir ? (uint8_t)(iLED_MAX - 1 - k) : k;
        for(c=0; c<3; c++)
        {
            v = fx_cv[k][c];
            if(v > iLED_HR_MAX)
                v = iLED_HR_MAX;
            if(fx_xf)
                v = (v * (256 - fx_xf) + (uint32_t)fx_xf_from[phys][ch[c]] * fx_xf) >> 8;
            pwm_rgb_hr[phys][ch[c]] = (uint16_t)v;
            pwm_rgb_tbl[phys][ch[c]] = (uint8_t)(v >> 6);
        }
    }
    fx_xf = (fx_xf > iFX_XFADE_STEP) ? (uint16_t)(fx_xf - iFX_XFADE_STEP) : 0;
    bled_hr_frame = true;
}

/* 从当前显示的画面开始交叉渐变 */
static void fx_xfade_begin(void)
{
    if(bled_hr_frame)
        memcpy(fx_xf_from, pwm_rgb_hr, sizeof(fx_xf_from));
    else
        memset(fx_xf_from, 0, sizeof(fx_xf_from));
    fx_xf = 256;
}

//=============================================================================;
// 灯效                                                                         ;
//=============================================================================;

/******************************************************************************
* 开机动画: 中心一点白光 -> 主题色从中心向两侧绽放 -> 一道光泽扫过 -> 渐变进入当前灯效
******************************************************************************/
static void fx_intro_frame(void)
{
    uint16_t t = (uint16_t)(iFX_INTRO_FRAMES - fx_intro);
    uint16_t u = (uint16_t)((t * 256U) / iFX_INTRO_FRAMES);
    uint16_t g, r, d, f;
    int32_t  x, e;
    uint8_t  k;
    fx_rgb_t c, w = {iLED_HR_MAX, iLED_HR_MAX, iLED_HR_MAX};

    g = (uint16_t)((u >= 140) ? 256 : ((u * 256U) / 140));
    r = (uint16_t)((fx_ease_out(g) * 1180U) >> 8);      // 半径 0 -> 4.6 颗灯
    for(k=0; k<iLED_MAX; k++)
    {
        d = fx_abs16((int32_t)k * 256 - 896);
        e = (int32_t)r - d + 150;
        f = (uint16_t)((e <= 0) ? 0 : ((e >= 300) ? 4096 : (e * 4096) / 300));
        fx_pal((uint16_t)(d * 20 + u * 80), &c);
        fx_set(k, &c, f);
    }
    if(u < 64)
        fx_splat(fx_cv, 896, 420, &w, (uint16_t)((64 - u) * (64 - u)));
    if((u >= 140) && (u < 230))
    {
        x = -512 + ((int32_t)(u - 140) * 2816) / 90;
        for(k=0; k<iLED_MAX; k++)
        {
            d = fx_abs16((int32_t)k * 256 - x);
            if(d < 384)
            {
                f = (uint16_t)(((384 - d) * 72U) / 384);
                fx_rgb_t p = {fx_cv[k][0], fx_cv[k][1], fx_cv[k][2]};
                fx_white(&p, f);
                fx_cv[k][0] = p.r; fx_cv[k][1] = p.g; fx_cv[k][2] = p.b;
            }
        }
    }

    if(0 == --fx_intro)
    {                                                   // 动画结束: 渐变进入灯效
        fx_commit();
        fx_xfade_begin();
    }
}

/******************************************************************************
* 1 釉光渐变: 静态主题渐变 (适合拍照), 每隔数秒一道淡淡的光泽从左到右扫过,
*             像釉面反光. 速度档位决定光泽出现的间隔.
******************************************************************************/
static void fx_glaze(void)
{
    uint8_t  k;
    uint16_t d, f, sweep = 200;
    int32_t  x;
    fx_rgb_t c;

    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_main() - 17500 + k * 5000), &c);
        if(fx_t < sweep)
        {
            x = -512 + ((int32_t)fx_t * 2816) / sweep;
            d = fx_abs16((int32_t)k * 256 - x);
            if(d < 420)
            {
                f = (uint16_t)(((uint32_t)(420 - d) * 80) / 420);
                fx_white(&c, (uint16_t)((fx_ease_io((uint16_t)((f * 256U) / 80)) * 80U) >> 8));
            }
        }
        fx_set(k, &c, 4096);
    }
    if(++fx_t >= fx_dur(1024))                         // 约 8 秒一次
        fx_t = 0;
}

/******************************************************************************
* 2 潮汐呼吸: 中心先亮, 两侧随后, 像潮水涨落; 颜色随呼吸沿色板缓慢漂移.
*             最低保留 ~14% 亮度. 周期约 5 秒 (默认速度)
******************************************************************************/
static void fx_tide(void)
{
    uint8_t  k;
    uint16_t w, lev;
    fx_rgb_t c;

    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(100));
    fx_col   = (uint16_t)(fx_col + fx_k(6));
    for(k=0; k<iLED_MAX; k++)
    {
        w = fx_wave((uint16_t)(fx_ph[0] - fx_abs16(2 * k - 7) * 1300));
        lev = (uint16_t)(580 + (((uint32_t)(w >> 4) * (4096 - 580)) >> 12));
        fx_pal((uint16_t)(fx_col + k * 2200), &c);
        fx_set(k, &c, lev);
    }
}

/******************************************************************************
* 3 双星: 两颗主题对比色的光点相向摆动、穿过彼此, 交汇处颜色叠加混色, 带短拖尾
******************************************************************************/
static void fx_twin(void)
{
    int32_t  s, x;
    fx_rgb_t a, b;

    fx_cv_keep(236);
    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(170));
    fx_col   = (uint16_t)(fx_col + fx_k(8));
    s = fx_sin16(fx_ph[0]);
    x = (s * 950) >> 15;
    fx_pal(fx_col, &a);
    fx_pal((uint16_t)(fx_col + 32768), &b);
    fx_splat(fx_tmp, 896 + x, 330, &a, 4096);
    fx_splat(fx_tmp, 896 - x, 330, &b, 4096);
    fx_merge_max();
}

/******************************************************************************
* 4 渐变流转: 整条灯带同时沿色板缓慢变色, 中心领先、两侧稍滞后, 边缘略暗增加纵深.
*             默认约 13 秒走完一圈色板
******************************************************************************/
static void fx_shift(void)
{
    uint8_t  k, d;
    fx_rgb_t c;

    fx_col = (uint16_t)(fx_col + fx_k(40));
    for(k=0; k<iLED_MAX; k++)
    {
        d = (uint8_t)fx_abs16(2 * k - 7);
        fx_pal((uint16_t)(fx_col - d * 900), &c);
        fx_set(k, &c, (uint16_t)(4096 - d * 110));
    }
}

/******************************************************************************
* 5 流光: 亮度波沿灯带流动 (波长 4 颗灯), 颜色沿色板连续变化;
*         升余弦波形 + ~12% 底光, 无台阶无闪断. 默认一个波周期 2 秒
******************************************************************************/
static void fx_flow(void)
{
    uint8_t  k;
    uint16_t w, lev;
    fx_rgb_t c;

    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(256));
    fx_col   = (uint16_t)(fx_col + fx_k(12));
    for(k=0; k<iLED_MAX; k++)
    {
        w = fx_wave((uint16_t)(fx_ph[0] - k * 16384));
        lev = (uint16_t)(492 + (((uint32_t)(w >> 4) * (4096 - 492)) >> 12));
        fx_pal((uint16_t)(fx_col - k * 6000), &c);
        fx_set(k, &c, lev);
    }
}

/******************************************************************************
* 6 星屑: 暗色主题渐变打底, 星点随机浮现 (快亮慢灭), 部分星点带白色高光
******************************************************************************/
static void fx_stardust(void)
{
    uint8_t  k;
    uint16_t ph, prev, e, t;
    fx_rgb_t bg, s;

    fx_col = (uint16_t)(fx_col + fx_k(4));
    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col + k * 4000), &bg);
        fx_set(k, &bg, 260);

        ph = fx_a[k];
        if(0 == ph)
        {
            if(fx_rand8() < fx_k(3))
            {
                fx_a[k] = 1;
                fx_c[k] = fx_rand8();
                fx_b[k] = (uint16_t)(2400 + fx_rand8() * 6);
                if(fx_rand8() < 70)
                    fx_b[k] |= 0x8000;                  // 白色高光星
            }
            continue;
        }
        prev = ph;
        ph = (uint16_t)(ph + fx_k(420));
        if(ph < prev)
        {
            fx_a[k] = 0;
            continue;
        }
        fx_a[k] = ph;

        if(ph < 10000)
            t = (uint16_t)(((uint32_t)ph << 8) / 10000);                // 快速点亮
        else
            t = (uint16_t)(((uint32_t)(65535 - ph) << 8) / 55535);      // 缓慢熄灭
        e = (uint16_t)(((uint32_t)t * t) >> 4);                         // 0..4096

        fx_pal((uint16_t)(fx_c[k] << 8), &s);
        if(fx_b[k] & 0x8000)
            fx_white(&s, 150);
        fx_add_to(fx_cv, k, &s, (uint16_t)(((uint32_t)e * (fx_b[k] & 0x0FFF)) >> 12));
    }
}

/******************************************************************************
* 7 波光: 两路不同速度的波相互干涉, 平方后形成水面焦散般的亮斑, 亮斑处泛白光
******************************************************************************/
static void fx_water(void)
{
    uint8_t  k;
    uint16_t w1, w2, s, q, gl;
    fx_rgb_t c;

    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(150));
    fx_ph[1] = (uint16_t)(fx_ph[1] + fx_k(97));
    fx_col   = (uint16_t)(fx_col + fx_k(5));
    for(k=0; k<iLED_MAX; k++)
    {
        w1 = fx_wave((uint16_t)(fx_ph[0] + k * 9000));
        w2 = fx_wave((uint16_t)(fx_ph[1] - k * 14000 + 20000));
        s  = (uint16_t)(((uint32_t)w1 + w2) >> 9);                      // 0..255
        q  = (uint16_t)((s * s) >> 8);
        gl = (uint16_t)((((q * q) >> 8) * q) >> 8);
        fx_pal((uint16_t)(fx_col + (w1 >> 3)), &c);
        fx_white(&c, (uint16_t)((gl * 110U) >> 8));
        fx_set(k, &c, (uint16_t)(900 + ((q * 3196U) >> 8)));
    }
}

/******************************************************************************
* 8 心跳: "扑通-扑通" 双脉冲 (约 66 次/分), 从中心向两侧传开; 峰值处颜色更暖更亮.
*         取代原"爆闪": 节奏感强但不刺眼
******************************************************************************/
static void fx_heart(void)
{
    uint8_t  k;
    uint16_t tt, e1, e2, e;
    fx_rgb_t c;

    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(560));
    for(k=0; k<iLED_MAX; k++)
    {
        tt = (uint16_t)(fx_ph[0] - fx_abs16(2 * k - 7) * 700);
        e1 = fx_bump(tt, 0, 9500);
        e2 = (uint16_t)(((uint32_t)fx_bump(tt, 12500, 9500) * 160) >> 8);
        e  = (e1 > e2) ? e1 : e2;
        fx_pal((uint16_t)(fx_main() + (e >> 4)), &c);
        fx_white(&c, (uint16_t)(e >> 11));
        fx_set(k, &c, (uint16_t)(330 + (((uint32_t)(e >> 4) * (4096 - 330)) >> 12)));
    }
}

/******************************************************************************
* 9 霓虹灯牌: 灯带分成 3 段"灯管", 依次闪烁点亮 (像霓虹灯通电), 之后稳定发光
*             带轻微电流嗡鸣感; 每隔几秒随机一段灯管接触不良般地闪几下
******************************************************************************/
static const uint8_t            fx_neon_tube[iLED_MAX] = {0, 0, 0, 1, 1, 2, 2, 2};
static const uint8_t            fx_neon_end[iLED_MAX]  = {1, 0, 1, 1, 1, 1, 0, 1};

static void fx_neon(void)
{
    uint8_t  t, k;
    uint16_t tg, lev;
    fx_rgb_t c;

    // fx_c[t]: 0 等待 1 点火中 2 常亮 3 故障闪烁; fx_b[t]: 计时; fx_a[t]: 目标; fx_a[t+3]: 显示
    for(t=0; t<3; t++)
    {
        switch(fx_c[t])
        {
            case 0:
                tg = 0;
                if(0 == --fx_b[t]) { fx_c[t] = 1; fx_b[t] = 64; }
                break;
            case 1:
                tg = fx_a[t];
                if(0 == (fx_b[t] & 0x03))
                    tg = (fx_rand8() < 150) ? 4096 : ((fx_rand8() < 128) ? 900 : 0);
                if(0 == --fx_b[t]) { fx_c[t] = 2; tg = 4096; }
                break;
            case 3:
                tg = fx_a[t];
                if(0 == (fx_b[t] & 0x03))
                    tg = (fx_rand8() < 128) ? 4096 : 1300;
                if(0 == --fx_b[t]) { fx_c[t] = 2; tg = 4096; }
                break;
            default:
                tg = (uint16_t)(3950 + (fx_rand8() & 0x7F));            // 嗡鸣
                break;
        }
        fx_a[t] = tg;
        fx_a[t+3] = (uint16_t)(fx_a[t+3] + ((int32_t)tg - fx_a[t+3]) / 2);
    }

    if((2 == fx_c[0]) && (2 == fx_c[1]) && (2 == fx_c[2]) && (0 == --fx_t))
    {
        t = (uint8_t)(fx_rand8() % 3);
        fx_c[t] = 3;
        fx_b[t] = (uint16_t)(18 + (fx_rand8() & 0x1F));
        fx_t = (uint16_t)(fx_dur(640) + fx_rand8() * 3);
    }

    for(k=0; k<iLED_MAX; k++)
    {
        t = fx_neon_tube[k];
        fx_pal((uint16_t)(fx_main() + t * 21845), &c);
        lev = fx_a[t+3];
        if(fx_neon_end[k])
            lev = (uint16_t)((lev * 218U) >> 8);                       // 灯管两端略暗
        fx_set(k, &c, lev);
    }
}

/******************************************************************************
* 10 钟摆: 单个光点做简谐摆动, 颜色随位置变化, 长拖尾划出一道渐变弧光
******************************************************************************/
static void fx_pendulum(void)
{
    int32_t  x;
    fx_rgb_t c;

    fx_cv_keep(247);
    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(150));
    fx_col   = (uint16_t)(fx_col + fx_k(5));
    x = 896 + ((fx_sin16(fx_ph[0]) * 920) >> 15);
    fx_pal((uint16_t)(fx_col + x * 12), &c);
    fx_splat(fx_tmp, x, 300, &c, 4096);
    fx_merge_max();
}

/******************************************************************************
* 11 流星雨: 最多 3 颗流星随机出发, 速度/亮度/颜色各不相同, 头部白热, 尾部渐隐
******************************************************************************/
static void fx_shower(void)
{
    uint8_t  i;
    fx_pt_t  *p;
    fx_rgb_t c;

    fx_cv_keep(228);
    for(i=0; i<iFX_PT_NUM; i++)
    {
        p = &fx_pt[i];
        if(!p->a)
        {
            if(fx_rand8() < fx_k(3))
            {
                p->a = 1;
                p->x = -300;
                p->v = (int16_t)(((uint32_t)fx_k(22) * (160 + (fx_rand8() >> 1) + (fx_rand8() >> 2))) >> 8);
                if(p->v < 4)
                    p->v = 4;
                p->c = fx_rand8();
                p->t = (uint16_t)(2600 + fx_rand8() * 5);
            }
            continue;
        }
        p->x = (int16_t)(p->x + p->v);
        if(p->x > (iLED_MAX * 256 + 300))
            p->a = 0;
        fx_pal((uint16_t)(p->c << 8), &c);
        fx_white(&c, 110);
        fx_splat(fx_tmp, p->x, 220, &c, p->t);
    }
    fx_merge_max();
}

/******************************************************************************
* 12 对撞: 两颗对比色光点从两端加速冲向中心, 相撞瞬间白光一闪,
*          混合色光环向两侧炸开后消散, 下一轮换一组颜色
******************************************************************************/
static void fx_collide(void)
{
    uint16_t T, t, r, d, diff, lev;
    int32_t  x;
    uint8_t  k;
    fx_rgb_t a, b, m, w = {iLED_HR_MAX, iLED_HR_MAX, iLED_HR_MAX};

    fx_pal(fx_col, &a);
    fx_pal((uint16_t)(fx_col + 32768), &b);
    fx_cv_keep((2 == fx_state) ? 232 : 225);
    fx_t++;

    if(0 == fx_state)
    {
        T = fx_dur(110);
        t = (uint16_t)(((uint32_t)fx_t << 8) / T);
        x = -256 + (((int32_t)fx_ease_in(t) * 1152) >> 8);
        fx_splat(fx_tmp, x, 300, &a, 4096);
        fx_splat(fx_tmp, 1792 - x, 300, &b, 4096);
        if(fx_t >= T) { fx_state = 1; fx_t = 0; }
    }
    else if(1 == fx_state)
    {
        T = fx_dur(70);
        t = (uint16_t)(((uint32_t)fx_t << 8) / T);
        if(t > 256)
            t = 256;
        r = (uint16_t)((fx_ease_out(t) * 1180U) >> 8);
        lev = (uint16_t)((256 - t) * 16);
        fx_mix(&a, &b, 128, &m);
        fx_white(&m, (uint16_t)((256 - t) >> 2));
        for(k=0; k<iLED_MAX; k++)
        {
            d = fx_abs16((int32_t)k * 256 - 896);
            diff = fx_abs16((int32_t)d - r);
            if(diff < 420)
                fx_add_to(fx_tmp, k, &m, (uint16_t)(((uint32_t)(420 - diff) * lev) / 420));
        }
        if(t < 90)
            fx_splat(fx_tmp, 896, 420, &w, (uint16_t)(((90 - t) * (90 - t) * 4096U) / 8100));
        if(fx_t >= T) { fx_state = 2; fx_t = 0; }
    }
    else
    {
        if(fx_t >= fx_dur(60))
        {
            fx_state = 0;
            fx_t = 0;
            fx_col = (uint16_t)(fx_col + iFX_STOP);
        }
    }
    fx_merge_max();
}

/******************************************************************************
* 13 绽放: 光从中心向两侧舒展开 (中心主色, 边缘渐变到相邻色), 停留片刻
*          轻轻摇曳, 再从两端向中心收拢; 每一轮换下一组颜色
******************************************************************************/
static void fx_bloom(void)
{
    static const uint16_t dur[4] = {100, 70, 90, 30};
    uint16_t T, t, R = 0, d, f, sh;
    int32_t  e;
    uint8_t  k;
    fx_rgb_t c;

    T = fx_dur(dur[fx_state & 3]);
    t = (uint16_t)(((uint32_t)fx_t << 8) / T);
    if(t > 256)
        t = 256;
    switch(fx_state)
    {
        case 0:  R = (uint16_t)((fx_ease_out(t) * 1130U) >> 8);         break;
        case 1:  R = 1130;                                             break;
        case 2:  R = (uint16_t)(((256 - fx_ease_in(t)) * 1130U) >> 8); break;
        default: R = 0;                                                break;
    }
    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(180));

    for(k=0; k<iLED_MAX; k++)
    {
        d = fx_abs16((int32_t)k * 256 - 896);
        e = (int32_t)R - d + 150;
        f = (uint16_t)((e <= 0) ? 0 : ((e >= 300) ? 4096 : (e * 4096) / 300));
        if(1 == fx_state)
        {
            sh = fx_wave((uint16_t)(fx_ph[0] + k * 8000));
            f = (uint16_t)((f * (3700U + (sh >> 7))) >> 12);           // 摇曳 ±5%
        }
        fx_pal((uint16_t)(fx_col + d * 14), &c);
        fx_white(&c, (uint16_t)((896 - d) >> 4));                     // 花心略亮
        fx_set(k, &c, f);
    }

    if(++fx_t >= T)
    {
        fx_t = 0;
        fx_state = (uint8_t)((fx_state + 1) & 3);
        if(0 == fx_state)
            fx_col = (uint16_t)(fx_col + 9000);
    }
}

/******************************************************************************
* 14 幕布: 新颜色像幕布一样从一侧滑入覆盖旧颜色, 幕布边缘带一道高光;
*          停留后换下一色, 方向左右交替
******************************************************************************/
static void fx_curtain(void)
{
    uint16_t T, t, cov, edge;
    int32_t  x, u;
    uint8_t  k, kk;
    fx_rgb_t a, b, c;

    fx_pal(fx_col, &a);
    fx_pal((uint16_t)(fx_col + iFX_STOP), &b);

    if(0 == fx_state)
    {
        T = fx_dur(110);
        t = (uint16_t)(((uint32_t)fx_t << 8) / T);
        if(t > 256)
            t = 256;
        x = -400 + (((int32_t)fx_ease_io(t) * 2592) >> 8);
        for(k=0; k<iLED_MAX; k++)
        {
            kk = fx_c[0] ? (uint8_t)(iLED_MAX - 1 - k) : k;
            u = x - (int32_t)kk * 256;
            cov  = (uint16_t)((u >= 400) ? 256 : ((u <= -400) ? 0 : ((u + 400) * 256) / 800));
            edge = (uint16_t)((fx_abs16(u) < 300) ? ((300 - fx_abs16(u)) * 70U) / 300 : 0);
            fx_mix(&a, &b, fx_ease_io(cov), &c);
            fx_white(&c, edge);
            fx_set(k, &c, 4096);
        }
        if(++fx_t >= T) { fx_state = 1; fx_t = 0; }
    }
    else
    {
        for(k=0; k<iLED_MAX; k++)
            fx_set(k, &b, 4096);
        if(++fx_t >= fx_dur(150))
        {
            fx_state = 0;
            fx_t = 0;
            fx_col = (uint16_t)(fx_col + iFX_STOP);
            fx_c[0] ^= 1;
        }
    }
}

/******************************************************************************
* 15 余晖 (按键响应): 按键位置的灯被"烧"成白热, 随后像金属冷却一样沿色板
*                    变色并慢慢暗下去; 平时保留 ~5% 主题底光
******************************************************************************/
static void fx_afterglow(void)
{
    uint8_t  p, k;
    uint16_t h, d;
    fx_rgb_t bg, c;

    fx_col = (uint16_t)(fx_col + fx_k(3));
    while(fx_key_pop(&p))
    {
        if(iLED_POS_NONE == p)
        {
            fx_a[iLED_MAX/2 - 1] = 4096;
            fx_a[iLED_MAX/2] = 4096;
            continue;
        }
        fx_a[p] = 4096;
        if((p > 0) && (fx_a[p-1] < 2200))
            fx_a[p-1] = 2200;
        if((p < iLED_MAX - 1) && (fx_a[p+1] < 2200))
            fx_a[p+1] = 2200;
    }

    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col + k * 4000), &bg);
        fx_set(k, &bg, 200);
        h = fx_a[k];
        if(0 == h)
            continue;
        fx_pal((uint16_t)(fx_main() + (4096 - h) * 5), &c);
        if(h > 2800)
            fx_white(&c, (uint16_t)((h - 2800) >> 3));
        fx_add_to(fx_cv, k, &c, h);
        d = (uint16_t)((((uint32_t)h * fx_k(4)) >> 8) + 1);
        fx_a[k] = (h > d) ? (uint16_t)(h - d) : 0;
    }
}

/******************************************************************************
* 16 柔光: 主题主色纯色常亮 (月光主题即暖白); 幻彩主题为粉彩渐变,
*          以几十秒到数分钟一圈的速度极慢流动
******************************************************************************/
static const uint8_t            fx_soft_div[5] = {24, 48, 96, 160, 240};

static void fx_soft(void)
{
    uint8_t  k;
    fx_rgb_t c;

    if(iFX_THEME_SPECTRUM != fx_theme_idx())
    {
        fx_pal(fx_main(), &c);
        for(k=0; k<iLED_MAX; k++)
            fx_set(k, &c, 4096);
        return;
    }
    if(++fx_t >= fx_soft_div[fx_spd()])
    {
        fx_t = 0;
        fx_col = (uint16_t)(fx_col + 256);
    }
    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col + k * 5000), &c);
        fx_white(&c, 110);
        fx_set(k, &c, 4096);
    }
}

/******************************************************************************
* 17 熔岩灯: 3 团大小会呼吸的光团以不同的慢周期漂移, 相遇时颜色融合 (保持色相);
*            极慢, 适合当作桌面氛围灯
******************************************************************************/
static const uint8_t            fx_lava_i1[3] = {43, 31, 23};
static const uint8_t            fx_lava_i2[3] = {71, 53, 37};

static void fx_lava(void)
{
    uint8_t  i, k;
    int32_t  x;
    uint16_t r, m;
    uint32_t s;
    fx_rgb_t c;

    fx_col = (uint16_t)(fx_col + fx_k(3));
    for(i=0; i<3; i++)
    {
        fx_ph[i]    = (uint16_t)(fx_ph[i] + fx_k(fx_lava_i1[i]));
        fx_pt[i].ph = (uint16_t)(fx_pt[i].ph + fx_k(fx_lava_i2[i]));
        x = 896 + ((fx_sin16(fx_ph[i]) * 640) >> 15) + ((fx_sin16(fx_pt[i].ph) * 300) >> 15);
        r = (uint16_t)(380 + (fx_wave((uint16_t)(fx_pt[i].ph * 2 + i * 20000)) >> 8));
        fx_pal((uint16_t)(fx_col + i * 21845), &c);
        fx_splat(fx_tmp, x, r, &c, 3600);
    }
    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col + k * 3000), &c);
        fx_add_to(fx_tmp, k, &c, 230);
        m = fx_tmp[k][0];
        if(fx_tmp[k][1] > m) m = fx_tmp[k][1];
        if(fx_tmp[k][2] > m) m = fx_tmp[k][2];
        if(m > iLED_HR_MAX)
        {                                               // 超出时等比压缩, 保持色相
            s = ((uint32_t)iLED_HR_MAX << 12) / m;
            fx_tmp[k][0] = (uint16_t)((fx_tmp[k][0] * s) >> 12);
            fx_tmp[k][1] = (uint16_t)((fx_tmp[k][1] * s) >> 12);
            fx_tmp[k][2] = (uint16_t)((fx_tmp[k][2] * s) >> 12);
        }
    }
    fx_tmp_to_cv();
}

/******************************************************************************
* 18 色带流动: 完整的主题渐变色带沿灯带持续滚动, 默认约 4.5 秒一圈
******************************************************************************/
static void fx_band(void)
{
    uint8_t  k;
    fx_rgb_t c;

    fx_col = (uint16_t)(fx_col + fx_k(110));
    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col - k * 5200), &c);
        fx_set(k, &c, (uint16_t)(4096 - fx_abs16(2 * k - 7) * 60));
    }
}

/******************************************************************************
* 19 极光: 两路光幕叠加, 明暗与色彩在主题色板内缓慢起伏
******************************************************************************/
static void fx_aurora(void)
{
    uint8_t  k;
    uint16_t w1, w2, m;
    fx_rgb_t c;

    fx_ph[0] = (uint16_t)(fx_ph[0] + fx_k(62));
    fx_ph[1] = (uint16_t)(fx_ph[1] + fx_k(37));
    fx_col   = (uint16_t)(fx_col + fx_k(4));
    for(k=0; k<iLED_MAX; k++)
    {
        w1 = fx_wave((uint16_t)(fx_ph[0] + k * 7000));
        w2 = fx_wave((uint16_t)(fx_ph[1] - k * 11500 + 16384));
        m  = (uint16_t)(((w2 >> 8) * (100 + (((w1 >> 8) * 156U) >> 8))) >> 8);
        fx_pal((uint16_t)(fx_col + ((int32_t)w1 - 32768) / 3), &c);
        fx_set(k, &c, (uint16_t)(500 + m * 14));
    }
}

/******************************************************************************
* 20 萤火虫: 3 只萤火虫缓慢游走, 各自不定时地亮起、熄灭, 带一点余光
******************************************************************************/
static void fx_firefly(void)
{
    uint8_t  i;
    uint16_t prev;
    fx_pt_t  *p;
    fx_rgb_t c;

    fx_cv_keep(215);
    for(i=0; i<iFX_PT_NUM; i++)
    {
        p = &fx_pt[i];
        p->v = (int16_t)(p->v + (int8_t)(fx_rand8() - 128) / 16);
        if(p->v > 48)  p->v = 48;
        if(p->v < -48) p->v = -48;
        p->x = (int16_t)(p->x + p->v / 16);
        if(p->x < 0)    { p->x = 0;    p->v = (int16_t)-p->v; }
        if(p->x > 1792) { p->x = 1792; p->v = (int16_t)-p->v; }

        if(p->t)
        {
            p->t--;
            continue;
        }
        prev = p->ph;
        p->ph = (uint16_t)(p->ph + fx_k(330));
        if(p->ph < prev)
        {
            p->ph = 0;
            p->t = (uint16_t)(fx_dur(80) + fx_rand8());
            continue;
        }
        if(iFX_THEME_SPECTRUM == fx_theme_idx())
            fx_lerp_stops(fx_firefly_rgb, fx_firefly_rgb, 0, &c);
        else
            fx_pal((uint16_t)(fx_main() + i * 6000), &c);
        fx_splat(fx_tmp, p->x, 240, &c, (uint16_t)(fx_wave(p->ph) >> 4));
    }
    fx_merge_max();
}

/******************************************************************************
* 21 篝火: 一维火焰模拟 (随机火星 + 热量扩散 + 冷却), 显示做平滑处理不刺眼;
*          落日 / 琥珀 / 幻彩 主题为真实火焰色, 其他主题为对应颜色的"冷焰"
******************************************************************************/
static void fx_fire(void)
{
    uint8_t  k, h[iLED_MAX], c8;
    uint16_t v, x;
    fx_rgb_t c;
    uint8_t  th = fx_theme_idx();
    bool     real = (0 == th) || (4 == th) || (iFX_THEME_SPECTRUM == th);

    if(++fx_t >= 3)
    {
        fx_t = 0;
        for(k=0; k<iLED_MAX; k++)
        {
            c8 = (uint8_t)(fx_rand8() % 18);
            fx_c[k] = (fx_c[k] > c8) ? (uint8_t)(fx_c[k] - c8) : 0;
        }
        for(k=0; k<iLED_MAX; k++)
            h[k] = (uint8_t)(((uint16_t)fx_c[k ? k-1 : 0] + 2 * fx_c[k] + fx_c[(k < iLED_MAX-1) ? k+1 : k]) >> 2);
        memcpy(fx_c, h, sizeof(h));
        if(fx_rand8() < fx_k(150))
        {
            k = (uint8_t)(fx_rand8() & (iLED_MAX - 1));
            v = (uint16_t)(fx_c[k] + 120 + (fx_rand8() % 120));
            fx_c[k] = (uint8_t)((v > 255) ? 255 : v);
        }
    }

    for(k=0; k<iLED_MAX; k++)
    {
        fx_a[k] = (uint16_t)(fx_a[k] + ((int32_t)fx_c[k] * 16 - fx_a[k]) / 8);  // 平滑, 避免刺眼的闪烁
        v = fx_a[k];
        if(real)
        {
            x = (uint16_t)((v >> 4) * 5);                                // 0..1275
            fx_lerp_stops(fx_fire_tbl[x >> 8], fx_fire_tbl[((x >> 8) < 5) ? (x >> 8) + 1 : 5],
                          (uint16_t)(x & 0xFF), &c);
        }
        else
        {
            fx_pal((uint16_t)(fx_main() + (v << 2)), &c);
            if(v > 3000)
                fx_white(&c, (uint16_t)((v - 3000) >> 3));
        }
        fx_set(k, &c, (uint16_t)(700 + ((v * 3396U) >> 12)));
    }
}

/******************************************************************************
* 22 番茄专注:
*   专注 -> 灯带沿主题渐变逐格填满, 当前格缓慢呼吸, 未完成部分保留微弱轨道
*   到点 -> 主题色柔和脉冲 3 次 -> 休息 (对比色, 灯带逐渐减少)
*   休息结束 -> 月光色脉冲 3 次 -> 等待 (慢呼吸), 按任意键开始下一个番茄
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
#define iFX_POMO_ALERT_FRAMES   (3*128)

static void fx_pomodoro(void)
{
    static const uint8_t moon[3] = {0xFF, 0xD9, 0xA8};
    uint8_t  k, full, frac, p;
    uint16_t lev, breathe, prog;
    uint32_t el, total;
    bool     key = false;
    fx_rgb_t c;

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
                fx_t = 0;
                fx_force_full = true;
                break;
            }
            prog = (uint16_t)(el / (total / (iLED_MAX * 256)));
            if(prog > (iLED_MAX * 256 - 1))
                prog = iLED_MAX * 256 - 1;
            full = (uint8_t)(prog >> 8);
            frac = (uint8_t)(prog & 0xFF);

            fx_ph[0] = (uint16_t)(fx_ph[0] + 64);                       // 4s 呼吸
            breathe = (uint16_t)(3200 + (fx_wave(fx_ph[0]) >> 6) * 14);  // 78%..100%

            for(k=0; k<iLED_MAX; k++)
            {
                if(iPOMO_FOCUS == fx_state)
                {
                    fx_pal((uint16_t)(fx_main() + k * 3500), &c);
                    if(k < full)
                        lev = 2800;
                    else if(k == full)
                        lev = (uint16_t)(380 + ((frac * (uint32_t)(breathe - 380)) >> 8));
                    else
                        lev = 230;
                }
                else
                {
                    fx_pal((uint16_t)(fx_main() + 32768), &c);
                    if(k > full)
                        lev = breathe;
                    else if(k == full)
                        lev = (uint16_t)(((256 - frac) * (uint32_t)breathe) >> 8);
                    else
                        lev = 0;
                }
                fx_set(k, &c, lev);
            }
            break;

        case iPOMO_ALERT_BREAK:
        case iPOMO_ALERT_DONE:
            fx_t++;
            lev = (uint16_t)(fx_wave((uint16_t)(fx_t << 9)) >> 4);
            if(iPOMO_ALERT_BREAK == fx_state)
                fx_pal(fx_main(), &c);
            else
                fx_lerp_stops(moon, moon, 0, &c);
            for(k=0; k<iLED_MAX; k++)
                fx_set(k, &c, lev);

            if((fx_t >= iFX_POMO_ALERT_FRAMES) || key)
            {
                fx_state++;
                fx_rtc0 = led_now_rtc;
                fx_force_full = false;
                fx_ph[0] = 0;
            }
            break;

        default: // iPOMO_WAIT
            if(key)
            {
                fx_state = iPOMO_FOCUS;
                fx_rtc0 = led_now_rtc;
                fx_ph[0] = 0;
                break;
            }
            fx_ph[0] = (uint16_t)(fx_ph[0] + 43);                       // 6s 慢呼吸
            fx_lerp_stops(moon, moon, 0, &c);
            lev = (uint16_t)(410 + (fx_wave(fx_ph[0]) >> 6) * 16);
            for(k=0; k<iLED_MAX; k++)
                fx_set(k, &c, lev);
            break;
    }
}

/******************************************************************************
* 23 打字涟漪: 从按键对应位置向两侧扩散的光环, 最多 4 个同时存在,
*              每个涟漪取色板中不同颜色; 平时保留 ~7% 主题底光
******************************************************************************/
#define iFX_RIPPLE_W            384

static void fx_ripple(void)
{
    uint8_t     p, k, j;
    uint16_t    d, diff;
    fx_ripple_t *r;
    fx_rgb_t    c;

    while(fx_key_pop(&p))
    {
        r = &fx_rp[fx_t++ & (iFX_RIPPLE_NUM - 1)];
        r->pos  = (int16_t)((iLED_POS_NONE == p) ? 896 : (p * 256));
        r->rad  = 0;
        r->life = 4096;
        r->c    = fx_rand8();
    }

    fx_col = (uint16_t)(fx_col + fx_k(3));
    for(k=0; k<iLED_MAX; k++)
    {
        fx_pal((uint16_t)(fx_col + k * 4000), &c);
        fx_set(k, &c, 300);
    }

    for(j=0; j<iFX_RIPPLE_NUM; j++)
    {
        r = &fx_rp[j];
        if(0 == r->life)
            continue;
        fx_pal((uint16_t)(r->c << 8), &c);
        for(k=0; k<iLED_MAX; k++)
        {
            d = fx_abs16((int32_t)k * 256 - r->pos);
            diff = fx_abs16((int32_t)d - r->rad);
            if(diff < iFX_RIPPLE_W)
                fx_add_to(fx_cv, k, &c,
                    (uint16_t)(((uint32_t)(iFX_RIPPLE_W - diff) * r->life) / iFX_RIPPLE_W));
        }
        r->rad = (uint16_t)(r->rad + fx_k(30));
        d = fx_k(48);
        r->life = (r->life > d) ? (uint16_t)(r->life - d) : 0;
        if(r->rad > (iLED_MAX * 256 + iFX_RIPPLE_W))
            r->life = 0;
    }
}

//=============================================================================;
// 入口                                                                         ;
//=============================================================================;

void led_effect_init(uint8_t mode)
{
    uint8_t i;

    fx_xfade_begin();                                   // 从当前画面渐变到新灯效

    memset(fx_cv, 0, sizeof(fx_cv));
    memset(fx_tmp, 0, sizeof(fx_tmp));
    memset(fx_ph, 0, sizeof(fx_ph));
    memset(fx_a, 0, sizeof(fx_a));
    memset(fx_b, 0, sizeof(fx_b));
    memset(fx_c, 0, sizeof(fx_c));
    memset(fx_pt, 0, sizeof(fx_pt));
    memset(fx_rp, 0, sizeof(fx_rp));
    fx_col = 0;
    fx_t = fx_t2 = 0;
    fx_state = 0;
    fx_rtc0 = led_now_rtc;
    fx_force_full = false;
    fx_key_flush();

    fx_rand_state ^= (uint16_t)led_now_rtc;
    if(0 == fx_rand_state)
        fx_rand_state = 0xACE1;

    if(false == fx_intro_done)
    {                                                   // 上电后第一次点亮: 开机动画
        fx_intro_done = true;
        fx_intro = iFX_INTRO_FRAMES;
        fx_xf = 0;
    }

    switch(mode)
    {
        case iMODE_LED_NEON:
            for(i=0; i<3; i++)
                fx_b[i] = (uint16_t)(30 + i * 50);      // 三段灯管依次点火
            fx_t = fx_dur(640);
            break;
        case iMODE_LED_FIREFLY:
            for(i=0; i<iFX_PT_NUM; i++)
            {
                fx_pt[i].x = (int16_t)(300 + i * 600);
                fx_pt[i].t = (uint16_t)(i * 70);
            }
            break;
        case iMODE_LED_FIRE:
            for(i=0; i<iLED_MAX; i++)
                fx_c[i] = 120;
            break;
        case iMODE_LED_STARDUST:
        case iMODE_LED_SHOWER:
        case iMODE_LED_RIPPLE:
            fx_col = fx_main();
            break;
        default:
            break;
    }
}

void led_effect_run(uint8_t mode)
{
    if(fx_intro)
    {
        fx_intro_frame();
        if(fx_intro)
            fx_commit();
        return;
    }

    switch(mode)
    {
        case iMODE_LED_GLAZE:       fx_glaze();         break;
        case iMODE_LED_TIDE:        fx_tide();          break;
        case iMODE_LED_TWIN:        fx_twin();          break;
        case iMODE_LED_SHIFT:       fx_shift();         break;
        case iMODE_LED_FLOW:        fx_flow();          break;
        case iMODE_LED_STARDUST:    fx_stardust();      break;
        case iMODE_LED_WATER:       fx_water();         break;
        case iMODE_LED_HEART:       fx_heart();         break;
        case iMODE_LED_NEON:        fx_neon();          break;
        case iMODE_LED_PENDULUM:    fx_pendulum();      break;
        case iMODE_LED_SHOWER:      fx_shower();        break;
        case iMODE_LED_COLLIDE:     fx_collide();       break;
        case iMODE_LED_BLOOM:       fx_bloom();         break;
        case iMODE_LED_CURTAIN:     fx_curtain();       break;
        case iMODE_LED_AFTERGLOW:   fx_afterglow();     break;
        case iMODE_LED_SOFT_ON:     fx_soft();          break;
        case iMODE_LED_LAVA:        fx_lava();          break;
        case iMODE_LED_BAND:        fx_band();          break;
        case iMODE_LED_AURORA:      fx_aurora();        break;
        case iMODE_LED_FIREFLY:     fx_firefly();       break;
        case iMODE_LED_FIRE:        fx_fire();          break;
        case iMODE_LED_POMODORO:    fx_pomodoro();      break;
        case iMODE_LED_RIPPLE:      fx_ripple();        break;
        default:                                        // iMODE_LED_OFF
            fx_key_flush();
            memset(fx_cv, 0, sizeof(fx_cv));
            break;
    }
    fx_commit();
}
