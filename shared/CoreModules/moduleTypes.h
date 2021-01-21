#pragma once
#include "coreProcessor.h"
#include "string.h"
#include <array>
#include <memory>
#include <string>

struct ModuleTypeSlug {
	static const size_t kStringLen = 20;
	char name[kStringLen];

	ModuleTypeSlug()
	{
		name[0] = '\0';
	}

	ModuleTypeSlug(const char *s)
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
	ModuleTypeSlug(const std::string s)
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

	bool operator==(const ModuleTypeSlug &rhs) const
	{
		for (size_t i = 0; i < kStringLen; i++) {
			if (this->name[i] != rhs.name[i])
				return false;
		}
		return true;
	}
};

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using CreateModuleFuncWithParams = std::unique_ptr<CoreProcessor> (*)(float *, const uint8_t *);

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, const char *name, CreateModuleFunc funcCreate)
	{
		bool already_exists = true;
		int id = getTypeID(typeslug);
		if (id == -1) {
			already_exists = false;
			id = next_id;
			next_id++;
			strcpy(module_slugs[id], typeslug.name);
		}
#ifndef STM32F7
		module_names[id] = name;
#endif
		creation_funcs[id] = funcCreate;
		return already_exists;
	}

	static bool registerModuleType(ModuleTypeSlug typeslug,
								   const char *name,
								   int firstOutputJackNumber,
								   CreateModuleFuncWithParams funcCreate)
	{
		bool already_exists = true;
		int new_id = getTypeID(typeslug);
		if (new_id == -1) {
			already_exists = false;
			new_id = next_id;
			next_id++;
			strcpy(module_slugs[new_id], typeslug.name);
		}
#ifndef STM32F7
		module_names[new_id] = name;
#endif
		output_jack_offsets[new_id] = firstOutputJackNumber;
		creation_funcs_wp[new_id] = funcCreate;
		return already_exists;
	}

	static std::unique_ptr<CoreProcessor>
	createWithParams(const ModuleTypeSlug typeslug, float *nodes, const uint8_t *indices)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return creation_funcs_wp[id](nodes, indices);

		return nullptr;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug, float *nodes, const uint8_t *indices)
	{
		return createWithParams(typeslug, nodes, indices);
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

	static int getOutJackOffset(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return output_jack_offsets[id];

		return 0;
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
	static inline std::array<CreateModuleFuncWithParams, MAX_MODULE_TYPES> creation_funcs_wp;
	static inline std::array<char[20], MAX_MODULE_TYPES> module_slugs;
#ifndef STM32F7
	static inline std::array<std::string, MAX_MODULE_TYPES> module_names;
#endif
	static inline std::array<int, MAX_MODULE_TYPES> output_jack_offsets;
	static inline int next_id = 0;
};
