#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view_mapping_pane_list.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "params/params_state.hh"

namespace MetaModule
{

struct ModuleViewMappingPane {
	ModuleViewMappingPane(PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue, ParamsMidiState &params)
		: patch_storage{patch_storage}
		, patch_mod_queue{patch_mod_queue}
		, patch{patch_storage.get_view_patch()}
		, params{params}
		, add_map_popup{patch_storage, patch_mod_queue} {
	}

	void init() {
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, scroll_to_top, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ControlArc, arc_change_cb, LV_EVENT_VALUE_CHANGED, this);
		//RELEASE = click on arc when done turning it
		lv_obj_add_event_cb(ui_ControlArc, control_button_cb, LV_EVENT_RELEASED, this);
	}

	void prepare_focus(lv_group_t *group, uint32_t width, bool patch_playing) {
		base_group = group;

		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_hide(ui_ControlAlert);
	}

	void show(const DrawnElement &drawn_el) {
		add_map_popup.hide();

		pane_group = lv_group_create();
		lv_group_remove_all_objs(pane_group);
		lv_group_set_editing(pane_group, false);

		patch = patch_storage.get_view_patch();
		if (patch.patch_name.length() == 0) {
			pr_warn("Patch name empty\n");
			return;
		}

		this_module_id = PageList::get_selected_module_id();
		if (this_module_id >= patch.module_slugs.size()) {
			pr_warn("Module has invalid ID\n");
			return;
		}

		auto slug = patch.module_slugs[this_module_id];

		// Knob name label
		lv_label_set_text(ui_Module_Name, slug.c_str());
		auto nm = base_element(drawn_el.element).short_name;
		if (nm.size() == 0)
			nm = "(no name)";
		lv_label_set_text(ui_Element_Name, nm.data());

		drawn_element = &drawn_el;

		std::visit([this](auto &el) { prepare_for_element(el); }, drawn_el.element);

		lv_show(ui_MappingParameters);
		lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_OFF);

		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;

		lv_group_focus_next(pane_group);
		lv_indev_set_group(indev, pane_group);

		add_map_popup.prepare_focus(pane_group);
	}

	void refresh() {
		if (drawn_element) {
			remove_all_items();
			show(*drawn_element);
		}
	}

	void hide() {
		lv_hide(ui_MappingParameters);
		lv_hide(ui_ControlAlert);
		add_map_popup.hide();

		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;

		if (base_group)
			lv_indev_set_group(indev, base_group);

		if (pane_group) {
			lv_group_del(pane_group);
			pane_group = nullptr;
		}

		remove_all_items();
	}

	void update() {
		add_map_popup.update(params);
	}

	void hide_addmap() {
		add_map_popup.hide();
	}

	bool addmap_visible() {
		return add_map_popup.visible;
	}

private:
	// used to work with lvgl object void* user_data
	static inline uint32_t knobset_indices[MaxKnobSets + 1]{PatchData::MIDIKnobSet, 0, 1, 2, 3, 4, 5, 6, 7};

	void remove_all_items() {
		auto num_circles = lv_obj_get_child_cnt(ui_MapList);
		for (unsigned i = 0; i < num_circles; i++) {
			auto child = lv_obj_get_child(ui_MapList, i);
			lv_obj_del_async(child);
		}
	}

	void group_add_button(lv_obj_t *obj, std::optional<uint32_t> set_i = std::nullopt) {
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, add_button_cb, LV_EVENT_PRESSED, this);
		if (set_i.has_value()) {
			if (set_i.value() == PatchData::MIDIKnobSet)
				lv_obj_set_user_data(obj, &(knobset_indices[0]));
			else
				lv_obj_set_user_data(obj, &(knobset_indices[set_i.value() + 1]));
		} else
			lv_obj_set_user_data(obj, nullptr);
	}

	void group_edit_button(lv_obj_t *obj, std::optional<uint32_t> set_i = std::nullopt) {
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, edit_button_cb, LV_EVENT_PRESSED, this);
		if (set_i.has_value())
			if (set_i.value() == PatchData::MIDIKnobSet)
				lv_obj_set_user_data(obj, &(knobset_indices[0]));
			else
				lv_obj_set_user_data(obj, &(knobset_indices[set_i.value() + 1]));
		else
			lv_obj_set_user_data(obj, nullptr);
	}

	void group_edit_cable_button(lv_obj_t *obj, uint32_t cable_idx) {
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, edit_cable_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_set_user_data(obj, reinterpret_cast<void *>(cable_idx));
	}

	void prepare_for_element(const BaseElement &) {
		lv_hide(ui_ControlButton);
		lv_hide(ui_MappedPanel);
	}

	void prepare_for_jack() {
		lv_hide(ui_ControlButton);
		lv_show(ui_MappedPanel);
		lv_hide(ui_MappedItemHeader);
		lv_label_set_text(ui_MappedListTitle, "Cables:");
	}

	void prepare_for_element(const JackOutput &) {
		prepare_for_jack();

		auto thisjack = Jack{.module_id = (uint16_t)PageList::get_selected_module_id(),
							 .jack_id = drawn_element->gui_element.idx.output_idx};
		for (unsigned idx = 0; auto &cable : patch_storage.get_view_patch().int_cables) {
			if (cable.out == thisjack) {
				for (auto &injack : cable.ins) {
					auto obj = list.create_cable_item(injack, ElementType::Input, patch_storage.get_view_patch());
					group_edit_cable_button(obj, idx);
				}
			}
			idx++;
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		if (panel_jack_id) {
			auto obj = list.create_panel_outcable_item(panel_jack_id.value());
			group_edit_button(obj);
		} else {
			auto obj = list.create_unmapped_list_item("Add cable...");
			group_add_button(obj);
		}
	}

	void prepare_for_element(const JackInput &) {
		prepare_for_jack();

		auto thisjack = Jack{.module_id = (uint16_t)PageList::get_selected_module_id(),
							 .jack_id = drawn_element->gui_element.idx.input_idx};
		for (auto &cable : patch_storage.get_view_patch().int_cables) {
			for (auto &injack : cable.ins) {
				if (injack == thisjack) {
					auto obj = list.create_cable_item(cable.out, ElementType::Output, patch_storage.get_view_patch());
					group_edit_button(obj);
				}
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		if (panel_jack_id) {
			auto obj = list.create_panel_incable_item(panel_jack_id.value());
			group_edit_button(obj);
		} else {
			auto obj = list.create_unmapped_list_item("Add cable...");
			group_add_button(obj);
		}
	}

	void prepare_for_element(const ParamElement &) {
		lv_show(ui_MappedPanel);
		lv_show(ui_MappedItemHeader);
		lv_show(ui_ControlButton, is_patch_playing);
		lv_label_set_text(ui_MappedListTitle, "Mappings:");

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ControlButton);
			lv_group_focus_obj(ui_ControlButton);
		}

		auto &patch = patch_storage.get_view_patch();
		this_module_id = PageList::get_selected_module_id();

		// Show MIDI set first
		show_knobset(patch.midi_maps, PatchData::MIDIKnobSet);

		// Show all knobsets with a mapping
		std::optional<unsigned> first_empty_set = std::nullopt;
		for (uint32_t set_i = 0; set_i < patch.knob_sets.size(); set_i++) {
			auto &set = patch.knob_sets[set_i];

			auto set_is_empty = show_knobset(set, set_i);
			if (set_is_empty && !first_empty_set.has_value())
				first_empty_set = set_i;
		}

		// Show the first empty knobset (if there is one)
		if (first_empty_set.has_value()) {
			unsigned set_i = first_empty_set.value();
			auto setname = patch.valid_knob_set_name(set_i);
			auto obj = list.create_unmapped_list_item(setname);
			group_add_button(obj, set_i);
		}
	}

	bool show_knobset(MappedKnobSet const &set, unsigned set_i) {
		bool set_is_empty = true;
		bool has_mapping_in_set = false;
		auto setname = patch.valid_knob_set_name(set_i);

		for (auto &map : set.set) {
			if (map.module_id > 0 && map.module_id < patch.module_slugs.size()) {
				set_is_empty = false;
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto obj = list.create_map_list_item(map, setname);
					group_edit_button(obj, set_i);
					has_mapping_in_set = true;
				}
			}
		}

		if (!set_is_empty && !has_mapping_in_set) {
			auto obj = list.create_unmapped_list_item(setname);
			group_add_button(obj, set_i);
		}

		return set_is_empty;
	}

	static void edit_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		//TODO
		(void)page;
		pr_err("Edit Map not implemented yet\n");
	}

	static void edit_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!event->target)
			return;

		auto cable_idx = reinterpret_cast<uint32_t>(event->target->user_data);
		pr_err("Edit Cable %d -- not implemented yet\n", cable_idx);
	}

	static void add_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		uint32_t knobset_id = 0; //FIXME
		auto obj = event->target;
		if (auto knobset_ptr = lv_obj_get_user_data(obj)) {
			knobset_id = *static_cast<uint32_t *>(knobset_ptr);
		}

		// Clear all CC events
		if (knobset_id == PatchData::MIDIKnobSet) {
			for (auto &cc : page->params.midi_ccs)
				cc.changed = false;
		}
		page->add_map_popup.show(knobset_id, page->drawn_element->gui_element.idx.param_idx);
	}

	static void add_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!event->target)
			return;

		pr_err("Add Cable %d -- not implemented yet\n",
			   page->drawn_element->gui_element.idx.input_idx,
			   page->drawn_element->gui_element.idx.output_idx);
	}

	static void scroll_to_top(lv_event_t *event) {
		if (event->target == ui_ControlButton) {
			lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_ON);
		}
	}

	static void control_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (event->target == ui_ControlButton) {
			lv_show(ui_ControlAlert);
			lv_obj_clear_state(ui_ControlButton, LV_STATE_PRESSED);
			lv_group_add_obj(page->pane_group, ui_ControlArc);
			lv_group_focus_obj(ui_ControlArc);

			auto param_id = page->drawn_element->gui_element.idx.param_idx;
			auto module_id = PageList::get_selected_module_id();
			auto cur_val = page->patch_storage.get_view_patch().get_static_knob_value(module_id, param_id);
			if (cur_val)
				lv_arc_set_value(ui_ControlArc, cur_val.value() * 100);
		}

		if (event->target == ui_ControlArc) {
			//defocus
			lv_hide(ui_ControlAlert);
			lv_group_focus_next(page->pane_group);
		}
	}

	static void arc_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);
		auto &patch = page->patch_storage.get_view_patch();

		StaticParam sp{
			.module_id = (uint16_t)PageList::get_selected_module_id(),
			.param_id = page->drawn_element->gui_element.idx.param_idx,
			.value = lv_arc_get_value(ui_ControlArc) / 100.f,
		};
		page->patch_mod_queue.put(SetStaticParam{.param = sp});
		patch.set_static_knob_value(sp.module_id, sp.param_id, sp.value);
	}

	PatchStorageProxy &patch_storage;
	PatchModQueue &patch_mod_queue;
	lv_group_t *base_group = nullptr;
	lv_group_t *pane_group = nullptr;
	const DrawnElement *drawn_element;
	bool is_patch_playing = false;
	PatchData &patch;
	ParamsMidiState &params;
	unsigned this_module_id = 0;

	MappingPaneList list;
	AddMapPopUp add_map_popup;
};

} // namespace MetaModule
