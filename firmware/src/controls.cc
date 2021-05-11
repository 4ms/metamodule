#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include <cstring>

namespace MetaModule
{

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
	volatile bool abcd = true;
	while (abcd)
		;

	cur_params->cvjacks[0] = (2047.5f - static_cast<float>(cvadc.get_val(0))) / 2047.5f;
	cur_params->cvjacks[1] = (2047.5f - static_cast<float>(cvadc.get_val(1))) / 2047.5f;
	// Oops! CV C and CV D are swapped:
	cur_params->cvjacks[2] = (2047.5f - static_cast<float>(cvadc.get_val(3))) / 2047.5f;
	cur_params->cvjacks[3] = (2047.5f - static_cast<float>(cvadc.get_val(2))) / 2047.5f;

	cur_params->buttons[0].copy_state(button0);
	cur_params->buttons[1].copy_state(button1);
	cur_params->gate_ins[0].copy_state(gate_in1);
	cur_params->gate_ins[1].copy_state(gate_in2);
	cur_params->gate_ins[2].copy_state(clock_in);
	cur_params->jack_senses = get_jacksense_reading();

	if (_first_param) {
		_first_param = false;

		// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
		for (int i = 0; i < NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i) / 4095.0f);
			cur_params->knobs[i] = _knobs[i].next();
		}

		// Metaparams:

		// PatchCV
		cur_metaparams->patchcv = get_patchcv_reading() / 4095.0f;

		// Rotary button
		if (rotary_button.is_just_pressed()) {
			_rotary_moved_while_pressed = false;
			cur_metaparams->rotary_button.register_rising_edge();
		}
		if (rotary_button.is_just_released()) {
			if (_rotary_moved_while_pressed)
				cur_metaparams->rotary_button.reset();
			else
				cur_metaparams->rotary_button.register_falling_edge();
		}

		// Rotary turning
		int tmp_rotary_motion = rotary.read();
		if (rotary_button.is_pressed()) {
			cur_metaparams->rotary.motion = 0;
			cur_metaparams->rotary_pushed.motion = tmp_rotary_motion;
			if (tmp_rotary_motion != 0)
				_rotary_moved_while_pressed = true;
		} else {
			cur_metaparams->rotary.motion = tmp_rotary_motion;
			cur_metaparams->rotary_pushed.motion = 0;
		}

		// int new_rotary_motion = rotary.read();
		// bool pressed = rotary_button.is_pressed();
		// cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
		// cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
		// if (pressed && tmp_rotary_motion)
		// 	_rotary_moved_while_pressed = true;

	} else {
		// Interpolate the knobs
		for (int i = 0; i < NumPot; i++)
			cur_params->knobs[i] = _knobs[i].next();
	}

	cur_params++;
	if (cur_params == param_blocks[0].params.end() || cur_params == param_blocks[1].params.end())
		_buffer_full = true;
}

void Controls::start()
{
	potadc.start();
	cvadc.start();
	jacksense_reader.start();

	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf1Lock>([&]() {
		_buffer_full = false;
		_first_param = true;
		cur_metaparams = &param_blocks[0].metaparams;
		cur_params = param_blocks[0].params.begin();
	});
	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf2Lock>([&]() {
		_buffer_full = false;
		_first_param = true;
		cur_metaparams = &param_blocks[1].metaparams;
		cur_params = param_blocks[1].params.begin();
	});
	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();

	read_controls_task.start();
	read_cvadc_task.start();
	// clock_out.low();
}

Controls::Controls(MuxedADC &potadc,
				   CVAdcChipT &cvadc,
				   DoubleBufParamBlock &param_blocks_ref,
				   GPIOExpander &gpio_expander)
	: potadc(potadc)
	, cvadc(cvadc)
	, jacksense_reader{gpio_expander}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
{
	// Todo: use RCC_Enable or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	read_controls_task.init(control_read_tim_conf, [this]() {
		// if (_buffer_full)
		// 	return;
		Debug::Pin1::high();
		HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
		HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
		update_debouncers();
		update_params();
		HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
		HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();
		Debug::Pin1::low();
	});
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() {
		Debug::Pin0::high();
		cvadc.read_and_switch_channels();
		Debug::Pin0::low();
	});
}
} // namespace MetaModule
