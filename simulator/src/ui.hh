#pragma once
#include "lv_port_indev.h"
#define printf_ printf
///

#include "gui/pages/page_manager.hh"
#include "params/params.hh"
#include "params/params_dbg_print.hh"
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
	Params params;
	MetaParams metaparams;

	ParamDbgPrint print_dbg_params{params, metaparams};
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

		static uint32_t last_lvgl_task_tm = 0;
		auto tm = lv_tick_get(); //milliseconds
		if (tm - last_lvgl_task_tm >= 1) {
			lvgl_update_task();
			last_lvgl_task_tm = tm;
		}

		// Transfer aux button events SDL => LVGL => metaparams
		if (input_driver.aux_button_just_pressed())
			metaparams.meta_buttons[0].register_falling_edge();

		if (input_driver.aux_button_just_released())
			metaparams.meta_buttons[0].register_rising_edge();

		if (unsigned cur_param = input_driver.selected_param(); cur_param < params.knobs.size()) {
			if (input_driver.param_inc()) {
				params.knobs[cur_param] = std::clamp(params.knobs[cur_param] + 0.05f, 0.f, 1.f);
				printf_("Knob #%d = %f\n", cur_param, params.knobs[cur_param]);
			}

			if (input_driver.param_dec()) {
				params.knobs[cur_param] = std::clamp(params.knobs[cur_param] - 0.05f, 0.f, 1.f);
				printf_("Knob #%d = %f\n", cur_param, params.knobs[cur_param]);
			}
		}

		static uint32_t last_page_task_tm = 0;
		tm = lv_tick_get();
		if (tm - last_page_task_tm >= 16) {
			page_update_task();
			last_page_task_tm = tm;
		}

		bool keep_running = input_driver.get_quit() == LV_QUIT_NONE;
		return keep_running;
	}

private:
	void lvgl_update_task() {
		lv_timer_handler();

		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			printf_("%s", msg.data());
			msg_queue.clear_message();
		}

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
	}

	void page_update_task() { //60Hz
		// TODO: update params and metaparams from user input
		// also metaparams contains the audio load
		// [[maybe_unused]] bool read_ok = param_cache.read_sync(&params, &metaparams);

		page_manager.update_current_page();
		patch_playloader.handle_sync_patch_loading();
	}
};

} // namespace MetaModule
