/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

#if STM32MP_LPDDR4_TYPE
/*
 * Program DfiWrRdDataCsConfig
 * - Fields:
 *   - dfiwrdatacspolarity
 *   - dfirddatacspolarity
 * - Dependencies:
 *   - user_input_advanced.EnableDfiCsPolarityFix
 */
static void dfiwrrddatacsconfig_program(void)
{
	uint16_t dfiwrdatacspolarity;
	uint16_t dfirddatacspolarity;

	/*
	 * DfiWrRdDataCsConfig : dfiwrdatacspolarity=0x1 and dfirddatacspolarity=0x1.
	 * Set DataCsPolarity bits to enable active high
	 */
	dfiwrdatacspolarity = 0x1U;
	dfirddatacspolarity = 0x1U;

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | C0 | CSR_DFIWRRDDATACSCONFIG_ADDR)),
		      (dfiwrdatacspolarity << CSR_DFIWRDATACSPOLARITY_LSB |
		       dfirddatacspolarity << CSR_DFIRDDATACSPOLARITY_LSB));
}
#endif /* STM32MP_LPDDR4_TYPE */

/*
 * Registers: Seq0BDLY0, Seq0BDLY1, Seq0BDLY2, Seq0BDLY3
 * - Program PIE instruction delays
 * - Dependencies:
 *   - user_input_basic.frequency
 */
static void seq0bdly_program(void)
{
	int pstate;

	/*
	 * Calculate the counts to obtain the correct delay for each frequency
	 * Need to divide by 4 since the delay value are specified in units of
	 * 4 clocks.
	 */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int lowfreqopt __attribute__((unused));
		int delayscale_x100 = 100;
		int p_addr;
		long long dfifrq_x10;
		long long dlllock_x10;
		uint16_t pscount[4]; /* Need delays for 0.5us, 1us, 10us, and 25us */

		p_addr = pstate << 20;
		dfifrq_x10 = (10 * userinputbasic.frequency[pstate] / 2);
		pscount[0] = (uint16_t)((dfifrq_x10 * delayscale_x100) / (10 * 100 * 2 * 4));

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		if ( userinputbasic.frequency[pstate] < 400) {
			lowfreqopt = 3;
		} else if ( userinputbasic.frequency[pstate] < 533) {
			lowfreqopt = 11;
		} else {
			lowfreqopt = 0;
		}

		pscount[1] = (uint16_t)(( 1 * dfifrq_x10 * delayscale_x100) / (10 * 100 * 4)) -
				     lowfreqopt;
#elif STM32MP_LPDDR4_TYPE
		pscount[1] = (uint16_t)((1 * dfifrq_x10 * delayscale_x100) / (10 * 100 * 4));
#endif /* STM32MP_LPDDR4_TYPE */
		pscount[2] = (uint16_t)((10 * dfifrq_x10 * delayscale_x100) / (10 * 100 * 4));

		if (dfifrq_x10 > 2665) {
			dlllock_x10 = 1760;
		} else if (dfifrq_x10 <= 2665 && dfifrq_x10 > 2000) {
			dlllock_x10 = 1320;
		} else {
			dlllock_x10 = 640;
		}

		pscount[3] = (uint16_t)(dlllock_x10 / (10 * 4));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | C0 | TMASTER |
							      CSR_SEQ0BDLY0_ADDR)),
			      pscount[0]);

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | C0 | TMASTER |
							      CSR_SEQ0BDLY1_ADDR)),
			      pscount[1]);

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | C0 | TMASTER |
							      CSR_SEQ0BDLY2_ADDR)),
			      pscount[2]);

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | C0 | TMASTER |
							      CSR_SEQ0BDLY3_ADDR)),
			      pscount[3]);
	}
}

/*
 * Registers: Seq0BDisableFlag0 Seq0BDisableFlag1 Seq0BDisableFlag2
 * Seq0BDisableFlag3 Seq0BDisableFlag4 Seq0BDisableFlag5
 * - Program PIE Instruction Disable Flags
 * - Dependencies:
 *   - user_input_advanced.DisableRetraining (DDR3/DDR4)
 *   - skip_training (DDR3/DDR4)
 *   - user_input_basic.frequency (DDR3/DDR4)
 */
static void seq0bdisableflag_program(__attribute__((unused))bool skip_training)
{
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG0_ADDR)),
		      0x0000U);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG1_ADDR)),
		      0x0173U);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG2_ADDR)),
		      0x0060U);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG3_ADDR)),
		      0x6110U);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG4_ADDR)),
		      0x2152U);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG5_ADDR)),
		      0xDFBDU);

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG6_ADDR)),
		      0xFFFFU);
#elif STM32MP_LPDDR4_TYPE
	if (skip_training || userinputadvanced.disableretraining ||
	    userinputbasic.frequency[0] < 333) {
		/* Disabling DRAM drift compensation */
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG |
							      CSR_SEQ0BDISABLEFLAG6_ADDR)),
			      0xFFFFU);
	} else {
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG |
							      CSR_SEQ0BDISABLEFLAG6_ADDR)),
			      0x2060U);
	}
#endif /* STM32MP_LPDDR4_TYPE */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_SEQ0BDISABLEFLAG7_ADDR)),
		      0x6152U);
}

#if STM32MP_LPDDR4_TYPE
/*
 * Registers: ppttrainsetup and ppttrainsetup2
 * - Related to DFI PHY Master Interface (PMI). See Register description in PUB.
 * - Enable DFI PMI if training firmware was run
 * - Fields:
 *   - PhyMstrTrainInterval
 *   - PhyMstrMaxReqToAck
 *   - PhyMstrFreqOverride
 * - Dependencies:
 *   - skip_training
 *   - user_input_basic.frequency
 *   - user_input_advanced.PhyMstrTrainInterval
 *   - user_input_advanced.PhyMstrMaxReqToAck
 */
static void ppttrainsetup_program(void)
{
	int pstate;

	/* Enabling Phy Master Interface for DRAM drift compensation */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		uint16_t ppttrainsetup;

		p_addr = pstate << 20;
		if (userinputbasic.frequency[pstate] >= 333) {
			ppttrainsetup =	(uint16_t)(
						(userinputadvanced.phymstrtraininterval[pstate] <<
						CSR_PHYMSTRTRAININTERVAL_LSB) |
						(userinputadvanced.phymstrmaxreqtoack[pstate] <<
						CSR_PHYMSTRMAXREQTOACK_LSB));

			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
									CSR_PPTTRAINSETUP_ADDR)),
				      ppttrainsetup);
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
									CSR_PPTTRAINSETUP2_ADDR)),
				      0x0003U);
		}
	}
}

/*
 * Registers AcsmPlayback*x*
 * - Program Address/Command Sequence Engine (ACSM) registers with
 *   required instructions for retraining algorithm.
 * - Dependencies:
 *   - user_input_basic.numpstates
 */
static void acsmplayback_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		uint16_t acsmplayback[2][4] = { { 0U, 0U, 0U, 0U },
						{ 0U, 0U, 0U, 0U } };
		int numvec;
		int p_addr;
		int vec;

		p_addr = pstate << 20;
		numvec = 0;
		acsmplayback[0][0] = 0x3U << 6 | 0x20U;
		acsmplayback[1][0] = 0x0U << 6 | 0x12U;
		acsmplayback[0][1] = 0x3U << 6 | 0x20U;
		acsmplayback[1][1] = 0x0U << 6 | 0x12U;
		acsmplayback[0][2] = 0x3U << 6 | 0x20U;
		acsmplayback[1][2] = 0x0U << 6 | 0x12u;
		numvec = 3;

		for (vec = 0; vec < numvec; vec++) {
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TACSM |
								      (CSR_ACSMPLAYBACK0X0_ADDR +
								       vec * 2))),
				      acsmplayback[0][vec]);

			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TACSM |
								      (CSR_ACSMPLAYBACK1X0_ADDR +
								       vec * 2))),
				      acsmplayback[1][vec]);
		}
	}
}

/*
 * Program Training Hardware Registers for mission mode retraining
 * and DRAM drift compensation algorithm.
 */
static void traininghwreg_program(void)
{
	int byte;
	uint16_t regdata;

	/* Programing Training Hardware Registers for mission mode retraining */

	/*
	 * - Register: AcsmCtrl13
	 *   - Fields: AcsmCkeEnb
	 */
	regdata = (0xFU << CSR_ACSMCKEENB_LSB);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (C0 | TACSM | CSR_ACSMCTRL13_ADDR)), regdata);

	/*
	 * - Register: AcsmCtrl1
	 *   - Fields: AcsmRepCnt
	 *             Need 19 iterations @ 0.25ui increments to cover 4.5UI
	 */
	regdata = (0xEU << CSR_ACSMREPCNT_LSB);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (C0 | TACSM | CSR_ACSMCTRL1_ADDR)), regdata);

	/*
	 * - Register: TsmByte1, TsmByte2
	 *   - Dependencies: userinputbasic.numdbyte
	 */

	for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
		int c_addr;
		int i_addr;
		int vec;

		/* for each chiplet */
		c_addr = byte * C1;
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE | CSR_TSMBYTE1_ADDR)),
			      0x1U);   /* [15:8] gstep; [7:0]bstep; */
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE | CSR_TSMBYTE2_ADDR)),
			      0x1U);   /* [15:0] good_bar; */

		regdata = (CSR_DTSMSTATICCMPR_MASK | CSR_DTSMSTATICCMPRVAL_MASK);

		/*
		 * - Register: TsmByte3, TsmByte5
		 *   - Fields:
		 *     - DtsmStaticCmpr
		 *     - DtsmStaticCmprVal
		 */
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE | CSR_TSMBYTE3_ADDR)),
			      regdata);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE | CSR_TSMBYTE5_ADDR)),
			      0x1U); /* [15:0] bad_bar; */

		/*
		 * - Register: TrainingParam
		 *   - Fields:
		 *     - EnDynRateReduction
		 *     - RollIntoCoarse
		 *     - IncDecRate
		 *     - TrainEnRxEn
		 *   - Dependencies:
		 *     - user_input_advanced.DisableRetraining
		 */
		regdata = (CSR_ENDYNRATEREDUCTION_MASK | CSR_ROLLINTOCOARSE_MASK |
			   (0x3U << CSR_INCDECRATE_LSB));
		regdata = userinputadvanced.disableretraining ?
			  regdata : (regdata | CSR_TRAINENRXEN_MASK);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE |
							      CSR_TRAININGPARAM_ADDR)),
			      regdata);

		/*
		 * - Register: Tsm0
		 *   - Fields:
		 *     - DtsmEnb
		 */
		regdata = (0x1U << CSR_DTSMENB_LSB);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | I0 | TDBYTE |
							      CSR_TSM0_ADDR)),
			      regdata);

		/*
		 * - Register: Tsm2
		 *   - Fields:
		 *     - DtsmDisErrChk
		 */
		regdata = (0x1U << CSR_DTSMDISERRCHK_LSB);
		for (vec = 1; vec <= I_MAX; vec++) {
			i_addr = vec * I1;
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | i_addr | TDBYTE |
								      CSR_TSM2_ADDR)),
				      regdata);
		} /* for vec */
	} /* for byte */
}
#endif /* STM32MP_LPDDR4_TYPE */

/*
 * - Register: calrate
 *   - Fields:
 *     - calOnce
 *     - calinterval
 *   - Dependencies
 *     - user_input_advanced.calinterval
 *     - user_input_advanced.calonce
 */
static void calrate_program(void)
{
	int calinterval;
	int calonce;
	uint16_t calrate;

	calinterval = userinputadvanced.calinterval;
	calonce = userinputadvanced.calonce;

	calrate = (uint16_t)((0x1 << CSR_CALRUN_LSB) | (calonce << CSR_CALONCE_LSB) |
			     (calinterval << CSR_CALINTERVAL_LSB));

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_CALRATE_ADDR)), calrate);
}

/*
 * Loads registers after training
 *
 * This function programs the PHY Initialization Engine (PIE) instructions and
 * the associated registers.
 * Training hardware registers are also programmed to for mission mode
 * retraining. (LPDDR4)
 *
 * \return void
 */
void ddrphy_phyinit_i_loadpieimage(bool skip_training)
{
	VERBOSE("%s Start\n", __func__);

	/*
	 * Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
	 * This allows the memory controller unrestricted access to the configuration CSRs.
	 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICROCONTMUXSEL_ADDR)), 0x0U);

	ddrphy_phyinit_loadpieprodcode();

#if STM32MP_LPDDR4_TYPE
	/*
	 * No user specified EnableDfiCsPolarityFix, running with new PUB with DFI CS polarity fix
	 * so program the data polarity CSR.
	 */
	dfiwrrddatacsconfig_program();
#endif /* STM32MP_LPDDR4_TYPE */

	/*
	 * - Register: Seq0BGPR7
	 *   - Program active CSx for MRS7 during D4 RDIMM frequency change
	 */

	seq0bdly_program();

	seq0bdisableflag_program(skip_training);

#if STM32MP_LPDDR4_TYPE
#if defined(USE_STM32MP257CXX_EMU)
     if (skip_training) {
#else /* USE_STM32MP257CXX_EMU */
     if (!skip_training) {
#endif /* USE_STM32MP257CXX_EMU */
		ppttrainsetup_program();
	}

	acsmplayback_program();

	traininghwreg_program();
#endif /* STM32MP_LPDDR4_TYPE */

	/*
	 * - Register: CalZap
	 *   - Prepare the calibration controller for mission mode.
	 *     Turn on calibration and hold idle until dfi_init_start is asserted sequence is
	 *     triggered.
	 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_CALZAP_ADDR)), 0x1U);

	calrate_program();

	/*
	 * At the end of this function, PHY Clk gating register UcclkHclkEnables is
	 * set for mission mode.  Additionally APB access is Isolated by setting
	 * MicroContMuxSel.
	 */
	/* Disabling Ucclk (PMU) and Hclk (training hardware) */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TDRTUB | CSR_UCCLKHCLKENABLES_ADDR)), 0x0U);

	/* Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1 */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TAPBONLY | CSR_MICROCONTMUXSEL_ADDR)), 0x1U);

	VERBOSE("%s End\n", __func__);
}
