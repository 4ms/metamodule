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
	MetaModule::UiAudioMailbox mbox;

	Simulator()
		: pages{patch_list, patch_player, params, metaparams, mbox, screen}
	{
		params.clear();
		metaparams.clear();
		screen.init();
		register_printf_destination(screen);
	}

	bool init()
	{
		patch_list.set_cur_patch_index(0);
		bool ok = patch_player.load_patch(patch_list.cur_patch());
		if (!ok)
			return false;
		pages.init();
		return true;
	}

	void refresh()
	{
		handle_rotary();
		pages.display_current_page();
	}

	void handle_rotary()
	{
		auto rotary_pushed_turned = metaparams.rotary_pushed.use_motion();
		if (rotary_pushed_turned < 0)
			pages.prev_page();
		if (rotary_pushed_turned > 0)
			pages.next_page();
	}
};

static Simulator sim;

extern "C" void rotary_fwd()
{
	sim.metaparams.rotary.motion++;
	sim.metaparams.rotary.abs_pos++;
	// sim.pages.next_page();
}

extern "C" void rotary_back()
{
	sim.metaparams.rotary.motion--;
	sim.metaparams.rotary.abs_pos--;
	// sim.pages.prev_page();
}

extern "C" void rotary_push_fwd()
{
	sim.metaparams.rotary_pushed.motion++;
	sim.metaparams.rotary_pushed.abs_pos++;
}

extern "C" void rotary_push_back()
{
	sim.metaparams.rotary_pushed.motion++;
	sim.metaparams.rotary_pushed.abs_pos++;
}

extern "C" void rotary_press()
{
	sim.metaparams.rotary_button.register_falling_edge();
}

extern "C" void rotary_release()
{
	sim.metaparams.rotary_button.register_rising_edge();
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
	return (sim.framebuf[x + y * ScreenConfT::viewWidth]);
}

size_t get_heap_size()
{
	return 0;
}

// void change_patch(uint32_t new_patch_index)
// {
// 	uint32_t cur_patch_index = sim.patch_list.cur_patch_index();
// 	// uint32_t new_patch_index = (cur_patch_index == 0) ? (sim.patch_list.NumPatches - 1) : cur_patch_index - 1;
// 	sim.patch_player.unload_patch();
// 	sim.patch_list.set_cur_patch_index(new_patch_index);
// 	sim.patch_player.load_patch(sim.patch_list.cur_patch());
// }
