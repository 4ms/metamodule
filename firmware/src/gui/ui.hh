#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "gui/notify/notification.hh"
#include "gui/pages/page_manager.hh"
#include "params/params.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"

namespace MetaModule
{

using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 4>;
static inline FrameBufferT framebuf1 alignas(64);
static inline FrameBufferT framebuf2 alignas(64);

class Ui {
private:
	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	NotificationQueue notify_queue;
	PageManager page_manager;
	ParamsMidiState params;
	MetaParams metaparams;

	ParamDbgPrint print_dbg_params{params, metaparams};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   FileStorageProxy &patch_storage,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue)
		: sync_params{sync_params}
		, patch_playloader{patch_playloader}
		, page_manager{patch_storage, patch_playloader, params, metaparams, notify_queue, patch_mod_queue} {

		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams);
		Gui::init_lvgl_styles();
		page_manager.init();
	}

	void update() {

		auto now = HAL_GetTick();
		if ((now - last_lv_update_tm) > 2) {
			last_lv_update_tm = now;
			lv_timer_handler();
		}

		now = HAL_GetTick();
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			page_update_task();
		}

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
	}

	LightWatcher &lights() {
		return params.lights;
	}

	bool new_patch_data = false;

private:
	void page_update_task() {
		//This returns false when audio stops
		//TODO: if (!read_ok) ... restart audio
		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);

		page_manager.update_current_page();

		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success) {
			notify_queue.put({load_status.error_string, Notification::Priority::Error, 5000});
		}

		new_patch_data = false;
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_lv_update_tm = 0;
};

} // namespace MetaModule
