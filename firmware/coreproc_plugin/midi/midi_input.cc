#include "midi/midi_in.hh"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"

namespace MetaModule
{

struct MidiInput::Internal {
	MidiQueue queue;
};

MidiInput::MidiInput()
	: internal{std::make_unique<Internal>()} {
	MidiRouter::subscribe_rx(&internal->queue);
}

MidiInput::~MidiInput() {
	MidiRouter::unsubscribe_rx(&internal->queue);
}

// Return a the next MIDI message, or std::nullopt if there are no new messages
std::optional<MidiMessage> MidiInput::pop_message() {
	// The queue carries the port alongside the message; this API predates that
	// and only exposes the message itself, so drop the port here.
	if (auto ported = internal->queue.data.get())
		return ported->msg;

	return std::nullopt;
}

// Same as pop_message() but with a different interface:
// if there is no message it does nothing and returns false.
// If there is a message, it returns true and copies the message to
// the provided message ptr.
bool MidiInput::pop_message(MidiMessage *message) {
	if (auto next_msg = pop_message(); next_msg.has_value()) {
		if (message != nullptr)
			*message = next_msg.value();
		return true;
	} else {
		return false;
	}
}

} // namespace MetaModule
