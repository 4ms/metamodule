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
	Ui(Params &p, LedCtl &l /*, Screen &s*/)
		: params{p}
		, leds{l}
	//, screen{s}
	{}

	void start()
	{
		leds.start_it_mode();
		params.controls.start();
	}

	void update()
	{
		// Set LED colors

		leds.but[0].set_background(Colors::yellow);
		leds.but[1].set_background(Colors::white);
		leds.clockLED.set_background(Colors::yellow);
		leds.rotaryLED.set_background(Colors::purple);
		leds.update();

		// Todo: set a timer to manage refresh
		static uint32_t last_update = 0;
		if (HAL_GetTick() - last_update > 15) {
			last_update = HAL_GetTick();
			Debug::set_0(true);
			leds.refresh();
			Debug::set_0(false);
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
