#pragma once
#include <cstdint>
#include <span>
#include <vector>

namespace MetaModule
{

// Encodes an RGB565 pixel buffer (LVGL lv_color16_t layout, LV_COLOR_16_SWAP==0:
// red in bits 11..15, green in bits 5..10, blue in bits 0..4) into an
// uncompressed 24-bit BMP. The source is row-major with the top row first;
// BMP stores rows bottom-up, so rows are emitted in reverse.
inline std::vector<char> encode_bmp24_from_rgb565(std::span<const uint16_t> pixels, uint32_t width, uint32_t height) {
	const uint32_t row_stride = (width * 3 + 3) & ~3u; // each row padded to 4 bytes
	const uint32_t pixel_bytes = row_stride * height;
	const uint32_t file_header_size = 14;
	const uint32_t info_header_size = 40;
	const uint32_t pixel_offset = file_header_size + info_header_size;
	const uint32_t file_size = pixel_offset + pixel_bytes;

	std::vector<char> out(file_size, 0);

	auto put16 = [&](uint32_t pos, uint16_t v) {
		out[pos] = (char)(v & 0xFF);
		out[pos + 1] = (char)((v >> 8) & 0xFF);
	};
	auto put32 = [&](uint32_t pos, uint32_t v) {
		out[pos] = (char)(v & 0xFF);
		out[pos + 1] = (char)((v >> 8) & 0xFF);
		out[pos + 2] = (char)((v >> 16) & 0xFF);
		out[pos + 3] = (char)((v >> 24) & 0xFF);
	};

	// BITMAPFILEHEADER
	out[0] = 'B';
	out[1] = 'M';
	put32(2, file_size);
	put32(6, 0); // reserved
	put32(10, pixel_offset);

	// BITMAPINFOHEADER
	put32(14, info_header_size);
	put32(18, width);
	put32(22, height); // positive height => bottom-up rows
	put16(26, 1);	   // color planes
	put16(28, 24);	   // bits per pixel
	put32(30, 0);	   // BI_RGB (no compression)
	put32(34, pixel_bytes);
	put32(38, 2835); // X pixels-per-meter (~72 dpi)
	put32(42, 2835); // Y pixels-per-meter
	put32(46, 0);	 // colors in palette
	put32(50, 0);	 // important colors

	for (uint32_t y = 0; y < height; y++) {
		// BMP is bottom-up: file row y comes from source row (height-1-y).
		const uint16_t *src_row = pixels.data() + (size_t)(height - 1 - y) * width;
		uint32_t dst = pixel_offset + y * row_stride;
		for (uint32_t x = 0; x < width; x++) {
			const uint16_t px = src_row[x];
			const uint8_t r5 = (px >> 11) & 0x1F;
			const uint8_t g6 = (px >> 5) & 0x3F;
			const uint8_t b5 = px & 0x1F;
			// Expand to 8-bit by replicating the high bits into the low bits.
			out[dst++] = (char)((b5 << 3) | (b5 >> 2)); // BMP pixel order is BGR
			out[dst++] = (char)((g6 << 2) | (g6 >> 4));
			out[dst++] = (char)((r5 << 3) | (r5 >> 2));
		}
	}

	return out;
}

} // namespace MetaModule
