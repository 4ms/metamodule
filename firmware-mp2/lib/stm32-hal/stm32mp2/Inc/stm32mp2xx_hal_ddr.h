/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ddr.h
  * @author  MCD Application Team
  * @brief   Header file of DDR HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_DDR_H
#define STM32MP2xx_HAL_DDR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32mp2xx_hal_def.h"

#if defined (DDRC) && defined (DDRPHYC)

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup DDR
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DDR_Exported_Types DDR Exported Types
  * @{
  */

/* Maximum number of PHY pstates used by the driver */
#define HAL_DDR_MAX_PSTATE 1

/* Maximum Number of swizzling parameters */
#define HAL_DDR_MAX_SWIZZLE_PARAM 44

/**
  * @brief  HAL DDR type definition
  */
typedef enum {
  STM32MP_DDR3,
  STM32MP_DDR4,
  STM32MP_LPDDR4,
}ddr_type;

/**
  * @brief  HAL DDR Self Refresh modes definition  
  */
typedef enum
{
  HAL_DDR_SW_SELF_REFRESH_MODE = 0x0U,   /*!< DDR Software Self Refresh Mode */
  HAL_DDR_AUTO_SELF_REFRESH_MODE = 0x1U, /*!< DDR Automatic Self Refresh Mode */
  HAL_DDR_HW_SELF_REFRESH_MODE = 0x2U,   /*!< DDR Hardware Self Refresh Mode */
  HAL_DDR_INVALID_MODE = 0x3U,           /*!< DDR Invalid Self Refresh Mode */
}HAL_DDR_SelfRefreshModeTypeDef;

/**
  * @brief  HAL DDR settings definition
  */
typedef struct {
  const char *name;
  uint32_t speed; /* in kHZ */
  unsigned long size; /* Memory size in byte = col * row * width */
}HAL_DDR_InfoTypeDef;

typedef struct {
  uint32_t MSTR;
  uint32_t MRCTRL0;
  uint32_t MRCTRL1;
  uint32_t MRCTRL2;
  uint32_t DERATEEN;
  uint32_t DERATEINT;
  uint32_t DERATECTL;
  uint32_t PWRCTL;
  uint32_t PWRTMG;
  uint32_t HWLPCTL;
  uint32_t RFSHCTL0;
  uint32_t RFSHCTL1;
  uint32_t RFSHCTL3;
  uint32_t CRCPARCTL0;
  uint32_t CRCPARCTL1;
  uint32_t INIT0;
  uint32_t INIT1;
  uint32_t INIT2;
  uint32_t INIT3;
  uint32_t INIT4;
  uint32_t INIT5;
  uint32_t INIT6;
  uint32_t INIT7;
  uint32_t DIMMCTL;
  uint32_t RANKCTL;
#ifndef STM32MP25XX_SI_CUT1_X
  uint32_t RANKCTL1;
#endif /* !STM32MP25XX_SI_CUT1_X */
  uint32_t ZQCTL0;
  uint32_t ZQCTL1;
  uint32_t ZQCTL2;
  uint32_t DFITMG0;
  uint32_t DFITMG1;
  uint32_t DFILPCFG0;
  uint32_t DFILPCFG1;
  uint32_t DFIUPD0;
  uint32_t DFIUPD1;
  uint32_t DFIUPD2;
  uint32_t DFIMISC;
  uint32_t DFITMG2;
  uint32_t DFITMG3;
  uint32_t DBICTL;
  uint32_t DFIPHYMSTR;
  uint32_t DBG0;
  uint32_t DBG1;
  uint32_t DBGCMD;
  uint32_t SWCTL;
#ifndef STM32MP25XX_SI_CUT1_X
  uint32_t SWCTLSTATIC;
#endif /* !STM32MP25XX_SI_CUT1_X */
  uint32_t POISONCFG;
  uint32_t PCCFG;
}HAL_DDR_RegTypeDef;

typedef struct {
  uint32_t RFSHTMG;
  uint32_t RFSHTMG1;
  uint32_t DRAMTMG0;
  uint32_t DRAMTMG1;
  uint32_t DRAMTMG2;
  uint32_t DRAMTMG3;
  uint32_t DRAMTMG4;
  uint32_t DRAMTMG5;
  uint32_t DRAMTMG6;
  uint32_t DRAMTMG7;
  uint32_t DRAMTMG8;
  uint32_t DRAMTMG9;
  uint32_t DRAMTMG10;
  uint32_t DRAMTMG11;
  uint32_t DRAMTMG12;
  uint32_t DRAMTMG13;
  uint32_t DRAMTMG14;
  uint32_t DRAMTMG15;
  uint32_t ODTCFG;
  uint32_t ODTMAP;
}HAL_DDR_TimingTypeDef;

typedef struct {
  uint32_t ADDRMAP0;
  uint32_t ADDRMAP1;
  uint32_t ADDRMAP2;
  uint32_t ADDRMAP3;
  uint32_t ADDRMAP4;
  uint32_t ADDRMAP5;
  uint32_t ADDRMAP6;
  uint32_t ADDRMAP7;
  uint32_t ADDRMAP8;
  uint32_t ADDRMAP9;
  uint32_t ADDRMAP10;
  uint32_t ADDRMAP11;
}HAL_DDR_MapTypeDef;

typedef struct {
  uint32_t SCHED;
  uint32_t SCHED1;
  uint32_t PERFHPR1;
  uint32_t PERFLPR1;
  uint32_t PERFWR1;
#ifndef STM32MP25XX_SI_CUT1_X
  uint32_t SCHED3;
  uint32_t SCHED4;
#endif /* !STM32MP25XX_SI_CUT1_X */
  uint32_t PCFGR_0;
  uint32_t PCFGW_0;
  uint32_t PCTRL_0;
  uint32_t PCFGQOS0_0;
  uint32_t PCFGQOS1_0;
  uint32_t PCFGWQOS0_0;
  uint32_t PCFGWQOS1_0;
#if STM32MP_DDR_DUAL_AXI_PORT
  uint32_t PCFGR_1;
  uint32_t PCFGW_1;
  uint32_t PCTRL_1;
  uint32_t PCFGQOS0_1;
  uint32_t PCFGQOS1_1;
  uint32_t PCFGWQOS0_1;
  uint32_t PCFGWQOS1_1;
#endif
}HAL_DDR_PerfTypeDef;

typedef struct {
  int dramtype;
  int dimmtype;
  int lp4xmode;
  int numdbyte;
  int numactivedbytedfi0;
  int numactivedbytedfi1;
  int numanib;
  int numrank_dfi0;
  int numrank_dfi1;
  int dramdatawidth;
  int numpstates;
  int frequency[HAL_DDR_MAX_PSTATE];
  int pllbypass[HAL_DDR_MAX_PSTATE];
  int dfifreqratio[HAL_DDR_MAX_PSTATE];
  int dfi1exists;
  int train2d;
  int hardmacrover;
  int readdbienable[HAL_DDR_MAX_PSTATE];
  int dfimode;
}HAL_DDR_BasicUiDef;

typedef struct {
  int lp4rxpreamblemode[HAL_DDR_MAX_PSTATE];
  int lp4postambleext[HAL_DDR_MAX_PSTATE];
  int d4rxpreamblelength[HAL_DDR_MAX_PSTATE];
  int d4txpreamblelength[HAL_DDR_MAX_PSTATE];
  int extcalresval;
  int is2ttiming[HAL_DDR_MAX_PSTATE];
  int odtimpedance[HAL_DDR_MAX_PSTATE];
  int tximpedance[HAL_DDR_MAX_PSTATE];
  int atximpedance;
  int memalerten;
  int memalertpuimp;
  int memalertvreflevel;
  int memalertsyncbypass;
  int disdynadrtri[HAL_DDR_MAX_PSTATE];
  int phymstrtraininterval[HAL_DDR_MAX_PSTATE];
  int phymstrmaxreqtoack[HAL_DDR_MAX_PSTATE];
  int wdqsext;
  int calinterval;
  int calonce;
  int lp4rl[HAL_DDR_MAX_PSTATE];
  int lp4wl[HAL_DDR_MAX_PSTATE];
  int lp4wls[HAL_DDR_MAX_PSTATE];
  int lp4dbird[HAL_DDR_MAX_PSTATE];
  int lp4dbiwr[HAL_DDR_MAX_PSTATE];
  int lp4nwr[HAL_DDR_MAX_PSTATE];
  int lp4lowpowerdrv;
  int drambyteswap;
  int rxenbackoff;
  int trainsequencectrl;
  int snpsumctlopt;
  int snpsumctlf0rc5x[HAL_DDR_MAX_PSTATE];
  int txslewrisedq[HAL_DDR_MAX_PSTATE];
  int txslewfalldq[HAL_DDR_MAX_PSTATE];
  int txslewriseac;
  int txslewfallac;
  int disableretraining;
  int disablephyupdate;
  int enablehighclkskewfix;
  int disableunusedaddrlns;
  int phyinitsequencenum;
  int enabledficspolarityfix;
  int phyvref;
  int sequencectrl[HAL_DDR_MAX_PSTATE];
}HAL_DDR_AdvancedUiDef;

typedef struct {
  int mr0[HAL_DDR_MAX_PSTATE];
  int mr1[HAL_DDR_MAX_PSTATE];
  int mr2[HAL_DDR_MAX_PSTATE];
  int mr3[HAL_DDR_MAX_PSTATE];
  int mr4[HAL_DDR_MAX_PSTATE];
  int mr5[HAL_DDR_MAX_PSTATE];
  int mr6[HAL_DDR_MAX_PSTATE];
  int mr11[HAL_DDR_MAX_PSTATE];
  int mr12[HAL_DDR_MAX_PSTATE];
  int mr13[HAL_DDR_MAX_PSTATE];
  int mr14[HAL_DDR_MAX_PSTATE];
  int mr22[HAL_DDR_MAX_PSTATE];
}HAL_DDR_ModeRegisterUiDef;

typedef struct {
  int swizzle[HAL_DDR_MAX_SWIZZLE_PARAM];
}HAL_DDR_SwizzleUiDef;

typedef struct  {
  HAL_DDR_InfoTypeDef       info;
  HAL_DDR_RegTypeDef        c_reg;
  HAL_DDR_TimingTypeDef     c_timing;
  HAL_DDR_MapTypeDef        c_map;
  HAL_DDR_PerfTypeDef       c_perf;
  HAL_DDR_BasicUiDef        p_uib;
  HAL_DDR_AdvancedUiDef     p_uia;
  HAL_DDR_ModeRegisterUiDef p_uim;
  HAL_DDR_SwizzleUiDef      p_uis;
}HAL_DDR_ConfigTypeDef;

/**
  * @brief  DDR Initialization Structure definition
  */
typedef struct
{
  bool wakeup_from_standby; /*!< [input]
                                 Specifies if the system is waking up from the
                                 standby mode. The application is in charge to
                                 get this information. It will impact the self
                                 refresh state and the related steps within
                                 the initialization sequence. */

  bool self_refresh;        /*!< [output]
                                 Specifies the DDR self refresh status.
                                 Self Refresh enabled if true. */

  uint32_t zdata;           /*!< [input]
                                 Specifies the ZQ calibration restored value
                                 if any. Only used by the initialization
                                 sequence if wakeup_from_standby is true. The
                                 application is in charge of saving/restoring
                                 it during low power transitions. Value is
                                 obtaines when calling HAL_DDR_SR_Entry. */

  bool clear_bkp;           /*!< [output]
                                 Specifies if backup should be cleared after
                                 DDR initialization (DDR lost content case).
                                 Clear requested if true. */
} DDR_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DDR_Exported_Constants DDR Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup DDR_Exported_Macros DDR Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DDR_Exported_Functions
  * @{
  */

HAL_StatusTypeDef HAL_DDR_Init(DDR_InitTypeDef *iddr);
HAL_StatusTypeDef HAL_DDR_SR_Entry(uint32_t *zq0cr0_zdata);
HAL_StatusTypeDef HAL_DDR_STDBY_SR_Entry(void);
HAL_StatusTypeDef HAL_DDR_SR_Exit(void);
HAL_StatusTypeDef HAL_DDR_SR_SetMode(HAL_DDR_SelfRefreshModeTypeDef mode);
HAL_DDR_SelfRefreshModeTypeDef HAL_DDR_SR_ReadMode(void);
HAL_StatusTypeDef HAL_DDR_SetRetentionAreaBase(unsigned long base);

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup DDR_Private_Types DDR Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup DDR_Private_Variables DDR Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup DDR_Private_Constants DDR Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DDR_Private_Macros DDR Private Macros
  * @{
  */

/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup DDR_Private_Functions DDR Private Functions
  * @{
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

#endif /* DDRC & DDRPHYC */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xxHAL_DDR_H */
