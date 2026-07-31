#pragma once
#include "midi/midi_message.hh"
#include "util/circular_buffer_opt.hh"

namespace MetaModule
{

struct MidiQueue {
	CircularBufferOpt<MidiMessage, 128> data;
};
// using MidiQueue = CircularBufferOpt<MidiMessage, 128>;

} // namespace MetaModule
