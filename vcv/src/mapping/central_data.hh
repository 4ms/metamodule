#pragma once
#include "mapping/ModuleID.h"
#include <rack.hpp>

//TODO: Rename this WhiteList
class CentralData {
public:
	CentralData() = default;
	~CentralData() = default;

	// True if module is in the 4ms or MetaModule compatible plugin
	bool isInPlugin(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		if (!module->model->plugin)
			return false;
		return (module->model->plugin->slug == "4msCompany") || (module->model->plugin->slug == "Befaco") ||
			   (module->model->plugin->slug == "Audible Instruments");
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
