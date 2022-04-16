#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	PatchViewPage(PatchInfo info, uint32_t patch_id = 0)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		init_bg(base);

		popup_cont = lv_obj_create(base);
		lv_obj_add_style(popup_cont, &Gui::popup_box_style, LV_PART_MAIN);
		lv_obj_set_flex_flow(popup_cont, LV_FLEX_FLOW_ROW);

		popup_patchname = lv_label_create(popup_cont);
		lv_obj_add_style(popup_patchname, &Gui::header_style, LV_PART_MAIN);
		// lv_obj_set_pos(popup_patchname, 0, 0);
		// lv_obj_set_align(popup_patchname, LV_ALIGN_TOP_MID);
		lv_obj_set_size(popup_patchname, 320, 30);

		popup_desc = lv_label_create(popup_cont);
		lv_obj_add_style(popup_patchname, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_long_mode(popup_desc, LV_LABEL_LONG_DOT);
		lv_obj_set_size(popup_desc, 320, 30);

		set_patch_id(patch_id);

		// group = lv_group_create();
		// lv_group_set_wrap(group, true);
	}

	void set_patch_id(uint32_t patch_id) {
		_patch_id = patch_id;
		lv_label_set_text(popup_patchname, patch_list.get_patch_name(_patch_id));
		lv_label_set_text(popup_desc, "TODO: Patch descriptions...");
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

private:
	lv_obj_t *popup_desc;
	lv_obj_t *popup_patchname;
	lv_obj_t *popup_cont;

	lv_obj_t *base;
	uint32_t _patch_id;
};
} // namespace MetaModule
  // void setup_popup() {
  // LVGLMemory::print_mem_usage("PatchSel::setup_popup 0");
  // popup_cont = lv_obj_create(base);
  // lv_obj_add_style(popup_cont, &Gui::popup_box_style, LV_PART_MAIN);
  // lv_obj_set_flex_flow(popup_cont, LV_FLEX_FLOW_ROW);

// popup_patchname = lv_label_create(popup_cont);
// lv_obj_add_style(popup_patchname, &Gui::header_style, LV_PART_MAIN);
// // lv_obj_set_pos(popup_patchname, 0, 0);
// // lv_obj_set_align(popup_patchname, LV_ALIGN_TOP_MID);
// // lv_obj_set_size(popup_patchname, 320, 30);

// popup_desc = lv_label_create(popup_cont);
// lv_label_set_long_mode(popup_desc, LV_LABEL_LONG_DOT);
//lv_obj_add_style(popup_desc, &style_popup_desc, LV_PART_MAIN);

////Play button
//popup_playbut = lv_btn_create(popup_cont);
//lv_obj_add_style(popup_playbut, &style_popup_buttons, LV_PART_MAIN);

//// lv_obj_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xc3, 0x70)); //LV_STATE_FOCUSED,
//// lv_style_set_bg_color(&style_popup_buttons,  lv_color_make(0xf6, 0xdd, 0x53));//LV_STATE_PRESSED,
//popup_playbut_label = lv_label_create(popup_playbut);
//lv_label_set_text(popup_playbut_label, "Play");

//// Explore button
//popup_explorebut = lv_btn_create(popup_cont);
//lv_obj_add_style(popup_explorebut, &style_popup_buttons, LV_PART_MAIN);
//popup_explorebut_label = lv_label_create(popup_explorebut);
//lv_label_set_text(popup_explorebut_label, "Explore...");

////Back image button
//popup_backbut = lv_btn_create(popup_cont);
//lv_obj_add_style(popup_backbut, &style_popup_backbut, LV_PART_MAIN);
//popup_backbut_label = lv_label_create(popup_backbut);
//lv_label_set_text(popup_backbut_label, "Explore...");

// Layout

// Patchname: center top
// lv_obj_set_pos(popup_patchname, 0, 0);
// lv_obj_align(popup_patchname, popup_cont, LV_ALIGN_IN_TOP_MID, 0, 0);
// lv_obj_set_size(popup_patchname, 320, 10);

// // Patch Desc: centered below patchname
// lv_obj_align(popup_desc, popup_patchname, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
// // lv_obj_set_pos(popup_desc, 0, 25);
// lv_obj_set_size(popup_desc, 320, 10);

// // Explore button: bottom center, up 10px
// lv_obj_align(popup_explorebut, popup_cont, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
// // Play button, above Explore, up 10px
// lv_obj_align(popup_playbut, popup_explorebut, LV_ALIGN_OUT_TOP_MID, 0, -10);
// // Back button: to the left of Play, top-aligned, 10px spacing
// lv_obj_align(popup_backbut, popup_playbut, LV_ALIGN_OUT_LEFT_TOP, -10, 0);

// Popup Group
// popup_group = lv_group_create();
// lv_group_set_wrap(popup_group, true);
// lv_group_add_obj(popup_group, popup_playbut);
// lv_group_add_obj(popup_group, popup_explorebut);
// lv_group_add_obj(popup_group, popup_backbut);

// lv_obj_add_event_cb(popup_backbut, popup_back_event_cb, LV_EVENT_CLICKED, this);
// lv_obj_add_event_cb(popup_playbut, popup_play_event_cb, LV_EVENT_CLICKED, this);
// lv_obj_add_event_cb(popup_explorebut, popup_explore_event_cb, LV_EVENT_CLICKED, this);

// hide_popup();

// wait_cont = lv_obj_create(base);
// lv_obj_set_align(wait_cont, LV_ALIGN_CENTER);
// lv_obj_add_style(wait_cont, &style_wait_cont, LV_PART_MAIN);
// lv_cont_set_layout(wait_cont, LV_LAYOUT_CENTER);
// lv_cont_set_fit(wait_cont, LV_FIT_TIGHT);

// wait_text = lv_label_create(wait_cont);
// lv_obj_add_style(wait_text, &style_popup_patchname, LV_PART_MAIN);
// lv_obj_set_align(wait_text, LV_ALIGN_CENTER);
// lv_label_set_text(wait_text, "Refreshing Patches...");

// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);

// wait_group = lv_group_create();
// }

// void _init_styles() {

//// Popup styles:
//lv_style_init(&style_popup_cont);
//lv_style_set_radius(&style_popup_cont, 0);
//lv_style_set_bg_color(&style_popup_cont, lv_color_make(0xe6, 0xe6, 0xe6));
//lv_style_set_bg_opa(&style_popup_cont, 255);
////lv_style_set_border_color(&style_popup_cont, lv_color_make(0xff, 0xc3, 0x70));
//lv_style_set_border_width(&style_popup_cont, 0);
//lv_style_set_border_opa(&style_popup_cont, 0);
//lv_style_set_pad_gap(&style_popup_cont, 10);
//lv_style_set_pad_all(&style_popup_cont, 4);

//lv_style_init(&style_popup_buttons);
//lv_style_set_radius(&style_popup_buttons, 8);
//lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xff, 0xff));
//// lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xc3, 0x70));//LV_STATE_FOCUSED,
//// lv_style_set_bg_color(&style_popup_buttons,  lv_color_make(0xf6, 0xdd, 0x53));//LV_STATE_PRESSED,
//lv_style_set_bg_opa(&style_popup_buttons, 255);
//lv_style_set_border_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));
//lv_style_set_border_width(&style_popup_buttons, 2);
//lv_style_set_text_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));

//lv_style_init(&style_popup_backbut);
//// lv_style_set_image_opa(&style_popup_backbut, 255);
////FOCUSED state:
//lv_style_set_radius(&style_popup_backbut, 6);
//lv_style_set_outline_color(&style_popup_backbut, lv_color_hex(0xabcdef));
//lv_style_set_outline_width(&style_popup_backbut, LV_DPX(2));
//lv_style_set_outline_opa(&style_popup_backbut, LV_OPA_0);
//// lv_style_set_outline_opa(&style_popup_backbut, LV_STATE_FOCUSED, LV_OPA_50);
//// lv_style_set_image_recolor(&style_popup_backbut, LV_STATE_FOCUSED, lv_color_hex(0x888888));
////lv_style_set_outline_pad(&style_popup_backbut, LV_STATE_FOCUSED, 4);
////lv_style_set_outline_blend_mode(&style_popup_backbut, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

//lv_style_init(&style_popup_desc);
//lv_style_set_radius(&style_popup_desc, 0);
//// lv_style_set_bg_color(&style_popup_desc, lv_color_make(0xff, 0xff, 0xff));
//lv_style_set_bg_opa(&style_popup_desc, 0);
//lv_style_set_text_color(&style_popup_desc, lv_color_make(0x78, 0x78, 0x78));
//lv_style_set_text_font(&style_popup_desc, &lv_font_MuseoSansRounded_500_16);
//lv_style_set_text_letter_space(&style_popup_desc, 0);
//lv_style_set_text_line_space(&style_popup_desc, 12);
//lv_style_set_pad_left(&style_popup_desc, 4);
//lv_style_set_pad_right(&style_popup_desc, 4);
//lv_style_set_pad_top(&style_popup_desc, 3);
//lv_style_set_pad_bottom(&style_popup_desc, 2);

//lv_style_init(&style_popup_patchname);
//// lv_style_set_radius(&style_popup_patchname, 0);
//// lv_style_set_bg_color(&style_popup_patchname, lv_color_make(0xa0, 0xa0, 0xa0));
//lv_style_set_bg_opa(&style_popup_patchname, 0);
//lv_style_set_text_color(&style_popup_patchname, lv_color_make(0x1c, 0x1c, 0x1c));
//lv_style_set_text_font(&style_popup_patchname, &lv_font_MuseoSansRounded_700_17);
//lv_style_set_text_letter_space(&style_popup_patchname, 1);
//lv_style_set_pad_left(&style_popup_patchname, 6);
//lv_style_set_pad_right(&style_popup_patchname, 6);
//lv_style_set_pad_top(&style_popup_patchname, 4);
//lv_style_set_pad_bottom(&style_popup_patchname, 4);

//// Wait cont style
//lv_style_init(&style_wait_cont);
//lv_style_set_radius(&style_wait_cont, 2);
//lv_style_set_bg_color(&style_wait_cont, lv_color_make(0xe6, 0xe6, 0xe6));
//lv_style_set_bg_opa(&style_wait_cont, 255);
//lv_style_set_border_color(&style_wait_cont, lv_color_make(0xff, 0xc3, 0x70));
//lv_style_set_border_width(&style_wait_cont, 1);
//lv_style_set_border_opa(&style_wait_cont, 255);
//lv_style_set_pad_gap(&style_wait_cont, 10);
//lv_style_set_pad_all(&style_wait_cont, 10);
// }
