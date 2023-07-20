#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_info_view.hh"
#include "module_type_slug.hh"
#include "util/seq_map.hh"
#include "util/static_string.hh"
#include <array>
#include <memory>

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using ModuleInfoView = MetaModule::ModuleInfoView;

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ModuleInfoView info) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		infos.insert(typeslug, info);
		creation_funcs.insert(typeslug, funcCreate);
		return already_exists;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug) {
		if (auto f_create = creation_funcs.get(typeslug))
			return (*f_create)();
		else
			return nullptr;
	}

	static std::string_view getModuleTypeName(ModuleTypeSlug typeslug) {
		if (auto m = infos.get(typeslug))
			return m->description;
		return "Not found.";
	}

	static ModuleInfoView &getModuleInfo(ModuleTypeSlug typeslug) {
		if (auto m = infos.get(typeslug))
			return *m;
		else
			return nullinfo;
	}

	// Returns true if slug is valid and registered.
	static bool isValidSlug(ModuleTypeSlug typeslug) {
		return infos.key_exists(typeslug);
	}

	static inline ModuleInfoView nullinfo{};

private:
	static constexpr int MAX_MODULE_TYPES = 512;

	static inline SeqMap<ModuleTypeSlug, CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline SeqMap<ModuleTypeSlug, ModuleInfoView, MAX_MODULE_TYPES> infos;

	// static constexpr auto _sz_creation_funcs = sizeof(creation_funcs); //48k
	// static constexpr auto _sz_infos = sizeof(infos);				   //112k
	// static constexpr auto _sz_view = sizeof(ModuleInfoView); //136B
};
