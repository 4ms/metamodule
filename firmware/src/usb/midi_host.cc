#include "midi_host.hh"
#include "debug.hh"
#include "printf.h"
#include "util/circular_buffer.hh"

// static bool led_state = false;

extern "C" void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost, uint8_t *end_data) {
	// led_state = !led_state;
	// Debug::green_LED1::set(rled_state);

	// swap read and write buffers, and start receiving
	MidiHost::_instance->swap_rx_buffers();
	MidiHost::_instance->start_rx(phost);
	// call callback on rx buffer  (which pushes recd data to circular_buffer)
	auto rxbuf = MidiHost::_instance->get_midi_data();
	MidiHost::_instance->_rx_callback(rxbuf);
}

void debug_midi_rx_callback(std::span<uint8_t> rxbuffer) {
	if (rxbuffer.size() < 4)
		return;

	auto msg = Midi::MidiMessage{rxbuffer[1], rxbuffer[2], rxbuffer[3]};
	printf_(".");
	if (msg.is_command<Midi::NoteOn>()) {
		printf_("Note: %d Vel: %d\n", msg.data.byte[0], msg.data.byte[1]);
	} else if (msg.is_command<Midi::NoteOff>()) {
		printf_("Note: %d off\n", msg.data.byte[0]);
	} else if (msg.is_command<Midi::PolyKeyPressue>()) {
		printf_("Poly Key Pressure: %d %d\n", msg.data.byte[0], msg.data.byte[1]);
	} else if (msg.is_command<Midi::ControlChange>()) {
		printf_("CC: #%d = %d\n", msg.data.byte[0], msg.data.byte[1]);
	} else if (msg.is_command<Midi::ProgramChange>()) {
		printf_("PC: #%d\n", msg.data.byte[0]);
	} else if (msg.is_command<Midi::ChannelPressure>()) {
		printf_("CP: #%d\n", msg.data.byte[0]);
	} else if (msg.is_command<Midi::ChannelPressure>()) {
		printf_("Bend: #%d\n", (msg.data.byte[0] | (msg.data.byte[1] << 7)) - 8192);
	} else if (msg.is_system_realtime<Midi::TimingClock>()) {
		// printf_("Clk\n");
	} else if (msg.is_sysex()) {
		printf_("SYSEX: 0x%02x%02x\n", msg.data.byte[0], msg.data.byte[1]);
	} else if (msg.raw_data()) {
		printf_("Raw: %06x\n", msg.raw_data());
	}
}
