#include "ui_local.h"
#include "CoreModules/elements/base_element.hh"
#include "conf/panel_conf.hh"
#include "gui/elements/panel_name.hh"
#include "gui/styles.hh"

namespace MetaModule
{

lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name) {
	lv_obj_t *obj = lv_btn_create(parent);
	lv_obj_set_width(obj, lv_pct(100));
	lv_obj_set_height(obj, LV_SIZE_CONTENT);
	lv_obj_set_align(obj, LV_ALIGN_LEFT_MID);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_obj_clear_flag(obj,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
						  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
						  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(obj, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(obj, lv_color_hex(0x555555), LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(obj, LV_OPA_100, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_hor(obj, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_ver(obj, 0, LV_STATE_DEFAULT);

	lv_obj_set_style_border_color(obj, lv_color_hex(0x333333), LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(obj, 255, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(obj, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_border_post(obj, true, LV_STATE_DEFAULT);

	lv_obj_set_style_border_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(obj, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(obj, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_border_post(obj, true, LV_STATE_FOCUSED);
	lv_obj_set_style_pad_ver(obj, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_pad_hor(obj, 6, LV_STATE_FOCUSED);

	lv_obj_set_style_border_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(obj, 255, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(obj, 2, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(obj, 0, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_post(obj, true, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_ver(obj, 2, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_hor(obj, 6, LV_STATE_FOCUS_KEY);

	lv_obj_t *label = lv_label_create(obj);
	lv_obj_set_width(label, lv_pct(100));
	lv_obj_set_height(label, LV_SIZE_CONTENT);
	lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
	lv_label_set_text(label, name);
	lv_obj_set_style_pad_ver(label, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_hor(label, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);
	lv_label_set_recolor(label, true);

	return obj;
}

lv_obj_t *create_plugin_list_version_item(lv_obj_t *parent, const char *name) {
	auto obj = create_plugin_list_item(parent, name);
	lv_obj_set_style_border_width(obj, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_hor(obj, 8, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_ver(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_ver(obj, 0, LV_STATE_FOCUSED);
	lv_obj_set_style_pad_ver(obj, 0, LV_STATE_FOCUS_KEY);
	return obj;
}

lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name) {
	lv_color_t circle_bgcolor;
	lv_color_t circle_bordercolor;
	unsigned circle_borderwidth = 0;

	if (type == JackMapType::Input) {
		circle_bgcolor = Gui::jack_palette[panel_jack_id % Gui::jack_palette.size()];
		circle_bordercolor = lv_color_black();
		circle_borderwidth = 0;
	} else {
		circle_bgcolor = lv_color_make_rgb565(0x88, 0x88, 0x88);
		circle_bordercolor = Gui::jack_palette[panel_jack_id % Gui::jack_palette.size()];
		circle_borderwidth = 2;
	}

	auto letter_color = panel_jack_id == 6 ? lv_color_white() : lv_color_make_rgb565(0x11, 0x11, 0x11);

	std::string letterchar = "";
	if (type == JackMapType::Input) {
		letterchar = get_panel_brief_name(JackInput{}, panel_jack_id);
	} else if (type == JackMapType::Output) {
		letterchar = get_panel_brief_name(JackOutput{}, panel_jack_id);
	}

	auto font = letterchar.size() > 1 ? &ui_font_MuseoSansRounded70014 : &ui_font_MuseoSansRounded70016;

	lv_obj_t *cont = lv_obj_create(parent);
	lv_obj_remove_style_all(cont);
	lv_obj_set_width(cont, 148);
	lv_obj_set_height(cont, LV_SIZE_CONTENT);
	lv_obj_set_align(cont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_add_flag(cont,
					LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_OVERFLOW_VISIBLE |
						LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_obj_clear_flag(cont,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_radius(cont, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(cont, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(cont, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(cont, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(cont, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(cont, 1, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(cont, 2, LV_STATE_FOCUSED);

	auto circle_width = letterchar.length() > 1 ? 30 : 20;
	lv_obj_t *circle = lv_btn_create(cont);
	lv_obj_set_width(circle, circle_width);
	lv_obj_set_height(circle, 20);
	lv_obj_set_x(circle, 0);
	lv_obj_set_y(circle, 31);
	lv_obj_set_align(circle, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(circle,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_radius(circle, 6, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(circle, circle_bgcolor, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(circle, 255, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(circle, circle_borderwidth, LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(circle, LV_OPA_100, LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(circle, circle_bordercolor, LV_STATE_DEFAULT);

	lv_obj_t *letter = lv_label_create(circle);
	lv_obj_set_width(letter, LV_SIZE_CONTENT);
	lv_obj_set_height(letter, LV_SIZE_CONTENT);
	lv_obj_set_align(letter, LV_ALIGN_CENTER);
	lv_label_set_text(letter, letterchar.data());
	lv_obj_clear_flag(letter,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
						  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
						  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_text_color(letter, letter_color, LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(letter, 255, LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(letter, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(letter, font, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(letter, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(letter, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(letter, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(letter, 2, LV_STATE_DEFAULT);

	lv_obj_t *label = lv_label_create(cont);
	lv_obj_set_width(label, 120);
	lv_obj_set_height(label, LV_SIZE_CONTENT);
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
	lv_label_set_text(label, name);

	return cont;
}

lv_obj_t *create_automap_item(lv_obj_t *parent, std::string_view name) {
	lv_obj_t *obj = lv_obj_create(parent);
	lv_obj_remove_style_all(obj);
	lv_obj_set_width(obj, 100);
	lv_obj_set_height(obj, 22);
	lv_obj_set_align(obj, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_pad_row(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto automap_switch = lv_switch_create(obj);
	lv_obj_set_width(automap_switch, 19);
	lv_obj_set_height(automap_switch, 18);
	lv_obj_set_align(automap_switch, LV_ALIGN_CENTER);
	lv_obj_add_state(automap_switch, LV_STATE_CHECKED); /// States
	lv_obj_set_style_radius(automap_switch, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(automap_switch, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(automap_switch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(automap_switch, lv_color_hex(0x888888), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(automap_switch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(automap_switch, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(automap_switch, lv_color_hex(0x333333), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(automap_switch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(automap_switch, lv_color_hex(0x333333), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(automap_switch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(automap_switch, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(automap_switch, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(automap_switch, lv_color_hex(0xFD8B18), LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(automap_switch, 255, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_width(automap_switch, 0, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_pad(automap_switch, 0, LV_PART_KNOB | LV_STATE_CHECKED);

	auto automap_label = lv_label_create(obj);
	lv_obj_set_width(automap_label, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(automap_label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(automap_label, LV_ALIGN_CENTER);
	lv_label_set_text(automap_label, name.data());
	lv_obj_set_style_text_font(automap_label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
	return obj;
}

lv_obj_t *create_labeled_check_obj(lv_obj_t *parent, const char *name) {
	auto check_panel = lv_obj_create(parent);
	lv_obj_set_height(check_panel, 20);
	lv_obj_set_width(check_panel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(check_panel, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(check_panel, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(check_panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_add_flag(check_panel, LV_OBJ_FLAG_OVERFLOW_VISIBLE); /// Flags
	lv_obj_clear_flag(check_panel,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_scrollbar_mode(check_panel, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(check_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(check_panel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
	auto label = lv_label_create(check_panel);
	lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_label_set_text(label, name);
	lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	auto check = lv_switch_create(check_panel);
	lv_obj_set_width(check, 35);
	lv_obj_set_height(check, 20);
	lv_obj_set_align(check, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(check, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
	lv_obj_clear_flag(check, LV_OBJ_FLAG_GESTURE_BUBBLE); /// Flags
	lv_obj_set_style_radius(check, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(check, 200, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);

	lv_obj_set_style_radius(check, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(check, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(check, -4, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(check, -6, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(check, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(check, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	return check_panel;
}

lv_obj_t *create_lv_list_button(lv_obj_t *parent, const char *name) {
	const auto out = lv_btn_create(parent);
	lv_obj_set_height(out, 25);
	lv_obj_set_width(out, lv_pct(100));
	lv_obj_set_align(out, LV_ALIGN_CENTER);
	lv_obj_clear_flag(out,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(out, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(out, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(out, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(out, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(out, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(out, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(out, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

	const auto label = lv_label_create(out);
	lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
	lv_label_set_text(label, name);

	return out;
}

lv_obj_t *create_lv_labeled_popup(lv_obj_t *parent, const char *label_text) {
	const auto out = lv_obj_create(parent);
	lv_obj_set_width(out, LV_SIZE_CONTENT); /// 1
	lv_obj_set_height(out, 236);			/// 1
	lv_obj_set_align(out, LV_ALIGN_RIGHT_MID);
	lv_obj_set_flex_flow(out, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(out, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_add_flag(out, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(out,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
						  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(out, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(out, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(out, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(out, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(out, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(out, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(out, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(out, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(out, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(out, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(out, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

	const auto label = lv_label_create(out);
	lv_obj_set_width(label, LV_SIZE_CONTENT);
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 30
	lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
	lv_label_set_text(label, label_text);
	lv_obj_set_style_text_color(label, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(label, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(label, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(label, -4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	return out;
}

lv_obj_t *create_lv_roller(lv_obj_t *parent) {
	auto out = lv_roller_create(parent);
	lv_roller_set_options(out, "(loading)", LV_ROLLER_MODE_NORMAL);
	lv_obj_set_height(out, 180);
	lv_obj_set_width(out, 200);
	lv_obj_set_align(out, LV_ALIGN_CENTER);
	lv_obj_clear_flag(out,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_style_text_color(out, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(out, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(out, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(out, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(out, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(out, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(out, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(out, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(out, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(out, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(out, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(out, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(out, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

	lv_obj_set_style_text_color(out, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(out, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(out, lv_color_hex(0xFD8B18), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(out, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(out, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(out, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(out, LV_BORDER_SIDE_NONE, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(out, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(out, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(out, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_blend_mode(out, LV_BLEND_MODE_NORMAL, LV_PART_SELECTED | LV_STATE_DEFAULT);
	return out;
}

lv_obj_t *create_button(lv_obj_t *parent, const char *name) {

	lv_obj_t *button = lv_btn_create(parent);
	lv_obj_set_height(button, 30);
	lv_obj_set_width(button, LV_SIZE_CONTENT);
	lv_obj_set_align(button, LV_ALIGN_CENTER);
	lv_obj_clear_flag(button,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_radius(button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(button, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_hor(button, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_outline_color(button, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(button, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(button, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

	lv_obj_t *label = lv_label_create(button);
	lv_obj_set_width(label, LV_SIZE_CONTENT);
	lv_obj_set_height(label, LV_SIZE_CONTENT);
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	lv_label_set_text(label, name);
	lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);

	return button;
}

lv_obj_t *create_settings_menu_title(lv_obj_t *parent, std::string const &title_name) {
	auto label = lv_label_create(parent);
	lv_obj_set_width(label, lv_pct(100));
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
	lv_label_set_text(label, title_name.c_str());
	lv_obj_set_style_text_color(label, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(label, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(label, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(label, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	return label;
}

lv_obj_t *create_settings_menu_switch(lv_obj_t *parent,
									  std::string const &onoff_label_text) { //, std::string const &slider_text) {
	auto cont = lv_obj_create(parent);
	lv_obj_set_height(cont, 25);
	lv_obj_set_width(cont, lv_pct(100));
	lv_obj_set_align(cont, LV_ALIGN_RIGHT_MID);
	lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(cont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(cont, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(cont, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(cont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(cont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(cont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(cont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto onoff_label = lv_label_create(cont);
	lv_obj_set_width(onoff_label, LV_SIZE_CONTENT);	 /// 1
	lv_obj_set_height(onoff_label, LV_SIZE_CONTENT); /// 1
	lv_label_set_text(onoff_label, onoff_label_text.c_str());
	lv_obj_set_style_text_color(onoff_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(onoff_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto onoff_switch = lv_switch_create(cont);
	lv_obj_set_width(onoff_switch, 35);
	lv_obj_set_height(onoff_switch, 20);
	lv_obj_set_align(onoff_switch, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(onoff_switch, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(onoff_switch,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_style_radius(onoff_switch, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(onoff_switch, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(onoff_switch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(onoff_switch, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(onoff_switch, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(onoff_switch, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(onoff_switch, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(onoff_switch, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(onoff_switch, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(onoff_switch, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(onoff_switch, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(
		onoff_switch, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(onoff_switch, 200, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(onoff_switch, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(onoff_switch, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);

	lv_obj_set_style_radius(onoff_switch, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(onoff_switch, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(onoff_switch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(onoff_switch, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(onoff_switch, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(onoff_switch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(onoff_switch, -4, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(onoff_switch, -6, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(onoff_switch, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(onoff_switch, -5, LV_PART_KNOB | LV_STATE_DEFAULT);

	return cont;
}

lv_obj_t *create_settings_menu_slider(lv_obj_t *parent, std::string const &slider_text) {
	auto slider_label = lv_label_create(parent);
	lv_obj_set_height(slider_label, 22);
	lv_obj_set_width(slider_label, lv_pct(88));
	lv_obj_set_align(slider_label, LV_ALIGN_CENTER);
	lv_label_set_text(slider_label, slider_text.c_str());
	lv_obj_add_flag(slider_label, LV_OBJ_FLAG_OVERFLOW_VISIBLE); /// Flags
	lv_obj_clear_flag(slider_label,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_text_color(slider_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(slider_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(slider_label, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(slider_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(slider_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(slider_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(slider_label, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(slider_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(slider_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(slider_label, lv_color_hex(0xAAAAAA), LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_opa(slider_label, 255, LV_PART_MAIN | LV_STATE_DISABLED);

	auto slider = lv_slider_create(slider_label);
	lv_slider_set_value(slider, 50, LV_ANIM_OFF);
	if (lv_slider_get_mode(slider) == LV_SLIDER_MODE_RANGE)
		lv_slider_set_left_value(slider, 0, LV_ANIM_OFF);
	lv_obj_set_height(slider, 20);
	lv_obj_set_width(slider, lv_pct(58));
	lv_obj_set_align(slider, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(slider, LV_OBJ_FLAG_SCROLL_ON_FOCUS);							/// Flags
	lv_obj_clear_flag(slider, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE); /// Flags
	lv_obj_set_style_radius(slider, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(slider, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(slider, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(slider, 200, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	lv_obj_set_style_outline_color(
		slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_USER_1);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_MAIN | LV_STATE_USER_1);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_MAIN | LV_STATE_USER_1);
	lv_obj_set_style_outline_pad(slider, 1, LV_PART_MAIN | LV_STATE_USER_1);

	lv_obj_set_style_radius(slider, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(slider, lv_color_hex(0x202328), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(slider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(slider, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(slider, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider, 20, LV_PART_INDICATOR | LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xFD8B18), LV_PART_INDICATOR | LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_INDICATOR | LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0x4165D5), LV_PART_INDICATOR | LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(slider, 128, LV_PART_INDICATOR | LV_STATE_DISABLED);
	lv_obj_set_style_border_color(slider, lv_color_hex(0x404040), LV_PART_INDICATOR | LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(slider, 255, LV_PART_INDICATOR | LV_STATE_DISABLED);
	lv_obj_set_style_radius(slider, 20, LV_PART_INDICATOR | LV_STATE_USER_1);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xFD8B18), LV_PART_INDICATOR | LV_STATE_USER_1);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_INDICATOR | LV_STATE_USER_1);

	lv_obj_set_style_radius(slider, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(slider, lv_color_hex(0x202328), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(slider, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(slider, LV_BORDER_SIDE_FULL, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0x202328), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(slider, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(slider, -3, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(slider, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(slider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xB4B2B4), LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_border_color(slider, lv_color_hex(0x404040), LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(slider, 255, LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_outline_color(slider, lv_color_hex(0x404040), LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_outline_opa(slider, 255, LV_PART_KNOB | LV_STATE_DISABLED);
	lv_obj_set_style_radius(slider, 15, LV_PART_KNOB | LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xEEEEEE), LV_PART_KNOB | LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_KNOB | LV_STATE_FOCUSED);
	lv_obj_set_style_radius(slider, 15, LV_PART_KNOB | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(slider, lv_color_hex(0xEEEEEE), LV_PART_KNOB | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(slider, 255, LV_PART_KNOB | LV_STATE_FOCUS_KEY);

	return slider_label;
}

lv_obj_t *create_midi_map_check(lv_obj_t *parent) {
	auto check = lv_switch_create(parent);
	lv_obj_set_width(check, 19);
	lv_obj_set_height(check, 18);
	lv_obj_set_align(check, LV_ALIGN_CENTER);
	lv_obj_add_flag(check, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK); /// Flags
	lv_obj_set_style_radius(check, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(check, lv_color_hex(0xDDDDDD), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(check, lv_color_hex(0x333333), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(check, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0xDDDDDD), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(check, 2, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(check, 2, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);

	lv_obj_set_style_radius(check, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x333333), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0xFD8B18), LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_width(check, 0, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_pad(check, 0, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(check, lv_color_hex(0xFD8B18), LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(check, 255, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(check, 1, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(check, 1, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(check, -1, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(check, 0, LV_PART_KNOB | LV_STATE_CHECKED);

	return check;
}

lv_obj_t *create_midi_map_label(lv_obj_t *parent, std::string const &title) {
	auto label = lv_label_create(parent);
	lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	lv_label_set_text(label, title.data());
	return label;
}

lv_obj_t *create_midi_map_dropdown(lv_obj_t *parent, std::string const &options) {
	auto dropdown = lv_dropdown_create(parent);
	lv_dropdown_set_dir(dropdown, LV_DIR_BOTTOM);
	lv_dropdown_set_options(dropdown, options.c_str());
	lv_obj_set_width(dropdown, 60);
	lv_obj_set_height(dropdown, 36);
	lv_obj_set_align(dropdown, LV_ALIGN_CENTER);
	lv_obj_add_flag(dropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_set_style_bg_color(dropdown, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(dropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto list = lv_dropdown_get_list(dropdown);
	lv_obj_set_style_text_letter_space(list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(list, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(list, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(list, lv_color_hex(0xFB8B18), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(list, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(list, lv_color_hex(0xFB8B18), LV_PART_SELECTED | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(list, 255, LV_PART_SELECTED | LV_STATE_CHECKED);

	lv_obj_add_style(dropdown, &Gui::dropdown_style, LV_PART_MAIN);
	lv_obj_add_style(dropdown, &Gui::dropdown_style_selected, LV_PART_SELECTED);
	lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY);
	lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY | LV_STATE_PRESSED);
	lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_EDITED);

	// lv_obj_set_style_pad_ver(dropdown, 8, LV_PART_MAIN);
	// lv_obj_set_style_border_width(dropdown, 0, LV_PART_MAIN);
	// lv_obj_set_style_bg_color(dropdown, lv_color_hex(0x999999), LV_PART_MAIN);
	lv_obj_set_style_text_font(dropdown, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);

	return dropdown;
}

} // namespace MetaModule
