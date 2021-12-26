#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"
#include "etl/map.h"
#include "util/static_string.hh"
#include <array>
//#include <string_view>

//using ModuleTypeSlug = std::string_view;
using ModuleTypeSlug = StaticString<31>;

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ModuleInfoView info) {
		auto m = creation_funcs.find(typeslug);
		bool already_exists = !(m == creation_funcs.end());

		infos[typeslug] = info;
		creation_funcs[typeslug] = funcCreate;
		return already_exists;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug) {
		auto m = creation_funcs.find(typeslug);
		if (m != creation_funcs.end())
			return m->second();
		else
			return nullptr;
	}

	static std::string_view getModuleTypeName(ModuleTypeSlug typeslug) {
		auto m = infos.find(typeslug);
		if (m != infos.end())
			return m->second.module_name;
		else
			return "Not found.";
	}

	static ModuleInfoView &getModuleInfo(ModuleTypeSlug typeslug) {
		auto m = infos.find(typeslug);
		if (m != infos.end())
			return m->second;
		else
			return nullmodule;
	}

	// Returns true if slug is valid and registered.
	static bool isValidSlug(ModuleTypeSlug typeslug) {
		auto m = infos.find(typeslug);
		return (m != infos.end());
	}

private:
	static constexpr int MAX_MODULE_TYPES = 512;
	static inline etl::map<std::string_view, CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline etl::map<std::string_view, ModuleInfoView, MAX_MODULE_TYPES> infos;

	static inline ModuleInfoView nullmodule{};
};
