#pragma once
#include "util/static_string.hh"
#include <vector>

const int MAX_MODULES_IN_PATCH = 32;
const int MAX_KNOBS_PER_MAPPING = 16;

// 4 Bytes
struct Jack {
	uint16_t module_id;
	uint16_t jack_id;
	bool operator==(const Jack &other) const {
		return this->module_id == other.module_id && this->jack_id == other.jack_id;
	}
};
static_assert(sizeof(Jack) == 4, "Jack should be 4B");

// 8 Bytes
struct StaticParam {
	uint16_t module_id;
	uint16_t param_id;
	float value;
};
static_assert(sizeof(StaticParam) == 8, "StaticParam should be 8B");

using AliasNameString = StaticString<15>;
static_assert(sizeof(AliasNameString) == 16, "AliasNameString should be 16B");

enum class MidiKnobAlias : uint16_t {
	MonoNote = 256,
	MonoGate = 257,
};

// 32 Bytes
struct MappedKnob {
	uint16_t panel_knob_id;
	uint16_t module_id;
	uint16_t param_id;
	uint16_t curve_type; // reserved for future use
	float min;
	float max;
	AliasNameString alias_name;

	// Returns the value of the mapped knob, given the panel knob value
	// Return value goes from min to max as panel_val goes from 0 to 1
	// If max < min then mapping will be reversed direction
	float get_mapped_val(float panel_val) const {
		return (max - min) * panel_val + min;
	}

	bool is_monophonic_note() const {
		return (panel_knob_id == static_cast<uint16_t>(MidiKnobAlias::MonoNote));
	}

	bool is_monophonic_gate() const {
		return (panel_knob_id == static_cast<uint16_t>(MidiKnobAlias::MonoGate));
	}
};

static_assert(sizeof(MappedKnob) == 32, "MappedKnob should be 32B");

struct InternalCable {
	Jack out;
	std::vector<Jack> ins;
};

struct MappedInputJack {
	uint32_t panel_jack_id;
	std::vector<Jack> ins;
	AliasNameString alias_name;
	bool is_monophonic_note() const {
		return (panel_jack_id == static_cast<uint16_t>(MidiKnobAlias::MonoNote));
	}

	bool is_monophonic_gate() const {
		return (panel_jack_id == static_cast<uint16_t>(MidiKnobAlias::MonoGate));
	}
};

// 24 Bytes
struct MappedOutputJack {
	uint32_t panel_jack_id;
	Jack out;
	AliasNameString alias_name;
};

static_assert(sizeof(MappedOutputJack) == 24, "MappedOutputJack should be 24B");

//TO BE REMOVED:
// struct MidiMap {
// 	int8_t midi_cc;
// 	uint8_t midi_chan;

// 	uint16_t module_id;
// 	uint16_t param_id;
// 	uint16_t curve_type; // reserved for future use
// 	float min;
// 	float max;
// 	AliasNameString alias_name;

// 	bool is_monophonic_note() const {
// 		return (midi_cc == -128) && (midi_chan & (1 << 7));
// 	}

// 	bool is_monophonic_gate() const {
// 		return (midi_cc == -128) && !(midi_chan & 0b10000000);
// 	}
// };
