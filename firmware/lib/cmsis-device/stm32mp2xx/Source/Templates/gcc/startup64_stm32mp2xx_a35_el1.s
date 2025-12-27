/*******************************************************************************
 * @file    startup64_stm32mp2xx_a35_el1.s
 * @author  Christophe ICORD (Intropack Team)
 * @version $VERSION$
 * @date    $DATE$
 * @brief   64-bit Cortex-A35 experimental start sequence
 *          when switching from EL3 to EL1 in Aarch64 execution state
 *          for single-core or cores in AMP mode
 *
 * LANGUAGE:  ASM ARMv8 Aarch64
 *
 * REFERENCE DOCUMENTS :
 *
 * . [A35_TRM]
 *   "Arm Cortex-A35 Processor"
 *   "Technical Reference Manual / 100236_0100_00_en"
 *   Revision: r1p0 / Issue 0100-00 / 28-Feb-2019
 *   (file cortex_a35_trm_100236_0100_00_en.pdf)
 *
 * . [ARM_DAI_0527A] Application Note
 *   "Bare-metal Boot Code for ARMv8-a Processors"
 *   ARM DAI 0527A -- Version 1.0 -- 31/03/2017
 *   (file DAI0527A_baremetal_boot_code_for_ARMv8_A_processors.pdf)
 *
 * . [ARMv8_RM DDI0487B.a]
 *   "ARM Architecture Reference Manual - ARMv8, for ARMv8-A architecture profile"
 *   (file DDI0487B_a_armv8_arm.pdf)
 *
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
**/

/*============================================================================*/
/* EL1 Vector table                                                           */
/*============================================================================*/
        .section ARM_VECTORS, "ax", %progbits
        // Weakly-import test-defined handlers.  The weak import means that if
        // a test does not define the handler then the default one will be
        // used.
        .weak el1_curr_el_sp0_sync_vector
        .weak el1_curr_el_sp0_irq_vector
        .weak el1_curr_el_sp0_fiq_vector
        .weak el1_curr_el_sp0_serror_vector
        .weak el1_curr_el_spx_sync_vector
        .weak el1_curr_el_spx_irq_vector
        .weak el1_curr_el_spx_fiq_vector
        .weak el1_curr_el_spx_serror_vector
        .weak el1_lower_el_aarch64_sync_vector
        .weak el1_lower_el_aarch64_irq_vector
        .weak el1_lower_el_aarch64_fiq_vector
        .weak el1_lower_el_aarch64_serror_vector
        .weak el1_lower_el_aarch32_sync_vector
        .weak el1_lower_el_aarch32_irq_vector
        .weak el1_lower_el_aarch32_fiq_vector
        .weak el1_lower_el_aarch32_serror_vector

        // Start of vectors
        .balign 0x800

        // Current EL with SP0
_el1_vector_table:
        .global _el1_vector_table
el1_curr_el_sp0_sync:
        // Branch to the weakly-imported test-defined handler.  If the test
        // does not define a handler then this instruction behaves like a NOP.
        b       el1_curr_el_sp0_sync_vector

        // Default code when a test does not define a replacement handler
        b       el1_curr_el_sp0_sync

        // Ensure next vector is aligned to the correct boundary
        .balign 0x80
el1_curr_el_sp0_irq:
        b       el1_curr_el_sp0_irq_vector
        b       el1_curr_el_sp0_irq

        .balign 0x80
el1_curr_el_sp0_fiq:
        b       el1_curr_el_sp0_fiq_vector
        b       el1_curr_el_sp0_fiq

        .balign 0x80
el1_curr_el_sp0_serror:
        b       el1_curr_el_sp0_serror_vector
        b       el1_curr_el_sp0_serror

        .balign 0x80
        // Current EL with SPx
el1_curr_el_spx_sync:
        // Simple exception handler (nested interrupts not allowed) :
        // see [ARM 100933_0100_en]
        // - stack all corruptible registers (x0-x15 & x29-x30)
        stp     x0,  x1,  [sp, #-16]!
        stp     x2,  x3,  [sp, #-16]!
        stp     x4,  x5,  [sp, #-16]!
        stp     x6,  x7,  [sp, #-16]!
        stp     x8,  x9,  [sp, #-16]!
        stp     x10, x11, [sp, #-16]!
        stp     x12, x13, [sp, #-16]!
        stp     x14, x15, [sp, #-16]!
        stp     x29, x30, [sp, #-16]!
        // - call C IRQ handler
        bl      el1_curr_el_spx_sync_vector
        // - restore all corruptible registers (x0-x15 & x29-x30)
        ldp     x29, x30, [sp], #16
        ldp     x14, x15, [sp], #16
        ldp     x12, x13, [sp], #16
        ldp     x10, x11, [sp], #16
        ldp     x8,  x9,  [sp], #16
        ldp     x6,  x7,  [sp], #16
        ldp     x4,  x5,  [sp], #16
        ldp     x2,  x3,  [sp], #16
        ldp     x0,  x1,  [sp], #16
        eret

        .balign 0x80
el1_curr_el_spx_irq:
        // Simple exception handler (nested interrupts not allowed) :
        // see [ARM 100933_0100_en]
        // - stack all corruptible registers (x0-x15 & x29-x30)
        stp     x0,  x1,  [sp, #-16]!
        stp     x2,  x3,  [sp, #-16]!
        stp     x4,  x5,  [sp, #-16]!
        stp     x6,  x7,  [sp, #-16]!
        stp     x8,  x9,  [sp, #-16]!
        stp     x10, x11, [sp, #-16]!
        stp     x12, x13, [sp, #-16]!
        stp     x14, x15, [sp, #-16]!
        stp     x29, x30, [sp, #-16]!
        // - call C IRQ handler
        bl      el1_curr_el_spx_irq_vector
        // - restore all corruptible registers (x0-x15 & x29-x30)
        ldp     x29, x30, [sp], #16
        ldp     x14, x15, [sp], #16
        ldp     x12, x13, [sp], #16
        ldp     x10, x11, [sp], #16
        ldp     x8,  x9,  [sp], #16
        ldp     x6,  x7,  [sp], #16
        ldp     x4,  x5,  [sp], #16
        ldp     x2,  x3,  [sp], #16
        ldp     x0,  x1,  [sp], #16
        eret

        .balign 0x80
el1_curr_el_spx_fiq:
        // Simple exception handler (nested interrupts not allowed) :
        // see [ARM 100933_0100_en]
        // - stack all corruptible registers (x0-x15 & x29-x30)
        stp     x0,  x1,  [sp, #-16]!
        stp     x2,  x3,  [sp, #-16]!
        stp     x4,  x5,  [sp, #-16]!
        stp     x6,  x7,  [sp, #-16]!
        stp     x8,  x9,  [sp, #-16]!
        stp     x10, x11, [sp, #-16]!
        stp     x12, x13, [sp, #-16]!
        stp     x14, x15, [sp, #-16]!
        stp     x29, x30, [sp, #-16]!
        // - call C IRQ handler
        bl      el1_curr_el_spx_fiq_vector
        // - restore all corruptible registers (x0-x15 & x29-x30)
        ldp     x29, x30, [sp], #16
        ldp     x14, x15, [sp], #16
        ldp     x12, x13, [sp], #16
        ldp     x10, x11, [sp], #16
        ldp     x8,  x9,  [sp], #16
        ldp     x6,  x7,  [sp], #16
        ldp     x4,  x5,  [sp], #16
        ldp     x2,  x3,  [sp], #16
        ldp     x0,  x1,  [sp], #16
        eret

        .balign 0x80
el1_curr_el_spx_serror:
        // Simple exception handler (nested interrupts not allowed) :
        // see [ARM 100933_0100_en]
        // - stack all corruptible registers (x0-x15 & x29-x30)
        stp     x0,  x1,  [sp, #-16]!
        stp     x2,  x3,  [sp, #-16]!
        stp     x4,  x5,  [sp, #-16]!
        stp     x6,  x7,  [sp, #-16]!
        stp     x8,  x9,  [sp, #-16]!
        stp     x10, x11, [sp, #-16]!
        stp     x12, x13, [sp, #-16]!
        stp     x14, x15, [sp, #-16]!
        stp     x29, x30, [sp, #-16]!
        // - call C IRQ handler
        bl      el1_curr_el_spx_serror_vector
        // - restore all corruptible registers (x0-x15 & x29-x30)
        ldp     x29, x30, [sp], #16
        ldp     x14, x15, [sp], #16
        ldp     x12, x13, [sp], #16
        ldp     x10, x11, [sp], #16
        ldp     x8,  x9,  [sp], #16
        ldp     x6,  x7,  [sp], #16
        ldp     x4,  x5,  [sp], #16
        ldp     x2,  x3,  [sp], #16
        ldp     x0,  x1,  [sp], #16
        eret

        .balign 0x80
        // Lower EL using AArch64
el1_lower_el_aarch64_sync:
        b       el1_lower_el_aarch64_sync_vector
        b       el1_lower_el_aarch64_sync

        .balign 0x80
el1_lower_el_aarch64_irq:
        b       el1_lower_el_aarch64_irq_vector
        b       el1_lower_el_aarch64_irq

        .balign 0x80
el1_lower_el_aarch64_fiq:
        b       el1_lower_el_aarch64_fiq_vector
        b       el1_lower_el_aarch64_fiq

        .balign 0x80
el1_lower_el_aarch64_serror:
        b       el1_lower_el_aarch64_serror_vector
        b       el1_lower_el_aarch64_serror

        .balign 0x80
        // Lower EL using AArch32
el1_lower_el_aarch32_sync:
        b       el1_lower_el_aarch32_sync_vector
        b       el1_lower_el_aarch32_sync

        .balign 0x80
el1_lower_el_aarch32_irq:
        b       el1_lower_el_aarch32_irq_vector
        b       el1_lower_el_aarch32_irq

        .balign 0x80
el1_lower_el_aarch32_fiq:
        b       el1_lower_el_aarch32_fiq_vector
        b       el1_lower_el_aarch32_fiq

        .balign 0x80
el1_lower_el_aarch32_serror:
        b       el1_lower_el_aarch32_serror_vector
        b       el1_lower_el_aarch32_serror
       .balign 0x80

/*============================================================================*/
/* EL3-EL1 Interface parameters                                               */
/*============================================================================*/
        .section boot, "ax", %progbits
_el3_el1_interface:
        .global _el3_el1_interface
        /* Fill EL3-EL1 interface following structure :      */
        /* - EL1 Aarch64 entry-point (_ResetA35_EL1) address */
        .word   _ResetA35_EL1
        /* - EL1 Vector table address                        */
        .word   _el1_vector_table
        /* - EL3-EL1 interface identification in ASCII format */
        /*   set to "EL3L" ("EL3 Launcher") by default        */
        .word   0x454C334C
        /* - EL1 Aarch64 security state for A35_1 core only (AMP mode) */
        /*   . Code for switching A35_1 to EL1 Aarch64 secure state    */
        #ifdef A35_NON_SECURE
        .word   0xAA6405E1
        #else
        .word   0xAA645EC1
        #endif /* A35_NON_SECURE */
        /* - Memory start address of EL1 A35_0 (AMP) / A35_* (SMP) application */
        .word   __MEM_START__
        /* - Memory end address of EL1 A35_0 (AMP) / A35_* (SMP) application */
        .word   EL1_STACK_BASE
        /* - EL3-EL1 interface location for A35_1 core (AMP mode) */
        #ifdef A35_X_IN_AMP_MODE
        .word   EL1_STACK_BASE
        /*   or padding word to fill memory (SMP mode)            */
        #else
        .word   0x00000000
        #endif /* A35_X_IN_AMP_MODE */
        .balign 0x20

/*============================================================================*/
/* Reset Handler (EL1 entry_point)                                            */
/*============================================================================*/
        .extern el1_main
        .extern mp2_el1_ttb0_base
        .extern mp2_el1_ttb1_base
        .extern mair_value
        .global _ResetA35_EL1
_ResetA35_EL1:
/*============================================================================*/
/* Initialize registers                                                       */
/*============================================================================*/
        /* Initialize the register bank */
        /* (not really needed, but done to run valid instructions) */
        mov     x0,  xzr
        mov     x1,  xzr
        mov     x2,  xzr
        mov     x3,  xzr
        mov     x4,  xzr
        mov     x5,  xzr
        mov     x6,  xzr
        mov     x7,  xzr
        mov     x8,  xzr
        mov     x9,  xzr
        mov     x10, xzr
        mov     x11, xzr
        mov     x12, xzr
        mov     x13, xzr
        mov     x14, xzr
        mov     x15, xzr
        mov     x16, xzr
        mov     x17, xzr
        mov     x18, xzr
        mov     x19, xzr
        mov     x20, xzr
        mov     x21, xzr
        mov     x22, xzr
        mov     x23, xzr
        mov     x24, xzr
        mov     x25, xzr
        mov     x26, xzr
        mov     x27, xzr
        mov     x28, xzr
        mov     x29, xzr
        mov     x30, xzr

        /* Clear link and status registers */
        /* The EL1 stack pointer register is not writable at EL1 level */
        /* (see C5.2.13 in [ARM DDI 0487B.a])   */
        /* It shall be initialized in upper EL. */
        msr     ELR_EL1,  x0
        msr     SPSR_EL1, x0

/*============================================================================*/
/* Disable MMU in case it was left enabled from an earlier run                */
/* This does not need to be done from a cold reset                            */
/*============================================================================*/
        mrs     x0, SCTLR_EL1
        bic     x0, x0, #0x1
        msr     SCTLR_EL1, x0

/*============================================================================*/
/* Set up Vector Base Address                                                 */
/*============================================================================*/
        ldr     x1, =_el1_vector_table
        msr     VBAR_EL1, x1

/*============================================================================*/
/* Initialize EL1 stack according to EL1 stack base                           */
/* Note stack must be 8-byte aligned.                                         */
/*============================================================================*/
        /* Get EL1 stack base (shall be 8-byte aligned = 0x40-multiple) */
        ldr     x0, =EL1_STACK_BASE
        /* Set EL1 stack pointer (SP) */
        mov     sp, x0
        isb     sy

/*============================================================================*/
/* Enable NEON and Floating Point (see 5.4 at page 50 in [ARM_DAI_0527A])     */
/* "In AArch64, you do not need to enable access to the NEON
    and FP registers.
    However, access to the NEON and FP registers can still be trapped"        */
/* Note : Some settings have been completed by EL3 start-up process           */
/*============================================================================*/
        /* - Check FP presence by reading ID_AA64PFR0_EL1 bits [19:16] "FP"  */
        /*   see [A35_TRM] B2.54 "AArch64 Processor Feature Register 0, EL1" */
        mrs     x0, ID_AA64PFR0_EL1
        ubfx    x0, x0, #16, #4
        /* - Skip FP initialization when FP not present */
        cbnz    x0, after_neon

        /* - Disable access trapping in EL1 and EL0           */
        /*   by setting CPACR_EL1 bits [21:20] "FPEN" to 0b11 */
        /*   see [A35_TRM] B2.31 "Architectural Feature Access Control Register, EL1" */
        mov     x1, #(0x3 << 20)
        msr     CPACR_EL1, x1
        isb     sy

        /* - Initialize FPU registers */
        fmov    d0,  xzr
        fmov    d1,  xzr
        fmov    d2,  xzr
        fmov    d3,  xzr
        fmov    d4,  xzr
        fmov    d5,  xzr
        fmov    d6,  xzr
        fmov    d7,  xzr
        fmov    d8,  xzr
        fmov    d9,  xzr
        fmov    d10, xzr
        fmov    d11, xzr
        fmov    d12, xzr
        fmov    d13, xzr
        fmov    d14, xzr
        fmov    d15, xzr
        fmov    d16, xzr
        fmov    d17, xzr
        fmov    d18, xzr
        fmov    d19, xzr
        fmov    d20, xzr
        fmov    d21, xzr
        fmov    d22, xzr
        fmov    d23, xzr
        fmov    d24, xzr
        fmov    d25, xzr
        fmov    d26, xzr
        fmov    d27, xzr
        fmov    d28, xzr
        fmov    d29, xzr
        fmov    d30, xzr
        fmov    d31, xzr
after_neon:

/*============================================================================*/
/* EL1 MMU Configuration (a bit different from EL3 MMU one)                   */
/* (see component stm32mp2xx_a35_el1_pagetables.s for details)                */
/*                                                                            */
/* Configure system to use extended v6 format page tables,                    */
/* with Access Flag Enable (AFE) bit disabled.                                */
/* Set translation table bases                                                */
/*============================================================================*/
        /* Configure Translation tables by setting properly                   */
        /* "Translation Control Register (EL1)" (see B2.94 in [A35_TRM]) :    */
        /* - bits   [5:0] "T0SZ" = 0b10_0000 = 32                             */
        /*          <=>   "The region size is 2^(64-T0SZ) = 2^32 bytes = 4GB" */
        /* - bit      [6] "RES0" = 0b0                                        */
        /* - bit      [7] "EPD0" = 0b0                                        */
        /*            <=> "Perform translation table walks using TTBR0_EL1."  */
        /* - bits   [9:8] "IRGN0" = 0b01                                      */
        /*            <=> "Normal memory, Inner Write-Back Read-Allocate      */
        /*                 Write-Allocate Cacheable"                          */
        /* - bits [11:10] "ORGN0" = 0b01                                      */
        /*            <=> "Normal memory, Outer Write-Back Read-Allocate      */
        /*                 Write-Allocate Cacheable"                          */
        /* - bits [13:12] "SH0" = 0b11                                        */
        /*            <=> "Inner Shareable"                                   */
        /* - bits [15:14] "TG0" = 0b00                                        */
        /*            <=> "Granule size for the TTBR0_EL1 is 4KB"             */
        /* - bits [21:16] "T1SZ" = 0b10_0000 = 32                             */
        /*            <=> "The region size is 2(64-T1SZ) = 2^32 bytes = 4GB"  */
        /* - bit     [22] "A1" = 0b0                                          */
        /*            <=> "TTBR0_EL1.ASID defines the ASID"                   */
        /* - bit     [23] "EPD1" = 0b1                                        */
        /*            <=> "A TLB miss on an address that is translated        */
        /*                 using TTBR1_EL1 generates a Translation fault.     */
        /*                 No translation table walk is performed."           */
        /* - bits [25:24] "IRGN1" = 0b01                                      */
        /*            <=> "Normal memory, Inner Write-Back Read-Allocate      */
        /*                 Write-Allocate Cacheable"                          */
        /* - bits [27:26] "ORGN1" = 0b01                                      */
        /*            <=> "Normal memory, Outer Write-Back Read-Allocate      */
        /*                 Write-Allocate Cacheable"                          */
        /* - bits [29:28] "SH1" = 0b11                                        */
        /*            <=> "Inner Shareable"                                   */
        /* - bits [31:30] "TG1" = 0b10                                        */
        /*            <=> "Granule size for the TTBR1_EL1 is 4KB."            */
        /* - bits [34:32] "IPS" = 0b000                                       */
        /*            <=> "Intermediate Physical Address Size is 32 bits,4GB."*/
        /* - bit     [35] "RES0" = 0b0                                        */
        /* - bit     [36] "AS" = 0b0                                          */
        /*            <=> "ASID Size is 8 bits."                              */
        /* - bit     [37] "TBI0" = 0b0                                        */
        /*            <=> "Top Byte used in the address calculation."         */
        /* - bit     [38] "TBI1" = 0b0                                        */
        /*            <=> "Top Byte used in the address calculation."         */
        /* - bits [63:39] "RES0" = 0b0000_0000_0000_0000_0000_0000_0          */
        /* ==> 0x0000_0000_B5A0_3520 */

        ldr     x1, =0xB5A03520
        msr     TCR_EL1, x1

        ldr     x1, mair_value
        msr     MAIR_EL1, x1

        adr     x0, mp2_el1_ttb0_base
        msr     TTBR0_EL1, x0
        adr     x0, mp2_el1_ttb1_base
        msr     TTBR1_EL1, x0
        isb

/*============================================================================*/
/* Invalidate EL1 MMU                                                         */
/*============================================================================*/
        /* Invalidate all TLB at EL1                                   */
        /* (see C5.5.1 "TLB Invalidate All, EL1" in [ARM DDI 0487B.a]) */
        tlbi    vmalle1
        /* Make sure translation table writes have drained into memory */
        /* and the TLB invalidation is complete.                       */
        dsb     sy
        isb

        /* Invalidate instruction cache and branch predictor      */
        /* (see C5.3.10 "Instruction Cache Invalidate All to PoU" */
        /*  in [ARM DDI 0487B.a])                                 */
        ic      iallu
        isb

/*============================================================================*/
/* SMP (Symmetric Multi-Processing) mode Management                           */
/* Disable Symmetric Multi-Processing by clearing                             */
/* CPUECTLR_EL1 bit 6 "SMPEN : Enable hardware management of data coherency"  */
/* (see B2.37 "CPU Extended Control Register, EL1" in [A35_TRM]               */
/* Possible at EL1 once ACTLR_EL3.CPUECTLR_EL1 access control bit 1 has been  */
/* set to 0b1 (see code of EL3 launcher)                                      */
/*============================================================================*/
        mrs     x0, S3_1_C15_C2_1
        bic     x0, x0, #(1<<6)
        msr     S3_1_C15_C2_1, x0
        isb

/*============================================================================*/
/* Enable data & instruction caches, branch predictor and MMU at EL1          */
/* by setting SCTLR_EL1 bits 0 "M", 2 "C" and 12 "I"                          */
/* (see B2.90 "System Control Register, EL1" in [A35_TRM])                    */
/* Note : Branch prediction not controllable on A35 (bit 11 = res1)           */
/*============================================================================*/
        mrs     x0, SCTLR_EL1
        bic     x0, x0, #(0x1 << 3)    /* Disable Stack Strict Alignment */
        orr     x0, x0, #(0x1 << 0)    /* enable MMU before scatter loading */
        orr     x0, x0, #(0x1 << 2)    /* enable D Cache        */
        orr     x0, x0, #(0x1 << 12)   /* enable I Cache        */
        msr     SCTLR_EL1, x0
        isb

/*============================================================================*/
/* Finalize startup processing completed by master core                       */
/*============================================================================*/
        /* Initialize data */
        /* - keep initialization of bss section to zero */
        ldr     x0, =__bss_start__
        ldr     x1, =__bss_end__
        sub     x2, x1, x0
        mov     x1, #0
        bl      memset
        /* - remove semi-hosting configuration : not needed */
//        bl      initialise_monitor_handles
        /* - remove __libc_init_array/__libc_fini_array : not needed (no C++ feature) */
//        ldr     x0, =__libc_fini_array
//        bl      atexit
//        bl      __libc_init_array
        dsb     sy
        isb

        /* Branch to main function */
        bl      main
loop_master_core:
        wfi
        isb
        b       loop_master_core
