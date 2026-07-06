/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Set messageBlock variable only if not set by user
 *
 * This function is used by ddrphy_phyinit_calcmb() to set calculated
 * messageBlock variables only when the user has not directly programmed them.
 *
 * @param[in]   ps      integer between 0-3. Specifies the PState for which the messageBlock field should be set.
 * @param[in]   field   A string representing the messageBlock field to be programed.
 * @param[in]   value   filed value
 *
 * @return 0 on success.
 * On error  returns the following values based on error:
 * - -1 : message block field specified by the input \c field string is not
 * found in the message block data structure.
 * - -2 : when dramtype does not support 2D training but a 2D training field is
 * programmed.
 */
int ddrphy_phyinit_softsetmb(int ps, char *field, int value)
{
		if (strcmp(field, "pstate") == 0) {
			if (shdw_ddr_1d[ps].pstate == 0) {
				mb_ddr_1d[ps].pstate = value;
			}
		} else if (strcmp(field, "pllbypassen") == 0) {
			if (shdw_ddr_1d[ps].pllbypassen == 0) {
				mb_ddr_1d[ps].pllbypassen = value;
			}
		} else if (strcmp(field, "dramfreq") == 0) {
			if (shdw_ddr_1d[ps].dramfreq == 0) {
				mb_ddr_1d[ps].dramfreq = value;
			}
		} else if (strcmp(field, "dfifreqratio") == 0) {
			if (shdw_ddr_1d[ps].dfifreqratio == 0) {
				mb_ddr_1d[ps].dfifreqratio = value;
			}
		} else if (strcmp(field, "bpznresval") == 0) {
			if (shdw_ddr_1d[ps].bpznresval == 0) {
				mb_ddr_1d[ps].bpznresval = value;
			}
		} else if (strcmp(field, "phyodtimpedance") == 0) {
			if (shdw_ddr_1d[ps].phyodtimpedance == 0) {
				mb_ddr_1d[ps].phyodtimpedance = value;
			}
		} else if (strcmp(field, "phydrvimpedance") == 0) {
			if (shdw_ddr_1d[ps].phydrvimpedance == 0) {
				mb_ddr_1d[ps].phydrvimpedance = value;
			}
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		} else if (strcmp(field, "dramtype") == 0) {
			if (shdw_ddr_1d[ps].dramtype == 0) {
				mb_ddr_1d[ps].dramtype = value;
			}
		} else if (strcmp(field, "disableddbyte") == 0) {
			if (shdw_ddr_1d[ps].disableddbyte == 0) {
				mb_ddr_1d[ps].disableddbyte = value;
			}
		} else if (strcmp(field, "enableddqs") == 0) {
			if (shdw_ddr_1d[ps].enableddqs == 0) {
				mb_ddr_1d[ps].enableddqs = value;
			}
		} else if (strcmp(field, "phycfg") == 0) {
			if (shdw_ddr_1d[ps].phycfg == 0) {
				mb_ddr_1d[ps].phycfg = value;
			}
#endif /* STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE */
#if STM32MP_DDR4_TYPE
		} else if (strcmp(field, "x16present") == 0) {
			if (shdw_ddr_1d[ps].x16present == 0) {
				mb_ddr_1d[ps].x16present = value;
			}
#endif /* STM32MP_DDR4_TYPE */
#if STM32MP_LPDDR4_TYPE
		} else if (strcmp(field, "enableddqscha") == 0) {
			if (shdw_ddr_1d[ps].enableddqscha == 0) {
				mb_ddr_1d[ps].enableddqscha = value;
			}
		} else if (strcmp(field, "cspresentcha") == 0) {
			if (shdw_ddr_1d[ps].cspresentcha == 0) {
				mb_ddr_1d[ps].cspresentcha = value;
			}
		} else if (strcmp(field, "enableddqschb") == 0) {
			if (shdw_ddr_1d[ps].enableddqschb == 0) {
				mb_ddr_1d[ps].enableddqschb = value;
			}
		} else if (strcmp(field, "cspresentchb") == 0) {
			if (shdw_ddr_1d[ps].cspresentchb == 0) {
				mb_ddr_1d[ps].cspresentchb = value;
			}
#endif /* STM32MP_LPDDR4_TYPE */
		} else {
			ERROR("%s unknown message block field name '%s'\n", __func__, field);
			return -1;
		}

	return 0;
}
