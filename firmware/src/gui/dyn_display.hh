#pragma once
#include "gui/dyn_display_drawer.hh"
#include "patch_play/patch_playloader.hh"
#include <memory>

namespace MetaModule
{

class DynamicDisplay {
public:
	DynamicDisplay(PatchPlayLoader &patch_playloader)
		: patch_playloader{patch_playloader} {
	}

	bool prepare_module(std::string_view slug, unsigned module_id, lv_obj_t *module_canvas, unsigned px_per_3U) {
		pr_trace("DynamicElementDraw: Prepare canvas for %s, id %u, pxp3u %u\n", slug.data(), module_id, px_per_3U);

		if (auto module = patch_playloader.get_plugin_module<CoreProcessor>(module_id)) {
			drawer = std::make_unique<DynamicDisplayDrawer>(module, slug);
			drawer->prepare(module_canvas, px_per_3U);
			return true;
		}

		return false;
	}

	void draw() {
		if (drawer) {
			drawer->draw();
		}
	}

	void blur() {
		if (drawer) {
			pr_dbg("DynamicElementDraw::blur()\n");
			drawer.reset();
		}
	}

private:
	PatchPlayLoader &patch_playloader;
	std::unique_ptr<DynamicDisplayDrawer> drawer{};
};

} // namespace MetaModule
