#pragma once
#include "CoreModules/moduleFactory.hh"
#include "util/static_string.hh"
#include <array>

const int MAX_MODULES_IN_PATCH = 32;

// maximum number of jacks involved in a stacked cable (4 means 1 output -> 3 inputs)
const int MAX_CONNECTIONS_PER_NODE = 4;

// maximum number of knob mapped to a single panel knob
const int MAX_KNOBS_PER_MAPPING = 16;

// 4 Bytes
struct Jack {
	int16_t module_id;
	int16_t jack_id;
	bool operator==(const Jack &other) const {
		return this->module_id == other.module_id && this->jack_id == other.jack_id;
	}
};

// 8 Bytes
struct StaticParam {
	int16_t module_id;
	int16_t param_id;
	float value;
};

// 16 Bytes
struct MappedKnob {
	int16_t panel_knob_id;
	int16_t module_id;
	int16_t param_id;
	int16_t curve_type; // reserved for future use
	float range;
	float offset;

	// Returns the value of the mapped knob, given the panel knob value
	// Return value goes from offset to offset+range as panel_val goes from 0 to 1
	// If range<0 then mapping will be reversed direction
	float get_mapped_val(float panel_val) {
		return range * panel_val + offset;
	}
};

// If number of ins exceeds MAX_CONNECTIONS_PER_NODE, then just add multiple InternalCable's
// 64 Bytes
struct InternalCable {
	Jack out;
	std::array<Jack, MAX_CONNECTIONS_PER_NODE - 1> ins;
};

// 64 Bytes
struct MappedInputJack {
	int32_t panel_jack_id;
	std::array<Jack, MAX_CONNECTIONS_PER_NODE - 1> ins;
};

// 8 Bytes
struct MappedOutputJack {
	int32_t panel_jack_id;
	Jack out;
};

// 48 Bytes
struct PatchHeader {
	uint32_t header_version;

	ModuleTypeSlug patch_name;

	uint16_t num_modules;
	uint16_t num_int_cables;

	uint16_t num_mapped_ins;
	uint16_t num_mapped_outs;

	uint16_t num_static_knobs;
	uint16_t num_mapped_knobs;
};

// Following PatchHeader is DATASIZE bytes of data,
// where DATASIZE = num_modules*sizeof(ModuleTypeSlug) + num_nets*sizeof(InternalCable)
// 					+ num_static_knobs*sizeof(StaticParam) + num_mapped_knobs*sizeof(MappedKnob)
//
// ModuleTypeSlug module_slugs[num_modules];
// InternalCable int_cables[num_int_cables];
// MappedInputJack mapped_ins[num_mapped_ins];
// MappedOutputJack mapped_outs[num_mapped_outs];
// StaticParam static_knobs[num_static_knobs];
// MappedKnob mapped_knobs[num_mapped_knobs];
