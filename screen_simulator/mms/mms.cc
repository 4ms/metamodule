#include <cstdint>

// Override dma2d to our stub:
#define _DMA2D_TRANSFER_HH
#include "stubs/drivers/dma2d_transfer.hh"
namespace target = ScreenSimulator;

// #define SIMULATOR
#include "pages/bouncing_balls.hh"
#include "pages/sim_test_page.hh"

// struct SimData {
// 	PatchList patch_list;
// 	PatchPlayer patch_player;
// 	MetaModule::Params params;
// 	MetaModule::MetaParams metaparams;
// 	ScreenConfT::FrameBufferT framebuf;
// 	ScreenFrameBuffer screen{framebuf};

// 	SimData() {
// 		params.clear();
// 		metaparams.clear();
// 		screen.set_rotation(MMScreenBufferConf::Rotation::CW90);
// 	}
// };

struct SimPageManager {
	PatchList patch_list;
	PatchPlayer patch_player;
	MetaModule::Params params;
	MetaModule::MetaParams metaparams;

	ScreenConfT::FrameBufferT framebuf;
	ScreenFrameBuffer screen{framebuf};

	MetaModule::SimulationTestPage testpage{{patch_list, patch_player, params, metaparams}, screen};
	MetaModule::BouncingBallsPage ball_page{{patch_list, patch_player, params, metaparams}, screen};

	unsigned cur_page = 0;

	SimPageManager()
	{
		screen.set_rotation(MMScreenBufferConf::Rotation::CW90);
	}

	void draw()
	{
		testpage.draw();
	}
};

static SimPageManager pm;

extern "C" void init_screen()
{
	pm.params.clear();
	pm.metaparams.clear();
	pm.testpage.draw();
}

extern "C" void refresh()
{
	pm.draw();
}

extern "C" uint16_t get_pixel(uint16_t x, uint16_t y)
{
	return (pm.framebuf[x + y * 240]);
}
