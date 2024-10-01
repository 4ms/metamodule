#include "midi_router.hh"
#include "midi_message.hh"
#include "midi_queue.hh"
#include <list>

namespace MetaModule
{

namespace
{
std::list<MidiQueue *> listeners;
}

void MidiRouter::subscribe(MidiQueue *listener) {
	listeners.push_back(listener);
}

void MidiRouter::unsubscribe(MidiQueue *listener) {
	std::erase(listeners, listener);
}

void MidiRouter::push_incoming_message(MidiMessage msg) {
	for (auto ob : listeners) {
		ob->put(msg);
	}
}

} // namespace MetaModule
