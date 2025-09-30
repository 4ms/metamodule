
#include "lvgl.h"
#include "meta5/ui.h"
#include "ui_local.h"

namespace MetaModule
{

lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCont;
lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateLabel;
lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCheck;
lv_obj_t *ui_SystemPrefsPatchSuggestSROverrideCont;
lv_obj_t *ui_SystemPrefsPatchSuggestSROverrideLabel;

lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCont;
lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeLabel;
lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCheck;
lv_obj_t *ui_SystemPrefsPatchSuggestBSOverrideCont;
lv_obj_t *ui_SystemPrefsPatchSuggestBSOverrideLabel;

void init_SystemPrefsPatchSuggestedAudioPane(lv_obj_t *parentTab) {
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
	lv_obj_set_style_border_width(ui_SystemPrefsPatchSuggestSampleRateCont, 1, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui_SystemPrefsPatchSuggestSampleRateCont, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui_SystemPrefsPatchSuggestSampleRateCont, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestSampleRateLabel = lv_label_create(ui_SystemPrefsPatchSuggestSampleRateCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestSampleRateLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestSampleRateLabel, "Allow patch to override:");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestSampleRateLabel, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestSampleRateCheck = create_prefs_check(ui_SystemPrefsPatchSuggestSampleRateCont);

	// Patch Samplerate Override row:
	ui_SystemPrefsPatchSuggestSROverrideCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsPatchSuggestSROverrideCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestSROverrideCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsPatchSuggestSROverrideCont, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SystemPrefsPatchSuggestSROverrideCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsPatchSuggestSROverrideCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_SystemPrefsPatchSuggestSROverrideCont,
						  LV_FLEX_ALIGN_SPACE_BETWEEN,
						  LV_FLEX_ALIGN_CENTER,
						  LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsPatchSuggestSROverrideCont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_pad_left(ui_SystemPrefsPatchSuggestSROverrideCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestSROverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsPatchSuggestSROverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsPatchSuggestSROverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto sr_title = lv_label_create(ui_SystemPrefsPatchSuggestSROverrideCont);
	lv_obj_set_width(sr_title, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(sr_title, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(sr_title, LV_ALIGN_CENTER);
	lv_label_set_text(sr_title, "Patch override:");
	lv_obj_set_style_text_font(sr_title, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsPatchSuggestSROverrideLabel = lv_label_create(ui_SystemPrefsPatchSuggestSROverrideCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestSROverrideLabel, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_SystemPrefsPatchSuggestSROverrideLabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SystemPrefsPatchSuggestSROverrideLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestSROverrideLabel, "32kHz");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestSROverrideLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestSROverrideLabel, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

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
	lv_obj_set_style_border_width(ui_SystemPrefsPatchSuggestBlocksizeCont, 1, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui_SystemPrefsPatchSuggestBlocksizeCont, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui_SystemPrefsPatchSuggestBlocksizeCont, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestBlocksizeLabel = lv_label_create(ui_SystemPrefsPatchSuggestBlocksizeCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_SIZE_CONTENT);
	lv_obj_set_align(ui_SystemPrefsPatchSuggestBlocksizeLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestBlocksizeLabel, "Allow patch to override:");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestBlocksizeLabel, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);

	ui_SystemPrefsPatchSuggestBlocksizeCheck = create_prefs_check(ui_SystemPrefsPatchSuggestBlocksizeCont);

	// Patch Blocksize Override row:
	ui_SystemPrefsPatchSuggestBSOverrideCont = lv_obj_create(parentTab);
	lv_obj_remove_style_all(ui_SystemPrefsPatchSuggestBSOverrideCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestBSOverrideCont, lv_pct(100));
	lv_obj_set_height(ui_SystemPrefsPatchSuggestBSOverrideCont, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SystemPrefsPatchSuggestBSOverrideCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_SystemPrefsPatchSuggestBSOverrideCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_SystemPrefsPatchSuggestBSOverrideCont,
						  LV_FLEX_ALIGN_SPACE_BETWEEN,
						  LV_FLEX_ALIGN_CENTER,
						  LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SystemPrefsPatchSuggestBSOverrideCont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_pad_left(ui_SystemPrefsPatchSuggestBSOverrideCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestBSOverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SystemPrefsPatchSuggestBSOverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SystemPrefsPatchSuggestBSOverrideCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	auto bs_title = lv_label_create(ui_SystemPrefsPatchSuggestBSOverrideCont);
	lv_obj_set_width(bs_title, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(bs_title, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(bs_title, LV_ALIGN_CENTER);
	lv_label_set_text(bs_title, "Patch override:");
	lv_obj_set_style_text_font(bs_title, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SystemPrefsPatchSuggestBSOverrideLabel = lv_label_create(ui_SystemPrefsPatchSuggestBSOverrideCont);
	lv_obj_set_width(ui_SystemPrefsPatchSuggestBSOverrideLabel, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_SystemPrefsPatchSuggestBSOverrideLabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SystemPrefsPatchSuggestBSOverrideLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_SystemPrefsPatchSuggestBSOverrideLabel, "256");
	lv_obj_set_style_text_font(ui_SystemPrefsPatchSuggestBSOverrideLabel, &ui_font_MuseoSansRounded70016, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui_SystemPrefsPatchSuggestBSOverrideLabel, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
}

} // namespace MetaModule
