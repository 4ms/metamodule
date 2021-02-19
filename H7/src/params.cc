#include "params.hh"
#include "debug.hh"
#include "example1.hh"
#include "example_drum.hh"
#include "example_duallfo.hh"
#include "example_karplus.hh"
#include "example_pitchShift_simple.hh"
#include "fadedelay_two.hh"
#include "math.hh"

Params::Params(Controls &c)
	: controls(c)
	, _patches{{exampleDualLFO}, {examplePitchShiftSimple}, {exampleDrum}, {fadedelay_example}}
{}

void Params::update()
{
	// Debug::Pin1::high();

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

	buttons[0].copy_state(controls.button0);
	buttons[1].copy_state(controls.button1);
	rotary_button.copy_state(controls.rotary_button);
	gate_ins[0].copy_state(controls.gate_in0);
	gate_ins[1].copy_state(controls.gate_in1);
	clock_in.copy_state(controls.clock_in);

	// Todo: Pot ADC and Patch CV copying from controls to params happens in main loop.
	// This might be a problem if we separate Controls and Params between cores.
	// Can we store the last reading in Controls:: and then copy it over to Params:: here?
	// Wait until we separate cores to make sure we'll need this

	// Debug::Pin1::low();
}
