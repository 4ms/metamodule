#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include "midi_controls.hh"
#include "patch/midi_def.hh"
#include "util/countzip.hh"

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

void Controls::update_params() {
	cur_params->gate_ins[0] = gate_in_1.is_high();
	cur_params->gate_ins[1] = gate_in_2.is_high();

	// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
	if (_new_adc_data_ready) {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i));
		}
		_new_adc_data_ready = false;
	}

	for (unsigned i = 0; i < PanelDef::NumPot; i++)
		cur_params->knobs[i] = _knobs[i].next();

	// Knob Expanders
	cur_metaparams->num_knob_expanders_found = control_expander.num_knob_expanders_connected();
	auto num_exp_knobs = cur_metaparams->num_knob_expanders_found * KnobExpander::NumKnobsPerExpander;
	if (num_exp_knobs > 0) {
		if (control_expander.has_new_knob_readings()) {
			// Get average of last two periods
			auto now = HAL_GetTick();
			exp_pot_data_ms = (now - last_exp_data_tm[0]) / 2.f;
			last_exp_data_tm[0] = last_exp_data_tm[1];
			last_exp_data_tm[1] = now;

			// Set new values
			for (auto knob_idx = 0u; knob_idx < num_exp_knobs; knob_idx++) {
				auto val = get_exp_pot_reading(knob_idx / 8, knob_idx % 8);
				_exp_knobs[knob_idx].set_new_value(val);
			}
		}
		for (auto knob_idx = 0u; knob_idx < num_exp_knobs; knob_idx++) {
			cur_params->knobs[PanelDef::NumPot + knob_idx] = _exp_knobs[knob_idx].next();
		}
	}

	if (_first_param) {
		_first_param = false;

		_midi_connected.update(_midi_host.is_connected());

		if (_midi_connected.went_low()) {
			_midi_parser.start_all_notes_off_sequence();
		}

		if (_midi_connected.is_high() && !cur_metaparams->midi_connected) {
			cur_metaparams->midi_connected = true;
		}

		if (cur_metaparams->midi_poly_chans > 0)
			_midi_parser.set_poly_num(cur_metaparams->midi_poly_chans);

		cur_params->jack_senses = sense_pin_reader.last_reading();

		// Button Expanders
		cur_metaparams->num_button_expanders_found = control_expander.num_button_expanders_connected();

		if (cur_metaparams->num_button_expanders_found > 0) {
			uint32_t buttons_state = control_expander.get_buttons();
			cur_metaparams->ext_buttons_pressed_event = 0;
			cur_metaparams->ext_buttons_released_event = 0;
			for (auto [i, extbut] : enumerate(ext_buttons)) {
				extbut.register_state(buttons_state & (1 << i));

				if (extbut.just_went_high()) {
					cur_metaparams->ext_buttons_pressed_event |= (1 << i);
				}
				if (extbut.just_went_low()) {
					cur_metaparams->ext_buttons_released_event |= (1 << i);
				}
			}
			control_expander.set_leds(cur_metaparams->button_leds);
		}

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
		cur_metaparams->rotary_button.set_state_no_events(rotary_button.is_pressed());

		// Rotary turning
		int new_rotary_motion = rotary.read();
		bool pressed = rotary_button.is_pressed();
		cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
		cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
		//"If rotary was turned at any point since button was pressed" --> logical OR of all (pressed AND new_motion)
		_rotary_moved_while_pressed |= pressed && (new_rotary_motion != 0);

		// Meta button
		cur_metaparams->meta_buttons[0].transfer_events(button0);
	}

	// Parse a MIDI message if available
	if (auto msg = _midi_rx_buf.get(); msg.has_value()) {
		cur_params->midi_event = _midi_parser.parse(msg.value());

	} else if (auto noteoff = _midi_parser.step_all_notes_off_sequence(); noteoff.has_value()) {
		if (noteoff.value().type == Midi::Event::Type::None) {
			cur_metaparams->midi_connected = false;
		}
		cur_params->midi_event = noteoff.value();

	} else {
		cur_params->midi_event.type = Midi::Event::Type::None;
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

	if (sample_rate != cur_metaparams->sample_rate || block_size != cur_metaparams->block_size) {
		sample_rate = cur_metaparams->sample_rate;
		block_size = cur_metaparams->block_size;
		change_samplerate_blocksize();
	}

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

	_midi_host.set_rx_callback([this](std::span<uint8_t> rxbuffer) {
		bool ignore = false;

		while (rxbuffer.size() >= 4) {
			auto msg = MidiMessage{rxbuffer[1], rxbuffer[2], rxbuffer[3]};

			//Starting ignoring from SysEx Start (F0)...
			if (msg.is_sysex())
				ignore = true;

			//...until SysEx End (F7) received
			if (ignore && msg.has_sysex_end())
				ignore = false;

			if (!ignore)
				_midi_rx_buf.put(msg);

			rxbuffer = rxbuffer.subspan(4);
			// msg.print();
		}
		_midi_host.receive();
	});
}

void Controls::process() {
	sense_pin_reader.update();
	control_expander.update();
}

void Controls::change_samplerate_blocksize() {
	for (auto &_knob : _knobs) {
		_knob.set_num_updates(sample_rate / AdcReadFrequency);
	}

	// float block_ms = 1000.f * (float)block_size / (float)sample_rate;
	float block_ms = 1000.f / (float)sample_rate;
	unsigned num_updates = std::clamp<unsigned>(std::round(exp_pot_data_ms / block_ms), 1u, 1024u);
	pr_dbg("%f -> %d\n", exp_pot_data_ms, num_updates);
	for (auto &knob : _exp_knobs) {
		knob.set_num_updates(num_updates);
	}
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref,
				   DoubleAuxStreamBlock &auxsignal_blocks_ref,
				   MidiHost &midi_host)
	: _midi_host{midi_host}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams)
	, auxstream_blocks{auxsignal_blocks_ref} {

	// TODO: get IRQn, ADC1 periph from PotAdcConf. Also use register_access<>
	// TODO: _new_adc_data_ready is written from multiple threads, but is not thread-safe. Use atomic? Or accept dropped/duplicate ADC values?
	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {
			// Debug::Pin1::high();
			ADC1->ISR = tmp | ADC_ISR_EOS;
			_new_adc_data_ready = true;
			// Debug::Pin1::low();
		}
	});

	change_samplerate_blocksize();

	pot_adc.start();

	// Todo: use RCC_Enable or create DBGMCU_Control:
	// HSEM_IT2_IRQn (125) and ADC1 (18) make it hard to debug, but they can't be frozen
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	read_controls_task.init([this]() {
		if (_buffer_full)
			return;
		update_debouncers();
		update_params();
	});

	if constexpr (AuxStream::BoardHasDac || AuxStream::BoardHasGateOuts) {
		auxstream.init();
		auxstream_updater.init([&]() { auxstream.output_next(); });
	}
}

float Controls::get_pot_reading(uint32_t pot_id) {
	auto raw = (int32_t)pot_vals[pot_id] - MinPotValue;
	float v = (float)raw / (4095.f - MinPotValue);
	return std::clamp(v, 0.f, 1.f);
}

float Controls::get_exp_pot_reading(uint32_t exp_idx, uint32_t pot_idx) {
	auto raw = control_expander.get_knob(exp_idx, pot_idx);
	float v = (float)raw / 4095.f;
	return std::clamp(v, 0.f, 1.f);
}

} // namespace MetaModule
