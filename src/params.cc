#include "math.hh"
#include "ui.hh"

using namespace MathTools;

void Params::update()
{
	uint16_t freq_cv[2] = {controls.freq1_cv.get(), controls.freq2_cv.get()};
	uint16_t res_cv[2] = {controls.res1_cv.get(), controls.res2_cv.get()};

	for (int i = 0; i < 2; i++) {
		auto rotary_motion = controls.rotary[i].read();
		if (controls.rotary_button[i].is_pressed())
			freq_knob_pos[i] += rotary_motion;
		else
			res_knob_pos[i] += rotary_motion;
		freq[i] = constrain((freq_knob_pos[i] / kFreqScaling) + (freq_cv[i] / 4095.0f), 0.f, 1.f);
		res[i] = constrain((res_knob_pos[i] / kResScaling) + (res_cv[i] / 4095.0f), 0.f, 1.f);

		//if (controls.pads.just_touched(i)) {
		if (controls.rotary_button[i].is_just_released()) {
			mode[i] = wrap<kNumFX>(mode[i] + 1);
		}
	}
}

