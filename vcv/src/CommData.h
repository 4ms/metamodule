#pragma once
#include "CoreModules/moduleTypes.h"
#include "util/math.hh"
#include <string>
#include <vector>

struct LabelButtonID {
	enum class Types { Knob, InputJack, OutputJack, Toggle } type;
	int ID;
};

struct ModuleID {
	int id;
	ModuleTypeSlug typeID;
	bool operator==(const ModuleID &rhs) const
	{
		return (this->id == rhs.id) && (this->typeID == rhs.typeID);
	}
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

	bool isSameParam(ParamStatus &other)
	{
		return (paramID == other.paramID) && (moduleID == other.moduleID);
	}
};

enum GlobalMessage {
	NoMessage,
	GetAllIDs,
	SendingIDs,
	InitMapping,

};

struct CommData {
	enum GlobalMessage messageType;
	std::vector<ModuleID> moduleData;
	std::vector<JackStatus> jackData;
	std::vector<ParamStatus> paramData;
	std::vector<LabelButtonID> mappings;
};
