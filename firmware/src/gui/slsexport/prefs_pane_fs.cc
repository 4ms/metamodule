#include "lvgl.h"
#include "meta5/ui.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsFSTitle;
lv_obj_t *ui_SystemPrefsFSMaxPatchesCont;
lv_obj_t *ui_SystemPrefsFSMaxPatchesLabel;
lv_obj_t *ui_SystemPrefsFSMaxPatchesDropdown;

void init_SystemPrefsFSPane(lv_obj_t *parentTab) {

	ui_SystemPrefsFSTitle = lv_label_create(parentTab);
	lv_obj_set_width(ui_SystemPrefsFSTitle, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsFSTitle, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsFSTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsFSTitle, "Patch Files");
	lv_obj_set_style_text_color(ui_SystemPrefsFSTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui_SystemPrefsFSTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_text_font(ui_SystemPrefsFSTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui_SystemPrefsFSTitle, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui_SystemPrefsFSTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui_SystemPrefsFSTitle, 2, LV_PART_MAIN);
	lv_obj_set_style_border_side(ui_SystemPrefsFSTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui_SystemPrefsFSTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsFSTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsFSTitle, 6, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsFSTitle, 2, LV_PART_MAIN);

	ui_SystemPrefsFSMaxPatchesCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsFSMaxPatchesCont);
	lv_obj_set_width(ui_SystemPrefsFSMaxPatchesCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsFSMaxPatchesCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsFSMaxPatchesCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsFSMaxPatchesCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(
		ui_SystemPrefsFSMaxPatchesCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsFSMaxPatchesCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsFSMaxPatchesCont, 2, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsFSMaxPatchesCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsFSMaxPatchesCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsFSMaxPatchesCont, 4, LV_PART_MAIN);

	ui_SystemPrefsFSMaxPatchesLabel = lv_label_create(ui_SystemPrefsFSMaxPatchesCont);
	lv_obj_set_width(ui_SystemPrefsFSMaxPatchesLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsFSMaxPatchesLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsFSMaxPatchesLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsFSMaxPatchesLabel, "Max Open Patches:");
	lv_obj_set_style_text_font(ui_SystemPrefsFSMaxPatchesLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);

	ui_SystemPrefsFSMaxPatchesDropdown = lv_dropdown_create(ui_SystemPrefsFSMaxPatchesCont);
	lv_dropdown_set_options(ui_SystemPrefsFSMaxPatchesDropdown, "2\n3\n4\n5\n6\n7\n8\n9\n10\n15\n20\n25");
	lv_dropdown_set_dir(ui_SystemPrefsFSMaxPatchesDropdown, LV_DIR_BOTTOM);
	lv_obj_set_width(ui_SystemPrefsFSMaxPatchesDropdown, 50);
	lv_obj_set_height(ui_SystemPrefsFSMaxPatchesDropdown, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsFSMaxPatchesDropdown, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsFSMaxPatchesDropdown,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_text_font(ui_SystemPrefsFSMaxPatchesDropdown, &ui_font_MuseoSansRounded70014, LV_PART_MAIN);
	lv_obj_set_style_pad_hor(ui_SystemPrefsFSMaxPatchesDropdown, 4, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui_SystemPrefsFSMaxPatchesDropdown, lv_color_hex(0x666666), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui_SystemPrefsFSMaxPatchesDropdown, 255, LV_PART_MAIN);
	lv_obj_set_style_outline_color(ui_SystemPrefsFSMaxPatchesDropdown, lv_color_hex(0x000000), LV_STATE_EDITED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsFSMaxPatchesDropdown, 0, LV_STATE_EDITED);
	lv_obj_set_style_outline_color(ui_SystemPrefsFSMaxPatchesDropdown, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsFSMaxPatchesDropdown, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui_SystemPrefsFSMaxPatchesDropdown, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui_SystemPrefsFSMaxPatchesDropdown, 1, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui_SystemPrefsFSMaxPatchesDropdown, lv_color_hex(0xFD8B18), LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui_SystemPrefsFSMaxPatchesDropdown, 255, LV_STATE_FOCUS_KEY);

	lv_obj_set_style_text_font(ui_SystemPrefsFSMaxPatchesDropdown, &lv_font_montserrat_14, LV_PART_INDICATOR);

	lv_obj_set_style_text_letter_space(lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), 0, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), 8, LV_PART_MAIN);
	lv_obj_set_style_bg_color(
		lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), lv_color_hex(0x666666), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), 255, LV_PART_MAIN);

	lv_obj_set_style_bg_color(
		lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), lv_color_hex(0xFD8B18), LV_PART_SELECTED);
	lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), 255, LV_PART_SELECTED);
	lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown),
							  lv_color_hex(0xFD8B18),
							  LV_PART_SELECTED | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(
		lv_dropdown_get_list(ui_SystemPrefsFSMaxPatchesDropdown), 255, LV_PART_SELECTED | LV_STATE_CHECKED);

	lv_obj_t *restart_note = lv_label_create(ui_SystemPrefsFSMaxPatchesCont);
	lv_obj_set_height(restart_note, LV_SIZE_CONTENT);
	lv_obj_set_width(restart_note, LV_SIZE_CONTENT);
	lv_obj_add_flag(restart_note, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

	lv_label_set_text(restart_note, "Takes effect after restart");
	lv_obj_set_style_text_color(restart_note, lv_color_hex(0xBBBBBB), LV_PART_MAIN);
	lv_obj_set_style_text_opa(restart_note, 255, LV_PART_MAIN);
	lv_obj_set_style_text_font(restart_note, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);
	lv_obj_set_style_border_width(restart_note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(restart_note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(restart_note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(restart_note, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(restart_note, 0, LV_PART_MAIN);

	lv_obj_t *spacer1 = lv_obj_create(ui_SystemPrefsFSMaxPatchesCont);
	lv_obj_set_size(spacer1, 1, 1);
	lv_obj_set_style_bg_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_outline_opa(spacer1, LV_OPA_0, LV_PART_MAIN);
}

} // namespace MetaModule
