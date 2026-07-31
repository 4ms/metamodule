#include "midi/midi_out.hh"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"

namespace MetaModule
{

struct MidiOutput::Internal {
	MidiQueue queue;
};

MidiOutput::MidiOutput()
	: internal{std::make_unique<Internal>()} {
	MidiRouter::subscribe_tx(&internal->queue);
}

MidiOutput::~MidiOutput() {
	MidiRouter::unsubscribe_tx(&internal->queue);
}

void MidiOutput::push_message(MidiMessage msg) {
	internal->queue.data.put(msg);
}

bool MidiOutput::is_queue_full() const {
	return internal->queue.data.full();
}
} // namespace MetaModule
