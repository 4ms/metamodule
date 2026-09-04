#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "patch/patch.hh"
#include <array>
#include <functional>
#include <string>

namespace MetaModule
{

// Popup showing what is attached to the Left and Right sides of a module.
// Each side is a full-width slot that reads like plain text with a white
// outline, and turns orange when highlighted. A filled slot also has a small
// red X button at its right edge for detaching.
struct ExpanderPopup {
	using SideCallback = std::function<void(ExpanderSide)>;

	ExpanderPopup()
		: popup{create_lv_labeled_popup(lv_layer_top(), "Expanders")}
		, group{lv_group_create()} {
		lv_hide(popup);
		lv_obj_set_width(popup, 300);
		lv_obj_set_height(popup, LV_SIZE_CONTENT);
		lv_obj_set_align(popup, LV_ALIGN_CENTER);
		lv_obj_set_style_pad_row(popup, 8, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(popup, 12, LV_PART_MAIN);

		for (auto side : {ExpanderSide::Left, ExpanderSide::Right}) {
			auto &row = rows[idx(side)];
			row.side = side;
			create_row(row);
			lv_group_add_obj(group, row.slot);
			lv_group_add_obj(group, row.remove_button); // skipped by the group while hidden
		}
		lv_group_set_wrap(group, false);
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		base = page_base;
		orig_group = current_group;
	}

	// slot_clicked: the slot itself was clicked (empty or filled)
	// remove_clicked: the X button of a filled slot was clicked
	void show(SideCallback slot_clicked, SideCallback remove_clicked) {
		on_slot_clicked = std::move(slot_clicked);
		on_remove_clicked = std::move(remove_clicked);

		if (base)
			lv_obj_set_parent(popup, base);

		lv_show(popup);
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(rows[0].slot);
		visible = true;
	}

	// Set a slot's text, and whether it's filled (which shows the X button)
	void set_slot(ExpanderSide side, std::string const &text, bool filled) {
		auto &row = rows[idx(side)];
		lv_label_set_text(row.label, text.c_str());

		if (!filled && lv_group_get_focused(group) == row.remove_button)
			lv_group_focus_obj(row.slot);

		lv_show(row.remove_button, filled);
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

	// Make the popup the input target again (e.g. after something else changed the active group)
	void activate() {
		if (visible)
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
	}

private:
	struct Row {
		lv_obj_t *container{};
		lv_obj_t *slot{};
		lv_obj_t *label{};
		lv_obj_t *remove_button{};
		ExpanderSide side{};
		ExpanderPopup *parent{};
	};

	static constexpr size_t idx(ExpanderSide side) {
		return side == ExpanderSide::Left ? 0 : 1;
	}

	void create_row(Row &row) {
		row.parent = this;

		// Row: the slot and its X button side by side. The X sits outside the
		// slot's outline, so highlighting the slot does not surround the X.
		row.container = lv_obj_create(popup);
		lv_obj_set_width(row.container, lv_pct(100));
		lv_obj_set_height(row.container, 30);
		lv_obj_clear_flag(row.container, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
		// Let the X button's focus outline draw past the row's right edge
		lv_obj_add_flag(row.container, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
		lv_obj_set_style_bg_opa(row.container, LV_OPA_TRANSP, LV_PART_MAIN);
		lv_obj_set_style_border_width(row.container, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(row.container, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_column(row.container, 6, LV_PART_MAIN);
		lv_obj_set_flex_flow(row.container, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(row.container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

		// Slot: plain text with a white outline, fills the row, orange when highlighted
		row.slot = lv_btn_create(row.container);
		lv_obj_set_flex_grow(row.slot, 1);
		lv_obj_set_height(row.slot, 30);
		lv_obj_clear_flag(row.slot,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_radius(row.slot, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(row.slot, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(row.slot, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(row.slot, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(row.slot, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(row.slot, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(row.slot, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_ver(row.slot, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_shadow_width(row.slot, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(row.slot, Gui::orange_highlight, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_bg_opa(row.slot, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(row.slot, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(row.slot, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_add_event_cb(row.slot, slot_click_cb, LV_EVENT_CLICKED, &row);

		row.label = lv_label_create(row.slot);
		lv_obj_set_width(row.label, lv_pct(100));
		lv_obj_set_height(row.label, LV_SIZE_CONTENT);
		lv_obj_set_align(row.label, LV_ALIGN_LEFT_MID);
		lv_label_set_long_mode(row.label, LV_LABEL_LONG_DOT);
		lv_obj_set_style_text_color(row.label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(row.label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_label_set_text(row.label, "");

		// X button: red with a white X, only shown when the slot is filled
		// (hidden objects are left out of the flex layout, so the slot then takes the full row)
		row.remove_button = lv_btn_create(row.container);
		lv_obj_set_size(row.remove_button, 22, 22);
		lv_obj_clear_flag(row.remove_button,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_radius(row.remove_button, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(row.remove_button, Gui::red_highlight, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(row.remove_button, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(row.remove_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_shadow_width(row.remove_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(row.remove_button, Gui::orange_highlight, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(row.remove_button, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(row.remove_button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(row.remove_button, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(row.remove_button, Gui::orange_highlight, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(row.remove_button, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_add_event_cb(row.remove_button, remove_click_cb, LV_EVENT_CLICKED, &row);
		lv_hide(row.remove_button);

		auto x_label = lv_label_create(row.remove_button);
		lv_obj_set_align(x_label, LV_ALIGN_CENTER);
		lv_label_set_text(x_label, "X");
		lv_obj_set_style_text_color(x_label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(x_label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	static void slot_click_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto *row = static_cast<Row *>(event->user_data);
		if (row->parent->on_slot_clicked)
			row->parent->on_slot_clicked(row->side);
	}

	static void remove_click_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto *row = static_cast<Row *>(event->user_data);
		if (row->parent->on_remove_clicked)
			row->parent->on_remove_clicked(row->side);
	}

	lv_obj_t *popup;
	lv_group_t *group;
	lv_obj_t *base = nullptr;
	lv_group_t *orig_group = nullptr;
	bool visible = false;

	std::array<Row, 2> rows{};

	SideCallback on_slot_clicked;
	SideCallback on_remove_clicked;
};

} // namespace MetaModule
