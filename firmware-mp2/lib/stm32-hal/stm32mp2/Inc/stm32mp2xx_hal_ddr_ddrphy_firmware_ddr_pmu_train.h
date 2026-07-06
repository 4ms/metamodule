/*
 * Copyright (C) 2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STM32MP2xx_HAL_DDR_DDRPHY_FIRMWARE_DDR_PMU_TRAIN_H
#define STM32MP2xx_HAL_DDR_DDRPHY_FIRMWARE_DDR_PMU_TRAIN_H

#if STM32MP_DDR3_TYPE
#define DDR_PMU_TRAIN_BIN_LEN  21544
#elif STM32MP_DDR4_TYPE
#define DDR_PMU_TRAIN_BIN_LEN  29988
#elif STM32MP_LPDDR4_TYPE
#define DDR_PMU_TRAIN_BIN_LEN  34384
#endif

unsigned char ddr_pmu_train_bin[DDR_PMU_TRAIN_BIN_LEN];

#endif /* STM32MP2xx_HAL_DDR_DDRPHY_FIRMWARE_DDR_PMU_TRAIN_H */
