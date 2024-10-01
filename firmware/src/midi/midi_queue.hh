#pragma once
#include "midi_message.hh"
#include "util/circular_buffer_opt.hh"

namespace MetaModule
{

using MidiQueue = CircularBufferOpt<MidiMessage, 128>;

} // namespace MetaModule
