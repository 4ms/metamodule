#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"
#include "pr_dbg.hh"

namespace MetaModule
{
class RollerHoverText {
public:
	// Typically `parent` will be the enclosing container of `roller`
	RollerHoverText(lv_obj_t *parent, lv_obj_t *roller)
		: label_cont{lv_obj_create(parent)}
		, label{lv_label_create(label_cont)}
		, roller{roller} {

		if (lv_obj_get_child_cnt(roller) > 0) {
			auto roller_label = lv_obj_get_child(roller, 0);
			lv_obj_add_event_cb(roller_label, redraw_done_cb, LV_EVENT_DRAW_POST_END, this);
		} else {
			pr_err("RollerHoverText requires a Roller, which must have a label child\n");
		}

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
		lv_obj_set_style_bg_opa(label, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_border_width(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_left(label, 15, LV_PART_MAIN);
		lv_obj_set_style_pad_right(label, 6, LV_PART_MAIN);
		lv_obj_set_style_radius(label, 0, LV_PART_MAIN);
		lv_label_set_recolor(label, true);
		lv_obj_clear_flag(label_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_hide(label);
	}

	void update() {
		if (display_timer > 0) {
			if (display_timer == 1) {
				auto new_sel_idx = lv_roller_get_selected(roller);
				if (new_sel_idx >= 0 && new_sel_idx < lv_roller_get_option_cnt(roller)) {
					if (sel_idx != new_sel_idx) {
						sel_idx = new_sel_idx;
						char sel_buf[64];
						lv_roller_get_selected_str(roller, sel_buf, 64);
						lv_label_set_text(label, sel_buf);
						lv_show(label);
						display_timer = 0;
					}
				} else {
					pr_warn("Invalid selection %d\n", sel_idx);
				}
			} else {
				display_timer--;
			}
		}
	}

	void hide() {
		lv_hide(label);
		display_timer = 0;
	}

	void display_in_time(uint32_t tm) {
		if (display_timer == 0) {
			display_timer = tm;
		}
	}

	static void redraw_done_cb(lv_event_t *event) {
		auto page = static_cast<RollerHoverText *>(event->user_data);
		if (event->code == LV_EVENT_DRAW_POST_END) {
			page->display_in_time(10);
		}
	}

	lv_obj_t *cont() {
		return label_cont;
	}

private:
	uint32_t display_timer = 0;
	lv_obj_t *label_cont;
	lv_obj_t *label;
	lv_obj_t *roller;
	uint32_t sel_idx = 0;
};

} // namespace MetaModule
