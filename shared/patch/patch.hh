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
};

// 24 Bytes
struct MappedOutputJack {
	uint32_t panel_jack_id;
	Jack out;
	AliasNameString alias_name;
};

static_assert(sizeof(MappedOutputJack) == 24, "MappedOutputJack should be 24B");

//Maps a midi cc to a knob
//Or maps a note on/off to a knob or switch [0/1] -> [min/max]
struct MidiMap {
	int8_t midi_cc;	   //0..127 -> CC#, -128..-1 -> Note
	uint8_t midi_chan; //0..16
	uint16_t module_id;
	uint16_t param_id;
	uint16_t curve_type; // reserved for future use
	float min;
	float max;
	AliasNameString alias_name;
};

static_assert(sizeof(MidiMap) == 32, "MidiMap should be 32B");
