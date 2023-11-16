/****************************************************************************
 * @file     mmu_ARMCA7.c
 * @brief    MMU Configuration for Arm
 *Cortex-A7 Device Series
 * @version  V1.2.0
 * @date     15. May 2019
 *
 * @note
 *
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
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

// Note: You should use the Shareable attribute carefully.
// For cores without coherency logic (such as SCU) marking a region as shareable forces the processor to not cache that
// region regardless of the inner cache settings. Cortex-A versions of RTX use LDREX/STREX instructions relying on Local
// monitors. Local monitors will be used only when the region gets cached, regions that are not cached will use the
// Global Monitor. Some Cortex-A implementations do not include Global Monitors, so wrongly setting the attribute
// Shareable may cause STREX to fail.

// Recall: When the Shareable attribute is applied to a memory region that is not Write-Back, Normal memory, data held
// in this region is treated as Non-cacheable. When SMP bit = 0, Inner WB/WA Cacheable Shareable attributes are treated
// as Non-cacheable. When SMP bit = 1, Inner WB/WA Cacheable Shareable attributes are treated as Cacheable.

// Following MMU configuration is expected
// SCTLR.AFE == 1 (Simplified access permissions model - AP[2:1] define access permissions, AP[0] is an access flag)
// SCTLR.TRE == 0 (TEX remap disabled, so memory type and attributes are described directly by bits in the descriptor)
// Domain 0 is always the Client domain
// Descriptors should place all memory in domain 0

#include "ld.h"
#include "stm32mp157cxx_ca7.h"

#define __TTB_BASE TTB

#define A7_SYSRAM_BASE 0x2FFC0000
#define A7_SYSRAM_SZ 0x00040000 /* 256kB */
#define A7_SYSRAM_1MB_SECTION_BASE 0x2FF00000

#define A7_SRAM1_BASE (0x30000000UL)
#define A7_SRAM2_BASE (0x30020000UL)
#define A7_SRAM3_BASE (0x30040000UL)
#define A7_SRAM4_BASE (0x30050000UL)
#define RETRAM (0x38000000UL)
#define A7_M4VECTOR_BASE RETRAM

// TTB base address
#define TTB_BASE ((uint32_t *)__TTB_BASE)

// L2 table pointers
//----------------------------------------

// The L1 translation table divides the full 4GB address space of a 32-bit core
// into 4096 equally sized sections, each of which describes 1MB of virtual memory space.
// The L1 translation table therefore contains 4096 32-bit (word-sized) entries.
#define TTB_L1_SIZE (0x00004000)
#define TTB_L2_SIZE (0x00000400)

//"Private" peripherals is just the GIC on STM32MP15x
#define PRIVATE_TABLE_L2_BASE_4k (__TTB_BASE + TTB_L1_SIZE)

static uint32_t Sect_Normal;	 // outer & inner wb/wa, non-shareable, executable, rw, domain 0, base addr 0
static uint32_t Sect_Normal_Cod; // outer & inner wb/wa, non-shareable, executable, ro, domain 0, base addr 0
static uint32_t Sect_Normal_RO;	 // as Sect_Normal_Cod, but not executable
static uint32_t Sect_Normal_RW;	 // as Sect_Normal_Cod, but writeable and not executable
static uint32_t Sect_Device_RO;	 // device, non-shareable, non-executable, ro, domain 0, base addr 0
static uint32_t Sect_Device_RW;	 // as Sect_Device_RO, but writeable
static uint32_t Sect_StronglyOrdered;
static uint32_t Sect_Normal_NonCache;

static uint32_t Page_L1_4k = 0x0;	// generic
static uint32_t Page_L1_64k = 0x0;	// generic
static uint32_t Page_4k_Device_RW;	// Shared device, not executable, rw, domain 0
static uint32_t Page_64k_Device_RW; // Shared device, not executable, rw, domain 0

void MMU_CreateTranslationTable(void) {
	mmu_region_attributes_Type region;

	// Create 4GB of faulting entries
	MMU_TTSection(TTB_BASE, 0, 4096, DESCRIPTOR_FAULT);

	section_normal(Sect_Normal, region);
	section_normal_cod(Sect_Normal_Cod, region);
	section_normal_ro(Sect_Normal_RO, region);
	section_normal_rw(Sect_Normal_RW, region);
	section_device_ro(Sect_Device_RO, region);
	section_device_rw(Sect_Device_RW, region);
	section_so(Sect_StronglyOrdered, region);
	section_normal_nc(Sect_Normal_NonCache, region);
	page64k_device_rw(Page_L1_64k, Page_64k_Device_RW, region);
	page4k_device_rw(Page_L1_4k, Page_4k_Device_RW, region);

	// ROM should be Cod (RO), but that seems to interfere with debugger loading an elf file, so setting it to Normal:
	// Todo: Investigate this
	MMU_TTSection(TTB_BASE, A7_CODE, A7_CODE_SZ / 0x100000, Sect_Normal);

	MMU_TTSection(TTB_BASE, A7_RAM, A7_RAM_SZ / 0x100000, Sect_Normal_RW);
	// MMU_TTSection(TTB_BASE, __RAM2_BASE, __RAM2_SZ / 0x100000, Sect_Normal_RW);
	MMU_TTSection(TTB_BASE, A7_HEAP, A7_HEAP_SZ / 0x100000, Sect_Normal_RW);

	//.ddma: non-cacheable
	// Note: section_so is quite a bit faster than section_normal_nc
	MMU_TTSection(TTB_BASE, DMABUF, DMABUF_SZ / 0x100000, Sect_StronglyOrdered);

	//.virtdrive: non-cacheable
	MMU_TTSection(TTB_BASE, VIRTDRIVE, VIRTDRIVE_SZ / 0x100000, Sect_StronglyOrdered);

	//M4 heap/data
	MMU_TTSection(TTB_BASE, M4_RODATA, M4_RODATA_SZ / 0x100000, Sect_StronglyOrdered);
	MMU_TTSection(TTB_BASE, M4_HEAP, M4_HEAP_SZ / 0x100000, Sect_StronglyOrdered);

	//.shared_memory and m4 codespace: 0x30000000, or 0x10000000 as seen by M4
	MMU_TTSection(TTB_BASE, A7_SRAM1_BASE, 1, Sect_Device_RW); // 1MB (actually is only 384kB)

	// M4 vector table (RETRAM: 0x38000000, or 0x00000000 as seen by M4)
	MMU_TTSection(TTB_BASE, A7_M4VECTOR_BASE, 1, Sect_Device_RW); // 1MB (actually is only 64kB)

	//.sysram
	MMU_TTSection(TTB_BASE, A7_SYSRAM_1MB_SECTION_BASE, 1, Sect_StronglyOrdered);

	// Peripheral memory
	// For better security: be more specific and use 4k tables to cover only actual peripherals, as in example file in
	// CMSIS
	MMU_TTSection(TTB_BASE, 0x40000000, 0x10000000 / 0x100000, Sect_Device_RW);
	MMU_TTSection(TTB_BASE, 0x50000000, 0x10000000 / 0x100000, Sect_Device_RW);

	// GIC
	// Only need: 0xA002 0000 - 0xA002 8000, but set 0xA002 0000 - 0XA0012 0000
	MMU_TTSection(TTB_BASE, __get_CBAR(), 1, Sect_Device_RW);

	// How to setup 4k or 64k pages:
	//
	// Each 1Mb section of 64k or 4k pages needs a L2 entry:
	// #define PRIVATE_TABLE_L2_BASE_4k       (__TTB_BASE + TTB_L1_SIZE)
	// #define PERIPHERAL_A_TABLE_L2_BASE_64k (__TTB_BASE + TTB_L1_SIZE + 0x400)
	// #define PERIPHERAL_B_TABLE_L2_BASE_64k (__TTB_BASE + TTB_L1_SIZE + 0x800)
	// #define SYNC_FLAGS_TABLE_L2_BASE_4k    (__TTB_BASE + TTB_L1_SIZE + 0xC00)
	//
	// Then, define all the pages to Fault:
	// MMU_TTPage4k (TTB_BASE, SomeAddressAlignedTo1MB, 256, Page_L1_4k, (uint32_t *)PRIVATE_TABLE_L2_BASE_4k,
	// DESCRIPTOR_FAULT);
	//
	// Then, define just the ones you need to be whatever you need
	// MMU_TTPage4k (TTB_BASE, SomeAddressAlignedto4K, 3, Page_L1_4k, (uint32_t *)PRIVATE_TABLE_L2_BASE_4k,
	// Page_4k_Device_RW);

	/* Set location of level 1 page table
	; 31:14 - Translation table base addr (31:14-TTBCR.N, TTBCR.N is 0 out of reset)
	; 13:7  - 0x0
	; 6     - IRGN[0] 0x1  (Inner WB WA)
	; 5     - NOS     0x0  (Non-shared)
	; 4:3   - RGN     0x01 (Outer WB WA)
	; 2     - IMP     0x0  (Implementation Defined)
	; 1     - S       0x0  (Non-shared)
	; 0     - IRGN[1] 0x0  (Inner WB WA) */
	__set_TTBR0(__TTB_BASE | 0x48);
	__ISB();

	/* Set up domain access control register
	; We set domain 0 to Client and all other domains to No Access.
	; All translation table entries specify domain 0 */
	__set_DACR(1);
	__ISB();
}
