#pragma once
#include <cstdint>
#include <utility>

namespace MetaModule
{

struct MidiSettings {
	enum class MidiFeedback : uint32_t { Disabled = 0, Enabled = 1 };

	MidiFeedback midi_feedback{MidiFeedback::Enabled};

	void make_valid() {
		if (std::to_underlying(midi_feedback) > 1) {
			midi_feedback = MidiFeedback::Disabled;
		}
	}
};

} // namespace MetaModule
