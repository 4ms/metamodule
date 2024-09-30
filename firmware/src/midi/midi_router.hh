#pragma once
#include "midi_message.hh"
#include "midi_queue.hh"

namespace MetaModule
{

struct MidiRouter {

	static void subscribe(MidiQueue *listener);
	void push_incoming_message(MidiMessage msg);
};

} // namespace MetaModule
