/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Read the Training Firmware Message Block results
 *
 * The procedure is as follows:
 *
 * -# Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
 * -# Read the Firmware Message Block to obtain the results from the training.
 * The user customizable function ddrphy_phyinit_usercustom_h_readmsgblock()
 * is called for the user to read any specific results from training.
 * -# Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1.
 * -# If training is required at another frequency, repeat the operations starting at step (E)
 *
 * \return void
 */
void ddrphy_phyinit_h_readmsgblock(void)
{
	VERBOSE("%s Start\n", __func__);

	/* 1. Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICROCONTMUXSEL_ADDR)), 0x0U);

	/* 2. Read the Firmware Message Block to obtain the results from the training */
	ddrphy_phyinit_usercustom_h_readmsgblock();

	/*
	 * 3. Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1
	 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICROCONTMUXSEL_ADDR)), 0x1U);

	/*
	 * 4. If training is required at another frequency, repeat the operations starting at step
	 * (E).
	 */

	VERBOSE("%s End\n", __func__);
}
