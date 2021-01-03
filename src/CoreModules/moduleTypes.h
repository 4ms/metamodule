#pragma once
#include "coreProcessor.h"
#include "string.h"
#include <memory>
#include <string>

struct ModuleTypeWrapper {
	static const int kStringLen = 20;
	char name[kStringLen];

	ModuleTypeWrapper()
	{
		name[0] = '\0';
	}

	ModuleTypeWrapper(const char *s)
	{
		for (size_t i = 0; i < kStringLen; i++) {
			if (i < strlen(s))
				name[i] = s[i];
			else
				name[i] = '\0';
		}
		name[kStringLen - 1] = '\0';
	}

	ModuleTypeWrapper(const std::string s)
	{
		for (size_t i = 0; i < kStringLen; i++) {
			if (i < s.length())
				name[i] = s.c_str()[i];
			else
				name[i] = '\0';
		}
		name[kStringLen - 1] = '\0';
	}
};

using ModuleIDType = ModuleTypeWrapper;

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleIDType typeslug, const char *name, CreateModuleFunc funcCreate)
	{
		int id = getTypeID(typeslug);
		if (!is_registered[id]) {
			creation_funcs[id] = funcCreate;
			is_registered[id] = true;
			// #ifdef STM32F7
			// 			strcpy(module_names[id], name);
			// 			// strcpy(module_names[id], name.c_str());
			// #else
			module_names[id] = name;
			// #endif
			return true;
		}
		return false;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleIDType typeslug)
	{
		int id = getTypeID(typeslug);
		if (is_registered[id])
			return creation_funcs[id]();

		return nullptr;
	}

	static std::string getModuleTypeName(ModuleIDType typeslug)
	{
		int id = getTypeID(typeslug);
		if (is_registered[id])
			return module_names[id];

		return "Not found.";
	}

	static int getTypeID(ModuleIDType typeslug)
	{
		return 0;
	}

private:
	static inline const int MAX_MODULE_TYPES = 64;
	static inline std::array<CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline std::array<char[20], MAX_MODULE_TYPES> module_slugs;
	static inline std::array<std::string, MAX_MODULE_TYPES> module_names;
	static inline std::array<bool, MAX_MODULE_TYPES> is_registered = {};
};
