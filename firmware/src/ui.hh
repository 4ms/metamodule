#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"

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

		ui_update_tmr.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz
				.priority1 = 2,
				.priority2 = 2,
			},
			[&] { update_ui(); });
		ui_update_tmr.start();
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
	Timekeeper ui_update_tmr;
};
} // namespace MetaModule
