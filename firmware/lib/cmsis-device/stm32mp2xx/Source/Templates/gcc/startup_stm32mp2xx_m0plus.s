/**
  ******************************************************************************
  * @file      startup_stm32mp2xx_m0plus.s
  * @author    Intropack Team
  * @brief     STM32MP2xx devices Cortex-M0+ vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branch to main in the C library (which eventually
  *                  calls main()).
  *            After its reset the Cortex-M0+ processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/**
 * @brief  This is the code called when the processor first
 *         starts execution following a reset event. Only the absolutely
 *         necessary set is performed, after which the application
 *         supplied main() routine is called.
 * @param  None
 * @retval None
*/

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM : *
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

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application entry point.*/
  bl main

LoopForever:
    b LoopForever

.size Reset_Handler, .-Reset_Handler

    .section .text.Weak_Handler_Check,"ax",%progbits
/* Weak_Handler_Check:
 * weak function called by Default_Handler
 * and which can be overridden by a more complex one
 * which reports current Cortex-M Exception processing status (from ICSR register)
 * This cannot be done directly from Default_Handler because the way it is used
 * in vector table makes overriding impossible
 * For an example of Weak_Handler_Check() override, see STM32MP257CXX_FPGA or STM32MP257CXX_EMU BSP
 */
  .align 1
  .thumb_func
  .weak Weak_Handler_Check
  .type Weak_Handler_Check, %function
Weak_Handler_Check:
Infinite_Loop:
  b Infinite_Loop
  .size Weak_Handler_Check, . - Weak_Handler_Check

/**
 * @brief  This is the code called when the processor receives an unexpected interrupt.
 *         This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
  bl Weak_Handler_Check
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The STM32MP2xx Cortex-M0+ vector table. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object

g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler

  /*******************************************************************************/
  /* External interrupts according to                                            */
  /* "Table 232. interrupt mapping for Cortex-M0+"                               */
  /* in chapitre 31 "interrupt list" of reference document                       */
  /* RM0457 - Reference Manual - STM32MP25xx - advanced ARM-based 32/64-bit MPUs */
  /* file "DM00485804 (RM0457) Rev0.3.pdf" (Revision 0.3 / 14-Apr-2022)          */
  /*******************************************************************************/

  .word  IWDG5_IRQHandler        /* Independent Watchdog 5 Early interrupt */
  .word  WWDG2_IRQHandler        /* Window Watchdog 2 Early Wakeup interrupt */
  .word  TAMP_IRQHandler         /* Tamper interrupt */
  .word  0
  .word  0
  .word  EXTI2_L_IRQHandler      /* EXTI2 lines 0 to 7 interrupt */
  .word  EXTI2_H_IRQHandler      /* EXTI2 lines 8 to 15 interrupt */
  .word  LPDMA_Channel0_IRQHandler   /* LPDMA Channel0 interrupt */
  .word  LPDMA_Channel1_IRQHandler   /* LPDMA Channel1 interrupt */
  .word  LPDMA_Channel2_IRQHandler   /* LPDMA Channel2 interrupt */
  .word  LPDMA_Channel3_IRQHandler   /* LPDMA Channel3 interrupt */
  .word  LPUART1_IRQHandler      /* LPUART1 global interrupt */
  .word  SPI8_IRQHandler         /* SPI8 global interrupt */
  .word  IPCC2_RX_IRQHandler     /* Mailbox 2 RX Occupied interrupt */
  .word  IPCC2_TX_IRQHandler     /* Mailbox 2 TX Free interrupt */
  .word  I2C8_IRQHandler         /* I2C8 global interrupt */
  .word  I3C4_IRQHandler         /* I3C4 global interrupt */
  .word  0
  .word  LPTIM3_IRQHandler       /* LPTIMER3 global interrupt */
  .word  LPTIM4_IRQHandler       /* LPTIMER4 global interrupt */
  .word  LPTIM5_IRQHandler       /* LPTIMER5 global interrupt */
  .word  HSEM_IRQHandler         /* HSEM non-secure interrupt */
  .word  0
  .word  ADF1_FLT_IRQHandler     /* ADF1 Filter global interrupt */
  .word  0
  .word  CPU1_SEV_IRQHandler     /* Cortex-A35 Send Event through EXTI2 */
  .word  CPU2_SEV_IRQHandler     /* Cortex-M33 Send Event through EXTI2 */
  .word  VDDCPU_VD_IRQHandler    /* VDDCPU voltage detector */
  .word  VDDCORE_VD_IRQHandler   /* VDDCORE voltage detector */
  .word  0
  .word  CTI_IRQ0_IRQHandler     /* CTI IRQ0 */
  .word  CTI_IRQ1_IRQHandler     /* CTI IRQ1 */

  .size g_pfnVectors, .-g_pfnVectors

/*******************************************************************************
 * Provide weak aliases for each Exception handler to the Default_Handler.
 * As they are weak aliases, any function with the same name will override
 * this definition.
 *******************************************************************************/
/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers 
 */
  .macro	def_irq_handler handler_name
  .weak \handler_name
  .thumb_set \handler_name, Default_Handler
  .endm

  def_irq_handler NMI_Handler
  def_irq_handler HardFault_Handler
  def_irq_handler SVC_Handler
  def_irq_handler PendSV_Handler
  def_irq_handler SysTick_Handler
  def_irq_handler IWDG5_IRQHandler
  def_irq_handler WWDG2_IRQHandler
  def_irq_handler TAMP_IRQHandler
  def_irq_handler EXTI2_L_IRQHandler
  def_irq_handler EXTI2_H_IRQHandler
  def_irq_handler LPDMA_Channel0_IRQHandler
  def_irq_handler LPDMA_Channel1_IRQHandler
  def_irq_handler LPDMA_Channel2_IRQHandler
  def_irq_handler LPDMA_Channel3_IRQHandler
  def_irq_handler LPUART1_IRQHandler
  def_irq_handler SPI8_IRQHandler
  def_irq_handler IPCC2_RX_IRQHandler
  def_irq_handler IPCC2_TX_IRQHandler
  def_irq_handler I2C8_IRQHandler
  def_irq_handler I3C4_IRQHandler
  def_irq_handler LPTIM3_IRQHandler
  def_irq_handler LPTIM4_IRQHandler
  def_irq_handler LPTIM5_IRQHandler
  def_irq_handler HSEM_IRQHandler
  def_irq_handler ADF1_FLT_IRQHandler
  def_irq_handler CPU1_SEV_IRQHandler
  def_irq_handler CPU2_SEV_IRQHandler
  def_irq_handler VDDCPU_VD_IRQHandler
  def_irq_handler VDDCORE_VD_IRQHandler
  def_irq_handler CTI_IRQ0_IRQHandler
  def_irq_handler CTI_IRQ1_IRQHandler

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
