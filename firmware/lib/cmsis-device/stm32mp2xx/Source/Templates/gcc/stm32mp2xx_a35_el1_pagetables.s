/*******************************************************************************
 * @file    stm32mp2xx_a35_el1_pagetables.s
 * @author  C.ICORD (Intropack Team)
 * @version $VERSION$
 * @date    $DATE$
 * @brief   EL1 Translation page tables for MMU/caches settings
 *
 * LANGUAGE:  ASM ARMv8 Aarch32/Aarch64
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
 * . [MP2_Memory_Map]
 *   Chapter 2 "Memory and bus architecture"
 *   in "RM0457 - Reference Manual"
 *   "STM32MP25xx - advanced ARM-based 32/64-bit MPUs"
 *   Revision 0.3 / 14-Apr-2022
 *   (file "DM00485804 (RM0457) Rev0.3.pdf")
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
/* Pagetables Initialization                                                  */
/*============================================================================*/
        .global  mp2_el1_ttb0_base
        .global  mp2_el1_ttb1_base
        .global  mp2_el1_ttb0_level2
        #ifdef __AARCH64__
        .global  mair_value
        #else
        .global  mair0_value
        .global  mair1_value
        #endif

        .equ XN,               (1<<22)
        .equ PXN,              (1<<21)
        .equ CONTIG,           (1<<20)

        .equ NGLOBAL,          (1<<11)
        .equ AF,               (1<<10) /* Access flag */
        .equ NON_SH,           (0<<8)
        .equ OUTER_SH,         (2<<8)
        .equ INNER_SH,         (3<<8)
        .equ AP2,              (1<<7) /* Read-only flag  */
        .equ AP1,              (1<<6) /* ELx access flag */
        .equ NS,               (1<<5)
        .equ IDX0,             (0<<2)
        .equ IDX1,             (1<<2)
        .equ IDX2,             (2<<2)
        .equ IDX3,             (3<<2)
        .equ IDX4,             (4<<2)
        .equ IDX5,             (5<<2)
        .equ IDX6,             (6<<2)
        .equ IDX7,             (7<<2)
        .equ BLOCK,            (1<<0)
        .equ TABLE,            (3<<0)
        .equ UNMAPPED,         (0<<0)

        .equ OUTER_WT,         (0<<6)
        .equ OUTER_WB,         (1<<6)
        .equ OUTER_NC,         (1<<6)
        .equ OUTER_NONTRANS,   (1<<7)
        .equ OUTER_WRALLOC,    (1<<4)
        .equ OUTER_RDALLOC,    (1<<5)

        /* Device Memory (see [ARMv8_RM DDI0487B.a] B2.7.2 page B2-112) : */
        /* - Device-nGnRnE memory aka (ARMv7) "Strongly Ordered Memory"   */
        /*   "nE" stands for "no Early Write Acknowledgement"             */
        .equ nGnRnE,           0x00
        /* - Device-nGnRE memory aka (ARMv7) "Device Memory"              */
        .equ nGnRE,            0x04
        /* - Device-nGRE memory */
        .equ nGRE,             0x08
        /* - Device-GRE memory */
        .equ GRE,              0x0C

        .equ INNER_WT,         (0<<2)
        .equ INNER_WB,         (1<<2)
        .equ INNER_NC,         (1<<2)
        .equ INNER_NONTRANS,   (1<<3)
        .equ INNER_WRALLOC,    (1<<0)
        .equ INNER_RDALLOC,    (1<<1)

        /* Normal Memory Inner & Outer cacheable (Write-Back Non transient Read & Write Allocate) */
        .equ IO_WBRWA, (OUTER_WB | OUTER_NONTRANS | OUTER_WRALLOC | OUTER_RDALLOC | INNER_WB | INNER_NONTRANS | INNER_WRALLOC | INNER_RDALLOC)
        /* Normal Memory Inner & Outer Non-cacheable */
        .equ IO_NC,    (INNER_NC | OUTER_NC)

        /* Memory attributes for MAIR0/MAIR1 */
        .equ ATTR0,            nGnRnE
        .equ ATTR1,            nGnRE
        .equ ATTR2,            IO_WBRWA
        .equ ATTR3,            IO_NC
        .equ ATTR4,            0
        .equ ATTR5,            0
        .equ ATTR6,            0
        .equ ATTR7,            0

        /* Secure Memory (by default on EL3) */
        .equ SO_MEMORY,           (IDX0 | AP1 | AF)
        .equ DEVICE,              (IDX1 | AP1 | AF)
        .equ MEMORY,              (IDX2 | AP1 | AF)
        .equ NC_MEMORY,           (IDX3 | AP1 | AF)

        /* Secure Memory (for ELx < EL3) */
        .equ SO_ELX_MEMORY,       (IDX0 | AF)
        .equ ELX_DEVICE,          (IDX1 | AF)
        .equ ELX_MEMORY,          (IDX2 | AF)
        .equ NC_ELX_MEMORY,       (IDX3 | AF)

        /* Non-secure Memory (for ELx < EL3) */
        .equ NS_SO_MEMORY,        (SO_ELX_MEMORY | NS)
        .equ NS_DEVICE,           (ELX_DEVICE    | NS)
        .equ NS_MEMORY,           (ELX_MEMORY    | NS)
        .equ NS_NC_MEMORY,        (NC_ELX_MEMORY | NS)

        /* Memory shareability :                                    */
        /* (see [ARMv8_RM DDI0487B.a] D4.5.1 pages D4-2090/D4-2091) */
        /* - for cacheable memory : set to Inner Shareable          */
        .equ SHARED_MEMORY,        (MEMORY    | INNER_SH)
        .equ SHARED_NS_MEMORY,     (NS_MEMORY | INNER_SH)
        .equ SHARED_ELX_MEMORY,    (ELX_MEMORY | INNER_SH)
        /* - for non-cacheable memory : set to Outer Shareable      */
        /*   (see "Note" at page D4-2091 in [ARMv8_RM DDI0487B.a])  */
        .equ SHARED_SO_MEMORY,     (SO_MEMORY  | OUTER_SH)
        .equ SHARED_DEVICE,        (DEVICE     | OUTER_SH)
        .equ SHARED_NC_MEMORY,     (NC_MEMORY  | OUTER_SH)

        .equ SHARED_SO_ELX_MEMORY, (SO_ELX_MEMORY | OUTER_SH)
        .equ SHARED_ELX_DEVICE,    (ELX_DEVICE    | OUTER_SH)
        .equ SHARED_NC_ELX_MEMORY, (NC_ELX_MEMORY | OUTER_SH)

        .equ SHARED_NS_SO_MEMORY,  (NS_SO_MEMORY | OUTER_SH)
        .equ SHARED_NS_DEVICE,     (NS_DEVICE    | OUTER_SH)
        .equ SHARED_NS_NC_MEMORY,  (NS_NC_MEMORY | OUTER_SH)

        /* Aarch64 : Put 64-bit value with correct endianness */
        #ifdef __AARCH64__
        .macro PUT_64B high, low
        .quad (\high << 32) + \low
        .endm
        /* Aarch32 : Put 32-bit values with correct endianness */
        #else
        .macro PUT_64B high, low
        .word \low
        .word \high
        .endm
        #endif

        .align 3
        #ifdef __AARCH64__
mair_value:
        PUT_64B ((ATTR7<<24) | (ATTR6<<16) | (ATTR5<<8) | (ATTR4<<0), (ATTR3<<24) | (ATTR2<<16) | (ATTR1<<8) | (ATTR0<<0))
        #else
mair0_value:
        .word (ATTR3<<24) | (ATTR2<<16) | (ATTR1<<8) | (ATTR0<<0)
mair1_value:
        .word (ATTR7<<24) | (ATTR6<<16) | (ATTR5<<8) | (ATTR4<<0)
        #endif

        /* Create an entry pointing to a next-level table */
        .macro TABLE_ENTRY PA, ATTR
        PUT_64B   \ATTR, ((\PA) + TABLE)
        .endm

        /* Create an entry for a 1GB block */
        .macro BLOCK_1GB PA, ATTR_HI, ATTR_LO
        PUT_64B   \ATTR_HI, ((\PA)  &  0xC0000000)  |  \ATTR_LO  |  BLOCK
        .endm

        /* Create an entry for a 2MB block */
        .macro BLOCK_2MB PA, ATTR_HI, ATTR_LO
        PUT_64B   \ATTR_HI, ((\PA)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        .endm

        /* Create an entry for a 32MB block (using multiple 2MB blocks) */
        .macro BLOCK_32MB PA, ATTR_HI, ATTR_LO
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0000000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0200000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0400000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0600000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0800000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0A00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0C00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x0E00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1000000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1200000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1400000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1600000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1800000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1A00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1C00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        PUT_64B   \ATTR_HI  |  CONTIG, ((\PA  |  0x1E00000)  &  0xFFE00000)  |  \ATTR_LO  |  BLOCK
        .endm

        /* Create an entry for a 1GB invalid block */
        .macro INVALID_1GB PA
        PUT_64B   0, ((\PA)  &  0xC0000000)
        .endm

        /* Create an entry for a 2MB invalid block */
        .macro INVALID_2MB PA
        PUT_64B   0, ((\PA)  &  0xFFE00000)
        .endm

        /* Create invalid entries for 32MB area */
        .macro INVALID_32MB PA
        PUT_64B   0, ((\PA  |  0x0000000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0200000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0400000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0600000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0800000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0A00000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0C00000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x0E00000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1000000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1200000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1400000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1600000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1800000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1A00000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1C00000)  &  0xFFE00000)
        PUT_64B   0, ((\PA  |  0x1E00000)  &  0xFFE00000)
        .endm

/*--------------------------------------------------------*/
/* MP2 EL1 First-level table                              */
/*                                                        */
/*   Entry 0: -> Second-level table "mp2_el1_ttb0_level2" */
/*               (see its description hereafter)          */
/*   Entry 1: -> Block 0x40000000 - 0x7FFFFFFF            */
/*               Shared Strongly Ordered Memory           */
/*   Entry 2: -> Block 0x80000000 - 0xBFFFFFFF            */
/*               (Whole range as (non-)cacheable Memory)  */
/*   Entry 3: -> Block 0xC0000000 - 0xFFFFFFFF            */
/*               (Whole range as non-cacheable Memory)    */
/*--------------------------------------------------------*/
        /* Table base address aligned to 32-byte */
        /* according to TCR_EL1.T0SZ value       */
        .balign 0x20
mp2_el1_ttb0_base:
        TABLE_ENTRY mp2_el1_ttb0_level2, 0
        BLOCK_1GB   0x40000000, 0, SHARED_SO_ELX_MEMORY
        #ifdef ST_NO_DDR
        INVALID_1GB 0x80000000
        INVALID_1GB 0xC0000000
        #else
        #ifdef CACHED_DDR
        BLOCK_1GB   0x80000000, 0, SHARED_ELX_MEMORY
        #else
        BLOCK_1GB   0x80000000, 0, SHARED_NC_ELX_MEMORY
        #endif
        BLOCK_1GB   0xC0000000, 0, SHARED_NC_ELX_MEMORY
        #endif

        /* Table base address aligned to 32-byte */
        /* according to TCR_EL1.T0SZ value       */
        .balign 0x20
mp2_el1_ttb1_base:
        BLOCK_1GB   0x00000000, 0, UNMAPPED
        BLOCK_1GB   0x40000000, 0, UNMAPPED
        BLOCK_1GB   0x80000000, 0, UNMAPPED
        BLOCK_1GB   0xC0000000, 0, UNMAPPED

/*---------------------------------------------------------------------------*/
/* Set memory mapping in [0x0000_0000; 0x3FFF_FFFF] area                     */
/* according to [MP2_Memory_Map]                                             */
/* Second-level table to embed all *RAM areas                                */
/* --> 512 entries (2MB areas) VA = PA                                       */
/*       =   1 for [0x0000_0000; 0x0020_0000[ : ROM (not-cached access)      */
/*       + 127 for [0x0020_0000; 0x1000_0000[ : unused (undefined) memory    */
/*       + 128 for [0x1000_0000; 0x2000_0000[ : PCIE (not-cached access)     */
/*       +   1 for [0x2000_0000; 0x2020_0000[ : *RAMs (not-cached access)    */
/*       + 127 for [0x2020_0000; 0x3000_0000[ : unused (undefined) memory    */
/*       +   1 for [0x3000_0000; 0x3020_0000[ : *RAMs (cached access)        */
/*       + 127 for [0x3020_0000; 0x4000_0000[ : unused (undefined) memory    */
/*---------------------------------------------------------------------------*/
        /* Level 2 table base address aligned to 4096-byte */
        .balign (1<<12)
mp2_el1_ttb0_level2 :
        .set ADDR, 0x000  /* Address counter for blocks */

        /* Range 0x0000_0000 -> 0x001F_FFFF : not-cached access to ROM */
        BLOCK_2MB (ADDR << 20), 0, SHARED_NC_ELX_MEMORY
        .set ADDR, ADDR+2

        /* Range 0x0020_0000 -> 0x0FFF_FFFF : undefined memory */
        .rept ((0x20 - 0x02) / 2)
        INVALID_2MB (ADDR << 20)
        .set ADDR, ADDR+2
        .endr
        .rept ((0x100 - 0x020) / 32)
        INVALID_32MB (ADDR << 20)
        .set ADDR, ADDR+32
        .endr

        /* Range 0x1000_0000 -> 0x1FFF_FFFF : PCIE memory */
        .rept ((0x200 - 0x100) / 32)
        BLOCK_32MB (ADDR << 20), 0, SHARED_NC_ELX_MEMORY
        .set ADDR, ADDR+32
        .endr

        /* Range 0x2000_0000 -> 0x201F_FFFF : not-cached access to all *RAMs */
        BLOCK_2MB (ADDR << 20), 0, SHARED_NC_ELX_MEMORY
        .set ADDR, ADDR+2

        /* Range 0x2020_0000 -> 0x2FFF_FFFF : undefined memory */
        .rept ((0x220 - 0x202) / 2)
        INVALID_2MB (ADDR << 20)
        .set ADDR, ADDR+2
        .endr
        .rept ((0x300 - 0x220) / 32)
        INVALID_32MB (ADDR << 20)
        .set ADDR, ADDR+32
        .endr

        /* Range 0x3000_0000 -> 0x301F_FFFF : cached access to all *RAMs */
        BLOCK_2MB (ADDR << 20), 0, SHARED_ELX_MEMORY
        .set ADDR, ADDR+2

        /* Range 0x3020_0000 -> 0x3FFF_FFFF : undefined memory */
        .rept ((0x320 - 0x302) / 2)
        INVALID_2MB (ADDR << 20)
        .set ADDR, ADDR+2
        .endr
        .rept ((0x400 - 0x320) / 32)
        INVALID_32MB (ADDR << 20)
        .set ADDR, ADDR+32
        .endr
