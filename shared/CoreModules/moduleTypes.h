#pragma once
#include "coreProcessor.h"
#include "util/static_string.hh"
#include <array>
#include <string.h>

#if defined(STM32H7) || defined(STM32F7)
	#define __MODULE_FACTORY_SAVE_SPACE
#endif

using ModuleTypeSlug = StaticString<20>;

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
			module_slugs[id] = typeslug;
		}
#ifndef __MODULE_FACTORY_SAVE_SPACE
		module_names[id] = name;
#endif
		creation_funcs[id] = funcCreate;
		return already_exists;
	}

	static bool registerModuleType(ModuleTypeSlug typeslug,
								   const char *name,
								   CreateModuleFuncWithParams funcCreate,
								   uint8_t numInputJacks,
								   uint8_t numOutputJacks,
								   uint8_t numParams)
	{
		bool already_exists = true;
		int new_id = getTypeID(typeslug);
		if (new_id == -1) {
			already_exists = false;
			new_id = next_id;
			next_id++;
			module_slugs[new_id] = typeslug;
		}
#ifndef __MODULE_FACTORY_SAVE_SPACE
		module_names[new_id] = name;
#endif
		output_jack_offsets[new_id] = numInputJacks;
		total_jacks[new_id] = numInputJacks + numOutputJacks;
		total_params[new_id] = numParams;
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

	static const char *getModuleTypeName(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
#ifndef __MODULE_FACTORY_SAVE_SPACE
			return module_names[id];
#else
			return module_slugs[id];
#endif

		return "Not found.";
	}

	static const char *getModuleSlug(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return module_slugs[id];

		return "????";
	}

	static uint8_t getOutJackOffset(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return output_jack_offsets[id];

		return 0;
	}

	static uint8_t getNumJacks(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return total_jacks[id];

		return 0;
	}

	static uint8_t getNumParams(ModuleTypeSlug typeslug)
	{
		int id = getTypeID(typeslug);
		if (id >= 0)
			return total_params[id];

		return 0;
	}

	static int getTypeID(ModuleTypeSlug typeslug)
	{
		for (int i = 0; i < MAX_MODULE_TYPES; i++) {
			auto &slug = module_slugs[i];
			if (slug == typeslug)
				return i;
		}
		return -1;
	}

private:
	static inline const int MAX_MODULE_TYPES = 256;
	static inline std::array<CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline std::array<CreateModuleFuncWithParams, MAX_MODULE_TYPES> creation_funcs_wp;
	static inline std::array<ModuleTypeSlug, MAX_MODULE_TYPES> module_slugs;
#ifndef __MODULE_FACTORY_SAVE_SPACE
	static inline std::array<StaticString<CoreProcessor::LongNameChars>, MAX_MODULE_TYPES> module_names;
#endif
	static inline std::array<uint8_t, MAX_MODULE_TYPES> output_jack_offsets;
	static inline std::array<uint8_t, MAX_MODULE_TYPES> total_jacks;
	static inline std::array<uint8_t, MAX_MODULE_TYPES> total_params;
	static inline int next_id = 0;
};
