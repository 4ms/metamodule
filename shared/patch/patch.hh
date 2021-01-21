#pragma once
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel.hh"
#include <vector>

const int MAX_MODULES_IN_PATCH = 16;
const int MAX_PARAMS_IN_PATCH = 256;
const int MAX_JACKS_PER_MODULE = 32;
const int MAX_NODES_IN_PATCH = MAX_JACKS_PER_MODULE * MAX_MODULES_IN_PATCH;

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

using ModuleList = std::array<ModuleTypeSlug, MAX_MODULES_IN_PATCH>;
using ModuleNodeList = uint8_t[MAX_JACKS_PER_MODULE]; // std::array<uint8_t, MAX_JACKS_PER_MODULE>;
using NodeList = std::array<ModuleNodeList, MAX_MODULES_IN_PATCH>;
using StaticParamList = std::array<StaticParam, MAX_PARAMS_IN_PATCH>;
using MappedParamList = std::array<MappedParam, Panel::NumKnobs>;

struct Patch {
	ModuleList modules_used;
	int num_modules;

	NodeList module_nodes;

	StaticParamList static_knobs;
	int num_static_knobs;

	MappedParamList mapped_knobs;
	int num_mapped_knobs;
};
