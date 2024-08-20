#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/pages/save_dialog.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
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

	void prepare_focus(unsigned module_id, lv_group_t *base_group) {
		module_idx = module_id;
		parent_group = base_group;
	}

	void show() {
		////////////////////////////////////////
		// TODO: this will display a dialog box for the user to check which knobs/jacks to map.
		// Not yet implemented!
		// For now we just make all maps without any GUI
		make_all_maps();
		return;
		////////////////////////////////////////
		////////////////////////////////////////

		auto patch = patches.get_view_patch();

		if (module_idx >= patch->module_slugs.size()) {
			pr_err("Invalid module index\n");
			return;
		}

		visible = true;

		auto slug = patch->module_slugs[module_idx];
		auto info = ModuleFactory::getModuleInfo(slug);

		lv_show(ui_AutoMapSelectPanel);
		lv_group_remove_all_objs(group);

		for (auto i = 0u; auto el : info.elements) {
			auto &idx = info.indices[i];
			if (idx.param_idx != ElementCount::Indices::NoElementMarker) {
				auto obj = create_automap_item(ui_AutoMapKnobCont, base_element(el).short_name);
				lv_group_add_obj(group, obj);

			} else if (idx.input_idx != ElementCount::Indices::NoElementMarker) {
				auto obj = create_automap_item(ui_AutoMapJackCont, base_element(el).short_name);
				lv_group_add_obj(group, obj);

			} else if (idx.output_idx != ElementCount::Indices::NoElementMarker) {
				auto obj = create_automap_item(ui_AutoMapJackCont, base_element(el).short_name);
				lv_group_add_obj(group, obj);
			}
		}

		lv_group_activate(group);

		// TODO: set callbacks on buttons
		// Map button push_back all selected items
		// maps_todo.push_back(indices);
	}

	void update() {
	}

	void hide() {
		lv_hide(ui_AutoMapSelectPanel);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

	void make_all_maps(bool single_knobset = false) {
		auto patch = patches.get_view_patch();
		if (!patch)
			return;

		if (module_idx >= patch->module_slugs.size())
			return;

		maps_todo.clear();

		auto slug = patch->module_slugs[module_idx];
		auto info = ModuleFactory::getModuleInfo(slug);
		for (auto idx : info.indices) {
			maps_todo.push_back(idx);
		}

		if (single_knobset) {
			if (patch->knob_sets.size() < MaxKnobSets) {
				auto new_knobset_id = patch->knob_sets.size();
				// Use first knobset if it's empty
				if (patch->knob_sets.size() == 1) {
					if (patch->knob_sets[0].set.size() == 0)
						new_knobset_id = 0;
				}
				make_maps(new_knobset_id);
				name_knobset_by_modulename(new_knobset_id);
			} else
				pr_warn("All knobsets full\n");
		} else {
			make_maps();
		}
	}

	void make_maps(std::optional<uint16_t> knobset_id = std::nullopt) {
		auto patch = patches.get_view_patch();

		for (auto indices : maps_todo) {
			auto_map.map(module_idx, indices, *patch, knobset_id);
		}
	}

private:
	void name_knobset_by_modulename(uint16_t knobset_id) {
		auto patch = patches.get_view_patch();
		if (knobset_id < patch->knob_sets.size()) {
			if (module_idx < patch->module_slugs.size()) {
				auto module_display_name = ModuleFactory::getModuleDisplayName(patch->module_slugs[module_idx]);
				patch->knob_sets[knobset_id].name = module_display_name;
			}
		}
	}

	void clear_element_checks() {
		lv_foreach_child(ui_AutoMapKnobCont, [](lv_obj_t *obj, unsigned id) {
			if (id > 0)
				lv_obj_del_async(obj);
			return true;
		});

		lv_foreach_child(ui_AutoMapJackCont, [](lv_obj_t *obj, unsigned id) {
			if (id > 0)
				lv_obj_del_async(obj);
			return true;
		});
	}

	OpenPatchManager &patches;
	AutoMapper auto_map;

	lv_group_t *parent_group = nullptr;
	lv_group_t *group;
	bool visible = false;

	std::vector<ElementCount::Indices> maps_todo;

	unsigned module_idx = 0;
};

} // namespace MetaModule
