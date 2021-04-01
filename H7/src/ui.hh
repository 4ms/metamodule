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
public:
	LedFrame<AnimationUpdateRate> &leds;
	ScreenFrameBuffer screen;
	PageManager pages;
	ParamCache &param_cache;
	Params params;
	MetaParams metaparams;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(PatchList &pl,
	   PatchPlayer &pp,
	   ParamCache &pc,
	   LedFrame<AnimationUpdateRate> &l,
	   MMScreenConf::FrameBufferT &screenbuf)
		: leds{l}
		, screen{screenbuf}
		, param_cache{pc}
		, pages{pl, pp, params, screen}
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
	}

private:
	Timekeeper screen_draw_task;

	void update_led_states()
	{
		// Debug::Pin1::high();
		// if (param_cache.read_sync_params().buttons[0].is_pressed())
		// 	leds.but[0].set_background(Colors::red);
		// else
		// 	leds.but[0].set_background(Colors::green);

		// if (param_cache.read_sync_params().buttons[1].is_pressed())
		// 	leds.but[1].set_background(Colors::blue);
		// else
		// 	leds.but[1].set_background(Colors::orange);

		// if (param_cache.read_sync_metaparams().rotary_button.is_pressed())
		// 	leds.rotaryLED.set_background(Colors::blue);
		// else
		// 	leds.rotaryLED.set_background(Colors::green);

		leds.rotaryLED.breathe(Colors::magenta, 1);
		leds.clockLED.breathe(Colors::green, 0.75f);
		leds.but[0].breathe(Colors::blue, 0.5f);
		leds.but[1].breathe(Colors::white, 0.1f);

		leds.update_animation();
		// Debug::Pin1::low();
	}
};
} // namespace MetaModule
