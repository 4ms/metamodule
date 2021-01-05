#pragma once
#include "CoreModules/moduleTypes.h"
#include "plugin.hpp"
#include "util/math.hh"
#include <string>

struct ModuleID {
	int id;
	ModuleIDType typeID;
};

struct JackStatus {
	int sendingJackId = 0;
	int receivedJackId = 0;
	int sendingModuleId = 0;
	int receivedModuleId = 0;
	bool connected = false;
	int receivedModuleType = 2;
};

struct ParamStatus {
	float value = 0;
	int paramID = 0;
	int moduleID = 0;
};

enum GlobalMessage {
	NoMessage,
	GetAllIDs,
	GetAllPatches,
	GetAllKnobs,
	SendingIDs,
};

struct CommData {
	enum GlobalMessage messageType;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
};
