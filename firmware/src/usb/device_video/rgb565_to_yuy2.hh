#pragma once
#include <array>
#include <cstdint>

namespace MetaModule
{

struct YuvEntry {
	uint8_t y;
	uint8_t u;
	uint8_t v;
};

constexpr YuvEntry rgb565_to_yuv(uint32_t rgb565) {
	uint32_t r = (rgb565 >> 11) & 0x1F;
	uint32_t g = (rgb565 >> 5) & 0x3F;
	uint32_t b = rgb565 & 0x1F;
	r = (r << 3) | (r >> 2);
	g = (g << 2) | (g >> 4);
	b = (b << 3) | (b >> 2);

	// Y = 0.299*R + 0.587*G + 0.114*B  (Q8: 77, 150, 29)
	int32_t y = (int32_t)(77 * r + 150 * g + 29 * b + 128) >> 8;
	// U = -0.169*R - 0.331*G + 0.500*B + 128
	int32_t u = ((-43 * (int32_t)r - 85 * (int32_t)g + 128 * (int32_t)b + 128) >> 8) + 128;
	// V = 0.500*R - 0.419*G - 0.081*B + 128
	int32_t v = ((128 * (int32_t)r - 107 * (int32_t)g - 21 * (int32_t)b + 128) >> 8) + 128;

	if (y < 0)
		y = 0;
	else if (y > 255)
		y = 255;
	if (u < 0)
		u = 0;
	else if (u > 255)
		u = 255;
	if (v < 0)
		v = 0;
	else if (v > 255)
		v = 255;

	return {(uint8_t)y, (uint8_t)u, (uint8_t)v};
}

constexpr auto make_rgb565_to_yuv_lut() {
	std::array<YuvEntry, 65536> lut{};
	for (uint32_t i = 0; i < 65536; i++) {
		lut[i] = rgb565_to_yuv(i);
	}
	return lut;
}

// 192KB lookup table, computed at compile time on hardware (gcc 12+)
// Compute at runtime startup for simulator because some compilers don't consider it constexpr.
// Indexed by RGB565 pixel value, returns {Y, U, V}.
#ifdef SIMULATOR
inline const auto rgb565_yuv_lut = make_rgb565_to_yuv_lut();
#else
inline constexpr auto rgb565_yuv_lut = make_rgb565_to_yuv_lut();
#endif

// Write one RGB565 pixel into a YUY2 framebuffer at the given x position.
// Even x: writes Y and U. Odd x: writes Y and V.
// This uses co-sited chroma (U from even pixel, V from odd pixel) which
// avoids needing to pair pixels and handles arbitrary region boundaries.
inline void write_yuy2_pixel(uint8_t *yuy2_row, int x, uint16_t rgb565) {
	auto &e = rgb565_yuv_lut[rgb565];
	yuy2_row[x * 2] = e.y;
	yuy2_row[x * 2 + 1] = (x & 1) ? e.v : e.u;
}

} // namespace MetaModule
