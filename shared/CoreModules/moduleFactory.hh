#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"
#include "etl/string.h"
#include "etl/unordered_map.h"
#include "module_type_slug.hh"
#include "util/static_string.hh"
#include <array>
#include <optional>

//TODO: Get rid of dependency on etl by using our own map or unordered_map

template<typename KeyT, typename ValT, size_t Size>
struct FlatMap {
	std::array<KeyT, Size> keys;
	std::array<ValT, Size> vals;
	size_t idx = 0;

	bool insert(KeyT key, ValT val) {
		if (idx >= Size)
			return false;
		keys[idx] = key;
		vals[idx] = val;
		idx++;
		return true;
	}

	ValT *get(KeyT key) {
		for (size_t i = 0; auto &k : keys) {
			if (k == key)
				return &vals[i];
		}
		return nullptr;
	}

	bool key_exists(KeyT key) {
		for (auto &k : keys) {
			if (k == key)
				return true;
		}
		return false;
	}
};

class ModuleFactory {
	using CreateModuleFunc = std::unique_ptr<CoreProcessor> (*)();
	using ElementInfoView = MetaModule::ElementInfoView;

public:
	ModuleFactory() = delete;

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ModuleInfoView info) {
		auto m = creation_funcs.find(typeslug.c_str());
		bool already_exists = !(m == creation_funcs.end());

		infos[typeslug.c_str()] = info;
		creation_funcs[typeslug.c_str()] = funcCreate;
		return already_exists;
	}

	static bool registerModuleType(ModuleTypeSlug typeslug, CreateModuleFunc funcCreate, ElementInfoView info) {
		auto m = creation_funcs.find(typeslug.c_str());
		bool already_exists = !(m == creation_funcs.end());

		// infos2[typeslug.c_str()] = info;
		infos2.insert(typeslug, info);

		creation_funcs[typeslug.c_str()] = funcCreate;
		return already_exists;
	}

	static std::unique_ptr<CoreProcessor> create(const ModuleTypeSlug typeslug) {
		auto m = creation_funcs.find(typeslug.c_str());
		if (m != creation_funcs.end())
			return m->second();
		else
			return nullptr;
	}

	static std::string_view getModuleTypeName(ModuleTypeSlug typeslug) {
		auto m = infos.find(typeslug.c_str());
		if (m != infos.end())
			return m->second.module_name;
		else {
			if (auto d = infos2.get(typeslug))
				return d->description;

			return "Not found.";
		}
	}

	static ModuleInfoView &getModuleInfo(ModuleTypeSlug typeslug) {
		auto m = infos.find(typeslug.c_str());
		if (m != infos.end())
			return m->second;
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
		auto m = infos.find(typeslug.c_str());
		auto m2 = infos2.key_exists(typeslug);
		return (m != infos.end()) || m2;
	}

	static inline ModuleInfoView nullinfo{};
	static inline ElementInfoView nullinfo2{};

private:
	static constexpr int MAX_MODULE_TYPES = 512;

	//Note: we can't use a string_view for the map key because the map is populated on initialization
	//and the char[] that the string_view points to might not be initialized yet -- resulting in an element with el.first.length() == 0
	//Ideally, we'd use StaticString<31>, but there is some functionality missing in StaticString which map requires
	// We could try using string_view and lazy init. Within the module Core.cpp: std::string_view get_slug() { static char _slug[] = "EnOsc"; return _slug; }

	static inline etl::unordered_map<etl::string<31>, CreateModuleFunc, MAX_MODULE_TYPES> creation_funcs;
	static inline etl::unordered_map<etl::string<31>, ModuleInfoView, MAX_MODULE_TYPES> infos;
	// static inline etl::unordered_map<etl::string<31>, ElementInfoView, 64> infos2;
	static inline FlatMap<ModuleTypeSlug, ElementInfoView, 64> infos2;

	// static constexpr auto _sz_creation_funcs = sizeof(creation_funcs); //48k
	// static constexpr auto _sz_infos = sizeof(infos);				   //112k
	// static constexpr auto _sz_view = sizeof(ModuleInfoView); //136B
};
