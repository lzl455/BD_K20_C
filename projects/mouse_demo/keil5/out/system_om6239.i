# 1 "../../../hal/device/om6239/system_om6239.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 350 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../../hal/device/om6239/system_om6239.c" 2
# 45 "../../../hal/device/om6239/system_om6239.c"
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 1 3
# 51 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
    typedef unsigned int size_t;






extern __attribute__((__nothrow__)) void *memcpy(void * __restrict ,
                    const void * __restrict , size_t ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) void *memmove(void * ,
                    const void * , size_t ) __attribute__((__nonnull__(1,2)));
# 77 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strcpy(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) char *strncpy(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(1,2)));
# 93 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strcat(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) char *strncat(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(1,2)));
# 117 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int memcmp(const void * , const void * , size_t ) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int strcmp(const char * , const char * ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int strncmp(const char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 141 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int strcasecmp(const char * , const char * ) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int strncasecmp(const char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 158 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int strcoll(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 169 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strxfrm(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(2)));
# 193 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void *memchr(const void * , int , size_t ) __attribute__((__nonnull__(1)));
# 209 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strchr(const char * , int ) __attribute__((__nonnull__(1)));
# 218 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strcspn(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 232 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strpbrk(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 247 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strrchr(const char * , int ) __attribute__((__nonnull__(1)));
# 257 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strspn(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 270 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strstr(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 280 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strtok(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) char *_strtok_r(char * , const char * , char ** ) __attribute__((__nonnull__(2,3)));
# 321 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void *memset(void * , int , size_t ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) char *strerror(int );







extern __attribute__((__nothrow__)) size_t strlen(const char * ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) size_t strlcpy(char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 362 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strlcat(char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 388 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void _membitcpybl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpybb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpyhl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpyhb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpywl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpywb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovebl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovebb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovehl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovehb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovewl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovewb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
# 46 "../../../hal/device/om6239/system_om6239.c" 2
# 1 "../../../hal/device/include\\om_device.h" 1
# 13 "../../../hal/device/include\\om_device.h"
# 1 "../../../hal/device/include/../om6239/om6239.h" 1
# 55 "../../../hal/device/include/../om6239/om6239.h"
typedef enum IRQn {

    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    SVCall_IRQn = -5,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,


    RTC_IRQn = 0,
    USB_IRQn = 1,
    USB_WK_IRQn = 2,
    RF_IRQn = 3,
    WAKEUP_GPIO0_IRQn = 4,
    TIMER0_IRQn = 5,
    VBUS_IRQn = 6,
    WDT_IRQn = 7,
    SF0_IRQn = 8,
    ENCODER_IRQn = 9,
    RF_DMA_IRQn = 10,
    AES128_IRQn = 11,
    UART0_IRQn = 12,
    SENSCAN_IRQn = 13,
    LEDC_IRQn = 14,
} IRQn_Type;
# 92 "../../../hal/device/include/../om6239/om6239.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
# 114 "../../../hal/device/include/../om6239/om6239.h"
# 1 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 1
# 29 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3





# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 35 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 2 3
# 63 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_version.h" 1 3
# 29 "../../../hal/CMSIS/Core/Include/cmsis_version.h" 3
# 64 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 2 3
# 115 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 1 3
# 47 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 1 3
# 31 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
# 64 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma clang diagnostic pop
# 260 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 295 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __CLZ(uint32_t value)
{
# 306 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 526 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
# 551 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
# 737 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}
# 750 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 762 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 792 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __builtin_arm_isb(0xF);
}
# 818 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 890 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 914 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 944 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 995 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1025 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 48 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 2 3
# 116 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 2 3
# 199 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:28;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
# 229 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
# 247 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:15;
    uint32_t T:1;
    uint32_t _reserved1:3;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
# 286 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:1;
    uint32_t SPSEL:1;
    uint32_t _reserved1:30;
  } b;
  uint32_t w;
} CONTROL_Type;
# 314 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile uint32_t ISER[1U];
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];
        uint32_t RESERVED1[31U];
  volatile uint32_t ISPR[1U];
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];
} NVIC_Type;
# 341 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
        uint32_t RESERVED0;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
        uint32_t RESERVED1;
  volatile uint32_t SHP[2U];
  volatile uint32_t SHCSR;
} SCB_Type;
# 448 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 623 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __asm volatile("":::"memory");
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __asm volatile("":::"memory");
  }
}
# 642 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 661 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
  }
}
# 680 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 699 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 714 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 732 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}
# 756 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
  else
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
}
# 781 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
# 808 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
# 832 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)(16 << 2);
  *(vectors + (int32_t)IRQn) = vector;

}
# 848 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)(16 << 2);
  return *(vectors + (int32_t)IRQn);
}






__attribute__((__noreturn__)) static __inline void __NVIC_SystemReset(void)
{
  __builtin_arm_dsb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  __builtin_arm_dsb(0xF);

  for(;;)
  {
    __builtin_arm_nop();
  }
}
# 892 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t SCB_GetFPUType(void)
{
    return 0U;
}
# 923 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
# 115 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/common_reg.h" 1
# 116 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/aes128_reg.h" 1
# 64 "../../../hal/device/om6239/../common/aes128_reg.h"
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t DATA[4];
    volatile uint32_t KEY[4];
    volatile uint32_t INT;
    volatile uint32_t INTMASK;
    volatile uint32_t SWAP;
} OM_AES128_Type;
# 117 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/rf_reg.h" 1
# 64 "../../../hal/device/om6239/../common/rf_reg.h"
typedef struct {
    volatile const uint32_t DMA_INT;
    volatile uint32_t DMA_INT_RAW;
    volatile uint32_t DMA_INT_MASK;
    volatile uint32_t DMA_CMD;
    volatile uint32_t DMA_ADDR;
    volatile uint32_t RFCE;
    volatile const uint32_t RX_PW;
    volatile uint32_t rsv1C;
    volatile uint32_t DFIFO_EN;
    volatile uint32_t CE_PULSE;

    volatile uint32_t ABORT;
    volatile uint32_t rsv2c[5];
    volatile uint32_t CONFIG;
    volatile uint32_t EN_AA;
    volatile uint32_t EN_RXADDR;
    volatile uint32_t SETUP_RETR;
    volatile uint32_t RF_CH;
    volatile uint32_t RF_SETUP;
    volatile uint32_t RF_STATUS;
    volatile uint32_t RSSI;
    union {
        volatile uint32_t RX_ADDR_P0;
        volatile uint32_t ACCESS_ADDR;
    };
    volatile uint32_t RX_ADDR_P0_H;
    volatile uint32_t RX_ADDR_P1;
    union {
        volatile uint32_t RX_ADDR_P2;
        volatile uint32_t BLE_CTL;
    };
    union {
        volatile uint32_t TX_ADDR;
        volatile uint32_t TX_ADVA;
    };
    union {
        volatile uint32_t TX_ADDR_H;
        volatile uint32_t TX_ADVA_H;
    };
    union {
        volatile uint32_t RX_PW_PIPE[3];
        volatile uint32_t TX_HEADER[3];
    };
    volatile const uint32_t FIFO_STATUS;
    volatile uint32_t DYNPD;
    volatile uint32_t FEATURE;
    volatile uint32_t SETUP_V;
    volatile uint32_t PRE_GURD;
    volatile const uint32_t RX_ADVA;
    volatile const uint32_t RX_ADVA_H;
    volatile const uint32_t RX_HEADER[3];
    volatile const uint32_t RX_STATUS[3];
    volatile const uint32_t DFIFO_STATUS;
    volatile uint32_t SETUP_DELAY;
    volatile uint32_t CRC_INIT;
    volatile uint32_t LINE;
    volatile uint32_t PLL_CTL0;
    volatile uint32_t PLL_CTL1;
    volatile uint32_t CAL_CTL;
    volatile uint32_t STATE;
    volatile uint32_t CHAN;
    volatile uint32_t FDEV;
    volatile uint32_t DAC_RANGE;
    volatile uint32_t CTUNING;
    volatile uint32_t FTUNING;
    volatile uint32_t RX_CTRL;
    volatile uint32_t rvF0;
    volatile uint32_t FAGC_CTRL_1;
    volatile uint32_t DOC_DACI;
    volatile uint32_t DOC_DACQ;
    volatile uint32_t AGC_CTRL;
    volatile uint32_t AGC_GAIN;
    volatile uint32_t RF_IVGEN;
    volatile uint32_t TEST_PKDET;
    volatile uint32_t rsv110;
    volatile uint32_t WHITELIST0;
    volatile uint32_t WHITELIST0_H;
    volatile uint32_t WHITELIST1;
    volatile uint32_t WHITELIST1_H;
    volatile uint32_t WHITELIST_CR;
    volatile uint32_t OBSERVE_TX;

    volatile uint32_t RX_CFO_EST;
    volatile uint32_t RX_DBG_CTRL;
} OM_RF_Type;
# 118 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/rtc_reg.h" 1
# 64 "../../../hal/device/om6239/../common/rtc_reg.h"
typedef struct {
    volatile uint32_t CR;
    volatile const uint32_t INTSTAT;
    volatile uint32_t INTRAWSTAT;
    volatile uint32_t INTMASK;
    volatile uint32_t TICK;
    volatile uint32_t ALARM0;
    volatile uint32_t CNT;
    volatile const uint32_t CNT_VALID;
    volatile const uint32_t CLKN_SYNC;
    volatile const uint32_t CLKN_VALID;
    volatile uint32_t ALARM1;
    volatile uint32_t ALARM2;
    volatile uint32_t WKRF_CR;
} OM_RTC_Type;
# 119 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/timer_reg.h" 1
# 64 "../../../hal/device/om6239/../common/timer_reg.h"
typedef struct {
    volatile uint32_t TINT;
    volatile uint32_t TINTMASK;
    volatile uint32_t TCON;
    volatile uint32_t TMOD;
    volatile uint32_t TH0;
    volatile uint32_t TL0;
    volatile uint32_t TDIV;
} OM_TIMER_Type;
# 120 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/pwm_reg.h" 1
# 64 "../../../hal/device/om6239/../common/pwm_reg.h"
typedef struct {
    volatile uint32_t PWMCON;
    volatile uint32_t PWMCR0;
    volatile uint32_t PWMCR1;
    volatile uint32_t PWMDIV;
    volatile uint32_t PWMPRD;
    union {
        volatile uint32_t PWMDC[8];
        struct {
            volatile uint32_t PWMDC0;
            volatile uint32_t PWMDC1;
            volatile uint32_t PWMDC2;
            volatile uint32_t PWMDC3;
            volatile uint32_t PWMDC4;
            volatile uint32_t PWMDC5;
            volatile uint32_t PWMDC6;
            volatile uint32_t PWMDC7;
        };
    };
} OM_PWM_Type;
# 121 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/usb_reg.h" 1
# 64 "../../../hal/device/om6239/../common/usb_reg.h"
typedef struct {

  volatile uint8_t FADDR;
  volatile uint8_t POWER;
  volatile uint8_t INTR_TX1;
  volatile uint8_t INTR_TX2;
  volatile uint8_t INTR_RX1;
  volatile uint8_t INTR_RX2;
  volatile uint8_t INTR_USB;
  volatile uint8_t INTR_TXEN1;
  volatile uint8_t INTR_TXEN2;
  volatile uint8_t INTR_RXEN1;
  volatile uint8_t INTR_RXEN2;
  volatile uint8_t INTR_USBEN;
  volatile uint8_t FRAME1;
  volatile uint8_t FRAME2;
  volatile uint8_t INDEX;
  volatile uint8_t DEVCTL;

  volatile uint8_t TXMAXP;
  union
  {
    volatile uint8_t CSR0;
    volatile uint8_t TXCSR1;
  };
  union
  {
    volatile uint8_t CSR02;
    volatile uint8_t TXCSR2;
  };
  volatile uint8_t RXMAXP;
  volatile uint8_t RXCSR1;
  volatile uint8_t RXCSR2;
  union
  {
    volatile uint8_t COUNT0;
    volatile uint8_t RXCOUNT1;
  };
  volatile uint8_t RXCOUNT2;
  volatile uint8_t x18_1e[7];
  volatile uint8_t FIFOSIZE;

  volatile uint32_t EPnFIFO[16];
       uint8_t x60_1ff[0x200-0x60];

  volatile uint32_t DMA_INTR;

} OM_USB_Type;
# 122 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/hcache_reg.h" 1
# 64 "../../../hal/device/om6239/../common/hcache_reg.h"
typedef struct {
     volatile const uint32_t TYPE;
     volatile uint32_t CONFIG;
     volatile uint32_t CTRL;
     volatile uint32_t STATUS;
          uint32_t RESERVE0[4];
     volatile uint32_t MAINT0;
     volatile uint32_t MAINT1;
     volatile uint32_t MON_CONFIG;
     volatile uint32_t MON_EN;
     volatile uint32_t MON_CTRL;
     volatile uint32_t MON_STATUS;
} OM_ICACHE_Type;
# 123 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/flash_reg.h" 1
# 64 "../../../hal/device/om6239/../common/flash_reg.h"
typedef struct {
    volatile const uint32_t INTR_STATUS;
    volatile uint32_t RAW_INTR_STATUS;
    volatile uint32_t INTR_MASK;
    volatile uint32_t COMMAND;
    volatile uint32_t COMMAND_DATA0_REG;
    volatile uint32_t COMMAND_DATA1_REG;
    volatile uint32_t ADDRESS_REG;
    volatile uint32_t READ_OPCODE_REG;
    volatile uint32_t CONFIGURATION_0;
    volatile uint32_t CONFIGURATION_1;
    volatile uint32_t WP_HOLD_REG;
} OM_FLASH_Type;
# 124 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/rcc_reg.h" 1
# 64 "../../../hal/device/om6239/../common/rcc_reg.h"
typedef struct {
    volatile uint32_t CLKCTRL;
    volatile uint32_t CLKGATE;
    volatile uint32_t RSTCTRL;
    volatile uint32_t M0CALIB;
    volatile uint32_t SYSCLK_SEL;




    volatile uint32_t rsv_x14;

    volatile uint32_t FLASH_CLKCTRL;
    volatile uint32_t FLASH_READ_OPCODE;
    volatile uint32_t FLASH_OFFSET;
    volatile uint32_t USB_CTRL;
    volatile uint32_t USB_WK_INT_CLR;
    volatile uint32_t USB_WK_SIG_SEL;
    volatile uint32_t USB_WK_CLK_SEL;
} OM_RCC_Type;
# 125 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/uart_reg.h" 1
# 64 "../../../hal/device/om6239/../common/uart_reg.h"
typedef struct {
    volatile uint32_t INTR_STATUS;
    volatile uint32_t INTR_MASK;
    volatile uint32_t SCON;
    volatile uint32_t SMOD;
    volatile uint32_t SREL;
    volatile uint32_t SBUF;
    volatile uint32_t FIFO_TH;
    volatile uint32_t FIFO_ST;
} OM_UART_Type;
# 126 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/wdt_reg.h" 1
# 64 "../../../hal/device/om6239/../common/wdt_reg.h"
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t SV;
} OM_WDT_Type;
# 127 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/gpio_reg.h" 1
# 64 "../../../hal/device/om6239/../common/gpio_reg.h"
typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t DATAOUT;



    volatile uint32_t DATAOUTSET;
    volatile uint32_t DATAOUTCLR;

    volatile uint32_t OUTENSET;
    volatile uint32_t OUTENCLR;
         uint32_t rsv_x18_x1c[2];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t INTTYPE0SET;
    volatile uint32_t INTTYPE0CLR;
    volatile uint32_t INTPOLSET;
    volatile uint32_t INTPOLCLR;
    volatile uint32_t INTSTATUS;
    volatile uint32_t rsv_x3c;
    volatile uint32_t INTTYPE1SET;
    volatile uint32_t INTTYPE1CLR;





} OM_GPIO_Type;
# 128 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/../common/pof_reg.h" 1
# 64 "../../../hal/device/om6239/../common/pof_reg.h"
typedef struct {
    volatile uint32_t rsv_x00_x3C[16];
    volatile uint32_t POFCON;
    volatile uint32_t POFMSK;
    volatile uint32_t DRV_CTRL;
} OM_POF_Type;
# 129 "../../../hal/device/include/../om6239/om6239.h" 2

# 1 "../../../hal/device/om6239/pmu_reg.h" 1
# 64 "../../../hal/device/om6239/pmu_reg.h"
typedef struct {
    volatile uint32_t BOOT_MODE;
    volatile uint32_t CLK32K_SEL;
    volatile uint32_t CLKLP_CTRL;
    volatile uint32_t ANA_CTRL;
    volatile uint32_t LPMS;
    volatile uint32_t WKINT_CLR;
    volatile uint32_t PLL_CTRL;
    volatile uint32_t PLL_CTRL1;
    volatile uint32_t rsv_x20;
    volatile uint32_t DELAY_CTRL;
    volatile uint32_t PINMUX_SEL;
    volatile uint32_t RF_DEBUG;
    volatile uint32_t FLASH_PWR_CMD;
    volatile uint32_t rsv_x34_x3c[3];
    volatile uint32_t PAD_WK_CTRL;
    volatile uint32_t PAD_WK_CTRL_1;
    volatile uint32_t PAD_BUF_EN;
    volatile uint32_t PAD_PD_CTRL;
    volatile uint32_t PAD_PU_CTRL;
    volatile uint32_t PAD_PU_CTRL_1;
    volatile uint32_t PAD_DRV_CTRL;
    volatile uint32_t PAD_DRV_CTRL_1;
    volatile uint32_t rsv_x60_x68[3];
    union {
        volatile uint32_t SW_RSVD0;
        volatile uint32_t CPU_CONTEXT_ADDR;
    };
    volatile uint32_t SW_RSVD1;
    volatile uint32_t SW_RSVD2;
    volatile uint32_t SW_RSVD3;
    volatile uint32_t SW_RSVD4;
    volatile uint32_t SW_RSVD5;
    volatile uint32_t SW_RSVD6;
    volatile uint32_t SW_RSVD7;
} OM_PMU_Type;
# 131 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/senscan_reg.h" 1
# 64 "../../../hal/device/om6239/senscan_reg.h"
typedef struct {
     volatile uint32_t CSR;
     volatile uint32_t ISR;
     volatile uint32_t IER;
     union {
          uint32_t ADDR_REG[7];
          struct {
               volatile uint32_t IDADDR;
               volatile uint32_t ID;
               volatile uint32_t MOADDR;
               volatile uint32_t XADDR;
               volatile uint32_t YADDR;
               volatile uint32_t HADDR1;
               volatile uint32_t HADDR2;
          };
     };
     volatile const uint32_t X_DATA;
     volatile const uint32_t Y_DATA;
     volatile uint32_t TR;
     volatile uint32_t TNS;
     volatile uint32_t SCAN_FREQ;
     volatile uint32_t RESYNC;
     volatile uint32_t CFG_CSR;
     volatile uint32_t CFG_ADDR;
     volatile uint32_t CFG_DATA;
} OM_SENSCAN_Type;
# 132 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/encoder_reg.h" 1
# 64 "../../../hal/device/om6239/encoder_reg.h"
typedef struct {
     volatile uint32_t EN;
     volatile uint32_t CNT;
     volatile uint32_t MODE;
     volatile uint32_t SAM;
     volatile uint32_t DBG;
     volatile uint32_t VALID;
} OM_ENCODER_Type;
# 133 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/om6239/ledc_reg.h" 1
# 64 "../../../hal/device/om6239/ledc_reg.h"
typedef struct {
     volatile uint32_t CR;
     volatile uint32_t SIG_TIM;
     volatile uint32_t RST_TIM;
     volatile uint32_t DMA_CTL;
} OM_LEDC_Type;
# 134 "../../../hal/device/include/../om6239/om6239.h" 2
# 182 "../../../hal/device/include/../om6239/om6239.h"
#pragma clang diagnostic pop
# 14 "../../../hal/device/include\\om_device.h" 2
# 47 "../../../hal/device/om6239/system_om6239.c" 2




void SystemInit(void)
{


    ((OM_RCC_Type *) 0x40000600)->CLKGATE |= (0x01U << (9U));
    ((OM_PMU_Type *) 0x40000000)->CLKLP_CTRL |= (0x1<<2);
    ((OM_PMU_Type *) 0x40000000)->CLK32K_SEL = 0;


    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = 0xFFFFFFU;
    ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) | (1UL );


    ((OM_PMU_Type *) 0x40000000)->LPMS |= (0x1U << 5);
    ((OM_PMU_Type *) 0x40000000)->FLASH_PWR_CMD = 0xABB9;
}
