/**
 ******************************************************************************
 * @file    stm32mp2xx_hal_wrapper_for_a35.h
 * @author  MCD Application Team
 * @version $VERSION$
 * @date    $DATE$
 * @brief   Wrapper of some specific HAL driver functions for Cortex-A35
 *          This file is included by stm32mp2xx_hal_conf.h
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_WRAPPER_FOR_A35_H
#define STM32MP2xx_HAL_WRAPPER_FOR_A35_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CORE_CA35)
/* Includes ------------------------------------------------------------------*/
/* From CMSIS "Core_A" */
#include "irq_ctrl.h"
#include "stm32mp2xx.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/* A35 Wrapper of HAL cortex functions for M33 (ARMv8-M) (see hal_cortex.h) */

inline void HAL_NVIC_SetPriority(IRQn_Type IRQn, unsigned pri, unsigned subpri)
{
	IRQ_SetPriority(IRQn, pri);
}

inline void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
	IRQ_Enable(IRQn);
}

inline void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
	IRQ_Disable(IRQn);
}

inline void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
	IRQ_ClearPending(IRQn);
}

inline void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
	IRQ_SetPending(IRQn);
}

inline uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
	return IRQ_GetPending(IRQn);
}

inline void HAL_NVIC_ConfigInterruptSecurity(IRQn_Type IRQn, uint32_t IRQSecurityState)
{
	((IRQSecurityState == 0x0) ? IRQ_SetMode(IRQn, IRQ_MODE_DOMAIN_SECURE) :
								 IRQ_SetMode(IRQn, IRQ_MODE_DOMAIN_NONSECURE));
}

/* Existing not (already) wrapped functions (needed ?) : */
// void HAL_NVIC_SystemReset(void);
// void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t *pPreemptPriority, uint32_t *pSubPriority);
// void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGrouping);
// uint32_t HAL_NVIC_GetPriorityGrouping(void);
// uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
// uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
// void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);

#endif /*CORE_CA35*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_WRAPPER_FOR_A35_H */
