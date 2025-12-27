/**
  ******************************************************************************
  * @file      startup_stm32mp211dxx_cm33.s
  * @author    Intropack Team
  * @brief     STM32MP211xx devices Cortex-M33 vector table for GCC toolchain.
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
  * Copyright (c) 2024 STMicroelectronics.
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
    .word   Reset_Handler               /* Reset Handler */
    .word   NMI_Handler                 /* NMI Handler */
    .word   HardFault_Handler           /* Hard Fault Handler */
    .word   MemManage_Handler           /* MPU Fault Handler */
    .word   BusFault_Handler            /* Bus Fault Handler */
    .word   UsageFault_Handler          /* Usage Fault Handler */
    .word   SecureFault_Handler         /* Secure Fault Handler */
    .word   0                           /* Reserved */
    .word   0                           /* Reserved */
    .word   0                           /* Reserved */
    .word   SVC_Handler                 /* SVCall Handler */
    .word   DebugMon_Handler            /* Debug Monitor Handler */
    .word   0                           /* Reserved */
    .word   PendSV_Handler              /* PendSV Handler */
    .word   SysTick_Handler             /* SysTick Handler */
  /*******************************************************************************/
  /* External interrupts according to                                            */
  /* "Table 187. interrupt mapping for Cortex®-M33"                              */
  /* in chapitre 26 "interrupt list" of reference document                       */
  /* RM0506 - Reference Manual - STM32MP21xx - advanced ARM-based 32/64-bit MPUs */
  /*******************************************************************************/
    .word   PVD_IRQHandler              /* PVD detector through EXTI */
    .word   PVM_IRQHandler              /* PVM detector through EXTI */
    .word   IWDG3_IRQHandler            /* Independent Watchdog 3 Early wake interrupt */
    .word   IWDG4_IRQHandler            /* Independent Watchdog 4 Early wake interrupt */
    .word   IWDG1_RST_IRQHandler        /* Independent Watchdog 1 Reset through EXTI */
    .word   IWDG2_RST_IRQHandler        /* Independent Watchdog 2 Reset through EXTI */
    .word   IWDG4_RST_IRQHandler        /* Independent Watchdog 4 Reset through EXTI */
    .word   WWDG1_IRQHandler            /* Window Watchdog 1 Early Wakeup interrupt */
    .word   0
    .word   0
    .word   TAMP_IRQHandler              /* Tamper interrupt (include LSECSS interrupts) *upts) */
    .word   RTC_IRQHandler               /* RTC global interrupt */
    .word   TAMP_S_IRQHandler            /* Tamper secure interrupt (include LSECSS interr interrupts)*/
    .word   RTC_S_IRQHandler             /* RTC global secure interrupt */
    .word   RCC_IRQHandler               /* RCC global interrupt */
    .word   EXTI2_0_IRQHandler           /* EXTI Line 0 interrupt */
    .word   EXTI2_1_IRQHandler           /* EXTI Line 1 interrupt */
    .word   EXTI2_2_IRQHandler           /* EXTI Line 2 interrupt */
    .word   EXTI2_3_IRQHandler           /* EXTI Line 3 interrupt */
    .word   EXTI2_4_IRQHandler           /* EXTI Line 4 interrupt */
    .word   EXTI2_5_IRQHandler           /* EXTI Line 5 interrupt */
    .word   EXTI2_6_IRQHandler           /* EXTI Line 6 interrupt */
    .word   EXTI2_7_IRQHandler           /* EXTI Line 7 interrupt */
    .word   EXTI2_8_IRQHandler           /* EXTI Line 8 interrupt */
    .word   EXTI2_9_IRQHandler           /* EXTI Line 9 interrupt */
    .word   EXTI2_10_IRQHandler          /* EXTI Line 10 interrupt */
    .word   EXTI2_11_IRQHandler          /* EXTI Line 11 interrupt */
    .word   EXTI2_12_IRQHandler          /* EXTI Line 12 interrupt */
    .word   EXTI2_13_IRQHandler          /* EXTI Line 13 interrupt */
    .word   EXTI2_14_IRQHandler          /* EXTI Line 14 interrupt */
    .word   EXTI2_15_IRQHandler          /* EXTI Line 15 interrupt */
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
    .word   ICACHE_IRQHandler           /* ICACHE interrupt */
    .word   DCACHE_IRQHandler           /* DCACHE interrupt */
    .word   ADC1_IRQHandler             /* ADC1 interrupt */
    .word   ADC2_IRQHandler             /* ADC2 interrupt */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   TIM1_BRK_IRQHandler         /* TIM1 Break interrupt */
    .word   TIM1_UP_IRQHandler          /* TIM1 Update interrupt */
    .word   TIM1_TRG_COM_IRQHandler     /* TIM1 Trigger and Commutation interrupts */
    .word   TIM1_CC_IRQHandler          /* TIM1 Capture Compare interrupt */
    .word   TIM2_IRQHandler             /* TIM2 global interrupt */
    .word   TIM3_IRQHandler             /* TIM3 global interrupt */
    .word   TIM4_IRQHandler             /* TIM4 global interrupt */
    .word   I2C1_IRQHandler             /* I2C1 Global interrupt */
    .word   I3C1_IRQHandler             /* I3C1 Global interrupt */
    .word   I2C2_IRQHandler             /* I2C2 Global interrupt */
    .word   I3C2_IRQHandler             /* I3C2 Global interrupt */
    .word   SPI1_IRQHandler             /* SPI1 global interrupt */
    .word   SPI2_IRQHandler             /* SPI2 global interrupt */
    .word   USART1_IRQHandler           /* USART1 global interrupt */
    .word   USART2_IRQHandler           /* USART2 global interrupt */
    .word   USART3_IRQHandler           /* USART3 global interrupt */
    .word   0
    .word   TIM8_BRK_IRQHandler         /* TIM8 Break interrupt */
    .word   TIM8_UP_IRQHandler          /* TIM8 Update interrupt */
    .word   TIM8_TRG_COM_IRQHandler     /* TIM8 Trigger & Commutation interrupt */
    .word   TIM8_CC_IRQHandler          /* TIM8 Capture Compare interrupt */
    .word   FMC_IRQHandler              /* FMC Global interrupt */
    .word   SDMMC1_IRQHandler           /* SDMMC1 Global interrupt */
    .word   TIM5_IRQHandler             /* TIM5 Global interrupt */
    .word   SPI3_IRQHandler             /* SPI3 Global interrupt */
    .word   UART4_IRQHandler            /* UART4 global interrupt */
    .word   UART5_IRQHandler            /* UART5 global interrupt */
    .word   TIM6_IRQHandler             /* TIM6 global interrupt */
    .word   TIM7_IRQHandler             /* TIM7 global interrupt */
    .word   ETH1_SBD_IRQHandler         /* ETH1 global interrupt */
    .word   ETH1_PMT_IRQHandler         /* ETH1 Wkup interrupt (PMT) */
    .word   ETH1_LPI_IRQHandler         /* ETH1 LPI interrupt */
    .word   0
    .word   0
    .word   0
    .word   USART6_IRQHandler           /* USART6 global interrupt */
    .word   I2C3_IRQHandler             /* I2C3 Global interrupt */
    .word   I3C3_IRQHandler             /* I3C3 Global interrupt */
    .word   USBH_EHCI_IRQHandler        /* USB Host EHCI Interrupt */
    .word   USBH_OHCI_IRQHandler        /* USB Host OHCI Interrupt */
    .word   DCMI_PSSI_IRQHandler        /* DCMI & PSSI global interrupt */
    .word   CSI2HOST_IRQHandler         /* CSI2 Host controller interrupt */
    .word   0
    .word   0            
    .word   HASH1_IRQHandler            /* Hash1 interrupt */
    .word   0         
    .word   FPU_IRQHandler              /* FPU global interrupt */
    .word   UART7_IRQHandler            /* UART7 global interrupt */
    .word   LPUART1_IRQHandler          /* LPUART1 global interrupt */
    .word   SPI4_IRQHandler             /* SPI4 global interrupt */
    .word   SPI5_IRQHandler             /* SPI5 global interrupt */
    .word   SPI6_IRQHandler             /* SPI6 global interrupt */
    .word   SAI1_IRQHandler             /* SAI1 global interrupt */
    .word   LTDC_IRQHandler             /* LTDC global interrupt */
    .word   LTDC_ER_IRQHandler          /* LTDC global error interrupt */
    .word   LTDC_SEC_IRQHandler         /* LTDC security global interrupt */
    .word   LTDC_SEC_ER_IRQHandler      /* LTDC security global error interrupt */
    .word   SAI2_IRQHandler             /* SAI2 global interrupt */
    .word   OCTOSPI1_IRQHandler         /* OCTOSPI1 global interrupt */
    .word   0
    .word   0       
    .word   LPTIM1_IRQHandler           /* LPTIMER1 global interrupt */
    .word   USBH_WAKEUP_IRQHandler      /* USBH Remote Wake up from USB2PHY1 */
    .word   SPDIFRX_IRQHandler          /* SPDIFRX global interrupt */
    .word   IPCC1_RX_IRQHandler         /* Mailbox 1 RX Occupied interrupt */
    .word   IPCC1_TX_IRQHandler         /* Mailbox 1 TX Free interrupt */
    .word   IPCC1_RX_S_IRQHandler       /* Mailbox 1 RX Occupied secure interrupt */
    .word   IPCC1_TX_S_IRQHandler       /* Mailbox 1 TX Free secure interrupt */
    .word   0            
    .word   0           
    .word   OTG_WAKEUP_IRQHandler       /* USB2 DR Remote Wake up from USB2PHY2 */
    .word   0
    .word   MDF1_FLT0_IRQHandler        /* MDF1 Filter0 Interrupt */
    .word   MDF1_FLT1_IRQHandler        /* MDF1 Filter1 Interrupt */
    .word   MDF1_FLT2_IRQHandler        /* MDF1 Filter2 Interrupt */
    .word   MDF1_FLT3_IRQHandler        /* MDF1 Filter3 Interrupt */
    .word   SAI3_IRQHandler             /* SAI3 global interrupt */
    .word   TIM15_IRQHandler            /* TIM15 global interrupt */
    .word   TIM16_IRQHandler            /* TIM16 global interrupt */
    .word   TIM17_IRQHandler            /* TIM17 global interrupt */
    .word   TIM12_IRQHandler            /* TIM12 global interrupt */
    .word   SDMMC2_IRQHandler           /* SDMMC2 global interrupt */
    .word   DCMIPP_IRQHandler           /* DCMIPP global interrupt */
    .word   nCTIIRQ1_IRQHandler         /* Cortex-M33 CTI interrupt 1 */
    .word   nCTIIRQ2_IRQHandler         /* Cortex-M33 CTI interrupt 2 */
    .word   TIM13_IRQHandler            /* TIM13 global interrupt */
    .word   TIM14_IRQHandler            /* TIM14 global interrupt */
    .word   TIM10_IRQHandler            /* TIM10 global interrupt */
    .word   RNG1_IRQHandler             /* RNG1 interrupt */
    .word   0
    .word   HASH2_IRQHandler            /* Hash2 interrupt */
    .word   SDMMC3_IRQHandler           /* SDMMC3 Global interrupt */
    .word   LPTIM2_IRQHandler           /* LPTIMER2 global interrupt */
    .word   LPTIM3_IRQHandler           /* LPTIMER3 global interrupt */
    .word   LPTIM4_IRQHandler           /* LPTIMER4 global interrupt */
    .word   LPTIM5_IRQHandler           /* LPTIMER5 global interrupt */
    .word   0
    .word   CPU1_SEV_IRQHandler         /* Cortex-A35 Send Event through EXTI */
    .word   RCC_WAKEUP_IRQHandler       /* RCC CPU2 Wake up interrupt */
    .word   SAI4_IRQHandler             /* SAI4 global interrupt */
    .word   DTS_IRQHandler              /* Temperature sensor interrupt */
    .word   TIM11_IRQHandler            /* TIM11 global interrupt */
    .word   CPU2_WAKEUP_PIN_IRQHandler  /* Interrupt for all 6 wake-up enabled by CPU2 */
    .word   OTG_IRQHandler              /* USB2 DR global interrupt */
    .word   RNG2_IRQHandler             /* RNG2 interrupt */
    .word   0
    .word   0
    .word   SERF_IRQHandler             /* SERF global interrupt */
    .word   0
    .word   RAMCFG_IRQHandler           /* RAM configuration global interrupt */
    .word   DDRCTRL_IRQHandler          /* DDRCTRL interrupt */
    .word   DDRPHYC_IRQHandler          /* DDRPHY interrupt (active low) */
    .word   DFI_ERR_IRQHandler          /* DDRPHY DFI error Interrupt */
    .word   IAC_IRQHandler              /* RIF Illegal access Controller interrupt */
    .word   VDDCPU_VD_IRQHandler        /* VDDCPU voltage detector */
    .word   VDDCORE_VD_IRQHandler       /* VDDCORE voltage detector */
    .word   0
    .word   HPDMA1Handler               /* HPDMA1 channel 0 to 15 wake up */
    .word   HPDMA2Handler               /* HPDMA2 channel 0 to 15 wake up */
    .word   HPDMA3Handler               /* HPDMA3 channel 0 to 15 wake up */
    .word   DBG_AUTH_HOST_IRQHandler    /* debugger has written DBG_AUTH_HOST register */
    .word   DBG_AUTH_ACK_IRQHandler     /* debugger has read DBG_AUTH_ACK register */
    .word   RCC_HSI_FMON_IRQHandler     /* HSI Frequency Monitor */
    .word   RCC_MSI_FMON_IRQHandler     /* MSI Frequency Monitor */
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
    .word   0
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
    .word   0
    .word   0
    .word   DDRPERFM_IRQHandler         /* DDR Performance Monitor Interrupt */

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
  def_irq_handler WWDG1_IRQHandler
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
  def_irq_handler ICACHE_IRQHandler
  def_irq_handler DCACHE_IRQHandler
  def_irq_handler ADC1_IRQHandler
  def_irq_handler ADC2_IRQHandler
  def_irq_handler FDCAN_CAL_IRQHandler
  def_irq_handler FDCAN1_IT0_IRQHandler
  def_irq_handler FDCAN2_IT0_IRQHandler
  def_irq_handler FDCAN1_IT1_IRQHandler
  def_irq_handler FDCAN2_IT1_IRQHandler
  def_irq_handler TIM1_BRK_IRQHandler
  def_irq_handler TIM1_UP_IRQHandler
  def_irq_handler TIM1_TRG_COM_IRQHandler
  def_irq_handler TIM1_CC_IRQHandler
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
  def_irq_handler CSI2HOST_IRQHandler
  def_irq_handler HASH1_IRQHandler
  def_irq_handler FPU_IRQHandler
  def_irq_handler UART7_IRQHandler
  def_irq_handler LPUART1_IRQHandler
  def_irq_handler SPI4_IRQHandler
  def_irq_handler SPI5_IRQHandler
  def_irq_handler SPI6_IRQHandler
  def_irq_handler SAI1_IRQHandler
  def_irq_handler LTDC_IRQHandler
  def_irq_handler LTDC_ER_IRQHandler
  def_irq_handler LTDC_SEC_IRQHandler
  def_irq_handler LTDC_SEC_ER_IRQHandler
  def_irq_handler SAI2_IRQHandler
  def_irq_handler OCTOSPI1_IRQHandler
  def_irq_handler LPTIM1_IRQHandler
  def_irq_handler USBH_WAKEUP_IRQHandler
  def_irq_handler SPDIFRX_IRQHandler
  def_irq_handler IPCC1_RX_IRQHandler
  def_irq_handler IPCC1_TX_IRQHandler
  def_irq_handler IPCC1_RX_S_IRQHandler
  def_irq_handler IPCC1_TX_S_IRQHandler
  def_irq_handler OTG_WAKEUP_IRQHandler
  def_irq_handler MDF1_FLT0_IRQHandler
  def_irq_handler MDF1_FLT1_IRQHandler
  def_irq_handler MDF1_FLT2_IRQHandler
  def_irq_handler MDF1_FLT3_IRQHandler
  def_irq_handler SAI3_IRQHandler
  def_irq_handler TIM15_IRQHandler
  def_irq_handler TIM16_IRQHandler
  def_irq_handler TIM17_IRQHandler
  def_irq_handler TIM12_IRQHandler
  def_irq_handler SDMMC2_IRQHandler
  def_irq_handler DCMIPP_IRQHandler
  def_irq_handler nCTIIRQ1_IRQHandler
  def_irq_handler nCTIIRQ2_IRQHandler
  def_irq_handler TIM13_IRQHandler
  def_irq_handler TIM14_IRQHandler
  def_irq_handler TIM10_IRQHandler
  def_irq_handler RNG1_IRQHandler
  def_irq_handler HASH2_IRQHandler
  def_irq_handler SDMMC3_IRQHandler
  def_irq_handler LPTIM2_IRQHandler
  def_irq_handler LPTIM3_IRQHandler
  def_irq_handler LPTIM4_IRQHandler
  def_irq_handler LPTIM5_IRQHandler
  def_irq_handler CPU1_SEV_IRQHandler
  def_irq_handler RCC_WAKEUP_IRQHandler
  def_irq_handler SAI4_IRQHandler
  def_irq_handler DTS_IRQHandler
  def_irq_handler TIM11_IRQHandler
  def_irq_handler CPU2_WAKEUP_PIN_IRQHandler
  def_irq_handler OTG_IRQHandler
  def_irq_handler RNG2_IRQHandler
  def_irq_handler SERF_IRQHandler
  def_irq_handler RAMCFG_IRQHandler
  def_irq_handler DDRCTRL_IRQHandler
  def_irq_handler DDRPHYC_IRQHandler
  def_irq_handler DFI_ERR_IRQHandler
  def_irq_handler IAC_IRQHandler
  def_irq_handler VDDCPU_VD_IRQHandler
  def_irq_handler VDDCORE_VD_IRQHandler
  def_irq_handler HPDMA1Handler
  def_irq_handler HPDMA2Handler
  def_irq_handler HPDMA3Handler
  def_irq_handler DBG_AUTH_HOST_IRQHandler
  def_irq_handler DBG_AUTH_ACK_IRQHandler
  def_irq_handler RCC_HSI_FMON_IRQHandler
  def_irq_handler RCC_MSI_FMON_IRQHandler
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
  def_irq_handler DDRPERFM_IRQHandler
