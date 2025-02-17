#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"
#include <optional>

namespace MetaModule
{

struct MidiRouter {

	static void subscribe(MidiQueue *listener);

	static void unsubscribe(MidiQueue *listener);

	// When hardware receives a MIDI message, it calls this
	// to forward the msg to all listeners
	static void push_incoming_message(MidiMessage msg);

	// Pop the latest message ready to be sent out via hardware
	// Virtual patch player calls this to get a message
	// which it forwards to M4 core
	static std::optional<MidiMessage> pop_outgoing_message();
};

} // namespace MetaModule
