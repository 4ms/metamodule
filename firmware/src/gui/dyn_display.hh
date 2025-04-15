#pragma once
#include "gui/dyn_display_drawer.hh"
#include "patch_play/patch_playloader.hh"
#include <memory>

namespace MetaModule
{

// TODO: merge this with DynamicDisplayDrawer
class DynamicDisplay {
public:
	DynamicDisplay(PatchPlayLoader &patch_playloader)
		: patch_playloader{patch_playloader} {
	}

	bool prepare_module(std::span<const DrawnElement> drawn_elements, unsigned module_id, lv_obj_t *module_canvas) {

		pr_dbg("DynamicDisplay: Prepare canvas for module_id %u\n", module_id);

		if (patch_playloader.get_plugin_module(module_id)) {
			drawer = std::make_unique<DynamicDisplayDrawer>(patch_playloader, drawn_elements, module_id);
			drawer->prepare(module_canvas);
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
			drawer.reset();
		}
	}

private:
	PatchPlayLoader &patch_playloader;
	std::unique_ptr<DynamicDisplayDrawer> drawer{};
};

} // namespace MetaModule
