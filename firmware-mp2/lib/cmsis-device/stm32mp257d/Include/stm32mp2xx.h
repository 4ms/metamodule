/**
  ******************************************************************************
  * @file    stm32mp2xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32MP2xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32MP2xx device used in the target application
  *              - To use or not the peripheral drivers in application code(i.e.
  *                code will be based on direct access to peripheral registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
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
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32mp1xx
  * @{
  */

#ifndef __STM32MP2xx_H
#define __STM32MP2xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32MP2)
#define STM32MP2
#endif /* STM32MP2 */

#if defined(STM32MP257Fxx) || defined(STM32MP257Dxx) || defined(STM32MP257Cxx) || defined(STM32MP257Axx) ||\
    defined(STM32MP255Fxx) || defined(STM32MP255Dxx) || defined(STM32MP255Cxx) || defined(STM32MP255Axx) ||\
    defined(STM32MP253Fxx) || defined(STM32MP253Dxx) || defined(STM32MP253Cxx) || defined(STM32MP253Axx) ||\
    defined(STM32MP251Fxx) || defined(STM32MP251Dxx) || defined(STM32MP251Cxx) || defined(STM32MP251Axx)
#if !defined(STM32MP25xxxx)
#define STM32MP25xxxx
#endif
#elif defined(STM32MP215Fxx) || defined(STM32MP215Dxx) || defined(STM32MP215Cxx) || defined(STM32MP215Axx) ||\
      defined(STM32MP213Fxx) || defined(STM32MP213Dxx) || defined(STM32MP213Cxx) || defined(STM32MP213Axx) ||\
      defined(STM32MP211Fxx) || defined(STM32MP211Dxx) || defined(STM32MP211Cxx) || defined(STM32MP211Axx)
#if !defined(STM32MP21xxxx)
#define STM32MP21xxxx
#endif
#elif defined(STM32MP235Fxx) || defined(STM32MP235Dxx) || defined(STM32MP235Cxx) || defined(STM32MP235Axx) ||\
      defined(STM32MP233Fxx) || defined(STM32MP233Dxx) || defined(STM32MP233Cxx) || defined(STM32MP233Axx) ||\
      defined(STM32MP231Fxx) || defined(STM32MP231Dxx) || defined(STM32MP231Cxx) || defined(STM32MP231Axx)
#if !defined(STM32MP23xxxx)
#define STM32MP23xxxx
#endif
#endif

/* Uncomment the line below according to the target STM32MP2 device used in your
   application
  */

#if !defined (STM32MP257Cxx)
//   #define STM32MP257Cxx  /*!< STM32MP257Cxx Devices */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
/* #define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number
  */
#define __STM32MP2xx_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32MP2xx_CMSIS_VERSION_SUB1   (0x02U) /*!< [23:16] sub1 version */
#define __STM32MP2xx_CMSIS_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32MP2xx_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32MP2xx_CMSIS_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */
#if defined(CORE_CA35)
  #if defined(STM32MP257Axx)
    #include "stm32mp257axx_ca35.h"
  #elif defined(STM32MP257Dxx)
    #include "stm32mp257dxx_ca35.h"
  #elif defined(STM32MP257Cxx)
    #include "stm32mp257cxx_ca35.h"
  #elif defined(STM32MP257Fxx)
    #include "stm32mp257fxx_ca35.h"
  #elif defined(STM32MP255Axx)
    #include "stm32mp255axx_ca35.h"
  #elif defined(STM32MP255Dxx)
    #include "stm32mp255dxx_ca35.h"
  #elif defined(STM32MP255Cxx)
    #include "stm32mp255cxx_ca35.h"
  #elif defined(STM32MP255Fxx)
    #include "stm32mp255fxx_ca35.h"
  #elif defined(STM32MP253Axx)
    #include "stm32mp253axx_ca35.h"
  #elif defined(STM32MP253Dxx)
    #include "stm32mp253dxx_ca35.h"
  #elif defined(STM32MP253Cxx)
    #include "stm32mp253cxx_ca35.h"
  #elif defined(STM32MP253Fxx)
    #include "stm32mp253fxx_ca35.h"
  #elif defined(STM32MP251Axx)
    #include "stm32mp251axx_ca35.h"
  #elif defined(STM32MP251Dxx)
    #include "stm32mp251dxx_ca35.h"
  #elif defined(STM32MP251Cxx)
    #include "stm32mp251cxx_ca35.h"
  #elif defined(STM32MP251Fxx)
    #include "stm32mp251fxx_ca35.h"
  #elif defined(STM32MP215Cxx)
    #include "stm32mp215cxx_ca35.h"
  #elif defined(STM32MP215Fxx)
    #include "stm32mp215fxx_ca35.h"
  #elif defined(STM32MP215Axx)
    #include "stm32mp215axx_ca35.h"
  #elif defined(STM32MP215Dxx)
    #include "stm32mp215dxx_ca35.h"
   #elif defined(STM32MP213Cxx)
    #include "stm32mp213cxx_ca35.h"
  #elif defined(STM32MP213Fxx)
    #include "stm32mp213fxx_ca35.h"
  #elif defined(STM32MP213Axx)
    #include "stm32mp213axx_ca35.h"
  #elif defined(STM32MP213Dxx)
    #include "stm32mp213dxx_ca35.h"
  #elif defined(STM32MP211Cxx)
    #include "stm32mp211cxx_ca35.h"
  #elif defined(STM32MP211Fxx)
    #include "stm32mp211fxx_ca35.h"
  #elif defined(STM32MP211Axx)
    #include "stm32mp211axx_ca35.h"
  #elif defined(STM32MP211Dxx)
    #include "stm32mp211dxx_ca35.h"
  #elif defined(STM32MP235Cxx)
    #include "stm32mp235cxx_ca35.h"
  #elif defined(STM32MP235Fxx)
    #include "stm32mp235fxx_ca35.h"
  #elif defined(STM32MP235Axx)
    #include "stm32mp235axx_ca35.h"
  #elif defined(STM32MP235Dxx)
    #include "stm32mp235dxx_ca35.h"
   #elif defined(STM32MP233Cxx)
    #include "stm32mp233cxx_ca35.h"
  #elif defined(STM32MP233Fxx)
    #include "stm32mp233fxx_ca35.h"
  #elif defined(STM32MP233Axx)
    #include "stm32mp233axx_ca35.h"
  #elif defined(STM32MP233Dxx)
    #include "stm32mp233dxx_ca35.h"
  #elif defined(STM32MP231Cxx)
    #include "stm32mp231cxx_ca35.h"
  #elif defined(STM32MP231Fxx)
    #include "stm32mp231fxx_ca35.h"
  #elif defined(STM32MP231Axx)
    #include "stm32mp231axx_ca35.h"
  #elif defined(STM32MP231Dxx)
    #include "stm32mp231dxx_ca35.h"
  #else
   #error "Please select first the target STM32MP2xx device used in your application (in stm32mp2xx.h file or IDE preprocessor defines)"
  #endif
#elif defined(CORE_CM33)
  #if defined(STM32MP257Axx)
    #include "stm32mp257axx_cm33.h"
  #elif defined(STM32MP257Dxx)
    #include "stm32mp257dxx_cm33.h"
  #elif defined(STM32MP257Cxx)
    #include "stm32mp257cxx_cm33.h"
  #elif defined(STM32MP257Fxx)
    #include "stm32mp257fxx_cm33.h"
  #elif defined(STM32MP255Axx)
    #include "stm32mp255axx_cm33.h"
  #elif defined(STM32MP255Dxx)
    #include "stm32mp255dxx_cm33.h"
  #elif defined(STM32MP255Cxx)
    #include "stm32mp255cxx_cm33.h"
  #elif defined(STM32MP255Fxx)
    #include "stm32mp255fxx_cm33.h"
  #elif defined(STM32MP253Axx)
    #include "stm32mp253axx_cm33.h"
  #elif defined(STM32MP253Dxx)
    #include "stm32mp253dxx_cm33.h"
  #elif defined(STM32MP253Cxx)
    #include "stm32mp253cxx_cm33.h"
  #elif defined(STM32MP253Fxx)
    #include "stm32mp253fxx_cm33.h"
  #elif defined(STM32MP251Axx)
    #include "stm32mp251axx_cm33.h"
  #elif defined(STM32MP251Dxx)
    #include "stm32mp251dxx_cm33.h"
  #elif defined(STM32MP251Cxx)
    #include "stm32mp251cxx_cm33.h"
  #elif defined(STM32MP251Fxx)
    #include "stm32mp251fxx_cm33.h"
  #elif defined(STM32MP215Axx)
    #include "stm32mp215axx_cm33.h"
  #elif defined(STM32MP215Cxx)
    #include "stm32mp215cxx_cm33.h"
  #elif defined(STM32MP215Fxx)
    #include "stm32mp215fxx_cm33.h"
  #elif defined(STM32MP215Dxx)
    #include "stm32mp215dxx_cm33.h"
  #elif defined(STM32MP213Cxx)
    #include "stm32mp213cxx_cm33.h"
  #elif defined(STM32MP213Fxx)
    #include "stm32mp213fxx_cm33.h"
  #elif defined(STM32MP213Axx)
    #include "stm32mp213axx_cm33.h"
  #elif defined(STM32MP213Dxx)
    #include "stm32mp213dxx_cm33.h"
  #elif defined(STM32MP211Cxx)
    #include "stm32mp211cxx_cm33.h"
  #elif defined(STM32MP211Fxx)
    #include "stm32mp211fxx_cm33.h"
  #elif defined(STM32MP211Axx)
    #include "stm32mp211axx_cm33.h"
  #elif defined(STM32MP211Dxx)
    #include "stm32mp211dxx_cm33.h"
  #elif defined(STM32MP235Axx)
    #include "stm32mp235axx_cm33.h"
  #elif defined(STM32MP235Cxx)
    #include "stm32mp235cxx_cm33.h"
  #elif defined(STM32MP235Fxx)
    #include "stm32mp235fxx_cm33.h"
  #elif defined(STM32MP235Dxx)
    #include "stm32mp235dxx_cm33.h"
  #elif defined(STM32MP233Cxx)
    #include "stm32mp233cxx_cm33.h"
  #elif defined(STM32MP233Fxx)
    #include "stm32mp233fxx_cm33.h"
  #elif defined(STM32MP233Axx)
    #include "stm32mp233axx_cm33.h"
  #elif defined(STM32MP233Dxx)
    #include "stm32mp233dxx_cm33.h"
  #elif defined(STM32MP231Cxx)
    #include "stm32mp231cxx_cm33.h"
  #elif defined(STM32MP231Fxx)
    #include "stm32mp231fxx_cm33.h"
  #elif defined(STM32MP231Axx)
    #include "stm32mp231axx_cm33.h"
  #elif defined(STM32MP231Dxx)
    #include "stm32mp231dxx_cm33.h"
  #else
    #error "Please select first the target STM32MP2xx device used in your application (in stm32mp2xx.h file or IDE preprocessor defines)"
  #endif
#elif defined(CORE_CM0PLUS)
  #if defined(STM32MP257Axx)
    #include "stm32mp257axx_cm0.h"
  #elif defined(STM32MP257Dxx)
    #include "stm32mp257dxx_cm0.h"
  #elif defined(STM32MP257Cxx)
    #include "stm32mp257cxx_cm0.h"
  #elif defined(STM32MP257Fxx)
    #include "stm32mp257fxx_cm0.h"
  #elif defined(STM32MP255Axx)
    #include "stm32mp255axx_cm0.h"
  #elif defined(STM32MP255Dxx)
    #include "stm32mp255dxx_cm0.h"
  #elif defined(STM32MP255Cxx)
    #include "stm32mp255cxx_cm0.h"
  #elif defined(STM32MP255Fxx)
    #include "stm32mp255fxx_cm0.h"
  #elif defined(STM32MP253Axx)
    #include "stm32mp253axx_cm0.h"
  #elif defined(STM32MP253Dxx)
    #include "stm32mp253dxx_cm0.h"
  #elif defined(STM32MP253Cxx)
    #include "stm32mp253cxx_cm0.h"
  #elif defined(STM32MP253Fxx)
    #include "stm32mp253fxx_cm0.h"
  #elif defined(STM32MP251Axx)
    #include "stm32mp251axx_cm0.h"
  #elif defined(STM32MP251Dxx)
    #include "stm32mp251dxx_cm0.h"
  #elif defined(STM32MP251Cxx)
    #include "stm32mp251cxx_cm0.h"
  #elif defined(STM32MP251Fxx)
    #include "stm32mp251fxx_cm0.h"
  #else
    #error "Please select first the target STM32MP2xx device used in your application (in stm32mp2xx.h file or IDE preprocessor defines)"
  #endif
#else
 #error "Please select first the target core (CORE_CA35, CORE_CM33 CORE_CM0PLUS) used in your application (in preprocessor defines)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */

/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#if defined(CORE_CA35)
inline uint64_t POSITION_VAL(uint64_t x) {
    if (x <= (1ULL<<0)) return 0;
    if (x <= (1ULL<<1)) return 1;
    if (x <= (1ULL<<2)) return 2;
    if (x <= (1ULL<<3)) return 3;
    if (x <= (1ULL<<4)) return 4;
    if (x <= (1ULL<<5)) return 5;
    if (x <= (1ULL<<6)) return 6;
    if (x <= (1ULL<<7)) return 7;
    if (x <= (1ULL<<8)) return 8;
    if (x <= (1ULL<<9)) return 9;
    if (x <= (1ULL<<10)) return 10;
    if (x <= (1ULL<<11)) return 11;
    if (x <= (1ULL<<12)) return 12;
    if (x <= (1ULL<<13)) return 13;
    if (x <= (1ULL<<14)) return 14;
    if (x <= (1ULL<<15)) return 15;
    if (x <= (1ULL<<16)) return 16;
    if (x <= (1ULL<<17)) return 17;
    if (x <= (1ULL<<18)) return 18;
    if (x <= (1ULL<<19)) return 19;
    if (x <= (1ULL<<20)) return 20;
    if (x <= (1ULL<<21)) return 21;
    if (x <= (1ULL<<22)) return 22;
    if (x <= (1ULL<<23)) return 23;
    if (x <= (1ULL<<24)) return 24;
    if (x <= (1ULL<<25)) return 25;
    if (x <= (1ULL<<26)) return 26;
    if (x <= (1ULL<<27)) return 27;
    if (x <= (1ULL<<28)) return 28;
    if (x <= (1ULL<<29)) return 29;
    if (x <= (1ULL<<30)) return 30;
    if (x <= (1ULL<<31)) return 31;
    if (x <= (1ULL<<32)) return 32;
    if (x <= (1ULL<<33)) return 33;
    if (x <= (1ULL<<34)) return 34;
    if (x <= (1ULL<<35)) return 35;
    if (x <= (1ULL<<36)) return 36;
    if (x <= (1ULL<<37)) return 37;
    if (x <= (1ULL<<38)) return 38;
    if (x <= (1ULL<<39)) return 39;
    if (x <= (1ULL<<40)) return 40;
    if (x <= (1ULL<<41)) return 41;
    if (x <= (1ULL<<42)) return 42;
    if (x <= (1ULL<<43)) return 43;
    if (x <= (1ULL<<44)) return 44;
    if (x <= (1ULL<<45)) return 45;
    if (x <= (1ULL<<46)) return 46;
    if (x <= (1ULL<<47)) return 47;
    if (x <= (1ULL<<48)) return 48;
    if (x <= (1ULL<<49)) return 49;
    if (x <= (1ULL<<50)) return 50;
    if (x <= (1ULL<<51)) return 51;
    if (x <= (1ULL<<52)) return 52;
    if (x <= (1ULL<<53)) return 53;
    if (x <= (1ULL<<54)) return 54;
    if (x <= (1ULL<<55)) return 55;
    if (x <= (1ULL<<56)) return 56;
    if (x <= (1ULL<<57)) return 57;
    if (x <= (1ULL<<58)) return 58;
    if (x <= (1ULL<<59)) return 59;
    if (x <= (1ULL<<60)) return 60;
    if (x <= (1ULL<<61)) return 61;
    if (x <= (1ULL<<62)) return 62;
    if (x <= (1ULL<<63)) return 63;
    return 0;
}
#else
#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))
#endif

/* Use of interrupt control for register exclusive access */
/* Atomic 32-bit register access macro to set one or several bits */
#define ATOMIC_SET_BIT(REG, BIT)                             \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    SET_BIT((REG), (BIT));                                   \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define ATOMIC_CLEAR_BIT(REG, BIT)                           \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    CLEAR_BIT((REG), (BIT));                                 \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK)            \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    MODIFY_REG((REG), (CLEARMSK), (SETMASK));                \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define ATOMIC_SETH_BIT(REG, BIT) ATOMIC_SET_BIT(REG, BIT)                                   \

/* Atomic 16-bit register access macro to clear one or several bits */
#define ATOMIC_CLEARH_BIT(REG, BIT) ATOMIC_CLEAR_BIT(REG, BIT)                               \

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFYH_REG(REG, CLEARMSK, SETMASK) ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK) \

/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32mp2xx_hal_conf.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32MP2xx_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
