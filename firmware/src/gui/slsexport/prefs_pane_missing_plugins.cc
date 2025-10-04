#include "lvgl.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsMissingPluginsTitle;
lv_obj_t *ui_SystemPrefsMissingPluginsCont;
lv_obj_t *ui_SystemPrefsMissingPluginsLabel;
lv_obj_t *ui_SystemPrefsMissingPluginsDropdown;

void init_SystemPrefsMissingPluginsPane(lv_obj_t *parentTab) {
	// Section title
	ui_SystemPrefsMissingPluginsTitle = lv_label_create(parentTab);
	lv_obj_set_width(ui_SystemPrefsMissingPluginsTitle, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsMissingPluginsTitle, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMissingPluginsTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsMissingPluginsTitle, "MISSING PLUGINS");
	lv_obj_set_style_text_color(ui_SystemPrefsMissingPluginsTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_SystemPrefsMissingPluginsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(
		ui_SystemPrefsMissingPluginsTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_SystemPrefsMissingPluginsTitle, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_SystemPrefsMissingPluginsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_SystemPrefsMissingPluginsTitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_SystemPrefsMissingPluginsTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_SystemPrefsMissingPluginsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsMissingPluginsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsMissingPluginsTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsMissingPluginsTitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Row container
	ui_SystemPrefsMissingPluginsCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsMissingPluginsCont);
	lv_obj_set_width(ui_SystemPrefsMissingPluginsCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsMissingPluginsCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMissingPluginsCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsMissingPluginsCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(
		ui_SystemPrefsMissingPluginsCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsMissingPluginsCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsMissingPluginsCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsMissingPluginsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsMissingPluginsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsMissingPluginsCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsMissingPluginsLabel = lv_label_create(ui_SystemPrefsMissingPluginsCont);
	lv_obj_set_width(ui_SystemPrefsMissingPluginsLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsMissingPluginsLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMissingPluginsLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsMissingPluginsLabel, "Automatically load missing plugins:");
	lv_obj_set_style_text_font(
		ui_SystemPrefsMissingPluginsLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Spacer to move dropdown to next track
	lv_obj_t *sp1 = lv_obj_create(ui_SystemPrefsMissingPluginsCont);
	lv_obj_set_height(sp1, 1);
	lv_obj_set_width(sp1, 1);
	lv_obj_set_style_bg_opa(sp1, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(sp1, LV_OPA_0, LV_PART_MAIN);

	lv_obj_t *sp2 = lv_obj_create(ui_SystemPrefsMissingPluginsCont);
	lv_obj_set_height(sp2, 55);
	lv_obj_set_width(sp2, 1);
	lv_obj_add_flag(sp2, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
	lv_obj_set_style_bg_opa(sp2, LV_OPA_0, LV_PART_MAIN);
	lv_obj_set_style_border_opa(sp2, LV_OPA_0, LV_PART_MAIN);

	ui_SystemPrefsMissingPluginsDropdown = lv_dropdown_create(ui_SystemPrefsMissingPluginsCont);
	lv_dropdown_set_options(ui_SystemPrefsMissingPluginsDropdown, "Ask\nAlways\nNever");
	lv_dropdown_set_dir(ui_SystemPrefsMissingPluginsDropdown, LV_DIR_BOTTOM);
	lv_obj_set_width(ui_SystemPrefsMissingPluginsDropdown, 185);
	lv_obj_set_height(ui_SystemPrefsMissingPluginsDropdown, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsMissingPluginsDropdown, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsMissingPluginsDropdown,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_text_font(
		ui_SystemPrefsMissingPluginsDropdown, &ui_font_MuseoSansRounded70014, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(
		ui_SystemPrefsMissingPluginsDropdown, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SystemPrefsMissingPluginsDropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsMissingPluginsDropdown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_EDITED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsMissingPluginsDropdown, 0, LV_PART_MAIN | LV_STATE_EDITED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsMissingPluginsDropdown, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui_SystemPrefsMissingPluginsDropdown, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui_SystemPrefsMissingPluginsDropdown, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui_SystemPrefsMissingPluginsDropdown, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(
		ui_SystemPrefsMissingPluginsDropdown, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui_SystemPrefsMissingPluginsDropdown, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
}

} // namespace MetaModule

