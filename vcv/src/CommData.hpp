#pragma once
#include "CoreModules/moduleFactory.hh"
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

	const char *objTypeStr() const
	{
		if (objType == Types::Knob)
			return "Knob";
		if (objType == Types::InputJack)
			return "InputJack";
		if (objType == Types::OutputJack)
			return "OutputJack";
		if (objType == Types::Toggle)
			return "Toggle";
		return "None";
	}

	void setObjTypeFromString(const char *str)
	{
		if (std::strcmp(str, "Knob") == 0)
			objType = Types::Knob;
		else if (std::strcmp(str, "InputJack") == 0)
			objType = Types::InputJack;
		else if (std::strcmp(str, "OutputJack") == 0)
			objType = Types::OutputJack;
		else if (std::strcmp(str, "Toggle") == 0)
			objType = Types::Toggle;
		else
			objType = Types::None;
	}
};

namespace std
{
template<>
struct hash<LabelButtonID> {
	std::size_t operator()(const LabelButtonID &k) const
	{
		using std::hash;
		return ((hash<int>()(k.objID) ^ (hash<int>()(k.moduleID) << 1)) >> 1) ^
			   (hash<int>()(static_cast<int>(k.objType)) << 1);
	}
};

} // namespace std

struct Mapping {
	LabelButtonID src;
	LabelButtonID dst;
	float range_min = 0.f;
	float range_max = 1.f;
	std::string alias_name{""};

	void clear()
	{
		dst.moduleID = -1;
		src.moduleID = -1;
		dst.objID = -1;
		src.objID = -1;
		dst.objType = LabelButtonID::Types::None;
		src.objType = LabelButtonID::Types::None;
		range_min = 0.f;
		range_max = 1.f;
		alias_name = "";
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
