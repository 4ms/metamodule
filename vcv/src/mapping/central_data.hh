#pragma once
#include "mapping/ModuleID.h"
#include <rack.hpp>

class CentralData {
public:
	CentralData() = default;
	~CentralData() = default;

	// True if module is regular module or hub in 4msCompany plugin
	bool isInPlugin(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		if (!module->model->plugin)
			return false;
		return module->model->plugin->slug == "4msCompany";
	}

	bool isHub(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		return module->model->slug == "PanelMedium";
	}
	bool isModuleInPlugin(rack::Module *module) {
		return isInPlugin(module) && !isHub(module);
	}

	void registerModule(ModuleID mod, rack::Module *module) {
	}

	void unregisterModule(ModuleID mod) {
	}

	rack::Module *getRegisteredModulePtr(int64_t moduleID) {
		auto context = rack::contextGet();
		auto engine = context->engine;
		auto *module = engine->getModule(moduleID);
		if (isModuleInPlugin(module)) {
			return module;
		}
		return nullptr;
	}

	bool isRegisteredHub(int64_t moduleID) {
		auto context = rack::contextGet();
		auto engine = context->engine;
		auto *module = engine->getModule(moduleID);
		return isHub(module);
	}

	struct RegisteredModule {
		int64_t id;
		ModuleTypeSlug slug;
		rack::Module *module;
	};

private:
	static inline const std::array<ModuleTypeSlug, 2> ValidHubSlugs = {"PANEL_8", "PanelMedium"};
};

extern std::unique_ptr<CentralData> centralData;
void initializeCentralData();
