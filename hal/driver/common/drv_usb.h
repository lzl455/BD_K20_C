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
 * @file     drv_usbd.h
 * @brief    USB Device Driver
 * @date     9 Jan. 2023
 * @author   OnMicro SW Team
 *
 * @defgroup USBD USBD
 * @ingroup  Peripheral
 * @brief    USB Device Driver
 * @details  USB Device Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * The OM32G57X support full speed usb device.
 *
 * <pre>
 * Features:
 *  • USB specification version 2.0 full-speed compliant
 *  • Configurable number of endpoints from 1 to 8
 *  • Dedicated packet buffer memory (SRAM) of 1024 bytes
 *  • Cyclic redundancy check (CRC) generation/checking, Non-return-to-zero Inverted
 *    (NRZI) encoding/decoding and bit-stuffing
 *  • Isochronous transfers support
 *  • Double-buffered bulk/isochronous endpoint support
 *  • USB Suspend/Resume operations
 *  • Frame locked clock pulse generation
 *  • USB 2.0 Link Power Management support
 *  • USB connect / disconnect capability (controllable embedded pull-up resistor on
 *    USB_DP line)
 * </pre>
 *
 *
 * @{
 */

#ifndef __PNC_HLP_USB_H__
#define __PNC_HLP_USB_H__


/*******************************************************************************
 * INCLUDES
 */

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef  __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * MACROS
 */

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK 0x80
#define USB_ENDPOINT_OUT(addr)      ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)       ((addr) | 0x80)

/**
 * USB endpoint direction and number.
 */
#define USB_EP_DIR_MASK 0x80U
#define USB_EP_DIR_IN   0x80U
#define USB_EP_DIR_OUT  0x00U

/** Get endpoint index (number) from endpoint address */
#define USB_EP_GET_IDX(ep) ((ep) & ~USB_EP_DIR_MASK)
/** Get direction from endpoint address */
#define USB_EP_GET_DIR(ep) ((ep)&USB_EP_DIR_MASK)
/** Get endpoint address from endpoint index and direction */
#define USB_EP_GET_ADDR(idx, dir) ((idx) | ((dir)&USB_EP_DIR_MASK))
/** True if the endpoint is an IN endpoint */
#define USB_EP_DIR_IS_IN(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_IN)
/** True if the endpoint is an OUT endpoint */
#define USB_EP_DIR_IS_OUT(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_OUT)

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 8
#endif

#ifndef MIN
/* Use Z_MIN for a GCC-only, single evaluation version */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

/*******************************************************************************
 * TYPEDEFS
 */
typedef enum {
    USB_EP0_STATE_SETUP = 0x0,      /**< SETUP DATA */
    USB_EP0_STATE_IN_DATA = 0x1,    /**< IN DATA */
    USB_EP0_STATE_IN_STATUS = 0x2,  /**< IN status*/
    USB_EP0_STATE_OUT_DATA = 0x3,   /**< OUT DATA */
    USB_EP0_STATE_OUT_STATUS = 0x4, /**< OUT status */
    USB_EP0_STATE_STALL = 0x5,      /**< STALL status */
} ep0_state_t;

/* Endpoint state */
struct usbd_ep_state {
    /** Endpoint max packet size */
    uint16_t ep_mps;
    /** Endpoint Transfer Type.
     * May be Bulk, Interrupt, Control or Isochronous
     */
    uint8_t ep_type;
    uint8_t ep_stalled; /** Endpoint stall flag */
};
#ifndef _USB_DC_H
/* USB Device Event*/
enum usbd_event {
    /** USB error reported by the controller */
    USBD_EVENT_ERROR,
    /** USB reset */
    USBD_EVENT_RESET,
    /** Start of Frame received */
    USBD_EVENT_SOF,
    /** USB connection established, hardware enumeration is completed */
    USBD_EVENT_CONNECTED,
    /** USB configuration done */
    USBD_EVENT_CONFIGURED,
    /** USB connection suspended by the HOST */
    USBD_EVENT_SUSPEND,
    /** USB connection lost */
    USBD_EVENT_DISCONNECTED,
    /** USB connection resumed by the HOST */
    USBD_EVENT_RESUME,

    /** USB interface selected */
    USBD_EVENT_SET_INTERFACE,
    /** USB interface selected */
    USBD_EVENT_SET_REMOTE_WAKEUP,
    /** USB interface selected */
    USBD_EVENT_CLEAR_REMOTE_WAKEUP,
    /** Set Feature ENDPOINT_HALT received */
    USBD_EVENT_SET_HALT,
    /** Clear Feature ENDPOINT_HALT received */
    USBD_EVENT_CLEAR_HALT,
    /** setup packet received */
    USBD_EVENT_SETUP_NOTIFY,
    /** ep0 in packet received */
    USBD_EVENT_EP0_IN_NOTIFY,
    /** ep0 out packet received */
    USBD_EVENT_EP0_OUT_NOTIFY,
    /** ep in packet except ep0 received */
    USBD_EVENT_EP_IN_NOTIFY,
    /** ep out packet except ep0 received */
    USBD_EVENT_EP_OUT_NOTIFY,
    /** Initial USB connection status */
    USBD_EVENT_UNKNOWN
};

/* Setup packet definition used to read raw data from USB line */
struct usb_setup_pkt {
    /** Request type. Bits 0:4 determine recipient, see
	 * \ref usb_request_recipient. Bits 5:6 determine type, see
	 * \ref usb_request_type. Bit 7 determines data transfer direction, see
	 * \ref usb_endpoint_direction.
	 */
    uint8_t bmRequestType;

    /** Request. If the type bits of bmRequestType are equal to
	 * \ref usb_request_type::LIBUSB_REQUEST_TYPE_STANDARD
	 * "USB_REQUEST_TYPE_STANDARD" then this field refers to
	 * \ref usb_standard_request. For other cases, use of this field is
	 * application-specific. */
    uint8_t bRequest;

    /** Value. Varies according to request */
    uint16_t wValue;

    /** Index. Varies according to request, typically used to pass an index
	 * or offset */
    uint16_t wIndex;

    /** Number of bytes to transfer */
    uint16_t wLength;
} __PACKED;

/**
 * @brief USB Endpoint Configuration.
 *
 * Structure containing the USB endpoint configuration.
 */
struct usbd_endpoint_cfg {
    /** The number associated with the EP in the device
     *  configuration structure
     *       IN  EP = 0x80 | \<endpoint number\>
     *       OUT EP = 0x00 | \<endpoint number\>
     */
    uint8_t ep_addr;
    /** Endpoint Transfer Type.
     * May be Bulk, Interrupt, Control or Isochronous
     */
    uint8_t ep_type;
    /** Endpoint max packet size */
    uint16_t ep_mps;
};

/* usb device driver */
typedef struct usbd_drv {
    volatile uint8_t dev_addr;
    volatile uint32_t fifo_size_offset;
    struct usb_setup_pkt setup;
    struct usbd_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];  /*!< IN endpoint parameters*/
    struct usbd_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS]; /*!< OUT endpoint parameters */
} usbd_drv_t;


/*******************************************************************************
 * EXTERN FUNCTIONS
 */

/**
 * @brief init device controller registers.
 * @return 0 on success, negative errno code on fail.
 */
int usbd_init(void);

/**
 * @brief deinit device controller registers.
 * @return 0 on success, negative errno code on fail.
 */
int usbd_deinit(void);

/**
 * @brief Attach USB for device connection
 *
 * Function to attach USB for device connection. Upon success, the USB PLL
 * is enabled, and the USB device is now capable of transmitting and receiving
 * on the USB bus and of generating interrupts.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_attach(void);

/**
 * @brief Detach the USB device
 *
 * Function to detach the USB device. Upon success, the USB hardware PLL
 * is powered down and USB communication is disabled.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_detach(void);

/**
 * @brief  Function to initiate a remote wakeup to the USB host.
 * @return none.
 */
void usbd_remote_wakeup(void);

/**
 * @brief Set USB device address
 *
 * @param[in] addr Device address
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_set_address(const uint8_t addr);

/**
 * @brief configure and enable endpoint.
 *
 * This function sets endpoint configuration according to one specified in USB.
 * endpoint descriptor and then enables it for data transfers.
 *
 * @param [in]  ep_desc Endpoint descriptor byte array.
 *
 * @return true if successfully configured and enabled.
 */
int usbd_ep_open(const struct usbd_endpoint_cfg *ep_cfg);

/**
 * @brief Disable the selected endpoint
 *
 * Function to disable the selected endpoint. Upon success interrupts are
 * disabled for the corresponding endpoint and the endpoint is no longer able
 * for transmitting/receiving data.
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_close(const uint8_t ep);

/**
 * @brief Set stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_set_stall(const uint8_t ep);

/**
 * @brief Clear stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_clear_stall(const uint8_t ep);

/**
 * @brief Check if the selected endpoint is stalled
 *
 * @param[in]  ep       Endpoint address corresponding to the one
 *                      listed in the device configuration table
 * @param[out] stalled  Endpoint stall status
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_is_stalled(const uint8_t ep, uint8_t *stalled);

/**
 * @brief Write data to the specified endpoint with poll mode.
 *
 * This function is called to write data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is transmitted
 * out.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to write
 * @param[in]  data_len  Length of the data requested to write. This may
 *                       be zero for a zero length status packet.
 * @param[out] ret_bytes Bytes scheduled for transmission. This value
 *                       may be NULL if the application expects all
 *                       bytes to be written
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_write(const uint8_t ep, const uint8_t *data, uint32_t data_len, uint32_t *ret_bytes);

/**
 * @brief Read data from the specified endpoint
 *
 * This function is called by the endpoint handler function, after an OUT
 * interrupt has been received for that EP. The application must only call this
 * function through the supplied usbd_ep_callback function. This function clears
 * the ENDPOINT NAK when max_data_len is 0, if all data in the endpoint FIFO has been read,
 * so as to accept more data from host.
 *
 * @param[in]  ep           Endpoint address corresponding to the one
 *                          listed in the device configuration table
 * @param[in]  data         Pointer to data buffer to write to
 * @param[in]  max_data_len Max length of data to read
 * @param[out] read_bytes   Number of bytes read. If data is NULL and
 *                          max_data_len is 0 the number of bytes
 *                          available for read should be returned.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_read(const uint8_t ep, uint8_t *data, uint32_t max_data_len, uint32_t *read_bytes);
#endif
/**
 * @brief The USB interrupt service routine function, should be called in USB IRQHandler
 *
 * @param None
 *
 * @return None
 */
void drv_usb_isr(void);

#ifdef  __cplusplus
}
#endif

#endif



/** @} */
