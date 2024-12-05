#pragma once
#include "app/ModuleWidget.hpp"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

class DynamicElementDraw {
public:
	DynamicElementDraw(PatchPlayLoader &patch_playloader)
		: patch_playloader{patch_playloader} {
	}

	bool prepare_module(unsigned this_module_id) {
		if (auto rack_module = patch_playloader.get_plugin_module<rack::engine::Module>(this_module_id)) {
			if (rack_module->module_widget) {
				return true;
			}
		}
		return false;
	}

private:
	PatchPlayLoader &patch_playloader;
};

} // namespace MetaModule
