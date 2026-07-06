/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Reads training results
 *
 * Read the Firmware Message Block via APB read commands to the DMEM address to
 * obtain training results.
 *
 * The default behavior of this function is to print comments relating to this
 * process. An example pseudo code for implementing this function is as follows:
 *
 * @code{.c}
 * {
 *   _read_1d_message_block_outputs_
 * }
 * @endcode
 *
 * A function call of the same name will be printed in the output text file.
 * User can choose to leave this function as is, or implement mechanism to
 * trigger message block read events in simulation.
 *
 * \return void
 */
void ddrphy_phyinit_usercustom_h_readmsgblock(void)
{
	VERBOSE(" 2. Read the Firmware Message Block to obtain the results from the training.\n");
	VERBOSE(" This can be accomplished by issuing APB read commands to the DMEM addresses.\n");
	VERBOSE(" Example:\n");
	VERBOSE("   _read_1d_message_block_outputs_\n");

	VERBOSE("%s Start\n", __func__);

	VERBOSE("%s End\n", __func__);
}
