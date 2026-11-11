/**     __  ___     _
 *   ___\ \/ / |__ | | ___
 *  / _ \\  /| '_ \| |/ _ \
 * |  __//  \| |_) | |  __/
 *  \___/_/\_\_.__/|_|\___|
 *
 * @file exe_hal_tc.h
 * @brief EXE HAL toolchain header.
 * @author onmicro
 * @date 2020/02
 */

#ifndef __EXE_HAL_TC_H__
#define __EXE_HAL_TC_H__

#if defined(__CORTEX_M) || defined(__ANDES_N) || defined(__MSP_N)

/* CMSIS headers are included already. */

#else

#if   defined ( __CC_ARM )
/*!< keywords for ARM Compiler */
#if !defined(__ASM)
#define __ASM                                  __asm
#endif
#if !defined(__INLINE)
#define __INLINE                               __inline
#define __STATIC_INLINE                        static __inline
#define __STATIC_FORCEINLINE                   static __forceinline
#endif
#define __NO_RETURN                            __declspec(noreturn)
#define __USED                                 __attribute__((used))
#define __WEAK                                 __attribute__((weak))
#define __PACKED                               __attribute__((packed))
#define __PACKED_STRUCT                        __packed struct
#define __PACKED_UNION                         __packed union
#define __ALIGNED(x)                           __attribute__((aligned(x)))

#elif defined ( __ICCARM__ )
/*!< keywords for IAR Compiler */
#define __ASM __asm
#define __INLINE inline
#define __STATIC_INLINE       static inline
#define __FORCEINLINE         _Pragma("inline=forced")
#define __STATIC_FORCEINLINE  __FORCEINLINE __STATIC_INLINE

#if __ICCARM_V8
#define __NO_RETURN __attribute__((__noreturn__))
#else
#define __NO_RETURN _Pragma("object_attribute=__noreturn")
#endif

#if __ICCARM_V8
#define __USED __attribute__((used))
#else
#define __USED _Pragma("__root")
#endif

#if __ICCARM_V8
#define __WEAK __attribute__((weak))
#else
#define __WEAK _Pragma("__weak")
#endif

#if __ICCARM_V8
#define __PACKED __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED __packed
#endif

#if __ICCARM_V8
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED_STRUCT __packed struct
#endif

#if __ICCARM_V8
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED_UNION __packed union
#endif

#if __ICCARM_V8
#define __ALIGNED(x) __attribute__((aligned(x)))
#elif (__VER__ >= 7080000)
/* Needs IAR language extensions */
#define __ALIGNED(x) __attribute__((aligned(x)))
#else
#warning No compiler specific solution for __ALIGNED.__ALIGNED is ignored.
#define __ALIGNED(n)     _Pragma(IAR_STR(data_alignment= ## n ##))
#endif

#elif defined ( __TMS470__ )
#define __ASM            __asm__                                      /*!< asm keyword for TI CCS Compiler       */
#define __STATIC_INLINE  static inline

#elif defined ( __GNUC__ ) || defined ( __ICCRISCV__ )
/*!< keywords for GNU Compiler */
#define __ASM                                  __asm
#define __INLINE                               inline
#define __STATIC_INLINE                        static inline
#define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#define __NO_RETURN                            __attribute__((__noreturn__))
#define __USED                                 __attribute__((used))
#define __WEAK                                 __attribute__((weak))
#define __PACKED                               __attribute__((packed, aligned(1)))
#define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#define __ALIGNED(x)                           __attribute__((aligned(x)))

#elif defined ( __TASKING__ )
#define __ASM            __asm__                                      /*!< asm keyword for TASKING Compiler      */
#define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */
#define __STATIC_INLINE  static inline
#define __ALIGNED(n)

#elif defined ( __C51__ )
#define __ASM
#define __INLINE
#define __STATIC_INLINE static
#define __STATIC_FORCEINLINE static
#define __NO_RETURN
#define __USED
#define __WEAK
#define __PACKED
#define __PACKED_STRUCT struct
#define __PACKED_UNION union
#define __ALIGNED(x)

#elif defined ( __LCC__ )
#define __ASM
#define __INLINE
#define __STATIC_INLINE static
#define __STATIC_FORCEINLINE static
#define __NO_RETURN
#define __USED
#define __WEAK
#define __PACKED
#define __PACKED_STRUCT struct
#define __PACKED_UNION union
#define __ALIGNED(x)

#endif /* different toolchain */

#endif /* if defined(__ASM) */

#endif /* #ifndef __EXE_HAL_TC_H__ */
