#pragma once
#include "CoreModules/moduleTypes.h"
#include "util/math.hh"
#include <string>
#include <vector>

struct LabelButtonID {
	enum class Types { None, Knob, InputJack, OutputJack, Toggle } objType;
	int objID;
	int moduleID;

	bool operator==(const LabelButtonID &rhs) const
	{
		return (objType == rhs.objType) && (objID == rhs.objID) && (moduleID == rhs.moduleID);
	}
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

	bool isSameJack(JackStatus &other)
	{
		return (sendingJackId == other.sendingJackId) && (sendingModuleId == other.sendingModuleId);
	}
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

