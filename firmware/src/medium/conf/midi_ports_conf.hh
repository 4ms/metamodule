#pragma once
#include "midi/midi_message.hh"
#include <array>

namespace MetaModule::Midi
{

// The MIDI ports, in the order the GUI and the modules' port menus list them: the USB jack, and the
// MIDI Expander's TRS and DIN5 jacks
inline constexpr std::array<Port, 3> BoardPorts{USB, TRS, DIN5};

} // namespace MetaModule::Midi
