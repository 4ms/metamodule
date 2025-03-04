#pragma once
#include "app/ModuleWidget.hpp"
#include "gui/dyn_element/base_dyn_draw.hh"
#include "gui/dyn_element/native_dyn_draw.hh"
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

	void prepare_module(std::string_view slug, unsigned module_id, lv_obj_t *module_canvas, unsigned px_per_3U) {
		pr_trace("DynamicElementDraw: Prepare canvas for %s, id %u, pxp3u %u\n", slug.data(), module_id, px_per_3U);

		drawer.reset();

		if (auto rack_module = patch_playloader.get_plugin_module<rack::engine::Module>(module_id)) {
			if (rack_module->module_widget.get()) {
				drawer = std::make_unique<RackDynDraw>(rack_module->module_widget);
			}
		}

		else if ([[maybe_unused]] auto native_module = patch_playloader.get_plugin_module<CoreProcessor>(module_id))
		{
			drawer = std::make_unique<DynDraw>(native_module, slug);
		}

		if (drawer) {
			drawer->prepare(module_canvas, px_per_3U);
		}
	}

	void draw() {
		if (drawer) {
			drawer->draw();
		}
	}

	void blur() {
		if (drawer) {
			drawer->blur();
		}
	}

	bool is_active() {
		return drawer ? true : false;
	}

private:
	PatchPlayLoader &patch_playloader;
	std::unique_ptr<BaseDynDraw> drawer{};
};

} // namespace MetaModule
