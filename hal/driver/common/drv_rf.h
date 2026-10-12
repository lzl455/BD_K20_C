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
 * @file   drv_hlp_rf.h
 * @brief  RF (2.4G and BLE) helper driver header.
 * @note   The APIs are inline macros or small routines to reduce code size.
 *
 * @addtogroup PANACEA
 * @{
 */
#ifndef _DRV_RF_H_
#define _DRV_RF_H_

#include <stdbool.h>

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/
/* FPGA since 2022/01/24. */
#define DRV_RF_FIFO_LEVEL           3

#define DRV_RF_PA_PWR_8dBm          (0x1F)
#define DRV_RF_PA_PWR_5dBm          (0x10)
#define DRV_RF_PA_PWR_4dBm          (0x0F)
#define DRV_RF_PA_PWR_2dBm          (8)
#define DRV_RF_PA_PWR_0dBm          (6)
#define DRV_RF_PA_PWR_N6dBm         (3)
#define DRV_RF_PA_PWR_N12dBm        (2)
#define DRV_RF_PA_PWR_N16dBm        (1)
#define DRV_RF_PA_PWR_N43dBm        (0)

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
/**
 * @brief The date rate bit per second.
 * @ref drv_rf24g_init()
 */
#define DRV_RF_DATE_RATE_1Mbps      0
#define DRV_RF_DATE_RATE_2Mbps      1

/**
 * @brief The definitions of pipe number.
 * @ref drv_rf_get_rx_pipe_no().
 */
#define DRV_RF_PIPE_NO_MAX          3
#define DRV_RF_PIPE_NO_RX_EMPTY     3
#define DRV_RF_PIPE_ALL_BITMASK     ((1U << (DRV_RF_PIPE_NO_MAX+0)) - 1)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Select MAC layer for 2.4G or BLE.
 */
void drv_rf_select_24g(void);
void drv_rf_select_ble(void);
/**
 * @brief  Check the work mode of the radio
 * @param  None
 * @return true means the work mode is ble
 *         false means the mode is 2.4G
 */
bool drv_rf_is_ble_mode(void);

/**
 * @brief  Initialize RF module for BLE, including calibration.
 * @note   Obsoleted.
 */
void drv_ble_init(void);
/**
 * @brief the 2.4G radio mode init.
 * @note   Obsoleted.
 */
void drv_rf24g_init(void);

/**
 * @brief  Set RF tx power level at dBm.
 * @param [in] pwr - @refer DRV_RF_PA_PWR_xxx.
 */
void drv_rf_set_tx_power(uint8_t pwr);
int8_t drv_rf_get_rssi(void);

/**
 * @brief  Set physical layer mode in 1Mbps or 2Mbps.
 */
void drv_rf_set_phy_mode_1mbps(void);
void drv_rf_set_phy_mode_2mbps(void);

/**
 * @brief  Set frequency channel at 2400MHz band, 1MHz/channel.
 * @param [in] channel - frequency channel [0,80]
 */
void drv_rf_set_channel(uint8_t channel);

/**
 * @brief  Adjust RF XTAL's capacity.
 * @param [in] tune - The tune value.
 */
void drv_rf_adjust_xtal(uint8_t tune);

/**
 * @brief  Enable/Disable the specific interrupts for BLE test or 2.4G.
 * @param [in] bitmask - The bitmask of interrupts.
 */
void drv_rf_enable_interrupt(uint8_t bitmask);
void drv_rf_disable_interrupt(uint8_t bitmask);

/**
 * @brief  Enable/Disable whitening for BLE, scramble for 2.4G.
 */
void drv_rf_enable_whitening(void);
void drv_rf_disable_whitening(void);

/**
 * @brief  Set initial CRC seed for BLE.
 * @param [in] crcinit - The initial CRC seed.
 */
void drv_ble_set_crc_init(uint32_t crcinit);

/**
 * @brief  Set Access Address for BLE.
 * @param [in] aa - Access Address.
 */
void drv_ble_set_access_address(uint32_t aa);

/**
 * @brief  Set BLE's channel index.
 * @param [in] chn_idx - channel index [0,39]
 */
void drv_ble_conn_set_chn_idx(uint8_t chn_idx);

/**
 * @brief  Set the local Bluetooth Device Address.
 * @param [in] bda - Bluetooth Device Address in 6-byte.
 */
void drv_ble_set_bda(const uint8_t *bda);

/**
 * @brief  Get the local Bluetooth Device Address.
 * @param [out] bda - Bluetooth Device Address in 6-byte.
 */
void drv_ble_get_bda(uint8_t bda[6]);

/**
 * @brief  Set the peer Bluetooth Device Address into whitelist.
 * @note   Filter for BLE scan and conn.
 * @param [in[ entry - The entry index of whitelist: [0,1]
 * @param [in] bda - Bluetooth Device Address in 6-byte.
 */
void drv_ble_set_whitelist(uint8_t entry, uint8_t bda[6]);
/**
 * @brief  Enable/Disable whitelist.
 */
void drv_ble_enable_whitelist(void);
void drv_ble_disable_whitelist(void);

/**
 * @brief  Set ADV_IND and SCAN_RSP packets for BLE broadcast.
 * @param [in] p_advdata - .AdvData field.
 * @param [in] len       - The length of .AdvData field.
 * @param [in] is_random - .TxAdd field: false=public true=random
 */
void drv_ble_set_adv_ind(const uint8_t *p_advdata, uint8_t len, bool is_random);
void drv_ble_set_scan_rsp(const uint8_t *p_advdata, uint8_t len, bool is_random);
void drv_ble_set_scan_req(const uint8_t *p_advdata, uint8_t len, bool is_random);

/**
 * @brief  Set/Update the length of BLE adv packet.
 * @param [in] len - The length of adv packet.
 */
void drv_ble_set_adv_pkt_len(uint8_t len);
/**
 * @brief  Set/Update the type of BLE adv packet.
 * @param [in] type - adv packet type: [ADV_IND, AUX_CONNECT_RSP].
 */
void drv_ble_set_adv_pkt_type(uint8_t type);

/**
 * @brief  Set the schedule time of an BLE event.
 * @param [in] tick_abs - The absolute tick of BLE event start:
 *                        anchor point - wakeup time - RF setup time.
 * @param [in] tick_timeout - The receive window size in ticks:
 *                            0 for adv event.
 */
void drv_ble_set_alarm2rf(uint32_t tick_abs, uint32_t tick_timeout);

/**
 * @brief  Set BLE state to advertising/connect/scan/rx test/tx test.
 */
void drv_ble_set_state_adv(void);
void drv_ble_set_state_conn_slave(void);
void drv_ble_set_state_scan(void);
void drv_ble_set_state_rxtest(void);
void drv_ble_set_state_txtest(void);
/**
 * @brief  Set BLE state to rx2tx/tx2rx to simulate Gazell protocol.
 */
void drv_ble_set_state_rx2tx(void);
void drv_ble_set_state_tx2rx(void);

/**
 * @brief  Start BLE event with the current BLE state.
 */
void drv_ble_start_event(void);

void drv_ble_abort_event(void);

void drv_ble_cancel_abort(void);

/**
 * @brief  Check current BLE state whether is advertising/connect/scan/rx test/tx test.
 * @return true/false.
 */
bool drv_ble_is_state_adv(void);
bool drv_ble_is_state_conn(void);
bool drv_ble_is_state_scan(void);
bool drv_ble_is_state_rxtest(void);
bool drv_ble_is_state_txtest(void);

/**
 * @brief  Start BLE event with the specific BLE state.
 */
void drv_ble_start_tx_adv(void);
void drv_ble_start_active_scan(void);
void drv_ble_start_passive_scan(void);
void drv_ble_start_tx_test(void);
void drv_ble_start_rx_test(void);

/**
 * @brief  When BLE/2.4G interrupt raises, get the interrupt status then clear.
 * @return The interrupt status.
 */
uint8_t drv_rf_get_and_clear_irq_status(void);

/**
 * @brief  Check BLE interrupt status: BLE event is done,
 *                                     BLE packet is received,
 *                                     receive timeout in TIFS or in alarm2rf timeout.
 * @param [in] status - The interrupt status.
 */
bool drv_ble_is_event_done(uint8_t status);
bool drv_ble_is_received(uint8_t status);
bool drv_ble_is_rx_timeout(uint8_t status);
bool drv_ble_is_synced(uint8_t status);

/**
 * @brief  Get the received status of rx fifos.
 * return 0x0 - all are empty.
 *        0x1 - rx fifo 0 is received (full).
 *        0x2 - rx fifo 1 is received (full).
 *        0x3 - rx fifo 0 & 1 are received (full).
 */
uint8_t drv_ble_get_rxed_pkt_bitmap(void);

/**
 * @brief  Check the received packet is CRC error.
 * @param [in] pkt_idx - rx fifo 0 or 1.
 * @return true is wrong packet, false is good packet.
 */
bool drv_ble_is_crc_err(int pkt_idx);

/**
 * @brief  Check the received packet is BLE SN/NESR error.
 * @param [in] pkt_idx - rx fifo 0 or 1.
 * @return true is error for retransmisson packet or NAK.
 *         false is good hardware flow control.
 */
bool drv_ble_is_sn_err(int pkt_idx);
bool drv_ble_is_nesn_err(int pkt_idx);

/**
 * @brief  Get the received BLE data/adv packet.
 * @param [in] pkt_idx - rx fifo 0 or 1.
 * @param [in/out] p_pkt - The pointer to BLE packet.
 * @return true is received.
 *         false is not received.
 */
bool drv_ble_get_data_pkt(int pkt_idx, uint8_t *p_pkt);
bool drv_ble_get_adv_pkt(int pkt_idx, uint8_t *p_pkt);
void drv_ble_read_data_pkt(uint8_t *pkt, uint8_t len);

/**
 * @brief  Reset rx/tx fifo management and its content.
 */
void drv_rf_reset_rx_fifo(void);
void drv_rf_reset_tx_fifo(void);

/**
 * @brief  Get the BLE anchor point when an BLE packet is synced.
 * @return The anchor point in RTC tick.
 */
uint32_t drv_ble_get_anchor_tick(void);

/**
 * @brief  Check whether an empty data packet is sent in the previous slot.
 * @param [in] pkt_idx - tx fifo 0 or 1.
 * @return true means an empty data packet is sent.
 *         false means a non-empty data packet is sent.
 */
bool drv_ble_tx_is_last_empty(int pkt_idx);

bool drv_ble_tx_fifo_is_full(void);
bool drv_ble_tx_fifo_is_empty(void);
uint8_t drv_ble_tx_fifo_idx(void);

/**
 * @brief  Put the BLE data/adv packet to be sent.
 * @note   must be in critical region
 *
 * @param [in] pkt_idx - tx fifo 0 or 1.
 * @param [in/out] p_pkt - The pointer to BLE packet.
 *
 * @return true is submitted.
 *         false is not submitted.
 */
void drv_ble_put_data_pkt(uint8_t *p_pkt);
bool drv_ble_put_adv_pkt(int pkt_idx, uint8_t *p_pkt);

/**
 * @brief  Put the BLE test packet to be sent.
 * @note   The multi-level will be disabled.
 * @param [in/out] p_pkt - The pointer to BLE packet.
 * @return always true for submitted.
 */
bool drv_ble_put_test_pkt(uint8_t *p_pkt);

/**
 * @brief  Put/Get the BLE test payload to simulate Gazell protocol.
 */
void drv_ble_put_test_payload(const uint8_t *p_payload, uint8_t data_type, uint8_t length);
uint8_t drv_ble_get_test_payload(uint8_t *p_payload);

/**
 * @brief  enable/disable rx (CONFIG[0]=0/1)
 */
void drv_rf_enable_rx(void );
void drv_rf_disable_rx(void );

/**
 * @brief  enable/disable crc (CONFIG[3]=0/1)
 */
void drv_rf_disable_crc(void );
void drv_rf_enable_crc(void );

/**
 * @brief  enable/disable dynamic playload length (FEATURE[2]=0/1)
 */
void drv_rf_enable_dynamic_payload_length(void );
void drv_rf_disable_dynamic_payload_length(void );

/**
 * @brief  enable/disable ack payload (FEATURE[1]=0/1)
 */
void drv_rf_enable_ack_payload(void );
void drv_rf_disable_ack_payload(void );

/**
 * @brief  enable/disable dynamic ack playload length (FEATURE[0]=0/1)
 */
void drv_rf_enable_dynamic_ack(void );
void drv_rf_disable_dynamic_ack(void );

/**
 * @brief  enable/disable carrier (RF_SETUP[7]=0/1)
 */
void drv_rf_test_start_carrier_tx(void );
void drv_rf_test_stop_carrier_tx(void );

/**
 * @brief  Reuse tx fifo content at the next packet.
 */
void drv_rf_reuse_tx_fifo(void );

/**
 * @brief  cleanup the radio, include flush tx/rx fifo, clear interrupt.
 */
void drv_rf_cleanup(void);

/**
 * @brief  Enable/disable 2.4G transceiver's interrupts.
 * @param [in] bitmask - bit mask of interrupts, @refer DRV_RF_IRQ_MASK_xxx
 */
void drv_rf_enable_interrupt(uint8_t bitmask);
void drv_rf_disable_interrupt(uint8_t bitmask);

/**
 * @brief  Enable/disable 2.4G transceiver's features by pipe number.
 * @param [in] bitmask - bit mask of pipe numbers.
 */
void drv_rf_enable_pipe(uint8_t bitmask);
void drv_rf_disable_pipe(uint8_t bitmask);
void drv_rf_enable_pipe_auto_ack(uint8_t bitmask);
void drv_rf_disable_pipe_auto_ack(uint8_t bitmask);
void drv_rf_enable_pipe_dynamic_payload_length(uint8_t bitmask);
void drv_rf_disable_pipe_dynamic_payload_length(uint8_t bitmask);
/**
 * @brief  Check whether DPL is enabled on the specific pipe.
 * @param [in] pipe_no - pipe number.
 * @return true for DPL enabled;
 *         false for SPL.
 */
bool drv_rf_is_pipe_dynamic_payload_length(uint8_t pipe_no);
/**
 * @brief  Set 2.4G transceiver's received static payload length (SPL) by pipe number.
 * @param [in] pipe_no - pipe number.
 * @param [in] len     - received payload length in byte.
 */
void drv_rf_set_pipe_rx_static_payload_length(uint8_t pipe_no, uint8_t len);
uint8_t drv_rf_get_pipe_rx_static_payload_length(uint8_t pipe_no);

/**
 * @brief  Enable/disable 2.4G transceiver's transmit guard time.
 * @note  Don't enable TX guard if communicate with nRF.
 */
void drv_rf_enable_tx_guard(void);
void drv_rf_disable_tx_guard(void);

/**
 * @brief  set/get access address .
 * @param [in] addr - address will be set/get.
 */
void drv_rf_set_rx_address_pipe0(const uint8_t addr[5]);
void drv_rf_set_rx_address_pipe1(uint8_t addr);
void drv_rf_set_rx_address_pipe2(uint8_t addr);
void drv_rf_set_tx_address(const uint8_t addr[5]);
void drv_rf_get_rx_address_pipe0(uint8_t addr[5]);
void drv_rf_get_tx_address(uint8_t addr[5]);

/**
 * @brief  Get the rx address pipe
 * @return The address
 */
uint8_t drv_rf_get_rx_address_pipe1(void);
uint8_t drv_rf_get_rx_address_pipe2(void);

/**
 * @brief  Get 2.4G transceiver's pipe number for the received payload.
 * @return The pipe number.
 */
uint8_t drv_rf_get_rx_pipe_no(void);
/**
 * @brief  Get 2.4G transceiver's received dynamic payload length (DPL).
 * @return The received payload length in byte.
 */
uint8_t drv_rf_get_rx_dynamic_payload_length(void);

/**
 * @brief  Get rf irq status.
 * @return The status register value.
 */
uint8_t drv_rf_get_irq_status(void);

/**
 * @brief  read/write 2.4G payload .
 * @param [in] p_payload - the data point of the payload.
 * @param [in] len       - The length of the payload.
 * @param [in] pipe      - pipe number
 */
void drv_rf_write_tx_payload(const uint8_t *p_payload, uint8_t len);
void drv_rf_write_ack_payload(const uint8_t *p_payload, uint8_t len, uint8_t pipe);
/**
 * @note  Dynamic ack must be enabled at both sides if AA.
 */
void drv_rf_write_tx_payload_noack(const uint8_t *p_payload, uint8_t len);
uint8_t drv_rf_read_rx_payload(uint8_t *p_payload);
/**
 * @note  Same function with drv_rf_read_rx_payload(), but fewer check inside.
 */
uint8_t drv_rf_read_rx_payload_static(uint8_t *p_payload, uint8_t len);

/**
 * @brief  Set the auto retry param in the 2.4G auto ack mode.
 * @param [in] delay_us - The interval of the two ack pkt
 * @param [in] count - The total number of the ack packet
 */
void drv_rf_set_auto_retry_param(uint16_t delay_us, uint8_t count);

/**
 * @brief  Check the fifo state
 * @param  none
 * @return the fifo state
 */
bool drv_rf_rx_fifo_is_empty(void );
bool drv_rf_rx_fifo_is_full(void );
bool drv_rf_tx_fifo_is_empty(void );
bool drv_rf_tx_fifo_is_full(void );
bool drv_rf_tx_fifo_is_reuse(void );

/**
 * @brief  print  all the radio register for debug.
 */
void drv_rf_dump_all_register(void);
/**
 * @brief  Get the interval fsm of RF hardware for debug.
 * @return The fsm value.
 */
uint16_t drv_rf_get_fsm(void);

/**
 * @brief  Get the om62XX chip ID .
 * @return The chip ID value.
 */
uint16_t drv_rf_get_chipID(void);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_RF_H_ */

/** @} */
