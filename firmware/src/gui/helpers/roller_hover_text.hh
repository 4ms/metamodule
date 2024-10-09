#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"

namespace MetaModule
{
class RollerHoverText {
public:
	RollerHoverText(lv_obj_t *parent)
		: label_cont{lv_obj_create(parent)}
		, label{lv_label_create(label_cont)} {
	}

	void init(lv_obj_t *roller) {
		lv_obj_set_align(label_cont, LV_ALIGN_CENTER);
		lv_obj_set_y(label_cont, lv_obj_get_y(roller) / 2 + 0);
		lv_obj_set_x(label_cont, 0);
		lv_obj_set_width(label_cont, lv_pct(109));
		lv_obj_set_height(label_cont, 19);
		lv_obj_set_style_pad_all(label_cont, 0, LV_PART_MAIN);
		lv_obj_set_style_radius(label_cont, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(label_cont, LV_OPA_0, LV_PART_MAIN);
		lv_obj_set_style_border_opa(label_cont, LV_OPA_0, LV_PART_MAIN);
		lv_obj_clear_flag(label_cont, LV_OBJ_FLAG_SCROLLABLE);

		this->roller = roller;
		lv_obj_set_align(label, LV_ALIGN_CENTER);
		lv_obj_set_y(label, 0);
		lv_obj_set_x(label, -1);
		lv_obj_set_height(label, 19);
		lv_obj_set_width(label, lv_pct(100));
		lv_label_set_text(label, "");
		lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
		lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_obj_set_style_text_opa(label, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_text_letter_space(label, 0, LV_PART_MAIN);
		lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN);
		lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
		lv_obj_set_style_radius(label, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(label, lv_color_hex(0xFD8B18), LV_PART_MAIN);
		// lv_obj_set_style_bg_color(label, lv_color_hex(0x00f0f0), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(label, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_border_width(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_left(label, 15, LV_PART_MAIN);
		lv_obj_set_style_pad_right(label, 10, LV_PART_MAIN);
		lv_obj_set_style_radius(label, 0, LV_PART_MAIN);
		lv_label_set_recolor(label, true);
		lv_obj_clear_flag(label_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_hide(label);
	}

	void update() {
		if (display_timer > 0) {
			if (display_timer == 1) {
				auto sel_idx = lv_roller_get_selected(roller);
				if (sel_idx >= 0 && sel_idx < lv_roller_get_option_cnt(roller)) {
					char sel_buf[64];
					lv_roller_get_selected_str(roller, sel_buf, 64);
					lv_label_set_text(label, sel_buf);
					lv_show(label);
					display_timer = 0;
				}
			} else
				display_timer--;
		}
	}

	void hide() {
		lv_hide(label);
		display_timer = 0;
	}

	void display_in_time(uint32_t tm) {
		display_timer = tm;
	}

	void set_width(uint32_t width) {
		// lv_obj_set_width(label, width - left_pad - 9);
		// lv_obj_set_x(label, left_pad);
	}

private:
	uint32_t display_timer = 0;
	lv_obj_t *label_cont;
	lv_obj_t *label;
	lv_obj_t *roller;

	static constexpr lv_coord_t left_pad = 8;
};

} // namespace MetaModule
