/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

void *ddrphy_phyinit_get_user_input_basic_base(void)
{
	return (void *)&userinputbasic;
}

int ddrphy_phyinit_get_user_input_basic_pllbypass_0(void)
{
	return userinputbasic.pllbypass[0];
}

void *ddrphy_phyinit_get_user_input_advanced_base(void)
{
	return (void *)&userinputadvanced;
}

void *ddrphy_phyinit_get_user_input_mode_register_base(void)
{
	return (void *)&userinputmoderegister;
}

void *ddrphy_phyinit_get_user_input_swizzle_base(void)
{
	return (void *)&userinputswizzle;
}

/*
 * This is used to initialize the PhyInit structures before user defaults and overrides are applied.
 *
 * @return Void
 */
void ddrphy_phyinit_initstruct(void)
{
	/*
	 * ##############################################################
	 * Basic Message Block Variables
	 * ##############################################################
	 */
	int myps;

	/*
	 * ##############################################################
	 * These are typically invariant across pstate
	 * ##############################################################
	 */
	uint8_t msgmisc = 0x00U;	/* For fast simulation */
	uint8_t reserved00 = 0x0U;	/*
					 * Set reserved00[7] = 1 (If using T28 attenuated receivers)
					 * Set reserved00[6:0] = 0 (Reserved; must be set to 0)
					 */

#ifdef USE_STM32MP257CXX_EMU
#if STM32MP_DDR3_TYPE
	uint8_t hdtctrl = 0xFU;
#elif STM32MP_DDR4_TYPE
	uint8_t hdtctrl = 0xFFU;
#elif STM32MP_LPDDR4_TYPE
	uint8_t hdtctrl = 0xC8U;
#endif /* STM32MP_LPDDR4_TYPE */
#else /* USE_STM32MP257CXX_EMU */
	uint8_t hdtctrl = 0xFFU;
#endif /* USE_STM32MP257CXX_EMU */

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	uint8_t cspresent = 0x01U;	/*
					 * Indicates presence of DRAM at each chip select for PHY.
					 *
					 * If the bit is set to 1, the CS is connected to DRAM.
					 * If the bit is set to 0, the CS is not connected to DRAM.
					 *
					 * Set cspresent[0]   = 1 (if CS0 is populated with DRAM)
					 * Set cspresent[1]   = 1 (if CS1 is populated with DRAM)
					 * Set cspresent[2]   = 1 (if CS2 is populated with DRAM)
					 * Set cspresent[3]   = 1 (if CS3 is populated with DRAM)
					 * Set cspresent[7:4] = 0 (Reserved; must be set to 0)
					 */
	uint8_t dfimrlmargin = 0x01U;	/* 1 is typically good in DDR3 */
#if STM32MP_DDR3_TYPE
	uint8_t addrmirror = 0x00U;	/*
					 * Set addrmirror[pstate] if CS[pstate] is mirrored.
					 * (typically odd CS are mirroed in DIMMs)
					 */
#else
	uint8_t addrmirror = 0xAAU;	/*
					 * Set addrmirror[pstate] if CS[pstate] is mirrored.
					 * (typically odd CS are mirroed in DIMMs)
					 */
#endif /* STM32MP_DDR3_TYPE */
	uint8_t wrodtpat_rank0 = 0x01U;	/*
					 * When Writing Rank0 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t wrodtpat_rank1 = 0x02U;	/*
					 * When Writing Rank1 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
#if STM32MP_DDR3_TYPE
	uint8_t wrodtpat_rank2 = 0x04U;	/*
					 * When Writing Rank2 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t wrodtpat_rank3 = 0x08U;	/*
					 * When Writing Rank3 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
#else
	uint8_t wrodtpat_rank2 = 0x00U;	/*
					 * When Writing Rank2 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t wrodtpat_rank3 = 0x00U;	/*
					 * When Writing Rank3 : Bits[3:0] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
#endif /* STM32MP_DDR3_TYPE */
	uint8_t rdodtpat_rank0 = 0x20U;	/*
					 * When Reading Rank0 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t rdodtpat_rank1 = 0x10U;	/*
					 * When Reading Rank1 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
#if STM32MP_DDR3_TYPE
	uint8_t rdodtpat_rank2 = 0x80U;	/*
					 * When Reading Rank2 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t rdodtpat_rank3 = 0x40U;	/*
					 * When Reading Rank3 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
#else
	uint8_t rdodtpat_rank2 = 0x00U;	/*
					 * When Reading Rank2 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */
	uint8_t rdodtpat_rank3 = 0x00U;	/*
					 * When Reading Rank3 : Bits[7:4] should be set to the
					 * desired setting of ODT[3:0] to the DRAM
					 */

	uint8_t d4misc = 0x1U;		/*
					 * Protect memory reset:
					 * 0x1 = dfi_reset_n cannot control BP_MEMRESERT_L to
					 *       devices after training.
					 * 0x0 = dfi_resert_n can control BP_MEMRESERT_L to
					 *       devices after training.
					 */
#endif /* STM32MP_DDR3_TYPE */
#elif STM32MP_LPDDR4_TYPE
	uint8_t caterminatingrankcha = 0x00U; /*Usually Rank0 is terminating rank */
	uint8_t caterminatingrankchb = 0x00U; /*Usually Rank0 is terminating rank */
	uint8_t dfimrlmargin = 0x02U; /*This needs to be large enough for max tDQSCK variation */
#endif /* STM32MP_LPDDR4_TYPE */

#if STM32MP_DDR3_TYPE
	uint8_t share2dvrefresult = 0x0U;
#elif STM32MP_DDR4_TYPE
	uint8_t share2dvrefresult = 0x1U;
#elif STM32MP_LPDDR4_TYPE
#ifdef USE_STM32MP257CXX_EMU
	uint8_t share2dvrefresult = 0x0U;
#else
	uint8_t share2dvrefresult = 0x1U;	/*
						 * Bitmap that controls which vref generator the
						 * phy will use per pstate
						 *     If share2dvrefresult[x] = 1, pstate x will
						 *     use the per-lane VrefDAC0/1 CSRs which can be
						 *     trained by 2d training. If 2D has not run
						 *     yet, VrefDAC0/1 will default to pstate 0's
						 *     1D phyVref messageBlock setting.
						 *     If share2dvrefresult[x] = 0, pstate x will
						 *     use the per-phy VrefInGlobal CSR, which are
						 *     set to pstate x's 1D phyVref messageBlock
						 *     setting.
						 */
#endif /* USE_STM32MP257CXX_EMU */
	uint8_t usebroadcastmr = 0x00U;
#endif /* STM32MP_LPDDR4_TYPE */

	/*
	 * ##############################################################
	 * These typically change across pstate
	 * ##############################################################
	 */

#if STM32MP_DDR4_TYPE
	uint16_t alt_cas_l[NB_PS]; /* Need to set if using RDDBI */
	uint16_t alt_wcas_l[NB_PS]; /* Need to set if using 2tck Write Preambles */
	uint16_t rtt_nom_wr_park0[NB_PS];
	uint16_t rtt_nom_wr_park1[NB_PS];
	uint16_t rtt_nom_wr_park2[NB_PS];
	uint16_t rtt_nom_wr_park3[NB_PS];
	uint16_t rtt_nom_wr_park4[NB_PS];
	uint16_t rtt_nom_wr_park5[NB_PS];
	uint16_t rtt_nom_wr_park6[NB_PS];
	uint16_t rtt_nom_wr_park7[NB_PS];
#endif /* STM32MP_DDR4_TYPE */

	VERBOSE("%s Start\n", __func__);

#if STM32MP_DDR4_TYPE
	for (myps = 0; myps < NB_PS; myps++) {
#ifdef USE_STM32MP257CXX_EMU
		alt_cas_l[myps] = 0x0001U;
#else
		alt_cas_l[myps] = 0x0000U;
#endif /* USE_STM32MP257CXX_EMU */
		alt_wcas_l[myps] = 0x0000U;
	}
#endif /* STM32MP_DDR4_TYPE */

	/*
	 * ##############################################################
	 * These are per-pstate Control Words for RCD
	 * Please enter the correct values for your configuration
	 * ##############################################################
	 */

	/*
	 * ##############################################################
	 * 95% of users will not need to edit below
	 * ##############################################################
	 */

#if STM32MP_DDR4_TYPE
	/*
	 * Per Rank MR seeting for RTT_NOM, RTT_WR, RTT_PARK per rank. Options unlikely need to be
	 * used. See MB details on how to program if required.
	 */
	for (myps = 0; myps < NB_PS; myps++) {
		rtt_nom_wr_park0[myps] = 0x0U;
		rtt_nom_wr_park1[myps] = 0x0U;
		rtt_nom_wr_park2[myps] = 0x0U;
		rtt_nom_wr_park3[myps] = 0x0U;
		rtt_nom_wr_park4[myps] = 0x0U;
		rtt_nom_wr_park5[myps] = 0x0U;
		rtt_nom_wr_park6[myps] = 0x0U;
		rtt_nom_wr_park7[myps] = 0x0U;
	}
#endif /* STM32MP_DDR4_TYPE */

	/* 1D message block defaults */
	for (myps = 0; myps < NB_PS; myps++) {
		mb_ddr_1d[myps].pstate = (uint8_t)myps;
		mb_ddr_1d[myps].sequencectrl = (uint16_t)userinputadvanced.sequencectrl[myps];
		mb_ddr_1d[myps].phyconfigoverride = 0x0U;
		mb_ddr_1d[myps].hdtctrl = hdtctrl;
		mb_ddr_1d[myps].msgmisc = msgmisc;
		mb_ddr_1d[myps].reserved00 = reserved00;
		mb_ddr_1d[myps].dfimrlmargin = dfimrlmargin;
		mb_ddr_1d[myps].phyvref = (uint8_t)userinputadvanced.phyvref;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		mb_ddr_1d[myps].cspresent = cspresent;
		mb_ddr_1d[myps].cspresentd0 = cspresent;
		mb_ddr_1d[myps].cspresentd1 = 0x0U; /* Unused */
		mb_ddr_1d[myps].addrmirror = addrmirror;

		mb_ddr_1d[myps].acsmodtctrl0 = wrodtpat_rank0 | rdodtpat_rank0;
		mb_ddr_1d[myps].acsmodtctrl1 = wrodtpat_rank1 | rdodtpat_rank1;
		mb_ddr_1d[myps].acsmodtctrl2 = wrodtpat_rank2 | rdodtpat_rank2;
		mb_ddr_1d[myps].acsmodtctrl3 = wrodtpat_rank3 | rdodtpat_rank3;

		mb_ddr_1d[myps].acsmodtctrl4 = 0x0U; /* Unused */
		mb_ddr_1d[myps].acsmodtctrl5 = 0x0U; /* Unused */
		mb_ddr_1d[myps].acsmodtctrl6 = 0x0U; /* Unused */
		mb_ddr_1d[myps].acsmodtctrl7 = 0x0U; /* Unused */
		mb_ddr_1d[myps].enableddqs = (uint8_t)((userinputbasic.numactivedbytedfi0 +
							userinputbasic.numactivedbytedfi1) * 8);
#if STM32MP_DDR3_TYPE
		mb_ddr_1d[myps].phycfg = (uint8_t)userinputadvanced.is2ttiming[myps];
#else
#ifdef USE_STM32MP257CXX_EMU
		mb_ddr_1d[myps].phycfg = (uint8_t)userinputadvanced.is2ttiming[myps];
#else
		mb_ddr_1d[myps].phycfg = (userinputmoderegister.mr3[myps] & 0x8) ?
					 0U : (uint8_t)userinputadvanced.is2ttiming[myps];
#endif /* USE_STM32MP257CXX_EMU */
		mb_ddr_1d[myps].x16present = (0x10 == userinputbasic.dramdatawidth) ?
					     mb_ddr_1d[myps].cspresent : 0x0U;
		mb_ddr_1d[myps].d4misc = d4misc;
		mb_ddr_1d[myps].cssetupgddec = 0x1U;	/*
							 * If Geardown is chosen, dynamically modify
							 * CS timing.
							 */
		mb_ddr_1d[myps].rtt_nom_wr_park0 = rtt_nom_wr_park0[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park1 = rtt_nom_wr_park1[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park2 = rtt_nom_wr_park2[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park3 = rtt_nom_wr_park3[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park4 = rtt_nom_wr_park4[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park5 = rtt_nom_wr_park5[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park6 = rtt_nom_wr_park6[myps];
		mb_ddr_1d[myps].rtt_nom_wr_park7 = rtt_nom_wr_park7[myps];
#endif /* STM32MP_DDR3_TYPE */

		mb_ddr_1d[myps].mr0 = (uint16_t)userinputmoderegister.mr0[myps];
		mb_ddr_1d[myps].mr1 = (uint16_t)userinputmoderegister.mr1[myps];
		mb_ddr_1d[myps].mr2 = (uint16_t)userinputmoderegister.mr2[myps];
#if STM32MP_DDR4_TYPE
		mb_ddr_1d[myps].mr3 = (uint16_t)userinputmoderegister.mr3[myps];
		mb_ddr_1d[myps].mr4 = (uint16_t)userinputmoderegister.mr4[myps];
		mb_ddr_1d[myps].mr5 = (uint16_t)userinputmoderegister.mr5[myps];
		mb_ddr_1d[myps].mr6 = (uint16_t)userinputmoderegister.mr6[myps];

		mb_ddr_1d[myps].alt_cas_l = alt_cas_l[myps];
		mb_ddr_1d[myps].alt_wcas_l = (uint8_t)alt_wcas_l[myps];

		/* Outputs - just initialize these to zero */
		mb_ddr_1d[myps].vrefdqr0nib0 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib1 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib2 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib3 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib4 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib5 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib6 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib7 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib8 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib9 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib10 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib11 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib12 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib13 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib14 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib15 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib16 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib17 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib18 = 0x00U;
		mb_ddr_1d[myps].vrefdqr0nib19 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib0 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib1 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib2 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib3 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib4 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib5 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib6 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib7 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib8 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib9 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib10 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib11 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib12 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib13 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib14 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib15 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib16 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib17 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib18 = 0x00U;
		mb_ddr_1d[myps].vrefdqr1nib19 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib0 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib1 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib2 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib3 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib4 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib5 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib6 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib7 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib8 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib9 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib10 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib11 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib12 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib13 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib14 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib15 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib16 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib17 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib18 = 0x00U;
		mb_ddr_1d[myps].vrefdqr2nib19 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib0 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib1 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib2 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib3 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib4 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib5 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib6 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib7 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib8 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib9 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib10 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib11 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib12 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib13 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib14 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib15 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib16 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib17 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib18 = 0x00U;
		mb_ddr_1d[myps].vrefdqr3nib19 = 0x00U;
#endif /* STM32MP_DDR4_TYPE */
#elif STM32MP_LPDDR4_TYPE
#ifdef USE_STM32MP257CXX_EMU
		mb_ddr_1d[myps].enableddqscha = userinputbasic.numactivedbytedfi0;
#else
		mb_ddr_1d[myps].enableddqscha = (uint8_t)(userinputbasic.numactivedbytedfi0 * 8);
#endif /* USE_STM32MP257CXX_EMU */
		mb_ddr_1d[myps].cspresentcha = (2 == userinputbasic.numrank_dfi0) ?
					       0x3U : (uint8_t)userinputbasic.numrank_dfi0;
#ifdef USE_STM32MP257CXX_EMU
		mb_ddr_1d[myps].enableddqschb = userinputbasic.numactivedbytedfi1;
#else
		mb_ddr_1d[myps].enableddqschb = (uint8_t)(userinputbasic.numactivedbytedfi1 * 8);
#endif /* USE_STM32MP257CXX_EMU */
		mb_ddr_1d[myps].cspresentchb = (2 == userinputbasic.numrank_dfi1) ?
					       0x3U : (uint8_t)userinputbasic.numrank_dfi1;
		mb_ddr_1d[myps].usebroadcastmr = usebroadcastmr;

		mb_ddr_1d[myps].lp4misc = 0x00U;
		mb_ddr_1d[myps].caterminatingrankcha = caterminatingrankcha;
		mb_ddr_1d[myps].caterminatingrankchb = caterminatingrankchb;
		mb_ddr_1d[myps].lp4quickboot = 0x00U;
		mb_ddr_1d[myps].catrainopt = 0x00U;
		mb_ddr_1d[myps].x8mode = 0x00U;

		mb_ddr_1d[myps].mr1_a0 = (uint8_t)userinputmoderegister.mr1[myps];
		mb_ddr_1d[myps].mr2_a0 = (uint8_t)userinputmoderegister.mr2[myps];
		mb_ddr_1d[myps].mr3_a0 = (uint8_t)userinputmoderegister.mr3[myps];
		mb_ddr_1d[myps].mr4_a0 = (uint8_t)userinputmoderegister.mr4[myps];
		mb_ddr_1d[myps].mr11_a0 = (uint8_t)userinputmoderegister.mr11[myps];
		mb_ddr_1d[myps].mr12_a0 = (uint8_t)userinputmoderegister.mr12[myps];
		mb_ddr_1d[myps].mr13_a0 = (uint8_t)userinputmoderegister.mr13[myps];
		mb_ddr_1d[myps].mr14_a0 = (uint8_t)userinputmoderegister.mr14[myps];
		mb_ddr_1d[myps].mr16_a0 = 0x00U;
		mb_ddr_1d[myps].mr17_a0 = 0x00U;
		mb_ddr_1d[myps].mr22_a0 = (uint8_t)userinputmoderegister.mr22[myps];
		mb_ddr_1d[myps].mr24_a0 = 0x00U;
		mb_ddr_1d[myps].mr1_a1 = (uint8_t)userinputmoderegister.mr1[myps];
		mb_ddr_1d[myps].mr2_a1 = (uint8_t)userinputmoderegister.mr2[myps];
		mb_ddr_1d[myps].mr3_a1 = (uint8_t)userinputmoderegister.mr3[myps];
		mb_ddr_1d[myps].mr4_a1 = (uint8_t)userinputmoderegister.mr4[myps];
		mb_ddr_1d[myps].mr11_a1 = (uint8_t)userinputmoderegister.mr11[myps];
		mb_ddr_1d[myps].mr12_a1 = (uint8_t)userinputmoderegister.mr12[myps];
		mb_ddr_1d[myps].mr13_a1 = (uint8_t)userinputmoderegister.mr13[myps];
		mb_ddr_1d[myps].mr14_a1 = (uint8_t)userinputmoderegister.mr14[myps];
		mb_ddr_1d[myps].mr16_a1 = 0x00U;
		mb_ddr_1d[myps].mr17_a1 = 0x00U;
		mb_ddr_1d[myps].mr22_a1 = (uint8_t)userinputmoderegister.mr22[myps];
		mb_ddr_1d[myps].mr24_a1 = 0x00U;

		mb_ddr_1d[myps].mr1_b0 = (uint8_t)userinputmoderegister.mr1[myps];
		mb_ddr_1d[myps].mr2_b0 = (uint8_t)userinputmoderegister.mr2[myps];
		mb_ddr_1d[myps].mr3_b0 = (uint8_t)userinputmoderegister.mr3[myps];
		mb_ddr_1d[myps].mr4_b0 = (uint8_t)userinputmoderegister.mr4[myps];
		mb_ddr_1d[myps].mr11_b0 = (uint8_t)userinputmoderegister.mr11[myps];
		mb_ddr_1d[myps].mr12_b0 = (uint8_t)userinputmoderegister.mr12[myps];
		mb_ddr_1d[myps].mr13_b0 = (uint8_t)userinputmoderegister.mr13[myps];
		mb_ddr_1d[myps].mr14_b0 = (uint8_t)userinputmoderegister.mr14[myps];
		mb_ddr_1d[myps].mr16_b0 = 0x00U;
		mb_ddr_1d[myps].mr17_b0 = 0x00U;
		mb_ddr_1d[myps].mr22_b0 = (uint8_t)userinputmoderegister.mr22[myps];
		mb_ddr_1d[myps].mr24_b0 = 0x00U;
		mb_ddr_1d[myps].mr1_b1 = (uint8_t)userinputmoderegister.mr1[myps];
		mb_ddr_1d[myps].mr2_b1 = (uint8_t)userinputmoderegister.mr2[myps];
		mb_ddr_1d[myps].mr3_b1 = (uint8_t)userinputmoderegister.mr3[myps];
		mb_ddr_1d[myps].mr4_b1 = (uint8_t)userinputmoderegister.mr4[myps];
		mb_ddr_1d[myps].mr11_b1 = (uint8_t)userinputmoderegister.mr11[myps];
		mb_ddr_1d[myps].mr12_b1 = (uint8_t)userinputmoderegister.mr12[myps];
		mb_ddr_1d[myps].mr13_b1 = (uint8_t)userinputmoderegister.mr13[myps];
		mb_ddr_1d[myps].mr14_b1 = (uint8_t)userinputmoderegister.mr14[myps];
		mb_ddr_1d[myps].mr16_b1 = 0x00U;
		mb_ddr_1d[myps].mr17_b1 = 0x00U;
		mb_ddr_1d[myps].mr22_b1 = (uint8_t)userinputmoderegister.mr22[myps];
		mb_ddr_1d[myps].mr24_b1 = 0x00U;
#endif /* STM32MP_LPDDR4_TYPE */

		mb_ddr_1d[myps].share2dvrefresult = share2dvrefresult;

		/* Zero out struct contents */
		memset((void *) &shdw_ddr_1d[myps], 0, sizeof(struct pmu_smb_ddr_1d));
	} /* myps */

	VERBOSE("%s End\n", __func__);
}
