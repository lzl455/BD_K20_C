/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: rf_hardware.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _RF_HARDWARE_H_
#define _RF_HARDWARE_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//----------------------------------------------------------------------------;
//配置常量定义区
//
#define DMA_CMD_DATA_BYTES_Pos      16
#define DMA_CMD_RX_PAYLOAD          0x61
#define DMA_CMD_TX_PAYLOAD          0xA0
#define DMA_CMD_FLUSH_TX            0xE1
#define DMA_CMD_FLUSH_RX            0xE2

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
#define DMA_CMD_TX_PAYLOAD_NAK      0xB0 // Enabled when FEATURE_EN_DYN_ACK is set.

//----------------------------------------------------------------------------;
// 宏定义
//
#define mCE_DEBUG_H             //OM_GPIO0->DATAOUT |= (1<<CE_PIN);
#define mCE_DEBUG_L             //OM_GPIO0->DATAOUT &= ~(1<<CE_PIN);

#define mRF_CE_HIGH_TX          {OM_RF->RFCE=1; mCE_DEBUG_H}
#define mRF_CE_HIGH_RX          {OM_RF->RFCE=1; /*rf_ctrl_reg|=brf_rx_status;*/ mCE_DEBUG_H}

#define mRF_CE_LOW_TX           {OM_RF->RFCE=0; mCE_DEBUG_L}
#define mRF_CE_LOW_RX           {OM_RF->RFCE=0; /*rf_ctrl_reg&=~brf_rx_status;*/ mCE_DEBUG_L}
#define mRF_CE_LOW_IDLE         {OM_RF->RFCE=0; /*rf_ctrl_reg&=~brf_rx_status;*/ mCE_DEBUG_L}

#define mFLUSH_FIFO             {OM_RF->DMA_CMD = DMA_CMD_FLUSH_TX;\
                                OM_RF->DMA_CMD =  DMA_CMD_FLUSH_RX;}

#define mRF_CLR_STATUS          OM_RF->RF_STATUS = OM_RF->RF_STATUS & (IRQ_STATUS_EVT_DS | IRQ_STATUS_RX_DR | IRQ_STATUS_TX_DS | IRQ_STATUS_SYNC_DS | IRQ_STATUS_RX_TIMEOUT)

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//


//-----------------------------------------------------------------------------;
// 外部函数引用
//



//=============================================================================;
// 内部定义外部部引用区                                                        ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//

//-----------------------------------------------------------------------------;
// 函数引用
//
//
//-----------------------------------------------------------------------------;

#endif

