/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

#if 0
void setup_scr_Dropdown1b(lv_ui *ui) {

	//Write codes Dropdown1b_cont
	ui->Dropdown1b_cont = lv_cont_create(ui->Dropdown1b, NULL);

	//Write style LV_CONT_PART_MAIN for Dropdown1b_cont
	static lv_style_t style_Dropdown1b_popup_menu_main;
	lv_style_reset(&style_Dropdown1b_popup_menu_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_popup_menu_main
	lv_style_set_radius(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown1b_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1b_cont, LV_CONT_PART_MAIN, &style_Dropdown1b_popup_menu_main);
	lv_obj_set_pos(ui->Dropdown1b_cont, 20, 20);
	lv_obj_set_size(ui->Dropdown1b_cont, 280, 200);
	lv_obj_set_click(ui->Dropdown1b_cont, false);

	//Write style LV_BTNMATRIX_PART_BG for Dropdown1b_main_buttons
	static lv_style_t style_Dropdown1b_main_buttons_bg;
	lv_style_reset(&style_Dropdown1b_main_buttons_bg);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_main_buttons_bg
	lv_style_set_radius(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 7);
	lv_style_set_pad_bottom(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_inner(&style_Dropdown1b_main_buttons_bg, LV_STATE_DEFAULT, 6);
	// lv_obj_add_style(ui->Dropdown1b_main_buttons, LV_BTNMATRIX_PART_BG, &style_Dropdown1b_main_buttons_bg);

	//Write style LV_BTNMATRIX_PART_BTN for Dropdown1b_main_buttons
	static lv_style_t style_Dropdown1b_main_buttons_btn;
	lv_style_reset(&style_Dropdown1b_main_buttons_btn);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_main_buttons_btn
	lv_style_set_radius(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 8);
	lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);

	//Added by DG:
	lv_style_set_bg_grad_dir(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_FOCUSED, lv_color_make(0xd6, 0xdd, 0xe3));
	lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_PRESSED, lv_color_make(0xe6, 0xdd, 0x53));
	//end

	lv_style_set_bg_opa(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xd6, 0xdd, 0xe3));
	lv_style_set_border_width(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));
	lv_obj_add_style(ui->Dropdown1b_main_buttons, LV_BTNMATRIX_PART_BTN, &style_Dropdown1b_main_buttons_btn);
	lv_obj_set_pos(ui->Dropdown1b_main_buttons, 38, 94);
	lv_obj_set_size(ui->Dropdown1b_main_buttons, 241, 104);

	//Write codes Dropdown1b_patch_description
	ui->Dropdown1b_patch_description = lv_label_create(ui->Dropdown1b_cont, NULL);
	lv_label_set_text(ui->Dropdown1b_patch_description, "Patch description...");
	lv_label_set_long_mode(ui->Dropdown1b_patch_description, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Dropdown1b_patch_description, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for Dropdown1b_patch_description
	static lv_style_t style_Dropdown1b_patch_description_main;
	lv_style_reset(&style_Dropdown1b_patch_description_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_patch_description_main
	lv_style_set_radius(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(
		&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(
		&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_text_font(
		&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_16);
	lv_style_set_text_letter_space(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_bottom(&style_Dropdown1b_patch_description_main, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->Dropdown1b_patch_description, LV_LABEL_PART_MAIN, &style_Dropdown1b_patch_description_main);
	lv_obj_set_pos(ui->Dropdown1b_patch_description, 0, 25);
	lv_obj_set_size(ui->Dropdown1b_patch_description, 280, 0);

	////Write codes Dropdown1b_patch_nam_bg
	//ui->Dropdown1b_patch_nam_bg = lv_canvas_create(ui->Dropdown1b_cont, NULL);

	////Write style LV_CANVAS_PART_MAIN for Dropdown1b_patch_nam_bg
	//static lv_style_t style_Dropdown1b_patch_nam_bg_main;
	//lv_style_reset(&style_Dropdown1b_patch_nam_bg_main);

	////Write style state: LV_STATE_DEFAULT for style_Dropdown1b_patch_nam_bg_main
	//lv_style_set_image_recolor(&style_Dropdown1b_patch_nam_bg_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	//lv_style_set_image_recolor_opa(&style_Dropdown1b_patch_nam_bg_main, LV_STATE_DEFAULT, 255);
	//lv_obj_add_style(ui->Dropdown1b_patch_nam_bg, LV_CANVAS_PART_MAIN, &style_Dropdown1b_patch_nam_bg_main);
	//lv_obj_set_pos(ui->Dropdown1b_patch_nam_bg, 0, 17);
	//lv_obj_set_size(ui->Dropdown1b_patch_nam_bg, 280, 8);
	//lv_color_t *buf_Dropdown1b_patch_nam_bg = (lv_color_t *)lv_mem_alloc(280 * 8 * 4);
	//lv_canvas_set_buffer(ui->Dropdown1b_patch_nam_bg, buf_Dropdown1b_patch_nam_bg, 280, 8, LV_IMG_CF_TRUE_COLOR);

	////Write codes Dropdown1b_line_header
	//ui->Dropdown1b_line_header = lv_canvas_create(ui->Dropdown1b_cont, NULL);

	////Write style LV_CANVAS_PART_MAIN for Dropdown1b_line_header
	//static lv_style_t style_Dropdown1b_line_header_main;
	//lv_style_reset(&style_Dropdown1b_line_header_main);

	////Write style state: LV_STATE_DEFAULT for style_Dropdown1b_line_header_main
	//lv_style_set_image_recolor(&style_Dropdown1b_line_header_main, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x8c, 0xcd));
	//lv_style_set_image_recolor_opa(&style_Dropdown1b_line_header_main, LV_STATE_DEFAULT, 255);
	//lv_obj_add_style(ui->Dropdown1b_line_header, LV_CANVAS_PART_MAIN, &style_Dropdown1b_line_header_main);
	//lv_obj_set_pos(ui->Dropdown1b_line_header, 0, 24);
	//lv_obj_set_size(ui->Dropdown1b_line_header, 280, 2);
	//lv_color_t *buf_Dropdown1b_line_header = (lv_color_t *)lv_mem_alloc(280 * 2 * 4);
	//lv_canvas_set_buffer(ui->Dropdown1b_line_header, buf_Dropdown1b_line_header, 280, 2, LV_IMG_CF_TRUE_COLOR);

	//Write codes Dropdown1b_patch_name
	ui->Dropdown1b_patch_name = lv_label_create(ui->Dropdown1b_cont, NULL);
	lv_label_set_text(ui->Dropdown1b_patch_name, "Patch Name 1");
	lv_label_set_long_mode(ui->Dropdown1b_patch_name, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Dropdown1b_patch_name, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Dropdown1b_patch_name
	static lv_style_t style_Dropdown1b_patch_name_main;
	lv_style_reset(&style_Dropdown1b_patch_name_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_patch_name_main
	lv_style_set_radius(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_color(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_dir(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0x1c, 0x1c, 0x1c));
	lv_style_set_text_font(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_17);
	lv_style_set_text_letter_space(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_bottom(&style_Dropdown1b_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1b_patch_name, LV_LABEL_PART_MAIN, &style_Dropdown1b_patch_name_main);
	lv_obj_set_pos(ui->Dropdown1b_patch_name, 0, 0);
	lv_obj_set_size(ui->Dropdown1b_patch_name, 280, 0);
	lv_cont_set_layout(ui->Dropdown1b_cont, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->Dropdown1b_cont, LV_FIT_NONE);

	//Write codes Dropdown1b_imgbtn_1
	ui->Dropdown1b_imgbtn_1 = lv_imgbtn_create(ui->Dropdown1b, NULL);

	//Write style LV_IMGBTN_PART_MAIN for Dropdown1b_imgbtn_1
	static lv_style_t style_Dropdown1b_imgbtn_1_main;
	lv_style_reset(&style_Dropdown1b_imgbtn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1b_imgbtn_1_main
	lv_style_set_text_color(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Dropdown1b_imgbtn_1, LV_IMGBTN_PART_MAIN, &style_Dropdown1b_imgbtn_1_main);
	lv_obj_set_pos(ui->Dropdown1b_imgbtn_1, 28, 143);
	lv_obj_set_size(ui->Dropdown1b_imgbtn_1, 27, 48);
	lv_imgbtn_set_src(ui->Dropdown1b_imgbtn_1, LV_BTN_STATE_RELEASED, &back_but_orange_neg_27x48);
	lv_imgbtn_set_checkable(ui->Dropdown1b_imgbtn_1, true);
}
#endif
