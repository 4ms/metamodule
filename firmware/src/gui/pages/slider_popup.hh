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
		: group(lv_group_create()) {

		create_objects(ui_ElementRollerPanel);

		lv_hide(popup);

		lv_obj_add_event_cb(slider, value_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(slider, click_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(slider, click_release_cb, LV_EVENT_RELEASED, this);
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
		lv_slider_set_range(slider, 0, arc_range_value[arc_range_idx]);
		lv_slider_set_value(slider, std::round(scaled_value * arc_range_value[arc_range_idx]), LV_ANIM_OFF);

		lv_show(popup);

		lv_group_activate(group);
		lv_group_focus_obj(slider);
		lv_group_set_editing(group, true);

		visible = true;
	}

	void update_label(std::string_view text) {
		if (text.length())
			lv_label_set_text(label, text.data());
	}

	void back() {
		lv_hide(popup);
		if (orig_group)
			lv_group_activate(orig_group);
		visible = false;

		if (on_done)
			on_done();
	}

	bool is_visible() const {
		return visible;
	}

private:
	static void value_changed_cb(lv_event_t *event) {
		auto page = static_cast<SliderPopup *>(event->user_data);
		auto val = lv_slider_get_value(page->slider);
		if (page->on_changed)
			page->on_changed((float)val / page->arc_range_value[page->arc_range_idx]);
	}

	static void click_cb(lv_event_t *event) {
		auto page = static_cast<SliderPopup *>(event->user_data);

		float cur_value = lv_slider_get_value(page->slider);
		auto cur_arc_range = lv_slider_get_max_value(page->slider);
		page->arc_range_idx = (page->arc_range_idx + 1) % page->arc_range_value.size();

		lv_slider_set_range(page->slider, 0, page->arc_range_value[page->arc_range_idx]);
		lv_label_set_text(page->click_label, "Click to change:");
		lv_label_set_text(page->res_label, page->arc_range_text[page->arc_range_idx].data());

		auto new_arc_range = lv_slider_get_max_value(page->slider);
		lv_slider_set_value(
			page->slider, std::round(cur_value / (float)cur_arc_range * (float)new_arc_range), LV_ANIM_OFF);
	}

	static void click_release_cb(lv_event_t *event) {
		auto page = static_cast<SliderPopup *>(event->user_data);
		lv_group_focus_obj(page->slider);
		lv_group_set_editing(page->group, true);
	}

	void create_objects(lv_obj_t *parent) {
		popup = lv_obj_create(parent);
		lv_obj_set_width(popup, lv_pct(100));
		lv_obj_set_height(popup, LV_SIZE_CONTENT); /// 1
		lv_obj_set_x(popup, 0);
		lv_obj_set_y(popup, -10);
		lv_obj_set_align(popup, LV_ALIGN_BOTTOM_MID);
		lv_obj_set_flex_flow(popup, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(popup, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
		lv_obj_add_flag(popup, LV_OBJ_FLAG_FLOATING); /// Flags
		lv_obj_clear_flag(popup,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
							  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(popup, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(popup, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(popup, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(popup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(popup, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(popup, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(popup, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(popup, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(popup, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_pad(popup, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(popup, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(popup, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(popup, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(popup, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(popup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(popup, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(popup, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_set_style_pad_left(popup, -4, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(popup, -4, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(popup, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(popup, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(popup, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(popup, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

		slider = lv_slider_create(popup);
		lv_obj_set_width(slider, 0);
		lv_obj_set_height(slider, 0);
		lv_obj_set_align(slider, LV_ALIGN_CENTER);
		lv_obj_add_flag(slider, LV_OBJ_FLAG_IGNORE_LAYOUT);
		lv_arc_set_value(slider, 0);

		lv_obj_set_style_bg_color(slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);

		lv_obj_set_style_bg_opa(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(slider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(slider, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(slider, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);

		lv_obj_set_style_border_opa(slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(slider, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(slider, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_border_opa(slider, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(slider, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

		label = lv_label_create(popup);
		lv_obj_set_width(label, lv_pct(100));
		lv_obj_set_height(label, LV_SIZE_CONTENT);
		lv_obj_set_align(label, LV_ALIGN_TOP_MID);
		lv_label_set_text(label, "Turn rotary to adjust");
		lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		auto res_cont = lv_obj_create(popup);
		lv_obj_remove_style_all(res_cont);
		lv_obj_set_width(res_cont, lv_pct(100));
		lv_obj_set_height(res_cont, LV_SIZE_CONTENT); /// 50
		lv_obj_set_align(res_cont, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(res_cont, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(res_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
		lv_obj_clear_flag(res_cont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags

		click_label = lv_label_create(res_cont);
		lv_obj_set_width(click_label, lv_pct(100));
		lv_obj_set_height(click_label, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(click_label, LV_ALIGN_BOTTOM_MID);
		lv_label_set_text(click_label, "Click to change:");
		lv_obj_set_style_text_color(click_label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(click_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(click_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(click_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(click_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(click_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(click_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		res_label = lv_label_create(res_cont);
		lv_obj_set_width(res_label, lv_pct(100));
		lv_obj_set_height(res_label, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(res_label, LV_ALIGN_BOTTOM_MID);
		lv_label_set_text(res_label, "Coarse");
		lv_obj_set_style_text_color(res_label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(res_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(res_label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(res_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(res_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(res_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(res_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	lv_obj_t *popup;
	lv_obj_t *label;
	lv_obj_t *slider;
	lv_obj_t *res_label;
	lv_obj_t *click_label;

	lv_group_t *group;
	lv_group_t *orig_group = nullptr;

	unsigned arc_range_idx = 0;
	std::array<unsigned, 3> arc_range_value{100, 1000, 10000};
	std::array<std::string_view, 3> arc_range_text{"Coarse", "Fine", "Ultra-fine"};

	bool visible = false;

	std::function<void(float)> on_changed;
	std::function<void()> on_done;
};

} // namespace MetaModule
