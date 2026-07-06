/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_bsec.h
  * @author  MCD Application Team
  * @brief   Header file of BSEC LL module.
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
#ifndef STM32MP2xx_LL_BSEC_H
#define STM32MP2xx_LL_BSEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"
#include "stm32mp2xx_ll_bsec.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(BSEC)

/** @defgroup BSEC_LL BSEC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


#define LL_BSEC_OTP_NB_WORDS                (uint32_t)(384)
#define LL_BSEC_OTP_WORD_INDEX_MAX          (uint32_t)(LL_BSEC_OTP_NB_WORDS-1)

#define LL_BSEC_OTP_LOWER_FIRST_WORD_INDEX  (uint32_t)(0)
#define LL_BSEC_OTP_LOWER_LAST_WORD_INDEX   (uint32_t)(127)

#define LL_BSEC_OTP_MIDDLE_FIRST_WORD_INDEX (uint32_t)(128)
#define LL_BSEC_OTP_MIDDLE_LAST_WORD_INDEX  (uint32_t)(255)

#define LL_BSEC_OTP_UPPER_FIRST_WORD_INDEX  (uint32_t)(256)
#define LL_BSEC_OTP_UPPER_LAST_WORD_INDEX   LL_BSEC_OTP_WORD_INDEX_MAX

#define LL_BSEC_SR_NVSTATE_B_0x16           0x16 /* 6b010110' */
#define LL_BSEC_SR_NVSTATE_B_0xD            0x0D /* 6b001101' */

/* Possible valid values of 'BSEC_SR.STATE' field */
#define LL_BSEC_SECURITY_STATE_OPEN        LL_BSEC_SR_NVSTATE_B_0x16 /* 0x16 = 6b010110' */
#define LL_BSEC_SECURITY_STATE_CLOSED      LL_BSEC_SR_NVSTATE_B_0xD  /* 0x0D = 6b001101' */

/* Possible sticky 'lock type' in BSEC : value have to be possibly combined in a mask */
#define LL_BSEC_STICKY_NOT_LOCKED          (0)
#define LL_BSEC_STICKY_PROG_LOCKED         (1 << 0)
#define LL_BSEC_STICKY_WRITE_LOCKED        (1 << 1)
#define LL_BSEC_STICKY_READ_LOCKED         (1 << 2)

/* Magic number value of register 'BSEC_UNMAPR' that says all ROM is currently mapped */
#define LL_BSEC_ROM_IS_FULLY_MAPPED_MAGIC  0xA1C0DE0D
#define LL_BSEC_ROM_IS_PARTIALLY_UNMAPPED  0xFFFFFFFF

/* Possible values returned by function 'LL_BSEC_Is_Rom_FullyMapped()' */
#define LL_BSEC_ROM_FULLY_MAPPED            1
#define LL_BSEC_ROM_PARTIAL_UNMAPPED        2
#define LL_BSEC_ROM_UNMAP_INVALID           3

/* Check word : OTP_HW_WORD0 reference value to be programmed in EWS when */
/* switching from virgin -> non virgin                                    */
#define LL_BSEC_CHECK_WORD_REF_VALUE        0xAAAA5555

/* Mask of field 'OTP_HW_WORD4.tk_retries' */
#define LL_BSEC_TK_RETRIES_MASK             0x0000FFFF
#define LL_BSEC_TK_RETRIES_BYTE3_MASK       0x0000F000
#define LL_BSEC_TK_RETRIES_START_BIT_POS    0

/* possible values of parameter 'prog' of function LL_BSEC_Set_OtpCtrl() */
#define LL_BSEC_OTPCR_PROG_BIT_IS_READ_REQ      0
#define LL_BSEC_OTPCR_PROG_BIT_IS_PROGRAM_REQ   1

/* possible values of parameter 'lock' of function LL_BSEC_Set_OtpCtrl() */
#define LL_BSEC_OTPCR_LOCK_BIT_IS_NOLOCK_REQ    0
#define LL_BSEC_OTPCR_LOCK_BIT_IS_LOCK_REQ      1

#define LL_BSEC_DENR_Pos         (0U)
#define LL_BSEC_DENR_Msk         (0x0000FFFF)


/*
 * Feature disabling word OTP_FEATURE_DISABLING bit definitions
 */

#define LL_BSEC_FEATURE_DISABLING_WORD_NB                   9

#define LL_BSEC_FEATURE_DISABLED_DUAL_CA35                  (1<<0)
#define LL_BSEC_FEATURE_DISABLED_CM0_PLUS                   (1<<1)
#define LL_BSEC_FEATURE_DISABLED_GPU                        (1<<2)
#define LL_BSEC_FEATURE_DISABLED_DSI                        (1<<3)
#define LL_BSEC_FEATURE_DISABLED_CSI                        (1<<4)
#define LL_BSEC_FEATURE_DISABLED_DUAL_ETH_GMAC              (1<<5)
#define LL_BSEC_FEATURE_DISABLED_FDCAN                      (1<<6)
#define LL_BSEC_FEATURE_DISABLED_USB3                       (1<<7)
#define LL_BSEC_FEATURE_DISABLED_PCIE                       (1<<8)
#define LL_BSEC_FEATURE_DISABLED_CRYPTO_CRYP_SAES_PKA_FULL  (1<<9)
#define LL_BSEC_FEATURE_DISABLED_DDRCRYP                    (1<<10)
#define LL_BSEC_FEATURE_DISABLED_OTFDEC                     (1<<11)
#define LL_BSEC_FEATURE_DISABLED_LVDS                       (1<<12)
#define LL_BSEC_FEATURE_DISABLED_RNG                        (1<<13)
#define LL_BSEC_FEATURE_DISABLED_RESERVED_FUTURE1           (1<<14) /* reserved for future use 1 */
#define LL_BSEC_FEATURE_DISABLED_RESERVED_FUTURE2           (1<<15) /* reserved for future use 2 */
#define LL_BSEC_FEATURE_DISABLED_GPU_NN_EXTENSION           (1<<16)
#define LL_BSEC_FEATURE_DISABLED_VDEC_VENC                  (1<<17)
#define LL_BSEC_FEATURE_DISABLED_CA35_AARCH64_BOOT          (1<<18)
#define LL_BSEC_FEATURE_DISABLED_ETHSW                      (1<<19) /* TSN switch */

/* Number of feature disable bits effectively used */
#define LL_BSEC_FEATURE_DISABLED_NB_BITS_USED             20

/* 'ECIES_CHIP_PRIVK_ENC' is on 256 bits = 8 words like 'ECIES_CHIP_PRIVK' */
#define LL_BSEC_NB_ENC_ECIES_WORDS                          8

/* 'HWKEY' is on 256 bits = 8 words  */
#define LL_BSEC_NB_HWKEY_WORDS                              8

/* 4 warm reset resistant scratch words BSEC_SCRATCHR0..3 in SoC */
#define LL_BSEC_NB_WARM_RESET_SCRATCH_REG                   4

/* 8 hot reset resistant scratch words BSEC_WOSCR0..7 in SoC */
#define LL_BSEC_NB_HOT_RESET_SCRATCH_REG                    8

/** Debug Profiles low level definition and BSEC_DENR related : Debug Enable / Disable **/

/* Key used to protect against un-intentional write to register :                                       */
/* to be written in upper 16 bits of register to be able to write value of signals in the 16 bits lower */
#define LL_BSEC_DENR_WRITE_KEY                              0xDEB60000

/* -- Cortex-M related */

/* Debug Cortex-M Non Secure Trace Only */
#define LL_BSEC_DBG_CM_NS_TRACEONLY     (BSEC_DENR_NIDENM  | \
                                         BSEC_DENR_DBGSWEN | \
                                         BSEC_DENR_HDPEN   | \
                                         BSEC_DENR_DEVICEEN)

/* Debug Cortex-M Non Secure Full Debug */
#define LL_BSEC_DBG_CM_NS_FULLDBG       (LL_BSEC_DBG_CM_NS_TRACEONLY  | \
                                         BSEC_DENR_DBGENM)

/* Debug Cortex-M Secure Trace Only */
#define LL_BSEC_DBG_CM_S_TRACEONLY      (LL_BSEC_DBG_CM_NS_TRACEONLY  | \
                                         BSEC_DENR_SPNIDENM)

/* Debug Cortex-M Secure Full Debug */
#define LL_BSEC_DBG_CM_S_FULLDBG      (LL_BSEC_DBG_CM_NS_FULLDBG  | \
                                       BSEC_DENR_SPIDENM          | \
                                       BSEC_DENR_SPNIDENM)

/* All Cortex-M signals : useful to suppress all debug by negation of this mask */
#define LL_BSEC_DBG_CM_ALL_SIGNALS    LL_BSEC_DBG_CM_S_FULLDBG

/* -- Cortex-A related */

/* Debug Cortex-A Non Secure Trace Only */
#define LL_BSEC_DBG_CA_NS_TRACEONLY     (BSEC_DENR_NIDENA  | \
                                         BSEC_DENR_DBGSWEN | \
                                         BSEC_DENR_HDPEN   | \
                                         BSEC_DENR_DEVICEEN)

/* Debug Cortex-A Non Secure Full Debug */
#define LL_BSEC_DBG_CA_NS_FULLDBG       (LL_BSEC_DBG_CA_NS_TRACEONLY  | \
                                         BSEC_DENR_DBGENA)

/* Debug Cortex-A Secure Trace Only */
#define LL_BSEC_DBG_CA_S_TRACEONLY      (LL_BSEC_DBG_CA_NS_TRACEONLY  | \
                                         BSEC_DENR_SPNIDENA)

/* Debug Cortex-A Secure Full Debug */
#define LL_BSEC_DBG_CA_S_FULLDBG      (LL_BSEC_DBG_CA_NS_FULLDBG  | \
                                       BSEC_DENR_SPIDENA          | \
                                       BSEC_DENR_SPNIDENA)

/* All Cortex-A signals : useful to suppress all debug by negation of this mask */
#define LL_BSEC_DBG_CA_ALL_SIGNALS    LL_BSEC_DBG_CA_S_FULLDBG

/* Global Debug Cortex-A + Cortex-M in Secure with Trace Only */
#define LL_BSEC_DBG_GLOBAL_S_TRACEONLY (LL_BSEC_DBG_CA_S_TRACEONLY | \
                                        LL_BSEC_DBG_CM_S_TRACEONLY)

/* Global Debug Cortex-A + Cortex-M in Secure and Full Debug */
#define LL_BSEC_DBG_GLOBAL_S_FULLDBG  (LL_BSEC_DBG_CA_S_FULLDBG | \
                                       LL_BSEC_DBG_CM_S_FULLDBG)

/* Global Debug Cortex-A + Cortex-M in Non Secure with Trace Only */
#define LL_BSEC_DBG_GLOBAL_NS_TRACEONLY (LL_BSEC_DBG_CA_NS_TRACEONLY | \
                                         LL_BSEC_DBG_CM_NS_TRACEONLY)

/* Global Debug Cortex-A + Cortex-M in Non Secure with Full Debug */
#define LL_BSEC_DBG_GLOBAL_NS_FULLDBG   (LL_BSEC_DBG_CA_NS_FULLDBG | \
                                         LL_BSEC_DBG_CM_NS_FULLDBG)

/* Global Debug Cortex-A Non Secure + Cortex-M Secure with Trace Only */
#define LL_BSEC_DBG_GLOBAL_CA_NS_CM_S_TRACEONLY  (LL_BSEC_DBG_CA_NS_TRACEONLY | \
                                                  LL_BSEC_DBG_CM_S_TRACEONLY)

/* Global Debug Cortex-A Non Secure + Cortex-M Secure with Full Debug */
#define LL_BSEC_DBG_GLOBAL_CA_NS_CM_S_FULLDBG  (LL_BSEC_DBG_CA_NS_FULLDBG | \
                                                LL_BSEC_DBG_CM_S_FULLDBG)


/* Exported macro ------------------------------------------------------------*/
/** @defgroup CRC_LL_Exported_Macros CRC Exported Macros
  * @{
  */

/** @defgroup CRC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_BSEC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, __VALUE__)

/**
  * @brief  Read a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_BSEC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @brief  Get BSEC Security State from 'BSEC_SR.NVSTATE' field
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value of field 'BSEC_SR.NVSTATE' shifted right to zero position.
  * To be compared with values of defines LL_BSEC_SECURITY_STATE_XXX.
  * Bits 31:26 NVSTATE[5:0]: Non-volatile state
  * 0x16: BSEC is in open state
  * 0x0D: BSEC is in closed state
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_SecurityState(BSEC_TypeDef * BSECx)
{
  return (uint32_t)(READ_BIT(BSECx->SR, BSEC_SR_NVSTATE)  >> BSEC_SR_NVSTATE_Pos);
}

/**
  * @brief  Get Hw Key Valid indication from 'BSEC_SR.HVALID' field
  *         Tells if the HW Key on chip is currently valid or not.
  *         When valid it can be used as a key choice from SAES block selection to use Hw Key.
  *
  *         Note : HW Key can never be read by any CPU via BSEC OTP shadows, neither
  *         OTP reload manual operation  : ie OTP_CFG376..383[31:0] : "OTP_HWKEY0..7"
  *         as this is trapped by Hw BSEC and will fail silently.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value of field 'BSEC_SR.HVALID' shifted right to zero position.
  * 0 : when Hw Key is not currently Valid
  * 1 : when Hw Key is currently valid : ie have been provisioned in EWS and successfully.
  */
__STATIC_INLINE uint32_t LL_BSEC_Is_HwKeyValid(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->SR, BSEC_SR_HVALID) == (BSEC_SR_HVALID)) ? 1UL : 0UL);
}

/**
  * @brief  Get BSEC OTP Status from 'BSEC_OTPSR' register
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value of full register 'BSEC_OTPSR' (32 bits).
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Read(BSEC_TypeDef * BSECx)
{
  return(READ_REG(BSECx->OTPSR));
}

/**
  * @brief  Get field 'BSEC_OTPSR.PPLMF'
  *         Indicate a mismatching Permanent Programming Lock error
  *         updated for 'otpWordIdx' during the most recent OTP 'otpWordIdx' reload action.
  *         Applicable only for 1-bit programmable fuses (lower fuses)
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'PPLMF' flag.
  * Value != 0 when there is a mismatching Permanent Programming Lock error
  *
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_MismatchingPermProgLock_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_PPLMF) == (BSEC_OTPSR_PPLMF)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.PPLF'
  *         Indicates whether the most recently read word is Permanently
  *         Programming locked.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'PPLF' flag.
  * Value != 0 when most recently read word is locked.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_PermProgLocked(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_PPLF) == (BSEC_OTPSR_PPLF)) ? 1UL : 0UL);
}
/**
  * @brief  Get field 'BSEC_OTPSR.SECF'
  *         Indicates whether there was a single-bit-error correction
  *         during BSEC boot (ie fuse analysis -> boot_done) or the most recent OTP reload action.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'SEC' flag.
  * Value != 0 when single-bit-error correction was detected.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_Sec_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_SECF) == (BSEC_OTPSR_SECF)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.DEDF'
  *         Indicates whether there was a double-error detected
  *         during BSEC boot (ie fuse analysis -> boot_done) or the most recent OTP reload action.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'DEDF' flag.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_Ded_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_DEDF) == (BSEC_OTPSR_DEDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.AMEF'
  *         Detect if reflected address != original address : Address Mismatch Error
  *         during BSEC boot (ie fuse analysis -> boot_done) or the most recent OTP reload action.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'AMEF' flag.
  * Value != 0 if reflected address != original address.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_AddressMismatch_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_DEDF) == (BSEC_OTPSR_DEDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.DISTURBF'
  *         Indicates a problem in the fuse bits readout
  *         during BSEC boot (ie fuse analysis -> boot_done) or the most recent OTP reload action.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'DISTURBF' flag.
  * Value != 0 if there was a problem in the fuse bits.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_Disturbed_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_DISTURBF) == (BSEC_OTPSR_DISTURBF)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.PROGFAIL'
  *         Indicates the most recent fuse-blowing procedure failed
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'PROGFAIL' flag.
  * Value != 0 when the most recent fuse-blowing procedure failed
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_ProgFail_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_PROGFAIL) == (BSEC_OTPSR_PROGFAIL)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.BUSY'
  *         Get BSEC Wrapper availability. When 'busy' flag is set, the BSECW is
  *         busy by an ongoing Hw operation. So CPU have to poll until the flag is reset
  *         to get access to the BSEC Hw.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : 1 when BSEC Wrapper is busy, 0 if BSEC Wrapper Hw is available.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_Busy(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_BUSY) == (BSEC_OTPSR_BUSY)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.HIDEUP'
  *         Get value of 'HIDEUP' : value != 0 when OTP upper (OTP256..383) are available
  *         value 0 when OTP upper (OTP256..383) are hidden (and kept in reset), this is the case
  *         in particular when BSEC security state is OPEN (where all debug is opened from reset).
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : 1 : when OTP Upper are inaccessible (because hidden and let in reset)
  *           0 : when OTP Upper are accessible to TZ secure CPU.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_HideUpper(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_HIDEUP) == (BSEC_OTPSR_HIDEUP)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.OTPSEC'
  *         stickily set whenever a single-error correction occurs during BSEC boot
  *
  * @Note : To be checked ONLY after a BSEC Boot. This flag is stickily set when it is set
  *         and is therefore not updated by an OTP reload operation.
  *         This is not a real error, as when flagged, the error have been auto corrected.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'OTPSEC' flag.
  * Value != 0 after a BSEC Boot shows there was a single-error correction during BSEC boot.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_OtpSec_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_OTPSEC) == (BSEC_OTPSR_OTPSEC)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.OTPERR'
  *         set whenever a problem occurs during BSEC boot
  *
  * @Note : To be checked ONLY after a BSEC Boot. This flag is stickily set when it is set
  *         and is therefore not updated by an OTP reload operation.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Value of 'OTPERR' flag.
  * Value != 0 after a BSEC Boot shows that a problem occurred during BSEC boot.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_OtpErr_Error(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_OTPERR) == (BSEC_OTPSR_OTPERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.OTPNVIR'
  *         Get sample life cycle state : is Check Word : OTP_HW_WORD0 programmed or Virgin ?
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval :
  * Value != 0 : when on current SoC sample, the Check Word have already been programmed.
  * Value == 0 : when current SoC sample have not yet passed the EWS Check Word programming step.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_NonVirgin(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_OTPNVIR) == (BSEC_OTPSR_OTPNVIR)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_OTPSR.FUSEOK'
  *         Get information whether the BSEC Boot was already done if returned value != 0
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval :
  * Value != 0 : BSEC boot already occurred.
  * Value == 0 : BSEC boot did not occurred yet.
  */
__STATIC_INLINE uint32_t LL_BSEC_OtpStatus_Is_FuseOk(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->OTPSR, BSEC_OTPSR_FUSEOK) == (BSEC_OTPSR_FUSEOK)) ? 1UL : 0UL);
}

/**
  * @brief  Get field 'BSEC_FVRn' : where n = 'otpWordNb' from second parameter.
  *
  * @Note1 : Of course this is applicable only if word 'otpWordNb' is shadowed in SoC by netlist ties
  *         which is readable by a read of register bit BSEC_SFSRx[y].
  *         otpWordNb = n = 32. x + y
  *         x = otpWordNb div 32
  *         y = otpWordNb mod 32
  *
  * @Note2 : For non shadowed words, this function have to be used to read OTP after an OTP reload operation.
  *
  * @Note 3 : WARNING : Write to BSEC Shadow register is forbidden (ie silently fails), when BSEC Security
  *           state is CLOSED. Of course neither of these checks is done in the current function and have
  *           to be verified externally before the call.
  *
  * @param  BSECx : pointer on BSEC HW instance
  * @param  otpWordNb : OTP word number from which the shadow have to be read.
  *
  * @retval : value read in BSEC_FVRn register.
  */
__STATIC_INLINE uint32_t LL_BSEC_Read_OtpShadow(BSEC_TypeDef * BSECx, uint32_t otpWordNb)
{
  return READ_REG(BSECx->FVRx[otpWordNb]);
}

/**
  * @brief  Write register 'BSEC_FVRn' : where n = 'otpWordNb' from second parameter, with
  *         value 'otpVal' from third parameter.
  *
  * @Note 1 : WARNING : Write to BSEC Shadow register is forbidden (ie silently fails), when BSEC Security
  *           state is CLOSED. Of course neither of these checks is done in the current function and have
  *           to be verified externally before the call.
  *
  * @param  BSECx : pointer on BSEC HW instance
  * @param  otpWordNb : OTP word number from which the shadow have to be read.
  * @param  otpVal    : value to be written in OTP word shadow register.
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Write_OtpShadow(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t otpVal)
{
  WRITE_REG(BSECx->FVRx[otpWordNb],otpVal);
}

/**
  * @brief  Function used to Get the Function lock mask from register 'BSEC_LOCKR'.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Return value of register 'BSEC_LOCKR'.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_FunctionStickyLock(BSEC_TypeDef * BSECx)
{
   return(READ_REG(BSECx->LOCKR));
}

/**
  * @brief  Function used to Write a Function lock mask in register 'BSEC_LOCKR'.
  *
  * @param  BSECx          : pointer on BSEC HW instance
  * @param  lockMaskValue  : lock mask value to write in register 'BSEC_LOCKR'
  *                          multiple locks can be combined by ORRing them in 'lockMaskValue'.
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Set_FunctionStickyLock(BSEC_TypeDef * BSECx, uint32_t lockMaskValue)
{
  WRITE_REG(BSECx->LOCKR,lockMaskValue);
}


/**
  * @brief  Low level function to be used for OTP fuse (ie programming) operation as a first step low level operation.
  *         The function write register BSEC_WDR with value to be fused. This should be done before programming
  *         the fuse operation itself by a call to 'LL_BSEC_Set_OtpCtrl(BSEC,otpWordNb,prog,lock)'.
  *
  * @ Note1 : WARNING : The SAFMEM and Kilopass XPM memory should be prealably
  *          powered up, and this is a preliminary before calling the current function.
  *          Also sticky program lock, availability of OTP upper if 'otpWordNb' is in upper area have to
  *          be checked externally before.
  *
  * @param  BSECx      : pointer on BSEC HW instance
  * @param  fuseValue  : 32 bits value to be fused : due to techno only bits to 1' in word will be fused.
  *
  * @retval : None
  */
__STATIC_INLINE void LL_BSEC_Set_WordValToFuse(BSEC_TypeDef * BSECx, uint32_t fuseValue)
{
   WRITE_REG(BSECx->WDR,fuseValue);
}


/**
  * @brief  Low level function to be used after a "lower region" word OTP Reload operation.
  *         (bitwise word protected by redundancy 2:1) showed a redundancy error indicated
  *         by BSEC_OTPSR.SECF = 1b1'. The call of the current function will return XOR
  *         of two redundancy words. So all bits to 1b1' in the returned value read in 'BSEC_SRDATAR'
  *         register are in redundancy error. This function allows then to know which bit of the word
  *         have a redundancy error.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Contents of register 'BSEC_SRDATAR', indicating mask of 2:1 redundancy errors
  *           for the OTP lower word (ie : bitwise), just reloaded by an OTP reload operation.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_LowerWordRedundancyErrorMask(BSEC_TypeDef * BSECx)
{
   return(READ_REG(BSECx->SRDATAR));
}


/**
  * @brief  Return information whether register 'BSEC_DENR' is currently sticky write locked
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : 1 if register 'BSEC_DENR' is currently sticky write locked
  *           0 otherwise.
  */
__STATIC_INLINE uint32_t LL_BSEC_Is_Denable_StickyWriteLocked(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->LOCKR, BSEC_LOCKR_DENLOCK) == (BSEC_LOCKR_DENLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Return information whether all BSEC registers are currently globally
  *         sticky write locked : this is the case for 'bsec_corekp1' and 'bsec_core1'.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : 1 if register all BSEC sub-parts : 'bsec_corekp1' and 'bsec_core1'
  *           are currently sticky write locked : meaning that following actions are without
  *           effect :
  *            - BSEC Shadow register write
  *            - OTP Reload operation
  *            - OTP programming operation
  *            - Any BSEC register write
  *           0 otherwise (no BSEC global ongoing sticky write lock).
  */
__STATIC_INLINE uint32_t LL_BSEC_Is_Global_StickyWriteLocked(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->LOCKR, BSEC_LOCKR_GWLOCK) == (BSEC_LOCKR_GWLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Return information whether HWKEY is currently sticky locked (and therefore made unusable).
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : 1 if HWKEY have been made unusable by SAES by previous sticky lock.
  *           0 otherwise (HWKEY can be used if it is valid : see 'BSEC_SR.HVALID' bit).
  */
__STATIC_INLINE uint32_t LL_BSEC_Is_HWKEY_StickyLocked(BSEC_TypeDef * BSECx)
{
  return ((READ_BIT(BSECx->LOCKR, BSEC_LOCKR_HKLOCK) == (BSEC_LOCKR_HKLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Low level function to get 32 bits value written in register 'BSEC_JTAGINR' via CLTAP JTAG chain
  *         by tester. Useful to request bootROM commands from tester to assist the tester the EWS stage for
  *         (ECIES, HWKEY) provisioning stages of EWS.
  *
  * @param  BSECx  : pointer on BSEC HW instance
  *
  * @retval : Contents of register 'BSEC_JTAGINR', is read.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_JtagIn(BSEC_TypeDef * BSECx)
{
   return(READ_REG(BSECx->JTAGINR));
}

/**
  * @brief  Low level function to write 32 bits of data to register 'BSEC_JTAGOUTR'.
  *         The word value will be readable by tester via CLTAP JTAG.
  *         Useful to communicate in direction bootROM -> tester as a result from EWS bootROM
  *         command execution for EWS stages (ECIES, HWKEY) where bootROM assists the tester.
  *
  * @param  BSECx  : pointer on BSEC HW instance
  * @param  value  : 32 bits value to be written to register 'BSEC_JTAGOUTR'.
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Write_JtagOut(BSEC_TypeDef * BSECx, uint32_t value)
{
  WRITE_REG(BSECx->JTAGOUTR,value);
}

/**
  * @brief  Low level function to get contents of register 'BSEC_DENR' but only
  *         the part lower 16 bits with debug signals, not upper part with protection key
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : Contents of register 'BSEC_DENR' debug signals only, but on 32 bits container.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_DenableSignals(BSEC_TypeDef * BSECx)
{

   return((READ_REG(BSECx->DENR) & LL_BSEC_DENR_Msk) >> LL_BSEC_DENR_Pos);
}

/**
  * @brief  Low level function to write 32 bits of data to register 'BSEC_DENR'.
  *
  * @Note : WARNING : the register 'BSEC_DENR' could be sticky write locked
  *         This has to be checked externally by a call to
  *         'LL_BSEC_Is_Denable_StickyWriteLocked(BSEC)' before calling the current
  *         function.
  *
  * @param  BSECx : pointer on BSEC HW instance
  * @param  dbgSignals : wanted state of debug signals on 32 bits
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Set_Denable(BSEC_TypeDef * BSECx, uint32_t dbgSignals)
{
   uint32_t value;

   /* Mask signals part : 16 bits lower from input parameter 'dbgSignals' */
   /* then append write protection key on 16 bits upper part              */
   value = (dbgSignals & 0x0000FFFF) | LL_BSEC_DENR_WRITE_KEY;
   WRITE_REG(BSECx->DENR,value);
}

/**
  * @brief  Low level function to partially unmap ROM by un-mapping the un-mappable
  *         area of ROM. This uses write of register BSEC_UNMAPRR.UNMAP = 0xFFFFFFFF.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : None.
  */
//__STATIC_INLINE void LL_BSEC_Rom_PartialUnmap(BSEC_TypeDef * BSECx)
//{
//  MODIFY_THIS_REG(BSEC,UNMAPR,UNMAP,(uint32_t)LL_BSEC_ROM_IS_PARTIALLY_UNMAPPED);
//}

/**
  * @brief  Low level function to set BSEC_UNMAPR.UNMAP field to value from parameter
  *         area of ROM. This uses write of register BSEC_UNMAPRR.UNMAP = 0xFFFFFFFF.
  *
  * @param  BSECx      : pointer on BSEC HW instance
  * @param  unmapValue : value to set in register field BSEC_UNMAPRR.UNMAP
  * @retval : None.
  */
//__STATIC_INLINE void LL_BSEC_Set_Unmap(BSEC_TypeDef * BSECx, uint32_t unmapValue)
//{
//  MODIFY_THIS_REG(BSEC,UNMAPR,UNMAP,unmapValue);
//}

/**
  * @brief  Low level function to Get BSEC_UNMAPR.UNMAP field
  *
  * @param  BSECx      : pointer on BSEC HW instance
  * @retval : None.
  */
//__STATIC_INLINE uint32_t LL_BSEC_Get_Unmap(BSEC_TypeDef * BSECx)
//{
//  return((uint32_t)READ_THIS_REG_FIELD(BSEC,UNMAPR,UNMAP));
//}

/**
  * @brief  Get field 'OTP_HW_WORD0' : is always shadowed on SoC, so get
  *         value from BSEC_FVR0 shadow register.
  *
  * @Note   Useful for bootROM to verify validity of check word against normal value :
  *         LL_BSEC_CHECK_WORD_REF_VALUE.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value read in BSEC_FVR0 register.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_OTP_CheckWord(BSEC_TypeDef * BSECx)
{
  return READ_REG(BSECx->FVRx[0]);
}

/**
  * @brief  Get field 'OTP_HW_WORD4.tk_retries' : is always shadowed on SoC, so get
  *         value from BSEC_FVR4.tk_retries shadow register field.
  *
  * @Note   Useful to know if ECIES have already be provisioned on a given sample.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : value read in field 'BSEC_FVR4.tk_retries'.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_OTP_TkRetries(BSEC_TypeDef * BSECx)
{
  return(((READ_REG(BSECx->FVRx[4]) & LL_BSEC_TK_RETRIES_MASK) >> LL_BSEC_TK_RETRIES_START_BIT_POS));
}

/**
  * @brief  Low level function to simply
  *         write in register 'BSEC_ENCKEYRx' (where x = wordIdx parameter < 8),
  *         a TK encrypted form of an ECIES_CHIP_PRIVK word (namely ECIES_CHIP_PRIVK_ENCx value).
  *
  * @Note1   Useful in ECIES provisioning stage in EWS.
  *
  * @Note2   WARNING : There is no verification if the BSEC Wrapper is currently BUSY before proceeding,
  *          to the write herein, neither if the sample is in BSEC CLOSED state to make a write effective, neither if
  *          all TK RETRIES are already burnt. All these necessary verification are to be done
  *          externally by SW before calling this function.
  *
  * @param[in] BSECx     : pointer on BSEC HW instance
  * @param[in] wordIdx   : the x of 'BSEC_ENCKEYRx' register, ie its instance, hence
  *                       ECIES Encrypted form word index of ECIES_CHIP_PRIVK_ENC.
  * @param[in] wordValue : The word value to be written in 'BSEC_ENCKEYRx' register
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Write_OTP_EncEcies_Word(BSEC_TypeDef * BSECx, uint32_t wordIdx, uint32_t wordValue)
{
  uint32_t * pEncKeyReg = (uint32_t*)((uint32_t)&BSECx->ENCKEYR0 + (wordIdx * 4));

  if(wordIdx < LL_BSEC_NB_ENC_ECIES_WORDS)
  {
    * pEncKeyReg = wordValue;
  }
}

/**
  * @brief  Low level function to simply
  *         make Hw process 'HWKEY' in BSEC generate from RNG a new random word, verify and fuse it in
  *         OTP word n = 376 + (wordIdx mod 8).
  *         The process needs to be called externally 8 times to have all HWKEY ready in OTP upper
  *         OTP_CFG376..383.
  *         Each time it write 'BSEC_HWKEYR.INDEX[2:0]' = wordIdx from second parameter (0..7), this lead
  *         to generation of OTP word n = 376 + (wordIdx mod 8) with a Random Number got from RNG.
  *
  * @Note1   Useful in HWKEY provisioning stage in EWS.
  *
  * @Note2   WARNING : There is no verification if the BSEC Wrapper is currently BUSY before proceeding,
  *          to the write herein, neither if the sample is in BSEC CLOSED state to make a write effective, neither if
  *          the RNG Hw block is clocked in RCC and ready (entropy).
  *          All these necessary verification are to be done externally before calling this function.
  *
  * @param  BSECx   : pointer on BSEC HW instance
  * @param  wordIdx : to generate HWKEYx word where x == 'wordIdx' from RNG bus (wordIdx = 0..7).
  *
  * @retval : None.
  */
__STATIC_INLINE void LL_BSEC_Write_OTP_HwKey_Word(BSEC_TypeDef * BSECx, uint32_t wordIdx)
{
  if(wordIdx < LL_BSEC_NB_HWKEY_WORDS)
  {
    MODIFY_REG(BSECx->HWKEYR,BSEC_HWKEYR_INDEX,wordIdx << BSEC_HWKEYR_INDEX_Pos);
  }
}

/**
  * @brief  Get field 'BSEC_WRCR.WRC' : this is a counter of 'warm resets' (BSEC 'rst_n')
  *         since last 'scratch_rst_n'.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : returns, the number of warm resets (rst_n only),
  *           since the last cold reset (scratch_rst_n).
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_WarmRstCounter(BSEC_TypeDef * BSECx)
{
  return(READ_REG(BSECx->WRCR));
}

/**
  * @brief  Get field 'BSEC_HRCR.HRC' : this is a counter of 'hot resets' (BSEC 'hot_rst_n')
  *         since last 'scratch_rst_n' (cold) or 'rst_n' (warm) resets.
  *
  * @param  BSECx : pointer on BSEC HW instance
  *
  * @retval : returns, the number of hot resets,
  *           since the last warm or cold reset.
  */
__STATIC_INLINE uint32_t LL_BSEC_Get_HotRstCounter(BSEC_TypeDef * BSECx)
{
  return(READ_REG(BSECx->HRCR));
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)

/**
  * @}
  */

uint32_t LL_BSEC_Is_StickyLocked(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t lockTypeToTest);
void     LL_BSEC_Set_StickyLock(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t lockType);
void     LL_BSEC_Set_OtpCtrl(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t prog, uint32_t lock);
uint32_t LL_BSEC_Is_Rom_FullyMapped(BSEC_TypeDef * BSECx);
uint32_t LL_BSEC_Is_ShadowedOtpReloadedInShadowValid(BSEC_TypeDef * BSECx, uint32_t otpWordNb);
uint32_t LL_BSEC_Is_Shadowed(BSEC_TypeDef * BSECx, uint32_t otpWordNb);
uint32_t LL_BSEC_Get_WarmResetPersistScratch(BSEC_TypeDef * BSECx, uint32_t scratchWordNb);
void     LL_BSEC_Write_WarmResetPersistScratchWord(BSEC_TypeDef * BSECx, uint32_t scratchWordNb, uint32_t value);
uint32_t LL_BSEC_Get_HotResetPersistScratch(BSEC_TypeDef * BSECx, uint32_t scratchWordNb);
void     LL_BSEC_Write_HotResetPersistScratchWord(BSEC_TypeDef * BSECx, uint32_t scratchWordNb, uint32_t value);
void     LL_BSEC_Set_OtpCtrl(BSEC_TypeDef * BSECx, uint32_t otpWordNb, uint32_t prog, uint32_t lock);

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

#endif /* defined(BSEC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_LL_BSEC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

