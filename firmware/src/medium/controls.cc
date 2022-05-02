#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"

namespace MetaModule
{

using namespace mdrivlib;

void Controls::update_debouncers() {
	rotary.update();
	rotary_button.update();
	button0.update();

	gate_in_1.update();
	gate_in_2.update();
}

// Mini:
// first param in block: 2.0-2.4us, @ 48kHz
// second param in block: 1.3-1.5us @ 48kHz
// load 6.8%
// Medium:
// to be measured... but it's 2.8us total for this + update_debouncers
void Controls::update_params() {
	cur_params->gate_ins[0].copy_state(gate_in_1);
	cur_params->gate_ins[1].copy_state(gate_in_2);

	// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
	if (_new_adc_data_ready) {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i) / 4095.0f);
		}
		_new_adc_data_ready = false;
	}

	for (unsigned i = 0; i < PanelDef::NumPot; i++)
		cur_params->knobs[i] = _knobs[i].next();

	if (_first_param) {
		_first_param = false;

		cur_params->jack_senses = 0; //jacksense_reader.read_sense_pins();
		store_jacksense_reading(cur_params->jack_senses);

		// PatchCV
		if constexpr (PanelDef::NumMetaCV > 0)
			cur_metaparams->patchcv = get_patchcv_reading() / 4095.0f;

		// Rotary button
		if (rotary_button.is_just_pressed()) {
			_rotary_moved_while_pressed = false;
			cur_metaparams->rotary_button.register_rising_edge();
		}

		if (rotary_button.is_just_released()) {
			if (_rotary_moved_while_pressed) {
				cur_metaparams->rotary_button.reset();
			} else {
				cur_metaparams->rotary_button.register_falling_edge();
			}
		}
		cur_metaparams->rotary_button.set_state(rotary_button.is_pressed());

		// Rotary turning
		int new_rotary_motion = rotary.read();
		bool pressed = rotary_button.is_pressed();
		cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
		cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
		//"If rotary was turned at any point since button was pressed" --> logical OR of all (pressed AND new_motion)
		_rotary_moved_while_pressed |= pressed && (new_rotary_motion != 0);

		// Meta button
		cur_metaparams->meta_buttons[0].transfer_events(button0);

	} else {
		cur_params->jack_senses = get_jacksense_reading();
	}

	cur_params++;
	if (cur_params == param_blocks[0].params.end() || cur_params == param_blocks[1].params.end())
		_buffer_full = true;
}

template<size_t block_num>
void Controls::start_param_block() {
	static_assert(block_num <= 1, "There is only block 0 and block 1");

	// 28us width, every 1.3ms (audio block rate for 64-frame blocks) = 2.15% load
	cur_metaparams = &param_blocks[block_num].metaparams;
	cur_params = param_blocks[block_num].params.begin();
	_first_param = true;
	_buffer_full = false;

	if constexpr (AuxStream::BoardHasDac || AuxStream::BoardHasGateOuts) {
		for (auto &aux : auxstream_blocks[block_num])
			auxstream.queue_data(aux);
	}
}

void Controls::start() {
	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf1Lock>([&]() { start_param_block<0>(); });

	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf2Lock>([&]() { start_param_block<1>(); });

	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();

	read_controls_task.start();
	if constexpr (AuxStream::BoardHasDac || AuxStream::BoardHasGateOuts) {
		auxstream_updater.start();
	}
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref,
				   DoubleAuxStreamBlock &auxsignal_blocks_ref,
				   GPIOExpander &main_gpioexpander,
				   GPIOExpander &ext_gpioexpander)
	: jacksense_reader{main_gpioexpander}
	, extaudio_jacksense_reader{ext_gpioexpander}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams)
	, _buffer_full{false}
	, auxstream_blocks{auxsignal_blocks_ref} {

	// TODO: get IRQn, ADC1 periph from PotAdcConf. Also use register_access<>
	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {
			ADC1->ISR = tmp | ADC_ISR_EOS;
			_new_adc_data_ready = true;
		}
	});

	pot_adc.start();

	Debug::Pin3::high();
	auto err = extaudio_jacksense_reader.start();
	if (err == GPIOExpander::Error::None)
		Debug::Pin3::low();
	Debug::Pin2::high();

	// Todo: use RCC_Enable or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	// mp1 m4: every ~20us + 60us gap every 64 pulses (1.3ms), width= 2.8us ... ~14% load
	read_controls_task.init(control_read_tim_conf, [this]() {
		if (_buffer_full) {
			return;
		}
		update_debouncers();
		update_params();
	});

	if constexpr (AuxStream::BoardHasDac || AuxStream::BoardHasGateOuts) {
		auxstream.init();
		auxstream_updater.init([&]() {
			// 0.35us wide, every 20.83us = 1.68% load
			auxstream.output_next();
		});
	}

	Debug::Pin2::low();
}

uint32_t Controls::get_pot_reading(uint32_t pot_id) {
	if (pot_id < NumPotAdcs)
		return pot_vals[pot_id];
	return 0;
}

uint32_t Controls::get_patchcv_reading() {
	return 0;
}

void Controls::store_jacksense_reading(uint16_t reading) {
	latest_jacksense_reading = reading;
}

uint32_t Controls::get_jacksense_reading() {
	return latest_jacksense_reading;
}

void Controls::collect_extaudio_jacksense_reading() {
	latest_extaudio_jacksense_reading = extaudio_jacksense_reader.collect_last_reading();
}

} // namespace MetaModule
