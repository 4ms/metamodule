#pragma once
#include "audio.hh"
#include "debug.hh"
#include "drivers/i2c.hh"
#include "leds.hh"
#include "params.hh"

class Ui {
public:
	Params &params;
	LedCtl &leds;

public:
	static constexpr uint32_t kUpdateRate_Hz = 125;
	static constexpr uint32_t kUpdateRate_ms = 1000U / (kUpdateRate_Hz);
	Ui(Params &p, LedCtl &l /*, Screen &s*/)
		: params{p}
		, leds{l}
	//, screen{s}
	{}

	void start()
	{
		leds.start_it_mode();
		params.controls.start();

		leds.but[0].set_background(Colors::yellow);
		leds.but[1].set_background(Colors::white);
		leds.clockLED.set_background(Colors::yellow);
		leds.rotaryLED.set_background(Colors::purple);

		leds.but[0].breathe(Colors::purple, 4 * kUpdateRate_Hz);
		// leds.but[1].breathe(Colors::red, 2 * kUpdateRate_Hz);
		leds.clockLED.breathe(Colors::pink, 3 * kUpdateRate_Hz);
		leds.rotaryLED.breathe(Colors::green, 2 * kUpdateRate_Hz);
	}

	void update()
	{
		// Todo: set a timer to manage refresh
		// static uint32_t last_update = 0;
		static uint32_t next_client = 0;

		// Todo: add queue to i2c
		if (!params.controls.i2c.is_ready()) {
			// if (HAL_GetTick() - last_update > kUpdateRate_ms) { // why is this 8ms instead of 16ms?
			// last_update = HAL_GetTick();
			switch (next_client) {
				case 0:
					Debug::set_3(true);
					leds.update();
					leds.refresh();
					Debug::set_3(false);
					next_client = 1;
					break;
				case 1:
					Debug::set_2(true);
					// params.controls.potadc.select_channel0_source
					// initiate read
					Debug::set_2(false);
					next_client = 0;
					break;
			}
		}

		// Update screen

		// for (int i = 0; i < 2; i++) {
		// Color freq_col, res_col;
		// if (params.knob_sel[i] == 0) {
		// 	freq_col = i ? Colors::blue : Colors::red;
		// 	res_col = Colors::grey;
		// } else {
		// 	freq_col = Colors::grey;
		// 	res_col = i ? Colors::blue : Colors::red;
		// }
		// leds.freq[i].set_background(Colors::off.blend(freq_col, params.knobs[i * 2 + 0] * 0.5f));
		// leds.res[i].set_background(Colors::off.blend(res_col, params.knobs[i * 2 + 1] * 0.5f));

		// if (params.controls.mode_button[i].is_pressed())
		// 	leds.but[i].set_background(Colors::white);
		// else
		// 	leds.but[i].set_background(Colors::off);
		// }

		// for (int i = 0; i < 5; i++) {
		// 	leds.mode[i].set_background(Colors::off);
		// 	if (i == params.fx_mode[0])
		// 		leds.mode[i].add_background(Colors::red);
		// 	if (i == params.fx_mode[1])
		// 		leds.mode[i].add_background(Colors::blue);
		// }
	}
};
