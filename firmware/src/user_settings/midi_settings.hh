#pragma once
#include <cstdint>
#include <utility>

namespace MetaModule
{

struct MidiSettings {
	enum class MidiFeedback : uint32_t { Disabled = 0, Enabled = 1 };

	MidiFeedback midi_feedback{MidiFeedback::Enabled};
	bool midi_quick_mapping{true}; // Enable MIDI quick mapping by default

	void make_valid() {
		if (std::to_underlying(midi_feedback) > 1) {
			midi_feedback = MidiFeedback::Disabled;
		}
		
		// Ensure midi_quick_mapping is a valid boolean
		if (*reinterpret_cast<uint8_t *>(&midi_quick_mapping) > 1) {
			midi_quick_mapping = true;
		}
	}
};

} // namespace MetaModule
