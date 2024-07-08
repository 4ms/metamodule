#include "ui_local.h"
#include "conf/panel_conf.hh"
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
	lv_obj_set_style_pad_left(obj, 6, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(obj, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(obj, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(obj, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(obj, 1, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(obj, 255, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(obj, 2, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(obj, 1, LV_STATE_FOCUS_KEY);

	lv_obj_t *label = lv_label_create(obj);
	lv_obj_set_width(label, lv_pct(100));
	lv_obj_set_height(label, LV_SIZE_CONTENT);
	lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
	lv_label_set_text(label, name);
	lv_obj_set_style_pad_all(label, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

	return obj;
}

lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name) {
	lv_color_t circle_bgcolor;
	lv_color_t circle_bordercolor;
	unsigned circle_borderwidth = 0;

	if (type == JackMapType::Input) {
		circle_bgcolor = panel_jack_id < Gui::jack_palette.size() ? Gui::jack_palette[panel_jack_id] :
																	lv_color_make_rgb565(0x80, 0x80, 0x80);
		circle_bordercolor = lv_color_black();
		circle_borderwidth = 0;
	} else {
		circle_bgcolor = lv_color_make_rgb565(0x88, 0x88, 0x88);
		circle_bordercolor = panel_jack_id < Gui::jack_palette.size() ? Gui::jack_palette[panel_jack_id] :
																		lv_color_make_rgb565(0x44, 0x44, 0x44);
		circle_borderwidth = 2;
	}

	auto letter_color = panel_jack_id == 6 ? lv_color_white() : lv_color_make_rgb565(0x11, 0x11, 0x11);

	std::string_view letterchar = "";
	if (type == JackMapType::Input && panel_jack_id < PanelDef::InJackAbbrev.size()) {
		letterchar = PanelDef::InJackAbbrev[panel_jack_id];
	} else if (type == JackMapType::Output && panel_jack_id < PanelDef::OutJackAbbrevs.size()) {
		letterchar = PanelDef::OutJackAbbrevs[panel_jack_id];
	}

	auto font = letterchar.size() > 1 ? &ui_font_MuseoSansRounded70014 : &ui_font_MuseoSansRounded70016;

	lv_obj_t *cont = lv_obj_create(parent);
	lv_obj_remove_style_all(cont);
	lv_obj_set_width(cont, 148);
	lv_obj_set_height(cont, LV_SIZE_CONTENT);
	lv_obj_set_align(cont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_add_flag(cont, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
	lv_obj_clear_flag(cont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_radius(cont, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(cont, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(cont, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(cont, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(cont, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(cont, 1, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(cont, 2, LV_STATE_FOCUSED);

	lv_obj_t *circle = lv_btn_create(cont);
	lv_obj_set_width(circle, 20);
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

	ui_AutoMapItemContSwitch = lv_switch_create(obj);
	lv_obj_set_width(ui_AutoMapItemContSwitch, 19);
	lv_obj_set_height(ui_AutoMapItemContSwitch, 18);
	lv_obj_set_align(ui_AutoMapItemContSwitch, LV_ALIGN_CENTER);
	lv_obj_add_state(ui_AutoMapItemContSwitch, LV_STATE_CHECKED); /// States
	lv_obj_set_style_radius(ui_AutoMapItemContSwitch, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_AutoMapItemContSwitch, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_AutoMapItemContSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(ui_AutoMapItemContSwitch, lv_color_hex(0x888888), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_AutoMapItemContSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(ui_AutoMapItemContSwitch, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_AutoMapItemContSwitch, lv_color_hex(0x333333), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_AutoMapItemContSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_AutoMapItemContSwitch, lv_color_hex(0x333333), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_AutoMapItemContSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui_AutoMapItemContSwitch, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui_AutoMapItemContSwitch, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_AutoMapItemContSwitch, lv_color_hex(0xFD8B18), LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_AutoMapItemContSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_width(ui_AutoMapItemContSwitch, 0, LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_outline_pad(ui_AutoMapItemContSwitch, 0, LV_PART_KNOB | LV_STATE_CHECKED);

	ui_AutoMapItemContLabel = lv_label_create(obj);
	lv_obj_set_width(ui_AutoMapItemContLabel, LV_SIZE_CONTENT);	 /// 1
	lv_obj_set_height(ui_AutoMapItemContLabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_AutoMapItemContLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_AutoMapItemContLabel, "Pitch");
	lv_obj_set_style_text_font(
		ui_AutoMapItemContLabel, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
	return obj;
}

} // namespace MetaModule
