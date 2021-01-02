#pragma once
#include "coreProcessor.h"
#include <memory>
#ifdef STM32F7
	#include "string.h"
#else
	#include <string>
#endif

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

	static bool registerModuleType(ModuleIDType id, const char *name, CreateModuleFunc funcCreate)
	{
		if (!is_registered[id]) {
			creation_funcs[id] = funcCreate;
			is_registered[id] = true;
#ifdef STM32F7
			strcpy(module_names[id], name);
			// strcpy(module_names[id], name.c_str());
#else
			module_names[id] = name;
#endif
			return true;
		}
		return false;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleIDType id)
	{
		if (is_registered[id])
			return creation_funcs[id]();

		return nullptr;
	}

	static std::string getModuleTypeName(ModuleIDType id)
	{
		if (is_registered[id])
			return module_names[id];

		return "Not found.";
	}

private:
	static inline std::array<CreateModuleFunc, NUM_MODULE_TYPES> creation_funcs;
	static inline std::array<char[20], NUM_MODULE_TYPES> module_names;
	static inline std::array<bool, NUM_MODULE_TYPES> is_registered = {};
};
