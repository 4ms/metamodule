#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	// Debug::set_1(true);
	uint32_t freqcv[2] = {controls.freq_cv0.get(), controls.freq_cv1.get()};
	uint32_t rescv[2] = {controls.res_cv0.get(), controls.res_cv1.get()};

	for (int i = 0; i < 2; i++) {
		float rotary_motion = static_cast<float>(controls.rotary[i].read());
		if (rotary_motion != 0.f) {
			if (controls.rotary_button[i].is_pressed())
				res_knob_pos[i] = constrain(res_knob_pos[i] + (rotary_motion / kFreqScaling), 0.f, 1.f);
			else
				freq_knob_pos[i] = constrain(freq_knob_pos[i] + (rotary_motion / kResScaling), 0.f, 1.f);
		}

		freq[i] = constrain(freq_knob_pos[i] + (freqcv[i] / 4095.0f) - 0.5f, 0.f, 1.f);
		res[i] = constrain(res_knob_pos[i] + (rescv[i] / 4095.0f) - 0.5f, 0.f, 1.f);

		if (controls.mode_button[i].is_just_released()) {
			mode[i] = wrap<kNumFX>(mode[i] + 1);
		}
	}
	// Debug::set_1(false);
}

