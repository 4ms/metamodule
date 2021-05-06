#include "stubs/drivers/arch.hh"
#include "stubs/sys/alloc_buffer.hh"
#include <cstdint>

// Override dma2d to our stub:
#define _DMA2D_TRANSFER_HH
#include "stubs/drivers/dma2d_transfer.hh"

#include "pages/page_manager.hh"

struct Simulator {
	PatchList patch_list;
	MetaModule::PatchPlayer patch_player;
	MetaModule::Params params;
	MetaModule::MetaParams metaparams;
	ScreenConfT::FrameBufferT framebuf;
	ScreenFrameBuffer screen{framebuf};
	MetaModule::PageManager pages;

	Simulator()
		: pages{patch_list, patch_player, params, metaparams, screen}
	{
		params.clear();
		metaparams.clear();
		screen.init();
		register_printf_destination(screen);
	}

	bool init()
	{
		auto &patch = patch_list.cur_patch();
		bool loaded_ok = patch_player.load_patch(patch);
		if (!loaded_ok)
			return false;
		pages.init();
		return true;
	}

	void refresh()
	{
		pages.display_current_page();
	}
};
static Simulator sim;

extern "C" void rotary_fwd()
{
	sim.pages.next_page();
}

extern "C" void rotary_back()
{
	sim.pages.prev_page();
}

extern "C" void rotary_push_fwd()
{
	sim.patch_list.next_patch();
	sim.patch_player.load_patch(sim.patch_list.cur_patch());
}

extern "C" void rotary_push_back()
{
	sim.patch_list.prev_patch();
	sim.patch_player.load_patch(sim.patch_list.cur_patch());
}

extern "C" void rotary_press()
{
	//
}

extern "C" void rotary_release()
{
	//
}

extern "C" void jump_to_page(unsigned page_num)
{
	sim.pages.jump_to_page(static_cast<MetaModule::Page>(page_num));
}

extern "C" void init_screen()
{
	sim.init();
}

extern "C" void refresh()
{
	sim.refresh();
}

extern "C" uint16_t get_pixel(uint16_t x, uint16_t y)
{
	return (sim.framebuf[x + y * 240]);
}

size_t get_heap_size()
{
	return 0;
}
