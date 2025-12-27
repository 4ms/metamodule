/*****************************************************************************
  * @file      startup_stm32mp21xx_m33_ns.s
 * @brief    CMSIS Core Device Startup File for ARM CM33 Device Series
 * @version  V5.00
 * @date     21. december 2017
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

  .syntax unified
  .arch armv7-m

/* select CLEAR BSS during startup */
#define __STARTUP_CLEAR_BSS

  .section .stack
  .align  3
#ifdef __STACK_SIZE
  .equ  Stack_Size, __STACK_SIZE
#else
  .equ  Stack_Size, 0x00000400
#endif
  .globl  __StackTop
  .globl  __StackLimit
__StackLimit:
  .space  Stack_Size
  .size __StackLimit, . - __StackLimit
__StackTop:
  .size __StackTop, . - __StackTop

  .section .heap
  .align  3
#ifdef __HEAP_SIZE
  .equ  Heap_Size, __HEAP_SIZE
#else
  .equ  Heap_Size, 0x00000C00
#endif
  .globl  __HeapBase
  .globl  __HeapLimit
__HeapBase:
  .if Heap_Size
  .space  Heap_Size
  .endif
  .size __HeapBase, . - __HeapBase
__HeapLimit:
  .size __HeapLimit, . - __HeapLimit

  .section .vectors,"a",%progbits
  .align 2
  .globl  __Vectors
__Vectors:
  .long __StackTop                  /* Top of Stack */
  .long Reset_Handler               /* Reset Handler */
  .long NMI_Handler                 /* NMI Handler */
  .long HardFault_Handler           /* Hard Fault Handler */
  .long MemManage_Handler           /* MPU Fault Handler */
  .long BusFault_Handler            /* Bus Fault Handler */
  .long UsageFault_Handler          /* Usage Fault Handler */
  .long 0                           /* Reserved */
  .long 0                           /* Reserved */
  .long 0                           /* Reserved */
  .long 0                           /* Reserved */
  .long SVC_Handler                 /* SVCall Handler */
  .long DebugMon_Handler            /* Debug Monitor Handler */
  .long 0                           /* Reserved */
  .long PendSV_Handler              /* PendSV Handler */
  .long SysTick_Handler             /* SysTick Handler */
  /*******************************************************************************/
  /* External interrupts according to                                            */
  /* "Table 187. interrupt mapping for Cortex®-M33"                              */
  /* in chapitre 26 "interrupt list" of reference document                       */
  /* RM0506 - Reference Manual - STM32MP21xx - advanced ARM-based 32/64-bit MPUs */
  /*******************************************************************************/
  .long PVD_IRQHandler              /* PVD detector through EXTI */
  .long PVM_IRQHandler              /* PVM detector through EXTI */
  .long IWDG3_IRQHandler            /* Independent Watchdog 3 Early wake interrupt */
  .long IWDG4_IRQHandler            /* Independent Watchdog 4 Early wake interrupt */
  .long IWDG1_RST_IRQHandler        /* Independent Watchdog 1 Reset through EXTI */
  .long IWDG2_RST_IRQHandler        /* Independent Watchdog 2 Reset through EXTI */
  .long IWDG4_RST_IRQHandler        /* Independent Watchdog 4 Reset through EXTI */
  .long WWDG1_IRQHandler            /* Window Watchdog 1 Early Wakeup interrupt */
  .long 0
  .long 0
  .long TAMP_IRQHandler              /* Tamper interrupt (include LSECSS interrupts) */
  .long RTC_IRQHandler               /* RTC global interrupt */
  .long TAMP_S_IRQHandler            /* Tamper secure interrupt (include LSECSS interrupts)*/
  .long RTC_S_IRQHandler             /* RTC global secure interrupt */
  .long RCC_IRQHandler               /* RCC global interrupt */
  .long EXTI2_0_IRQHandler           /* EXTI Line 0 interrupt */
  .long EXTI2_1_IRQHandler           /* EXTI Line 1 interrupt */
  .long EXTI2_2_IRQHandler           /* EXTI Line 2 interrupt */
  .long EXTI2_3_IRQHandler           /* EXTI Line 3 interrupt */
  .long EXTI2_4_IRQHandler           /* EXTI Line 4 interrupt */
  .long EXTI2_5_IRQHandler           /* EXTI Line 5 interrupt */
  .long EXTI2_6_IRQHandler           /* EXTI Line 6 interrupt */
  .long EXTI2_7_IRQHandler           /* EXTI Line 7 interrupt */
  .long EXTI2_8_IRQHandler           /* EXTI Line 8 interrupt */
  .long EXTI2_9_IRQHandler           /* EXTI Line 9 interrupt */
  .long EXTI2_10_IRQHandler          /* EXTI Line 10 interrupt */
  .long EXTI2_11_IRQHandler          /* EXTI Line 11 interrupt */
  .long EXTI2_12_IRQHandler          /* EXTI Line 12 interrupt */
  .long EXTI2_13_IRQHandler          /* EXTI Line 13 interrupt */
  .long EXTI2_14_IRQHandler          /* EXTI Line 14 interrupt */
  .long EXTI2_15_IRQHandler          /* EXTI Line 15 interrupt */
  .long HPDMA1_Channel0_IRQHandler  /* HPDMA1 Channel0 interrupt */
  .long HPDMA1_Channel1_IRQHandler  /* HPDMA1 Channel1 interrupt */
  .long HPDMA1_Channel2_IRQHandler  /* HPDMA1 Channel2 interrupt */
  .long HPDMA1_Channel3_IRQHandler  /* HPDMA1 Channel3 interrupt */
  .long HPDMA1_Channel4_IRQHandler  /* HPDMA1 Channel4 interrupt */
  .long HPDMA1_Channel5_IRQHandler  /* HPDMA1 Channel5 interrupt */
  .long HPDMA1_Channel6_IRQHandler  /* HPDMA1 Channel6 interrupt */
  .long HPDMA1_Channel7_IRQHandler  /* HPDMA1 Channel7 interrupt */
  .long HPDMA1_Channel8_IRQHandler  /* HPDMA1 Channel8 interrupt */
  .long HPDMA1_Channel9_IRQHandler  /* HPDMA1 Channel9 interrupt */
  .long HPDMA1_Channel10_IRQHandler /* HPDMA1 Channel10 interrupt */
  .long HPDMA1_Channel11_IRQHandler /* HPDMA1 Channel11 interrupt */
  .long HPDMA1_Channel12_IRQHandler /* HPDMA1 Channel12 interrupt */
  .long HPDMA1_Channel13_IRQHandler /* HPDMA1 Channel13 interrupt */
  .long HPDMA1_Channel14_IRQHandler /* HPDMA1 Channel14 interrupt */
  .long HPDMA1_Channel15_IRQHandler /* HPDMA1 Channel15 interrupt */
  .long HPDMA2_Channel0_IRQHandler  /* HPDMA2 Channel0 interrupt */
  .long HPDMA2_Channel1_IRQHandler  /* HPDMA2 Channel1 interrupt */
  .long HPDMA2_Channel2_IRQHandler  /* HPDMA2 Channel2 interrupt */
  .long HPDMA2_Channel3_IRQHandler  /* HPDMA2 Channel3 interrupt */
  .long HPDMA2_Channel4_IRQHandler  /* HPDMA2 Channel4 interrupt */
  .long HPDMA2_Channel5_IRQHandler  /* HPDMA2 Channel5 interrupt */
  .long HPDMA2_Channel6_IRQHandler  /* HPDMA2 Channel6 interrupt */
  .long HPDMA2_Channel7_IRQHandler  /* HPDMA2 Channel7 interrupt */
  .long HPDMA2_Channel8_IRQHandler  /* HPDMA2 Channel8 interrupt */
  .long HPDMA2_Channel9_IRQHandler  /* HPDMA2 Channel9 interrupt */
  .long HPDMA2_Channel10_IRQHandler /* HPDMA2 Channel10 interrupt */
  .long HPDMA2_Channel11_IRQHandler /* HPDMA2 Channel11 interrupt */
  .long HPDMA2_Channel12_IRQHandler /* HPDMA2 Channel12 interrupt */
  .long HPDMA2_Channel13_IRQHandler /* HPDMA2 Channel13 interrupt */
  .long HPDMA2_Channel14_IRQHandler /* HPDMA2 Channel14 interrupt */
  .long HPDMA2_Channel15_IRQHandler /* HPDMA2 Channel15 interrupt */
  .long HPDMA3_Channel0_IRQHandler  /* HPDMA3 Channel0 interrupt */
  .long HPDMA3_Channel1_IRQHandler  /* HPDMA3 Channel1 interrupt */
  .long HPDMA3_Channel2_IRQHandler  /* HPDMA3 Channel2 interrupt */
  .long HPDMA3_Channel3_IRQHandler  /* HPDMA3 Channel3 interrupt */
  .long HPDMA3_Channel4_IRQHandler  /* HPDMA3 Channel4 interrupt */
  .long HPDMA3_Channel5_IRQHandler  /* HPDMA3 Channel5 interrupt */
  .long HPDMA3_Channel6_IRQHandler  /* HPDMA3 Channel6 interrupt */
  .long HPDMA3_Channel7_IRQHandler  /* HPDMA3 Channel7 interrupt */
  .long HPDMA3_Channel8_IRQHandler  /* HPDMA3 Channel8 interrupt */
  .long HPDMA3_Channel9_IRQHandler  /* HPDMA3 Channel9 interrupt */
  .long HPDMA3_Channel10_IRQHandler /* HPDMA3 Channel10 interrupt */
  .long HPDMA3_Channel11_IRQHandler /* HPDMA3 Channel11 interrupt */
  .long HPDMA3_Channel12_IRQHandler /* HPDMA3 Channel12 interrupt */
  .long HPDMA3_Channel13_IRQHandler /* HPDMA3 Channel13 interrupt */
  .long HPDMA3_Channel14_IRQHandler /* HPDMA3 Channel14 interrupt */
  .long HPDMA3_Channel15_IRQHandler /* HPDMA3 Channel15 interrupt */
  .long ICACHE_IRQHandler           /* ICACHE interrupt */
  .long DCACHE_IRQHandler           /* DCACHE interrupt */
  .long ADC1_IRQHandler             /* ADC1 interrupt */
  .long ADC2_IRQHandler             /* ADC2 interrupt */
  .long FDCAN_CAL_IRQHandler        /* FDCAN CCU interrupt */
  .long FDCAN1_IT0_IRQHandler       /* FDCAN1 interrupt 0 */
  .long FDCAN2_IT0_IRQHandler       /* FDCAN2 interrupt 0 */
  .long FDCAN1_IT1_IRQHandler       /* FDCAN1 interrupt 1 */
  .long FDCAN2_IT1_IRQHandler       /* FDCAN2 interrupt 1 */
  .long TIM1_BRK_IRQHandler         /* TIM1 Break interrupt */
  .long TIM1_UP_IRQHandler          /* TIM1 Update interrupt */
  .long TIM1_TRG_COM_IRQHandler     /* TIM1 Trigger and Commutation interrupts */
  .long TIM1_CC_IRQHandler          /* TIM1 Capture Compare interrupt */
  .long TIM2_IRQHandler             /* TIM2 global interrupt */
  .long TIM3_IRQHandler             /* TIM3 global interrupt */
  .long TIM4_IRQHandler             /* TIM4 global interrupt */
  .long I2C1_IRQHandler             /* I2C1 Global interrupt */
  .long I3C1_IRQHandler             /* I3C1 Global interrupt */
  .long I2C2_IRQHandler             /* I2C2 Global interrupt */
  .long I3C2_IRQHandler             /* I3C2 Global interrupt */
  .long SPI1_IRQHandler             /* SPI1 global interrupt */
  .long SPI2_IRQHandler             /* SPI2 global interrupt */
  .long USART1_IRQHandler           /* USART1 global interrupt */
  .long USART2_IRQHandler           /* USART2 global interrupt */
  .long USART3_IRQHandler           /* USART3 global interrupt */
  .long VDEC_IRQHandler             /* VDEC global interrupt */
  .long TIM8_BRK_IRQHandler         /* TIM8 Break interrupt */
  .long TIM8_UP_IRQHandler          /* TIM8 Update interrupt */
  .long TIM8_TRG_COM_IRQHandler     /* TIM8 Trigger & Commutation interrupt */
  .long TIM8_CC_IRQHandler          /* TIM8 Capture Compare interrupt */
  .long FMC_IRQHandler              /* FMC Global interrupt */
  .long SDMMC1_IRQHandler           /* SDMMC1 Global interrupt */
  .long TIM5_IRQHandler             /* TIM5 Global interrupt */
  .long SPI3_IRQHandler             /* SPI3 Global interrupt */
  .long UART4_IRQHandler            /* UART4 global interrupt */
  .long UART5_IRQHandler            /* UART5 global interrupt */
  .long TIM6_IRQHandler             /* TIM6 global interrupt */
  .long TIM7_IRQHandler             /* TIM7 global interrupt */
  .long ETH1_SBD_IRQHandler         /* ETH1 global interrupt */
  .long ETH1_PMT_IRQHandler         /* ETH1 Wkup interrupt (PMT) */
  .long ETH1_LPI_IRQHandler         /* ETH1 LPI interrupt */
  .long ETH2_SBD_IRQHandler         /* ETH2 global interrupt */
  .long ETH2_PMT_IRQHandler         /* ETH2 Wkup interrupt (PMT) */
  .long ETH2_LPI_IRQHandler         /* ETH2 LPI interrupt */
  .long USART6_IRQHandler           /* USART6 global interrupt */
  .long I2C3_IRQHandler             /* I2C3 Global interrupt */
  .long I3C3_IRQHandler             /* I3C3 Global interrupt */
  .long USBH_EHCI_IRQHandler        /* USB Host EHCI Interrupt */
  .long USBH_OHCI_IRQHandler        /* USB Host OHCI Interrupt */
  .long DCMI_PSSI_IRQHandler        /* DCMI & PSSI global interrupt */
  .long CSI2HOST_IRQHandler         /* CSI2 Host controller interrupt */
  .long DSI_IRQHandler              /* DSI Host controller global interrupt */
  .long CRYP1_IRQHandler            /* Crypto1 interrupt */
  .long HASH1_IRQHandler            /* Hash1 interrupt */
  .long PKA_IRQHandler              /* PKA interrupt */
  .long FPU_IRQHandler              /* FPU global interrupt */
  .long UART7_IRQHandler            /* UART7 global interrupt */
  .long LPUART1_IRQHandler          /* LPUART1 global interrupt */
  .long SPI4_IRQHandler             /* SPI4 global interrupt */
  .long SPI5_IRQHandler             /* SPI5 global interrupt */
  .long SPI6_IRQHandler             /* SPI6 global interrupt */
  .long SAI1_IRQHandler             /* SAI1 global interrupt */
  .long LTDC_IRQHandler             /* LTDC global interrupt */
  .long LTDC_ER_IRQHandler          /* LTDC global error interrupt */
  .long LTDC_SEC_IRQHandler         /* LTDC security global interrupt */
  .long LTDC_SEC_ER_IRQHandler      /* LTDC security global error interrupt */
  .long SAI2_IRQHandler             /* SAI2 global interrupt */
  .long OCTOSPI1_IRQHandler         /* OCTOSPI1 global interrupt */
  .long OCTOSPI2_IRQHandler         /* OCTOSPI2 global interrupt */
  .long OTFDEC1_IRQHandler          /* OTFDEC1 interrupt */
  .long LPTIM1_IRQHandler           /* LPTIMER1 global interrupt */
  .long USBH_WAKEUP_IRQHandler      /* USBH Remote Wake up from USB2PHY1 */
  .long SPDIFRX_IRQHandler          /* SPDIFRX global interrupt */
  .long IPCC1_RX_IRQHandler         /* Mailbox 1 RX Occupied interrupt */
  .long IPCC1_TX_IRQHandler         /* Mailbox 1 TX Free interrupt */
  .long IPCC1_RX_S_IRQHandler       /* Mailbox 1 RX Occupied secure interrupt */
  .long IPCC1_TX_S_IRQHandler       /* Mailbox 1 TX Free secure interrupt */
  .long SAES_IRQHandler             /* Secure AES */
  .long CRYP2_IRQHandler            /* Crypto2 interrupt */
  .long OTG_WAKEUP_IRQHandler       /* USB2 DR Remote Wake up from USB2PHY2 */
  .long GPU_IRQHandler              /* GPU global interrupt */
  .long MDF1_FLT0_IRQHandler        /* MDF1 Filter0 Interrupt */
  .long MDF1_FLT1_IRQHandler        /* MDF1 Filter1 Interrupt */
  .long MDF1_FLT2_IRQHandler        /* MDF1 Filter2 Interrupt */
  .long MDF1_FLT3_IRQHandler        /* MDF1 Filter3 Interrupt */
  .long SAI3_IRQHandler             /* SAI3 global interrupt */
  .long TIM15_IRQHandler            /* TIM15 global interrupt */
  .long TIM16_IRQHandler            /* TIM16 global interrupt */
  .long TIM17_IRQHandler            /* TIM17 global interrupt */
  .long TIM12_IRQHandler            /* TIM12 global interrupt */
  .long SDMMC2_IRQHandler           /* SDMMC2 global interrupt */
  .long DCMIPP_IRQHandler           /* DCMIPP global interrupt */
  .long nCTIIRQ1_IRQHandler         /* Cortex-M33 CTI interrupt 1 */
  .long nCTIIRQ2_IRQHandler         /* Cortex-M33 CTI interrupt 2 */
  .long TIM13_IRQHandler            /* TIM13 global interrupt */
  .long TIM14_IRQHandler            /* TIM14 global interrupt */
  .long TIM10_IRQHandler            /* TIM10 global interrupt */
  .long RNG1_IRQHandler             /* RNG1 interrupt */
  .long ADF1_FLT_IRQHandler         /* ADF1 Filter Interrupt */
  .long HASH2_IRQHandler            /* Hash2 interrupt */
  .long SDMMC3_IRQHandler           /* SDMMC3 Global interrupt */
  .long LPTIM2_IRQHandler           /* LPTIMER2 global interrupt */
  .long LPTIM3_IRQHandler           /* LPTIMER3 global interrupt */
  .long LPTIM4_IRQHandler           /* LPTIMER4 global interrupt */
  .long LPTIM5_IRQHandler           /* LPTIMER5 global interrupt */
  .long OTFDEC2_IRQHandler          /* OTFDEC2 interrupt */
  .long CPU1_SEV_IRQHandler         /* Cortex-A35 Send Event through EXTI */
  .long RCC_WAKEUP_IRQHandler       /* RCC CPU2 Wake up interrupt */
  .long SAI4_IRQHandler             /* SAI4 global interrupt */
  .long DTS_IRQHandler              /* Temperature sensor interrupt */
  .long TIM11_IRQHandler            /* TIM11 global interrupt */
  .long CPU2_WAKEUP_PIN_IRQHandler  /* Interrupt for all 6 wake-up enabled by CPU2 */
  .long OTG_IRQHandler              /* USB2 DR global interrupt */
  .long RNG2_IRQHandler             /* RNG2 interrupt */
  .long UCPD1_IRQHandler            /* USB PD interrupt */
  .long 0
  .long SERF_IRQHandler             /* SERF global interrupt */
  .long BUSPERFM_IRQHandler         /* BUS Performance Monitor Interrupt */
  .long RAMCFG_IRQHandler           /* RAM configuration global interrupt */
  .long DDRCTRL_IRQHandler          /* DDRCTRL interrupt */
  .long DDRPHYC_IRQHandler          /* DDRPHY interrupt (active low) */
  .long DFI_ERR_IRQHandler          /* DDRPHY DFI error Interrupt */
  .long IAC_IRQHandler              /* RIF Illegal access Controller interrupt */
  .long VDDCPU_VD_IRQHandler        /* VDDCPU voltage detector */
  .long VDDCORE_VD_IRQHandler       /* VDDCORE voltage detector */
  .long 0
  .long HPDMA1Handler               /* HPDMA1 channel 0 to 15 wake up */
  .long HPDMA2Handler               /* HPDMA2 channel 0 to 15 wake up */
  .long HPDMA3Handler               /* HPDMA3 channel 0 to 15 wake up */
  .long UCPD1_VBUS_IRQHandler       /* USB TypeC VBUS valid */
  .long UCPD1_VSAFE5V_IRQHandler    /* USB TypeC VSAFE5V valid */
  .long RCC_HSI_FMON_IRQHandler     /* HSI Frequency Monitor */
  .long VDDGPU_VD_IRQHandler        /* VDDGPU voltage detector */
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long EXTI1_0_IRQHandler          /* EXTI1 Line 0 interrupt */
  .long EXTI1_1_IRQHandler          /* EXTI1 Line 1 interrupt */
  .long EXTI1_2_IRQHandler          /* EXTI1 Line 2 interrupt */
  .long EXTI1_3_IRQHandler          /* EXTI1 Line 3 interrupt */
  .long EXTI1_4_IRQHandler          /* EXTI1 Line 4 interrupt */
  .long EXTI1_5_IRQHandler          /* EXTI1 Line 5 interrupt */
  .long EXTI1_6_IRQHandler          /* EXTI1 Line 6 interrupt */
  .long EXTI1_7_IRQHandler          /* EXTI1 Line 7 interrupt */
  .long EXTI1_8_IRQHandler          /* EXTI1 Line 8 interrupt */
  .long EXTI1_9_IRQHandler          /* EXTI1 Line 9 interrupt */
  .long EXTI1_10_IRQHandler         /* EXTI1 Line 10 interrupt */
  .long EXTI1_11_IRQHandler         /* EXTI1 Line 11 interrupt */
  .long EXTI1_12_IRQHandler         /* EXTI1 Line 12 interrupt */
  .long EXTI1_13_IRQHandler         /* EXTI1 Line 13 interrupt */
  .long EXTI1_14_IRQHandler         /* EXTI1 Line 14 interrupt */
  .long EXTI1_15_IRQHandler         /* EXTI1 Line 15 interrupt */
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long 0
  .long IS2M_IRQHandler             /* IS2M fault detect */
  .long 0
  .long DDRPERFM_IRQHandler         /* DDR Performance Monitor Interrupt */

  .size __Vectors, . - __Vectors

  .text
  .thumb
  .thumb_func
  .align  2
  .globl  Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
/* set stack pointer */
  ldr   r0, =__StackTop
  mov   sp, r0



/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */
#ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
  ldr r4, =__copy_table_start__
  ldr r5, =__copy_table_end__

.L_loop0:
  cmp r4, r5
  bge .L_loop0_done
  ldr r1, [r4]
  ldr r2, [r4, #4]
  ldr r3, [r4, #8]

.L_loop0_0:
  subs  r3, #4
  ittt  ge
  ldrge r0, [r1, r3]
  strge r0, [r2, r3]
  bge .L_loop0_0

  adds  r4, #12
  b .L_loop0

.L_loop0_done:
#else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
  ldr r1, =__etext
  ldr r2, =__data_start__
  ldr r3, =__data_end__

.L_loop1:
  cmp r2, r3
  ittt  lt
  ldrlt r0, [r1], #4
  strlt r0, [r2], #4
  blt .L_loop1
#endif /*__STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
  ldr r3, =__zero_table_start__
  ldr r4, =__zero_table_end__

.L_loop2:
  cmp r3, r4
  bge .L_loop2_done
  ldr r1, [r3]
  ldr r2, [r3, #4]
  movs  r0, 0

.L_loop2_0:
  subs  r2, #4
  itt ge
  strge r0, [r1, r2]
  bge .L_loop2_0

  adds  r3, #8
  b .L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
  ldr r1, =__bss_start__
  ldr r2, =__bss_end__

  movs  r0, 0
.L_loop3:
  cmp r1, r2
  itt lt
  strlt r0, [r1], #4
  blt .L_loop3
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

#ifndef __NO_SYSTEM_INIT
  bl  SystemInit
#endif

/* Call static constructors */
  bl __libc_init_array

/* Call the application's entry point.*/
  bl main

  .pool
  .size Reset_Handler, . - Reset_Handler

/* Weak_Handler_Check:
 * weak function called by Default_Handler
 * and which can be overridden by a more complex one
 * which reports current Cortex-M Exception processing status (from ICSR register)
 * This can't be done directly from Default_Handler because the way it is used
 * in vectors table makes overriding impossible
 */
  .align  1
  .thumb_func
  .weak Weak_Handler_Check
  .type Weak_Handler_Check, %function
Weak_Handler_Check:
  b .
  .size Weak_Handler_Check, . - Weak_Handler_Check

  .align  1
  .thumb_func
  .weak Default_Handler
  .type Default_Handler, %function
Default_Handler:
  b Weak_Handler_Check
  .size Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
  .macro  def_irq_handler handler_name
  .weak \handler_name
  .set  \handler_name, Default_Handler
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
  def_irq_handler CSI2HOST_IRQHandler
  def_irq_handler DSI_IRQHandler
  def_irq_handler CRYP1_IRQHandler
  def_irq_handler HASH1_IRQHandler
  def_irq_handler PKA_IRQHandler
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
  def_irq_handler OCTOSPI2_IRQHandler
  def_irq_handler OTFDEC1_IRQHandler
  def_irq_handler LPTIM1_IRQHandler
  def_irq_handler USBH_WAKEUP_IRQHandler
  def_irq_handler SPDIFRX_IRQHandler
  def_irq_handler IPCC1_RX_IRQHandler
  def_irq_handler IPCC1_TX_IRQHandler
  def_irq_handler IPCC1_RX_S_IRQHandler
  def_irq_handler IPCC1_TX_S_IRQHandler
  def_irq_handler SAES_IRQHandler
  def_irq_handler CRYP2_IRQHandler
  def_irq_handler OTG_WAKEUP_IRQHandler
  def_irq_handler GPU_IRQHandler
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
  def_irq_handler ADF1_FLT_IRQHandler
  def_irq_handler HASH2_IRQHandler
  def_irq_handler SDMMC3_IRQHandler
  def_irq_handler LPTIM2_IRQHandler
  def_irq_handler LPTIM3_IRQHandler
  def_irq_handler LPTIM4_IRQHandler
  def_irq_handler LPTIM5_IRQHandler
  def_irq_handler OTFDEC2_IRQHandler
  def_irq_handler CPU1_SEV_IRQHandler
  def_irq_handler RCC_WAKEUP_IRQHandler
  def_irq_handler SAI4_IRQHandler
  def_irq_handler DTS_IRQHandler
  def_irq_handler TIM11_IRQHandler
  def_irq_handler CPU2_WAKEUP_PIN_IRQHandler
  def_irq_handler OTG_IRQHandler
  def_irq_handler RNG2_IRQHandler
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
  def_irq_handler HPDMA1Handler
  def_irq_handler HPDMA2Handler
  def_irq_handler HPDMA3Handler
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

  .end
