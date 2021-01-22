#pragma once
#include "accel_param.hh"
#include "controls.hh"
#include "drivers/stm32xx.h"
#include "drivers/uart.hh"

class Params {
public:
	Params(Controls &c)
		: controls(c)
	{}

	float cvjacks[4];
	float knobs[4];
	uint8_t fx_mode[2] = {0};

	int knob_sel[2] = {0, 0};

public:
	void update();
	Controls &controls;

private:
	// Adjust these as needed:
	static const int kFreqKnob_Accel = 150;
	static const int kFreqKnob_Weight = 200;
	static const int kFreqKnob_CatchupWeight = 333;

	static const int kResKnob_Accel = 350;
	static const int kResKnob_Weight = 200;
	static const int kResKnonb_CatchupWeight = 333;

	AccelParam smoothed_knob[4]{
		{kFreqKnob_Accel, kFreqKnob_Weight, kFreqKnob_CatchupWeight, 0.5f},
		{kFreqKnob_Accel, kFreqKnob_Weight, kFreqKnob_CatchupWeight, 0.5f},
		{kResKnob_Accel, kResKnob_Weight, kResKnonb_CatchupWeight, 0.5f},
		{kResKnob_Accel, kResKnob_Weight, kResKnonb_CatchupWeight, 0.5f},
	};

	bool knob_moved_while_pressed[2] = {false, false};

	static const inline uint8_t kNumFX = 5; // Todo: how to enforce this matches size of AudioFXList?

	// Uart screen;
	// uint32_t last_update_time = 0;
	// void update_screen();
};

