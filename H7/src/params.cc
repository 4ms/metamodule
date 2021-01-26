#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	// SCB_CleanInvalidateDCache(); // required until/unless we get ADC buffers into DTCM RAM

	// Debug::set_1(true);
	cvjacks[0] = controls.cv_sense[0].is_pressed() ? controls.cvadc.get(0) / 4095.f : 0U;
	cvjacks[1] = controls.cv_sense[1].is_pressed() ? controls.cvadc.get(1) / 4095.f : 0U;
	cvjacks[2] = controls.cv_sense[2].is_pressed() ? controls.cvadc.get(2) / 4095.f : 0U;
	cvjacks[3] = controls.cv_sense[3].is_pressed() ? controls.cvadc.get(3) / 4095.f : 0U;

	for (int i = 0; i < 2; i++) {
		int32_t rotary_motion = controls.rotary[i].read();
		int32_t motion[2] = {0, 0};

		if (controls.rotary_button[i].is_just_pressed()) {
			knob_moved_while_pressed[i] = false;
		}
		if (controls.rotary_button[i].is_just_released() && !knob_moved_while_pressed[i]) {
			knob_sel[i] = 1 - knob_sel[i];
		}
		if (controls.rotary_button[i].is_pressed()) {
			if (rotary_motion != 0) {
				knob_moved_while_pressed[i] = true;
				// handle push+turn:
				// if (knob_sel[i] == FREQ)
				// 	freq_cv_atten[i] = constrain(freq_cv_atten[i] + rotary_motion / 100.f, 0.f, 1.f);
				// else
				// 	res_cv_atten[i] = constrain(res_cv_atten[i] + rotary_motion / 100.f, 0.f, 1.f);
			}
		} else {
			motion[knob_sel[i]] = rotary_motion;
		}

		knobs[i * 2 + 0] = constrain(smoothed_knob[i * 2 + 0].update(motion[0]), 0.f, 1.f);
		knobs[i * 2 + 1] = constrain(smoothed_knob[i * 2 + 1].update(motion[1]), 0.f, 1.f);

		if (controls.mode_button[i].is_just_released()) {
			fx_mode[i] = wrap<kNumFX>(fx_mode[i] + 1);
		}
	}

	// update_screen();

	// Debug::set_1(false);
}

// void Params::update_screen()
// {
// 	if (HAL_GetTick() - last_update_time > 50) {
// 		last_update_time = HAL_GetTick();

// 		uint8_t d[6];
// 		d[0] = 0xAA;
// 		d[1] = static_cast<uint8_t>(knobs[0] * 100.f);
// 		d[2] = static_cast<uint8_t>(knobs[1] * 100.f);
// 		d[3] = static_cast<uint8_t>(knobs[2] * 100.f);
// 		d[4] = static_cast<uint8_t>(knobs[3] * 100.f);
// 		d[5] = 0xA5;
// 		screen.send(d, 6);
// 	}
// }
