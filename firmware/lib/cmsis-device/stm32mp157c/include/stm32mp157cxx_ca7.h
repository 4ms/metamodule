/**
 ******************************************************************************
 * @file    stm32mp157cxx_ca7.h
 * @author  MCD Application Team
 * @brief   CMSIS stm32mp157cxx_ca7 Device Peripheral Access Layer Header File.
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

/** @addtogroup stm32mp157cxx_ca7
 * @{
 */

#ifndef __STM32MP157Cxx_CA7_H
	#define __STM32MP157Cxx_CA7_H

	#ifdef __cplusplus
extern "C" {
	#endif /* __cplusplus */

	/**
	 * @brief Bit position definition inside a 32 bits registers
	 */
	#define B(x) ((uint32_t)1 << x)
/**
 * @}
 */

	#include "stm32mp157cxx_ca7_irqn.h"

/** @addtogroup Configuration_section_for_CMSIS
 * @{
 */

	#define SDC /*!< Step Down Converter feature */

	/**
	 * @brief Configuration of the Cortex-M4/ Cortex-M7 Processor and Core Peripherals
	 */

	/* ===========================================================================================================================
	 */
	/* ================                           Processor and Core Peripheral Section ================ */
	/* ===========================================================================================================================
	 */

	/* ===========================  Configuration of the ARM Cortex-A Processor and Core Peripherals
	 * ============================ */
	#define __CORTEX_A 7U	 /*!< Cortex-A# Core                              */
	#define __CA_REV 0x0005U /*!< Core revision r0p0                          */
	#define __FPU_PRESENT 1U /*!< Set to 1 if FPU is present                  */
	#define __GIC_PRESENT 1U /*!< Set to 1 if GIC is present                  */
	#define __TIM_PRESENT 1U /*!< Set to 1 if TIM is present                  */
	#define __L2C_PRESENT 0U /*!< Set to 1 if L2C is present                  */

	#define GIC_BASE 0xA0021000
	#define GIC_DISTRIBUTOR_BASE GIC_BASE
	#define GIC_INTERFACE_BASE (GIC_BASE + 0x1000)

	#include "core_ca.h"
	#include "system_stm32mp1xx_A7.h"

	#include <stdint.h>

	#include "stm32mp157cxx_ca7_macros.h"
	#include "stm32mp157cxx_ca7_periphaddrs.h"
	#include "stm32mp157cxx_ca7_structs.h"

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
	#define PKG_ID_Pos (27U)
	#define PKG_ID_Msk (0x7U << PKG_ID_Pos) /*!< 0x38000000 */
	#define PKG_ID PKG_ID_Msk				/*!< Package Type */

	#define RPN_ID_Pos (0U)
	#define RPN_ID_Msk (0xFFU << RPN_ID_Pos) /*!< 0x000000FF */
	#define RPN_ID RPN_ID_Msk				 /*!< Device Part Number */

	#define DV_DEV_ID_Pos (0U)
	#define DV_DEV_ID_Msk (0xFFFU << DV_DEV_ID_Pos) /*!< 0x00000FFF */
	#define DV_DEV_ID DV_DEV_ID_Msk					/*!< Device ID */
	#define DV_REV_ID_Pos (16U)
	#define DV_REV_ID_Msk (0xFFFFU << DV_REV_ID_Pos) /*!< 0xFFFF0000 */
	#define DV_REV_ID DV_REV_ID_Msk					 /*!< Device Rev ID */

	#include "stm32mp157cxx_ca7_regs01.h"
	#include "stm32mp157cxx_ca7_regs02.h"
	#include "stm32mp157cxx_ca7_regs03.h"
	#include "stm32mp157cxx_ca7_regs04.h"
	#include "stm32mp157cxx_ca7_regs05.h"
	#include "stm32mp157cxx_ca7_regs06.h"
	#include "stm32mp157cxx_ca7_regs07.h"
	#include "stm32mp157cxx_ca7_regs08.h"

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

	#ifdef __cplusplus
}
	#endif /* __cplusplus */

#endif /* __STM32MP157Cxx_CA7_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
