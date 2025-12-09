#include "controls.hh"
#include "conf/debug.hh"
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include "midi_controls.hh"
#include "patch/midi_def.hh"
#include "util/countzip.hh"

#include "hardware-test.hh"

namespace MetaModule
{

using namespace mdrivlib;

void Controls::update_debouncers() {
	encoder1.update();
	encoder2.update();

	random_gate_in.update();
	trig_in.update();
	sync_in.update();
	rec_gate_in.update();
}

// Interpolate adc readings across the param block, since we capture them at a slower rate than audio process
void interpolate_adcs(unsigned update_ctr, auto &values, auto &dest) {
	if (update_ctr >= values[0].get_num_updates()) {
		// Don't overshoot value:
		for (unsigned i = 0; i < values.size(); i++) {
			auto val = values[i].target_val;
			dest[i] = std::clamp(val, 0.f, 1.f);
			values[i].cur_val = values[i].target_val;
		}
	} else {
		for (unsigned i = 0; i < values.size(); i++) {
			auto val = values[i].next();
			dest[i] = std::clamp(val, 0.f, 1.f);
		}
	}
}

void Controls::update_params() {
	// Gates
	cur_params->gate_ins = random_gate_in.is_high() ? 0b0001 : 0b00;
	cur_params->gate_ins |= trig_in.is_high() ? 0b0010 : 0b00;
	cur_params->gate_ins |= sync_in.is_high() ? 0b0100 : 0b00;
	cur_params->gate_ins |= rec_gate_in.is_high() ? 0b1000 : 0b00;

	// CV jacks (non-muxed ADCs)
	num_cv_updates++;
	interpolate_adcs(num_cv_updates, cvs, cur_params->cvs);

	// Knobs (ADC muxes)
	num_pot_updates++;
	interpolate_adcs(num_pot_updates, knobs, cur_params->knobs);

	// Block-rate metaparams
	if (_first_param) {
		_first_param = false;

		update_midi_connected();

		cur_metaparams->buttons0 = gpio_expanders.get_buttons(0);
		cur_metaparams->buttons1 = gpio_expanders.get_buttons(1);
		cur_metaparams->buttons2 = gpio_expanders.get_buttons(2);

		gpio_expanders.set_leds(0, cur_leds->leds0);
		gpio_expanders.set_leds(1, cur_leds->leds1);
		gpio_expanders.set_leds(2, cur_leds->leds2);

		set_neopixels();

		cur_metaparams->usb_midi_connected = usb_midi_connected;

		cur_metaparams->encoder[0].motion = encoder1.read();
		cur_metaparams->encoder[1].motion = encoder2.read();
	}

	parse_midi();

	output_dac();

	cur_params++;
	if (cur_params == param_blocks[0].params.end() || cur_params == param_blocks[1].params.end())
		_buffer_full = true;
}

void Controls::update_midi_connected() {
	usb_midi_connected_raw.update(usb_midi_host.is_connected());

	if (usb_midi_connected_raw.went_high()) {
		usb_midi_connected = true;
	}
}

void Controls::set_neopixels() {
	for (auto led = 0; auto color : cur_leds->neo_a) {
		neopixel_a.set_led(led, color.red(), color.green(), color.blue());
		led++;
	}

	for (auto led = 0; auto color : cur_leds->neo_b) {
		neopixel_b.set_led(led, color.red(), color.green(), color.blue());
		led++;
	}

	for (auto led = 0; auto color : cur_leds->neo_vu) {
		// neopixel_vu.set_led(led, color.red(), color.green(), color.blue());
		led++;
	}
}

void Controls::parse_midi() {
	// Parse outgoing MIDI message if available and connected
	if (cur_params->usb_raw_midi.raw() != MidiMessage{}.raw()) {
		if (usb_midi_connected_raw.is_high()) {
			std::array<uint8_t, 4> bytes;
			cur_params->usb_raw_midi.make_usb_msg(bytes);
			usb_midi_host.transmit(bytes);
		}
	}

	auto uart_midi_raw = cur_params->uart_raw_midi.raw();
	if (uart_midi_raw != MidiMessage{}.raw()) {
		uart_midi.transmit(uart_midi_raw >> 16); //status
		uart_midi.transmit(uart_midi_raw >> 8);	 //data[0]
		uart_midi.transmit(uart_midi_raw >> 0);	 //data[1]
	}

	// Parse incoming MIDI messages if available
	cur_params->usb_raw_midi = usb_midi_rx_buf.get().value_or(MidiMessage{});
	cur_params->uart_raw_midi = uart_midi_rx_buf.get().value_or(MidiMessage{});
}

template<size_t block_num>
void Controls::start_param_block() {
	static_assert(block_num <= 1, "There is only block 0 and block 1");

	// 28us width, every 1.3ms (audio block rate for 64-frame blocks) = 2.15% load
	cur_metaparams = &param_blocks[block_num].metaparams;
	cur_params = param_blocks[block_num].params.begin();
	cur_leds = &param_blocks[block_num].leds;
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

	usb_midi_host.set_rx_callback([this](std::span<uint8_t> rxbuffer) {
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
				usb_midi_rx_buf.put(msg);

			rxbuffer = rxbuffer.subspan(4);
			// msg.print();
		}
		usb_midi_host.receive();
	});
}

void Controls::process() {
	gpio_expanders.update();
}

void Controls::set_samplerate(unsigned sample_rate) {
	this->sample_rate = sample_rate;
	for (auto &knob : knobs) {
		knob.set_num_updates(sample_rate * 8 / AdcReadFrequency);
	}
	for (auto &cv : cvs) {
		cv.set_num_updates(sample_rate / AdcReadFrequency);
	}
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref, MidiHost &midi_host)
	: usb_midi_host{midi_host}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams)
	, cur_leds(&param_blocks_ref[0].leds) {

	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {

			// Store readings into unpacked array
			for (uint32_t i = ADCs::VOct; auto &cv : cvs) {
				cv.set_new_value(get_adc_reading(i));
				i++;
			}
			num_cv_updates = 0;

			auto offset = mux_chan & 0b111;
			for (uint32_t mux = ADCs::Mux1; mux <= ADCs::Mux5; mux++) {
				knobs[mux * 8 + offset].set_new_value(get_adc_reading(mux));
			}

			// Advance the MUX
			mux_chan++;
			adc_mux_a.set(mux_chan & 0b001);
			adc_mux_b.set(mux_chan & 0b010);
			adc_mux_c.set(mux_chan & 0b100);
			if (mux_chan == 0) {
				num_pot_updates = 0;
			}

			// Let mux pins settle
			int x = ADCs::mux_settle_period;
			while (x--) {
				__NOP();
			}

			// Start conversion
			ADC1->ISR = tmp | ADC_ISR_EOS;
			ADC1->CR |= ADC_CR_ADSTART;
		}
	});

	set_samplerate(sample_rate);

	adc.start();

	uart_midi.init();

	haptic_out.init();

	test_pins();

	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	// Task is called at sample rate
	read_controls_task.init([this]() {
		if (_buffer_full) {
			return;
		}
		update_debouncers();
		update_params();
	});
}

void Controls::output_dac() {
	cv_out.set(0, cur_params->dac0);
	cv_out.set(1, cur_params->dac1);
}

float Controls::get_adc_reading(uint32_t adc_id) {
	if (adc_id < raw_adc_vals.size()) {
		auto raw = (int32_t)raw_adc_vals[adc_id];
		float val = raw - ADCs::MinPotValue;
		return std::clamp(val / (ADCs::MaxPotValue - ADCs::MinPotValue), 0.f, 1.f);
	} else
		return 0;
}

} // namespace MetaModule
