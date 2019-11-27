#pragma once
#include "audio.hh"
#include "leds.hh"
#include "touch.hh"
#include "debug.h"
#include "controls.hh"

class Params {
public:
	float freq[2];
	float res[2];

public:
	void read(Controls& controls);
	void update(Controls& controls);
};


class Ui {
public:
	Controls controls;
	Params params;
	Audio audio;
	LedCtl leds;

public:
	Ui() {
		last_update_tick_= HAL_GetTick();

		leds.freq1.set_background(Colors::pink);
		leds.res1.set_background(Colors::cyan);

		// leds.res1.set_glow(Colors::red, 2);

	}

	void update() {
		leds.freq1.set_background(Colors::red.blend(Colors::off, params.freq[0]));

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
