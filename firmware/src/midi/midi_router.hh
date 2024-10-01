#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"

namespace MetaModule
{

struct MidiRouter {
	static void subscribe(MidiQueue *listener);
	static void unsubscribe(MidiQueue *listener);
	static void push_incoming_message(MidiMessage msg);
};

} // namespace MetaModule
