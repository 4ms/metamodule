// Self-extracting boot stub for the MetaModule firmware image.
//
// MP1-Boot loads this stub (with its embedded LZ4-compressed payload) into
// the FWBUFFER region (0xCC000040) and jumps to _start, exactly as it would
// boot the application directly.
//
// The payload is the complete multi-record uimg (A7 + M4 segments) that
// elf_to_uimg.py produces. This stub:
//   1. LZ4-decompresses it to a staging area in DDR (0xD0000000)
//   2. Verifies the CRC32 of the decompressed image
//   3. Walks the uimg records, copying each payload to its load address
//      (mirroring BootMediaLoader::load_image in mp1-boot)
//   4. Jumps to the entry point found in the kernel-type record
//
// On entry, interrupts are masked and MMU is off. Then we enable the MMU
// with a flat 1:1 section table (DDR cacheable, everything else Device).
// Before jumping to the app we clean the data cache and return the CPU
// to the same state mp1-boot hands us: MMU off, D-cache off/clean,
// I-cache on/invalidated.

#include "lz4_crc32.h"
#include <stdint.h>

// STAGING is overridable so tests can host-compile this file (see test/)
#ifndef STAGING
#define STAGING ((uint8_t *)0xD0000000)
#endif

// L1 translation table location: the _TTB region from system/linker/memory.ld
// (16KB-aligned). The app builds its own tables there later, after it takes over.
#define TTB_ADDR 0xC0100000u

// Implemented in start.S (kept out of this file so tests can host-compile it)
void mmu_on(uint32_t ttb_addr);
void __attribute__((noreturn)) mmu_off_and_jump(uint32_t entry);

// Boot splash over SPI4 (splash.c). Compiled out of host tests via SELFEXTRACT_NO_SPLASH.
#ifndef SELFEXTRACT_NO_SPLASH
void splash_show(void);
#else
static inline void splash_show(void) {}
#endif

// Flat 1MB-section table: virtual == physical for the whole 4GB space.
//   DDR (0xC0000000-0xE0000000): Normal cacheable, executable
//   SYSRAM at 0x2FF00000: Normal non-cacheable, executable (mp1-boot's exception vectors)
//   everything else: Device (peripherals, SRAM/RETRAM for M4 firmware)
static void fill_translation_table(void) {
	volatile uint32_t *ttb = (volatile uint32_t *)TTB_ADDR;
	for (uint32_t i = 0; i < 4096; i++) {
		uint32_t base = i << 20;
		uint32_t desc;
		if (i >= 0xC00 && i < 0xE00)
			desc = base | 0x1C0E; // section, TEX=001, AP=11, C, B
		else if (i == 0x2FF)
			desc = base | 0x1C02; // section, TEX=001, AP=11, non-cacheable
		else
			desc = base | 0xC16; // section, AP=11, B (device), XN
		ttb[i] = desc;
	}
}

#define PACK_MAGIC 0x58534D4Du
#define UIMG_MAGIC 0x27051956u
#define UIMG_HEADER_SIZE 64u
#define IH_TYPE_KERNEL 2

extern const uint8_t _payload_start[];

struct pack_header {
	uint32_t magic;
	uint32_t usize; // uncompressed size
	uint32_t csize; // compressed size
	uint32_t crc;	// crc32 of uncompressed data
};

// U-Boot legacy image header; all uint32_t fields are big-endian
struct uimg_header {
	uint32_t ih_magic;
	uint32_t ih_hcrc;
	uint32_t ih_time;
	uint32_t ih_size; // header + payload bytes
	uint32_t ih_load;
	uint32_t ih_ep;
	uint32_t ih_dcrc;
	uint8_t ih_os;
	uint8_t ih_arch;
	uint8_t ih_type;
	uint8_t ih_comp;
	uint8_t ih_name[32];
};

static uint32_t be32(uint32_t x) {
	return __builtin_bswap32(x);
}

void __attribute__((noreturn)) stub_main(void) {
	const struct pack_header *ph = (const struct pack_header *)_payload_start;

	if (ph->magic != PACK_MAGIC)
		goto fail;

	fill_translation_table();
	mmu_on(TTB_ADDR);

	// Blank the screen and show the boot logo while we decompress. The app
	// re-resets and re-inits the panel when it starts, so this is transparent.
	splash_show();

	uint32_t written = lz4_decompress(_payload_start + sizeof(*ph), ph->csize, STAGING);
	if (written != ph->usize)
		goto fail;

	if (crc32_calc(STAGING, ph->usize) != ph->crc)
		goto fail;

	// Walk the concatenated uimg records, mirroring mp1-boot's loader
	{
		uint32_t entry = 0;
		uint32_t off = 0;

		while (off + UIMG_HEADER_SIZE <= ph->usize) {
			const struct uimg_header *h = (const struct uimg_header *)(STAGING + off);
			if (be32(h->ih_magic) != UIMG_MAGIC)
				break;

			uint32_t size = be32(h->ih_size); // includes the 64-byte header
			uint32_t load = be32(h->ih_load);
			uint32_t ep = be32(h->ih_ep);

			if (size < UIMG_HEADER_SIZE || off + size > ph->usize)
				goto fail;

			if (h->ih_type == IH_TYPE_KERNEL && ep >= load && ep < load + size)
				entry = ep;

			copy((uint8_t *)load, STAGING + off + UIMG_HEADER_SIZE, size - UIMG_HEADER_SIZE);

			off += size;
		}

		if (entry == 0)
			goto fail;

		// Cleans the D-cache, disables MMU/D-cache, invalidates I-cache, jumps
		mmu_off_and_jump(entry);
	}

fail:
	// Bad flash contents: jumping to garbage helps nobody. Hang here (the
	// unit can still be recovered over USB DFU or via SD card boot).
	for (;;)
		;
}
