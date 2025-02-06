#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "lvgl.h"
#include "patch_play/auto_map.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

struct ModuleViewAutoMapDialog {
	ModuleViewAutoMapDialog(PatchModQueue &patch_mod_queue, OpenPatchManager &patches, NotificationQueue &notify_queue)
		: patches{patches}
		, notify_queue{notify_queue}
		, auto_map{patch_mod_queue}
		, group(lv_group_create()) {
	}

	void prepare_focus(unsigned module_id, lv_group_t *base_group) {
		module_idx = module_id;
		parent_group = base_group;
		patch = patches.get_view_patch();
	}

	void show() {
		////////////////////////////////////////
		// TODO: this will display a dialog box for the user to check which knobs/jacks to map.
		// Not yet implemented!

		if (module_idx >= patch->module_slugs.size()) {
			pr_err("Invalid module index\n");
			return;
		}

		visible = true;

		auto slug = patch->module_slugs[module_idx];
		auto info = ModuleFactory::getModuleInfo(slug);

		lv_show(ui_AutoMapSelectPanel);
		lv_group_remove_all_objs(group);

		lv_group_add_obj(group, ui_AutoMapCancelButton);
		lv_group_add_obj(group, ui_AutoMapSaveButton);

		// Knobss
		lv_group_add_obj(group, ui_AutoMapAllKnobsButton);
		for (auto i = 0u; auto el : info.elements) {
			auto &idx = info.indices[i];
			if (idx.param_idx != ElementCount::Indices::NoElementMarker) {
				auto obj = create_automap_item(ui_AutoMapKnobCont, base_element(el).short_name);
				lv_group_add_obj(group, obj);
			}
		}

		//Jacks
		lv_group_add_obj(group, ui_AutoMapAllJacksButton);
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

	void map_all() {
		// map into all knobsets
		maps_todo.clear();
		make_knob_maps(std::nullopt);
		make_jack_maps();
	}

	void map_knobs_single_knobset() {
		maps_todo.clear();
		if (auto first_free_knobset = first_empty_knobset()) {
			make_knob_maps(first_free_knobset); // map into all knobsets
		} else {
			notify_queue.put({"Cannot map, all knob sets are full", Notification::Priority::Error, 2000});
		}
	}

private:
	void make_jack_maps() {
		if (!patch || module_idx >= patch->module_slugs.size())
			return;

		auto slug = patch->module_slugs[module_idx];
		auto info = ModuleFactory::getModuleInfo(slug);
		for (auto idx : info.indices) {
			if (idx.input_idx != ElementCount::Indices::NoElementMarker ||
				idx.output_idx != ElementCount::Indices::NoElementMarker)
				maps_todo.push_back(idx);
		}

		make_maps();
	}

	void make_knob_maps(std::optional<unsigned> knobset) {
		if (!patch || module_idx >= patch->module_slugs.size())
			return;

		auto slug = patch->module_slugs[module_idx];
		auto info = ModuleFactory::getModuleInfo(slug);
		for (auto i = 0u; auto idx : info.indices) {
			bool is_mappable_param = std::visit(overloaded{
													[](BaseElement const &el) { return false; },
													[](ParamElement const &el) { return true; },
													[](AltParamElement const &el) { return false; },
												},
												info.elements[i]);

			if (is_mappable_param && idx.param_idx != ElementCount::Indices::NoElementMarker) {
				maps_todo.push_back(idx);
			}
			i++;
		}

		make_maps(knobset);
		if (knobset.has_value())
			name_knobset_by_modulename(knobset.value());
	}

	void make_maps(std::optional<uint16_t> knobset_id = std::nullopt) {
		if (!patch)
			return;

		for (auto indices : maps_todo) {
			auto_map.map(module_idx, indices, *patch, knobset_id);
		}
		maps_todo.clear();
	}

	std::optional<unsigned> first_empty_knobset() {
		if (patch->knob_sets.size() >= MaxKnobSets) {
			return std::nullopt;

		} else if (patch->knob_sets.size() == 1) {
			// Use first knobset if it's empty
			if (patch->knob_sets[0].set.size() == 0)
				return 0;
		}

		return patch->knob_sets.size();
	}

	void name_knobset_by_modulename(uint16_t knobset_id) {
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
	NotificationQueue &notify_queue;
	AutoMapper auto_map;

	lv_group_t *parent_group = nullptr;
	lv_group_t *group;
	bool visible = false;

	std::vector<ElementCount::Indices> maps_todo;

	unsigned module_idx = 0;

	PatchData *patch = nullptr;
};

} // namespace MetaModule
