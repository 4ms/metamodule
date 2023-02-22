#pragma once
#include "a7/static_buffers.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "param_cache.hh"
#include "params.hh"
#include "params_dbg_print.hh"
#include "patch_playloader.hh"
#include "patch_storage_proxy.hh"
#include "patchlist.hh"

namespace MetaModule
{
class Ui {
private:
	ParamCache &param_cache;
	PatchStorageProxy &patch_storage;
	PatchPlayLoader &patch_playloader;

	MessageQueue msg_queue;
	PageManager page_manager;
	Params params;
	MetaParams metaparams;

	ParamDbgPrint print_dbg_params{params, metaparams};

	using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 8>;
	// static inline FrameBufferT framebuf1;
	// static inline FrameBufferT framebuf2;

	static inline LVGLDriver gui{
		MMDisplay::flush_to_screen, MMDisplay::read_input, StaticBuffers::framebuf1, StaticBuffers::framebuf2};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   PatchStorageProxy &patch_storage,
	   ParamCache &pc,
	   PatchModQueue &patch_mod_queue)
		: param_cache{pc}
		, patch_storage{patch_storage}
		, patch_playloader{patch_playloader}
		, msg_queue{1024}
		, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void start() {
		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams, StaticBuffers::framebuf2);
		Gui::init_lvgl_styles();
		page_manager.init();

		page_update_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz = 16ms
				.priority1 = 2,
				.priority2 = 0,
			},
			[&] {
			// Debug::Pin1::high();
			// static uint32_t poll_tmr = 0;
			// if (poll_tmr++ >= 100) { //1.6sec
			// 	poll_tmr = 0;
			// 	patch_storage.poll_media_change();
			// }
			page_update_task();
			// Debug::Pin1::low();
			});
		page_update_tm.start();

		ui_event_tm.init(
			{
				.TIMx = TIM16,
				.period_ns = 1000000000 / 600, // =  600Hz = 1.6ms
				.priority1 = 3,
				.priority2 = 3,
			},
			[&] {
			// Debug::Pin2::high();
			lvgl_update_task();
			// Debug::Pin2::low();
			});
		ui_event_tm.start();

		MMDisplay::start();
	}

private:
	void lvgl_update_task() {
		page_update_tm.stop();
		lv_timer_handler();
		page_update_tm.start();

		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			printf_("%s", msg.data());
			msg_queue.clear_message();
		}

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
	}

	void page_update_task() { //60Hz
		//This returns false when audio stops
		bool read_ok = param_cache.read_sync(&params, &metaparams);
		// if (read_ok) {
		// 	Debug::Pin1::low();
		// } else {
		// 	Debug::Pin1::high();
		// }
		page_manager.update_current_page();
		patch_playloader.handle_sync_patch_loading();
	}

	mdrivlib::Timekeeper page_update_tm;
	mdrivlib::Timekeeper ui_event_tm;
};

} // namespace MetaModule
