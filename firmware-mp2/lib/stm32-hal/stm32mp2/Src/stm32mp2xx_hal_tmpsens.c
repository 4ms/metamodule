/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_tmpsens.c
  * @author  MCD Application Team
  * @version V0.0.1
  * @date    01-July-2016
  * @brief   TMPSENS HAL module driver.  
  *          This file provides firmware functions to manage the following 
  *          functionalities of the TMPSENS peripheral:
  *           + Initialization and de-initialization functions
  *           + Start/Stop operation functions in polling mode.
  *           + Start/Stop operation functions in interrupt mode.
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *         
  @verbatim
================================================================================
          ##### TMPSENS Peripheral features #####
================================================================================
           
  [..]       
      The STM32MP1xx device family integrate one TMPSENSerature sensor interface :

 
            ##### How to use this driver #####
================================================================================
  [..]

      
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @defgroup TMPSENS TMPSENS
  * @brief TMPSENS HAL module driver
  * @{
  */

#ifdef HAL_TMPSENS_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup TMPSENS_Private_Constants
  * @{
  */

/* @brief CFGR register reset value */
#define TMPSENS_CFGR1_RESET_VALUE (0U)

/* @brief Delay for TMPSENS startup time
 * @note  Delay required to get ready for TMPSENS Block.
 * @note  Unit: ms
 */
#define TMPSENS_DELAY_STARTUP (1U)

/* @brief TMPSENS measure ready flag time out value.
 * @note  Maximal measurement time is when LSE is selected as ref_clock and
 *        maximal sampling time is used, taking calibration into account this
 *        is equivalent to ~620 us. Use 5 ms as arbitrary timeout
 * @note Unit: ms
 */
#define TS_TIMEOUT_MS (5U)

/* @brief TMPSENS High Speed Clock frequency
 * @note Unit: 100 Hz
 */
#if defined(STM32MP1)
#define HS_CLK_FREQ   (HAL_RCC_GetPCLK3Freq())
#endif
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup TMPSENS_Exported_Functions TMPSENS Exported Functions
  * @{
  */

/** @defgroup TMPSENS_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @brief    Initialization and de-initialization functions.
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions to initialize and de-initialize comparators

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the TMPSENS according to the specified
  *         parameters in the TMPSENS_InitTypeDef and initialize the associated handle.
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_Init(TMPSENS_HandleTypeDef *htmpsens)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the TMPSENS handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if ((htmpsens == NULL)  || (htmpsens->State == HAL_TMPSENS_STATE_BUSY_LOCKED)
                      || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    return HAL_ERROR;
  }
  else
  {
    /* Check the parameters */
    assert_param(IS_TMPSENS_ALL_INSTANCE(htmpsens->Instance));
    assert_param(IS_TMPSENS_QUICKMEAS(htmpsens->Init.QuickMeasure));
    assert_param(IS_TMPSENS_REFCLK(htmpsens->Init.RefClock));
    assert_param(IS_TMPSENS_TRIGGERINPUT(htmpsens->Init.TriggerInput));
    assert_param(IS_TMPSENS_SAMPLINGTIME(htmpsens->Init.SamplingTime));
    assert_param(IS_TMPSENS_INTERRUPTTHRESHOLD(htmpsens->Init.HighInterruptThreshold));
    assert_param(IS_TMPSENS_INTERRUPTTHRESHOLD(htmpsens->Init.LowInterruptThreshold));

    if (htmpsens->State == HAL_TMPSENS_STATE_RESET)
    {
      /* Init the low level hardware */
      HAL_TMPSENS_MspInit(htmpsens);
    }

    /* Check Quick Measure option is enabled or disabled */
    if (htmpsens->Init.QuickMeasure == TMPSENS_QUICKMEAS_DISABLE)
    {
      /* Check Reference clock selection */
      if (htmpsens->Init.RefClock == TMPSENS_REFCLKSEL_PCLK)
      {
        assert_param(IS_TMPSENS_DIVIDER_RATIO_NUMBER(htmpsens->Init.Divider));
      }
      /* Quick measurement mode disabled */
      CLEAR_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_Q_MEAS_OPT);
    }
    else
    { /* TMPSENS_QUICKMEAS_ENABLE shall be used only when the LSE clock is
         selected as reference clock */
      if (htmpsens->Init.RefClock != TMPSENS_REFCLKSEL_LSE)
      {
        return HAL_ERROR;
      }
      /* Quick measurement mode enabled
         No calibration needed */
      SET_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_Q_MEAS_OPT);
    }

    /* set the TMPSENS clk source */
    if (htmpsens->Init.RefClock == TMPSENS_REFCLKSEL_LSE)
    {
       SET_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_REFCLK_SEL);
    }
    else
    {
      CLEAR_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_REFCLK_SEL);
    }

    MODIFY_REG(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_HSREF_CLK_DIV,
               (htmpsens->Init.Divider << TMPSENS_CFGR1_HSREF_CLK_DIV_Pos));
    MODIFY_REG(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_SMP_TIME,
               htmpsens->Init.SamplingTime);

    if (htmpsens->Init.TriggerInput == TMPSENS_TRIGGER_HW_NONE_CONT)
    {
      MODIFY_REG(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_INTRIG_SEL,
                 TMPSENS_TRIGGER_HW_NONE);
    }
    else
    {
      MODIFY_REG(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_INTRIG_SEL,
                 htmpsens->Init.TriggerInput);
    }

    MODIFY_REG(htmpsens->Instance->ITR1, TMPSENS_ITR1_TS1_HITTHD,
               (htmpsens->Init.HighInterruptThreshold << TMPSENS_ITR1_TS1_HITTHD_Pos));
    MODIFY_REG(htmpsens->Instance->ITR1, TMPSENS_ITR1_TS1_LITTHD,
               htmpsens->Init.LowInterruptThreshold);

    /* Set HAL TMPSENS handle state */
    if (htmpsens->State == HAL_TMPSENS_STATE_RESET)
    {
       htmpsens->State = HAL_TMPSENS_STATE_READY;
    }
  }

  return status;
}

/**
  * @brief  DeInitialize the TMPSENS peripheral.
  * @note   Deinitialization cannot be performed if the TMPSENS configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_DeInit(TMPSENS_HandleTypeDef *htmpsens)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the TMPSENS handle allocation */
  /* DeInit not allowed if calibration is on going */
  if((htmpsens == NULL) || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_TMPSENS_ALL_INSTANCE(htmpsens->Instance));

    /* Set TMPSENS_CFGR register to reset value */
    WRITE_REG(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_RESET_VALUE);

    /* DeInit the low level hardware */
    HAL_TMPSENS_MspDeInit(htmpsens);

    htmpsens->State = HAL_TMPSENS_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htmpsens);
  }

  return status;
}

/**
  * @brief  Initialize the TMPSENS MSP.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_MspInit(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the TMPSENS MSP.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_MspDeInit(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup TMPSENS_Exported_Functions_Group2 Start-Stop operation functions
 *  @brief   Start-Stop operation functions.
 *
@verbatim
 ===============================================================================
                      ##### TMPSENS Start Stop operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start a TMPSENSerature Sensor without interrupt.
      (+) Stop a TMPSENSerature Sensor  without interrupt.
      (+) Start a TMPSENSerature Sensor  with interrupt generation.
      (+) Stop a TMPSENSerature Sensor  with interrupt generation.

@endverbatim
  * @{
  */

/**
  * @brief  Start the TMPSENSerature sensor.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_Start(TMPSENS_HandleTypeDef *htmpsens)
{
  uint32_t tickstart = 0;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the TMPSENS handle allocation and lock status */
  if((htmpsens == NULL) || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {
    if(htmpsens->State == HAL_TMPSENS_STATE_READY)
    {
      /* Enable the selected TMPSENSerature sensor */
      __HAL_TMPSENS_ENABLE(htmpsens);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till TS1_RDY flag is set */
      while (__HAL_TMPSENS_GET_FLAG(htmpsens, TMPSENS_FLAG_TS1_RDY) == RESET)
      {
        if ((int32_t) (HAL_GetTick() - tickstart ) > TMPSENS_DELAY_STARTUP)
        {
           return HAL_TIMEOUT;
        }
      }

      if(__HAL_TMPSENS_GET_TRIGGER(htmpsens,TMPSENS_TRIGGER_HW_NONE_CONT) == SET)
      {
        /* Start continuous measures */
        SET_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

        /* Ensure start is taken into account */
        HAL_Delay(1);
      }

      htmpsens->State = HAL_TMPSENS_STATE_BUSY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}
/**
  * @brief  Enable the interrupt(s) and start the TMPSENSerature sensor
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_Start_IT(TMPSENS_HandleTypeDef *htmpsens)
{
  uint32_t tickstart = 0;
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TMPSENS_INTERRUPTSOURCE(htmpsens->Init.InterruptSource));

  /* Check the TMPSENS handle allocation and lock status */
  if((htmpsens == NULL) || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {
    if(htmpsens->State == HAL_TMPSENS_STATE_READY)
    {
      /* On Asynchronous mode enable the TMPSENS EXTI line */
      if ((htmpsens->Init.InterruptSource & TMPSENS_IT_ASYNC) != RESET)
      {
        if (__HAL_TMPSENS_GET_REFCLK(htmpsens, TMPSENS_REFCLKSEL_LSE) != SET)
        {
          status = HAL_ERROR;
        }
        else
        {
          __HAL_TMPSENS_EXTI_ENABLE_IT();
        }
      }

      /* Enable the IT(s) */
      __HAL_TMPSENS_ENABLE_IT(htmpsens,htmpsens->Init.InterruptSource);

      /* Enable the selected TMPSENSerature sensor */
      __HAL_TMPSENS_ENABLE(htmpsens);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till TS1_RDY flag is set */
      while (__HAL_TMPSENS_GET_FLAG(htmpsens, TMPSENS_FLAG_TS1_RDY) == RESET)
      {
        if ((int32_t) (HAL_GetTick() - tickstart ) > TMPSENS_DELAY_STARTUP)
        {
           return HAL_TIMEOUT;
        }
      }

      if(__HAL_TMPSENS_GET_TRIGGER(htmpsens,TMPSENS_TRIGGER_HW_NONE_CONT) == SET)
      {
        /* Start continuous measures */
        SET_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

        /* Ensure start is taken into account */
        HAL_Delay(1);
      }

      htmpsens->State = HAL_TMPSENS_STATE_BUSY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}
/**
  * @brief  Stop the TMPSENSerature Sensor.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_Stop(TMPSENS_HandleTypeDef *htmpsens)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the TMPSENS handle allocation and lock status */
  if((htmpsens == NULL) || (htmpsens->State == HAL_TMPSENS_STATE_BUSY_LOCKED) \
                     || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {
    if(htmpsens->State == HAL_TMPSENS_STATE_BUSY)
    {
      if(__HAL_TMPSENS_GET_TRIGGER(htmpsens,TMPSENS_TRIGGER_HW_NONE_CONT) == SET)
      {
        CLEAR_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

        /* Ensure stop is taken into account */
        HAL_Delay(1);
      }

      /* Disable the selected TMPSENSerature sensor */
      __HAL_TMPSENS_DISABLE(htmpsens);

      htmpsens->State = HAL_TMPSENS_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}
/**
  * @brief  Disable the interrupt(s) and stop the TMPSENSerature sensor.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_Stop_IT(TMPSENS_HandleTypeDef *htmpsens)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TMPSENS_INTERRUPTSOURCE(htmpsens->Init.InterruptSource));

  /* Check the TMPSENS handle allocation and lock status */
  if((htmpsens == NULL) || (htmpsens->State == HAL_TMPSENS_STATE_BUSY_LOCKED) \
                     || (htmpsens->State == HAL_TMPSENS_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {
    if(htmpsens->State == HAL_TMPSENS_STATE_BUSY)
    {

      if(__HAL_TMPSENS_GET_TRIGGER(htmpsens,TMPSENS_TRIGGER_HW_NONE_CONT) == SET)
      {
        CLEAR_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

        /* Ensure stop is taken into account */
        HAL_Delay(1);
      }

      /* Disable the selected TMPSENSerature sensor */
      __HAL_TMPSENS_DISABLE(htmpsens);

      __HAL_TMPSENS_DISABLE_IT(htmpsens,htmpsens->Init.InterruptSource);

      /* On Asynchronous mode disable the TMPSENS EXTI line */
      if ((htmpsens->Init.InterruptSource & TMPSENS_IT_ASYNC) != RESET)
      {
        __HAL_TMPSENS_EXTI_DISABLE_IT();
      }

      htmpsens->State = HAL_TMPSENS_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}
/**
  * @brief  Get temperature from TMPSENS
  * @param  htmpsens  TMPSENS handle
  * @note   If TMPSENS_TRIGGER_HW_NONE (SW trigger) is used one measure is
  *         triggered by this function. Else (HW trigger) this function
  *         retrieves latest available measure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TMPSENS_GetTMPSENS(TMPSENS_HandleTypeDef *htmpsens)
{
  uint32_t tickstart = 0;

  int32_t freq_meas = 0;
  int32_t samples = 0;

  int32_t t0_temp ;
  int32_t t0_freq;
  int32_t ramp_coeff;
  uint32_t count_read = 0; /* @TODO: Erase after debug */
  uint32_t tmp_smp_time = 0;

  /* Software trigger */
  if (__HAL_TMPSENS_GET_TRIGGER(htmpsens,TMPSENS_TRIGGER_HW_NONE) == SET )
  {
    /* Start measure */
    SET_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

    /* Ensure start is taken into account */
    HAL_Delay(1);

    /* Stop measure */
    CLEAR_BIT(htmpsens->Instance->CFGR1, TMPSENS_CFGR1_TS1_START);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Wait till TS1_RDY flag is set */
    while (__HAL_TMPSENS_GET_FLAG(htmpsens, TMPSENS_FLAG_TS1_RDY) == RESET)
    {
      count_read++;
      if ((HAL_GetTick() - tickstart ) > TS_TIMEOUT_MS)
      {
        /* @TODO: erase after debug Ts1_Count_R and htmpsens->Measure.Ts1_Sample*/
         htmpsens->Measure.Ts1_Count_R = count_read;
         htmpsens->Measure.Ts1_Sample = (htmpsens->Instance->DR & TMPSENS_DR_TS1_MFREQ);
         return HAL_TIMEOUT;
      }
    }
  }

  /* Get the total number of samples */
  samples = (htmpsens->Instance->DR & TMPSENS_DR_TS1_MFREQ);

  /* Save the total number of samples (debug). @TODO: To erase */
  htmpsens->Measure.Ts1_Sample = samples;

  if (samples == RESET)
  {
    return HAL_ERROR;
  }

  tmp_smp_time = ((htmpsens->Instance->CFGR1 & TMPSENS_CFGR1_TS1_SMP_TIME) >> TMPSENS_CFGR1_TS1_SMP_TIME_Pos);
  if(tmp_smp_time == 0) {tmp_smp_time = 1;}

  /* Get the mean number of samples per period */
  samples /= tmp_smp_time;

  if ((htmpsens->Instance->CFGR1 & TMPSENS_CFGR1_REFCLK_SEL) == TMPSENS_REFCLKSEL_LSE)
  {
    freq_meas = LSE_VALUE * samples; /* On Hz */
  }
  else
  {
    freq_meas = HS_CLK_FREQ / samples; /* On Hz */
  }

  /* Save measured frequency (debug) */
  htmpsens->Measure.Ts1_Fmt = freq_meas;

  /* Read factory settings */
  t0_temp = htmpsens->Instance->T0VALR1 >> TMPSENS_T0VALR1_TS1_T0_Pos;
  if ((t0_temp  & TMPSENS_T0VALR1_TS1_T0) == 0U)
  {
    t0_temp = 30; /* 30 oC */
  }
  t0_freq = (htmpsens->Instance->T0VALR1 & TMPSENS_T0VALR1_TS1_FMT0) * 100; /* [Hz] */
  ramp_coeff = htmpsens->Instance->RAMPVALR & TMPSENS_RAMPVALR_TS1_RAMP_COEFF; /* [oC/Hz] */

  /* @TODO: To re-enable code below once SoC calibrated (to clean up)*/
#if 0
  if (ramp_coeff == RESET)
  {
    return HAL_ERROR;
  }
#else
  /* Figure out the temperature [oC] */
  htmpsens->Measure.Ts1_Temp = t0_temp + ((freq_meas - t0_freq) / ramp_coeff);
#endif

  return HAL_OK;
}

/**
  * @brief  TMPSENSerature sensor IRQ Handler.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL status
  */
void HAL_TMPSENS_IRQHandler(TMPSENS_HandleTypeDef *htmpsens)
{
  /* TMPSENS interrupts */

  /* Check end of measure Asynchronous IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_AITEF)) != RESET)
  {
      __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CAITEF);
      HAL_TMPSENS_AsyncEndCallback(htmpsens);
  }

  /* Check low threshold Asynchronous IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_AITLF)) != RESET)
  {
    __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CAITLF);
    HAL_TMPSENS_AsyncLowCallback(htmpsens);
  }

  /* Check high threshold Asynchronous IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_AITHF)) != RESET)
  {
    __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CAITHF);
    HAL_TMPSENS_AsyncHighCallback(htmpsens);
  }

  /* Check end of measure IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_ITEF)) != RESET)
  {
      __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CITEF);
      HAL_TMPSENS_EndCallback(htmpsens);
  }

  /* Check low threshold IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_ITLF)) != RESET)
  {
      __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CITLF);
      HAL_TMPSENS_LowCallback(htmpsens);
  }

  /* Check high threshold IT */
  if((__HAL_TMPSENS_GET_FLAG(htmpsens,TMPSENS_FLAG_TS1_ITHF)) != RESET)
  {
     __HAL_TMPSENS_CLEAR_FLAG(htmpsens,TMPSENS_CLEAR_TS1_CITHF);
     HAL_TMPSENS_HighCallback(htmpsens);

  }
}

/**
  * @}
  */

/** @defgroup TMPSENS_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   Management functions.
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the TMPSENSerature sensors.

@endverbatim
  * @{
  */


/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_EndCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_LowCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_HighCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_AsyncEndCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_AsyncLowCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @brief  TMPSENSerature Sensor End measure callback.
  * @param  htmpsens  TMPSENS handle
  * @retval None
  */
__weak void HAL_TMPSENS_AsyncHighCallback(TMPSENS_HandleTypeDef *htmpsens)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TMPSENS_EndCallback should be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup TMPSENS_Exported_Functions_Group4 Peripheral State functions
 *  @brief   Peripheral State functions.
 *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the TMPSENS handle state.
  * @param  htmpsens  TMPSENS handle
  * @retval HAL state
  */
HAL_TMPSENS_StateTypeDef HAL_TMPSENS_GetState(TMPSENS_HandleTypeDef *htmpsens)
{
  /* Check the TMPSENS handle allocation */
  if(htmpsens == NULL)
  {
    return HAL_TMPSENS_STATE_RESET;
  }

  /* Return TMPSENS handle state */
  return htmpsens->State;
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_COMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
