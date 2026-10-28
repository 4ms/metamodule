#include "panel_controls.hh"
#include "conf/hsem_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "drivers/hsem.hh"
#include <cstdio>

namespace MetaModule
{

using namespace mdrivlib;

namespace
{
// Same as MP1's Controls::clear_rx_message()
void clear_rx_message(Params &params) {
	params.raw_msg = MidiMessage{};
	params.midi_port = 0;
	params.midi_event.type = Midi::Event::Type::None;
	params.midi_event.port = 0;
}

// In Controls::Button order
constexpr std::array<const char *, ExpanderControls::NumButtons> ButtonNames{
	"BUT1", "BUT2", "BUT3", "BUT4", "BUT5", "BUT6", "BUT7", "BUT8",
	"NAV1", "NAV2", "NAV3", "NAV4", "NAV5", "NAV6", "KNOBSET", "PLAY",
};

constexpr uint8_t TCA9555_InputPort0 = 0x00;
} // namespace

PanelControls::PanelControls(DoubleBufParamBlock &param_blocks)
	: param_blocks{param_blocks}
	, cur_metaparams{&param_blocks[0].metaparams}
	, cur_params{param_blocks[0].params.data()}
	, cur_params_end{cur_params + param_blocks[0].params.size()} {
	// Headphone amp off until headphones are plugged in
	HpShutdownPin::high();
}

void PanelControls::start() {
	// Same as MP1's Controls::start()
	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreGlobalBase::register_channel_ISR<ParamsBuf1Lock>([this] { start_param_block<0>(); });

	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreGlobalBase::register_channel_ISR<ParamsBuf2Lock>([this] { start_param_block<1>(); });

	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();
	HWSemaphoreGlobalBase::enable_all_handlers();

	expanders.start();

	frame_task.init([this] { update(); });
	frame_task.start();
}

// The A35 just released the other block's semaphore: it's done with that block. The next frame
// starts filling it. (The HSEM interrupt can preempt update(), so update() makes the switch.)
template<size_t block_num>
void PanelControls::start_param_block() {
	next_block.store(block_num, std::memory_order_relaxed);
}

void PanelControls::start_midi(MidiHost &midi_host, UsbMidiDevice &midi_device) {
	this->midi_host = &midi_host;

	// Same as MP1's Controls::start()
	midi_host.set_rx_callback([this, &midi_host](std::span<uint8_t> rxbuffer) {
		route_usb_midi_rx(rxbuffer);
		midi_host.receive();
	});
	midi_device.set_rx_callback([this](std::span<uint8_t> rxbuffer) { route_usb_midi_rx(rxbuffer); });

	// Last: update() checks this
	this->midi_device = &midi_device;
}

// Each audio frame: MP1's read_controls_task
void PanelControls::update() {
	frame_count = frame_count + 1;

	rotary.update();
	rotary_button.update();
	back_button.update();

	ctl_encoder.update();
	ctl_encoder_pos = ctl_encoder_pos + ctl_encoder.read();
	ctl_encoder_button.update();
	gate_in_1.update();
	gate_in_2.update();
	expanders.update();
	update_headphone_amp();

	if (auto block = next_block.exchange(-1, std::memory_order_relaxed); block >= 0) {
		auto &param_block = param_blocks[block];
		cur_metaparams = &param_block.metaparams;
		cur_params = param_block.params.data();
		cur_params_end = cur_params + param_block.params.size();
		first_frame = true;
		block_full = false;
	}

	if (block_full)
		return;

	if (first_frame) {
		first_frame = false;
		update_metaparams();
	}

	if (midi_device)
		process_midi_frame(*cur_params);

	if (++cur_params == cur_params_end)
		block_full = true;
}

void PanelControls::update_metaparams() {
	update_rotary();

	cur_metaparams->meta_buttons[0].transfer_events(back_button);

	cur_metaparams->usb_connection = usb_connection;

	if (midi_device) {
		update_midi_connected();
		cur_metaparams->midi_ports_connected = midi_usb_connected ? (1 << Midi::Event::USB) : 0;
	}
}

// Same as MP1's Controls::update_midi_connected()
void PanelControls::update_midi_connected() {
	midi_usb_connected_raw.update(midi_host->is_connected() || midi_device->is_connected());

	if (midi_usb_connected_raw.went_low())
		midi_parser.start_all_notes_off_sequence();

	if (midi_usb_connected_raw.went_high())
		midi_usb_connected = true;

	if (cur_metaparams->midi_poly_chans > 0)
		midi_parser.set_poly_num(cur_metaparams->midi_poly_chans);

	midi_parser.set_14bit_mode(cur_metaparams->midi_14bit_mode);
}

// MP1's Controls::parse_midi(), for one frame, without the MIDI expander
void PanelControls::process_midi_frame(Params &params) {
	// The audio stream left this frame's outgoing message here
	if (MidiMessage out_msg = params.raw_msg; out_msg.raw() != MidiMessage{}.raw()) {
		if (params.midi_port == Midi::Event::Port::USB && midi_usb_connected_raw.is_high()) {
			std::array<uint8_t, 4> bytes;
			out_msg.make_usb_msg(bytes);
			if (midi_host->is_connected())
				midi_host->transmit(bytes);
			else if (midi_device->is_connected())
				midi_device->transmit(bytes);
		}
	}

	if (auto msg = midi_usb_rx_buf.get(); msg.has_value()) {
		params.raw_msg = msg.value();
		params.midi_port = Midi::Event::Port::USB;
		params.midi_event = midi_parser.parse(msg.value());
		params.midi_event.port = Midi::Event::Port::USB;

	} else if (auto noteoff = midi_parser.step_all_notes_off_sequence()) {
		if (noteoff->type == Midi::Event::Type::None) {
			midi_usb_connected = false;
			cur_metaparams->midi_ports_connected &= ~(1 << Midi::Event::USB);
			clear_rx_message(params);
		} else {
			// The panic sequence is a USB-disconnect artifact, not something a jack sent
			params.midi_event = *noteoff;
			params.midi_event.port = Midi::Event::Port::USB;
			params.raw_msg = {0x80, noteoff->note, 0};
			params.midi_port = Midi::Event::Port::USB;
		}

	} else {
		clear_rx_message(params);
	}
}

// USB interrupt (device) or main loop (host)
void PanelControls::route_usb_midi_rx(std::span<uint8_t> rxbuffer) {
	while (rxbuffer.size() >= 4) {
		midi_usb_rx_buf.put(MidiMessage{rxbuffer[0], rxbuffer[1], rxbuffer[2], rxbuffer[3]});
		rxbuffer = rxbuffer.subspan(4);
	}
}

// Same as MP1's Controls::update_rotary()
void PanelControls::update_rotary() {
	if (rotary_button.is_just_pressed()) {
		rotary_moved_while_pressed = false;
		cur_metaparams->rotary_button.register_rising_edge();
	}

	if (rotary_button.is_just_released()) {
		if (rotary_moved_while_pressed) {
			cur_metaparams->rotary_button.reset();
		} else {
			cur_metaparams->rotary_button.register_falling_edge();
		}
	}
	cur_metaparams->rotary_button.set_state_no_events(rotary_button.is_pressed());

	int new_rotary_motion = rotary.read();
	bool pressed = rotary_button.is_pressed();
	cur_metaparams->rotary.motion = pressed ? 0 : new_rotary_motion;
	cur_metaparams->rotary_pushed.motion = pressed ? new_rotary_motion : 0;
	// If the rotary was turned at any point since the button was pressed
	rotary_moved_while_pressed |= pressed && (new_rotary_motion != 0);
}

} // namespace MetaModule

namespace MetaModule
{

void PanelControls::update_headphone_amp() {
	if (++hp_sense_ctr < HpSenseFrames)
		return;
	hp_sense_ctr = 0;

	hp_sense.register_state(HpSensePin::read());

	if (hp_sense.just_went_high()) {
		HpShutdownPin::low();
		headphones_plugged = true;
	}
	if (hp_sense.just_went_low()) {
		HpShutdownPin::high();
		headphones_plugged = false;
	}
}

void PanelControls::process() {
	expanders.process();
	print_changes();
}

void PanelControls::update_jack_sense(mdrivlib::I2CPeriph &i2c4) {
	auto now = HAL_GetTick();
	if (now - last_jack_sense_tm < JackSensePollMs)
		return;
	last_jack_sense_tm = now;

	std::array<uint8_t, 2> rx{};
	if (i2c4.mem_read(JackSense::gpio_expander_conf.addr << 1, TCA9555_InputPort0, 1, rx.data(), rx.size()) !=
		mdrivlib::I2CPeriph::I2C_NO_ERR)
	{
		if (!jack_sense_failed)
			printf("M33: jack sense expander U1212: read FAILED\n");
		jack_sense_failed = true;
		return;
	}
	jack_sense_failed = false;

	uint16_t reading = (rx[1] << 8) | rx[0];
	auto prev = jack_sense_reading;
	jack_sense_reading = reading;

	if (!prev) {
		printf("Jack sense: 0x%04x\n", reading);
		return;
	}

	// jacksense_pin_order: panel jacks (ins, then outs) -> bits
	for (unsigned jack = 0; jack < std::size(jacksense_pin_order); jack++) {
		auto bit = jacksense_pin_order[jack];
		if (((reading ^ *prev) >> bit) & 1) {
			auto name = jack < PanelDef::NumUserFacingInJacks ? PanelDef::InJackNames[jack] :
																PanelDef::OutJackNames[jack - PanelDef::NumUserFacingInJacks];
			printf("Jack sense: %.*s = %u\n", int(name.size()), name.data(), (reading >> bit) & 1);
		}
	}
}

// Bring-up: reports the controls that aren't passed on to the param blocks yet
void PanelControls::print_changes() {
	for (unsigned i = 0; i < ExpanderControls::NumEncoders; i++) {
		auto pos = expanders.encoder_position(i);
		if (pos != printed_enc_positions[i]) {
			printf("ENC%u %+ld (%ld)\n", i + 1, long(pos - printed_enc_positions[i]), long(pos));
			printed_enc_positions[i] = pos;
		}

		auto &but = expanders.encoder_button(i);
		if (but.is_just_pressed())
			printf("ENC%u button pressed\n", i + 1);
		if (but.is_just_released())
			printf("ENC%u button released\n", i + 1);
	}

	for (unsigned i = 0; i < ExpanderControls::NumButtons; i++) {
		auto &but = expanders.button(i);
		if (but.is_just_pressed())
			printf("%s pressed\n", ButtonNames[i]);
		if (but.is_just_released())
			printf("%s released\n", ButtonNames[i]);
	}

	if (int32_t pos = ctl_encoder_pos; pos != printed_ctl_encoder_pos) {
		printf("CTLENC %+ld (%ld)\n", long(pos - printed_ctl_encoder_pos), long(pos));
		printed_ctl_encoder_pos = pos;
	}
	if (ctl_encoder_button.is_just_pressed())
		printf("CTLENC button pressed\n");
	if (ctl_encoder_button.is_just_released())
		printf("CTLENC button released\n");

	if (bool g = gate_in_1.is_high(); g != printed_gate_in_1) {
		printf("GateIn1 %s\n", g ? "high" : "low");
		printed_gate_in_1 = g;
	}
	if (bool g = gate_in_2.is_high(); g != printed_gate_in_2) {
		printf("GateIn2 %s\n", g ? "high" : "low");
		printed_gate_in_2 = g;
	}

	if (bool hp = headphones_plugged; hp != printed_headphones_plugged) {
		printf("Headphones %s: amp %s\n", hp ? "plugged in" : "unplugged", hp ? "on" : "off");
		printed_headphones_plugged = hp;
	}
}

} // namespace MetaModule
