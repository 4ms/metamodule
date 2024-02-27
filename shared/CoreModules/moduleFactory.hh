#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/module_type_slug.hh"
#include <util/seq_map.hh>
#include <util/static_string.hh>
#include <memory>
#include <vector>

// Why does this not work?
// extern "C" {
//typedef struct lv_img_dsc_t lv_img_dsc_t;
// // struct lv_img_dsc_t;
// }

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using ModuleInfoView = MetaModule::ModuleInfoView;
	using FaceplatePtr = void *;

public:
	ModuleFactory() = delete;

	static bool
	registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate, const ModuleInfoView &info) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		infos.insert(typeslug, info);
		creation_funcs.insert(typeslug, funcCreate);
		return already_exists;
	}

	static bool registerModuleType(const ModuleTypeSlug &typeslug, const ModuleInfoView &info) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		infos.insert(typeslug, info);
		return already_exists;
	}

	static bool registerModuleType(const ModuleTypeSlug &typeslug, CreateModuleFunc funcCreate) {
		bool already_exists = creation_funcs.key_exists(typeslug);
		creation_funcs.insert(typeslug, funcCreate);
		return already_exists;
	}

	static bool registerModuleFaceplate(const ModuleTypeSlug &typeslug, FaceplatePtr faceplate) {
		if (faceplates.key_exists(typeslug)) {
			return false;
		} else {
			return faceplates.insert(typeslug, faceplate);
		}
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug &typeslug) {
		if (auto f_create = creation_funcs.get(typeslug))
			return (*f_create)();
		else
			return nullptr;
	}

	static std::string_view getModuleTypeName(const ModuleTypeSlug &typeslug) {
		if (auto m = infos.get(typeslug))
			return m->description;
		return "Not found.";
	}

	static ModuleInfoView &getModuleInfo(const ModuleTypeSlug &typeslug) {
		if (auto m = infos.get(typeslug))
			return *m;
		else
			return nullinfo;
	}

	static FaceplatePtr getModuleFaceplate(const ModuleTypeSlug &typeslug) {
		if (auto m = faceplates.get(typeslug))
			return *m;
		else
			return nullptr;
	}

	// Returns true if slug is valid and registered.
	static bool isValidSlug(const ModuleTypeSlug &typeslug) {
		return infos.key_exists(typeslug) && creation_funcs.key_exists(typeslug);
	}

	static std::vector<ModuleTypeSlug> getAllSlugs() {
		std::vector<ModuleTypeSlug> slugs;
		slugs.assign(infos.keys.begin(), std::next(infos.keys.begin(), infos.size()));
		return slugs;
	}

	static inline ModuleInfoView nullinfo{};

private:
	static constexpr int MAX_MODULE_TYPES = 512;

	static inline SeqMap<ModuleTypeSlug, CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline SeqMap<ModuleTypeSlug, ModuleInfoView, MAX_MODULE_TYPES> infos;
	static inline SeqMap<ModuleTypeSlug, FaceplatePtr, MAX_MODULE_TYPES> faceplates;

	// static constexpr auto _sz_creation_funcs = sizeof(creation_funcs); //48k
	// static constexpr auto _sz_infos = sizeof(infos);				   //112k
	// static constexpr auto _sz_view = sizeof(ModuleInfoView); //136B
};
