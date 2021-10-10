#include "stubs/sys/alloc_buffer.hh"
#include <cstdint>

// Override dma2d to our stub:
#define _DMA2D_TRANSFER_HH
#include "stubs/drivers/dma2d_transfer.hh"

#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"

struct Simulator {
	MetaModule::PageManager pages;
	MetaModule::ParamQueue param_queue;

	MetaModule::Params params;
	MetaModule::MetaParams metaparams;
	MetaModule::PatchList patch_list;
	MetaModule::PatchPlayer patch_player;
	MetaModule::UiAudioMailbox mbox;

	Simulator()
		: pages{patch_list, patch_player, params, metaparams, mbox}
	{
		MetaModule::MMDisplay::init();
	}

	uint16_t get_pixel(uint16_t x, uint16_t y)
	{
		return MetaModule::MMDisplay::framebuffer[x][y].full;
	}

	bool init()
	{
		params.clear();
		metaparams.clear();
		pages.init();

		MetaModule::MMDisplay::start();

		pages.init();

		return true;
	}

	void update_ui()
	{
		//param_queue.read_sync(&params, &metaparams);
		handle_rotary();
		pages.update_current_page();
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
	sim.metaparams.rotary_pushed.motion--;
	sim.metaparams.rotary_pushed.abs_pos--;
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

extern "C" void update_ui()
{
	sim.update_ui();
}

extern "C" uint16_t get_pixel(uint16_t x, uint16_t y)
{
	return sim.get_pixel(x, y);
}

size_t get_heap_size()
{
	return 0;
}
