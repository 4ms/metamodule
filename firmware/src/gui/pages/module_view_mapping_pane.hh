#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "src/core/lv_obj.h"

namespace MetaModule
{

struct ModuleViewMappingPane {
	// MessageQueue &msg_queue;
	ModuleViewMappingPane(PatchStorageProxy &patch_storage)
		: patch_storage{patch_storage} {
	}

	void init() {
		// lv_obj_set_parent(ui_MappingParameters, lv_layer_top());
		lv_obj_add_event_cb(ui_AddMap, add_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_PRESSED, this);

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

		std::visit([&, this](auto &el) { prepare_for_element(el, drawn_el); }, drawn_el.element);

		display_num_mappings();

		show();
	}

	void remove_all_map_circles() {
		auto num_circles = lv_obj_get_child_cnt(ui_MapList);
		pr_dbg("Remove %d circles\n", num_circles);
		for (unsigned i = 0; i < num_circles; i++) {
			auto child = lv_obj_get_child(ui_MapList, i);
			lv_obj_del_async(child);
		}
	}

	void display_num_mappings() {
		char text[32];
		if (num_mappings)
			snprintf_(text, 31, "Found %d Mappings", num_mappings);
		else
			snprintf_(text, 31, "Not Mapped");

		lv_label_set_text(ui_MappedInfo, text);
	}

	void prepare_for_element(const BaseElement &, const DrawnElement &drawn_el) {
		lv_obj_add_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);
		if (drawn_el.gui_element.mapped_panel_id.has_value())
			num_mappings = 1;
		else
			num_mappings = 0;
	}

	void prepare_for_element(const ParamElement &, const DrawnElement &drawn_el) {
		lv_obj_clear_flag(ui_ControlButton, LV_OBJ_FLAG_HIDDEN);
		lv_group_add_obj(pane_group, ui_ControlButton);

		auto &patch = patch_storage.get_view_patch();
		auto this_module_id = PageList::get_selected_module_id();

		num_mappings = 0;

		for (auto &set : patch.knob_sets) {
			for (auto &map : set.set) {
				if (map.param_id == drawn_el.gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto obj = ui_MapCircle_create(ui_MapList);

					auto label = ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_CIRCLE_KNOBLETTER);
					auto name = PanelDef::get_map_param_name(map.panel_knob_id);
					lv_label_set_text(label, name.data());

					auto setname = ui_comp_get_child(obj, UI_COMP_MAPCIRCLE_KNOBSETNAMETEXT);
					lv_label_set_text(setname, set.name.c_str());

					lv_group_add_obj(pane_group, obj);
					num_mappings++;
				}
			}
		}

		lv_group_add_obj(pane_group, ui_AddMap);
	}

	void blur() {
		// if (pane_group) {
		// 	lv_group_del(pane_group);
		// 	pane_group = nullptr;
		// }
	}

	void show() {
		if (!visible) {
			printf_("Showing...\n");
			lv_obj_add_flag(ui_ElementRoller, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev) {
				printf_("Invalid indev\n");
				return;
			}
			lv_indev_set_group(indev, pane_group);
			lv_group_focus_obj(ui_ControlButton);

			auto numingroup = lv_group_get_obj_count(pane_group);
			printf_("%d obj in pane_group\n", numingroup);

			visible = true;
		} else
			printf_("Already visible\n");
	}

	void hide() {
		if (visible) {
			lv_obj_clear_flag(ui_ElementRoller, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;

			if (base_group) {
				lv_indev_set_group(indev, base_group);
				auto numingroup = lv_group_get_obj_count(base_group);
				printf_("%d obj in base_group\n", numingroup);
			} else
				printf_("No base_group set\n");

			if (pane_group) {
				lv_group_del(pane_group);
				pane_group = nullptr;
			} else
				printf_("No pane_group!\n");

			remove_all_map_circles();

			visible = false;
		} else
			printf_("Already hidden\n");
	}

	static void edit_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		(void)page;
	}

	static void add_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		(void)page;
	}

	static void control_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		(void)page;
	}

	PatchStorageProxy &patch_storage;
	uint32_t num_mappings = 0;
	lv_group_t *base_group;
	lv_group_t *pane_group = nullptr;
	bool visible = false;
};

} // namespace MetaModule
