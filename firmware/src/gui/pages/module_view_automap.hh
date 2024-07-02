#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/pages/save_dialog.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/auto_map.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct ModuleViewAutoMapDialog {
	ModuleViewAutoMapDialog(PatchModQueue &patch_mod_queue, OpenPatchManager &patches)
		: patches{patches}
		, auto_map{patch_mod_queue}
		, group(lv_group_create()) {
	}

	void prepare_focus(unsigned module_id) {
		module_idx = module_id;
	}

	void show() {
		auto patch = patches.get_view_patch();
		if (module_idx < patch->module_slugs.size()) {
			auto slug = patch->module_slugs[module_idx];
			auto info = ModuleFactory::getModuleInfo(slug);
			//TODO: populate selection panel
			//give focus to it
			// set callbacks on buttons
			// Map button push_back all selected items
			for (auto indices : info.indices) {
				maps_todo.push_back(indices);
			}
		}
	}

	void update() {
	}

	void hide() {
	}

private:
	void make_maps() {
		auto patch = patches.get_view_patch();

		for (auto indices : maps_todo) {
			if (auto res = auto_map.map(module_idx, indices, *patch); res.has_value()) {
				pr_dbg("Auto mapping module %d, param %d ", module_idx, indices.param_idx);
				pr_dbg("to panel knob %d in set %d\n", res->panel_el_id, res->set_id);
			} else {
				pr_err("Failed to map\n");
			}
		}
	}

	OpenPatchManager &patches;
	AutoMapper auto_map;

	lv_group_t *group;

	std::vector<ElementCount::Indices> maps_todo;

	unsigned module_idx = 0;
};

} // namespace MetaModule
