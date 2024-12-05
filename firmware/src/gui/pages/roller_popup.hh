#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "lvgl.h"
#include "src/core/lv_event.h"
#include "src/core/lv_group.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_tree.h"
#include "src/widgets/lv_roller.h"
#include <functional>
#include <string_view>
#include <tuple>

namespace MetaModule
{

struct RollerPopup {
	RollerPopup(const std::string_view label)
		: popup{create_lv_labeled_popup(lv_layer_sys(), label.data())}
		, roller(create_lv_roller(popup))
		, group(lv_group_create()) {
		lv_hide(popup);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_CLICKED, this);
		lv_group_add_obj(group, roller);
	}

	lv_obj_t *popup;
	lv_obj_t *roller;

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
	}

	static void roller_click_cb(lv_event_t *event) {
		if (!event || !event->user_data) {
			return;
		}
		auto page = static_cast<RollerPopup *>(event->user_data);
		const auto roller_idx = lv_roller_get_selected(event->target);
		page->callback(roller_idx);
		page->hide();
	}

	void show(auto cb, const char *message, const char *options, const uint16_t start_index) {

		lv_roller_set_options(roller, options, LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(roller, start_index, LV_ANIM_OFF);

		lv_obj_set_parent(popup, base);

		lv_show(popup);

		callback = std::move(cb);

		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(roller);
		lv_group_set_editing(group, true);

		visible = true;
	}

	void hide() {
		lv_hide(popup);
		if (orig_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), orig_group);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

protected:
	lv_obj_t *base;
	lv_group_t *group;
	lv_group_t *orig_group;

	bool visible = false;

	std::function<void(unsigned)> callback;
};

} // namespace MetaModule
