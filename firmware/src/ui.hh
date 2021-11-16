#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"

namespace MetaModule
{
static __attribute__((section(".ddma"))) std::array<lv_color_t, ScreenConf::width * ScreenConf::height> buf_1;
static __attribute__((section(".ddma"))) std::array<lv_color_t, ScreenConf::width * ScreenConf::height> buf_2;

class Ui {
private:
	PageManager page_manager;
	ParamQueue &param_queue;

	Params params;
	MetaParams metaparams;
	PatchList patch_list;

	UiAudioMailbox &mbox;

	static inline LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, buf_1, buf_2};

public:
	Ui(PatchPlayer &pp, ParamQueue &pc, UiAudioMailbox &uiaudiomailbox)
		: param_queue{pc}
		, mbox{uiaudiomailbox}
		, page_manager{patch_list, pp, params, metaparams, uiaudiomailbox} {
	}

	void start() {

		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams, buf_1);
		page_manager.init();

		page_update_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz
				.priority1 = 1,
				.priority2 = 2,
			},
			[&] { update_ui_task(); });
		page_update_tm.start();
		MMDisplay::start();
	}

	void update() {
		if (MMDisplay::is_ready()) {
			// Debug::Pin1::high();
			MMDisplay::clear_ready();
			// v8:
			// lv_timer_handler();
			lv_task_handler();
			// Debug::Pin1::low();
		}
	}

	void update_ui_task() {
		// Debug::Pin3::high();
		param_queue.read_sync(&params, &metaparams);
		handle_rotary();
		page_manager.update_current_page();
		// Debug::Pin3::low();
	}

	void handle_rotary() {
		auto rotary_pushed_turned = metaparams.rotary_pushed.use_motion();
		if (rotary_pushed_turned < 0)
			page_manager.prev_page();
		if (rotary_pushed_turned > 0)
			page_manager.next_page();
	}

private:
	mdrivlib::Timekeeper page_update_tm;
};
} // namespace MetaModule
