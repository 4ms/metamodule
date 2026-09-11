#include "midi/midi_router.hh"
#include "midi/midi_message.hh"
#include "midi/midi_queue.hh"
#include <atomic>
#include <list>

namespace MetaModule
{

namespace
{
std::list<MidiQueue *> listeners;
std::list<MidiQueue *> transmitters;

// Number of queues the patch subscribed (system queues not counted)
std::atomic<unsigned> num_patch_subs{};
} // namespace

void MidiRouter::subscribe_rx(MidiQueue *listener) {
	listeners.push_back(listener);
	num_patch_subs.fetch_add(1, std::memory_order_relaxed);
}

void MidiRouter::unsubscribe_rx(MidiQueue *listener) {
	if (std::erase(listeners, listener))
		num_patch_subs.fetch_sub(1, std::memory_order_relaxed);
}

void MidiRouter::push_incoming_message(MidiMessage msg, uint8_t port) {
	for (auto ob : listeners) {
		ob->data.put({msg, port});
	}
}

void MidiRouter::subscribe_tx(MidiQueue *outqueue) {
	transmitters.push_back(outqueue);
	num_patch_subs.fetch_add(1, std::memory_order_relaxed);
}

void MidiRouter::unsubscribe_tx(MidiQueue *outqueue) {
	if (std::erase(transmitters, outqueue))
		num_patch_subs.fetch_sub(1, std::memory_order_relaxed);
}

void MidiRouter::subscribe_tx_system(MidiQueue *outqueue) {
	transmitters.push_back(outqueue);
}

void MidiRouter::unsubscribe_tx_system(MidiQueue *outqueue) {
	std::erase(transmitters, outqueue);
}

std::optional<PortedMidiMessage> MidiRouter::pop_outgoing_message() {
	for (auto xmitter : transmitters) {
		if (auto msg = xmitter->data.get()) {
			// return the first outgoing message found, carrying the destination
			// port the sending module chose.
			return msg;
		}
	}
	return {};
}

bool MidiRouter::has_patch_subscribers() {
	return num_patch_subs.load(std::memory_order_relaxed) > 0;
}

} // namespace MetaModule
