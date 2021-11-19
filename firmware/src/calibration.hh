#pragma once
#include "conf/panel_conf.hh"
#include <cstdint>

struct Calibration {

	static inline float slope[PanelDef::NumAudioIn];
	static inline float offset[PanelDef::NumAudioIn];

	static float adjust_chan(int i, float raw) {
		return (raw - offset[i]) * slope[i];
	}

	// AIN3 (Audio In 1 jack)
	//  C4 = 12610
	//  C2 = 6352

	static bool calibrate_chan(int i, float C2val, float C4val) {
		// f octave = (cal_running_total_ - reading_at_C2) / kCalibration2Volts;
		// f slope = 12_f / octave;

		// if ((slope / nominal_slope_ - 1_f).abs() < kCalibrationSuccessTolerance) {
		// 	slope_ = slope;
		// 	offset_ = reading_at_C2 - (kCalibration2Volts * 12_f / slope_);
		constexpr float TwoOctavesVolts = 2.f;
		float octave = (C4val - C2val) / TwoOctavesVolts;
		slope[i] = 12.f / octave;
		offset[i] = C2val - (TwoOctavesVolts * octave);
		return true;
	}
};
