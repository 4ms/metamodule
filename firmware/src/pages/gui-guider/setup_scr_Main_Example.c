/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Main_Example(lv_ui *ui){

	//Write codes Main_Example
	ui->Main_Example = lv_obj_create(NULL, NULL);

	//Write codes Main_Example_btn_1
	ui->Main_Example_btn_1 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_1
	static lv_style_t style_Main_Example_btn_1_main;
	lv_style_reset(&style_Main_Example_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_1_main
	lv_style_set_radius(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_1, LV_BTN_PART_MAIN, &style_Main_Example_btn_1_main);
	lv_obj_set_pos(ui->Main_Example_btn_1, 120, 165);
	lv_obj_set_size(ui->Main_Example_btn_1, 80, 30);
	ui->Main_Example_btn_1_label = lv_label_create(ui->Main_Example_btn_1, NULL);
	lv_label_set_text(ui->Main_Example_btn_1_label, "PARAMETER 3");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_btn_2
	ui->Main_Example_btn_2 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_2
	static lv_style_t style_Main_Example_btn_2_main;
	lv_style_reset(&style_Main_Example_btn_2_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_2_main
	lv_style_set_radius(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_2, LV_BTN_PART_MAIN, &style_Main_Example_btn_2_main);
	lv_obj_set_pos(ui->Main_Example_btn_2, 220, 165);
	lv_obj_set_size(ui->Main_Example_btn_2, 80, 30);
	ui->Main_Example_btn_2_label = lv_label_create(ui->Main_Example_btn_2, NULL);
	lv_label_set_text(ui->Main_Example_btn_2_label, "LFO SPEED");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_btn_3
	ui->Main_Example_btn_3 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_3
	static lv_style_t style_Main_Example_btn_3_main;
	lv_style_reset(&style_Main_Example_btn_3_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_3_main
	lv_style_set_radius(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_3, LV_BTN_PART_MAIN, &style_Main_Example_btn_3_main);
	lv_obj_set_pos(ui->Main_Example_btn_3, 220, 200);
	lv_obj_set_size(ui->Main_Example_btn_3, 77, 30);
	ui->Main_Example_btn_3_label = lv_label_create(ui->Main_Example_btn_3, NULL);
	lv_label_set_text(ui->Main_Example_btn_3_label, "PARAMETER 6");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_btn_4
	ui->Main_Example_btn_4 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_4
	static lv_style_t style_Main_Example_btn_4_main;
	lv_style_reset(&style_Main_Example_btn_4_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_4_main
	lv_style_set_radius(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_4, LV_BTN_PART_MAIN, &style_Main_Example_btn_4_main);
	lv_obj_set_pos(ui->Main_Example_btn_4, 20, 165);
	lv_obj_set_size(ui->Main_Example_btn_4, 80, 30);
	ui->Main_Example_btn_4_label = lv_label_create(ui->Main_Example_btn_4, NULL);
	lv_label_set_text(ui->Main_Example_btn_4_label, "PARAMETER 1");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_btn_5
	ui->Main_Example_btn_5 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_5
	static lv_style_t style_Main_Example_btn_5_main;
	lv_style_reset(&style_Main_Example_btn_5_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_5_main
	lv_style_set_radius(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_5, LV_BTN_PART_MAIN, &style_Main_Example_btn_5_main);
	lv_obj_set_pos(ui->Main_Example_btn_5, 120, 200);
	lv_obj_set_size(ui->Main_Example_btn_5, 80, 30);
	ui->Main_Example_btn_5_label = lv_label_create(ui->Main_Example_btn_5, NULL);
	lv_label_set_text(ui->Main_Example_btn_5_label, "PARAMETER 5");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_btn_6
	ui->Main_Example_btn_6 = lv_btn_create(ui->Main_Example, NULL);

	//Write style LV_BTN_PART_MAIN for Main_Example_btn_6
	static lv_style_t style_Main_Example_btn_6_main;
	lv_style_reset(&style_Main_Example_btn_6_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_btn_6_main
	lv_style_set_radius(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_border_width(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_Main_Example_btn_6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_btn_6, LV_BTN_PART_MAIN, &style_Main_Example_btn_6_main);
	lv_obj_set_pos(ui->Main_Example_btn_6, 20, 200);
	lv_obj_set_size(ui->Main_Example_btn_6, 80, 30);
	ui->Main_Example_btn_6_label = lv_label_create(ui->Main_Example_btn_6, NULL);
	lv_label_set_text(ui->Main_Example_btn_6_label, "PARAMETER 4");
	lv_obj_set_style_local_text_color(ui->Main_Example_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x3c, 0x3c));
	lv_obj_set_style_local_text_font(ui->Main_Example_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_12);

	//Write codes Main_Example_arc_1
	ui->Main_Example_arc_1 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_1
	static lv_style_t style_Main_Example_arc_1_bg;
	lv_style_reset(&style_Main_Example_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_1_bg
	lv_style_set_bg_color(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_1_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_1, LV_ARC_PART_BG, &style_Main_Example_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_1
	static lv_style_t style_Main_Example_arc_1_indic;
	lv_style_reset(&style_Main_Example_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_1_indic
	lv_style_set_line_color(&style_Main_Example_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_Main_Example_arc_1_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_1, LV_ARC_PART_INDIC, &style_Main_Example_arc_1_indic);
	lv_obj_set_pos(ui->Main_Example_arc_1, 30, 75);
	lv_obj_set_size(ui->Main_Example_arc_1, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_1, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_1, 120, 300);
	lv_arc_set_rotation(ui->Main_Example_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_arc_2
	ui->Main_Example_arc_2 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_2
	static lv_style_t style_Main_Example_arc_2_bg;
	lv_style_reset(&style_Main_Example_arc_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_2_bg
	lv_style_set_bg_color(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_2_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_2, LV_ARC_PART_BG, &style_Main_Example_arc_2_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_2
	static lv_style_t style_Main_Example_arc_2_indic;
	lv_style_reset(&style_Main_Example_arc_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_2_indic
	lv_style_set_line_color(&style_Main_Example_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_Main_Example_arc_2_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_2, LV_ARC_PART_INDIC, &style_Main_Example_arc_2_indic);
	lv_obj_set_pos(ui->Main_Example_arc_2, 30, 10);
	lv_obj_set_size(ui->Main_Example_arc_2, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_2, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_2, 120, 220);
	lv_arc_set_rotation(ui->Main_Example_arc_2, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_arc_3
	ui->Main_Example_arc_3 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_3
	static lv_style_t style_Main_Example_arc_3_bg;
	lv_style_reset(&style_Main_Example_arc_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_3_bg
	lv_style_set_bg_color(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_3_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_3, LV_ARC_PART_BG, &style_Main_Example_arc_3_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_3
	static lv_style_t style_Main_Example_arc_3_indic;
	lv_style_reset(&style_Main_Example_arc_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_3_indic
	lv_style_set_line_color(&style_Main_Example_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_line_width(&style_Main_Example_arc_3_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_3, LV_ARC_PART_INDIC, &style_Main_Example_arc_3_indic);
	lv_obj_set_pos(ui->Main_Example_arc_3, 130, 10);
	lv_obj_set_size(ui->Main_Example_arc_3, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_3, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_3, 120, 150);
	lv_arc_set_rotation(ui->Main_Example_arc_3, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_arc_4
	ui->Main_Example_arc_4 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_4
	static lv_style_t style_Main_Example_arc_4_bg;
	lv_style_reset(&style_Main_Example_arc_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_4_bg
	lv_style_set_bg_color(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_4_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_4, LV_ARC_PART_BG, &style_Main_Example_arc_4_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_4
	static lv_style_t style_Main_Example_arc_4_indic;
	lv_style_reset(&style_Main_Example_arc_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_4_indic
	lv_style_set_line_color(&style_Main_Example_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_Main_Example_arc_4_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_4, LV_ARC_PART_INDIC, &style_Main_Example_arc_4_indic);
	lv_obj_set_pos(ui->Main_Example_arc_4, 230, 75);
	lv_obj_set_size(ui->Main_Example_arc_4, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_4, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_4, 120, 10);
	lv_arc_set_rotation(ui->Main_Example_arc_4, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_arc_5
	ui->Main_Example_arc_5 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_5
	static lv_style_t style_Main_Example_arc_5_bg;
	lv_style_reset(&style_Main_Example_arc_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_5_bg
	lv_style_set_bg_color(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_5_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_5, LV_ARC_PART_BG, &style_Main_Example_arc_5_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_5
	static lv_style_t style_Main_Example_arc_5_indic;
	lv_style_reset(&style_Main_Example_arc_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_5_indic
	lv_style_set_line_color(&style_Main_Example_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_line_width(&style_Main_Example_arc_5_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_5, LV_ARC_PART_INDIC, &style_Main_Example_arc_5_indic);
	lv_obj_set_pos(ui->Main_Example_arc_5, 130, 75);
	lv_obj_set_size(ui->Main_Example_arc_5, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_5, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_5, 120, 30);
	lv_arc_set_rotation(ui->Main_Example_arc_5, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_arc_6
	ui->Main_Example_arc_6 = lv_arc_create(ui->Main_Example, NULL);

	//Write style LV_ARC_PART_BG for Main_Example_arc_6
	static lv_style_t style_Main_Example_arc_6_bg;
	lv_style_reset(&style_Main_Example_arc_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_6_bg
	lv_style_set_bg_color(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Main_Example_arc_6_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_6, LV_ARC_PART_BG, &style_Main_Example_arc_6_bg);

	//Write style LV_ARC_PART_INDIC for Main_Example_arc_6
	static lv_style_t style_Main_Example_arc_6_indic;
	lv_style_reset(&style_Main_Example_arc_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_arc_6_indic
	lv_style_set_line_color(&style_Main_Example_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_Main_Example_arc_6_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Main_Example_arc_6, LV_ARC_PART_INDIC, &style_Main_Example_arc_6_indic);
	lv_obj_set_pos(ui->Main_Example_arc_6, 230, 10);
	lv_obj_set_size(ui->Main_Example_arc_6, 60, 60);
	lv_arc_set_bg_angles(ui->Main_Example_arc_6, 120, 60);
	lv_arc_set_angles(ui->Main_Example_arc_6, 120, 2);
	lv_arc_set_rotation(ui->Main_Example_arc_6, 0);
	lv_obj_set_style_local_pad_top(ui->Main_Example_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Main_Example_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Main_Example_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Main_Example_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Main_Example_label_1
	ui->Main_Example_label_1 = lv_label_create(ui->Main_Example, NULL);
	lv_label_set_text(ui->Main_Example_label_1, "HEADERS");
	lv_label_set_long_mode(ui->Main_Example_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Main_Example_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Main_Example_label_1
	static lv_style_t style_Main_Example_label_1_main;
	lv_style_reset(&style_Main_Example_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_label_1_main
	lv_style_set_radius(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Main_Example_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_label_1, LV_LABEL_PART_MAIN, &style_Main_Example_label_1_main);
	lv_obj_set_pos(ui->Main_Example_label_1, 15, 142);
	lv_obj_set_size(ui->Main_Example_label_1, 290, 0);

	//Write codes Main_Example_label_2
	ui->Main_Example_label_2 = lv_label_create(ui->Main_Example, NULL);
	lv_label_set_text(ui->Main_Example_label_2, "HEADERS");
	lv_label_set_long_mode(ui->Main_Example_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Main_Example_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Main_Example_label_2
	static lv_style_t style_Main_Example_label_2_main;
	lv_style_reset(&style_Main_Example_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_label_2_main
	lv_style_set_radius(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Main_Example_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_label_2, LV_LABEL_PART_MAIN, &style_Main_Example_label_2_main);
	lv_obj_set_pos(ui->Main_Example_label_2, 10, 142);
	lv_obj_set_size(ui->Main_Example_label_2, 100, 0);

	//Write codes Main_Example_label_3
	ui->Main_Example_label_3 = lv_label_create(ui->Main_Example, NULL);
	lv_label_set_text(ui->Main_Example_label_3, "HEADERS");
	lv_label_set_long_mode(ui->Main_Example_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Main_Example_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Main_Example_label_3
	static lv_style_t style_Main_Example_label_3_main;
	lv_style_reset(&style_Main_Example_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_Main_Example_label_3_main
	lv_style_set_radius(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Main_Example_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Main_Example_label_3, LV_LABEL_PART_MAIN, &style_Main_Example_label_3_main);
	lv_obj_set_pos(ui->Main_Example_label_3, 210, 142);
	lv_obj_set_size(ui->Main_Example_label_3, 100, 0);
}