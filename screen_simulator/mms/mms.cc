#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "pages/styles.hh"
#include "param_cache.hh"
#include "params.hh"
#include "patch_mod_queue.hh"
#include "patch_playloader.hh"
#include "patches_default.hh"
#include "patchlist.hh"
#include "stubs/patch_storage_proxy.hh"

#include <cstdint>

struct Simulator {
	MetaModule::LVGLDriver gui{MetaModule::MMDisplay::flush_to_screen, MetaModule::MMDisplay::read_input};
	MetaModule::PatchPlayer patch_player;

	MetaModule::ParamCache param_cache;
	MetaModule::PatchStorageProxy patch_storage;
	MetaModule::PatchPlayLoader patch_playloader{patch_storage, patch_player};

	MetaModule::MessageQueue msg_queue{1024};
	MetaModule::PageManager page_manager;
	MetaModule::Params params;
	MetaModule::MetaParams metaparams;

	MetaModule::PatchModQueue patch_mod_queue;

	Simulator()
		: page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
		MetaModule::MMDisplay::init(metaparams);

		for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
			// patch_list.add_patch_from_yaml(DefaultPatches::get_patch(i));
		}
	}

	bool init() {
		MetaModule::MMDisplay::start();
		MetaModule::Gui::init_lvgl_styles();
		// patch_loader.load_patch(1);
		params.clear();
		metaparams.clear();
		page_manager.init();

		return true;
	}

	void update_ui() {
		//Todo: enable this:
		//param_queue.read_sync(&params, &metaparams);
		page_manager.update_current_page();
	}

	uint16_t get_pixel(uint16_t x, uint16_t y) {
		return MetaModule::MMDisplay::framebuffer[x][y].full;
	}
};

// Global simulator ui object
static Simulator sim;

extern "C" void button_press() {
	sim.metaparams.meta_buttons[0].register_rising_edge();
}

extern "C" void button_release() {
	sim.metaparams.meta_buttons[0].register_falling_edge();
}

extern "C" void rotary_fwd() {
	sim.metaparams.rotary.motion++;
	sim.metaparams.rotary.abs_pos++;
}

extern "C" void rotary_back() {
	sim.metaparams.rotary.motion--;
	sim.metaparams.rotary.abs_pos--;
}

extern "C" void rotary_push_fwd() {
	sim.metaparams.rotary_pushed.motion++;
	sim.metaparams.rotary_pushed.abs_pos++;
}

extern "C" void rotary_push_back() {
	sim.metaparams.rotary_pushed.motion--;
	sim.metaparams.rotary_pushed.abs_pos--;
}

extern "C" void rotary_press() {
	sim.metaparams.rotary_button.register_rising_edge();
}

extern "C" void rotary_release() {
	sim.metaparams.rotary_button.register_falling_edge();
}

extern "C" void init_screen() {
	sim.init();
}

extern "C" void update_ui() {
	sim.update_ui();
}

extern "C" void set_knob(uint32_t knob_id, float val) {
	if (knob_id < PanelDef::NumPot)
		sim.params.knobs[knob_id] = val;
}

extern "C" uint16_t get_pixel(uint16_t x, uint16_t y) {
	return sim.get_pixel(x, y);
}

size_t get_heap_size() {
	return 1;
}
