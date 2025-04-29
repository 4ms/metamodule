#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include <optional>

namespace MetaModule
{

struct MidiRouter {

	// MIDI RX:
	static void subscribe_rx(MidiQueue *listener);

	static void unsubscribe_rx(MidiQueue *listener);

	// When hardware receives a MIDI message, it calls this
	// to forward the msg to all listeners
	static void push_incoming_message(MidiMessage msg);

	// MIDI TX:
	static void subscribe_tx(MidiQueue *listener);

	static void unsubscribe_tx(MidiQueue *listener);

	// Pop the latest message ready to be sent out via hardware
	// Audio Stream calls this to get a message
	// which it forwards to M4 core
	static std::optional<MidiMessage> pop_outgoing_message();
};

} // namespace MetaModule
