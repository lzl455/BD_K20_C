# 1 "../../../mode_usb/hal_usb_decs.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 350 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../../mode_usb/hal_usb_decs.c" 2
# 11 "../../../mode_usb/hal_usb_decs.c"
# 1 "../../../mode_usb/main_usb.h" 1
# 13 "../../../mode_usb/main_usb.h"
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
# 14 "../../../mode_usb/main_usb.h" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdbool.h" 1 3
# 15 "../../../mode_usb/main_usb.h" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 1 3
# 53 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef unsigned int size_t;
# 68 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef __builtin_va_list __va_list;
# 87 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __fpos_t_struct {
    unsigned long long int __pos;





    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
# 108 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __FILE FILE;
# 119 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
struct __FILE {
    union {
        long __FILE_alignment;



        char __FILE_size[84];

    } __FILE_opaque;
};
# 138 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;
# 224 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int remove(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int rename(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 243 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *tmpfile(void);






extern __attribute__((__nothrow__)) char *tmpnam(char * );
# 265 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fclose(FILE * ) __attribute__((__nonnull__(1)));
# 275 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fflush(FILE * );
# 285 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *fopen(const char * __restrict ,
                           const char * __restrict ) __attribute__((__nonnull__(1,2)));
# 329 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *freopen(const char * __restrict ,
                    const char * __restrict ,
                    FILE * __restrict ) __attribute__((__nonnull__(2,3)));
# 342 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void setbuf(FILE * __restrict ,
                    char * __restrict ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) int setvbuf(FILE * __restrict ,
                   char * __restrict ,
                   int , size_t ) __attribute__((__nonnull__(1)));
# 370 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int fprintf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 393 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _fprintf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int _printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));








#pragma __printf_args
extern __attribute__((__nothrow__)) int _sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __attribute__((__nothrow__)) int snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));
# 460 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _snprintf(char * __restrict , size_t ,
                      const char * __restrict , ...) __attribute__((__nonnull__(3)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int fscanf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 503 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _fscanf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));








#pragma __scanf_args
extern __attribute__((__nothrow__)) int _scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int sscanf(const char * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 541 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _sscanf(const char * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int _vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int _vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int _vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int __ARM_vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int _vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) int vfprintf(FILE * __restrict ,
                    const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 584 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int vsprintf(char * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 594 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int __ARM_vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));

extern __attribute__((__nothrow__)) int vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 609 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _vsprintf(char * __restrict ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vfprintf(FILE * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vsnprintf(char * __restrict , size_t ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 635 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_asprintf(char ** , const char * __restrict , ...) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) int __ARM_vasprintf(char ** , const char * __restrict , __va_list ) __attribute__((__nonnull__(2)));
# 649 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetc(FILE * ) __attribute__((__nonnull__(1)));
# 659 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *fgets(char * __restrict , int ,
                    FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 673 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputc(int , FILE * ) __attribute__((__nonnull__(2)));
# 683 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputs(const char * __restrict , FILE * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int getc(FILE * ) __attribute__((__nonnull__(1)));
# 704 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (getchar)(void);
# 713 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *gets(char * ) __attribute__((__nonnull__(1)));
# 725 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int putc(int , FILE * ) __attribute__((__nonnull__(2)));
# 737 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (putchar)(int );






extern __attribute__((__nothrow__)) int puts(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int ungetc(int , FILE * ) __attribute__((__nonnull__(2)));
# 778 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fread(void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 794 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t __fread_bytes_avail(void * __restrict ,
                    size_t , FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 810 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fwrite(const void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 822 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetpos(FILE * __restrict , fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 833 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fseek(FILE * , long int , int ) __attribute__((__nonnull__(1)));
# 850 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fsetpos(FILE * __restrict , const fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 863 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) long int ftell(FILE * ) __attribute__((__nonnull__(1)));
# 877 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void rewind(FILE * ) __attribute__((__nonnull__(1)));
# 886 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void clearerr(FILE * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int feof(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) int ferror(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) void perror(const char * );
# 917 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _fisatty(FILE * ) __attribute__((__nonnull__(1)));



extern __attribute__((__nothrow__)) void __use_no_semihosting_swi(void);
extern __attribute__((__nothrow__)) void __use_no_semihosting(void);
# 16 "../../../mode_usb/main_usb.h" 2
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 58 "../../../hal/driver/include\\om_driver.h"
# 1 "../../../hal/driver/include/../om6239/driver_om6239.h" 1
# 53 "../../../hal/driver/include/../om6239/driver_om6239.h"
# 1 "../../../hal/driver/include\\RTE_driver.h" 1
# 58 "../../../hal/driver/include\\RTE_driver.h"
# 1 "../config\\RTE_om6239.h" 1
# 59 "../../../hal/driver/include\\RTE_driver.h" 2
# 54 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../common/includes\\om_error.h" 1
# 53 "../../../common/includes\\om_error.h"
typedef enum {
    OM_ERROR_OK = 0,
    OM_ERROR_UNSPECIFIC = 1,
    OM_ERROR_BUSY = 2,
    OM_ERROR_TIMEOUT = 3,
    OM_ERROR_UNSUPPORTED = 4,
    OM_ERROR_PARAMETER = 5,
    OM_ERROR_RESOURCES = 6,
    OM_ERROR_PERMISSION = 7,
    OM_ERROR_OUT_OF_RANGE = 8,
    OM_ERROR_ALIGN = 9,
    OM_ERROR_STATUS = 10,
    OM_ERROR_VERIFY = 11,
    OM_ERROR_FAIL = 12,
    OM_ERROR_HARDWARE = 13,

    OM_ERROR_MAX = 0xFFFFFFFFU,
} om_error_t;
# 55 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../common/includes\\om_compiler.h" 1
# 56 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../common/includes\\om_common.h" 1
# 57 "../../../hal/driver/include/../om6239/driver_om6239.h" 2

# 1 "../../../hal/driver/include/../om6239/../common/drv_utils.h" 1
# 54 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
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
# 1 "../../../hal/device/include/../om6239/../common/common_reg.h" 1
# 116 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/aes128_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/aes128_reg.h"
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t DATA[4];
    volatile uint32_t KEY[4];
    volatile uint32_t INT;
    volatile uint32_t INTMASK;
    volatile uint32_t SWAP;
} OM_AES128_Type;
# 117 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/rf_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rf_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/rtc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rtc_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/timer_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/timer_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/pwm_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/pwm_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/usb_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/usb_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/hcache_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/hcache_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/flash_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/flash_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/rcc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rcc_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/uart_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/uart_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/wdt_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/wdt_reg.h"
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t SV;
} OM_WDT_Type;
# 127 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/gpio_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/gpio_reg.h"
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
# 1 "../../../hal/device/include/../om6239/../common/pof_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/pof_reg.h"
typedef struct {
    volatile uint32_t rsv_x00_x3C[16];
    volatile uint32_t POFCON;
    volatile uint32_t POFMSK;
    volatile uint32_t DRV_CTRL;
} OM_POF_Type;
# 129 "../../../hal/device/include/../om6239/om6239.h" 2

# 1 "../../../hal/device/include/../om6239/pmu_reg.h" 1
# 64 "../../../hal/device/include/../om6239/pmu_reg.h"
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
# 1 "../../../hal/device/include/../om6239/senscan_reg.h" 1
# 64 "../../../hal/device/include/../om6239/senscan_reg.h"
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
# 1 "../../../hal/device/include/../om6239/encoder_reg.h" 1
# 64 "../../../hal/device/include/../om6239/encoder_reg.h"
typedef struct {
     volatile uint32_t EN;
     volatile uint32_t CNT;
     volatile uint32_t MODE;
     volatile uint32_t SAM;
     volatile uint32_t DBG;
     volatile uint32_t VALID;
} OM_ENCODER_Type;
# 133 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/ledc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/ledc_reg.h"
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
# 55 "../../../hal/driver/include/../om6239/../common/drv_utils.h" 2
# 534 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline void register_set(volatile uint32_t *reg, uint32_t mask, uint32_t value)
{
    register uint32_t reg_prev;

    reg_prev = *reg;
    reg_prev &= ~mask;
    reg_prev |= mask & value;
    *reg = reg_prev;
}
# 553 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline void register_set_raw(volatile uint32_t *reg, uint32_t mask, uint32_t value)
{
    *reg = mask & value;
}
# 566 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline void register_set1(volatile uint32_t *reg, uint32_t mask)
{
    *reg |= mask;
}
# 579 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline void register_set0(volatile uint32_t *reg, uint32_t mask)
{
    *reg &= ~mask;
}
# 593 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline uint32_t register_get(const volatile uint32_t *reg, uint32_t mask, uint32_t pos)
{
    return (*reg & mask) >> pos;
}
# 607 "../../../hal/driver/include/../om6239/../common/drv_utils.h"
__attribute__((always_inline)) static __inline uint32_t register_get_raw(const volatile uint32_t *reg, uint32_t mask)
{
    return *reg & mask;
}
# 59 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_common.h" 1
# 79 "../../../hal/driver/include/../om6239/../common/drv_common.h"
typedef enum {

    DRV_EVENT_COMMON_NONE = 0,
    DRV_EVENT_COMMON_ERROR = (1U << 0),
    DRV_EVENT_COMMON_ABORT = (1U << 1),

    DRV_EVENT_COMMON_GENERAL = (1U << 4),
    DRV_EVENT_COMMON_WRITE_COMPLETED = (1U << 5),
    DRV_EVENT_COMMON_READ_COMPLETED = (1U << 6),
    DRV_EVENT_COMMON_READ_WRITE_COMPLETED = (1U << 5) + (1U << 6),
    DRV_EVENT_COMMON_RX_OVERFLOW = (1U << 7),
    DRV_EVENT_COMMON_DMA2PERIPH_COMPLETED = (1U << 8),



    DRV_EVENT_ADC_EOC = (1U << 16),
    DRV_EVENT_ADC_FIFO_HALF = (1U << 17),
    DRV_EVENT_ADC_FIFO_FULL = (1U << 18),
    DRV_EVENT_ADC_FIFO_OVERFLOW = (1U << 19),


    DRV_EVENT_I2C_TRANS = (1U << 16),


    DRV_EVENT_SYSTICK = (1U << 16),


    DRV_EVENT_RTC_TICK = (1U << 0),
    DRV_EVENT_RTC_ALARM0 = (1U << 1),
    DRV_EVENT_RTC_ALARM1 = (1U << 2),


    DRV_EVENT_LOW_TIMER_OVERFLOW_FLAG = (1U << 0),
    DRV_EVENT_HIGH_TIMER_OVERFLOW_FLAG = (1U << 1),


    DRV_EVENT_SENSCAN_SCAN_DONE = (1U << 0),
    DRV_EVENT_SENSCAN_RESYNC_START = (1U << 1),
    DRV_EVENT_SENSCAN_RESYNC_DONE = (1U << 2),
    DRV_EVENT_SENSCAN_RESYNC_SCAN = (1U << 3),
    DRV_EVENT_SENSCAN_CFG_DONE = (1U << 4),
} drv_event_t;






typedef void(*drv_isr_callback_t)(void *om_reg, drv_event_t event, void *param0, void *param1);




typedef struct {
    drv_isr_callback_t isr_cb;
    uint16_t tx_num;
    uint16_t tx_cnt;
    uint8_t *tx_buf;
    uint16_t rx_num;
    uint16_t rx_cnt;
    uint8_t *rx_buf;
} drv_env_t;




typedef struct {
    uint32_t cap;
    void *reg;
    void *env;
} drv_resource_t;
# 60 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_cortex.h" 1
# 59 "../../../hal/driver/include/../om6239/../common/drv_cortex.h"
# 1 "../../../hal/driver/common/drv_rcc.h" 1
# 54 "../../../hal/driver/common/drv_rcc.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 55 "../../../hal/driver/common/drv_rcc.h" 2
# 69 "../../../hal/driver/common/drv_rcc.h"
extern uint32_t SystemCoreClock;
# 79 "../../../hal/driver/common/drv_rcc.h"
typedef enum {
    RCC_SYS_CLK_SEL_OSC16M = 0U,
    RCC_SYS_CLK_SEL_PLL48M = 1U,
} rcc_sys_clk_sel_t;
# 91 "../../../hal/driver/common/drv_rcc.h"
typedef enum {
    RCC_DIV_CLK_SEL_1 = 0U,
    RCC_DIV_CLK_SEL_2 = 1U,
    RCC_DIV_CLK_SEL_4 = 2U,
    RCC_DIV_CLK_SEL_8 = 3U,
    RCC_DIV_CLK_SEL_16 = 4U,
    RCC_DIV_CLK_SEL_32 = 5U,
    RCC_DIV_CLK_SEL_64 = 6U,
    RCC_DIV_CLK_SEL_128 = 7U,
} rcc_div_clk_sel_t;
# 109 "../../../hal/driver/common/drv_rcc.h"
typedef enum {

    RCC_CLK_LEDC = (0x01U << (0U)),



    RCC_CLK_FLASH = (0x01U << (1U)),
    RCC_CLK_RF = (0x01U << (2U)),
    RCC_CLK_USB = (0x01U << (3U)),
    RCC_CLK_TIMER0 = (0x01U << (4U)),
    RCC_CLK_UART0 = (0x01U << (5U)),
    RCC_CLK_GPIO0 = (0x01U << (6U)),
    RCC_CLK_SWD = (0x01U << (7U)),
    RCC_CLK_AES128 = (0x01U << (8U)),
    RCC_CLK_ANA = (0x01U << (9U)),
    RCC_CLK_RTC = (0x01U << (10U)),
    RCC_CLK_WDT = (0x01U << (11U)),
    RCC_CLK_PWM = (0x01U << (12U)),

    RCC_CLK_ENCODER = (0x01U << (13U)),
    RCC_CLK_SENSCAN = (0x01U << (14U)),

} rcc_clk_t;
# 140 "../../../hal/driver/common/drv_rcc.h"
typedef enum {
    RCC_RST_RF_FSM = (0x01U << (4U)),
    RCC_RST_RF = (0x01U << (5U)),
    RCC_RST_USB = (0x01U << (6U)),

    RCC_RST_GPIO0 = (0x01U << (9U)),

    RCC_RST_FLASH = (0x01U << (6U)),
    RCC_RST_TIMER0 = (0x01U << (8U)),
    RCC_RST_AES128 = (0x01U << (10U)),
    RCC_RST_OSC = (0x01U << (11U)),
    RCC_RST_UART0 = (0x01U << (12U)),
    RCC_RST_PWM = (0x01U << (13U)),

    RCC_RST_LEDC = (0x01U << (14U)),
    RCC_RST_ENCODER = (0x01U << (15U)),
    RCC_RST_SENSCAN = (0x01U << (16U)),

} rcc_rst_t;
# 167 "../../../hal/driver/common/drv_rcc.h"
typedef enum {
    RCC_RST_TYPE_POWER_ON = 0U,
    RCC_RST_TYPE_WATCH_DOG = 1U,
    RCC_RST_TYPE_SOFT = 2U,
    RCC_RST_TYPE_DEEP_SLEEP = 3U,
    RCC_RST_TYPE_DEEP_STAND_BY = 4U,
} rcc_rst_type_t;
# 183 "../../../hal/driver/common/drv_rcc.h"
typedef enum {
    RCC_RTC_CLK_SOURCE_32K = 0U,
    RCC_RTC_CLK_SOURCE_2M = 1U,
} rcc_rtc_clk_source_t;
# 195 "../../../hal/driver/common/drv_rcc.h"
typedef struct {
    rcc_sys_clk_sel_t sys_clk_sel;
    rcc_div_clk_sel_t div_clk_sel;
    uint8_t div_clk_flash;



} rcc_config_t;
# 253 "../../../hal/driver/common/drv_rcc.h"
__attribute__((always_inline)) static __inline rcc_rst_type_t drv_rcc_get_reset(void)
{
    return (rcc_rst_type_t)(((OM_RCC_Type *) 0x40000600)->RSTCTRL & 0x07);
}
# 267 "../../../hal/driver/common/drv_rcc.h"
extern void drv_rcc_init(void);
# 279 "../../../hal/driver/common/drv_rcc.h"
extern uint32_t drv_rcc_clock_get(rcc_clk_t _dev_type);
# 290 "../../../hal/driver/common/drv_rcc.h"
__attribute__((always_inline)) static __inline void drv_rcc_rtc_clock_source_set(rcc_rtc_clk_source_t rtc_clk_source)
{
    ((OM_PMU_Type *) 0x40000000)->CLK32K_SEL = (rtc_clk_source == RCC_RTC_CLK_SOURCE_2M) ? (0x1u << 0) : 0U;
}
# 60 "../../../hal/driver/include/../om6239/../common/drv_cortex.h" 2
# 61 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_gpio.h" 1
# 76 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
typedef uint32_t gpio_mask_t;
# 85 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
typedef enum {
    GPIO_TRIG_NONE = 0U,
    GPIO_TRIG_RISING_EDGE = 1U,
    GPIO_TRIG_FALLING_EDGE = 2U,
    GPIO_TRIG_BOTH_EDGE = 3U,
    GPIO_TRIG_LOW_LEVEL = 4U,
    GPIO_TRIG_HIGH_LEVEL = 5U,
} gpio_trig_t;
# 101 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
typedef enum {
    GPIO_DIR_OUTPUT = 0U,
    GPIO_DIR_INPUT = 1U,
} gpio_dir_t;
# 113 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
typedef enum {
    GPIO_CONTROL_CLK_DISABLE = 0U,
    GPIO_CONTROL_CLK_ENABLE = 1U,
    GPIO_CONTROL_RESET = 2U,
} gpio_control_t;
# 126 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
typedef struct {
    OM_GPIO_Type *om_gpio;
    uint8_t gpio_idx;
    gpio_trig_t trig : 3;
    gpio_dir_t dir : 1;
    uint8_t out_val : 1;
} gpio_config_t;
# 152 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline void drv_gpio_set_dir(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, gpio_dir_t dir)
{
    if (dir == GPIO_DIR_OUTPUT) {
        om_gpio->OUTENSET = gpio_mask;
    } else {
        om_gpio->OUTENCLR = gpio_mask;
    }
}
# 171 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline gpio_dir_t drv_gpio_get_dir(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{
    if (om_gpio->OUTENSET & gpio_mask) {
        return GPIO_DIR_OUTPUT;
    } else {
        return GPIO_DIR_INPUT;
    }
}
# 190 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline uint32_t drv_gpio_read(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{
    return (om_gpio->DATA & gpio_mask);
}
# 206 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline void drv_gpio_write(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, uint8_t val)
{

    if(val) {
        om_gpio->DATAOUTSET = gpio_mask;
    } else {
        om_gpio->DATAOUTCLR = gpio_mask;
    }
# 223 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
}
# 235 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline void drv_gpio_toggle(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask)
{

    om_gpio->DATAOUT ^= gpio_mask;

}
# 251 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline uint32_t drv_gpio_port_read(OM_GPIO_Type *om_gpio)
{
    return om_gpio->DATA;
}
# 264 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
__attribute__((always_inline)) static __inline void drv_gpio_port_write(OM_GPIO_Type *om_gpio, uint32_t port_val)
{
    om_gpio->DATAOUT = port_val;
}
# 279 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
extern om_error_t drv_gpio_init(const gpio_config_t *gpio_config, uint32_t gpio_config_num);
# 292 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
extern void drv_gpio_set_trig(OM_GPIO_Type *om_gpio, gpio_mask_t gpio_mask, gpio_trig_t trig);
# 305 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
extern void *drv_gpio_control(OM_GPIO_Type *om_gpio, gpio_control_t control, void *argu);
# 329 "../../../hal/driver/include/../om6239/../common/drv_gpio.h"
extern void drv_gpio_isr(OM_GPIO_Type *om_gpio);
# 62 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_rtc.h" 1
# 69 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
typedef enum {
    RTC_ALARM_0 = 0U,
    RTC_ALARM_1 = 1U,
    RTC_ALARM_2 = 2U,
} rtc_alarm_t;
# 82 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
typedef enum {
    RTC_CONTROL_WAIT_TIME_SYNCED = 1U,
    RTC_CONTROL_TICK_INT_EN = 2U,
    RTC_CONTROL_ALARM0_INT_EN = 3U,
    RTC_CONTROL_ALARM1_INT_EN = 4U,
    RTC_CONTROL_SET_ALARM0 = 5U,
    RTC_CONTROL_SET_ALARM1 = 6U,
    RTC_CONTROL_SET_ALARM2 = 7U,
    RTC_CONTROL_IS_TICK = 8U,
    RTC_CONTROL_IS_ALARMED = 9U,
    RTC_CONTROL_IS_ON = 10U,
    RTC_CONTROL_DISABLE_TIME = 11U,
    RTC_CONTROL_GET_ALARM0 = 12U,
    RTC_CONTROL_GET_ALARM1 = 13U,
    RTC_CONTROL_GET_ALARM2 = 14U,
    RTC_CONTROL_TICK_INT_DISABLE = 15U,
    RTC_CONTROL_ALARM1_RF_DISABLE = 16U,
    RTC_CONTROL_ALARM0_INT_DIS = 17U,
} rtc_control_t;
# 133 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
__attribute__((always_inline)) static __inline void *drv_rtc_control(OM_RTC_Type *om_rtc, rtc_control_t control, void *argu)
{
    uint32_t ret;

    ret = (uint32_t)OM_ERROR_OK;

    do { uint32_t _primask = __get_PRIMASK(); __disable_irq();;
    switch (control) {
        case RTC_CONTROL_WAIT_TIME_SYNCED:
            while (!om_rtc->CNT_VALID);
            break;
        case RTC_CONTROL_TICK_INT_EN:
            om_rtc->INTMASK |= (1u << (0));
            break;
        case RTC_CONTROL_ALARM0_INT_EN:
            om_rtc->INTMASK |= (1u << (1));
            break;
        case RTC_CONTROL_ALARM1_INT_EN:
            om_rtc->INTMASK |= (1u << (2));
            break;
        case RTC_CONTROL_SET_ALARM0:
            while (0 == (om_rtc->CR & (1u << (10))));
            om_rtc->ALARM0 = (uint32_t)argu;
            break;
        case RTC_CONTROL_SET_ALARM1:
            while (0 == (om_rtc->CR & (1u << (11))));
            om_rtc->ALARM1 = (uint32_t)argu;
            break;
        case RTC_CONTROL_SET_ALARM2:
            while (0 == (om_rtc->CR & (1u << (12))));
            om_rtc->ALARM2 = (uint32_t)argu;
            break;
        case RTC_CONTROL_IS_TICK:
            if (om_rtc->INTSTAT & (1u << (0))) {
                om_rtc->INTRAWSTAT = (1u << (0));
                ret = 1U;
            } else {
                ret = 0U;
            }
            break;
        case RTC_CONTROL_IS_ALARMED:
            if (om_rtc->INTSTAT & (1u << (1))) {
                om_rtc->INTRAWSTAT = (1u << (1));
                ret = 1U;
            } else {
                ret = 0U;
            }
            break;
        case RTC_CONTROL_IS_ON:
            ret = (om_rtc->CR & (1u << (0))) ? 1U : 0U;
            break;
        case RTC_CONTROL_DISABLE_TIME:
            while (0 == (om_rtc->CR & (1u << (8))));
            om_rtc->CR = 0;
            om_rtc->INTMASK = 0;
            break;
        case RTC_CONTROL_GET_ALARM0:
            ret = om_rtc->ALARM0;
            break;
        case RTC_CONTROL_GET_ALARM1:
            ret = om_rtc->ALARM1;
            break;
        case RTC_CONTROL_GET_ALARM2:
            ret = om_rtc->ALARM2;
            break;
        case RTC_CONTROL_TICK_INT_DISABLE:
            om_rtc->INTMASK &= ~(1u << (0));
            break;
        case RTC_CONTROL_ALARM1_RF_DISABLE:
            om_rtc->WKRF_CR = 0;
            break;
        case RTC_CONTROL_ALARM0_INT_DIS:
            om_rtc->INTMASK &= ~(1u << (1));
            break;
        default:
            break;
    }
    if (!_primask) { __enable_irq(); } } while(0);

    return (void *)ret;
}
# 224 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern om_error_t drv_rtc_init(OM_RTC_Type *om_rtc);
# 237 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern void drv_rtc_set_alarm(OM_RTC_Type *om_rtc, rtc_alarm_t alarm, uint32_t time);
# 249 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern void drv_rtc_set_tick_hz(int hz);
# 261 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern void drv_rtc_wait_clocks(OM_RTC_Type *om_rtc, uint32_t clocks);
# 272 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern uint32_t drv_rtc_read(OM_RTC_Type *om_rtc);
# 301 "../../../hal/driver/include/../om6239/../common/drv_rtc.h"
extern void drv_rtc_isr_callback(void);

extern void pnc_rtc_set_alarm(uint32_t time);
extern void drv_rtc_set_alarm0(uint32_t time);
# 63 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_aes128.h" 1
# 68 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
typedef enum {
    AES128_NOT_LITTLE_ENDIAN = 0U,
    AES128_IS_LITTLE_ENDIAN = 3U,
} aes128_is_little_endian_t;
# 80 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
typedef enum {
    AES128_CONTROL_LITTLE_ENDIAN = 0U,
    AES128_CONTROL_BIG_ENDIAN = 1U,
    AES128_CONTROL_SET_KEY = 2U,
    AES128_CONTROL_CLK_DISABLE = 3U,
    AES128_CONTROL_CLK_ENABLE = 4U,
    AES128_CONTROL_RESET = 5U,
} aes128_control_t;







typedef struct {
    uint8_t is_little_endian;

} aes128_config_t;
# 122 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern void *drv_aes128_control(OM_AES128_Type *om_aes128, aes128_control_t control, void *argu);
# 134 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern om_error_t drv_aes128_init(OM_AES128_Type *om_aes128, const aes128_config_t *config);
# 148 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern om_error_t drv_aes128_encrypt(OM_AES128_Type *om_aes128,
                                     uint32_t key[4],
                                     uint32_t input[4],
                                     uint32_t output[4]);
# 161 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern void drv_aes128_cryp(OM_AES128_Type *om_aes128, uint32_t plain_cipher[4]);
# 175 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern om_error_t drv_aes128_encrypt_int(OM_AES128_Type *om_aes128,
                                         uint32_t key[4],
                                         uint32_t input[4],
                                         uint32_t output[4]);
# 206 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern void drv_aes128_isr_callback(OM_AES128_Type *om_aes128, drv_event_t event, uint32_t* output, uint8_t encrypt_length);
# 217 "../../../hal/driver/include/../om6239/../common/drv_aes128.h"
extern void drv_aes128_isr(OM_AES128_Type *om_aes128);
# 64 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_timer.h" 1
# 65 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_pwm.h" 1
# 66 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_rf.h" 1
# 76 "../../../hal/driver/include/../om6239/../common/drv_rf.h"
void drv_rf_select_24g(void);
void drv_rf_select_ble(void);






_Bool drv_rf_is_ble_mode(void);





void drv_ble_init(void);




void drv_rf24g_init(void);





void drv_rf_set_tx_power(uint8_t pwr);
int8_t drv_rf_get_rssi(void);




void drv_rf_set_phy_mode_1mbps(void);
void drv_rf_set_phy_mode_2mbps(void);





void drv_rf_set_channel(uint8_t channel);





void drv_rf_adjust_xtal(uint8_t tune);





void drv_rf_enable_interrupt(uint8_t bitmask);
void drv_rf_disable_interrupt(uint8_t bitmask);




void drv_rf_enable_whitening(void);
void drv_rf_disable_whitening(void);





void drv_ble_set_crc_init(uint32_t crcinit);





void drv_ble_set_access_address(uint32_t aa);





void drv_ble_conn_set_chn_idx(uint8_t chn_idx);





void drv_ble_set_bda(const uint8_t *bda);





void drv_ble_get_bda(uint8_t bda[6]);







void drv_ble_set_whitelist(uint8_t entry, uint8_t bda[6]);



void drv_ble_enable_whitelist(void);
void drv_ble_disable_whitelist(void);







void drv_ble_set_adv_ind(const uint8_t *p_advdata, uint8_t len, _Bool is_random);
void drv_ble_set_scan_rsp(const uint8_t *p_advdata, uint8_t len, _Bool is_random);
void drv_ble_set_scan_req(const uint8_t *p_advdata, uint8_t len, _Bool is_random);





void drv_ble_set_adv_pkt_len(uint8_t len);




void drv_ble_set_adv_pkt_type(uint8_t type);
# 206 "../../../hal/driver/include/../om6239/../common/drv_rf.h"
void drv_ble_set_alarm2rf(uint32_t tick_abs, uint32_t tick_timeout);




void drv_ble_set_state_adv(void);
void drv_ble_set_state_conn_slave(void);
void drv_ble_set_state_scan(void);
void drv_ble_set_state_rxtest(void);
void drv_ble_set_state_txtest(void);



void drv_ble_set_state_rx2tx(void);
void drv_ble_set_state_tx2rx(void);




void drv_ble_start_event(void);

void drv_ble_abort_event(void);

void drv_ble_cancel_abort(void);





_Bool drv_ble_is_state_adv(void);
_Bool drv_ble_is_state_conn(void);
_Bool drv_ble_is_state_scan(void);
_Bool drv_ble_is_state_rxtest(void);
_Bool drv_ble_is_state_txtest(void);




void drv_ble_start_tx_adv(void);
void drv_ble_start_active_scan(void);
void drv_ble_start_passive_scan(void);
void drv_ble_start_tx_test(void);
void drv_ble_start_rx_test(void);





uint8_t drv_rf_get_and_clear_irq_status(void);







_Bool drv_ble_is_event_done(uint8_t status);
_Bool drv_ble_is_received(uint8_t status);
_Bool drv_ble_is_rx_timeout(uint8_t status);
_Bool drv_ble_is_synced(uint8_t status);
# 274 "../../../hal/driver/include/../om6239/../common/drv_rf.h"
uint8_t drv_ble_get_rxed_pkt_bitmap(void);






_Bool drv_ble_is_crc_err(int pkt_idx);







_Bool drv_ble_is_sn_err(int pkt_idx);
_Bool drv_ble_is_nesn_err(int pkt_idx);
# 299 "../../../hal/driver/include/../om6239/../common/drv_rf.h"
_Bool drv_ble_get_data_pkt(int pkt_idx, uint8_t *p_pkt);
_Bool drv_ble_get_adv_pkt(int pkt_idx, uint8_t *p_pkt);
void drv_ble_read_data_pkt(uint8_t *pkt, uint8_t len);




void drv_rf_reset_rx_fifo(void);
void drv_rf_reset_tx_fifo(void);





uint32_t drv_ble_get_anchor_tick(void);







_Bool drv_ble_tx_is_last_empty(int pkt_idx);

_Bool drv_ble_tx_fifo_is_full(void);
_Bool drv_ble_tx_fifo_is_empty(void);
uint8_t drv_ble_tx_fifo_idx(void);
# 337 "../../../hal/driver/include/../om6239/../common/drv_rf.h"
void drv_ble_put_data_pkt(uint8_t *p_pkt);
_Bool drv_ble_put_adv_pkt(int pkt_idx, uint8_t *p_pkt);







_Bool drv_ble_put_test_pkt(uint8_t *p_pkt);




void drv_ble_put_test_payload(const uint8_t *p_payload, uint8_t data_type, uint8_t length);
uint8_t drv_ble_get_test_payload(uint8_t *p_payload);




void drv_rf_enable_rx(void );
void drv_rf_disable_rx(void );




void drv_rf_disable_crc(void );
void drv_rf_enable_crc(void );




void drv_rf_enable_dynamic_payload_length(void );
void drv_rf_disable_dynamic_payload_length(void );




void drv_rf_enable_ack_payload(void );
void drv_rf_disable_ack_payload(void );




void drv_rf_enable_dynamic_ack(void );
void drv_rf_disable_dynamic_ack(void );




void drv_rf_test_start_carrier_tx(void );
void drv_rf_test_stop_carrier_tx(void );




void drv_rf_reuse_tx_fifo(void );




void drv_rf_cleanup(void);





void drv_rf_enable_interrupt(uint8_t bitmask);
void drv_rf_disable_interrupt(uint8_t bitmask);





void drv_rf_enable_pipe(uint8_t bitmask);
void drv_rf_disable_pipe(uint8_t bitmask);
void drv_rf_enable_pipe_auto_ack(uint8_t bitmask);
void drv_rf_disable_pipe_auto_ack(uint8_t bitmask);
void drv_rf_enable_pipe_dynamic_payload_length(uint8_t bitmask);
void drv_rf_disable_pipe_dynamic_payload_length(uint8_t bitmask);






_Bool drv_rf_is_pipe_dynamic_payload_length(uint8_t pipe_no);





void drv_rf_set_pipe_rx_static_payload_length(uint8_t pipe_no, uint8_t len);
uint8_t drv_rf_get_pipe_rx_static_payload_length(uint8_t pipe_no);





void drv_rf_enable_tx_guard(void);
void drv_rf_disable_tx_guard(void);





void drv_rf_set_rx_address_pipe0(const uint8_t addr[5]);
void drv_rf_set_rx_address_pipe1(uint8_t addr);
void drv_rf_set_rx_address_pipe2(uint8_t addr);
void drv_rf_set_tx_address(const uint8_t addr[5]);
void drv_rf_get_rx_address_pipe0(uint8_t addr[5]);
void drv_rf_get_tx_address(uint8_t addr[5]);





uint8_t drv_rf_get_rx_address_pipe1(void);
uint8_t drv_rf_get_rx_address_pipe2(void);





uint8_t drv_rf_get_rx_pipe_no(void);




uint8_t drv_rf_get_rx_dynamic_payload_length(void);





uint8_t drv_rf_get_irq_status(void);







void drv_rf_write_tx_payload(const uint8_t *p_payload, uint8_t len);
void drv_rf_write_ack_payload(const uint8_t *p_payload, uint8_t len, uint8_t pipe);



void drv_rf_write_tx_payload_noack(const uint8_t *p_payload, uint8_t len);
uint8_t drv_rf_read_rx_payload(uint8_t *p_payload);



uint8_t drv_rf_read_rx_payload_static(uint8_t *p_payload, uint8_t len);






void drv_rf_set_auto_retry_param(uint16_t delay_us, uint8_t count);






_Bool drv_rf_rx_fifo_is_empty(void );
_Bool drv_rf_rx_fifo_is_full(void );
_Bool drv_rf_tx_fifo_is_empty(void );
_Bool drv_rf_tx_fifo_is_full(void );
_Bool drv_rf_tx_fifo_is_reuse(void );




void drv_rf_dump_all_register(void);




uint16_t drv_rf_get_fsm(void);





uint16_t drv_rf_get_chipID(void);
# 67 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_icache.h" 1
# 55 "../../../hal/driver/include/../om6239/../common/drv_icache.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 56 "../../../hal/driver/include/../om6239/../common/drv_icache.h" 2
# 70 "../../../hal/driver/include/../om6239/../common/drv_icache.h"
typedef enum {
    ICACHE_MONITOR_MODE_CYCLE = 0U,
    ICACHE_MONITOR_MODE_INSN_HIT = 1U,
    ICACHE_MONITOR_MODE_DATA_HIT = 2U,
} icache_monitor_mode_t;
# 90 "../../../hal/driver/include/../om6239/../common/drv_icache.h"
__attribute__((always_inline)) static __inline uint32_t get_icache_get_monitor_count(void)
{
    return ((OM_ICACHE_Type *) 0x40000400)->MON_STATUS;
}






static __inline void drv_icache_enable(void)
{
    ((OM_ICACHE_Type *) 0x40000400)->CONFIG = 0;
    ((OM_ICACHE_Type *) 0x40000400)->CTRL = (1u << 0);
    while ((((OM_ICACHE_Type *) 0x40000400)->STATUS & (1u << 0)) == 0);
}






static __inline void drv_icache_disable(void)
{
    ((OM_ICACHE_Type *) 0x40000400)->CONFIG = (1u << 0);
    ((OM_ICACHE_Type *) 0x40000400)->CTRL = 0;
    while ((((OM_ICACHE_Type *) 0x40000400)->STATUS & (1u << 0)) != 0);
}






static __inline void drv_icache_inv_all(void)
{

    ((OM_ICACHE_Type *) 0x40000400)->MAINT0 = (1u << 0);

    ((OM_ICACHE_Type *) 0x40000400)->MON_CTRL = 1;
}
# 142 "../../../hal/driver/include/../om6239/../common/drv_icache.h"
extern void drv_icache_monitor_ctrl(uint8_t monitor_en, icache_monitor_mode_t monitor_mode);
# 68 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_flash.h" 1
# 55 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 56 "../../../hal/driver/include/../om6239/../common/drv_flash.h" 2
# 71 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
typedef enum {
    FLASH_ERASE_PAGE = 0x81u,
    FLASH_ERASE_SECTOR = 0x20u,
    FLASH_ERASE_BLOCK_32K = 0x52u,
    FLASH_ERASE_BLOCK_64K = 0xD8u,
    FLASH_ERASE_CHIP = 0xC7u,
} flash_erase_t;
# 86 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
typedef enum {
    RCC_XIP_OPCODE_FREAD = 0x0Bu,
    RCC_XIP_OPCODE_DREAD = 0x3Bu,
    RCC_XIP_OPCODE_2READ = 0xBBu,
    RCC_XIP_OPCODE_QREAD = 0x6Bu,
    RCC_XIP_OPCODE_4READ = 0xEBu,
} flash_xip_opcode_t;
# 101 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
typedef struct {
    uint8_t flash_dly_cycle;
    flash_xip_opcode_t xip_opcode;
} flash_config_t;
# 122 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
extern __attribute((used, section("RAM_CODE"), noinline)) om_error_t drv_flash_init(void);
# 136 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
extern __attribute((used, section("RAM_CODE"), noinline)) om_error_t drv_flash_read(uint32_t offset_addr,
                                            uint8_t *data,
                                            uint32_t data_len);
# 150 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
extern __attribute((used, section("RAM_CODE"), noinline)) om_error_t drv_flash_write(uint32_t offset_addr,
                                             uint8_t *data,
                                             uint32_t data_len);
# 162 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
extern __attribute((used, section("RAM_CODE"), noinline)) om_error_t drv_flash_erase(uint32_t offset_addr,
                                             flash_erase_t erase_type);







extern __attribute((used, section("RAM_CODE"), noinline)) void drv_flash_enter_deeppowerdown(void);
# 180 "../../../hal/driver/include/../om6239/../common/drv_flash.h"
extern __attribute((used, section("RAM_CODE"), noinline)) void drv_flash_exit_deeppowerdown(void);
# 69 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_wdt.h" 1
# 54 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 55 "../../../hal/driver/include/../om6239/../common/drv_wdt.h" 2
# 69 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
typedef enum {
    WDT_CONTROL_CLK_DISABLE = 0U,
    WDT_CONTROL_CLK_ENABLE = 1U,
    WDT_CONTROL_FEED = 2U,
    WDT_CONTROL_STOP_ON_DEBUG = 3U,
    WDT_CONTROL_STOP_ON_SLEEP = 4U,
    WDT_CONTROL_INT_ENABLE = 5U,
    WDT_CONTROL_INT_DISABLE = 6U,
} wdt_control_t;
# 86 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
typedef struct {
    uint32_t timeout_ms;
} wdt_config_t;
# 116 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
extern void *drv_wdt_control(OM_WDT_Type *om_wdt, wdt_control_t control, void *argu);
# 128 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
extern om_error_t drv_wdt_init(OM_WDT_Type *om_wdt);
# 139 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
extern void drv_wdt_keep_alive(OM_WDT_Type *om_wdt);
# 165 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
extern void drv_wdt_isr_callback(OM_WDT_Type *om_wdt, drv_event_t event);
# 176 "../../../hal/driver/include/../om6239/../common/drv_wdt.h"
extern void drv_wdt_isr(OM_WDT_Type *om_wdt);
# 70 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_uart.h" 1
# 71 "../../../hal/driver/include/../om6239/driver_om6239.h" 2


# 1 "../../../hal/driver/include/../om6239/drv_pmu.h" 1
# 54 "../../../hal/driver/include/../om6239/drv_pmu.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 55 "../../../hal/driver/include/../om6239/drv_pmu.h" 2
# 69 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_POWER_ID_RTC32K = 0U,
    PMU_POWER_ID_RTC2M = 1U,
} pmu_power_id_t;
# 81 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_POWER_DOWN = 0U,
    PMU_POWER_ON = 1U,
    PMU_POWER_UNKNOWN = 2U,
} pmu_power_t;
# 94 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_PLL_CTRL_STOP = 0U,
    PMU_PLL_CTRL_START = 1U,
    PMU_PLL_CTRL_RESET = 2U,
} pmu_pll_ctrl_t;
# 107 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_WAKEUP_SRC_IO = 1u << 0,
    PMU_WAKEUP_SRC_RTC = 1u << 1,
    PMU_WAKEUP_SRC_RTC_TICK = 1u << 2,
    PMU_WAKEUP_SRC_RTC_ALARM = 1u << 3,
    PMU_WAKEUP_SRC_RTC_ALARM1 = 1u << 4,
    PMU_WAKEUP_SRC_WDT = 1u << 5,
    PMU_WAKEUP_SRC_VBUS_DET = 1u << 6,
} pmu_wakeup_src_t;
# 124 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_POWER_MODE_KEEP = 0U,
    PMU_POWER_MODE_AUTO = 1U,
} pmu_power_mode_t;
# 136 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_DEV_ID_FLASH_POWER = 0U,
} pmu_dev_id_t;
# 147 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_LPM_IDLE = 0U,
    PMU_LPM_STOP0 = 1U,
    PMU_LPM_STOP1 = 2U,
    PMU_LPM_STANDBY = 3U,
    PMU_LPM_RETENTION = 4U,
    PMU_LPM_DEEP_SLEEP = 5U,
    PMU_LPM_ACTIVE = 6U,
} pmu_lpm_t;
# 164 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_PIN_MODE_PP = 0U,
    PMU_PIN_MODE_FLOAT = 1U,
    PMU_PIN_MODE_PU = 2U,
    PMU_PIN_MODE_PD = 3U,
} pmu_pin_mode_t;
# 178 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_PIN_DRIVER_CURRENT_8MA = 0U,
    PMU_PIN_DRIVER_CURRENT_24MA = 1U,
    PMU_PIN_DRIVER_CURRENT_32MA = 2U,
    PMU_PIN_DRIVER_CURRENT_48MA = 3U,
} pmu_pin_driver_current_t;
# 192 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_PIN_WAKEUP_TYPE_DISABLE = 0U,
    PMU_PIN_WAKEUP_TYPE_RISE = 1U,
    PMU_PIN_WAKEUP_TYPE_FALL = 2U,
} pmu_pin_wakeup_type_t;
# 205 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_UART_SEL_IO_04_06 = 0U,
    PMU_UART_SEL_IO_09_10 = 1U,
    PMU_UART_SEL_IO_18_21 = 2U,
} pmu_uart_sel_t;
# 218 "../../../hal/driver/include/../om6239/drv_pmu.h"
typedef enum {
    PMU_LEDC_SEL_IO_01 = 0U,
    PMU_LEDC_SEL_IO_05 = 1U,
    PMU_LEDC_SEL_IO_17 = 2U,
    PMU_LEDC_SEL_IO_27 = 3U,
} pmu_ledc_sel_t;
# 239 "../../../hal/driver/include/../om6239/drv_pmu.h"
__attribute__((always_inline)) static __inline pmu_wakeup_src_t drv_pmu_get_wakeup_src(void)
{
    return (pmu_wakeup_src_t)((((OM_PMU_Type *) 0x40000000)->WKINT_CLR & (0x7Fu << 1)) >> 1);
}






__attribute__((always_inline)) static __inline void drv_pmu_clear_wakeup(void)
{
    ((OM_PMU_Type *) 0x40000000)->WKINT_CLR = (0x1U << 0);
}
# 261 "../../../hal/driver/include/../om6239/drv_pmu.h"
__attribute__((always_inline)) static __inline uint8_t drv_pmu_get_low_power_mode(void)
{
    return ((OM_PMU_Type *) 0x40000000)->LPMS & (0x7U << 0);
}
# 275 "../../../hal/driver/include/../om6239/drv_pmu.h"
__attribute__((always_inline)) static __inline void drv_pmu_ram_retention_ctrl(uint8_t en)
{
    if (en) {

        ((OM_PMU_Type *) 0x40000000)->LPMS |= (0x1U << 3);
    } else {
        ((OM_PMU_Type *) 0x40000000)->LPMS &= ~(0x1U << 3);
    }
}
# 294 "../../../hal/driver/include/../om6239/drv_pmu.h"
__attribute__((always_inline)) static __inline void drv_pmu_uart_select(pmu_uart_sel_t uart_sel)
{
    register_set(&(((OM_PMU_Type *) 0x40000000)->PINMUX_SEL), (0x3u << 0), uart_sel);
}
# 308 "../../../hal/driver/include/../om6239/drv_pmu.h"
__attribute__((always_inline)) static __inline void drv_pmu_ledc_sel(pmu_ledc_sel_t ledc_sel)
{
    register_set(&(((OM_PMU_Type *) 0x40000000)->PINMUX_SEL), (0x3u << 4), ledc_sel << 4);
}
# 322 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern void drv_pmu_syspll_ctrl(pmu_pll_ctrl_t syspll_ctrl);
# 334 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern void drv_pmu_power_set(pmu_power_id_t power_id, pmu_power_t power);
# 345 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern pmu_power_t drv_pmu_power_get(pmu_power_id_t power_id);
# 357 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern om_error_t drv_pmu_power_mode_select(pmu_dev_id_t dev_id, pmu_power_mode_t power_mode);
# 368 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern __attribute((used, section("RAM_CODE"), noinline)) void drv_pmu_set_low_power_mode(pmu_lpm_t level);
# 377 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern _Bool drv_pmu_can_pop_cpu(void);
# 387 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern void drv_pmu_pin_mode_set(uint8_t pin_idx, pmu_pin_mode_t mode);
# 397 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern void drv_pmu_pin_driven_current_set(uint8_t pin_idx, pmu_pin_driver_current_t driven);
# 407 "../../../hal/driver/include/../om6239/drv_pmu.h"
extern void drv_pmu_wakeup_pin_set(uint8_t pin_idx, pmu_pin_wakeup_type_t trigger_type);

extern void drv_pmu_rf_mode_set(uint8_t rf_mode);
extern uint8_t drv_pmu_rf_mode_get(void);
# 74 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/../common/drv_pinmux.h" 1
# 75 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/drv_senscan.h" 1
# 76 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/drv_ledc.h" 1
# 55 "../../../hal/driver/include/../om6239/drv_ledc.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 56 "../../../hal/driver/include/../om6239/drv_ledc.h" 2
# 70 "../../../hal/driver/include/../om6239/drv_ledc.h"
typedef struct {
    uint32_t reset_cycles;
    uint16_t long_pulse_cycles;
    uint16_t short_pulse_cycles;
} ledc_config_t;
# 93 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern om_error_t drv_ledc_init(OM_LEDC_Type *om_ledc, ledc_config_t *config);
# 106 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern om_error_t drv_ledc_write();
# 119 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern om_error_t drv_ledc_write_int(OM_LEDC_Type *om_ledc, uint8_t *data, uint16_t data_len);
# 132 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern void drv_ledc_register_isr_callback(OM_LEDC_Type *om_ledc, drv_isr_callback_t isr_cb);
# 146 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern void drv_ledc_isr_callback(OM_LEDC_Type *om_ledc, drv_event_t event);
# 157 "../../../hal/driver/include/../om6239/drv_ledc.h"
extern void drv_ledc_isr(OM_LEDC_Type *om_ledc);
# 77 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/drv_encoder.h" 1
# 55 "../../../hal/driver/include/../om6239/drv_encoder.h"
# 1 "../../../hal/driver/include\\om_driver.h" 1
# 56 "../../../hal/driver/include/../om6239/drv_encoder.h" 2
# 71 "../../../hal/driver/include/../om6239/drv_encoder.h"
typedef enum {
    ENCODER_PINMUX_SEL_IO_00_01 = 0U,
    ENCODER_PINMUX_SEL_IO_05_06 = 1U,
    ENCODER_PINMUX_SEL_IO_20_21 = 2U,
    ENCODER_PINMUX_SEL_IO_24_25 = 3U,
} encoder_pinmux_sel_t;
# 85 "../../../hal/driver/include/../om6239/drv_encoder.h"
typedef enum {
    ENCODER_DEBOUNCE_TIME_0 = 0U,
    ENCODER_DEBOUNCE_TIME_62D5US = 1U,
    ENCODER_DEBOUNCE_TIME_125US = 2U,
    ENCODER_DEBOUNCE_TIME_187US = 3U,
    ENCODER_DEBOUNCE_TIME_250US = 4U,
    ENCODER_DEBOUNCE_TIME_312D5US = 5U,
    ENCODER_DEBOUNCE_TIME_375US = 6U,
    ENCODER_DEBOUNCE_TIME_437D5US = 7U,
    ENCODER_DEBOUNCE_TIME_500US = 8U,
    ENCODER_DEBOUNCE_TIME_562D5US = 9U,
    ENCODER_DEBOUNCE_TIME_625US = 10U,
    ENCODER_DEBOUNCE_TIME_687D5US = 11U,
    ENCODER_DEBOUNCE_TIME_750US = 12U,
    ENCODER_DEBOUNCE_TIME_812D5US = 13U,
    ENCODER_DEBOUNCE_TIME_875US = 14U,
    ENCODER_DEBOUNCE_TIME_1MS = 15U,
} encoder_debounce_time_t;
# 111 "../../../hal/driver/include/../om6239/drv_encoder.h"
typedef enum {
    ENCODER_MODE_0 = 0U,
    ENCODER_MODE_1 = 1U,
    ENCODER_MODE_2 = 2U,
    ENCODER_MODE_3 = 3U,
} encoder_mode_t;
# 125 "../../../hal/driver/include/../om6239/drv_encoder.h"
typedef enum {
    ENCODER_CONTROL_START = 1U,
    ENCODER_CONTROL_STOP = 2U,
    ENCODER_CONTROL_READ_WHEEL_DATA = 3U,
    ENCODER_CONTROL_WAKEUP_EN = 4U,
    ENCODER_CONTROL_WAKEUP_DISABLE = 5U,
    ENCODER_CONTROL_READ_WHEEL_VALID = 6U,
} encoder_control_t;
# 141 "../../../hal/driver/include/../om6239/drv_encoder.h"
typedef struct {
    encoder_pinmux_sel_t pinmux_sel;
    encoder_debounce_time_t debounce_time;
    encoder_mode_t mode;
} encoder_config_t;
# 168 "../../../hal/driver/include/../om6239/drv_encoder.h"
__attribute__((always_inline)) static __inline void *drv_encoder_control(OM_ENCODER_Type *om_encoder, encoder_control_t control, void *argu)
{
    uint32_t ret;

    ret = (uint32_t)OM_ERROR_OK;

    switch (control) {
        case ENCODER_CONTROL_START:
            om_encoder->EN |= (1U << (0U));
            break;
        case ENCODER_CONTROL_STOP:
            om_encoder->EN &= ~(1U << (0U));
            break;
        case ENCODER_CONTROL_READ_WHEEL_DATA:
            ret = om_encoder->CNT;
            break;
        case ENCODER_CONTROL_WAKEUP_EN:
            om_encoder->EN |= (1U << (2U));
            break;
        case ENCODER_CONTROL_WAKEUP_DISABLE:
            om_encoder->EN &= ~(1U << (2U));
            break;
        case ENCODER_CONTROL_READ_WHEEL_VALID:
                ret = om_encoder->VALID;
            break;
        default:
            break;
    }

    return (void *)ret;
}
# 210 "../../../hal/driver/include/../om6239/drv_encoder.h"
extern void drv_encoder_init(void);
# 221 "../../../hal/driver/include/../om6239/drv_encoder.h"
extern om_error_t drv_encoder_read_int(OM_ENCODER_Type *om_encoder);
# 234 "../../../hal/driver/include/../om6239/drv_encoder.h"
extern void drv_encoder_register_isr_callback(OM_ENCODER_Type *om_encoder, drv_isr_callback_t isr_cb);
# 246 "../../../hal/driver/include/../om6239/drv_encoder.h"
extern void drv_encoder_isr(OM_ENCODER_Type *om_encoder);
# 78 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 1 "../../../hal/driver/include/../om6239/drv_dynamic_load.h" 1
# 60 "../../../hal/driver/include/../om6239/drv_dynamic_load.h"
typedef struct {
    uint32_t* src;
    uint32_t* dest;
    uint32_t len;
} __copy_table_t;

typedef struct {
    uint32_t* dest;
    uint32_t len;
} __zero_table_t;

typedef struct {
    __copy_table_t ro_rw_section;
    __zero_table_t zi_section;
} app_t;
# 90 "../../../hal/driver/include/../om6239/drv_dynamic_load.h"
void drv_dynamic_load_app(app_t *app);
# 79 "../../../hal/driver/include/../om6239/driver_om6239.h" 2
# 59 "../../../hal/driver/include\\om_driver.h" 2
# 17 "../../../mode_usb/main_usb.h" 2

# 1 "../main\\main.h" 1
# 246 "../main\\main.h"
typedef enum {
    iDEVICE_TYPE_BLE = 1U,
    iDEVICE_TYPE_BT0 = 0U,
    iDEVICE_TYPE_BT1 = 1U,
    iDEVICE_TYPE_BT2 = 2U,
    iDEVICE_TYPE_24G = 3U,
    iDEVICE_TYPE_USB = 4U,
    iDEVICE_TYPE_ERR = 5U,
} device_type_t;




extern _Bool brf_rate;
extern _Bool bmode_swtich_valid;

extern volatile uint8_t ble_24g_ctrl;







extern volatile unsigned char sys_ctrl;




extern uint8_t sys_type;






extern device_type_t device_type;
extern device_type_t bt_index;

extern volatile uint32_t sys_tick_count;
extern uint32_t rtc_init_value;
extern uint32_t rtc_cur_value;
extern uint32_t rtc_temp_value;

extern uint8_t wheel_data;
extern uint8_t m_tx_count;
extern uint8_t key_tx_count;
extern uint8_t key_ex_tx_count;
extern uint8_t mmk_tx_count;
extern uint8_t def_tx_count;




extern uint8_t m_data_flag;







extern uint8_t hint_led_status;
# 317 "../main\\main.h"
extern uint8_t kb_led_status;






extern uint8_t mouse_data_key;
extern uint16_t mouse_x;
extern uint16_t mouse_y;
extern uint8_t mouse_data_z;

extern unsigned char std_key[];
# 341 "../main\\main.h"
extern uint8_t mmk_data_l;
extern uint8_t mmk_data_h;
extern uint8_t kb_bd_addr[];

extern uint32_t const ble_sleep_1_time_tbl[];
extern uint32_t const ble_sleep_2_time_tbl[];




extern void mouse_periph_wakeup_enable(uint8_t mask);
# 19 "../../../mode_usb/main_usb.h" 2

# 1 "../led\\led.h" 1
# 55 "../led\\led.h"
enum led_level
{
    iLED_LEV_MIN=0,
    iLED_LEV_0 = 0,
    iLED_LEV_1 = 1,
    iLED_LEV_2 = 2,
    iLED_LEV_3 = 3,
    iLED_LEV_4 = 4,
    iLED_LEV_MAX = 4,
};

enum speed_level
{
    iSPEED_LEV_MIN = 0,
    iSPEED_LEV_1 = 0,
    iSPEED_LEV_2 = 1,
    iSPEED_LEV_3 = 2,
    iSPEED_LEV_4 = 3,
    iSPEED_LEV_5 = 4,
    iSPEED_LEV_MAX = 4,
};

typedef enum {
    iMODE_LED_OFF =0,
    iMODE_LED_ON =1,
    iMODE_LED_BREATH =2,
    iMODE_LED_SNAKE =3,
    iMODE_LED_NHJB =4,
    iMODE_LED_LG_L_R =5,
    iMODE_LED_STAR =6,
    iMODE_LED_SBZL =7,
    iMODE_LED_BS =8,
    iMODE_LED_QCNH =9,
    iMODE_LED_LHTW =10,
    iMODE_LED_DXTW =11,
    iMODE_LED_SXTW =12,
    iMODE_LED_TXTW =13,
    iMODE_LED_FXTW =14,
    iMODE_LED_JG =15,

    iMODE_LED_MAX =15,
    iMODE_LED_INVALID =16,
    iLOGO_INVALID = 0x0F,
} logo_mode_t;
# 119 "../led\\led.h"
extern _Bool blogo_status;
extern _Bool bled_bright_en;
extern _Bool bback_led_status;
extern _Bool bargb_valid;

extern uint8_t gtemp_i;
extern uint8_t gtemp_j;
extern uint8_t gtemp_x;

extern uint8_t led_hint_mode;
extern uint8_t led_cur_mode;
extern uint8_t led_mode_bak;

extern uint8_t logo_hint_time_count;
extern uint8_t logo_hint_on_time;
extern uint8_t logo_hint_off_time;

extern uint8_t rgb_enable;

extern uint16_t led_ctrl_reg;
extern uint16_t led_status_reg;
extern uint8_t led_use_flag;

extern uint8_t led_cur_mode;
extern uint8_t led_pre_mode;
extern enum speed_level led_speed_lev;
extern unsigned char led_rgb_index;
extern unsigned char pwm_value;
extern enum led_level led_light_lev;

extern uint16_t lfsr_value;
extern uint8_t start_dec_count;
extern uint8_t snake_led_index;

extern uint8_t pwm_time_count;
extern uint16_t delay_time_count;
extern uint8_t rgb_index;
extern uint8_t led_process_index;
extern uint8_t hint_time_count;
extern uint32_t exled_rtc_count;

extern uint8_t pwm_rgb_tbl[(8)][3];

extern uint8_t pwm_duty_array_0[];
extern uint8_t pwm_duty_array_1[];
extern uint8_t pwm_duty_array_2[];
extern uint8_t pwm_duty_array_3[];

extern unsigned char const rgb_en_tbl[];

extern unsigned char const led_liuguang_l_r_tbl[];
extern unsigned char const led_liuguang_rgb_tbl[];
extern unsigned char const sbzl_r_tbl[];
extern unsigned char const sbzl_g_tbl[];
extern unsigned char const sbzl_b_tbl[];
extern unsigned char const sbzl_ctrl_tbl[];





extern void ledc_init(void);
extern void led_status_hint(void);

extern void logo_off(void);
extern void device_led_on(void);
extern void device_led_off(void);

extern void device_led_process(void);
extern void logo_process(void);

extern void clr_rgb(void);
extern void rgb_pwm0_w(void);
extern void rgb_w_max(void);

extern void led_mode_on(void);
extern void led_mode_breath(void);
extern void led_mode_snake(void);
extern void led_mode_nhjb(void);
extern void led_mode_liuguang(void);
extern void led_mode_star(void);
extern void led_mode_sbzl(void);

extern void led_mode_baoshan(void);
extern void led_mode_qcnh(void);
extern void led_mode_lhtw(void);
extern void led_mode_dxtw(void);
extern void led_mode_sxtw(void);
extern void led_mode_txtw(void);
# 21 "../../../mode_usb/main_usb.h" 2
# 1 "../periph\\lvd.h" 1
# 175 "../periph\\lvd.h"
extern unsigned char bat_status;
# 186 "../periph\\lvd.h"
extern _Bool bbat_update;
extern unsigned char bat_value;
extern uint8_t lvd_scan_count;




extern void usb_5v_check(void);

extern void bat_init(void);
extern unsigned char bat_voltage_check(void);
extern void led_hint_process(void);
# 22 "../../../mode_usb/main_usb.h" 2
# 1 "../periph\\wheel.h" 1
# 44 "../periph\\wheel.h"
extern uint8_t wheel_status;
# 57 "../periph\\wheel.h"
extern void wheel_scan(void);
# 23 "../../../mode_usb/main_usb.h" 2

# 1 "../../../mode_24g\\sleep.h" 1
# 56 "../../../mode_24g\\sleep.h"
extern void mcu_sleep(void);
extern void rtc_init(void);
extern void sleep_process(void);
# 25 "../../../mode_usb/main_usb.h" 2
# 1 "../periph\\userdefined_key.h" 1
# 32 "../periph\\userdefined_key.h"
extern _Bool bkey_break_or_realse;

extern unsigned char define_key_status;




extern unsigned char define_key_ctrl;
# 48 "../periph\\userdefined_key.h"
extern uint8_t decode_data_l;
# 59 "../periph\\userdefined_key.h"
extern uint8_t decode_data_h;
# 71 "../periph\\userdefined_key.h"
extern unsigned char define_key_fifo[];
extern unsigned char com_key_index;



extern unsigned char define_key_flag;
# 101 "../periph\\userdefined_key.h"
extern void define_key_process(void);
# 26 "../../../mode_usb/main_usb.h" 2
# 1 "../periph\\time_delay.h" 1
# 56 "../periph\\time_delay.h"
extern void delayus(unsigned int time);

extern void uart_init(void);
extern void uart_tx(unsigned char data);
# 27 "../../../mode_usb/main_usb.h" 2

# 1 "../flash\\flash.h" 1
# 61 "../flash\\flash.h"
extern _Bool bflash_ctrl;




extern _Bool flash_write(unsigned int addr, unsigned int length);
extern _Bool flash_write_ble_addr(unsigned int addr);
extern _Bool flash_read(unsigned int addr, unsigned int length);
extern _Bool flash_erase(unsigned char bank);
# 29 "../../../mode_usb/main_usb.h" 2
# 1 "../flash\\flash_process.h" 1
# 152 "../flash\\flash_process.h"
enum key_mod
{
    iKEY_MODE_MIN=0,
    iKEY_MODE_0 = 0,
    iKEY_MODE_1 = 1,
    iKEY_MODE_2 = 2,
    iKEY_MODE_3 = 3,
    iKEY_MODE_MAX = 3,
};




extern _Bool bsave_status;
extern _Bool bsave_cfg_dpi;
extern _Bool bsave_ble_id;
extern _Bool bsave_mode;

extern unsigned char device_status_base;
extern uint8_t flash_fifo[];

extern uint8_t def_key_dat[];
extern uint8_t def_key_fn_dat[];

extern uint8_t para_cfg_dat[];





extern uint8_t report_dpi[];
extern uint8_t ble_id[];

extern uint8_t key_mode;

extern uint8_t sleep_time_24g;
extern uint8_t sleep_time_ble;
extern uint8_t report_usb;
extern uint8_t report_24g;
extern uint8_t sys_mode;

extern uint8_t mouse_lod_set;
extern uint8_t key_delay_set;
extern uint16_t adv_cfg_value;
# 204 "../flash\\flash_process.h"
extern uint8_t device_status_base;
extern uint8_t sys_cfg_base;




extern void laod_defaut_status(void);
extern void laod_mouse_status(void);
extern void laod_cfg_dpi(void);

extern void laod_flash_cfg(void);

extern void flash_save_status(void);
extern void flash_save_cfg_dpi(void);

extern void flash_load_ble_addr(void);
extern void flash_save_ble_addr(void);
# 30 "../../../mode_usb/main_usb.h" 2

# 1 "../../../mode_usb/hid_process.h" 1
# 152 "../../../mode_usb/hid_process.h"
extern _Bool bjump_boot;

extern volatile unsigned char hid_ctrl_reg;







extern unsigned char in_report_data[];
extern unsigned char out_report_data[];
extern unsigned char hid_flag;




extern void hid_process(void);
# 32 "../../../mode_usb/main_usb.h" 2
# 1 "../../../mode_usb/usb_cfg_info.h" 1
# 71 "../../../mode_usb/usb_cfg_info.h"
extern _Bool busb_mouse_in_en;
extern _Bool bkey_mode_change;

extern unsigned char usb_ctrl_flag;
# 85 "../../../mode_usb/usb_cfg_info.h"
extern unsigned char g_USB_Ep_Status[4];
extern unsigned char g_USB_State;




extern void usb_data_process(void);
# 33 "../../../mode_usb/main_usb.h" 2
# 80 "../../../mode_usb/main_usb.h"
extern void mouse_usb_init(void);
extern int main_usb(void);
# 12 "../../../mode_usb/hal_usb_decs.c" 2

# 1 "../../../mode_usb/usb_descriptor.h" 1
# 470 "../../../mode_usb/usb_descriptor.h"
unsigned char const string255[] = {
 10,
 0X03,
 'B',0,'Y',0,'C',0,'X',0,
};

unsigned char const stringmanufacturer[] = {
    34,0x03,
 'G',0,'a',0,'m',0,'i',0,'n',0,'g',0,' ',0,
 'K',0,'e',0,'y',0,'b',0,'o',0,'a',0,'r',0,'d',0,' ',0,
};

unsigned char const StringDescSerialNum[] =
{
    28,
 0x03,
 'N',0,'o',0,'.',0,
 '0',0,'7',0,'3',0,'-',0,
 '0',0,'0',0,'0',0,'3',0,'-',0,
 '2',0,
};

unsigned char const HID_ReportDescriptor_Define[] = {

    0x05,0x01,
    0x09,0x02,
    0xA1,0x01,
      0x85,0x02,
      0x09,0x01,
      0xA1,0x00,
        0x05,0x09,
        0x19,1,
        0x29,8,
        0x15,0,
        0x25,1,
        0x95,8,
        0x75,1,
        0x81,0<<0 | 1<<1 | 0<<2,
        0x05,0x01,
        0x09,0x30,
        0x09,0x31,
        0x16,(0xF801 & 0xFF),((0xF801 >> 8) & 0xFF),
        0x26,(0x07FF & 0xFF),((0x07FF >> 8) & 0xFF),
        0x75,12,
        0x95,2,
        0x81,0<<0 | 1<<1 | 1<<2,
        0x09,0x38,
        0x15,0x81,
        0x25,0x7F,
        0x75,8,
        0x95,1,
        0x81,0<<0 | 1<<1 | 1<<2,
        0x05,0x0C,
        0x0A,(0x0238 & 0xFF),((0x0238 >> 8) & 0xFF),
        0x95,1,
        0x81,0<<0 | 1<<1 | 1<<2,
      0xC0,
    0xC0,

    0x05,0x01,
    0x09,0x06,
    0xA1,0x01,
      0x85,0x05,
      0x05,0x07,
   0x15,0,
   0x25,1,
   0x19,0x00,
   0x29,0x77,
   0x95,0x78,
   0x75,1,
   0x81,0<<0 | 1<<1 | 0<<2,
    0xC0,


    0x05,0x0C,
    0x09,0x01,
    0xA1,0x01,
      0x85,0x01,
      0x19,1,
      0x2A,(0x03FF & 0xFF),((0x03FF >> 8) & 0xFF),
      0x15,1,
      0x26,(0x03FF & 0xFF),((0x03FF >> 8) & 0xFF),
      0x95,1,
      0x75,16,
      0x81,0<<0 | 0<<1,
    0xC0,

    0x06,0x0F,0xFF,
    0x09,0x01,
    0xA1,0x01,
      0x85,0x0E,
      0x09,0x02,
      0x15,0,
      0x26,(0xFF & 0xFF),((0xFF >> 8) & 0xFF),
      0x75,8,
      0x95,31,
      0x81,0<<0 | 1<<1 | 0<<2,
      0x09,0x02,
      0x15,0,
      0x26,(0xFF & 0xFF),((0xFF >> 8) & 0xFF),
      0x75,8,
      0x95,31,
      0x91,0<<0 | 1<<1 | 0<<2,
    0xC0
};


unsigned char const HID_ReportDescriptor_Keyboard_6key[] = {
    0x05,0x01,
    0x09,0x06,
    0xA1,0x01,
      0x05,0x08,
      0x19,0x01,
      0x29,0x05,
      0x15,0,
      0x25,1,
      0x95,5,
      0x75,1,
      0x91,0<<0 | 1<<1 | 0<<2,
      0x95,1,
      0x75,3,
      0x91,1<<0,
      0x05,0x07,
      0x1A,(0xE0 & 0xFF),((0xE0 >> 8) & 0xFF),
      0x2A,(0xE7 & 0xFF),((0xE7 >> 8) & 0xFF),
      0x15,0,
      0x25,1,
      0x95,8,
      0x75,1,
      0x81,0<<0 | 1<<1 | 0<<2,
      0x95,1,
      0x75,8,
      0x81,1<<0,
      0x19,0,
      0x2A,(0xFF & 0xFF),((0xFF >> 8) & 0xFF),
      0x15,0,
      0x26,(0xFF & 0xFF),((0xFF >> 8) & 0xFF),
      0x95,6,
      0x81,0<<0 | 0<<1,
    0xC0
};
# 623 "../../../mode_usb/usb_descriptor.h"
unsigned char const DEVICE_Descriptor[] = {
    0x12,
    0x01,
    (0x0110&0xFF),(0x0110>>8)&0xFF,
    0x00,
    0x00,
    0x00,
    0x020,
    (0x32C2&0xFF),(0x32C2>>8)&0xFF,
    (0x0028&0xFF),(0x0028>>8)&0xFF,
    (0x6239&0xFF),(0x6239>>8)&0xFF,
    0x01,
    0x02,
    0x03,
    0x01
};


unsigned char const g_usb_conf_desc[] = {


    0x09,
    0x02,
    (59&0xFF),(59>>8)&0xFF,
    0x02,
    0x01,
    0x00,
    0xA0,
    (500 / 2),




    0x09,
    0x04,
    0x00,
    0x00,
    0x01,
    0x03,
    0x01,
    0x01,
    0x00,


    0x09,
    0x21,
    (0x0110&0xFF),(0x0110>>8)&0xFF,
    0x00,
    0x01,
    0x22,
    (sizeof(HID_ReportDescriptor_Keyboard_6key)&0xFF),(sizeof(HID_ReportDescriptor_Keyboard_6key)>>8)&0xFF,


    0x07,
    0x05,
    (1 | 0x80),
    0x03,
    (8&0xFF),(8>>8)&0xFF,
    0x01,



    0x09,
    0x04,
    0x01,
    0x00,
    0x01,
    0x03,
    0,
    0,
    0x00,


    0x09,
    0x21,
    (0x0110&0xFF),(0x0110>>8)&0xFF,
    0x00,
    0x01,
    0x22,
    (sizeof(HID_ReportDescriptor_Define)&0xFF),(sizeof(HID_ReportDescriptor_Define)>>8)&0xFF,


    0x07,
    0x05,
    (3 | 0x80),
    0x03,
    (32&0xFF),(32>>8)&0xFF,
    0x01,
};

unsigned char const DeviceHidDescriptor_KB[]={
    0x09,
    0x21,
    (0x0110&0xFF),(0x0110>>8)&0xFF,
    0x00,
    0x01,
    0x22,
    (sizeof(HID_ReportDescriptor_Keyboard_6key)&0xFF),(sizeof(HID_ReportDescriptor_Keyboard_6key)>>8)&0xFF
};

unsigned char const DeviceHidDescriptor_DEF[]={
    0x09,
    0x21,
    (0x0110&0xFF),(0x0110>>8)&0xFF,
    0x00,
    0x01,
    0x22,
    (sizeof(HID_ReportDescriptor_Define)&0xFF),(sizeof(HID_ReportDescriptor_Define)>>8)&0xFF
};


unsigned char const String0Descriptor[] = {
    0x04,
    0x03,
    (0x0409&0xFF),(0x0409>>8)&0xFF
};
# 14 "../../../mode_usb/hal_usb_decs.c" 2
# 27 "../../../mode_usb/hal_usb_decs.c"
static enum ep0_state_t {
  USB_EP0_WAITING_SETUP,
  USB_EP0_TX,
  USB_EP0_WAITING_TX0,
  USB_EP0_WAITING_STS,
  USB_EP0_RX,
  USB_EP0_SENDING_STS,
  USB_EP0_ERROR
} ep0_state;
# 54 "../../../mode_usb/hal_usb_decs.c"
_Bool busb_mouse_in_en;
_Bool busb_open;
unsigned char usb_ctrl_flag;

static uint8_t stall_data_size0;

unsigned char *g_USB_DataPtr;
unsigned char g_USB_DataSize;

unsigned char g_USB_Ep_Status[4];
unsigned char g_USB_State;
unsigned char usbrx0fifo[8];

unsigned char Mouse_Current_Protocol;
unsigned char Keyboard_Current_Protocol;
unsigned char Def_Current_Protocol;

unsigned char Control_Idle;
unsigned char Keyboard_Idle;
unsigned char Mouse_Idle;
unsigned char Def_Idle;

unsigned char g_sys_alternate;
unsigned char sof_count;
# 90 "../../../mode_usb/hal_usb_decs.c"
void set_stall(void)
{
    ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001;
}

void usb_data_size_min(unsigned char length)
{
    g_USB_DataSize = length;
    if((0 == usbrx0fifo[7]) && (usbrx0fifo[6]<length))
        g_USB_DataSize = usbrx0fifo[6];
}
# 109 "../../../mode_usb/hal_usb_decs.c"
static void packetizer_isr_ep0_in(void)
{
    uint8_t size, i;
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];


    if(g_USB_DataSize == 0)
    {
        if (stall_data_size0 == 1)
        {
          do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);

        }
        else
        {
          stall_data_size0 = 1;
        }
        return;
    }

    size = ((g_USB_DataSize) < (0x020) ? (g_USB_DataSize) : (0x020));

    for(i = 0; i < size; i++)
    {
        *fifo_ep0 = g_USB_DataPtr[i];
    }

    if (size < 0x020) {
        stall_data_size0 = 1;

        do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
    }
    else
    {


        ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002;
    }


    g_USB_DataPtr += size;
    g_USB_DataSize -= size;

    return;
}
# 162 "../../../mode_usb/hal_usb_decs.c"
void hid_get_idle(void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

    if(usbrx0fifo[0] == 0xA2)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0xA1)
    {
        if(usbrx0fifo[4] == 0xff)
        {
            *fifo_ep0 = Control_Idle;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else if(usbrx0fifo[4] == 0x00)
        {
            *fifo_ep0 = Keyboard_Idle;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else if(usbrx0fifo[4] == 0x01)
        {
            *fifo_ep0 = Mouse_Idle;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
# 207 "../../../mode_usb/hal_usb_decs.c"
void hid_get_protocol(void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

    if(usbrx0fifo[0] == 0xA2)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0xA1)
    {
        if(usbrx0fifo[4] == 0x00)
        {
            *fifo_ep0 = Keyboard_Current_Protocol;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else if(usbrx0fifo[4] == 0x01)
        {
            *fifo_ep0 = Mouse_Current_Protocol;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
# 247 "../../../mode_usb/hal_usb_decs.c"
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
            if(usbrx0fifo[4] == 0xff)
            {
                Control_Idle = usbrx0fifo[3];
                g_USB_DataSize = 0;
                packetizer_isr_ep0_in();
            }
            else if(usbrx0fifo[4] == 0x00)
            {
                Keyboard_Idle=usbrx0fifo[3];
                g_USB_DataSize = 0;
                packetizer_isr_ep0_in();
            }
            else if(usbrx0fifo[4] == 0x01)
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
# 295 "../../../mode_usb/hal_usb_decs.c"
void hid_set_protocol (void)
{
    if(0x00 ==usbrx0fifo[2])
        usb_ctrl_flag &= ~(1<<0);
    else
        usb_ctrl_flag |= (1<<0);

    if(usbrx0fifo[0] == 0x22)
    {
         usbrx0fifo[0]--;
         usbrx0fifo[1]--;
    }

    if(usbrx0fifo[0] == 0x21)
    {
        if(usbrx0fifo[4] == 0x00)
        {
            Keyboard_Current_Protocol=usbrx0fifo[2];
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else if(usbrx0fifo[4] == 0x01)
        {
            Mouse_Current_Protocol= usbrx0fifo[2];
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
# 338 "../../../mode_usb/hal_usb_decs.c"
static void usb_get_status(void)
{
    uint8_t i, *ptr;
    volatile uint16_t *fifo_ep0 = (volatile uint16_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

    if((usbrx0fifo[2] | usbrx0fifo[3] | usbrx0fifo[7]) || (usbrx0fifo[6] != 2))
    {
        set_stall ();
        return;
    }

    if(g_USB_State == 0x03)
    {
        if(usbrx0fifo[4] != 0x00)
        {
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
        }
        else
        {
            *fifo_ep0 = (0 << 8) | 0;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
    }
    else if(g_USB_State == 0x04)
    {
        switch(usbrx0fifo[0])
        {
            case 0x80:
                if(usbrx0fifo[5] || usbrx0fifo[4])
                {
                    set_stall ();
                }
                else
                {
                    if(0 != (usb_ctrl_flag & (1<<1) ))
                        *fifo_ep0 = 0x0002;
                    else
                        *fifo_ep0 = 0x0000;
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
                }
                break;
            case 0x81:
                if(usbrx0fifo[5] | usbrx0fifo[4])
                {
                    set_stall ();
                }
                else
                {
                    *fifo_ep0 = 0x0000;
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
                }
                break;
            case 0x82:
                if(usbrx0fifo[4] !=0 )
                {
                    if(0x03 == g_USB_Ep_Status[usbrx0fifo[4]&0x03])
                        *fifo_ep0 = 0x0001;
                    else
                        *fifo_ep0 = 0x0000;
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
                }
                else
                {
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                }
                break;
            default:
                do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);

                break;
        }
    }
    else
    {
        do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
    }
}
# 423 "../../../mode_usb/hal_usb_decs.c"
void usb_clear_feature(void)
{
    unsigned char Power_Reg;
    if(usbrx0fifo[0] == 0x00)
    {
        if(usbrx0fifo[2] == 0x01)
        {
            usb_ctrl_flag &= ~((1<<1));
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else
        {
            set_stall ();
        }
    }
    else if(usbrx0fifo[0] == 0x02)
    {
        if(usbrx0fifo[4] !=0)
        {
            g_USB_Ep_Status[usbrx0fifo[4]&0x03] = 0x00;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
# 463 "../../../mode_usb/hal_usb_decs.c"
void usb_set_feature (void)
{
    unsigned char Power_Reg;

    if(usbrx0fifo[0] == 0x00)
    {
        if(usbrx0fifo[2] == 0x01)
        {
            usb_ctrl_flag |= (1<<1);
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
            g_USB_Ep_Status[usbrx0fifo[4]&0x03] = 0x03;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
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
# 504 "../../../mode_usb/hal_usb_decs.c"
void usb_set_address(void)
{
    if ((usbrx0fifo[0] != 0) || (usbrx0fifo[2] & 0x80)
         || (usbrx0fifo[3] | usbrx0fifo[4] | usbrx0fifo[5] | usbrx0fifo[6] | usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        g_USB_State = 0x03;

        ((OM_USB_Type *) 0x41000000)->FADDR = usbrx0fifo[2];
    }
}
# 526 "../../../mode_usb/hal_usb_decs.c"
static void usb_get_descriptor(void)
{
    switch(usbrx0fifo[3])
    {
        case 0x01:
            usb_ctrl_flag |= (1<<0);

            g_USB_DataPtr = (uint8_t*)DEVICE_Descriptor;
            usb_data_size_min(sizeof(DEVICE_Descriptor));

            packetizer_isr_ep0_in();
            break;
        case 0x02:

            g_USB_DataPtr = (uint8_t*)g_usb_conf_desc;
            usb_data_size_min(sizeof(g_usb_conf_desc));
            packetizer_isr_ep0_in();
            break;
        case 0x03:
           switch(usbrx0fifo[2])
           {
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
                do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                break;
           }
           break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);

            break;
        case 0x21:
            if(0 == ((usbrx0fifo[4] & 0xFF)))
            {
                g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_KB;
                usb_data_size_min(sizeof(DeviceHidDescriptor_KB));
                packetizer_isr_ep0_in();
            }
            else if(1 == ((usbrx0fifo[4] & 0xFF)))
            {
                g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_DEF;
                usb_data_size_min(sizeof(DeviceHidDescriptor_DEF));
                packetizer_isr_ep0_in();
            }
            break;
        case 0x22:
            if(0 == ((usbrx0fifo[4] & 0xFF)))
            {
                g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Keyboard_6key;
                usb_data_size_min(sizeof(HID_ReportDescriptor_Keyboard_6key));
                packetizer_isr_ep0_in();
            }
            else if(1 == ((usbrx0fifo[4] & 0xFF)))
            {
                g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Define;
                usb_data_size_min(sizeof(HID_ReportDescriptor_Define));
                packetizer_isr_ep0_in();
            }
            break;
        default:
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
            break;
    }
}
# 625 "../../../mode_usb/hal_usb_decs.c"
void usb_get_config (void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

    if((usbrx0fifo[0] != 0x80) || (usbrx0fifo[6] != 1)
        || (usbrx0fifo[2] | usbrx0fifo[3] | usbrx0fifo[4] | usbrx0fifo[5] | usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        if (g_USB_State == 0x04)
        {
            *fifo_ep0 = 0x01;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
        else if (g_USB_State == 0x03)
        {
            *fifo_ep0 = 0x00;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
    }
}
# 656 "../../../mode_usb/hal_usb_decs.c"
void usb_set_config(void)
{
    if((g_USB_State == 0x02) || (usbrx0fifo[0] != 0) || (usbrx0fifo[2] > 1)
        || (usbrx0fifo[3]) | (usbrx0fifo[4]) | (usbrx0fifo[5]) | (usbrx0fifo[6]) | (usbrx0fifo[7]))
    {
        set_stall();
    }
    else
    {
        if(usbrx0fifo[2] > 0)
        {
            g_USB_State = 0x04;
            g_USB_Ep_Status[1] = 0x00;
            g_USB_Ep_Status[2] = 0x00;
            g_USB_Ep_Status[3] = 0x00;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);

            usb_ctrl_flag |= (1<<5);



            __NVIC_EnableIRQ(USB_WK_IRQn);




            ((OM_USB_Type *) 0x41000000)->POWER = 0x01;
        }
        else
        {
            g_USB_State = 0x03;
            g_USB_Ep_Status[1] = 0x03;
            g_USB_Ep_Status[2] = 0x03;
            g_USB_Ep_Status[3] = 0x03;
            do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
        }
    }
}
# 702 "../../../mode_usb/hal_usb_decs.c"
void usb_get_interface (void)
{
    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

    if (usbrx0fifo[0] == 0x81)
    {
        *fifo_ep0 = g_sys_alternate;
        do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0002 | 0x0008; ep0_state = USB_EP0_WAITING_STS; } while (0);
    }
    else
    {
        set_stall();
    }
}
# 724 "../../../mode_usb/hal_usb_decs.c"
void usb_set_interface (void)
{
    if (usbrx0fifo[0] == 0x01)
    {
        if(usbrx0fifo[5] == 0x00)
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[1] = 0x00;
        }
        else if(usbrx0fifo[5] == 0x01)
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[2] = 0x00;
        }
        else if(usbrx0fifo[5] == 0x02)
        {
            g_sys_alternate = usbrx0fifo[3];
            g_USB_Ep_Status[3] = 0x00;
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

    if((usbrx0fifo[0] & 0x60 ) == 0x20)
    {
        if(usbrx0fifo[1] == 0x06 )
        {
            switch( usbrx0fifo[3] )
            {
                case 0x21:
                    if(0 == ((usbrx0fifo[4] & 0xFF)))
                    {
                        g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_KB;
                        usb_data_size_min(sizeof(DeviceHidDescriptor_KB));
                        packetizer_isr_ep0_in();
                    }
                    else if(1 == ((usbrx0fifo[4] & 0xFF)))
                    {
                        g_USB_DataPtr = (uint8_t*)DeviceHidDescriptor_DEF;
                        usb_data_size_min(sizeof(DeviceHidDescriptor_DEF));
                        packetizer_isr_ep0_in();
                    }
                    break;
                case 0x22:
                    if(0 == ((usbrx0fifo[4] & 0xFF)))
                    {
                        g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Keyboard_6key;
                        usb_data_size_min(sizeof(HID_ReportDescriptor_Keyboard_6key));
                        packetizer_isr_ep0_in();
                    }
                    else if(1 == ((usbrx0fifo[4] & 0xFF)))
                    {
                        g_USB_DataPtr = (uint8_t*)HID_ReportDescriptor_Define;
                        usb_data_size_min(sizeof(HID_ReportDescriptor_Define));
                        packetizer_isr_ep0_in();
                    }
                    break;
                default:
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                    break;
            }
        }
        else
        {
            switch( usbrx0fifo[1] )
            {
                case 0x01:
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                    break;
                case 0x02:
                    hid_get_idle();
                    break;
                case 0x0a:
                    hid_set_idle();
                    break;
                case 0x03:
                    hid_get_protocol();
                    break;
                case 0x0b:
                    hid_set_protocol();
                    break;
                case 0x09:
                    usb_ctrl_flag |= (1<<3);
                    ep0_state = USB_EP0_RX;
                    break;
                default:
                    do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                    break;
            }
        }

    }

    else if((usbrx0fifo[0] & 0x60) == 0x00)
    {
        switch(usbrx0fifo[1])
        {
            case 0x00:
                usb_get_status();
                break;
            case 0x01:
                usb_clear_feature();
                break;
            case 0x03:
                usb_set_feature();
                break;
            case 0x04:
                break;
            case 0x05:
                usb_set_address();
                break;
            case 0x06:
                usb_get_descriptor();
                break;
            case 0x07:
                break;
            case 0x08:
                usb_get_config();
                break;
            case 0x09:
                usb_set_config();
                break;
            case 0x0A:
                usb_get_interface();
                break;
            case 0x0B:
                usb_set_interface();
                break;
            case 0x0C:
                break;
            default:
                do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
                break;
        }
    }
    else
    {
        do { ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0020 | 0x0001; } while(0);
    }
}

extern _Bool busb_valid;
# 881 "../../../mode_usb/hal_usb_decs.c"
static void usb_ep_setup(void)
{
    ((OM_USB_Type *) 0x41000000)->INDEX = 1;
    ((OM_USB_Type *) 0x41000000)->INTR_TXEN1 |= (1<<1);
    ((OM_USB_Type *) 0x41000000)->TXMAXP = 0x008 / 8;
    ((OM_USB_Type *) 0x41000000)->TXCSR2 |= 0x2000 >> 8;

    ((OM_USB_Type *) 0x41000000)->INDEX = 2;
    ((OM_USB_Type *) 0x41000000)->INTR_TXEN1 |= (1<<2);
    ((OM_USB_Type *) 0x41000000)->TXMAXP = 0x020 / 8;
    ((OM_USB_Type *) 0x41000000)->TXCSR2 |= 0x2000 >> 8;

    ((OM_USB_Type *) 0x41000000)->INDEX = 3;
    ((OM_USB_Type *) 0x41000000)->INTR_TXEN1 |= (1<<3);
    ((OM_USB_Type *) 0x41000000)->TXMAXP = 0x040 / 8;
    ((OM_USB_Type *) 0x41000000)->TXCSR2 |= 0x2000 >> 8;

    ((OM_USB_Type *) 0x41000000)->INDEX = 0;

    __NVIC_EnableIRQ(USB_WK_IRQn);
    ((OM_USB_Type *) 0x41000000)->POWER = 0x01;
}

static void usb_reset_process(void)
{
    ep0_state = USB_EP0_WAITING_SETUP;

    g_USB_State = 0x02;
    usb_ctrl_flag &= ~((1<<1)|(1<<5)|(1<<2));
    usb_ctrl_flag |= (1<<0);

    g_USB_Ep_Status[1] = 0x03;
    g_USB_Ep_Status[2] = 0x03;
    g_USB_Ep_Status[3] = 0x03;


    usb_ep_setup();
}






void USB_WK_IRQHandler(void)
{





    ((OM_RCC_Type *) 0x40000600)->USB_WK_INT_CLR = 0x01;
# 942 "../../../mode_usb/hal_usb_decs.c"
    usb_ctrl_flag &= ~(1<<2);
}

extern uint32_t sleep_into_work_rtc;






void USB_IRQHandler(void)
{
    unsigned char ep_in_if = ((OM_USB_Type *) 0x41000000)->INTR_TX1;
    unsigned char ep_out_if = ((OM_USB_Type *) 0x41000000)->INTR_RX1;
    unsigned char common_if = ((OM_USB_Type *) 0x41000000)->INTR_USB;

    usb_ctrl_flag &= ~(1<<2);

    if(ep_in_if & 0x01)
    {
        ((OM_USB_Type *) 0x41000000)->INDEX = 0;
        unsigned char csr0 = ((OM_USB_Type *) 0x41000000)->CSR0;

        if(csr0 & 0x0004)
        {
            ((OM_USB_Type *) 0x41000000)->CSR0 &= ~0x0004;
            ep0_state = USB_EP0_WAITING_SETUP;
        }
        if(csr0 & 0x0010)
        {
            ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0080;
            ep0_state = USB_EP0_WAITING_SETUP;
        }

        switch (ep0_state)
        {
            case USB_EP0_WAITING_STS:
            case USB_EP0_SENDING_STS:

                ep0_state = USB_EP0_WAITING_SETUP;


            case USB_EP0_WAITING_SETUP:
                if (csr0 & 0x0001)
                {

                    g_USB_DataPtr = 0;
                    g_USB_DataSize = 0;
                    stall_data_size0 = 0;


                    volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];


                    usbrx0fifo[0] = *fifo_ep0;
                    usbrx0fifo[1] = *fifo_ep0;
                    usbrx0fifo[2] = *fifo_ep0;
                    usbrx0fifo[3] = *fifo_ep0;
                    usbrx0fifo[4] = *fifo_ep0;
                    usbrx0fifo[5] = *fifo_ep0;
                    usbrx0fifo[6] = *fifo_ep0;
                    usbrx0fifo[7] = *fifo_ep0;

                    if(0 == usbrx0fifo[6])
                    {
                        ep0_state = USB_EP0_SENDING_STS;


                        ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0040 | 0x0008;
                    }
                    else
                    {
                        if(usbrx0fifo[0] & 0x80)
                            ep0_state = USB_EP0_TX;
                        else
                            ep0_state = USB_EP0_RX;

                        ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0040;
                    }

                    if((0x21==usbrx0fifo[0])&&(0x09==usbrx0fifo[1]))
                    {
                        usb_ctrl_flag |= (1<<3);
                        ep0_state = USB_EP0_RX;
                    }
                    else
                        usb_setup_process();
                }

                break;
            case USB_EP0_RX:
                if (csr0 & 0x0001)
                {
                    g_USB_DataSize = 0;


                    if(0 != (usb_ctrl_flag&(1<<3)))
                    {
                        volatile uint8_t *fifo_ep0 = (volatile uint8_t *)&((OM_USB_Type *) 0x41000000)->EPnFIFO[0];

                        usb_ctrl_flag &= ~(1<<3);
                        if(32 == usbrx0fifo[6])
                        {
                            for(unsigned char i=0; i<32; i++)
                                out_report_data[i] = *fifo_ep0;

                            hid_ctrl_reg |= (1<<1);
                        }
                        else if(1 == usbrx0fifo[6])
                        {
                            kb_led_status = (*fifo_ep0&0x07);
                        }
                    }

                    ((OM_USB_Type *) 0x41000000)->CSR0 |= 0x0040 | 0x0008;
                    ep0_state = USB_EP0_WAITING_SETUP;
                }
                break;
            case USB_EP0_TX:

                packetizer_isr_ep0_in();

                break;
            default:

                break;
        }
    }

    if(common_if & 0x01)
    {
        usb_ctrl_flag |= (1<<2);
    }

    if(common_if & 0x04)
    {
        usb_reset_process();
    }

    if(common_if & 0x08)
    {
        busb_valid = 1;
        sys_tick_count++;
        sof_count++;
        if(0==(sof_count&0x07))
            drv_ledc_write();

        if((3 == report_usb)
            ||(2 == report_usb))
        {
            if(0==(sof_count&0x03))
                sys_ctrl |= (1<<2);
        }
        else if(1 == report_usb)
        {
            if(0==(sof_count&0x03))
                sys_ctrl |= (1<<2);
        }
        else
        {
            if(0==(sof_count&0x07))
                sys_ctrl |= (1<<2);
        }

        sleep_into_work_rtc = drv_rtc_read(((OM_RTC_Type *) 0x40000200));
    }

    if(ep_in_if)
    {
        if(ep_in_if & (1<<1))
            g_USB_Ep_Status[1] = 0x00;
        if (ep_in_if & (1<<2))
            g_USB_Ep_Status[2] = 0x00;
        if (ep_in_if & (1<<3))
            g_USB_Ep_Status[3] = 0x00;
    }
}

extern void delayus(unsigned int time);
# 1129 "../../../mode_usb/hal_usb_decs.c"
void hal_usb_init(void)
{
    uint8_t ei;


    g_USB_State = 0x02;
    stall_data_size0 = 0;


    drv_pmu_syspll_ctrl(PMU_PLL_CTRL_START);
    do { (1U) ? (((OM_RCC_Type *) 0x40000600)->CLKGATE |= (RCC_CLK_USB)) : (((OM_RCC_Type *) 0x40000600)->CLKGATE &= ~(RCC_CLK_USB)); } while(0);

    ((OM_RCC_Type *) 0x40000600)->USB_WK_CLK_SEL = 1;


    ((OM_RCC_Type *) 0x40000600)->USB_CTRL = 0;
    delayus(50000);

    drv_pmu_pin_mode_set(2, PMU_PIN_MODE_FLOAT);
    drv_pmu_pin_mode_set(3, PMU_PIN_MODE_FLOAT);

    ((OM_RCC_Type *) 0x40000600)->USB_CTRL = (0x1 << 4);


    ((OM_USB_Type *) 0x41000000)->INTR_USBEN = 0x04 | 0x02 | 0x01|0x08;
    ((OM_USB_Type *) 0x41000000)->INTR_TXEN1 = 0x01;
    __NVIC_EnableIRQ(USB_IRQn);


    for(ei = 1; ei < 8; ei++)
    {
        ((OM_USB_Type *) 0x41000000)->INDEX = ei;
        ((OM_USB_Type *) 0x41000000)->TXMAXP = 0;
        ((OM_USB_Type *) 0x41000000)->RXMAXP = 0;
    }
}
# 1173 "../../../mode_usb/hal_usb_decs.c"
void hi5_usb_init(void)
{
    if(1 == busb_open)
        return;

    busb_open = 1;

    hal_usb_init();
    usb_ep_setup();





    usb_ctrl_flag &= ~(1<<2);
    usb_ctrl_flag &= ~(1<<1);
    g_USB_Ep_Status[1] = 0x03;
    g_USB_Ep_Status[2] = 0x03;
    g_USB_Ep_Status[3] = 0x03;
}
# 1201 "../../../mode_usb/hal_usb_decs.c"
void usb_disconnect(void)
{
    busb_open = 0;

    ((OM_RCC_Type *) 0x40000600)->USB_CTRL = 0;


    drv_pmu_pin_mode_set(2, PMU_PIN_MODE_PD);
    drv_pmu_pin_mode_set(3, PMU_PIN_MODE_PD);
}
