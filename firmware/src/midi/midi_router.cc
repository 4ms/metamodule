#include "midi_router.hh"
#include <list>

namespace MetaModule
{

// static CircularBuffer<MidiMessage, 256> queue;
std::list<MidiQueue *> listeners;

void MidiRouter::subscribe(MidiQueue *listener) {
	listeners.push_back(listener);
}

void MidiRouter::push_incoming_message(MidiMessage msg) {
	for (auto ob : listeners) {
		ob->onMessage(msg);
	}
}

} // namespace MetaModule
