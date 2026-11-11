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
 * @file     drv_usb.c
 * @brief    usb driver
 * @date     8. Apr 2024
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_USB)
#include <stddef.h>
#include "om_driver.h"

#ifndef USBD_IRQHandler
#define USBD_IRQHandler  //use actual usb irq name instead
#endif

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 2
#endif

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 8
#endif

#define USB_EP0_DEFAULT_SIZE  0x10

/* Endpoint state */
struct musb_ep_state {
    /** Endpoint max packet size */
    uint16_t ep_mps;
    /** Endpoint Transfer Type.
     * May be Bulk, Interrupt, Control or Isochronous
     */
    uint8_t ep_type;
    uint8_t ep_stalled; /** Endpoint stall flag */
};

/* Driver state */
struct musb_udc {
    volatile uint8_t dev_addr;
    volatile uint32_t fifo_size_offset;
    struct usb_setup_pkt setup;
    struct musb_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];  /*!< IN endpoint parameters*/
    struct musb_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS]; /*!< OUT endpoint parameters */
} g_musb_udc;

static volatile uint8_t usb_ep0_state = USB_EP0_STATE_SETUP;
volatile uint16_t ep0_last_size = 0;

/* get current active ep */
__RAM_CODE static uint8_t musb_get_active_ep(void)
{
    return OM_USB->INDEX;
}

/* set the active ep */
__RAM_CODE static void musb_set_active_ep(uint8_t ep_index)
{
    OM_USB->INDEX = ep_index;
}

__RAM_CODE static void musb_write_packet(uint8_t ep_idx, uint8_t *buffer, uint16_t len)
{
    uint32_t flags;
    uint8_t i, ei = ep_idx & 0x7F;
    volatile uint8_t *fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[ei];
    uint8_t old_ep_idx;

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    // Copy the data into the USB controller
    for( i = 0; i < len; i++ )
    {
      *fifo_epn = buffer[i];
     // printf("%02x ", buffer[i]);
    }
   // printf("\r\n");

    musb_set_active_ep(old_ep_idx);

}

__RAM_CODE static void musb_read_packet(uint8_t ep_idx, uint8_t *buffer, uint16_t len)
{
    uint32_t flags;
    uint8_t i, ei = ep_idx & 0x7F;
    volatile uint8_t *fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[ei];
    uint8_t old_ep_idx;

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    for (i=0; i<len; i++) {
        buffer[i] = *fifo_epn;
        //printf("%02x ", buffer[i]);
    }
    //printf("\r\n");
    musb_set_active_ep(old_ep_idx);
}

static uint32_t musb_get_fifo_size(uint16_t mps, uint16_t *used)
{
    uint32_t size;

    for (uint8_t i = 0; i <= 8; i++) {
        size = (8 << i);
        if (mps <= size) {
            *used = size;
            return i;
        }
    }

    *used = 0;
    return 8;
}

__WEAK void usbd_event_notify_handler(uint8_t event, void *arg)
{
}

__WEAK void usb_dc_low_level_init(void)
{
  uint8_t ei;

  /* Switch on USB PLL & USB module */
  drv_pmu_syspll_ctrl(PMU_PLL_CTRL_START);
  DRV_RCC_CLOCK_ENABLE(RCC_CLK_USB, 1U);
  /* USB wakeup clock @32KHz. */
  OM_RCC->USB_WK_CLK_SEL = 1;

  // Disconnect from USB-bus if we are in this routine from a power on and not a soft reset
  OM_RCC->USB_CTRL = 0; // disconnect
  DRV_DELAY_MS(50);
  /* Enable pull-up on usb port */
  drv_pmu_pin_mode_set(2, PMU_PIN_MODE_FLOAT);
  drv_pmu_pin_mode_set(3, PMU_PIN_MODE_FLOAT);
  OM_RCC->USB_CTRL = (0x1 << 4); // connect


  // Setup interrupts
#if 0//ONMICRO_CONF_HI5MOUSE_HRR
  OM_USB->INTR_USBEN = USB_INTR_RESET | USB_INTR_RESUME | USB_INTR_SUSPEND | USB_INTR_SOF;
#else
  OM_USB->INTR_USBEN = USB_INTR_RESET | USB_INTR_RESUME | USB_INTR_SUSPEND;
#endif
  OM_USB->INTR_TXEN1 = 0x01;
  NVIC_EnableIRQ(USB_IRQn);
  OM_USB->POWER = USB_POWER_ENABLE_SUSPEND; //enable suspend

  // Set all endpoints to not valid (except EP0IN and EP0OUT)
  for (ei = 1; ei < 8; ei++) {
    OM_USB->INDEX = ei;
    OM_USB->TXMAXP = 0;
    OM_USB->RXMAXP = 0;
  }
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

__WEAK uint8_t usb_ge_ep0_size(void)
{
    return USB_EP0_DEFAULT_SIZE;
}

int usb_dc_init(void)
{
    memset(&g_musb_udc, 0, sizeof(struct musb_udc));

    g_musb_udc.out_ep[0].ep_mps = usb_ge_ep0_size();
    g_musb_udc.out_ep[0].ep_type = 0x00;
    g_musb_udc.in_ep[0].ep_mps = usb_ge_ep0_size();
    g_musb_udc.in_ep[0].ep_type = 0x00;
    g_musb_udc.fifo_size_offset = usb_ge_ep0_size();

    usb_dc_low_level_init();

    return 0;
}

int usb_dc_deinit(void)
{
    return 0;
}

void usbd_remote_wakeup(void)
{
    // Wakeup the USB controller via remote pin
    if (OM_USB->POWER & USB_POWER_SUSPEND_MODE) {
        OM_USB->POWER |= USB_POWER_RESUME;
        DRV_DELAY_MS(10);    // Wait until the USB clock starts
        OM_USB->POWER &= ~USB_POWER_RESUME;
    }
}

int usbd_set_address(const uint8_t addr)
{
    if (addr == 0) {
        OM_USB->FADDR = 0;
    }
    OM_USB->FADDR = addr;
    g_musb_udc.dev_addr = addr;
    return 0;
}

int usbd_ep_open(const struct usbd_endpoint_cfg *ep_cfg)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep_cfg->ep_addr);
    uint8_t old_ep_idx;
    uint8_t temp = (ep_idx & 0x7f) - 1;
    uint8_t stemp = 1 << (ep_idx & 0x7f);


    if (ep_idx == 0) {
        return 0;
    }

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    if (USB_EP_DIR_IS_OUT(ep_cfg->ep_addr)) {
        g_musb_udc.out_ep[ep_idx].ep_mps = ep_cfg->ep_mps;
        g_musb_udc.out_ep[ep_idx].ep_type = ep_cfg->ep_type;
      // Add the callback, enable the interrupt and validate the endpoint
        OM_USB->INTR_RXEN1 |= stemp;
        OM_USB->RXMAXP = ep_cfg->ep_mps / 8;
        /* Enable the EP direction as Rx. */
        OM_USB->TXCSR2 &= ~(USB_TXCSR_MODE >> 8);
    } else {
        g_musb_udc.in_ep[ep_idx].ep_mps = ep_cfg->ep_mps;
        g_musb_udc.in_ep[ep_idx].ep_type = ep_cfg->ep_type;
        // enable the interrupt and validate the endpoint
        OM_USB->INTR_TXEN1 |= stemp;
        OM_USB->TXMAXP = ep_cfg->ep_mps / 8;
        /* Enable the EP direction as Tx. */
        OM_USB->TXCSR2 |= USB_TXCSR_MODE >> 8;
    }

    musb_set_active_ep(old_ep_idx);

    return 0;
}

int usbd_ep_close(const uint8_t ep)
{
    return 0;
}

int usbd_ep_set_stall(const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint8_t old_ep_idx;

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (ep_idx == 0x00) {
            usb_ep0_state = USB_EP0_STATE_STALL;
            OM_USB->CSR0 |= USB_CSR0_P_SENDSTALL | USB_CSR0_P_RXPKTRDY;
        } else {
            OM_USB->RXCSR1 |= USB_RXCSR_P_SENDSTALL;
        }
    } else {
        if (ep_idx == 0x00) {
            usb_ep0_state = USB_EP0_STATE_STALL;
            OM_USB->CSR0 |= USB_CSR0_P_SENDSTALL | USB_CSR0_P_RXPKTRDY;
        } else {
            OM_USB->TXCSR1 |= USB_TXCSR_P_SENDSTALL;
        }
    }

    musb_set_active_ep(old_ep_idx);
    return 0;
}

int usbd_ep_clear_stall(const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint8_t old_ep_idx;

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (ep_idx == 0x00) {

        } else {
            // Clear the stall on an OUT endpoint.
            OM_USB->RXCSR1 &= ~USB_RXCSR_P_SENDSTALL;
        }
    } else {
        if (ep_idx == 0x00) {

        } else {
            // Clear the stall on an IN endpoint.
            OM_USB->TXCSR1 &= ~USB_TXCSR_P_SENDSTALL;
        }
    }

    musb_set_active_ep(old_ep_idx);
    return 0;
}

int usbd_ep_is_stalled(const uint8_t ep, uint8_t *stalled)
{
    uint8_t saved_ei = OM_USB->INDEX;
    uint8_t ei = ep & 0x7F;

    OM_USB->INDEX = ei;
    if (0 == ei) {
        *stalled = OM_USB->CSR0 & USB_CSR0_P_SENDSTALL ? 1 : 0;
    }
    if (ep & 0x80) {
        /* IN endpoints */
        *stalled = OM_USB->TXCSR1 & USB_TXCSR_P_SENDSTALL ? 1 : 0;
    } else {
        *stalled = OM_USB->RXCSR1 & USB_RXCSR_P_SENDSTALL ? 1 : 0;
    }
    OM_USB->INDEX = saved_ei;

    return 0;
}

int usbd_ep_write(const uint8_t ep, const uint8_t *data, uint32_t data_len, uint32_t *ret_bytes)
{
    int ret = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint32_t timeout = 0xffffff;
    uint8_t old_ep_idx;

    if (!data && data_len) {
        return -1;
    }

   OM_CRITICAL_BEGIN();

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    if (!data_len) {
        if (ep == 0x00) {
            OM_USB->CSR0 |= USB_CSR0_P_TXPKTRDY | USB_CSR0_P_DATAEND;
        } else {

        }
        goto _RET;
    }

    if (ep_idx != 0x00) {
        while (OM_USB->TXCSR1 & USB_TXCSR_P_TXPKTRDY) {
            if (OM_USB->TXCSR1 & USB_TXCSR_P_UNDERRUN) {
                ret = -2;
                goto _RET;
            }
            if (!(timeout--)) {
                ret = -3;
                goto _RET;
            }
        }
    }

    ep0_last_size = data_len;

    if (data_len > g_musb_udc.in_ep[ep_idx].ep_mps) {
        data_len = g_musb_udc.in_ep[ep_idx].ep_mps;
    }
    else {
       ep0_last_size = 0;
    }

    musb_write_packet(ep_idx, (uint8_t *)data, data_len);

    if (ep_idx == 0x00) {
        if(ep0_last_size == 0) {
            OM_USB->CSR0 |= USB_CSR0_P_TXPKTRDY | USB_CSR0_P_DATAEND;
        }
        else {
            OM_USB->CSR0 |= USB_CSR0_P_TXPKTRDY;
        }
    } else {
        OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
    }

    if (ret_bytes) {
        *ret_bytes = data_len;
    }

_RET:
    musb_set_active_ep(old_ep_idx);

    OM_CRITICAL_END();

    return ret;

}

int usbd_ep_read(const uint8_t ep, uint8_t *data, uint32_t max_data_len, uint32_t *read_bytes)
{
    int ret = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint32_t read_count = 0;
    uint8_t old_ep_idx;

    OM_CRITICAL_BEGIN();

    old_ep_idx = musb_get_active_ep();
    musb_set_active_ep(ep_idx);

    if (max_data_len == 0) {
        if (ep_idx != 0x00)
           /* Unload and ACK Out packet. */
           OM_USB->RXCSR1 &= ~USB_RXCSR_P_RXPKTRDY;
        goto _RET;
    }

    if (ep_idx == 0x00) {
        if (usb_ep0_state == USB_EP0_STATE_SETUP) {
            memcpy(data, (uint8_t *)&g_musb_udc.setup, 8);
        } else {
            read_count = OM_USB->COUNT0;
            read_count = MIN(read_count, max_data_len);
            musb_read_packet(0, data, read_count);
        }
    } else {
        read_count = OM_USB->RXCOUNT1;
        read_count = MIN(read_count, max_data_len);
        musb_read_packet(ep_idx, data, read_count);
    }

    if (read_bytes) {
        *read_bytes = read_count;
    }

_RET:
    musb_set_active_ep(old_ep_idx);

    OM_CRITICAL_END();

    return ret;
}

static void handle_ep0(void)
{
    uint8_t ep0_status = OM_USB->CSR0;

    if (ep0_status & USB_CSR0_P_SENTSTALL) {
        OM_USB->CSR0 &= ~USB_CSR0_P_SENTSTALL;
        usb_ep0_state = USB_EP0_STATE_SETUP;
    }

    if (ep0_status & USB_CSR0_P_SETUPEND) {
      /* A control transation ends. */
      OM_USB->CSR0 |= USB_CSR0_P_SERVICED_SETUPEND;
      usb_ep0_state = USB_EP0_STATE_SETUP;
    }

    switch (usb_ep0_state) {
        case USB_EP0_STATE_SETUP:
            if (ep0_status & USB_CSR0_P_RXPKTRDY) {
                ep0_last_size = 0;
                uint32_t read_count = OM_USB->COUNT0;

                if (read_count != 8) {
                    return;
                }

                musb_read_packet(0, (uint8_t *)&g_musb_udc.setup, 8);
                if (g_musb_udc.setup.wLength) {
                    /* Inform HW that setup packet is read, and HW will send ACK pakcet automatically. */
                    OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY;
                } else {
                    /* Don't set USB_CSR0_P_DATAEND alone, otherwise it won't self-clearing, then HW will send IN ZLP Status packets automatically. */
                    OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY | USB_CSR0_P_DATAEND;
                }

                usbd_event_notify_handler(USBD_EVENT_SETUP_NOTIFY, NULL);

                if (usb_ep0_state != USB_EP0_STATE_STALL) {
                    if (g_musb_udc.setup.wLength) {
                        if (g_musb_udc.setup.bmRequestType & 0x80) {
                            usb_ep0_state = USB_EP0_STATE_IN_DATA;
                            if (ep0_last_size > g_musb_udc.in_ep[0].ep_mps) {

                            } else {
                                usb_ep0_state = USB_EP0_STATE_OUT_STATUS;
                            }
                        } else {
                            usb_ep0_state = USB_EP0_STATE_OUT_DATA;
                        }
                    } else {
                        usb_ep0_state = USB_EP0_STATE_SETUP;
                    }
                }
            }

            break;

        case USB_EP0_STATE_IN_DATA:
            usbd_event_notify_handler(USBD_EVENT_EP0_IN_NOTIFY, NULL);
            if (ep0_last_size <= g_musb_udc.in_ep[0].ep_mps) {
                usb_ep0_state = USB_EP0_STATE_OUT_STATUS;
            }
            break;
        case USB_EP0_STATE_IN_STATUS:
            usb_ep0_state = USB_EP0_STATE_SETUP;
            break;
        case USB_EP0_STATE_OUT_DATA:
            if (ep0_status & USB_CSR0_P_RXPKTRDY) {
                usbd_event_notify_handler(USBD_EVENT_EP0_OUT_NOTIFY, NULL);
                if (g_musb_udc.setup.wLength <= g_musb_udc.out_ep[0].ep_mps) {
                    usb_ep0_state = USB_EP0_STATE_IN_STATUS;
                    OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY | USB_CSR0_P_DATAEND;
                } else {
                    OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY;
                }
            }
            break;
        case USB_EP0_STATE_OUT_STATUS:
            usb_ep0_state = USB_EP0_STATE_SETUP;
            break;
    }
}

void drv_usb_isr(void)
{
    uint32_t is;
    uint32_t txis;
    uint32_t rxis;
    uint8_t old_ep_idx;

    is = OM_USB->INTR_USB;
    txis = OM_USB->INTR_TX1;
    rxis = OM_USB->INTR_RX1;

    //HWREGB(USB_BASE + MUSB_IS_OFFSET) = is;

    old_ep_idx = musb_get_active_ep();

    /* Receive a reset signal from the USB bus */
    if (is & USB_INTR_RESET) {
        usbd_event_notify_handler(USBD_EVENT_RESET, NULL);
        ep0_last_size = 0;
        usb_ep0_state = USB_EP0_STATE_SETUP;
	      /*
	       * HW will clear POWER register upon USB reset.
	       * SW enable suspend mode here after enumerated, so
	       * USB suspend signal is skipped when reset firmware.
	       * Don't toggle this enable bit, otherwise a fake suspend irq will occur.
	       */
	      OM_USB->POWER = USB_POWER_ENABLE_SUSPEND;
    }

    if (is & USB_INTR_SOF) {
    }

    if (is & USB_INTR_RESUME) {
    }

    if (is & USB_INTR_SUSPEND) {
    }

    //txis &= HWREGH(USB_BASE + MUSB_TXIE_OFFSET);
    /* Handle EP0 interrupt */
    if (txis & 0x01) {
        musb_set_active_ep(0);
        handle_ep0();
        txis &= ~0x01;
    }

    for (uint32_t ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
        if (txis & (1 << ep_idx)) {
            musb_set_active_ep(ep_idx);
            //HWREGH(USB_BASE + MUSB_TXIS_OFFSET) = (1 << ep_idx);
            //if (HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) & USB_TXCSRL1_UNDRN) {
            //    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_TXCSRL1_UNDRN;
            //}
            usbd_event_notify_handler(USBD_EVENT_EP_IN_NOTIFY, (void *)(0x80 | ep_idx));
        }
    }

    //rxis &= HWREGH(USB_BASE + MUSB_RXIE_OFFSET);
    for (uint32_t ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
        if (rxis & (1 << ep_idx)) {
            musb_set_active_ep(ep_idx);
            if (OM_USB->RXCSR1 & USB_RXCSR_P_RXPKTRDY) {
                usbd_event_notify_handler(USBD_EVENT_EP_OUT_NOTIFY, (void *)(ep_idx & 0x7f));
            }
        }
    }

    musb_set_active_ep(old_ep_idx);
}
#endif

void USB_IRQHandler(void)
{
    drv_usb_isr();
}
