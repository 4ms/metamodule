#include "cmsis_gcc.h"
#include <stddef.h>
#include <stdint.h>

// ==========================
// Region definitions (STM32MP25x typical)
// ==========================
#define DDR_BASE 0x80000000ULL
#define DDR_SIZE 0x40000000ULL // 1 GiB

// Coarse peripheral/device window.
#define PERIPH_BASE 0x40000000ULL
#define PERIPH_SIZE 0x40000000ULL // 1 GiB -> 0x4000_0000..0x7FFF_FFFF

// ROM checks SYSRAM branch targets within [0x0E00_0000, 0x0E03_FFFF]
// Map one 2 MiB block starting at 0x0E00_0000 as Normal cacheable.
// #define IRAM2M_BASE 0x0E000000ULL // 2 MiB aligned
// #define IRAM2M_SIZE 0x00200000ULL // 2 MiB

// ==========================
// AArch64 stage-1 descriptor bits
// ==========================
#define DESC_VALID (1ULL << 0)
#define DESC_TABLE (1ULL << 1) // for table descriptors
#define DESC_BLOCK (0ULL << 1) // for block descriptors at L1/L2

#define PTE_AF (1ULL << 10)
#define PTE_SH_INNER (3ULL << 8)  // Inner Shareable
#define PTE_AP_RW_EL1 (0ULL << 6) // EL1 RW, EL0 no access
#define PTE_NS (1ULL << 5)		  // Non-secure

#define PTE_ATTRINDX(n) ((uint64_t)(n) << 2) // bits[4:2]

// MAIR encodings:
//  AttrIdx0: Device-nGnRnE = 0x00
//  AttrIdx1: Normal WBWA   = 0xFF
#define MAIR_ATTR_DEVICE_nGnRnE 0x00ULL
#define MAIR_ATTR_NORMAL_WBWA 0xFFULL

// ==========================
// TCR_EL1 (4KB granule, 48-bit VA, 40-bit PA)
// ==========================
#define TCR_TG0_4K (0ULL << 14)
#define TCR_SH0_INNER (3ULL << 12)
#define TCR_ORGN0_WBWA (1ULL << 10)
#define TCR_IRGN0_WBWA (1ULL << 8)
#define TCR_EPD1_DISABLE (1ULL << 23) // disable TTBR1 walks
#define TCR_T0SZ_48BIT (16ULL << 0)	  // 48-bit VA => T0SZ=16
#define TCR_IPS_40BIT (2ULL << 32)	  // 0b010 => 40-bit PA

// SCTLR_EL1
#define SCTLR_M (1ULL << 0)
#define SCTLR_C (1ULL << 2)
#define SCTLR_I (1ULL << 12)

// ==========================
// Page tables (4KB aligned)
// L0 -> L1 -> (optional) L2 for VA[0..1GiB)
// ==========================
static uint64_t tt_l0[512] __attribute__((aligned(4096)));
static uint64_t tt_l1[512] __attribute__((aligned(4096)));
static uint64_t tt_l2_low[512] __attribute__((aligned(4096))); // backs L1[0] (VA 0..1GiB)

// --------------------------
// System register helpers
// --------------------------
static inline void dsb_sy(void) {
	__asm__ volatile("dsb sy" ::: "memory");
}
static inline void isb(void) {
	__asm__ volatile("isb" ::: "memory");
}

static inline void write_mair_el1(uint64_t v) {
	__asm__ volatile("msr mair_el1, %0" : : "r"(v) : "memory");
}
static inline void write_tcr_el1(uint64_t v) {
	__asm__ volatile("msr tcr_el1, %0" : : "r"(v) : "memory");
}
static inline void write_ttbr0_el1(uint64_t v) {
	__asm__ volatile("msr ttbr0_el1, %0" : : "r"(v) : "memory");
}

static inline uint64_t read_sctlr_el1(void) {
	uint64_t v;
	__asm__ volatile("mrs %0, sctlr_el1" : "=r"(v));
	return v;
}
static inline void write_sctlr_el1(uint64_t v) {
	__asm__ volatile("msr sctlr_el1, %0" : : "r"(v) : "memory");
}

static inline void tlbi_vmalle1is(void) {
	__asm__ volatile("tlbi vmalle1is" ::: "memory");
}
static inline void ic_iallu(void) {
	__asm__ volatile("ic iallu" ::: "memory");
}

// Clean+invalidate all data cache to PoC
static inline void dcache_civac_all(void) {
	// Iterate by set/way using CCSIDR. This is the standard ARM pattern.
	// Assumes data cache is at least present at EL1. Safe even if D-cache is off.
	uint64_t clidr;
	__asm__ volatile("mrs %0, clidr_el1" : "=r"(clidr));

	for (unsigned level = 0; level < 7; level++) {
		unsigned ctype = (clidr >> (level * 3)) & 0x7U;
		if (ctype < 2)
			continue; // no data/unified cache at this level

		uint64_t csselr = (uint64_t)(level << 1); // select data/unified
		__asm__ volatile("msr csselr_el1, %0" : : "r"(csselr));
		isb();

		uint64_t ccsidr;
		__asm__ volatile("mrs %0, ccsidr_el1" : "=r"(ccsidr));

		unsigned line_len = ((ccsidr & 0x7) + 4); // log2(words) + 2 => log2(bytes)
		unsigned ways = ((ccsidr >> 3) & 0x3FF) + 1;
		unsigned sets = ((ccsidr >> 13) & 0x7FFF) + 1;

		// way_shift = 32 - log2(ways)
		unsigned way_shift = 32;
		unsigned tmp = ways - 1;
		while (tmp) {
			way_shift--;
			tmp >>= 1;
		}

		for (unsigned way = 0; way < ways; way++) {
			for (unsigned set = 0; set < sets; set++) {
				uint64_t sw = ((uint64_t)level << 1) | ((uint64_t)set << line_len) | ((uint64_t)way << way_shift);
				__asm__ volatile("dc cisw, %0" : : "r"(sw));
			}
		}
	}

	dsb_sy();
}

static void zero_tables(void) {
	for (size_t i = 0; i < 512; i++) {
		tt_l0[i] = 0;
		tt_l1[i] = 0;
		tt_l2_low[i] = 0;
	}
}

static void map_l1_block(uint64_t va, uint64_t pa, uint64_t attr) {
	// L1 index: VA[38:30] (1 GiB)
	const uint64_t idx = (va >> 30) & 0x1FFULL;
	tt_l1[idx] = (pa & 0xFFFFFC0000000ULL) | attr;
}

static void map_l2_block_low_2m(uint64_t va, uint64_t pa, uint64_t attr) {
	// L2 index: VA[29:21] (2 MiB) within the L2 table that backs L1[0] (VA 0..1GiB)
	const uint64_t idx = (va >> 21) & 0x1FFULL;
	tt_l2_low[idx] = (pa & 0xFFFFFFE00000ULL) | attr;
}

// ==========================
// Complete map + enable
// ==========================
void MMU_CreateTranslationTable(void) {
	// If U-Boot left caches/MMU enabled, clean+invalidate before changing attributes/tables.
	// This avoids “stale” lines or aliasing surprises when you flip to your own map. :contentReference[oaicite:5]{index=5}
	dcache_civac_all();
	ic_iallu();
	dsb_sy();
	isb();

	const uint64_t attr_normal = DESC_VALID | DESC_BLOCK | PTE_ATTRINDX(1) | // MAIR idx 1: Normal WBWA
								 PTE_SH_INNER | PTE_AF | PTE_AP_RW_EL1 | PTE_NS;

	const uint64_t attr_device = DESC_VALID | DESC_BLOCK | PTE_ATTRINDX(0) | // MAIR idx 0: Device-nGnRnE
								 PTE_AF | PTE_AP_RW_EL1 | PTE_NS;

	zero_tables();

	// L0[0] -> L1
	tt_l0[0] = ((uint64_t)tt_l1) | DESC_VALID | DESC_TABLE;

	// L1[0] -> L2 for VA 0..1GiB so we can place a precise SRAM mapping in low space.
	tt_l1[0] = ((uint64_t)tt_l2_low) | DESC_VALID | DESC_TABLE;

	// SRAM/SYSRAM region (2 MiB window at 0x0E00_0000) cacheable
	// map_l2_block_low_2m(IRAM2M_BASE, IRAM2M_BASE, attr_normal);

	// Peripherals 0x4000_0000..0x7FFF_FFFF as Device
	map_l1_block(PERIPH_BASE, PERIPH_BASE, attr_device);

	// DDR 1GiB @ 0x8000_0000 as Normal cacheable (you execute here)
	map_l1_block(DDR_BASE, DDR_BASE, attr_normal);

	dsb_sy();

	// MAIR: idx0 Device, idx1 Normal WBWA
	const uint64_t mair = (MAIR_ATTR_DEVICE_nGnRnE << (8 * 0)) | (MAIR_ATTR_NORMAL_WBWA << (8 * 1));
	write_mair_el1(mair);

	// TCR: 4KB granule, inner shareable, WBWA, 48-bit VA, 40-bit PA, TTBR1 disabled
	const uint64_t tcr = TCR_T0SZ_48BIT | TCR_TG0_4K | TCR_SH0_INNER | TCR_ORGN0_WBWA | TCR_IRGN0_WBWA |
						 TCR_EPD1_DISABLE | TCR_IPS_40BIT;
	write_tcr_el1(tcr);

	// TTBR0 -> L0
	write_ttbr0_el1((uint64_t)tt_l0);

	__DSB();
	isb();

	// Invalidate TLBs for the new regime
	tlbi_vmalle1is();
	dsb_sy();
	isb();

	// Enable MMU + caches
	uint64_t sctlr = read_sctlr_el1();
	sctlr |= (SCTLR_M | SCTLR_C | SCTLR_I);
	write_sctlr_el1(sctlr);
	isb();
}
