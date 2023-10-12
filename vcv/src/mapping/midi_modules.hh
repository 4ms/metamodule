#pragma once
#include "mapping/JackMap.hh"
#include <rack.hpp>

namespace MetaModule::MIDI
{

struct MidiCVSettings {
	float pwRange = 0;
	unsigned channels = 0;
	enum PolyMode { ROTATE_MODE, REUSE_MODE, RESET_MODE, MPE_MODE };
	PolyMode polyMode = ROTATE_MODE;
};

struct MidiGateSettings {
	std::array<int8_t, 16> notes{};
	bool velocity_mode = false;
	bool mpe_mode = false;
};

struct MidiCCCVSettings {
	std::array<int8_t, 16> CCnums{};
	std::array<int8_t, 16> values{};
	bool smooth = false;
	bool mpe_mode = false;
	bool lsb_mode = false;
};

struct MidiCCKnobSettings {};

struct Settings {
	MidiCVSettings CV;
	MidiGateSettings gate;
	MidiCCCVSettings CCCV;
	MidiCCKnobSettings CCKnob;
};

std::optional<MidiCVSettings> readMidiCVModule(int64_t module_id);
std::optional<MidiGateSettings> readMidiGateModule(int64_t module_id);
std::optional<MidiCCCVSettings> readMidiCCCVModule(int64_t module_id);
std::optional<MidiCCKnobSettings> readMidiMapModule(int64_t module_id);

} // namespace MetaModule::MIDI
