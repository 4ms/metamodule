// File split up #/#:
/**
 ******************************************************************************
 * @file    stm32mp157cxx_ca7.h
 * @author  MCD Application Team
 * @brief   CMSIS stm32mp157cxx_ca7 Device Peripheral Access Layer Header File.
 *
 *          This file contains:
 *           - Data structures and the address mapping for all peripherals
 *           - Peripheral's registers declarations and bits definition
 *           - Macros to access peripherals registers hardware
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/** @addtogroup CMSIS_Device
 * @{
 */

/** @addtogroup stm32mp157cxx_ca7
 * @{
 */

/** @addtogroup Exported_macros
 * @{
 */

/******************************* ADC Instances ********************************/
#define IS_ADC_ALL_INSTANCE(INSTANCE) (((INSTANCE) == ADC1) || ((INSTANCE) == ADC2))

#define IS_ADC_MULTIMODE_MASTER_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

#define IS_ADC_COMMON_INSTANCE(INSTANCE) ((INSTANCE) == ADC12_COMMON)

/******************************** DTS Instances ******************************/
#define IS_DTS_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DTS1)

/******************************* CRC Instances ********************************/
#define IS_CRC_ALL_INSTANCE(INSTANCE) (((INSTANCE) == CRC1) || ((INSTANCE) == CRC2))

/******************************* DAC Instances ********************************/
#define IS_DAC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DAC1)

/******************************* DCMI Instances *******************************/
#define IS_DCMI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DCMI)

/****************************** DFSDM Instances *******************************/
#define IS_DFSDM_FILTER_ALL_INSTANCE(INSTANCE)                                                                         \
	(((INSTANCE) == DFSDM1_Filter0) || ((INSTANCE) == DFSDM1_Filter1) || ((INSTANCE) == DFSDM1_Filter2) ||             \
	 ((INSTANCE) == DFSDM1_Filter3) || ((INSTANCE) == DFSDM1_Filter4) || ((INSTANCE) == DFSDM1_Filter5))

#define IS_DFSDM_CHANNEL_ALL_INSTANCE(INSTANCE)                                                                        \
	(((INSTANCE) == DFSDM1_Channel0) || ((INSTANCE) == DFSDM1_Channel1) || ((INSTANCE) == DFSDM1_Channel2) ||          \
	 ((INSTANCE) == DFSDM1_Channel3) || ((INSTANCE) == DFSDM1_Channel4) || ((INSTANCE) == DFSDM1_Channel5) ||          \
	 ((INSTANCE) == DFSDM1_Channel6) || ((INSTANCE) == DFSDM1_Channel7))

/******************************** DMA Instances *******************************/
#define IS_DMA_STREAM_ALL_INSTANCE(INSTANCE)                                                                           \
	(((INSTANCE) == DMA1_Stream0) || ((INSTANCE) == DMA1_Stream1) || ((INSTANCE) == DMA1_Stream2) ||                   \
	 ((INSTANCE) == DMA1_Stream3) || ((INSTANCE) == DMA1_Stream4) || ((INSTANCE) == DMA1_Stream5) ||                   \
	 ((INSTANCE) == DMA1_Stream6) || ((INSTANCE) == DMA1_Stream7) || ((INSTANCE) == DMA2_Stream0) ||                   \
	 ((INSTANCE) == DMA2_Stream1) || ((INSTANCE) == DMA2_Stream2) || ((INSTANCE) == DMA2_Stream3) ||                   \
	 ((INSTANCE) == DMA2_Stream4) || ((INSTANCE) == DMA2_Stream5) || ((INSTANCE) == DMA2_Stream6) ||                   \
	 ((INSTANCE) == DMA2_Stream7))

/******************************** DMA Request Generator Instances **************/
#define IS_DMA_REQUEST_GEN_ALL_INSTANCE(INSTANCE)                                                                      \
	(((INSTANCE) == DMAMUX1_RequestGenerator0) || ((INSTANCE) == DMAMUX1_RequestGenerator1) ||                         \
	 ((INSTANCE) == DMAMUX1_RequestGenerator2) || ((INSTANCE) == DMAMUX1_RequestGenerator3))
/******************************** MDMA Request Generator Instances **************/
#define IS_MDMA_STREAM_ALL_INSTANCE(INSTANCE)                                                                          \
	(((INSTANCE) == MDMA_Channel0) || ((INSTANCE) == MDMA_Channel1) || ((INSTANCE) == MDMA_Channel2) ||                \
	 ((INSTANCE) == MDMA_Channel3) || ((INSTANCE) == MDMA_Channel4) || ((INSTANCE) == MDMA_Channel5) ||                \
	 ((INSTANCE) == MDMA_Channel6) || ((INSTANCE) == MDMA_Channel7) || ((INSTANCE) == MDMA_Channel8) ||                \
	 ((INSTANCE) == MDMA_Channel9) || ((INSTANCE) == MDMA_Channel10) || ((INSTANCE) == MDMA_Channel11) ||              \
	 ((INSTANCE) == MDMA_Channel12) || ((INSTANCE) == MDMA_Channel13) || ((INSTANCE) == MDMA_Channel14) ||             \
	 ((INSTANCE) == MDMA_Channel15) || ((INSTANCE) == MDMA_Channel16))
/******************************* QUADSPI Instances *******************************/
#define IS_QSPI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == QUADSPI)

/******************************* FDCAN Instances ******************************/
#define IS_FDCAN_ALL_INSTANCE(INSTANCE) (((INSTANCE) == FDCAN1) || ((INSTANCE) == FDCAN2))

#define IS_FDCAN_TT_INSTANCE(INSTANCE) ((INSTANCE) == FDCAN1)

/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE)                                                                                 \
	(((INSTANCE) == GPIOA) || ((INSTANCE) == GPIOB) || ((INSTANCE) == GPIOC) || ((INSTANCE) == GPIOD) ||               \
	 ((INSTANCE) == GPIOE) || ((INSTANCE) == GPIOF) || ((INSTANCE) == GPIOG) || ((INSTANCE) == GPIOH) ||               \
	 ((INSTANCE) == GPIOI) || ((INSTANCE) == GPIOJ) || ((INSTANCE) == GPIOK) || ((INSTANCE) == GPIOZ))

/**************************** GPIO Lock Instances *****************************/
/* On L4, all GPIO Bank support the Lock mechanism */
#define IS_GPIO_LOCK_INSTANCE(INSTANCE) IS_GPIO_ALL_INSTANCE(INSTANCE)

/******************************** HSEM Instances *******************************/
#define IS_HSEM_ALL_INSTANCE(INSTANCE) ((INSTANCE) == HSEM)
/********************  Bit definition for HSEM_CR register  *****************/
#define HSEM_CPU1_COREID (0x00000001U) /* Semaphore Core CA7 ID */
#define HSEM_CPU2_COREID (0x00000002U) /* Semaphore Core CM4 ID */
#define HSEM_CR_COREID_CURRENT (HSEM_CPU1_COREID << HSEM_CR_COREID_Pos)

#define HSEM_SEMID_MIN (0U)	 /* HSEM ID Min*/
#define HSEM_SEMID_MAX (31U) /* HSEM ID Max */

#define HSEM_PROCESSID_MIN (0U)	  /* HSEM Process ID Min */
#define HSEM_PROCESSID_MAX (255U) /* HSEM Process ID Max */

#define HSEM_CLEAR_KEY_MIN (0U)		 /* HSEM clear Key Min value */
#define HSEM_CLEAR_KEY_MAX (0xFFFFU) /* HSEM clear Key Max value */

/******************************** I2C Instances *******************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == I2C1) || ((INSTANCE) == I2C2) || ((INSTANCE) == I2C3) || ((INSTANCE) == I2C4) ||                   \
	 ((INSTANCE) == I2C5) || ((INSTANCE) == I2C6))
/************** I2C Instances : wakeup capability from stop modes *************/
#define IS_I2C_WAKEUP_FROMSTOP_INSTANCE(INSTANCE) IS_I2C_ALL_INSTANCE(INSTANCE)

/****************************** SMBUS Instances *******************************/
#define IS_SMBUS_ALL_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == I2C1) || ((INSTANCE) == I2C2) || ((INSTANCE) == I2C3) || ((INSTANCE) == I2C4) ||                   \
	 ((INSTANCE) == I2C5) || ((INSTANCE) == I2C6))

/******************************* IPCC Instances ********************************/
#define IS_IPCC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == IPCC)

/******************************** I2S Instances *******************************/
#define IS_I2S_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || ((INSTANCE) == SPI2) || ((INSTANCE) == SPI3))

/****************************** LTDC Instances ********************************/
#define IS_LTDC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == LTDC)

/******************************* RNG Instances ********************************/
#define IS_RNG_ALL_INSTANCE(INSTANCE) (((INSTANCE) == RNG1) || ((INSTANCE) == RNG2))

/******************************* HASH Instances ********************************/
#define IS_HASH_ALL_INSTANCE(INSTANCE) (((INSTANCE) == HASH1) || ((INSTANCE) == HASH2))

/******************************* HASH Instances ********************************/
#define IS_HASH_DIGEST_ALL_INSTANCE(INSTANCE) (((INSTANCE) == HASH1_DIGEST) || ((INSTANCE) == HASH2_DIGEST))

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == RTC)

/******************************** SDMMC Instances *****************************/
#define IS_SDMMC_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SDMMC1) || ((INSTANCE) == SDMMC2) || ((INSTANCE) == SDMMC3))

/******************************** SMBUS Instances *****************************/
#define IS_SMBUS_INSTANCE(INSTANCE) ((INSTANCE) == I2C1)

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == SPI1) || ((INSTANCE) == SPI2) || ((INSTANCE) == SPI3) || ((INSTANCE) == SPI4) ||                   \
	 ((INSTANCE) == SPI5) || ((INSTANCE) == SPI6))

#define IS_SPI_HIGHEND_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || ((INSTANCE) == SPI2) || ((INSTANCE) == SPI3))

/****************** LPTIM Instances : All supported instances *****************/
#define IS_LPTIM_INSTANCE(INSTANCE)                                                                                    \
	(((INSTANCE) == LPTIM1) || ((INSTANCE) == LPTIM2) || ((INSTANCE) == LPTIM3) || ((INSTANCE) == LPTIM4) ||           \
	 ((INSTANCE) == LPTIM5))

/****************** LPTIM Instances : supporting encoder interface **************/
#define IS_LPTIM_ENCODER_INTERFACE_INSTANCE(INSTANCE) (((INSTANCE) == LPTIM1) || ((INSTANCE) == LPTIM2))

/****************** TIM Instances : All supported instances *******************/
#define IS_TIM_INSTANCE(INSTANCE)                                                                                      \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM6) || ((INSTANCE) == TIM7) || ((INSTANCE) == TIM8) ||                   \
	 ((INSTANCE) == TIM12) || ((INSTANCE) == TIM13) || ((INSTANCE) == TIM14) || ((INSTANCE) == TIM15) ||               \
	 ((INSTANCE) == TIM16) || ((INSTANCE) == TIM17))
/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM12) || ((INSTANCE) == TIM13) ||                 \
	 ((INSTANCE) == TIM14) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) || ((INSTANCE) == TIM17))
/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM12) || ((INSTANCE) == TIM15))
/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))
/************ TIM Instances : at least 5 capture/compare channels *************/
#define IS_TIM_CC5_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))
/************ TIM Instances : at least 6 capture/compare channels *************/
#define IS_TIM_CC6_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))

/******************** TIM Instances : Advanced-control timers *****************/

/******************* TIM Instances : Timer input XOR function *****************/
#define IS_TIM_XOR_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))
/****************** TIM Instances : DMA requests generation (UDE) *************/
#define IS_TIM_DMA_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM6) || ((INSTANCE) == TIM7) || ((INSTANCE) == TIM8) ||                   \
	 ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) || ((INSTANCE) == TIM17))

/************ TIM Instances : DMA requests generation (CCxDE) *****************/
#define IS_TIM_DMA_CC_INSTANCE(INSTANCE)                                                                               \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/************ TIM Instances : DMA requests generation (COMDE) *****************/
#define IS_TIM_CCDMA_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15))

/******************** TIM Instances : DMA burst feature ***********************/
#define IS_TIM_DMABURST_INSTANCE(INSTANCE)                                                                             \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/***************** TIM Instances : external trigger reamp input availabe *******/
#define IS_TIM_ETR_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/***************** TIM Instances : external trigger reamp input availabe *******/
#define IS_TIM_ETRSEL_INSTANCE(INSTANCE)                                                                               \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM5) ||                   \
	 ((INSTANCE) == TIM8))

/****** TIM Instances : master mode available (TIMx_CR2.MMS available )********/
#define IS_TIM_MASTER_INSTANCE(INSTANCE)                                                                               \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM6) || ((INSTANCE) == TIM7) || ((INSTANCE) == TIM8) ||                   \
	 ((INSTANCE) == TIM12) || ((INSTANCE) == TIM15))

/****** TIM Instances : Salve mode available (TIMx_SMCR.TS available )*********/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM12) || ((INSTANCE) == TIM15))

/****************** TIM Instances : remapping capability **********************/
#define IS_TIM_REMAP_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM5) ||                   \
	 ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting synchronization ****************/
#define IS_TIM_SYNCHRO_INSTANCE(INSTANCE) IS_TIM_MASTER_INSTANCE(INSTANCE)

/****** TIM Instances : TRGO2 available (TIMx_CR2.MMS2 available )*********/
#define IS_TIM_TRGO2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))

/****** TIM Instances : TISEL available (TIMx_TISEL available )*********/
#define IS_TIM_TISEL_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting commutation event *************/
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE)                                                                    \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/****** TIM Instances : TIM_CCR5_GC5C available (TIMx_CCR5.GC5C available )*********/
#define IS_TIM_COMBINED3PHASEPWM_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))
/******************* TIM Instances : output(s) available **********************/
#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL)                                                                         \
	((((INSTANCE) == TIM1) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM2) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM3) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM4) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM5) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM8) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) ||                         \
							   ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4))) ||                       \
	 (((INSTANCE) == TIM12) && (((CHANNEL) == TIM_CHANNEL_1))) ||                                                      \
	 (((INSTANCE) == TIM13) && (((CHANNEL) == TIM_CHANNEL_1))) ||                                                      \
	 (((INSTANCE) == TIM14) && (((CHANNEL) == TIM_CHANNEL_1))) ||                                                      \
	 (((INSTANCE) == TIM15) && (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2))) ||                      \
	 (((INSTANCE) == TIM16) && (((CHANNEL) == TIM_CHANNEL_1))) ||                                                      \
	 (((INSTANCE) == TIM17) && (((CHANNEL) == TIM_CHANNEL_1))))

/****************** TIM Instances : supporting the break function *************/
#define IS_TIM_BREAK_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/************** TIM Instances : supporting Break source selection *************/
#define IS_TIM_BREAKSOURCE_INSTANCE(INSTANCE)                                                                          \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting complementary output(s) ********/
#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL)                                                                        \
	((((INSTANCE) == TIM1) &&                                                                                          \
	  (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) || ((CHANNEL) == TIM_CHANNEL_3))) ||               \
	 (((INSTANCE) == TIM8) &&                                                                                          \
	  (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) || ((CHANNEL) == TIM_CHANNEL_3))) ||               \
	 (((INSTANCE) == TIM15) && ((CHANNEL) == TIM_CHANNEL_1)) ||                                                        \
	 (((INSTANCE) == TIM16) && ((CHANNEL) == TIM_CHANNEL_1)) ||                                                        \
	 (((INSTANCE) == TIM17) && ((CHANNEL) == TIM_CHANNEL_1)))

/****************** TIM Instances : supporting counting mode selection ********/
#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)                                                                  \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)                                                                   \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting clock division *****************/
#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)                                                                       \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16) ||                 \
	 ((INSTANCE) == TIM17))
/****************** TIM Instances : supporting external clock mode 1 for ETRF input */
#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE)                                                                 \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting external clock mode 2 **********/
#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE)                                                                 \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))
/****************** TIM Instances : supporting external clock mode 1 for TIX inputs*/
#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)                                                                      \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting internal trigger inputs(ITRX) *******/
#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)                                                                     \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8) || ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting OCxREF clear *******************/
#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3))
/****************** TIM Instances : TIM_32B_COUNTER ***************************/
#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE) (((INSTANCE) == TIM2) || ((INSTANCE) == TIM5))

/****************** TIM Instances : TIM_BKIN2 ***************************/
#define IS_TIM_BKIN2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))

/************ TIM Instances : Advanced timers  ********************************/
#define IS_TIM_ADVANCED_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting encoder interface **************/
#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)                                                                    \
	(((INSTANCE) == TIM1) || ((INSTANCE) == TIM2) || ((INSTANCE) == TIM3) || ((INSTANCE) == TIM4) ||                   \
	 ((INSTANCE) == TIM5) || ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting Hall sensor interface **********/
#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(__INSTANCE__)                                                            \
	(((__INSTANCE__) == TIM1) || ((__INSTANCE__) == TIM2) || ((__INSTANCE__) == TIM3) || ((__INSTANCE__) == TIM4) ||   \
	 ((__INSTANCE__) == TIM5) || ((__INSTANCE__) == TIM8))

/******************** USART Instances : Synchronous mode **********************/
#define IS_USART_INSTANCE(INSTANCE)                                                                                    \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == USART6))

/******************** USART Instances : SPI slave mode ************************/
#define IS_UART_SPI_SLAVE_INSTANCE(INSTANCE)                                                                           \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == USART6))

/******************** UART Instances : Asynchronous mode **********************/
#define IS_UART_INSTANCE(INSTANCE)                                                                                     \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/******************** UART Instances : FIFO mode.******************************/
#define IS_UART_FIFO_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/****************** UART Instances : Auto Baud Rate detection *****************/
#define IS_USART_AUTOBAUDRATE_DETECTION_INSTANCE(INSTANCE)                                                             \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/*********************** UART Instances : Driver Enable ***********************/
#define IS_UART_DRIVER_ENABLE_INSTANCE(INSTANCE)                                                                       \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/********************* UART Instances : Half-Duplex mode **********************/
#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE)                                                                          \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/******************* UART Instances : Hardware Flow control *******************/
#define IS_UART_HWFLOW_INSTANCE(INSTANCE)                                                                              \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/************************* UART Instances : LIN mode **************************/
#define IS_UART_LIN_INSTANCE(INSTANCE)                                                                                 \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/****************** UART Instances : Wake-up from Stop mode *******************/
#define IS_UART_WAKEUP_FROMSTOP_INSTANCE(INSTANCE)                                                                     \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/************************* UART Instances : IRDA mode *************************/
#define IS_IRDA_INSTANCE(INSTANCE)                                                                                     \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == UART4) ||            \
	 ((INSTANCE) == UART5) || ((INSTANCE) == USART6) || ((INSTANCE) == UART7) || ((INSTANCE) == UART8))

/********************* USART Instances : Smard card mode **********************/
#define IS_SMARTCARD_INSTANCE(INSTANCE)                                                                                \
	(((INSTANCE) == USART1) || ((INSTANCE) == USART2) || ((INSTANCE) == USART3) || ((INSTANCE) == USART6))

/****************************** IWDG Instances ********************************/
#define IS_IWDG_ALL_INSTANCE(INSTANCE) (((INSTANCE) == IWDG1) || ((INSTANCE) == IWDG2))

/****************************** USB Instances ********************************/
#define IS_USB_ALL_INSTANCE(INSTANCE) ((INSTANCE) == USB)

/****************************** WWDG Instances ********************************/

#define IS_WWDG_ALL_INSTANCE(INSTANCE) ((INSTANCE) == WWDG1)

/****************************** MDIOS Instances ********************************/
#define IS_MDIOS_ALL_INSTANCE(INSTANCE) ((INSTANCE) == MDIOS)

/****************************** CEC Instances *********************************/
#define IS_CEC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CEC)

/****************************** SAI Instances ********************************/
#define IS_SAI_ALL_INSTANCE(INSTANCE)                                                                                  \
	(((INSTANCE) == SAI1_Block_A) || ((INSTANCE) == SAI1_Block_B) || ((INSTANCE) == SAI2_Block_A) ||                   \
	 ((INSTANCE) == SAI2_Block_B) || ((INSTANCE) == SAI3_Block_A) || ((INSTANCE) == SAI3_Block_B) ||                   \
	 ((INSTANCE) == SAI4_Block_A) || ((INSTANCE) == SAI4_Block_B))

/****************************** SPDIFRX Instances ********************************/
#define IS_SPDIFRX_ALL_INSTANCE(INSTANCE) ((INSTANCE) == SPDIFRX)

/******************************* BSEC VERSION ********************************/
#define BSEC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* TZPC VERSION ********************************/
#define TZPC_VERSION(INSTANCE) ((INSTANCE)->IP_VER)

/******************************* FMC VERSION ********************************/
#define FMC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* SYSCFG VERSION ********************************/
#define SYSCFG_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* ETHERNET VERSION ********************************/
#define ETH_VERSION(INSTANCE) ((INSTANCE)->MACVR)

/******************************* EXTI VERSION ********************************/
#define EXTI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* PWR VERSION ********************************/
#define PWR_VERSION(INSTANCE) ((INSTANCE)->VER)

/******************************* RCC VERSION ********************************/
#define RCC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* HDP VERSION ********************************/
#define HDP_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* IPCC VERSION ********************************/
#define IPCC_VERSION(INSTANCE) ((INSTANCE)->VER)

/******************************* HSEM VERSION ********************************/
#define HSEM_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* GPIO VERSION ********************************/
#define GPIO_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DMA VERSION ********************************/
#define DMA_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DMAMUX VERSION ********************************/
#define DMAMUX_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* MDMA VERSION ********************************/
#define MDMA_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* TAMP VERSION ********************************/
#define TAMP_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* RTC VERSION ********************************/
#define RTC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* SDMMC VERSION ********************************/
#define SDMMC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* QUADSPI VERSION ********************************/
#define QUADSPI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* CRC VERSION ********************************/
#define CRC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* RNG VERSION ********************************/
#define RNG_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* HASH VERSION ********************************/
#define HASH_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* CRYP VERSION ********************************/
#define CRYP_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DCMI VERSION ********************************/
#define DCMI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* CEC VERSION ********************************/
#define CEC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* LPTIM VERSION ********************************/
#define LPTIM_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* TIM VERSION ********************************/
#define TIM_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* IWDG VERSION ********************************/
#define IWDG_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* WWDG VERSION ********************************/
#define WWDG_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DFSDM VERSION ********************************/
#define DFSDM_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* SAI VERSION ********************************/
#define SAI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* MDIOS VERSION ********************************/
#define MDIOS_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* I2C VERSION ********************************/
#define I2C_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* USART VERSION ********************************/
#define USART_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* SPDIFRX VERSION ********************************/
#define SPDIFRX_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* SPI VERSION ********************************/
#define SPI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* ADC VERSION ********************************/
#define ADC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DLYB VERSION ********************************/
#define DLYB_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DAC VERSION ********************************/
#define DAC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DSI VERSION ********************************/
#define DSI_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* USBPHYC VERSION ********************************/
#define USBPHYC_VERSION(INSTANCE) ((INSTANCE)->VERR)

/******************************* DEVICE VERSION ********************************/
#define DEVICE_REVISION() (((DBGMCU->IDCODE) & (DBGMCU_IDCODE_REV_ID_Msk)) >> DBGMCU_IDCODE_REV_ID_Pos)
#define IS_DEVICE_REV_B() (DEVICE_REVISION() == 0x2000)

/******************************* DEVICE ID  ************************************/
#define DEVICE_ID() ((DBGMCU->IDCODE) & (DBGMCU_IDCODE_DEV_ID_Msk))

/**
 * @brief  Check whether platform is engineering boot mode
 * @param  None
 * @retval TRUE or FALSE
 */
#define IS_ENGINEERING_BOOT_MODE()                                                                                     \
	(((SYSCFG->BOOTR) & (SYSCFG_BOOTR_BOOT2 | SYSCFG_BOOTR_BOOT1 | SYSCFG_BOOTR_BOOT0)) == (SYSCFG_BOOTR_BOOT2))

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
