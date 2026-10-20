/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pcd_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PCD HAL Extension module.
  *          This file includes the relevant driver file for firmware
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#if defined(USB3DRD_BASE) /* 4ms: all MP25x have the USB3DR (DWC3), not only MP257C */
#include "stm32mp2xx_hal_pcd_drd_ex.h"
#else
#include "stm32mp2xx_hal_pcd_otg_ex.h"
#endif /*STM32MP257Cxx*/

