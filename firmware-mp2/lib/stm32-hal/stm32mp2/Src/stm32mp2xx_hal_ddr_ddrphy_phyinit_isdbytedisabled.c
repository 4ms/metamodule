/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"
#include "stm32mp2xx_hal_ddr_ddrphy_wrapper.h"

/*
 * Helper function to determine if a given DByte is Disabled given PhyInit inputs.
 * @return 1 if disabled, 0 if enabled.
 */
int ddrphy_phyinit_isdbytedisabled(int dbytenumber)
{
	int disabledbyte;
	int nad0 __attribute__((unused));
	int nad1 __attribute__((unused));

	disabledbyte = 0; /* Default assume Dbyte is Enabled */

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	/* Implements Section 1.3 of Pub Databook */
	disabledbyte = (dbytenumber > userinputbasic.numactivedbytedfi0 - 1) ? 1 : 0;
#elif STM32MP_LPDDR4_TYPE
	nad0 = userinputbasic.numactivedbytedfi0;
	nad1 = userinputbasic.numactivedbytedfi1;

	if (nad0 + nad1 > userinputbasic.numdbyte) {
		ERROR("%s invalid PHY configuration:\n", __func__);
		ERROR("numactivedbytedfi0(%d)+numactivedbytedfi1(%d)>numdbytes(%d).\n",
		      nad0, nad1, userinputbasic.numdbyte);
	}

	/* Implements Section 1.3 of Pub Databook */
	if (userinputbasic.dfi1exists) {
		if (userinputbasic.numactivedbytedfi1 == 0) {
			/* Only dfi0 (ChA) is enabled, dfi1 (ChB) disabled */
			disabledbyte = (dbytenumber > userinputbasic.numactivedbytedfi0 - 1) ?
				       1 : 0;
		} else {
			/* DFI1 enabled */
			disabledbyte = ((userinputbasic.numactivedbytedfi0 - 1 < dbytenumber) &&
					(dbytenumber < (userinputbasic.numdbyte / 2))) ?
				       1 : (dbytenumber >
					    ((userinputbasic.numdbyte / 2) +
					     userinputbasic.numactivedbytedfi1 - 1)) ? 1 : 0;
		}
	} else if (userinputbasic.dfi1exists == 0x0) {
		disabledbyte = (dbytenumber > userinputbasic.numactivedbytedfi0 - 1) ? 1 : 0;
	} else {
		ERROR("%s invalid PHY configuration:dfi1exists is neither 1 or 0.\n", __func__);
	}
#endif /* STM32MP_LPDDR4_TYPE */

	/* Qualify results against MessageBlock */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	if (mb_ddr_1d[0].enableddqs < 1 ||
	    mb_ddr_1d[0].enableddqs > 8 * userinputbasic.numactivedbytedfi0) {
		ERROR("%s enableddqs(%d)\n", __func__, mb_ddr_1d[0].enableddqs);
		ERROR("Value must be 0 < enableddqs < userinputbasic.numactivedbytedfi0 * 8.\n");
	}

	if (dbytenumber < 8) {
		disabledbyte = disabledbyte | (mb_ddr_1d[0].disableddbyte & (0x1 << dbytenumber));
	}
#elif STM32MP_LPDDR4_TYPE
	if (mb_ddr_1d[0].enableddqscha < 1 ||
	    mb_ddr_1d[0].enableddqscha > 8 * userinputbasic.numactivedbytedfi0) {
		ERROR("%s enableddqscha(%d)\n", __func__, mb_ddr_1d[0].enableddqscha);
		ERROR("Value must be 0 < enableddqscha < userinputbasic.numactivedbytedfi0 * 8.\n");
	}

	if (userinputbasic.dfi1exists && userinputbasic.numactivedbytedfi1 > 0 &&
	    (mb_ddr_1d[0].enableddqschb < 1 ||
	     mb_ddr_1d[0].enableddqschb > 8 * userinputbasic.numactivedbytedfi1)) {
		ERROR("%s enableddqschb(%d)\n", __func__, mb_ddr_1d[0].enableddqschb);
		ERROR("Value must be 0 < enableddqschb < userinputbasic.numactivedbytedfi1 * 8.\n");
	}
#endif /* STM32MP_LPDDR4_TYPE */

	return disabledbyte;
}
