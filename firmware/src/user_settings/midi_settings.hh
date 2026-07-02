#pragma once
#include <cstdint>
#include <utility>

namespace MetaModule
{

struct MidiSettings {
	enum class MidiFeedback : uint32_t { Disabled = 0, Enabled = 1 };
	enum class KnobsetControl : uint32_t { Disabled = 0, Enabled = 1 };
	enum class Midi14BitCC : uint32_t { Disabled = 0, Enabled = 1 };

	MidiFeedback midi_feedback{MidiFeedback::Enabled};
	KnobsetControl knobset_control{KnobsetControl::Disabled};
	uint32_t knobset_cc{0};
	uint32_t knobset_channel{16};

	// When enabled, the MIDI parser combines CC 0-31 (MSB) with CC 32-63 (LSB) into
	// a single 14-bit value. Default off (standard 7-bit CC behavior).
	Midi14BitCC midi_14bit_cc{Midi14BitCC::Disabled};

	void make_valid() {
		if (std::to_underlying(midi_feedback) > 1) {
			midi_feedback = MidiFeedback::Disabled;
		}
		if (std::to_underlying(knobset_control) > 1) {
			knobset_control = KnobsetControl::Disabled;
		}
		if (std::to_underlying(midi_14bit_cc) > 1) {
			midi_14bit_cc = Midi14BitCC::Disabled;
		}
		if (knobset_cc > 127) {
			knobset_cc = 0;
		}
		if (knobset_channel < 1 || knobset_channel > 16) {
			knobset_channel = 1;
		}
	}
};

} // namespace MetaModule
