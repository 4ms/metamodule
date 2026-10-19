/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_tmpsens.h
  * @author  MCD Application Team
  * @version V0.0.1
  * @date    01-July-2016
  * @brief   Header file of TMPSENS HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#ifndef __STM32MP1xx_HAL_TMPSENS_H
#define __STM32MP1xx_HAL_TMPSENS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal_def.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @addtogroup TMPSENS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TMPSENS_Exported_Types TMPSENS Exported Types
  * @{
  */

/**
  * @brief  TMPSENS Init structure definition
  */
typedef struct
{
  uint32_t QuickMeasure;  /*!< Specifies the quick measure option selection of
                               the TMPSENSerature sensor.
                               This parameter can be a value of
                               @ref TMPSENS_QUIKMEAS */

  uint32_t RefClock;      /*!< Specifies the reference clock selection of the
                               TMPSENSerature sensor.
                               This parameter can be a value of @ref
                               TMPSENS_REFCLKSEL */

  uint32_t TriggerInput;  /*!< Specifies the trigger input of the TMPSENSerature
                               sensor.
                               This parameter can be a value of @ref
                               TMPSENS_TriggerConfig */

  uint32_t SamplingTime;  /*!< Specifies the sampling time configuration.
                               This parameter can be a value of @ref
                               TMPSENS_SMP_TIME */

  uint32_t Divider;       /*!< Specifies the high speed clock divider ratio */

  uint32_t InterruptSource; /*!< Specifies the interrupt source of the
                                 TMPSENSerature sensor.
                                 This parameter can be a value of @ref
                                 TMPSENS_InterruptSource_Definitions */

  uint32_t HighInterruptThreshold;  /*!< Specifies the high Interrupt threshold
                                         of the TMPSENSerature sensor */

  uint32_t LowInterruptThreshold; /*!<  Specifies the low Interrupt threshold of
                                        the TMPSENSerature sensor */
#ifdef __STM32MP1xx_H
  uint32_t WakeupTarget;  /*!< Specifies the Wakeup Target.
                               This parameter can be a value of @ref
                               TMPSENS_WakeupTarget_Definitions */
#endif
}TMPSENS_InitTypeDef;


/**
  * @brief  TMPSENS Measure structure definition
  */
typedef struct
{
  int32_t Ts1_Sample;    /*!< Specifies the measured sample number for TMPSENS1
                              (for debug purposes) */
  int32_t Ts1_Fmt;       /*!< Specifies the measured frequency for TMPSENS1
                              (for debug purposes) */
  int32_t Ts1_Temp;      /*!< Specifies the measured temperature for TMPSENS1 */
  uint32_t Ts1_Count_R;   /*!< Specifies the number of reads before getting a SW
                               measured temperature for TMPSENS1
                               (for debug purposes)*/
}TMPSENS_MeasureTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_TMPSENS_STATE_RESET       = 0x00, /*!< TMPSENS not yet initialized or
                                             disabled */
  HAL_TMPSENS_STATE_READY       = 0x01, /*!< TMPSENS initialized and ready for
                                             use */
  HAL_TMPSENS_STATE_CALIBBUSY   = 0x02, /*!< TMPSENS is enabled in auto
                                             calibration mode */
  HAL_TMPSENS_STATE_BUSY        = 0x03, /*!< TMPSENS is running */
  HAL_TMPSENS_STATE_BUSY_LOCKED = 0x04  /*!< TMPSENS is running and the
                                             configuration is locked */
}HAL_TMPSENS_StateTypeDef;

/**
  * @brief  TMPSENS Handle Structure definition
  */
typedef struct
{
  TMPSENS_TypeDef         *Instance;    /*!< Register base address */
  TMPSENS_InitTypeDef     Init;         /*!< TMPSENS required parameters */
  TMPSENS_MeasureTypeDef  Measure;      /*!< Measured values */
  HAL_LockTypeDef         Lock;         /*!< Locking object */
  __IO HAL_TMPSENS_StateTypeDef  State; /*!< COMP communication state */
} TMPSENS_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup TMPSENS_Exported_Constants TMPSENS Exported Constants
  * @{
  */

/** @defgroup TMPSENS_TriggerConfig  TMPSENS Trigger Configuration
  * @{
  */

/* @brief No Hardware trigger detection */
#define TMPSENS_TRIGGER_HW_NONE   (0U)

/* @brief External Interrupt Mode with LPTIMER1 trigger detection */
#define TMPSENS_TRIGGER_LPTIMER1  TMPSENS_CFGR1_TS1_INTRIG_SEL_0

/* @brief External Interrupt Mode with LPTIMER2 trigger detection */
#define TMPSENS_TRIGGER_LPTIMER2  TMPSENS_CFGR1_TS1_INTRIG_SEL_1

/* @brief External Interrupt Mode with LPTIMER3 trigger detection */
#define TMPSENS_TRIGGER_LPTIMER3  ((uint32_t)TMPSENS_CFGR1_TS1_INTRIG_SEL_0 \
                                   | TMPSENS_CFGR1_TS1_INTRIG_SEL_1)

/* @brief External Interrupt Mode with EXTI13 trigger detection */
#define TMPSENS_TRIGGER_SYSCFG_EXTI13 TMPSENS_CFGR1_TS1_INTRIG_SEL_2

/* @brief No Hardware trigger detection on continuous mode */
#define TMPSENS_TRIGGER_HW_NONE_CONT  ((uint32_t)TMPSENS_CFGR1_TS1_INTRIG_SEL_0 \
                                       | TMPSENS_CFGR1_TS1_INTRIG_SEL_1 \
                                       | TMPSENS_CFGR1_TS1_INTRIG_SEL_2)
/**
  * @}
  */

/** @defgroup TMPSENS_QUIKMEAS  TMPSENS Quick Measurement
  * @{
  */
#define TMPSENS_QUICKMEAS_ENABLE \
          TMPSENS_CFGR1_Q_MEAS_OPT      /*!< Enable the Quick Measure (Measure
                                             without calibration) */
#define TMPSENS_QUICKMEAS_DISABLE (0U)  /*!< Disable the Quick Measure (Measure
                                             with calibration) */
/**
  * @}
  */

/** @defgroup TMPSENS_REFCLKSEL   TMPSENS Reference Clock Selection
  * @{
  */
#define TMPSENS_REFCLKSEL_LSE \
          TMPSENS_CFGR1_REFCLK_SEL  /*!< Low speed REF clock (LSE) */
#define TMPSENS_REFCLKSEL_PCLK (0U) /*!< High speed REF clock (PCLK) */

/**
  * @}
  */

/** @defgroup TMPSENS_SMP_TIME   TMPSENS Sampling Time
  * @{
  */
#define TMPSENS_SMP_TIME_1_CYCLE    ((uint32_t)(0x00000000 | TMPSENS_CFGR1_TS1_SMP_TIME_0))                     /*!< 1 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_2_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_1))                                  /*!< 2 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_3_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_1))   /*!< 3 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_4_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_2))                                  /*!< 4 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_5_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_2))   /*!< 5 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_6_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_2))   /*!< 6 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_7_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_2))     /*!< 7 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_8_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_3))                                  /*!< 8 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_9_CYCLE    ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_3))   /*!< 9 clock cycle for the sampling time  */
#define TMPSENS_SMP_TIME_10_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_3))   /*!< 10 clock cycle for the sampling time */
#define TMPSENS_SMP_TIME_11_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_3))     /*!< 11 clock cycle for the sampling time */
#define TMPSENS_SMP_TIME_12_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_2 | TMPSENS_CFGR1_TS1_SMP_TIME_3))   /*!< 12 clock cycle for the sampling time */
#define TMPSENS_SMP_TIME_13_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_2 | TMPSENS_CFGR1_TS1_SMP_TIME_3))     /*!< 13 clock cycle for the sampling time */
#define TMPSENS_SMP_TIME_14_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_2 | TMPSENS_CFGR1_TS1_SMP_TIME_3))     /*!< 14 clock cycle for the sampling time */
#define TMPSENS_SMP_TIME_15_CYCLE   ((uint32_t)(TMPSENS_CFGR1_TS1_SMP_TIME_0 | TMPSENS_CFGR1_TS1_SMP_TIME_1 | TMPSENS_CFGR1_TS1_SMP_TIME_2 | TMPSENS_CFGR1_TS1_SMP_TIME_3)) /*!< 15 clock cycle for the sampling time */

/**
  * @}
  */
/** @defgroup TMPSENS_InterruptSource_Definitions  TMPSENS Interrupt Source Definitions
  * @{
  */
#define TMPSENS_ITSRC_HIGH      TMPSENS_ITENR_TS1_ITHEN
#define TMPSENS_ITSRC_LOW       TMPSENS_ITENR_TS1_ITLEN
#define TMPSENS_ITSRC_END       TMPSENS_ITENR_TS1_ITEEN
#define TMPSENS_ITSRC_ASYN_HIGH TMPSENS_ITENR_TS1_AITHEN
#define TMPSENS_ITSRC_ASYN_LOW  TMPSENS_ITENR_TS1_AITLEN
#define TMPSENS_ITSRC_ASYN_END  TMPSENS_ITENR_TS1_AITEEN

/**
  * @}
  */

/** @defgroup TMPSENS_WakeupTarget_Definitions TMPSENS Wakeup Target Definitions
  * @{
  */
#define TMPSENS_WAKEUPTARGET_CPU1 (1U)
#define TMPSENS_WAKEUPTARGET_CPU2 (2U)
/**
  * @}
  */
/** @defgroup TMPSENS_Flag TMPSENS Flag
  * @{
  */
#define TMPSENS_FLAG_TS1_ITEF   TMPSENS_SR_TS1_ITEF   /*!< Interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_FLAG_TS1_ITLF   TMPSENS_SR_TS1_ITLF   /*!< Interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_FLAG_TS1_ITHF   TMPSENS_SR_TS1_ITHF   /*!< Interrupt flag for high threshold for TMPSENS1 */
#define TMPSENS_FLAG_TS1_AITEF  TMPSENS_SR_TS1_AITEF  /*!< Asynchronous Interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_FLAG_TS1_AITLF  TMPSENS_SR_TS1_AITLF  /*!< Asynchronous Interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_FLAG_TS1_AITHF  TMPSENS_SR_TS1_AITHF  /*!< Asynchronous Interrupt flag for high threshold for TMPSENS1 */
#define TMPSENS_FLAG_TS1_RDY    TMPSENS_SR_TS1_RDY    /*!< Ready flag for TMPSENS1 */

/**
  * @}
  */
/** @defgroup TMPSENS_IT_CLEAR Flags  TMPSENS Interruption Clear Flags
  * @{
  */
#define TMPSENS_CLEAR_TS1_CITEF   TMPSENS_ICIFR_TS1_CITEF   /*!< Clear Interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_CLEAR_TS1_CITLF   TMPSENS_ICIFR_TS1_CITLF   /*!< Clear Interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_CLEAR_TS1_CITHF   TMPSENS_ICIFR_TS1_CITHF   /*!< Clear Interrupt flag for high threshold for TMPSENS1 */
#define TMPSENS_CLEAR_TS1_CAITEF  TMPSENS_ICIFR_TS1_CAITEF  /*!< Clear Asynchronous Interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_CLEAR_TS1_CAITLF  TMPSENS_ICIFR_TS1_CAITLF  /*!< Clear Asynchronous Interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_CLEAR_TS1_CAITHF  TMPSENS_ICIFR_TS1_CAITHF  /*!< Clear Asynchronous Interrupt flag for high threshold for TMPSENS1 */

/**
  * @}
  */
/** @defgroup TMPSENS_Interrupts_Definitions TMPSENS Interrupts Definitions
  * @{
  */
#define TMPSENS_IT_TS1_ITEEN  TMPSENS_ITENR_TS1_ITEEN   /*!< Enable interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_IT_TS1_ITLEN  TMPSENS_ITENR_TS1_ITLEN   /*!< Enable interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_IT_TS1_ITHEN  TMPSENS_ITENR_TS1_ITHEN   /*!< Enable interrupt flag for high threshold for TMPSENS1 */
#define TMPSENS_IT_TS1_AITEEN TMPSENS_ITENR_TS1_AITEEN  /*!< Enable asynchronous interrupt flag for end of measure for TMPSENS1 */
#define TMPSENS_IT_TS1_AITLEN TMPSENS_ITENR_TS1_AITLEN  /*!< Enable asynchronous interrupt flag for low threshold for TMPSENS1  */
#define TMPSENS_IT_TS1_AITHEN TMPSENS_ITENR_TS1_AITHEN  /*!< Enable asynchronous interrupt flag for high threshold for TMPSENS1 */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/** @defgroup TMPSENS_Exported_Macros TMPSENS Exported Macros
  * @{
  */

/** @brief  Reset TMPSENS handle state
  * @param  __HANDLE__ TMPSENS handle.
  * @retval None
  */
#define __HAL_TMPSENS_RESET_HANDLE_STATE(__HANDLE__)  \
        ((__HANDLE__)->State = HAL_TMPSENS_STATE_RESET)

/**
  * @brief  Enable the specified TMPSENSerature sensor
  * @param  __HANDLE__ TMPSENS handle.
  * @retval None
  */
#define __HAL_TMPSENS_ENABLE(__HANDLE__)  \
        SET_BIT((__HANDLE__)->Instance->CFGR1, TMPSENS_CFGR1_TS1_EN)

/**
  * @brief  Disable the specified TMPSENSerature sensor
  * @param  __HANDLE__ TMPSENS handle.
  * @retval None
  */
#define __HAL_TMPSENS_DISABLE(__HANDLE__) \
        CLEAR_BIT((__HANDLE__)->Instance->CFGR1, TMPSENS_CFGR1_TS1_EN)

#if defined(CORE_CA7)
/**
  * @brief  Enable the TMPSENS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_ENABLE_IT()  \
        SET_BIT(EXTI_C1->IMR3,TMPSENS_EXTI_LINE_TMPSENS1)

/**
  * @brief  Disable the TMPSENS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_DISABLE_IT() \
        CLEAR_BIT(EXTI_C1->IMR3,TMPSENS_EXTI_LINE_TMPSENS1)

/**
  * @brief  Enable the TMPSENS EXTI Line in event mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_ENABLE_EVENT() \
        SET_BIT(EXTI_C1->EMR3,TMPSENS_EXTI_LINE_TMPSENS1)

/**
  * @brief  Disable the TMPSENS EXTI Line in event mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_DISABLE_EVENT()  \
        CLEAR_BIT(EXTI_C1->EMR3, TMPSENS_EXTI_LINE_TMPSENS1)

#elif defined(CORE_CM4)

/**
  * @brief  Enable the TMPSENS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_ENABLE_IT()  \
        SET_BIT(EXTI_C2->IMR3,TMPSENS_EXTI_LINE_TMPSENS1)

/**
  * @brief  Disable the TMPSENS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_DISABLE_IT() \
        CLEAR_BIT(EXTI_C2->IMR3,TMPSENS_EXTI_LINE_TMPSENS1)


/**
  * @brief  Enable the TMPSENS EXTI Line in event mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_ENABLE_EVENT() \
        SET_BIT(EXTI_C2->EMR3,TMPSENS_EXTI_LINE_TMPSENS1)


/**
  * @brief  Disable the TMPSENS EXTI Line in event mode
  * @retval None
  */
#define __HAL_TMPSENS_EXTI_DISABLE_EVENT()  \
        CLEAR_BIT(EXTI_C2->EMR3, TMPSENS_EXTI_LINE_TMPSENS1)

#endif /* CORE_CM4 */

/** @brief  Checks whether the specified TMPSENS flag is set or not.
  * @param  __HANDLE__ specifies the TMPSENS Handle.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg TMPSENS_FLAG_TS1_ITEF:  Interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_ITLF:  Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_ITHF:  Interrupt flag for high threshold for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_AITLF: Asynchronous Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_AITLF: Asynchronous Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_AITLF: Asynchronous Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_FLAG_TS1_RDY:   Ready flag for TMPSENS1
  *            @retval The new state of __FLAG__ (SET or RESET).
  */
#define __HAL_TMPSENS_GET_FLAG(__HANDLE__, __FLAG__)  \
        (((((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__)))? SET : RESET)


/** @brief  Clears the specified TMPSENS pending flag.
  * @param  __HANDLE__ specifies the TMPSENS Handle.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg TMPSENS_CLEAR_TS1_CITEF: Clear Interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_CLEAR_TS1_CITLF: Clear Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_CLEAR_TS1_CITHF: Clear Interrupt flag for high threshold for TMPSENS1
  *            @arg TMPSENS_CLEAR_TS1_CAITLF: Clear Asynchronous Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_CLEAR_TS1_CAITLF: Clear Asynchronous Interrupt flag for low threshold for TMPSENS1
  *            @arg TMPSENS_CLEAR_TS1_CAITLF: Clear Asynchronous Interrupt flag for low threshold for TMPSENS1
  * @retval None
  */
#define __HAL_TMPSENS_CLEAR_FLAG(__HANDLE__, __FLAG__)  \
        ((__HANDLE__)->Instance->ICIFR  = (__FLAG__))


/** @brief  Enable the specified TMPSENS interrupt.
  * @param  __HANDLE__ specifies the TMPSENS Handle.
  * @param  __INTERRUPT__ specifies the TMPSENS interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg TMPSENS_IT_TS1_ITEEN :Enable interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITLEN :Enable interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITHEN :Enable interrupt flag for high of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITEEN :Enable asynchronous interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITLEN :Enable asynchronous interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITHEN :Enable asynchronous interrupt flag for high of measure for TMPSENS1
  * @retval None
  */
#define __HAL_TMPSENS_ENABLE_IT(__HANDLE__, __INTERRUPT__)  \
        SET_BIT((__HANDLE__)->Instance->ITENR, __INTERRUPT__)


/** @brief  Disable the specified TMPSENS interrupt.
  * @param  __HANDLE__ specifies the TMPSENS Handle.
  * @param  __INTERRUPT__ specifies the TMPSENS interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg TMPSENS_IT_TS1_ITEEN :Enable interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITLEN :Enable interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITHEN :Enable interrupt flag for high of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITEEN :Enable asynchronous interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITLEN :Enable asynchronous interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITHEN :Enable asynchronous interrupt flag for high of measure for TMPSENS1
  * @retval None
  */
#define __HAL_TMPSENS_DISABLE_IT(__HANDLE__,__INTERRUPT__)  \
        CLEAR_BIT((__HANDLE__)->Instance->ITENR, __INTERRUPT__)


/** @brief  Check whether the specified TMPSENS interrupt source is enabled or not.
  * @param __HANDLE__ TMPSENS handle.
  * @param __INTERRUPT__ TMPSENS interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg TMPSENS_IT_TS1_ITEEN :Enable interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITLEN :Enable interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_ITHEN :Enable interrupt flag for high of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITEEN :Enable asynchronous interrupt flag for end of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITLEN :Enable asynchronous interrupt flag for low of measure for TMPSENS1
  *            @arg TMPSENS_IT_TS1_AITHEN :Enable asynchronous interrupt flag for high of measure for TMPSENS1
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_TMPSENS_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  \
        (( ((__HANDLE__)->Instance->ITENR & (__INTERRUPT__)) == (__INTERRUPT__) \
        )? SET : RESET)


/** @brief  Check whether the specified TMPSENS REFCLK is selected
  * @param __HANDLE__ TMPSENS handle.
  * @param __REFCLK__ TMPSENS reference clock to check
  *          This parameter can be one of the following values:
  * @arg TMPSENS_REFCLKSEL_LSE:   Low speed REF clock
  * @arg TMPSENS_REFCLKSEL_PCLK:  High speed REF clock
  * @retval State of the REF clock tested (SET or RESET)
  */
#define __HAL_TMPSENS_GET_REFCLK(__HANDLE__, __REFCLK__)  \
        (( ((__HANDLE__)->Instance->CFGR1 & (__REFCLK__)) == (__REFCLK__) \
        )? SET : RESET)

/** @brief  Check whether the specified TMPSENS TRIGGER is selected
  * @param __HANDLE__ TMPSENS handle.
  * @param __TRIGGER__ TMPSENS input trigger to check
  *          This parameter can be one of the following values:
  * @arg TMPSENS_TRIGGER_HW_NONE:       No HW trigger (SW trigger)
  * @arg TMPSENS_TRIGGER_LPTIMER1:      LPTIMER1 trigger
  * @arg TMPSENS_TRIGGER_LPTIMER2:      LPTIMER2 trigger
  * @arg TMPSENS_TRIGGER_LPTIMER3:      LPTIMER3 trigger
  * @arg TMPSENS_TRIGGER_SYSCFG_EXTI13: EXTI13 trigger
  * @retval State of the input TRIGGER tested (SET or RESET)
  */
#define __HAL_TMPSENS_GET_TRIGGER(__HANDLE__, __TRIGGER__)  \
    (( ((__HANDLE__)->Instance->CFGR1 & (TMPSENS_CFGR1_TS1_INTRIG_SEL)) == (__TRIGGER__) \
     )? SET : RESET)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TMPSENS_Exported_Functions
  * @{
  */

/** @addtogroup TMPSENS_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_TMPSENS_Init(TMPSENS_HandleTypeDef *hTMPSENS);
HAL_StatusTypeDef HAL_TMPSENS_DeInit (TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_MspInit(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_MspDeInit(TMPSENS_HandleTypeDef *hTMPSENS);
/**
  * @}
  */

/* IO operation functions  *****************************************************/
/** @addtogroup TMPSENS_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_TMPSENS_Start(TMPSENS_HandleTypeDef *hTMPSENS);
HAL_StatusTypeDef HAL_TMPSENS_Stop(TMPSENS_HandleTypeDef *hTMPSENS);
HAL_StatusTypeDef HAL_TMPSENS_GetTMPSENS(TMPSENS_HandleTypeDef *hTMPSENS);
HAL_StatusTypeDef HAL_TMPSENS_Start_IT(TMPSENS_HandleTypeDef *hTMPSENS);
HAL_StatusTypeDef HAL_TMPSENS_Stop_IT(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_IRQHandler(TMPSENS_HandleTypeDef *hTMPSENS);
/* Callback in Interrupt mode */
void              HAL_TMPSENS_EndCallback(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_LowCallback(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_HighCallback(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_AsyncEndCallback(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_AsyncLowCallback(TMPSENS_HandleTypeDef *hTMPSENS);
void              HAL_TMPSENS_AsyncHighCallback(TMPSENS_HandleTypeDef *hTMPSENS);
/**
  * @}
  */

/* Peripheral Control functions  ************************************************/
/** @addtogroup TMPSENS_Exported_Functions_Group3
  * @{
  */

/**
  * @}
  */

/* Peripheral State functions  **************************************************/
/** @addtogroup TMPSENS_Exported_Functions_Group4
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup TMPSENS_Private_Constants TMPSENS Private Constants
  * @{
  */
/** @defgroup TMPSENS_ExtiLine TMPSENS EXTI Lines
  * @{
  */
#if defined(STM32MP1)
#define TMPSENS_EXTI_LINE_TMPSENS1           (EXTI_IMR3_IM72)  /*!< EXTI line 72 connected to TMPSENS1 output */
#endif
/**
  * @}
  */

/** @defgroup TMPSENS_IT_Type TMPSENS IT Type
  * @{
  */
#define TMPSENS_IT_ASYNC  (TMPSENS_IT_TS1_AITEEN | TMPSENS_IT_TS1_AITLEN | TMPSENS_IT_TS1_AITHEN) /*!< TEMPSENS ASYNC IT */
#define TMPSENS_IT_SYNC   (TMPSENS_IT_TS1_ITEEN | TMPSENS_IT_TS1_ITLEN | TMPSENS_IT_TS1_ITHEN)    /*!< TEMPSENS SYNC IT */
/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup TMPSENS_Private_Macros TMPSENS Private Macros
  * @{
  */

/** @defgroup TMPSENS_IS_TMPSENS_Definitions  TMPSENS Private macros to check input parameters
  * @{
  */
#define IS_TMPSENS_QUICKMEAS(__SEL__)   (((__SEL__) == TMPSENS_QUICKMEAS_DISABLE) || \
                                         ((__SEL__) == TMPSENS_QUICKMEAS_ENABLE))

#define IS_TMPSENS_REFCLK(__SEL__)      (((__SEL__) == TMPSENS_REFCLKSEL_LSE) || \
                                         ((__SEL__) == TMPSENS_REFCLKSEL_PCLK))


#define IS_TMPSENS_TRIGGERINPUT(__INPUT__)  (((__INPUT__) == TMPSENS_TRIGGER_HW_NONE)   || \
                                             ((__INPUT__) == TMPSENS_TRIGGER_LPTIMER1)  || \
                                             ((__INPUT__) == TMPSENS_TRIGGER_LPTIMER2)  || \
                                             ((__INPUT__) == TMPSENS_TRIGGER_LPTIMER3)  || \
                                             ((__INPUT__) == TMPSENS_TRIGGER_SYSCFG_EXTI13) || \
                                             ((__INPUT__) == TMPSENS_TRIGGER_HW_NONE_CONT))

#define IS_TMPSENS_INTERRUPTTHRESHOLD(__THRESHOLD__)  ((__THRESHOLD__) <= 0xFFFF)

#define IS_TMPSENS_DIVIDER_RATIO_NUMBER(__NUMBER__) (((__NUMBER__) >= ((uint32_t)2)) && ((__NUMBER__) <= ((uint32_t)127)))

#define IS_TMPSENS_SAMPLINGTIME(__CYCLE__)  (((__CYCLE__) == TMPSENS_SMP_TIME_1_CYCLE)  || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_2_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_3_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_4_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_5_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_6_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_7_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_8_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_9_CYCLE)    || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_10_CYCLE)   || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_11_CYCLE)   || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_12_CYCLE)   || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_13_CYCLE)   || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_14_CYCLE)   || \
                                             ((__CYCLE__) == TMPSENS_SMP_TIME_15_CYCLE))
/* All combinations of interrupts are allowed */
#define IS_TMPSENS_INTERRUPTSOURCE(__SOURCE__)  ((((__SOURCE__) & ~(TMPSENS_IT_ASYNC | TMPSENS_IT_SYNC)) == RESET) && \
                                                 (((__SOURCE__) & (TMPSENS_IT_ASYNC | TMPSENS_IT_SYNC)) != RESET))
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP1xx_HAL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
