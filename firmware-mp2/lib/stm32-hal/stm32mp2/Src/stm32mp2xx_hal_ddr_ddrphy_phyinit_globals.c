/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/* Global struct defines */
struct runtime_config runtimeconfig;
struct user_input_basic userinputbasic;
struct user_input_advanced userinputadvanced;
struct user_input_mode_register userinputmoderegister;
struct user_input_swizzle userinputswizzle;

/* Firmware 1D Message Block structures */
struct pmu_smb_ddr_1d mb_ddr_1d[NB_PS];
/* Shadow of 1D message block. Used by PhyInit to track user changes to the data structure */
struct pmu_smb_ddr_1d shdw_ddr_1d[NB_PS];

/*
 * Represent the value stored in Step C into the register with the same name.
 * Defined as a global variable so that implementation of ddrphy_phyinit_progcsrskiptrain()
 * function does not require a PHY read register implementation.
 */
int ardptrinitval[NB_PS];
