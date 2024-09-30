#include "midi.hpp"
#include "midi/midi_router.hh"

namespace rack::midi
{

struct InputQueue::Internal {

	MetaModule::MidiQueue queue;
};

InputQueue::InputQueue()
	: internal(new Internal) {

	MetaModule::MidiRouter::subscribe(&internal->queue);
}

} // namespace rack::midi
