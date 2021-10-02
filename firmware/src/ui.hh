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

public:
	Ui(PatchPlayer &pp, ParamQueue &pc, UiAudioMailbox &uiaudiomailbox)
		: param_queue{pc}
		, mbox{uiaudiomailbox}
		, pages{patch_list, pp, params, metaparams, uiaudiomailbox}
	{
		MMDisplay::init();
	}

	void start()
	{
		params.clear();
		metaparams.clear();
		// register_printf_destination(screen);
		pages.init();

		MMDisplay::start();

		slider_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz
				.priority1 = 2,
				.priority2 = 2,
			},
			[&] { update_ui(); });
		slider_tm.start();
	}

	void update_ui()
	{
		using namespace mdrivlib;
		param_queue.read_sync(&params, &metaparams);
		handle_rotary();

		// if (HWSemaphore<ScreenFrameWriteLock>::is_locked()) {
		// 	return;
		// }

		// HWSemaphore<ScreenFrameBufLock>::lock();
		pages.update_current_page();

		// screen.flush_cache();
		// HWSemaphore<ScreenFrameBufLock>::unlock();
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
	Timekeeper slider_tm;
};
} // namespace MetaModule
