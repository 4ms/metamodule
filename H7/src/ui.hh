#pragma once
#include "Adafruit_GFX_Library/Fonts/FreeMono12pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSansBold18pt7b.h"
#include "audio.hh"
#include "debug.hh"
#include "drivers/i2c.hh"
#include "leds.hh"
#include "params.hh"
#include "screen.hh"
#include "sys/alloc_buffer.hh"
#include "sys/mem_usage.hh"

template<unsigned AnimationUpdateRate = 100>
class Ui {
public:
	Params &params;
	LedCtl<AnimationUpdateRate> &leds;
	Screen &screen;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(Params &p, LedCtl<AnimationUpdateRate> &l, Screen &s)
		: params{p}
		, leds{l}
		, screen{s}
	{}

	Color bgcolor = Colors::pink;
	Color patch_fgcolor = Colors::blue;
	Color load_fgcolor = Colors::cyan;
	Color pots_fgcolor = Colors::green;

	void start()
	{
		screen.init();
		// Debug::Pin2::high();
		screen.fill(bgcolor);
		// Debug::Pin2::low();

		draw_patch_name();
		draw_audio_load();

		leds.start();
		params.controls.start();

		leds.but[0].set_background(Colors::grey);
		leds.but[1].set_background(Colors::grey);
		leds.clockLED.set_background(Colors::blue.blend(Colors::black, 0.5f));
		leds.rotaryLED.set_background(Colors::grey);

		// Todo: set led_update_task_conf.update_rate_Hz to be a factor of AnimationUpdateRate and Hz
		//
		led_update_task.init(led_update_task_conf, [this]() { leds.update(); });
		led_update_task.start();
	}

	uint32_t last_screen_update = 0;
	void update()
	{
		if (params.buttons[0].is_pressed())
			leds.but[0].set_background(Colors::red);
		else
			leds.but[0].set_background(Colors::grey);

		if (params.buttons[1].is_pressed())
			leds.but[1].set_background(Colors::blue);
		else
			leds.but[1].set_background(Colors::grey);

		if (params.rotary_button.is_pressed())
			leds.rotaryLED.set_background(Colors::blue);
		else
			leds.rotaryLED.set_background(Colors::grey);

		uint32_t now = HAL_GetTick();
		if (now - last_screen_update > 100) {
			last_screen_update = now;
			draw_audio_load();
			draw_pot_values();
		}

		if (params.should_redraw_patch) {
			params.should_redraw_patch = false;
			draw_patch_name();
		}

		// screen.setTextColor(Colors::white.Rgb565());
		// screen.setTextSize(1);

		// if (params.buttons[1].is_just_pressed())
		// 	leds.but[1].set_background(Colors::red);

		// if (params.buttons[1].is_just_released())
		// 	leds.but[1].set_background(Colors::blue);

		// if (params.buttons[0].is_just_pressed())
		// 	leds.but[0].set_background(Colors::red);

		// if (params.buttons[0].is_just_released())
		// 	leds.but[0].set_background(Colors::blue);

		// if (params.rotary_button.is_just_pressed())
		// 	leds.rotaryLED.set_background(Colors::white);

		// if (params.rotary_button.is_just_released())
		// 	leds.rotaryLED.set_background(Colors::blue);
	}

private:
	Timekeeper led_update_task;

	void draw_patch_name()
	{
		// Debug::Pin2::high();
		screen.fillRect(0, 30, 240, 150, bgcolor.Rgb565());
		// Debug::Pin2::low();
		screen.setFont(&FreeSansBold18pt7b);
		screen.setTextColor(patch_fgcolor.Rgb565());
		screen.setTextSize(1);
		uint32_t y = 60;
		for (int i = 1; i < params.cur_patch().num_modules; i++) {
			screen.setCursor(10, y);
			// Debug::Pin2::high();
			screen.print(params.cur_patch().modules_used[i].name);
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
		screen.print(params.audio_load, 10);
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
			// screen.print((uint16_t)(i < 4 ? params.cvjacks[i] * 100 : params.knobs[i - 4] * 100));
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
