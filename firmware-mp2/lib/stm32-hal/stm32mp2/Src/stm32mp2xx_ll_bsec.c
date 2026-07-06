/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_bsec.c
  * @author  MCD Application Team
  * @brief   PKA LL module driver.
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

#if defined (USE_HAL_DRIVER)
#undef USE_HAL_DRIVER
#endif

#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_ll_bsec.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined (BSEC)

/** @addtogroup BSEC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define NULL ((char*)0)

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup BSEC_LL_Exported_Functions BSEC Exported Functions
  * @{
  */

/**
  * @}
  */

/**
  * @brief  Return information whether OTP word 'otpWordNb' is currently sticky locked.
  *         with the single lock type in parameter 'lockTypeToTest'.
  *         This is readable by a read of register bit BSEC_S*LOCKx[y]. (* = P, W, R) where :
  *         otpWordNb = 32. x + y
  *         x = otpWordNb div 32
  *         y = otpWordNb mod 32
  *
  * @param  BSECx          : pointer on BSEC HW instance
  * @param  otpWordNb      : OTP word number from which we want to know if is sticky locked with 'lockTypeToTest'.
  * @param  lockTypeToTest : Type of sticky lock to test (one at a time of course not combination here).
  *
  * @retval : 1 if OTP 'otpWordNb' is currently sticky locked with the lock type from 'lockTypeToTest' parameter.
  *           0 otherwise (ie not locked with that lock type at least).
  */
uint32_t LL_BSEC_Is_StickyLocked(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t lockTypeToTest)
{
  uint32_t x;
  uint32_t y;
  uint32_t * pSLockReg; /* pointer to BSEC_S*LOCKx register */
  uint32_t retVal = 0;

  /** Get x, y from otpWordNb : ie Reg Index is 'x' and register bit position in that register is 'y' */
  x = otpWordNb / 32;
  y = otpWordNb % 32;

  /* Compute lock type Address Offset depending on 'lockTypeToTest' */
  switch(lockTypeToTest)
  {
  case LL_BSEC_STICKY_PROG_LOCKED :
    pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SPLOCK0) + (x * 4));
    retVal = ((*pSLockReg & (1 << y)) >> y);
    break;

  case LL_BSEC_STICKY_WRITE_LOCKED :
    pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SWLOCK0) + (x * 4));
    retVal = ((*pSLockReg & (1 << y)) >> y);
    break;

  case LL_BSEC_STICKY_READ_LOCKED :
    pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SRLOCK0) + (x * 4));
    retVal = ((*pSLockReg & (1 << y)) >> y);
    break;

  default :
    break;
  } /* of switch(lockTypeToTest) */

  return(retVal);
}

/**
  * @brief  Function used to handle single or multiple sticky locks requests on the same
  *         OTP word 'otpWordNb'. The lock type or combination of lock types are in parameter 'lockType'.
  *         Each operation is done by a write of register bit BSEC_S*LOCKx[y]. (* = P, W, R) where :
  *         otpWordNb = 32. x + y
  *         where : x = otpWordNb div 32 ('x' is index of register to apply the lock type 'P', 'W', 'R')
  *         and     y = otpWordNb mod 32 ('y' is concerned bit in register 'x')
  *
  * @param  BSECx          : pointer on BSEC HW instance
  * @param  otpWordNb      : OTP word number from which we want to know if is sticky locked with 'lockTypeToTest'.
  * @param  lockType       : Type of sticky locks to set.
  *
  * @retval : None.
  */
void LL_BSEC_Set_StickyLock(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t lockType)
{
    uint32_t x;
    uint32_t y;
    uint32_t * pSLockReg; /* pointer to BSEC_S*LOCKx register */

    /* Get x, y from otpWordNb : ie Reg Index 'x' and register bit position in that register 'y' */
    x = otpWordNb / 32;
    y = otpWordNb % 32;

    /* Compute lock type Address Offset depending on 'lockType' */
    if((lockType & LL_BSEC_STICKY_PROG_LOCKED) != 0)
    {
      pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SPLOCK0) + (x * 4));
      *pSLockReg |= (1 << y);
    }

    if((lockType & LL_BSEC_STICKY_WRITE_LOCKED) != 0)
    {
      pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SWLOCK0) + (x * 4));
      *pSLockReg |= (1 << y);
    }

    if((lockType & LL_BSEC_STICKY_READ_LOCKED) != 0)
    {
      pSLockReg = (uint32_t*)((uint32_t)&(BSECx->SRLOCK0) + (x * 4));
      *pSLockReg |= (1 << y);
    }
}



/**
  * @brief  Low level function to be used for OTP fuse (ie programming) or OTP Reload (ie OTP Read)
  *         operations.
  *
  * @ Note1 : WARNING : for an OTP fuse operation, the SAFMEM and Kilopass XPM memory should be prealably
  *          powered up, and this is a preliminary before calling the current function.
  *          Also sticky program lock, availability of OTP upper if 'otpWordNb' is in upper area have to
  *          be checked externally before.
  *
  * @ Note2 : WARNING : For an OTP fuse operation the value to be fused should be programmed before in
  *          'BSEC_WDR' register by a previous call to 'LL_BSEC_Set_WordValToFuse(BSEC_BASE, fuseValue)'.
  *
  * @param  BSECx      : pointer on BSEC HW instance
  * @param  otpWordNb  : OTP word number from which we want to know if is shadowed or not.
  * @param  prog       : indicate the operation : 0 is for OTP Reload, 1 is for OTP fuse operation.
  * @param  lock       : ONLY Valid for OTP fuse operation, lock != 0 allows to permanently
  *                      program lock the word after its fusing.
  *
  * @retval : None
  */
void LL_BSEC_Set_OtpCtrl(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t prog, uint32_t lock)
{
  uint32_t regVal = 0;

  if(prog == 0)
   {
     /* we are in OTP Reload (ie OTP Read operation)              */
     /* force lock to 0 for read operation as this is a non sense */
     lock = 0;
   }

   regVal |= ((lock & 0x1) << BSEC_OTPCR_PPLOCK_Pos)  | \
             ((prog & 0x1) << BSEC_OTPCR_PROG_Pos)    | \
             ((otpWordNb & BSEC_OTPCR_ADDR_Msk) << BSEC_OTPCR_ADDR_Pos);

   WRITE_REG(BSEC->OTPCR,regVal);
}



/**
  * @brief  Return information whether the ROM un-mappable part if actually mapped or not : hence
  *         if the ROM is fully mapped or only partially (ie un-mappable part unmapped).
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value : LL_BSEC_ROM_FULLY_MAPPED if all ROM is mapped : ie the ROM un-mappable part is mapped.
  *           value : LL_BSEC_ROM_PARTIAL_UNMAPPED0 when a part of ROM (the un-mappable part) is unmapped, then ROM is only
  *                   partially mapped.
  *           value : LL_BSEC_ROM_UNMAP_INVALID if ROM Unmap feature seems to have been hacked.
  */
uint32_t LL_BSEC_Is_Rom_FullyMapped(BSEC_TypeDef * BSECx)
{
  uint32_t fieldVal = READ_REG(BSEC->UNMAPR);

  if(fieldVal == LL_BSEC_ROM_IS_FULLY_MAPPED_MAGIC)
  {
    return(LL_BSEC_ROM_FULLY_MAPPED);
  }
  else if(fieldVal == LL_BSEC_ROM_IS_PARTIALLY_UNMAPPED)
  {
    return(LL_BSEC_ROM_PARTIAL_UNMAPPED);
  }
  else
  {
    return(LL_BSEC_ROM_UNMAP_INVALID);
  }
  return 0; // never occurs
}



/**
  * @brief  Return information whether a shadowed OTP word 'otpWordNb' have successfully been reloaded to shadow
  *         following a either a BSEC boot (ie : auto-reload shadow from scratch or warm reset) or by the last manual reload
  *         operation triggered by user.
  *
  * @ Note  WARNING : This function gives ONLY validity status for 'otpWordNb' that are Shadowed in SoC !!.
  *                   Before using this function make first a call to LL_BSEC_Is_Shadowed(BSEC_BASE, otpWordNb) to
  *                   know if 'otpWordNb' is effectively shadowed in SoC.
  *
  *         This is readable by a read of register bit BSEC_OTPVLDRx[y] where :
  *         otpWordNb = 32. x + y
  *         x = otpWordNb div 32
  *         y = otpWordNb mod 32
  *
  * @param  BSECx      : pointer on BSEC HW instance
  * @param  otpWordNb  : OTP word number (Shadowed in SoC) from which we want to know if the last
  *                      auto-reload (from BSEC boot) or manual reload by user trigger fuse Read operation lead
  *                      to valid contents in related BSEC shadow register.
  *
  * @retval : 1 if OTP 'otpWordNb' was effectively correctly updated in respective shadow register
  *           0 if OTP word 'otpWordNb' value updated in respective shadow register is known to be erroneous.
  */
uint32_t LL_BSEC_Is_ShadowedOtpReloadedInShadowValid(BSEC_TypeDef * BSECx, uint32_t otpWordNb)
{
  uint32_t x;
  uint32_t y;
  uint32_t * pOtpValidLoadReg; /* pointer to BSEC_OTPVLDRx register */

  /* Get x, y from otpWordNb : ie : register Index 'x' and register bit position in that register 'y' */
  x = otpWordNb / 32;
  y = otpWordNb % 32;

  pOtpValidLoadReg = (uint32_t*)((uint32_t)&(BSECx->OTPVLDR0)+ (x * 4));
  return(((*pOtpValidLoadReg & (1 << y)) >> y));
}

/**
  * @brief  Return information whether OTP word 'otpWordNb' is shadowed or not in SoC
  *
  * @ Note  This information is defined by netlist ties and is SoC dependent.
  *
  *         This is readable by a read of register bit BSEC_SFSRx[y] where :
  *         otpWordNb = 32. x + y
  *         x = otpWordNb div 32
  *         y = otpWordNb mod 32
  *
  * @param  BSECx          : pointer on BSEC HW instance
  * @param  otpWordNb      : OTP word number from which we want to know if is shadowed or not.
  *
  * @retval : 1 if OTP 'otpWordNb' is effectively shadowed in SoC
  *           0 if OTP word 'otpWordNb' is not shadowed in SoC.
  */
uint32_t LL_BSEC_Is_Shadowed(BSEC_TypeDef * BSECx, uint32_t otpWordNb)
{
  uint32_t x;
  uint32_t y;
  uint32_t * pBsecSfsrReg; /* pointer to 'BSEC_SFSRx' register */

  /* Get x, y from otpWordNb : ie Reg Index 'x' and register bit position in that register 'y' */
  x = otpWordNb / 32;
  y = otpWordNb % 32;

  pBsecSfsrReg = (uint32_t*)((uint32_t)&(BSECx->SFSR0) + (x * 4));
  return(((*pBsecSfsrReg & (1 << y)) >> y));
}

/*
  * @brief  Low level function to get BSEC_SCRATCHRx register (x=0..3) contents.
  *         The content of those registers is preserved during a warm reset ('rst_n')
  *         and hot reset ('hot_rst_n'), but not on a 'scratch_rst_n' (cold reset = rst_por).
  *
  * @param[in]  BSECx          : pointer on BSEC HW instance
  * @param[in]  scratchWordNb  : scratch word number (0..3) is the valid range.
  *
  * @retval : Contents of register 'BSEC_SCRATCHRx', with x = 'scratchWordNb'.
  */
uint32_t LL_BSEC_Get_WarmResetPersistScratch(BSEC_TypeDef * BSECx, uint32_t scratchWordNb)
{
  uint32_t * pBsecScratchReg; /* pointer to 'BSEC_SCRATCHRx' register */
  uint32_t retVal = 0;

  if(scratchWordNb < LL_BSEC_NB_WARM_RESET_SCRATCH_REG)
  {
    pBsecScratchReg = (uint32_t*)((uint32_t)&BSECx->SCRATCHR0 + (scratchWordNb * 4));
    retVal = *pBsecScratchReg;
  }

  return(retVal);
}

/**
  * @brief  Low level function to Write BSEC_SCRATCHRx register word x = 'scratchWordNb'
  *         with contents from second parameter 'value'.
  *         The content of those registers is preserved during a warm reset ('rst_n')
  *         and hot reset ('hot_rst_n'), but not on a 'scratch_rst_n' (cold reset = rst_por).
  *
  * @param[in]  BSECx          : pointer on BSEC HW instance
  * @param[in]  scratchWordNb  : scratch word number : (0..3) is the valid range.
  * @param[in]  value          : 32 bits value to write to scratch register number x (x=0..3).
  *
  * @retval : None.
  */
void LL_BSEC_Write_WarmResetPersistScratchWord(BSEC_TypeDef * BSECx, uint32_t scratchWordNb, uint32_t value)
{
  uint32_t * pBsecScratchReg; /* pointer to 'BSEC_SCRATCHRx' register */

  if(scratchWordNb < LL_BSEC_NB_WARM_RESET_SCRATCH_REG)
  {
    pBsecScratchReg = (uint32_t*)((uint32_t)&BSECx->SCRATCHR0 + (scratchWordNb * 4));
    *pBsecScratchReg = value;
  }
}

/**
  * @brief  Low level function to get BSEC_WOSCRx register (x=0..7) contents.
  *         The content of those registers is preserved during a hot reset only ('hot_rst_n'),
  *         but not on a warm reset 'rst_n' neither on a 'scratch_rst_n' (cold reset = rst_por).
  *
  * @param[in]  BSECx          : pointer on BSEC HW instance
  * @param[in]  scratchWordNb  : scratch word number (0..7) is the valid range.
  *
  * @retval : Contents of register 'BSEC_WOSCRx', with x = 'scratchWordNb'.
  */
uint32_t LL_BSEC_Get_HotResetPersistScratch(BSEC_TypeDef * BSECx, uint32_t scratchWordNb)
{
  uint32_t * pBsecScratchReg; /* pointer to 'BSEC_WOSCRx' register */
  uint32_t retVal = 0;

  if(scratchWordNb < LL_BSEC_NB_HOT_RESET_SCRATCH_REG)
  {
    pBsecScratchReg = (uint32_t*)((uint32_t)&BSECx->WOSCR0 + (scratchWordNb * 4));
    retVal = *pBsecScratchReg;
  }

  return(retVal);
}

/**
  * @brief  Low level function to Write BSEC_WOSCRx register word x = 'scratchWordNb'
  *         with contents from second parameter 'value'.
  *         The content of those registers is preserved during a hot reset ('hot_rst_n')
  *         but not on a warm reset 'rst_n', neither on a 'scratch_rst_n' (cold reset = rst_por).
  *
  * @param[in]  BSECx          : pointer on BSEC HW instance
  * @param[in]  scratchWordNb  : scratch word number : (0..7) is the valid range.
  * @param[in]  value          : 32 bits value to write to scratch register number x (x=0..7).
  *
  * @retval : None.
  */
void LL_BSEC_Write_HotResetPersistScratchWord(BSEC_TypeDef * BSECx, uint32_t scratchWordNb, uint32_t value)
{
  uint32_t * pBsecScratchReg; /* pointer to 'BSEC_WOSCRx' register */

  if(scratchWordNb < LL_BSEC_NB_HOT_RESET_SCRATCH_REG)
  {
    pBsecScratchReg = (uint32_t*)((uint32_t)&BSECx->WOSCR0 + (scratchWordNb * 4));
    *pBsecScratchReg = value;
  }
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (BSEC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


