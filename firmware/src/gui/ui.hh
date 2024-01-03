#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "gui/message_notification.hh"
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

using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 8>;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf1 alignas(64);
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf2 alignas(64);

class Ui {
private:
	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	MessageQueue msg_queue;
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
		, msg_queue{1024}
		, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {

		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams, framebuf2);
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

		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			pr_info("%s", msg.data());
			MessageNotification::show(msg);
			msg_queue.clear_message();
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
		bool load_status = patch_playloader.handle_sync_patch_loading();
		if (!load_status)
			msg_queue.append_message("Loading patch failed");

		new_patch_data = false;
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_lv_update_tm = 0;
};

} // namespace MetaModule
