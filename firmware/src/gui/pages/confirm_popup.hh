#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <functional>
#include <string_view>

namespace MetaModule
{

struct ConfirmPopup {
	lv_obj_t *panel;
	lv_obj_t *cancel_button;
	lv_obj_t *cancel_label;
	lv_obj_t *confirm_button;
	lv_obj_t *confirm_label;
	lv_obj_t *trash_button;
	lv_obj_t *message_label;
	lv_obj_t *choice2_button;
	lv_obj_t *choice2_label;

	ConfirmPopup(lv_obj_t *parent = ui_MainMenu)
		: group(lv_group_create()) {
		init_widgets(parent);
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
		lv_hide(panel);
	}

	void show(auto cb, const char *message, std::string_view choice1_text, std::string_view choice2_text = "") {
		remove_all_event_cb(cancel_button);
		lv_obj_add_event_cb(cancel_button, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(confirm_button);
		lv_obj_add_event_cb(confirm_button, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(trash_button);
		lv_obj_add_event_cb(trash_button, button_callback, LV_EVENT_CLICKED, this);

		remove_all_event_cb(choice2_button);
		lv_obj_add_event_cb(choice2_button, button_callback, LV_EVENT_CLICKED, this);

		lv_group_remove_all_objs(group);

		lv_obj_set_parent(panel, base);

		lv_show(panel);

		lv_label_set_text(cancel_label, "Cancel");
		lv_label_set_text(message_label, message);

		callback = std::move(cb);

		lv_group_add_obj(group, cancel_button);

		lv_group_activate(group);

		if (choice2_text.size() > 0) {
			lv_show(choice2_button);
			lv_obj_clear_state(choice2_button, LV_STATE_FOCUSED);
			lv_obj_clear_state(choice2_button, LV_STATE_FOCUS_KEY);
			lv_label_set_text_fmt(choice2_label, "%.*s", (int)choice2_text.size(), choice2_text.data());
			lv_group_add_obj(group, choice2_button);
		} else {
			lv_hide(choice2_button);
		}

		if (choice1_text == "Trash") {
			lv_hide(confirm_button);
			lv_show(trash_button);
			lv_obj_clear_state(trash_button, LV_STATE_FOCUSED);
			lv_obj_clear_state(trash_button, LV_STATE_FOCUS_KEY);
			lv_group_add_obj(group, trash_button);
			lv_show(cancel_button);
			lv_group_focus_obj(cancel_button);
		} else {
			lv_show(confirm_button);
			lv_obj_clear_state(confirm_button, LV_STATE_FOCUSED);
			lv_obj_clear_state(confirm_button, LV_STATE_FOCUS_KEY);
			lv_hide(trash_button);
			lv_group_add_obj(group, confirm_button);

			if (choice1_text.length() == 0) {
				lv_label_set_text(confirm_label, "OK");
				lv_hide(cancel_button);
				lv_group_focus_obj(confirm_button);
			} else {
				lv_label_set_text_fmt(confirm_label, "%.*s", (int)choice1_text.size(), choice1_text.data());
				lv_show(cancel_button);
				lv_group_focus_obj(cancel_button);
			}
		}

		lv_group_set_wrap(group, false);

		lv_obj_set_style_text_font(message_label, &ui_font_MuseoSansRounded70016, 0);
		lv_obj_refr_size(message_label);
		if (lv_obj_get_height(message_label) > 200) {
			lv_obj_set_style_text_font(message_label, &ui_font_MuseoSansRounded50014, 0);
		}

		visible = true;
	}

	void hide() {
		lv_hide(panel);
		lv_group_activate(orig_group);
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
			if (event->target == page->cancel_button)
				page->callback(0);

			else if (event->target == page->trash_button || event->target == page->confirm_button)
				page->callback(1);

			else if (event->target == page->choice2_button)
				page->callback(2);
		}

		page->hide();
	}

	void init_widgets(lv_obj_t *parent) {
		panel = lv_obj_create(parent);
		lv_obj_set_width(panel, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(panel, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(panel, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
		lv_obj_add_flag(panel, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
		lv_obj_clear_flag(panel,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(panel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(panel, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_side(panel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(panel, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(panel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_pad(panel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(panel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(panel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

		message_label = lv_label_create(panel);
		lv_obj_set_width(message_label, 180);
		lv_obj_set_height(message_label, LV_SIZE_CONTENT); /// 30
		lv_obj_set_align(message_label, LV_ALIGN_CENTER);
		lv_label_set_text(message_label, "Are you sure you want to Delete this mapping?");
		lv_obj_set_style_text_color(message_label, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(message_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(message_label, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(message_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(message_label, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(message_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(message_label, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(message_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_pad(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(message_label, -4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(message_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		auto button_panel = lv_obj_create(panel);
		lv_obj_set_height(button_panel, 50);
		lv_obj_set_width(button_panel, LV_SIZE_CONTENT); /// 1
		lv_obj_set_x(button_panel, 0);
		lv_obj_set_y(button_panel, 18);
		lv_obj_set_align(button_panel, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(button_panel, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(button_panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_add_flag(button_panel, LV_OBJ_FLAG_OVERFLOW_VISIBLE); /// Flags
		lv_obj_clear_flag(button_panel,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_scrollbar_mode(button_panel, LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_radius(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(button_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(button_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(button_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(button_panel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

		cancel_button = lv_btn_create(button_panel);
		lv_obj_set_width(cancel_button, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(cancel_button, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(cancel_button, LV_ALIGN_CENTER);
		lv_obj_add_flag(cancel_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
		lv_obj_clear_flag(cancel_button,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(cancel_button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(cancel_button, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(cancel_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(cancel_button, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(cancel_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(cancel_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(cancel_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(cancel_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(cancel_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(cancel_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(cancel_button, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_opa(cancel_button, 0, LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_color(cancel_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(cancel_button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(cancel_button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(cancel_button, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(cancel_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(cancel_button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_width(cancel_button, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_pad(cancel_button, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

		cancel_label = lv_label_create(cancel_button);
		lv_obj_set_width(cancel_label, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(cancel_label, LV_SIZE_CONTENT); /// 1
		lv_obj_set_x(cancel_label, -1);
		lv_obj_set_y(cancel_label, 0);
		lv_obj_set_align(cancel_label, LV_ALIGN_CENTER);
		lv_label_set_text(cancel_label, "Cancel");
		lv_obj_set_style_text_color(cancel_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(cancel_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(cancel_label, &ui_font_MuseoSansRounded50016, LV_PART_MAIN | LV_STATE_DEFAULT);

		trash_button = lv_btn_create(button_panel);
		lv_obj_set_width(trash_button, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(trash_button, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(trash_button, LV_ALIGN_CENTER);
		lv_obj_add_flag(trash_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
		lv_obj_clear_flag(trash_button,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(trash_button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(trash_button, lv_color_hex(0xE91C25), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(trash_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(trash_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(trash_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(trash_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(trash_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(trash_button, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_opa(trash_button, 0, LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_color(trash_button, lv_color_hex(0xE91C25), LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(trash_button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(trash_button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(trash_button, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(trash_button, lv_color_hex(0xE91C25), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(trash_button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_width(trash_button, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_pad(trash_button, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_color(trash_button, lv_color_hex(0xE91C25), LV_PART_MAIN | LV_STATE_USER_1);
		lv_obj_set_style_outline_opa(trash_button, 255, LV_PART_MAIN | LV_STATE_USER_1);
		lv_obj_set_style_outline_width(trash_button, 2, LV_PART_MAIN | LV_STATE_USER_1);
		lv_obj_set_style_outline_pad(trash_button, 3, LV_PART_MAIN | LV_STATE_USER_1);

		auto trash_icon = lv_label_create(trash_button);
		lv_obj_set_width(trash_icon, LV_SIZE_CONTENT);	/// 1
		lv_obj_set_height(trash_icon, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(trash_icon, LV_ALIGN_CENTER);
		lv_label_set_text(trash_icon, "");
		lv_obj_set_style_text_color(trash_icon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(trash_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(trash_icon, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(trash_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(trash_icon, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(trash_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(trash_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(trash_icon, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(trash_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		choice2_button = lv_btn_create(button_panel);
		lv_obj_set_width(choice2_button, LV_SIZE_CONTENT);	/// 1
		lv_obj_set_height(choice2_button, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(choice2_button, LV_ALIGN_CENTER);
		lv_obj_add_flag(choice2_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
		lv_obj_clear_flag(choice2_button, LV_OBJ_FLAG_SCROLLABLE);	  /// Flags
		lv_obj_set_style_radius(choice2_button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(choice2_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(choice2_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(choice2_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(choice2_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(choice2_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(choice2_button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_width(choice2_button, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_pad(choice2_button, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

		choice2_label = lv_label_create(choice2_button);
		lv_obj_set_width(choice2_label, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(choice2_label, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(choice2_label, LV_ALIGN_CENTER);
		lv_label_set_text(choice2_label, "Choice");
		lv_obj_set_style_text_color(choice2_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(choice2_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(choice2_label, &ui_font_MuseoSansRounded50016, LV_PART_MAIN | LV_STATE_DEFAULT);

		confirm_button = lv_btn_create(button_panel);
		lv_obj_set_width(confirm_button, LV_SIZE_CONTENT);	/// 1
		lv_obj_set_height(confirm_button, LV_SIZE_CONTENT); /// 1
		lv_obj_set_align(confirm_button, LV_ALIGN_CENTER);
		lv_obj_add_flag(confirm_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
		lv_obj_clear_flag(confirm_button,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(confirm_button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(confirm_button, lv_color_hex(0x2095F6), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(confirm_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(confirm_button, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(confirm_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(confirm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(confirm_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(confirm_button, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(confirm_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(confirm_button, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(confirm_button, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_opa(confirm_button, 0, LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_outline_color(confirm_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(confirm_button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(confirm_button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(confirm_button, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(confirm_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(confirm_button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_width(confirm_button, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_pad(confirm_button, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

		confirm_label = lv_label_create(confirm_button);
		lv_obj_set_width(confirm_label, LV_SIZE_CONTENT);  /// 1
		lv_obj_set_height(confirm_label, LV_SIZE_CONTENT); /// 1
		lv_obj_set_x(confirm_label, -1);
		lv_obj_set_y(confirm_label, 0);
		lv_obj_set_align(confirm_label, LV_ALIGN_CENTER);
		lv_label_set_text(confirm_label, "Confirm");
		lv_obj_set_style_text_color(confirm_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(confirm_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(confirm_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(confirm_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(confirm_label, &ui_font_MuseoSansRounded50016, LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_hide(panel);
	}

protected:
	lv_obj_t *base{};
	lv_group_t *group;
	lv_group_t *orig_group{};

	bool visible = false;

	std::function<void(unsigned)> callback;
};

} // namespace MetaModule
