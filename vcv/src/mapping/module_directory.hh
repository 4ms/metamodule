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

		if (module->model->plugin->slug == "Befaco") {
			if (module->model->slug == "NoisePlethora")
				return false;
			if (module->model->slug == "Muxlicer")
				return false;
			return true;
		}

		if (module->model->plugin->slug == "AudibleInstruments")
			return true;

		if (module->model->plugin->slug == "HetrickCV")
			return true;

		return false;
	}

	static bool isHub(std::string_view slug) {
		if (slug == "PanelMedium")
			return true;
		if (slug == "HubMedium")
			return true;

		return false;
	}

	static bool isHub(rack::Module *module) {
		if (!module)
			return false;
		if (!module->model)
			return false;

		return isHub(module->model->slug);
	}

	static bool isModuleInPlugin(rack::Module *module) {
		return isInPlugin(module) && !isHub(module);
	}
};
