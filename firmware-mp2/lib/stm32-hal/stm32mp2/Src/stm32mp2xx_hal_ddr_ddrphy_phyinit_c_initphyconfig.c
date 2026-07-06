/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>

#include "stm32mp2xx_hal.h"
#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"
#include "stm32mp2xx_hal_ddr_ddrphy_wrapper.h"

/*
 * Program txslewrate:
 * - txslewrate::txpredrvmode is dependent on dramtype.
 * - txslewrate::txprep and txslewrate::txpren are technology-specific.
 *   User should consult the "Output Slew Rate" section of HSpice Model App Note in specific
 *   technology for recommended settings.
 */
static void txslewrate_program(void)
{
	int pstate;
	int txpredrvmode;

#if STM32MP_DDR3_TYPE
	txpredrvmode = 0x3;
#elif STM32MP_DDR4_TYPE
	txpredrvmode = 0x2;
#elif STM32MP_LPDDR4_TYPE
	txpredrvmode = 0x1;
#endif /* STM32MP_LPDDR4_TYPE */

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int p_addr;
		int txpren; /* Default to 0xf (max). Optimal setting is technology specific. */
		int txprep; /* Default to 0xf (max). Optimal setting is technology specific. */
		uint16_t txslewrate;

		p_addr = pstate << 20;

		txprep = userinputadvanced.txslewrisedq[pstate];
		txpren = userinputadvanced.txslewfalldq[pstate];

		txslewrate = (uint16_t)((txpredrvmode << CSR_TXPREDRVMODE_LSB) |
					(txpren << CSR_TXPREN_LSB) |
					(txprep << CSR_TXPREP_LSB));

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int lane;

			c_addr = byte << 12;
			for (lane = 0; lane <= B_MAX; lane++) {
				int b_addr;

				b_addr = lane << 8;
				mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TDBYTE |
									      c_addr | b_addr |
									      CSR_TXSLEWRATE_ADDR)),
					      txslewrate);
			}
		}
	}
}

/*
 * Program atxslewrate:
 * - atxslewrate::atxpredrvmode is dependent on dramtype and whether
 *   the ACX4 instance is used for AC or CK
 * - atxslewrate::atxprep and atxslewrate::atxpren are technology-specific
 *   User should consult the "Output Slew Rate" section of
 *   HSpice Model App Note in specific technology for recommended settings
 */
static void atxslewrate_program(void)
{
	int anib;
	int atxpren; /* Default to 0xf (max). Optimal setting is technology specific. */
	int atxprep; /* Default to 0xf (max). Optimal setting is technology specific. */
	int ck_anib_inst[2];

	atxprep = userinputadvanced.txslewriseac;
	atxpren = userinputadvanced.txslewfallac;

	/*
	 * # of ANIBs      CK ANIB Instance
	 * ACX8            ANIB 1
	 */
	if (userinputbasic.numanib == 8) {
		ck_anib_inst[0] = 1;
		ck_anib_inst[1] = 1;
	}

	for (anib = 0; anib < userinputbasic.numanib; anib++) {
		int atxpredrvmode;
		int c_addr;
		uint16_t atxslewrate;

		c_addr = anib << 12;

		if (anib == ck_anib_inst[0] || anib == ck_anib_inst[1]) { /* CK ANIB instance */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
			atxpredrvmode = 0x0;
#elif STM32MP_LPDDR4_TYPE
			atxpredrvmode = 0x1;
#endif /* STM32MP_LPDDR4_TYPE */
		} else { /* non-CK ANIB instance */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
			atxpredrvmode = 0x3;
#elif STM32MP_LPDDR4_TYPE
			atxpredrvmode = 0x1;
#endif /* STM32MP_LPDDR4_TYPE */
		}

		atxslewrate = (uint16_t)((atxpredrvmode << CSR_ATXPREDRVMODE_LSB) |
					 (atxpren << CSR_ATXPREN_LSB) |
					 (atxprep << CSR_ATXPREP_LSB));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TANIB | c_addr |
							      CSR_ATXSLEWRATE_ADDR)),
					  atxslewrate);
	}
}

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
/*
 * Program dfirddatacsdestmap and dfiwrdatacsdestmap
 * - Dependencies: mb_ddr_1d[0].msgmisc[6] Determine Partial Rank Support
 */
static void dfidatacsdestmap_program(void)
{

	if ((mb_ddr_1d[0].msgmisc & 0x40) != 0) {
		int pstate;
		uint16_t dfirddatacsdestmap = 0xA0U;
		uint16_t dfiwrdatacsdestmap = 0xA0U;

		for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
			int p_addr;

			p_addr = pstate << 20;

			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
								      CSR_DFIRDDATACSDESTMAP_ADDR)),
				      dfirddatacsdestmap);
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
								      CSR_DFIWRDATACSDESTMAP_ADDR)),
				      dfiwrdatacsdestmap);
		}
	}
}
#endif /* STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE */

/*
 * Program pllctrl2:
 * - Calculate PLL controls per p-state from frequency
 */
static void pllctrl2_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		uint16_t pllctrl2;

		p_addr = pstate << 20;

		if (userinputbasic.frequency[pstate] / 2 < 235) {
			pllctrl2 = 0x7U;
		} else if (userinputbasic.frequency[pstate] / 2 < 313) {
			pllctrl2 = 0x6U;
		} else if (userinputbasic.frequency[pstate] / 2 < 469) {
			pllctrl2 = 0xBU;
		} else if (userinputbasic.frequency[pstate] / 2 < 625) {
			pllctrl2 = 0xAU;
		} else if (userinputbasic.frequency[pstate] / 2 < 938) {
			pllctrl2 = 0x19U;
		} else if (userinputbasic.frequency[pstate] / 2 < 1067) {
			pllctrl2 = 0x18U;
		} else {
			pllctrl2 = 0x19U;
		}

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_PLLCTRL2_ADDR)),
			      pllctrl2);
	}
}

/*
 * Program ardptrinitval:
 * - The values programmed here assume ideal properties of DfiClk and Pclk including:
 *   - DfiClk skew
 *   - DfiClk jitter
 *   - DfiClk PVT variations
 *   - Pclk skew
 *   - Pclk jitter
 *
 * ardptrinitval Programmed differently based on PLL Bypass mode and frequency:
 * - PLL Bypassed mode:
 *   - For MemClk frequency > 933MHz, the valid range of ardptrinitval_p0[3:0] is: 2-5
 *   - For MemClk frequency < 933MHz, the valid range of ardptrinitval_p0[3:0] is: 1-5
 * - PLL Enabled mode:
 *   - For MemClk frequency > 933MHz, the valid range of ardptrinitval_p0[3:0] is: 1-5
 *   - For MemClk frequency < 933MHz, the valid range of ardptrinitval_p0[3:0] is: 0-5
 */
static void ardptrinitval_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;

		p_addr = pstate << 20;

		if (userinputbasic.frequency[pstate] >= 933) {
			ardptrinitval[pstate] = 0x2;
		} else {
			ardptrinitval[pstate] = 0x1;
		}

		/* Add one UI for synchronizer on SyncBus when PLL is bypassed */
		if (userinputbasic.pllbypass[pstate] == 1) {
			ardptrinitval[pstate]++;
		}

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_ARDPTRINITVAL_ADDR)),
			      (uint16_t)ardptrinitval[pstate]);
	}
}

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
/*
 * Program ProcOdtCtl:
 * - Sets procodtalwayson/procodtalwaysoff for LPDDR4 for 4 different pstates using the PIE
 *   register seq0bgpr4.
 */
static void procodtctl_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		int procodtalwayson;
		int procodtalwaysoff;
		uint16_t seq0bgpr4;

		p_addr = pstate << 20;

		procodtalwaysoff = 0;
		procodtalwayson = 0;

		seq0bgpr4 = (uint16_t)(0x00000000U |
				       (procodtalwayson << CSR_PROCODTALWAYSON_LSB) |
				       (procodtalwaysoff << CSR_PROCODTALWAYSOFF_LSB));
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TINITENG | C0 |
							      CSR_SEQ0BGPR4_ADDR)),
			      seq0bgpr4);
	}
}
#endif /* STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE */

/*
 * Program dbytedllmodecntrl:
 * - dllrxpreamblemode
 * Program dqspreamblecontrol:
 * - Fields:
 *   - twotckrxdqspre
 *   - twotcktxdqspre
 *   - positiondfeinit
 *   - lp4tgltwotcktxdqspre
 *   - lp4postambleext
 *   - lp4sttcprebridgerxen
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_advanced.lp4rxpreamblemode (LPDDR4)
 *   - user_input_advanced.wdqsext (LPDDR4)
 *   - user_input_advanced.d4txpreamblelength (DDR4)
 */
static void dbytedllmodecntrl_program(int *twotckrxdqspre)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int disdllgainivseed = 1;
		int disdllseedsel = 0;
		int dllgainiv = 0x1;
		int dllgaintv = 0x6;
		int dllrxpreamblemode = 0;
		int lcdlseed0 = 0x21;
		int lp4postambleext = 0;
		int lp4sttcprebridgerxen = 0;
		int lp4tgltwotcktxdqspre = 0;
		int p_addr;
		int positiondfeinit;
		int twotcktxdqspre = 0;
		int wdqsextension = 0;
		uint16_t dbytedllmodecntrl;
		uint16_t dllgainctl;
		uint16_t dlllockparam;
		uint16_t dqspreamblecontrol;

		p_addr = pstate << 20;

#if STM32MP_DDR3_TYPE
		/* Same as default */
		twotckrxdqspre[pstate]  = 0x0;
		lp4sttcprebridgerxen    = 0x0;
		dllrxpreamblemode       = 0x0;
		twotcktxdqspre          = 0x0;
		lp4tgltwotcktxdqspre    = 0x0;
		positiondfeinit         = 0x0;
		lp4postambleext         = 0x0;
#elif STM32MP_DDR4_TYPE
		twotckrxdqspre[pstate]  = userinputadvanced.d4rxpreamblelength[pstate];
		lp4sttcprebridgerxen    = 0x0;
		dllrxpreamblemode       = 0x1;
		twotcktxdqspre          = userinputadvanced.d4txpreamblelength[pstate];
		lp4tgltwotcktxdqspre    = 0x0;
		positiondfeinit         = 0x2;
		lp4postambleext         = 0x0;
#elif STM32MP_LPDDR4_TYPE
		/* Set to 1 if static Rx preamble */
		twotckrxdqspre[pstate] = !userinputadvanced.lp4rxpreamblemode[pstate];
		/* Set to 1 if static Rx preamble */
		lp4sttcprebridgerxen = !userinputadvanced.lp4rxpreamblemode[pstate];
		dllrxpreamblemode = 0x1;
		/* Must be 2*Tck Tx preamble according to JEDEC (mr1.OP[2] = 1) */
		twotcktxdqspre = 0x1;
		/* Must be toggling Tx preamble */
		lp4tgltwotcktxdqspre = 0x1;
		positiondfeinit = 0x0;
		lp4postambleext = userinputadvanced.lp4postambleext[pstate];
		wdqsextension = userinputadvanced.wdqsext;
#endif /* STM32MP_LPDDR4_TYPE */

		dqspreamblecontrol = (uint16_t)(
					(wdqsextension << CSR_WDQSEXTENSION_LSB) |
					(lp4sttcprebridgerxen << CSR_LP4STTCPREBRIDGERXEN_LSB) |
					(lp4postambleext << CSR_LP4POSTAMBLEEXT_LSB) |
					(lp4tgltwotcktxdqspre << CSR_LP4TGLTWOTCKTXDQSPRE_LSB) |
					(positiondfeinit << CSR_POSITIONDFEINIT_LSB) |
					(twotcktxdqspre << CSR_TWOTCKTXDQSPRE_LSB) |
					(twotckrxdqspre[pstate] << CSR_TWOTCKRXDQSPRE_LSB));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DQSPREAMBLECONTROL_ADDR)),
			      dqspreamblecontrol);

		dbytedllmodecntrl = (uint16_t)(dllrxpreamblemode << CSR_DLLRXPREAMBLEMODE_LSB);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER |
							      CSR_DBYTEDLLMODECNTRL_ADDR)),
			      dbytedllmodecntrl);

		dllgainctl = (uint16_t)(dllgainiv | (dllgaintv << CSR_DLLGAINTV_LSB));
		dlllockparam = (uint16_t)(disdllseedsel |
					  (disdllgainivseed << CSR_DISDLLGAINIVSEED_LSB) |
					  (lcdlseed0 << CSR_LCDLSEED0_LSB));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DLLLOCKPARAM_ADDR)),
			      dlllockparam);

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DLLGAINCTL_ADDR)),
			      dllgainctl);
	}
}

/*
 * Program procodttimectl:
 * - Fields:
 *   - POdtStartDelay[3:2]
 *   - POdtTailWidth[1:0]
 * - Dependencies:
 *   - user_input_basic.frequency
 *   - user_input_basic.dramtype
 */
static void procodttimectl_program(int *twotckrxdqspre)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		uint16_t procodttimectl;

		p_addr = pstate << 20;

		if (userinputadvanced.wdqsext) {
			/* POdtStartDelay = 0x0 and  POdtTailWidth  = 0x3 */
			procodttimectl = 0x3U;
		} else if (userinputbasic.frequency[pstate] <= 933) {
			/* Memclk Freq <= 933MHz: POdtStartDelay = 0x2 and POdtTailWidth  = 0x2 */
			procodttimectl = 0xAU;
		} else if (userinputbasic.frequency[pstate] <= 1200) {
			/* 933MHz < Memclk Freq <= 1200MHz */
			if (twotckrxdqspre[pstate] == 1) {
				/* POdtStartDelay = 0x0 and  POdtTailWidth  = 0x2 */
				procodttimectl = 0x2U;
			} else {
				/* POdtStartDelay = 0x1 and POdtTailWidth  = 0x2 */
				procodttimectl = 0x6U;
			}
		} else {
			/* Memclk Freq > 1200MHz */
			if (twotckrxdqspre[pstate] == 1) {
				/* POdtStartDelay = 0x0 and POdtTailWidth  = 0x3 */
				procodttimectl = 0x3U;
			} else {
				/* POdtStartDelay = 0x1 and POdtTailWidth  = 0x3 */
				procodttimectl = 0x7U;
			}
		}

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_PROCODTTIMECTL_ADDR)),
			      procodttimectl);
	}
}

/*
 * Program txodtdrvstren:
 * - Fields:
 *   - ODTStrenP_px[5:0]
 *   - ODTStrenN_px[11:6]
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_advanced.odtimpedance
 * \return 0 on success.
 */
static int txodtdrvstren_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int odtstrenn_state;
		int odtstrenp_state;
		int p_addr;
		uint16_t txodtdrvstren;

		p_addr = pstate << 20;

		odtstrenp_state = ddrphy_phyinit_mapdrvstren(
							(int)userinputadvanced.odtimpedance[pstate],
							ODTSTRENP);
		if (odtstrenp_state < 0) {
			return odtstrenp_state;
		}

		odtstrenn_state = ddrphy_phyinit_mapdrvstren(
							(int)userinputadvanced.odtimpedance[pstate],
							ODTSTRENN);
		if (odtstrenn_state < 0) {
			return odtstrenn_state;
		}

		txodtdrvstren = (uint16_t)((odtstrenn_state << CSR_ODTSTRENN_LSB) |
					   odtstrenp_state);

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int lane;

			c_addr = byte << 12;
			for (lane = 0; lane <= B_MAX; lane++) {
				int b_addr;

				b_addr = lane << 8;
				mmio_write_16((uintptr_t)
					      (DDRPHYC_BASE + 4 * (p_addr | TDBYTE | c_addr |
								   b_addr |
								   CSR_TXODTDRVSTREN_ADDR)),
					      txodtdrvstren);
			}
		}
	}

	return 0;
}

/*
 * Program tximpedancectrl1:
 * - Fields:
 *   - DrvStrenFSDqP[5:0]
 *   - DrvStrenFSDqN[11:6]
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_advanced.tximpedance
 * \return 0 on success.
 */
static int tximpedancectrl1_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int byte;
		int drvstrenfsdqn_state;
		int drvstrenfsdqp_state;
		int p_addr;
		uint16_t tximpedancectrl1;

		p_addr = pstate << 20;

		drvstrenfsdqp_state = ddrphy_phyinit_mapdrvstren(
							(int)userinputadvanced.tximpedance[pstate],
							DRVSTRENFSDQP);
		if (drvstrenfsdqp_state < 0) {
			return drvstrenfsdqp_state;
		}

		drvstrenfsdqn_state = ddrphy_phyinit_mapdrvstren(
							(int)userinputadvanced.tximpedance[pstate],
							DRVSTRENFSDQN);
		if (drvstrenfsdqn_state < 0) {
			return drvstrenfsdqn_state;
		}

		tximpedancectrl1 = (uint16_t)((drvstrenfsdqn_state << CSR_DRVSTRENFSDQN_LSB) |
					      (drvstrenfsdqp_state << CSR_DRVSTRENFSDQP_LSB));

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int lane;

			c_addr = byte << 12;
			for (lane = 0; lane <= B_MAX; lane++) {
				int b_addr;

				b_addr = lane << 8;
				mmio_write_16((uintptr_t)
					      (DDRPHYC_BASE + 4 * (p_addr | TDBYTE | c_addr |
								   b_addr |
								   CSR_TXIMPEDANCECTRL1_ADDR)),
					      tximpedancectrl1);
			}
		}
	}

	return 0;
}

/*
 * Program atximpedance:
 * - Fields:
 *   - ADrvStrenP[4:0]
 *   - ADrvStrenN[9:5]
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_advanced.atximpedance
 * \return 0 on success.
 */
static int atximpedance_program(void)
{
	int adrvstrenn_state;
	int adrvstrenp_state;
	int anib;
	uint16_t atximpedance;

	adrvstrenp_state = ddrphy_phyinit_mapdrvstren((int)userinputadvanced.atximpedance,
						      ADRVSTRENP);
	if (adrvstrenp_state < 0) {
		return adrvstrenp_state;
	}

	adrvstrenn_state = ddrphy_phyinit_mapdrvstren((int)userinputadvanced.atximpedance,
						      ADRVSTRENN);
	if (adrvstrenn_state < 0) {
		return adrvstrenn_state;
	}

	atximpedance = (uint16_t)((adrvstrenn_state << CSR_ADRVSTRENN_LSB) |
				  (adrvstrenp_state << CSR_ADRVSTRENP_LSB));

	for (anib = 0; anib < userinputbasic.numanib; anib++) {
		int c_addr;

		c_addr = anib << 12;
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TANIB | c_addr |
							      CSR_ATXIMPEDANCE_ADDR)),
			      atximpedance);
	}

	return 0;
}

/*
 * Program dfimode:
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_basic.dfi1exists
 *   - user_input_basic.numactivedbytedfi0
 *   - user_input_basic.numactivedbytedfi1
 */
static void dfimode_program(void)
{
	uint16_t dfimode;

	if (userinputbasic.dfi1exists == 1) {
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		dfimode = 0x5U; /* DFI1 exists but disabled; DFI0 controls entire PHY */
#elif STM32MP_LPDDR4_TYPE
		if (userinputbasic.numactivedbytedfi1 > 0) {
			dfimode = 0x3U; /* Both DFI0 and DFI1 active */
		} else if (userinputbasic.numactivedbytedfi0 > userinputbasic.numdbyte / 2 &&
			   userinputbasic.numdbyte == 4) {
			dfimode = 0x5U; /* DFI1 exists but disabled; DFI0 controls entire PHY */
		} else {
			dfimode = 0x1U; /* DFI1 exists but disabled; DFI0 controls 1/2 PHY */
		}
#endif /* STM32MP_LPDDR4_TYPE */
	} else {
		dfimode = 0x1U; /* DFI1 does not physically exists */
	}

#if STM32MP_LPDDR4_TYPE
	dfimode = 0x5U;
#endif

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_DFIMODE_ADDR)), dfimode);
}

/*
 * Program dficamode:
 * - Fields:
 *   - DfiLp3CAMode
 *   - DfiD4CAMode
 *   - DfiLp4CAMode
 *   - DfiD4AltCAMode
 * - Dependencies:
 *   - user_input_basic.dramtype
 */
static void dficamode_program(void)
{
	uint16_t dficamode;

#if STM32MP_DDR3_TYPE
	dficamode = 0U;
#elif STM32MP_DDR4_TYPE
	dficamode = 2U;
#elif STM32MP_LPDDR4_TYPE
	dficamode = 4U;
#endif /* STM32MP_LPDDR4_TYPE */

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_DFICAMODE_ADDR)), dficamode);
}

/*
 * Program caldrvstr0:
 * - Fields:
 *   - caldrvstrpd50[3:0]
 *   - caldrvstrpu50[7:4]
 * - Dependencies:
 *   - user_input_advanced.extcalresval
 *   - userinputadvanced.lp4lowpowerdrv (LPDDR4)
 *   - mb_ddr_1d[0].mr3_a0 (LPDDR4)
 */
static void caldrvstr0_program(void)
{
	uint16_t caldrvstr0;
	uint16_t caldrvstrpd50;
	uint16_t caldrvstrpu50;

	caldrvstrpu50 = (uint16_t)userinputadvanced.extcalresval;

	caldrvstrpd50 = caldrvstrpu50;
	caldrvstr0 = (caldrvstrpu50 << CSR_CALDRVSTRPU50_LSB) | caldrvstrpd50;

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_CALDRVSTR0_ADDR)), caldrvstr0);
}

/*
 * Program CalUclkInfo:
 * - Impedance calibration CLK Counter.
 * - Fields:
 *   - caluclkticksper1us
 * - Dependencies:
 *   - user_input_basic.frequency
 */
static void caluclkinfo_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		long long caluclkticksper1us_x10;
		uint16_t caluclkticksper1us;

		p_addr = pstate << 20;

		/* Number of DfiClk cycles per 1us */
		caluclkticksper1us_x10 = (long long)(10 * 1 * userinputbasic.frequency[pstate]) / 2;
		caluclkticksper1us = (uint16_t)(caluclkticksper1us_x10 / 10);

		if (((long long)(userinputbasic.frequency[pstate]) % 2) != 0) {
			caluclkticksper1us++;
		}

		if (caluclkticksper1us < 24U) {
			/* Minimum value of caluclkticksper1us = 24 */
			caluclkticksper1us = 24U;
		}

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_CALUCLKINFO_ADDR)),
			      caluclkticksper1us);
	}
}

/*
 * Program Calibration CSRs based on user input
 *
 * CSRs to program:
 *      calrate: calinterval
 *               calonce
 * User input dependencies:
 *      calinterval
 *      calonce
 */
static void calibration_program(void)
{
	int calinterval;
	int calonce;
	uint16_t calrate;

	calinterval = userinputadvanced.calinterval;
	calonce = userinputadvanced.calonce;

	calrate = (uint16_t)((calonce << CSR_CALONCE_LSB) | (calinterval << CSR_CALINTERVAL_LSB));

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_CALRATE_ADDR)), calrate);
}

/*
 * Program vrefinglobal:
 * - dqdqsrcvcntrl and csrvrefinglobal to select Global VREF
 *   from Master to be used in each DQ
 * - Fields:
 *   - globalvrefinsel: Select Range of GlobalVref DAC. Default: set to 1.
 *   - globalvrefindac: Vref level is set based on mb_ddr_1d[pstate].phyvref value.
 *     The following formula is used to convert the phyvref into the register setting.
 *       \f{eqnarray*}{
 *           PhyVrefPrcnt &=& \frac{mb_ddr_1d[pstate].phyvref}{128} \\
 *        if globalvrefinsel = 1 :
 *           globalvrefindac &=& 1+\frac{PhyVrefPrcnt}{0.005} \\
 *        if globalvrefinsel = 0 :
 *           globalvrefindac &=& \frac{(PhyVrefPrcnt-0.345)}{0.005} \\
 *           RxVref &=& (globalvrefindac == 0) ? Hi-Z : (PhyVrefPrcnt \times VDDQ)
 *        \f}
 * - Dependencies:
 *   - user_input_basic.dramtype
 *
 * Program dqdqsrcvcntrl:
 * - dqdqsrcvcntrl and csrvrefinglobal to select Global VREF
 *   from Master to be used in each DQ
 * - Fields:
 *  - selanalogvref
 *  - majormodedbyte
 *  - ExtVrefRange
 *  - DfeCtrl
 *  - GainCurrAdj
 * - Dependencies:
 *   - user_input_basic.dramtype
 */
static void vrefinglobal_program(void)
{
	int majormodedbyte;
	int pstate;

#if STM32MP_DDR3_TYPE
	majormodedbyte = 0;
#elif STM32MP_DDR4_TYPE
	majormodedbyte = 3;
#elif STM32MP_LPDDR4_TYPE
	majormodedbyte = 2;
#endif /* STM32MP_LPDDR4_TYPE */

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int32_t vref_percentvddq = (mb_ddr_1d[pstate].phyvref) * 1000 * 100 / 128;
		uint8_t globalvrefindac = 0x0;
		uint8_t globalvrefinsel = 0x4;
		int byte;
		int dfectrl_defval = 0;
		int extvrefrange_defval = 0;
		int gaincurradj_defval = 0xb;
		int p_addr;
		int selanalogvref = 1; /* Use Global VREF from Master */
		uint16_t dqdqsrcvcntrl;
		uint16_t vrefinglobal;

		p_addr = pstate << 20;

		/* Check range1 first. Only use range0 if customer input maxes out range1. */
		globalvrefindac = (uint8_t)((vref_percentvddq / 500) + 1); /* Min value is 1 */
		if (globalvrefindac > 127) {
			/* Min value is 1 */
			globalvrefindac = (uint8_t)(MAX((vref_percentvddq - 34500), 500) / 500);
			globalvrefinsel = 0x0;
		}
		globalvrefindac = MIN(globalvrefindac, (uint8_t)127);

		vrefinglobal = (uint16_t)((globalvrefindac << CSR_GLOBALVREFINDAC_LSB) |
					  globalvrefinsel);
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_VREFINGLOBAL_ADDR)),
			      vrefinglobal);

		dqdqsrcvcntrl = (uint16_t)((gaincurradj_defval << CSR_GAINCURRADJ_LSB) |
					   (majormodedbyte << CSR_MAJORMODEDBYTE_LSB) |
					   (dfectrl_defval << CSR_DFECTRL_LSB) |
					   (extvrefrange_defval << CSR_EXTVREFRANGE_LSB) |
					   (selanalogvref << CSR_SELANALOGVREF_LSB));

		for (byte = 0; byte < userinputbasic.numdbyte; byte++) {
			int c_addr;
			int lane;

			c_addr = byte << 12;
			for (lane = 0; lane <= B_MAX; lane++) {
				int b_addr;

				b_addr = lane << 8;
				mmio_write_16((uintptr_t)
					      (DDRPHYC_BASE + 4 * (p_addr | TDBYTE | c_addr |
								   b_addr |
								   CSR_DQDQSRCVCNTRL_ADDR)),
					      dqdqsrcvcntrl);
			}
		}
	}
}

/*
 * Program dfifreqratio :
 * - Dependencies:
 *   - user_input_basic.dfifreqratio
 */
static void dfifreqratio_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		uint16_t dfifreqratio;

		p_addr = pstate << 20;

		dfifreqratio = (uint16_t)userinputbasic.dfifreqratio[pstate];

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DFIFREQRATIO_ADDR)),
			      dfifreqratio);
	}
}

/*
 * Program tristatemodeca based on dramtype and 2T Timing
 * - Fields:
 *   - CkDisVal
 *   - disdynadrtri
 *   - ddr2tmode
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_advanced.is2ttiming
 *   - user_input_advanced.disdynadrtri
 */
static void tristatemodeca_program(void)
{
	int ckdisval_def;
	int pstate;

	/* CkDisVal depends on dramtype */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	ckdisval_def = 1; /* {CLK_t,CLK_c} = 2'b00; */
#elif STM32MP_LPDDR4_TYPE
	ckdisval_def = 0; /* {CLK_t,CLK_c} = 2'b01; */
#endif /* STM32MP_LPDDR4_TYPE */

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int ddr2tmode;
		int disdynadrtri;
		int p_addr;
		uint16_t tristatemodeca;

		p_addr = pstate << 20;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		disdynadrtri = userinputadvanced.disdynadrtri[pstate];
#elif STM32MP_LPDDR4_TYPE
		disdynadrtri = 1;
#endif /* STM32MP_LPDDR4_TYPE */

		ddr2tmode = userinputadvanced.is2ttiming[pstate];

		tristatemodeca = (uint16_t)((ckdisval_def << CSR_CKDISVAL_LSB) |
					    (ddr2tmode << CSR_DDR2TMODE_LSB) |
					    (disdynadrtri << CSR_DISDYNADRTRI_LSB));

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_TRISTATEMODECA_ADDR)),
			      tristatemodeca);
	}
}

/*
 * Program DfiXlat based on Pll Bypass Input
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_basic.pllbypass
 */
static void dfixlat_program(void)
{
	int pstate;
	uint16_t loopvector;
	uint16_t pllbypass_dat = 0U;
	uint16_t skipddc_dat = 0U;	/*
					 * Set to vector offset based on pstate frequency to disable
					 * dram drift compensation.
					 */

	for (pstate = 0; pstate < NB_PS; pstate++) {
		pllbypass_dat |= (uint16_t)(userinputbasic.pllbypass[pstate] << (4 * pstate));

		if (userinputbasic.frequency[pstate] < 333) {
			skipddc_dat |= 0x5U << (4 * pstate);
		}
	}

	for (loopvector = 0U; loopvector < 8U; loopvector++) {
		uint16_t dfifreqxlat_dat;
		uintptr_t reg = (uintptr_t)(DDRPHYC_BASE + 4 * (C0 | TMASTER |
								(CSR_DFIFREQXLAT0_ADDR +
								 loopvector)));

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		if (loopvector == 0U) {
			/*
			 * Relock DfiFreq = 00,01,02,03)  Use StartVec 5 (pll_enabled) or
			 * StartVec 6 (pll_bypassed).
			 */
			dfifreqxlat_dat = pllbypass_dat + 0x5555U;

			mmio_write_16(reg, dfifreqxlat_dat);
		} else if (loopvector == 7U) {
			/* LP3-entry DfiFreq = 1F */
			mmio_write_16(reg, 0xF000U);
		} else {
			/*
			 * Everything else = skip retrain  (could also map to 0000 since retrain
			 * code is excluded, but this is cleaner).
			 */
			mmio_write_16(reg, 0x5555U);
		}
#elif STM32MP_LPDDR4_TYPE
		if (loopvector == 0U) {
			/*
			 * Retrain & Relock DfiFreq = 00,01,02,03)  Use StartVec 0 (pll_enabled) or
			 * StartVec 1 (pll_bypassed).
			 */
			dfifreqxlat_dat = pllbypass_dat + skipddc_dat + 0x0000U;
			mmio_write_16(reg, dfifreqxlat_dat);
		} else if (loopvector == 2U) {
			/*
			 * Retrain only DfiFreq = 08,09,0A,0B)  Use StartVec 4 (1, and maybe 2,3,
			 * used by verif).
			 */
			mmio_write_16(reg, 0x4444U);
		} else if (loopvector == 3U) {
			/* Phymstr type state change, StartVec 8 */
			mmio_write_16(reg, 0x8888U);
		} else if (loopvector == 4U) {
			/*
			 * Relock only DfiFreq = 10,11,12,13   Use StartVec 5 (pll_enabled) or
			 * StartVec 6 (pll_bypassed).
			 */
			dfifreqxlat_dat = pllbypass_dat + 0x5555U;
			mmio_write_16(reg, dfifreqxlat_dat);
		} else if (loopvector == 7U) {
			/* LP3-entry DfiFreq = 1F */
			mmio_write_16(reg, 0xF000U);
		} else {
			/* Everything else */
			mmio_write_16(reg, 0x0000U);
		}
#endif /* STM32MP_LPDDR4_TYPE */
	}
}

/*
 * Program dqdqsrcvcntrl1 (Receiver Powerdown) and DbyteMiscMode
 * - see function ddrphy_phyinit_isdbytedisabled() to determine
 *   which DBytes are turned off completely based on PHY configuration.
 * - Fields:
 *   - DByteDisable
 *   - PowerDownRcvr
 *   - PowerDownRcvrDqs
 *   - RxPadStandbyEn
 * - Dependencies:
 *   - user_input_basic.dramtype
 *   - user_input_basic.dfi1exists
 *   - user_input_basic.numactivedbytedfi0
 *   - user_input_basic.numactivedbytedfi1
 *   - user_input_basic.numdbyte
 *   - user_input_basic.dramdatawidth (DDR3/DDR4)
 *   - mb_ddr_1d[0].mr5 (DDR4)
 *   - user_input_advanced.lp4dbird (LPDDR4)
 */
static void dqdqsrcvcntrl1_program(void)
{
	int lp4dbird __attribute__((unused));
	int pstate __attribute__((unused));
	int d;
	uint16_t mr5 __attribute__((unused));
	uint16_t regdata;
	uint16_t regdata1;
	uint16_t regdata2; /* Turn off Rx of DBI lane */

	regdata = 0x1U << CSR_DBYTEDISABLE_LSB;

	regdata1 = (0x1FFU << CSR_POWERDOWNRCVR_LSB |
		    0x1U << CSR_POWERDOWNRCVRDQS_LSB |
		    0x1U << CSR_RXPADSTANDBYEN_LSB);

	regdata2 = (0x100U << CSR_POWERDOWNRCVR_LSB | CSR_RXPADSTANDBYEN_MASK);

#if STM32MP_DDR4_TYPE
	mr5 = 0U;
#elif STM32MP_LPDDR4_TYPE
	lp4dbird = 0;
#endif /* STM32MP_LPDDR4_TYPE */

#if !STM32MP_DDR3_TYPE
	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
#if STM32MP_DDR4_TYPE
		/* OR all mr4 masked values, to help check in next loop */
		mr5 |= (mb_ddr_1d[pstate].mr5 >> 12) & 0x1U;
#elif STM32MP_LPDDR4_TYPE
		/* OR all Lp4DbiRd values, to help check in next loop */
		lp4dbird |= userinputadvanced.lp4dbird[pstate];
#endif /* STM32MP_LPDDR4_TYPE */
	}
#endif /* !STM32MP_DDR3_TYPE */

	/* Implements Section 1.3 of Pub Databook */
	for (d = 0; d < userinputbasic.numdbyte; d++) { /* For each dbyte */
		int c_addr;

		c_addr = d * C1;
		if (ddrphy_phyinit_isdbytedisabled(d)) {
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE |
								      CSR_DBYTEMISCMODE_ADDR)),
				      regdata);
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (c_addr | TDBYTE |
								      CSR_DQDQSRCVCNTRL1_ADDR)),
				      regdata1);
		} else {
			/* Disable RDBI lane if not used. */
#if STM32MP_DDR3_TYPE
			if ((userinputbasic.dramdatawidth != 4)) {
#elif STM32MP_DDR4_TYPE
			if ((userinputbasic.dramdatawidth != 4) && mr5 == 0U) {
#elif STM32MP_LPDDR4_TYPE
			if (lp4dbird == 0) {
#endif /* STM32MP_LPDDR4_TYPE */
				mmio_write_16((uintptr_t)
					      (DDRPHYC_BASE + 4 * (c_addr | TDBYTE |
								   CSR_DQDQSRCVCNTRL1_ADDR)),
					      regdata2);
			} /* DBI */
		} /* DbyteDisable */
	} /* for each dbyte */
}

/*
 * Program masterx4config
 * - Fields:
 *   - x4tg
 *   - masterx4config
 * - Dependencies:
 *   - user_input_basic.dramdatawidth
 *
 * \note PHY does not support mixed dram device data width
 */
static void masterx4config_program(void)
{
	int x4tg;
	uint16_t masterx4config;

	if (userinputbasic.dramdatawidth == 4) {
		x4tg = 0xF;
	} else {
		x4tg = 0x0;
	}

	masterx4config = (uint16_t)(x4tg << CSR_X4TG_LSB);

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_MASTERX4CONFIG_ADDR)),
		      masterx4config);
}

#if !STM32MP_DDR3_TYPE
/*
 * Program dmipinpresent based on dramtype and Read-DBI enable
 * - Fields:
 *   - RdDbiEnabled
 * - Dependencies:
 *   - user_input_basic.dramdatawidth
 *   - mb_ddr_1d[0].mr5 (DDR4)
 *   - user_input_advanced.lp4dbird (LPDDR4)
 */
static void dmipinpresent_program(void)
{
	int pstate;

	for (pstate = 0; pstate < userinputbasic.numpstates; pstate++) {
		int p_addr;
		uint16_t dmipinpresent;

		p_addr = pstate << 20;

#if STM32MP_DDR4_TYPE
		/* For DDR4, Read DBI is enabled in mr5-A12 */
		dmipinpresent = (mb_ddr_1d[pstate].mr5 >> 12) & 0x1U;
#elif STM32MP_LPDDR4_TYPE
		dmipinpresent = (uint16_t)userinputadvanced.lp4dbird[pstate];
#endif /* STM32MP_LPDDR4_TYPE */

		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (p_addr | TMASTER |
							      CSR_DMIPINPRESENT_ADDR)),
			      dmipinpresent);
	}
}
#endif /* !STM32MP_DDR3_TYPE */

/*
 * Program aforcetricont and acx4anibdis
 * - Fields:
 *   - aforcetricont
 *   - acx4anibdis
 * - Dependencies:
 *   - user_input_basic.numrank_dfi0
 *   - user_input_basic.numrank_dfi1
 *   - user_input_basic.numanib
 *   - user_input_advanced.disableunusedaddrlns
 */
static void aforcetricont_acx4anibdis_program(void)
{
	int anib;
	uint16_t acx4anibdis = 0x0U;

	for (anib = 0;
	     (anib < userinputbasic.numanib) && userinputadvanced.disableunusedaddrlns;
	     anib++) {
		int c_addr;
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		int numrank = userinputbasic.numrank_dfi0 + userinputbasic.numrank_dfi1;
#elif STM32MP_LPDDR4_TYPE
		int numrank0 = userinputbasic.numrank_dfi0;
		int numrank1 = userinputbasic.numrank_dfi1;
#endif /* STM32MP_LPDDR4_TYPE */
		uint16_t aforcetricont = 0x0U;

		c_addr = anib << 12;
		aforcetricont = 0x0U;

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
		if (anib == 0 && numrank == 1) {
			aforcetricont = 0x2U;
		} else if (anib == 1 && numrank == 1) {
			aforcetricont = 0xCU;
		} else if (anib == 6) {
			aforcetricont = 0x1U;
		}
#elif STM32MP_LPDDR4_TYPE
		if (anib == 0 && numrank0 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 0 && numrank0 == 1) {
			aforcetricont = 0x2U;
		} else if (anib == 1 && numrank0 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 1 && numrank0 == 1) {
			aforcetricont = 0x8U;
		} else if (anib == 2 && numrank0 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 3 && numrank1 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 3 && numrank1 == 1) {
			aforcetricont = 0x2U;
		} else if (anib == 4 && numrank1 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 4 && numrank1 == 1) {
			aforcetricont = 0x8U;
		} else if (anib == 5 && numrank1 == 0) {
			aforcetricont = 0xFU;
		} else if (anib == 6) {
			aforcetricont = 0xFU;
		} else if (anib == 7) {
			aforcetricont = 0xFU;
		}
#endif /* STM32MP_LPDDR4_TYPE */

		/*
		 * If all the lanes can be disabled, and Anib is not the first or last disable
		 * entire chiplet
		 */
		if (aforcetricont == 0xFU && anib != 0 && anib != userinputbasic.numanib - 1) {
			acx4anibdis = acx4anibdis | (0x1U << anib);
		}
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TANIB | c_addr |
							      CSR_AFORCETRICONT_ADDR)),
			      aforcetricont);
	}

	mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_ACX4ANIBDIS_ADDR)),
		      acx4anibdis);
}

/*
 * Implements Step C of initialization sequence
 *
 * This function programs majority of PHY configuration registers based
 * on data input into PhyInit data structures.
 *
 * This function programs PHY configuration registers based on information
 * provided in the PhyInit data structures (userinputbasic, userinputadvanced).
 * The user can overwrite the programming of this function by modifying
 * ddrphy_phyinit_usercustom_custompretrain().  Please see
 * ddrphy_phyinit_struct.h for PhyInit data structure definition.
 *
 * \return 0 on success.
 */
int ddrphy_phyinit_c_initphyconfig(void)
{
	int twotckrxdqspre[NB_PS] = { };
	int ret;

	/*
	 * Step (C) Initialize PHY Configuration
	 * Load the required PHY configuration registers for the appropriate mode and memory
	 * configuration.
	 */

	VERBOSE("%s Start\n", __func__);

	txslewrate_program();

	atxslewrate_program();

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	dfidatacsdestmap_program();
#endif /* STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE */

	pllctrl2_program();

	ardptrinitval_program();

#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
	procodtctl_program();
#endif /* STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE */

	dbytedllmodecntrl_program(twotckrxdqspre);

	procodttimectl_program(twotckrxdqspre);

	ret = txodtdrvstren_program();
	if (ret != 0) {
		return ret;
	}

	ret = tximpedancectrl1_program();
	if (ret != 0) {
		return ret;
	}

	ret = atximpedance_program();
	if (ret != 0) {
		return ret;
	}

	dfimode_program();

	dficamode_program();

	caldrvstr0_program();

	caluclkinfo_program();

	calibration_program();

	vrefinglobal_program();

	dfifreqratio_program();

	tristatemodeca_program();

	dfixlat_program();

	dqdqsrcvcntrl1_program();

	masterx4config_program();

#if !STM32MP_DDR3_TYPE
	dmipinpresent_program();

#if STM32MP_LPDDR4_TYPE
	/*
	 * Program DFIPHYUPD
	 * - Fields:
	 *   - DFIPHYUPDMODE
	 *   - DFIPHYUPDCNT
	 * - Dependencies:
	 *   - user_input_advanced.disablephyupdate
	 */
	if (userinputadvanced.disablephyupdate) {
		mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * (TMASTER | CSR_DFIPHYUPD_ADDR)), 0x0U);
	}
#endif /* STM32MP_LPDDR4_TYPE */
#endif /* !STM32MP_DDR3_TYPE */

	aforcetricont_acx4anibdis_program();

	VERBOSE("%s End\n", __func__);

	return 0;
}
