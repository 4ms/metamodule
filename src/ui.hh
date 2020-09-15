#pragma once
#include "audio.hh"
#include "controls.hh"
//#include "debug.h"
#include "i2c.hh"
#include "leds.hh"
#include "params.hh"

class Ui {
public:
	Controls controls;
	Params params{controls};
	LedCtl leds;

public:
	Ui(I2CPeriph &i2c)
		: leds{i2c}
	{}

	void update()
	{
		for (int i = 0; i < 2; i++) {
			leds.freq[i].set_background(Colors::off.blend(Colors::white, params.freq[i]));
			leds.res[i].set_background(Colors::off.blend(Colors::white, params.res[i]));
		}
		for (int i = 0; i < 5; i++) {
			leds.mode[i].set_background(Colors::off);
			if (i == params.mode[0])
				leds.mode[i].add_background(Colors::red);
			if (i == params.mode[1])
				leds.mode[i].add_background(Colors::blue);
		}
		leds.update();
	}
};
