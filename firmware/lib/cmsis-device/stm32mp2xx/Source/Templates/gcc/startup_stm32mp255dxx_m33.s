/**
  ******************************************************************************
  * @file      startup_stm32mp255dxx_m33.s
  * @author    Intropack Team
  * @brief     STM32MP257xx devices Cortex-M33 vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address,
  *                - Configure the clock system
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M33 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m33
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word   _sidata
/* start address for the .data section. defined in linker script */
.word   _sdata
/* end address for the .data section. defined in linker script */
.word   _edata
/* start address for the .bss section. defined in linker script */
.word   _sbss
/* end address for the .bss section. defined in linker script */
.word   _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section    .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
    ldr   sp, =_estack    /* set stack pointer */

/* Call the clock system initialization function.*/
    bl  SystemInit

/* Copy the data segment initializers from flash to SRAM *
 * Load from _sidata -> _sdata through _edata
 * _sidata has a vma = lma in flash at the end of .text
 * _sdata has a lma in flash but a vma of ram, so here we move it from where
 * it was loaded (lma) into where it will be accessed (vma).
 * Register Scheme:
 *  r0 = _sdata, r1 = _edata, r2 = _sidata
 *  r3 = index (goes from 0 -> _sdata - _edata)
 *  r4 = temp var for *(_sidata + r3) or (_sdata + r3)
 * This is all equivalent to this C code :
 *  int index = 0;
 *  extern uint32_t *_sdata, *_sidata;
 *  while (_sdata + index < _edata) {
 *    *_sdata[index] = *_sidata[index];
 *    index += 1;
 *  }
 */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit

    ldr r2, =_sbss
    b   LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs    r3, #0
    str r3, [r2], #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss

/* Call static constructors */
    bl __libc_init_array
/* Call the application entry point */
    bl  main

LoopForever:
    b LoopForever

.size   Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section    .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b   Infinite_Loop
    .size   Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex-M33.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
    .section    .isr_vectors,"a",%progbits
    .type   g_pfnVectors, %object

    .globl  __Vectors
__Vectors:
g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   MemManage_Handler
    .word   BusFault_Handler
    .word   UsageFault_Handler
    .word   SecureFault_Handler
    .word   0
    .word   0
    .word   0
    .word   SVC_Handler
    .word   DebugMon_Handler
    .word   0
    .word   PendSV_Handler
    .word   SysTick_Handler
  /*******************************************************************************/
  /* External interrupts according to                                            */
  /* "Table 231. interrupt mapping for Cortex-M33"                               */
  /* in chapitre 31 "interrupt list" of reference document                       */
  /* RM0457 - Reference Manual - STM32MP25xx - advanced ARM-based 32/64-bit MPUs */
  /* file "DM00485804 (RM0457) Rev0.3.pdf" (Revision 0.3 / 14-Apr-2022)          */
  /*******************************************************************************/
    .word   PVD_IRQHandler              /* PVD detector through EXTI */
    .word   PVM_IRQHandler              /* PVM detector through EXTI */
    .word   IWDG3_IRQHandler            /* Independent Watchdog 3 Early wake interrupt */
    .word   IWDG4_IRQHandler            /* Independent Watchdog 4 Early wake interrupt */
    .word   IWDG1_RST_IRQHandler        /* Independent Watchdog 1 Reset through EXTI */
    .word   IWDG2_RST_IRQHandler        /* Independent Watchdog 2 Reset through EXTI */
    .word   IWDG4_RST_IRQHandler        /* Independent Watchdog 4 Reset through EXTI */
    .word   IWDG5_RST_IRQHandler        /* Independent Watchdog 5 Reset through EXTI */
    .word   WWDG1_IRQHandler            /* Window Watchdog 1 Early Wakeup interrupt */
    .word   0
    .word   0
    .word   WWDG2_RST_IRQHandler        /* Window Watchdog 2 Reset through EXTI */
    .word   TAMP_IRQHandler             /* Tamper interrupt (include LSECSS interrupts) */
    .word   RTC_IRQHandler              /* RTC global interrupt */
    .word   TAMP_S_IRQHandler           /* Tamper secure interrupt (include LSECSS interrupts) */
    .word   RTC_S_IRQHandler            /* RTC global secure interrupt */
    .word   RCC_IRQHandler              /* RCC global interrupt */
    .word   EXTI2_0_IRQHandler          /* EXTI2 Line 0 interrupt */
    .word   EXTI2_1_IRQHandler          /* EXTI2 Line 1 interrupt */
    .word   EXTI2_2_IRQHandler          /* EXTI2 Line 2 interrupt */
    .word   EXTI2_3_IRQHandler          /* EXTI2 Line 3 interrupt */
    .word   EXTI2_4_IRQHandler          /* EXTI2 Line 4 interrupt */
    .word   EXTI2_5_IRQHandler          /* EXTI2 Line 5 interrupt */
    .word   EXTI2_6_IRQHandler          /* EXTI2 Line 6 interrupt */
    .word   EXTI2_7_IRQHandler          /* EXTI2 Line 7 interrupt */
    .word   EXTI2_8_IRQHandler          /* EXTI2 Line 8 interrupt */
    .word   EXTI2_9_IRQHandler          /* EXTI2 Line 9 interrupt */
    .word   EXTI2_10_IRQHandler         /* EXTI2 Line 10 interrupt */
    .word   EXTI2_11_IRQHandler         /* EXTI2 Line 11 interrupt */
    .word   EXTI2_12_IRQHandler         /* EXTI2 Line 12 interrupt */
    .word   EXTI2_13_IRQHandler         /* EXTI2 Line 13 interrupt */
    .word   EXTI2_14_IRQHandler         /* EXTI2 Line 14 interrupt */
    .word   EXTI2_15_IRQHandler         /* EXTI2 Line 15 interrupt */
    .word   HPDMA1_Channel0_IRQHandler  /* HPDMA1 Channel0 interrupt */
    .word   HPDMA1_Channel1_IRQHandler  /* HPDMA1 Channel1 interrupt */
    .word   HPDMA1_Channel2_IRQHandler  /* HPDMA1 Channel2 interrupt */
    .word   HPDMA1_Channel3_IRQHandler  /* HPDMA1 Channel3 interrupt */
    .word   HPDMA1_Channel4_IRQHandler  /* HPDMA1 Channel4 interrupt */
    .word   HPDMA1_Channel5_IRQHandler  /* HPDMA1 Channel5 interrupt */
    .word   HPDMA1_Channel6_IRQHandler  /* HPDMA1 Channel6 interrupt */
    .word   HPDMA1_Channel7_IRQHandler  /* HPDMA1 Channel7 interrupt */
    .word   HPDMA1_Channel8_IRQHandler  /* HPDMA1 Channel8 interrupt */
    .word   HPDMA1_Channel9_IRQHandler  /* HPDMA1 Channel9 interrupt */
    .word   HPDMA1_Channel10_IRQHandler /* HPDMA1 Channel10 interrupt */
    .word   HPDMA1_Channel11_IRQHandler /* HPDMA1 Channel11 interrupt */
    .word   HPDMA1_Channel12_IRQHandler /* HPDMA1 Channel12 interrupt */
    .word   HPDMA1_Channel13_IRQHandler /* HPDMA1 Channel13 interrupt */
    .word   HPDMA1_Channel14_IRQHandler /* HPDMA1 Channel14 interrupt */
    .word   HPDMA1_Channel15_IRQHandler /* HPDMA1 Channel15 interrupt */
    .word   HPDMA2_Channel0_IRQHandler  /* HPDMA2 Channel0 interrupt */
    .word   HPDMA2_Channel1_IRQHandler  /* HPDMA2 Channel1 interrupt */
    .word   HPDMA2_Channel2_IRQHandler  /* HPDMA2 Channel2 interrupt */
    .word   HPDMA2_Channel3_IRQHandler  /* HPDMA2 Channel3 interrupt */
    .word   HPDMA2_Channel4_IRQHandler  /* HPDMA2 Channel4 interrupt */
    .word   HPDMA2_Channel5_IRQHandler  /* HPDMA2 Channel5 interrupt */
    .word   HPDMA2_Channel6_IRQHandler  /* HPDMA2 Channel6 interrupt */
    .word   HPDMA2_Channel7_IRQHandler  /* HPDMA2 Channel7 interrupt */
    .word   HPDMA2_Channel8_IRQHandler  /* HPDMA2 Channel8 interrupt */
    .word   HPDMA2_Channel9_IRQHandler  /* HPDMA2 Channel9 interrupt */
    .word   HPDMA2_Channel10_IRQHandler /* HPDMA2 Channel10 interrupt */
    .word   HPDMA2_Channel11_IRQHandler /* HPDMA2 Channel11 interrupt */
    .word   HPDMA2_Channel12_IRQHandler /* HPDMA2 Channel12 interrupt */
    .word   HPDMA2_Channel13_IRQHandler /* HPDMA2 Channel13 interrupt */
    .word   HPDMA2_Channel14_IRQHandler /* HPDMA2 Channel14 interrupt */
    .word   HPDMA2_Channel15_IRQHandler /* HPDMA2 Channel15 interrupt */
    .word   HPDMA3_Channel0_IRQHandler  /* HPDMA3 Channel0 interrupt */
    .word   HPDMA3_Channel1_IRQHandler  /* HPDMA3 Channel1 interrupt */
    .word   HPDMA3_Channel2_IRQHandler  /* HPDMA3 Channel2 interrupt */
    .word   HPDMA3_Channel3_IRQHandler  /* HPDMA3 Channel3 interrupt */
    .word   HPDMA3_Channel4_IRQHandler  /* HPDMA3 Channel4 interrupt */
    .word   HPDMA3_Channel5_IRQHandler  /* HPDMA3 Channel5 interrupt */
    .word   HPDMA3_Channel6_IRQHandler  /* HPDMA3 Channel6 interrupt */
    .word   HPDMA3_Channel7_IRQHandler  /* HPDMA3 Channel7 interrupt */
    .word   HPDMA3_Channel8_IRQHandler  /* HPDMA3 Channel8 interrupt */
    .word   HPDMA3_Channel9_IRQHandler  /* HPDMA3 Channel9 interrupt */
    .word   HPDMA3_Channel10_IRQHandler /* HPDMA3 Channel10 interrupt */
    .word   HPDMA3_Channel11_IRQHandler /* HPDMA3 Channel11 interrupt */
    .word   HPDMA3_Channel12_IRQHandler /* HPDMA3 Channel12 interrupt */
    .word   HPDMA3_Channel13_IRQHandler /* HPDMA3 Channel13 interrupt */
    .word   HPDMA3_Channel14_IRQHandler /* HPDMA3 Channel14 interrupt */
    .word   HPDMA3_Channel15_IRQHandler /* HPDMA3 Channel15 interrupt */
    .word   LPDMA_Channel0_IRQHandler   /* LPDMA Channel0 interrupt */
    .word   LPDMA_Channel1_IRQHandler   /* LPDMA Channel1 interrupt */
    .word   LPDMA_Channel2_IRQHandler   /* LPDMA Channel2 interrupt */
    .word   LPDMA_Channel3_IRQHandler   /* LPDMA Channel3 interrupt */
    .word   ICACHE_IRQHandler           /* ICACHE interrupt */
    .word   DCACHE_IRQHandler           /* DCACHE interrupt */
    .word   ADC1_IRQHandler             /* ADC1 interrupt */
    .word   ADC2_IRQHandler             /* ADC2  interrupt */
    .word   ADC3_IRQHandler             /* ADC3 interrupt */
    .word   FDCAN_CAL_IRQHandler        /* FDCAN CCU interrupt */
    .word   FDCAN1_IT0_IRQHandler       /* FDCAN1 interrupt 0 */
    .word   FDCAN2_IT0_IRQHandler       /* FDCAN2 interrupt 0 */
    .word   FDCAN3_IT0_IRQHandler       /* FDCAN3 interrupt 0 */
    .word   FDCAN1_IT1_IRQHandler       /* FDCAN1 interrupt 1 */
    .word   FDCAN2_IT1_IRQHandler       /* FDCAN2 interrupt 1 */
    .word   FDCAN3_IT1_IRQHandler       /* FDCAN3 interrupt 1 */
    .word   TIM1_BRK_IRQHandler         /* TIM1 Break interrupt */
    .word   TIM1_UP_IRQHandler          /* TIM1 Update interrupt */
    .word   TIM1_TRG_COM_IRQHandler     /* TIM1 Trigger and Commutation interrupts */
    .word   TIM1_CC_IRQHandler          /* TIM1 Capture Compare interrupt */
    .word   TIM20_BRK_IRQHandler        /* TIM20 Break interrupt */
    .word   TIM20_UP_IRQHandler         /* TIM20 Update interrupt */
    .word   TIM20_TRG_COM_IRQHandler    /* TIM20 Trigger and Commutation interrupts */
    .word   TIM20_CC_IRQHandler         /* TIM20 Capture Compare interrupt */
    .word   TIM2_IRQHandler             /* TIM2 global interrupt */
    .word   TIM3_IRQHandler             /* TIM3 global interrupt */
    .word   TIM4_IRQHandler             /* TIM4 global interrupt */
    .word   I2C1_IRQHandler             /* I2C1 global interrupt */
    .word   I3C1_IRQHandler             /* I3C1 global interrupt */
    .word   I2C2_IRQHandler             /* I2C2 global interrupt */
    .word   I3C2_IRQHandler             /* I3C2 global interrupt */
    .word   SPI1_IRQHandler             /* SPI1 global interrupt */
    .word   SPI2_IRQHandler             /* SPI2 global interrupt */
    .word   USART1_IRQHandler           /* USART1 global interrupt */
    .word   USART2_IRQHandler           /* USART2 global interrupt */
    .word   USART3_IRQHandler           /* USART3 global interrupt */
    .word   VDEC_IRQHandler             /* VDEC global interrupt */
    .word   TIM8_BRK_IRQHandler         /* TIM8 Break interrupt */
    .word   TIM8_UP_IRQHandler          /* TIM8 Update interrupt */
    .word   TIM8_TRG_COM_IRQHandler     /* TIM8 Trigger & Commutation interrupt */
    .word   TIM8_CC_IRQHandler          /* TIM8 Capture Compare interrupt */
    .word   FMC_IRQHandler              /* FMC global interrupt */
    .word   SDMMC1_IRQHandler           /* SDMMC1 global interrupt */
    .word   TIM5_IRQHandler             /* TIM5 global interrupt */
    .word   SPI3_IRQHandler             /* SPI3 global interrupt */
    .word   UART4_IRQHandler            /* UART4 global interrupt */
    .word   UART5_IRQHandler            /* UART5 global interrupt */
    .word   TIM6_IRQHandler             /* TIM6 global interrupt */
    .word   TIM7_IRQHandler             /* TIM7 global interrupt */
    .word   ETH1_SBD_IRQHandler         /* ETH1 global interrupt */
    .word   ETH1_PMT_IRQHandler         /* ETH1 wake-up interrupt */
    .word   ETH1_LPI_IRQHandler         /* ETH1 LPI interrupt */
    .word   ETH2_SBD_IRQHandler         /* ETH2 global interrupt */
    .word   ETH2_PMT_IRQHandler         /* ETH2 wake-up interrupt */
    .word   ETH2_LPI_IRQHandler         /* ETH2 LPI interrupt */
    .word   USART6_IRQHandler           /* USART6 global interrupt */
    .word   I2C3_IRQHandler             /* I2C3 global interrupt */
    .word   I3C3_IRQHandler             /* I3C3 global interrupt */
    .word   USBH_EHCI_IRQHandler        /* USB Host EHCI interrupt */
    .word   USBH_OHCI_IRQHandler        /* USB Host OHCI interrupt */
    .word   DCMI_PSSI_IRQHandler        /* DCMI & PSSI global interrupt */
    .word   CSI_IRQHandler              /* CSI-2 interrupt */
    .word   DSI_IRQHandler              /* DSI Host controller global interrupt */
    .word   0
    .word   HASH_IRQHandler             /* Hash interrupt */
    .word   PKA_IRQHandler              /* PKA interrupt */
    .word   FPU_IRQHandler              /* FPU global interrupt */
    .word   UART7_IRQHandler            /* UART7 global interrupt */
    .word   UART8_IRQHandler            /* UART8 global interrupt */
    .word   UART9_IRQHandler            /* UART9 global interrupt */
    .word   LPUART1_IRQHandler          /* LPUART1 global interrupt */
    .word   SPI4_IRQHandler             /* SPI4 global interrupt */
    .word   SPI5_IRQHandler             /* SPI5 global interrupt */
    .word   SPI6_IRQHandler             /* SPI6 global interrupt */
    .word   SPI7_IRQHandler             /* SPI7 global interrupt */
    .word   SPI8_IRQHandler             /* SPI8 global interrupt */
    .word   SAI1_IRQHandler             /* SAI1 global interrupt */
    .word   LTDC_IRQHandler             /* LTDC global interrupt */
    .word   LTDC_ER_IRQHandler          /* LTDC global error interrupt */
    .word   LTDC_SEC_IRQHandler         /* LTDC security global interrupt */
    .word   LTDC_SEC_ER_IRQHandler      /* LTDC security global error interrupt */
    .word   SAI2_IRQHandler             /* SAI2 global interrupt */
    .word   OCTOSPI1_IRQHandler         /* OCTOSPI1 global interrupt */
    .word   OCTOSPI2_IRQHandler         /* OCTOSPI2 global interrupt */
    .word   0
    .word   LPTIM1_IRQHandler           /* LPTIMER1 global interrupt */
    .word   VENC_IRQHandler             /* VENC global interrupt */
    .word   I2C4_IRQHandler             /* I2C4 global interrupt */
    .word   USBH_WAKEUP_IRQHandler      /* USB Host remote wake up from USB2PHY1 interrupt */
    .word   SPDIFRX_IRQHandler          /* SPDIFRX global interrupt */
    .word   IPCC1_RX_IRQHandler        /* Mailbox 1 RX Occupied interrupt */
    .word   IPCC1_TX_IRQHandler        /* Mailbox 1 TX Free interrupt */
    .word   IPCC1_RX_S_IRQHandler      /* Mailbox 1 RX Occupied secure interrupt */
    .word   IPCC1_TX_S_IRQHandler      /* Mailbox 1 TX Free secure interrupt */
    .word   IPCC2_RX_IRQHandler        /* Mailbox 2 RX Occupied interrupt */
    .word   IPCC2_TX_IRQHandler        /* Mailbox 2 TX Free interrupt */
    .word   IPCC2_RX_S_IRQHandler      /* Mailbox 2 RX Occupied secure interrupt */
    .word   IPCC2_TX_S_IRQHandler      /* Mailbox 2 TX Free secure interrupt */
    .word   0
    .word   0
    .word   I2C5_IRQHandler             /* I2C5 global interrupt */
    .word   USB3DR_WAKEUP_IRQHandler    /* USB3 remote wake up from USB2PHY1 interrupt */
    .word   GPU_IRQHandler              /* GPU global Interrupt */
    .word   MDF1_FLT0_IRQHandler        /* MDF1 Filter0 interrupt */
    .word   MDF1_FLT1_IRQHandler        /* MDF1 Filter1 interrupt */
    .word   MDF1_FLT2_IRQHandler        /* MDF1 Filter2 interrupt */
    .word   MDF1_FLT3_IRQHandler        /* MDF1 Filter3 interrupt */
    .word   MDF1_FLT4_IRQHandler        /* MDF1 Filter4 interrupt */
    .word   MDF1_FLT5_IRQHandler        /* MDF1 Filter5 interrupt */
    .word   MDF1_FLT6_IRQHandler        /* MDF1 Filter6 interrupt */
    .word   MDF1_FLT7_IRQHandler        /* MDF1 Filter7 interrupt */
    .word   SAI3_IRQHandler             /* SAI3 global interrupt */
    .word   TIM15_IRQHandler            /* TIM15 global interrupt */
    .word   TIM16_IRQHandler            /* TIM16 global interrupt */
    .word   TIM17_IRQHandler            /* TIM17 global interrupt */
    .word   TIM12_IRQHandler            /* TIM12 global interrupt */
    .word   SDMMC2_IRQHandler           /* SDMMC2 global interrupt */
    .word   DCMIPP_IRQHandler           /* DCMIPP global interrupt */
    .word   HSEM_IRQHandler             /* HSEM nonsecure interrupt */
    .word   HSEM_S_IRQHandler           /* HSEM secure interrupt */
    .word   nCTIIRQ1_IRQHandler         /* Cortex-M33 CTI interrupt 1 */
    .word   nCTIIRQ2_IRQHandler         /* Cortex-M33 CTI interrupt 2 */
    .word   TIM13_IRQHandler            /* TIM13 global interrupt */
    .word   TIM14_IRQHandler            /* TIM14 global interrupt */
    .word   TIM10_IRQHandler            /* TIM10 global interrupt */
    .word   RNG_IRQHandler              /* RNG global interrupt */
    .word   ADF1_FLT_IRQHandler         /* ADF1 Filter interrupt */
    .word   I2C6_IRQHandler             /* I2C6 global interrupt */
    .word   COMBOPHY_WAKEUP_IRQHandler  /* COMBOPHY LFPS start request interrupt */
    .word   I2C7_IRQHandler             /* I2C7 global interrupt */
    .word   0
    .word   I2C8_IRQHandler             /* I2C8 global interrupt */
    .word   I3C4_IRQHandler             /* I3C4 global interrupt */
    .word   SDMMC3_IRQHandler           /* SDMMC3 global interrupt */
    .word   LPTIM2_IRQHandler           /* LPTIMER2 global interrupt */
    .word   LPTIM3_IRQHandler           /* LPTIMER3 global interrupt */
    .word   LPTIM4_IRQHandler           /* LPTIMER4 global interrupt */
    .word   LPTIM5_IRQHandler           /* LPTIMER5 global interrupt */
    .word   0
    .word   CPU1_SEV_IRQHandler         /* Cortex-A35 Send Event through EXTI */
    .word   CPU3_SEV_IRQHandler         /* Cortex-M0+ Send Event through EXTI */
    .word   RCC_WAKEUP_IRQHandler       /* RCC CPU2 Wake up interrupt */
    .word   SAI4_IRQHandler             /* SAI4 global interrupt */
    .word   DTS_IRQHandler              /* Temperature sensor interrupt */
    .word   TIM11_IRQHandler            /* TIMER11 global interrupt */
    .word   CPU2_WAKEUP_PIN_IRQHandler  /* Interrupt for all 6 wake-up enabled by CPU2 */
    .word   USB3DR_BC_IRQHandler        /* USB3 BC interrupt */
    .word   USB3DR_IRQHandler           /* USB3 interrupt */
    .word   UCPD1_IRQHandler            /* USB PD interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   SERF_IRQHandler             /* SERF global interrupt */
    .word   BUSPERFM_IRQHandler         /* BUS Performance Monitor interrupt */
    .word   RAMCFG_IRQHandler           /* RAM configuration global interrupt */
    .word   DDRCTRL_IRQHandler          /* DDRCTRL interrupt */
    .word   DDRPHYC_IRQHandler          /* DDRPHY interrupt (active low) */
    .word   DFI_ERR_IRQHandler          /* DDRPHY DFI error interrupt */
    .word   IAC_IRQHandler              /* RIF Illegal access Controller interrupt */
    .word   VDDCPU_VD_IRQHandler        /* VDDCPU voltage detector interrupt */
    .word   VDDCORE_VD_IRQHandler       /* VDDCORE voltage detector interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   HPDMA1_WKUP_IRQHandler      /* HPDMA1 channel 0 to 15 wake up */
    .word   HPDMA2_WKUP_IRQHandler      /* HPDMA2 channel 0 to 15 wake up */
    .word   HPDMA3_WKUP_IRQHandler      /* HPDMA3 channel 0 to 15 wake up */
    .word   LPDMA_WKUP_IRQHandler       /* LPDMA channel 0 to 3 wake up */
    .word   UCPD1_VBUS_IRQHandler        /* USB TypeC VBUS valid interrupt */
    .word   UCPD1_VSAFE5V_IRQHandler     /* USB TypeC VSAFE5V valid interrupt */
    .word   RCC_HSI_FMON_IRQHandler     /* HSI Frequency Monitor interrupt */
    .word   VDDGPU_VD_IRQHandler        /* VDDGPU voltage detector interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   EXTI1_0_IRQHandler          /* EXTI1 Line 0 interrupt */
    .word   EXTI1_1_IRQHandler          /* EXTI1 Line 1 interrupt */
    .word   EXTI1_2_IRQHandler          /* EXTI1 Line 2 interrupt */
    .word   EXTI1_3_IRQHandler          /* EXTI1 Line 3 interrupt */
    .word   EXTI1_4_IRQHandler          /* EXTI1 Line 4 interrupt */
    .word   EXTI1_5_IRQHandler          /* EXTI1 Line 5 interrupt */
    .word   EXTI1_6_IRQHandler          /* EXTI1 Line 6 interrupt */
    .word   EXTI1_7_IRQHandler          /* EXTI1 Line 7 interrupt */
    .word   EXTI1_8_IRQHandler          /* EXTI1 Line 8 interrupt */
    .word   EXTI1_9_IRQHandler          /* EXTI1 Line 9 interrupt */
    .word   EXTI1_10_IRQHandler         /* EXTI1 Line 10 interrupt */
    .word   EXTI1_11_IRQHandler         /* EXTI1 Line 11 interrupt */
    .word   EXTI1_12_IRQHandler         /* EXTI1 Line 12 interrupt */
    .word   EXTI1_13_IRQHandler         /* EXTI1 Line 13 interrupt */
    .word   EXTI1_14_IRQHandler         /* EXTI1 Line 14 interrupt */
    .word   EXTI1_15_IRQHandler         /* EXTI1 Line 15 interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   IS2M_IRQHandler             /* IS2M fault detection interrupt */
    .word   0
    .word   DDRPERFM_IRQHandler         /* DDR Performance Monitor interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

    .size   g_pfnVectors, .-g_pfnVectors


/*******************************************************************************
 * Provide weak aliases for each Exception handler to the Default_Handler.
 * As they are weak aliases, any function with the same name will override
 * this definition.
 ******************************************************************************/
/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers
 */
    .macro  def_irq_handler handler_name
    .weak \handler_name
    .thumb_set \handler_name, Default_Handler
    .endm

    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler MemManage_Handler
    def_irq_handler BusFault_Handler
    def_irq_handler UsageFault_Handler
    def_irq_handler SecureFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler DebugMon_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler

    def_irq_handler PVD_IRQHandler
    def_irq_handler PVM_IRQHandler
    def_irq_handler IWDG3_IRQHandler
    def_irq_handler IWDG4_IRQHandler
    def_irq_handler IWDG1_RST_IRQHandler
    def_irq_handler IWDG2_RST_IRQHandler
    def_irq_handler IWDG4_RST_IRQHandler
    def_irq_handler IWDG5_RST_IRQHandler
    def_irq_handler WWDG1_IRQHandler
    def_irq_handler WWDG2_RST_IRQHandler
    def_irq_handler TAMP_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler TAMP_S_IRQHandler
    def_irq_handler RTC_S_IRQHandler
    def_irq_handler RCC_IRQHandler
    def_irq_handler EXTI2_0_IRQHandler
    def_irq_handler EXTI2_1_IRQHandler
    def_irq_handler EXTI2_2_IRQHandler
    def_irq_handler EXTI2_3_IRQHandler
    def_irq_handler EXTI2_4_IRQHandler
    def_irq_handler EXTI2_5_IRQHandler
    def_irq_handler EXTI2_6_IRQHandler
    def_irq_handler EXTI2_7_IRQHandler
    def_irq_handler EXTI2_8_IRQHandler
    def_irq_handler EXTI2_9_IRQHandler
    def_irq_handler EXTI2_10_IRQHandler
    def_irq_handler EXTI2_11_IRQHandler
    def_irq_handler EXTI2_12_IRQHandler
    def_irq_handler EXTI2_13_IRQHandler
    def_irq_handler EXTI2_14_IRQHandler
    def_irq_handler EXTI2_15_IRQHandler
    def_irq_handler HPDMA1_Channel0_IRQHandler
    def_irq_handler HPDMA1_Channel1_IRQHandler
    def_irq_handler HPDMA1_Channel2_IRQHandler
    def_irq_handler HPDMA1_Channel3_IRQHandler
    def_irq_handler HPDMA1_Channel4_IRQHandler
    def_irq_handler HPDMA1_Channel5_IRQHandler
    def_irq_handler HPDMA1_Channel6_IRQHandler
    def_irq_handler HPDMA1_Channel7_IRQHandler
    def_irq_handler HPDMA1_Channel8_IRQHandler
    def_irq_handler HPDMA1_Channel9_IRQHandler
    def_irq_handler HPDMA1_Channel10_IRQHandler
    def_irq_handler HPDMA1_Channel11_IRQHandler
    def_irq_handler HPDMA1_Channel12_IRQHandler
    def_irq_handler HPDMA1_Channel13_IRQHandler
    def_irq_handler HPDMA1_Channel14_IRQHandler
    def_irq_handler HPDMA1_Channel15_IRQHandler
    def_irq_handler HPDMA2_Channel0_IRQHandler
    def_irq_handler HPDMA2_Channel1_IRQHandler
    def_irq_handler HPDMA2_Channel2_IRQHandler
    def_irq_handler HPDMA2_Channel3_IRQHandler
    def_irq_handler HPDMA2_Channel4_IRQHandler
    def_irq_handler HPDMA2_Channel5_IRQHandler
    def_irq_handler HPDMA2_Channel6_IRQHandler
    def_irq_handler HPDMA2_Channel7_IRQHandler
    def_irq_handler HPDMA2_Channel8_IRQHandler
    def_irq_handler HPDMA2_Channel9_IRQHandler
    def_irq_handler HPDMA2_Channel10_IRQHandler
    def_irq_handler HPDMA2_Channel11_IRQHandler
    def_irq_handler HPDMA2_Channel12_IRQHandler
    def_irq_handler HPDMA2_Channel13_IRQHandler
    def_irq_handler HPDMA2_Channel14_IRQHandler
    def_irq_handler HPDMA2_Channel15_IRQHandler
    def_irq_handler HPDMA3_Channel0_IRQHandler
    def_irq_handler HPDMA3_Channel1_IRQHandler
    def_irq_handler HPDMA3_Channel2_IRQHandler
    def_irq_handler HPDMA3_Channel3_IRQHandler
    def_irq_handler HPDMA3_Channel4_IRQHandler
    def_irq_handler HPDMA3_Channel5_IRQHandler
    def_irq_handler HPDMA3_Channel6_IRQHandler
    def_irq_handler HPDMA3_Channel7_IRQHandler
    def_irq_handler HPDMA3_Channel8_IRQHandler
    def_irq_handler HPDMA3_Channel9_IRQHandler
    def_irq_handler HPDMA3_Channel10_IRQHandler
    def_irq_handler HPDMA3_Channel11_IRQHandler
    def_irq_handler HPDMA3_Channel12_IRQHandler
    def_irq_handler HPDMA3_Channel13_IRQHandler
    def_irq_handler HPDMA3_Channel14_IRQHandler
    def_irq_handler HPDMA3_Channel15_IRQHandler
    def_irq_handler LPDMA_Channel0_IRQHandler
    def_irq_handler LPDMA_Channel1_IRQHandler
    def_irq_handler LPDMA_Channel2_IRQHandler
    def_irq_handler LPDMA_Channel3_IRQHandler
    def_irq_handler ICACHE_IRQHandler
    def_irq_handler DCACHE_IRQHandler
    def_irq_handler ADC1_IRQHandler
    def_irq_handler ADC2_IRQHandler
    def_irq_handler ADC3_IRQHandler
    def_irq_handler FDCAN_CAL_IRQHandler
    def_irq_handler FDCAN1_IT0_IRQHandler
    def_irq_handler FDCAN2_IT0_IRQHandler
    def_irq_handler FDCAN3_IT0_IRQHandler
    def_irq_handler FDCAN1_IT1_IRQHandler
    def_irq_handler FDCAN2_IT1_IRQHandler
    def_irq_handler FDCAN3_IT1_IRQHandler
    def_irq_handler TIM1_BRK_IRQHandler
    def_irq_handler TIM1_UP_IRQHandler
    def_irq_handler TIM1_TRG_COM_IRQHandler
    def_irq_handler TIM1_CC_IRQHandler
    def_irq_handler TIM20_BRK_IRQHandler
    def_irq_handler TIM20_UP_IRQHandler
    def_irq_handler TIM20_TRG_COM_IRQHandler
    def_irq_handler TIM20_CC_IRQHandler
    def_irq_handler TIM2_IRQHandler
    def_irq_handler TIM3_IRQHandler
    def_irq_handler TIM4_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler I3C1_IRQHandler
    def_irq_handler I2C2_IRQHandler
    def_irq_handler I3C2_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler SPI2_IRQHandler
    def_irq_handler USART1_IRQHandler
    def_irq_handler USART2_IRQHandler
    def_irq_handler USART3_IRQHandler
    def_irq_handler VDEC_IRQHandler
    def_irq_handler TIM8_BRK_IRQHandler
    def_irq_handler TIM8_UP_IRQHandler
    def_irq_handler TIM8_TRG_COM_IRQHandler
    def_irq_handler TIM8_CC_IRQHandler
    def_irq_handler FMC_IRQHandler
    def_irq_handler SDMMC1_IRQHandler
    def_irq_handler TIM5_IRQHandler
    def_irq_handler SPI3_IRQHandler
    def_irq_handler UART4_IRQHandler
    def_irq_handler UART5_IRQHandler
    def_irq_handler TIM6_IRQHandler
    def_irq_handler TIM7_IRQHandler
    def_irq_handler ETH1_SBD_IRQHandler
    def_irq_handler ETH1_PMT_IRQHandler
    def_irq_handler ETH1_LPI_IRQHandler
    def_irq_handler ETH2_SBD_IRQHandler
    def_irq_handler ETH2_PMT_IRQHandler
    def_irq_handler ETH2_LPI_IRQHandler
    def_irq_handler USART6_IRQHandler
    def_irq_handler I2C3_IRQHandler
    def_irq_handler I3C3_IRQHandler
    def_irq_handler USBH_EHCI_IRQHandler
    def_irq_handler USBH_OHCI_IRQHandler
    def_irq_handler DCMI_PSSI_IRQHandler
    def_irq_handler CSI_IRQHandler
    def_irq_handler DSI_IRQHandler
    def_irq_handler HASH_IRQHandler
    def_irq_handler PKA_IRQHandler
    def_irq_handler FPU_IRQHandler
    def_irq_handler UART7_IRQHandler
    def_irq_handler UART8_IRQHandler
    def_irq_handler UART9_IRQHandler
    def_irq_handler LPUART1_IRQHandler
    def_irq_handler SPI4_IRQHandler
    def_irq_handler SPI5_IRQHandler
    def_irq_handler SPI6_IRQHandler
    def_irq_handler SPI7_IRQHandler
    def_irq_handler SPI8_IRQHandler
    def_irq_handler SAI1_IRQHandler
    def_irq_handler LTDC_IRQHandler
    def_irq_handler LTDC_ER_IRQHandler
    def_irq_handler LTDC_SEC_IRQHandler
    def_irq_handler LTDC_SEC_ER_IRQHandler
    def_irq_handler SAI2_IRQHandler
    def_irq_handler OCTOSPI1_IRQHandler
    def_irq_handler OCTOSPI2_IRQHandler
    def_irq_handler LPTIM1_IRQHandler
    def_irq_handler VENC_IRQHandler
    def_irq_handler I2C4_IRQHandler
    def_irq_handler USBH_WAKEUP_IRQHandler
    def_irq_handler SPDIFRX_IRQHandler
    def_irq_handler IPCC1_RX_IRQHandler
    def_irq_handler IPCC1_TX_IRQHandler
    def_irq_handler IPCC1_RX_S_IRQHandler
    def_irq_handler IPCC1_TX_S_IRQHandler
    def_irq_handler IPCC2_RX_IRQHandler
    def_irq_handler IPCC2_TX_IRQHandler
    def_irq_handler IPCC2_RX_S_IRQHandler
    def_irq_handler IPCC2_TX_S_IRQHandler
    def_irq_handler I2C5_IRQHandler
    def_irq_handler USB3DR_WAKEUP_IRQHandler
    def_irq_handler GPU_IRQHandler
    def_irq_handler MDF1_FLT0_IRQHandler
    def_irq_handler MDF1_FLT1_IRQHandler
    def_irq_handler MDF1_FLT2_IRQHandler
    def_irq_handler MDF1_FLT3_IRQHandler
    def_irq_handler MDF1_FLT4_IRQHandler
    def_irq_handler MDF1_FLT5_IRQHandler
    def_irq_handler MDF1_FLT6_IRQHandler
    def_irq_handler MDF1_FLT7_IRQHandler
    def_irq_handler SAI3_IRQHandler
    def_irq_handler TIM15_IRQHandler
    def_irq_handler TIM16_IRQHandler
    def_irq_handler TIM17_IRQHandler
    def_irq_handler TIM12_IRQHandler
    def_irq_handler SDMMC2_IRQHandler
    def_irq_handler DCMIPP_IRQHandler
    def_irq_handler HSEM_IRQHandler
    def_irq_handler HSEM_S_IRQHandler
    def_irq_handler nCTIIRQ1_IRQHandler
    def_irq_handler nCTIIRQ2_IRQHandler
    def_irq_handler TIM13_IRQHandler
    def_irq_handler TIM14_IRQHandler
    def_irq_handler TIM10_IRQHandler
    def_irq_handler RNG_IRQHandler
    def_irq_handler ADF1_FLT_IRQHandler
    def_irq_handler I2C6_IRQHandler
    def_irq_handler COMBOPHY_WAKEUP_IRQHandler
    def_irq_handler I2C7_IRQHandler
    def_irq_handler I2C8_IRQHandler
    def_irq_handler I3C4_IRQHandler
    def_irq_handler SDMMC3_IRQHandler
    def_irq_handler LPTIM2_IRQHandler
    def_irq_handler LPTIM3_IRQHandler
    def_irq_handler LPTIM4_IRQHandler
    def_irq_handler LPTIM5_IRQHandler
    def_irq_handler CPU1_SEV_IRQHandler
    def_irq_handler CPU3_SEV_IRQHandler
    def_irq_handler RCC_WAKEUP_IRQHandler
    def_irq_handler SAI4_IRQHandler
    def_irq_handler DTS_IRQHandler
    def_irq_handler TIM11_IRQHandler
    def_irq_handler CPU2_WAKEUP_PIN_IRQHandler
    def_irq_handler USB3DR_BC_IRQHandler
    def_irq_handler USB3DR_IRQHandler
    def_irq_handler UCPD1_IRQHandler
    def_irq_handler SERF_IRQHandler
    def_irq_handler BUSPERFM_IRQHandler
    def_irq_handler RAMCFG_IRQHandler
    def_irq_handler DDRCTRL_IRQHandler
    def_irq_handler DDRPHYC_IRQHandler
    def_irq_handler DFI_ERR_IRQHandler
    def_irq_handler IAC_IRQHandler
    def_irq_handler VDDCPU_VD_IRQHandler
    def_irq_handler VDDCORE_VD_IRQHandler
    def_irq_handler HPDMA1_WKUP_IRQHandler
    def_irq_handler HPDMA2_WKUP_IRQHandler
    def_irq_handler HPDMA3_WKUP_IRQHandler
    def_irq_handler LPDMA_WKUP_IRQHandler
    def_irq_handler UCPD1_VBUS_IRQHandler
    def_irq_handler UCPD1_VSAFE5V_IRQHandler
    def_irq_handler RCC_HSI_FMON_IRQHandler
    def_irq_handler VDDGPU_VD_IRQHandler
    def_irq_handler EXTI1_0_IRQHandler
    def_irq_handler EXTI1_1_IRQHandler
    def_irq_handler EXTI1_2_IRQHandler
    def_irq_handler EXTI1_3_IRQHandler
    def_irq_handler EXTI1_4_IRQHandler
    def_irq_handler EXTI1_5_IRQHandler
    def_irq_handler EXTI1_6_IRQHandler
    def_irq_handler EXTI1_7_IRQHandler
    def_irq_handler EXTI1_8_IRQHandler
    def_irq_handler EXTI1_9_IRQHandler
    def_irq_handler EXTI1_10_IRQHandler
    def_irq_handler EXTI1_11_IRQHandler
    def_irq_handler EXTI1_12_IRQHandler
    def_irq_handler EXTI1_13_IRQHandler
    def_irq_handler EXTI1_14_IRQHandler
    def_irq_handler EXTI1_15_IRQHandler
    def_irq_handler IS2M_IRQHandler
    def_irq_handler DDRPERFM_IRQHandler
