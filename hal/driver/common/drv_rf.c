/**
 *  ____       _   _        ____                    ��  H
 * |  _ \ __ _| \ | | __ _ / ___|___  __ _          ��  A
 * | |_) / _` |  \| |/ _` | |   / _ \/ _` |         ��  Low
 * |  __/ (_| | |\  | (_| | |__|  __/ (_| |             Level
 * |_|   \__,_|_| \_|\__,_|\____\___|\__,_|         LUWEI
 *
 * @project   Panacea
 * @copyright Copyright (c) 2021 OnMicro Corp.
 * @author    wei.lu@onmicro.com.cn
 * @license   SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file    drv_hlp_rf.c
 * @brief   RF (2.4G and BLE) helper driver source.
 *
 * @addtogroup PANACEA
 * @{
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "om_driver.h"
#include "main.h"

typedef struct {
    uint8_t  tx_fifo_idx;
} rf_env_t;


/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/
#define DRV_RF_TX_SETUP_TIME_TICK   8 /*8+130+10xtal us*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
/* CONFIG register: mask(1) interrupts etc. */
#define CONFIG_EN_TX_GUARD          (1u << 7)
#define CONFIG_MASK_EVT_DS          (1u << 7)
#define CONFIG_MASK_RX_DR           (1u << 6)
#define CONFIG_MASK_TX_DS           (1u << 5)
#define CONFIG_MASK_SYNC_DS         (1u << 4)
#define CONFIG_EN_CRC               (1u << 3)
#define CONFIG_MASK_RX_TIMEOUT      (1u << 2)
#define CONFIG_PRIM_RX              (1u << 0) //2.4G only

/* RF_STATUS register: irq status etc. */
#define IRQ_STATUS_EVT_DS           (1u << 7)
#define IRQ_STATUS_RX_DR            (1u << 6)
#define IRQ_STATUS_TX_DS            (1u << 5)
#define IRQ_STATUS_SYNC_DS          (1u << 4)
#define IRQ_STATUS_RX_TIMEOUT       (1u << 3)
/* 2.4G */
#define IRQ_STATUS_MAX_RT           (1u << 4)
#define STATUS_RX_P_NO_Pos          1
#define STATUS_RX_P_NO_Msk          (0x3 << 1)
#define STATUS_TX_FULL              (1u << 0)

/* RX_STATUS register: BLE receive status etc. */
#define BLE_STATUS_LASTEMPTY        (1u << 6)
#define BLE_STATUS_SNERR            (1u << 5)
#define BLE_STATUS_NESNERR          (1u << 4)
#define BLE_STATUS_CRCERR           (1u << 3)
#define BLE_STATUS_LENERR           (1u << 2)
#define BLE_STATUS_TYPEERR          (1u << 1)
#define BLE_STATUS_SYNERR           (1u << 0)

/* FIFO_STATUS register. */
#define FIFO_STATUS_TX_REUSE        (1u << 6)
#define FIFO_STATUS_TX_FULL         (1u << 5)
#define FIFO_STATUS_TX_EMPTY        (1u << 4)
#define FIFO_STATUS_RX_FULL         (1u << 1)
#define FIFO_STATUS_RX_EMPTY        (1u << 0)

/* SETUP register: test, calibration, PA etc. */
#define SETUP_CARRIER_TX_EN         (1u << 7)
#define SETUP_CAL_DONE              (1u << 5)
#define SETUP_CAL_EN                (1u << 4)
#define SETUP_RF_DR_HIGH            (1u << 3)

#define SETUP_PA_PWR_BIT3_Pos       6
#define SETUP_PA_PWR_BIT210_Pos     0
#define SETUP_PA_PWR_Msk            ((1 << SETUP_PA_PWR_BIT3_Pos) | (0x7 << SETUP_PA_PWR_BIT210_Pos))
#define SETUP_PA_PWR_SET(value)     ((((value) >> 3) << SETUP_PA_PWR_BIT3_Pos) | \
                                     ((value) & 0x7) << SETUP_PA_PWR_BIT210_Pos)
#define SETUP_PA_PWR_8dBm           15
#define SETUP_PA_PWR_5dBm           8
#define SETUP_PA_PWR_4dBm           7
#define SETUP_PA_PWR_0dBm           3
#define SETUP_PA_PWR_N6dBm          1
#define SETUP_PA_PWR_N12dBm         1
#define SETUP_PA_PWR_N16dBm         0
#define SETUP_PA_PWR_N43dBm         0

/* IVGEN register. */
#define IVGEN_PA_VOLTAGE_Pos        7
#define IVGEN_PA_VOLTAGE_Msk        (1U << IVGEN_PA_VOLTAGE_Pos)

/* FEATURE register: BLE, GFSK, VCO etc. */
#define FEATURE_BLE_EN              (1u << 6)
#define FEATURE_BP_GAU              (1u << 4)
#define FEATURE_VCO_AMP_TX_MUX      (1u << 3)
#define FEATURE_EN_DPL              (1u << 2)
#define FEATURE_EN_ACK_PAY          (1u << 1)
#define FEATURE_EN_DYN_ACK          (1u << 0)

/* FAGC_CTRL register: VCO etc. */
#define FAGC_PKDET_VREFC_Msk        (0x7 << 26)
#define FAGC_PKDET_VREF2C_Msk       (0x3 << 24)
#define FAGC_DPD_LO_THR_Msk         (0x7FF << 12)
#define FAGC_VCO_AMP_MN             (1 << 8)
#define FAGC_VCO_AMP_CTL_Msk        (0xF << 4)
#define FAGC_VCO_PKREF_CTL_Msk      (0xF << 0)

/* PLL_CTL0 register */
#define PLL_FOFFSET_SEL_Pos         24
#define PLL_FOFFSET_SEL_Msk         (0x3 << PLL_FOFFSET_SEL_Pos)
#define PLL_FOFFSET_SEL_1Mbps       0x1
#define PLL_FOFFSET_SEL_2Mbps       0x2

#define PLL_DAC_RANGE_MN_Pos        5
#define PLL_DAC_RANGE_MN_Msk        (1u << PLL_DAC_RANGE_MN_Pos)

#define RF_PLL(name,value) \
  (((value) << PLL_##name##_Pos) & PLL_##name##_Msk)
#define RF_PLL_INS(name,value,old) \
  (((old) & ~PLL_##name##_Msk) | RF_PLL(name,value))

/* CAL_CTL register: calibration RC, VCO LDO etc. */
#define CAL_BP_RX_ADDR_Pos          13
#define CAL_BP_RX_ADDR_Msk          (1U << CAL_BP_RX_ADDR_Pos)

#define CAL_VCO_LDO_CAL_REG_Pos     8
#define CAL_VCO_LDO_CAL_REG_Msk     (0x7 << CAL_VCO_LDO_CAL_REG_Pos)
#define CAL_VCO_LDO_CAL_MN          (1u << 7)

#define CAL_RC_CAL_CTL_REG_Pos      0
#define CAL_RC_CAL_CTL_REG_Msk      (0x1F << CAL_RC_CAL_CTL_REG_Pos)
#define CAL_RC_CAL_CTL_MN           (1u << 6)

/* RX_CTRL register: modem algorithm. */
#define ALG_SBE_MAX_TH_Pos          13
#define ALG_SBE_MAX_TH_Msk          (0x7 << ALG_SBE_MAX_TH_Pos)

#define ALG_XCORR_TH_Pos            6
#define ALG_XCORR_TH_Msk            (0x7F << ALG_XCORR_TH_Pos)

#define ALG_EN_DC_REMOVAL_Pos       5
#define ALG_EN_DC_REMOVAL_Msk       (1 << ALG_EN_DC_REMOVAL_Pos)

#define ALG_EN_SBE_Pos              4
#define ALG_EN_SBE_Msk              (1 << ALG_EN_SBE_Pos)

#define ALG_H_IDX_Pos               0
#define ALG_H_IDX_Msk               (0x3 << ALG_H_IDX_Pos)

/* DMA_CMD register */
#define DMA_CMD_DATA_BYTES_Pos      16
#define DMA_CMD_DATA_BYTES_Msk      (0xFF << DMA_CMD_DATA_BYTES_Pos)

#define DMA_CMD_OP_Pos              0
#define DMA_CMD_OP_Msk              (0xFF << DMA_CMD_OP_Pos)
#define DMA_CMD_RX_PAYLOAD          0x61
#define DMA_CMD_TX_PAYLOAD          0xA0
#define DMA_CMD_FLUSH_TX            0xE1
#define DMA_CMD_FLUSH_RX            0xE2
#define DMA_CMD_REUSE_FIFO          0xE3
#define DMA_CMD_TX_ACK(pipe)        (0xA8|(pipe))
#define DMA_CMD_TX_PAYLOAD_NAK      0xB0 // Enabled when FEATURE_EN_DYN_ACK is set.

/* BLE_CTL register: ble states. */
#define BLE_CTL_EVENT_ABORT         (1 << 7)
#define BLE_CTL_MD_DISABLE          (1 << 6)
#define BLE_CTL_FC_DISABLE          (1 << 5)
#define BLE_CTL_INFINITE_RX         (1 << 4)
/* slave connection: 0x05 or 0x0d
   0x05: hw fsm will force tx empty packet when lastempty=1 (tx empty just now);
   0x0d: hw fsm allows sw fill tx fifo     when lastempty=1.
*/
#define BLE_CTL_FMT_ADV             0x3
#define BLE_CTL_FMT_CONN_SLAVE      0x5//0xD
#define BLE_CTL_FMT_CONN_MASTER     0x4
#define BLE_CTL_FMT_SCAN_ACTIVE     0x6
#define BLE_CTL_FMT_SCAN_PASSIVE    0x8

#define BLE_CTL_FMT_TXTEST          0x9
#define BLE_CTL_FMT_RXTEST          0xB

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#define US_TO_TICK(us)              ((32 * (us) / 1000) + 1)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
static rf_env_t rf_env;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
/**
 * @brief hs6220 radio calibration.
 * @param [in] daterate - 0 for 1Mbps
 *                      - 1 for 2Mbps
 */
static void radio_calibration(uint8_t datarate)
{
    OM_RF->RFCE = 0;
    OM_RF->CONFIG = CONFIG_EN_CRC | CONFIG_PRIM_RX;

    OM_RF->RF_CH = 0x28; //2440MHz

    /* The calibration values are different for 1Mbps and 2Mbps(0.32&0.5 modualtion index). */
    if (datarate) {
        /* 0.32 modualtion index  */
        OM_RF->RF_SETUP = SETUP_CAL_EN | SETUP_RF_DR_HIGH | SETUP_PA_PWR_SET(0x0F/*5dBm*/);
        OM_RF->PLL_CTL0 = RF_PLL_INS(FOFFSET_SEL, PLL_FOFFSET_SEL_2Mbps, OM_RF->PLL_CTL0);
        OM_RF->FDEV = 0x29;
        OM_RF->RX_CTRL = ((1 << ALG_SBE_MAX_TH_Pos) | (0x50 << ALG_XCORR_TH_Pos) |
                         ALG_EN_DC_REMOVAL_Msk | ALG_EN_SBE_Msk |
                         ((OM_RF->RX_CTRL & (~ALG_H_IDX_Msk)) | (1 << ALG_H_IDX_Pos))); //0.32

        /* 0.5 modualtion index  */
        // OM_RF->RF_SETUP = SETUP_CAL_EN | SETUP_RF_DR_HIGH | SETUP_PA_PWR_SET(8/*5dBm*/);
        // OM_RF->PLL_CTL0 &= ~PLL_FOFFSET_SEL_Msk;
        // OM_RF->FDEV = 0x40;
        // OM_RF->RX_CTRL = ((1 << ALG_SBE_MAX_TH_Pos) | (0x50 << ALG_XCORR_TH_Pos) |
        //                  ALG_EN_DC_REMOVAL_Msk | ALG_EN_SBE_Msk |
        //                  (OM_RF->RX_CTRL & ~ALG_H_IDX_Msk | (2 << ALG_H_IDX_Pos))); //0.5
    } else {
        OM_RF->RF_SETUP = SETUP_CAL_EN | SETUP_PA_PWR_SET(0x0F/*5dBm*/);
        OM_RF->PLL_CTL0 = RF_PLL_INS(FOFFSET_SEL, PLL_FOFFSET_SEL_1Mbps, OM_RF->PLL_CTL0);
        OM_RF->FDEV = 0x25; //0x20=250khz 0x25=290khz 0x40=500khz?
        OM_RF->RX_CTRL = ((1 << ALG_SBE_MAX_TH_Pos) | (0x50 << ALG_XCORR_TH_Pos) |
                         ALG_EN_DC_REMOVAL_Msk | ALG_EN_SBE_Msk |
                         ((OM_RF->RX_CTRL & (~ALG_H_IDX_Msk)) | (2 << ALG_H_IDX_Pos))); //0.5
    }

    /* Initial frequency drift pass with CMW500 */
    OM_RF->TEST_PKDET = 0x00050020; //0x20 for A2; 0x24 for A1
    #if (CONFIG_OM6236)
    OM_RF->FAGC_CTRL_1 = 0x0905a010;
    #endif
    //OM_RF->FAGC_CTRL_1 |= 0x07;

    /* Set vco_amp_tx_mux=0 before calibration for small vco_amp: A1's default is 1. */
    OM_RF->FEATURE = FEATURE_BP_GAU;

    /* Emit CE pulse (200us) to start calibration. */
    OM_RF->CE_PULSE = 1;
    /* Wait calibration done. */
    while (0 == (OM_RF->RF_SETUP & SETUP_CAL_DONE));
    OM_RF->RF_IVGEN = (OM_RF->RF_IVGEN & ~0xFF) | 0x17;
}


static void fill_tx_fifo(const uint8_t *p_payload, uint8_t len)
{
    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_TX_PAYLOAD;
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

__RAM_CODE void read_rx_fifo(uint8_t *p_payload, uint8_t len)
{
    uint8_t payload[31];

    if (p_payload == NULL) {
        p_payload = payload;
    }

    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_RX_PAYLOAD;
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

static void fill_ack_fifo(const uint8_t *p_payload, uint8_t len, uint8_t pipe)
{
    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_TX_ACK(pipe);
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

__RAM_CODE static void fill_tx_fifo_nak(const uint8_t *p_payload, uint8_t len)
{
    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_TX_PAYLOAD_NAK;
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/
void drv_rf_reset_rx_fifo(void)
{
    OM_RF->DMA_CMD = (0 << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_FLUSH_RX;
}

void drv_rf_reset_tx_fifo(void)
{
    OM_RF->DMA_CMD = (0 << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_FLUSH_TX;
    rf_env.tx_fifo_idx = 0;
}

void drv_rf_reuse_tx_fifo(void)
{
    OM_RF->DMA_CMD = (0 << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_REUSE_FIFO;
}

__RAM_CODE void drv_rf_write_tx_payload(const uint8_t *p_payload, uint8_t len)
{
    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_TX_PAYLOAD;
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

void drv_rf_write_ack_payload(const uint8_t *p_payload, uint8_t len, uint8_t pipe)
{
    fill_ack_fifo(p_payload, len, pipe);
}

__RAM_CODE void drv_rf_write_tx_payload_noack(const uint8_t *p_payload, uint8_t len)
{
    OM_CRITICAL_BEGIN();
    OM_RF->DMA_ADDR = (uint32_t)p_payload;
    OM_RF->DMA_CMD = (len << DMA_CMD_DATA_BYTES_Pos) | DMA_CMD_TX_PAYLOAD_NAK;
    /* Wait done. */
    while (OM_RF->DMA_INT_RAW == 0);
    OM_RF->DMA_INT_RAW = 1;
    OM_CRITICAL_END();
}

/* DPL */
uint8_t drv_rf_get_rx_dynamic_payload_length(void)
{
    return OM_RF->RX_PW;
}

/* SPL */
void drv_rf_set_pipe_rx_static_payload_length(uint8_t pipe_no, uint8_t len)
{
    OM_RF->RX_PW_PIPE[pipe_no] = len;
}
uint8_t drv_rf_get_pipe_rx_static_payload_length(uint8_t pipe_no)
{
    return OM_RF->RX_PW_PIPE[pipe_no];
}

__RAM_CODE uint8_t drv_rf_read_rx_payload(uint8_t *p_payload)
{
    uint8_t len, pipe_no;
    pipe_no = drv_rf_get_rx_pipe_no();
    if (pipe_no >= DRV_RF_PIPE_NO_RX_EMPTY) {
        return 0;
    }

    /* RX_PW indicates the received payload length for both DPL & SPL. */
    len = OM_RF->RX_PW;
    read_rx_fifo(p_payload, len);

    return len;
}

uint8_t drv_rf_read_rx_payload_static(uint8_t *p_payload, uint8_t len)
{
    uint8_t rx_pw = drv_rf_get_rx_dynamic_payload_length();
    read_rx_fifo(p_payload, len);
    return rx_pw;
}

void drv_rf_select_24g(void)
{
    /* Enable 2.4G mode. */
    OM_RF->FEATURE = FEATURE_BP_GAU; //FSK
    /* Enable multiply level FIFO. */
    OM_RF->DFIFO_EN = 1;
    /* ALARM1 acts as normal alarm in sw. */
    //OM_RTC->WKRF_CR = 0;
    /* ALARM1 acts as ALARM2RF. */
    OM_RTC->WKRF_CR = 1;
    /* Enable RSSI */
    OM_RF->RSSI |= (1U << 14);
}
void drv_rf_select_ble(void)
{
    /* Enable BLE mode. */
    OM_RF->FEATURE = FEATURE_BLE_EN; //GFSK
    //OM_RF->FEATURE = FEATURE_BLE_EN | FEATURE_BP_GAU; //FSK
    /* ALARM1 acts as ALARM2RF. */
    OM_RTC->WKRF_CR = 1;
}

bool drv_rf_is_ble_mode(void)
{
    return OM_RF->FEATURE & FEATURE_BLE_EN ? true : false;
}

void drv_ble_init(void)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RF, 1U);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_AES128, 1U);
    radio_calibration(DRV_RF_DATE_RATE_1Mbps);

    drv_rf_select_ble();

    /* Enable interrupts of EVT_DS only. (RX_TIMEOUT set EVT_DS also.) */
    OM_RF->CONFIG = CONFIG_MASK_RX_DR | CONFIG_MASK_TX_DS | CONFIG_MASK_SYNC_DS | CONFIG_EN_CRC | CONFIG_MASK_RX_TIMEOUT;

    /*
      PLL_CTL1    : 104200   ;PA_wait=0x10/16=1us TXPLL_wait=0x42=66us AFC_wait=0x00=0us
                             ;rx2tx=AFC_wait+AFC_W_sel+TXPLL_wait+PA_wait+PAup1us+preGuard4us=0+56+66+1+1+4=128us
      CAL_CTL     : 28659f20 ;RXPLL_wait=0x28=40us  [13]bp_rx_addr=0 means decode the extra byte of rx_addr.
                             ;AFC_W_sel=b11=56us bp_afc=0
    */
    //OM_RF->PLL_CTL1 = 0x104207;

    /* Borrow guard time to implement 15-bit preamble: grd_cnt=6 is 7-bit pre_guard time. */
    //OM_RF->PRE_GURD = 0x76;
    //OM_RF->SETUP_DELAY = 0xf0; //sub extra 7us delay
    /* TIFS adjustment. */
    #if CONFIG_FPGA
    /* FPGA */
    OM_RF->SETUP_DELAY = 0xa9; //rx2tx: -2us; tx2rx: -1us
    #else
    /* ASIC */
    //OM_RF->PRE_GURD = 0x7d; //grd_cnt: 0xd, 14-bit pre_guard time
    //OM_RF->SETUP_DELAY = 0xfa; //rx2tx: -7us; tx2rx: -2us
    OM_RF->SETUP_DELAY = 0xaa; //rx2tx: -0us; tx2rx: -2us
    #endif

    /* alarm2rf requires it. */
    drv_rtc_control(OM_RTC, RTC_CONTROL_ALARM1_INT_EN, NULL);
}

void drv_rf24g_init(void)
{
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RF, 1U);

    if(true==brf_rate)
        radio_calibration(DRV_RF_DATE_RATE_2Mbps);
    else
        radio_calibration(DRV_RF_DATE_RATE_1Mbps);

    drv_rf_set_tx_power(0x18);

    drv_rf_select_24g();
    OM_RF->EN_RXADDR = 0x0F; //scramble_en = 0
    OM_RF->SETUP_RETR = 0x00;
    OM_RF->FEATURE |= (FEATURE_EN_DPL|FEATURE_EN_ACK_PAY|FEATURE_EN_DYN_ACK);

    drv_rf_reset_rx_fifo();
    drv_rf_reset_tx_fifo();
    drv_rf_get_and_clear_irq_status();
    NVIC_DisableIRQ(RF_IRQn);
}

void drv_rf_set_tx_power(uint8_t pwr)
{
    OM_RF->RF_SETUP = (OM_RF->RF_SETUP & ~SETUP_PA_PWR_Msk) |
                      SETUP_PA_PWR_SET((pwr>>1) & 0xf);

    if (0==(pwr & 0x01)) {
        OM_RF->RF_IVGEN |= IVGEN_PA_VOLTAGE_Msk;
    } else {
        OM_RF->RF_IVGEN &= ~IVGEN_PA_VOLTAGE_Msk;
    }
}
int8_t drv_rf_get_rssi(void)
{
    //drv_uart0_put_char(OM_RF->RSSI);
    return (int8_t)(OM_RF->RSSI & 0xff);
}

void drv_rf_set_channel(uint8_t channel)
{
    OM_RF->RF_CH = channel;
    //drv_uart0_put_char(channel);
}

void drv_rf_adjust_xtal(uint8_t tune)
{
    OM_RF->RF_IVGEN = (OM_RF->RF_IVGEN & ~0xFF) | tune;
}

void drv_rf_enable_interrupt(uint8_t bitmask)
{
    OM_RF->CONFIG &= ~bitmask;
}
void drv_rf_disable_interrupt(uint8_t bitmask)
{
    OM_RF->CONFIG |= bitmask;
}

void drv_rf_set_phy_mode_1mbps(void)
{
    OM_RF->RF_SETUP &= ~SETUP_RF_DR_HIGH;
    OM_RF->PLL_CTL0 = RF_PLL_INS(FOFFSET_SEL, PLL_FOFFSET_SEL_1Mbps, OM_RF->PLL_CTL0);
    OM_RF->FDEV = 0x20;
}
void drv_rf_set_phy_mode_2mbps(void)
{
    OM_RF->RF_SETUP |= SETUP_RF_DR_HIGH;
    OM_RF->PLL_CTL0 = RF_PLL_INS(FOFFSET_SEL, PLL_FOFFSET_SEL_2Mbps, OM_RF->PLL_CTL0);
    OM_RF->FDEV = 0x29;
}

void drv_rf_test_start_carrier_tx(void)
{
    OM_RF->RF_SETUP |= SETUP_CARRIER_TX_EN;
}
void drv_rf_test_stop_carrier_tx(void)
{
    OM_RF->RF_SETUP &= ~SETUP_CARRIER_TX_EN;
}

void drv_rf_set_rx_address_pipe0(const uint8_t addr[5])
{
    uint32_t lo4;
    memcpy(&lo4, addr, 4);
    OM_RF->RX_ADDR_P0 = lo4;
    OM_RF->RX_ADDR_P0_H = addr[4];
}
void drv_rf_set_rx_address_pipe1(uint8_t addr_lsb)
{
    OM_RF->RX_ADDR_P1 = addr_lsb;
}
void drv_rf_set_rx_address_pipe2(uint8_t addr_lsb)
{
    OM_RF->RX_ADDR_P2 = addr_lsb;
}
void drv_rf_set_tx_address(const uint8_t addr[5])
{
    uint32_t lo4;
    memcpy(&lo4, addr, 4);
    OM_RF->TX_ADDR = lo4;
    OM_RF->TX_ADDR_H = addr[4];
}

void drv_rf_get_rx_address_pipe0(uint8_t addr[5])
{
    uint32_t lo4;
    lo4 = OM_RF->RX_ADDR_P0;
    memcpy(addr, &lo4, 4);
    addr[4] = OM_RF->RX_ADDR_P0_H;
}
uint8_t drv_rf_get_rx_address_pipe1(void)
{
    return OM_RF->RX_ADDR_P1;
}
uint8_t drv_rf_get_rx_address_pipe2(void)
{
    return OM_RF->RX_ADDR_P2;
}
void drv_rf_get_tx_address(uint8_t addr[5])
{
    uint32_t lo4;
    lo4 = OM_RF->TX_ADDR;
    memcpy(addr, &lo4, 4);
    addr[4] = OM_RF->TX_ADDR_H;
}

void drv_rf_enable_pipe(uint8_t bitmask)
{
    OM_RF->EN_RXADDR |= bitmask;
}

void drv_rf_disable_pipe(uint8_t bitmask)
{
    OM_RF->EN_RXADDR &= ~bitmask;
}

void drv_rf_enable_pipe_auto_ack(uint8_t bitmask)
{
    OM_RF->EN_AA |= bitmask;
}

void drv_rf_disable_pipe_auto_ack(uint8_t bitmask)
{
    OM_RF->EN_AA &= ~bitmask;
}

void drv_rf_enable_pipe_dynamic_payload_length(uint8_t bitmask)
{
    OM_RF->DYNPD |= bitmask;
}

void drv_rf_disable_pipe_dynamic_payload_length(uint8_t bitmask)
{
    OM_RF->DYNPD &= ~bitmask;
}

bool drv_rf_is_pipe_dynamic_payload_length(uint8_t pipe_no)
{
    return OM_RF->DYNPD & (1 << pipe_no) ? true : false;
}

uint8_t drv_rf_get_rx_pipe_no(void)
{
    /* return 0,1,2,3. 3 means rx fifo empty. */
    return (OM_RF->RF_STATUS & STATUS_RX_P_NO_Msk) >> STATUS_RX_P_NO_Pos;
}

void drv_rf_set_auto_retry_param(uint16_t delay_us, uint8_t count)
{
    /* .ARD: b'0000=250us b'0001=500us */
    OM_RF->SETUP_RETR = ((delay_us >> 4) & 0xf0) | count;
}

void drv_rf_enable_whitening(void)
{
    OM_RF->EN_RXADDR |= (1u << 3)/*scramble_en*/;
}
void drv_rf_disable_whitening(void)
{
    OM_RF->EN_RXADDR &= ~(1u << 3);
}

void drv_rf_enable_rx(void)
{
    OM_RF->CONFIG |= CONFIG_PRIM_RX;
}

void drv_rf_disable_rx(void)
{
    OM_RF->CONFIG &= ~CONFIG_PRIM_RX;
}

void drv_rf_enable_crc(void)
{
    OM_RF->CONFIG |= CONFIG_EN_CRC;
}

void drv_rf_disable_crc(void)
{
    OM_RF->CONFIG &= ~CONFIG_EN_CRC;
}

void drv_rf_enable_tx_guard(void)
{
    OM_RF->CONFIG |= CONFIG_EN_TX_GUARD;
}
void drv_rf_disable_tx_guard(void)
{
    OM_RF->CONFIG &= ~CONFIG_EN_TX_GUARD;
}

uint8_t drv_rf_get_and_clear_irq_status(void)
{
    uint8_t status = OM_RF->RF_STATUS;
    #if 1
    /* RF->ABORT is clear by HW since FPGA 03/28. */
    #else
    /* Workaround: restore to support MD. */
    OM_RF->BLE_CTL &= ~BLE_CTL_EVENT_ABORT;
    #endif
    /* w1c. */
    OM_RF->RF_STATUS = status & (IRQ_STATUS_EVT_DS | IRQ_STATUS_RX_DR | IRQ_STATUS_TX_DS | IRQ_STATUS_SYNC_DS | IRQ_STATUS_RX_TIMEOUT);
    return status;
}

uint8_t drv_rf_get_irq_status(void)
{
    return OM_RF->RF_STATUS;
}

bool drv_rf_rx_fifo_is_empty(void)
{
    return OM_RF->FIFO_STATUS & FIFO_STATUS_RX_EMPTY ? true : false;
}
bool drv_rf_rx_fifo_is_full(void)
{
    return OM_RF->FIFO_STATUS & FIFO_STATUS_RX_FULL ? true : false;
}
bool drv_rf_tx_fifo_is_empty(void)
{
    return OM_RF->FIFO_STATUS & FIFO_STATUS_TX_EMPTY ? true : false;
}
bool drv_rf_tx_fifo_is_full(void)
{
    return OM_RF->FIFO_STATUS & FIFO_STATUS_TX_FULL ? true : false;
}
bool drv_rf_tx_fifo_is_reuse(void)
{
    return OM_RF->FIFO_STATUS & FIFO_STATUS_TX_REUSE ? true : false;
}

uint8_t drv_ble_tx_fifo_idx(void)
{
    return rf_env.tx_fifo_idx;
}

void drv_rf_enable_dynamic_ack(void)
{
    OM_RF->FEATURE |= FEATURE_EN_DYN_ACK;
}
void drv_rf_disable_dynamic_ack(void)
{
    OM_RF->FEATURE &= ~FEATURE_EN_DYN_ACK;
}
void drv_rf_enable_ack_payload(void)
{
    OM_RF->FEATURE |= FEATURE_EN_ACK_PAY;
}
void drv_rf_disable_ack_payload(void)
{
    OM_RF->FEATURE &= ~FEATURE_EN_ACK_PAY;
}
void drv_rf_enable_dynamic_payload_length(void)
{
    OM_RF->FEATURE |= FEATURE_EN_DPL;
}
void drv_rf_disable_dynamic_payload_length(void)
{
    OM_RF->FEATURE &= ~FEATURE_EN_DPL;
}

void drv_ble_set_crc_init(uint32_t crcinit)
{
    OM_RF->CRC_INIT = crcinit;
}

void drv_ble_set_access_address(uint32_t aa)
{
    OM_RF->ACCESS_ADDR = aa;
}

void drv_ble_set_chn_idx(uint8_t chn_idx)
{
    /* Offset to 2400 in 2MHz. */
    int off_2mhz = 1;

    //drv_uart0_put_char(chn_idx);
    if (chn_idx <= 10) {
        off_2mhz = chn_idx + 2;
    } else if (chn_idx <= 36) {
        off_2mhz = chn_idx + 3;
    }

    if (chn_idx == 37) {
        off_2mhz = 1;
    }
    if (chn_idx == 39) {
        off_2mhz = 40;
    }
    if (chn_idx == 38) {
        off_2mhz = 13;
    }

    OM_RF->RF_CH = off_2mhz*2;
}

void drv_ble_conn_set_chn_idx(uint8_t chn_idx)
{
    uint8_t rf_ch;

    //drv_uart0_put_char(chn_idx);
    if (chn_idx <= 10) {    /* [0 10] corresponding to [2404 2424] MHz*/
        rf_ch = (chn_idx<<1) + 4;
    } else if (chn_idx <= 36) {
        rf_ch = (chn_idx<<1) + 6;   /* [11 36] corresponding to [2428 2478] MHz */
    }

    OM_RF->RF_CH = rf_ch;
}

void drv_ble_set_bda(const uint8_t *bda)
{
    uint32_t adva;
    memcpy(&adva, bda, 4);
    OM_RF->TX_ADVA = adva;
    adva = 0;
    memcpy(&adva, bda+4, 2);
    OM_RF->TX_ADVA_H = adva;
}

void drv_ble_get_bda(uint8_t bda[6])
{
    uint32_t tx_addr[2];
    tx_addr[0] = OM_RF->TX_ADVA;
    tx_addr[1] = OM_RF->TX_ADVA_H;
    memcpy(bda, tx_addr, 6);
}

void drv_ble_set_whitelist(uint8_t entry, uint8_t bda[6])
{
    __IO uint32_t *regl = &OM_RF->WHITELIST0;
    __IO uint32_t *regh = &OM_RF->WHITELIST0_H;
    if (1 == entry) {
        regl += 2;
        regh += 2;
    }

    *regl = *(uint32_t *)(&bda[0]);   /*lint !e2445*/
    *regh = *(uint32_t *)(&bda[4]);   /*lint !e2445*/
}

void drv_ble_enable_whitelist(void)
{
    OM_RF->WHITELIST_CR = 0x1;
}

void drv_ble_disable_whitelist(void)
{
    OM_RF->WHITELIST_CR = 0x0;
}

void drv_ble_set_adv_ind(const uint8_t *p_advdata, uint8_t len, bool is_random)
{
    OM_RF->TX_HEADER[0] = ((len+6) << 8) | (is_random ? 0x40/* TxAdd=1 Random Address */ : 0x00) | 0x0;
    /* .AdvData */
    if (len > 0) {
        fill_tx_fifo(p_advdata, len);
    }
}

void drv_ble_set_scan_rsp(const uint8_t *p_advdata, uint8_t len, bool is_random)
{
    if (NULL == p_advdata) {
        /* no SCAN_RSP for non-discoverable mode. */
        OM_RF->TX_HEADER[1] = 0x0000;
        return;
    }
    OM_RF->TX_HEADER[1] = ((len+6) << 8) | (is_random ? 0x40/* TxAdd=1 Random Address */ : 0x00) | 0x4;
    /* .AdvData */
    if (len > 0) {
        fill_tx_fifo(p_advdata, len);
    }
}

void drv_ble_set_scan_req(const uint8_t *p_advdata, uint8_t len, bool is_random)
{
    if (NULL == p_advdata) {
        OM_RF->TX_HEADER[0] = 0x0000;
        return;
    }
    OM_RF->TX_HEADER[0] = ((len+6) << 8) | (is_random ? 0x40/* TxAdd=1 Random Address */ : 0x00) | 0x3;
    /* .AdvData */
    if (len > 0) {
        fill_tx_fifo(p_advdata, len);
    }
}
void drv_ble_set_connect_ind(uint8_t *buf)
{
    OM_RF->TX_HEADER[0] = (buf[1] << 8) | buf[0];
    /* .AdvData */
    fill_tx_fifo(buf+8, buf[1]-6/* 减去adva长度*/);
}

void drv_ble_set_adv_pkt_len(uint8_t len)
{
    uint16_t hdr = OM_RF->TX_HEADER[0];
    hdr = (len << 8) | (hdr & 0x00FF);
    OM_RF->TX_HEADER[0] = hdr;
}
void drv_ble_set_adv_pkt_type(uint8_t type)
{
    uint16_t hdr = OM_RF->TX_HEADER[0];
    hdr = (hdr & 0xFFF0) | (type << 0);
    OM_RF->TX_HEADER[0] = hdr;
}

/**
 * @brief Set the schedule time of an BLE event.
 * @param [in] tick_abs - The absolute tick of BLE event start:
 *                        anchor point - wakeup time - RF setup time.
 * @param [in] tick_timeout - The receive window size in ticks:
 *                            0 for adv event.
 */
void drv_ble_set_alarm2rf(uint32_t tick_abs, uint32_t tick_timeout)
{
    /* Don't consider wakeup time here. */
    uint32_t tick = tick_abs - DRV_RF_TX_SETUP_TIME_TICK;
    /* If overwrite the previous tick, SW must guarantee the delta of two ticks > 100+us */
    drv_rtc_control(OM_RTC, RTC_CONTROL_SET_ALARM1, (void* )tick);
    if ((tick - drv_rtc_read(OM_RTC)) >= (1U << 31U)) {
        //printf(" now=%x %x\n", drv_rtc_read(OM_RTC), tick);
        //drv_uart0_put_char(0xa2);
        while(1);
        /* Allow debug via SWD during adv. */
        //tick_abs = drv_rtc_read(OM_RTC) + 10*32;
        drv_rtc_control(OM_RTC, RTC_CONTROL_SET_ALARM1, (void* )tick_abs);
    }
    if (0 == tick_timeout) {
        return;
    }

    /* Workaround: Wait alarm2 expires, then a new alarm2 value is set. */
    //while (drv_rtc_read(OM_RTC) < (OM_RTC->ALARM2+4));
    drv_rtc_control(OM_RTC, RTC_CONTROL_SET_ALARM2, (void* )(tick_abs + tick_timeout + DRV_RF_TX_SETUP_TIME_TICK));
}

void drv_ble_set_state_adv(void)
{
    OM_RF->DFIFO_EN = 1;
    OM_RF->BLE_CTL = BLE_CTL_FMT_ADV;
}

void drv_ble_set_state_conn_slave(void)
{
    OM_RF->DFIFO_EN = 1;
    OM_RF->BLE_CTL = BLE_CTL_FMT_CONN_SLAVE;
    /* Flush the adv packets in tx fifos to avoid as data packet in conn state. */
    drv_rf_reset_tx_fifo();
    /* Always receive the 1st data packet into rx fifo 0. */
    drv_rf_reset_rx_fifo();
}

void drv_ble_set_state_conn_master(void)
{
    OM_RF->DFIFO_EN = 1;

    OM_RF->CONFIG = CONFIG_MASK_RX_DR | CONFIG_MASK_TX_DS | CONFIG_MASK_SYNC_DS | CONFIG_EN_CRC | CONFIG_MASK_RX_TIMEOUT;

    OM_RF->BLE_CTL = BLE_CTL_FMT_CONN_MASTER;
    /* Flush the adv packets in tx fifos to avoid as data packet in conn state. */
    drv_rf_reset_tx_fifo();
    /* Always receive the 1st data packet into rx fifo 0. */
    drv_rf_reset_rx_fifo();
}

void drv_ble_set_state_scan(void)
{
    OM_RF->BLE_CTL = BLE_CTL_FMT_SCAN_ACTIVE;
}
void drv_ble_set_state_rxtest(void)
{
    OM_RF->BLE_CTL = BLE_CTL_FMT_RXTEST;
}
void drv_ble_set_state_txtest(void)
{
    OM_RF->BLE_CTL = BLE_CTL_FMT_TXTEST;
}
void drv_ble_set_state_rx2tx(void)
{
    OM_RF->DFIFO_EN = 0;
    OM_RF->BLE_CTL = BLE_CTL_MD_DISABLE | BLE_CTL_FC_DISABLE | BLE_CTL_INFINITE_RX | BLE_CTL_FMT_CONN_SLAVE;
}
void drv_ble_set_state_tx2rx(void)
{
    OM_RF->DFIFO_EN = 0;
    OM_RF->BLE_CTL = BLE_CTL_MD_DISABLE | BLE_CTL_FC_DISABLE | BLE_CTL_FMT_CONN_MASTER;
}
void drv_ble_start_event(void)
{
    OM_RF->CE_PULSE = 1;
}

bool drv_ble_dev_is_master(void)
{
    uint8_t type = OM_RF->BLE_CTL & 0x0f;
    if((type == BLE_CTL_FMT_CONN_MASTER) || (type == BLE_CTL_FMT_SCAN_ACTIVE)) {
        return true;  
    } else {
        return false;
    }
}

void drv_ble_abort_event(void)
{
    /* It cannot abort ADV state;
       it will use single packet rx/tx mode for CONN state;
       it can abort SCAN state but cannot abort the received fsm. */
    #if 1
    /* It is clear by HW when event done interupt raises. */
    OM_RF->ABORT = 1;
    #else
    OM_RF->BLE_CTL |= BLE_CTL_EVENT_ABORT;
    /* Don't clear this bit at once, otherwise it won't abort. */
    //OM_RF->BLE_CTL &= ~BLE_CTL_EVENT_ABORT;
    #endif
}

void drv_ble_cancel_abort(void)
{
    OM_RF->ABORT = 0;
}

void drv_ble_start_tx_adv(void)
{
    // OM_RF->BLE_CTL = BLE_CTL_FMT_ADV;
    OM_RF->CE_PULSE = 1;
}
void drv_ble_start_active_scan(void)
{
    OM_RF->CONFIG = CONFIG_MASK_TX_DS | CONFIG_MASK_SYNC_DS | CONFIG_EN_CRC;
    OM_RF->BLE_CTL = BLE_CTL_FMT_SCAN_ACTIVE;
    OM_RF->CE_PULSE = 1;
}
void drv_ble_start_passive_scan(void)
{
    OM_RF->CONFIG = CONFIG_MASK_TX_DS | CONFIG_MASK_SYNC_DS | CONFIG_EN_CRC;
    OM_RF->BLE_CTL = BLE_CTL_FMT_SCAN_PASSIVE;
    //OM_RF->BLE_CTL = BLE_CTL_FMT_SCAN_PASSIVE | BLE_CTL_INFINITE_RX;
    OM_RF->CE_PULSE = 1;
}
void drv_ble_start_tx_test(void)
{
    OM_RF->BLE_CTL = BLE_CTL_FMT_TXTEST;
    OM_RF->CE_PULSE = 1;
}
void drv_ble_start_rx_test(void)
{
    OM_RF->BLE_CTL = BLE_CTL_FMT_RXTEST;
    OM_RF->CE_PULSE = 1;
}

bool drv_ble_is_event_done(uint8_t status)
{
    return status & IRQ_STATUS_EVT_DS ? true : false;
}
bool drv_ble_is_received(uint8_t status)
{
    return status & IRQ_STATUS_RX_DR ? true : false;
}
bool drv_ble_is_tx_done(uint8_t status)
{
    return status & IRQ_STATUS_TX_DS ? true : false;
}
bool drv_ble_is_synced(uint8_t status)
{
    return status & IRQ_STATUS_SYNC_DS ? true : false;
}
bool drv_ble_is_state_adv(void)
{
    uint8_t state = OM_RF->BLE_CTL & 0x0F;
    return BLE_CTL_FMT_ADV == state ? true : false;
}
bool drv_ble_is_state_conn(void)
{
    uint8_t state = OM_RF->BLE_CTL & 0x0F;
    return BLE_CTL_FMT_CONN_SLAVE == state ? true : false;
}
bool drv_ble_is_state_scan(void)
{
    uint8_t state = OM_RF->BLE_CTL & 0x0F;
    if ((BLE_CTL_FMT_SCAN_ACTIVE == state) ||
            (BLE_CTL_FMT_SCAN_PASSIVE == state)) {
        return true;
    } else {
        return false;
    }
}
bool drv_ble_is_state_rxtest(void)
{
    uint8_t state = OM_RF->BLE_CTL & 0x0F;
    return BLE_CTL_FMT_RXTEST == state ? true : false;
}
bool drv_ble_is_state_txtest(void)
{
    uint8_t state = OM_RF->BLE_CTL & 0x0F;
    return BLE_CTL_FMT_RXTEST == state ? true : false;
}

uint8_t drv_ble_get_rxed_pkt_bitmap(void)
{
    return OM_RF->DFIFO_STATUS & ((1 << DRV_RF_FIFO_LEVEL)-1);
}
bool drv_ble_is_rx_timeout(uint8_t status)
{
    return status & IRQ_STATUS_RX_TIMEOUT ? true : false;
}
/* HW will abort connect event once received an CRC error. */
bool drv_ble_is_crc_err(int pkt_idx)
{
    return OM_RF->RX_STATUS[pkt_idx] & (BLE_STATUS_CRCERR | BLE_STATUS_LENERR | BLE_STATUS_TYPEERR | BLE_STATUS_SYNERR) ? true : false;
}
bool drv_ble_is_sn_err(int pkt_idx)
{
    return OM_RF->RX_STATUS[pkt_idx] & BLE_STATUS_SNERR ? true : false;
}
bool drv_ble_is_nesn_err(int pkt_idx)
{
    return OM_RF->RX_STATUS[pkt_idx] & BLE_STATUS_NESNERR ? true : false;
}
bool drv_ble_get_data_pkt(int pkt_idx, uint8_t *p_pkt)
{
    uint16_t hdr;
    uint8_t len;

    /* return false if rx fifo idx is empty. */
    if (0 == (OM_RF->DFIFO_STATUS & (0x1 << pkt_idx))) {
        return false;
    }

    hdr = OM_RF->RX_HEADER[pkt_idx];
    memcpy(p_pkt, &hdr, 2);
    len = p_pkt[1];
    /* Always read rx fifo even if length is zero. */
    read_rx_fifo(p_pkt+2, len);
    return true;
}

bool drv_ble_get_adv_pkt(int pkt_idx, uint8_t *p_pkt)
{
    uint32_t adva;
    uint16_t hdr;
    uint8_t len;

    /* return false if rx fifo idx is empty. */
    if (0 == (OM_RF->DFIFO_STATUS & (0x1 << pkt_idx))) {
        return false;
    }

    /* .AdvA */
    adva = OM_RF->RX_ADVA;
    hdr  = OM_RF->RX_ADVA_H;
    memcpy(p_pkt+2, &adva, 4);
    memcpy(p_pkt+2+4, &hdr, 2);
    /* .Header */
    hdr = OM_RF->RX_HEADER[pkt_idx];
    memcpy(p_pkt, &hdr, 2);
    len = p_pkt[1];
    /* .AdvData */
    if (len > 6) {
        len -= 6;
        read_rx_fifo(p_pkt+2+6, len);
    }
    return true;
}

void drv_ble_read_data_pkt(uint8_t *pkt, uint8_t len)
{
    read_rx_fifo(pkt, len);
}

uint32_t drv_ble_get_anchor_tick(void)
{
    /* ygw: the reg sync time since AA synced is ~100us. */
    /* 26us wait in orf2usb's RF_IRQHandler() */
    /* Comment this poll wait because it is called in isr lazy as possible. */
    while (!OM_RTC->CLKN_VALID);
    /* hs6220 0+32+62us: PRE1+AA4 + alg sync cost + 32k sync cost. =4 */
    return OM_RTC->CLKN_SYNC - US_TO_TICK(0+32+62);
}

bool drv_ble_tx_is_last_empty(int pkt_idx)
{
    return OM_RF->RX_STATUS[pkt_idx] & BLE_STATUS_LASTEMPTY ? true : false;
}

bool drv_ble_tx_fifo_is_full(void)
{
    return OM_RF->DFIFO_STATUS & (0x1 << (DRV_RF_FIFO_LEVEL + rf_env.tx_fifo_idx));
}

bool drv_ble_tx_fifo_is_empty(void)
{
    return (OM_RF->DFIFO_STATUS & 0x38) ? false : true;
}

void drv_ble_put_data_pkt(uint8_t *p_pkt)
{
    uint16_t hdr;
    uint8_t len;

    memcpy(&hdr, p_pkt, 2);
    len = p_pkt[1];

    if (0 != len) {
        fill_tx_fifo(p_pkt+2, len);
    }
    OM_RF->TX_HEADER[rf_env.tx_fifo_idx] = hdr;

    if (rf_env.tx_fifo_idx < (DRV_RF_FIFO_LEVEL - 1)) {
        rf_env.tx_fifo_idx++;
    } else {
        rf_env.tx_fifo_idx = 0;
    }
}

bool drv_ble_put_adv_pkt(int pkt_idx, uint8_t *p_pkt)
{
    uint32_t adva;
    uint16_t hdr;
    uint8_t len;

    /* return false if tx fifo idx is full. */
    if (0 != (OM_RF->DFIFO_STATUS & (0x1 << (DRV_RF_FIFO_LEVEL+pkt_idx)))) {
        return false;
    }

    /* .AdvA */
    memcpy(&adva, p_pkt+2, 4);
    memcpy(&hdr,  p_pkt+2+4, 2);
    OM_RF->TX_ADVA = adva;
    OM_RF->TX_ADVA_H = hdr;
    /* .Header */
    memcpy(&hdr, p_pkt, 2);
    OM_RF->TX_HEADER[pkt_idx] = hdr;
    len = p_pkt[1];
    /* .AdvData */
    if (len > 6) {
        len -= 6;
        fill_tx_fifo(p_pkt+2+6, len);
    }
    return true;
}
bool drv_ble_put_test_pkt(uint8_t *p_pkt)
{
    uint16_t hdr;
    uint8_t len;
    /* HW will cascade 3-level FIFO into one for tx/rx test mode. */
    int pkt_idx = 0;

    /* Disable multi-level FIFO for bigger (>31) test packet,
       and don't check DFIFO_STATUS later. */
    OM_RF->DFIFO_EN = 0;
    /* Flush the existing data before refill the new data. */
    drv_rf_reset_tx_fifo();

    memcpy(&hdr, p_pkt, 2);
    OM_RF->TX_HEADER[pkt_idx] = hdr;
    len = p_pkt[1];
    if (0 != len) {
        fill_tx_fifo(p_pkt+2, len);
        drv_rf_reuse_tx_fifo();
    }
    return true;
}
void drv_ble_put_test_payload(const uint8_t *p_payload, uint8_t data_type, uint8_t length)
{
    /* Flush the existing data before refill the new data. */
    drv_rf_reset_tx_fifo();

    //OM_RF->TX_HEADER[0] = (length << 8) | 0x00/*PRBS9*/;
    OM_RF->TX_HEADER[0] = (length << 8) | data_type/*all 0*/;
    //drv_uart0_put_char(length);
    if (0 != length) {
        fill_tx_fifo(p_payload, length);
        drv_rf_reuse_tx_fifo();
    }
}
uint8_t drv_ble_get_test_payload(uint8_t *p_payload)
{
    uint8_t length;

    if (drv_ble_is_crc_err(0)) {
        //flush_rx_fifo();
        return 0;
    }
    length = OM_RF->RX_HEADER[0] >> 8;
    //drv_uart0_put_char(length);
    /* Always read rx fifo even if length is zero. */
    read_rx_fifo(p_payload, length);
    return length;
}

void drv_rf_cleanup(void)
{
    drv_rf_reset_rx_fifo();
    drv_rf_reset_tx_fifo();
    drv_rf_get_and_clear_irq_status();
}

uint16_t drv_rf_get_fsm(void)
{
    return OM_RF->STATE;
}

void drv_rf_switch_bank(uint8_t bank_no)
{
    /* dummy */
}

uint16_t drv_rf_get_chipID(void)
{
    return OM_RF->LINE;
}

void drv_rf_dump_all_register(void)
{
    #if 0
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_RF, 1U);
    printf("DFIFO_EN    : %02x\r\n", OM_RF->DFIFO_EN    );
    printf("CONFIG      : %02x\r\n", OM_RF->CONFIG      );
    printf("EN_AA       : %02x\r\n", OM_RF->EN_AA       );
    printf("EN_RXADDR   : %02x\r\n", OM_RF->EN_RXADDR   );
    printf("SETUP_RETR  : %02x\r\n", OM_RF->SETUP_RETR  );
    printf("RF_CH       : %02x\r\n", OM_RF->RF_CH       );
    printf("RF_SETUP    : %02x\r\n", OM_RF->RF_SETUP    );
    printf("RSSI        : %02x\r\n", OM_RF->RSSI        );
    printf("RX_ADDR_P0  : %08x\r\n", OM_RF->RX_ADDR_P0  );
    printf("RX_ADDR_P0_H: %02x\r\n", OM_RF->RX_ADDR_P0_H);
    printf("RX_ADDR_P1  : %02x\r\n", OM_RF->RX_ADDR_P1  );
    printf("RX_ADDR_P2  : %02x\r\n", OM_RF->RX_ADDR_P2  );
    printf("TX_ADDR     : %08x\r\n", OM_RF->TX_ADDR     );
    printf("TX_ADDR_H   : %02x\r\n", OM_RF->TX_ADDR_H   );
    printf("RX_PW/DPL   : %02x\r\n", OM_RF->RX_PW);
    printf("RX_PW_P0    : %02x\r\n", OM_RF->RX_PW_PIPE[0]);
    printf("RX_PW_P1    : %02x\r\n", OM_RF->RX_PW_PIPE[1]);
    printf("RX_PW_P2    : %02x\r\n", OM_RF->RX_PW_PIPE[2]);
    printf("FIFO_STATUS : %02x\r\n", OM_RF->FIFO_STATUS );
    printf("DYNPD       : %02x\r\n", OM_RF->DYNPD       );
    printf("FEATURE     : %02x\r\n", OM_RF->FEATURE     );
    printf("SETUP_VALUE : %06x\r\n", OM_RF->SETUP_V     );
    printf("PRE_GURD    : %04x\r\n", OM_RF->PRE_GURD    );
    printf("PLL_CTL0    : %08x\r\n", OM_RF->PLL_CTL0    );
    printf("PLL_CTL1    : %06x\r\n", OM_RF->PLL_CTL1    );
    printf("CAL_CTL     : %08x\r\n", OM_RF->CAL_CTL     );
    printf("STATE       : %04x\r\n", OM_RF->STATE       );
    printf("CHAN        : %08x\r\n", OM_RF->CHAN        );
    printf("FDEV        : %02x\r\n", OM_RF->FDEV        );
    printf("DAC_RANGE   : %02x\r\n", OM_RF->DAC_RANGE   );
    printf("CTUNING     : %04x\r\n", OM_RF->CTUNING     );
    printf("FTUNING     : %04x\r\n", OM_RF->FTUNING     );
    printf("RX_CTRL     : %04x\r\n", OM_RF->RX_CTRL     );
    printf("FAGC_CTRL_1 : %08x\r\n", OM_RF->FAGC_CTRL_1 );
    printf("DOC_DACI    : %04x\r\n", OM_RF->DOC_DACI    );
    printf("DOC_DACQ    : %04x\r\n", OM_RF->DOC_DACQ    );
    printf("AGC_CTRL    : %06x\r\n", OM_RF->AGC_CTRL    );
    printf("AGC_GAIN    : %04x\r\n", OM_RF->AGC_GAIN    );
    printf("RF_IVGEN    : %06x\r\n", OM_RF->RF_IVGEN    );
    printf("TEST_PKDET  : %06x\r\n", OM_RF->TEST_PKDET  );
    #endif
}

/** @} */
