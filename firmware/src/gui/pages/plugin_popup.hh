#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/lv_obj_copy.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_tree.h"
#include <functional>
#include <string_view>

namespace MetaModule
{

struct PluginPopup {
	PluginPopup()
		: group{lv_group_create()} {
		auto p = create_labeled_check_obj(ui_DelMapPopUpPanel, "Autoload");
		lv_obj_move_to_index(p, 1);
		check = lv_obj_get_child(p, -1);
		lv_obj_add_event_cb(check, toggle_callback, LV_EVENT_VALUE_CHANGED, this);
		lv_hide(check);
		lv_hide(p);
		lv_hide(lv_obj_get_child(p, 0));
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
		lv_hide(ui_DelMapPopUpPanel);
	}

	void show(auto button_cb, auto toggle_cb, const char *message, std::string_view choice1_text, bool state) {
		lv_hide(ui_TrashButton2);
		lv_hide(ui_Choice2Button);

		remove_all_event_cb(ui_CancelButton);
		lv_obj_add_event_cb(ui_CancelButton, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(ui_ConfirmButton);
		lv_obj_add_event_cb(ui_ConfirmButton, button_callback, LV_EVENT_CLICKED, this);

		lv_group_remove_all_objs(group);

		lv_obj_set_parent(ui_DelMapPopUpPanel, base);

		lv_show(ui_DelMapPopUpPanel);

		lv_label_set_text(ui_DelMapLabel, message);

		_button_callback = std::move(button_cb);
		_toggle_callback = std::move(toggle_cb);

		lv_check(check, state);

		auto p = lv_obj_get_parent(check);
		lv_show(check);
		lv_show(p);
		lv_show(lv_obj_get_child(p, 0));

		lv_group_add_obj(group, check);

		lv_show(ui_ConfirmButton);
		lv_label_set_text_fmt(ui_ConfirmLabel, "%.*s", (int)choice1_text.size(), choice1_text.data());
		lv_group_add_obj(group, ui_ConfirmButton);

		lv_group_add_obj(group, ui_CancelButton);
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(ui_CancelButton);

		visible = true;
	}

	void hide() {
		auto p = lv_obj_get_parent(check);
		lv_hide(check);
		lv_hide(p);
		lv_hide(lv_obj_get_child(p, 0));

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
		auto page = static_cast<PluginPopup *>(event->user_data);
		if (!page)
			return;

		if (page->_button_callback) {
			if (event->target == ui_CancelButton)
				page->_button_callback(0);
			else if (event->target == ui_ConfirmButton)
				page->_button_callback(1);
		}

		page->hide();
	}

	static void toggle_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PluginPopup *>(event->user_data);
		if (!page)
			return;

		if (page->_toggle_callback) {
			if (event->target == page->check)
				page->_toggle_callback(lv_obj_has_state(page->check, LV_STATE_CHECKED));
		}
	}

protected:
	lv_obj_t *check;
	lv_obj_t *base;
	lv_group_t *group;
	lv_group_t *orig_group;

	bool visible = false;

	std::function<void(unsigned)> _button_callback;
	std::function<void(bool)> _toggle_callback;
};

} // namespace MetaModule
