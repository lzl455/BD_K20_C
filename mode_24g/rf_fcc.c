/*******************************************************************************
* Copyright (c) 2009, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: rf_connect_check.c
* 文件描述: RF对码检测
*******************************************************************************/
#include "main_24g.h"
#include "hid_process.h"
#include "usb_cfg_info.h"

//----------------------------------------------------------------------------;
//变量定义
//
extern unsigned char            dat_24g_0[];

#define test_ctrl               dat_24g_0[26]
//{
    #define bkey_swtich_en      (1<<7)
    #define bkey_wave_en        (1<<6)
    #define bkey_freq_en        (1<<5)
    #define bkey_tx_en          (1<<4)

    #define bkey_swtich_press   (1<<3)
    #define bkey_wave_press     (1<<2)
    #define bkey_freq_press     (1<<1)
    #define bkey_tx_press       (1<<0)
//}

#define test_mode               dat_24g_0[27]
#define test_freq               dat_24g_0[28]
#define test_power              dat_24g_0[29]
#define tx_time                 dat_24g_0[30]
#define idle_time               dat_24g_0[31]

extern void wait_irq(void);

//----------------------------------------------------------------------------;
// 表格定义区
//
unsigned char           const    fcc_hop_freq_tbl[] ={
    (2402 - 2400),
    (2468 - 2400),
	(2432 - 2400),
	(2448 - 2400),
	(2464 - 2400),
	(2404 - 2400),
	(2450 - 2400),
	(2440 - 2400),
	(2428 - 2400),
	(2410 - 2400),
	(2476 - 2400),
	(2412 - 2400),
	(2454 - 2400),
	(2418 - 2400),
	(2470 - 2400),
	(2480 - 2400),
};

unsigned char           const    fcc_tx_freq_tbl[] ={
    (2402 - 2400),
    (2440 - 2400),
	(2480 - 2400),
	(2440 - 2400),
};

/******************************************************************************
* 函数名称: hid_cmd_fcc_test
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void hid_cmd_fcc_test(void)
{
    uint8_t i, fcc_temp;
    uint32_t rtc_temp;

    mRF_CE_LOW_IDLE;
    delayus(250);
    DRV_RCC_RESET(RCC_RST_RF_FSM);
    mFLUSH_FIFO;

    drv_rf24g_init();

    test_freq = out_report_data[3];
    test_power = (out_report_data[4] & 0x1F);
    tx_time = out_report_data[5];
    idle_time = out_report_data[6];

    drv_rf_set_tx_power(test_power);

    switch(out_report_data[2])
    {
        case iHID_CMD_FCC_FREQ:                 // 跳频测试
            OM_RF->CONFIG = 0x8A;

            while(1)
            {
                rtc_temp = drv_rtc_read(OM_RTC);
                while(1)
                {
                    drv_wdt_keep_alive(OM_WDT);
                    if(hid_ctrl_reg & bhid_data_process)
                        return;
                    if(mMS_TO_TICK(2) < drv_rtc_read(OM_RTC)-rtc_temp)
                        break;
                }

                mFLUSH_FIFO;
                mRF_CLR_STATUS;

                test_freq++;
                if(test_freq < 40)
                {
                    if(freq_index>=16)
                        freq_index = 0;
                        
                    OM_RF->RF_CH = fcc_hop_freq_tbl[freq_index&0x0F];	
                }
                else
                {
                    if(freq_index>=40)
                        freq_index = 0;
                    OM_RF->RF_CH = ((freq_index<<1)+2);	
                }

                if(0 == tx_time)
                    tx_time = 1;

                drv_rf_write_tx_payload_noack(rf_data_fifo, tx_time&0x1F);
                OM_RF->CE_PULSE = 1;
                wait_irq();
            }

            break;
        case iHID_CMD_FCC_TX:
            OM_RF->CONFIG = 0x8A;
            OM_RF->RF_CH = test_freq;

            /* random tx */
            OM_RF->AGC_CTRL |= (1<<23);
            OM_RF->CAL_CTL  |= (1<<14);

            mRF_CE_HIGH_TX;
            while(1)
            {
                drv_wdt_keep_alive(OM_WDT);
                OM_RF->AGC_CTRL |= (1<<23) ;
                if((0 == tx_time) ||(0 == idle_time))
                {
                    while(1)
                    {
                        drv_wdt_keep_alive(OM_WDT);
                        if(0!=(hid_ctrl_reg & bhid_data_process))
                            break;
                    }
                    goto fcc_hspf_test_out;
                }
    
                for(fcc_temp=0; fcc_temp<=tx_time; fcc_temp++)
                {
                    if(0!=(hid_ctrl_reg & bhid_data_process))
                        goto fcc_hspf_test_out;

                    delayus(95);
                }
    
                OM_RF->AGC_CTRL &= ~(1<<23) ;
                for(fcc_temp=1; fcc_temp<=idle_time; fcc_temp++)
                {
                    if(0!=(hid_ctrl_reg & bhid_data_process))
                        goto fcc_hspf_test_out;
                    delayus(95);
                }
            }
fcc_hspf_test_out:
            mRF_CE_LOW_TX;

            OM_RF->AGC_CTRL &= ~(1<<23);
            OM_RF->CAL_CTL &= ~(1<<14);

            break;
        case iHID_CMD_FCC_RX:
            OM_RF->CONFIG = 0x8B;
            OM_RF->RF_CH = test_freq;

            mRF_CE_HIGH_RX;
            while(1)
            {
                drv_wdt_keep_alive(OM_WDT);
                if(0!=(hid_ctrl_reg & bhid_data_process))
                    break;
            }
            mRF_CE_LOW_RX

            break;
        case iHID_CMD_FCC_CONT_WAVE:
            OM_RF->CONFIG = 0x8A;
            OM_RF->RF_SETUP |= 0x80;
            OM_RF->RF_CH = test_freq;
            OM_RCC->CLKGATE |= RCC_DEV_CLK_GATE_SWD_CLK_GATE_MASK; // disable jtag

            mRF_CE_HIGH_RX;
            while(1)
            {
                drv_wdt_keep_alive(OM_WDT);
                if(0!=(hid_ctrl_reg & bhid_data_process))
                    break;
            }
            mRF_CE_LOW_RX
            OM_RCC->CLKGATE &= ~RCC_DEV_CLK_GATE_SWD_CLK_GATE_MASK; // disable jtag

            break;
    }
}

/******************************************************************************
* 函数名称: key_into_fcc_test
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void fcc_test_key_scan(void)
{
    drv_wdt_keep_alive(OM_WDT);
    matrixkey_scan();
    if(0 != (matrix_status[iKEY_FCC_TX_C]&iKEY_FCC_TX_R))
    {
        if(0==(test_ctrl&bkey_tx_press))
        {
            test_ctrl |= bkey_tx_press;
            test_ctrl |= bkey_tx_en;
        }
    }
    else
    {
        test_ctrl &= ~bkey_tx_press;
    }

    if(0 != (matrix_status[iKEY_FCC_FREQ_C]&iKEY_FCC_FREQ_R))
    {
        if(0==(test_ctrl&bkey_freq_press))
        {
            test_ctrl |= bkey_freq_press;
            test_ctrl |= bkey_freq_en;
        }
    }
    else
    {
        test_ctrl &= ~bkey_freq_press;
    }

    if(0 != (matrix_status[iKEY_FCC_WAVE_C]&iKEY_FCC_WAVE_R))
    {
        if(0==(test_ctrl&bkey_wave_press))
        {
            test_ctrl |= bkey_wave_press;
            test_ctrl |= bkey_wave_en;
        }
    }
    else
    {
        test_ctrl &= ~bkey_wave_press;
    }

    if(0 != (matrix_status[iKEY_SWTICH_FREQ_C]&iKEY_SWTICH_FREQ_R))
    {
        if(0==(test_ctrl&bkey_swtich_press))
        {
            test_ctrl |= bkey_swtich_press;
            test_ctrl |= bkey_swtich_en;
        }
    }
    else
    {
        test_ctrl &= ~bkey_swtich_press;
    }
}

/******************************************************************************
* 函数名称: key_into_fcc_test
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void key_into_fcc_test(void)
{
    uint8_t i, fcc_temp;
    uint32_t rtc_temp;

    if(0 == (matrix_status[iKEY_FN_C]&iKEY_FN_R))
        return;
    if(0 == (matrix_status[iKEY_SWTICH_FREQ_C]&iKEY_SWTICH_FREQ_R))
        return;

    if(iDEVICE_TYPE_24G == device_type)
    {
        if(0 == (matrix_status[iKEY_24G_C]&iKEY_24G_R))
            return;

    }
    else if(iDEVICE_TYPE_BT0 == device_type)
    {
        if(0 == (matrix_status[iKEY_BT0_C]&iKEY_BT0_R))
            return;
    }
    else
        return;

    OM_CRITICAL_BEGIN();
    NVIC_ClearPendingIRQ(RF_IRQn);
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_DisableIRQ(RF_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);
    
    test_mode = iHID_CMD_FCC_TX;
    test_ctrl = bkey_swtich_press;

    if(iDEVICE_TYPE_24G == device_type)
    {
        brf_rate = true;
        drv_rf24g_init();
    }
    else
    {
        brf_rate = false;
        drv_rf24g_init();
    }

    drv_rf_set_tx_power(DRV_RF_PA_PWR_2dBm);

    while(1)
    {
        mRF_CE_LOW_IDLE;
        delayus(250);

        if(iHID_CMD_FCC_FREQ == test_mode)
        {
//-----------------------------------------------------------------------------
// 跳频
            DRV_RCC_RESET(RCC_RST_RF_FSM);
            OM_RF->CONFIG = 0x8A;

            while(1)
            {
                rtc_temp = drv_rtc_read(OM_RTC);
                fcc_test_key_scan();
                if(0 != (test_ctrl&bkey_tx_en))
                {
                    test_ctrl &= ~bkey_tx_en;
                    test_mode = iHID_CMD_FCC_TX;
                    goto fcc_test_end;
                }
                if(0 != (test_ctrl&bkey_freq_en))
                {
                    test_ctrl &= ~bkey_freq_en;
//                    test_mode = iHID_CMD_FCC_FREQ;
//                    goto fcc_test_end;
                }
                if(0 != (test_ctrl&bkey_wave_en))
                {
                    test_ctrl &= ~bkey_wave_en;
                    test_mode = iHID_CMD_FCC_CONT_WAVE;
                    goto fcc_test_end;
                }

                mFLUSH_FIFO;
                mRF_CLR_STATUS;

                if(0 == (test_ctrl&bkey_swtich_press))
                {                               // 松开16个频点
                    if(freq_index>=16)
                        freq_index = 0;
                    OM_RF->RF_CH = fcc_hop_freq_tbl[freq_index&0x0F];	
                }
                else
                {                               // 按住40个频点
                    if(freq_index>=40)
                        freq_index = 0;
                    OM_RF->RF_CH = ((freq_index<<1)+2);	
                }

                drv_rf_write_tx_payload_noack(rf_data_fifo, 16);
                OM_RF->CE_PULSE = 1;
                wait_irq();

                while(1)
                {
                    if(mMS_TO_TICK(2) < drv_rtc_read(OM_RTC)-rtc_temp)
                        break;
                }

                freq_index++;
            }
        }
        else if(iHID_CMD_FCC_TX == test_mode)
        {
            test_freq = 0;
            while(1)
            {
//----------------------------------------------
// TX
                OM_RF->CONFIG = 0x8A;
                OM_RF->RF_CH = fcc_tx_freq_tbl[test_freq&0x03];

                /* random tx */
                OM_RF->AGC_CTRL |= (1<<23);
                OM_RF->CAL_CTL  |= (1<<14);

                mRF_CE_HIGH_TX;
                while(1)
                {
                    rtc_temp = drv_rtc_read(OM_RTC);

                    OM_RF->AGC_CTRL |= (1<<23) ;
                    delayus(500);
                    OM_RF->AGC_CTRL &= ~(1<<23) ;

                    fcc_test_key_scan();
                    if(0 != (test_ctrl&bkey_swtich_en))
                    {
                        test_ctrl &= ~bkey_swtich_en;
                        break;                  // 切换到接收状态
                    }
                    if(0 != (test_ctrl&bkey_tx_en))
                    {
                        test_ctrl &= ~bkey_tx_en;
                        //test_mode = iHID_CMD_FCC_TX;
                        //goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_freq_en))
                    {                           // 切换到跳频
                        test_ctrl &= ~bkey_freq_en;
                        test_mode = iHID_CMD_FCC_FREQ;
                        goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_wave_en))
                    {                           // 切换到空载
                        test_ctrl &= ~bkey_wave_en;
                        test_mode = iHID_CMD_FCC_CONT_WAVE;
                        goto fcc_test_end;
                    }

                    while(1)
                    {
                        if(mMS_TO_TICK(2) < drv_rtc_read(OM_RTC)-rtc_temp)
                            break;
                    }
                }
                mRF_CE_LOW_TX;

                OM_RF->AGC_CTRL &= ~(1<<23);
                OM_RF->CAL_CTL &= ~(1<<14);
//----------------------------------------------
// RX
                OM_RF->CONFIG = 0x8B;
                mRF_CE_HIGH_RX;
                while(1)
                {
                    rtc_temp = drv_rtc_read(OM_RTC);

                    fcc_test_key_scan();
                    if(0 != (test_ctrl&bkey_swtich_en))
                    {
                        test_ctrl &= ~bkey_swtich_en;
                        break;
                    }
                    if(0 != (test_ctrl&bkey_tx_en))
                    {
                        test_ctrl &= ~bkey_tx_en;
                        //test_mode = iHID_CMD_FCC_TX;
                        //goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_freq_en))
                    {
                        test_ctrl &= ~bkey_freq_en;
                        test_mode = iHID_CMD_FCC_FREQ;
                        goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_wave_en))
                    {
                        test_ctrl &= ~bkey_wave_en;
                        test_mode = iHID_CMD_FCC_CONT_WAVE;
                        goto fcc_test_end;
                    }

                    while(1)
                    {
                        if(mMS_TO_TICK(2) < drv_rtc_read(OM_RTC)-rtc_temp)
                            break;
                    }
                }

                mRF_CE_LOW_TX;
                test_freq++;
            }
        }
        else if(iHID_CMD_FCC_CONT_WAVE == test_mode)
        {
            test_freq = 0;
            while(1)
            {
//----------------------------------------------
// 空载波
                OM_RF->CONFIG = 0x8A;
                OM_RF->RF_SETUP |= 0x80;
                OM_RF->RF_CH = fcc_tx_freq_tbl[test_freq&0x03];

                mRF_CE_HIGH_TX;

                while(1)
                {
                    rtc_temp = drv_rtc_read(OM_RTC);
                    fcc_test_key_scan();
                    if(0 != (test_ctrl&bkey_swtich_en))
                    {
                        test_ctrl &= ~bkey_swtich_en;
                        break;
                    }
                    if(0 != (test_ctrl&bkey_tx_en))
                    {
                        test_ctrl &= ~bkey_tx_en;
                        test_mode = iHID_CMD_FCC_TX;
                        goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_freq_en))
                    {
                        test_ctrl &= ~bkey_freq_en;
                        test_mode = iHID_CMD_FCC_FREQ;
                        goto fcc_test_end;
                    }
                    if(0 != (test_ctrl&bkey_wave_en))
                    {
                        test_ctrl &= ~bkey_wave_en;
//                        test_mode = iHID_CMD_FCC_CONT_WAVE;
//                        goto fcc_test_end;
                    }

                    if(mMS_TO_TICK(2) < drv_rtc_read(OM_RTC)-rtc_temp)
                        break;
                }

                mRF_CE_LOW_TX;
                test_freq++;
                delayus(1000);
            }
        }

fcc_test_end:
        mRF_CE_LOW_TX;

        OM_RF->AGC_CTRL &= ~(1<<23);
        OM_RF->CAL_CTL &= ~(1<<14);
        OM_RF->RF_SETUP &= ~0x80;

        delayus(100000);
    }

    OM_CRITICAL_END();
}


