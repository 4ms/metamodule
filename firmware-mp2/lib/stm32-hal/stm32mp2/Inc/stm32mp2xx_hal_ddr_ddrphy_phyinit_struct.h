/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DDRPHY_PHYINIT_STRUCT_H
#define DDRPHY_PHYINIT_STRUCT_H

/*
 * This file defines the internal data structures used in PhyInit to store user configuration.
 *
 * Please see \ref docref to obtain necessary information for program variables
 * correctly for your PHY variant and process technology.
 */

#define NB_PS		1

/* Enumerator for DRAM Type */
enum dramtypes {
	DDR4,	/* DDR4 */
	DDR3,	/* DDR3 */
	LPDDR4, /* LPDDR4 */
};

/* Enumerator for DIMM Type */
enum dimmtypes {
#ifdef USE_STM32MP257CXX_EMU
	UDIMM = 0x0,  /* UDIMM */
#endif /* USE_STM32MP257CXX_EMU */
	NODIMM = 0x4 /* No DIMM (Soldered-on) */
};

/*
 * Structure for basic (mandatory) user inputs
 *
 * The following basic data structure must be set and completed correctly so
 * that the PhyInit software package can accurate program PHY registers.
 */
struct user_input_basic {
	int dramtype; /* DRAM Module Type */

	/*
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | DDR4
	 *   0x1 | DDR3
	 *   0x2 | LPDDR4
	 */

	int dimmtype; /* Choose the Dimm type from one of below */

	/*
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | UDIMM (if USE_STM32MP257CXX_EMU)
	 *   0x4 | No DIMM (Soldered-on)
	 */

	int lp4xmode; /* Indicates LPDDR4X mode support */

	/*
	 * - must be set as hex
	 * - Only used for LPDDR4, but not valid here.
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | LPDDR4 mode, when dramtype is LPDDR4
	 */

	int numdbyte; /* Enter number of dbytes physically instantiated in RTL */

	/*
	 * - Must be decimal integer.
	 * - Must match verilog define DDRPHY_NUM_DBYTE_*in ddrphy_*_VDEFINES.v.
	 *   For example if DDRPHY_NUM_DBYTE_8 is defined in
	 *   RTL ddrphy_ac12d8ch2_VDEFINES.v, this variable must be set to decimal 8.
	 */

	int numactivedbytedfi0; /* Enter number of active dbytes to be controlled by dfi0 */

	/*
	 * - See PUB databook section on supported PHY configurations for valid settings.
	 * - Must be decimal integer.
	 */

	int numactivedbytedfi1; /* Enter number of active dbytes to be controlled by dfi1 */

	/*
	 * - See PUB databook section on supported PHY configurations for valid settings.
	 * - Only used for LPDDR4
	 * - Must be decimal integer.
	 */

	int numanib; /* Enter number of ANIBs physically instantiated */

	/*
	 * - See PUB databook section on supported PHY configurations for valid settings.
	 * - Must be decimal integer.
	 * - Must match verilog define DDRPHY_NUM_ANIB_* in ddrphy_*_VDEFINES.v
	 *   for example if DDRPHY_NUM_ANIB_12 is defined in RTL ddrphy_ac12d8ch2_VDEFINES.v
	 *   this variable must be set to decimal 8.
	 */

	int numrank_dfi0; /* Number of ranks in DFI0 channel */

	/*
	 * - See PUB databook section on supported PHY configurations for valid settings.
	 * - Must match the number of DRAM ranks attached to the PHY.
	 * - Must be decimal integer.
	 */

	int numrank_dfi1; /* Number of ranks in DFI1 channel (if DFI1 exists) */

	/*
	 * - See PUB databook section on supported PHY configurations for valid settings.
	 * - Only used for LPDDR4
	 * - Must match the number of DRAM ranks attached to the PHY.
	 * - Must be decimal integer.
	 */

	int dramdatawidth; /* Width of the DRAM device */

	/*
	 * - Enter 4,8,16 or 32 depending on protocol and dram type according below table.
	 * - Must be decimal integer.
	 * - See PUB databook section "Supported System Configurations" for DRAM width options
	 *   supported by your PHY product.
	 *
	 * Protocol | Valid Options | Default
	 * -------- | ------------- | ---
	 * DDR3     | 4,8,16        | 8
	 * DDR4     | 4,8,16        | 8
	 * LPDDR4   | 8,16          | 16
	 *
	 * \note LPDDR4 x8 width device will be supported in future PHY product.
	 * For mixed x8 and x16 width devices, set variable to x8.
	 *
	 */

	int numpstates; /* Number of p-states used */

	/*
	 * - Must be decimal integer, lower or equal to NB_PS.
	 *   this variable must be set to decimal 1.
	 */

	int frequency[NB_PS]; /* Memclk Frequency for each PState */

	/*
	 * - Must be decimal integer.
	 * - Memclk frequency in MHz round up to next highest integer. Enter 334 for 333.333, etc.
	 *
	 * [0] - P0 Memclk frequency in MHz
	 * [1] - P1 Memclk frequency in MHz
	 * [2] - P2 Memclk frequency in MHz
	 * [3] - P3 Memclk frequency in MHz
	 */

	int pllbypass[NB_PS]; /* Indicates if PLL should be in Bypass mode */

	/*
	 * - See PUB Databook section "PLL Bypass Mode" under "Clocking and Timing" for
	 *   requirements.
	 * - At datarates below DDR333 rate PLL must be in Bypass Mode.
	 * - Must be set as hex.
	 *
	 * [0] - PLL Bypass Enable for P0
	 * [1] - PLL Bypass Enable for P1
	 * [2] - PLL Bypass Enable for P2
	 * [3] - PLL Bypass Enable for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x1 | Enabled
	 *   0x0 | Disabled
	 */

	int dfifreqratio[NB_PS]; /* Selected Dfi Frequency ratio */

	/*
	 * - Used to program the dfifreqratio register. This register controls how dfi_freq_ratio
	 *   input pin should be driven inaccordance with DFI Spec.
	 * - See PUB databook section "DfiClk" on detailes on how set value.
	 * - must be set as hex
	 *
	 * [0] - DFI Frequency Ratio for P0
	 * [1] - DFI Frequency Ratio for P1
	 * [2] - DFI Frequency Ratio for P2
	 * [3] - DFI Frequency Ratio for P3
	 *
	 * Binary Value | Description
	 *        ----- | ------
	 *        2'b01 | 1:2 DFI Frequency Ratio (default)
	 */

	int dfi1exists; /* Indicates whether they PHY configuration has Dfi1 channel */

	/*
	 * - Must match value of Verilog define DDRPHY_DFI1_EXISTS in RTL file
	 *   ddrphy_*_VDEFINES.v.
	 * - must be set as hex
	 */

	int train2d; /* Obsolete. Not used. */

	/*
	 * - This variable is set via input variable to function ddrphy_phyinit_sequence()
	 * - This exists for backward compatibility and no longer used.
	 */

	int hardmacrover; /* Hard Macro Family version in use */

	/*
	 * - Please see technology specific PHY Databook for "Hard Macro Family" version. The
	 *   variable is used to fine tune analog register value settings.
	 * - Must be decimal integer.
	 *
	 * Value | Description
	 * ----- | ------
	 *   3   | hardmacro family D
	 */

	int readdbienable[NB_PS]; /* Obsolete. Not Used. */

	/*
	 * - Use messageBlock DMIPinPreset instead if DBI is enabled.
	 * - This exists for backward compatibility and no longer used.
	 */

	int dfimode; /* Obsolete. Not Used. */

	/*
	 * - dfimode register is programed based on other parameters
	 * - This exists for backward compatibility and no longer used.
	 */
};


/* Structure for advanced (optional) user inputs
 *
 * If user does not enter a value for these parameters, a default recommended or
 * default value will be used
 */
struct user_input_advanced {
	int lp4rxpreamblemode[NB_PS]; /* Selects between DRAM static read vs toggle read preamble */

	/*
	 * - Determine desired DRAM Read Preamble Mode based on SI Analysis and DRAM Part in use.
	 * - the PHY training firmware will program DRAM mr1-OP[3] after training based on setting.
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x1 | toggling preamble
	 *   0x0 | static preamble
	 */

	int lp4postambleext[NB_PS]; /* Extend write postamble in LPDDR4 */

	/*
	 * - This variable is used to calculate LPDDR4 mr3-OP[1] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Set value according to your SI analysis and DRAM requirement.
	 * - Applicable only if dramtype == LPDDR4
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | half Memclk postamble
	 *   0x1 | 1.5 Memclk postabmle (defualt)
	 */

	int d4rxpreamblelength[NB_PS]; /* Length of read preamble in DDR4 mode */

	/*
	 * - This variable is used to calculate DDR4 mr4-OP[11] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Set value according to your SI analysis and DRAM requirement.
	 * - Applicable only if dramtype == DDR4
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 |  1 Tck
	 *   0x1 |  2 Tck (default)
	 */

	int d4txpreamblelength[NB_PS]; /* Length of write preamble in DDR4 mode */

	/*
	 * - This variable is used to calculate DDR4 mr4-OP[12] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Set value according to your SI analysis and DRAM requirement.
	 * - Applicable only if dramtype == DDR4
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | 1 Tck (default)
	 *   0x1 | 2 Tck
	 */

	int extcalresval; /* External Impedance calibration pull-down resistor value select */

	/*
	 * - Indicates value of impedance calibration pull-down resistor connected to BP_ZN pin of
	 *   the PHY. See Section "Impedance Calibrator" section in the PUB Databook for details
	 *   on PHY impedance engine and the ZN requirements for the reference external resistor.
	 * - must be set as hex
	 * - Drop-down menu:
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | 240 ohm (default)
	 */

	int is2ttiming[NB_PS];	/*
				 * Set to 1 to use 2T timing for address/command, otherwise 1T
				 * timing will be used.
				 */

	/*
	 * - See section "2T Timing and Geardown Support" in PUB Databook.
	 *   Determine 1T or 2T Timing operation mode based on SI Analysis and DRAM Timing.
	 *   - In 1T mode, CK, CS, CA all have the same nominal timing, ie. ATxDly[6:0] will have
	 *     same value for all ANIBs
	 *   - In 2T mode, CK, CS,have the same nominal timing (e.g. AtxDly[6:0]=0x00), while CA is
	 *     delayed by 1UI
	 *     (e.g. ATxDly[6:0]=0x40)
	 * - This values is used to program phycfg setting in messageBlock.
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | 1T Timing (default)
	 *   0x1 | 2T Timing
	 */

	int odtimpedance[NB_PS]; /* Enter desired ODT impedance in ohm */

	/*
	 * - Used for programming TxOdtDrvStren registers.
	 * - See "Electrical Parameters" in PHY Databook for supported ODT impedance
	 *   range given your Hard Macro Family. Set based on Typical values from
	 *   "On-die termination (ODT) programable resistances" in the input conditions
	 *   table for each protocol. See table foot notes for more details.
	 * - Based on SI Analysis and DRAM modules, select from supported values in the PHY
	 *   Databook. Only values in the PUB databook are supported.
	 * - Enter 0 for open/high-impedance
	 * - Must be decimal integer.
	 * - default:60
	 *
	 * [0] - ODT in Ohm for P0
	 * [1] - ODT in Ohm for P1
	 * [2] - ODT in Ohm for P2
	 * [3] - ODT in Ohm for P3
	 *
	 */

	int tximpedance[NB_PS]; /* Tx Drive Impedance for DQ/DQS in ohm */

	/*
	 * - Used for programming TxImpedanceCtrl1 registers.
	 * - See "Electrical Parameters" in PHY Databook for supported impedance
	 *   range given your Hard Macro Family. Set based on Typical values from
	 *   "Outpu drive pull-up/down Impedance: DQ, DQS outputs" in "Common DC Output Paremeters"
	 *   table for each protocol. See table foot notes for more details.
	 * - Based on SI Analysis and DRAM modules, select from supported values in the PHY
	 *   Databook. Only values in the PUB databook are supported.
	 * - Enter 0 for open/high-impedance
	 * - Must be decimal integer.
	 * - Default value: 60
	 * - Must be decimal integer.
	 *
	 * [0] - impedance in Ohm for P0
	 * [1] - impedance in Ohm for P1
	 * [2] - impedance in Ohm for P2
	 * [3] - impedance in Ohm for P3
	 */

	int atximpedance; /* Tx Drive Impedance for AC in ohm */

	/*
	 * - Used for programming ATxImpedance register.
	 * - See "Electrical Parameters" in PHY Databook for supported impedance
	 *   range given your Hard Macro Family. Set based on Typical values from
	 *   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC
	 *   Output Paremeters" table for each protocol. See table foot notes for more details.
	 * - Based on SI Analysis and DRAM modules, select from supported values in the PHY
	 *   Databook. Only values in the PUB databook are supported.
	 * - Enter 0 for open/high-impedance
	 * - Must be decimal integer.
	 * - Default value: 20 (HMA,HMB,HMC,HMD), 40 (HME)
	 * - Must be decimal integer.
	 */

	int memalerten; /* Enables BP_ALERT programming of PHY registers */

	/*
	 * - Used for programming MemAlertControl and MemAlertControl2 register.
	 * - Program if you require using BP_ALERT pin (to receive or terminate signal) of the PHY
	 *   otherwise leave at default value, otherwise leave at default value to save power.
	 * - Applicable only if dramtype == DDR3 or DDR4, but not valid here.
	 * - Must be hex.
	 *
	 * Value | Description
	 * ----- | ------
	 * 0x0 | Disable BP_ALERT (default)
	 */

	int memalertpuimp; /* Specify MemAlert Pull-up Termination Impedance */

	/*
	 * - Programs the pull-up termination on BP_ALERT.
	 * - Not valid here (fixed 0 value)
	 */

	int memalertvreflevel; /* Specify the Vref level for BP_ALERT(MemAlert) Receiver */

	/*
	 * - See register description for MemAlertControl.MALERTVrefLevel in the PUB databook for
	 *   the formula to set desired VREF by :
	 *     Vref = VDDQ \times (0.51 + MALERTVrefLevel[6:0] \times 0.00345)
	 * - Default VREF = 0.65 * VDDQ --> MemAlertVrefLevel[6:0] = 7'd41 = 0x29
	 * - Must be set as hex.
	 * - Not valid here (fixed 0 value)
	 */

	int memalertsyncbypass;	/*
				 * When set, this bit bypasses the DfiClk synchronizer on
				 * dfi_alert_n.
				 */

	/*
	 * - See PUB databook register description for MemAlertControl2 for further details.
	 * - Default = 0x0
	 * - Must be set as hex.
	 * - Not valid here (fixed 0 value)
	 */

	int disdynadrtri[NB_PS]; /* Disable Dynamic Per-MEMCLK Address Tristate feature */

	/*
	 * - See PUB databook section "Dynamic Per-MEMCLK Address Tristate" and register
	 *   description of TristateModeCA.DisDynAdrTri for detailed explanation of this feature.
	 *   Program this variable if you require to disable this feature.
	 *   - In DDR3/2T mode, the dynamic tristate feature should be disabled
	 *     if the controller cannot follow the 2T PHY tristate protocol.
	 *   - In DDR4/2T/2N mode, the dynamic tristate feature should be disabled
	 *     if the controller cannot follow the 2T PHY tristate protocol.
	 *   - In LPDDR4 mode, the dynamic tristate feature should be disabled.
	 * - Must be set as hex.
	 *
	 * Value | Description
	 * ----- | ------
	 *  0x0  | Enable Dynamic Tristate (default) (if USE_STM32MP257CXX_EMU)
	 *  0x1  | Disable Dynamic Tristate
	 */

	int phymstrtraininterval[NB_PS];	/*
						 * Specifies the how frequent dfi_phymstr_req is
						 * issued by PHY
						 */

	/*
	 * - See PUB databook section "DFI Master Interface" and DFI 3.1
	 *   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
	 * - Based on SI analysis determine how frequent DRAM drift compensation and
	 *   re-training is required.
	 * - Determine if Memory controller supports DFI PHY Master Interface.
	 * - Program based on desired setting for PPTTrainSetup.PhyMstrTrainInterval register.
	 *   See register description in PUB Databook for translation table
	 *   of values to MEMCLKs. Example values provided in below table.
	 * - Only required in LPDDR4.
	 * - default : 0xa
	 * - Must be set as hex.
	 * - Example :
	 *
	 * Example Value | Description
	 * ----- | ------
	 *   0xa | PPT Train Interval = 268435456 MEMCLKs (default)
	 */

	int phymstrmaxreqtoack[NB_PS];	/*
					 * Max time from dfi_phymstr_req asserted to
					 * dfi_phymstr_ack asserted.
					 */

	/*
	 * - Based on your Memory controller's(MC) specification determine how long the PHY
	 *   should wait for the assertion of dfi_phymstr_ack once dfi_phymstr_req has
	 *   been issued by the PHY. If the MC does not ack the PHY's request, PHY may issue
	 *   dfi_error.
	 * - See PUB databook section "DFI Master Interface" and DFI 3.1
	 *   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
	 * - This value will be used to program PPTTrainSetup.PhyMstrMaxReqToAck register.
	 *   See detailed register description in PUB Databook.
	 * - default: 0x5
	 * - Only required in LPDDR4.
	 * - Must be set as hex.
	 * - Example:
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x5 | PPT Max. Req to Ack. = 8192 MEMCLKs (default)
	 */

	int wdqsext; /* Enable Write DQS Extension feature of PHY */

	/*
	 * - See App Note "Cores LPDDR4 MultiPHY : WDQS Extension Application Note"
	 * - Must be set as hex.
	 *
	 * Value | Description
	 * ----- | ------
	 *   0x0 | Disable Write DQS Extension feature. (default)
	 *   0x1 | Enable Write DQS Extension feature.
	 */

	int calinterval; /* Specifies the interval between successive calibrations, in mS */

	/*
	 * - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance
	 *   calibration FSM. Based on feedback from SI analysis, determine desired
	 *   calibration interval for your System.
	 * - Program variable based on desired setting for CalRate.CalInterval register.
	 *   See detailed register description in PUB Databook.
	 * - must be set as hex
	 * - Fixed 0x9 value (20mS interval)
	 */

	int calonce; /* This setting changes the behaviour of CalRun register */

	/*
	 * - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance
	 *   calibration FSM. Based on feedback from SI analysis, determine desired
	 *   calibration interval for your System.
	 * - If you desire to manually trigger impedance calibration in mission mode set
	 *   this variable to 1, and toggle CalRun in mission mode. See PUB Databook section
	 *   "Impedance Calibration Engine Setup" and register description for CalRate.CalOnce.
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ------
	 * 0x0   | Calibration will proceed at the rate determined by CalInterval. This field should
	 *         only be changed while the calibrator is idle. ie before csr CalRun is set.
	 */

	int lp4rl[NB_PS]; /* LPDDR4 Dram Read Latency */

	/*
	 * - This variable is used to calculate LPDDR4 mr2-OP[2:0] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Determine values based on your DRAM part's supported speed and
	 *   latency bin.
	 * - Default: calculated based on user_input_basic.frequency
	 *   and "JEDEC JESD209-4A (LPDDR4)" Table 28 "Read and Write Latencies".
	 *   Lowest latency selected when more than one latency can be used.
	 *   for example given configuration for LPDDR4, x16, NoDbi and DDR533,
	 *   RL=10 is selected rather than 14.
	 * - must be set as hex
	 * - Applicable only if dramtype == LPDDR4
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 */

	int lp4wl[NB_PS]; /* LPDDR4 Dram Write Latency */

	/*
	 * - This variable is used to calculate LPDDR4 mr2-OP[5:3] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Determine values based on your DRAM part's supported speed and
	 *   latency bin.
	 * - Default: calculated based on user_input_basic.frequency
	 *   and "JEDEC JESD209-4A (LPDDR4)" Table 28 "Read and Write Latencies".
	 *   Lowest latency selected when more than one latency can be used.
	 * - must be set as hex
	 * - Applicable only if dramtype == LPDDR4
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 */

	int lp4wls[NB_PS]; /* LPDDR4 Dram WL Set */

	/*
	 * - This variable is used to calculate LPDDR4 mr2-OP[6] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Determine value based on Memory controllers requirement of DRAM State after
	 *   PHY training.
	 * - must be set as hex
	 * - Applicable only if dramtype == LPDDR4
	 */

	/*
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 *   --- | ---
	 *   0x0 | WL Set "A" (default)
	 */

	int lp4dbird[NB_PS]; /* LPDDR4 Dram DBI-Read Enable */

	/*
	 * - Determine if you require to using DBI for the given PState.
	 *   If Read DBI is not used PHY receivers are turned off to save power.
	 * - This variable is used to calculate LPDDR4 mr3-OP[6] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - PHY register DMIPinPresent is programmed based on this parameter.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Applicable only if dramtype == LPDDR4
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 *   --- | ---
	 *   0x0 | Disabled (default)
	 *   0x1 | Enabled
	 */

	int lp4dbiwr[NB_PS]; /* LPDDR4 Dram DBI-Write Enable */

	/*
	 * - This variable is used to calculate LPDDR4 mr3-OP[7] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Applicable only if dramtype == LPDDR4
	 * - must be set as hex
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Value | Description
	 *   --- | ---
	 *   0x0 | Disabled (default)
	 *   0x1 | Enabled
	 */

	int lp4nwr[NB_PS]; /* LPDDR4 Write-Recovery for Auto- Pre-charge commands */

	/*
	 * - This variable is used to calculate LPDDR4 mr1-OP[6:4] set in the meessageBlock.
	 *   The training firmware will set DRAM MR according to MR value
	 *   in the messageBlock at the end of training.
	 * - Please refer to JEDEC JESD209-4A (LPDDR4) Spec for definition of MR.
	 * - Determine values based on your DRAM part's supported speed and
	 *   latency bin.
	 * - Default: calculated based on user_input_basic.frequency
	 *   and "JEDEC JESD209-4A (LPDDR4)" Table 28 "Read and Write Latencies".
	 *   Lowest latency selected when more than one latency can be used.
	 * - must be set as hex
	 * - Applicable only if dramtype == LPDDR4
	 *
	 * [0] - setting for P0
	 * [1] - setting for P1
	 * [2] - setting for P2
	 * [3] - setting for P3
	 *
	 * Binary Value | Description
	 * --- | ---
	 * 000 | nWR = 6 (default)
	 * 001 | nWR = 10
	 * 010 | nWR = 16
	 * 011 | nWR = 20
	 * 100 | nWR = 24
	 * 101 | nWR = 30
	 * 110 | nWR = 34
	 * 111 | nWR = 40
	 */

	int lp4lowpowerdrv; /* Configure output Driver in Low power mode */

	/*
	 * - Feature only supported for Hard Macro Family E (HME)
	 * - Use NMOS Pull-up for Low-Power IO
	 * - Not valid here
	 */

	int drambyteswap; /* DRAM Oscillator count source mapping for skip_training */

	/*
	 * - The PHY supports swapping of DRAM oscillator count values between paired DBytes for the
	 *   purpose of tDQSDQ DRAM Drift Compensation(DDC).
	 * - Each DByte has a register bit to control the source of the oscillator count value used
	 *   to perform tDQSDQ Drift compensation.
	 *   On silicon the training firmware will determine the DByte swap and program
	 *   PptCtlStatic register to select oscillator count source. When skip_train is used,
	 *   training firmware is skipped thus manual programming may be required depending on
	 *   configuration.
	 * - The default hardware configuration is for odd Dbyte instance n to use oscillator count
	 *   values from its paired Dbyte instance n-1. So Dbyte1 will use the oscillator count
	 *   values from Dbyte0, Dbyte3 will use Dbyte2 and so on. This is required for DRAM Data
	 *   width =16.
	 * - Each bit of this field corresponds to a DBYTE:
	 *   - bit-0 = setting for DBYTE0
	 *   - bit-1 = setting for DBYTE1
	 *   - bit-2 = setting for DBYTE2
	 *   - . . .
	 *   - bit-n = setting for DBYTEn
	 * - By setting the associated bit for each DByte to 1, PHY will use non-default source for
	 *   count value.
	 *   - for even Dbytes, non-default source is to use the odd pair count value.
	 *   - for odd Dbytes, no-default source to use data received directly from the DRAM.
	 * - Byte swapping must be the same across different ranks.
	 * - must be set as hex
	 * - default : 0x0
	 * - if Byte mode devices are indicated via the x8mode messageBlock parameter, this variable
	 *   is ignored as PHY only supports a limited configuration set based on Byte mode
	 *   configuration.
	 *
	 * Example:
	 *   DramByteSwap = 0x03 - Dbyte0: use count values from Dbyte1, Dbyte1 uses count values
	 *   received directly received from DRAM.
	 *   Rest of Dbytes have default source for DRAM oscilator count.
	 */

	int rxenbackoff; /* Determines the Placement of PHY Read Gate signal */

	/*
	 * - Only used in LPDDR4 when lp4rxpreamblemode==0 (static preamble) for skip_train==true
	 *   For other dramtypes or LPDDR4-toggling-preamble no options are available and
	 *   PhyInit will set position as required. See source code in
	 *   ddrphy_phyinit_c_initphyconfig() to see how the RxEnBackOff register is set.
	 * - For skip_train==false, FW will set the position based on Preamble.
	 * - We recommend keeping this setting at default value.
	 *   SI analysis is required to determine if default value needs to be changed.
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ---
	 *   0x1 | Position read gate 1UI from the first valid edge of DQS_t
	 *         (LPDDR4 Static preamble only) (default)
	 */

	int trainsequencectrl; /* Firmware Training Sequence Control */

	/*
	 * - This input is used to program sequencectrl in messageBlock.
	 *   It controls the training stages executed by firmware.
	 *   consult the training firmware App Note section "1D Training Steps" for details on
	 *   training stages.
	 * - For production silicon we recommend to use default value programmed by PhyInit.
	 * - If running simulation for the first time, program value according to "Initial
	 *   interactions with the firmware" section in Training firmware App Note.
	 */

	int snpsumctlopt;	/*
				 * Enable Fast Frequency Change (FFC) Optimizations specific to
				 * UMCTL2.
				 */

	/*
	 * - Consult UMCTL2 documentation to ensure when optimizations can be enabled.
	 * - Not valid for dimmtype=NODIMM
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ---
	 * 0 | Disable FFC MRW optimization (default)
	 */

	int snpsumctlf0rc5x[NB_PS];	/*
					 * F0RX5x RCD Control Word when using Fast Frequency
					 * Change(FFC) optimizations specific to UMCTL2
					 */

	/*
	 * - When UMCTL2 optimizations are enabled PHY will perform RCD MRW during fast frequency
	 *   change request.
	 *   The correct RCD control word value for each PState must be programmed in this field.
	 *   Consult the RCD spec and UMCTL documentation to determine the correct value based on
	 *   DRAM configuration and operating speed.
	 * - Not valid for dimmtype=NODIMM
	 * - Only valid for when SnpsUmctlOpt=1
	 * - must be set as hex
	 *
	 * [0] - F0RC5x for PState 0
	 * [1] - F0RC5x for PState 1
	 * [2] - F0RC5x for PState 2
	 * [3] - F0RC5x for PState 3
	 */

	int txslewrisedq[NB_PS]; /* Pull-up slew rate control for DBYTE Tx */

	/*
	 * - Value specified here will be written to register TxSlewRate.TxPreP by PhyInit.
	 *   See register description for more information.
	 * - Please consult the "Output Slew Rate" section of DQ Hspice App Note in
	 *   specific technology for recommended settings for your technology and Hard Macro Family.
	 *   Protocol specific values are provided under the rise_index column.
	 * - must be set as hex
	 *
	 * [0] - setting for PState 0
	 * [1] - setting for PState 1
	 * [2] - setting for PState 2
	 * [3] - setting for PState 3
	 */

	int txslewfalldq[NB_PS]; /* Pull-down slew rate control for DBYTE Tx */

	/*
	 * - Value specified here will be written to TxSlewRate.TxPreN by PhyInit.
	 *   See register description for more information.
	 * - Please consult the "Output Slew Rate" section of DQ HSPICE App Note in
	 *   specific technology for recommended settings for your technology and Hard Macro Family.
	 * - Protocol specific values are provided under the fall_index column.
	 * - must be set as hex
	 *
	 * [0] - setting for PState 0
	 * [1] - setting for PState 1
	 * [2] - setting for PState 2
	 * [3] - setting for PState 3
	 */

	int txslewriseac; /* Pull-up slew rate control for ANIB Tx */

	/*
	 * - Value specified here will be written to ATxSlewRate.ATxPreP
	 *   See register description for more information.
	 * - Please consult the "Output Slew Rate" section of CA HSPICE Model App Note in
	 *   specific technology for recommended settings for your technology and Hard Macro Family.
	 * - Protocol specific values are provided under the rise_index column.
	 * - must be set as hex
	 */

	int txslewfallac; /* Pull-down slew rate control for ANIB Tx */

	/*
	 * - Value specified here will be written to ATxSlewRate.ATxPreN
	 *   See register description for more information.
	 * - Please consult the "Output Slew Rate" section of CA HSPICE Model App Note in
	 *   specific technology for recommended settings for your technology and Hard Macro Family.
	 * - Protocol specific values are provided under the fall_index column.
	 * - must be set as hex
	 */

	int disableretraining; /* Disable PHY DRAM Drift compensation re-training */

	/*
	 * - Disable PHY re-training during DFI frequency change requests in LPDDR4.
	 *   See Firmware Training App Note section "DRAM Drift Compensation" for details of steps
	 *   in re-training.
	 * - The purpose of retraining is to compensate for drift in the DRAM.
	 *   Determine based on SI analysis and DRAM datasheet if retraining can be disabled.
	 * - Only applied to LPDDR4. No retraining is required in DDR4/3.
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ---
	 *   0x1 | Disable retraining
	 *   0x0 | Enable retraining
	 */

	int disablephyupdate; /* Disable DFI PHY Update feature */

	/*
	 * - Disable DFI PHY Update feature. When set PHY will not assert dfi0/1_phyupd_req.
	 *   See DFI specification for DFI PHY update interface. See PUB databook section
	 *   "PHY Update" for details of the DFI PHY update interface implementation.
	 * - Only effects LPDDR4
	 * - must be set as hex
	 *
	 * Value | Description
	 * ----- | ---
	 *   0x1 | Disable DFI PHY Update
	 *   0x0 | Enable DFI PHY Update
	 */


	int enablehighclkskewfix;	/*
					 * Enable alternative PIE program
					 *
					 * See STAR 9001264921 for details on this workaround.
					 * If enabled the PIE reinitializes the FIFO pointers a
					 * second time due for designs with large skew between
					 * chiplet DfiClk branches. If enabled PIE latencies in all
					 * protocols are increased by 60 DfiClks.
					 *
					 * Value | Description
					 * ----- | ---
					 *   0x0 | Disable (default)
					 */

	int disableunusedaddrlns;       /*
					 * Turn off or tristate Address Lanes when possible.
					 *
					 * - When enabled, PHY will tristate unused address lanes to
					 *   save power when possible by using Acx4AnibDis and
					 *   AForceTriCont registers.
					 * - This feature is only implemented for the default PHY
					 *   Address bump mapping and Ranks must be populated in
					 *   order. ie Rank1 cannot be used if Rank0 is unpopulated.
					 * - For alternative bump mapping follow the following
					 *   guideline to achieve maximum power savings:
					 *   - For each unused BP_A bump program AForceTriCont[4:0]
					 *     bits based on register description.
					 *   - if all lanes of an Anib are unused _AND_ ANIB is not
					 *     the first or last instance set bit associated with
					 *     the instance in Acs4AnibDis registers. see register
					 *     description for details.
					 *
					 * Value | Description
					 * ----- | ---
					 *   0x1 | Enable
					 */

	int phyinitsequencenum;		/*
					 * Switches between supported phyinit training sequences
					 *   refer to "Alternative PHY Training sequence" document
					 *   for further details.
					 *
					 * Value | Description
					 * ----- | ---
					 *   0x0 | Minimizes number of Imem/Dmem loads (default)
					 */

	int enabledficspolarityfix;     /*
					 * Enable alternative PIE program
					 *
					 * See STAR 9001524249 for details on this workaround. Set
					 * to 1 if PUB_VERSION <2.43a, otherwise set to 0. If
					 * enabled the PIE programs Dfi{Rd,Wr}DataCsDestMap CSR's
					 * to default values 0x00E4 before running PPT.
					 * Before exiting PPT, PIE will restore
					 * Dfi{Rd,Wr}DataCsDestMap CSR's to 0x00E1.
					 *
					 * Value | Description
					 * ----- | ---
					 *   0x0 | Disable (default)
					 */

	int phyvref;			/*
					 * Must be programmed with the Vref level to be used by the
					 * PHY during reads
					 *
					 * The units of this field are a percentage of VDDQ
					 * according to the following equation:
					 *
					 * Receiver Vref = VDDQ*phyvref[6:0]/128
					 *
					 * For example to set Vref at 0.75*VDDQ, set this field to
					 * 0x60.
					 *
					 * For digital simulation, any legal value can be used. For
					 * silicon, the users must calculate the analytical Vref by
					 * using the impedances, terminations, and series resistance
					 * present in the system.
					 */

	int sequencectrl[NB_PS];	/*
					 * Controls the training steps to be run. Each bit
					 * corresponds to a training step.
					 *
					 * If the bit is set to 1, the training step will run.
					 * If the bit is set to 0, the training step will be
					 * skipped.
					 *
					 * Training step to bit mapping:
					 * sequencectrl[0] = Run DevInit - Device/phy
					 *		     initialization. Should always be set.
					 * sequencectrl[1] = Run WrLvl - Write leveling
					 * sequencectrl[2] = Run RxEn - Read gate training
					 * sequencectrl[3] = Run RdDQS1D - 1d read dqs training
					 * sequencectrl[4] = Run WrDQ1D - 1d write dq training
					 * sequencectrl[5] = RFU, must be zero
					 * sequencectrl[6] = RFU, must be zero
					 * sequencectrl[7] = RFU, must be zero
					 * sequencectrl[8] = Run RdDeskew - Per lane read dq deskew
					 *		     training
					 * sequencectrl[9] = Run MxRdLat - Max read latency training
					 * sequencectrl[10] = RFU, must be zero
					 * sequencectrl[11] = RFU, must be zero
					 * sequencectrl[12] = RFU, must be zero
					 * sequencectrl[13] = RFU, must be zero
					 * sequencectrl[15-14] = RFU, must be zero
					 */
};

/*
 * Structure for mode register (mandatory) user inputs
 *
 * The following basic data structure must be set and completed correctly so
 * that the PhyInit software package can accurate fill message block structure.
 * Only some mrx are used per DDR type, on related width:
 * - DDR3: mr0..2 are used (16-bits values)
 * - DDR4: mr0..6 are used (16-bits values)
 * - LPDDR4: mr1..4 and mr11..22 are used (8-bits values)
 */
struct user_input_mode_register {
	int mr0[NB_PS];
	int mr1[NB_PS];
	int mr2[NB_PS];
	int mr3[NB_PS];
	int mr4[NB_PS];
	int mr5[NB_PS];
	int mr6[NB_PS];
	int mr11[NB_PS];
	int mr12[NB_PS];
	int mr13[NB_PS];
	int mr14[NB_PS];
	int mr22[NB_PS];
};

/*
 * Structure for swizzle (mandatory) user inputs
 *
 * The following basic data structure must be set and completed correctly so
 * that the PhyInit software package can accurate set swizzle (IO muxing) config.
 * Only some swizzles are used per DDR type:
 * - DDR3/DDR3: swizzle 0..32 are used
 *   - 26 for hwtswizzle
 *   - 7 for acswizzle
 * - LPDDR4:  swizzle 0..43 are used
 *   - 8 per byte for dqlnsel (total 32)
 *   - 6 for mapcaatodfi
 *   - 6 for mapcabtodfi
 */
#define NB_HWT_SWIZZLE			26
#define NB_AC_SWIZZLE			7
#define NB_DQLNSEL_SWIZZLE_PER_BYTE	8
#define NB_MAPCAATODFI_SWIZZLE		6
#define NB_MAPCABTODFI_SWIZZLE		6
#define NB_SWIZZLE	44
struct user_input_swizzle {
	int swizzle[NB_SWIZZLE];
};

#endif /* DDRPHY_PHYINIT_STRUCT_H */

