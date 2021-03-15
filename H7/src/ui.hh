#pragma once
#include "Adafruit_GFX_Library/Fonts/FreeMono12pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSansBold18pt7b.h"
#include "audio.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/memory_transfer.hh"
#include "leds.hh"
#include "m7/hsem_handler.hh"
#include "params.hh"
#include "patchlist.hh"
#include "screen.hh"
// #include "screen2.hh"
#include "sys/alloc_buffer.hh"
#include "sys/mem_usage.hh"

namespace MetaModule
{
template<unsigned AnimationUpdateRate = 100>
class Ui {
public:
	Params &params;
	PatchList &patch_list;
	LedFrame<AnimationUpdateRate> &leds;
	// Screen screen;
	ScreenFrameBuffer screen;
	ScreenFrameWriter screen_writer;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(Params &p,
	   PatchList &pl,
	   LedFrame<AnimationUpdateRate> l,
	   MMScreenConf::FrameBufferT &screenbuf,
	   MMScreenConf::FrameBufferT *screen_writer_buf)
		: params{p}
		, patch_list{pl}
		, leds{l}
		, screen{screenbuf}
		, screen_writer{screen_writer_buf}
	{}

	Color bgcolor = Colors::pink;
	Color patch_fgcolor = Colors::blue.blend(Colors::white, 0.5f);
	Color load_fgcolor = Colors::cyan;
	Color pots_fgcolor = Colors::red;

	void start()
	{
		// // HWSemaphore<ScreenFrameBuf1Lock>::lock();
		screen.init();
		screen.fill(bgcolor);
		draw_patch_name();
		draw_audio_load();

		// // HWSemaphore<ScreenFrameBuf1Lock>::unlock();

		screen_writer.init();
		screen_writer.transfer_buffer_to_screen();

		HAL_Delay(40);
		screen.fill(pots_fgcolor);
		screen_writer.transfer_buffer_to_screen();

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
		HWSemaphoreCoreHandler::register_channel_ISR<LEDFrameBufLock>([&]() { update_led_states(); });
		HWSemaphore<LEDFrameBufLock>::enable_channel_ISR();
	}

	uint32_t last_screen_update = 0;
	void update()
	{
		uint32_t now = HAL_GetTick();
		if (now - last_screen_update > 100) {
			last_screen_update = now;
			draw_audio_load();
			draw_pot_values();
			if (patch_list.should_redraw_patch) {
				patch_list.should_redraw_patch = false;
				draw_patch_name();
			}
			// screen_writer.transfer_buffer_to_screen();
		}
	}

private:
	Timekeeper led_update_task;

	void update_led_states()
	{
		if (params.buttons[0].is_pressed())
			leds.but[0].set_background(Colors::red);
		else
			leds.but[0].set_background(Colors::green);

		if (params.buttons[1].is_pressed())
			leds.but[1].set_background(Colors::blue);
		else
			leds.but[1].set_background(Colors::orange);

		if (params.rotary_button.is_pressed())
			leds.rotaryLED.set_background(Colors::blue);
		else
			leds.rotaryLED.set_background(Colors::green);

		leds.rotaryLED.breathe(Colors::magenta, 1);
		leds.clockLED.breathe(Colors::green, 0.75f);
		leds.but[0].breathe(Colors::blue, 0.5f);
		leds.but[1].breathe(Colors::white, 0.01f);

		leds.update_animation();
	}

	void draw_patch_name()
	{
		// Debug::Pin2::high();
		screen.fillRect(0, 30, 240, 150, bgcolor.Rgb565());
		// Debug::Pin2::low();
		screen.setFont(&FreeSansBold18pt7b);
		screen.setTextColor(patch_fgcolor.Rgb565());
		screen.setTextSize(1);
		uint32_t y = 60;
		for (int i = 1; i < patch_list.cur_patch().num_modules; i++) {
			screen.setCursor(10, y);
			// Debug::Pin2::high();
			screen.print(patch_list.cur_patch().modules_used[i].name);
			// Debug::Pin2::low();
			y += 35;
		}
	}

	void draw_audio_load()
	{
		screen.setTextColor(load_fgcolor.Rgb565(), bgcolor.Rgb565());
		screen.setTextSize(2);
		screen.setFont(NULL);
		screen.setCursor(0, 10);
		screen.print(patch_list.audio_load, 10);
		screen.print("% ");
		screen.print(get_heap_size() / 1024, 10);
		screen.print("kb ");
		screen.print(BigAlloc<Ui>::get_memory_usage() / 1024, 10);
		screen.print("kb   ");
	}

	void draw_pot_values()
	{
		// Debug::Pin2::high();
		screen.setTextColor(pots_fgcolor.Rgb565(), bgcolor.Rgb565());
		screen.setTextSize(2);
		screen.setFont(NULL);
		int y = 180;
		for (int i = 0; i < 12; i++) {
			screen.setCursor((i & 0b11) * 60, y);
			if (i < 4)
				screen.print((uint16_t)(params.cvjacks[i] * 100));
			else
				screen.print((uint16_t)(params.knobs[i - 4] * 100));

			screen.print("  ");
			if (i == 3 || i == 7)
				y += 20;
		}

		// Debug::Pin2::low();
	}
	void draw_test_squares()
	{
		// Should see a 1-pixel border around the 4-square, and a 1-pixel gap between squares
		screen.fillRect(0, 0, 44, 44, Colors::purple.Rgb565());
		screen.fillRect(1, 1, 20, 20, Colors::red.Rgb565());
		screen.fillRect(1, 23, 20, 20, Colors::green.Rgb565());
		screen.fillRect(23, 1, 20, 20, Colors::orange.Rgb565());
		screen.fillRect(23, 23, 20, 20, Colors::grey.Rgb565());

		screen.fillRect(196, 196, 44, 44, Colors::white.Rgb565());
		screen.fillRect(219, 219, 20, 20, Colors::yellow.Rgb565());
		screen.fillRect(197, 219, 20, 20, Colors::purple.Rgb565());
		screen.fillRect(197, 197, 20, 20, Colors::pink.Rgb565());
		screen.fillRect(219, 197, 20, 20, Colors::cyan.Rgb565());
	}
};
} // namespace MetaModule
