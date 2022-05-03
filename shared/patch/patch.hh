#pragma once
#include "CoreModules/moduleFactory.hh"
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

// 8 Bytes
struct StaticParam {
	uint16_t module_id;
	uint16_t param_id;
	float value;
};

using AliasNameString = StaticString<15>;

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

// 16 Bytes
struct InternalCable {
	Jack out;
	std::vector<Jack> ins;
};

// 16 Bytes
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
