#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include <cstring>

namespace MetaModule
{

using namespace mdrivlib;

void Controls::update_debouncers()
{
	rotary.update();
	rotary_button.update();
	button0.update();

	gate_in_1.update();
	gate_in_2.update();
}

// first param in block: 2.0-2.4us, @ 48kHz
// second param in block: 1.3-1.5us @ 48kHz
// load 6.8%
void Controls::update_params()
{
	//cur_params->buttons[0].copy_state(button0);
	cur_params->gate_ins[0].copy_state(gate_in_1);
	cur_params->gate_ins[1].copy_state(gate_in_2);

	if (_first_param) {
		_first_param = false;

		cur_params->jack_senses = jacksense_reader.read_sense_pins();
		store_jacksense_reading(cur_params->jack_senses);

		// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
		for (int i = 0; i < PanelDef::NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i) / 4095.0f);
			cur_params->knobs[i] = _knobs[i].next();
		}

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
		int new_rotary_motion = rotary.read();
		bool pressed = rotary_button.is_pressed();
		cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
		cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
		_rotary_moved_while_pressed = (pressed && new_rotary_motion);

	} else {
		cur_params->jack_senses = get_jacksense_reading();

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

	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf1Lock>([&]() {
		cur_metaparams = &param_blocks[0].metaparams;
		cur_params = param_blocks[0].params.begin();
		_first_param = true;
		_buffer_full = false;

		for (auto &aux : auxstream_blocks[0])
			auxstream.queue_data(aux);
	});

	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf2Lock>([&]() {
		cur_metaparams = &param_blocks[1].metaparams;
		cur_params = param_blocks[1].params.begin();
		_first_param = true;
		_buffer_full = false;

		for (auto &aux : auxstream_blocks[1])
			auxstream.queue_data(aux);
	});
	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();

	read_controls_task.start();
	read_cvadc_task.start();
	auxstream_updater.start();
}

Controls::Controls(mdrivlib::MuxedADC &potadc,
				   DoubleBufParamBlock &param_blocks_ref,
				   DoubleAuxStreamBlock &auxsignal_blocks_ref)
	: potadc(potadc)
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams)
	, _buffer_full{false}
	, auxstream_blocks{auxsignal_blocks_ref}
{
	// Todo: use RCC_Enable or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	// mp1 m4: 20.1us, width= 4.1us
	read_controls_task.init(control_read_tim_conf, [this]() {
		if (_buffer_full) {
			return;
		}
		update_debouncers();
		update_params();
	});

	auxstream.init();
	auxstream_updater.init([&]() {
		// Debug::Pin2::high();
		auxstream.output_next();
		// Debug::Pin2::low();
	});
}

void Controls::store_pot_reading(uint32_t pot_id, uint32_t val)
{
	if (pot_id >= PanelDef::NumPot)
		store_patchcv_reading(val);
	else
		latest_pot_reading[pot_id] = val > 4095 ? 4095 : val;
}
uint32_t Controls::get_pot_reading(uint32_t pot_id)
{
	return latest_pot_reading[pot_id];
}

void Controls::store_patchcv_reading(uint32_t patchcv)
{
	latest_patchcv_reading = patchcv > 4095 ? 4095 : patchcv;
}
uint32_t Controls::get_patchcv_reading()
{
	return latest_patchcv_reading;
}

void Controls::store_jacksense_reading(uint16_t reading)
{
	latest_jacksense_reading = reading;
}
uint32_t Controls::get_jacksense_reading()
{
	return latest_jacksense_reading;
}

} // namespace MetaModule
