/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

void setup_scr_Knob_view(lv_ui *ui)
{

	//Write codes Knob_view
	ui->Knob_view = lv_obj_create(NULL, NULL);

	//Write codes Knob_view_arc_1
	ui->Knob_view_arc_1 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_1
	static lv_style_t style_Knob_view_arc_1_bg;
	lv_style_reset(&style_Knob_view_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_1_bg
	lv_style_set_bg_color(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_1_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_1, LV_ARC_PART_BG, &style_Knob_view_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_1
	static lv_style_t style_Knob_view_arc_1_indic;
	lv_style_reset(&style_Knob_view_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_1_indic
	lv_style_set_line_color(&style_Knob_view_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_Knob_view_arc_1_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_1, LV_ARC_PART_INDIC, &style_Knob_view_arc_1_indic);
	lv_obj_set_pos(ui->Knob_view_arc_1, 30, 75);
	lv_obj_set_size(ui->Knob_view_arc_1, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_1, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_1, 120, 300);
	lv_arc_set_rotation(ui->Knob_view_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_2
	ui->Knob_view_arc_2 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_2
	static lv_style_t style_Knob_view_arc_2_bg;
	lv_style_reset(&style_Knob_view_arc_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_2_bg
	lv_style_set_bg_color(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_2_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_2, LV_ARC_PART_BG, &style_Knob_view_arc_2_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_2
	static lv_style_t style_Knob_view_arc_2_indic;
	lv_style_reset(&style_Knob_view_arc_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_2_indic
	lv_style_set_line_color(&style_Knob_view_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_Knob_view_arc_2_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_2, LV_ARC_PART_INDIC, &style_Knob_view_arc_2_indic);
	lv_obj_set_pos(ui->Knob_view_arc_2, 30, 10);
	lv_obj_set_size(ui->Knob_view_arc_2, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_2, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_2, 120, 220);
	lv_arc_set_rotation(ui->Knob_view_arc_2, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_3
	ui->Knob_view_arc_3 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_3
	static lv_style_t style_Knob_view_arc_3_bg;
	lv_style_reset(&style_Knob_view_arc_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_3_bg
	lv_style_set_bg_color(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_3_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_3, LV_ARC_PART_BG, &style_Knob_view_arc_3_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_3
	static lv_style_t style_Knob_view_arc_3_indic;
	lv_style_reset(&style_Knob_view_arc_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_3_indic
	lv_style_set_line_color(&style_Knob_view_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_line_width(&style_Knob_view_arc_3_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_3, LV_ARC_PART_INDIC, &style_Knob_view_arc_3_indic);
	lv_obj_set_pos(ui->Knob_view_arc_3, 130, 10);
	lv_obj_set_size(ui->Knob_view_arc_3, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_3, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_3, 120, 150);
	lv_arc_set_rotation(ui->Knob_view_arc_3, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_4
	ui->Knob_view_arc_4 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_4
	static lv_style_t style_Knob_view_arc_4_bg;
	lv_style_reset(&style_Knob_view_arc_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_4_bg
	lv_style_set_bg_color(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_4_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_4, LV_ARC_PART_BG, &style_Knob_view_arc_4_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_4
	static lv_style_t style_Knob_view_arc_4_indic;
	lv_style_reset(&style_Knob_view_arc_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_4_indic
	lv_style_set_line_color(&style_Knob_view_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_Knob_view_arc_4_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_4, LV_ARC_PART_INDIC, &style_Knob_view_arc_4_indic);
	lv_obj_set_pos(ui->Knob_view_arc_4, 230, 75);
	lv_obj_set_size(ui->Knob_view_arc_4, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_4, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_4, 120, 10);
	lv_arc_set_rotation(ui->Knob_view_arc_4, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_5
	ui->Knob_view_arc_5 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_5
	static lv_style_t style_Knob_view_arc_5_bg;
	lv_style_reset(&style_Knob_view_arc_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_5_bg
	lv_style_set_bg_color(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_5_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_5, LV_ARC_PART_BG, &style_Knob_view_arc_5_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_5
	static lv_style_t style_Knob_view_arc_5_indic;
	lv_style_reset(&style_Knob_view_arc_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_5_indic
	lv_style_set_line_color(&style_Knob_view_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x88, 0xd7, 0xc9));
	lv_style_set_line_width(&style_Knob_view_arc_5_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_5, LV_ARC_PART_INDIC, &style_Knob_view_arc_5_indic);
	lv_obj_set_pos(ui->Knob_view_arc_5, 130, 75);
	lv_obj_set_size(ui->Knob_view_arc_5, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_5, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_5, 120, 30);
	lv_arc_set_rotation(ui->Knob_view_arc_5, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_6
	ui->Knob_view_arc_6 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_6
	static lv_style_t style_Knob_view_arc_6_bg;
	lv_style_reset(&style_Knob_view_arc_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_6_bg
	lv_style_set_bg_color(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_6_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_6, LV_ARC_PART_BG, &style_Knob_view_arc_6_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_6
	static lv_style_t style_Knob_view_arc_6_indic;
	lv_style_reset(&style_Knob_view_arc_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_6_indic
	lv_style_set_line_color(&style_Knob_view_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_Knob_view_arc_6_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->Knob_view_arc_6, LV_ARC_PART_INDIC, &style_Knob_view_arc_6_indic);
	lv_obj_set_pos(ui->Knob_view_arc_6, 230, 10);
	lv_obj_set_size(ui->Knob_view_arc_6, 60, 60);
	lv_arc_set_bg_angles(ui->Knob_view_arc_6, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_6, 120, 2);
	lv_arc_set_rotation(ui->Knob_view_arc_6, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_label_1
	ui->Knob_view_label_1 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_1, "");
	lv_label_set_long_mode(ui->Knob_view_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_1
	static lv_style_t style_Knob_view_label_1_main;
	lv_style_reset(&style_Knob_view_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_1_main
	lv_style_set_radius(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_letter_space(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_1, LV_LABEL_PART_MAIN, &style_Knob_view_label_1_main);
	lv_obj_set_pos(ui->Knob_view_label_1, 10, 147);
	lv_obj_set_size(ui->Knob_view_label_1, 300, 0);

	//Write codes Knob_view_label_2
	ui->Knob_view_label_2 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_2, "LBL1");
	lv_label_set_long_mode(ui->Knob_view_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_2
	static lv_style_t style_Knob_view_label_2_main;
	lv_style_reset(&style_Knob_view_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_2_main
	lv_style_set_radius(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_2, LV_LABEL_PART_MAIN, &style_Knob_view_label_2_main);
	lv_obj_set_pos(ui->Knob_view_label_2, 10, 150);
	lv_obj_set_size(ui->Knob_view_label_2, 40, 0);

	//Write codes Knob_view_arc_7
	ui->Knob_view_arc_7 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_7
	static lv_style_t style_Knob_view_arc_7_bg;
	lv_style_reset(&style_Knob_view_arc_7_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_7_bg
	lv_style_set_bg_color(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_7_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_7, LV_ARC_PART_BG, &style_Knob_view_arc_7_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_7
	static lv_style_t style_Knob_view_arc_7_indic;
	lv_style_reset(&style_Knob_view_arc_7_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_7_indic
	lv_style_set_line_color(&style_Knob_view_arc_7_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_7_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_7, LV_ARC_PART_INDIC, &style_Knob_view_arc_7_indic);
	lv_obj_set_pos(ui->Knob_view_arc_7, 10, 180);
	lv_obj_set_size(ui->Knob_view_arc_7, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_7, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_7, 120, 220);
	lv_arc_set_rotation(ui->Knob_view_arc_7, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_8
	ui->Knob_view_arc_8 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_8
	static lv_style_t style_Knob_view_arc_8_bg;
	lv_style_reset(&style_Knob_view_arc_8_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_8_bg
	lv_style_set_bg_color(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_8_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_8, LV_ARC_PART_BG, &style_Knob_view_arc_8_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_8
	static lv_style_t style_Knob_view_arc_8_indic;
	lv_style_reset(&style_Knob_view_arc_8_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_8_indic
	lv_style_set_line_color(&style_Knob_view_arc_8_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_8_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_8, LV_ARC_PART_INDIC, &style_Knob_view_arc_8_indic);
	lv_obj_set_pos(ui->Knob_view_arc_8, 113, 180);
	lv_obj_set_size(ui->Knob_view_arc_8, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_8, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_8, 120, 150);
	lv_arc_set_rotation(ui->Knob_view_arc_8, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_9
	ui->Knob_view_arc_9 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_9
	static lv_style_t style_Knob_view_arc_9_bg;
	lv_style_reset(&style_Knob_view_arc_9_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_9_bg
	lv_style_set_bg_color(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_9_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_9, LV_ARC_PART_BG, &style_Knob_view_arc_9_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_9
	static lv_style_t style_Knob_view_arc_9_indic;
	lv_style_reset(&style_Knob_view_arc_9_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_9_indic
	lv_style_set_line_color(&style_Knob_view_arc_9_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_9_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_9, LV_ARC_PART_INDIC, &style_Knob_view_arc_9_indic);
	lv_obj_set_pos(ui->Knob_view_arc_9, 216, 180);
	lv_obj_set_size(ui->Knob_view_arc_9, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_9, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_9, 120, 2);
	lv_arc_set_rotation(ui->Knob_view_arc_9, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_10
	ui->Knob_view_arc_10 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_10
	static lv_style_t style_Knob_view_arc_10_bg;
	lv_style_reset(&style_Knob_view_arc_10_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_10_bg
	lv_style_set_bg_color(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_10_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_10, LV_ARC_PART_BG, &style_Knob_view_arc_10_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_10
	static lv_style_t style_Knob_view_arc_10_indic;
	lv_style_reset(&style_Knob_view_arc_10_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_10_indic
	lv_style_set_line_color(&style_Knob_view_arc_10_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_10_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_10, LV_ARC_PART_INDIC, &style_Knob_view_arc_10_indic);
	lv_obj_set_pos(ui->Knob_view_arc_10, 268, 180);
	lv_obj_set_size(ui->Knob_view_arc_10, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_10, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_10, 120, 10);
	lv_arc_set_rotation(ui->Knob_view_arc_10, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_11
	ui->Knob_view_arc_11 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_11
	static lv_style_t style_Knob_view_arc_11_bg;
	lv_style_reset(&style_Knob_view_arc_11_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_11_bg
	lv_style_set_bg_color(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_11_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_11, LV_ARC_PART_BG, &style_Knob_view_arc_11_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_11
	static lv_style_t style_Knob_view_arc_11_indic;
	lv_style_reset(&style_Knob_view_arc_11_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_11_indic
	lv_style_set_line_color(&style_Knob_view_arc_11_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_11_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_11, LV_ARC_PART_INDIC, &style_Knob_view_arc_11_indic);
	lv_obj_set_pos(ui->Knob_view_arc_11, 164, 180);
	lv_obj_set_size(ui->Knob_view_arc_11, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_11, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_11, 120, 30);
	lv_arc_set_rotation(ui->Knob_view_arc_11, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_arc_12
	ui->Knob_view_arc_12 = lv_arc_create(ui->Knob_view, NULL);

	//Write style LV_ARC_PART_BG for Knob_view_arc_12
	static lv_style_t style_Knob_view_arc_12_bg;
	lv_style_reset(&style_Knob_view_arc_12_bg);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_12_bg
	lv_style_set_bg_color(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_Knob_view_arc_12_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_12, LV_ARC_PART_BG, &style_Knob_view_arc_12_bg);

	//Write style LV_ARC_PART_INDIC for Knob_view_arc_12
	static lv_style_t style_Knob_view_arc_12_indic;
	lv_style_reset(&style_Knob_view_arc_12_indic);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_arc_12_indic
	lv_style_set_line_color(&style_Knob_view_arc_12_indic, LV_STATE_DEFAULT, lv_color_make(0x75, 0xa9, 0xd1));
	lv_style_set_line_width(&style_Knob_view_arc_12_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->Knob_view_arc_12, LV_ARC_PART_INDIC, &style_Knob_view_arc_12_indic);
	lv_obj_set_pos(ui->Knob_view_arc_12, 61, 180);
	lv_obj_set_size(ui->Knob_view_arc_12, 40, 40);
	lv_arc_set_bg_angles(ui->Knob_view_arc_12, 120, 60);
	lv_arc_set_angles(ui->Knob_view_arc_12, 120, 300);
	lv_arc_set_rotation(ui->Knob_view_arc_12, 0);
	lv_obj_set_style_local_pad_top(ui->Knob_view_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->Knob_view_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->Knob_view_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->Knob_view_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes Knob_view_label_3
	ui->Knob_view_label_3 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_3, "LBL2");
	lv_label_set_long_mode(ui->Knob_view_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_3
	static lv_style_t style_Knob_view_label_3_main;
	lv_style_reset(&style_Knob_view_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_3_main
	lv_style_set_radius(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_3, LV_LABEL_PART_MAIN, &style_Knob_view_label_3_main);
	lv_obj_set_pos(ui->Knob_view_label_3, 61, 150);
	lv_obj_set_size(ui->Knob_view_label_3, 40, 0);

	//Write codes Knob_view_label_4
	ui->Knob_view_label_4 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_4, "LBL3");
	lv_label_set_long_mode(ui->Knob_view_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_4
	static lv_style_t style_Knob_view_label_4_main;
	lv_style_reset(&style_Knob_view_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_4_main
	lv_style_set_radius(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_4, LV_LABEL_PART_MAIN, &style_Knob_view_label_4_main);
	lv_obj_set_pos(ui->Knob_view_label_4, 114, 150);
	lv_obj_set_size(ui->Knob_view_label_4, 40, 0);

	//Write codes Knob_view_label_5
	ui->Knob_view_label_5 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_5, "LBL4");
	lv_label_set_long_mode(ui->Knob_view_label_5, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_5, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_5
	static lv_style_t style_Knob_view_label_5_main;
	lv_style_reset(&style_Knob_view_label_5_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_5_main
	lv_style_set_radius(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_5, LV_LABEL_PART_MAIN, &style_Knob_view_label_5_main);
	lv_obj_set_pos(ui->Knob_view_label_5, 165, 150);
	lv_obj_set_size(ui->Knob_view_label_5, 40, 0);

	//Write codes Knob_view_label_6
	ui->Knob_view_label_6 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_6, "LBL5");
	lv_label_set_long_mode(ui->Knob_view_label_6, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_6, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_6
	static lv_style_t style_Knob_view_label_6_main;
	lv_style_reset(&style_Knob_view_label_6_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_6_main
	lv_style_set_radius(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_6, LV_LABEL_PART_MAIN, &style_Knob_view_label_6_main);
	lv_obj_set_pos(ui->Knob_view_label_6, 216, 150);
	lv_obj_set_size(ui->Knob_view_label_6, 40, 0);

	//Write codes Knob_view_label_7
	ui->Knob_view_label_7 = lv_label_create(ui->Knob_view, NULL);
	lv_label_set_text(ui->Knob_view_label_7, "LBL6");
	lv_label_set_long_mode(ui->Knob_view_label_7, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Knob_view_label_7, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Knob_view_label_7
	static lv_style_t style_Knob_view_label_7_main;
	lv_style_reset(&style_Knob_view_label_7_main);

	//Write style state: LV_STATE_DEFAULT for style_Knob_view_label_7_main
	lv_style_set_radius(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_color(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_bg_grad_dir(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, &lv_font_MuseoSansCondensed_700_13);
	lv_style_set_text_letter_space(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Knob_view_label_7_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Knob_view_label_7, LV_LABEL_PART_MAIN, &style_Knob_view_label_7_main);
	lv_obj_set_pos(ui->Knob_view_label_7, 269, 150);
	lv_obj_set_size(ui->Knob_view_label_7, 40, 0);
}
