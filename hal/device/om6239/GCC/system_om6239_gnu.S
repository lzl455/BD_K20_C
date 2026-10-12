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
 * @file     system_om6239_gnu.S
 * @brief
 * @date     12 Sept. 2023
 * @author   OnMicro SW Team
 *
 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

/*******************************************************************************
 * MACROS
 */
 /* PMU register */
#define __CPU_MSP_SAVED_ADDR                0x4000006CU

 /* NVIC register */
#define __NVIC_ISER_REG_ADDR                0xE000E100U
#define __NVIC_IP_0_REG_ADDR                0xE000E400U
#define __NVIC_IP_1_REG_ADDR                0xE000E404U
#define __NVIC_IP_2_REG_ADDR                0xE000E408U
 /* SYSTICK register */
#define __SYSTICK_CTRL_REG_ADDR             0xE000E010U
#define __SYSTICK_LOAD_REG_ADDR             0xE000E014U
 /* AES128 register */
#define __AES128_KEY0_REG_ADDR              0x40000114U
#define __AES128_KEY1_REG_ADDR              0x40000118U
#define __AES128_KEY2_REG_ADDR              0x4000011CU
#define __AES128_KEY3_REG_ADDR              0x40000120U
#define __AES128_SWAP_REG_ADDR              0x4000012CU

.syntax unified


/*******************************************************************************
 * SECTION
 */
.global SystemContextStore
.type SystemContextStore, %function
.global SystemContextRestore
.type SystemContextRestore, %function

/* void SystemContextStore(void) */
SystemContextStore:
    /* Push register to stack */
    PUSH {R0-R7, LR}

    MOV R0, R8
    MOV R1, R9
    MOV R2, R10
    MOV R3, R11
    MOV R4, R12
    LDR R7, =__NVIC_ISER_REG_ADDR
    LDR R5, [R7]
    LDR R7, =__NVIC_IP_0_REG_ADDR
    LDR R6, [R7]
    LDR R7, =__NVIC_IP_1_REG_ADDR
    LDR R7, [R7]
    PUSH {R0-R7}

    LDR R7, =__SYSTICK_CTRL_REG_ADDR
    LDR R0, [R7]
    LDR R7, =__SYSTICK_LOAD_REG_ADDR
    LDR R1, [R7]
    LDR R7, =__AES128_KEY0_REG_ADDR
    LDR R2, [R7]
    LDR R7, =__AES128_KEY1_REG_ADDR
    LDR R3, [R7]
    LDR R7, =__AES128_KEY2_REG_ADDR
    LDR R4, [R7]
    LDR R7, =__AES128_KEY3_REG_ADDR
    LDR R5, [R7]
    LDR R7, =__AES128_SWAP_REG_ADDR
    LDR R6, [R7]
    LDR R7, =__NVIC_IP_2_REG_ADDR
    LDR R7, [R7]
    PUSH {R0-R7}

    /* Save MSP */
    LDR R0, =__CPU_MSP_SAVED_ADDR
    MRS R1, MSP
    STR R1, [R0]

    /* Good Night */
    WFI

    /* Resume Place */
__SYSTEM_CPU_RESUME:
    /* Restore MSP */
    LDR R0, =__CPU_MSP_SAVED_ADDR
    LDR R1, [R0]
    MSR MSP, R1

    /* invalidate the saved MSP */
    MOVS R2, #0
    STR  R2, [R0]

    /* Pop register */
    POP {R0-R7}
    LDR R7, =__SYSTICK_CTRL_REG_ADDR
    STR R0, [R7]
    LDR R7, =__SYSTICK_LOAD_REG_ADDR
    STR R1, [R7]
    LDR R7, =__AES128_KEY0_REG_ADDR
    STR R2, [R7]
    LDR R7, =__AES128_KEY1_REG_ADDR
    STR R3, [R7]
    LDR R7, =__AES128_KEY2_REG_ADDR
    STR R4, [R7]
    LDR R7, =__AES128_KEY3_REG_ADDR
    STR R5, [R7]
    LDR R7, =__AES128_SWAP_REG_ADDR
    STR R6, [R7]
    LDR R7, =__NVIC_IP_2_REG_ADDR
    STR R7, [R7]

    POP {R0-R7}
    MOV R8,  R0
    MOV R9,  R1
    MOV R10, R2
    MOV R11, R3
    MOV R12, R4
    LDR R7, =__NVIC_ISER_REG_ADDR
    STR R5, [R7]
    LDR R7, =__NVIC_IP_0_REG_ADDR
    STR R6, [R7]
    LDR R7, =__NVIC_IP_1_REG_ADDR
    STR R7, [R7]

    POP {R0-R7, PC}


/* void SystemContextRestore(void) */
SystemContextRestore:
    LDR R0, =__CPU_MSP_SAVED_ADDR
    LDR R1, [R0]
    CMP R1, #0
    /* if __CPU_MSP_SAVED_ADDR != 0 restore context */
    BEQ __SYSTEM_CPU_POWER_UP_RESET

    /* goto  resume */
    B __SYSTEM_CPU_RESUME

__SYSTEM_CPU_POWER_UP_RESET:
    /* Normal system reset */
    BX LR

    .end
