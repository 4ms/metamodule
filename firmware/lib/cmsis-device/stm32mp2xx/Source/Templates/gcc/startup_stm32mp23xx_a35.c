/*******************************************************************************
 * @file    startup_stm32mp23xx_a35.c
 * @author  C.ICORD (Intropack Team)
 * @version $VERSION$
 * @date    $DATE$
 * @brief   CMSIS Cortex-A35 Device Peripheral Access Layer
 *          A35 Aarch32 Start-up source file
 *
 *   This file :
 *      - maps parameters for EL3 monitor, when it launches current Aarch32
 *        application at EL1 (including AMP/SMP mode and security state)
 *      - sets up initial PC to "Reset Handler"
 *      - manages A35_0/A35_1 or A35_1/A35_0 as master/slave cores
 *      - puts slave core in "Wait for interrupt" state
 *      - gets Exception level by testing PE state
 *      - configures cores according to Exception level (EL3 vs EL1)
 *      - sets up Exception vectors
 *      - sets up stacks for all exception modes
 *      - configures IRQ table
 *      - sets caches and MMU configuration at EL1 (only)
 *      - enables NEON and FPU
 *******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2022 STMicroelectronics</center></h2>
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
 *******************************************************************************
 */
#include "stm32mp23xx.h"
#include "system_stm32mp23xx.h"

/*----------------------------------------------------------------------------
  Definitions
 *----------------------------------------------------------------------------*/
#define USR_MODE 0x10            /* User mode */
#define FIQ_MODE 0x11            /* Fast Interrupt Request mode */
#define IRQ_MODE 0x12            /* Interrupt Request mode */
#define SVC_MODE 0x13            /* Supervisor mode */
#define MON_MODE 0x16            /* Monitor mode */
#define ABT_MODE 0x17            /* Abort mode */
#define UND_MODE 0x1B            /* Undefined Instruction mode */
#define SYS_MODE 0x1F            /* System mode */

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void EL3_EL1_Interface (void) __attribute__ ((naked, section("RESET")));
void Vectors           (void) __attribute__ ((naked, section("RESET")));
void Reset_Handler     (void) __attribute__ ((naked, section("RESET")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
void Undef_Handler (void) __attribute__ ((weak, alias("Default_Undef_Handler")));
void SVC_Handler   (void) __attribute__ ((weak, alias("Default_SVC_Handler")));
void PAbt_Handler  (void) __attribute__ ((weak, alias("Default_PAbt_Handler")));
void DAbt_Handler  (void) __attribute__ ((weak, alias("Default_DAbt_Handler")));
void Rsvd_Handler  (void) __attribute__ ((weak, alias("Default_Rsvd_Handler")));
void IRQ_Handler   (void) __attribute__ ((weak, alias("Default_IRQ_Handler")));
void FIQ_Handler   (void) __attribute__ ((weak, alias("Default_FIQ_Handler")));

/*----------------------------------------------------------------------------
  SoC External Interrupt Handlers
 *----------------------------------------------------------------------------*/
/* Interrupt handler for non-allocated interrupts */
void RESERVED_IRQHandler(void) __attribute__ ((weak, alias("Default_ITHandler")));
/* Interrupt handlers for SGI interrupts */
void SGI0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SGI15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
/* IRQ handlers for PPI interrupts */
void HypervisorTimer_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VirtualTimer_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void Legacy_nFIQ_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SecurePhysicalTimer_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void NonSecurePhysicalTimer_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void Legacy_nIRQ_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
/* IRQ handlers for SPI interrupts */
void PVD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PVM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG3_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG2_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG4_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IWDG5_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void WWDG1_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void WWDG2_RST_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TAMP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RTC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TAMP_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RTC_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RCC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI2_15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_Channel15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_Channel15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_Channel15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPDMA_Channel0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPDMA_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPDMA_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPDMA_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ICACHE_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DCACHE_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ADC1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ADC2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ADC3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN_CAL_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN1_IT0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN2_IT0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN3_IT0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN1_IT1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN2_IT1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FDCAN3_IT1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM1_BRK_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM1_UP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM1_TRG_COM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM1_CC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM20_BRK_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM20_UP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM20_TRG_COM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM20_CC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I3C1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I3C2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USART1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USART2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USART3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VDEC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM8_BRK_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM8_UP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM8_TRG_COM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM8_CC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void FMC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SDMMC1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UART4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UART5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH1_SBD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH1_PMT_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH1_LPI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH2_SBD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH2_PMT_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETH2_LPI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USART6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I3C3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USBH_EHCI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USBH_OHCI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DCMI_PSSI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void CSI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DSI_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
#if defined(STM32MP235Cxx)
void CRYP1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
#endif /* STM32MP235Cxx */
void HASH_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PKA_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UART7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UART8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UART9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPUART1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPI8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SAI1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LTDC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LTDC_ER_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LTDC_SEC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LTDC_SEC_ER_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SAI2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void OCTOSPI1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void OCTOSPI2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void OTFDEC1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPTIM1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VENC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USBH_WAKEUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SPDIFRX_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC1_RX_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC1_TX_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC1_RX_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC1_TX_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC2_RX_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC2_TX_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC2_RX_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IPCC2_TX_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SAES_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
#if defined(STM32MP235Cxx)
void CRYP2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
#endif /* STM32MP235Cxx */
void I2C5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USB3DR_WAKEUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void GPU_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void MDF1_FLT7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SAI3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM16_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM17_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SDMMC2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DCMIPP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HSEM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HSEM_S_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void CPU2_SYSRESETQ_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RNG_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ADF1_FLT_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void COMBOPHY_WAKEUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I2C8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void I3C4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SDMMC3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPTIM2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPTIM3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPTIM4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPTIM5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void OTFDEC2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void CPU2_SEV_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void CPU3_SEV_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RCC_WAKEUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SAI4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DTS_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void TIM11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void CPU1_WAKEUP_PIN_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USB3DR_BC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void USB3DR_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UCPD1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_AER_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_AERM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_BW_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_BWM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_BWAUTO_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_BWAUTOM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_PME_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_PMEM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_SYSERR_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void SERF_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void BUSPERFM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RAMCFG_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DDRCTRL_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DDRPHYC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DFI_ERR_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IAC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VDDCPU_VD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VDDCORE_VD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RETRAMCRC_ERR_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETHSW_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETHSW_MSGBUF_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void ETHSW_FSC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA1_WKUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA2_WKUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void HPDMA3_WKUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void LPDMA_WKUP_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UCPD1_VBUS_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void UCPD1_VSAFE5V_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void RCC_HSI_FMON_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void VDDGPU_VD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_PTMRDY_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_PTMUPD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_INTA_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_INTB_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_INTC_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_INTD_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void EXTI1_15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void IS2M_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void L2WERR_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void DDRPERFM_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMSTAT16_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSIGBL_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI2_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI3_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI4_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI5_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI6_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI7_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI8_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI9_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI10_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI11_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI12_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI13_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI14_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI15_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI16_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI17_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI18_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI19_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI20_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI21_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI22_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI23_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI24_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI25_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI26_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI27_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI28_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI29_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI30_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PCIE_MSI31_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMUIRQ0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void PMUIRQ1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void COMMRX0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void COMMRX1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void COMMTX0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void COMMTX1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void nCTIIRQ0_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));
void nCTIIRQ1_IRQHandler (void) __attribute__ ((weak, alias("Default_ITHandler")));

/*----------------------------------------------------------------------------
  EL3-EL1 Interface parameters
 *----------------------------------------------------------------------------*/
void EL3_EL1_Interface(void)
{
  /* Fill EL3-EL1 interface following structure : */
  /* - EL1 entry-point (Reset_Handler) address    */
#if defined(A35_STARTUP_IN_ARM_MODE)
  __asm__ volatile(".WORD   start_reset_handler");
#else
  __asm__ volatile(".WORD   Reset_Handler");
#endif /* defined(A35_STARTUP_IN_ARM_MODE) */
  /* - EL1 Vector table address                   */
  __asm__ volatile(".WORD   vector_table_addr");
  /* - EL3-EL1 interface identification in ASCII format */
  /*   set to "EL3L" ("EL3 Launcher") by default        */
  __asm__ volatile(".WORD   0x454C334C");
  /* - EL1 Aarch32 security state                   */
  /*   applied to A35_0 core only in AMP mode       */
  /*   or to both A35_0/A35_1 in SMP mode :         */
  /*   . Code for switching A35_0 resp. A35_0/A35_1 */
  /*     to EL1 Aarch32 non-secure state            */
#ifdef A35_NON_SECURE
  __asm__ volatile(".WORD   0xAA3205E1");
  /*     or to EL1 Aarch32 secure state             */
#else
  __asm__ volatile(".WORD   0xAA325EC1");
#endif /* A35_NON_SECURE */
  /* - Memory start address of EL1 A35_0 (AMP) / A35_* (SMP) application */
  __asm__ volatile(".WORD   __MEM_START__");
  /* - Memory end address of EL1 A35_0 (AMP) / A35_* (SMP) application */
  __asm__ volatile(".WORD   FIQ_STACK-1");
  /* - EL3-EL1 interface location for A35_1 core (AMP mode) */
  __asm__ volatile(
#ifdef A35_X_IN_AMP_MODE
  ".WORD   FIQ_STACK  \n"
  /*   or padding word to fill memory (SMP mode)            */
#else
  ".WORD   0x0        \n"
#endif /* A35_X_IN_AMP_MODE */
  /* - Dummy data for alignment */
  ".HWORD   0x0       \n"
  );
}

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector Table
 *----------------------------------------------------------------------------*/
void Vectors(void) {
  __asm__ volatile(
  "vector_table_addr:         \n"
  "B      Reset_Handler       \n"
  "B      Undef_Handler       \n"
  "B      SVC_Handler         \n"
  "B      PAbt_Handler        \n"
  "B      DAbt_Handler        \n"
  "B      Rsvd_Handler        \n"
  "B      IRQ_Handler         \n"
  "B      FIQ_Handler         \n"
  /* - Dummy data for alignment */
  ".HWORD   0x0               \n"
  );
}

/*----------------------------------------------------------------------------
  Interrupt Handlers Table :
  WARNING ! "_IRQHandler" name suffix is inherited from MCU products (used in MCU HAL)
            THIS DOESN'T MEAN THAT ALL INTERRUPTS ARE ROUTED THROUGH IRQ LINE
            BETWEEN GIC400 AND CPU !
            (see SystemInit() implementation for design details about interrupts
             management through IRQ and FIQ lines)
 *----------------------------------------------------------------------------*/
IRQHandler_t Interrupt_Handlers_Table[MAX_IRQ_n] = {
   /* Software Generated Interrupts */
   SGI0_IRQHandler,                    /* 0 */
   SGI1_IRQHandler,
   SGI2_IRQHandler,
   SGI3_IRQHandler,
   SGI4_IRQHandler,
   SGI5_IRQHandler,
   SGI6_IRQHandler,
   SGI7_IRQHandler,
   SGI8_IRQHandler,
   SGI9_IRQHandler,
   SGI10_IRQHandler,                   /* 10 */
   SGI11_IRQHandler,
   SGI12_IRQHandler,
   SGI13_IRQHandler,
   SGI14_IRQHandler,
   SGI15_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,                /* 20 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   /* Private Peripheral Interrupts */
   RESERVED_IRQHandler,                /* 25 */
   HypervisorTimer_IRQHandler,
   VirtualTimer_IRQHandler,
   RESERVED_IRQHandler,
   SecurePhysicalTimer_IRQHandler,
   NonSecurePhysicalTimer_IRQHandler,  /* 30 */
   RESERVED_IRQHandler,
   /******  STM32 specific Interrupt Numbers **************************************/
   /* External interrupts according to                                            */
   /* "Table 234. STM32MP25xx interrupt mapping for Cortex-A35"                   */
   /* in chapitre 32 "interrupt list" of reference document                       */
   /* RM0457 - Reference Manual - STM32MP25xx - advanced ARM-based 32/64-bit MPUs */
   /* file "DM00485804 (RM0457) Rev0.2.pdf" (Revision 0.2 / 27-Jul-2021)          */
   /*******************************************************************************/
   PVD_IRQHandler,
   PVM_IRQHandler,
   IWDG1_IRQHandler,
   IWDG2_IRQHandler,                   /* 35 */
   IWDG3_RST_IRQHandler,
   IWDG2_RST_IRQHandler,
   IWDG4_RST_IRQHandler,
   IWDG5_RST_IRQHandler,
   RESERVED_IRQHandler,                /* 40 */
   RESERVED_IRQHandler,
   WWDG1_RST_IRQHandler,
   WWDG2_RST_IRQHandler,
   TAMP_IRQHandler,
   RTC_IRQHandler,                     /* 45 */
   TAMP_S_IRQHandler,
   RTC_S_IRQHandler,
   RCC_IRQHandler,
   EXTI2_0_IRQHandler,
   EXTI2_1_IRQHandler,                 /* 50 */
   EXTI2_2_IRQHandler,
   EXTI2_3_IRQHandler,
   EXTI2_4_IRQHandler,
   EXTI2_5_IRQHandler,
   EXTI2_6_IRQHandler,                 /* 55 */
   EXTI2_7_IRQHandler,
   EXTI2_8_IRQHandler,
   EXTI2_9_IRQHandler,
   EXTI2_10_IRQHandler,
   EXTI2_11_IRQHandler,                /* 60 */
   EXTI2_12_IRQHandler,
   EXTI2_13_IRQHandler,
   EXTI2_14_IRQHandler,
   EXTI2_15_IRQHandler,
   HPDMA1_Channel0_IRQHandler,         /* 65 */
   HPDMA1_Channel1_IRQHandler,
   HPDMA1_Channel2_IRQHandler,
   HPDMA1_Channel3_IRQHandler,
   HPDMA1_Channel4_IRQHandler,
   HPDMA1_Channel5_IRQHandler,         /* 70 */
   HPDMA1_Channel6_IRQHandler,
   HPDMA1_Channel7_IRQHandler,
   HPDMA1_Channel8_IRQHandler,
   HPDMA1_Channel9_IRQHandler,
   HPDMA1_Channel10_IRQHandler,        /* 75 */
   HPDMA1_Channel11_IRQHandler,
   HPDMA1_Channel12_IRQHandler,
   HPDMA1_Channel13_IRQHandler,
   HPDMA1_Channel14_IRQHandler,
   HPDMA1_Channel15_IRQHandler,        /* 80 */
   HPDMA2_Channel0_IRQHandler,
   HPDMA2_Channel1_IRQHandler,
   HPDMA2_Channel2_IRQHandler,
   HPDMA2_Channel3_IRQHandler,
   HPDMA2_Channel4_IRQHandler,         /* 85 */
   HPDMA2_Channel5_IRQHandler,
   HPDMA2_Channel6_IRQHandler,
   HPDMA2_Channel7_IRQHandler,
   HPDMA2_Channel8_IRQHandler,
   HPDMA2_Channel9_IRQHandler,         /* 90 */
   HPDMA2_Channel10_IRQHandler,
   HPDMA2_Channel11_IRQHandler,
   HPDMA2_Channel12_IRQHandler,
   HPDMA2_Channel13_IRQHandler,
   HPDMA2_Channel14_IRQHandler,        /* 95 */
   HPDMA2_Channel15_IRQHandler,
   HPDMA3_Channel0_IRQHandler,
   HPDMA3_Channel1_IRQHandler,
   HPDMA3_Channel2_IRQHandler,
   HPDMA3_Channel3_IRQHandler,        /* 100 */
   HPDMA3_Channel4_IRQHandler,
   HPDMA3_Channel5_IRQHandler,
   HPDMA3_Channel6_IRQHandler,
   HPDMA3_Channel7_IRQHandler,
   HPDMA3_Channel8_IRQHandler,        /* 105 */
   HPDMA3_Channel9_IRQHandler,
   HPDMA3_Channel10_IRQHandler,
   HPDMA3_Channel11_IRQHandler,
   HPDMA3_Channel12_IRQHandler,
   HPDMA3_Channel13_IRQHandler,       /* 110 */
   HPDMA3_Channel14_IRQHandler,
   HPDMA3_Channel15_IRQHandler,
   LPDMA_Channel0_IRQHandler,
   LPDMA_Channel1_IRQHandler,
   LPDMA_Channel2_IRQHandler,         /* 115 */
   LPDMA_Channel3_IRQHandler,
   ICACHE_IRQHandler,
   DCACHE_IRQHandler,
   ADC1_IRQHandler,
   ADC2_IRQHandler,                   /* 120 */
   ADC3_IRQHandler,
   FDCAN_CAL_IRQHandler,
   FDCAN1_IT0_IRQHandler,
   FDCAN2_IT0_IRQHandler,
   FDCAN3_IT0_IRQHandler,             /* 125 */
   FDCAN1_IT1_IRQHandler,
   FDCAN2_IT1_IRQHandler,
   FDCAN3_IT1_IRQHandler,
   TIM1_BRK_IRQHandler,
   TIM1_UP_IRQHandler,                /* 130 */
   TIM1_TRG_COM_IRQHandler,
   TIM1_CC_IRQHandler,
   TIM20_BRK_IRQHandler,
   TIM20_UP_IRQHandler,
   TIM20_TRG_COM_IRQHandler,          /* 135 */
   TIM20_CC_IRQHandler,
   TIM2_IRQHandler,
   TIM3_IRQHandler,
   TIM4_IRQHandler,
   I2C1_IRQHandler,                   /* 140 */
   I3C1_IRQHandler,
   I2C2_IRQHandler,
   I3C2_IRQHandler,
   SPI1_IRQHandler,
   SPI2_IRQHandler,                   /* 145 */
   USART1_IRQHandler,
   USART2_IRQHandler,
   USART3_IRQHandler,
   VDEC_IRQHandler,
   TIM8_BRK_IRQHandler,               /* 150 */
   TIM8_UP_IRQHandler,
   TIM8_TRG_COM_IRQHandler,
   TIM8_CC_IRQHandler,
   FMC_IRQHandler,
   SDMMC1_IRQHandler,                 /* 155 */
   TIM5_IRQHandler,
   SPI3_IRQHandler,
   UART4_IRQHandler,
   UART5_IRQHandler,
   TIM6_IRQHandler,                   /* 160 */
   TIM7_IRQHandler,
   ETH1_SBD_IRQHandler,
   ETH1_PMT_IRQHandler,
   ETH1_LPI_IRQHandler,
   ETH2_SBD_IRQHandler,               /* 165 */
   ETH2_PMT_IRQHandler,
   ETH2_LPI_IRQHandler,
   USART6_IRQHandler,
   I2C3_IRQHandler,
   I3C3_IRQHandler,                   /* 170 */
   USBH_EHCI_IRQHandler,
   USBH_OHCI_IRQHandler,
   DCMI_PSSI_IRQHandler,
   CSI_IRQHandler,
   DSI_IRQHandler,                    /* 175 */
#if defined(STM32MP235Fxx)
   CRYP1_IRQHandler,
#else /* STM32MP235Fxx */
   RESERVED_IRQHandler,
#endif /* else STM32MP235Fxx */
   HASH_IRQHandler,
   PKA_IRQHandler,
   RESERVED_IRQHandler,
   UART7_IRQHandler,                  /* 180 */
   UART8_IRQHandler,
   UART9_IRQHandler,
   LPUART1_IRQHandler,
   SPI4_IRQHandler,
   SPI5_IRQHandler,                   /* 185 */
   SPI6_IRQHandler,
   SPI7_IRQHandler,
   SPI8_IRQHandler,
   SAI1_IRQHandler,
   LTDC_IRQHandler,                   /* 190 */
   LTDC_ER_IRQHandler,
   LTDC_SEC_IRQHandler,
   LTDC_SEC_ER_IRQHandler,
   SAI2_IRQHandler,
   OCTOSPI1_IRQHandler,               /* 195 */
   OCTOSPI2_IRQHandler,
   OTFDEC1_IRQHandler,
   LPTIM1_IRQHandler,
   VENC_IRQHandler,
   I2C4_IRQHandler,                   /* 200 */
   USBH_WAKEUP_IRQHandler,
   SPDIFRX_IRQHandler,
   IPCC1_RX_IRQHandler,
   IPCC1_TX_IRQHandler,
   IPCC1_RX_S_IRQHandler,             /* 205 */
   IPCC1_TX_S_IRQHandler,
   IPCC2_RX_IRQHandler,
   IPCC2_TX_IRQHandler,
   IPCC2_RX_S_IRQHandler,
   IPCC2_TX_S_IRQHandler,             /* 210 */
   SAES_IRQHandler,
#if defined(STM32MP235Fxx)
   CRYP2_IRQHandler,
#else /* STM32MP235Fxx */
   RESERVED_IRQHandler,
#endif /* else STM32MP235Fxx */
   I2C5_IRQHandler,
   USB3DR_WAKEUP_IRQHandler,
   GPU_IRQHandler,                    /* 215 */
   MDF1_FLT0_IRQHandler,
   MDF1_FLT1_IRQHandler,
   MDF1_FLT2_IRQHandler,
   MDF1_FLT3_IRQHandler,
   MDF1_FLT4_IRQHandler,              /* 220 */
   MDF1_FLT5_IRQHandler,
   MDF1_FLT6_IRQHandler,
   MDF1_FLT7_IRQHandler,
   SAI3_IRQHandler,
   TIM15_IRQHandler,                  /* 225 */
   TIM16_IRQHandler,
   TIM17_IRQHandler,
   TIM12_IRQHandler,
   SDMMC2_IRQHandler,
   DCMIPP_IRQHandler,                 /* 230 */
   HSEM_IRQHandler,
   HSEM_S_IRQHandler,
   RESERVED_IRQHandler,
   CPU2_SYSRESETQ_IRQHandler,
   TIM13_IRQHandler,                  /* 235 */
   TIM14_IRQHandler,
   TIM10_IRQHandler,
   RNG_IRQHandler,
   ADF1_FLT_IRQHandler,
   I2C6_IRQHandler,                   /* 240 */
   COMBOPHY_WAKEUP_IRQHandler,
   I2C7_IRQHandler,
   RESERVED_IRQHandler,
   I2C8_IRQHandler,
   I3C4_IRQHandler,                   /* 245 */
   SDMMC3_IRQHandler,
   LPTIM2_IRQHandler,
   LPTIM3_IRQHandler,
   LPTIM4_IRQHandler,
   LPTIM5_IRQHandler,                 /* 250 */
   OTFDEC2_IRQHandler,
   CPU2_SEV_IRQHandler,
   CPU3_SEV_IRQHandler,
   RCC_WAKEUP_IRQHandler,
   SAI4_IRQHandler,                   /* 255 */
   DTS_IRQHandler,
   TIM11_IRQHandler,
   CPU1_WAKEUP_PIN_IRQHandler,
   USB3DR_BC_IRQHandler,
   USB3DR_IRQHandler,                 /* 260 */
   UCPD1_IRQHandler,
   RESERVED_IRQHandler,
   PCIE_AER_IRQHandler,
   PCIE_AERM_IRQHandler,
   PCIE_BW_IRQHandler,                /* 265 */
   PCIE_BWM_IRQHandler,
   PCIE_BWAUTO_IRQHandler,
   PCIE_BWAUTOM_IRQHandler,
   PCIE_PME_IRQHandler,
   PCIE_PMEM_IRQHandler,              /* 270 */
   PCIE_SYSERR_IRQHandler,
   SERF_IRQHandler,
   BUSPERFM_IRQHandler,
   RAMCFG_IRQHandler,
   DDRCTRL_IRQHandler,                /* 275 */
   DDRPHYC_IRQHandler,
   DFI_ERR_IRQHandler,
   IAC_IRQHandler,
   VDDCPU_VD_IRQHandler,
   VDDCORE_VD_IRQHandler,             /* 280 */
   RETRAMCRC_ERR_IRQHandler,
   ETHSW_IRQHandler,
   ETHSW_MSGBUF_IRQHandler,
   ETHSW_FSC_IRQHandler,
   HPDMA1_WKUP_IRQHandler,            /* 285 */
   HPDMA2_WKUP_IRQHandler,
   HPDMA3_WKUP_IRQHandler,
   LPDMA_WKUP_IRQHandler,
   UCPD1_VBUS_IRQHandler,
   UCPD1_VSAFE5V_IRQHandler,           /* 290 */
   RCC_HSI_FMON_IRQHandler,
   VDDGPU_VD_IRQHandler,
   RESERVED_IRQHandler,
   PCIE_PTMRDY_IRQHandler,
   PCIE_PTMUPD_IRQHandler,            /* 295 */
   PCIE_INTA_IRQHandler,
   PCIE_INTB_IRQHandler,
   PCIE_INTC_IRQHandler,
   PCIE_INTD_IRQHandler,
   EXTI1_0_IRQHandler,                /* 300 */
   EXTI1_1_IRQHandler,
   EXTI1_2_IRQHandler,
   EXTI1_3_IRQHandler,
   EXTI1_4_IRQHandler,
   EXTI1_5_IRQHandler,                /* 305 */
   EXTI1_6_IRQHandler,
   EXTI1_7_IRQHandler,
   EXTI1_8_IRQHandler,
   EXTI1_9_IRQHandler,
   EXTI1_10_IRQHandler,               /* 310 */
   EXTI1_11_IRQHandler,
   EXTI1_12_IRQHandler,
   EXTI1_13_IRQHandler,
   EXTI1_14_IRQHandler,
   EXTI1_15_IRQHandler,               /* 315 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,               /* 320 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,               /* 325 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,               /* 330 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,               /* 335 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   IS2M_IRQHandler,                   /* 340 */
   L2WERR_IRQHandler,
   DDRPERFM_IRQHandler,
   RESERVED_IRQHandler,
   PMSTAT0_IRQHandler,
   PMSTAT1_IRQHandler,                /* 345 */
   PMSTAT2_IRQHandler,
   PMSTAT3_IRQHandler,
   PMSTAT4_IRQHandler,
   PMSTAT5_IRQHandler,
   PMSTAT6_IRQHandler,                /* 350 */
   PMSTAT7_IRQHandler,
   PMSTAT8_IRQHandler,
   PMSTAT9_IRQHandler,
   PMSTAT10_IRQHandler,
   PMSTAT11_IRQHandler,               /* 355 */
   PMSTAT12_IRQHandler,
   PMSTAT13_IRQHandler,
   PMSTAT14_IRQHandler,
   PMSTAT15_IRQHandler,
   PMSTAT16_IRQHandler,               /* 360 */
   PCIE_MSIGBL_IRQHandler,
   PCIE_MSI0_IRQHandler,
   PCIE_MSI1_IRQHandler,
   PCIE_MSI2_IRQHandler,
   PCIE_MSI3_IRQHandler,              /* 365 */
   PCIE_MSI4_IRQHandler,
   PCIE_MSI5_IRQHandler,
   PCIE_MSI6_IRQHandler,
   PCIE_MSI7_IRQHandler,
   PCIE_MSI8_IRQHandler,              /* 370 */
   PCIE_MSI9_IRQHandler,
   PCIE_MSI10_IRQHandler,
   PCIE_MSI11_IRQHandler,
   PCIE_MSI12_IRQHandler,
   PCIE_MSI13_IRQHandler,             /* 375 */
   PCIE_MSI14_IRQHandler,
   PCIE_MSI15_IRQHandler,
   PCIE_MSI16_IRQHandler,
   PCIE_MSI17_IRQHandler,
   PCIE_MSI18_IRQHandler,             /* 380 */
   PCIE_MSI19_IRQHandler,
   PCIE_MSI20_IRQHandler,
   PCIE_MSI21_IRQHandler,
   PCIE_MSI22_IRQHandler,
   PCIE_MSI23_IRQHandler,             /* 385 */
   PCIE_MSI24_IRQHandler,
   PCIE_MSI25_IRQHandler,
   PCIE_MSI26_IRQHandler,
   PCIE_MSI27_IRQHandler,
   PCIE_MSI28_IRQHandler,             /* 390 */
   PCIE_MSI29_IRQHandler,
   PCIE_MSI30_IRQHandler,
   PCIE_MSI31_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,               /* 395 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   PMUIRQ0_IRQHandler,                /* 400 */
   PMUIRQ1_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   COMMRX0_IRQHandler,
   COMMRX1_IRQHandler,                /* 405 */
   RESERVED_IRQHandler,
   RESERVED_IRQHandler,
   COMMTX0_IRQHandler,
   COMMTX1_IRQHandler,
   RESERVED_IRQHandler,               /* 410 */
   RESERVED_IRQHandler,
   nCTIIRQ0_IRQHandler,
   nCTIIRQ1_IRQHandler,
   RESERVED_IRQHandler,
   RESERVED_IRQHandler                /* 415 */
};

uint32_t g_isAarch32inEL3_flag = 1;

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void) {
#if defined(A35_STARTUP_IN_ARM_MODE)
  /* Force ARM mode (vs Thumb mode forced by build toolchain) */
  __asm__ volatile(
  ".code 32                           \n"
  "start_reset_handler:               \n");
#endif /* defined(A35_STARTUP_IN_ARM_MODE) */
  __asm__ volatile(
  /* Mask interrupts */
  "CPSID  if                                       \n"

#if !defined(NO_PARKED_A35)
  /* Put any ("slave") core other than "master" core to sleep */
  /* Read MPIDR for extracting core index */
  "MRC    p15, 0, R0, c0, c0, 5                    \n"
  "ANDS   R0, R0, #3                               \n"
#if defined(MASTER_A35_1)
  "BNE master                                      \n"
#else
  "BEQ master                                      \n"
#endif /* defined(MASTER_A35_1) */
  /* Park "slave" core in "Wait for Interrupt" */
  "goToSleep:                                      \n"
  "WFI                                             \n"
  "B      goToSleep                                \n"
  "master:                                         \n"
#endif /* !defined(NO_PARKED_A35) */

  /* Reset SCTLR Settings */
  "MRC    p15, 0, R0, c1, c0, 0                    \n"  /* Read CP15 System Control register */
  "BIC    R0, R0, #(0x1 << 12)                     \n"  /* Clear I bit 12 to disable I Cache */
  "BIC    R0, R0, #(0x1 <<  2)                     \n"  /* Clear C bit  2 to disable D Cache */
  "BIC    R0, R0, #0x1                             \n"  /* Clear M bit  0 to disable MMU */
  "BIC    R0, R0, #(0x1 << 11)                     \n"  /* Clear Z bit 11 to disable branch prediction */
  "BIC    R0, R0, #(0x1 << 13)                     \n"  /* Clear V bit 13 to disable hivecs */
  "ORR    R0, R0, #(0x1 << 30)                     \n"  /* Set TE bit to take exceptions in Thumb mode */
  "MCR    p15, 0, R0, c1, c0, 0                    \n"  /* Write value back to CP15 System Control register */
  "ISB                                             \n"

  /* Configure ACTLR */
  "MRC    p15, 0, r0, c1, c0, 1                    \n"  /* Read CP15 Auxiliary Control Register */
  "ORR    r0, r0, #(1 <<  1)                       \n"  /* Enable L2 prefetch hint (UNK/WI since r4p1) */
  "MCR    p15, 0, r0, c1, c0, 1                    \n"  /* Write CP15 Auxiliary Control Register */

  /* Set Vector Base Address Register (VBAR) to point to this application's vector table */
  "LDR    R0, =vector_table_addr                   \n"
  "MCR    p15, 0, R0, c12, c0, 0                   \n"
  );

  __asm__ volatile(
  /* Get CPSR to know whether current Aarch32 code is running in EL3 or in EL1 */
  "MRS    R3, CPSR                                 \n"
  /* When code is running in EL3 (CPSR.A bit 8 = 0b0), */
  "ANDS   R3, R3, #0x100                           \n"
  "CMP    R3, #0x100                               \n"
  "BNE    clear_Aarch32inEL3_flag                  \n"
  /* - reset Secure Configuration Register (SCR) to its reset value 0x0 */
  "LDR    R0, =0x0                                 \n"
  "MCR    p15, 0, R0, c1, c1, 0                    \n"
  /* - set Aarch32_in_EL3_flag to 1 */
  "LDR    R2, =0x1                                 \n"
  "B      end_of_CPSR_processing                   \n"
  /* else (when code is running in EL1) */
  "clear_Aarch32inEL3_flag:                        \n"
  /* - clear Aarch32_in_EL3_flag to 0 */
  "LDR    R2, =0x0                                 \n"
  "end_of_CPSR_processing:                         \n"
  "LDR    R3, =g_isAarch32inEL3_flag               \n"
  "STR    R2, [R3]                                 \n"
  );

  __asm__ volatile(
  /* Setup Stack for each exceptional mode */
  "CPS    %[fiq_mode]                              \n"
  "LDR    SP, =FIQ_STACK                           \n"
  "CPS    %[irq_mode]                              \n"
  "LDR    SP, =IRQ_STACK                           \n"
  "CPS    %[svc_mode]                              \n"
  "LDR    SP, =SVC_STACK                           \n"
  "CPS    %[abt_mode]                              \n"
  "LDR    SP, =ABT_STACK                           \n"
  "CPS    %[und_mode]                              \n"
  "LDR    SP, =UND_STACK                           \n"
  "CPS    %[sys_mode]                              \n"
  "LDR    SP, =SYS_STACK                           \n"

  /* workaround to avoid stepping issue */
  "CPS    %[svc_mode]                              \n"

  /* Initialize system : variables (before enabling MMU) and interrupts) */
  "BL     SystemInit                               \n"

  /* Configure and enable MMU & caches at EL1 (only) */
  "LDR    R1, =g_isAarch32inEL3_flag               \n"
  "LDR    R0, [R1]                                 \n"
  "ANDS   R0, R0, #1                               \n"
  "BNE    after_mmu_cache_config                   \n"
  ::[usr_mode] "M" (USR_MODE),
    [fiq_mode] "M" (FIQ_MODE),
    [irq_mode] "M" (IRQ_MODE),
    [svc_mode] "M" (SVC_MODE),
    [abt_mode] "M" (ABT_MODE),
    [und_mode] "M" (UND_MODE),
    [sys_mode] "M" (SYS_MODE));

#if !defined(NO_A35_MMU_CACHE_ENABLE)
  __asm__ volatile(
  /* Set EL1 MMU Configuration (a bit different from EL3 MMU one) */
  /* according to VMSAv8-32 long-descriptor format                */
  /* (see pages 24-26 in [ARM_DAI_0527A] )                        */
  /* - Initialize translation tables :   */
  ".extern mair0_value                             \n"
  ".extern mair1_value                             \n"
  ".extern mp2_el1_ttb0_base                       \n"
  ".extern mp2_el1_ttb1_base                       \n"
  /*   . by setting MAIR0 value */
  /*     (see G6.2.102 "MAIR0, Memory Attribute Indirection Register 0" */
  /*      in [ARM_DDI_0487B.a]  */
  /*      and B1.95 "Memory Attribute Indirection Registers 0 and 1" */
  /*      in [A35_TRM])         */
  /*     Note : only MAIR0 is needed in present code */
  "LDR     r0, =mair0_value                        \n"
  "LDR     r1, [r0]                                \n"
  "MCR     p15, 0, r1, c10, c2, 0                  \n"
  /*   . by setting MAIR1 value */
  /*     (see G6.2.103 "MAIR1, Memory Attribute Indirection Register 1" */
  /*      in [ARM_DDI_0487B.a]  */
  /*      and B1.95 "Memory Attribute Indirection Registers 0 and 1" */
  /*      in [A35_TRM])         */
  /*     Note : MAIR1 is not used in present code */
  "LDR     r0, =mair1_value                        \n"
  "LDR     r1, [r0]                                \n"
  "MCR     p15, 0, r1, c10, c2, 1                  \n"
  /*   . by setting TTBCR value */
  /*     (see G6.2.156 "TTBCR, Translation Table Base Control Register" */
  /*      in [ARM DDI 0487B.a]  */
  /*      and B1.112 "TTBCR with Long-descriptor translation table format" */
  /*      in [A35_TRM])         */
  /*      - bits   [2:0] "T0SZ" = 0b000 = 0                                  */
  /*               <=> The region size is 2^(32-T0SZ) = 2^32 bytes = 4GB.    */
  /*      - bits   [6:3] "RES0" = 0b0000                                     */
  /*      - bit      [7] "EPD0" = 0b0                                        */
  /*                 <=> "Perform translation table walks using TTBR0."      */
  /*      - bits   [9:8] "IRGN0" = 0b01                                      */
  /*                 <=> "Normal memory, Inner Write-Back Read-Allocate      */
  /*                      Write-Allocate Cacheable"                          */
  /*      - bits [11:10] "ORGN0" = 0b01                                      */
  /*                 <=> "Normal memory, Outer Write-Back Read-Allocate      */
  /*                      Write-Allocate Cacheable"                          */
  /*      - bits [13:12] "SH0" = 0b11                                        */
  /*                 <=> "Inner Shareable"                                   */
  /*      - bits [15:14] "RES0" = 0b00                                       */
  /*      - bits [18:16] "T1SZ" = 0b000 = 0                                  */
  /*                 <=> "The region size is 2(32-T1SZ) = 2^32 bytes = 4GB.  */
  /*      - bits [21:19] "RES0" = 0b000                                      */
  /*      - bit     [22] "A1" = 0b0                                          */
  /*                 <=> "TTBR0.ASID defines the ASID.                       */
  /*      - bit     [23] "EPD1" = 0b1                                        */
  /*                 <=> "A TLB miss on an address that is translated        */
  /*                      using TTBR1 generates a Translation fault.         */
  /*                      No translation table walk is performed."           */
  /*      - bits [25:24] "IRGN1" = 0b01                                      */
  /*                 <=> "Normal memory, Inner Write-Back Read-Allocate      */
  /*                      Write-Allocate Cacheable"                          */
  /*      - bits [27:26] "ORGN1" = 0b01                                      */
  /*                 <=> "Normal memory, Outer Write-Back Read-Allocate      */
  /*                      Write-Allocate Cacheable"                          */
  /*      - bits [29:28] "SH1"   = 0b11                                      */
  /*                 <=> "Inner Shareable"                                   */
  /*      - bit       30 "RES0"  = 0b0                                       */
  /*      - bit       31 "EAE"   = 0b1 "Extended Address Enable"             */
  /*                 <=> "Use the VMSAv8-32 translation system               */
  /*                      with the Long-descriptor translation table format" */
  /*      ==> 0xB580_3500                                                    */
  "LDR     r0, =0xB5803500                         \n"
  "MCR     p15, 0, r0, c2, c0, 2                   \n"
  /*   . by setting TTBR0 64-bit value   */
  /*     (see G6.2.158 "TTBR0, Translation Table Base Register 0" */
  /*      in [ARM DDI 0487B.a] */
  /*      and B1.115 "TTBR0 with Long-descriptor translation table format" */
  /*      in [A35_TRM])        */
  /*      - bits   [4:0] "RES0" ("T0SZ" = 0)                    */
  /*      - bits  [31:5] "BADDR[31:5]" = @mp2_el1_ttb0_base     */
  "LDR     r0, =mp2_el1_ttb0_base                  \n"
  /*      - bits [47:32] "BADDR[47:31]" = 0b0000_0000_0000_0000 */
  /*      - bits [55:48] "ASID" = 0b0000_0000                   */
  /*      - bits [63:56] "RES0" = 0b0000_0000                   */
  "MOV     r1, #0                                  \n"
  "MCRR    p15, 0, r0, r1, c2                      \n"
  /*   . by setting TTBR1 64-bit value   */
  /*     (see G6.2.159 "TTBR1, Translation Table Base Register 1" */
  /*      in [ARM DDI 0487B.a] */
  /*      and B1.118 "TTBR1 with Long-descriptor translation table format" */
  /*      in [A35_TRM])        */
  /*      - bits   [4:0] "RES0" ("T1SZ" = 0)                    */
  /*      - bits  [31:5] "BADDR[31:5]" = @mp2_el1_ttb1_base     */
  "LDR     r0, =mp2_el1_ttb1_base                  \n"
  /*      - bits [47:32] "BADDR[47:31]" = 0b0000_0000_0000_0000 */
  /*      - bits [55:48] "ASID" = 0b0000_0000                   */
  /*      - bits [63:56] "RES0" = 0b0000_0000                   */
  "MOV     r1, #0                                  \n"
  "MCRR    p15, 1, r0, r1, c2                      \n"
  "ISB                                             \n"

  /*************************************************************************/
  /* Note : as described in G6.2.34 "DACR, Domain Access Control Register" */
  /*        in [ARM DDI 0487B.a] and in B1.47 in [A35_TRM] :               */
  /*        "This register has no function when TTBCR.EAE is set to 1,     */
  /*         to select the Long-descriptor translation table format."      */
  /*************************************************************************/

  /* Invalidate the MMU and caches : */
  /* - Invalidate all TLB            */
  /*   (see G6.2.128 "TLBIALL, TLB Invalidate All" in [ARM_DDI_0487B.a]) */
  "MCR     p15, 0, r0, c8, c7, 0                   \n"  /* Write TLBIALL */
  "DSB                                             \n"
  "ISB                                             \n"
  /* - Invalidate instruction cache */
  /*   (see G6.2.75 "ICIALLU, Instruction Cache Invalidate All to PoU" */
  /*    in [ARM_DDI_0487B.a])       */
  "MCR     p15, 0, r0, c7, c5, 0                   \n"  /* Write ICIALLU */
  "ISB                                             \n"

  /* - Clean and invalidate data cache */
  /*   As described in 4.3.1 "Cleaning and invalidating the caches" */
  /*   at pages 21-22 of [ARM DAI 0527A] :                          */
  /*   "In ARMv8-A processors and most ARMv7-A processors,          */
  /*    you do not have to do this because hardware automatically   */
  /*    invalidates all cache RAMs after reset."                    */

  /* - Invalidate branch predictor */
  /*   (see G6.2.21 "BPIALL, Branch Predictor Invalidate All" */
  /*    in [ARM_DDI_0487B.a])      */
  "MCR     p15, 0, r0, c7, c5, 6                   \n"  /* Write BPIALL */
  "ISB                                             \n"

  /* Enable the MMU and caches */
  /* - enable Symmetric Multi-Processing according to selection   */
  /*   by setting CPUECTLR bit 6 "SMPEN" accordingly              */
  /*   (see B.1.43 "CPU Extended Control Register" in [A35_TRM]   */
  /*                                                              */
  /*   WARNING ! Only settable in EL3 (see code of EL3 launcher)  */

  /* - enable instruction cache, branch predictor and MMU */
  /*   by setting SCTLR bits 0 "M" and 12 "I" */
  /*   (see B1.105 "System Control Register" in [A35_TRM] */
  /*   Note : Branch prediction not controllable on A35 (bit 11 = res1) */
  "MRC     p15, 0, R0, c1, c0, 0                   \n"  /* Read SCTLR register */
  "ORR     R0, R0, #(0x1 << 12)                    \n"  /* Set bit "I" (Instruction Cache) */
  "ORR     R0, R0, #0x1                            \n"  /* Set bit "M" (Memory Management Unit) */
  "MCR     p15, 0, R0, c1, c0, 0                   \n"  /* Write SCTLR register */
  "DSB                                             \n"
  "ISB                                             \n"
  );
#endif /* ! NO_A35_MMU_CACHE_ENABLE */

  __asm__ volatile(
#if defined(A35_STARTUP_IN_ARM_MODE)
  /* Force ARM mode (vs Thumb mode forced by build toolchain) */
  ".code 32                                        \n"
#endif /* defined(A35_STARTUP_IN_ARM_MODE) */
  "after_mmu_cache_config:                         \n"

#if !defined(NEON_FPU_OFF)
  /* Enable NEON and Floating Point */
  /* (see 4.4 at pages 28-29 in [ARM_DAI_0527A]) */
  /* "In AArch32 mode, access to NEON technology and FP functionality */
  /*  is disabled by default, so it must be explicitly enabled"       */
  /* - Enable access to NEON/FP by enabling access to Coprocessors 10 and 11. */
  /*   Enable Full Access in both privileged and non-privileged modes */
  /*   by setting CPACR bits [23:20] "CP11" & "CP10" to 0b1111 */
  /*   see B1.41 "Architectural Feature Access Control Register" in [A35_TRM] */
  "MOVS    r0, #0                                  \n"
  "ORR     r0, r0, #(0xF << 20)                    \n"
  "MCR     p15, 0, r0, c1, c0, 2                   \n"
  "ISB                                             \n"
  /* - Switch on the FP and NEON hardware  */
  /*   by setting FPEXC bit 30 "EN" to 0b1 */
  /*   (see G6.2.49 "FPEXC, Floating-Point Exception Control register" */
  /*    in [ARM_DDI_0487B.a])              */
  "MOVS    r1, #0                                  \n"
  "ORR     r1, r1, #(0x1 << 30)                    \n"
  "VMSR    FPEXC, r1                               \n"
#endif /* !defined(NEON_FPU_OFF) */

  /* Unmask interrupts */
  "CPSIE  if                                       \n"

  /* Initialize libc */
  "BL __libc_init_array                            \n"

  /* Call __main */
  "BL     main                                     \n"
  );
}

/*----------------------------------------------------------------------------
  Default vector handlers for vector table
 *----------------------------------------------------------------------------*/
__attribute__ ((weakref("While1_UndefITHandler"))) static void Default_Undef_Handler(void);
__attribute__ ((weakref("Nop_ITHandler"))) static void Default_SVC_Handler(void);
__attribute__ ((weakref("While1_PAbtITHandler"))) static void Default_PAbt_Handler(void);
__attribute__ ((weakref("While1_DAbtITHandler"))) static void Default_DAbt_Handler(void);
__attribute__ ((weakref("While1_RsvdITHandler"))) static void Default_Rsvd_Handler(void);
__attribute__ ((weakref("Nop_ITHandler"))) static void Default_IRQ_Handler(void);
__attribute__ ((weakref("Nop_ITHandler"))) static void Default_FIQ_Handler(void);

/*----------------------------------------------------------------------------
  Default IT handler for interrupt table
 *----------------------------------------------------------------------------*/
__attribute__ ((weak, alias("While1_ITHandler"))) void Default_ITHandler(void);
/* Fix debugger use of equivalent weak symbols */
__attribute__ ((weak, alias("Default_ITHandler"))) void AAA_Default_ITHandler(void);

/*----------------------------------------------------------------------------
  Weak interrupt handlers for default definition for vector and interrupt tables
 *----------------------------------------------------------------------------*/
__attribute__ ((interrupt)) void Nop_ITHandler(void)
{
  return;
}
__attribute__ ((interrupt)) void While1_UndefITHandler(void)
{
  while(1);
}
__attribute__ ((interrupt)) void While1_DAbtITHandler(void)
{
  while(1);
}
__attribute__ ((interrupt)) void While1_PAbtITHandler(void)
{
  while(1);
}
__attribute__ ((interrupt)) void While1_RsvdITHandler(void)
{
  while(1);
}
__attribute__ ((interrupt)) void While1_ITHandler(void)
{
  while(1);
}
