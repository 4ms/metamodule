#pragma once
#include "util/math.hh"
#include <cstdint>

class Calibrator {
public:
	Calibrator() = default;
	Calibrator(float slope, float offset)
		: _slope(slope)
		, _offset(offset) {
	}

	float adjust(float raw) {
		return (raw - _offset) * _slope;
	}

	void set_slope_offset(float slope, float offset) {
		_slope = slope;
		_offset = offset;
	}

	template<int TargetLowValue, int TargetHighValue>
	bool calibrate_chan(float zero_measurement, float low_measurement, float high_measurement) {
		constexpr float TargetRange = TargetHighValue - TargetLowValue;
		float t_slope = TargetRange / (high_measurement - low_measurement);
		float t_offset = low_measurement - TargetLowValue / t_slope;
		if (MathTools::f_abs(t_offset - zero_measurement) > 0.0001f) {
			return false;
		}
		_slope = t_slope;
		_offset = t_offset;
		return true;
	}

	template<int TargetLowValue, int TargetHighValue, int Divider = 1>
	void calibrate_chan(float low_measurement, float high_measurement) {
		constexpr float TargetRange = (float)(TargetHighValue - TargetLowValue) / (float)Divider;
		_slope = TargetRange / (high_measurement - low_measurement);
		_offset = low_measurement - ((float)TargetLowValue / (float)Divider) / _slope;
	}

private:
	float _slope = 1.0f;
	float _offset = 0.f;
};
