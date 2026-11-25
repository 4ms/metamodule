// Unpacks the A35 image from the payload that pack_elf.py makes (the format is described there).
// start.S calls this with the caches on.

#include "../selfextract/lz4_crc32.h"
#include <stdint.h>

// Tests compile this file for the host, and unpack into a buffer
#ifndef LOAD_PTR
#define LOAD_PTR(addr) ((uint8_t *)(uintptr_t)(addr))
#endif

#define PACK_MAGIC 0x58324D4Du // 'MM2X'

struct pack_header {
	uint32_t magic;
	uint32_t num_segments;
	uint64_t entry;
};

struct segment_header {
	uint64_t load;
	uint32_t usize; // uncompressed size
	uint32_t csize; // compressed size
	uint32_t crc;	// crc32 of the uncompressed data
	uint32_t reserved;
};

// Unpacks each segment to its load address.
// Returns the image's entry point, or 0 if the payload is bad.
uint64_t unpack(const uint8_t *payload) {
	const struct pack_header *ph = (const struct pack_header *)payload;

	if (ph->magic != PACK_MAGIC || ph->entry == 0)
		return 0;

	const uint8_t *p = payload + sizeof(*ph);

	for (uint32_t i = 0; i < ph->num_segments; i++) {
		const struct segment_header *sh = (const struct segment_header *)p;
		const uint8_t *data = p + sizeof(*sh);
		uint8_t *dst = LOAD_PTR(sh->load);

		if (lz4_decompress(data, sh->csize, dst) != sh->usize)
			return 0;

		if (crc32_calc(dst, sh->usize) != sh->crc)
			return 0;

		// The next header is at an 8-byte boundary
		p = data + ((sh->csize + 7u) & ~7u);
	}

	return ph->entry;
}
