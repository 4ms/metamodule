#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/ui_local.h"
#include <cmath>
#include <functional>

namespace MetaModule
{

// A popup showing a single lv_slider, focused on its own lv_group so the rotary
// encoder adjusts its value directly. Clicking (or calling hide()) restores focus
// to whatever group was active before show() was called.
struct SliderPopup {
	SliderPopup()
		: popup{create_lv_labeled_popup(lv_layer_sys(), "")}
		, label{lv_obj_get_child(popup, 0)}
		, slider{lv_slider_create(popup)}
		, group(lv_group_create()) {
		lv_hide(popup);

		lv_obj_set_width(slider, 200);
		lv_slider_set_range(slider, 0, Resolution);

		lv_obj_add_event_cb(slider, value_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(slider, click_cb, LV_EVENT_CLICKED, this);
		lv_group_add_obj(group, slider);
	}

	void show(std::function<void(float)> changed_cb,
			  std::function<void()> done_cb,
			  std::string_view title,
			  float scaled_value,
			  lv_group_t *cur_group) {
		on_changed = std::move(changed_cb);
		on_done = std::move(done_cb);
		orig_group = cur_group;

		lv_label_set_text(label, title.data());
		lv_slider_set_value(slider, std::round(scaled_value * Resolution), LV_ANIM_OFF);

		lv_show(popup);

		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(slider);
		lv_group_set_editing(group, true);

		visible = true;
	}

	void update_label(std::string_view text) {
		if (text.length())
			lv_label_set_text(label, text.data());
	}

	void hide() {
		lv_hide(popup);
		if (orig_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), orig_group);
		visible = false;
	}

	bool is_visible() const {
		return visible;
	}

	static constexpr int32_t Resolution = 1000;

private:
	static void value_changed_cb(lv_event_t *event) {
		auto page = static_cast<SliderPopup *>(event->user_data);
		auto val = lv_slider_get_value(page->slider);
		if (page->on_changed)
			page->on_changed((float)val / Resolution);
	}

	static void click_cb(lv_event_t *event) {
		auto page = static_cast<SliderPopup *>(event->user_data);
		page->hide();
		if (page->on_done)
			page->on_done();
	}

	lv_obj_t *popup;
	lv_obj_t *label;
	lv_obj_t *slider;
	lv_group_t *group;
	lv_group_t *orig_group = nullptr;

	bool visible = false;

	std::function<void(float)> on_changed;
	std::function<void()> on_done;
};

} // namespace MetaModule
