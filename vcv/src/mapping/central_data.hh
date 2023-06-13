#pragma once
#include "mapping/ModuleID.h"
#include <rack.hpp>

struct ModuleDirectory {

	// True if module is in the 4ms or MetaModule compatible plugin
	static bool isInPlugin(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;
		if (!module->model->plugin)
			return false;

		if (module->model->plugin->slug == "4msCompany")
			return true;
		if (module->model->plugin->slug == "Befaco")
			return true;
		if (module->model->plugin->slug == "Audible Instruments")
			return true;

		return false;
	}

	static bool isHub(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;

		return module->model->slug == "PanelMedium";
	}

	static bool isModuleInPlugin(rack::Module *module) {
		return isInPlugin(module) && !isHub(module);
	}
};
