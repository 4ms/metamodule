#include "lvgl.h"
// #include "meta5/ui.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsCatchupTitle;
lv_obj_t *ui_SystemPrefsCatchupModeCont;
lv_obj_t *ui_SystemPrefsCatchupModeLabel;
lv_obj_t *ui_SystemPrefsCatchupModeDropdown;
lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsCont;
lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsLabel;
lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsCheck;

void init_SystemPrefsCatchupPane(lv_obj_t *parentTab) {

	ui_SystemPrefsCatchupTitle = lv_label_create(parentTab);
	lv_obj_set_width(ui_SystemPrefsCatchupTitle, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsCatchupTitle, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsCatchupTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsCatchupTitle, "KNOB CATCHUP MODE");
	lv_obj_set_style_text_color(ui_SystemPrefsCatchupTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_SystemPrefsCatchupTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(
		ui_SystemPrefsCatchupTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_SystemPrefsCatchupTitle, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_SystemPrefsCatchupTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_SystemPrefsCatchupTitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_SystemPrefsCatchupTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_SystemPrefsCatchupTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsCatchupTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsCatchupTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsCatchupTitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsCatchupModeCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsCatchupModeCont);
	lv_obj_set_width(ui_SystemPrefsCatchupModeCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsCatchupModeCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsCatchupModeCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsCatchupModeCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(
		ui_SystemPrefsCatchupModeCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsCatchupModeCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsCatchupModeCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsCatchupModeCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsCatchupModeCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsCatchupModeCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsCatchupModeLabel = lv_label_create(ui_SystemPrefsCatchupModeCont);
	lv_obj_set_width(ui_SystemPrefsCatchupModeLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsCatchupModeLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsCatchupModeLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsCatchupModeLabel, "Default Catchup Mode:");
	lv_obj_set_style_text_font(
		ui_SystemPrefsCatchupModeLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_t *spacer1 = lv_obj_create(ui_SystemPrefsCatchupModeCont);
	lv_obj_set_height(spacer1, 1);
	lv_obj_set_width(spacer1, 1);
	lv_obj_set_style_bg_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(spacer1, LV_OPA_0, LV_PART_MAIN);

	lv_obj_t *spacer2 = lv_obj_create(ui_SystemPrefsCatchupModeCont);
	lv_obj_set_height(spacer2, 55);
	lv_obj_set_width(spacer2, 1);
	lv_obj_add_flag(spacer2, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
	lv_obj_set_style_bg_opa(spacer2, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(spacer2, LV_OPA_0, LV_PART_MAIN);

	ui_SystemPrefsCatchupModeDropdown = lv_dropdown_create(ui_SystemPrefsCatchupModeCont);
	lv_dropdown_set_options(ui_SystemPrefsCatchupModeDropdown, "Knob movement\nEqual value\nLinear fade");
	lv_dropdown_set_dir(ui_SystemPrefsCatchupModeDropdown, LV_DIR_BOTTOM);
	lv_obj_set_width(ui_SystemPrefsCatchupModeDropdown, 185);
	lv_obj_set_height(ui_SystemPrefsCatchupModeDropdown, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsCatchupModeDropdown, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsCatchupModeDropdown,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_text_font(
		ui_SystemPrefsCatchupModeDropdown, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(
		ui_SystemPrefsCatchupModeDropdown, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsCatchupModeDropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsCatchupModeDropdown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_EDITED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsCatchupModeDropdown, 0, LV_PART_MAIN | LV_STATE_EDITED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsCatchupModeDropdown, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsCatchupModeDropdown, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui_SystemPrefsCatchupModeDropdown, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui_SystemPrefsCatchupModeDropdown, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsCatchupModeDropdown, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui_SystemPrefsCatchupModeDropdown, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

	lv_obj_set_style_text_font(
		ui_SystemPrefsCatchupModeDropdown, &lv_font_montserrat_14, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_text_letter_space(
		lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown), 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(
		lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown), 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown),
							  lv_color_hex(0x666666),
							  LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(
		lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown),
							  lv_color_hex(0xFD8B18),
							  LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(
		lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown), 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown),
							  lv_color_hex(0xFD8B18),
							  LV_PART_SELECTED | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(
		lv_dropdown_get_list(ui_SystemPrefsCatchupModeDropdown), 255, LV_PART_SELECTED | LV_STATE_CHECKED);

	ui_SystemPrefsCatchupExcludeButtonsCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsCatchupExcludeButtonsCont);
	lv_obj_set_width(ui_SystemPrefsCatchupExcludeButtonsCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsCatchupExcludeButtonsCont, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SystemPrefsCatchupExcludeButtonsCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsCatchupExcludeButtonsCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_SystemPrefsCatchupExcludeButtonsCont,
						  LV_FLEX_ALIGN_SPACE_BETWEEN,
						  LV_FLEX_ALIGN_CENTER,
						  LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsCatchupExcludeButtonsCont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_pad_left(ui_SystemPrefsCatchupExcludeButtonsCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsCatchupExcludeButtonsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsCatchupExcludeButtonsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsCatchupExcludeButtonsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsCatchupExcludeButtonsLabel = lv_label_create(ui_SystemPrefsCatchupExcludeButtonsCont);
	lv_obj_set_width(ui_SystemPrefsCatchupExcludeButtonsLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsCatchupExcludeButtonsLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsCatchupExcludeButtonsLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsCatchupExcludeButtonsLabel, "Switches always track:");
	lv_obj_set_style_text_font(
		ui_SystemPrefsCatchupExcludeButtonsLabel, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsCatchupExcludeButtonsCheck = lv_switch_create(ui_SystemPrefsCatchupExcludeButtonsCont);
	lv_obj_set_width(ui_SystemPrefsCatchupExcludeButtonsCheck, 35);
	lv_obj_set_height(ui_SystemPrefsCatchupExcludeButtonsCheck, 20);
	lv_obj_set_align(ui_SystemPrefsCatchupExcludeButtonsCheck, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(ui_SystemPrefsCatchupExcludeButtonsCheck, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(ui_SystemPrefsCatchupExcludeButtonsCheck,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_style_radius(ui_SystemPrefsCatchupExcludeButtonsCheck, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(
		ui_SystemPrefsCatchupExcludeButtonsCheck, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsCatchupExcludeButtonsCheck, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsCatchupExcludeButtonsCheck, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsCatchupExcludeButtonsCheck, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui_SystemPrefsCatchupExcludeButtonsCheck, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui_SystemPrefsCatchupExcludeButtonsCheck, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsCatchupExcludeButtonsCheck, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui_SystemPrefsCatchupExcludeButtonsCheck, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui_SystemPrefsCatchupExcludeButtonsCheck, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui_SystemPrefsCatchupExcludeButtonsCheck, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui_SystemPrefsCatchupExcludeButtonsCheck,
								   lv_color_hex(0xFD8B18),
								   LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(
		ui_SystemPrefsCatchupExcludeButtonsCheck, 200, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(
		ui_SystemPrefsCatchupExcludeButtonsCheck, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(
		ui_SystemPrefsCatchupExcludeButtonsCheck, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);

	lv_obj_set_style_radius(ui_SystemPrefsCatchupExcludeButtonsCheck, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(
		ui_SystemPrefsCatchupExcludeButtonsCheck, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_SystemPrefsCatchupExcludeButtonsCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(ui_SystemPrefsCatchupExcludeButtonsCheck, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(
		ui_SystemPrefsCatchupExcludeButtonsCheck, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsCatchupExcludeButtonsCheck, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_SystemPrefsCatchupExcludeButtonsCheck, -4, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsCatchupExcludeButtonsCheck, -6, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsCatchupExcludeButtonsCheck, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsCatchupExcludeButtonsCheck, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
}

} // namespace MetaModule
