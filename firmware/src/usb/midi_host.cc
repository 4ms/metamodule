#include "midi_host.hh"
#include "printf.h"

extern "C" void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost) {
	auto msg = MidiHost::_instance->get_rx_message();
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

	MidiHost::_instance->start_rx();
}
