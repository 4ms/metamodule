/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_group_arc_sketches(lv_ui *ui){

	//Write codes group_arc_sketches
	ui->group_arc_sketches = lv_obj_create(NULL, NULL);

	//Write codes group_arc_sketches_arc_1
	ui->group_arc_sketches_arc_1 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_1
	static lv_style_t style_group_arc_sketches_arc_1_bg;
	lv_style_reset(&style_group_arc_sketches_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_1_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_1_bg, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_1, LV_ARC_PART_BG, &style_group_arc_sketches_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_1
	static lv_style_t style_group_arc_sketches_arc_1_indic;
	lv_style_reset(&style_group_arc_sketches_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_1_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches_arc_1_indic, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_1, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_1_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_1, 236, 44);
	lv_obj_set_size(ui->group_arc_sketches_arc_1, 43, 43);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_1, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches_arc_1, 120, 220);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_2
	ui->group_arc_sketches_arc_2 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_2
	static lv_style_t style_group_arc_sketches_arc_2_bg;
	lv_style_reset(&style_group_arc_sketches_arc_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_2_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_2_bg, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_2, LV_ARC_PART_BG, &style_group_arc_sketches_arc_2_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_2
	static lv_style_t style_group_arc_sketches_arc_2_indic;
	lv_style_reset(&style_group_arc_sketches_arc_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_2_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches_arc_2_indic, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_2, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_2_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_2, 217, 26);
	lv_obj_set_size(ui->group_arc_sketches_arc_2, 80, 80);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_2, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches_arc_2, 120, 300);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_2, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_3
	ui->group_arc_sketches_arc_3 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_3
	static lv_style_t style_group_arc_sketches_arc_3_bg;
	lv_style_reset(&style_group_arc_sketches_arc_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_3_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_3_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_3, LV_ARC_PART_BG, &style_group_arc_sketches_arc_3_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_3
	static lv_style_t style_group_arc_sketches_arc_3_indic;
	lv_style_reset(&style_group_arc_sketches_arc_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_3_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches_arc_3_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_3, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_3_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_3, 197, 6);
	lv_obj_set_size(ui->group_arc_sketches_arc_3, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_3, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches_arc_3, 120, 2);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_3, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_4
	ui->group_arc_sketches_arc_4 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_4
	static lv_style_t style_group_arc_sketches_arc_4_bg;
	lv_style_reset(&style_group_arc_sketches_arc_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_4_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_4_bg, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_4, LV_ARC_PART_BG, &style_group_arc_sketches_arc_4_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_4
	static lv_style_t style_group_arc_sketches_arc_4_indic;
	lv_style_reset(&style_group_arc_sketches_arc_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_4_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches_arc_4_indic, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_4, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_4_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_4, 38, 46);
	lv_obj_set_size(ui->group_arc_sketches_arc_4, 43, 43);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_4, 90, 270);
	lv_arc_set_angles(ui->group_arc_sketches_arc_4, 90, 150);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_4, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_5
	ui->group_arc_sketches_arc_5 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_5
	static lv_style_t style_group_arc_sketches_arc_5_bg;
	lv_style_reset(&style_group_arc_sketches_arc_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_5_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_5_bg, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_5, LV_ARC_PART_BG, &style_group_arc_sketches_arc_5_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_5
	static lv_style_t style_group_arc_sketches_arc_5_indic;
	lv_style_reset(&style_group_arc_sketches_arc_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_5_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches_arc_5_indic, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_5, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_5_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_5, 20, 28);
	lv_obj_set_size(ui->group_arc_sketches_arc_5, 80, 80);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_5, 90, 270);
	lv_arc_set_angles(ui->group_arc_sketches_arc_5, 90, 180);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_5, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_6
	ui->group_arc_sketches_arc_6 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_6
	static lv_style_t style_group_arc_sketches_arc_6_bg;
	lv_style_reset(&style_group_arc_sketches_arc_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_6_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_6_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_6, LV_ARC_PART_BG, &style_group_arc_sketches_arc_6_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_6
	static lv_style_t style_group_arc_sketches_arc_6_indic;
	lv_style_reset(&style_group_arc_sketches_arc_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_6_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches_arc_6_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_6, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_6_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_6, 1, 8);
	lv_obj_set_size(ui->group_arc_sketches_arc_6, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_6, 90, 270);
	lv_arc_set_angles(ui->group_arc_sketches_arc_6, 90, 230);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_6, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_7
	ui->group_arc_sketches_arc_7 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_7
	static lv_style_t style_group_arc_sketches_arc_7_bg;
	lv_style_reset(&style_group_arc_sketches_arc_7_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_7_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_7_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_7, LV_ARC_PART_BG, &style_group_arc_sketches_arc_7_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_7
	static lv_style_t style_group_arc_sketches_arc_7_indic;
	lv_style_reset(&style_group_arc_sketches_arc_7_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_7_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_7_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches_arc_7_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->group_arc_sketches_arc_7, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_7_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_7, 100, 117);
	lv_obj_set_size(ui->group_arc_sketches_arc_7, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_7, 90, 270);
	lv_arc_set_angles(ui->group_arc_sketches_arc_7, 90, 230);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_7, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_7, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_8
	ui->group_arc_sketches_arc_8 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_8
	static lv_style_t style_group_arc_sketches_arc_8_bg;
	lv_style_reset(&style_group_arc_sketches_arc_8_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_8_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_8_bg, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_8, LV_ARC_PART_BG, &style_group_arc_sketches_arc_8_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_8
	static lv_style_t style_group_arc_sketches_arc_8_indic;
	lv_style_reset(&style_group_arc_sketches_arc_8_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_8_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_8_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches_arc_8_indic, LV_STATE_DEFAULT, 15);
	lv_obj_add_style(ui->group_arc_sketches_arc_8, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_8_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_8, 119, 137);
	lv_obj_set_size(ui->group_arc_sketches_arc_8, 80, 80);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_8, 90, 260);
	lv_arc_set_angles(ui->group_arc_sketches_arc_8, 90, 180);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_8, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_9
	ui->group_arc_sketches_arc_9 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_9
	static lv_style_t style_group_arc_sketches_arc_9_bg;
	lv_style_reset(&style_group_arc_sketches_arc_9_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_9_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_9_bg, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_9, LV_ARC_PART_BG, &style_group_arc_sketches_arc_9_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_9
	static lv_style_t style_group_arc_sketches_arc_9_indic;
	lv_style_reset(&style_group_arc_sketches_arc_9_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_9_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_9_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches_arc_9_indic, LV_STATE_DEFAULT, 13);
	lv_obj_add_style(ui->group_arc_sketches_arc_9, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_9_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_9, 137, 155);
	lv_obj_set_size(ui->group_arc_sketches_arc_9, 43, 43);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_9, 90, 240);
	lv_arc_set_angles(ui->group_arc_sketches_arc_9, 90, 120);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_9, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_10
	ui->group_arc_sketches_arc_10 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_10
	static lv_style_t style_group_arc_sketches_arc_10_bg;
	lv_style_reset(&style_group_arc_sketches_arc_10_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_10_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_10_bg, LV_STATE_DEFAULT, 12);
	lv_obj_add_style(ui->group_arc_sketches_arc_10, LV_ARC_PART_BG, &style_group_arc_sketches_arc_10_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_10
	static lv_style_t style_group_arc_sketches_arc_10_indic;
	lv_style_reset(&style_group_arc_sketches_arc_10_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_10_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_10_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches_arc_10_indic, LV_STATE_DEFAULT, 12);
	lv_obj_add_style(ui->group_arc_sketches_arc_10, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_10_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_10, 101, 11);
	lv_obj_set_size(ui->group_arc_sketches_arc_10, 100, 100);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_10, 90, 270);
	lv_arc_set_angles(ui->group_arc_sketches_arc_10, 90, 230);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_10, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_11
	ui->group_arc_sketches_arc_11 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_11
	static lv_style_t style_group_arc_sketches_arc_11_bg;
	lv_style_reset(&style_group_arc_sketches_arc_11_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_11_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_11_bg, LV_STATE_DEFAULT, 12);
	lv_obj_add_style(ui->group_arc_sketches_arc_11, LV_ARC_PART_BG, &style_group_arc_sketches_arc_11_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_11
	static lv_style_t style_group_arc_sketches_arc_11_indic;
	lv_style_reset(&style_group_arc_sketches_arc_11_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_11_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_11_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches_arc_11_indic, LV_STATE_DEFAULT, 12);
	lv_obj_add_style(ui->group_arc_sketches_arc_11, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_11_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_11, 117, 26);
	lv_obj_set_size(ui->group_arc_sketches_arc_11, 70, 70);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_11, 90, 250);
	lv_arc_set_angles(ui->group_arc_sketches_arc_11, 90, 180);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_11, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches_arc_12
	ui->group_arc_sketches_arc_12 = lv_arc_create(ui->group_arc_sketches, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches_arc_12
	static lv_style_t style_group_arc_sketches_arc_12_bg;
	lv_style_reset(&style_group_arc_sketches_arc_12_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_12_bg
	lv_style_set_bg_color(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches_arc_12_bg, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->group_arc_sketches_arc_12, LV_ARC_PART_BG, &style_group_arc_sketches_arc_12_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches_arc_12
	static lv_style_t style_group_arc_sketches_arc_12_indic;
	lv_style_reset(&style_group_arc_sketches_arc_12_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches_arc_12_indic
	lv_style_set_line_color(&style_group_arc_sketches_arc_12_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches_arc_12_indic, LV_STATE_DEFAULT, 11);
	lv_obj_add_style(ui->group_arc_sketches_arc_12, LV_ARC_PART_INDIC, &style_group_arc_sketches_arc_12_indic);
	lv_obj_set_pos(ui->group_arc_sketches_arc_12, 132, 40);
	lv_obj_set_size(ui->group_arc_sketches_arc_12, 43, 40);
	lv_arc_set_bg_angles(ui->group_arc_sketches_arc_12, 90, 230);
	lv_arc_set_angles(ui->group_arc_sketches_arc_12, 90, 120);
	lv_arc_set_rotation(ui->group_arc_sketches_arc_12, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
}