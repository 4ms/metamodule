#pragma once
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel.hh"
#include "util/static_string.hh"

// #define USE_NODES
static constexpr bool USE_NODES = false;

const int MAX_MODULES_IN_PATCH = 8;
const int MAX_PARAMS_IN_PATCH = 64;
const int MAX_JACKS_PER_MODULE = 32;
const int MAX_NODES_IN_PATCH = MAX_JACKS_PER_MODULE * MAX_MODULES_IN_PATCH;

const int MAX_CONNECTIONS_PER_NODE = 16;
const int MAX_KNOBS_PER_MAPPING = 16;

struct Jack {
	int16_t module_id;
	int16_t jack_id;
};

struct StaticParam {
	int16_t module_id;
	int16_t param_id;
	float value;
};

struct MappedParam {
	int16_t module_id;
	int16_t param_id;
	int16_t panel_knob_id;
};

struct Net {
	uint32_t num_jacks;
	std::array<Jack, MAX_CONNECTIONS_PER_NODE> jacks;
};
using NetList = std::array<Net, MAX_NODES_IN_PATCH>;

using ModuleList = std::array<ModuleTypeSlug, MAX_MODULES_IN_PATCH>;
using ModuleNodeList = uint8_t[MAX_JACKS_PER_MODULE]; // std::array<uint8_t, MAX_JACKS_PER_MODULE>;
using NodeList = std::array<ModuleNodeList, MAX_MODULES_IN_PATCH>;
using StaticParamList = std::array<StaticParam, MAX_PARAMS_IN_PATCH>;
using MappedParamList = std::array<MappedParam, Panel::NumKnobs>;

struct Patch {
	ModuleTypeSlug patch_name;
	ModuleList modules_used;
	int num_modules;

	NodeList module_nodes;

	// FixMe: non-node only code:
	NetList nets;
	int num_nets;

	StaticParamList static_knobs;
	int num_static_knobs;

	MappedParamList mapped_knobs;
	int num_mapped_knobs;
};

struct PatchRef {
	PatchRef(const Patch &p)
		: patch(p)
	{}

	const Patch &patch;
};

////////////////////////

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
	float get_mapped_val(float panel_val)
	{
		return range * panel_val + offset;
	}
};

// If number of ins exceeds MAX_CONNECTIONS_PER_NODE, then just add multiple InternalCable's
struct InternalCable {
	Jack out;
	std::array<Jack, MAX_CONNECTIONS_PER_NODE - 1> ins;
};

struct MappedInputJack {
	int32_t panel_jack_id;
	std::array<Jack, MAX_CONNECTIONS_PER_NODE - 1> ins;
};

struct MappedOutputJack {
	int32_t panel_jack_id;
	Jack out;
};

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
// where DATASIZE = name_strlen + 1 + num_modules*sizeof(ModuleTypeSlug) + num_nets*sizeof(InternalCable)
// 					+ num_static_knobs*sizeof(StaticParam) + num_mapped_knobs*sizeof(MappedParamC)
//
// char patch_name[name_strlen+1]; //null terminated
// ModuleTypeSlug module_slugs[num_modules];
// InternalCable int_cables[num_int_cables];
// MappedInputJack mapped_ins[num_mapped_ins];
// MappedOutputJack mapped_outs[num_mapped_outs];
// StaticParam static_knobs[num_static_knobs];
// MappedKnob mapped_knobs[num_mapped_knobs];
