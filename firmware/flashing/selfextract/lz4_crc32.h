// The decoder the self-extract stubs share: MP1's (stub.c) and MP2's (../selfextract_mp2/stub.c).
// Freestanding, and safe with the MMU off (no unaligned word accesses).
#pragma once
#include <stdint.h>

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
		0x00000000,
		0x1DB71064,
		0x3B6E20C8,
		0x26D930AC,
		0x76DC4190,
		0x6B6B51F4,
		0x4DB26158,
		0x5005713C,
		0xEDB88320,
		0xF00F9344,
		0xD6D6A3E8,
		0xCB61B38C,
		0x9B64C2B0,
		0x86D3D2D4,
		0xA00AE278,
		0xBDBDF21C,
	};
	uint32_t crc = 0xFFFFFFFFu;
	while (len--) {
		crc ^= *data++;
		crc = (crc >> 4) ^ tab[crc & 15];
		crc = (crc >> 4) ^ tab[crc & 15];
	}
	return crc ^ 0xFFFFFFFFu;
}
