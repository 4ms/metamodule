#include <cstdint>
#define _DMA2D_TRANSFER_HH
#include "stubs/dma2d_transfer.hh"
#include "pages/sim_test_page.hh"

// void init() {
		
// }

uint16_t get_pixel(uint16_t x, uint16_t y) {
	if (x<120 && y<120)
		return 0xf800; //red
	if (x<120)
		return 0x07e0; //green
	if (y<120)
		return 0x001f; //blue

	return 0xffff; //white
}

uint32_t get_pixel32(uint16_t x, uint16_t y) {
	if (x<120 && y<120)
		return 0x000000FF; //blue
	if (x<120)
		return 0x0000FF00; //green
	if (y<120)
		return 0x00FF0000; //red

	return 0x00FF00FF; //purple
}
