#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include "patch/midi_def.hh"

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
	cur_params->gate_ins[0].copy_state(gate_in_1);
	cur_params->gate_ins[1].copy_state(gate_in_2);

	// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
	if (_new_adc_data_ready) {
		for (unsigned i = 0; i < PanelDef::NumPot; i++) {
			_knobs[i].set_new_value(get_pot_reading(i));
		}
		_new_adc_data_ready = false;
	}
	for (unsigned i = 0; i < PanelDef::NumPot; i++)
		cur_params->knobs[i] = _knobs[i].next();

	if (_first_param) {
		_first_param = false;

		cur_metaparams->midi_connected = _midi_host.is_connected();
		cur_params->jack_senses = get_jacksense_reading();

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

	unsigned gate_evt_num = 0;

	while (_midi_rx_buf.num_filled()) {
		auto msg = _midi_rx_buf.get();

		// Monophonic MIDI CV/Gate
		if (msg.is_command<MidiCommand::NoteOff>() || (msg.is_command<MidiCommand::NoteOn>() && msg.velocity() == 0)) {
			midi_note.gate = false;
			midi_note.vel = 0;

			if (gate_evt_num < MidiMaxSimulGates) {
				cur_params->midi.gate_events[gate_evt_num].notenum = msg.note();
				cur_params->midi.gate_events[gate_evt_num].gateamp = 0;
				gate_evt_num++;
			}

		} else if (msg.is_command<MidiCommand::NoteOn>()) {

			midi_note.pitch = (msg.note() - 24) / 12.f; //60 = C3 = 3V. 72 = C4 = 4V etc...
			midi_note.vel = msg.velocity() / 12.7f;		//0..127 => 0..10V
			midi_note.gate = true;

			if (gate_evt_num < MidiMaxSimulGates) {
				cur_params->midi.gate_events[gate_evt_num].notenum = msg.note();
				cur_params->midi.gate_events[gate_evt_num].gateamp = msg.velocity() / 12;
				gate_evt_num++;
			}
		}
	}

	if (!_midi_host.is_connected()) {
		//if rx buffer is empty AND we've disconnected, turn off the midi gate
		//so we don't end up with stuck notes
		midi_note.pitch = 0.f;
		midi_note.gate = false;
		midi_note.vel = 0.f;
		//TODO: handle all possible note offs for gate_events
	}

	cur_params->midi.notes[0] = midi_note;

	Debug::red_LED1::set(midi_note.gate);

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

	_midi_host.set_rx_callback([this](std::span<uint8_t> rxbuffer) {
		if (rxbuffer.size() < 4)
			return;
		// Debug::Pin0::high();
		auto msg = MidiMessage{rxbuffer[1], rxbuffer[2], rxbuffer[3]};
		_midi_rx_buf.put(msg);
		// msg.print();
		// Debug::Pin0::low();

		_midi_host.receive();
	});
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref,
				   DoubleAuxStreamBlock &auxsignal_blocks_ref,
				   GPIOExpander &main_gpioexpander,
				   GPIOExpander &ext_gpioexpander,
				   MidiHost &midi_host)
	: jacksense_reader{main_gpioexpander}
	, extaudio_jacksense_reader{ext_gpioexpander}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams)
	, _buffer_full{false}
	, auxstream_blocks{auxsignal_blocks_ref}
	, _midi_host{midi_host} {
	// TODO: get IRQn, ADC1 periph from PotAdcConf. Also use register_access<>
	// TODO: _new_adc_data_ready is written from multiple threads, but is not thread-safe. Use atomic? Or accept dropped/duplicate ADC values?
	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {
			ADC1->ISR = tmp | ADC_ISR_EOS;
			_new_adc_data_ready = true;
		}
	});

	pot_adc.start();

	extaudio_jacksense_reader.start();

	// Todo: use RCC_Enable or create DBGMCU_Control:
	// HSEM_IT2_IRQn (125) and ADC1 (18) make it hard to debug, but they can't be frozen
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	// mp1 m4: every ~20us + 60us gap every 64 pulses (1.3ms), width= 2.8us ... ~14% load
	read_controls_task.init(control_read_tim_conf, [this]() {
		// Debug::Pin3::high();
		if (_buffer_full)
			return;
		update_debouncers();
		update_params();
		// Debug::Pin3::low();
	});

	if constexpr (AuxStream::BoardHasDac || AuxStream::BoardHasGateOuts) {
		auxstream.init();
		auxstream_updater.init([&]() { auxstream.output_next(); });
	}

	// Debug::Pin2::low();
}

float Controls::get_pot_reading(uint32_t pot_id) {
	if (pot_id < NumPotAdcs) {
		auto raw = (int32_t)pot_vals[pot_id];
		int32_t val = raw - MinPotValue;
		if (val < 0)
			val = 0;
		return (float)val / (4096.f - MinPotValue);
	}
	return 0;
}

uint32_t Controls::get_patchcv_reading() {
	return 0;
}

uint32_t Controls::get_jacksense_reading() {
	uint16_t main_jacksense = jacksense_reader.get_last_reading();
	uint16_t aux_jacksense = extaudio_jacksense_reader.get_last_reading();

	//Fix for MM p11 mono jacks: patched = high, outputs always patched
	// main_jacksense |= 0x00FF; //mark outputs always plugged

	// For stereo jacks on inputs: patched = low, outputs always patched
	// main_jacksense = (~main_jacksense) | 0x00FF;

	// For stereo jacks on all jacks: patched = low
	main_jacksense = ~main_jacksense;

	return main_jacksense | (aux_jacksense << 16);
}

} // namespace MetaModule
