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
	float freq_cv_atten[2] = {1.f, 1.f};
	float res_cv_atten[2] = {1.f, 1.f};
	uint8_t fx_mode[2] = {0};

	enum SelectedKnob { FREQ, RES };
	SelectedKnob knob_sel[2] = {FREQ, FREQ};

public:
	void update();
	Controls &controls;

private:
	//Adjust these as needed:
	static const int kFreqKnob_Accel = 150;
	static const int kFreqKnob_Weight = 200;
	static const int kFreqKnonb_CatchupWeight = 333;

	static const int kResKnob_Accel = 350;
	static const int kResKnob_Weight = 200;
	static const int kResKnonb_CatchupWeight = 333;

	AccelParam smoothed_freq[2] {
		{kFreqKnob_Accel, kFreqKnob_Weight, kFreqKnonb_CatchupWeight, 0.5f},
		{kFreqKnob_Accel, kFreqKnob_Weight, kFreqKnonb_CatchupWeight, 0.5f},
	};

	AccelParam smoothed_res[2] {
		{kResKnob_Accel, kResKnob_Weight, kResKnonb_CatchupWeight, 0.5f},
		{kResKnob_Accel, kResKnob_Weight, kResKnonb_CatchupWeight, 0.5f},
	};

	bool knob_moved_while_pressed[2] = {false, false};

	static const inline uint8_t kNumFX = 5; // Todo: how to enforce this matches size of AudioFXList?
};

