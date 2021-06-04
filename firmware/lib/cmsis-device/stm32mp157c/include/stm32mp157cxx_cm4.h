/**
  ******************************************************************************
  * @file    stm32mp157cxx_cm4.h
  * @author  MCD Application Team
  * @brief   CMSIS stm32mp157cxx_cm4 Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripherals registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS_Device
  * @{
  */

/** @addtogroup stm32mp157cxx_cm4
  * @{
  */

#ifndef __STM32MP157Cxx_CM4_H
#define __STM32MP157Cxx_CM4_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**
  * @brief Bit position definition inside a 32 bits registers
  */
#define  B(x) \
        ((uint32_t) 1 << x)
/**
  * @}
  */

#include "stm32mp157cxx_cm4_irqn.h"


/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

#define SDC        /*!< Step Down Converter feature */

/**
  * @brief Configuration of the Cortex-M4/ Cortex-M7 Processor and Core Peripherals
   */
#define __CM4_REV                 0x0001  /*!< Cortex-M4 revision r0p1                       */
#define __MPU_PRESENT             1       /*!< CM4 provides an MPU                           */
#define __NVIC_PRIO_BITS          4       /*!< CM4 uses 4 Bits for the Priority Levels       */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT             1       /*!< FPU present                                   */

#include "core_cm4.h"                     /*!< Cortex-M4 processor and core peripherals      */
#include "system_stm32mp1xx.h"


#include <stdint.h>

#include "stm32mp157cxx_cm4_structs.h"
#include "stm32mp157cxx_cm4_periphaddrs.h"        

/** @addtogroup Exported_constants
  * @{
  */

  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                        Device Electronic Signature                         */
/*                                                                            */
/******************************************************************************/
#define PKG_ID_Pos              (27U)
#define PKG_ID_Msk              (0x7U << PKG_ID_Pos)        /*!< 0x38000000 */
#define PKG_ID                  PKG_ID_Msk                  /*!< Package Type */

#define RPN_ID_Pos              (0U)
#define RPN_ID_Msk              (0xFFU << RPN_ID_Pos)       /*!< 0x000000FF */
#define RPN_ID                  RPN_ID_Msk                  /*!< Device Part Number */

#define DV_DEV_ID_Pos           (0U)
#define DV_DEV_ID_Msk           (0xFFFU << DV_DEV_ID_Pos)   /*!< 0x00000FFF */
#define DV_DEV_ID               DV_DEV_ID_Msk               /*!< Device ID */
#define DV_REV_ID_Pos           (16U)
#define DV_REV_ID_Msk           (0xFFFFU << DV_REV_ID_Pos)  /*!< 0xFFFF0000 */
#define DV_REV_ID               DV_REV_ID_Msk               /*!< Device Rev ID */

#include "stm32mp157cxx_cm4_regs01.h"
#include "stm32mp157cxx_cm4_regs02.h"
#include "stm32mp157cxx_cm4_regs03.h"
#include "stm32mp157cxx_cm4_regs04.h"
#include "stm32mp157cxx_cm4_regs05.h"
#include "stm32mp157cxx_cm4_regs06.h"
#include "stm32mp157cxx_cm4_regs07.h"
#include "stm32mp157cxx_cm4_regs08.h"

#include "stm32mp157cxx_cm4_macros.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32MP157Cxx_CM4_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
