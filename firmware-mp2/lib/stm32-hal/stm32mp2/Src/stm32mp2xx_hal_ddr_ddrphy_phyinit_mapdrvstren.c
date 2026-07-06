/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <string.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * Maps impedance values to register settings
 *
 * Reads the pull-up/pull-down driver impedance from drvstren_ohm input
 * and encodes that value for the CSR field specified in targetcsr input,
 * based on DDR protocol.
 *
 * @param[in] drvstren_ohm drive strenght / ODT impedance in Ohms
 *
 * @param[in] targetcsr Target CSR for the impedance value. on of following
 * enum drvtype:
 *   - DRVSTRENFSDQP
 *   - DRVSTRENFSDQN
 *   - ODTSTRENP
 *   - ODTSTRENN
 *   - ADRVSTRENP
 *   - ADRVSTRENN
 *
 * \return >=0 value on success, else negative.
 */
int ddrphy_phyinit_mapdrvstren(int drvstren_ohm, enum drvtype targetcsr)
{
	int stren_setting = -1;

	if ((targetcsr == DRVSTRENFSDQP) || (targetcsr == DRVSTRENFSDQN)) {
		if (drvstren_ohm == 0) {
			stren_setting = 0x00; /* High-impedance */
		} else if (drvstren_ohm < 29) {
			stren_setting = 0x3f;
		} else if (drvstren_ohm < 31) {
			stren_setting = 0x3e;
		} else if (drvstren_ohm < 33) {
			stren_setting = 0x3b;
		} else if (drvstren_ohm < 35) {
			stren_setting = 0x3a;
		} else if (drvstren_ohm < 38) {
			stren_setting = 0x39;
		} else if (drvstren_ohm < 41) {
			stren_setting = 0x38;
		} else if (drvstren_ohm < 45) {
			stren_setting = 0x1b;
		} else if (drvstren_ohm < 50) {
			stren_setting = 0x1a;
		} else if (drvstren_ohm < 56) {
			stren_setting = 0x19;
		} else if (drvstren_ohm < 64) {
			stren_setting = 0x18;
		} else if (drvstren_ohm < 74) {
			stren_setting = 0x0b;
		} else if (drvstren_ohm < 88) {
			stren_setting = 0x0a;
		} else if (drvstren_ohm < 108) {
			stren_setting = 0x09;
		} else if (drvstren_ohm < 140) {
			stren_setting = 0x08;
		} else if (drvstren_ohm < 200) {
			stren_setting = 0x03;
		} else if (drvstren_ohm < 360) {
			stren_setting = 0x02;
		} else if (drvstren_ohm < 481) {
			stren_setting = 0x01;
		} else {
			stren_setting = 0x00; /* High-impedance */
		}
	} else if (targetcsr == ODTSTRENP) {
#if STM32MP_DDR3_TYPE
		/*
		 * DDR3 - P and N has the same impedance and non-zero
		 * user input is half the individual pull-up and pull-down impedances values
		 * because of parallel between them
		 */
		if (drvstren_ohm == 0) {
			stren_setting = 0x00; /* High-impedance */
		} else if (drvstren_ohm < 15) {
			stren_setting = 0x3f;
		} else if (drvstren_ohm < 16) {
			stren_setting = 0x3e;
		} else if (drvstren_ohm < 17) {
			stren_setting = 0x3b;
		} else if (drvstren_ohm < 18) {
			stren_setting = 0x3a;
		} else if (drvstren_ohm < 20) {
			stren_setting = 0x39;
		} else if (drvstren_ohm < 21) {
			stren_setting = 0x38;
		} else if (drvstren_ohm < 23) {
			stren_setting = 0x1b;
		} else if (drvstren_ohm < 26) {
			stren_setting = 0x1a;
		} else if (drvstren_ohm < 29) {
			stren_setting = 0x19;
		} else if (drvstren_ohm < 33) {
			stren_setting = 0x18;
		} else if (drvstren_ohm < 38) {
			stren_setting = 0x0b;
		} else if (drvstren_ohm < 45) {
			stren_setting = 0x0a;
		} else if (drvstren_ohm < 55) {
			stren_setting = 0x09;
		} else if (drvstren_ohm < 71) {
			stren_setting = 0x08;
		} else if (drvstren_ohm < 101) {
			stren_setting = 0x03;
		} else if (drvstren_ohm < 181) {
			stren_setting = 0x02;
		} else if (drvstren_ohm < 241) {
			stren_setting = 0x01;
		} else {
			stren_setting = 0x00; /* High-impedance */
		}
#elif STM32MP_DDR4_TYPE
		/* DDR4 - P is non-zero */
		if (drvstren_ohm == 0) {
			stren_setting = 0x00; /* High-impedance */
		} else if (drvstren_ohm < 29) {
			stren_setting = 0x3f;
		} else if (drvstren_ohm < 31) {
			stren_setting = 0x3e;
		} else if (drvstren_ohm < 33) {
			stren_setting = 0x3b;
		} else if (drvstren_ohm < 35) {
			stren_setting = 0x3a;
		} else if (drvstren_ohm < 38) {
			stren_setting = 0x39;
		} else if (drvstren_ohm < 41) {
			stren_setting = 0x38;
		} else if (drvstren_ohm < 45) {
			stren_setting = 0x1b;
		} else if (drvstren_ohm < 50) {
			stren_setting = 0x1a;
		} else if (drvstren_ohm < 56) {
			stren_setting = 0x19;
		} else if (drvstren_ohm < 64) {
			stren_setting = 0x18;
		} else if (drvstren_ohm < 74) {
			stren_setting = 0x0b;
		} else if (drvstren_ohm < 88) {
			stren_setting = 0x0a;
		} else if (drvstren_ohm < 108) {
			stren_setting = 0x09;
		} else if (drvstren_ohm < 140) {
			stren_setting = 0x08;
		} else if (drvstren_ohm < 200) {
			stren_setting = 0x03;
		} else if (drvstren_ohm < 360) {
			stren_setting = 0x02;
		} else if (drvstren_ohm < 481) {
			stren_setting = 0x01;
		} else {
			stren_setting = 0x00; /* High-impedance */
		}
#elif STM32MP_LPDDR4_TYPE
		/* LPDDR4 - P is high-Z */
		stren_setting = 0x00; /* High-impedance */
#endif /* STM32MP_LPDDR4_TYPE */
	} else if (targetcsr == ODTSTRENN) {
#if STM32MP_DDR3_TYPE
		/*
		 * DDR3 - P and N has the same impedance and non-zero
		 * Times 2 of user input because of parallel pull-up and pull-down termination
		 */
		if (drvstren_ohm == 0) {
			stren_setting = 0x00; /* High-impedance */
		} else if (drvstren_ohm < 15) {
			stren_setting = 0x3f;
		} else if (drvstren_ohm < 16) {
			stren_setting = 0x3e;
		} else if (drvstren_ohm < 17) {
			stren_setting = 0x3b;
		} else if (drvstren_ohm < 18) {
			stren_setting = 0x3a;
		} else if (drvstren_ohm < 20) {
			stren_setting = 0x39;
		} else if (drvstren_ohm < 21) {
			stren_setting = 0x38;
		} else if (drvstren_ohm < 23) {
			stren_setting = 0x1b;
		} else if (drvstren_ohm < 26) {
			stren_setting = 0x1a;
		} else if (drvstren_ohm < 29) {
			stren_setting = 0x19;
		} else if (drvstren_ohm < 33) {
			stren_setting = 0x18;
		} else if (drvstren_ohm < 38) {
			stren_setting = 0x0b;
		} else if (drvstren_ohm < 45) {
			stren_setting = 0x0a;
		} else if (drvstren_ohm < 55) {
			stren_setting = 0x09;
		} else if (drvstren_ohm < 71) {
			stren_setting = 0x08;
		} else if (drvstren_ohm < 101) {
			stren_setting = 0x03;
		} else if (drvstren_ohm < 181) {
			stren_setting = 0x02;
		} else if (drvstren_ohm < 241) {
			stren_setting = 0x01;
		} else {
			stren_setting = 0x00; /* High-impedance */
		}
#elif STM32MP_DDR4_TYPE
		/* DDR4 - N is high-Z */
		stren_setting = 0x00; /* High-impedance */
#elif STM32MP_LPDDR4_TYPE
		/* LPDDR4 - N is non-zero */
		if (drvstren_ohm == 0) {
			stren_setting = 0x00; /* High-impedance */
		} else if (drvstren_ohm < 29) {
			stren_setting = 0x3f;
		} else if (drvstren_ohm < 31) {
			stren_setting = 0x3e;
		} else if (drvstren_ohm < 33) {
			stren_setting = 0x3b;
		} else if (drvstren_ohm < 35) {
			stren_setting = 0x3a;
		} else if (drvstren_ohm < 38) {
			stren_setting = 0x39;
		} else if (drvstren_ohm < 41) {
			stren_setting = 0x38;
		} else if (drvstren_ohm < 45) {
			stren_setting = 0x1b;
		} else if (drvstren_ohm < 50) {
			stren_setting = 0x1a;
		} else if (drvstren_ohm < 56) {
			stren_setting = 0x19;
		} else if (drvstren_ohm < 64) {
			stren_setting = 0x18;
		} else if (drvstren_ohm < 74) {
			stren_setting = 0x0b;
		} else if (drvstren_ohm < 88) {
			stren_setting = 0x0a;
		} else if (drvstren_ohm < 108) {
			stren_setting = 0x09;
		} else if (drvstren_ohm < 140) {
			stren_setting = 0x08;
		} else if (drvstren_ohm < 200) {
			stren_setting = 0x03;
		} else if (drvstren_ohm < 360) {
			stren_setting = 0x02;
		} else if (drvstren_ohm < 481) {
			stren_setting = 0x01;
		} else {
			stren_setting = 0x00; /* High-impedance */
		}
#endif /* STM32MP_LPDDR4_TYPE */
	} else if ((targetcsr == ADRVSTRENP) || (targetcsr == ADRVSTRENN)) {
		if (drvstren_ohm == 120) {
			stren_setting = 0x00;
		} else if (drvstren_ohm == 60) {
			stren_setting = 0x01;
		} else if (drvstren_ohm == 40) {
			stren_setting = 0x03;
		} else if (drvstren_ohm == 30) {
			stren_setting = 0x07;
		} else if (drvstren_ohm == 24) {
			stren_setting = 0x0F;
		} else if (drvstren_ohm == 20) {
			stren_setting = 0x1F;
		} else {
			ERROR("%s userinputadvanced.atximpedance %d Ohms value is not valid.\n",
			      __func__, drvstren_ohm);
			ERROR("Valid values are: 20, 24, 30, 40, 60 and 120 Ohms.\n");
		}

	} else {
		ERROR("targetcsr = %u, in %s, is not valid.\n",
		      targetcsr, __func__);
	}

	return stren_setting;
}
