#pragma once
#include "audio_stream.hh"
#include "lv_port_indev.h"
#define printf_ printf
///

#include "gui/pages/page_manager.hh"
#include "params/params_state.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_file/patchlist.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

class Ui {
private:
	PatchPlayLoader &patch_playloader;

	MessageQueue msg_queue;
	PageManager page_manager;
	ParamsState params;
	MetaParams metaparams;

	Player player;

	LvglEncoderSimulatorDriver input_driver{keys};

	RotaryEncoderKeys keys{
		.turn_cw = SDLK_RIGHT,
		.turn_ccw = SDLK_LEFT,
		.click = SDLK_DOWN,
		.aux_button = SDLK_UP,
		.quit = SDLK_ESCAPE,
		.param_inc = ']',
		.param_dec = '[',
	};

public:
	Ui(PatchPlayLoader &patch_playloader, PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue)
		: patch_playloader{patch_playloader}
		, msg_queue{1024}
		, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void start() {
		params.clear();
		metaparams.clear();

		Gui::init_lvgl_styles();
		page_manager.init();

		patch_playloader.audio_is_muted();
	}

	// "Scheduler" for UI tasks
	// returns true until it gets a QUIT event
	bool update() {

		auto tm = lv_tick_get(); //milliseconds
		if (tm - last_lvgl_task_tm >= 1) {
			lvgl_update_task();
			last_lvgl_task_tm = tm;
		}

		tm = lv_tick_get();
		if (tm - last_page_task_tm >= 16) {
			transfer_aux_button_events();
			transfer_params();
			page_update_task();
			last_page_task_tm = tm;
		}

		bool keep_running = input_driver.get_quit() == LV_QUIT_NONE;
		return keep_running;
	}

private:
	uint32_t last_lvgl_task_tm = 0;
	uint32_t last_page_task_tm = 0;

	void lvgl_update_task() {
		lv_timer_handler();

		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			printf_("%s", msg.data());
			msg_queue.clear_message();
		}
	}

	void page_update_task() { //60Hz
		page_manager.update_current_page();
		patch_playloader.handle_sync_patch_loading();
	}

	void transfer_aux_button_events() {
		// Transfer aux button events SDL => LVGL => metaparams
		if (input_driver.aux_button_just_pressed())
			metaparams.meta_buttons[0].register_falling_edge();

		if (input_driver.aux_button_just_released())
			metaparams.meta_buttons[0].register_rising_edge();
	}

	void transfer_params() {
		if (unsigned cur_param = input_driver.selected_param(); cur_param < params.knobs.size()) {
			params.knobs[cur_param].changed = false;

			if (input_driver.param_inc()) {
				params.knobs[cur_param].val = std::clamp(params.knobs[cur_param] + 0.05f, 0.f, 1.f);
				params.knobs[cur_param].changed = true;

				printf("Knob #%d = %1.2f\n", cur_param, (double)params.knobs[cur_param].val);
			}

			if (input_driver.param_dec()) {
				params.knobs[cur_param].val = std::clamp(params.knobs[cur_param] - 0.05f, 0.f, 1.f);
				params.knobs[cur_param].changed = true;

				printf("Knob #%d = %1.2f\n", cur_param, (double)params.knobs[cur_param].val);
			}
		}
	}
};

} // namespace MetaModule
