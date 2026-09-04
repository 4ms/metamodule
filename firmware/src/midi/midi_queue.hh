#pragma once
#include "midi/midi_message.hh"
#include "util/circular_buffer_opt.hh"

namespace MetaModule
{

// A received message plus the port it arrived on, so listeners can filter by
// jack. The port can't live in MidiMessage: that's plugin ABI, and both nibbles
// of its usb_hdr are already spoken for (cin describes the packet, cable_num is
// the attached USB device's own cable number).
struct PortedMidiMessage {
	MidiMessage msg{};
	uint8_t port{}; // Midi::Event::Port

	PortedMidiMessage() = default;
	PortedMidiMessage(MidiMessage m, uint8_t p = 0)
		: msg{m}
		, port{p} {
	}
};

struct MidiQueue {
	CircularBufferOpt<PortedMidiMessage, 128> data;
};

} // namespace MetaModule
