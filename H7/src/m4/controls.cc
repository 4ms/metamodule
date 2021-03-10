#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include <cstring>
using namespace MetaModule;
// CM4: 10kHz, 2.9% = 2.9us
//
// We have: knobs, buttons, rotary, gate ins, cv jacks
// CV jacks may eventually be SAI and synced with audio, so let's not worry too much about them, treat them like knobs
// for now
//
// Gate ins + knobs: store values in a buffer. If we can do Controls::read() at 48kHz, then it's BLOCK_SIZE long
// Then after audio block relinquishes lock on params, we can transfer the buffer.
// --- would be better if we transferred it right before audio block needs it, but that might be hard to anticipate
// --- ... maybe after audio block lifts lock, we do a few more reads into the buffers, then transfer

// MDMA for one Param struct (pin high->low) takes 2.2us, sometimes up to 4us (bus delays?)
void Controls::update_debouncers()
{
	rotary.update();
	rotary_button.update();
	button0.update();
	button1.update();

	gate_in0.update();
	gate_in1.update();
	clock_in.update();
}

void Controls::update_params()
{
	Params *params = cur_params;

	if (params <= &param_blocks[1][0])
		Debug::Pin1::high();
	else
		Debug::Pin2::high();

	for (int i = 0; i < 4; i++) {
		params->cvjacks[i] = (2047.5f - static_cast<float>(cvadc.get_val(i))) / 2047.5f;
	}

	int tmp_rotary_motion = rotary.read();

	if (rotary_button.is_just_pressed()) {
		_rotary_moved_while_pressed = false;
		params->rotary_button.register_rising_edge();
	}
	if (rotary_button.is_just_released() && !_rotary_moved_while_pressed) {
		params->rotary_button.register_falling_edge();
	}
	if (rotary_button.is_pressed()) {
		if (params->rotary_motion != 0) {
			_rotary_moved_while_pressed = true;
			params->rotary_pushed_motion += tmp_rotary_motion;
		}
	} else {
		params->rotary_position += tmp_rotary_motion;
		if (tmp_rotary_motion > 0)
			params->rotary_motion = 1;
		else if (tmp_rotary_motion < 0)
			params->rotary_motion = -1;
		else
			params->rotary_motion = 0;
	}

	params->buttons[0].copy_state(button0);
	params->buttons[1].copy_state(button1);
	params->rotary_button.copy_state(rotary_button);
	params->gate_ins[0].copy_state(gate_in0);
	params->gate_ins[1].copy_state(gate_in1);
	params->clock_in.copy_state(clock_in);

	for (int i = 0; i < 8; i++)
		params->knobs[i] = get_pot_reading(i) / 4095.0f;

	params->patchcv = get_patchcv_reading() / 4095.0f;

	if (params <= &param_blocks[1][0])
		Debug::Pin1::low();
	else
		Debug::Pin2::low();

	cur_params++;
	if (cur_params >= &param_blocks[2][0])
		cur_params = &param_blocks[0][0];
}

void Controls::start()
{

	potadc.start();
	cvadc.start();

	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_ISR();
	InterruptManager::registerISR(HSEM2_IRQn, 0, 0, [&]() {
		if (HWSemaphore<ParamsBuf1Lock>::is_ISR_triggered_and_enabled()) {
			Debug::Pin3::high();
			Debug::Pin3::low();
			cur_params = &param_blocks[0][0];
			HWSemaphore<ParamsBuf1Lock>::clear_ISR();
		} else if (HWSemaphore<ParamsBuf2Lock>::is_ISR_triggered_and_enabled()) {
			Debug::Pin2::high();
			Debug::Pin2::low();
			cur_params = &param_blocks[1][0];
			HWSemaphore<ParamsBuf2Lock>::clear_ISR();
		} else {
			Debug::Pin1::high();
			Debug::Pin1::low();
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
		update_debouncers();
		update_params();
	});
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() { cvadc.read_and_switch_channels(); });
}
