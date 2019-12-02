#pragma once
#include "audio.hh"
#include "leds.hh"
#include "touch.hh"
#include "debug.h"
#include "controls.hh"
#include "params.hh"

class Ui {
public:
	Controls controls;
	Params params;
	Audio audio;
	LedCtl leds;

public:
	Ui() {
		last_update_tick_= HAL_GetTick();

		// leds.res1.set_glow(Colors::red, 2);

	}

	void update() {
		// leds.freq1.set_background(Colors::white.blend(Colors::off, params.freq[0]));
		// leds.res1.set_background(Colors::white.blend(Colors::off, params.res[0]));
		leds.freq1.set_background(Colors::grey);
		leds.res1.set_background(Colors::grey);

		leds.freq2.set_background(Colors::grey);
		leds.res2.set_background(Colors::grey);

		leds.mode[0].set_background(Colors::grey);
		leds.mode[1].set_background(Colors::grey);
		leds.mode[2].set_background(Colors::grey);
		leds.mode[3].set_background(Colors::grey);
		leds.mode[4].set_background(Colors::grey);

		// if ((last_update_tick_ - HAL_GetTick()) > 500) {

		// 	if (params.controls.pads.touched(0))
		// 		leds.freq1.set_background(Colors::green);
		// 	else
		// 		leds.freq1.set_background(Colors::blue);

		// 	if (params.controls.pads.touched(1))
		// 		leds.res1.set_background(Colors::green);
		// 	else
		// 		leds.res1.set_background(Colors::blue);
		// 	last_update_tick_ = HAL_GetTick();
		// }

		leds.update();
	}

	uint32_t last_update_tick_;
};
