#include "controls.hh"
#include "debug.hh"

// CM7: 10kHz, 1.6% = 1.6us
void Controls::read()
{
	// Debug::Pin2::high();
	rotary.update();
	rotary_button.update();
	button0.update();
	button1.update();

	gate_in0.update();
	gate_in1.update();
	clock_in.update();

	// Debug::Pin2::low();
	Debug::Pin1::high();
	dest.lock_for_write();

	for (int i = 0; i < 4; i++) {
		dest.cvjacks[i] = (2047.5f - static_cast<float>(cvadc.get_val(i))) / 2047.5f;
	}

	int tmp_rotary_motion = rotary.read();

	if (rotary_button.is_just_pressed()) {
		_rotary_moved_while_pressed = false;
		dest.rotary_button.register_rising_edge();
	}
	if (rotary_button.is_just_released() && !_rotary_moved_while_pressed) {
		dest.rotary_button.register_falling_edge();
	}
	if (rotary_button.is_pressed()) {
		if (dest.rotary_motion != 0) {
			_rotary_moved_while_pressed = true;
			dest.rotary_pushed_motion += tmp_rotary_motion;
		}
	} else {
		dest.rotary_motion += tmp_rotary_motion;
	}

	dest.buttons[0].copy_state(button0);
	dest.buttons[1].copy_state(button1);
	dest.rotary_button.copy_state(rotary_button);
	dest.gate_ins[0].copy_state(gate_in0);
	dest.gate_ins[1].copy_state(gate_in1);
	dest.clock_in.copy_state(clock_in);

	for (int i = 0; i < 8; i++)
		dest.knobs[i] = get_pot_reading(i) / 4095.0f;

	dest.patchcv = get_patchcv_reading() / 4095.0f;

	Debug::Pin1::low();
	dest.unlock_for_write();
}

void Controls::start()
{
	potadc.start();
	cvadc.start();
	read_controls_task.start();
	read_cvadc_task.start();
	clock_out.low();
}

Controls::Controls(MuxedADC &potadc, CVAdcChipT &cvadc, Params &dest)
	: potadc(potadc)
	, cvadc(cvadc)
	, dest(dest)
{

	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() { cvadc.read_and_switch_channels(); });
	dest.init();
}

