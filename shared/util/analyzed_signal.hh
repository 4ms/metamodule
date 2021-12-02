#pragma once
#include <cstdint>
#include <limits>

template<uint32_t iir_coef_int>
struct AnalyzedSignal {
	static constexpr float iir_coef = 1.f / (float)iir_coef_int;
	static constexpr float iir_coef_inv = 1.f - iir_coef;

	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::min();
	float avg = 0.f;
	float iir = 0.f;

	void update(float newval) {
		if (newval < min)
			min = newval;
		if (newval > max)
			max = newval;
		iir += iir_coef * (newval - iir);
	}

	void reset_to(float curval) {
		avg = curval;
		iir = curval;
		min = curval; // std::numeric_limits<float>::max();
		max = curval; // std::numeric_limits<float>::min();
	}
};
