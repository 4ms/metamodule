#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <functional>

namespace MetaModule
{

struct ConfirmPopup {

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;

		group = lv_group_create();

		lv_obj_add_event_cb(ui_CancelButton, button_callback, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ConfirmButton, button_callback, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_TrashButton2, button_callback, LV_EVENT_CLICKED, this);

		lv_hide(ui_DelMapPopUpPanel);
	}

	void show(auto cb, const char *button_text = "Trash") {
		callback = std::move(cb);

		lv_obj_set_parent(ui_DelMapPopUpPanel, base);

		lv_show(ui_DelMapPopUpPanel);

		if (strcmp(button_text, "Trash") != 0) {
			lv_show(ui_ConfirmButton);
			lv_hide(ui_TrashButton2);
			lv_label_set_text(ui_ConfirmLabel, button_text);
			lv_group_remove_all_objs(group);
			lv_group_add_obj(group, ui_CancelButton);
			lv_group_add_obj(group, ui_ConfirmButton);
		} else {
			lv_hide(ui_ConfirmButton);
			lv_show(ui_TrashButton2);
			lv_group_remove_all_objs(group);
			lv_group_add_obj(group, ui_CancelButton);
			lv_group_add_obj(group, ui_TrashButton2);
		}

		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(ui_CancelButton);

		visible = true;
	}

	void hide() {
		lv_hide(ui_DelMapPopUpPanel);
		if (orig_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), orig_group);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

	static void button_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ConfirmPopup *>(event->user_data);
		if (!page)
			return;

		if (page->callback) {
			if (event->target == ui_CancelButton)
				page->callback(false);
			else if (event->target == ui_TrashButton2 || event->target == ui_ConfirmButton)
				page->callback(true);
		}

		page->hide();
	}

private:
	lv_obj_t *base;
	lv_group_t *group;
	lv_group_t *orig_group;

	bool visible = false;

	std::function<void(bool)> callback;
};

} // namespace MetaModule
