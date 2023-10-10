#pragma once
#include "midi_def.hh"
#include "util/static_string.hh"
#include <optional>
#include <vector>

constexpr int MAX_MODULES_IN_PATCH = 32;
constexpr unsigned MaxKnobSets = 8;

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
		return (panel_knob_id == static_cast<uint16_t>(MidiMonoNoteParam));
	}

	bool is_monophonic_gate() const {
		return (panel_knob_id == static_cast<uint16_t>(MidiMonoGateParam));
	}

	bool operator==(const MappedKnob &other) {
		return (module_id == other.module_id) && (param_id == other.param_id);
	}
};
static_assert(sizeof(MappedKnob) == 32, "MappedKnob should be 32B");

struct MappedKnobSet {
	std::vector<MappedKnob> set;
	AliasNameString name;
};

struct InternalCable {
	Jack out;
	std::vector<Jack> ins;
	std::optional<uint16_t> color;
};

struct MappedInputJack {
	uint32_t panel_jack_id;
	std::vector<Jack> ins;
	AliasNameString alias_name;

	std::optional<uint32_t> midi_note_pitch() const {
		return is_midi_note_pitch() ? std::optional<uint32_t>{panel_jack_id - MidiMonoNoteJack} : std::nullopt;
	}

	std::optional<uint32_t> midi_note_gate() const {
		return is_midi_note_gate() ? std::optional<uint32_t>{panel_jack_id - MidiMonoGateJack} : std::nullopt;
	}

	std::optional<uint32_t> midi_note_vel() const {
		return is_midi_note_vel() ? std::optional<uint32_t>{panel_jack_id - MidiMonoVelJack} : std::nullopt;
	}

	std::optional<uint32_t> midi_gate() const {
		return std::nullopt;
		// return is_midi_note_vel() ? std::optional<uint32_t>{panel_jack_id - MidiMonoVelJack} : std::nullopt;
	}

	bool is_midi_note_pitch() const {
		return (panel_jack_id >= static_cast<uint16_t>(MidiMonoNoteJack)) &&
			   (panel_jack_id <= static_cast<uint16_t>(MidiNote8Jack));
	}

	bool is_midi_note_gate() const {
		return (panel_jack_id >= static_cast<uint16_t>(MidiMonoGateJack)) &&
			   (panel_jack_id <= static_cast<uint16_t>(MidiGate8Jack));
	}

	bool is_midi_note_vel() const {
		return (panel_jack_id >= static_cast<uint16_t>(MidiMonoVelJack)) &&
			   (panel_jack_id <= static_cast<uint16_t>(MidiVel8Jack));
	}
};

// 24 Bytes
struct MappedOutputJack {
	uint32_t panel_jack_id;
	Jack out;
	AliasNameString alias_name;
};

static_assert(sizeof(MappedOutputJack) == 24, "MappedOutputJack should be 24B");

struct ModuleInitState {
	uint32_t module_id;
	// StaticString<31> plugin_slug;
	// StaticString<31> module_slug;
	// StaticString<15> version;
	std::string data_json;
	// json_t *data_json;
};
