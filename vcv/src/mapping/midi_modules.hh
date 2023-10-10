#pragma once
#include "patch/patch.hh"
#include <rack.hpp>

namespace MetaModule::MIDIMapping
{

std::vector<MappedKnob> mapMidiMaps(rack::Module *module);
std::vector<MappedInputJack> mapMidiToCV(rack::Module *module);

} // namespace MetaModule::MIDIMapping
