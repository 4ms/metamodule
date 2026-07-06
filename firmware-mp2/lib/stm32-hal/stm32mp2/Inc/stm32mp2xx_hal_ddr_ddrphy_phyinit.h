/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DDRPHY_PHYINIT_H
#define DDRPHY_PHYINIT_H

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit_usercustom.h"

#define DDRPHY_PHYINIT_RID 20220100

/* Global Structures : instantiated in ddrphy_globals.c */
extern struct runtime_config runtimeconfig;

extern struct user_input_basic userinputbasic;
extern struct user_input_advanced userinputadvanced;
extern struct user_input_mode_register userinputmoderegister;
extern struct user_input_swizzle userinputswizzle;

extern struct pmu_smb_ddr_1d mb_ddr_1d[NB_PS];
extern struct pmu_smb_ddr_1d shdw_ddr_1d[NB_PS];

/* Function definitions */
int ddrphy_phyinit_softsetmb(int ps, char *field, int value);
void ddrphy_phyinit_initstruct(void);
void *ddrphy_phyinit_get_user_input_basic_base(void);
int ddrphy_phyinit_get_user_input_basic_pllbypass_0(void);
void *ddrphy_phyinit_get_user_input_advanced_base(void);
void *ddrphy_phyinit_get_user_input_mode_register_base(void);
void *ddrphy_phyinit_get_user_input_swizzle_base(void);

#endif /* DDRPHY_PHYINIT_H */
