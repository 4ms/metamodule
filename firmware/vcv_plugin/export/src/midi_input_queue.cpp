#include "midi.hpp"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"

namespace rack::midi
{

struct InputQueue::Internal {
	MetaModule::MidiQueue queue;
};

InputQueue::InputQueue()
	: internal(new Internal) {

	MetaModule::MidiRouter::subscribe_rx(&internal->queue);
}

InputQueue::~InputQueue() {
	MetaModule::MidiRouter::unsubscribe_rx(&internal->queue);
	delete internal;
}

void InputQueue::onMessage(const Message &message) {
	// Who calls this?
	// MidiMessage msg{message.bytes[0], message.bytes[1], message.bytes[2]};
	// internal->queue.put(msg);
}

bool InputQueue::tryPop(rack::midi::Message *messageOut, int64_t maxFrame) {
	if (!messageOut)
		return false;

	if (auto msg = internal->queue.get()) {
		// Convert to rack::midi::Message
		if (msg->status & 0x80) { // status byte
			if (channel < 0 || (channel == msg->status.channel)) {
				messageOut->setSize(msg->message_size());
				messageOut->bytes[0] = msg->status;
				messageOut->bytes[1] = msg->data.byte[0];
				messageOut->bytes[2] = msg->data.byte[1];
				return true;
			}
		}
	}

	return false;
}

size_t InputQueue::size() {
	return internal->queue.count();
}

} // namespace rack::midi
