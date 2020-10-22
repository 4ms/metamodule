#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	SCB_CleanInvalidateDCache(); // required until/unless we get ADC buffers into DTCM RAM
	// Debug::set_1(true);
	uint32_t freqcv[2];
	uint32_t rescv[2];
	freqcv[0] = controls.freq_sense[0].is_pressed() ? 0U : controls.freq_cv0.get();
	freqcv[1] = controls.freq_sense[1].is_pressed() ? 0U : controls.freq_cv1.get();
	rescv[0] = controls.res_sense[0].is_pressed() ? 0U : controls.res_cv0.get();
	rescv[1] = controls.res_sense[1].is_pressed() ? 0U : controls.res_cv1.get();

	for (int i = 0; i < 2; i++) {
		float rotary_motion = static_cast<float>(controls.rotary[i].read());
		if (rotary_motion != 0.f) {
			if (controls.rotary_button[i].is_pressed())
				res_knob_pos[i] = constrain(res_knob_pos[i] + (rotary_motion / kFreqScaling), -1.f, 1.f);
			else
				freq_knob_pos[i] = constrain(freq_knob_pos[i] + (rotary_motion / kResScaling), -1.f, 1.f);
		}

		freq[i] = constrain(freq_knob_pos[i] + (freqcv[i] / 4095.0f), 0.f, 1.f);
		res[i] = constrain(res_knob_pos[i] + (rescv[i] / 4095.0f), 0.f, 1.f);

		if (controls.mode_button[i].is_just_released()) {
			mode[i] = wrap<kNumFX>(mode[i] + 1);
		}
	}
	// Debug::set_1(false);
}
