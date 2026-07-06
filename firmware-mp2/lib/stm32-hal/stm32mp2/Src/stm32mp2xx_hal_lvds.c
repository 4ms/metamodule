/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_lvds.c
  * @author  MCD Application Team
  * @brief   LVDS HAL module driver
  *          This file provides firmware functions to manage the following
  *          functionalities of the Digital Camera Interface (lvds) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================


	*** LVDS HAL driver macros list ***
	=============================================
	[..]
	   Below the list of most used macros in LVDS HAL driver.

	  (+) __HAL_LVDS_ENABLE: Enable the LVDS Host.
	  (+) __HAL_LVDS_DISABLE: Disable the LVDS Host.
	  (+) __HAL_LVDS_PLL_ENABLE: Enable the LVDS PLL.
	  (+) __HAL_LVDS_PLL_DISABLE: Disable the LVDS PLL.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */
/** @defgroup lvds lvds
 * @brief lvds HAL module driver
 * @{
 */

#ifdef HAL_LVDS_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LVDS_TIMEOUT_VALUE						((uint32_t)1000U) /* 1s */

/* Private macro -------------------------------------------------------------*/
#define SET_MAP(__MAP__, __FIELD__) (__MAP__) << (__FIELD__)

/* Private variables ---------------------------------------------------------*/

// Expected JEIDA-RGB888 data to be sent in LSB format
//          bit6 ............................bit0
// CHAN0   {ONE, ONE, ZERO, ZERO, ZERO, ONE, ONE}
// CHAN1   {G2,  R7,  R6,   R5,   R4,   R3,  R2}
// CHAN2   {B3,  B2,  G7,   G6,   G5,   G4,  G3}
// CHAN3   {DE,  VS,  HS,   B7,   B6,   B5,  B4}
// CHAN4   {CE,  B1,  B0,   G1,   G0,   R1,  R0}

const HAL_LVDS_MapTypeDef HAL_LVDS_Map_JEIDA_RGB888[5][7] = {
		{HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ONE},  // CH0
		{HAL_LVDS_MAP_G_2, HAL_LVDS_MAP_R_7, HAL_LVDS_MAP_R_6,  HAL_LVDS_MAP_R_5,  HAL_LVDS_MAP_R_4,  HAL_LVDS_MAP_R_3, HAL_LVDS_MAP_R_2},
		{HAL_LVDS_MAP_B_3, HAL_LVDS_MAP_B_2, HAL_LVDS_MAP_G_7,  HAL_LVDS_MAP_G_6,  HAL_LVDS_MAP_G_5,  HAL_LVDS_MAP_G_4, HAL_LVDS_MAP_G_3},
		{HAL_LVDS_MAP_D_E, HAL_LVDS_MAP_V_S, HAL_LVDS_MAP_H_S,  HAL_LVDS_MAP_B_7,  HAL_LVDS_MAP_B_6,  HAL_LVDS_MAP_B_5, HAL_LVDS_MAP_B_4},
		{HAL_LVDS_MAP_C_E, HAL_LVDS_MAP_B_1, HAL_LVDS_MAP_B_0,  HAL_LVDS_MAP_G_1,  HAL_LVDS_MAP_G_0,  HAL_LVDS_MAP_R_1, HAL_LVDS_MAP_R_0}	// CH4
};

// Expected VESA-RGB888 data to be sent in LSB format
//          bit6 ............................bit0
// CHAN0   {ONE, ONE, ZERO, ZERO, ZERO, ONE, ONE}
// CHAN1   {G0,  R5,  R4,   R3,   R2,   R1,  R0}
// CHAN2   {B1,  B0,  G5,   G4,   G3,   G2,  G1}
// CHAN3   {DE,  VS,  HS,   B5,   B4,   B3,  B2}
// CHAN4   {CE,  B7,  B6,   G7,   G6,   R7,  R6}

const HAL_LVDS_MapTypeDef HAL_LVDS_Map_VESA_RGB888[5][7] = {
		{HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ONE, HAL_LVDS_MAP_ONE},		// CH0
		{HAL_LVDS_MAP_G_0, HAL_LVDS_MAP_R_5, HAL_LVDS_MAP_R_4,  HAL_LVDS_MAP_R_3,  HAL_LVDS_MAP_R_2,  HAL_LVDS_MAP_R_1, HAL_LVDS_MAP_R_0},		// CH1
		{HAL_LVDS_MAP_B_1, HAL_LVDS_MAP_B_0, HAL_LVDS_MAP_G_5,  HAL_LVDS_MAP_G_4,  HAL_LVDS_MAP_G_3,  HAL_LVDS_MAP_G_2, HAL_LVDS_MAP_G_1},		// CH2
		{HAL_LVDS_MAP_D_E, HAL_LVDS_MAP_V_S, HAL_LVDS_MAP_H_S,  HAL_LVDS_MAP_B_5,  HAL_LVDS_MAP_B_4,  HAL_LVDS_MAP_B_3, HAL_LVDS_MAP_B_2},		// CH3
		{HAL_LVDS_MAP_C_E, HAL_LVDS_MAP_B_7, HAL_LVDS_MAP_B_6,  HAL_LVDS_MAP_G_7,  HAL_LVDS_MAP_G_6,  HAL_LVDS_MAP_R_7, HAL_LVDS_MAP_R_6}		// CH4
};

// Expected JEIDA/VESA-RGB666 data to be sent in LSB format
//          bit6 ............................bit0
// CHAN0   {ONE, ONE, ZERO, ZERO, ZERO, ONE, ONE}
// CHAN1   {G2,  R7,  R6,   R5,   R4,   R3,  R2}
// CHAN2   {B3,  B2,  G7,   G6,   G5,   G4,  G3}
// CHAN3   {DE,  VS,  HS,   B7,   B6,   B5,  B4}
// CHAN4   {00,  00,  00,   00,   00,   00,  00}

const HAL_LVDS_MapTypeDef HAL_LVDS_Map_RGB666[5][7] = {
		{HAL_LVDS_MAP_ONE,  HAL_LVDS_MAP_ONE,  HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ONE,  HAL_LVDS_MAP_ONE},	// CH0
		{HAL_LVDS_MAP_G_2,  HAL_LVDS_MAP_R_7,  HAL_LVDS_MAP_R_6,   HAL_LVDS_MAP_R_5,   HAL_LVDS_MAP_R_4,   HAL_LVDS_MAP_R_3,  HAL_LVDS_MAP_R_2},
		{HAL_LVDS_MAP_B_3,  HAL_LVDS_MAP_B_2,  HAL_LVDS_MAP_G_7,   HAL_LVDS_MAP_G_6,   HAL_LVDS_MAP_G_5,   HAL_LVDS_MAP_G_4,  HAL_LVDS_MAP_G_3},
		{HAL_LVDS_MAP_D_E,  HAL_LVDS_MAP_V_S,  HAL_LVDS_MAP_H_S,   HAL_LVDS_MAP_B_7,   HAL_LVDS_MAP_B_6,   HAL_LVDS_MAP_B_5,  HAL_LVDS_MAP_B_4},
		{HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ZERO,  HAL_LVDS_MAP_ZERO, HAL_LVDS_MAP_ZERO}	// CH4
};

/* Private function prototypes -----------------------------------------------*/
void LVDS_PHY_SetPLL(LVDS_HandleTypeDef *hlvds,LVDS_PLLInitTypeDef *PLLInit);

uint32_t LVDS_PHY_StartMst(LVDS_HandleTypeDef *hlvds);
uint32_t LVDS_PHY_StartSlv(LVDS_HandleTypeDef *hlvds);

/* Private functions ---------------------------------------------------------*/
void LVDS_PHY_SetPLL(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit)
{
	uint32_t en_sd, en_twg, fpfd, twg_threshold, twg_step, sd_code;

	/* TODO check other parameters */
//	assert_param(IS_LVDS_PLL_MODE(PLLInit->ISMASTER));
	assert_param(IS_LVDS_PLL_MODE(PLLInit->PLLMODE));
	assert_param(IS_LVDS_PLL_BDIV(PLLInit->PLLBDIV));
	assert_param(IS_LVDS_PLL_MDIV(PLLInit->PLLMDIV));
	assert_param(IS_LVDS_PLL_NDIV(PLLInit->PLLNDIV));
	assert_param(IS_LVDS_PLL_FREF(PLLInit->PLLFREF));

	fpfd = PLLInit->PLLFREF / PLLInit->PLLNDIV;

	if (PLLInit->PLLMODE == LVDS_PLL_MODE_INT) {
		assert_param(PLLInit->FRACIN == 0);
		assert_param(PLLInit->DOWN_SPREAD == 0);

		en_sd = 0;
		en_twg = 0;
		sd_code = 0;
		twg_threshold = 0;
		twg_step = 0;
	} else if (PLLInit->PLLMODE == LVDS_PLL_MODE_FRAC) {
		en_twg = 0;
		if (PLLInit->ISMASTER) {
		 en_sd = LVDS_PMPLLCR1_MST_PLL_SD_ENABLE;
		} else {
			// TODO ?
		}
		twg_threshold = ((4 * PLLInit->MODDEP * PLLInit->PLLMDIV / 100) * 8388608/256) / 1000;
		twg_step = twg_threshold /(fpfd/(4 * PLLInit->MODFREQ));
		sd_code = ((PLLInit->FRACIN * 131072) / 1000) + 4194304;
	} else {
		if (PLLInit->ISMASTER) {
			en_twg = LVDS_PMPLLCR1_MST_PLL_TWG_ENABLE;
			en_sd = LVDS_PMPLLCR1_MST_PLL_SD_ENABLE;
		} else {
			// TODO ?
		}
		twg_threshold = ((4 * PLLInit->MODDEP * PLLInit->PLLMDIV / 100) * 8388608/256) / 1000;
		twg_step = twg_threshold /(fpfd/(4 * PLLInit->MODFREQ));
		sd_code = ((PLLInit->FRACIN * 131072) / 1000) + 4194304;
	}

//	if (PLLInit->ISMASTER) {
		//i_lvds_pll_input_div_setting = input_divider;
		hlvds->Instance->PMPLLCR2 = PLLInit->PLLNDIV << LVDS_PMPLLCR2_MST_PLL_INPUT_DIV_Pos;

		//i_lvds_pll_bit_div_setting = bit_divider;
		hlvds->Instance->PMPLLCR2 |= PLLInit->PLLBDIV << LVDS_PMPLLCR2_MST_PLL_BIT_DIV_Pos;

		//i_lvds_pll_sd_int_ratio = feedback_divider;
		hlvds->Instance->PMPLLSDCR1 = PLLInit->PLLMDIV << LVDS_PMPLLSDCR1_MST_PLL_SD_INT_RATIO_Pos;


		//i_lvds_pll_test_div_setting = test_divider;
		hlvds->Instance->PMPLLTESTCR  = PLLInit->TESTDIV << LVDS_PMPLLTESTCR_MST_PLL_TEST_DIV_SETTINGS_Pos;

//		//i_lvds_pll_sd_enable = en_sd | en_twg; i_lvds_pll_use_bit_clk_in_sync =1; i_lvds_pll_use_ls_clk_in_sync =1;
//		CLEAR_REG(hlvds->Instance->PMPLLCR1);
//		hlvds->Instance->PMPLLCR1 = en_sd;
//		hlvds->Instance->PMPLLCR1 |= en_twg;
//
//		//i_lvds_pll_twg_threshold = ((4 * modulation_depth * feedback_divider / 100.0) * 8388608/256.0) / 1000.0;
//		hlvds->Instance->PMPLLTWGCR2 = twg_threshold << LVDS_PMPLLTWGCR2_MST_PLL_TWG_THRESHOLD_Pos;
//
//		//i_lvds_pll_twg_step  =  i_lvds_pll_twg_threshold /(fpfd/(4 * modulation_frequency));
//		hlvds->Instance->PMPLLTWGCR1 = twg_step << LVDS_PMPLLTWGCR1_MST_PLL_TWG_STEP_Pos;
//
//		//i_lvds_pll_twg_down_spread = down_spread;
//		hlvds->Instance->PMPLLTWGCR1 |= PLLInit->DOWN_SPREAD << LVDS_PMPLLTWGCR1_MST_PLL_TWG_DOWN_SPREAD_Pos;

		//i_lvds_pll_sd_input_code_bypass  = (fractional_component * 131072.0)/1000.0 + 4194304;
//		hlvds->Instance->PMPLLSDCR2 = sd_code << LVDS_PMPLLSDCR2_MST_PLL_SD_INPUT_CODE_BYPASS_Pos;
//  } else {
  	//i_lvds_pll_input_div_setting = input_divider;
  	hlvds->Instance->PSPLLCR2 = PLLInit->PLLNDIV << LVDS_PSPLLCR2_SLV_PLL_INPUT_DIV_Pos;

  	//i_lvds_pll_bit_div_setting = bit_divider;
  	hlvds->Instance->PSPLLCR2 |= PLLInit->PLLBDIV << LVDS_PSPLLCR2_SLV_PLL_BIT_DIV_Pos;

  	//i_lvds_pll_sd_int_ratio = feedback_divider;
  	hlvds->Instance->PSPLLSDCR1 = PLLInit->PLLMDIV << LVDS_PSPLLSDCR1_SLV_PLL_SD_INT_RATIO_Pos;

  	//i_lvds_pll_test_div_setting = test_divider;
  	hlvds->Instance->PSPLLTESTCR  = PLLInit->TESTDIV << LVDS_PSPLLTESTCR_SLV_PLL_TEST_DIV_SETTINGS_Pos;

//  	CLEAR_REG(hlvds->Instance->PSPLLCR1);
//  	//i_lvds_pll_sd_enable = en_sd; i_lvds_pll_use_bit_clk_in_sync =0; i_lvds_pll_use_ls_clk_in_sync =0;
//  	hlvds->Instance->PSPLLCR1 = en_sd << LVDS_PSPLLCR1_SLV_PLL_SD_ENABLE_Pos;
//
//  	//i_lvds_pll_twg_enable = en_twg;
//  	hlvds->Instance->PSPLLCR1 |= en_twg << LVDS_PSPLLCR1_SLV_PLL_TWG_ENABLE_Pos;
//
//  	//i_lvds_pll_twg_threshold = ((4 * modulation_depth * feedback_divider / 100.0) * 8388608/256.0) / 1000.0;
//  	hlvds->Instance->PSPLLTWGCR2 = twg_threshold << LVDS_PSPLLTWGCR2_SLV_PLL_TWG_THRESHOLD_Pos;
//
//  	//i_lvds_pll_twg_step  =  i_lvds_pll_twg_threshold /(fpfd/(4 * modulation_frequency));
//  	hlvds->Instance->PSPLLTWGCR1 = twg_step << LVDS_PSPLLTWGCR1_SLV_PLL_TWG_STEP_Pos;
//
//  	//i_lvds_pll_twg_down_spread = down_spread;
//  	hlvds->Instance->PSPLLTWGCR1 |= PLLInit->DOWN_SPREAD << LVDS_PSPLLTWGCR1_SLV_PLL_TWG_DOWN_SPREAD_Pos;
//
//  	//i_lvds_pll_sd_input_code_bypass  = (fractional_component * 131072.0)/1000.0 + 4194304;
//  	hlvds->Instance->PSPLLSDCR2 = sd_code << LVDS_PSPLLSDCR2_SLV_PLL_SD_INPUT_CODE_BYPASS_Pos;
//  }
}

uint32_t LVDS_PHY_StartMst(LVDS_HandleTypeDef *hlvds)
{
	uint32_t tickstart;
	volatile uint32_t lock;

	// PLL lock timing control for the monitor unmask after startup (pll_en)
	// Adjust the value so that the masking window is opened at start-up
	hlvds->Instance->PMMPLCR = (0x200-0x160) << LVDS_PMMPLCR_MST_MON_PLL_LOCK_UNMASK_TUNE_Pos;

	//i_lvds_bias_en = 1 on both PHY
	hlvds->Instance->PMBCR2 = LVDS_PMBCR2_MST_BIAS_EN;

	//i_lvds_ls_clk_out_en = 1;
	//i_lvds_dp_clk_out_en = 1;
	//i_lvds_bit_clk_out_en = 1;
	hlvds->Instance->PMGCR |= LVDS_PMGCR_MST_DP_CLK_OUT_ENABLE | LVDS_PMGCR_MST_LS_CLK_OUT_ENABLE | LVDS_PMGCR_MST_BIT_CLK_OUT_ENABLE;

	//i_lvds_pll_test_div_en = 1;
	hlvds->Instance->PMPLLTESTCR |= LVDS_PMPLLTESTCR_MST_PLL_TEST_DIV_EN ;

	//i_lvds_pll_dividers_en = 1;
	hlvds->Instance->PMPLLCR1 |= LVDS_PMPLLCR1_MST_PLL_DIVIDERS_ENABLE ;

	//i_lvds_ser_data_ok =1;
	hlvds->Instance->PMSCR = LVDS_PMSCR_MST_SER_DATA_OK;

	//i_lvds_pll_en = 1;
	hlvds->Instance->PMPLLCR1 |= LVDS_PMPLLCR1_MST_PLL_ENABLE ;

	/* Get tick */
	tickstart = HAL_GetTick();

    /* Wait for PLL lock (using the new status register)
	 * Wait until the regulator is ready
	 */
	do
	{
		/* Check for the Timeout */
		if ((HAL_GetTick() - tickstart) > LVDS_TIMEOUT_VALUE)
		{
			return HAL_TIMEOUT;
		}
	} while ((hlvds->Instance->PMSSR1 & 0x7) != 0x7);

	HAL_Delay(1000);

	// Select MST PHY clock as pixel clock for the LDITX instead of FREF
	hlvds->Instance->WCLKCR = LVDS_WCLKCR_SLV_CLKPIX_SEL;

//    hlvds->Instance->PMPLLTESTCR |= LVDS_PMPLLTESTCR_MST_PLL_TEST_CLK_EN_Msk;

	return lock;
}

// Function to enable PLL/divider/... in SLV PHY
uint32_t LVDS_PHY_StartSlv(LVDS_HandleTypeDef *hlvds)
{
	uint32_t tickstart;
	volatile uint32_t lock;

	// PLL lock timing control for the monitor unmask after startup (pll_en)
	// Adjust the value so that the masking window is opened at start-up
	hlvds->Instance->PSMPLCR = (0x200-0x160) << LVDS_PSMPLCR_SLV_MON_PLL_LOCK_UNMASK_TUNE_Pos;

	//i_lvds_bias_en = 1
	hlvds->Instance->PSBCR2 = LVDS_PSBCR2_SLV_BIAS_EN;

	//i_lvds_ls_clk_out_en = 1;
	//i_lvds_dp_clk_out_en = 1;
	//i_lvds_bit_clk_out_en = 1;
	hlvds->Instance->PSGCR |= LVDS_PSGCR_SLV_DP_CLK_OUT_ENABLE | LVDS_PSGCR_SLV_LS_CLK_OUT_ENABLE | LVDS_PSGCR_SLV_BIT_CLK_OUT_ENABLE;

	//i_lvds_pll_test_div_en = 1;
	hlvds->Instance->PSPLLTESTCR |= LVDS_PSPLLTESTCR_SLV_PLL_TEST_DIV_EN;

	//i_lvds_pll_dividers_en = 1;
	hlvds->Instance->PSPLLCR1 |= LVDS_PSPLLCR1_SLV_PLL_DIVIDERS_ENABLE;

	//i_lvds_ser_data_ok =1;
	hlvds->Instance->PSSCR = LVDS_PSSCR_SLV_SER_DATA_OK;

	//i_lvds_pll_en = 1;
	hlvds->Instance->PSPLLCR1 |= LVDS_PSPLLCR1_SLV_PLL_ENABLE;

	/* Get tick */
	tickstart = HAL_GetTick();

	// LVDS_PSMPLSR_SLV_MON_PLL_LOCK_PERMANENT_FAULT should go high to indicate lock mechanism is starting
	// Wait for PLL lock
	do
	{
		/* Check for the Timeout */
		if ((HAL_GetTick() - tickstart) > LVDS_TIMEOUT_VALUE)
		{
			return HAL_TIMEOUT;
		}
	} while ((hlvds->Instance->PSSSR1 & 0x7) != 0x7);

	HAL_Delay(1000);

	// Select SLV PHY clock as pixel clock for the LDITX instead of FREF
	hlvds->Instance->WCLKCR = LVDS_WCLKCR_SLV_CLKPIX_SEL;// | LVDS_WCLKCR_SRCSEL;

    hlvds->Instance->PSPLLTESTCR |= LVDS_PSPLLTESTCR_SLV_PLL_TEST_CLK_EN;

	return lock;
}

HAL_StatusTypeDef LVDS_PHY_SetPreEmphasisAmplitude(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t amplitude)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPEACR = amplitude;
  } else {
  	hlvds->Instance->PSPEACR = amplitude;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPreEmphasisTime(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t time)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPETCR = time;
  } else {
  	hlvds->Instance->PSPETCR = time;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetRXLoopback(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t loopback)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMRLPCR = loopback;
  } else {
  	hlvds->Instance->PSRLPCR = loopback;
  }

  /* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetCurrentMode(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t reg1, uint32_t reg2)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMCMCR1 = reg1;
    hlvds->Instance->PMCMCR2 = reg2;
  } else {
    hlvds->Instance->PSCMCR1 = reg1;
    hlvds->Instance->PSCMCR2 = reg2;
  }

  /* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetFlipedge(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t flipedge)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMFCR = flipedge;
  } else {
    hlvds->Instance->PSFCR = flipedge;
  }

  /* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetSpare(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t spare1, uint32_t spare2)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMSCR1 = spare1;
    hlvds->Instance->PMSCR2 = spare2;
  } else {
    hlvds->Instance->PSSCR1 = spare1;
    hlvds->Instance->PSSCR2 = spare2;
  }

  /* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetBias(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit,
		uint32_t bias1, uint32_t bias2,
		uint32_t bias3, uint32_t bias4, uint32_t bias5)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMBCR1 = bias1;
    hlvds->Instance->PMBCR2 = bias2;
    hlvds->Instance->PMBCR3 = bias3;
    hlvds->Instance->PMBCR4 = bias4;
    hlvds->Instance->PMBCR5 = bias5;
  } else {
    hlvds->Instance->PSBCR1 = bias1;
    hlvds->Instance->PSBCR2 = bias2;
    hlvds->Instance->PSBCR3 = bias3;
    hlvds->Instance->PSBCR4 = bias4;
    hlvds->Instance->PSBCR5 = bias5;
  }

  /* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetImpedance(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t impedance)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMICR = impedance;
  } else {
    hlvds->Instance->PSICR = impedance;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorBandgapCurrent(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t bandgap)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMBCCR = bandgap;
  } else {
    hlvds->Instance->PSMBCCR = bandgap;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorBandgapLoop(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t bandgap_loop)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMBLCR = bandgap_loop;
  } else {
    hlvds->Instance->PSMBLCR = bandgap_loop;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorBandgapOutputVoltage(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t voltage)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMBOVCR = voltage;
  } else {
    hlvds->Instance->PSMBOVCR = voltage;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorPLLLDOOutputVoltage(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit,  uint32_t voltage)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMPLOVCR = voltage;
  } else {
    hlvds->Instance->PSMPLOVCR = voltage;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorPLLLock(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t lock)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMPLCR = lock;
  } else {
    hlvds->Instance->PSMPLCR = lock;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorPLLReferenceOK(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t ref)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMPROCR = ref;
  } else {
    hlvds->Instance->PSMPROCR = ref;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorSerializerClk(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t serializer_clk)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMSCCR = serializer_clk;
  } else {
    hlvds->Instance->PSMSCCR = serializer_clk;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetMonitorSerializer(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t serializer)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMMSCR = serializer;
  } else {
    hlvds->Instance->PSMSCR = serializer;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetDebug(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t debug)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMDCR = debug;
  } else {
    hlvds->Instance->PSDCR = debug;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_EnableDataLanes(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t config)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMCFGCR = config;
  } else {
    hlvds->Instance->PSCFGCR = config;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLMode(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t mode1, uint32_t mode2)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLCR1 = mode1;
    hlvds->Instance->PMPLLCR2 = mode2;
  } else {
    hlvds->Instance->PSPLLCR1 = mode1;
    hlvds->Instance->PSPLLCR2 = mode2;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLSD(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t sd1, uint32_t sd2)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLSDCR1 = sd1;
    hlvds->Instance->PMPLLSDCR2 = sd2;
  } else {
    hlvds->Instance->PSPLLSDCR1 = sd1;
    hlvds->Instance->PSPLLSDCR2 = sd2;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLTWG(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t twg1, uint32_t twg2)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLTWGCR1 = twg1;
    hlvds->Instance->PMPLLTWGCR2 = twg2;
  } else {
    hlvds->Instance->PSPLLTWGCR1 = twg1;
    hlvds->Instance->PSPLLTWGCR2 = twg2;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLLDO(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t config)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLLDOCR = config;
  } else {
    hlvds->Instance->PSPLLLDOCR = config;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLCP(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t cp)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLCPCR = cp;
  } else {
    hlvds->Instance->PSPLLCPCR = cp;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLConfig(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t config)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLCFGCR = config;
  } else {
    hlvds->Instance->PSPLLCFGCR = config;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef LVDS_PHY_SetPLLTest(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit, uint32_t test)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

  if (PLLInit->ISMASTER) {
    hlvds->Instance->PMPLLTESTCR = test;
  } else {
    hlvds->Instance->PSPLLTESTCR = test;
  }

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef core(LVDS_HandleTypeDef *hlvds)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Process locked */
  __HAL_LOCK(hlvds);

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_PHY_PLLConfig(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit)
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	/* Check PLLInit parameters */
	assert_param(IS_LVDS_PLL_FREF(PLLInit->PLLFREF));
	assert_param(IS_LVDS_PLL_BDIV(PLLInit->PLLBDIV));
	assert_param(IS_LVDS_PLL_MDIV(PLLInit->PLLMDIV));
	assert_param(IS_LVDS_PLL_NDIV(PLLInit->PLLNDIV));

	/* Power up bias and PLL dividers ******************************************************/
	WRITE_REG(hlvds->Instance->PMDCR, LVDS_PMDCR_MST_POWER_OK);
	WRITE_REG(hlvds->Instance->PSDCR, LVDS_PSDCR_SLV_POWER_OK);

	SET_BIT(hlvds->Instance->PMCMCR1, LVDS_PMCMCR1_MST_CM_EN_DL3	\
									| LVDS_PMCMCR1_MST_CM_EN_DL2	\
									| LVDS_PMCMCR1_MST_CM_EN_DL1	\
									| LVDS_PMCMCR1_MST_CM_EN_DL0);

	SET_BIT(hlvds->Instance->PMCMCR2, LVDS_PMCMCR2_MST_CM_EN_DL4);

//	hlvds->Instance->PMPLLCPCR = 0x00000001;
//	hlvds->Instance->PSPLLCPCR = 0x00000001;

	hlvds->Instance->PMRLPCR = 0x1F000000;
//	hlvds->Instance->PSRLPCR = 0x1F000000;

	SET_BIT(hlvds->Instance->PSCMCR1, LVDS_PSCMCR1_SLV_CM_EN_DL3	\
									| LVDS_PSCMCR1_SLV_CM_EN_DL2	\
									| LVDS_PSCMCR1_SLV_CM_EN_DL1	\
									| LVDS_PSCMCR1_SLV_CM_EN_DL0);

	SET_BIT(hlvds->Instance->PSCMCR2, LVDS_PSCMCR2_SLV_CM_EN_DL4);

	SET_BIT(hlvds->Instance->PMBCR3, LVDS_PMBCR3_MST_VM_EN_DL3	\
									| LVDS_PMBCR3_MST_VM_EN_DL2	\
									| LVDS_PMBCR3_MST_VM_EN_DL1	\
									| LVDS_PMBCR3_MST_VM_EN_DL0	\
									| LVDS_PMBCR3_MST_VM_EN_DL4);

	SET_BIT(hlvds->Instance->PSBCR3, LVDS_PSBCR3_SLV_VM_EN_DL3	\
									| LVDS_PSBCR3_SLV_VM_EN_DL2	\
									| LVDS_PSBCR3_SLV_VM_EN_DL1	\
									| LVDS_PSBCR3_SLV_VM_EN_DL0	\
									| LVDS_PSBCR3_SLV_VM_EN_DL4);

	SET_BIT(hlvds->Instance->PMBCR1, LVDS_PMBCR1_MST_EN_BIAS_DL3	\
									| LVDS_PMBCR1_MST_EN_BIAS_DL2	\
									| LVDS_PMBCR1_MST_EN_BIAS_DL1	\
									| LVDS_PMBCR1_MST_EN_BIAS_DL0	\
									| LVDS_PMBCR1_MST_EN_BIAS_DL4);

	SET_BIT(hlvds->Instance->PSBCR1, LVDS_PSBCR1_SLV_EN_BIAS_DL3	\
									| LVDS_PSBCR1_SLV_EN_BIAS_DL2	\
									| LVDS_PSBCR1_SLV_EN_BIAS_DL1	\
									| LVDS_PSBCR1_SLV_EN_BIAS_DL0	\
									| LVDS_PSBCR1_SLV_EN_BIAS_DL4);

	SET_BIT(hlvds->Instance->PMCFGCR, LVDS_PMCFGCR_MST_EN_DIG_DL);
	SET_BIT(hlvds->Instance->PSCFGCR, LVDS_PSCFGCR_SLV_EN_DIG_DL);

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_ConfigDataMapping(LVDS_HandleTypeDef *hlvds)
{
	/* TODO Set Data Channels for RGB666 color coding */
	if(!(hlvds->Init.ColorCoding)) /* RGB666 */
		HAL_LVDS_SetPattern(hlvds, HAL_LVDS_Map_RGB666);

	if(hlvds->Init.ColorCoding && hlvds->Init.DataMapping) /* VESA-RGB888 */
		HAL_LVDS_SetPattern(hlvds, HAL_LVDS_Map_VESA_RGB888);

	if(hlvds->Init.ColorCoding && !(hlvds->Init.DataMapping)) /* JEIDA-RGB888 */
		HAL_LVDS_SetPattern(hlvds, HAL_LVDS_Map_JEIDA_RGB888);

	return HAL_OK;
}

/* Exported functions --------------------------------------------------------*/

/** @defgroup lvds_Exported_Functions lvds Exported Functions
  * @{
  */

/** @defgroup lvds_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the lvds
      (+) De-initialize the lvds

@endverbatim
*/

/**
  * @}
  */

/**
  * @brief  Initializes the LVDS according to the specified
  *         parameters in the LVDS_InitTypeDef and create the associated handle.
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @param  PLLInit  pointer to a LVDS_PLLInitTypeDef structure that contains
  *                  the PLL Clock structure definition for the LVDS.
  * @retval HAL status
 */
HAL_StatusTypeDef HAL_LVDS_Init(LVDS_HandleTypeDef *hlvds, LVDS_CfgTypeDef *cfg, LVDS_PLLInitTypeDef *PLLInit)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	/* Initialize the low level hardware */
	if (hlvds->State == HAL_LVDS_STATE_RESET)
		HAL_LVDS_MspInit(hlvds);

	/* Change LVDS peripheral state */
	hlvds->State = HAL_LVDS_STATE_BUSY;

	HAL_LVDS_PHY_Init(hlvds, PLLInit);
	HAL_LVDS_ConfigMode(hlvds, cfg);

	// Fix CDL1CR register
	WRITE_REG(hlvds->Instance->CDL1CR, 0x4321);
//	// Fix CDL2CR register
	WRITE_REG(hlvds->Instance->CDL2CR, 0x59876);

	/****************************** Error management *****************************/

	/* Reset the Error Mask and init the error code */
	hlvds->ErrorMsk = 0U;
	//  TODO Manage LVDS error handling
	//  hlvds->ErrorCode = HAL_LVDS_ERROR_NONE;

	/* Initialize the LVDS state*/
	hlvds->State = HAL_LVDS_STATE_READY;

	return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_PHY_Init(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit)
{
	HAL_StatusTypeDef status;

	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
		return HAL_ERROR;

	if (PLLInit == NULL)
		return HAL_ERROR;

	/*************************** Enable LVDS PLL ***************************/
	/* Release LVDS PHY Master & Slave from reset */
	WRITE_REG(hlvds->Instance->PMGCR, LVDS_PMGCR_MST_DIVIDERS_RSTN | LVDS_PMGCR_MST_RSTZ);
	WRITE_REG(hlvds->Instance->PSGCR, LVDS_PSGCR_SLV_DIVIDERS_RSTN | LVDS_PSGCR_SLV_RSTZ);

	/*********************** Set the LVDS clock parameters ************************/

	/* Set PLL Slv & Mst configs and timings */
	LVDS_PHY_SetPLL(hlvds, PLLInit);

	status = HAL_LVDS_PHY_PLLConfig(hlvds, PLLInit);
	if (status != HAL_OK)
		return status;

	/*************************** Set the PHY parameters ***************************/

	LVDS_PHY_StartMst(hlvds);
    LVDS_PHY_StartSlv(hlvds);

	return HAL_OK;
}

/**
  * @brief  De-initializes the LVDS peripheral registers to their default reset
  *         values.
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LVDS_DeInit(LVDS_HandleTypeDef *hlvds)
{
	/* Check the LVDS handle allocation */
	if (hlvds == NULL)
	{
		return HAL_ERROR;
	}

	/* Change LVDS peripheral state */
	hlvds->State = HAL_LVDS_STATE_BUSY;

	/* TODO: Disable things here */
	/* Disable LVDS module */
	__HAL_LVDS_DISABLE(hlvds);

	/* Disable D-PHY clocks and digital */
	CLEAR_BIT(hlvds->Instance->PMGCR, LVDS_PMGCR_MST_RSTZ);
	CLEAR_BIT(hlvds->Instance->PMGCR, (LVDS_PMGCR_MST_DP_CLK_OUT_ENABLE		|
			LVDS_PMGCR_MST_LS_CLK_OUT_ENABLE		|
			LVDS_PMGCR_MST_BIT_CLK_OUT_ENABLE)	);

	/* Shutdown the LVDS PLL */
	__HAL_LVDS_PLL_DISABLE(hlvds);

	/* Assert LVDS PHY Master & Slave in reset mode */
	CLEAR_BIT(hlvds->Instance->PMGCR, LVDS_PMGCR_MST_DIVIDERS_RSTN | LVDS_PMGCR_MST_RSTZ);
	CLEAR_BIT(hlvds->Instance->PSGCR, LVDS_PSGCR_SLV_DIVIDERS_RSTN | LVDS_PSGCR_SLV_RSTZ);

	/* DeInit the low level hardware */
	HAL_LVDS_MspDeInit(hlvds);

	/* Reinitialize ErrorCode */
	/* TODO: implement */
	//	hlvds->ErrorCode = HAL_LVDS_ERROR_NONE;

	/* Initialize the LVDS state */
	hlvds->State = HAL_LVDS_STATE_RESET;

	/* Release Lock */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

/**
  * @brief  Initializes the LVDS MSP.
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @retval None
  */
__weak void HAL_LVDS_MspInit(LVDS_HandleTypeDef *hlvds)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlvds);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LVDS_MspInit could be implemented in the user file
   */
}

/**
  * @brief  De-initializes the LVDS MSP.
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @retval None
  */
__weak void HAL_LVDS_MspDeInit(LVDS_HandleTypeDef *hlvds)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlvds);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LVDS_MspDeInit could be implemented in the user file
   */
}

HAL_StatusTypeDef HAL_LVDS_ConfigMode(LVDS_HandleTypeDef *hlvds, LVDS_CfgTypeDef *cfg)
{
	uint32_t distribution;
	uint32_t status = HAL_OK;

	/* Check function parameters */
	assert_param(IS_LVDS_LINK(cfg->NumberOfLinks));
	assert_param(IS_LVDS_DISPLAY(cfg->NumberOfDisplays));
	assert_param(IS_LVDS_VS_POLARITY(cfg->VSPolarity));
	assert_param(IS_LVDS_HS_POLARITY(cfg->HSPolarity));
	assert_param(IS_LVDS_DE_POLARITY(cfg->DEPolarity));
	assert_param(IS_LVDS_LINK_PHASE(cfg->LinkPhase));

	/* Set channel distribution */
	CLEAR_BIT(hlvds->Instance->CR, LVDS_CR_LKMOD);

	distribution = (LVDS_CLOCK_LANE_MST << LVDS_CDL1CR_DISTR0_Pos) + (LVDS_DATA_LANE_0 << LVDS_CDL1CR_DISTR1_Pos) \
				+ (LVDS_DATA_LANE_1 << LVDS_CDL1CR_DISTR2_Pos) + (LVDS_DATA_LANE_2 << LVDS_CDL1CR_DISTR3_Pos)
				+ (LVDS_DATA_LANE_3 << LVDS_CDL1CR_DISTR4_Pos);
	HAL_LVDS_SetChannelDistribution(hlvds, LVDS_LINK1_SELECT, distribution);

	if(cfg->NumberOfLinks)
	{
		SET_BIT(hlvds->Instance->CR, LVDS_CR_LKMOD);

		distribution = (LVDS_CLOCK_LANE_SLV << LVDS_CDL2CR_DISTR0_Pos) + (LVDS_DATA_LANE_4 << LVDS_CDL2CR_DISTR1_Pos)
					+ (LVDS_DATA_LANE_5 << LVDS_CDL2CR_DISTR2_Pos) + (LVDS_DATA_LANE_6 << LVDS_CDL2CR_DISTR3_Pos)
					+ (LVDS_DATA_LANE_7 << LVDS_CDL2CR_DISTR4_Pos);

		HAL_LVDS_SetChannelDistribution(hlvds, LVDS_LINK2_SELECT, distribution);
	}

	if(cfg->NumberOfDisplays)
	{
		distribution = (LVDS_CLOCK_LANE_MST << LVDS_CDL2CR_DISTR0_Pos) + (LVDS_DATA_LANE_0 << LVDS_CDL2CR_DISTR1_Pos)
					+ (LVDS_DATA_LANE_1 << LVDS_CDL2CR_DISTR2_Pos) + (LVDS_DATA_LANE_2 << LVDS_CDL2CR_DISTR3_Pos)
					+ (LVDS_DATA_LANE_3 << LVDS_CDL2CR_DISTR4_Pos);

		HAL_LVDS_SetChannelDistribution(hlvds, LVDS_LINK2_SELECT, distribution);
	}

	/* Set Data Mapping */
	status = HAL_LVDS_ConfigDataMapping(hlvds);

	/* Set signal polarity */
	CLEAR_BIT(hlvds->Instance->CR, LVDS_CR_VSPOL | LVDS_CR_HSPOL | LVDS_CR_DEPOL);
	SET_BIT(hlvds->Instance->CR, cfg->VSPolarity | cfg->HSPolarity | cfg->DEPolarity);

	/* Set link phase */
	CLEAR_BIT(hlvds->Instance->CR, LVDS_CR_LKPHA);
	if (cfg->NumberOfLinks)
		SET_BIT(hlvds->Instance->CR, cfg->LinkPhase);

	return status;
}

/**
  * @brief  Start the LVDS module
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LVDS_Start(LVDS_HandleTypeDef *hlvds)
{
  /* Process locked */
  __HAL_LOCK(hlvds);

  /* Enable the LVDS host */
  __HAL_LVDS_ENABLE(hlvds);

  /* Process unlocked */
  __HAL_UNLOCK(hlvds);

  return HAL_OK;
}

/**
  * @brief  Stop the LVDS module
  * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
  *               the configuration information for the LVDS.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LVDS_Stop(LVDS_HandleTypeDef *hlvds)
{
  /* Process locked */
  __HAL_LOCK(hlvds);

  /* Disable the LVDS host */
  __HAL_LVDS_DISABLE(hlvds);

  /* Process unlocked */
  __HAL_UNLOCK(hlvds);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_SetPattern(LVDS_HandleTypeDef *hlvds, const HAL_LVDS_MapTypeDef pattern[5][7])
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	/* TODO check the parameters */
//	assert_param(IS_PATTERN_SIZE(pattern));

	/* Clear the generator */
	CLEAR_REG(hlvds->Instance->DMLCR0);
	CLEAR_REG(hlvds->Instance->DMMCR0);
	CLEAR_REG(hlvds->Instance->DMLCR1);
	CLEAR_REG(hlvds->Instance->DMMCR1);
	CLEAR_REG(hlvds->Instance->DMLCR2);
	CLEAR_REG(hlvds->Instance->DMMCR2);
	CLEAR_REG(hlvds->Instance->DMLCR3);
	CLEAR_REG(hlvds->Instance->DMMCR3);
	CLEAR_REG(hlvds->Instance->DMLCR4);
	CLEAR_REG(hlvds->Instance->DMMCR4);

	/* Set the pattern in Data Mapping */
	WRITE_REG(hlvds->Instance->DMLCR0, ((pattern[0][0]) + (pattern[0][1] << 5) + (pattern[0][2] << 10) + (pattern[0][3] << 15)));
	WRITE_REG(hlvds->Instance->DMMCR0, ((pattern[0][4]) + (pattern[0][5] << 5) + (pattern[0][6] << 10)));
	WRITE_REG(hlvds->Instance->DMLCR1, ((pattern[1][0]) + (pattern[1][1] << 5) + (pattern[1][2] << 10) + (pattern[1][3] << 15)));
	WRITE_REG(hlvds->Instance->DMMCR1, ((pattern[1][4]) + (pattern[1][5] << 5) + (pattern[1][6] << 10)));
	WRITE_REG(hlvds->Instance->DMLCR2, ((pattern[2][0]) + (pattern[2][1] << 5) + (pattern[2][2] << 10) + (pattern[2][3] << 15)));
	WRITE_REG(hlvds->Instance->DMMCR2, ((pattern[2][4]) + (pattern[2][5] << 5) + (pattern[2][6] << 10)));
	WRITE_REG(hlvds->Instance->DMLCR3, ((pattern[3][0]) + (pattern[3][1] << 5) + (pattern[3][2] << 10) + (pattern[3][3] << 15)));
	WRITE_REG(hlvds->Instance->DMMCR3, ((pattern[3][4]) + (pattern[3][5] << 5) + (pattern[3][6] << 10)));
	WRITE_REG(hlvds->Instance->DMLCR4, ((pattern[4][0]) + (pattern[4][1] << 5) + (pattern[4][2] << 10) + (pattern[4][3] << 15)));
	WRITE_REG(hlvds->Instance->DMMCR4, ((pattern[4][4]) + (pattern[4][5] << 5) + (pattern[4][6] << 10)));

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_BistStart(LVDS_HandleTypeDef *hlvds, uint32_t polynome)
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	/* TODO check the parameters */
	assert_param(IS_LVDS_PRBS_POLYNOME(polynome));

	CLEAR_BIT(hlvds->Instance->CDL2CR, LVDS_CDL2CR_PRBS_Msk);
	SET_BIT(hlvds->Instance->CDL2CR, polynome);

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}


HAL_StatusTypeDef HAL_LVDS_BistStop(LVDS_HandleTypeDef *hlvds)
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	CLEAR_BIT(hlvds->Instance->CDL2CR, LVDS_CDL2CR_PRBS_Msk);

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

HAL_StatusTypeDef HAL_LVDS_BistConfig(LVDS_HandleTypeDef *hlvds, uint32_t link, uint32_t custom)
{
	return HAL_LVDS_SetChannelDistribution(hlvds, link, custom);
}

HAL_StatusTypeDef HAL_LVDS_SetLanePolarity(LVDS_HandleTypeDef *hlvds, uint32_t link, uint32_t channels)
{
	HAL_StatusTypeDef status = HAL_OK;

	uint32_t lk1pol, lk2pol;
	uint32_t lk2pol_msk = (LVDS_CR_LK2POL_Msk >> LVDS_CR_LK1POL_Pos);
	uint32_t lk1pol_msk = (LVDS_CR_LK1POL_Msk >> LVDS_CR_LK1POL_Pos);

	/* Process locked */
	__HAL_LOCK(hlvds);

	/* TODO: Check function parameters */
	assert_param(IS_LVDS_LINK(link));
	/* uint32_t channels has to be between 0x00U and 0x1FU */
	assert_param(IS_LVDS_CHANNEL(channels));


	/* Computing LK1POL & LK2POL
	 	 channels[9:0] is LVDS_CR.LK2POL + LVDS_CR.LK1POL */
	lk1pol = (channels & lk1pol_msk);
	lk2pol = ((channels & lk2pol_msk) >> 5U);

	/* Set Link polarity */
	CLEAR_BIT(hlvds->Instance->CR, LVDS_CR_LK1POL);
	SET_BIT(hlvds->Instance->CR, (lk1pol << LVDS_CR_LK1POL_Pos));

	CLEAR_BIT(hlvds->Instance->CR, LVDS_CR_LK2POL);
	SET_BIT(hlvds->Instance->CR, (lk2pol << LVDS_CR_LK2POL_Pos));

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return status;
}

/**
 * @brief  Set custom value for a given lane
 * @param  hlvds  		pointer to a LVDS_HandleTypeDef structure that contains
 *               			the configuration information for the LVDS.
 * @param  channel   Lane to be modified.
 * 										This parameter can be LVDS_LINK1_SELECT or LVDS_LINK2_SELECT
 * @param  distribution 		Custom value to modify
 * 										This parameter can be any value of LVDS_Channel_Distribution_values.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_LVDS_SetChannelDistribution(LVDS_HandleTypeDef *hlvds, uint32_t link, uint32_t distribution)
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	/* Check function parameters */
	assert_param(IS_LVDS_LINK_SELECTED(link));
	assert_param(IS_LVDS_CHANNEL(distribution));

	if (link == LVDS_LINK1_SELECT) {
		CLEAR_REG(hlvds->Instance->CDL1CR);
		WRITE_REG(hlvds->Instance->CDL1CR, distribution);
	} else {
		CLEAR_REG(hlvds->Instance->CDL2CR);
		WRITE_REG(hlvds->Instance->CDL2CR, distribution);
	}

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

/**
 * @brief  Set custom timing for the PHY
 * @param  hlvds  pointer to a LVDS_HandleTypeDef structure that contains
 *               the configuration information for the LVDS.
 * @param  Timing  PHY timing to be adjusted.
 *                 This parameter can be any value of @arg LVDS_PHY_Timing
 * @param  State  ENABLE or DISABLE
 * @param  Value  Custom value of the timing
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_LVDS_PHY_SetTimings(LVDS_HandleTypeDef *hlvds, uint32_t Timing, FunctionalState State, uint32_t Value)
{
	/* Process locked */
	__HAL_LOCK(hlvds);

	/* TODO: Check function parameters */
	//  assert_param(IS_DSI_PHY_TIMING(Timing));
	//  assert_param(IS_FUNCTIONAL_STATE(State));

	//	TODO: Update

	/* Process unlocked */
	__HAL_UNLOCK(hlvds);

	return HAL_OK;
}

/**
 * @brief	 Return the LVDS state
 * @param	 hlvds	pointer to a LVDS_HandleTypeDef structure that contains
 * 								the configuration information for the LVDS.
 * @retval HAL  state
 */
uint32_t HAL_LVDS_GetState(LVDS_HandleTypeDef *hlvds)
{
	/* Get the state and return it */
	return hlvds->State;
}


#endif /* HAL_LVDS_MODULE_ENABLED */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
