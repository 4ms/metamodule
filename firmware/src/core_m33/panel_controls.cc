#include "panel_controls.hh"
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include <algorithm>

namespace MetaModule
{

using namespace mdrivlib;

namespace
{
// Lower priority than the HSEM interrupt (0: see HWSemaphoreGlobalBase::enable_all_handlers()), so
// a new block can start during update(), but update() never interrupts start_param_block()
const TimekeeperConfig FrameTimerConf{
	.TIMx = TIM6,
	.period_ns = TimekeeperConfig::Hz(48000),
	.priority1 = 1,
	.priority2 = 0,
};

// Same as MP1's Controls::clear_rx_message()
void clear_rx_message(Params &params) {
	params.raw_msg = MidiMessage{};
	params.midi_port = 0;
	params.midi_event.type = Midi::Event::Type::None;
	params.midi_event.port = 0;
}
} // namespace

PanelControls::PanelControls(DoubleBufParamBlock &param_blocks)
	: param_blocks{param_blocks}
	, cur_metaparams{&param_blocks[0].metaparams}
	, cur_params{param_blocks[0].params.data()} {
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

	frame_timer.init(FrameTimerConf, [this] { update(); });
	frame_timer.start();
}

// The A35 just released the other block's semaphore: it's done with that block
template<size_t block_num>
void PanelControls::start_param_block() {
	cur_metaparams = &param_blocks[block_num].metaparams;
	cur_params = param_blocks[block_num].params.data();
	new_block = true;
}

void PanelControls::start_midi(UsbMidiDevice &midi_device, volatile uint32_t const &audio_block_size) {
	this->audio_block_size = &audio_block_size;
	midi_device.set_rx_callback([this](std::span<uint8_t> rxbuffer) { route_usb_midi_rx(rxbuffer); });
	// Last: update() checks this
	this->midi_device = &midi_device;
}

void PanelControls::update() {
	rotary.update();
	rotary_button.update();
	back_button.update();

	// Like MP1, the metaparams are written once per block, at its first frame
	if (new_block) {
		new_block = false;
		update_metaparams();
	}
}

void PanelControls::update_metaparams() {
	update_rotary();

	cur_metaparams->meta_buttons[0].transfer_events(back_button);

	cur_metaparams->usb_connection = usb_connection;

	update_midi();
}

// The block's MIDI, all at once: see the header comment
void PanelControls::update_midi() {
	if (!midi_device)
		return;

	update_midi_connected();
	cur_metaparams->midi_ports_connected = midi_usb_connected ? (1 << Midi::Event::USB) : 0;

	uint32_t block_size = *audio_block_size;
	block_size = std::min<uint32_t>(block_size, StreamConf::Audio::MaxBlockSize);
	for (auto &params : std::span{cur_params, block_size})
		process_midi_frame(params);
}

// Same as MP1's Controls::update_midi_connected(), without the USB MIDI host
void PanelControls::update_midi_connected() {
	midi_usb_connected_raw.update(midi_device->is_connected());

	if (midi_usb_connected_raw.went_low())
		midi_parser.start_all_notes_off_sequence();

	if (midi_usb_connected_raw.went_high())
		midi_usb_connected = true;

	if (cur_metaparams->midi_poly_chans > 0)
		midi_parser.set_poly_num(cur_metaparams->midi_poly_chans);

	midi_parser.set_14bit_mode(cur_metaparams->midi_14bit_mode);
}

// MP1's Controls::parse_midi(), for one frame, without the MIDI expander or the USB MIDI host
void PanelControls::process_midi_frame(Params &params) {
	// The audio stream left this frame's outgoing message here
	if (MidiMessage out_msg = params.raw_msg; out_msg.raw() != MidiMessage{}.raw()) {
		if (params.midi_port == Midi::Event::Port::USB && midi_usb_connected_raw.is_high()) {
			std::array<uint8_t, 4> bytes;
			out_msg.make_usb_msg(bytes);
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

// USB interrupt
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
