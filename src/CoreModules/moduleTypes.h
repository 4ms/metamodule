#pragma once
#include "coreProcessor.h"
#include <map>
#include <memory>
#include <string>

enum ModuleType {
	PANEL,
	LFO,
	MIXER4,
	AD_ENVELOPE,
	CROSSFADE,
	LOGIC,
	SAMPLEHOLD,
	ATTENUVERT,
	FADEDELAY,
	VCA,

	NUM_MODULE_TYPES
};

using ModuleIDType = ModuleType;

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleIDType id, const std::string name, CreateModuleFunc funcCreate)
	{
		if (auto it = creation_funcs.find(id); it == creation_funcs.end()) {
			creation_funcs[id] = funcCreate;
			module_names[id] = name;
			return true;
		}
		return false;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleIDType id)
	{
		if (auto it = creation_funcs.find(id); it != creation_funcs.end())
			return it->second();

		return nullptr;
	}

	static std::string getModuleTypeName(ModuleIDType id)
	{
		if (auto it = module_names.find(id); it != module_names.end())
			return module_names[id];

		return "Not found. ID=" + std::to_string(static_cast<size_t>(id));
	}

private:
	static inline std::map<ModuleIDType, CreateModuleFunc> creation_funcs;
	static inline std::map<ModuleIDType, std::string> module_names;
};

