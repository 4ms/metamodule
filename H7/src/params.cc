#include "params.hh"
#include "debug.hh"
#include "math.hh"
using namespace MathTools;

void Params::update()
{
	Debug::Pin1::high();

	for (int i = 0; i < 4; i++) {
		cvjacks[i] = (2047.5f - static_cast<float>(controls.cvadc.get_val(i))) / 2047.5f;
	}

	int tmp_rotary_motion = controls.rotary.read();

	if (controls.rotary_button.is_just_pressed()) {
		_rotary_moved_while_pressed = false;
		rotary_button.register_rising_edge();
	}
	if (controls.rotary_button.is_just_released() && !_rotary_moved_while_pressed) {
		rotary_button.register_falling_edge();
	}
	if (controls.rotary_button.is_pressed()) {
		if (rotary_motion != 0) {
			_rotary_moved_while_pressed = true;
			rotary_pushed_motion += tmp_rotary_motion;
		}
	} else {
		rotary_motion += tmp_rotary_motion;
	}

	for (int i = 0; i < 2; i++) {
		if (controls.button[i].just_went_high())
			buttons[i].register_rising_edge();

		if (controls.button[i].just_went_low())
			buttons[i].register_falling_edge();
	}

	// Todo: Pot ADC and Patch CV copying from controls to params happens in main loop.
	// This might be a problem if we separate Controls and Params between cores.
	// Can we store the last reading in Controls:: and then copy it over to Params:: here?
	// Wait until we separate cores to make sure we'll need this

	Debug::Pin1::low();
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
