#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_tree.h"
#include <functional>
#include <optional>
#include <string_view>

namespace MetaModule
{

struct PluginPopup : ConfirmPopup {
	PluginPopup()
		: group{lv_group_create()} {
		auto p = create_labeled_check_obj(panel, "Pre-load");
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
		lv_hide(panel);
	}

	void show(auto callback, const char *message, std::string_view choice1_text, bool state) {
		lv_hide(trash_button);
		lv_hide(choice2_button);

		remove_all_event_cb(cancel_button);
		lv_obj_add_event_cb(cancel_button, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(confirm_button);
		lv_obj_add_event_cb(confirm_button, button_callback, LV_EVENT_CLICKED, this);

		lv_group_remove_all_objs(group);

		lv_obj_set_parent(panel, base);

		lv_show(panel);

		lv_label_set_text(cancel_label, "Close");
		lv_label_set_text(message_label, message);

		_callback = std::move(callback);

		lv_check(check, state);

		auto p = lv_obj_get_parent(check);
		lv_show(check);
		lv_show(p);
		lv_show(lv_obj_get_child(p, 0));

		lv_group_add_obj(group, check);

		lv_group_add_obj(group, cancel_button);
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(cancel_button);

		lv_show(confirm_button);
		lv_label_set_text_fmt(confirm_label, "%.*s", (int)choice1_text.size(), choice1_text.data());
		lv_group_add_obj(group, confirm_button);

		lv_group_set_wrap(group, false);

		visible = true;
	}

	void hide() {
		auto p = lv_obj_get_parent(check);
		lv_hide(check);
		lv_hide(p);
		lv_hide(lv_obj_get_child(p, 0));

		lv_hide(panel);
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

		if (page->_callback) {
			if (event->target == page->cancel_button)
				page->_callback(0, {});
			else if (event->target == page->confirm_button)
				page->_callback(1, {});
		}

		page->hide();
	}

	static void toggle_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PluginPopup *>(event->user_data);
		if (!page)
			return;

		if (page->_callback) {
			if (event->target == page->check)
				page->_callback({}, lv_obj_has_state(page->check, LV_STATE_CHECKED));
		}
	}

protected:
	lv_obj_t *check;
	lv_obj_t *base;
	lv_group_t *group;
	lv_group_t *orig_group;

	bool visible = false;

	std::function<void(std::optional<unsigned>, std::optional<bool>)> _callback;
};

} // namespace MetaModule
