/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_csi.h
  * @author  MCD Application Team
  * @brief   Header file of CSI HAL module.
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
        and/or other materials provided with the distribution.
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
#ifndef __STM32MP2xx_HAL_CSI_H
#define __STM32MP2xx_HAL_CSI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup __STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup CSI
  * @brief CSI HAL module driver
  * @{
  */

/** @defgroup CSI_Exported_Constants CSI Exported Constants
  * @{
  */

/**
  * @brief CSI_Error_Code CSI Error Code
  */
#define HAL_CSI_ERROR_NONE            (0x00000000U)    /*!< No error                                                 */
#define HAL_CSI_ERROR_SYNC            (0x00000001U)    /*!< Invalid Synchronization error                            */
#define HAL_CSI_ERROR_WDG             (0x00000002U)    /*!< Watchdog error                                           */
#define HAL_CSI_ERROR_SPKT            (0x00000004U)    /*!< Short packet error                                       */
#define HAL_CSI_ERROR_DTID            (0x00000008U)    /*!< Data type ID  error                                      */
#define HAL_CSI_ERROR_CECC            (0x00000010U)    /*!< Corrected ECC error                                      */
#define HAL_CSI_ERROR_ECC             (0x00000020U)    /*!< ECC error                                                */
#define HAL_CSI_ERROR_CRC             (0x00000040U)    /*!< CRC error                                                */
#define HAL_CSI_ERROR_SOF             (0x00000080U)    /*!< Start Of Frame error                                     */
#define HAL_CSI_ERROR_SOFSYNC         (0x00000100U)    /*!< Start Of Frame Synchronization error                     */
#define HAL_CSI_ERROR_DPHY_ESC        (0x00000200U)    /*!< DPHY RX Escape entry error                               */
#define HAL_CSI_ERROR_DPHY_LP_SYNC    (0x00000400U)    /*!< DPHY RX Low power data transmission synchronization error */
#define HAL_CSI_ERROR_DPHY_CTRL       (0x00000800U)    /*!< DPHY RX control error                                    */

/**
  * @}
  */

/** @defgroup CSI_Private_Macros   CSI Private Macros
  * @{
  */
/** @brief Set a register from HAL CSI handle
  * @param  __HANDLE__ pointer to the CSI handle.
  * @param  __FIELD__  specifies the CSI register name.
  * @param  __VALUE__  specifies the value to be set.
  * @retval None
  */
#define __HAL_CSI_SET_REG(__HANDLE__, __FIELD__, __VALUE__) ((__HANDLE__)->Instance->__FIELD__ = (__VALUE__))

/** @brief Set a bit in a CSI register from HAL CSI handle
  * @param  __HANDLE__ pointer to the CSI handle.
  * @param  __FIELD__  specifies the CSI register name.
  * @param  __BIT__  specifies the bit to be set.
  * @retval None
  */
#define __HAL_CSI_SET_BIT(__HANDLE__, __FIELD__, __BIT__) ((__HANDLE__)->Instance->__FIELD__ |= (__BIT__))

/** @brief Clear a bit in a CSI register from HAL CSI handle
  * @param  __HANDLE__ pointer to the CSI handle.
  * @param  __FIELD__  specifies the CSI register name.
  * @param  __BIT__  specifies the bit to be clear.
  * @retval None
  */
#define __HAL_CSI_CLEAR_BIT(__HANDLE__, __FIELD__, __BIT__) ((__HANDLE__)->Instance->__FIELD__ &= ~(__BIT__))

/** @brief Get masked register value from HAL CSI handle
  * @param  __HANDLE__ pointer to the CSI handle.
  * @param  __FIELD__  specifies the CSI register name.
  * @param  __MASK__  specifies the mask to be applied.
  * @retval None
  */
#define __HAL_CSI_GET_MASKED_REG(__HANDLE__, __FIELD__, __MASK__)  ((__HANDLE__)->Instance->__FIELD__ & (__MASK__))

/** @brief Get a bit in a CSI register from HAL CSI handle
  * @param  __HANDLE__ pointer to the CSI handle.
  * @param  __FIELD__  specifies the CSI register name.
  * @param  __BIT__  specifies the bit to be checked.
  * @retval None
  */
#define __HAL_CSI_GET_BIT(__HANDLE__, __FIELD__, __BIT__) (!!((__HANDLE__)->Instance->__FIELD__ >> (__BIT__)))

#define __HAL_CSI_ENABLE_IT(__HANDLE__, __ITS__) ((__HANDLE__)->Instance->IER0 |= (__ITS__))
#define __HAL_CSI_DISABLE_IT(__HANDLE__, __ITS__) ((__HANDLE__)->Instance->IER0 &= ~(__ITS__))
#define __HAL_CSI_ENABLE_PHY_IT(__HANDLE__, __ITS__) ((__HANDLE__)->Instance->IER1 |= (__ITS__))
#define __HAL_CSI_DISABLE_PHY_IT(__HANDLE__, __ITS__) ((__HANDLE__)->Instance->IER1 &= ~(__ITS__))
/**
  * @}
  */

/** @defgroup CSI_Exported_Types CSI Exported Types
  * @{
  */
/**
  * @brief  HAL CSI State structures definition
  */
typedef enum
{
  HAL_CSI_STATE_RESET             = 0x00U,  /*!< CSI not yet initialized or disabled  */
  HAL_CSI_STATE_READY             = 0x01U,  /*!< CSI initialized and ready for use    */
  HAL_CSI_STATE_BUSY              = 0x02U,  /*!< CSI internal processing is ongoing   */
  HAL_CSI_STATE_TIMEOUT           = 0x03U,  /*!< CSI timeout state                    */
  HAL_CSI_STATE_ERROR             = 0x04U,  /*!< CSI error state                      */
  HAL_CSI_STATE_SUSPENDED         = 0x05U   /*!< CSI suspend state                    */
} HAL_CSI_StateTypeDef;

/**
  * @brief HAL CSI DPHY_RX configuration
  */
#define HAL_CSI_DPHYRX_DL0_DISABLED  0
#define HAL_CSI_DPHYRX_DL0_ENABLED   CSI_PCR_DL0EN
#define HAL_CSI_DPHYRX_DL1_DISABLED  0
#define HAL_CSI_DPHYRX_DL1_ENABLED   CSI_PCR_DL1EN
#define HAL_CSI_DPHYRX_CL_DISABLED   0
#define HAL_CSI_DPHYRX_CL_ENABLED    CSI_PCR_CLEN
#define HAL_CSI_DPHYRX_DISABLED      CSI_PCR_PWRDOWN
#define HAL_CSI_DPHYRX_ENABLED       0

/**
  * @brief HAL CSI lane merger configuration
  */
#define HAL_CSI_LM_SINGLE_LANE  (1U << CSI_LMCFGR_LANENB_Pos)
#define HAL_CSI_LM_DUAL_LANE    (2U << CSI_LMCFGR_LANENB_Pos)
#define HAL_CSI_LM_LOGIC_LANE0  (1U)
#define HAL_CSI_LM_LOGIC_LANE1  (2U)

/**
  * @brief HAL CSI Watchdog Counter configuration
  */
#define HAL_CSI_WATCHDOG_CNT_DISABLED  0

/**
  * @brief HAL CSI Common format definition
  */
typedef enum
{
  HAL_CSI_INPUTPIXEL_BPP6         = 0x00U,  /*!< 6 bit words */
  HAL_CSI_INPUTPIXEL_BPP7         = 0x01U,  /*!< 7 bit words */
  HAL_CSI_INPUTPIXEL_BPP8         = 0x02U,  /*!< 8 bit words */
  HAL_CSI_INPUTPIXEL_BPP10        = 0x03U,  /*!< 10 bit words */
  HAL_CSI_INPUTPIXEL_BPP12        = 0x04U,  /*!< 12 bit words */
  HAL_CSI_INPUTPIXEL_BPP14        = 0x05U,  /*!< 14 bit words */
  HAL_CSI_INPUTPIXEL_BPP16        = 0x06U   /*!< 16 bit words */
} HAL_CSI_InputPixelTypeDef;

/**
  * @brief  HAL CSI Lane Merger structures definition
  */
#define HAL_CSI_LANE_DISABLED  (0U)
#define HAL_CSI_LANE_ENABLED   (1U)
typedef struct
{
  uint32_t PhysicalLane0_Status;  /*!< Enable or not the Physical Lane 0 */
  uint32_t PhysicalLane0_Mapping; /*!< Mapping of Physical Lane 0        */
  uint32_t PhysicalLane1_Status;  /*!< Enable or not the Physical Lane 0 */
  uint32_t PhysicalLane1_Mapping; /*!< Mapping of Physical Lane 1        */
} CSI_LaneMergerTypeDef;

/**
  * @brief HAL CSI Bitrate definition
  */
typedef enum
{
  HAL_CSI_BT_80 = 0,
  HAL_CSI_BT_90,
  HAL_CSI_BT_100,
  HAL_CSI_BT_110,
  HAL_CSI_BT_120,
  HAL_CSI_BT_130,
  HAL_CSI_BT_140,
  HAL_CSI_BT_150,
  HAL_CSI_BT_160,
  HAL_CSI_BT_170,
  HAL_CSI_BT_180,
  HAL_CSI_BT_190,
  HAL_CSI_BT_205,
  HAL_CSI_BT_220,
  HAL_CSI_BT_235,
  HAL_CSI_BT_250,
  HAL_CSI_BT_275,
  HAL_CSI_BT_300,
  HAL_CSI_BT_325,
  HAL_CSI_BT_350,
  HAL_CSI_BT_400,
  HAL_CSI_BT_450,
  HAL_CSI_BT_500,
  HAL_CSI_BT_550,
  HAL_CSI_BT_600,
  HAL_CSI_BT_650,
  HAL_CSI_BT_700,
  HAL_CSI_BT_750,
  HAL_CSI_BT_800,
  HAL_CSI_BT_850,
  HAL_CSI_BT_900,
  HAL_CSI_BT_950,
  HAL_CSI_BT_1000,
  HAL_CSI_BT_1050,
  HAL_CSI_BT_1100,
  HAL_CSI_BT_1150,
  HAL_CSI_BT_1200,
  HAL_CSI_BT_1250,
  HAL_CSI_BT_1300,
  HAL_CSI_BT_1350,
  HAL_CSI_BT_1400,
  HAL_CSI_BT_1450,
  HAL_CSI_BT_1500,
  HAL_CSI_BT_1550,
  HAL_CSI_BT_1600,
  HAL_CSI_BT_1650,
  HAL_CSI_BT_1700,
  HAL_CSI_BT_1750,
  HAL_CSI_BT_1800,
  HAL_CSI_BT_1850,
  HAL_CSI_BT_1900,
  HAL_CSI_BT_1950,
  HAL_CSI_BT_2000,
  HAL_CSI_BT_2050,
  HAL_CSI_BT_2100,
  HAL_CSI_BT_2150,
  HAL_CSI_BT_2200,
  HAL_CSI_BT_2250,
  HAL_CSI_BT_2300,
  HAL_CSI_BT_2350,
  HAL_CSI_BT_2400,
  HAL_CSI_BT_2450,
  HAL_CSI_BT_2500,
} HAL_CSI_Bitrate;

/**
  * @brief  HAL CSI Initialization structures definition
  */
typedef struct
{
  CSI_LaneMergerTypeDef LaneMerger;       /*!< Lane Merger configuration           */
  HAL_CSI_Bitrate PhyBitrate;             /*!< Bitrange range                      */
  uint32_t WatchdogCnt;                   /*!< Watchdog Counter configuration      */
} CSI_InitTypeDef;

/**
  * @brief  HAL CSI handle structures definition
  */
typedef struct __CSI_HandleTypeDef
{
  CSI_TypeDef                    *Instance;                            /*!< CSI registers base address      */
  CSI_InitTypeDef                Init;                                 /*!< CSI init parameters             */
  __IO HAL_CSI_StateTypeDef      State;                                /*!< CSI state                       */
  __IO uint32_t                  ErrorCode;                            /*!< CSI Error code                  */
} CSI_HandleTypeDef;

/**
  * @brief  HAL CSI Virtual Channels (for HAL_CSI_Start and HAL_CSI_Stop functions only)
  */
#define HAL_CSI_VIRTUAL_CHANNEL_0 (1U << 0U)
#define HAL_CSI_VIRTUAL_CHANNEL_1 (1U << 1U)
#define HAL_CSI_VIRTUAL_CHANNEL_2 (1U << 2U)
#define HAL_CSI_VIRTUAL_CHANNEL_3 (1U << 3U)
#define HAL_CSI_ALL_VIRTUAL_CHANNELS (HAL_CSI_VIRTUAL_CHANNEL_0 | HAL_CSI_VIRTUAL_CHANNEL_1 | \
                                      HAL_CSI_VIRTUAL_CHANNEL_2 | HAL_CSI_VIRTUAL_CHANNEL_3)
#define HAL_CSI_VIRTUAL_CHANNEL_NB  (4U)

/**
  * @brief  HAL CSI Virtual Channel configuration structure definition
  */
#define HAL_CSI_DATATYPE_NB  (7U)
typedef struct
{
  uint32_t NoDataTypeFiltering;                     /*!< 0 or 1 to enable or disable DataType filtering */
  HAL_CSI_InputPixelTypeDef CommonDataTypeFormat;   /*!< DataTypeFormat applied for all data type */
  struct
  {
    uint32_t Enable;                                /*!< State (1 or 0 to enable/disable) of the datatype filtering */
    uint32_t Class;                                 /*!< Class ID */
    HAL_CSI_InputPixelTypeDef DataTypeFormat;       /*!< DataTypeFormat applied for the data type */
  } DataType[HAL_CSI_DATATYPE_NB];
} CSI_VirtualChannelConfigTypeDef;

/**
  * @brief  HAL CSI Line Byte Counters configuration structure definition
  */
typedef struct
{
  uint32_t Enable;  /*!< 1 or 0 to enable or disable the LineByte event */
  uint16_t LineCnt; /*!< Line number to detect */
  uint16_t ByteCnt; /*!< Byte number to detect */
  uint32_t VC;      /*!< Virtual Channel number */
} CSI_LineByteCounterConfigTypeDef;
#define HAL_CSI_COUNTER_NB  4

/**
  * @brief  HAL CSI Timers configuration structure definition
  */
#define HAL_CSI_TIMER_START_SOF 0
#define HAL_CSI_TIMER_START_EOF 1
typedef struct
{
  uint32_t Enable; /*!< 1 or 0 to enable or disable the Timer event */
  uint32_t Start;  /*!< 0 to start counter at Start Of Frame, 1 to start counter at End Of Frame */
  uint32_t Count;  /*!< Number of clock cycle to count from the start point */
  uint32_t VC;     /*!< Virtual Channel number */
} CSI_TimerConfigTypeDef;
#define HAL_CSI_TIMER_NB  4

/**
  * @brief  HAL CSI Error Event definition
  */
typedef enum
{
  HAL_CSI_SyncError         = (1 << 0),  /*!< Synchronisation error detected. arg0 contains the VC, arg1 unused */
  HAL_CSI_WatchdogError     = (1 << 1),  /*!< Watchdog error detected. arg0 contains the VC, arg1 unused */
  HAL_CSI_ShortPacketError  = (1 << 2),  /*!< Short packet error detected. arg0 contains the VC, arg1 contains the DT */
  HAL_CSI_DataTypeIDError   = (1 << 3),  /*!< DataTypeID error detected. arg0 contains the VC, arg1 contains the DT */
  HAL_CSI_CECCError         = (1 << 4),  /*!< CECC error detected. arg0 contains the VC, arg1 contains the DT */
  HAL_CSI_ECCError          = (1 << 5),  /*!< ECC error detected. arg0 / arg1 unused */
  HAL_CSI_CRCError          = (1 << 6),  /*!< CRC error detected. arg0 contains the VC, arg1 contains the DT */
  HAL_CSI_SOTError          = (1 << 7),  /*!< SOT error detected. arg0 contains the lane number, arg1 unused */
  HAL_CSI_SOTSynchroError   = (1 << 8),  /*!< SOT Synchronisation error detected. arg0 contains the lane number, arg1 unused */
  HAL_CSI_EscapeEntryError  = (1 << 9),  /*!< Escape mode entry error detected. arg0 contains the lane number, arg1 unused */
  HAL_CSI_LowPowerTXSynchroError  = (1 << 10), /*!< LowPowerTX Synchro error detected. arg0 contains the lane number, arg1 unused */
  HAL_CSI_ControlError  = (1 << 11),     /*!< Control error detected. arg0 contains the lane number, arg1 unused */
} HAL_CSI_ErrorEventTypeDef;

/**
  * @brief  HAL CSI Event definition
  */
typedef enum
{
  HAL_CSI_StartOfFrame     = (1 << 0), /*!< Start Of Frame detected. arg0 contains the Virtual Channel, arg1 unused */
  HAL_CSI_EndOfFrame       = (1 << 1), /*!< End of Frame detected. arg0 contains the Virtual Channel, arg1 unused */
  HAL_CSI_TimerEvent       = (1 << 2), /*!< Timer event detected. arg0 contains the Virtual Channel, arg1 unused */
  HAL_CSI_LineByte         = (1 << 3), /*!< Line/Byte event detected. arg0 contains the Virtual Channel, arg1 unused */
  HAL_CSI_CCFifoFull       = (1 << 4), /*!< Clock Changer Fifo event detected. arg0/arg1 unused */
  HAL_CSI_ShortPkt         = (1 << 5), /*!< Short packet event detected. arg0 contains the Virtual Channel, arg1 contains the current data field (bit[15:0]) and data type (bit21:16) */
} HAL_CSI_EventTypeDef;
/**
  * @}
  */

/** @defgroup CSI_Exported_Functions CSI Exported Functions
  * @{
  */
/** @addtogroup CSI_Exported_Functions_Group1 Init/DeInit/Config functions
  * @{
  */
HAL_StatusTypeDef HAL_CSI_Init(CSI_HandleTypeDef *pHcsi);
HAL_StatusTypeDef HAL_CSI_DeInit(CSI_HandleTypeDef *pHcsi);
HAL_StatusTypeDef HAL_CSI_ConfigVirtualChan(CSI_HandleTypeDef *pHcsi, uint32_t vchan,
                                            CSI_VirtualChannelConfigTypeDef *Config);
HAL_StatusTypeDef HAL_CSI_ConfigLineByteCounter(CSI_HandleTypeDef *pHcsi, uint32_t counter,
                                                const CSI_LineByteCounterConfigTypeDef *Config);
HAL_StatusTypeDef HAL_CSI_ConfigTimer(CSI_HandleTypeDef *pHcsi, uint32_t timer,const CSI_TimerConfigTypeDef *Config);
void HAL_CSI_MspInit(CSI_HandleTypeDef *pHcsi);
void HAL_CSI_MspDeInit(CSI_HandleTypeDef *pHcsi);
void HAL_CSI_WritePHYReg(CSI_HandleTypeDef *pHcsi, uint32_t reg_msb, uint32_t reg_lsb, uint32_t val);
/**
  * @}
  */

/** @addtogroup CSI_Exported_Functions_Group2 Start/Stop functions
  * @{
  */
HAL_StatusTypeDef HAL_CSI_Start(CSI_HandleTypeDef *pHcsi, uint32_t vchans);
HAL_StatusTypeDef HAL_CSI_Stop(CSI_HandleTypeDef *pHcsi, uint32_t vchans);
/**
  * @}
  */

/** @addtogroup CSI_Exported_Functions_Group3 Callback functions
  * @{
  */
void HAL_CSI_ErrorEventCallback(CSI_HandleTypeDef *pHcsi, HAL_CSI_ErrorEventTypeDef error,
                                uint32_t arg0, uint32_t arg1);
void HAL_CSI_EventCallback(CSI_HandleTypeDef *pHcsi, HAL_CSI_EventTypeDef event, uint32_t arg0, uint32_t arg1);
/**
  * @}
  */

/** @addtogroup CSI_Exported_Functions_Group4 Peripheral State functions
* @{
*/
HAL_CSI_StateTypeDef HAL_CSI_GetState(const CSI_HandleTypeDef *pHcsi);
uint32_t HAL_CSI_GetError(const CSI_HandleTypeDef *pHcsi);
/**
  * @}
  */

/** @addtogroup CSI_Exported_Functions_Group5 IRQ handler function
* @{
*/
void HAL_CSI_IRQHandler(CSI_HandleTypeDef *pHcsi);
/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_HAL_CSI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
