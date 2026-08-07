#include "midi/midi_router.hh"
#include "midi/midi_message.hh"
#include "midi/midi_queue.hh"
#include <list>

namespace MetaModule
{

namespace
{
std::list<MidiQueue *> listeners;
std::list<MidiQueue *> transmitters;
} // namespace

void MidiRouter::subscribe_rx(MidiQueue *listener) {
	listeners.push_back(listener);
}

void MidiRouter::unsubscribe_rx(MidiQueue *listener) {
	std::erase(listeners, listener);
}

void MidiRouter::push_incoming_message(MidiMessage msg, uint8_t port) {
	for (auto ob : listeners) {
		ob->data.put({msg, port});
	}
}

void MidiRouter::subscribe_tx(MidiQueue *outqueue) {
	transmitters.push_back(outqueue);
}

void MidiRouter::unsubscribe_tx(MidiQueue *outqueue) {
	std::erase(transmitters, outqueue);
}

std::optional<MidiMessage> MidiRouter::pop_outgoing_message() {
	for (auto xmitter : transmitters) {
		if (auto msg = xmitter->data.get()) {
			// return the first outgoing message found.
			// TX carries no port yet: destination routing is still to come, so
			// the port field on an outgoing message is unused.
			return msg->msg;
		}
	}
	return {};
}

} // namespace MetaModule
