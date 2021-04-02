#pragma once

namespace ScreenSimulator
{
struct DMA2DTransfer {
	void init() {}

	void fillrect_rgb565(uint32_t starting_addr, uint16_t width, uint16_t height, uint16_t screen_width, uint16_t color)
	{
		uint16_t *frameptr = reinterpret_cast<uint16_t *>(starting_addr);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				*frameptr++ = color;
			}
			*frameptr += screen_width - width;
		}
	}
};

} // namespace ScreenSimulator
