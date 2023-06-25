#pragma once
#define printf_ printf
///

#include "pages/page_manager.hh"
#include "params.hh"
#include "params_dbg_print.hh"
#include "patch_mod_queue.hh"
#include "patch_playloader.hh"
#include "patch_storage_proxy.hh"
#include "patchlist.hh"

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

public:
	Ui(PatchPlayLoader &patch_playloader, PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue)
		: patch_playloader{patch_playloader}
		, msg_queue{1024}
		, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void start() {
		params.clear();
		metaparams.clear();

		// MMDisplay::init(metaparams, StaticBuffers::framebuf2);
		Gui::init_lvgl_styles();
		page_manager.init();

		// MMDisplay::start();
	}

	// Polling "Scheduler" for UI tasks
	void update() {
		static uint32_t last_lvgl_task_tm = 0;
		static uint32_t last_page_task_tm = 0;

		auto tm = lv_tick_get();
		if (tm - last_lvgl_task_tm >= 1) {
			lvgl_update_task();
			last_lvgl_task_tm = tm;
		}

		tm = lv_tick_get();
		if (tm - last_page_task_tm >= 16) {
			page_update_task();
			last_page_task_tm = tm;
		}
	}

private:
	void lvgl_update_task() {
		// page_update_tm.stop();
		lv_timer_handler();
		// page_update_tm.start();

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
