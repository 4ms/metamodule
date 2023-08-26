#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"

namespace MetaModule
{

struct ModuleViewMappingPane {
	// MessageQueue &msg_queue;
	ModuleViewMappingPane(PatchStorageProxy &patch_storage)
		: patch_storage{patch_storage} {
	}

	void init() {
		lv_obj_add_event_cb(ui_EditMap, edit_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_AddMapButton, add_button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_PRESSED, this);

		visible = false;
	}

	void focus(lv_group_t *group, const DrawnElement &drawn_el) {
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

		std::visit(overloaded{[&](const BaseElement &) {},
							  [&](const ParamElement &) {
								  focus_mapped_knob(drawn_el);
							  }},
				   drawn_el.element);
	}

	void focus_mapped_knob(const DrawnElement &drawn_el) {
		auto &patch = patch_storage.get_view_patch();
		auto this_module_id = PageList::get_selected_module_id();

		// auto maps = patch.get_knob_mappings(this_module_id, drawn_el.gui_element.module_idx);

		// if (maps.size() > 0) {
		// 	lv_group_add_obj(pane_group, ui_EditMap);
		// } else {
		// 	lv_group_add_obj(pane_group, ui_AddMapButton);
		// 	lv_group_add_obj(pane_group, ui_ControlButton);
		// }
	}

	void blur() {
		if (pane_group) {
			lv_group_del(pane_group);
			pane_group = nullptr;
		}
	}

	void show() {
		if (!visible) {
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			lv_indev_set_group(indev, pane_group);
			if (num_mappings > 0) {
				lv_group_focus_obj(ui_EditMap);
			} else {
				lv_group_focus_obj(ui_AddMapButton);
				lv_group_focus_obj(ui_ControlButton);
			}
			visible = true;
		}
	}

	void hide() {
		if (visible) {
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			if (base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
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
