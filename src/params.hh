#pragma once
#include "controls.hh"
#include "util/accel_param.hh"
#include <stm32f7xx.h>

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{}

	float freq[2];
	float res[2];
	uint8_t mode[2] = {0};


public:
	void update();
	Controls &controls;

private:
	static const int kFreqKnob_Accel = 150;
	static const int kFreqKnob_Weight = 200;
	static const int kFreqKnonb_CatchupWeight = 333;
	AccelParam<kFreqKnob_Accel, kFreqKnob_Weight, kFreqKnonb_CatchupWeight> smoothed_freq[2] = {0.5f, 0.5f};

	static const int kResKnob_Accel = 350;
	static const int kResKnob_Weight = 200;
	static const int kResKnonb_CatchupWeight = 333;
	AccelParam<kResKnob_Accel, kResKnob_Weight, kResKnonb_CatchupWeight> smoothed_res[2] = {0.5f, 0.5f};

	static const inline uint8_t kNumFX = 5; // Todo: how to enforce this matches size of AudioFXList?
};

