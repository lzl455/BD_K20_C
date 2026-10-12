/*******************************************************************************
* Copyright (c) 2012, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: USB_Cfg_Info.h
* 文件描述:
* 版    本: V1.0.0
* 作    者: 易谦
* 日    期: 2022/3/18
*******************************************************************************/
#include "main_usb.h"
#include "main.h"
#include "usb_descriptor.h"

//-----------------------------------------------------------------------------
//配置定义
//
#undef USB_EP0_HSNAK
#undef USB_EP0_STALL
/* HW handles NAK automatically. */
#define USB_EP0_HSNAK()     do { } while(0)
#define USB_EP0_STALL()     do { OM_USB->CSR0 |= USB_CSR0_P_SENDSTALL | USB_CSR0_P_RXPKTRDY; } while(0) // Set both DSTALL and STALL when we want to stall a request during a SETUP transaction
#define USB_EP0_DSTALL()    USB_EP0_STALL()

#define USB_EP0_TXDATAEND() do { OM_USB->CSR0 |= USB_CSR0_P_TXPKTRDY | USB_CSR0_P_DATAEND; ep0_state = USB_EP0_WAITING_STS; } while (0)

static enum ep0_state_t {
  USB_EP0_WAITING_SETUP,                /**< Waiting for SETUP data.        */
  USB_EP0_TX,                           /**< Transmitting.                  */
  USB_EP0_WAITING_TX0,                  /**< Waiting transmit 0.            */
  USB_EP0_WAITING_STS,                  /**< Waiting status.                */
  USB_EP0_RX,                           /**< Receiving.                     */
  USB_EP0_SENDING_STS,                  /**< Sending status.                */
  USB_EP0_ERROR                         /**< Error, EP0 stalled.            */
} ep0_state;

//-----------------------------------------------------------------------------
//外部变量引用
//

/** The upper 8 bits of a 16 bit value */
#define MSB(a) ((a & 0xFF00) >> 8)
/** The lower 8 bits (of a 16 bit value) */
#define LSB(a) ((a & 0xFF))

/** Leaves the minimum of the two arguments */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
/** Leaves the maximum of the two arguments */
#define MAX(a, b) ((a) < (b) ? (b) : (a))

//-----------------------------------------------------------------------------
//内部变量定义
//
bool                        busb_mouse_in_en;
bool                        busb_open;
unsigned char               usb_ctrl_flag;

static uint8_t              stall_data_size0;

unsigned char               *g_USB_DataPtr;
unsigned char               g_USB_DataSize;

unsigned char               g_USB_Ep_Status[4];
unsigned char               g_USB_State;
unsigned char               usbrx0fifo[8];

unsigned char               Mouse_Current_Protocol;
unsigned char               Keyboard_Current_Protocol;
unsigned char               Def_Current_Protocol;

unsigned char               Control_Idle;
unsigned char               Keyboard_Idle;
unsigned char               Mouse_Idle;
unsigned char               Def_Idle;

unsigned char               g_sys_alternate;
unsigned char               sof_count;

//----------------------------------------------------------------------------;
//表格定义区
//

/******************************************************************************
* 函数名称: set_stall
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void set_stall(void)
{
    OM_USB->CSR0 |= USB_CSR0_P_SENDSTALL | USB_CSR0_P_RXPKTRDY;
}

void usb_data_size_min(unsigned char length)
{
    g_USB_DataSize = length;
    if((0 == usbrx0fifo[7]) && (usbrx0fifo[6]<length))
        g_USB_DataSize = usbrx0fifo[6];
}

/******************************************************************************
* 函数名称: packetizer_isr_ep0_in
* 功能描述:
* 输入参数: 无
* 输出参数: 无
// This routine is called by functions that shall send their first packet and when the EP0IN interrupt is set
******************************************************************************/
static void packetizer_isr_ep0_in(void)
{
    uint8_t size, i;
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

    // We are getting a ep0in interupt when the host send ACK and do not have any more data to send
    if(g_USB_DataSize == 0)
    {
        if (stall_data_size0 == 1)
        {                                       /* The last data packet is ZLP packet. */
          USB_EP0_TXDATAEND();
          //USB_EP0_DSTALL();
        }
        else
        {
          stall_data_size0 = 1;
        }
        return;
    }

    size = MIN(g_USB_DataSize, USB_EP0_FIFO_SIZE);
    // Copy data to the USB-controller buffer
    for(i = 0; i < size; i++)
    {
        *fifo_ep0 = g_USB_DataPtr[i];
    }

    if (size < USB_EP0_FIFO_SIZE) {
        stall_data_size0 = 1;
        /* The last data packet is partial packet. */
        USB_EP0_TXDATAEND();
    }
    else
    {
        // Tell the USB-controller how many bytes to send
        // If a IN is received from host after this the USB-controller will send the data
        OM_USB->CSR0 |= USB_CSR0_P_TXPKTRDY;
    }

    // Update the packetizer data
    g_USB_DataPtr += size;
    g_USB_DataSize -= size;

    return;
}

/******************************************************************************
* 函数名称: hid_get_idle
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hid_get_idle(void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

    if(usbrx0fifo[0] == 0xA2)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0xA1)
    {
        if(usbrx0fifo[4] == 0xff)     //control interface
        {
            *fifo_ep0 = Control_Idle;
            USB_EP0_TXDATAEND();
        }
        else if(usbrx0fifo[4] == 0x00)     //keyboard interface
        {
            *fifo_ep0 = Keyboard_Idle;
            USB_EP0_TXDATAEND();
        }
        else if(usbrx0fifo[4] == 0x01)     //mouse interface
        {
            *fifo_ep0 = Mouse_Idle;
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();
        }
    }
    else
    {
        set_stall ();
    }
}

/******************************************************************************
* 函数名称: hid_get_protocol
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hid_get_protocol(void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

    if(usbrx0fifo[0] == 0xA2)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0xA1)
    {
        if(usbrx0fifo[4] == 0x00)               // keyboard interface
        {
            *fifo_ep0 = Keyboard_Current_Protocol;
            USB_EP0_TXDATAEND();
        }
        else if(usbrx0fifo[4] == 0x01)          // mouse interface
        {
            *fifo_ep0 = Mouse_Current_Protocol;
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();
        }
    }
    else
    {
        set_stall ();
    }
}

/******************************************************************************
* 函数名称: hid_set_idle
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hid_set_idle (void)
{
    if(usbrx0fifo[0] == 0x21)
    {
		if((usbrx0fifo[2] | usbrx0fifo[3]) == 0x00)
		{
            g_USB_DataSize = 0;
            packetizer_isr_ep0_in();
		}
        else
        {
            if(usbrx0fifo[4] == 0xff)           // control interface
            {
                Control_Idle = usbrx0fifo[3];
                g_USB_DataSize = 0;
                packetizer_isr_ep0_in();
            }
            else if(usbrx0fifo[4] == 0x00)      // keyboard interface
            {
                Keyboard_Idle=usbrx0fifo[3];
                g_USB_DataSize = 0;
                packetizer_isr_ep0_in();
            }
            else if(usbrx0fifo[4] == 0x01)      // mouse interface
            {
                Mouse_Idle = usbrx0fifo[3];
                g_USB_DataSize = 0;
                packetizer_isr_ep0_in();
            }
            else
            {
                set_stall ();
            }
        }
    }
    else
    {
        set_stall ();
    }
}

/******************************************************************************
* 函数名称: hid_set_protocol
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hid_set_protocol (void)
{
    if(0x00 ==usbrx0fifo[2])
        usb_ctrl_flag &= ~bsleep_eable;
    else
        usb_ctrl_flag |= bsleep_eable;

    if(usbrx0fifo[0] == 0x22)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0x21)
    {
        if(usbrx0fifo[4] == 0x00)               // keyboard interface
        {
            Keyboard_Current_Protocol=usbrx0fifo[2];
            USB_EP0_TXDATAEND();
        }
        else if(usbrx0fifo[4] == 0x01)          // mouse interface
        {
            Mouse_Current_Protocol= usbrx0fifo[2];
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();
        }
    }
    else
    {
        set_stall ();
    }
}

/******************************************************************************
* 函数名称: usb_get_status
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
static void usb_get_status(void)
{
    uint8_t  i, *ptr;
    volatile uint16_t *fifo_ep0 = (volatile uint16_t *)&OM_USB->EPnFIFO[0];

    if((usbrx0fifo[2] | usbrx0fifo[3] | usbrx0fifo[7]) || (usbrx0fifo[6] != 2))
    {
        set_stall ();
        return;
    }

    if(g_USB_State == DEV_ADDRESS)
    {
        if(usbrx0fifo[4] != 0x00)
        {
            USB_EP0_STALL();
        }
        else
        {
            *fifo_ep0 = (0 << 8) | 0;
            USB_EP0_TXDATAEND();
        }
    }
    else if(g_USB_State == DEV_CONFIGURED)
    {
        switch(usbrx0fifo[0])
        {
            case 0x80:                          // Device
                if(usbrx0fifo[5] || usbrx0fifo[4])
                {
                    set_stall ();
                }
                else
                {
                    if(0 != (usb_ctrl_flag & bwakeup_usb_enable ))
                        *fifo_ep0 = 0x0002;
                    else
                        *fifo_ep0 = 0x0000;
                    USB_EP0_TXDATAEND();
                }
                break;
            case 0x81:                          // Interface
                if(usbrx0fifo[5] | usbrx0fifo[4])
                {
                    set_stall ();
                }
                else
                {
                    *fifo_ep0 = 0x0000;
                    USB_EP0_TXDATAEND();
                }
                break;
            case 0x82:                          // Endpoint
                if(usbrx0fifo[4] !=0 )
                {
                    if(EP_HALT == g_USB_Ep_Status[usbrx0fifo[4]&0x03])
                        *fifo_ep0 = 0x0001;
                    else
                        *fifo_ep0 = 0x0000;
                    USB_EP0_TXDATAEND();
                }
                else
                {
                    USB_EP0_STALL();
                }
                break;
            default:
                USB_EP0_STALL();

                break;
        }
    }
    else
    {
        USB_EP0_STALL();
    }
}

/******************************************************************************
* 函数名称: usb_clear_feature
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_clear_feature(void)
{
    unsigned char Power_Reg;
    if(usbrx0fifo[0] == 0x00)
    {
        if(usbrx0fifo[2] == 0x01)
        {
            usb_ctrl_flag &= ~(bwakeup_usb_enable);
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();                       // Send procedural stall
        }
    }
    else if(usbrx0fifo[0] == 0x02)              // not clear feature device
    {
        if(usbrx0fifo[4] !=0)
        {
            g_USB_Ep_Status[usbrx0fifo[4]&0x03] = EP_IDLE;
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();                       // Send procedural stall
        }
    }
    else
    {
         set_stall ();                          // Send procedural stall
    }
}

/******************************************************************************
* 函数名称: usb_set_feature
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_set_feature (void)
{
    unsigned char Power_Reg;

    if(usbrx0fifo[0] == 0x00)
    {
        if(usbrx0fifo[2] == 0x01)
        {
            usb_ctrl_flag |= bwakeup_usb_enable;
            USB_EP0_TXDATAEND();
        }
        else
        {
             set_stall ();
        }
    }
    else if(usbrx0fifo[0] == 0x02)
    {
        if(usbrx0fifo[4]!=0)
        {
            g_USB_Ep_Status[usbrx0fifo[4]&0x03] = EP_HALT;
            USB_EP0_TXDATAEND();
        }
        else
        {
            set_stall ();
        }
    }
    else
    {
         set_stall ();
    }
}

/******************************************************************************
* 函数名称: usb_set_address
* 功能描述: 为设备设置一个唯一的地址
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_set_address(void)
{
    if ((usbrx0fifo[0] != 0) || (usbrx0fifo[2] & 0x80)
         || (usbrx0fifo[3] | usbrx0fifo[4] | usbrx0fifo[5] | usbrx0fifo[6] | usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        g_USB_State = DEV_ADDRESS;
        /* After FADDR is updated, HW will accept the packets with the same address field. */
        OM_USB->FADDR = usbrx0fifo[2];
    }
}

/******************************************************************************
* 函数名称: usb_get_descriptor
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
static void usb_get_descriptor(void)
{
    switch(usbrx0fifo[3])
    {
        case DSCR_TYPE_DEV:
            usb_ctrl_flag |= bsleep_eable;

            g_USB_DataPtr = (uint8_t*)DEVICE_Descriptor;
            usb_data_size_min(sizeof(DEVICE_Descriptor));

            packetizer_isr_ep0_in();
            break;
        case DSCR_TYPE_CONFIGURATION:
            // For now we just support one configuration. The asked configuration is stored in LSB(wValue).
            g_USB_DataPtr = (uint8_t*)g_usb_conf_desc;
            usb_data_size_min(sizeof(g_usb_conf_desc));
            packetizer_isr_ep0_in();
            break;
        case DSCR_TYPE_STRING:
  	        switch(usbrx0fifo[2])
  	        {                   // For now we just support english as string descriptor language.
  	            case 0x00:
                    g_USB_DataPtr = (uint8_t*)String0Descriptor;
                    usb_data_size_min(sizeof(String0Descriptor));
  	                packetizer_isr_ep0_in();

  		            break;
  	      	    case 0x01:
                    g_USB_DataPtr = (uint8_t*)string255;
                    usb_data_size_min(sizeof(string255));
                    packetizer_isr_ep0_in();

                    break;
  		        case 0x02:
                    g_USB_DataPtr = (uint8_t*)stringmanufacturer;
                    usb_data_size_min(sizeof(stringmanufacturer));
                    packetizer_isr_ep0_in();

  		            break;
  		        case 0x03:
                    g_USB_DataPtr = (uint8_t*)StringDescSerialNum;
                    usb_data_size_min(sizeof(StringDescSerialNum));
                    packetizer_isr_ep0_in();

  		            break;
  		        default:
  		            USB_EP0_STALL();
  		            break;
  	        }
  	        break;
        case USB_INTERFACE_DESCRIPTOR_TYPE:
        case USB_ENDPOINT_DESCRIPTOR_TYPE:
        case USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
        case USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE:
        case USB_INTERFACE_POWER_DESCRIPTOR_TYPE:
            USB_EP0_STALL();

            break;
        case HID_HID_DESCRIPTOR_TYPE:
            if(0 == LSB(usbrx0fifo[4]))
            {
                g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_KB;
                usb_data_size_min(sizeof(DeviceHidDescriptor_KB));
                packetizer_isr_ep0_in();
            }
            else if(1 == LSB(usbrx0fifo[4]))
            {
                g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_DEF;
                usb_data_size_min(sizeof(DeviceHidDescriptor_DEF));
                packetizer_isr_ep0_in();
            }
            break;
        case  DSCR_TYPE_HID_REPORT:
            if(0 == LSB(usbrx0fifo[4]))
            {
                g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Keyboard_6key;
                usb_data_size_min(sizeof(HID_ReportDescriptor_Keyboard_6key));
                packetizer_isr_ep0_in();
            }
            else if(1 == LSB(usbrx0fifo[4]))
            {
                g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Define;
                usb_data_size_min(sizeof(HID_ReportDescriptor_Define));
                packetizer_isr_ep0_in();
            }
            break;
        default:
            USB_EP0_STALL();
            break;
    }
}

/******************************************************************************
* 函数名称: usb_get_config
* 功能描述: 获得设备的当前配置值
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_get_config (void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

    if((usbrx0fifo[0] != 0x80) || (usbrx0fifo[6] != 1)
        || (usbrx0fifo[2] | usbrx0fifo[3] | usbrx0fifo[4]  | usbrx0fifo[5] | usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        if (g_USB_State == DEV_CONFIGURED)
        {
            *fifo_ep0 = 0x01;
            USB_EP0_TXDATAEND();
        }
        else if (g_USB_State == DEV_ADDRESS)
        {
            *fifo_ep0 = 0x00;
            USB_EP0_TXDATAEND();
        }
    }
}

/******************************************************************************
* 函数名称: usb_set_config
* 功能描述: 激活设备的某个配置
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_set_config(void)
{
    if((g_USB_State == DEV_DEFAULT) || (usbrx0fifo[0] != 0) || (usbrx0fifo[2] > 1)
        || (usbrx0fifo[3]) | (usbrx0fifo[4]) | (usbrx0fifo[5]) | (usbrx0fifo[6]) | (usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        if(usbrx0fifo[2] > 0)                   // Any positive configuration request
        {                                       // results in configuration being set to 1
            g_USB_State = DEV_CONFIGURED;
            g_USB_Ep_Status[1] = EP_IDLE;       // Set endpoint status to idle (enabled)
            g_USB_Ep_Status[2] = EP_IDLE;
            g_USB_Ep_Status[3] = EP_IDLE;
            USB_EP0_TXDATAEND();

            usb_ctrl_flag |= bep1_ep2_enable;

            /* SW enable wakeup irq here after enumerated, so
             * USB wakeup signal is skipped when reset firmware*/
            NVIC_EnableIRQ(USB_WK_IRQn);
            /* HW will clear POWER register upon USB reset.
             * SW enable suspend mode here after enumerated, so
             * USB suspend signal is skipped when reset firmware.
             * Don't toggle this enable bit, otherwise a fake suspend irq will occur*/
            OM_USB->POWER = USB_POWER_ENABLE_SUSPEND;
        }
        else
        {
            g_USB_State = DEV_ADDRESS;          // Unconfigures device by setting state to
            g_USB_Ep_Status[1] = EP_HALT;       // address, and changing endpoint 1 and 2
            g_USB_Ep_Status[2] = EP_HALT;       // status to halt
            g_USB_Ep_Status[3] = EP_HALT;       // status to halt
            USB_EP0_TXDATAEND();
        }
    }
}

/******************************************************************************
* 函数名称: usb_get_interface
* 功能描述: 获得设备接口当前工作的选择设置值
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_get_interface (void)
{                                               // only one interface is supported by
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

    if (usbrx0fifo[0] == 0x81)
    {
        *fifo_ep0 = g_sys_alternate;
        USB_EP0_TXDATAEND();
    }
    else
    {
        set_stall();
    }
}

/******************************************************************************
* 函数名称: usb_set_interface
* 功能描述: 设置接口
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_set_interface (void)
{
    if (usbrx0fifo[0] == 0x01)
    {
        if(usbrx0fifo[5] == 0x00)               // interface 0
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[1] = EP_IDLE;
        }
        else if(usbrx0fifo[5] == 0x01)          // interface 1
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[2] = EP_IDLE;
        }
        else if(usbrx0fifo[5] == 0x02)          // interface 2
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[3] = EP_IDLE;
        }
        g_USB_DataSize = 0;
        packetizer_isr_ep0_in();
    }
    else
    {
	    set_stall(); 
    }
}
static void __attribute__((noinline)) usb_setup_process(void)
{
    // bmRequestType = 0 01 xxxxx : Data transfer direction: Host-to-device, Type: Class
    if((usbrx0fifo[0] & 0x60 ) == 0x20)  // Class request
    {
        if(usbrx0fifo[1] == STD_RQST_GET_DESCRIPTOR )
        {
            switch( usbrx0fifo[3] )
            {
                case HID_HID_DESCRIPTOR_TYPE:
                    if(0 == LSB(usbrx0fifo[4]))
                    {
                        g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_KB;
                        usb_data_size_min(sizeof(DeviceHidDescriptor_KB));
                        packetizer_isr_ep0_in();
                    }
                    else if(1 == LSB(usbrx0fifo[4]))
                    {
                        g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_DEF;
                        usb_data_size_min(sizeof(DeviceHidDescriptor_DEF));
                        packetizer_isr_ep0_in();
                    }
                    break;
                case  DSCR_TYPE_HID_REPORT:
                    if(0 == LSB(usbrx0fifo[4]))
                    {
                        g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Keyboard_6key;
                        usb_data_size_min(sizeof(HID_ReportDescriptor_Keyboard_6key));
                        packetizer_isr_ep0_in();
                    }
                    else if(1 == LSB(usbrx0fifo[4]))
                    {
                        g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Define;
                        usb_data_size_min(sizeof(HID_ReportDescriptor_Define));
                        packetizer_isr_ep0_in();
                    }
                    break;
                default:
                    USB_EP0_STALL();
                    break;
            }
        } 
        else  //if(( usbrx0fifo[0] & 0x20 ) == 0x20) // This is a class specific request D5..6: Type Class(value 1)
        { 
            switch( usbrx0fifo[1] )
            {
                case 0x01:                          // Get_Report
                    USB_EP0_STALL();
                    break;
                case 0x02:                          // Get_Idle
                    hid_get_idle();
                    break;
                case 0x0a:                          // Set_Idle;
                    hid_set_idle();
                    break;
                case 0x03:                          // Get_Protocol
                    hid_get_protocol();
                    break;
                case 0x0b:                          // Set_Protocol
                    hid_set_protocol();
                    break;
                case 0x09:                          // Set_Report
                    usb_ctrl_flag |= busb_report_set;
                    ep0_state = USB_EP0_RX;
                    break;
                default:
                    USB_EP0_STALL();
                    break;
            }
        }
// Call the callback function. Data to be sent back to the host is store by the callback in data_ptr and the size in data_size.
    }
    // bmRequestType = 0 00 xxxxx : Data transfer direction: Host-to-device Type: Standard
    else if((usbrx0fifo[0] & 0x60) == 0x00)
    {
        switch(usbrx0fifo[1])
        {
            case STD_RQST_GET_STATUS:
                usb_get_status();
                break;
            case STD_RQST_CLEAR_FEATURE:
                usb_clear_feature();
                break;
            case STD_RQST_SET_FEATURE:
                usb_set_feature();
                break;
            case STD_RQST_RSVD1:
                break;
            case STD_RQST_SET_ADDRESS:
                usb_set_address();
                break;
            case STD_RQST_GET_DESCRIPTOR:
                usb_get_descriptor();
                break;
            case STD_RQST_SET_DESCRIPTOR:
                break;
            case STD_RQST_GET_CONFIGURATION:
                usb_get_config();
                break;
            case STD_RQST_SET_CONFIGURATION:
                usb_set_config();
                break;
            case STD_RQST_GET_INTERFACE: // GET_INTERFACE
                usb_get_interface();
                break;
            case STD_RQST_SET_INTERFACE: // SET_INTERFACE (We do not support this)
                usb_set_interface();
                break;
            case STD_RQST_SYNCH_FRAME:   // SYNCH_FRAME (We do not support this)
                break;
            default:
                USB_EP0_STALL();
                break;
        }
    }
    else // Unknown request type
    {
        USB_EP0_STALL();
    }
}

extern bool    busb_valid;

/******************************************************************************
* 函数名称: HIDDataProcess
* 功能描述: 处理HID数据
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
static void usb_ep_setup(void)
{
    OM_USB->INDEX = 1;
    OM_USB->INTR_TXEN1 |= (1<<1);
    OM_USB->TXMAXP = USB_EP1_FIFO_SIZE / 8;
    OM_USB->TXCSR2 |= USB_TXCSR_MODE >> 8;      /* Enable the EP direction as Tx. */

    OM_USB->INDEX = 2;
    OM_USB->INTR_TXEN1 |= (1<<2);
    OM_USB->TXMAXP = USB_EP2_FIFO_SIZE / 8;
    OM_USB->TXCSR2 |= USB_TXCSR_MODE >> 8;      /* Enable the EP direction as Tx. */

    OM_USB->INDEX = 3;
    OM_USB->INTR_TXEN1 |= (1<<3);
    OM_USB->TXMAXP = USB_EP3_FIFO_SIZE / 8;
    OM_USB->TXCSR2 |= USB_TXCSR_MODE >> 8;      /* Enable the EP direction as Tx. */

    OM_USB->INDEX = 0;

    NVIC_EnableIRQ(USB_WK_IRQn);
    OM_USB->POWER = USB_POWER_ENABLE_SUSPEND;
}

static void usb_reset_process(void)
{
    ep0_state = USB_EP0_WAITING_SETUP;

    g_USB_State = DEV_DEFAULT;
    usb_ctrl_flag &= ~(bwakeup_usb_enable|bep1_ep2_enable|busb_suspend_resume);
    usb_ctrl_flag |= bsleep_eable;

    g_USB_Ep_Status[1] = EP_HALT;
    g_USB_Ep_Status[2] = EP_HALT;
    g_USB_Ep_Status[3] = EP_HALT;

    /* SW must re-setup endpoints because TXCSR, TXMAP, RXMAP is clear by usb reset. */
    usb_ep_setup();
}

/******************************************************************************
* 函数名称: USB_WK_IRQHandler
* 功能描述:
* 说    明:
******************************************************************************/
void USB_WK_IRQHandler(void)
{
    /*
     * It costs ~37us or ~27us to reach here.
     * hcache on:  1800-cycle@48MHz      ;  6800-cycle if keep PLL on?
     * hcache off: 1300-cycle@48MHz, 1500; 13000-cycle if keep PLL on?
     */
    OM_RCC->USB_WK_INT_CLR = 0x01; //w1c

    // We are awoken by the bus
    //g_hal_usb.bm_state |= USB_BM_STATE_HOST_WU;

    // Check if the wakeup source is the pin to the USB controller
    // If it is by the pin to the USB controller we want to start
    // a remote wakeup

    //NVIC_EnableIRQ(RTC_IRQn);
    usb_ctrl_flag &= ~busb_suspend_resume;
}

extern uint32_t sleep_into_work_rtc;

/******************************************************************************
* 函数名称: USB_IRQHandler
* 功能描述:
* 说    明:
******************************************************************************/
void USB_IRQHandler(void)
{
    unsigned char ep_in_if = OM_USB->INTR_TX1;
    unsigned char ep_out_if = OM_USB->INTR_RX1;
    unsigned char common_if = OM_USB->INTR_USB;

    usb_ctrl_flag &= ~busb_suspend_resume;

    if(ep_in_if & 0x01)
    {
        OM_USB->INDEX = 0;
        unsigned char csr0 = OM_USB->CSR0;

        if(csr0 & USB_CSR0_P_SENTSTALL)
        {                   /* After SENDSTALL, hw raise this EP0 interrupt. */
            OM_USB->CSR0 &= ~USB_CSR0_P_SENTSTALL;
            ep0_state = USB_EP0_WAITING_SETUP;
        }
        if(csr0 & USB_CSR0_P_SETUPEND)
        {                   /* A control transation ends. */
            OM_USB->CSR0 |= USB_CSR0_P_SERVICED_SETUPEND;
            ep0_state = USB_EP0_WAITING_SETUP;
        }

        switch (ep0_state)
        {
            case USB_EP0_WAITING_STS:
            case USB_EP0_SENDING_STS:
                /* Status stage: hw raise this extra EP0 interrupt. */
                ep0_state = USB_EP0_WAITING_SETUP;
                /* fallthrough because USB_CSR0_P_RXPKTRDY might raise also. */

            case USB_EP0_WAITING_SETUP:
                if (csr0 & USB_CSR0_P_RXPKTRDY)
                {
                    /* Setup token. */
                    g_USB_DataPtr = NULL;
                    g_USB_DataSize = 0;
                    stall_data_size0 = 0;

                    /* Setup data valid. */
                    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

                    // Parsing the request into request structure
                    usbrx0fifo[0] = *fifo_ep0;
                    usbrx0fifo[1] = *fifo_ep0;
                    usbrx0fifo[2] = *fifo_ep0;
                    usbrx0fifo[3] = *fifo_ep0;
                    usbrx0fifo[4] = *fifo_ep0;
                    usbrx0fifo[5] = *fifo_ep0;
                    usbrx0fifo[6] = *fifo_ep0;
                    usbrx0fifo[7] = *fifo_ep0;

                    if(0 == usbrx0fifo[6])
                    {   /* Move to status stage for Zero Data Request. */
                        ep0_state = USB_EP0_SENDING_STS;
                        /* Don't set USB_CSR0_P_DATAEND alone, otherwise it won't self-clearing,
                         then HW will send IN ZLP Status packets automatically. */
                        OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY | USB_CSR0_P_DATAEND;
                    }
                    else
                    {
                        if(usbrx0fifo[0] & 0x80)
                            ep0_state = USB_EP0_TX;
                        else
                            ep0_state = USB_EP0_RX;
                        /* Inform HW that setup packet is read, and HW will send ACK pakcet automatically. */
                        OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY;
                    }

                    if((0x21==usbrx0fifo[0])&&(0x09==usbrx0fifo[1]))
                    {
                        usb_ctrl_flag |= busb_report_set;
                        ep0_state = USB_EP0_RX;
                    }
                    else
                        usb_setup_process();
                }

                break;
            case USB_EP0_RX:
                if (csr0 & USB_CSR0_P_RXPKTRDY)
                {   /* Data stage: EP0 out. */
                    g_USB_DataSize = 0;

                    /* Class Interface, HID Set Report: usb status in the encrypted user data? */
                    if(0 != (usb_ctrl_flag&busb_report_set))
                    {
                        volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&OM_USB->EPnFIFO[0];

                        usb_ctrl_flag &= ~busb_report_set;
                        if(32 == usbrx0fifo[6])
                        {
                            for(unsigned char i=0; i<32; i++)
                                out_report_data[i] = *fifo_ep0;

                            hid_ctrl_reg |= bhid_data_process;
                        }
                        else if(1 == usbrx0fifo[6])
                        {
                            kb_led_status = (*fifo_ep0&0x07);
                        }
                    }

                    OM_USB->CSR0 |= USB_CSR0_P_SERVICED_RXPKTRDY | USB_CSR0_P_DATAEND;
                    ep0_state = USB_EP0_WAITING_SETUP;
                }
                break;
            case USB_EP0_TX:
                /* Data stage: EP0 in. */
                packetizer_isr_ep0_in();

                break;
            default:

                break;
        }
    }

    if(common_if & USB_INTR_SUSPEND)
    {
        usb_ctrl_flag |= busb_suspend_resume;
    }

    if(common_if & USB_INTR_RESET)
    {
        usb_reset_process();
    }

    if(common_if & USB_INTR_SOF)
    {
        busb_valid = true;
        sys_tick_count++;
        sof_count++;
        if(0==(sof_count&0x07))
            drv_ledc_write();

        if((iREPORT_1000 == report_usb)
            ||(iREPORT_500 == report_usb))
        {
            if(0==(sof_count&0x03))
                sys_ctrl |= bscan_flag;
        }
        else if(iREPORT_250 == report_usb)
        {
            if(0==(sof_count&0x03))
                sys_ctrl |= bscan_flag;
        }
        else //if(iREPORT_125 == report_usb)
        {
            if(0==(sof_count&0x07))
                sys_ctrl |= bscan_flag;
        }

        sleep_into_work_rtc = drv_rtc_read(OM_RTC);
    }

    if(ep_in_if)
    {
        if(ep_in_if & (1<<1))
            g_USB_Ep_Status[1] = EP_IDLE;
        if (ep_in_if & (1<<2))
            g_USB_Ep_Status[2] = EP_IDLE;
        if (ep_in_if & (1<<3))
            g_USB_Ep_Status[3] = EP_IDLE;
    }
}

extern void delayus(unsigned int time);

/******************************************************************************
* 函数名称: hal_usb_init
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hal_usb_init(void)
{
    uint8_t ei;

    // Setup state information
    g_USB_State = DEV_DEFAULT;
    stall_data_size0 = 0;

    /* Switch on USB PLL & USB module */
    drv_pmu_syspll_ctrl(PMU_PLL_CTRL_START);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_USB, 1U);
    /* USB wakeup clock @32KHz. */
    OM_RCC->USB_WK_CLK_SEL = 1;

    // Disconnect from USB-bus if we are in this routine from a power on and not a soft reset
    OM_RCC->USB_CTRL = 0; // disconnect
    delayus(50000);
    /* Enable pull-up on usb port */
    drv_pmu_pin_mode_set(2, PMU_PIN_MODE_FLOAT);
    drv_pmu_pin_mode_set(3, PMU_PIN_MODE_FLOAT);

    OM_RCC->USB_CTRL = (0x1 << 4); // connect

    // Setup interrupts
    OM_USB->INTR_USBEN = USB_INTR_RESET | USB_INTR_RESUME | USB_INTR_SUSPEND|USB_INTR_SOF;
    OM_USB->INTR_TXEN1 = 0x01;
    NVIC_EnableIRQ(USB_IRQn);

    // Set all endpoints to not valid (except EP0IN and EP0OUT)
    for(ei = 1; ei < 8; ei++)
    {
        OM_USB->INDEX = ei;
        OM_USB->TXMAXP = 0;
        OM_USB->RXMAXP = 0;
    }
}

/******************************************************************************
* 函数名称: hi5_usb_init
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void hi5_usb_init(void)
{
    if(true == busb_open)
        return;
    
    busb_open = true;
    // USB HAL initialization
    hal_usb_init();
    usb_ep_setup();

    /* Scan mouse in RTC ISR. */
    //NVIC_DisableIRQ(RTC_IRQn);

    //usb_ctrl_flag |= busb_suspend_resume;
    usb_ctrl_flag &= ~busb_suspend_resume;
    usb_ctrl_flag &= ~bwakeup_usb_enable;
    g_USB_Ep_Status[1] = EP_HALT;
    g_USB_Ep_Status[2] = EP_HALT;
    g_USB_Ep_Status[3] = EP_HALT;
}

/******************************************************************************
* 函数名称: usb_disconnect
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void usb_disconnect(void)
{
    busb_open = false;

    OM_RCC->USB_CTRL = 0;                       // disconnect
//    DRV_RCC_CLOCK_ENABLE(RCC_CLK_USB, 0U);

    drv_pmu_pin_mode_set(2, PMU_PIN_MODE_PD);
    drv_pmu_pin_mode_set(3, PMU_PIN_MODE_PD);
}

