#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/module_info_base.hh"
#include "module_type_slug.hh"
#include "util/seq_map.hh"
#include "util/static_string.hh"
#include <array>
#include <memory>

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using ElementInfoView = MetaModule::ElementInfoView;

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ModuleInfoView info) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		infos.insert(typeslug, info);
		creation_funcs.insert(typeslug, funcCreate);
		return already_exists;
	}

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ElementInfoView info) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		infos2.insert(typeslug, info);
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
			return m->module_name;
		else if (auto d = infos2.get(typeslug))
			return d->description;
		return "Not found.";
	}

	static ModuleInfoView &getModuleInfo(ModuleTypeSlug typeslug) {
		if (auto m = infos.get(typeslug))
			return *m;
		else
			return nullinfo;
	}

	static ElementInfoView &getModuleInfo2(ModuleTypeSlug typeslug) {
		if (auto d = infos2.get(typeslug))
			return *d;
		else
			return nullinfo2;
	}

	// Returns true if slug is valid and registered.
	static bool isValidSlug(ModuleTypeSlug typeslug) {
		if (infos.key_exists(typeslug))
			return true;
		if (infos2.key_exists(typeslug))
			return true;
		return false;
	}

	static inline ModuleInfoView nullinfo{};
	static inline ElementInfoView nullinfo2{};

private:
	static constexpr int MAX_MODULE_TYPES = 512;

	static inline SeqMap<ModuleTypeSlug, CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline SeqMap<ModuleTypeSlug, ModuleInfoView, MAX_MODULE_TYPES> infos;
	static inline SeqMap<ModuleTypeSlug, ElementInfoView, 64> infos2;

	// static constexpr auto _sz_creation_funcs = sizeof(creation_funcs); //48k
	// static constexpr auto _sz_infos = sizeof(infos);				   //112k
	// static constexpr auto _sz_view = sizeof(ModuleInfoView); //136B
};
