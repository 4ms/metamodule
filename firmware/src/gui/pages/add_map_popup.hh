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

namespace MetaModule
{

struct AddMapPopUp {
	AddMapPopUp(PatchStorageProxy &patch_storage, PatchModQueue &patch_mod_queue)
		: patch_storage{patch_storage}
		, patch_mod_queue{patch_mod_queue} {

		lv_obj_add_event_cb(ui_OkAdd, button_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_CancelAdd, button_cb, LV_EVENT_PRESSED, this);
	}
	//

	void prepare_focus(lv_group_t *group) {
		base_group = group;
	}

	void show(uint32_t knobset_id, uint16_t param_id) {
		selected_knob = std::nullopt;

		popup_group = lv_group_create();
		lv_group_remove_all_objs(popup_group);
		lv_group_set_editing(popup_group, false);
		lv_group_add_obj(popup_group, ui_CancelAdd);
		lv_group_add_obj(popup_group, ui_OkAdd);
		lv_group_focus_obj(ui_CancelAdd);

		lv_show(ui_AddMapPopUp);
		lv_obj_scroll_to_y(ui_AddMapPopUp, 0, LV_ANIM_OFF);

		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;

		lv_indev_set_group(indev, popup_group);

		param_idx = param_id;
		set_id = knobset_id;
		visible = true;
	}

	void hide() {
		visible = false;
		lv_hide(ui_AddMapPopUp);

		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;

		if (base_group)
			lv_indev_set_group(indev, base_group);

		if (popup_group) {
			lv_group_del(popup_group);
			popup_group = nullptr;
		}
	}

	void update(ParamsState &params) {
		if (visible) {
			for (unsigned i = 0; auto const &knob : params.knobs) {
				if (knob.changed) {
					auto name = PanelDef::get_map_param_name(i);
					lv_label_set_text_fmt(ui_MapDetected, "Knob: %.4s", name.data());
					selected_knob = i;
				}
				i++;
			}
		}
	}

	static void button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<AddMapPopUp *>(event->user_data);

		if (event->target == ui_OkAdd) {
			if (page->selected_knob.has_value()) {
				uint16_t module_id = PageList::get_selected_module_id();

				page->patch_mod_queue.put(AddMapping{
					.map =
						{
							.panel_knob_id = page->selected_knob.value(),
							.module_id = module_id,
							.param_id = page->param_idx,
							.min = 0.f,
							.max = 1.f,
						},
					.set_id = page->set_id,
				});
			}
			page->hide();
		}

		else if (event->target == ui_CancelAdd)
		{
			page->hide();
		}
	}

	PatchStorageProxy &patch_storage;
	PatchModQueue &patch_mod_queue;
	lv_group_t *base_group = nullptr;
	lv_group_t *popup_group = nullptr;

	uint16_t param_idx = 0;
	uint32_t set_id = 0;
	bool visible = false;
	std::optional<uint16_t> selected_knob{};
};

} // namespace MetaModule
