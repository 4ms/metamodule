// Self-extracting boot stub for the MetaModule firmware image.
//
// MP1-Boot loads this stub (with its embedded LZ4-compressed payload) into
// the FWBUFFER region and jumps to _start, exactly as it would boot the
// application directly -- no bootloader changes are needed.
//
// The payload is the complete multi-record uimg (A7 + M4 segments) that
// elf_to_uimg.py produces. This stub:
//   1. LZ4-decompresses it to a staging area in DDR
//   2. Verifies the CRC32 of the decompressed image
//   3. Walks the uimg records, copying each payload to its load address
//      (mirroring BootMediaLoader::load_image in mp1-boot)
//   4. Jumps to the entry point found in the kernel-type record
//
// Memory layout (see system/linker/memory.ld):
//   0xCC000040  this stub + compressed payload (FWBUFFER region, 20MB;
//               never a load target of any uimg record)
//   0xD0000000  staging area for the decompressed uimg (inside the A7_HEAP
//               region; only VMAs live there, no record loads there)
//
// Execution state: ARM mode, interrupts masked, MMU off (so all data
// accesses are uncached/strongly-ordered -- keep word accesses aligned).

#include <stdint.h>

// STAGING is overridable so tests can host-compile this file (see test/)
#ifndef STAGING
#define STAGING ((uint8_t *)0xD0000000)
#endif

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

// Byte-wise copy with an aligned-word fast path. With the MMU off, DDR
// accesses are strongly-ordered, so unaligned word accesses would fault.
static void copy(uint8_t *dst, const uint8_t *src, uint32_t len) {
	if ((((uintptr_t)dst | (uintptr_t)src) & 3) == 0) {
		while (len >= 16) {
			uint32_t a = ((const uint32_t *)src)[0];
			uint32_t b = ((const uint32_t *)src)[1];
			uint32_t c = ((const uint32_t *)src)[2];
			uint32_t d = ((const uint32_t *)src)[3];
			((uint32_t *)dst)[0] = a;
			((uint32_t *)dst)[1] = b;
			((uint32_t *)dst)[2] = c;
			((uint32_t *)dst)[3] = d;
			dst += 16;
			src += 16;
			len -= 16;
		}
	}
	while (len--)
		*dst++ = *src++;
}

// LZ4 block format decoder
static uint32_t lz4_decompress(const uint8_t *src, uint32_t slen, uint8_t *dst) {
	const uint8_t *s = src;
	const uint8_t *send = src + slen;
	uint8_t *d = dst;

	while (s < send) {
		uint32_t token = *s++;

		uint32_t litlen = token >> 4;
		if (litlen == 15) {
			uint8_t b;
			do {
				b = *s++;
				litlen += b;
			} while (b == 255);
		}
		copy(d, s, litlen);
		d += litlen;
		s += litlen;

		if (s >= send)
			break; // final sequence is literals-only

		uint32_t offset = s[0] | ((uint32_t)s[1] << 8);
		s += 2;

		uint32_t mlen = (token & 15) + 4;
		if ((token & 15) == 15) {
			uint8_t b;
			do {
				b = *s++;
				mlen += b;
			} while (b == 255);
		}

		// Matches may overlap the bytes being written: copy byte-wise
		const uint8_t *m = d - offset;
		while (mlen--)
			*d++ = *m++;
	}

	return (uint32_t)(d - dst);
}

static uint32_t crc32_calc(const uint8_t *data, uint32_t len) {
	// Nibble-table CRC-32 (poly 0xEDB88320), matches zlib.crc32
	static const uint32_t tab[16] = {
		0x00000000, 0x1DB71064, 0x3B6E20C8, 0x26D930AC,
		0x76DC4190, 0x6B6B51F4, 0x4DB26158, 0x5005713C,
		0xEDB88320, 0xF00F9344, 0xD6D6A3E8, 0xCB61B38C,
		0x9B64C2B0, 0x86D3D2D4, 0xA00AE278, 0xBDBDF21C,
	};
	uint32_t crc = 0xFFFFFFFFu;
	while (len--) {
		crc ^= *data++;
		crc = (crc >> 4) ^ tab[crc & 15];
		crc = (crc >> 4) ^ tab[crc & 15];
	}
	return crc ^ 0xFFFFFFFFu;
}

static void invalidate_icache_and_predictors(void) {
#if defined(__arm__)
	uint32_t zero = 0;
	// ICIALLU: invalidate entire instruction cache
	__asm volatile("mcr p15, 0, %0, c7, c5, 0" ::"r"(zero));
	// BPIALL: invalidate branch predictor array
	__asm volatile("mcr p15, 0, %0, c7, c5, 6" ::"r"(zero));
	__asm volatile("dsb");
	__asm volatile("isb");
#endif
}

void __attribute__((noreturn)) stub_main(void) {
	const struct pack_header *ph = (const struct pack_header *)_payload_start;

	if (ph->magic != PACK_MAGIC)
		goto fail;

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

		invalidate_icache_and_predictors();

		typedef void __attribute__((noreturn)) (*entry_t)(void);
		((entry_t)entry)();
	}

fail:
	// Bad flash contents: jumping to garbage helps nobody. Hang here (the
	// unit can still be recovered over USB DFU).
	for (;;)
		;
}
