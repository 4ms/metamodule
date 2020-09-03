#pragma once
#include "controls.hh"
#include <stm32f7xx.h>

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{
	}

	float freq[2];
	float res[2];
	uint8_t mode[2] = {0};

public:
	void update();

private:
	static const inline uint8_t kNumFX = 5; //Todo: how to enforce this matches size of AudioFXList?
	Controls &controls;
};

