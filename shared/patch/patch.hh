#pragma once
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel.hh"
#include "util/static_string.hh"

// #define USE_NODES
static constexpr bool USE_NODES = false;

const int MAX_MODULES_IN_PATCH = 16;
const int MAX_PARAMS_IN_PATCH = 64;
const int MAX_JACKS_PER_MODULE = 32;
const int MAX_NODES_IN_PATCH = MAX_JACKS_PER_MODULE * MAX_MODULES_IN_PATCH;

// FixMe: non-node only code:
const int MAX_CONNECTIONS_PER_NODE = 4;

// Todo: will this pack into 4 bytes on all systems?
struct Jack {
	uint16_t module_id;
	uint16_t jack_id;
};

struct StaticParam {
	uint16_t module_id;
	uint16_t param_id;
	float value;
};

struct MappedParam {
	uint16_t module_id;
	uint16_t param_id;
	uint16_t panel_knob_id;
};

// FixMe: non-node only code:
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

// Todo: move cached patch info here:
struct PatchAnalysis {
	// get_panel_input_connection
	// get_panel_output_connection
	// get_duplicate_module_type_id
};

struct PatchRef {
	PatchRef(const Patch &p)
		: patch(p)
	{}

	const Patch &patch;
};
