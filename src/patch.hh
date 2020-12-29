#pragma once
#include "moduleTypes.h"
#include <vector>

// const int MAX_MODULES_IN_PATCH = 32;
// const int MAX_NODES_IN_PATCH = 256;
// const int MAX_CONNECTIONS_PER_NODE = 16;

struct EndPoint {
	int module_id;
	int jack_id;
};

struct StaticParam {
	int module_id;
	int param_id;
	float value;
};

// using Node = std::array<EndPoint, MAX_CONNECTIONS_PER_NODE>;
// using NetList = std::array<Node, MAX_NODES_IN_PATCH>;
// using ModuleList = std::array<ModuleType, MAX_MODULES_IN_PATCH>;

using Node = std::vector<EndPoint>;
using NetList = std::vector<Node>;
using ModuleList = std::vector<ModuleType>;
using StaticParamList = std::vector<StaticParam>;

struct Patch {
	ModuleList modules_used;
	NetList nets;
	StaticParamList knobs;

	// int num_nets, num_modules; // if we're not using vectors
};

