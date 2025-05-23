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
	cur_params->gate_ins = gate_in_1.is_high() ? 0b01 : 0b00;
	cur_params->gate_ins |= gate_in_2.is_high() ? 0b10 : 0b00;

	// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
	if (_new_adc_data_ready) {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i));
			num_pot_updates = 0;
		}
		_new_adc_data_ready = false;
	}

	num_pot_updates++;
	if (num_pot_updates >= _knobs[0].get_num_updates()) {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			auto val = _knobs[i].target_val;
			cur_params->knobs[i] = std::clamp(val, 0.f, 1.f);
			_knobs[i].cur_val = _knobs[i].target_val;
		}
	} else {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			auto val = _knobs[i].next();
			cur_params->knobs[i] = std::clamp(val, 0.f, 1.f);
		}
	}

	if (_first_param) {
		_first_param = false;

		update_midi_connected();

		cur_metaparams->midi_connected = _midi_connected;

		cur_metaparams->jack_senses = sense_pin_reader.last_reading();

		update_rotary();

		// Meta button
		cur_metaparams->meta_buttons[0].transfer_events(button0);
	}

	parse_midi();

	cur_params++;
	if (cur_params == param_blocks[0].params.end() || cur_params == param_blocks[1].params.end())
		_buffer_full = true;
}

void Controls::update_rotary() {
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
}

void Controls::update_midi_connected() {
	_midi_connected_raw.update(_midi_host.is_connected());

	if (_midi_connected_raw.went_low()) {
		_midi_parser.start_all_notes_off_sequence();
	}

	if (_midi_connected_raw.went_high()) {
		_midi_connected = true;
	}

	if (cur_metaparams->midi_poly_chans > 0)
		_midi_parser.set_poly_num(cur_metaparams->midi_poly_chans);
}

void Controls::parse_midi() {
	// Parse outgoing MIDI message if available and connected
	if (cur_params->raw_msg.raw() != MidiMessage{}.raw()) {
		if (_midi_connected_raw.is_high()) {
			std::array<uint8_t, 4> bytes;
			cur_params->raw_msg.make_usb_msg(bytes);
			_midi_host.transmit(bytes);
		}
	}

	// Parse a MIDI message if available
	if (auto msg = _midi_rx_buf.get(); msg.has_value()) {
		cur_params->raw_msg = msg.value();
		cur_params->midi_event = _midi_parser.parse(msg.value());

	} else if (auto noteoff = _midi_parser.step_all_notes_off_sequence()) {
		if (noteoff->type == Midi::Event::Type::None) {
			_midi_connected = false;
			cur_metaparams->midi_connected = _midi_connected;
			cur_params->raw_msg = MidiMessage{};
			cur_params->midi_event.type = Midi::Event::Type::None;
		} else {
			cur_params->midi_event = *noteoff;
			cur_params->raw_msg = {0x80, noteoff->note, 0};
		}

	} else {
		cur_params->raw_msg = MidiMessage{};
		cur_params->midi_event.type = Midi::Event::Type::None;
	}
}

template<size_t block_num>
void Controls::start_param_block() {
	static_assert(block_num <= 1, "There is only block 0 and block 1");

	// 28us width, every 1.3ms (audio block rate for 64-frame blocks) = 2.15% load
	cur_metaparams = &param_blocks[block_num].metaparams;
	cur_params = param_blocks[block_num].params.begin();
	_first_param = true;
	_buffer_full = false;

	if (sample_rate != cur_metaparams->sample_rate) {
		set_samplerate(cur_metaparams->sample_rate);
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
}

void Controls::set_samplerate(unsigned sample_rate) {
	this->sample_rate = sample_rate;
	for (auto &_knob : _knobs) {
		_knob.set_num_updates(sample_rate / AdcReadFrequency);
	}
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref, MidiHost &midi_host)
	: _midi_host{midi_host}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams) {

	// TODO: get IRQn, ADC1 periph from PotAdcConf. Also use register_access<>
	// TODO: _new_adc_data_ready is written from multiple threads, but is not thread-safe. Use atomic? Or accept dropped/duplicate ADC values?
	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {
			ADC1->ISR = tmp | ADC_ISR_EOS;
			_new_adc_data_ready = true;
		}
	});

	set_samplerate(sample_rate);

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
}

float Controls::get_pot_reading(uint32_t pot_id) {
	if (pot_id < pot_vals.size()) {
		auto raw = (int32_t)pot_vals[pot_id];
		float val = raw - MinPotValue;
		return std::clamp(val / MaxPotValue, 0.f, 1.f);
	}
	return 0;
}

} // namespace MetaModule
