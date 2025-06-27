
#include "lvgl.h"
#include "meta5/ui.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsMidiTitle;
lv_obj_t *ui_SystemPrefsMidiFeedbackCont;
lv_obj_t *ui_SystemPrefsMidiFeedbackLabel;
lv_obj_t *ui_SystemPrefsMidiFeedbackCheck;

void init_SystemPrefsMidiPane(lv_obj_t *parentTab) {

	ui_SystemPrefsMidiTitle = lv_label_create(parentTab);
	lv_obj_set_width(ui_SystemPrefsMidiTitle, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsMidiTitle, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMidiTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsMidiTitle, "MIDI");
	lv_obj_set_style_text_color(ui_SystemPrefsMidiTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui_SystemPrefsMidiTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_text_font(ui_SystemPrefsMidiTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui_SystemPrefsMidiTitle, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui_SystemPrefsMidiTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui_SystemPrefsMidiTitle, 2, LV_PART_MAIN);
	lv_obj_set_style_border_side(ui_SystemPrefsMidiTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui_SystemPrefsMidiTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsMidiTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsMidiTitle, 6, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsMidiTitle, 2, LV_PART_MAIN);

	ui_SystemPrefsMidiFeedbackCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsMidiFeedbackCont);
	lv_obj_set_width(ui_SystemPrefsMidiFeedbackCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsMidiFeedbackCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMidiFeedbackCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsMidiFeedbackCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(
		ui_SystemPrefsMidiFeedbackCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsMidiFeedbackCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsMidiFeedbackCont, 2, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsMidiFeedbackCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsMidiFeedbackCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsMidiFeedbackCont, 4, LV_PART_MAIN);

	ui_SystemPrefsMidiFeedbackLabel = lv_label_create(ui_SystemPrefsMidiFeedbackCont);
	lv_obj_set_width(ui_SystemPrefsMidiFeedbackLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsMidiFeedbackLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMidiFeedbackLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsMidiFeedbackLabel, "Enable Feedback:");
	lv_obj_set_style_text_font(ui_SystemPrefsMidiFeedbackLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);

	ui_SystemPrefsMidiFeedbackCheck = lv_switch_create(ui_SystemPrefsMidiFeedbackCont);
	lv_obj_set_width(ui_SystemPrefsMidiFeedbackCheck, 35);
	lv_obj_set_height(ui_SystemPrefsMidiFeedbackCheck, 20);
	lv_obj_set_align(ui_SystemPrefsMidiFeedbackCheck, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(ui_SystemPrefsMidiFeedbackCheck, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(ui_SystemPrefsMidiFeedbackCheck,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_style_radius(ui_SystemPrefsMidiFeedbackCheck, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_SystemPrefsMidiFeedbackCheck, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsMidiFeedbackCheck, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsMidiFeedbackCheck, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsMidiFeedbackCheck, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui_SystemPrefsMidiFeedbackCheck, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui_SystemPrefsMidiFeedbackCheck, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsMidiFeedbackCheck, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui_SystemPrefsMidiFeedbackCheck, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui_SystemPrefsMidiFeedbackCheck, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui_SystemPrefsMidiFeedbackCheck, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

	lv_obj_set_style_bg_color(
		ui_SystemPrefsMidiFeedbackCheck, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_SystemPrefsMidiFeedbackCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_bg_color(ui_SystemPrefsMidiFeedbackCheck, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsMidiFeedbackCheck, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_SystemPrefsMidiFeedbackCheck, -4, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsMidiFeedbackCheck, -6, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsMidiFeedbackCheck, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsMidiFeedbackCheck, -5, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_obj_t *note = lv_label_create(ui_SystemPrefsMidiFeedbackCont);
	lv_obj_set_height(note, LV_SIZE_CONTENT);
	lv_obj_set_width(note, LV_SIZE_CONTENT);
	lv_obj_add_flag(note, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

	lv_label_set_text(note, "Sends MIDI to controller\nwhen MIDI-mapped parameters\nchange");
	lv_obj_set_style_text_color(note, lv_color_hex(0xBBBBBB), LV_PART_MAIN);
	lv_obj_set_style_text_opa(note, 255, LV_PART_MAIN);
	lv_obj_set_style_text_font(note, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
	lv_obj_set_style_border_width(note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(note, 0, LV_PART_MAIN);

	lv_obj_t *spacer1 = lv_obj_create(ui_SystemPrefsMidiFeedbackCont);
	lv_obj_set_size(spacer1, 1, 1);
	lv_obj_set_style_bg_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_outline_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
}

} // namespace MetaModule
