#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

// lodepng is built as part of LVGL's PNG support, with the encoder enabled by
// default. Forward-declare the entry points we need instead of pulling in the
// header from deep inside the lvgl source tree. NOTE: LVGL's build of lodepng
// routes its allocator through the LVGL memory pool (lodepng_malloc ->
// lv_mem_alloc), so the buffer it returns MUST be released with lv_mem_free()
// and not libc free() (doing so faults). lodepng_free itself is static, so we
// call lv_mem_free directly.
extern "C" unsigned
lodepng_encode24(unsigned char **out, size_t *outsize, const unsigned char *image, unsigned w, unsigned h);
extern "C" void lv_mem_free(void *data); // no-op on nullptr

namespace MetaModule
{

// Encodes an RGB565 pixel buffer (LVGL lv_color16_t layout, LV_COLOR_16_SWAP==0:
// red in bits 11..15, green 5..10, blue 0..4), row-major with the top row first,
// as an 8-bit truecolor PNG via lodepng. Returns the PNG bytes, or empty on
// failure.
inline std::vector<char> encode_png24_from_rgb565(std::span<const uint16_t> pixels, uint32_t width, uint32_t height) {
	const size_t count = (size_t)width * height;
	std::vector<unsigned char> rgb(count * 3);
	for (size_t i = 0; i < count; i++) {
		const uint16_t px = pixels[i];
		const uint8_t r5 = (px >> 11) & 0x1F;
		const uint8_t g6 = (px >> 5) & 0x3F;
		const uint8_t b5 = px & 0x1F;
		// Expand to 8-bit by replicating the high bits into the low bits.
		rgb[i * 3 + 0] = (r5 << 3) | (r5 >> 2);
		rgb[i * 3 + 1] = (g6 << 2) | (g6 >> 4);
		rgb[i * 3 + 2] = (b5 << 3) | (b5 >> 2);
	}

	unsigned char *out = nullptr;
	size_t outsize = 0;
	const unsigned err = lodepng_encode24(&out, &outsize, rgb.data(), width, height);

	std::vector<char> png;
	if (!err && out)
		png.assign(reinterpret_cast<char *>(out), reinterpret_cast<char *>(out) + outsize);

	lv_mem_free(out); // matches lodepng_malloc -> lv_mem_alloc; safe on nullptr
	return png;
}

} // namespace MetaModule
