/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Store the message block into the bottom of the local DMEM array
 *
 * \return void
 */
void ddrphy_phyinit_storemsgblk(void *msgblkptr, int sizeofmsgblk, int mem[])
{
	/* Local variables */
	int loop;
	uint16_t *dataarray;

	/* Recast the structure pointer as a pointer to an array of 16-bit values */
	dataarray = (uint16_t *)msgblkptr;

	/* Loop over the structure 16 bits at a time and load dmem */
	for (loop = 0; loop < (int)(sizeofmsgblk / sizeof(uint16_t)); loop++) {
		/* The data is the data in the structure at the loop offset */
		mem[loop] = dataarray[loop];
	}

}
