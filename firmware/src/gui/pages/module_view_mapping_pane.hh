#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "params/params_state.hh"
#include <gui/pages/module_view_mapping_pane_list.hh>

namespace MetaModule
{

struct ModuleViewMappingPane {
	ModuleViewMappingPane(PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue)
		: patch_storage{patch_storage}
		, patch_mod_queue{patch_mod_queue}
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

		auto &patch = patch_storage.get_view_patch();
		if (patch.patch_name.length() == 0) {
			pr_warn("Patch name empty\n");
			return;
		}

		auto this_module_id = PageList::get_selected_module_id();
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

	void update(ParamsMidiState &params) {
		add_map_popup.update(params);
	}

private:
	// used to work with lvgl object void* user_data
	static inline uint32_t knobset_indices[MaxKnobSets]{0, 1, 2, 3, 4, 5, 6, 7};

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
		if (set_i.has_value())
			lv_obj_set_user_data(obj, &(knobset_indices[set_i.value()]));
		else
			lv_obj_set_user_data(obj, nullptr);
	}

	void group_edit_button(lv_obj_t *obj, std::optional<uint32_t> set_i = std::nullopt) {
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, edit_button_cb, LV_EVENT_PRESSED, this);
		if (set_i.has_value())
			lv_obj_set_user_data(obj, &(knobset_indices[set_i.value()]));
		else
			lv_obj_set_user_data(obj, nullptr);
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
		for (auto &cable : patch_storage.get_view_patch().int_cables) {
			if (cable.out == thisjack) {
				for (auto &injack : cable.ins) {
					auto obj = list.create_cable_item(injack, ElementType::Input, patch_storage.get_view_patch());
					group_edit_button(obj);
				}
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		if (panel_jack_id) {
			std::string_view name = PanelDef::get_map_outjack_name(panel_jack_id.value());
			auto obj = list.create_panelcable_item(name, panel_jack_id.value());
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
			std::string_view name = PanelDef::get_map_injack_name(panel_jack_id.value());
			auto obj = list.create_panelcable_item(name, panel_jack_id.value());
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
		auto this_module_id = PageList::get_selected_module_id();

		for (uint32_t set_i = 0; auto &set : patch.knob_sets) {
			bool has_mapping = false;
			for (auto &map : set.set) {
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto name = PanelDef::get_map_param_name(map.panel_knob_id);
					auto setname = patch.validate_knob_set_name(set_i);
					auto obj = list.create_map_list_item(name, setname, map.panel_knob_id % 6);
					group_edit_button(obj, set_i);
					has_mapping = true;
				}
			}
			if (!has_mapping) {
				auto setname = patch.validate_knob_set_name(set_i);
				auto obj = list.create_unmapped_list_item(setname);
				group_add_button(obj, set_i);
			}
			set_i++;
		}
	}

	static void edit_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		//TODO
		(void)page;
		printf_("Edit\n");
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
		page->add_map_popup.show(knobset_id, page->drawn_element->gui_element.idx.param_idx);
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

	MappingPaneList list;
	AddMapPopUp add_map_popup;
};

} // namespace MetaModule
