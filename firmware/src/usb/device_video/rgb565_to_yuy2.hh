#pragma once
#include <cstdint>

namespace MetaModule
{

// Convert a pair of RGB565 pixels to YUY2 (4 bytes: Y0 U Y1 V).
// Uses fixed-point integer math (Q8).
inline void rgb565_pair_to_yuy2(uint16_t px0, uint16_t px1, uint8_t *out) {
	// Extract RGB components (scale to 0-255)
	uint32_t r0 = (px0 >> 11) & 0x1F;
	uint32_t g0 = (px0 >> 5) & 0x3F;
	uint32_t b0 = px0 & 0x1F;
	r0 = (r0 << 3) | (r0 >> 2);
	g0 = (g0 << 2) | (g0 >> 4);
	b0 = (b0 << 3) | (b0 >> 2);

	uint32_t r1 = (px1 >> 11) & 0x1F;
	uint32_t g1 = (px1 >> 5) & 0x3F;
	uint32_t b1 = px1 & 0x1F;
	r1 = (r1 << 3) | (r1 >> 2);
	g1 = (g1 << 2) | (g1 >> 4);
	b1 = (b1 << 3) | (b1 >> 2);

	// Y = 0.299*R + 0.587*G + 0.114*B  (Q8: 77, 150, 29)
	uint32_t y0 = (77 * r0 + 150 * g0 + 29 * b0 + 128) >> 8;
	uint32_t y1 = (77 * r1 + 150 * g1 + 29 * b1 + 128) >> 8;

	// Use average of both pixels for chroma
	uint32_t r_avg = (r0 + r1 + 1) >> 1;
	uint32_t g_avg = (g0 + g1 + 1) >> 1;
	uint32_t b_avg = (b0 + b1 + 1) >> 1;

	// U = -0.169*R - 0.331*G + 0.500*B + 128  (Q8: -43, -85, 128)
	int32_t u = ((-43 * (int32_t)r_avg - 85 * (int32_t)g_avg + 128 * (int32_t)b_avg + 128) >> 8) + 128;
	// V = 0.500*R - 0.419*G - 0.081*B + 128  (Q8: 128, -107, -21)
	int32_t v = ((128 * (int32_t)r_avg - 107 * (int32_t)g_avg - 21 * (int32_t)b_avg + 128) >> 8) + 128;

	// Clamp
	if (y0 > 255) y0 = 255;
	if (y1 > 255) y1 = 255;
	if (u < 0) u = 0; else if (u > 255) u = 255;
	if (v < 0) v = 0; else if (v > 255) v = 255;

	out[0] = (uint8_t)y0;
	out[1] = (uint8_t)u;
	out[2] = (uint8_t)y1;
	out[3] = (uint8_t)v;
}

// Convert count RGB565 pixels starting at src into YUY2 at dst.
// count must be even. dst must have room for count*2 bytes.
inline void rgb565_to_yuy2(const uint16_t *src, uint8_t *dst, uint32_t count) {
	for (uint32_t i = 0; i < count; i += 2) {
		rgb565_pair_to_yuy2(src[i], src[i + 1], dst + i * 2);
	}
}

} // namespace MetaModule
