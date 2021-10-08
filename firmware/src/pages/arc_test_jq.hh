#pragma once
#include "lvgl/src/lv_widgets/lv_arc.h"
#include "pages/base.hh"
#include "pages/fonts.hh"

namespace MetaModule
{
// Todo: this should display User-set names for jacks:
// Instead of "Drum#3:Out", should be "Kick Out"
struct ArcTestJQPage : PageBase {
	ArcTestJQPage(PatchInfo info)
		: PageBase{info}
	{
		ui = &base_ui;
	}

	struct {
		lv_obj_t *screen;
		lv_obj_t *screen_btn_1;
		lv_obj_t *screen_btn_1_label;
		lv_obj_t *screen_btn_2;
		lv_obj_t *screen_btn_2_label;
		lv_obj_t *screen_btn_3;
		lv_obj_t *screen_btn_3_label;
		lv_obj_t *screen_btn_4;
		lv_obj_t *screen_btn_4_label;
		lv_obj_t *screen_btn_5;
		lv_obj_t *screen_btn_5_label;
		lv_obj_t *screen_btn_6;
		lv_obj_t *screen_btn_6_label;
		lv_obj_t *screen_arc_1;
		lv_obj_t *screen_ta_2;
		lv_obj_t *screen_ta_1;
		lv_obj_t *screen_arc_2;
		lv_obj_t *screen_arc_3;
		lv_obj_t *screen_arc_4;
		lv_obj_t *screen_arc_5;
		lv_obj_t *screen_arc_6;
	} base_ui, *ui;

	bool is_init = false;

	static inline lv_obj_t *kb;
	static void kb_event_cb(lv_obj_t *event_kb, lv_event_t event)
	{
		/* Just call the regular event handler */
		lv_keyboard_def_event_cb(event_kb, event);
		if (event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL) {
			if (NULL != kb) {
				lv_obj_del(kb);
			}
		}
	}
	static void text_area_event_cb(lv_obj_t *ta, lv_event_t event)
	{
		if (event == LV_EVENT_CLICKED) {
			if (!lv_debug_check_obj_valid(kb)) {
				/* Create a keyboard and make it fill the width of the above text areas */
				kb = lv_keyboard_create(lv_scr_act(), NULL);
				lv_obj_set_event_cb(kb, kb_event_cb);
				lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);
			}
			lv_keyboard_set_textarea(kb, ta);
			lv_keyboard_set_cursor_manage(kb, true);
		}
	}

	void init()
	{
		//Write codes screen
		ui->screen = lv_obj_create(NULL, NULL);

		//Added by DG:
		// lv_obj_set_style_local_bg_color(ui->screen, 0, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));

		//Write codes screen_btn_1
		ui->screen_btn_1 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_1
		static lv_style_t style_screen_btn_1_main;
		lv_style_reset(&style_screen_btn_1_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_1_main
		lv_style_set_radius(&style_screen_btn_1_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
		lv_style_set_bg_grad_color(&style_screen_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
		lv_style_set_bg_grad_dir(&style_screen_btn_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_1_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_1_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_1_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_1_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_1, LV_BTN_PART_MAIN, &style_screen_btn_1_main);
		lv_obj_set_pos(ui->screen_btn_1, 120, 165);
		lv_obj_set_size(ui->screen_btn_1, 80, 30);
		ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1, NULL);
		lv_label_set_text(ui->screen_btn_1_label, "PARAMETER 5");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_btn_2
		ui->screen_btn_2 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_2
		static lv_style_t style_screen_btn_2_main;
		lv_style_reset(&style_screen_btn_2_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_2_main
		lv_style_set_radius(&style_screen_btn_2_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
		lv_style_set_bg_grad_color(&style_screen_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
		lv_style_set_bg_grad_dir(&style_screen_btn_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_2_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_2_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_2_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_2_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_2, LV_BTN_PART_MAIN, &style_screen_btn_2_main);
		lv_obj_set_pos(ui->screen_btn_2, 220, 165);
		lv_obj_set_size(ui->screen_btn_2, 80, 30);
		ui->screen_btn_2_label = lv_label_create(ui->screen_btn_2, NULL);
		lv_label_set_text(ui->screen_btn_2_label, "LFO SPEED");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_btn_3
		ui->screen_btn_3 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_3
		static lv_style_t style_screen_btn_3_main;
		lv_style_reset(&style_screen_btn_3_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_3_main
		lv_style_set_radius(&style_screen_btn_3_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_bg_grad_color(&style_screen_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_bg_grad_dir(&style_screen_btn_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_3_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_3_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_3_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_3_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_3, LV_BTN_PART_MAIN, &style_screen_btn_3_main);
		lv_obj_set_pos(ui->screen_btn_3, 220, 200);
		lv_obj_set_size(ui->screen_btn_3, 77, 30);
		ui->screen_btn_3_label = lv_label_create(ui->screen_btn_3, NULL);
		lv_label_set_text(ui->screen_btn_3_label, "PARAMETER 6");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_btn_4
		ui->screen_btn_4 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_4
		static lv_style_t style_screen_btn_4_main;
		lv_style_reset(&style_screen_btn_4_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_4_main
		lv_style_set_radius(&style_screen_btn_4_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
		lv_style_set_bg_grad_color(&style_screen_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
		lv_style_set_bg_grad_dir(&style_screen_btn_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_4_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_4_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_4_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_4_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_4, LV_BTN_PART_MAIN, &style_screen_btn_4_main);
		lv_obj_set_pos(ui->screen_btn_4, 20, 165);
		lv_obj_set_size(ui->screen_btn_4, 80, 30);
		ui->screen_btn_4_label = lv_label_create(ui->screen_btn_4, NULL);
		lv_label_set_text(ui->screen_btn_4_label, "PARAMETER 1");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_btn_5
		ui->screen_btn_5 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_5
		static lv_style_t style_screen_btn_5_main;
		lv_style_reset(&style_screen_btn_5_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_5_main
		lv_style_set_radius(&style_screen_btn_5_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
		lv_style_set_bg_grad_color(&style_screen_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
		lv_style_set_bg_grad_dir(&style_screen_btn_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_5_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_5_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_5_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_5_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_5, LV_BTN_PART_MAIN, &style_screen_btn_5_main);
		lv_obj_set_pos(ui->screen_btn_5, 120, 200);
		lv_obj_set_size(ui->screen_btn_5, 80, 30);
		ui->screen_btn_5_label = lv_label_create(ui->screen_btn_5, NULL);
		lv_label_set_text(ui->screen_btn_5_label, "PARAMETER 2");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_btn_6
		ui->screen_btn_6 = lv_btn_create(ui->screen, NULL);

		//Write style LV_BTN_PART_MAIN for screen_btn_6
		static lv_style_t style_screen_btn_6_main;
		lv_style_reset(&style_screen_btn_6_main);

		//Write style state: LV_STATE_DEFAULT for style_screen_btn_6_main
		lv_style_set_radius(&style_screen_btn_6_main, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_bg_grad_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_bg_grad_dir(&style_screen_btn_6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_border_width(&style_screen_btn_6_main, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
		lv_style_set_outline_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 0);
		lv_obj_add_style(ui->screen_btn_6, LV_BTN_PART_MAIN, &style_screen_btn_6_main);
		lv_obj_set_pos(ui->screen_btn_6, 20, 200);
		lv_obj_set_size(ui->screen_btn_6, 80, 30);
		ui->screen_btn_6_label = lv_label_create(ui->screen_btn_6, NULL);
		lv_label_set_text(ui->screen_btn_6_label, "PARAMETER 4");
		lv_obj_set_style_local_text_color(
			ui->screen_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
		lv_obj_set_style_local_text_font(
			ui->screen_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

		//Write codes screen_arc_1
		ui->screen_arc_1 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_1
		static lv_style_t style_screen_arc_1_bg;
		lv_style_reset(&style_screen_arc_1_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_1_bg
		lv_style_set_bg_color(&style_screen_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_arc_1_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_1_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_1_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_1, LV_ARC_PART_BG, &style_screen_arc_1_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_1
		static lv_style_t style_screen_arc_1_indic;
		lv_style_reset(&style_screen_arc_1_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_1_indic
		lv_style_set_line_color(&style_screen_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_line_width(&style_screen_arc_1_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_1, LV_ARC_PART_INDIC, &style_screen_arc_1_indic);
		lv_obj_set_pos(ui->screen_arc_1, 30, 75);
		lv_obj_set_size(ui->screen_arc_1, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_1, 120, 60);
		lv_arc_set_angles(ui->screen_arc_1, 120, 300);
		lv_arc_set_rotation(ui->screen_arc_1, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Write codes screen_ta_2
		ui->screen_ta_2 = lv_textarea_create(ui->screen, NULL);

		//Write style LV_PAGE_PART_BG for screen_ta_2
		static lv_style_t style_screen_ta_2_bg;
		lv_style_reset(&style_screen_ta_2_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_2_bg
		lv_style_set_radius(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 8);
		lv_style_set_border_color(&style_screen_ta_2_bg, LV_STATE_DEFAULT, lv_color_make(0xdc, 0xdc, 0xdc));
		lv_style_set_border_width(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_text_color(&style_screen_ta_2_bg, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
		lv_style_set_text_letter_space(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 1);
		lv_style_set_pad_left(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_right(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_top(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_bottom(&style_screen_ta_2_bg, LV_STATE_DEFAULT, 2);
		lv_obj_add_style(ui->screen_ta_2, LV_PAGE_PART_BG, &style_screen_ta_2_bg);

		//Write style LV_PAGE_PART_SCROLLABLE for screen_ta_2
		static lv_style_t style_screen_ta_2_scrollable;
		lv_style_reset(&style_screen_ta_2_scrollable);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_2_scrollable
		lv_style_set_radius(&style_screen_ta_2_scrollable, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_screen_ta_2_scrollable, LV_STATE_DEFAULT, lv_color_make(0xdc, 0xdc, 0xdc));
		lv_style_set_bg_grad_color(&style_screen_ta_2_scrollable, LV_STATE_DEFAULT, lv_color_make(0xdc, 0xdc, 0xdc));
		lv_style_set_bg_grad_dir(&style_screen_ta_2_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_ta_2_scrollable, LV_STATE_DEFAULT, 255);
		lv_obj_add_style(ui->screen_ta_2, LV_PAGE_PART_SCROLLABLE, &style_screen_ta_2_scrollable);

		//Write style LV_PAGE_PART_EDGE_FLASH for screen_ta_2
		static lv_style_t style_screen_ta_2_edge_flash;
		lv_style_reset(&style_screen_ta_2_edge_flash);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_2_edge_flash
		lv_style_set_radius(&style_screen_ta_2_edge_flash, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_screen_ta_2_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_color(&style_screen_ta_2_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_dir(&style_screen_ta_2_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_ta_2_edge_flash, LV_STATE_DEFAULT, 255);
		lv_obj_add_style(ui->screen_ta_2, LV_PAGE_PART_EDGE_FLASH, &style_screen_ta_2_edge_flash);
		lv_obj_set_pos(ui->screen_ta_2, 9, 140);
		lv_obj_set_size(ui->screen_ta_2, 300, 17);
		lv_obj_set_event_cb(ui->screen_ta_2, text_area_event_cb);
		lv_textarea_set_text_align(ui->screen_ta_2, LV_LABEL_ALIGN_CENTER);

		//Write codes screen_ta_1
		ui->screen_ta_1 = lv_textarea_create(ui->screen, NULL);

		//Write style LV_PAGE_PART_BG for screen_ta_1
		static lv_style_t style_screen_ta_1_bg;
		lv_style_reset(&style_screen_ta_1_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_1_bg
		lv_style_set_radius(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 8);
		lv_style_set_border_color(&style_screen_ta_1_bg, LV_STATE_DEFAULT, lv_color_make(0xdc, 0xdc, 0xdc));
		lv_style_set_border_width(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_text_color(&style_screen_ta_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_text_font(&style_screen_ta_1_bg, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_10);
		lv_style_set_text_letter_space(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 1);
		lv_style_set_pad_left(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_right(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_top(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_bottom(&style_screen_ta_1_bg, LV_STATE_DEFAULT, 2);
		lv_obj_add_style(ui->screen_ta_1, LV_PAGE_PART_BG, &style_screen_ta_1_bg);

		//Write style LV_PAGE_PART_SCROLLABLE for screen_ta_1
		static lv_style_t style_screen_ta_1_scrollable;
		lv_style_reset(&style_screen_ta_1_scrollable);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_1_scrollable
		lv_style_set_radius(&style_screen_ta_1_scrollable, LV_STATE_DEFAULT, 8);
		lv_style_set_bg_color(&style_screen_ta_1_scrollable, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_bg_grad_color(&style_screen_ta_1_scrollable, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_bg_grad_dir(&style_screen_ta_1_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_ta_1_scrollable, LV_STATE_DEFAULT, 255);
		lv_obj_add_style(ui->screen_ta_1, LV_PAGE_PART_SCROLLABLE, &style_screen_ta_1_scrollable);

		//Write style LV_PAGE_PART_EDGE_FLASH for screen_ta_1
		static lv_style_t style_screen_ta_1_edge_flash;
		lv_style_reset(&style_screen_ta_1_edge_flash);

		//Write style state: LV_STATE_DEFAULT for style_screen_ta_1_edge_flash
		lv_style_set_radius(&style_screen_ta_1_edge_flash, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_screen_ta_1_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_color(&style_screen_ta_1_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_dir(&style_screen_ta_1_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_ta_1_edge_flash, LV_STATE_DEFAULT, 255);
		lv_obj_add_style(ui->screen_ta_1, LV_PAGE_PART_EDGE_FLASH, &style_screen_ta_1_edge_flash);
		lv_obj_set_pos(ui->screen_ta_1, 9, 140);
		lv_obj_set_size(ui->screen_ta_1, 300, 17);
		lv_textarea_set_text(ui->screen_ta_1, "PARAMETER INFO, CH. HEADERS");
		lv_obj_set_event_cb(ui->screen_ta_1, text_area_event_cb);
		lv_textarea_set_text_align(ui->screen_ta_1, LV_LABEL_ALIGN_CENTER);

		//Write codes screen_arc_2
		ui->screen_arc_2 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_2
		static lv_style_t style_screen_arc_2_bg;
		lv_style_reset(&style_screen_arc_2_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_2_bg
		lv_style_set_bg_color(&style_screen_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
		lv_style_set_bg_opa(&style_screen_arc_2_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_2_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_2_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_2, LV_ARC_PART_BG, &style_screen_arc_2_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_2
		static lv_style_t style_screen_arc_2_indic;
		lv_style_reset(&style_screen_arc_2_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_2_indic
		lv_style_set_line_color(&style_screen_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
		lv_style_set_line_width(&style_screen_arc_2_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_2, LV_ARC_PART_INDIC, &style_screen_arc_2_indic);
		lv_obj_set_pos(ui->screen_arc_2, 30, 10);
		lv_obj_set_size(ui->screen_arc_2, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_2, 120, 60);
		lv_arc_set_angles(ui->screen_arc_2, 120, 220);
		lv_arc_set_rotation(ui->screen_arc_2, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Write codes screen_arc_3
		ui->screen_arc_3 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_3
		static lv_style_t style_screen_arc_3_bg;
		lv_style_reset(&style_screen_arc_3_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_3_bg
		lv_style_set_bg_color(&style_screen_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_screen_arc_3_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_3_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_3_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_3, LV_ARC_PART_BG, &style_screen_arc_3_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_3
		static lv_style_t style_screen_arc_3_indic;
		lv_style_reset(&style_screen_arc_3_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_3_indic
		lv_style_set_line_color(&style_screen_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
		lv_style_set_line_width(&style_screen_arc_3_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_3, LV_ARC_PART_INDIC, &style_screen_arc_3_indic);
		lv_obj_set_pos(ui->screen_arc_3, 130, 10);
		lv_obj_set_size(ui->screen_arc_3, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_3, 120, 60);
		lv_arc_set_angles(ui->screen_arc_3, 120, 150);
		lv_arc_set_rotation(ui->screen_arc_3, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Write codes screen_arc_4
		ui->screen_arc_4 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_4
		static lv_style_t style_screen_arc_4_bg;
		lv_style_reset(&style_screen_arc_4_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_4_bg
		lv_style_set_bg_color(&style_screen_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
		lv_style_set_bg_opa(&style_screen_arc_4_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_4_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_4_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_4, LV_ARC_PART_BG, &style_screen_arc_4_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_4
		static lv_style_t style_screen_arc_4_indic;
		lv_style_reset(&style_screen_arc_4_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_4_indic
		lv_style_set_line_color(&style_screen_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_line_width(&style_screen_arc_4_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_4, LV_ARC_PART_INDIC, &style_screen_arc_4_indic);
		lv_obj_set_pos(ui->screen_arc_4, 230, 75);
		lv_obj_set_size(ui->screen_arc_4, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_4, 120, 60);
		lv_arc_set_angles(ui->screen_arc_4, 120, 120); //120, 10 breaks
		lv_arc_set_rotation(ui->screen_arc_4, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Write codes screen_arc_5
		ui->screen_arc_5 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_5
		static lv_style_t style_screen_arc_5_bg;
		lv_style_reset(&style_screen_arc_5_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_5_bg
		lv_style_set_bg_color(&style_screen_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
		lv_style_set_bg_opa(&style_screen_arc_5_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_5_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_5_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_5, LV_ARC_PART_BG, &style_screen_arc_5_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_5
		static lv_style_t style_screen_arc_5_indic;
		lv_style_reset(&style_screen_arc_5_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_5_indic
		lv_style_set_line_color(&style_screen_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
		lv_style_set_line_width(&style_screen_arc_5_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_5, LV_ARC_PART_INDIC, &style_screen_arc_5_indic);
		lv_obj_set_pos(ui->screen_arc_5, 130, 75);
		lv_obj_set_size(ui->screen_arc_5, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_5, 120, 60);
		lv_arc_set_angles(ui->screen_arc_5, 120, 30);
		lv_arc_set_rotation(ui->screen_arc_5, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Write codes screen_arc_6
		ui->screen_arc_6 = lv_arc_create(ui->screen, NULL);

		//Write style LV_ARC_PART_BG for screen_arc_6
		static lv_style_t style_screen_arc_6_bg;
		lv_style_reset(&style_screen_arc_6_bg);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_6_bg
		lv_style_set_bg_color(&style_screen_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_color(&style_screen_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
		lv_style_set_bg_grad_dir(&style_screen_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
		lv_style_set_bg_opa(&style_screen_arc_6_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_border_width(&style_screen_arc_6_bg, LV_STATE_DEFAULT, 0);
		lv_style_set_line_color(&style_screen_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_line_width(&style_screen_arc_6_bg, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_6, LV_ARC_PART_BG, &style_screen_arc_6_bg);

		//Write style LV_ARC_PART_INDIC for screen_arc_6
		static lv_style_t style_screen_arc_6_indic;
		lv_style_reset(&style_screen_arc_6_indic);

		//Write style state: LV_STATE_DEFAULT for style_screen_arc_6_indic
		lv_style_set_line_color(&style_screen_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
		lv_style_set_line_width(&style_screen_arc_6_indic, LV_STATE_DEFAULT, 16);
		lv_obj_add_style(ui->screen_arc_6, LV_ARC_PART_INDIC, &style_screen_arc_6_indic);
		lv_obj_set_pos(ui->screen_arc_6, 230, 10);
		lv_obj_set_size(ui->screen_arc_6, 60, 60);
		lv_arc_set_bg_angles(ui->screen_arc_6, 120, 60);
		lv_arc_set_angles(ui->screen_arc_6, 120, 2);
		lv_arc_set_rotation(ui->screen_arc_6, 0);
		lv_obj_set_style_local_pad_top(ui->screen_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_bottom(ui->screen_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_left(ui->screen_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
		lv_obj_set_style_local_pad_right(ui->screen_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

		//Added by DG:
		lv_arc_set_adjustable(ui->screen_arc_1, true);
		lv_arc_set_adjustable(ui->screen_arc_2, true);
		lv_arc_set_adjustable(ui->screen_arc_3, true);
		lv_arc_set_adjustable(ui->screen_arc_4, true);
		lv_arc_set_adjustable(ui->screen_arc_5, true);
		lv_arc_set_adjustable(ui->screen_arc_6, true);

		is_init = true;
	}

	void focus(PageChangeDirection dir)
	{
		if (!is_init)
			init();

		auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
							   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
																	   LV_SCR_LOAD_ANIM_FADE_ON;
		lv_scr_load_anim(ui->screen, animation_style, 500, 0, false);
	}

	void blur() {}

	void update()
	{
		lv_arc_set_value(ui->screen_arc_1, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->screen_arc_2, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->screen_arc_3, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->screen_arc_4, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->screen_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->screen_arc_6, params.knobs[5] * 100.f);
	}
};
} // namespace MetaModule
