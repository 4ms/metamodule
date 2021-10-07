#pragma once
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/timekeeper.hh"
#include "hsem_handler.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"
#include "sys/alloc_buffer.hh"
#include "sys/mem_usage.hh"

namespace MetaModule
{

class Ui {
private:
	PageManager pages;
	ParamQueue &param_queue;

	Params params;
	MetaParams metaparams;
	PatchList patch_list;

	UiAudioMailbox &mbox;

	static inline LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input};

public:
	Ui(PatchPlayer &pp, ParamQueue &pc, UiAudioMailbox &uiaudiomailbox)
		: param_queue{pc}
		, mbox{uiaudiomailbox}
		, pages{patch_list, pp, params, metaparams, uiaudiomailbox}
	{
		MMDisplay::init(metaparams);
	}

	void start()
	{
		MMDisplay::start();

		params.clear();
		metaparams.clear();
		// register_printf_destination(screen);
		pages.init();

		page_update_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz
				.priority1 = 1,
				.priority2 = 2,
			},
			[&] { update_ui_task(); });
		page_update_tm.start();
	}

	void update()
	{
		if (MMDisplay::is_ready()) {
			Debug::Pin1::high();
			MMDisplay::clear_ready();
			//v8:
			//lv_timer_handler();
			lv_task_handler();
			Debug::Pin1::low();
		}
	}

	void update_ui_task()
	{
		Debug::Pin3::high();
		param_queue.read_sync(&params, &metaparams);
		handle_rotary();
		pages.update_current_page();
		Debug::Pin3::low();
	}

	void handle_rotary()
	{
		auto rotary_pushed_turned = metaparams.rotary_pushed.use_motion();
		if (rotary_pushed_turned < 0)
			pages.prev_page();
		if (rotary_pushed_turned > 0)
			pages.next_page();
	}

private:
	Timekeeper page_update_tm;
};
} // namespace MetaModule
