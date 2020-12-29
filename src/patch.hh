#pragma once
#include "moduleTypes.h"
#include <vector>

// Todo: will this pack into 4 bytes on all systems?
struct EndPoint {
	uint16_t module_id;
	uint16_t jack_id;
};

const uint16_t LAST_ = 0xFFFF;

struct StaticParam {
	uint16_t module_id;
	uint16_t param_id;
	float value;
};

const int MAX_MODULES_IN_PATCH = 64;
const int MAX_NODES_IN_PATCH = 256;
const int MAX_PARAMS_IN_PATCH = 256;
const int MAX_CONNECTIONS_PER_NODE = 16;

using Node = std::array<EndPoint, MAX_CONNECTIONS_PER_NODE>;
using NetList = std::array<Node, MAX_NODES_IN_PATCH>;
using ModuleList = std::array<ModuleType, MAX_MODULES_IN_PATCH>;
using StaticParamList = std::array<StaticParam, MAX_PARAMS_IN_PATCH>;

struct Patch {
	ModuleList modules_used;
	NetList nets;
	StaticParamList knobs;
};

