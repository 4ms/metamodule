#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include <cstring>

namespace MetaModule
{

// Note: not using MDMA because for one Param struct (debug pin high->low) took 2.2us, sometimes up to 4us (bus delays?)
static bool stop = true;

void Controls::update_debouncers()
{
	rotary.update();
	rotary_button.update();
	button0.update();
	button1.update();

	gate_in1.update();
	gate_in2.update();
	clock_in.update();
}

// first param in block: 2.0-2.4us, @ 48kHz
// second param in block: 1.3-1.5us @ 48kHz
// load 6.8%
void Controls::update_params()
{
	Debug::Pin1::high();

	Params *params = cur_params;
	Params *first_param = (params < &param_blocks[1][0]) ? &param_blocks[0][0] : &param_blocks[1][0];

	params->cvjacks[0] = (2047.5f - static_cast<float>(cvadc.get_val(0))) / 2047.5f;
	params->cvjacks[1] = (2047.5f - static_cast<float>(cvadc.get_val(1))) / 2047.5f;
	params->cvjacks[2] = (2047.5f - static_cast<float>(cvadc.get_val(3))) / 2047.5f;
	params->cvjacks[3] = (2047.5f - static_cast<float>(cvadc.get_val(2))) / 2047.5f;
	// for (int i = 0; i < NumCVIn; i++)
	// 	params->cvjacks[i] = (2047.5f - static_cast<float>(cvadc.get_val(i))) / 2047.5f;

	params->buttons[0].copy_state(button0);
	params->buttons[1].copy_state(button1);
	params->gate_ins[0].copy_state(clock_in);
	params->gate_ins[1].copy_state(gate_in1);
	params->gate_ins[2].copy_state(gate_in2);

	if (params == first_param) {
		int tmp_rotary_motion = rotary.read();

		if (rotary_button.is_just_pressed()) {
			_rotary_moved_while_pressed = false;
			params->rotary_button.register_rising_edge();
		}
		if (rotary_button.is_just_released() && !_rotary_moved_while_pressed) {
			params->rotary_button.register_falling_edge();
			// Todo: if button is released and _rotary_moved_while_pressed == true, then do we need to tell
			// params->rotary_button that the button is released?
		}

		if (rotary_button.is_pressed()) {
			params->rotary_motion = 0;
			params->rotary_pushed_motion = tmp_rotary_motion;
			if (tmp_rotary_motion != 0)
				_rotary_moved_while_pressed = true;
		} else {
			params->rotary_motion = tmp_rotary_motion;
			params->rotary_pushed_motion = 0;
		}

		params->rotary_button.copy_state(rotary_button);

		for (int i = 0; i < NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i) / 4095.0f);
			params->knobs[i] = _knobs[i].next();
			// params->knobs[i] = get_pot_reading(i) / 4095.0f;
		}

		params->patchcv = get_patchcv_reading() / 4095.0f;

	} else {
		params->patchcv = first_param->patchcv;

		for (int i = 0; i < NumPot; i++)
			params->knobs[i] = _knobs[i].next();

		// jacksenses
		params->rotary_button.copy_state(first_param->rotary_button);
		params->rotary_motion = first_param->rotary_motion;
		params->rotary_pushed_motion = first_param->rotary_pushed_motion;
	}

	cur_params++;
	if (cur_params == &param_blocks[1][0] || cur_params == &param_blocks[2][0])
		stop = true;

	Debug::Pin1::low();
}

void Controls::start()
{
	potadc.start();
	cvadc.start();

	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_ISR();
	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_ISR();
	InterruptManager::registerISR(HSEM2_IRQn, 0, 0, [&]() {
		if (HWSemaphore<ParamsBuf1Lock>::is_ISR_triggered_and_enabled()) {
			Debug::Pin3::high();
			stop = false;
			cur_params = &param_blocks[0][0];
			HWSemaphore<ParamsBuf1Lock>::clear_ISR();
			return;
		}
		if (HWSemaphore<ParamsBuf2Lock>::is_ISR_triggered_and_enabled()) {
			Debug::Pin3::low();
			stop = false;
			cur_params = &param_blocks[1][0];
			HWSemaphore<ParamsBuf2Lock>::clear_ISR();
			return;
		}
	});
	HWSemaphore<ParamsBuf1Lock>::enable_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_ISR();

	read_controls_task.start();
	read_cvadc_task.start();
	clock_out.low();
}

Controls::Controls(MuxedADC &potadc, CVAdcChipT &cvadc, ParamBlock *param_block_base)
	: potadc(potadc)
	, cvadc(cvadc)
	, param_blocks(param_block_base)
	, cur_param_block(param_block_base)
	, cur_params(&param_block_base[0][0])
{
	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() {
		if (stop)
			return;
		update_debouncers();
		update_params();
	});
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() { cvadc.read_and_switch_channels(); });
}
} // namespace MetaModule
