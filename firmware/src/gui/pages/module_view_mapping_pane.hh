#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
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
		lv_obj_add_event_cb(ui_AddMap, add_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlArc, arc_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ControlArc, control_button_cb, LV_EVENT_RELEASED, this);

		visible = false;
	}

	void show(lv_group_t *group, const DrawnElement &drawn_el) {
		base_group = group;
		pane_group = lv_group_create();
		lv_group_remove_all_objs(pane_group);
		lv_group_set_editing(pane_group, false);

		auto this_module_id = PageList::get_selected_module_id();
		auto &patch = patch_storage.get_view_patch();
		if (patch.patch_name.length() == 0) {
			pr_warn("Patch name empty\n");
			return;
		}
		if (this_module_id >= patch.module_slugs.size()) {
			pr_warn("Module has invalid ID\n");
			return;
		}

		auto slug = patch.module_slugs[this_module_id];
		if (!slug.length()) {
			pr_warn("Module has invalid slug\n");
			return;
		}

		auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			pr_warn("Knob Edit page got empty module slug.\n");
			return;
		}

		// Knob name label
		lv_label_set_text(ui_Module_Name, slug.c_str());
		auto nm = std::visit([&](auto &el) -> std::string_view { return el.short_name; }, drawn_el.element);
		lv_label_set_text(ui_Element_Name, nm.data());

		drawn_element = &drawn_el;

		std::visit([&, this](auto &el) { prepare_for_element(el, drawn_el); }, drawn_el.element);

		// display_num_mappings();

		show();
	}

	void prepare_focus(uint32_t width, bool patch_playing) {
		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_obj_add_flag(ui_ControlAlert, LV_OBJ_FLAG_HIDDEN);
	}

	void blur() {
	}

	void show() {
		if (!visible) {
			lv_obj_add_flag(ui_ElementRoller, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;

			lv_indev_set_group(indev, pane_group);

			visible = true;
		}
	}

	void hide() {
		if (visible) {
			lv_obj_clear_flag(ui_ElementRoller, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

			lv_obj_add_flag(ui_ControlAlert, LV_OBJ_FLAG_HIDDEN);

			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;

			if (base_group)
				lv_indev_set_group(indev, base_group);

			if (pane_group) {
				lv_group_del(pane_group);
				pane_group = nullptr;
			}

			remove_all_map_circles();

			visible = false;
		}
	}

private:
	void remove_all_map_circles() {
		auto num_circles = lv_obj_get_child_cnt(ui_MapList);
		for (unsigned i = 0; i < num_circles; i++) {
			auto child = lv_obj_get_child(ui_MapList, i);
			lv_obj_del_async(child);
		}
	}

	// void display_num_mappings() {
	// 	char text[32];
	// 	if (num_mappings)
	// 		snprintf_(text, 31, "Found %d Mappings", num_mappings);
	// 	else
	// 		snprintf_(text, 31, "Not Mapped");
	// 	lv_label_set_text(ui_MappedInfo, text);
	// }

	lv_obj_t *create_map_circle(std::string_view name, std::string_view knobset_name, unsigned color_id) {
		auto obj = ui_MapCircle_create(ui_MapList);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_KNOBSETNAMETEXT);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[color_id % 6], LV_STATE_DEFAULT);
		lv_label_set_text(label, name.data());
		lv_label_set_text(setname, knobset_name.data());
		return obj;
	}

	void prepare_for_element(const BaseElement &, const DrawnElement &drawn_el) {
		lv_obj_add_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);
		num_mappings = 0;
	}

	void prepare_for_element(const JackElement &, const DrawnElement &drawn_el) {
		lv_obj_add_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);
		num_mappings = 0;

		if (drawn_el.gui_element.mapped_panel_id.has_value()) {

			//TODO: find jack mapping in patch
			auto obj = create_map_circle("?", "???", 0);
			lv_group_add_obj(pane_group, obj);
			num_mappings = 1;
			lv_obj_add_flag(ui_AddMap, LV_OBJ_FLAG_HIDDEN);
		}

		if (num_mappings == 0) {
			lv_obj_clear_flag(ui_AddMap, LV_OBJ_FLAG_HIDDEN);
			lv_group_focus_obj(ui_ControlButton);
		}
	}

	void prepare_for_element(const ParamElement &, const DrawnElement &drawn_el) {
		if (is_patch_playing)
			lv_obj_clear_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);
		else
			lv_obj_add_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);

		lv_group_add_obj(pane_group, ui_ControlButton);
		lv_group_add_obj(pane_group, ui_AddMap);

		auto &patch = patch_storage.get_view_patch();
		auto this_module_id = PageList::get_selected_module_id();

		num_mappings = 0;

		for (auto &set : patch.knob_sets) {
			for (auto &map : set.set) {
				if (map.param_id == drawn_el.gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto name = PanelDef::get_map_param_name(map.panel_knob_id);
					auto obj = create_map_circle(name, set.name.c_str(), map.panel_knob_id % 6);
					lv_group_add_obj(pane_group, ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_CIRCLE));
					num_mappings++;
				}
			}
		}

		lv_group_focus_obj(ui_ControlButton);
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
			lv_obj_clear_flag(ui_ControlAlert, LV_OBJ_FLAG_HIDDEN);
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
			lv_obj_add_flag(ui_ControlAlert, LV_OBJ_FLAG_HIDDEN);
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
	uint32_t num_mappings = 0;
	lv_group_t *base_group;
	lv_group_t *pane_group = nullptr;
	const DrawnElement *drawn_element;
	bool visible = false;
	bool is_patch_playing = false;
};

} // namespace MetaModule
