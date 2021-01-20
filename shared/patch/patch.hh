#pragma once
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel.hh"
#include <vector>

// Todo: will this pack into 4 bytes on all systems?
struct EndPoint {
	uint16_t module_id;
	uint16_t jack_id;
};

struct StaticParam {
	uint16_t module_id;
	uint16_t param_id;
	float value;
};

const int MAX_MODULES_IN_PATCH = 16;
const int MAX_NODES_IN_PATCH = 256;
const int MAX_PARAMS_IN_PATCH = 256;
const int MAX_CONNECTIONS_PER_NODE = 16;

struct Net {
	uint16_t num_nodes;
	std::array<EndPoint, MAX_CONNECTIONS_PER_NODE> nodes;
};

struct MappedParam {
	uint16_t module_id;
	uint16_t param_id;
	uint16_t panel_knob_id;
};

using NetList = std::array<Net, MAX_NODES_IN_PATCH>;
using ModuleList = std::array<ModuleTypeSlug, MAX_MODULES_IN_PATCH>;
using StaticParamList = std::array<StaticParam, MAX_PARAMS_IN_PATCH>;
using MappedParamList = std::array<MappedParam, Panel::NumKnobs>;

struct Patch {
	ModuleList modules_used;
	int num_modules;

	NetList nets;
	int num_nets;

	StaticParamList static_knobs;
	int num_static_knobs;

	MappedParamList mapped_knobs;
	int num_mapped_knobs;
};

