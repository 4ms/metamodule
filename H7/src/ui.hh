#pragma once
#include "audio.hh"
#include "debug.hh"
#include "drivers/i2c.hh"
#include "leds.hh"
#include "params.hh"

template<unsigned AnimationUpdateRate = 100>
class Ui {
public:
	Params &params;
	LedCtl<AnimationUpdateRate> &leds;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(Params &p, LedCtl<AnimationUpdateRate> &l /*, Screen &s*/)
		: params{p}
		, leds{l}
	//, screen{s}
	{}

	void start()
	{
		leds.start_it_mode();
		params.controls.start();

		leds.but[0].set_background(Colors::yellow);
		leds.but[0].breathe(Colors::purple, 4 * Hz);

		leds.but[1].set_background(Colors::white);
		leds.but[1].breathe(Colors::red, 2 * Hz);

		leds.clockLED.set_background(Colors::blue);
		leds.clockLED.breathe(Colors::pink, 3 * Hz);

		leds.rotaryLED.set_background(Colors::blue);
		leds.rotaryLED.breathe(Colors::green, 0.5f * Hz);

		// Todo: set led_update_task_conf.update_rate_Hz to be a factor of AnimationUpdateRate and Hz
		//
		led_update_task.init(led_update_task_conf, [this]() { leds.update(); });
		led_update_task.start();
	}

	void update()
	{
		// Todo: set led colors/flash/breathe/background etc based on Params
		// leds.update();
	}

private:
	Timekeeper led_update_task;
};
