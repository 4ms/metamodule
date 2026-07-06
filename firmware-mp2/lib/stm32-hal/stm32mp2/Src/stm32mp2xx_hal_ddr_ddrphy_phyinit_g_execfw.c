/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Execute the Training Firmware
 *
 * The training firmware is executed with the following procedure:
 *
 * -# Reset the firmware microcontroller by writing the MicroReset register to
 * set the StallToMicro and ResetToMicro fields to 1 (all other fields should be
 * zero). Then rewrite the registers so that only the StallToMicro remains set
 * (all other fields should be zero).
 * -# Begin execution of the training firmware by setting the MicroReset
 * register to 4'b0000.
 * -# Wait for the training firmware to complete by following the procedure in
 * "uCtrl Initialization and Mailbox Messaging" implemented in
 * ddrphy_phyinit_usercustom_g_waitfwdone() function.
 * -# Halt the microcontroller.
 *
 * \return 0 on success.
 */
int ddrphy_phyinit_g_execfw(void)
{
	int ret;

	VERBOSE("%s Start\n", __func__);

	/*
	 * 1. Reset the firmware microcontroller by writing the MicroReset CSR to set the
	 * StallToMicro and ResetToMicro fields to 1 (all other fields should be zero).
	 * Then rewrite the CSR so that only the StallToMicro remains set (all other fields should
	 * be zero).
	 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICROCONTMUXSEL_ADDR)),
		      CSR_STALLTOMICRO_MASK);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICRORESET_ADDR)),
		      CSR_RESETTOMICRO_MASK | CSR_STALLTOMICRO_MASK);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICRORESET_ADDR)),
		      CSR_STALLTOMICRO_MASK);

	/* 2. Begin execution of the training firmware by setting the MicroReset CSR to 0 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICRORESET_ADDR)), 0x0U);

	/*
	 * 3. Wait for the training firmware to complete by following the procedure in
	 * "uCtrl Initialization and Mailbox Messaging".
	 */
	ret = ddrphy_phyinit_usercustom_g_waitfwdone();
	if (ret != 0) {
		return ret;
	}

	/* 4. Halt the microcontroller */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICRORESET_ADDR)),
		      CSR_STALLTOMICRO_MASK);

	VERBOSE("%s End\n", __func__);

	return 0;
}
