#pragma once
#include "core_a7/static_buffers.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "gui/pages/page_manager.hh"
#include "params/params.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_file/patchlist.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"

namespace MetaModule
{
class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	MessageQueue msg_queue;
	PageManager page_manager;
	ParamsState params;
	MetaParams metaparams;

	ParamDbgPrint print_dbg_params{params, metaparams};

	static inline UartLog init_uart;
	static inline LVGLDriver gui{
		MMDisplay::flush_to_screen, MMDisplay::read_input, StaticBuffers::framebuf1, StaticBuffers::framebuf2};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   PatchStorageProxy &patch_storage,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue)
		: sync_params{sync_params}
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

		// page_update_tm.init(
		// 	{
		// 		.TIMx = TIM17,
		// 		.period_ns = 1000000000 / 60, // =  60Hz = 16ms
		// 		.priority1 = 2,
		// 		.priority2 = 0,
		// 	},
		// 	[&] { page_update_task(); });
		// page_update_tm.start();

		ui_event_tm.init(
			{
				.TIMx = TIM16,
				.period_ns = 1000000000 / 600, // =  600Hz = 1.6ms
				.priority1 = 2,
				.priority2 = 0,
			},
			[&] { lvgl_update_task(); });
		ui_event_tm.start();

		MMDisplay::start();
	}

private:
	void lvgl_update_task() {
		Debug::Pin2::high();
		lv_timer_handler();
		Debug::Pin2::low();

		Debug::Pin1::high();
		if (throttle_ctr-- <= 0) {
			throttle_ctr = throttle_amt;
			page_update_task();
		}
		Debug::Pin1::low();

		Debug::Pin0::high();
		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			// printf_("%s", msg.data());
			msg_queue.clear_message();
		}
		Debug::Pin0::low();

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
	}

	void page_update_task() { //60Hz
		//This returns false when audio stops
		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);
		//if (!read_ok) ... restart audio
		page_manager.update_current_page();
		patch_playloader.handle_sync_patch_loading();
	}

	static constexpr int32_t throttle_amt = 10;
	int32_t throttle_ctr = 0;

	// mdrivlib::Timekeeper page_update_tm;
	mdrivlib::Timekeeper ui_event_tm;
};

} // namespace MetaModule
