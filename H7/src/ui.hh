#pragma once
#include "audio.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/memory_transfer.hh"
#include "leds.hh"
#include "m7/hsem_handler.hh"
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
	PatchList &patchlist;
	uint32_t last_changed_page_tm = 0;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(PatchList &pl,
	   PatchPlayer &pp,
	   ParamCache &pc,
	   UiAudioMailbox &uiaudiomailbox,
	   LedFrame<AnimationUpdateRate> &l,
	   MMScreenConf::FrameBufferT &screenbuf)
		: leds{l}
		, screen{screenbuf}
		, param_cache{pc}
		, mbox{uiaudiomailbox}
		, pages{pl, pp, params, metaparams, screen}
		, patchlist{pl}
	{}

	void start()
	{
		params.clear();
		metaparams.clear();
		screen.init();
		pages.init();

		leds.but[0].set_background(Colors::grey);
		leds.but[1].set_background(Colors::grey);
		leds.clockLED.set_background(Colors::blue.blend(Colors::black, 0.5f));
		leds.rotaryLED.set_background(Colors::green);

		// Todo: led animation rate depends on I2C rate... not easy to set  maybe we can have it self-calibrate against
		// the SysTick?
		// Otherwise we can use this: but we'd have to make it thread-safe we could just have
		// update_animation() just update the TriOsc and fade (but not write actual color to the framebuffer)
		// led_update_task.init(led_update_animation_task_conf, [this]() { leds.update_animation(); });
		// led_update_task.start();
		HWSemaphoreCoreHandler::register_channel_ISR<LEDFrameBufLock>([&]() {
			if (HWSemaphore<LEDFrameBufLock>::lock() == HWSemaphoreFlag::LockedOk) {
				update_led_states();
				// Todo: doesn't this cause the ISR to trigger itself?
				HWSemaphore<LEDFrameBufLock>::unlock();
			}
		});
		HWSemaphore<LEDFrameBufLock>::enable_channel_ISR();

		screen_draw_task.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 33, // =  33Hz
				.priority1 = 3,
				.priority2 = 3,

			},
			[&]() { refresh_screen(); });
		screen_draw_task.start();
	}

	void refresh_screen()
	{
		param_cache.read_sync_metaparams(&metaparams);
		param_cache.read_sync_params(&params);
		update();
		if (HWSemaphore<ScreenFrameWriteLock>::is_locked()) {
			return;
		}
		HWSemaphore<ScreenFrameBufLock>::lock();
		pages.display_current_page();
		screen.flush_cache();
		HWSemaphore<ScreenFrameBufLock>::unlock();
	}

	void update()
	{
		auto rotary = metaparams.rotary.use_motion();
		if (rotary < 0) {
			pages.prev_page();
		}

		if (rotary > 0) {
			pages.next_page();
		}

		auto rotary_pushed = metaparams.rotary_pushed.use_motion();
		if (rotary_pushed) {
			auto now_tm = HAL_GetTick();
			if (now_tm - last_changed_page_tm > 100) {
				last_changed_page_tm = now_tm;
				if (rotary_pushed < 0)
					mbox.new_patch_index = patchlist.cur_patch_index() - 1;
				if (rotary_pushed > 0)
					mbox.new_patch_index = patchlist.cur_patch_index() + 1;
				mbox.load_new_patch = true;
			}
		}
	}

private:
	Timekeeper screen_draw_task;

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
