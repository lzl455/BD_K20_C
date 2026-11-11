/* ----------------------------------------------------------------------------
 * Copyright (c) 2020-2030 OnMicro Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of OnMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -------------------------------------------------------------------------- */

/**
 * @file     usb_reg.h
 * @brief    USB Register define
 * @date     8. Apr 2024
 * @author   OnMicro SW Team
 *
 * @ingroup  REGS
 * @brief    USB Registers for OnMicro OM62xx
 * @details  USB Registers definitions
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */
#ifndef __USB_REG_H
#define __USB_REG_H


/*******************************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include "common_reg.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
typedef struct {
  /* Common registers */
  __IO uint8_t      FADDR;        //00
  __IO uint8_t      POWER;        //01
  __IO uint8_t      INTR_TX1;     //02
  __IO uint8_t      INTR_TX2;     //03
  __IO uint8_t      INTR_RX1;     //04
  __IO uint8_t      INTR_RX2;     //05
  __IO uint8_t      INTR_USB;     //06
  __IO uint8_t      INTR_TXEN1;   //07
  __IO uint8_t      INTR_TXEN2;   //08
  __IO uint8_t      INTR_RXEN1;   //09
  __IO uint8_t      INTR_RXEN2;   //0a
  __IO uint8_t      INTR_USBEN;   //0b
  __IO uint8_t      FRAME1;       //0c
  __IO uint8_t      FRAME2;       //0d
  __IO uint8_t      INDEX;        //0e
  __IO uint8_t      DEVCTL;       //0f
  /* Indexed registers */
  __IO uint8_t      TXMAXP;       //10
  union
  {
    __IO uint8_t    CSR0;         //11
    __IO uint8_t    TXCSR1;
  };
  union
  {
    __IO uint8_t    CSR02;        //12
    __IO uint8_t    TXCSR2;
  };
  __IO uint8_t      RXMAXP;       //13
  __IO uint8_t      RXCSR1;       //14
  __IO uint8_t      RXCSR2;       //15
  union
  {
    __IO uint8_t    COUNT0;       //16
    __IO uint8_t    RXCOUNT1;
  };
  __IO uint8_t      RXCOUNT2;     //17
  __IO uint8_t      x18_1e[7];
  __IO uint8_t      FIFOSIZE;     //1f
  /* FIFO port */
  __IO uint32_t     EPnFIFO[16];  //20
       uint8_t      x60_1ff[0x200-0x60];
  /* DMA registers */
  __IO uint32_t     DMA_INTR;     //200
  //HS_UDMA_CH_Type   DMA_CH[1];
} OM_USB_Type;

/******************************************************************************/
/*                                                                            */
/*                          USB FS Dual-Role Controller                       */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for POWER register  **********************/
#define  USB_POWER_ISO_UPDATE                0x80                          /*!<set by CPU in Peripheral mode */
#define  USB_POWER_VBUSVAL                   0x40                          /*!<set when VBUS > VBUSVAL threshold */
#define  USB_POWER_VBUSSESS                  0x20                          /*!<set when VBUS > VBUSSESS threshold */
#define  USB_POWER_VBUSLO                    0x10                          /*!<set when VBUS > VBUSLO threshold */
#define  USB_POWER_RESET                     0x08                          /*!<set when Reset signaling is detected in Peripheral mode;
                                                                             !<set and clear by CPU to generate Reset signaling in Host mode */
#define  USB_POWER_RESUME                    0x04                          /*!<set and clear by CPU to generate Resume signaling in suspend mode */
#define  USB_POWER_SUSPEND_MODE              0x02                          /*!<set if Suspend mode is entered in Peripheral mode;
                                                                             !<set by CPU when Suspend mode is entered in Host mode */
#define  USB_POWER_ENABLE_SUSPEND            0x01                          /*!<set by CPU to enter into Suspend mode when Suspend signaling is recevied in Peripheral mode */

/*******************  Bit definition for INTRUSB register  ********************/
#define  USB_INTR_VBUS_ERROR                 0x80                          /*!<set when VBUS < VBUSVAL in A device */
#define  USB_INTR_SESS_REQ                   0x40                          /*!<set when Session Request signaling is deteted in A device */
#define  USB_INTR_DISCONNECT                 0x20                          /*!<set when a device disconnect is detected in Host mode;
                                                                             !<set when a session ends in Peripheral mode */
#define  USB_INTR_CONNECT                    0x10                          /*!<set when a device connect is detected in Host mode */
#define  USB_INTR_SOF                        0x08                          /*!<set when a new frame starts */
#define  USB_INTR_RESET                      0x04                          /*!<set when Reset signaling is detected in Peripheral mode */
#define  USB_INTR_BABBLE                     0x04                          /*!<set when babble (sends more data > MPS) in Host mode */
#define  USB_INTR_RESUME                     0x02                          /*!<set when Resume signaling is detected in Suspend mode */
#define  USB_INTR_SUSPEND                    0x01                          /*!<set when Suspend signaling is detected in Peripheral mode */

/*******************  Bit definition for DEVCTL register  *********************/
#define  USB_DEVCTL_CID                      0x80                          /*!<set when the ID pin is B device */
#define  USB_DEVCTL_FSDEV                    0x40                          /*!<set when a full-speed device is connected in Host mode */
#define  USB_DEVCTL_LSDEV                    0x20                          /*!<set when a low-speed device is connected in Host mode */
#define  USB_DEVCTL_PUCON                    0x10                          /*!<set when a pull-up resistor on D+ line as a peripheral */
#define  USB_DEVCTL_PDCON                    0x08                          /*!<set when a pull-down resistor on D+ line as a host */
#define  USB_DEVCTL_HOST_MODE                0x04                          /*!<set when act as a Host */
#define  USB_DEVCTL_HOST_REQ                 0x02                          /*!<set by CPU to initiate the Host Negotiation when Suspend mode is entered */
#define  USB_DEVCTL_SESSION                  0x01                          /*!<set/clear by CPU to start/end a session in A device;
                                                                             !<set/clear when a session starts/ends in B device */

/*******************  Bit definition for CSR0 register  ***********************/
#define  USB_CSR0_FLUSHFIFO                  0x0100                        /*!<set by CPU to flush EP0's FIFO, self-clearing */
#define  USB_CSR0_P_SERVICED_SETUPEND        0x0080                        /*!<set by CPU to clear SetupEnd bit, self-clearing */
#define  USB_CSR0_P_SERVICED_RXPKTRDY        0x0040                        /*!<set by CPU to clear RxPktRdy bit, self-clearing */
#define  USB_CSR0_P_SENDSTALL                0x0020                        /*!<set by CPU to send STALL handshake, self-clearing */
#define  USB_CSR0_P_SETUPEND                 0x0010                        /*!<set and raise interrupt when a control transaction ends, clear by CPU via SERVICED_SETUPEND */
#define  USB_CSR0_P_DATAEND                  0x0008                        /*!<set by CPU for Tx/Rx the last data packet or Tx ZLP, self-clearing */
#define  USB_CSR0_P_SENTSTALL                0x0004                        /*!<set when a STALL handshake is sent, clear by CPU */
#define  USB_CSR0_P_TXPKTRDY                 0x0002                        /*!<set by CPU after loading a data packet into FIFO, self-clearing; raise interrupt when transmitted */
#define  USB_CSR0_P_RXPKTRDY                 0x0001                        /*!<set and raise interrupt when a a data packet received, clear by CPU via SERVICED_RXPKTRDY */

#define  USB_CSR0_H_DIS_PING                 0x0800
#define  USB_CSR0_H_WR_DATATOGGLE            0x0400
#define  USB_CSR0_H_DATATOGGLE               0x0200
#define  USB_CSR0_H_NAKTIMEOUT               0x0080                        /*!<set when NAK response receive timeout, clear by CPU to allow EP0 exit the halted status */
#define  USB_CSR0_H_STATUSPKT                0x0040                        /*!<set and TxPktRdy or ReqPkt by CPU to perform a status stage transaction, while data toggle must be 1 for DATA1 packet */
#define  USB_CSR0_H_REQPKT                   0x0020                        /*!<set by CPU to perform an IN transaction, clear when RxPktRdy is set */
#define  USB_CSR0_H_ERROR                    0x0010                        /*!<set and raise interrupt when 3 retries of transaction but no response, clear by CPU */
#define  USB_CSR0_H_SETUPPKT                 0x0008                        /*!<set and TxPktRdy by CPU to send a SETUP token instead of OUT token */
#define  USB_CSR0_H_RXSTALL                  0x0004                        /*!<set when a STALL handshake is received, clear by CPU */
#define  USB_CSR0_H_TXPKTRDY                 0x0002                        /*!<USB_CSR0_P_TXPKTRDY */
#define  USB_CSR0_H_RXPKTRDY                 0x0001                        /*!<USB_CSR0_P_RXPKTRDY, but clear by CPU directly */

/*******************  Bit definition for TXCSR register  **********************/
#define  USB_TXCSR_AUTOSET                   0x8000                        /*!<set by CPU, and TxPktRdy will be automatically set when MPS data is loaded into Tx FIFO */
#define  USB_TXCSR_ISO                       0x4000                        /*!<set by CPU in Peripheral mode to enable Tx EP in ISO in stead of Bulk or Interrupt */
#define  USB_TXCSR_MODE                      0x2000                        /*!<set by CPU to enable the EP as Tx, clear by CPU as Rx */
#define  USB_TXCSR_DMAENAB                   0x1000                        /*!<set by CPU to enable DMA for the Tx EP */
#define  USB_TXCSR_FRCDATATOG                0x0800                        /*!<set by CPU to force the EP data toggle switch */
#define  USB_TXCSR_DMAMODE                   0x0400                        /*!<set by CPU to select DMA mode 1 (no interrupt), or DMA mode 0 */
#define  USB_TXCSR_H_WR_DATATOGGLE           0x0200
#define  USB_TXCSR_H_DATATOGGLE              0x0100

#define  USB_TXCSR_P_INCOMPTX                0x0080
#define  USB_TXCSR_P_CLRDATATOG              0x0040                        /*!<set by CPU to reset EP data toggle to 0 */
#define  USB_TXCSR_P_SENTSTALL               0x0020                        /*!<set when a STALL handshake is sent, while flush Tx FIFO and clear TxPktRdy, clear by CPU */
#define  USB_TXCSR_P_SENDSTALL               0x0010                        /*!<set by CPU to send STALL handshake to an IN token, clear by CPU to termiate the stall condition */
#define  USB_TXCSR_P_FLUSHFIFO               0x0008                        /*!<set by CPU to flush Tx FIFO, set twice if double buffered */
#define  USB_TXCSR_P_UNDERRUN                0x0004                        /*!<set if an IN token is received but TxPktRdy not set, clear by CPU */
#define  USB_TXCSR_P_FIFONOTEMPTY            0x0002                        /*!<set if at least 1 packet in Tx FIFO */
#define  USB_TXCSR_P_TXPKTRDY                0x0001                        /*!<USB_CSR0_P_TXPKTRDY */

#define  USB_TXCSR_H_NAKTIMEOUT              0x0080                        /*!<set when NAK response receive timeout, clear by CPU to allow bulk EP exit the halted status */
#define  USB_TXCSR_H_CLRDATATOG              0x0040                        /*!<set by CPU to reset EP data toggle to 0 */
#define  USB_TXCSR_H_RXSTALL                 0x0020                        /*!<set when a STALL handshake is received, clear by CPU */
#define  USB_TXCSR_H_FLUSHFIFO               0x0008                        /*!<USB_TXCSR_P_FLUSHFIFO */
#define  USB_TXCSR_H_ERROR                   0x0004                        /*!<set and raise interrupt when 3 retries of transaction but no response, clear by CPU */
#define  USB_TXCSR_H_FIFONOTEMPTY            0x0002                        /*!<USB_TXCSR_P_FIFONOTEMPTY */
#define  USB_TXCSR_H_TXPKTRDY                0x0001                        /*!<USB_TXCSR_P_TXPKTRDY */

/*******************  Bit definition for RXCSR register  **********************/
#define  USB_RXCSR_AUTOCLEAR                 0x8000                        /*!<set by CPU, and RxPktRdy will be automatically cleared MPS data is unloaded from Rx FIFO */
#define  USB_RXCSR_AUTOREQ                   0x4000                        /*!<set by CPU in Host mode, and ReqPkt will be automatically set when RxPktRdy is cleared */
#define  USB_RXCSR_ISO                       0x4000                        /*!<set by CPU in Peripheral mode to enable Rx EP in ISO in stead of Bulk or Interrupt */
#define  USB_RXCSR_DMAENAB                   0x2000                        /*!<set by CPU to enable DMA for the Rx EP */
#define  USB_RXCSR_DMAMODE                   0x1000                        /*!<set by CPU to select DMA mode 1 (no interrupt if !MPS), or DMA mode 0 */
#define  USB_RXCSR_P_CLRDATATOG              0x0080                        /*!<USB_TXCSR_P_CLRDATATOG */
#define  USB_RXCSR_P_SENTSTALL               0x0040                        /*?<USB_TXCSR_P_SENTSTALL, but not via Tx FIFO? */
#define  USB_RXCSR_P_SENDSTALL               0x0020                        /*?<USB_TXCSR_P_SENDSTALL, but OUT token? */
#define  USB_RXCSR_P_FLUSHFIFO               0x0010                        /*!<set by CPU to flush Rx FIFO, set twice if double buffered */
#define  USB_RXCSR_P_DATAERROR               0x0008                        /*!<set when RxPktRdy set and CRC or bit-stuff error in ISO, clear by CPU via RxPktRdy */
#define  USB_RXCSR_P_OVERRUN                 0x0004                        /*!<set when OUT packet not loaded into Rx FIFO in ISO, clear by CPU */
#define  USB_RXCSR_P_FIFOFULL                0x0002                        /*!<set if Rx FIFO is full */
#define  USB_RXCSR_P_RXPKTRDY                0x0001                        /*!<set and raise interrupt when a a data packet received, clear by CPU */

#define  USB_RXCSR_H_CLRDATATOG              0x0080                        /*!<USB_RXCSR_P_CLRDATATOG */
#define  USB_RXCSR_H_RXSTALL                 0x0040                        /*!<USB_CSR0_H_RXSTALL */
#define  USB_RXCSR_H_REQPKT                  0x0020                        /*!<USB_CSR0_H_REQPKT */
#define  USB_RXCSR_H_FLUSHFIFO               0x0010                        /*!<USB_RXCSR_P_FLUSHFIFO */
#define  USB_RXCSR_H_NAKTIMEOUT              0x0008                        /*!<USB_CSR0_H_NAKTIMEOUT, but EPn in Bulk */
#define  USB_RXCSR_H_DATAERROR               0x0008                        /*!<USB_RXCSR_P_DATAERROR in ISO */
#define  USB_RXCSR_H_ERROR                   0x0004                        /*!<USB_CSR0_H_ERROR, but EPn in Bulk or Interrupt */
#define  USB_RXCSR_H_FIFOFULL                0x0002                        /*!<USB_RXCSR_P_FIFOFULL */
#define  USB_RXCSR_H_RXPKTRDY                0x0001                        /*!<USB_RXCSR_P_RXPKTRDY */

/*******************  Bit definition for TX/RXTYPE register  ******************/
#define  USB_TYPE_PROTOCOL_SHIFT             4
#define  USB_TYPE_PROTOCOL_ISO               0x10                          /*!<Iso  in Host mode */
#define  USB_TYPE_PROTOCOL_BULK              0x20                          /*!<Bulk in Host mode */
#define  USB_TYPE_PROTOCOL_INTERRUPT         0x30                          /*!<Interrupt in Host mode */
#define  USB_TYPE_EP_SHIFT                   0
#define  USB_TYPE_EP_MASK                    0x0F                          /*!<EP number during enumeration in Host mode */
#define  USB_TYPE_PROTOCOL(type)             ((type) << USB_TYPE_PROTOCOL_SHIFT)
#define  USB_TYPE_EP(ep)                     ((ep) << USB_TYPE_EP_SHIFT)

/*******************  Bit definition for TX/RXFIFO register  ******************/
#define  USB_FIFO_SZ_SHIFT                   13
#define  USB_FIFO_SZ_MASK                    0xE000                        /*!<FIFO size, i.e MPS=2^(SZ+3)*/
#define  USB_FIFO_DPB_SHIFT                  12
#define  USB_FIFO_DPB_MASK                   0x1000                        /*!<set by CPU if double-packet buffering */
#define  USB_FIFO_AD_SHIFT                   0
#define  USB_FIFO_AD_MASK                    0x0FFF                        /*!Start address of the EP FIFO in units of 8-byte */
#define  USB_FIFO_SZ(sz)                     ((29-__builtin_clz((sz)-1)) << USB_FIFO_SZ_SHIFT)
#define  USB_FIFO_DPB(dpb)                   ((dpb) << USB_FIFO_DPB_SHIFT)
#define  USB_FIFO_AD(ad)                     (((ad) >> 3) << USB_FIFO_AD_SHIFT)

/*******************  Bit definition for NAKLIMITn/0 register  ****************/
#define  USB_NAKLIMIT_DISABLE                0x00                          /*!<0 or 1 disables the NAK timeout function */

/*******************  Bit definition for DMA_INTR register  *******************/
#define  USB_DMA_INTR_CH4                    0x00000008                    /*!<set when DMA channel 4 raise */
#define  USB_DMA_INTR_CH3                    0x00000004                    /*!<set when DMA channel 3 raise */
#define  USB_DMA_INTR_CH2                    0x00000002                    /*!<set when DMA channel 2 raise */
#define  USB_DMA_INTR_CH1                    0x00000001                    /*!<set when DMA channel 1 raise */

/*******************  Bit definition for DMA_CTRL1/2/3/4 register  ************/
#define  USB_DMA_CTRL_BUS_ERROR              0x00008000                    /*!<set when AHB bus error */
#define  USB_DMA_CTRL_MPS_MASK               0x00007F00                    /*!<MPS in uints of 8-byte, in DMA mode 1 */
#define  USB_DMA_CTRL_EP_MASK                0x000000F0                    /*!<EP number in this DMA channel */
#define  USB_DMA_CTRL_INTR_EN                0x00000008                    /*!<0=disable; 1=enable */
#define  USB_DMA_CTRL_DMA_MODE               0x00000004                    /*!<DMA mode 0 or 1 */
#define  USB_DMA_CTRL_DIR                    0x00000002                    /*!<0=Out EP;  1=In EP */
#define  USB_DMA_CTRL_DMA_EN                 0x00000001                    /*!<0=disable; 1=enable */

#endif  /* __USB_REG_H */


/** @} */
