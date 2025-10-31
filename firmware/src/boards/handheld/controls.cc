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
	encoder1_but.update();
	encoder2_but.update();
	button_1.update();
	button_2.update();
	button_3.update();
	button_4.update();
	sense_in_jack.update();
	sense_out_jack.update();
}

void Controls::update_params() {
	if (_first_param) {
		_first_param = false;

		update_midi_connected();

		cur_metaparams->usb_midi_connected = usb_midi_connected;

		cur_metaparams->buttons[0].process(button_1.is_high());
		cur_metaparams->buttons[1].process(button_2.is_high());
		cur_metaparams->buttons[2].process(button_3.is_high());
		cur_metaparams->buttons[3].process(button_4.is_high());
		cur_metaparams->buttons[4].process(encoder1_but.is_high());
		cur_metaparams->buttons[5].process(encoder2_but.is_high());

		cur_metaparams->battery_status.level = batt.battery_percent_remaining();
		cur_metaparams->battery_status.is_charging = batt.is_charging();

		cur_metaparams->encoders[0].motion = encoder1.read();
		cur_metaparams->encoders[1].motion = encoder2.read();
	}

	// TODO: smooth these
	auto xyz = accel.get_latest();
	cur_params->accel[0] = std::clamp(((int32_t)xyz.x + 32768) / 65536.f, 0.f, 1.f);
	cur_params->accel[1] = std::clamp(((int32_t)xyz.y + 32768) / 65536.f, 0.f, 1.f);
	cur_params->accel[2] = std::clamp(((int32_t)xyz.z + 32768) / 65536.f, 0.f, 1.f);

	parse_midi();

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

void Controls::parse_midi() {
	// Parse outgoing MIDI message if available and connected
	if (cur_params->usb_raw_midi.raw() != MidiMessage{}.raw()) {
		if (usb_midi_connected_raw.is_high()) {
			std::array<uint8_t, 4> bytes;
			cur_params->usb_raw_midi.make_usb_msg(bytes);
			usb_midi_host.transmit(bytes);
		}
	}
	// Parse incoming MIDI messages if available
	cur_params->usb_raw_midi = usb_midi_rx_buf.get().value_or(MidiMessage{});
}

template<size_t block_num>
void Controls::start_param_block() {
	static_assert(block_num <= 1, "There is only block 0 and block 1");

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
	accel.update();
	batt.update();

	static unsigned last_dump = 0;
#ifdef DUMP_BATT_STATUS_CONTINUALLY
	if (HAL_GetTick() - last_dump > 5000) {
		last_dump = HAL_GetTick();
		batt.dump_registers();
	}
#endif

	if (button_1.is_pressed() && button_4.is_pressed()) {
		//limit to once per second
		if (HAL_GetTick() - last_dump > 1000) {
			last_dump = HAL_GetTick();
			batt.dump_registers();
		}
	}
}

void Controls::set_samplerate(unsigned sample_rate) {
	this->sample_rate = sample_rate;
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref, MidiHost &midi_host)
	: usb_midi_host{midi_host}
	, param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams) {

	set_samplerate(sample_rate);

	accel.init();
	batt.init();

	// test_pins();

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

} // namespace MetaModule
