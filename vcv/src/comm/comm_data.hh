#pragma once
#include "CoreModules/moduleFactory.hh"
#include <cstring>
#include <vector>

struct MappableObj {
	enum class Type { None, Knob, InputJack, OutputJack, Toggle, MidiNote, MidiGate } objType;
	int64_t objID;
	int64_t moduleID;

	bool operator==(const MappableObj &rhs) const
	{
		return (objType == rhs.objType) && (objID == rhs.objID) && (moduleID == rhs.moduleID);
	}

	bool mappable_to(const Type otherType) const
	{
		return (objType == otherType) || (objType == Type::Knob && otherType == Type::MidiNote) ||
			   (objType == Type::MidiNote && otherType == Type::Knob) ||
			   (objType == Type::MidiGate && otherType == Type::Knob) ||
			   (objType == Type::Knob && otherType == Type::MidiGate);
	}

	const char *objTypeStr() const
	{
		if (objType == Type::Knob)
			return "Knob";
		if (objType == Type::InputJack)
			return "InputJack";
		if (objType == Type::OutputJack)
			return "OutputJack";
		if (objType == Type::Toggle)
			return "Toggle";
		if (objType == Type::MidiNote)
			return "MidiValue";
		if (objType == Type::MidiGate)
			return "MidiGate";
		return "None";
	}

	void setObjTypeFromString(const char *str)
	{
		if (std::strcmp(str, "Knob") == 0)
			objType = Type::Knob;
		else if (std::strcmp(str, "InputJack") == 0)
			objType = Type::InputJack;
		else if (std::strcmp(str, "OutputJack") == 0)
			objType = Type::OutputJack;
		else if (std::strcmp(str, "Toggle") == 0)
			objType = Type::Toggle;
		else if (std::strcmp(str, "MidiValue") == 0)
			objType = Type::MidiNote;
		else if (std::strcmp(str, "MidiGate") == 0)
			objType = Type::MidiGate;
		else
			objType = Type::None;
	}
};

namespace std
{
template<>
struct hash<MappableObj> {
	std::size_t operator()(const MappableObj &k) const
	{
		using std::hash;
		return ((hash<int>()(k.objID) ^ (hash<int64_t>()(k.moduleID) << 1)) >> 1) ^
			   (hash<int>()(static_cast<int>(k.objType)) << 1);
	}
};

} // namespace std

struct Mapping {
	MappableObj src;
	MappableObj dst;
	float range_min = 0.f;
	float range_max = 1.f;
	std::string alias_name{""};

	void clear()
	{
		dst.moduleID = -1;
		src.moduleID = -1;
		dst.objID = -1;
		src.objID = -1;
		dst.objType = MappableObj::Type::None;
		src.objType = MappableObj::Type::None;
		range_min = 0.f;
		range_max = 1.f;
		alias_name = "";
	}
};

struct ModuleID {
	int64_t id;
	ModuleTypeSlug slug;

	bool operator==(const ModuleID &rhs) const { return (this->id == rhs.id) && (this->slug == rhs.slug); }
};

struct JackStatus {
	int sendingJackId = 0;
	int receivedJackId = 0;
	int64_t sendingModuleId = 0;
	int64_t receivedModuleId = 0;
	bool connected = false;

	bool isSameJack(JackStatus &other)
	{
		return (sendingJackId == other.sendingJackId) && (sendingModuleId == other.sendingModuleId);
	}
};

struct ParamStatus {
	float value = 0;
	int paramID = 0;
	int64_t moduleID = 0;

	bool isSameParam(ParamStatus &other) { return (paramID == other.paramID) && (moduleID == other.moduleID); }
};
