#pragma once
#include "delay.hh"
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"

namespace MetaModule
{

// A horizontal scroll indicator, pinned to the bottom of a page.
// Unlike LVGL's scrollbar, it's not tied to UI events, and can be glued to the page rather than
// to the parent object.
class HScrollBar {
public:
	// page: where the bar is drawn, pinned to the bottom of its content area
	// scroller: the object whose horizontal scroll position is being shown
	HScrollBar(lv_obj_t *page, lv_obj_t *scroller)
		: page{page}
		, scroller{scroller}
		, bar{lv_obj_create(page)} {

		lv_obj_add_flag(bar, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_IGNORE_LAYOUT);
		lv_obj_clear_flag(bar,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SNAPPABLE);

		lv_obj_set_height(bar, HeightPx);
		lv_obj_set_style_radius(bar, 3, LV_PART_MAIN);
		lv_obj_set_style_bg_color(bar, lv_color_hex(0xDF7D1A), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
		lv_obj_set_style_border_width(bar, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_all(bar, 0, LV_PART_MAIN);

		lv_hide(bar);
	}

	// Call whenever the scroll position or the scrollable extent changes
	// The bar hides itself when there is nothing to scroll.
	void show() {
		auto scrolled_left = lv_obj_get_scroll_left(scroller);
		auto scrolled_right = lv_obj_get_scroll_right(scroller);
		auto hidden = scrolled_left + scrolled_right;

		if (hidden <= 0) {
			hide();
			return;
		}

		auto track = lv_obj_get_content_width(page);
		auto view = lv_obj_get_content_width(scroller);

		auto width = std::max<lv_coord_t>(MinWidthPx, track * view / (view + hidden));
		auto x = (track - width) * scrolled_left / hidden;

		lv_obj_set_width(bar, width);
		lv_obj_set_pos(bar, x, lv_obj_get_content_height(page) - HeightPx);
		lv_obj_move_foreground(bar);

		lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
		lv_show(bar);
		shown_tm = get_time();
	}

	// Fades out a moment (HoldMs) after the last show()
	void update() {
		if (lv_obj_has_flag(bar, LV_OBJ_FLAG_HIDDEN))
			return;

		auto elapsed = get_time() - shown_tm;
		if (elapsed < HoldMs)
			return;

		auto fading = elapsed - HoldMs;
		if (fading >= FadeMs) {
			hide();
			return;
		}

		lv_obj_set_style_bg_opa(bar, LV_OPA_COVER - (LV_OPA_COVER * fading / FadeMs), LV_PART_MAIN);
	}

	void hide() {
		lv_hide(bar);
	}

private:
	static constexpr uint32_t HoldMs = 150;
	static constexpr uint32_t FadeMs = 100;

	static constexpr lv_coord_t HeightPx = 4;
	static constexpr lv_coord_t MinWidthPx = 12;

	lv_obj_t *page;
	lv_obj_t *scroller;
	lv_obj_t *bar;
	uint64_t shown_tm = 0;
};

} // namespace MetaModule
