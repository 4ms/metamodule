
#include "lvgl.h"
#include "meta5/ui.h"
#include "ui_local.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsPatchSuggestTitle;
lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCont;
lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateLabel;
lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCheck;

lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCont;
lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeLabel;
lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCheck;

void init_SystemPrefsPatchSuggestedAudioPane(lv_obj_t *parentTab) {
	// Title
	ui_SystemPrefsPatchSuggestTitle = lv_label_create(parentTab);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestTitle, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsPatchSuggestTitle, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestTitle, "Patch Audio Suggestions");
	lv_obj_set_style_text_color(ui_SystemPrefsPatchSuggestTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui_SystemPrefsPatchSuggestTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui_SystemPrefsPatchSuggestTitle, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui_SystemPrefsPatchSuggestTitle, 255, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui_SystemPrefsPatchSuggestTitle, 2, LV_PART_MAIN);
	lv_obj_set_style_border_side(ui_SystemPrefsPatchSuggestTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui_SystemPrefsPatchSuggestTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestTitle, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsPatchSuggestTitle, 6, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsPatchSuggestTitle, 2, LV_PART_MAIN);

	// Samplerate row
	ui_SystemPrefsPatchSuggestSampleRateCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsPatchSuggestSampleRateCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestSampleRateCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsPatchSuggestSampleRateCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestSampleRateCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsPatchSuggestSampleRateCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_SystemPrefsPatchSuggestSampleRateCont,
						  LV_FLEX_ALIGN_SPACE_BETWEEN,
						  LV_FLEX_ALIGN_CENTER,
						  LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsPatchSuggestSampleRateCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsPatchSuggestSampleRateCont, 2, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestSampleRateCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsPatchSuggestSampleRateCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsPatchSuggestSampleRateCont, 4, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestSampleRateLabel = lv_label_create(ui_SystemPrefsPatchSuggestSampleRateCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestSampleRateLabel, "Apply samplerate:");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestSampleRateLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestSampleRateCheck = create_prefs_check(ui_SystemPrefsPatchSuggestSampleRateCont);

	// Blocksize row
	ui_SystemPrefsPatchSuggestBlocksizeCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsPatchSuggestBlocksizeCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestBlocksizeCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsPatchSuggestBlocksizeCont, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestBlocksizeCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsPatchSuggestBlocksizeCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_SystemPrefsPatchSuggestBlocksizeCont,
						  LV_FLEX_ALIGN_SPACE_BETWEEN,
						  LV_FLEX_ALIGN_CENTER,
						  LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsPatchSuggestBlocksizeCont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_pad_left(ui_SystemPrefsPatchSuggestBlocksizeCont, 2, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestBlocksizeCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui_SystemPrefsPatchSuggestBlocksizeCont, 4, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsPatchSuggestBlocksizeCont, 4, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestBlocksizeLabel = lv_label_create(ui_SystemPrefsPatchSuggestBlocksizeCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestBlocksizeLabel, "Apply blocksize:");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestBlocksizeLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestBlocksizeCheck = create_prefs_check(ui_SystemPrefsPatchSuggestBlocksizeCont);
}

} // namespace MetaModule
