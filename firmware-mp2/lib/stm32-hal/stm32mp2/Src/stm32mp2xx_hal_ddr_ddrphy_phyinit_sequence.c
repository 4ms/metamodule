/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * This function implements the flow of PhyInit software to initialize the PHY.
 *
 * The execution sequence follows the overview figure provided in the PhyInit App Note.
 *
 * \returns 0 on completion of the sequence, EXIT_FAILURE on error.
 */
int ddrphy_phyinit_sequence(bool skip_training, bool reten)
{
	int ret;

	/* Check user input pstate number consistency vs. SW capabilities */
	if (userinputbasic.numpstates > NB_PS) {
		return -1;
	}

	/* registering function inputs */
	runtimeconfig.skip_train = skip_training;

	VERBOSE("%s Start\n", __func__);

	/* Initialize structures */
	ddrphy_phyinit_initstruct();

	/* Re-calculate Firmware Message Block input based on final user input */
	ret = ddrphy_phyinit_calcmb();
	if (ret != 0) {
		return ret;
	}

	/* (A) Bring up VDD, VDDQ, and VAA */
	/* ddrphy_phyinit_usercustom_a_bringuppower(); */

	/* (B) Start Clocks and Reset the PHY */
	/* ddrphy_phyinit_usercustom_b_startclockresetphy(); */

	/* (C) Initialize PHY Configuration */
	ret = ddrphy_phyinit_c_initphyconfig();
	if (ret != 0) {
		return ret;
	}
	/*
	 * Customize any register write desired; This can include any CSR not covered by PhyInit
	 * or user wish to override values calculated in step_C
	 */
	ddrphy_phyinit_usercustom_custompretrain();

	/* Stop retention register tracking for training firmware related registers */
	ret = ddrphy_phyinit_reginterface(STOPTRACK, 0, 0);
	if (ret != 0) {
		return ret;
	}

#ifdef USE_STM32MP257CXX_EMU
	/* No firmware execution (i.e. always skip training) in emulation setup */
	runtimeconfig.skip_train = true;
#endif /* USE_STM32MP257CXX_EMU */

	if (runtimeconfig.skip_train) {
		/* Skip running training firmware entirely */
		ddrphy_phyinit_progcsrskiptrain(runtimeconfig.skip_train);
#ifndef USE_STM32MP257CXX_EMU
	} else {
		int pstate;

		/* Run all 1D power states, then 2D P0, to reduce total Imem/Dmem loads. */

		/* (D) Load the IMEM Memory for 1D training */
		ddrphy_phyinit_d_loadimem();

		for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
			/* (E) Set the PHY input clocks to the desired frequency */
			/* ddrphy_phyinit_usercustom_e_setdficlk(pstate); */

			/*
			 * Note: this routine implies other items such as dfifreqratio, DfiCtlClk
			 * are also set properly.
			 * Because the clocks are controlled in the SOC, external to the software
			 * and PHY, this step intended to be replaced by the user with the necessary
			 * SOC operations to achieve the new input frequency to the PHY.
			 */

			/* (F) Write the Message Block parameters for the training firmware */
			ret = ddrphy_phyinit_f_loaddmem(pstate);
			if (ret != 0) {
				return ret;
			}

			/* (G) Execute the Training Firmware */
			ret = ddrphy_phyinit_g_execfw();
			if (ret != 0) {
				return ret;
			}

			/* (H) Read the Message Block results */
			ddrphy_phyinit_h_readmsgblock();
		}
#endif /* !USE_STM32MP257CXX_EMU */
	}

	/* Start retention register tracking for training firmware related registers */
	ret = ddrphy_phyinit_reginterface(STARTTRACK, 0, 0);
	if (ret != 0) {
		return ret;
	}

	/* (I) Load PHY Init Engine Image */
	ddrphy_phyinit_i_loadpieimage(runtimeconfig.skip_train);

	/*
	 * Customize any CSR write desired to override values programmed by firmware or
	 * ddrphy_phyinit_i_loadpieimage()
	 */
	ddrphy_phyinit_usercustom_customposttrain();

	if (reten) {
		/* Save value of tracked registers for retention restore sequence. */
		ret = ddrphy_phyinit_usercustom_saveretregs();
		if (ret != 0) {
			return ret;
		}

		runtimeconfig.reten = reten;
	}

	/* (J) Initialize the PHY to Mission Mode through DFI Initialization */
	/* ddrphy_phyinit_usercustom_j_entermissionmode(); */

	VERBOSE("%s End\n", __func__);

	return 0;
}
