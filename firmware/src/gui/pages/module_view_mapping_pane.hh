#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "src/core/lv_obj.h"

namespace MetaModule
{

struct ModuleViewMappingPane {
	ModuleViewMappingPane(PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue)
		: patch_storage{patch_storage}
		, patch_mod_queue{patch_mod_queue} {
	}

	void init() {
		// lv_obj_add_event_cb(ui_AddMap, add_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, scroll_top_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ControlArc, arc_change_cb, LV_EVENT_VALUE_CHANGED, this);
		//RELEASE = click on arc when done turning it
		lv_obj_add_event_cb(ui_ControlArc, control_button_cb, LV_EVENT_RELEASED, this);

		visible = false;
	}

	void prepare_focus(lv_group_t *group, uint32_t width, bool patch_playing) {
		base_group = group;

		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_hide(ui_ControlAlert);
	}

	void show(const DrawnElement &drawn_el) {
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

		if (!visible) {
			lv_hide(ui_ElementRoller);
			lv_show(ui_MappingParameters);
			lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_OFF);

			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;

			lv_group_focus_next(pane_group);
			lv_indev_set_group(indev, pane_group);

			visible = true;
		}
	}

	void hide() {
		if (visible) {
			lv_show(ui_ElementRoller);
			lv_hide(ui_MappingParameters);
			lv_hide(ui_ControlAlert);

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

			visible = false;
		}
	}

private:
	void remove_all_items() {
		auto num_circles = lv_obj_get_child_cnt(ui_MapList);
		for (unsigned i = 0; i < num_circles; i++) {
			auto child = lv_obj_get_child(ui_MapList, i);
			lv_obj_del_async(child);
		}
	}

	void create_map_list_item(std::string_view name, std::string_view knobset_name, unsigned color_id) {
		auto obj = ui_MappedKnobSetItem_create(ui_MapList);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[color_id], LV_STATE_DEFAULT);
		lv_label_set_text(label, name.data());
		lv_label_set_text(setname, knobset_name.data());
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
	}

	void create_unmapped_list_item(std::string_view knobset_name) {
		auto obj = ui_UnmappedSetItem_create(ui_MapList);
		auto setname = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_label_set_text(setname, knobset_name.data());
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
	}

	void create_panelcable_item(std::string_view panel_jack_name, unsigned color_id) {
		auto obj = ui_MappedKnobSetItem_create(ui_MapList);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP_REVERSE);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[color_id], LV_STATE_DEFAULT);
		lv_label_set_text(label, "");
		lv_label_set_text_fmt(setname, "Panel %.16s", panel_jack_name.data());
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
	}

	void create_cable_item(Jack jack, JackDir dir) {
		auto obj = ui_UnmappedSetItem_create(ui_MapList);
		auto label = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_style_pad_left(label, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
		auto &patch = patch_storage.get_view_patch();
		auto name = get_full_jack_name(jack, dir, patch);
		lv_label_set_text_fmt(
			label, "%s %.16s %.16s", dir == JackDir::In ? "->" : "<-", name.module_name.data(), name.jack_name.data());
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
	}

	void create_jack_map_item(std::string_view name, std::optional<uint16_t> jack_id) {
		if (jack_id) {
			create_panelcable_item(name.data(), jack_id.value());
		}
		create_unmapped_list_item("Add cable...");
	}

	void prepare_for_element(const BaseElement &) {
		lv_hide(ui_ControlButton);
		lv_hide(ui_MappedPanel);

		lv_group_focus_obj(ui_ControlButton);
	}

	void prepare_for_jack() {
		lv_hide(ui_ControlButton);
		lv_show(ui_MappedPanel);
		lv_hide(ui_MappedItemHeader);
		lv_label_set_text(ui_MappedListTitle, "Cables:");

		lv_group_focus_obj(ui_ControlButton);
	}

	void prepare_for_element(const JackOutput &) {
		prepare_for_jack();

		auto thisjack = Jack{.module_id = (uint16_t)PageList::get_selected_module_id(),
							 .jack_id = drawn_element->gui_element.idx.output_idx};
		for (auto &cable : patch_storage.get_view_patch().int_cables) {
			if (cable.out == thisjack) {
				for (auto &injack : cable.ins)
					create_cable_item(injack, JackDir::In);
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		std::string_view name = panel_jack_id ? PanelDef::get_map_outjack_name(panel_jack_id.value()) : "";
		create_jack_map_item(name, panel_jack_id);
	}

	void prepare_for_element(const JackInput &) {
		prepare_for_jack();

		auto thisjack = Jack{.module_id = (uint16_t)PageList::get_selected_module_id(),
							 .jack_id = drawn_element->gui_element.idx.input_idx};
		for (auto &cable : patch_storage.get_view_patch().int_cables) {
			for (auto &injack : cable.ins) {
				if (injack == thisjack)
					create_cable_item(cable.out, JackDir::Out);
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		std::string_view name = panel_jack_id ? PanelDef::get_map_injack_name(panel_jack_id.value()) : "";
		create_jack_map_item(name, panel_jack_id);
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

		for (unsigned set_i = 0; auto &set : patch.knob_sets) {
			bool has_mapping = false;
			for (auto &map : set.set) {
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto name = PanelDef::get_map_param_name(map.panel_knob_id);
					create_map_list_item(name, set.name.c_str(), map.panel_knob_id % 6);
					has_mapping = true;
				}
			}
			if (!has_mapping) {
				auto setname = patch.validate_knob_set_name(set_i);
				create_unmapped_list_item(setname);
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
	}

	static void add_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);
		//TODO
		(void)page;
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

	static void scroll_top_cb(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_ON);
	}

	PatchStorageProxy &patch_storage;
	PatchModQueue &patch_mod_queue;
	lv_group_t *base_group;
	lv_group_t *pane_group = nullptr;
	const DrawnElement *drawn_element;
	bool visible = false;
	bool is_patch_playing = false;
};

} // namespace MetaModule
