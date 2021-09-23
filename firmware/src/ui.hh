#pragma once
#include "conf/hsem_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/timekeeper.hh"
#include "hsem_handler.hh"
#include "leds.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"
#include "sys/alloc_buffer.hh"
#include "sys/mem_usage.hh"

namespace MetaModule
{

template<unsigned AnimationUpdateRate = 100>
class Ui {
private:
	LedFrame<AnimationUpdateRate> &leds;
	ScreenFrameBuffer screen;
	PageManager pages;

	// Ui stores its own copy of params and metaparams because while it's accessing these in order to draw the screen,
	// respond to rotary motion, etc. the audio process loop might interrupt it and update the values in ParamCache
	ParamCache &param_cache;
	Params params;
	MetaParams metaparams;

	UiAudioMailbox &mbox;

	// Todo remove once we have pages editing the cur_patch
	PatchPlayer &player;
	PatchList &patch_list;
	uint32_t last_changed_page_tm = 0;

public:
	Ui(PatchList &pl,
	   PatchPlayer &pp,
	   ParamCache &pc,
	   UiAudioMailbox &uiaudiomailbox,
	   LedFrame<AnimationUpdateRate> &l,
	   MMScreenBufferConf::FrameBufferT &screenbuf)
		: leds{l}
		, screen{screenbuf}
		, param_cache{pc}
		, mbox{uiaudiomailbox}
		, pages{pl, pp, params, metaparams, uiaudiomailbox, screen}
		, patch_list{pl}
		, player{pp}
	{}

	void start()
	{
		params.clear();
		metaparams.clear();

		screen.init();
		register_printf_destination(screen);
		pages.init();

		//Disabling LEDs for now, until we figure out how to integrate them in patches
		// Mini:
		// leds.but[0].set_background(Colors::grey);
		// leds.but[1].set_background(Colors::grey);
		// leds.clockLED.set_background(Colors::blue.blend(Colors::black, 0.5f));
		// leds.rotaryLED.set_background(Colors::green);

		// Todo: led animation rate depends on I2C rate... not easy to set  maybe we can have it self-calibrate against
		// the SysTick?
		// Otherwise we can use this: but we'd have to make it thread-safe we could just have
		// update_animation() just update the TriOsc and fade (but not write actual color to the framebuffer)
		// led_update_task.init(led_update_animation_task_conf, [this]() { leds.update_animation(); });
		// led_update_task.start();
		// HWSemaphoreCoreHandler::register_channel_ISR<LEDFrameBufLock>([&]() {
		// 	if (HWSemaphore<LEDFrameBufLock>::lock() == HWSemaphoreFlag::LockedOk) {
		// 		// update_led_states();
		// 		// Todo: doesn't this cause the ISR to trigger itself?
		// 		HWSemaphore<LEDFrameBufLock>::unlock();
		// 	}
		// });
		// HWSemaphore<LEDFrameBufLock>::enable_channel_ISR();

		update_ui_task.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 33, // =  33Hz
				.priority1 = 2,
				.priority2 = 2,

			},
			[&]() { update_ui(); });
		update_ui_task.start();
	}

	void update_ui()
	{
		Debug::Pin4::high();
		param_cache.read_sync(&params, &metaparams);
		handle_rotary();
		Debug::Pin4::low();

		if (HWSemaphore<ScreenFrameWriteLock>::is_locked()) {
			return;
		}

		HWSemaphore<ScreenFrameBufLock>::lock();
		Debug::Pin1::high();
		pages.display_current_page();
		screen.flush_cache();
		Debug::Pin1::low();
		HWSemaphore<ScreenFrameBufLock>::unlock();
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
	Timekeeper update_ui_task;

	void update_led_states()
	{
		// Todo: audio process reads led brightness from coreModules, for each mapped LED
		// and stores that in UiAudioMailbox
		// UI uses that data to set LEDs here
		// Todo: confirm thread-safety: m4 unlock -> update_led_states(), but will wait until audio.process() is done
		// [right?]
		// ... can audio.process() interrupt this?
		//
		leds.rotaryLED.set_background(Colors::green);
		leds.rotaryLED.breathe(Colors::magenta, 0.5f);

		leds.update_animation();
	}
};
} // namespace MetaModule
