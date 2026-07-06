/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_lvds.h
  * @author  MCD Application Team
  * @brief   Header file of LVDS HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_HAL_LVDS_H
#define __STM32MP2xx_HAL_LVDS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

#if defined (LVDS)
/** @addtogroup __STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup LVDS LVDS
  * @brief LVDS HAL module driver
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup LVDS_Exported_Constants LVDS Exported Constants
  * @{
  */

/** @defgroup LVDS_Number_Of_Links LVDS Number Of Links
 * @{
 */
#define LVDS_ONE_LINK		0x00U
#define LVDS_TWO_LINKS		0x01U
/**
 * @}
 */

/**
 * @defgroup LVDS_Number_Of_Displays LVDS Number of displays
 */
#define LVDS_ONE_DISPLAY		0x00U
#define LVDS_TWO_DISPLAYS		0x01U

/** @defgroup LVDS_Data_Mapping LVDS Data Mapping
 * @{
 */
#define LVDS_DT_MAP_JEIDA		0x00U
#define LVDS_DT_MAP_VESA		0x01U
/**
 * @}
 */

/**
 * @defgroup
 */
#define LVDS_DISPLAY_DISABLE	0x00000000U
#define LVDS_DISPLAY_ENABLE		LVDS_CR_LVDSEN

/**
 * @defgroup
 */
#define LVDS_HS_POLARITY_NORMAL		0x00000000U
#define LVDS_HS_POLARITY_INVERTED	LVDS_CR_HSPOL

/**
 * @defgroup
 */
#define LVDS_VS_POLARITY_NORMAL		0x00000000U
#define LVDS_VS_POLARITY_INVERTED	LVDS_CR_VSPOL

/**
 * @defgroup
 */
#define LVDS_DE_POLARITY_NORMAL		0x00000000U
#define LVDS_DE_POLARITY_INVERTED	LVDS_CR_DEPOL

/**
 * @defgroup LVDS_Link_Phase
 */
#define LVDS_PHASE_EAO		0x00000000U
#define LVDS_PHASE_EBO		LVDS_CR_LKPHA

/**
 * @defgroup LVDS_Link_Selection
 */
#define LVDS_LINK1_SELECT		0x0U
#define LVDS_LINK2_SELECT		0x1U

/** @defgroup LVDS_Color_Coding LVDS Color Coding
 * @{
 */
#define LVDS_RGB666		0x00U
#define LVDS_RGB888		0x01U
/**
 * @}
 */

/**
 * @defgroup LVDS_PRBS LVDS PRBS
 */
#define LVDS_PRBS_07		0x00000000U
#define LVDS_PRBS_15		LVDS_CDL2CR_PRBS_0
#define LVDS_PRBS_23		LVDS_CDL2CR_PRBS_1
#define LVDS_PRBS_31		(LVDS_CDL2CR_PRBS_0 | LVDS_CDL2CR_PRBS_1)

/**
 * @defgroup LVDS_Channel_Distribution_values
 */
#define LVDS_CLOCK_LANE_MST		0x0U
#define LVDS_DATA_LANE_0		0x1U
#define LVDS_DATA_LANE_1		0x2U
#define LVDS_DATA_LANE_2		0x3U
#define LVDS_DATA_LANE_3		0x4U
#define LVDS_CLOCK_LANE_SLV		0x5U
#define LVDS_DATA_LANE_4		0x6U
#define LVDS_DATA_LANE_5		0x7U
#define LVDS_DATA_LANE_6		0x8U
#define LVDS_DATA_LANE_7		0x9U
#define LVDS_PRBS				0xAU


 /*
  * PLL functional mode
  */
 #define LVDS_PLL_TWG_ENABLE 	0x1U
 #define LVDS_PLL_SD_ENABLE 		0x10U

 /* Integer mode : SD disable & TWG disable */
 #define LVDS_PLL_MODE_INT		0x00U
 /* Fractional mode : SD enable & TWG disable */
 #define LVDS_PLL_MODE_FRAC		LVDS_PLL_SD_ENABLE
 /* Spread Spectrum Clocking mode : SD enable & TWG enable */
 #define LVDS_PLL_MODE_SSC		(LVDS_PLL_SD_ENABLE | LVDS_PLL_TWG_ENABLE)


/* Exported macro ------------------------------------------------------------*/

/** @defgroup LVDS_Exported_Macros LVDS Exported Macros
 * @{
 */

/**
 * @brief Enables the LVDS host.
 * @param __HANDLE__ LVDS host.
 * @retval None.
 */
#define __HAL_LVDS_ENABLE(__HANDLE__) do {								\
		__IO uint32_t tmpreg = 0x00U;									\
		SET_BIT((__HANDLE__)->Instance->CR, LVDS_CR_LVDSEN);			\
		tmpreg = READ_BIT((__HANDLE__)->Instance->CR, LVDS_CR_LVDSEN);	\
		UNUSED(tmpreg);													\
} while(0U)

/**
 * @brief Disables the LVDS host.
 * @param __HANDLE__ LVDS host.
 * @retval None.
 */
#define __HAL_LVDS_DISABLE(__HANDLE__) do {								\
		__IO uint32_t tmpreg = 0x00U;									\
		CLEAR_BIT((__HANDLE__)->Instance->CR, LVDS_CR_LVDSEN);			\
		tmpreg = READ_BIT((__HANDLE__)->Instance->CR, LVDS_CR_LVDSEN);	\
		UNUSED(tmpreg);													\
} while(0U)

/**
 * @brief Enables the LVDS PLL.
 * @param __HANDLE__ LVDS PLL.
 * @retval None.
 */
#define __HAL_LVDS_PLL_ENABLE(__HANDLE__) do {												\
		__IO uint32_t tmpreg = 0x00U;														\
		SET_BIT((__HANDLE__)->Instance->PMPLLCR1, LVDS_PMPLLCR1_MST_PLL_ENABLE);			\
		tmpreg = READ_BIT((__HANDLE__)->Instance->PMPLLCR1, LVDS_PMPLLCR1_MST_PLL_ENABLE);	\
		UNUSED(tmpreg);																		\
} while(0U)

/**
 * @brief Enables the LVDS PLL.
 * @param __HANDLE__ LVDS PLL.
 * @retval None.
 */
#define __HAL_LVDS_PLL_DISABLE(__HANDLE__) do {												\
		__IO uint32_t tmpreg = 0x00U;														\
		CLEAR_BIT((__HANDLE__)->Instance->PMPLLCR1, LVDS_PMPLLCR1_MST_PLL_ENABLE);			\
		tmpreg = READ_BIT((__HANDLE__)->Instance->PMPLLCR1, LVDS_PMPLLCR1_MST_PLL_ENABLE);	\
		UNUSED(tmpreg);																		\
} while(0U)


#define __HAL_LVDS_PLL_LOCKED(__HANDLE__) (!(((__HANDLE__)->Instance->PMSSR1) & LVDS_PMSSR1_MST_DRV_A0_SPARE_RD & 1))
#define __HAL_LVDS_PLL_LOCKED_BIS(__HANDLE__) ((__HANDLE__)->Instance->PMPLLSR & LVDS_PMPLLSR_MST_PLL_LOCK)

/**
 * @}
 */


/* Exported types ------------------------------------------------------------*/


typedef enum
{
	HAL_LVDS_MAP_R_0  = 0x00U,
	HAL_LVDS_MAP_R_1  = 0x01U,
	HAL_LVDS_MAP_R_2  = 0x02U,
	HAL_LVDS_MAP_R_3  = 0x03U,
	HAL_LVDS_MAP_R_4  = 0x04U,
	HAL_LVDS_MAP_R_5  = 0x05U,
	HAL_LVDS_MAP_R_6  = 0x06U,
	HAL_LVDS_MAP_R_7  = 0x07U,
	HAL_LVDS_MAP_G_0  = 0x08U,
	HAL_LVDS_MAP_G_1  = 0x09U,
	HAL_LVDS_MAP_G_2  = 0x0AU,
	HAL_LVDS_MAP_G_3  = 0x0BU,
	HAL_LVDS_MAP_G_4  = 0x0CU,
	HAL_LVDS_MAP_G_5  = 0x0DU,
	HAL_LVDS_MAP_G_6  = 0x0EU,
	HAL_LVDS_MAP_G_7  = 0x0FU,
	HAL_LVDS_MAP_B_0  = 0x10U,
	HAL_LVDS_MAP_B_1  = 0x11U,
	HAL_LVDS_MAP_B_2  = 0x12U,
	HAL_LVDS_MAP_B_3  = 0x13U,
	HAL_LVDS_MAP_B_4  = 0x14U,
	HAL_LVDS_MAP_B_5  = 0x15U,
	HAL_LVDS_MAP_B_6  = 0x16U,
	HAL_LVDS_MAP_B_7  = 0x17U,
	HAL_LVDS_MAP_H_S  = 0x18U,
	HAL_LVDS_MAP_V_S  = 0x19U,
	HAL_LVDS_MAP_D_E  = 0x1AU,
	HAL_LVDS_MAP_C_E  = 0x1BU,
	HAL_LVDS_MAP_C_I  = 0x1CU,
	HAL_LVDS_MAP_TOG  = 0x1DU,
	HAL_LVDS_MAP_ONE  = 0x1EU,
	HAL_LVDS_MAP_ZERO	= 0x1FU,
} HAL_LVDS_MapTypeDef;

/**
 * @defgroup LVDS Init Structure definition
 */
typedef struct
{
	uint32_t DataMapping;			/*!< Data Mapping
										This parameter can be any value of @ref LVDS_Data_Mapping */

	uint32_t ColorCoding;			/*!< Color coding for LTDC interface
										This parameter can be any value of @ref LVDS_Color_Coding	*/

} LVDS_InitTypeDef;


/**
 * @brief LVDS PLL Clock structure definition
 */
typedef struct
{
	int      ISMASTER;
	int      PLLMODE;
	uint32_t PLLBDIV;			/*!< PLL Output Division Factor
									This parameter must be a value between 0x002 and 0   */

	uint32_t PLLMDIV; 	/* Feedback divider */
	uint32_t PLLNDIV;			/*!< PLL Input Division Factor
									This parameter can be any value of @ref LVDS_PLL_NDIV */

	uint32_t PLLFREF;	/* PLL reference frequency should be < 25MHz */

	uint32_t TESTDIV;
	uint32_t MODDEP;
	uint32_t MODFREQ;
	uint32_t FRACIN;
	uint32_t DOWN_SPREAD;

} LVDS_PLLInitTypeDef;

/**
 * @brief  LVDS configuration
 */
typedef struct
{
	uint32_t NumberOfLinks;            		/*!< Number of links
																					It is either 1 Link (4DL) or 2 (8DL)
																					This parameter can be any value of @ref LVDS_Number_Of_Links */

	uint32_t NumberOfDisplays;            /*!< Number of displays
																					It is either 1 or 2  with same content on both
																					This parameter can be any value of @ref LVDS_Number_Of_Displays */

	uint32_t HSPolarity;                   /*!< HSYNC pin polarity
                                              This parameter can be any value of @ref LVDS_HSYNC_Polarity         */

	uint32_t VSPolarity;                   /*!< VSYNC pin polarity
                                              This parameter can be any value of @ref LVDS_VSYNC_Active_Polarity  */

	uint32_t DEPolarity;                   /*!< Data Enable pin polarity
                                              This parameter can be any value of @ref LVDS_DATA_ENABLE_Polarity   */

	uint32_t LinkPhase;										/*!< Link phase
  																						This parameter can be any value of @ref LVDS_Link_Phase						*/
} LVDS_CfgTypeDef;

/**
 * @brief  HAL LVDS States Structure Definition
 */
typedef enum
{
	HAL_LVDS_STATE_RESET   = 0x00U,
	HAL_LVDS_STATE_READY   = 0x01U,
	HAL_LVDS_STATE_ERROR   = 0x02U,
	HAL_LVDS_STATE_BUSY    = 0x03U,
	HAL_LVDS_STATE_TIMEOUT = 0x04U
} HAL_LVDS_StateTypeDef;

/**
 * @brief  HAL LVDS handle structures definition
 */
typedef struct __LVDS_HandleTypeDef
{
	LVDS_TypeDef				*Instance;		/*!< Register base address       */
	LVDS_InitTypeDef			Init;			/*!< LVDS Init parameters		 */
	HAL_LockTypeDef				Lock;			/*!< LVDS peripheral status      */
	__IO HAL_LVDS_StateTypeDef	State;			/*!< LVDS communication state    */
	__IO uint32_t				ErrorCode;		/*!< LVDS Error code             */
	uint32_t					ErrorMsk;		/*!< LVDS Error monitoring mask  */
} LVDS_HandleTypeDef;

/**********************************************************************************************/
/*                                  LVDS HAL Control / Init definitions                     */
/**********************************************************************************************/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LVDS_Exported_Functions LVDS Exported Functions
 * @{
 */
HAL_StatusTypeDef HAL_LVDS_Init(LVDS_HandleTypeDef *hlvds, LVDS_CfgTypeDef *cfg, LVDS_PLLInitTypeDef *PLLInit);
HAL_StatusTypeDef HAL_LVDS_DeInit(LVDS_HandleTypeDef *hlvds);

HAL_StatusTypeDef HAL_LVDS_PHY_Init(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef * PLLInit);
HAL_StatusTypeDef HAL_LVDS_PHY_SetTimings(LVDS_HandleTypeDef *hlvds, uint32_t Timing, FunctionalState State, uint32_t Value);
HAL_StatusTypeDef HAL_LVDS_PHY_PLLConfig(LVDS_HandleTypeDef *hlvds, LVDS_PLLInitTypeDef *PLLInit);

void HAL_LVDS_MspInit(LVDS_HandleTypeDef *hlvds);
void HAL_LVDS_MspDeInit(LVDS_HandleTypeDef *hlvds);

uint32_t HAL_LVDS_GetState(LVDS_HandleTypeDef *hlvds);
HAL_StatusTypeDef HAL_LVDS_Start(LVDS_HandleTypeDef *hlvds);
HAL_StatusTypeDef HAL_LVDS_Stop(LVDS_HandleTypeDef *hlvds);
HAL_StatusTypeDef HAL_LVDS_ConfigMode(LVDS_HandleTypeDef *hlvds, LVDS_CfgTypeDef *cfg);
HAL_StatusTypeDef HAL_LVDS_ConfigDataMapping(LVDS_HandleTypeDef *hlvds);
HAL_StatusTypeDef HAL_LVDS_SetPattern(LVDS_HandleTypeDef *hlvds, const HAL_LVDS_MapTypeDef pattern[5][7]);
HAL_StatusTypeDef HAL_LVDS_BistStart(LVDS_HandleTypeDef *hlvds, uint32_t polynome);
HAL_StatusTypeDef HAL_LVDS_BistStop(LVDS_HandleTypeDef *hlvds);
HAL_StatusTypeDef HAL_LVDS_BistConfig(LVDS_HandleTypeDef *hlvds, uint32_t distrib, uint32_t custom);
HAL_StatusTypeDef HAL_LVDS_SetLanePolarity(LVDS_HandleTypeDef *hlvds, uint32_t link, uint32_t channels);
HAL_StatusTypeDef HAL_LVDS_SetCustomLaneConfig(LVDS_HandleTypeDef *hlvds, uint32_t distrib, uint32_t custom);
HAL_StatusTypeDef HAL_LVDS_SetChannelDistribution(LVDS_HandleTypeDef *hlvds, uint32_t link, uint32_t distribution);
/**
 * @}
 */


 /* Private macros ------------------------------------------------------------*/
/** @defgroup LVDS_Private_Macros LVDS Private Macros
 * @{
 */

#define IS_LVDS_PLL_BDIV(__BDIV__)		((2U <= (__BDIV__)) && ((__BDIV__) <= 1023U))
#define IS_LVDS_PLL_MDIV(__MDIV__)		((1U <= (__MDIV__)) && ((__MDIV__) <= 1023U))
#define IS_LVDS_PLL_NDIV(__NDIV__)		((1U <= (__NDIV__)) && ((__NDIV__) <= 1023U))
#define IS_LVDS_PLL_FREF(__FREF__)		((0U <= (__FREF__)) && ((__FREF__) <= 40000000))
#define IS_LVDS_LINK(__LINK__)		(((__LINK__) == LVDS_ONE_LINK) || \
									((__LINK__) == LVDS_TWO_LINKS))
#define IS_LVDS_DISPLAY(__CHANNEL__)		(((__CHANNEL__) == LVDS_ONE_DISPLAY) || \
											((__CHANNEL__) == LVDS_TWO_DISPLAYS))
#define IS_LVDS_VS_POLARITY(__POLARITY__)		(((__POLARITY__) == LVDS_VS_POLARITY_NORMAL) || \
												((__POLARITY__) == LVDS_VS_POLARITY_INVERTED))
#define IS_LVDS_HS_POLARITY(__POLARITY__)		(((__POLARITY__) == LVDS_HS_POLARITY_NORMAL) || \
												((__POLARITY__) == LVDS_HS_POLARITY_INVERTED))
#define IS_LVDS_DE_POLARITY(__POLARITY__)		(((__POLARITY__) == LVDS_DE_POLARITY_NORMAL) || \
												((__POLARITY__) == LVDS_DE_POLARITY_INVERTED))
#define IS_LVDS_LINK_PHASE(__PHASE__)		(((__PHASE__) == LVDS_PHASE_EAO) || \
											((__PHASE__) == LVDS_PHASE_EBO))
#define IS_LVDS_LINK_SELECTED(__LINK__)		(((__LINK__) == LVDS_LINK1_SELECT) || \
											((__LINK__) == LVDS_LINK2_SELECT))
#define IS_LVDS_CHANNEL(__CHANNEL__)		((0x00U <= (__CHANNEL__)) && ((__CHANNEL__) <= 0xAAAAAU))
#define IS_PATTERN_SIZE(__PATTERN__)		((sizeof((__PATTERN__)) == 7) && \
											(sizeof((__PATTERN__)[0]) == 5))
#define IS_LVDS_PRBS_POLYNOME(__POLYNOME__)		(((__POLYNOME__) == LVDS_PRBS_07) || \
												((__POLYNOME__) == LVDS_PRBS_15) || \
												((__POLYNOME__) == LVDS_PRBS_23) || \
												((__POLYNOME__) == LVDS_PRBS_31))
#define IS_LVDS_CHANNEL_VALUE(__CHANNEL__)		((0x0U <= (__CHANNEL__)) && ((__CHANNEL__) <= 0xAU))
#define IS_LVDS_PLL_MODE(__PLLMODE__)		(((__PLLMODE__) == LVDS_PLL_MODE_INT) || \
		                                     ((__PLLMODE__) == LVDS_PLL_MODE_FRAC) || \
																				 ((__PLLMODE__) == LVDS_PLL_MODE_SSC))

/**
 * @}
 */

#endif /* LVDS */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_HAL_LVDS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
