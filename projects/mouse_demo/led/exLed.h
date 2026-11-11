/**
 * @file exLogo.h
 * @author cfn
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __EX_LED_
#define __EX_LED_

//-----------------------------------------------------------------------------;
// UART DELAY DEFINE
//
#define CMD_HEARDER_0           0x00
#define CMD_HEARDER_1           0xAA
#define CMD_CS_SUM              0x00

extern uint8_t                  exled_ctrl;

extern uint32_t                 exled;
//{
    #define bled_K7             (1<<27)
    #define bled_K6             (1<<26)
    #define bled_K5             (1<<25)
    #define bled_K4             (1<<24)

    #define bled_K3             (1<<23)
    #define bled_K2             (1<<22)
    #define bled_K1             (1<<21)
    #define bled_K8             (1<<19)
    #define bled_2_G            (1<<18)
    #define bled_2_F            (1<<17)

    #define bled_K9             (1<<15)
    #define bled_2_C            (1<<14)
    #define bled_2_B            (1<<13)
    #define bled_2_E            (1<<11)
    #define bled_2_D            (1<<10)
    #define bled_1_E            (1<<9)
    //#define NULL                (1<<8)

    #define bled_2_A            (1<<7)
    #define bled_1_G            (1<<6)
    #define bled_1_F            (1<<5)
    //#define NULL                (1<<4)
    #define bled_1_D            (1<<3)
    #define bled_1_C            (1<<2)
    #define bled_1_B            (1<<1)
    #define bled_1_A            (1<<0)
//}
extern uint8_t                  exio_ctrl;
//{
    #define bpwm_off            (1<<6)
//}

//-----------------------------------------------------------------------------;
// EXTERN FUNCTION DECLARATION 
//
extern void exLogo_send(void);

#endif  /* __MOUSE_H */
