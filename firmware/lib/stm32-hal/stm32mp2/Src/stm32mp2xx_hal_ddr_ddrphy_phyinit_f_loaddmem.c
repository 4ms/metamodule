/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"
#ifdef __AARCH64__
#include "stm32mp2xx_hal_ddr_ddrphy_firmware_ddr_pmu_train.h"
#endif

/*
 * This function loads the training firmware DMEM image and write the
 * Message Block parameters for the training firmware into the SRAM.
 *
 * This function performs the following tasks:
 *
 * -# Load the firmware DMEM segment to initialize the data structures from the
 * DMEM incv file provided in the training firmware package.
 * -# Write the Firmware Message Block with the required contents detailing the training parameters.
 *
 * \return 0 on success.
 */
int ddrphy_phyinit_f_loaddmem(int pstate)
{
	struct pmu_smb_ddr_1d *msgblkptr;
	int sizeofmsgblk;
	uint16_t *ptr16;
	uint32_t *ptr32;

	VERBOSE("%s Start (pstate=%d)\n", __func__, pstate);

	/* Set a pointer to the message block */
	msgblkptr = &mb_ddr_1d[pstate];

	/* Some basic checks on MessageBlock */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	if ((msgblkptr->enableddqs > 8 * (userinputbasic.numactivedbytedfi0)) ||
	    (msgblkptr->enableddqs <= 0)) {
		ERROR("%s enableddqs is Zero or greater than NumActiveDbytes for Dfi0\n",__func__);
		return -1;
	}
#elif STM32MP_LPDDR4_TYPE
	if (msgblkptr->enableddqscha % 16 != 0 || msgblkptr->enableddqschb % 16 != 0) {
		ERROR("%s Lp3/Lp4 - Number of Dq's Enabled per Channel much be multipe of 16\n",
		      __func__);
		return -1;
	}

	if ((msgblkptr->enableddqscha > 8 * (userinputbasic.numactivedbytedfi0)) ||
	    (msgblkptr->enableddqschb > 8 * (userinputbasic.numactivedbytedfi1)) ||
	    (msgblkptr->enableddqscha == 0 && msgblkptr->enableddqschb == 0)) {
		ERROR("%s EnabledDqsChA/B are not set correctly./1\n", __func__);
		return -1;
	}
#endif /* STM32MP_LPDDR4_TYPE */

	sizeofmsgblk = sizeof(mb_ddr_1d[pstate]);

	ptr16 = (uint16_t *)msgblkptr;
	ddrphy_phyinit_writeoutmsgblk(ptr16, DMEM_ST_ADDR, sizeofmsgblk);

#ifdef __AARCH64__
	ptr32 = (uint32_t *)(ddr_pmu_train_bin + STM32MP_DDR_FW_DMEM_OFFSET);
#else
	ptr32 = (uint32_t *)(STM32MP_DDR_FW_BASE + STM32MP_DDR_FW_DMEM_OFFSET);
#endif
	ddrphy_phyinit_writeoutmem(ptr32, DMEM_ST_ADDR + DMEM_BIN_OFFSET,
				   DMEM_SIZE - STM32MP_DDR_FW_DMEM_OFFSET);

	VERBOSE("%s End\n", __func__);

	return 0;
}
