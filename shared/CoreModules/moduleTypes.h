#pragma once
#include "coreProcessor.h"
#include "string.h"
#include <array>
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
#ifndef STM32F7
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
#endif

	bool operator==(const ModuleTypeWrapper &rhs) const
	{
		for (size_t i = 0; i < kStringLen; i++) {
			if (this->name[i] != rhs.name[i])
				return false;
		}
		return true;
	}
};

using ModuleTypeSlug = ModuleTypeWrapper;

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, const char *name, CreateModuleFunc funcCreate)
	{
		int id = getTypeID(typeslug);
		if (id == -1) {
			id = next_id;
			next_id++;
			creation_funcs[id] = funcCreate;
			strcpy(module_slugs[id], typeslug.name);
#ifndef STM32F7
			module_names[id] = name;
#endif
			return true;
		}
		return false;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return creation_funcs[id]();

		return nullptr;
	}

#ifndef STM32F7
	static std::string getModuleTypeName(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return module_names[id];

		return "Not found.";
	}
#endif

	static std::string getModuleSlug(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return module_slugs[id];

		return "????";
	}

	static int getTypeID(ModuleTypeSlug typeslug)
	{
		for (int i = 0; i < MAX_MODULE_TYPES; i++) {
			auto &slug = module_slugs[i];
			if (strcmp(slug, typeslug.name) == 0)
				return i;
		}
		return -1;
	}

private:
	static inline const int MAX_MODULE_TYPES = 64;
	static inline std::array<CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline std::array<char[20], MAX_MODULE_TYPES> module_slugs;
#ifndef STM32F7
	static inline std::array<std::string, MAX_MODULE_TYPES> module_names;
#endif
	static inline int next_id = 0;
};
