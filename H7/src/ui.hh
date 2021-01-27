#pragma once
#include "audio.hh"
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
		leds.update();

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
