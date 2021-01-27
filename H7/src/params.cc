#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	// SCB_CleanInvalidateDCache(); // required until/unless we get ADC buffers into DTCM RAM

	// Debug::set_1(true);
	// cvjacks[0] = controls.cv_sense[0].is_pressed() ? controls.cvadc.get(0) / 4095.f : 0U;
	// cvjacks[1] = controls.cv_sense[1].is_pressed() ? controls.cvadc.get(1) / 4095.f : 0U;
	// cvjacks[2] = controls.cv_sense[2].is_pressed() ? controls.cvadc.get(2) / 4095.f : 0U;
	// cvjacks[3] = controls.cv_sense[3].is_pressed() ? controls.cvadc.get(3) / 4095.f : 0U;

	int32_t rotary_motion = controls.rotary.read();

	if (controls.rotary_button.is_just_pressed()) {
		knob_moved_while_pressed = false;
	}
	if (controls.rotary_button.is_just_released() && !knob_moved_while_pressed) {
		// Handle button tap
	}
	if (controls.rotary_button.is_pressed()) {
		if (rotary_motion != 0) {
			knob_moved_while_pressed = true;
			// Handle push+turn
		}
	} else {
		// Handle turning (not pushed)
	}

	for (int i = 0; i < 2; i++) {
		buttons[i] = controls.button[i].is_pressed();
	}

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
