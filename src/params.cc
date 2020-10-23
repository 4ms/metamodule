#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	//SCB_CleanInvalidateDCache(); // required until/unless we get ADC buffers into DTCM RAM
	
	// Debug::set_1(true);
	uint32_t freqcv[2];
	uint32_t rescv[2];
	freqcv[0] = controls.freq_sense[0].is_pressed() ? 0U : controls.freq_cv0.get();
	freqcv[1] = controls.freq_sense[1].is_pressed() ? 0U : controls.freq_cv1.get();
	rescv[0] = controls.res_sense[0].is_pressed() ? 0U : controls.res_cv0.get();
	rescv[1] = controls.res_sense[1].is_pressed() ? 0U : controls.res_cv1.get();

	for (int i = 0; i < 2; i++) {
		int32_t rotary_motion = controls.rotary[i].read();
		int32_t freq_motion = 0;
		int32_t res_motion = 0;

		if (controls.rotary_button[i].is_just_pressed()) {
			knob_moved_while_pressed[i] = false;
		}
		if (controls.rotary_button[i].is_just_released() && !knob_moved_while_pressed[i]) {
			knob_sel[i] = knob_sel[i] == FREQ ? RES: FREQ;
		}
		if (controls.rotary_button[i].is_pressed()) {
			if (rotary_motion!=0) {
				knob_moved_while_pressed[i] = true;
				//handle changing CV atten
				if (knob_sel[i] == FREQ)
					freq_cv_atten[i] = constrain(freq_cv_atten[i] + rotary_motion/100.f, 0.f, 1.f);
				else
					res_cv_atten[i] = constrain(res_cv_atten[i] + rotary_motion/100.f, 0.f, 1.f);
			}
		} else {
			if (knob_sel[i] == FREQ) {
				freq_motion = rotary_motion;
			} else {
				res_motion = rotary_motion;
			}
		}

		float freq_knob_pos = smoothed_freq[i].update(freq_motion);
		float res_knob_pos = smoothed_res[i].update(res_motion);

		float freq_cv = freq_cv_atten[i] * freqcv[i] / 4095.f;
		float res_cv = res_cv_atten[i] * rescv[i] / 4095.f;

		freq[i] = constrain(freq_knob_pos + freq_cv, 0.f, 1.f);
		res[i] = constrain(res_knob_pos + res_cv, 0.f, 1.f);


		if (controls.mode_button[i].is_just_released()) {
			fx_mode[i] = wrap<kNumFX>(fx_mode[i] + 1);
		}
	}
	// Debug::set_1(false);
}

