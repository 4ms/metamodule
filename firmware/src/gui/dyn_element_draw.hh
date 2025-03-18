#pragma once
#include "gui/dyn_element/base_dyn_draw.hh"
#include "gui/dyn_element/native_dyn_draw.hh"
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

		if (auto module = patch_playloader.get_plugin_module<CoreProcessor>(module_id)) {
			drawer = std::make_unique<DynDraw>(module, slug);
			drawer->prepare(module_canvas, px_per_3U);
		} else {
			pr_dbg("Module idx %d is no a CoreProcessor?\n", module_id);
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
	std::unique_ptr<DynDraw> drawer{};
};

} // namespace MetaModule
