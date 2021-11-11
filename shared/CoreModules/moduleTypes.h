#pragma once
#include "coreProcessor.h"
#include "util/static_string.hh"
#include <array>
#include <string.h>

using ModuleTypeSlug = StaticString<31>;

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, const char *name, CreateModuleFunc funcCreate) {
		bool already_exists = true;
		int id = getTypeID(typeslug);
		if (id == -1) {
			already_exists = false;
			id = next_id;
			next_id++;
			if (next_id >= MAX_MODULE_TYPES)
				next_id = 0; // FixMe: Report/handle this ERROR!
			module_slugs[id] = typeslug;
		}
		module_names[id] = name;
		creation_funcs[id] = funcCreate;
		return already_exists;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug) {
		int id = getTypeID(typeslug);
		if (id >= 0)
			return creation_funcs[id]();

		return nullptr;
	}

	static const char *getModuleTypeName(ModuleTypeSlug typeslug) {
		int id = getTypeID(typeslug);
		if (id >= 0)
			return module_names[id];
		return "Not found.";
	}

	// Returns the slug if it's valid and registered.
	// Otherwise returns "????"
	static const char *getModuleSlug(ModuleTypeSlug typeslug) {
		int id = getTypeID(typeslug);
		if (id >= 0)
			return module_slugs[id];

		return "????";
	}

	static int getTypeID(ModuleTypeSlug typeslug) {
		for (int i = 0; i < MAX_MODULE_TYPES; i++) {
			auto &slug = module_slugs[i];
			if (slug == typeslug)
				return i;
		}
		return -1;
	}

private:
	static inline const int MAX_MODULE_TYPES = 512;
	static inline std::array<CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline std::array<ModuleTypeSlug, MAX_MODULE_TYPES> module_slugs;
	static inline std::array<StaticString<CoreProcessor::LongNameChars>, MAX_MODULE_TYPES> module_names;
	static inline int next_id = 0;
};
