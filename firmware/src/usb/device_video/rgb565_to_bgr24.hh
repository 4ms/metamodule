#pragma once
#include <cstdint>

namespace MetaModule
{

// Write one RGB565 pixel as BGR24 (3 bytes: B, G, R) into a framebuffer row.
// Byte order matches the UVC "BGR3" uncompressed format
// (Windows MEDIASUBTYPE_RGB24 GUID).
inline void write_bgr24_pixel(uint8_t *row, int x, uint16_t rgb565) {
	uint32_t r = (rgb565 >> 11) & 0x1F;
	uint32_t g = (rgb565 >> 5) & 0x3F;
	uint32_t b = rgb565 & 0x1F;
	// Expand 5/6/5-bit channels to 8-bit by replicating MSBs into LSBs
	row[x * 3 + 0] = (uint8_t)((b << 3) | (b >> 2));
	row[x * 3 + 1] = (uint8_t)((g << 2) | (g >> 4));
	row[x * 3 + 2] = (uint8_t)((r << 3) | (r >> 2));
}

} // namespace MetaModule
