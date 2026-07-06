// MMU setup template for STM32MP2 Cortex-A35.
// Copy this file into your project and edit populate_tables() to match your memory map.
// Ported from 4ms/stm32mp2-baremetal shared/mmu/mmu.cc (verified on STM32MP257 hardware).

#include "drivers/system_reg.hh"
#include "boot/page_table.hh"
#include <stddef.h>
#include <stdint.h>

using namespace mdrivlib;

// TCR register bits:

// T0SZ: bits in Virt address = 64 - T0SZ
#define TCR_T0SZ_48BIT (16ULL << 0) // 48-bit
#define TCR_T0SZ_34BIT (30ULL << 0) // 34-bit
#define TCR_T0SZ_32BIT (32ULL << 0) // 32-bit

// IPS/PS: bits in physical address: 32 + PS*4
#define TCR_IPS_40BIT_EL1 (2ULL << 32) // 0b010 => 40-bit PA (EL1)
#define TCR_PS_40BIT_EL3 (2ULL << 16)  // 0b010 => 40-bit PA (EL3)
#define TCR_IPS_32BIT_EL1 (0ULL << 32) // 0b000 => 32-bit PA (EL1)
#define TCR_PS_32BIT_EL3 (0ULL << 16)  // 0b000 => 32-bit PA (EL3)

// Other bits
#define TCR_TG0_4K (0ULL << 14)			  // TG0: 4 kB granules
#define TCR_SH0_INNER (3ULL << 12)		  // SH0: translation table walks are inner shareable
#define TCR_ORGN0_WBWA (1ULL << 10)		  // ORGN0: translation table walks are outer WB/WA
#define TCR_IRGN0_WBWA (1ULL << 8)		  // IRGN0: translation table walks are inner WB/WA
#define TCR_EPD1_DISABLE_EL1 (1ULL << 23) // disable TTBR1 walks (TTBR0 only valid)

// Page tables: base is 4 x 1GB, then 2MB tables
alignas(4096) MMU::PageTable<1024 * 1024 * 1024, 0x00000000> L0;
alignas(4096) MMU::PageTable<2 * 1024 * 1024, 0x00000000> L1_sram;
alignas(4096) MMU::PageTable<2 * 1024 * 1024, 0x40000000> L1_periphs;
alignas(4096) MMU::PageTable<2 * 1024 * 1024, 0x80000000> L1_ddr1;
alignas(4096) MMU::PageTable<2 * 1024 * 1024, 0xC0000000> L1_ddr2;

static bool is_init = false;

static void populate_tables()
{
	if (get_core_id() != 0)
		return;

	if (is_init)
		return;

	L0.clear();
	L1_sram.clear();
	L1_periphs.clear();
	L1_ddr1.clear();
	L1_ddr2.clear();

	// 4 x 1GB entries
	L0.table_entry(0x00000000, L1_sram);
	L0.table_entry(0x40000000, L1_periphs);
	L0.table_entry(0x80000000, L1_ddr1);
	L0.table_entry(0xC0000000, L1_ddr2);

	// 2MB entries for SYSRAM:
	L1_sram.block_entry(0x0A000000, MMU::MemType::Normal, MMU::AccessRW | MMU::NonSecure);
	L1_sram.block_entry(0x0E000000, MMU::MemType::Normal, MMU::AccessRW);
	L1_sram.block_entry(0x20000000, MMU::MemType::Normal, MMU::AccessRW | MMU::NonSecure | MMU::PrivExecuteNever);
	L1_sram.block_entry(0x30000000, MMU::MemType::Normal, MMU::AccessRW | MMU::PrivExecuteNever);

	// Peripherals
	L1_periphs.fill_block_entries(0x40000000,
								  0x60000000,
								  MMU::MemType::Device,
								  MMU::PrivExecuteNever | MMU::NonShareable | MMU::NonSecure | MMU::AccessRW);

	// DDR:
	L1_ddr1.fill_block_entries(0x80000000, 0xC0000000, MMU::MemType::Normal, MMU::AccessRW);
	L1_ddr2.fill_block_entries(0xC0000000, 0x100000000, MMU::MemType::Normal, MMU::AccessRW);

	is_init = true;
	dsb_sy();
}

extern "C" void mmu_enable()
{
	// If caches/MMU are already enabled, clean+invalidate before changing attributes/tables.
	// This avoids “stale” lines or aliasing surprises
	dcache_civac_all();
	ic_iallu();
	dsb_sy();
	isb();

	populate_tables();

	// Point TTBR0 to the top level page table
	//   TTBR0 -> L0
	write_ttbr0_el1(L0.base());

	write_mair_el1(MMU::MAIR);

	// Translation regime configuration
	constexpr uint64_t tcr_el1 = TCR_T0SZ_34BIT | TCR_TG0_4K | TCR_SH0_INNER | TCR_ORGN0_WBWA | TCR_IRGN0_WBWA |
								 TCR_EPD1_DISABLE_EL1 | TCR_IPS_32BIT_EL1;

	write_tcr_el1(tcr_el1);

	//  Invalidate TLBs for the new regime
	dsb_sy();
	isb();
	tlbi_vmalle1is();
	dsb_sy();
	isb();

	// Enable MMU + caches
	uint64_t sctlr = read_sctlr_el1();
	sctlr |= (SCTLR_M | SCTLR_C | SCTLR_I);
	write_sctlr_el1(sctlr);
	isb();
}

extern "C" void mmu_enable_el3()
{
	dcache_civac_all();
	ic_iallu();
	dsb_sy();
	isb();

	uint64_t sctlr = read_sctlr_el3();
	sctlr &= ~(SCTLR_WXN);
	sctlr &= ~(SCTLR_A);
	sctlr &= ~(SCTLR_SA);
	write_sctlr_el3(sctlr);

	populate_tables();
	asm("dmb st");

	// Point TTBR0 to the top level page table
	write_ttbr0_el3(L0.base());

	// Initialize MAIR_EL3 to have attributes matching MAIR_IDX
	write_mair_el3(MMU::MAIR);

	// Translation regime configuration
	constexpr uint64_t tcr_el3 =
		TCR_T0SZ_34BIT | TCR_TG0_4K | TCR_SH0_INNER | TCR_ORGN0_WBWA | TCR_IRGN0_WBWA | TCR_PS_32BIT_EL3;
	write_tcr_el3(tcr_el3);

	//  Invalidate TLBs for the new regime
	dsb_sy();
	isb();

	tlbi_all_e3();
	dsb_sy();
	isb();

	ic_iallu();
	dsb_sy();
	isb();

	// Enable MMU + caches
	sctlr = read_sctlr_el3();
	sctlr |= SCTLR_M | SCTLR_C | SCTLR_I;
	write_sctlr_el3(sctlr);

	tlbi_all_e3();
	isb();
}
