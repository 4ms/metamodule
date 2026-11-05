#pragma once
#include "midi/midi_message.hh"
#include <array>

namespace MetaModule::Midi
{

// The MIDI ports, in the order the GUI and the modules' port menus list them: the USB jack, and the
// DIN5 jacks on the jack board (no TRS)
inline constexpr std::array<Port, 2> BoardPorts{USB, DIN5};

} // namespace MetaModule::Midi
