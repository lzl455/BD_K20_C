/*******************************************************************************
* Copyright (c) 2013, SHENZHEN HUNTERSUN Co.,LTD.
* All rights reserved.
*
* 文件名称: usb_user_process.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include "main_usb.h"
#include "main.h"

/*******************************************************************************
 USB数据的报告ID定义
*******************************************************************************/
//
//-----------------------------------------------------------------------------;

//----------------------------------------------------------------------------;
//外部变量定义
//

//
//----------------------------------------------------------------------------;
//寄存器定义

/******************************************************************************
* 函数名称: sleep_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明: 无
******************************************************************************/
static void system_reset(void)
{
    OM_RCC->USB_CTRL = 0;
    delayus(10000);
    DRV_RCC_RESET(RCC_RST_USB);
    DRV_RCC_RESET(RCC_RST_UART0);
    DRV_RCC_RESET(RCC_RST_GPIO0);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_USB, 0);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_UART0, 0);
    DRV_RCC_CLOCK_ENABLE(RCC_CLK_GPIO0, 0);
}

/******************************************************************************
* 函数名称: jump_to_boot
* 功能描述: 跳转到应用boot
* 输入参数:
* 输出参数:
* 说    明: 无
******************************************************************************/
__RAM_CODE void jump_to_boot(void)
{
    SysTick->CTRL = 0;
    /* Reset interrupt controller. */
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;
    system_reset();
    __disable_irq();

    OM_PMU->BOOT_MODE = 0xAAAA0000;
    OM_RCC->FLASH_OFFSET = 0x66000000;
    //pnc_cpm_reset_sys();
#if defined(__arm__)
  /* The new remapping become available when reset is asserted. */
  //NVIC_SystemReset();
  __DSB();
  /* HW will disable AHB cache after reset, so don't invalidate it here. */
  SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                 SCB_AIRCR_SYSRESETREQ_Msk);
  /* HW will continue XIP while reset request is asserted, so
     NVIC_SystemReset() must be locked in RAM, otherwise XIP will fail here. */
  __DSB();
#endif
  while (1);
}

/******************************************************************************
* 函数名称: usb_data_process()
* 功能描述: USB数据发送处理
* 输入参数: 无
* 输出参数: 无
* 说    明: USB数据发送处理
******************************************************************************/
void usb_data_process(void)
{
    unsigned char ControlReg;
    volatile uint8_t *fifo_epn;

    if(0==(usb_ctrl_flag&bep1_ep2_enable))
    {
        return;
    }

    if(0==(m_data_flag&0x1F))
        return;

__disable_irq();
    OM_USB->INDEX = 1;
    if (OM_USB->TXCSR1 & USB_TXCSR_P_TXPKTRDY)
    {
        //USB_Write_Reg(M_REG_INCSR1, INCSR_SDSTL);
    }
    else if(g_USB_Ep_Status[1] == EP_IDLE)
    {
        if(m_data_flag&bstd_kb_data_send)
        {
            m_data_flag &= ~bstd_kb_data_send;
            fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[1];

            *fifo_epn = std_kb_data_modifier;
            *fifo_epn = 0;
            *fifo_epn = std_kb_data_key1;
            *fifo_epn = std_kb_data_key2;
            *fifo_epn = std_kb_data_key3;
            *fifo_epn = std_kb_data_key4;
            *fifo_epn = std_kb_data_key5;
            *fifo_epn = std_kb_data_key6;

            OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
            g_USB_Ep_Status[1] = EP_TX;
        }
    }

    OM_USB->INDEX = 3;
    if (OM_USB->TXCSR1 & USB_TXCSR_P_TXPKTRDY)
    {
        //USB_Write_Reg(M_REG_INCSR1, INCSR_SDSTL);
    }
    else if(g_USB_Ep_Status[3] == EP_IDLE)
    {
        if(m_data_flag & bstd_ex_data_send)
        {
            m_data_flag &= ~bstd_ex_data_send;

            fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[3];
            *fifo_epn = iREPORT_ID_KB_KEY;
            for(uint8_t i=0; i<15; i++)
                *fifo_epn = std_key[i+7];

            OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
            g_USB_Ep_Status[3] = EP_TX;
        }
        else if(m_data_flag & bmmk_data_send)
        {
            m_data_flag &= ~bmmk_data_send;

            fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[3];
            *fifo_epn = iREPORT_ID_MULTIM_KEY;
            *fifo_epn = mmk_data_l;
            *fifo_epn = mmk_data_h;

            OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
            g_USB_Ep_Status[3] = EP_TX;
        }
        else if(m_data_flag & bhid_data_send)
        {
            m_data_flag &= ~bhid_data_send;

            fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[3];

            *fifo_epn = iREPORT_ID_CUSTOMER_DATA;
            for(unsigned char i=1; i<32; i++)
                *fifo_epn = in_report_data[i];

            OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
            g_USB_Ep_Status[3] = EP_TX;

            if(bjump_boot
				&&(0x55 == out_report_data[2])
                && (0xAA == out_report_data[3])
                && (0x00 == out_report_data[4])
                && (0xFF == out_report_data[5]))
            {
                delayus(5000);
                OM_RCC->USB_CTRL = 0;           // disconnect
		        delayus(200000);

                OM_PMU->SW_RSVD7 = iAPP_INTO_BOOT;
                jump_to_boot();
            }
        }
        else if(m_data_flag&bmouse_data_send)
        {
            m_data_flag &= ~bmouse_data_send;
            if(0 == (usb_ctrl_flag & bsleep_eable))
            {
                fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[3];
                *fifo_epn = (mouse_data_key&0x1F);
                *fifo_epn = (mouse_x&0xFF);
                *fifo_epn = (mouse_y&0xFF);
                *fifo_epn = mouse_data_z;

                OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
                g_USB_Ep_Status[3] = EP_TX;

                mouse_data_z = 0;
            }
            else
            {
                busb_mouse_in_en = false;
                fifo_epn = (volatile uint8_t *)&OM_USB->EPnFIFO[3];

                *fifo_epn = iREPORT_ID_MOUSE;
                *fifo_epn = (mouse_data_key&0x1F);
                *fifo_epn = (mouse_x&0xFF);
                *fifo_epn = (((mouse_x>>8)&0x0f)|((mouse_y<<4)&0xf0));
                *fifo_epn = ((mouse_y>>4)&0xFF);
                *fifo_epn = mouse_data_z;
                *fifo_epn = 0;

                OM_USB->TXCSR1 |= USB_TXCSR_P_TXPKTRDY;
                g_USB_Ep_Status[3] = EP_TX;

                mouse_data_z = 0;
            }
        }
    }
__enable_irq();
}
