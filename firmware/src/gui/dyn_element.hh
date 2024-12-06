#pragma once
#include "app/ModuleWidget.hpp"
#include "gui/dyn_element/base_dyn_draw.hh"
#include "gui/dyn_element/rack_dyn_draw.hh"
#include "patch_play/patch_playloader.hh"
#include <memory>

namespace MetaModule
{

class DynamicElementDraw {
public:
	DynamicElementDraw(PatchPlayLoader &patch_playloader)
		: patch_playloader{patch_playloader} {
	}

	void prepare_module(unsigned this_module_id, lv_obj_t *canvas) {
		drawer.reset();

		if (auto rack_module = patch_playloader.get_plugin_module<rack::engine::Module>(this_module_id)) {
			if (rack_module->module_widget) {
				drawer = std::make_unique<RackDynDraw>(rack_module->module_widget);
				drawer->prepare(canvas);
			}
		}
	}

	void draw(lv_obj_t *canvas) {
		if (drawer) {
			drawer->draw(canvas);
		}
	}

private:
	PatchPlayLoader &patch_playloader;
	std::unique_ptr<BaseDynDraw> drawer{};
};

} // namespace MetaModule
