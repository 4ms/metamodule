#pragma once
#include "audio.hh"
//#include "debug.h"
#include "i2c.hh"
#include "leds.hh"
#include "params.hh"

class Ui {
public:
	Params &params;
	LedCtl &leds;

public:
	Ui(Params &p, LedCtl &l)
		: params{p}
		, leds{l}
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
	}
};
