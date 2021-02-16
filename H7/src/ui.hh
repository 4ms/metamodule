#pragma once
#include "Fonts/FreeMono12pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "audio.hh"
#include "debug.hh"
#include "drivers/i2c.hh"
#include "leds.hh"
#include "params.hh"
#include "screen.hh"

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

	void start()
	{
		screen.init();
		screen.fill(Colors::pink);

		draw_patch_name();

		screen.setFont(&FreeMono12pt7b);
		screen.setTextColor(ST77XX::WHITE);
		screen.setTextSize(1);
		screen.setCursor(2, 20);
		screen.print("Load:");

		screen.setCursor(80, 20);
		screen.print(params.audio_load, 10);

		leds.start_it_mode();
		params.controls.start();

		leds.but[0].set_background(Colors::yellow);

		leds.but[1].set_background(Colors::white);

		leds.clockLED.set_background(Colors::blue);

		leds.rotaryLED.set_background(Colors::blue);

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
			leds.but[0].set_background(Colors::white);

		if (params.buttons[1].is_pressed())
			leds.but[1].set_background(Colors::blue);
		else
			leds.but[1].set_background(Colors::white);

		if (params.rotary_button.is_pressed())
			leds.rotaryLED.set_background(Colors::blue);
		else
			leds.rotaryLED.set_background(Colors::white);

		uint32_t now = HAL_GetTick();
		if (now - last_screen_update > 1000) {
			last_screen_update = now;
			draw_audio_load();
		}

		if (params.should_redraw_patch) {
			params.should_redraw_patch = false;
			draw_patch_name();
		}

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
		screen.fillRect(0, 30, 240, 210, Colors::pink.Rgb565());
		screen.setFont(&FreeSansBold18pt7b);
		screen.setTextColor(ST77XX::WHITE);
		screen.setTextSize(1);
		uint32_t y = 60;
		for (int i = 1; i < params.cur_patch().num_modules; i++) {
			screen.setCursor(10, y);
			screen.print(params.cur_patch().modules_used[i].name);
			y += 40;
		}
	}

	void draw_audio_load()
	{
		screen.fillRect(80, 0, 60, 25, Colors::pink.Rgb565());
		screen.setFont(&FreeMono12pt7b);
		screen.setTextColor(ST77XX::WHITE);
		screen.setTextSize(1);
		screen.setCursor(80, 20);
		screen.print(params.audio_load, 10);
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
