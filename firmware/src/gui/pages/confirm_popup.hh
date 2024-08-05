#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <functional>
#include <string_view>

namespace MetaModule
{

struct ConfirmPopup {
	ConfirmPopup()
		: group(lv_group_create()) {
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
		lv_hide(ui_DelMapPopUpPanel);
	}

	void show(auto cb, const char *message, std::string_view choice1_text, std::string_view choice2_text = "") {
		remove_all_event_cb(ui_CancelButton);
		lv_obj_add_event_cb(ui_CancelButton, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(ui_ConfirmButton);
		lv_obj_add_event_cb(ui_ConfirmButton, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(ui_TrashButton2);
		lv_obj_add_event_cb(ui_TrashButton2, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(ui_Choice2Button);
		lv_obj_add_event_cb(ui_Choice2Button, button_callback, LV_EVENT_CLICKED, this);

		lv_group_remove_all_objs(group);

		lv_obj_set_parent(ui_DelMapPopUpPanel, base);

		lv_show(ui_DelMapPopUpPanel);

		lv_label_set_text(ui_DelMapLabel, message);

		callback = std::move(cb);

		if (choice2_text.size() > 0) {
			lv_show(ui_Choice2Button);
			lv_label_set_text_fmt(ui_Choice2Label, "%.*s", (int)choice2_text.size(), choice2_text.data());
			lv_group_add_obj(group, ui_Choice2Button);
		} else {
			lv_hide(ui_Choice2Button);
		}

		if (choice1_text == "Trash") {
			lv_hide(ui_ConfirmButton);
			lv_show(ui_TrashButton2);
			lv_group_add_obj(group, ui_TrashButton2);
		} else {
			lv_show(ui_ConfirmButton);
			lv_hide(ui_TrashButton2);
			lv_label_set_text_fmt(ui_ConfirmLabel, "%.*s", (int)choice1_text.size(), choice1_text.data());
			lv_group_add_obj(group, ui_ConfirmButton);
		}

		lv_group_add_obj(group, ui_CancelButton);
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
				page->callback(0);

			else if (event->target == ui_TrashButton2 || event->target == ui_ConfirmButton)
				page->callback(1);

			else if (event->target == ui_Choice2Button)
				page->callback(2);
		}

		page->hide();
	}

protected:
	lv_obj_t *base;
	lv_group_t *group;
	lv_group_t *orig_group;

	bool visible = false;

	std::function<void(unsigned)> callback;
};

} // namespace MetaModule
