#pragma once
#include "controls.hh"
#include <stm32f7xx.h>

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{}

	float freq[2];
	float res[2];
	uint8_t mode[2] = {0};
	float freq_knob_pos[2] = {0.5f, 0.5f};
	float res_knob_pos[2] = {0.5f, 0.5f};

public:
	void update();
	Controls &controls;

private:
	static const inline float kFreqScaling =
		100.0f; // Todo: figure out what this should equal, and put it somewhere sensible
	static const inline float kResScaling = 100.0f;
	static const inline uint8_t kNumFX = 5; // Todo: how to enforce this matches size of AudioFXList?
};

