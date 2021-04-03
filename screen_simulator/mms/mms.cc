#include <cstdint>

// Override dma2d to our stub:
#define _DMA2D_TRANSFER_HH
#include "stubs/drivers/dma2d_transfer.hh"
namespace target = ScreenSimulator;

#include "pages/sim_test_page.hh"

struct SimPageManager {
	PatchList patch_list;
	PatchPlayer patch_player;
	MetaModule::Params params;
	MetaModule::MetaParams metaparams;

	ScreenConfT::FrameBufferT framebuf;
	ScreenFrameBuffer screen{framebuf};

	MetaModule::SimulationTestPage testpage{{patch_list, patch_player, params, metaparams}, screen};

	SimPageManager()
	{
		screen.set_rotation(MMScreenBufferConf::Rotation::CW90);
	}
};

static SimPageManager pm;

extern "C" void init_screen()
{
	pm.params.clear();
	pm.metaparams.clear();
	pm.testpage.draw();
	// for (int y = 0; y < 240; y += 2) {
	// 	for (int x = 0; x < 240; x++) {
	// 		pm.screen.drawPixel(x, y + 1, 0x00ff);
	// 		// pm.framebuf[x + y * 240] = 0xffff;
	// 		// pm.framebuf[x + (y + 1) * 240] = 0xff00;
	// 	}
	// }
}

extern "C" uint16_t get_pixel(uint16_t x, uint16_t y)
{
	return (pm.framebuf[x + y * 240]);

	// if (x < 120 && y < 120)
	// 	return 0xf800; // red
	// if (x < 120)
	// 	return 0x07e0; // green
	// if (y < 120)
	// 	return 0x001f; // blue

	// return 0xffff; // white
}
