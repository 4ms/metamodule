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
	Params params{controls};
	LedCtl leds;

public:
	Ui() {
		// leds.res1.set_glow(Colors::red, 2);
	}

	void update() {
		leds.freq1.set_background(Colors::off.blend(Colors::white, params.freq[0]));
		leds.res1.set_background(Colors::off.blend(Colors::white, params.res[0]));

		leds.freq2.set_background(Colors::off.blend(Colors::white, params.freq[1]));
		leds.res2.set_background(Colors::off.blend(Colors::white, params.res[1]));

		leds.mode[0].set_background(Colors::off);
		leds.mode[1].set_background(Colors::off);
		leds.mode[2].set_background(Colors::off);
		leds.mode[3].set_background(Colors::off);
		leds.mode[4].set_background(Colors::off);

		//Todo: add color
		leds.mode[params.mode[0]].set_background(Colors::red);
		leds.mode[params.mode[1]].set_background(Colors::blue);


		leds.update();
	}

	void handle_sensor_queue() {
		controls.pads.handle_message_queue();
	}

};
