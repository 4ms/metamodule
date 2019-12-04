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
	LedCtl leds;

public:
	Ui() {
		last_update_tick_= HAL_GetTick();

		// leds.res1.set_glow(Colors::red, 2);

	}

	void update() {
		leds.freq1.set_background(Colors::off.blend(Colors::white, params.freq[0]));
		leds.res1.set_background(Colors::off.blend(Colors::white, params.res[0]));

		leds.freq2.set_background(Colors::off.blend(Colors::white, params.freq[1]));
		leds.res2.set_background(Colors::off.blend(Colors::white, params.res[1]));

		static uint8_t mode[2] = {0};

		leds.mode[0].set_background(Colors::off);
		leds.mode[1].set_background(Colors::off);
		leds.mode[2].set_background(Colors::off);
		leds.mode[3].set_background(Colors::off);
		leds.mode[4].set_background(Colors::off);

		//Todo: add color
		leds.mode[mode[0]].set_background(Colors::red);
		leds.mode[mode[1]].set_background(Colors::blue);

		//Todo: timing on this is poor, respond only to interrupt pin
		if ((last_update_tick_ - HAL_GetTick()) > 2000) {

			if (controls.pads.touched(2))
				if (++mode[0]>=4) mode[0]=0;

			if (controls.pads.touched(0))
				if (++mode[1]>=4) mode[1]=0;

			last_update_tick_ = HAL_GetTick();
		}

		leds.update();
	}

	uint32_t last_update_tick_;
};
