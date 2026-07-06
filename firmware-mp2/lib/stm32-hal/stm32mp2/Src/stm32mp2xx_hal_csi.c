/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_csi.c
  * @author  MCD Application Team
  * @brief   CSI HAL module driver
  *          This file provides firmware functions to manage the following
  *          functionalities of the Digital Camera Interface (CSI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================


  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 STMicroelectronics</center></h2>
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
/** @defgroup CSI CSI
  * @brief CSI HAL module driver
  * @{
  */

#ifdef HAL_CSI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define VC0_IT (CSI_IER0_LB0IE | CSI_IER0_TIM0IE | CSI_IER0_SOF0IE | CSI_IER0_EOF0IE)
#define VC1_IT (CSI_IER0_LB1IE | CSI_IER0_TIM1IE | CSI_IER0_SOF1IE | CSI_IER0_EOF1IE)
#define VC2_IT (CSI_IER0_LB2IE | CSI_IER0_TIM2IE | CSI_IER0_SOF2IE | CSI_IER0_EOF2IE)
#define VC3_IT (CSI_IER0_LB3IE | CSI_IER0_TIM3IE | CSI_IER0_SOF3IE | CSI_IER0_EOF3IE)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup CSI_Exported_Functions CSI Exported Functions
  * @{
  */

/** @defgroup CSI_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the CSI
      (+) De-initialize the CSI

@endverbatim
  * @{
  */

/*
 * Table of hsfreqrange & osc_freq_target for the Synopsis D-PHY
 */
struct SNPS_Freqs {
  uint32_t hsfreqrange;
  uint32_t osc_freq_target;
} SNPS_Freqs [] = {
  { 0x00U, 460U },	/* HAL_CSI_BT_80 */
  { 0x10U, 460U },	/* HAL_CSI_BT_90 */
  { 0x20U, 460U },	/* HAL_CSI_BT_100 */
  { 0x30U, 460U },	/* HAL_CSI_BT_110 */
  { 0x01U, 460U },	/* HAL_CSI_BT_120 */
  { 0x11U, 460U },	/* HAL_CSI_BT_130 */
  { 0x21U, 460U },	/* HAL_CSI_BT_140 */
  { 0x31U, 460U },	/* HAL_CSI_BT_150 */
  { 0x02U, 460U },	/* HAL_CSI_BT_160 */
  { 0x12U, 460U },	/* HAL_CSI_BT_170 */
  { 0x22U, 460U },	/* HAL_CSI_BT_180 */
  { 0x32U, 460U },	/* HAL_CSI_BT_190 */
  { 0x03U, 460U },	/* HAL_CSI_BT_205 */
  { 0x13U, 460U },	/* HAL_CSI_BT_220 */
  { 0x23U, 460U },	/* HAL_CSI_BT_235 */
  { 0x33U, 460U },	/* HAL_CSI_BT_250 */
  { 0x04U, 460U },	/* HAL_CSI_BT_275 */
  { 0x14U, 460U },	/* HAL_CSI_BT_300 */
  { 0x25U, 460U },	/* HAL_CSI_BT_325 */
  { 0x35U, 460U },	/* HAL_CSI_BT_350 */
  { 0x05U, 460U },	/* HAL_CSI_BT_400 */
  { 0x16U, 460U },	/* HAL_CSI_BT_450 */
  { 0x26U, 460U },	/* HAL_CSI_BT_500 */
  { 0x37U, 460U },	/* HAL_CSI_BT_550 */
  { 0x07U, 460U },	/* HAL_CSI_BT_600 */
  { 0x18U, 460U },	/* HAL_CSI_BT_650 */
  { 0x28U, 460U },	/* HAL_CSI_BT_700 */
  { 0x39U, 460U },	/* HAL_CSI_BT_750 */
  { 0x09U, 460U },	/* HAL_CSI_BT_800 */
  { 0x19U, 460U },	/* HAL_CSI_BT_850 */
  { 0x29U, 460U },	/* HAL_CSI_BT_900 */
  { 0x3AU, 460U },	/* HAL_CSI_BT_950 */
  { 0x0AU, 460U },	/* HAL_CSI_BT_1000 */
  { 0x1AU, 460U },	/* HAL_CSI_BT_1050 */
  { 0x2AU, 460U },	/* HAL_CSI_BT_1100 */
  { 0x3BU, 460U },	/* HAL_CSI_BT_1150 */
  { 0x0BU, 460U },	/* HAL_CSI_BT_1200 */
  { 0x1BU, 460U },	/* HAL_CSI_BT_1250 */
  { 0x2BU, 460U },	/* HAL_CSI_BT_1300 */
  { 0x3CU, 460U },	/* HAL_CSI_BT_1350 */
  { 0x0CU, 460U },	/* HAL_CSI_BT_1400 */
  { 0x1CU, 460U },	/* HAL_CSI_BT_1450 */
  { 0x2CU, 460U },	/* HAL_CSI_BT_1500 */
  { 0x3DU, 285U },	/* HAL_CSI_BT_1550 */
  { 0x0DU, 295U },	/* HAL_CSI_BT_1600 */
  { 0x1DU, 304U },	/* HAL_CSI_BT_1650 */
  { 0x2EU, 313U },	/* HAL_CSI_BT_1700 */
  { 0x3EU, 322U },	/* HAL_CSI_BT_1750 */
  { 0x0EU, 331U },	/* HAL_CSI_BT_1800 */
  { 0x1EU, 341U },	/* HAL_CSI_BT_1850 */
  { 0x2FU, 350U },	/* HAL_CSI_BT_1900 */
  { 0x3FU, 359U },	/* HAL_CSI_BT_1950 */
  { 0x0FU, 368U },	/* HAL_CSI_BT_2000 */
  { 0x40U, 377U },	/* HAL_CSI_BT_2050 */
  { 0x41U, 387U },	/* HAL_CSI_BT_2100 */
  { 0x42U, 396U },	/* HAL_CSI_BT_2150 */
  { 0x43U, 405U },	/* HAL_CSI_BT_2200 */
  { 0x44U, 414U },	/* HAL_CSI_BT_2250 */
  { 0x45U, 423U },	/* HAL_CSI_BT_2300 */
  { 0x46U, 432U },	/* HAL_CSI_BT_2350 */
  { 0x47U, 442U },	/* HAL_CSI_BT_2400 */
  { 0x48U, 451U },	/* HAL_CSI_BT_2450 */
  { 0x49U, 460U },	/* HAL_CSI_BT_2500 */
};

/**
  * @brief  Write register into the D-PHY via the Test registers
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for CSI.
  * @retval HAL status
  */
void HAL_CSI_WritePHYReg(CSI_HandleTypeDef *pHcsi, uint32_t reg_msb, uint32_t reg_lsb, uint32_t val)
{
  /* Based on sequence described at section 5.2.3.2 of DesignWave document */
  /* For writing the 4-bit testcode MSBs */
  /* Set testen to high */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to high */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, CSI_PTCR0_TCKEN);

  /* Place 0x00 in testdin */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to low (with the falling edge on testclk, the testdin signal content is latched internally) */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, 0x00);

  /* Set testen to low */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, 0x00);

  /* Place the 8-bit word corresponding to the testcode MSBs in testdin */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, reg_msb & 0xffU);

  /* Set testclk to high */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, CSI_PTCR0_TCKEN);

  /* For writing the 8-bit testcode LSBs */
  /* Set testclk to low */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, 0x00);

  /* Set testen to high */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to high */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, CSI_PTCR0_TCKEN);

  /* Place the 8-bit word test data in testdin */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, CSI_PTCR1_TWM | (reg_lsb & 0xffU));

  /* Set testclk to low (with the falling edge on testclk, the testdin signal content is latched internally) */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, 0x00);

  /* Set testen to low */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, 0x00);

  /* For writing the data */
  /* Place the 8-bit word corresponding to the page offset in testdin */
  __HAL_CSI_SET_REG(pHcsi, PTCR1, val & 0xffU);

  /* Set testclk to high (test data is programmed internally */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, CSI_PTCR0_TCKEN);

  /* Finish by setting testclk to low */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, 0x00);
}

/**
  * @brief  Initializes the CSI according to the specified
  *         parameters in the CSI_InitTypeDef and create the associated handle.
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *                  the configuration information for CSI.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_Init(CSI_HandleTypeDef *pHcsi)
{
  uint32_t nb_lanes;

  /* Check pointer validity */
  if (pHcsi == NULL)
  {
    return HAL_ERROR;
  }

#if (USE_HAL_CSI_REGISTER_CALLBACKS == 1)

#else
  /* Check HAL state */
  if (pHcsi->State == HAL_CSI_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_CSI_MspInit(pHcsi);
  }
#endif /* USE_HAL_CSI_REGISTER_CALLBACKS */

  /* Ensure the CSI is disabled */
  __HAL_CSI_CLEAR_BIT(pHcsi, CR, CSI_CR_CSIEN);

  /* Configure the Lane Merger */
  if ((pHcsi->Init.LaneMerger.PhysicalLane0_Status == HAL_CSI_LANE_ENABLED) &&
      (pHcsi->Init.LaneMerger.PhysicalLane1_Status == HAL_CSI_LANE_ENABLED))
  {
    nb_lanes = HAL_CSI_LM_DUAL_LANE;
  }
  else if ((pHcsi->Init.LaneMerger.PhysicalLane0_Status == HAL_CSI_LANE_DISABLED) &&
           (pHcsi->Init.LaneMerger.PhysicalLane1_Status == HAL_CSI_LANE_DISABLED))
  {
    /* This case doesn't make any sense */
    return HAL_ERROR;
  }
  else
  {
    nb_lanes = HAL_CSI_LM_SINGLE_LANE;
  }

  /* Check Lane Merger configuration - mapping can be either LANE0 or LANE1
   and cannot be same for both physical lanes */
  if (((pHcsi->Init.LaneMerger.PhysicalLane0_Mapping != HAL_CSI_LM_LOGIC_LANE0) &&
       (pHcsi->Init.LaneMerger.PhysicalLane0_Mapping != HAL_CSI_LM_LOGIC_LANE1)) ||
      ((pHcsi->Init.LaneMerger.PhysicalLane1_Mapping != HAL_CSI_LM_LOGIC_LANE0) &&
       (pHcsi->Init.LaneMerger.PhysicalLane1_Mapping != HAL_CSI_LM_LOGIC_LANE1)) ||
      (pHcsi->Init.LaneMerger.PhysicalLane0_Mapping == pHcsi->Init.LaneMerger.PhysicalLane1_Mapping))
  {
    return HAL_ERROR;
  }

  __HAL_CSI_SET_REG(pHcsi, LMCFGR, nb_lanes |
                    ((pHcsi->Init.LaneMerger.PhysicalLane0_Mapping) << CSI_LMCFGR_DL0MAP_Pos) |
                    ((pHcsi->Init.LaneMerger.PhysicalLane1_Mapping) << CSI_LMCFGR_DL1MAP_Pos));

  /* Configure the watchdog counter */
  __HAL_CSI_SET_REG(pHcsi, WDR, pHcsi->Init.WatchdogCnt & CSI_WDR_CNT_Msk);

  /* Enable the CSI */
  __HAL_CSI_SET_BIT(pHcsi, CR, CSI_CR_CSIEN);

  /* Enable some interrupts, not related to virtual channels - all error cases */
  __HAL_CSI_ENABLE_IT(pHcsi, CSI_IER0_SYNCERRIE | CSI_IER0_WDERRIE |
                      CSI_IER0_SPKTERRIE | CSI_IER0_IDERRIE |
                      CSI_IER0_CECCERRIE | CSI_IER0_ECCERRIE |
                      CSI_IER0_CRCERRIE | CSI_IER0_SPKTIE |
                      CSI_IER0_CCFIFOFIE);

  if (pHcsi->Init.LaneMerger.PhysicalLane0_Status == HAL_CSI_LANE_ENABLED)
  {
    __HAL_CSI_ENABLE_PHY_IT(pHcsi, CSI_IER1_ESOTDL0IE | CSI_IER1_ESOTSYNCDL0IE |
                            CSI_IER1_EESCDL0IE | CSI_IER1_ESYNCESCDL0IE |
                            CSI_IER1_ECTRLDL0IE);
  }

  if (pHcsi->Init.LaneMerger.PhysicalLane1_Status == HAL_CSI_LANE_ENABLED)
  {
    __HAL_CSI_ENABLE_PHY_IT(pHcsi, CSI_IER1_ESOTDL1IE | CSI_IER1_ESOTSYNCDL1IE |
                            CSI_IER1_EESCDL1IE | CSI_IER1_ESYNCESCDL1IE |
                            CSI_IER1_ECTRLDL1IE);
  }

  /* Start D-PHY Configuration - based on DesignWare spec, section 5.2.4.1 */
  /* Stop the D-PHY */
  __HAL_CSI_CLEAR_BIT(pHcsi, PRCR, CSI_PRCR_PEN);

  /* Get the D-PHY enabledb but with all lanes disabled */
  __HAL_CSI_SET_REG(pHcsi, PCR, 0x00);

  /* Set the testclk (clock enable) on during 15ns */
  __HAL_CSI_SET_REG(pHcsi, PTCR0, CSI_PTCR0_TCKEN);

  HAL_Delay(1);

  __HAL_CSI_SET_REG(pHcsi, PTCR0, 0x00);

  /* Set hsfreqrange */
  __HAL_CSI_SET_REG(pHcsi, PFCR, (0x28U << CSI_PFCR_CCFR_Pos) |
                    (SNPS_Freqs[pHcsi->Init.PhyBitrate].hsfreqrange << CSI_PFCR_HSFR_Pos));

  /* set reg @08 deskew_polarity_rw 1'b1 */
  HAL_CSI_WritePHYReg(pHcsi, 0x00, 0x08, 0x38);

  /* set reg @0xE4 counter_for_des_en_config_if_rx 0x10 + DLL prog EN */
  /* This is because 13<= cfgclkfreqrange[5:0]<=38 */
  HAL_CSI_WritePHYReg(pHcsi, 0x00, 0xe4, 0x11);

  /* set reg @0xe3 & reg @0xe2 value DLL target oscilation freq */
  /* Based on the table page 77, osc_freq_target */
  HAL_CSI_WritePHYReg(pHcsi, 0x00, 0xe3,
		      SNPS_Freqs[pHcsi->Init.PhyBitrate].osc_freq_target >> 8);
  HAL_CSI_WritePHYReg(pHcsi, 0x00, 0xe3,
		      SNPS_Freqs[pHcsi->Init.PhyBitrate].osc_freq_target & 0xFFU);

  /* set basedir_0 to RX - Christophe DLD 0 RX, 1 TX. Synopsys 1 RX 0 TX  + freq range */
  __HAL_CSI_SET_REG(pHcsi, PFCR, (0x28U << CSI_PFCR_CCFR_Pos) |
                    (SNPS_Freqs[pHcsi->Init.PhyBitrate].hsfreqrange << CSI_PFCR_HSFR_Pos) | CSI_PFCR_DLD);

  /* Enable the D-PHY_RX lane(s) etc */
  __HAL_CSI_SET_REG(pHcsi, PCR,
                    ((pHcsi->Init.LaneMerger.PhysicalLane0_Status == HAL_CSI_LANE_ENABLED) ?
                     (uint32_t)CSI_PCR_DL0EN : 0U) |
                    ((pHcsi->Init.LaneMerger.PhysicalLane1_Status == HAL_CSI_LANE_ENABLED) ?
                     (uint32_t)CSI_PCR_DL1EN : 0U) |
                    CSI_PCR_CLEN);

  /* Enable the D-PHY_RX lane(s) etc */
  __HAL_CSI_SET_REG(pHcsi, PCR,
                    ((pHcsi->Init.LaneMerger.PhysicalLane0_Status == HAL_CSI_LANE_ENABLED) ? 
                     (uint32_t)CSI_PCR_DL0EN : 0U) |
                    ((pHcsi->Init.LaneMerger.PhysicalLane1_Status == HAL_CSI_LANE_ENABLED) ? 
                     (uint32_t)CSI_PCR_DL1EN : 0U) |
                    CSI_PCR_CLEN | CSI_PCR_PWRDOWN);

  /* Enable PHY, out of reset */
  __HAL_CSI_SET_BIT(pHcsi, PRCR, CSI_PRCR_PEN);

  /* Remove the force */
  __HAL_CSI_SET_REG(pHcsi, PMCR, 0x00);

  /* Change the CSI state */
  pHcsi->State = HAL_CSI_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  De-initializes the CSI peripheral registers to their default reset
  *         values.
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for CSI.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_DeInit(CSI_HandleTypeDef *pHcsi)
{
  /* Check pointer validity */
  if (pHcsi == NULL)
  {
    return HAL_ERROR;
  }

  /* PowerDown the D-PHY_RX lane(s) etc */
  __HAL_CSI_SET_REG(pHcsi, PCR, 0);

  /* Disable some interrupts, not related to virtual channels - all error cases */
  __HAL_CSI_DISABLE_IT(pHcsi, CSI_IER0_SYNCERRIE | CSI_IER0_WDERRIE |
                       CSI_IER0_SPKTERRIE | CSI_IER0_IDERRIE |
                       CSI_IER0_CECCERRIE | CSI_IER0_ECCERRIE |
                       CSI_IER0_CRCERRIE);
  __HAL_CSI_DISABLE_PHY_IT(pHcsi, CSI_IER1_ESOTDL0IE | CSI_IER1_ESOTSYNCDL0IE |
                           CSI_IER1_EESCDL0IE | CSI_IER1_ESYNCESCDL0IE |
                           CSI_IER1_ECTRLDL0IE | CSI_IER1_ESOTDL1IE |
                           CSI_IER1_ESOTSYNCDL1IE | CSI_IER1_EESCDL1IE |
                           CSI_IER1_ESYNCESCDL1IE | CSI_IER1_ECTRLDL1IE);

  /* Disable the CSI */
  __HAL_CSI_CLEAR_BIT(pHcsi, CR, CSI_CR_CSIEN);

  /* Initialize the CSI state*/
  pHcsi->State = HAL_CSI_STATE_RESET;

#if (USE_HAL_CSI_REGISTER_CALLBACKS == 1)
  if (pHcsi->MspDeInitCallback == NULL)
  {
    pHcsi->MspDeInitCallback = HAL_CSI_MspDeInit;
  }

  /* DeInit the low level hardware */
  pHcsi->MspDeInitCallback(pHcsi);
#else
  /* DeInit the low level hardware */
  HAL_CSI_MspDeInit(pHcsi);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

  return HAL_OK;
}

/**
  * @brief  Configure a virtual channel of the CSI (filtering)
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure
  * @param  vchan ID of the virtual channel to configure (0..3)
  * @param  Config pointer to a CSI_VirtualChannelConfigTypeDef structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_ConfigVirtualChan(CSI_HandleTypeDef *pHcsi, uint32_t vchan,
                                            CSI_VirtualChannelConfigTypeDef *Config)
{
  uint32_t cfgr1 = 0;
  uint32_t cfgr2 = 0;
  uint32_t cfgr3 = 0;
  uint32_t cfgr4 = 0;
  struct dt_cfg
  {
    uint32_t *reg;
    uint32_t offset;
  } DTCFG[HAL_CSI_DATATYPE_NB] =
  {
    { &cfgr1, 16 }, /* DT0 */
    { &cfgr2, 0 },  /* DT1 */
    { &cfgr2, 16 }, /* DT2 */
    { &cfgr3, 0 },  /* DT3 */
    { &cfgr3, 16 }, /* DT4 */
    { &cfgr4, 0 },  /* DT5 */
    { &cfgr4, 16 }, /* DT6 */
  };

  /* Check pointer and input values validity */
  if ((pHcsi == NULL) || (Config == NULL) || (vchan >= HAL_CSI_VIRTUAL_CHANNEL_NB))
  {
    return HAL_ERROR;
  }


  /* Handle the ALLDT case first */
  if (Config->NoDataTypeFiltering == 1U)
  {
    cfgr1 = ((uint32_t)Config->CommonDataTypeFormat << CSI_VC0CFGR1_CDTFT_Pos) | CSI_VC0CFGR1_ALLDT;
  }
  else
  {
    uint32_t i;
    for (i = 0U; i < HAL_CSI_DATATYPE_NB; i++)
    {
      if (Config->DataType[i].Enable == 0U)
      {
        continue;
      }
      *(DTCFG[i].reg) |= (((uint32_t)Config->DataType[i].Class) << (DTCFG[i].offset)) | \
        		  ((uint32_t)Config->DataType[i].DataTypeFormat << (DTCFG[i].offset + 8U));
      cfgr1 |= (1UL << (CSI_VC0CFGR1_DT0EN_Pos + i));
    }
  }

  switch (vchan)
  {
    case 0:
      __HAL_CSI_SET_REG(pHcsi, VC0CFGR1, cfgr1);
      __HAL_CSI_SET_REG(pHcsi, VC0CFGR2, cfgr2);
      __HAL_CSI_SET_REG(pHcsi, VC0CFGR3, cfgr3);
      __HAL_CSI_SET_REG(pHcsi, VC0CFGR4, cfgr4);
      break;
    case 1:
      __HAL_CSI_SET_REG(pHcsi, VC1CFGR1, cfgr1);
      __HAL_CSI_SET_REG(pHcsi, VC1CFGR2, cfgr2);
      __HAL_CSI_SET_REG(pHcsi, VC1CFGR3, cfgr3);
      __HAL_CSI_SET_REG(pHcsi, VC1CFGR4, cfgr4);
      break;
    case 2:
      __HAL_CSI_SET_REG(pHcsi, VC2CFGR1, cfgr1);
      __HAL_CSI_SET_REG(pHcsi, VC2CFGR2, cfgr2);
      __HAL_CSI_SET_REG(pHcsi, VC2CFGR3, cfgr3);
      __HAL_CSI_SET_REG(pHcsi, VC2CFGR4, cfgr4);
      break;
    case 3:
      __HAL_CSI_SET_REG(pHcsi, VC3CFGR1, cfgr1);
      __HAL_CSI_SET_REG(pHcsi, VC3CFGR2, cfgr2);
      __HAL_CSI_SET_REG(pHcsi, VC3CFGR3, cfgr3);
      __HAL_CSI_SET_REG(pHcsi, VC3CFGR4, cfgr4);
      break;
  default:
    /* do something*/
    break;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the LineByte triggers
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure
  * @param  counter ID of the counter to configure (0..3)
  * @param  Config pointer to a CSI_LineByteCounterConfigTypeDef structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_ConfigLineByteCounter(CSI_HandleTypeDef *pHcsi, uint32_t counter,
                                                const CSI_LineByteCounterConfigTypeDef *Config)
{
  uint32_t conf_reg = 0x00;
  uint32_t reg;
  struct
  {
    uint32_t vc_off;
    uint32_t en_off;
  }const lbxvc[HAL_CSI_COUNTER_NB] =
  {
    { CSI_PRGITR_LB0VC_Pos, CSI_PRGITR_LB0EN_Pos }, /* LB0 */
    { CSI_PRGITR_LB1VC_Pos, CSI_PRGITR_LB1EN_Pos }, /* LB1 */
    { CSI_PRGITR_LB2VC_Pos, CSI_PRGITR_LB2EN_Pos }, /* LB2 */
    { CSI_PRGITR_LB3VC_Pos, CSI_PRGITR_LB3EN_Pos }, /* LB3 */
  };

  /* Check pointer and input values validity */
  if ((pHcsi == NULL) || (Config == NULL) || (counter >= (uint32_t)HAL_CSI_COUNTER_NB))
  {
    return HAL_ERROR;
  }

  if (Config->Enable == 1U)
  {
    conf_reg = ((uint32_t)Config->LineCnt << CSI_LB0CFGR_LINECNT_Pos) | (uint32_t)Config->ByteCnt;
  }

  /* Stop the LineByte counter (if it is running) */
  reg = __HAL_CSI_GET_MASKED_REG(pHcsi, PRGITR, 0xffffffffU);
  reg &= ~(0x01U << lbxvc[counter].en_off);
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  /* Apply the configuration */
  switch (counter)
  {
    case 0:
      __HAL_CSI_SET_REG(pHcsi, LB0CFGR, conf_reg);
      break;
    case 1:
      __HAL_CSI_SET_REG(pHcsi, LB1CFGR, conf_reg);
      break;
    case 2:
      __HAL_CSI_SET_REG(pHcsi, LB2CFGR, conf_reg);
      break;
    case 3:
      __HAL_CSI_SET_REG(pHcsi, LB3CFGR, conf_reg);
      break;
  default:
    /*do something*/
    break;
  }

  reg &= ~(0x03U << lbxvc[counter].vc_off);
  reg |= (Config->VC << lbxvc[counter].vc_off);
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  reg |= (~~Config->Enable << lbxvc[counter].en_off);
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  return HAL_OK;
}

/**
  * @brief  Configure the Timer triggers
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure
  * @param  timer ID of the counter to configure (0..3)
  * @param  Config pointer to a CSI_TimerConfigTypeDef structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_ConfigTimer(CSI_HandleTypeDef *pHcsi, uint32_t timer, const CSI_TimerConfigTypeDef *Config)
{
  uint32_t conf_reg = 0x00;
  uint32_t reg;
  struct
  {
    uint32_t vc_off;
    uint32_t start_off;
    uint32_t en_off;
  } const tim[HAL_CSI_TIMER_NB] =
  {
    { CSI_PRGITR_TIM0VC_Pos, CSI_PRGITR_TIM0EOF_Pos, CSI_PRGITR_TIM0EN_Pos }, /* TIM0 */
    { CSI_PRGITR_TIM1VC_Pos, CSI_PRGITR_TIM1EOF_Pos, CSI_PRGITR_TIM1EN_Pos }, /* TIM1 */
    { CSI_PRGITR_TIM2VC_Pos, CSI_PRGITR_TIM2EOF_Pos, CSI_PRGITR_TIM2EN_Pos }, /* TIM2 */
    { CSI_PRGITR_TIM3VC_Pos, CSI_PRGITR_TIM3EOF_Pos, CSI_PRGITR_TIM3EN_Pos }, /* TIM3 */
  };

  /* Check pointer and input values validity */
  if ((pHcsi == NULL) || (Config == NULL) || (timer >= (uint32_t)HAL_CSI_TIMER_NB))
  {
    return HAL_ERROR;
  }

  if (Config->Enable == 1U)
  {
    conf_reg = (Config->Count & CSI_TIM0CFGR_COUNT_Msk);
  }

  /* Stop the timer (if it is running) */
  reg = __HAL_CSI_GET_MASKED_REG(pHcsi, PRGITR, 0xffffffffU);
  reg &= ~(0x01U << tim[timer].en_off);
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  /* Apply the configuration */
  switch (timer)
  {
    case 0:
      __HAL_CSI_SET_REG(pHcsi, TIM0CFGR, conf_reg);
      break;
    case 1:
      __HAL_CSI_SET_REG(pHcsi, TIM1CFGR, conf_reg);
      break;
    case 2:
      __HAL_CSI_SET_REG(pHcsi, TIM2CFGR, conf_reg);
      break;
    case 3:
      __HAL_CSI_SET_REG(pHcsi, TIM3CFGR, conf_reg);
      break;
  default:
    /* do something*/
    break;
  }

  reg &= ~((0x03U << tim[timer].vc_off) | (0x01U << tim[timer].start_off));
  reg |= ((Config->VC << tim[timer].vc_off) | (Config->Start << tim[timer].start_off));
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  reg |= (~~Config->Enable << tim[timer].en_off);
  __HAL_CSI_SET_REG(pHcsi, PRGITR, reg);

  return HAL_OK;
}

/**
* @brief  Initializes the CSI MSP.
* @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
*               the configuration information for CSI.
* @retval None
*/
__weak void HAL_CSI_MspInit(CSI_HandleTypeDef *pHcsi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(pHcsi);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CSI_MspInit could be implemented in the user file
   */
}

/**
* @brief  De-Initializes the CSI MSP.
* @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
*               the configuration information for CSI.
* @retval None
*/
__weak void HAL_CSI_MspDeInit(CSI_HandleTypeDef *pHcsi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(pHcsi);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CSI_MspInit could be implemented in the user file
   */
}
/**
  * @}
  */

/** @defgroup CSI_Exported_Functions_Group2 Start/Stop functions
 *  @brief   Function handling the start/stop of the CSI Virtual Channel processing
 *
@verbatim
 ===============================================================================
                ##### Start/Stop functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start the processing of a virtual channel
      (+) Stop the processing of a virtual channel

@endverbatim
  * @{
  */
/**
  * @brief  Start the processing of one or sereval virtual channels
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure
  * @param  vchans one or more virtual channel to start
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_Start(CSI_HandleTypeDef *pHcsi, uint32_t vchans)
{
  /* Check pointer validity */
  if (pHcsi == NULL)
  {
    return HAL_ERROR;
  }

  __HAL_CSI_SET_BIT(pHcsi, CR,
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_0)!=0U) ? (uint32_t)CSI_CR_VC0START : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_1)!=0U) ? (uint32_t)CSI_CR_VC1START : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_2)!=0U) ? (uint32_t)CSI_CR_VC2START : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_3)!=0U) ? (uint32_t)CSI_CR_VC3START : 0U));

  /* Enable Interrupts related to the Virtual Channel enabled */
  __HAL_CSI_ENABLE_IT(pHcsi,
                      (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_0)!=0U) ? (uint32_t)VC0_IT : 0U) |
                      (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_1)!=0U) ? (uint32_t)VC1_IT : 0U) |
                      (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_2)!=0U) ? (uint32_t)VC2_IT : 0U) |
                      (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_3)!=0U) ? (uint32_t)VC3_IT : 0U));

  /* Wait for the start of all requested virtual channels */
  while (__HAL_CSI_GET_MASKED_REG(pHcsi, SR0, ((vchans & HAL_CSI_ALL_VIRTUAL_CHANNELS) << CSI_SR0_VC0STATEF_Pos)) \
                                  != ((vchans & HAL_CSI_ALL_VIRTUAL_CHANNELS) << CSI_SR0_VC0STATEF_Pos))
  {
    HAL_Delay(1);
  }

  return HAL_OK;
}

/**
  * @brief  Stop the processing of one or sereval virtual channels
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure
  * @param  vchans one or more virtual channel to stop
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CSI_Stop(CSI_HandleTypeDef *pHcsi, uint32_t vchans)
{
  /* Check pointer validity */
  if (pHcsi == NULL)
  {
    return HAL_ERROR;
  }

  __HAL_CSI_SET_BIT(pHcsi, CR,
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_0) != 0U) ? (uint32_t)CSI_CR_VC0STOP : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_1) != 0U) ? (uint32_t)CSI_CR_VC1STOP : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_2) != 0U) ? (uint32_t)CSI_CR_VC2STOP : 0U) |
                    (((vchans & (uint32_t)HAL_CSI_VIRTUAL_CHANNEL_3) != 0U) ? (uint32_t)CSI_CR_VC3STOP : 0U));

  /* Wait for the start of all requested virtual channels */
  while (__HAL_CSI_GET_MASKED_REG(pHcsi, SR0, (vchans & HAL_CSI_ALL_VIRTUAL_CHANNELS) << CSI_SR0_VC0STATEF_Pos)!=0U)
  {
    HAL_Delay(1);
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup CSI_Exported_Functions_Group3 Callback functions
 *  @brief   Callback (event / error) functions
 *
@verbatim
 ===============================================================================
                ##### Callback functions #####
 ===============================================================================
    [..]  This section provides function called upon:
      (+) events triggered by the CSI
      (+) errors triggered by the CSI

@endverbatim
  * @{
  */
/**
  * @brief  CSI Error Event callback
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for CSI.
  * @param  error HAL_CSI_ErrorEventTypeDef type of the error
  * @param  arg0 argument (depend on error)
  * @param  arg1 argument (depend on error)
  * @retval None
  */
__weak void HAL_CSI_ErrorEventCallback(CSI_HandleTypeDef *pHcsi, HAL_CSI_ErrorEventTypeDef error,
                                       uint32_t arg0, uint32_t arg1)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CSI_ErrorEventCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(pHcsi);
  UNUSED(error);
  UNUSED(arg0);
  UNUSED(arg1);
}

/**
  * @brief  CSI Event callback
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for CSI.
  * @param  event HAL_CSI_EventTypeDef type of the event
  * @param  arg0 argument (depend on event)
  * @param  arg1 argument (depend on event)
  * @retval None
  */
__weak void HAL_CSI_EventCallback(CSI_HandleTypeDef *pHcsi, HAL_CSI_EventTypeDef event, uint32_t arg0, uint32_t arg1)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CSI_EventCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(pHcsi);
  UNUSED(event);
  UNUSED(arg0);
  UNUSED(arg1);
}
/**
  * @}
  */

/** @defgroup CSI_Exported_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *
@verbatim
 ===============================================================================
               ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Check the CSI state.
      (+) Get the specific CSI error flag.

@endverbatim
  * @{
  */

/**
  * @brief  Return the CSI state
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for CSI.
  * @retval HAL state
  */
HAL_CSI_StateTypeDef HAL_CSI_GetState(const CSI_HandleTypeDef *pHcsi)
{
  return pHcsi->State;
}

/**
 * @brief  Return the CSI error code
 * @param  pHcsi  pointer to a CSI_HandleTypeDef structure that contains
 *              the configuration information for CSI.
 * @retval CSI Error Code
 */
uint32_t HAL_CSI_GetError(const CSI_HandleTypeDef *pHcsi)
{
  return pHcsi->ErrorCode;
}
/**
  * @}
  */

/** @defgroup CSI_Exported_Functions_Group5 IRQ handler function
 *  @brief   IRQ handler function
 *
@verbatim
 ===============================================================================
                ##### IRQ handler function #####
 ===============================================================================
    [..]  This section provides function allowing to:
      (+) Handle the various interrupts generated by the CSI IP

@endverbatim
  * @{
  */

/**
  * @brief  Handles CSI interrupt request.
  * @param  pHcsi pointer to a CSI_HandleTypeDef structure that contains
  *               the configuration information for the CSI.
  * @retval None
  */
typedef void (*irq_error_cb_t)(CSI_HandleTypeDef *pHcsim, HAL_CSI_ErrorEventTypeDef error,
                               uint32_t arg0, uint32_t arg1);
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CSI_SR0_ERROR_FLAGS (CSI_SR0_SYNCERRF | CSI_SR0_WDERRF | CSI_SR0_SPKTERRF | CSI_SR0_IDERRF | \
                              CSI_SR0_CECCERRF | CSI_SR0_ECCERRF | CSI_SR0_CRCERRF)
#define CSI_SR0_EVENTS_FLAGS (CSI_SR0_SPKTF | CSI_SR0_CCFIFOFF | CSI_SR0_EOF0F | CSI_SR0_EOF1F | CSI_SR0_EOF2F | \
                              CSI_SR0_EOF3F | CSI_SR0_SOF0F | CSI_SR0_SOF1F | CSI_SR0_SOF2F | CSI_SR0_SOF3F | \
                              CSI_SR0_TIM0F | CSI_SR0_TIM1F | CSI_SR0_TIM2F | CSI_SR0_TIM3F | CSI_SR0_LB0F | \
                              CSI_SR0_LB1F | CSI_SR0_LB2F | CSI_SR0_LB3F)
#define CSI_SR1_ERROR_FLAGS (CSI_SR1_ESOTDL0F | CSI_SR1_ESOTSYNCDL0F | CSI_SR1_EESCDL0F | CSI_SR1_ESYNCESCDL0F | \
                              CSI_SR1_ECTRLDL0F | CSI_SR1_ESOTDL1F | CSI_SR1_ESOTSYNCDL1F | CSI_SR1_EESCDL1F | \
                              CSI_SR1_ESYNCESCDL1F | CSI_SR1_ECTRLDL1F )
void HAL_CSI_IRQHandler(CSI_HandleTypeDef *pHcsi)
{
  CSI_TypeDef *regs = pHcsi->Instance;
  /* Structure containing information about each error interrupt */
  struct
  {
    uint32_t flag;
    uint32_t errorcode;
    HAL_CSI_ErrorEventTypeDef type;
    __IO uint32_t *arg_reg;
    uint32_t vchan_off;
    uint32_t data_type_off;
  } errors_sr0[] =
  {
    { CSI_SR0_SYNCERRF, HAL_CSI_ERROR_SYNC, HAL_CSI_SyncError, &(regs->ERR2), CSI_ERR2_SYNCVCERR_Pos, 0xFFFF },
    { CSI_SR0_WDERRF, HAL_CSI_ERROR_WDG, HAL_CSI_WatchdogError, &(regs->ERR2), CSI_ERR2_SYNCVCERR_Pos, 0xFFFF },
    { CSI_SR0_SPKTERRF, HAL_CSI_ERROR_SPKT, HAL_CSI_ShortPacketError, &(regs->ERR2), \
     CSI_ERR2_SPKTVCERR_Pos, CSI_ERR2_SPKTDTERR_Pos },
    { CSI_SR0_IDERRF, HAL_CSI_ERROR_DTID, HAL_CSI_DataTypeIDError, &(regs->ERR1), \
     CSI_ERR1_IDVCERR_Pos, CSI_ERR1_IDDTERR_Pos },
    { CSI_SR0_CECCERRF, HAL_CSI_ERROR_CECC, HAL_CSI_CECCError, &(regs->ERR1), \
     CSI_ERR1_CECCVCERR_Pos, CSI_ERR1_CECCDTERR_Pos},
    { CSI_SR0_ECCERRF, HAL_CSI_ERROR_ECC, HAL_CSI_ECCError, &(regs->ERR1), 0xFFFF, 0xFFFF },
    { CSI_SR0_CRCERRF, HAL_CSI_ERROR_CRC, HAL_CSI_CRCError, &(regs->ERR1), \
     CSI_ERR1_CRCVCERR_Pos, CSI_ERR1_CRCDTERR_Pos },
  };

  struct
  {
    uint32_t flag;
    uint32_t errorcode;
    HAL_CSI_ErrorEventTypeDef type;
    uint32_t lane;
  } errors_sr1[] =
  {
    { CSI_SR1_ESOTDL0F, HAL_CSI_ERROR_SOF, HAL_CSI_SOTError, 0},
    { CSI_SR1_ESOTSYNCDL0F, HAL_CSI_ERROR_SOFSYNC, HAL_CSI_SOTSynchroError, 0 },
    { CSI_SR1_EESCDL0F, HAL_CSI_ERROR_DPHY_ESC, HAL_CSI_EscapeEntryError, 0 },
    { CSI_SR1_ESYNCESCDL0F, HAL_CSI_ERROR_DPHY_LP_SYNC, HAL_CSI_LowPowerTXSynchroError, 0 },
    { CSI_SR1_ECTRLDL0F, HAL_CSI_ERROR_DPHY_CTRL, HAL_CSI_ControlError, 0 },
    { CSI_SR1_ESOTDL1F, HAL_CSI_ERROR_SOF, HAL_CSI_SOTError, 1 },
    { CSI_SR1_ESOTSYNCDL1F, HAL_CSI_ERROR_SOFSYNC, HAL_CSI_SOTSynchroError, 1 },
    { CSI_SR1_EESCDL1F, HAL_CSI_ERROR_DPHY_ESC, HAL_CSI_EscapeEntryError, 1 },
    { CSI_SR1_ESYNCESCDL1F, HAL_CSI_ERROR_DPHY_LP_SYNC, HAL_CSI_LowPowerTXSynchroError, 1 },
    { CSI_SR1_ECTRLDL1F, HAL_CSI_ERROR_DPHY_CTRL, HAL_CSI_ControlError, 1 },
  };

  /* Structure containing information about each virtual channel related interrupt */
  struct
  {
    uint32_t flag;
    HAL_CSI_EventTypeDef type;
    uint32_t arg0;
  } chans[] =
  {
    /* End of frame */
    { CSI_SR0_EOF0F, HAL_CSI_EndOfFrame, 0 },
    { CSI_SR0_EOF1F, HAL_CSI_EndOfFrame, 1 },
    { CSI_SR0_EOF2F, HAL_CSI_EndOfFrame, 2 },
    { CSI_SR0_EOF3F, HAL_CSI_EndOfFrame, 3 },
    /* Start of frame */
    { CSI_SR0_SOF0F, HAL_CSI_StartOfFrame, 0 },
    { CSI_SR0_SOF1F, HAL_CSI_StartOfFrame, 1 },
    { CSI_SR0_SOF2F, HAL_CSI_StartOfFrame, 2 },
    { CSI_SR0_SOF3F, HAL_CSI_StartOfFrame, 3 },
    /* Timer */
    { CSI_SR0_TIM0F, HAL_CSI_TimerEvent, 0 },
    { CSI_SR0_TIM1F, HAL_CSI_TimerEvent, 1 },
    { CSI_SR0_TIM2F, HAL_CSI_TimerEvent, 2 },
    { CSI_SR0_TIM3F, HAL_CSI_TimerEvent, 3 },
    /* Line Byte */
    { CSI_SR0_LB0F, HAL_CSI_LineByte, 0 },
    { CSI_SR0_LB1F, HAL_CSI_LineByte, 1 },
    { CSI_SR0_LB2F, HAL_CSI_LineByte, 2 },
    { CSI_SR0_LB3F, HAL_CSI_LineByte, 3 },
    /* Short Packet */
    { CSI_SR0_SPKTF, HAL_CSI_ShortPkt, 0 },
    /* Clock Changer FIFO Full */
    { CSI_SR0_CCFIFOFF, HAL_CSI_CCFifoFull, 0 },
  };
  uint32_t irq_status;
  uint32_t i;

  /* Should not be null at this stage : handle tested to avoid system crash */
  if (pHcsi == NULL)
  {
    return;
  }

  /* Read the SR0 register once */
  irq_status = __HAL_CSI_GET_MASKED_REG(pHcsi, SR0, CSI_SR0_ERROR_FLAGS | CSI_SR0_EVENTS_FLAGS);

  /* Loop through all error interrupt sources */
  i = 0;
  while (((irq_status & (uint32_t)CSI_SR0_ERROR_FLAGS) != 0U) && ((i < (uint32_t)ARRAY_SIZE(errors_sr0)) != 0U))
  {
    if ((irq_status & (errors_sr0[i].flag)) != 0U)
    {
      uint32_t error_reg;
      uint32_t vchan = 0;
      uint32_t data_type = 0;

      __HAL_CSI_SET_BIT(pHcsi, FCR0, errors_sr0[i].flag);
      irq_status &= ~errors_sr0[i].flag;
      pHcsi->ErrorCode |= errors_sr0[i].errorcode;
      pHcsi->State = HAL_CSI_STATE_ERROR;

      error_reg = *(errors_sr0[i].arg_reg);

      if (errors_sr0[i].vchan_off != 0xFFFFU)
      {
        vchan = (error_reg >> errors_sr0[i].vchan_off) & 0x03U;
      }

      if (errors_sr0[i].data_type_off != 0xFFFFU)
      {
        data_type = (error_reg >> errors_sr0[i].data_type_off) & 0x3fU;
      }
      HAL_CSI_ErrorEventCallback(pHcsi, errors_sr0[i].type, vchan, data_type);
    }
    i++;
  }

  i = 0;
  /* Loop through all virtual channel interrupt sources */
  while (((irq_status & (uint32_t)CSI_SR0_EVENTS_FLAGS) != 0U) && ((i < (uint32_t)ARRAY_SIZE(chans)) != 0U))
  {
    if ((irq_status & (chans[i].flag) )!= 0U)
    {
      __HAL_CSI_SET_BIT(pHcsi, FCR0, chans[i].flag);
      irq_status &= ~chans[i].flag;
      if (chans[i].flag != CSI_SR0_SPKTF)
      {
        HAL_CSI_EventCallback(pHcsi, chans[i].type, chans[i].arg0, 0);
      }
      else
      {
        uint32_t tmp;
        tmp = __HAL_CSI_GET_MASKED_REG(pHcsi, SPDFR, 0xffffffffU);
        HAL_CSI_EventCallback(pHcsi, chans[i].type,
                              (tmp & CSI_SPDFR_VCHANNEL_Msk) >> CSI_SPDFR_VCHANNEL_Pos,
                              (tmp & (CSI_SPDFR_DATATYPE_Msk | CSI_SPDFR_DATAFIELD_Msk)));
      }
    }
    i++;
  }

  /* Read the SR1 register once */
  irq_status = __HAL_CSI_GET_MASKED_REG(pHcsi, SR1, CSI_SR1_ERROR_FLAGS);

  /* Loop through all error interrupt sources */
  i = 0;
  while ((irq_status != 0U) && (i < ARRAY_SIZE(errors_sr1)))
  {
    if ((irq_status & (errors_sr1[i].flag)) != 0U)
    {
      __HAL_CSI_SET_BIT(pHcsi, FCR1, errors_sr1[i].flag);
      irq_status &= ~errors_sr1[i].flag;
      pHcsi->ErrorCode |= errors_sr1[i].errorcode;
      pHcsi->State = HAL_CSI_STATE_ERROR;

      HAL_CSI_ErrorEventCallback(pHcsi, errors_sr1[i].type, errors_sr1[i].lane, 0);
    }
    i++;
  }
}
/**
  * @}
  */

#endif /* HAL_CSI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
