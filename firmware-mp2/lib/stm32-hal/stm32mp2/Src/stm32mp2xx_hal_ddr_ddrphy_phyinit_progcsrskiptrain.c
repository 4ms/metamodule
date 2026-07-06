/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"
#include "stm32mp2xx_hal_ddr_ddrphy_wrapper.h"

struct phyinit_timings {
	int tstaoff[NB_PS];
	int tpdm[NB_PS];
	int tcasl_add[NB_PS];
};

static struct phyinit_timings timings;

/*
 * set tstaoff, tpdm and tcasl_add
 */
static void set_timings(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		timings.tstaoff[pstate] = 0;
		timings.tpdm[pstate] = 0;

		timings.tcasl_add[pstate] = 0;
	}
}

/*
 * Program dfimrl per P-state according to this formula:
 *
 *         dfimrl = ceiling( (ARdPtrinitval*UI + phy_tx_insertion_dly +
 *                            phy_rx_insertion_dly + PHY_Rx_Fifo_dly + tDQSCK + tstaoff) /
 *                           dficlk_period)
 *
 * All terms in above equation specified in ps
 * tDQSCK - determine from memory model
 * tstaoff - determine from memory model
 * phy_tx_insertion_dly = 200ps
 * phy_rx_insertion_dly = 200ps
 * phy_rx_fifo_dly      = 200ps + 4UI
 */
static void dfimrl_program(void)
{
	int pstate;

	/* ### Set dfimrl per p-state ### // */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int dfimrl_in_dficlk;
		int p_addr;
		int phy_rx_fifo_dly;
		int phy_rx_insertion_dly = 200;
		int phy_tx_insertion_dly = 200;
		long long dficlk_period_x1000;
		long long dfimrl_in_fs;
		long long uifs;
		uint16_t dfimrl;

		p_addr = pstate << 20;

		uifs = (1000 * 1000000 * 1) / (userinputbasic.frequency[pstate] * 2);
		dficlk_period_x1000 = 4 * uifs;

		phy_rx_fifo_dly = (int)(((200 * 1000) + 4 * uifs) / 1000);

		dfimrl_in_fs = (ardptrinitval[pstate] * uifs) +
			       ((phy_tx_insertion_dly + phy_rx_insertion_dly + phy_rx_fifo_dly +
				 timings.tstaoff[pstate] + timings.tcasl_add[pstate] +
				 timings.tpdm[pstate]) * 1000);

		dfimrl_in_dficlk = (int)dfimrl_in_fs / dficlk_period_x1000;
		if ((dfimrl_in_fs % dficlk_period_x1000) != 0) {
			dfimrl_in_dficlk++;
		}
		dfimrl = (uint16_t)(dfimrl_in_dficlk + mb_ddr_1d[pstate].dfimrlmargin);

		/*
		 * mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TDBYTE | CBRD |
		 *                                              CSR_DFIMRL_ADDR)),
		 *              dfimrl);
		 */
		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;

			c_addr = byte << 12;
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TDBYTE | c_addr |
								      CSR_DFIMRL_ADDR)),
				      dfimrl);
		}

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER | CSR_HWTMRL_ADDR)),
			      dfimrl);
	}
}

/*
 * Program txdqsdlytg0/1[9:0] per P-State:
 *
 *         txdqsdlytg*[9:6] = floor( (4*UI + tstaoff) / UI)
 *         txdqsdlytg*[5:0] = ceiling( (tstaoff%UI / UI) * 32)
 *
 * tstaoff and UI expressed in ps
 *
 * For HMD and LPDDR4X and MEMCLK <= 533 mhz:
 *    txdqsdlytg*[9:6] = 0x5
 *
 * For other dimm types, leave TDqsDlyTg*[9:0] at default 0x100
 *
 * ppp_0001_cccc_uuuu_1101_0000
 *
 * if DDR3 or DDR4
 *      num_timingroup = numrank_dfi0;
 * else
 *      num_timingroup = numrank_dfi0 + numrank_dfi1 * dfi1exists;
 */
static void txdqsdlytg_program(uint16_t *txdqsdly)
{
	int pstate;

	/* ### Set per p-state ### // */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int p_addr;
		int txdqsdlytg_5to0; /* Fine delay - 1/32UI per increment */
		int txdqsdlytg_9to6; /* Coarse delay - 1UI per increment */
		int txdqsdlytg_fine_default = 0;
		int txdqsdlytg_coarse_default = 4;
		long long tmp_value;
		long long uifs;

		p_addr = pstate << 20;

		uifs = (1000 * 1000000 * 1) / (userinputbasic.frequency[pstate] * 2);

		txdqsdlytg_9to6 = (int)(((int)((txdqsdlytg_coarse_default * uifs) / 1000) +
					 timings.tstaoff[pstate] + timings.tcasl_add[pstate]
					 - timings.tpdm[pstate]) / (int)(uifs / 1000));

		tmp_value = fmodll((txdqsdlytg_fine_default * uifs / 32 +
				    ((timings.tstaoff[pstate] +	timings.tcasl_add[pstate]) * 1000) -
				    (timings.tpdm[pstate] * 1000)), uifs);
		txdqsdlytg_5to0 = (int)(tmp_value / uifs * 32);
		if ((tmp_value % uifs) != 0) {
			txdqsdlytg_5to0++;
		}

		/* Bit-5 of LCDL is no longer used, so bumping bit-5 of fine_dly up to coarse_dly */
		if (txdqsdlytg_5to0 >= 32) {
			txdqsdlytg_9to6 = txdqsdlytg_9to6 + 1;
			txdqsdlytg_5to0 = txdqsdlytg_5to0 - 32;
		}

		txdqsdly[pstate] = (uint16_t)((txdqsdlytg_9to6 << 6) | txdqsdlytg_5to0);

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int nibble;

			c_addr = byte << 12;
			for (nibble = 0; nibble < 2; nibble++) {
				int u_addr;

				if (ddrphy_phyinit_isdbytedisabled(byte)) {
					continue;
				}

				u_addr = nibble << 8;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
				if ((mb_ddr_1d[pstate].cspresent & 0x1) >> 0) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_TXDQSDLYTG0_ADDR)),
						      txdqsdly[pstate]);
				}
#elif STM32MP_LPDDR4_TYPE
				if (((mb_ddr_1d[pstate].cspresentcha & 0x1) >> 0) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x1) >> 0)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_TXDQSDLYTG0_ADDR)),
						      txdqsdly[pstate]);
				}

				if (((mb_ddr_1d[pstate].cspresentcha & 0x2) >> 1) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x2) >> 1)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_TXDQSDLYTG1_ADDR)),
						      txdqsdly[pstate]);
				}
#endif /* STM32MP_LPDDR4_TYPE */
			}
		}
	}
}

/*
 * ##############################################################
 *
 * Program txdqdlyTg0/1[8:0] per P-state:
 *
 *     txdqdlyTg*[8:6] = floor( (txdqsdlytg*[5:0]*UI/32 + tDQS2DQ + 0.5UI) / UI)
 *     txdqdlyTg*[5:0] = ceil( ((txdqsdlytg*[5:0]*UI/32 + tDQS2DQ + 0.5UI)%UI / UI) * 32)
 *
 * ##############################################################
 */
static void txdqdlytg_program(uint16_t *txdqsdly)
{
	int pstate;

	/* ### Set per p-state ### // */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int p_addr;
		int txdqdly_5to0; /* Fine delay - 1/32UI per increment */
		int txdqdly_8to6; /* Coarse delay - 1UI per increment */
		int txdqsdlytg_5to0; /* Fine delay - 1/32UI per increment */
		long long tmp_value;
		long long uifs;
		uint16_t txdqdly;

		p_addr = pstate << 20;

		uifs = (1000 * 1000000 * 1) / (userinputbasic.frequency[pstate] * 2);

		txdqsdlytg_5to0 = (int)txdqsdly[pstate] & 0x3f;

		txdqdly_8to6 = (int)(((txdqsdlytg_5to0 * uifs / 32) + (uifs / 2)) / uifs);
		tmp_value = fmodll(((txdqsdlytg_5to0 * uifs / 32) + (uifs / 2)), uifs);
		txdqdly_5to0 = (int)(((tmp_value * 32) / uifs));
		if ((tmp_value % uifs) != 0) {
			txdqdly_5to0++;
		}

		/* Bit-5 of LCDL is no longer used, so bumping bit-5 of fine_dly up to coarse_dly */
		if (txdqdly_5to0 >= 32) {
			txdqdly_8to6 = txdqdly_8to6 + 1;
			txdqdly_5to0 = txdqdly_5to0 - 32;
		}

		txdqdly = (uint16_t)((txdqdly_8to6 << 6) | txdqdly_5to0);

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int lane;

			c_addr = byte << 12;
			for (lane = 0; lane < 9; lane++) {
				int r_addr;

				if (ddrphy_phyinit_isdbytedisabled(byte)) {
					continue;
				}

				r_addr = lane << 8;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
				if ((mb_ddr_1d[pstate].cspresent & 0x1) >> 0) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      r_addr |
									CSR_TXDQDLYTG0_ADDR)),
						      txdqdly);
				}
#elif STM32MP_LPDDR4_TYPE
				if (((mb_ddr_1d[pstate].cspresentcha & 0x1) >> 0) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x1) >> 0)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      r_addr |
									CSR_TXDQDLYTG0_ADDR)),
						      txdqdly);
				}

				if (((mb_ddr_1d[pstate].cspresentcha & 0x2) >> 1) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x2) >> 1)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      r_addr |
									CSR_TXDQDLYTG1_ADDR)),
						      txdqdly);
				}
#endif /* STM32MP_LPDDR4_TYPE */
			}
		}
	}
}

/*
 * Program rxendly0/1[10:0] per P-State:
 *
 *         rxendly[10:6] = floor( (4*UI + tDQSCK + tstaoff) / UI)
 *         rxendly[5:0]  = ceil( ((tDQSCK + tstaoff) % UI) * 32)
 *
 * tDQSCK, tstaoff and UI expressed in ps
 */
static void rxendly_program(__attribute__((unused))bool skip_train)
{
	int pstate;


	int rxendly_coarse_default = 4;
	int rxendly_fine_default = 0;

	/* ### Set per p-state ### // */
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int backoff_x1000 __attribute__((unused));
		int zerobackoff_x1000 __attribute__((unused));
		int byte;
		int p_addr;
		int rxendly_10to6; /* Coarse delay - 1UI per increment */
		int rxendly_5to0; /* Fine delay - 1/32UI per increment */
		int totfinestep;
		long long finestepfs; /* fine steps in fs */
		long long rxendly_offset_x1000000 = 0; /* 0 offset is 1UI before the first DQS. */
		long long totfs;
		long long uifs;
		uint16_t rxendly;

		p_addr = pstate << 20;

		uifs = (1000 * 1000000 * 1) / (userinputbasic.frequency[pstate] * 2);

#if STM32MP_LPDDR4_TYPE
		/* Compensate for pptenrxenbackoff */
		zerobackoff_x1000 = (1000 * 24) / 32;
		if (userinputadvanced.lp4rxpreamblemode[pstate] == 1) {
			backoff_x1000 = (1000 * 1) - ((1000 * 2) / 32);
		} else {
			backoff_x1000 = (1000 * userinputadvanced.rxenbackoff) - ((1000 * 2) / 32);
		}

		if (skip_train && !userinputadvanced.disableretraining) {
			rxendly_offset_x1000000 = userinputbasic.frequency[pstate] < 333 ?
						  backoff_x1000 * uifs : zerobackoff_x1000 * uifs;
		} else if (skip_train && userinputadvanced.disableretraining) {
			rxendly_offset_x1000000 = zerobackoff_x1000 * uifs;
		}
#endif /* STM32MP_LPDDR4_TYPE */

		finestepfs = uifs / 32;
		totfs = ((32 * rxendly_coarse_default * finestepfs) +
			 (rxendly_fine_default * finestepfs) +
			 ((timings.tstaoff[pstate] + timings.tcasl_add[pstate] +
			   timings.tpdm[pstate]) * 1000) + (rxendly_offset_x1000000 / 1000));
		totfinestep = totfs / finestepfs;

		rxendly_10to6 = totfinestep / 32;
		rxendly_5to0  = fmodi(totfinestep, 32);

		/* Bit-5 of LCDL is no longer used, so bumping bit-5 of fine_dly up to coarse_dly */
		if (rxendly_5to0 >= 32) {
			rxendly_10to6 = rxendly_10to6 + 1;
			rxendly_5to0 = rxendly_5to0 - 32;
		}

		rxendly = (uint16_t)((rxendly_10to6 << 6) | rxendly_5to0);

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int nibble;

			c_addr = byte << 12;
			for (nibble = 0; nibble < 2; nibble++) {
				int u_addr;

				if (ddrphy_phyinit_isdbytedisabled(byte)) {
					continue;
				}

				u_addr = nibble << 8;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
				if ((mb_ddr_1d[pstate].cspresent & 0x1) >> 0) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_RXENDLYTG0_ADDR)),
						      rxendly);
				}
#elif STM32MP_LPDDR4_TYPE
				if (((mb_ddr_1d[pstate].cspresentcha & 0x1) >> 0) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x1) >> 0)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_RXENDLYTG0_ADDR)),
						      rxendly);
				}

				if (((mb_ddr_1d[pstate].cspresentcha & 0x2) >> 1) |
				    ((mb_ddr_1d[pstate].cspresentchb & 0x2) >> 1)) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
										      u_addr |
									CSR_RXENDLYTG1_ADDR)),
						      rxendly);
				}
#endif /* STM32MP_LPDDR4_TYPE */
			}
		}
	}
}

#if STM32MP_LPDDR4_TYPE
/*
 * Programming Seq0BGPR1/2/3 for LPDDR4
 */
static void seq0bgpr_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) { /* for each p_addr */
		int extradly;
		int rl = 0; /* computed read latency */
		int wl = 0; /* computed write latency */
		uint16_t mr_dbi_rd; /* extracted field from MR */
		uint16_t mr_rl;
		uint16_t mr_wl;
		uint16_t mr_wls;
		uint16_t regdata;
		unsigned int p;

		extradly = 3; /* LPDDR4 */

		switch (pstate) {
		case 0:
			p = P0;
			break;
		case 1:
			p = P1;
			break;
		case 2:
			p = P2;
			break;
		case 3:
			p = P3;
			break;
		default:
			p = P0;
			break;
		}

		mr_rl = (uint16_t)userinputadvanced.lp4rl[pstate];	/* RL[2:0] */
		mr_wl = (uint16_t)userinputadvanced.lp4wl[pstate];	/* WL[5:3] */
		mr_wls = (uint16_t)userinputadvanced.lp4wls[pstate];	/* WLS */
		mr_dbi_rd = (uint16_t)userinputadvanced.lp4dbird[pstate]; /* DBI-RD */

		switch (mr_dbi_rd << 3 | mr_rl) {
		/* DBI-RD Disabled */
		case  0U:
			rl = 6;
			break;
		case  1U:
			rl = 10;
			break;
		case  2U:
			rl = 14;
			break;
		case  3U:
			rl = 20;
			break;
		case  4U:
			rl = 24;
			break;
		case  5U:
			rl = 28;
			break;
		case  6U:
			rl = 32;
			break;
		case  7U:
			rl = 36;
			break;
		/* DBI-RD Enabled */
		case  8U:
			rl = 6;
			break;
		case  9U:
			rl = 12;
			break;
		case 10U:
			rl = 16;
			break;
		case 11U:
			rl = 22;
			break;
		case 12U:
			rl = 28;
			break;
		case 13U:
			rl = 32;
			break;
		case 14U:
			rl = 36;
			break;
		case 15U:
			rl = 40;
			break;
		default:
			rl = 6;
			break;
		}

		switch (mr_wls << 3 | mr_wl) {
		/* DBI-RD Disabled */
		case  0U:
			wl = 4;
			break;
		case  1U:
			wl = 6;
			break;
		case  2U:
			wl = 8;
			break;
		case  3U:
			wl = 10;
			break;
		case  4U:
			wl = 12;
			break;
		case  5U:
			wl = 14;
			break;
		case  6U:
			wl = 16;
			break;
		case  7U:
			wl = 18;
			break;
		/* DBI-RD Enabled */
		case  8U:
			wl = 4;
			break;
		case  9U:
			wl = 8;
			break;
		case 10U:
			wl = 12;
			break;
		case 11U:
			wl = 18;
			break;
		case 12U:
			wl = 22;
			break;
		case 13U:
			wl = 26;
			break;
		case 14U:
			wl = 30;
			break;
		case 15U:
			wl = 34;
			break;
		default:
			wl = 4;
			break;
		}


		/* Program Seq0b_GPRx */
		regdata = (uint16_t)((rl - 5 + extradly) << CSR_ACSMRCASLAT_LSB);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p | C0 | TINITENG | R2 |
							      CSR_SEQ0BGPR1_ADDR)), regdata);

		regdata = (uint16_t)((wl - 5 + extradly) << CSR_ACSMWCASLAT_LSB);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p | C0 | TINITENG | R2 |
							      CSR_SEQ0BGPR2_ADDR)), regdata);

		regdata = (uint16_t)((rl - 5 + extradly + 4 + 8) << CSR_ACSMRCASLAT_LSB);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p | C0 | TINITENG | R2 |
							      CSR_SEQ0BGPR3_ADDR)), regdata);
	} /* for each p_addr */
}

/*
 * Program hwtlpcsena and hwtlpcsenb based on number of ranks per channel
 * Applicable only for LPDDR4.  These CSRs have no effect
 * for DDR3/4
 *
 * CSRs to program:
 *      hwtlpcsena
 *      hwtlpcsenb
 *
 * User input dependencies:
 *      dramtype
 *      dfi1exists
 *      numrank_dfi0
 *      numrank_dfi1
 */
static void hwtlpcsen_program(void)
{
	uint16_t hwtlpcsena;
	uint16_t hwtlpcsenb;

	/* Channel A - 1'b01 if signal-rank, 2'b11 if dual-rank */
	hwtlpcsena = (uint16_t)userinputbasic.numrank_dfi0 | 0x1U;
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_HWTLPCSENA_ADDR)), hwtlpcsena);

	/*
	 * Channel B - 1'b01 if signal-rank, 2'b11 if dual-rank
	 * If DFI1 exists but disabled, numrank_dfi0 is used to program CsEnB
	 */
	if (userinputbasic.dfi1exists == 1 && userinputbasic.numactivedbytedfi1 == 0) {
		hwtlpcsenb = (uint16_t)userinputbasic.numrank_dfi0 | 0x1U;
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_HWTLPCSENB_ADDR)),
			      hwtlpcsenb);
	} else if (userinputbasic.dfi1exists == 1 && userinputbasic.numactivedbytedfi1 > 0) {
		hwtlpcsenb = (uint16_t)userinputbasic.numrank_dfi1 | 0x1U;
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_HWTLPCSENB_ADDR)),
			      hwtlpcsenb);
	} else { /* Disable Channel B */
		hwtlpcsenb = 0x0U;
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_HWTLPCSENB_ADDR)),
			      hwtlpcsenb);
	}
}

/*
 * Program pptdqscntinvtrntg0 and pptdqscntinvtrntg1
 * Calculated based on tDQS2DQ and Frequencey
 * Applicable to LPDDR4 only
 *
 * 65536*(tdqs2dq_value_rank<rank>_chan<chan>*2)/(2*2048*UI(ps)_int)
 *
 * CSRs to program:
 *      pptdqscntinvtrntg0
 *      pptdqscntinvtrntg1
 *
 * User input dependencies:
 *      tDQS2DQ
 *      frequency
 */
static void pptdqscntinvtrntg_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		int numrank_total;
		int rank;

		/* Calculate total number of timing groups (ranks) */
		numrank_total = userinputbasic.numrank_dfi0 +
				userinputbasic.numrank_dfi1 * userinputbasic.dfi1exists;

		p_addr = pstate << 20;

		/* ### Set per timing group ### // */
		for (rank = 0; rank < numrank_total; rank++) {
			int byte;
			uint16_t pptdqscntinvtrntg0;
			uint16_t pptdqscntinvtrntg1;

			switch (rank) {
			case 0:
				pptdqscntinvtrntg0 = 0U;
				break;
			case 1:
				pptdqscntinvtrntg1 = 0U;
				break;
			}

			for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
				int c_addr;

				c_addr = byte << 12;
				if (rank == 0) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
								CSR_PPTDQSCNTINVTRNTG0_ADDR)),
						      pptdqscntinvtrntg0);
				} else if (rank == 1) {
					mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr |
										      TDBYTE |
										      c_addr |
								CSR_PPTDQSCNTINVTRNTG1_ADDR)),
						      pptdqscntinvtrntg1);
				}
			}
		}
	}
}

/*
 * CSRs to program:
 *      PptCtlStatic:: DOCByteSelTg0/1
 *                   :: pptenrxenbackoff
 *
 * User input dependencies::
 *      dramtype
 *      dramdatawidth
 * Sim dependencies::
 *      DramByteSwap
 */
static void pptctlstatic_program(void)
{
	int byte;
	int pptenrxenbackoff;

	/*
	 * The customer will setup some fields in this csr so the fw needs to do a
	 * read-modify-write here.
	 */

	if (userinputadvanced.lp4rxpreamblemode[0] == 1) { /* Rx-preamble mode for PS0 */
		/* Programming PptCtlStatic detected toggling preamble */
		pptenrxenbackoff = 0x1; /* toggling RD_PRE */
	} else {
		pptenrxenbackoff = userinputadvanced.rxenbackoff; /* static RD_PRE */
	}

	for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
		int c_addr;
		uint16_t regdata;
		uint8_t pptentg1;
		unsigned int docbytetg0;
		unsigned int docbytetg1;

		/* Each Dbyte could have a different configuration. */
		c_addr = byte * C1;
		if (byte % 2 == 0) {
			docbytetg0 = 0x1U & (unsigned int)(userinputadvanced.drambyteswap >> byte);
			docbytetg1 = 0x1U & (unsigned int)(userinputadvanced.drambyteswap >> byte);
		} else {
			docbytetg0 = 0x1U &
				     (unsigned int)(~(userinputadvanced.drambyteswap >> byte));
			docbytetg1 = 0x1U &
				     (unsigned int)(~(userinputadvanced.drambyteswap >> byte));
		}

		pptentg1 = ((userinputbasic.numrank_dfi0 == 2) ||
			    (userinputbasic.numrank_dfi1 == 2)) ? 0x1U : 0x0U;
		regdata = (uint16_t)(0x1U << CSR_PPTENDQS2DQTG0_LSB |
				     pptentg1 << CSR_PPTENDQS2DQTG1_LSB |
				     0x1U << CSR_PPTENRXENDLYTG0_LSB |
				     pptentg1 << CSR_PPTENRXENDLYTG1_LSB |
				     pptenrxenbackoff << CSR_PPTENRXENBACKOFF_LSB |
				     docbytetg0 << CSR_DOCBYTESELTG0_LSB |
				     docbytetg1 << CSR_DOCBYTESELTG1_LSB);

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE |
							      CSR_PPTCTLSTATIC_ADDR)), regdata);
	}
}
#endif /* STM32MP_LPDDR4_TYPE */

/*
 * Program hwtcamode based on dram type
 *
 * CSRs to program:
 *      hwtcamode::hwtlp3camode
 *               ::hwtd4camode
 *               ::hwtlp4camode
 *               ::hwtd4altcamode
 *               ::hwtcsinvert
 *               ::hwtdbiinvert
 *
 * User input dependencies::
 *      dramtype
 */
static void hwtcamode_program(void)
{
	int hwtlp3camode = 0;
	int hwtd4camode = 0;
	int hwtlp4camode = 0;
	int hwtd4altcamode = 0;
	int hwtcsinvert = 0;
	int hwtdbiinvert = 0;
	uint16_t hwtcamode;

#if STM32MP_DDR4_TYPE
	hwtd4camode = 1;
#elif STM32MP_LPDDR4_TYPE
	hwtlp4camode = 1;
	hwtcsinvert = 1;
	hwtdbiinvert = 1;
#endif /* STM32MP_LPDDR4_TYPE */

	hwtcamode = (uint16_t)((hwtdbiinvert << CSR_HWTDBIINVERT_LSB) |
			       (hwtcsinvert << CSR_HWTCSINVERT_LSB) |
			       (hwtd4altcamode << CSR_HWTD4ALTCAMODE_LSB) |
			       (hwtlp4camode << CSR_HWTLP4CAMODE_LSB) |
			       (hwtd4camode << CSR_HWTD4CAMODE_LSB) |
			       (hwtlp3camode << CSR_HWTLP3CAMODE_LSB));

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_HWTCAMODE_ADDR)), hwtcamode);
}

/*
 * Program DllGainCtl and DllLockParam based on frequency
 */
static void dllgainctl_dlllockparam_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int dllgainiv;
		int dllgaintv;
		int lcdlseed;
		int memck_freq;
		int p_addr;
		int stepsize_x10 = 47;	/*
					 * Nominal stepsize, in units of tenths of a ps,
					 * if nominal=4.7ps use 47
					 */
		uint16_t wddllgainctl;
		uint16_t wddlllockparam;

		memck_freq = userinputbasic.frequency[pstate];
		/*
		 * lcdlseed = ((1000000/memck_freq)/2)/lcdl_stepsize  ...
		 * where default lcdl_stepsize=4.7  in simulation
		 */
		p_addr = pstate << 20;

		dllgainiv = 0x00;
		dllgaintv = 0x02;

		if (memck_freq >= 332) {
			dllgainiv = 0x01;
			dllgaintv = 0x03;
		}
		if (memck_freq >= 532) {
			dllgainiv = 0x02;
			dllgaintv = 0x04;
		}
		if (memck_freq >= 800) {
			dllgainiv = 0x03;
			dllgaintv = 0x05;
		}
		if (memck_freq >= 1200) {
			dllgainiv = 0x04;
			dllgaintv = 0x05;
		}

		/*
		 * lcdlseed= (1000000/(2*memck_freq)) * (100/(120*(stepsize_nominal)));
		 * *100/105 is to bias the seed low
		 */
		lcdlseed = (1000000 * 10 * 100) / (2 * memck_freq * stepsize_x10 * 105);

		if (lcdlseed > 511 - 32) {
			lcdlseed = 511 - 32;
		}

		if (lcdlseed < 32) {
			lcdlseed = 32;
		}

		wddllgainctl = (uint16_t)((CSR_DLLSEEDSEL_MASK & 0x0000U) |
					  (CSR_DLLGAINTV_MASK & (dllgaintv << CSR_DLLGAINTV_LSB)) |
					  (CSR_DLLGAINIV_MASK & (dllgainiv << CSR_DLLGAINIV_LSB)));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DLLGAINCTL_ADDR)), wddllgainctl);


		wddlllockparam = (uint16_t)((CSR_LCDLSEED0_MASK & (lcdlseed << CSR_LCDLSEED0_LSB)) |
					    (CSR_DISDLLGAINIVSEED_MASK & 0xFFFFU) |
					    (CSR_DISDLLSEEDSEL_MASK & 0x0000U));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DLLLOCKPARAM_ADDR)),
			      wddlllockparam);
	}
}

/*
 * Program AcsmCtrl23 for Fw and Ppt.
 *
 * CSRs to program:
 *   AcsmCtrl23::AcsmCsMask
 *               AcsmCsMode
 */
static void acsmctrl23_program(void)
{
	uint16_t regdata;

	regdata = (0x0FU << CSR_ACSMCSMASK_LSB | 0x1U << CSR_ACSMCSMODE_LSB);
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (C0 | TACSM | CSR_ACSMCTRL23_ADDR)), regdata);
}

/*
 * Set PllForceCal to 1 and PllDacValIn to some arbitrary value
 */
static void pllforcecal_plldacvalin_program(void)
{
	int dacval_in = 0x10;
	int force_cal = 0x1;
	int pllencal = 0x1;
	int maxrange = 0x1f;
	int pstate;
	uint16_t pllctrl3_gpr;
	uint16_t pllctrl3_startup;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr = pstate << 20;

		/* Just to test */
		switch (pstate) {
		case 0:
			dacval_in = 0x10;
			break;
		case 1:
			dacval_in = 0x11;
			break;
		case 2:
			dacval_in = 0x12;
			break;
		case 3:
			dacval_in = 0x13;
			break;
		default:
			dacval_in = 0x14;
			break;
		}

		pllctrl3_startup = (uint16_t)((dacval_in << CSR_PLLDACVALIN_LSB) |
					      (maxrange << CSR_PLLMAXRANGE_LSB));
		pllctrl3_gpr = pllctrl3_startup |
			       (uint16_t)((force_cal << CSR_PLLFORCECAL_LSB) |
					  (pllencal << CSR_PLLENCAL_LSB));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_PLLCTRL3_ADDR)),
			      pllctrl3_startup);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TINITENG |
							      CSR_SEQ0BGPR6_ADDR)), pllctrl3_gpr);
	}
}

/*
 * This function programs registers that are normally set by training
 * firmware.
 *
 * This function is used in lieu of running 1D or 1D training steps. PhyInit
 * calls this function when skip_train = true. In that case, PhyInit does not
 * execute training firmware and this function is called instead to program
 * PHY registers according to DRAM timing parameters specified in userInputSim
 * data structure. See documentation of ddrphy_phyinit_struct.h file
 * details of timing parameters available in skip training.
 *
 * \warning ddrphy_phyinit_progcsrskiptrain() only supports zero board
 * delay model. If system board delays are set or randomized, full 1D or 1D
 * initialization flow must be executed.
 *
 * This function replaces these steps in the PHY Initialization sequence:
 *  - (E) Set the PHY input clocks to the desired frequency
 *  - (F) Write the Message Block parameters for the training firmware
 *  - (G) Execute the Training Firmware
 *  - (H) Read the Message Block results
 *
 * \returns \c void
 */
void ddrphy_phyinit_progcsrskiptrain(bool skip_train)
{
	uint16_t txdqsdly[NB_PS] = { };

	VERBOSE("%s Start\n", __func__);

	set_timings();

	/*
	 * Program ATxDlY
	 * For DDR4, DDR3 and LPDDR4, leave AtxDly[6:0] at default (0x0)
	 */

	dfimrl_program();

	txdqsdlytg_program(txdqsdly);

	txdqdlytg_program(txdqsdly);

	rxendly_program(skip_train);

#if STM32MP_LPDDR4_TYPE
	seq0bgpr_program();

	hwtlpcsen_program();

	pptdqscntinvtrntg_program();

	pptctlstatic_program();
#endif /* STM32MP_LPDDR4_TYPE */

	hwtcamode_program();

	dllgainctl_dlllockparam_program();

	acsmctrl23_program();

	pllforcecal_plldacvalin_program();

	/*
	 * ##############################################################
	 *
	 * Setting PhyInLP3 to 0 to cause PIE to execute LP2 sequence instead of INIT on first
	 * dfi_init_start.
	 * This prevents any DRAM commands before DRAM is initialized, which is the case for
	 * skip_train.
	 *
	 * Moved to here from dddrphy_phyinit_I_loadPIEImage()
	 * These should not be needed on S3-exit
	 *
	 * Note this executes for SkipTrain only, *not* DevInit+SkipTrain
	 * DevInit+SkipTrain already initializes DRAM and thus don't need to avoid DRAM commands
	 *
	 * ##############################################################
	 */
	if (skip_train) {
		/*
		 * Special skipTraining configuration to Prevent DRAM Commands on the first dfi
		 * status interface handshake. In order to see this behavior, the first dfi_freq
		 * should be in the range of 0x0f < dfi_freq_sel[4:0] < 0x14.
		 */
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TINITENG | CSR_PHYINLP3_ADDR)), 0x0U);
	}

	VERBOSE("%s End\n", __func__);
}
