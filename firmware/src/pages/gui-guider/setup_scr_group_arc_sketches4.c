/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_group_arc_sketches4(lv_ui *ui){

	//Write codes group_arc_sketches4
	ui->group_arc_sketches4 = lv_obj_create(NULL, NULL);

	//Write codes group_arc_sketches4_arc_1
	ui->group_arc_sketches4_arc_1 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_1
	static lv_style_t style_group_arc_sketches4_arc_1_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_1_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_1_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_1, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_1
	static lv_style_t style_group_arc_sketches4_arc_1_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_1_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_1_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_1, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_1_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_1, 78, 99);
	lv_obj_set_size(ui->group_arc_sketches4_arc_1, 43, 43);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_1, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_1, 120, 175);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_2
	ui->group_arc_sketches4_arc_2 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_2
	static lv_style_t style_group_arc_sketches4_arc_2_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_2_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_2_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_2, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_2_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_2
	static lv_style_t style_group_arc_sketches4_arc_2_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_2_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_2_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_2, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_2_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_2, 65, 87);
	lv_obj_set_size(ui->group_arc_sketches4_arc_2, 68, 68);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_2, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_2, 120, 200);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_2, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_4
	ui->group_arc_sketches4_arc_4 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_4
	static lv_style_t style_group_arc_sketches4_arc_4_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_4_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_4_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_4, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_4_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_4
	static lv_style_t style_group_arc_sketches4_arc_4_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_4_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_4_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_4, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_4_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_4, 52, 74);
	lv_obj_set_size(ui->group_arc_sketches4_arc_4, 94, 94);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_4, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_4, 120, 210);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_4, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_3
	ui->group_arc_sketches4_arc_3 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_3
	static lv_style_t style_group_arc_sketches4_arc_3_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_3_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_3_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_3, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_3_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_3
	static lv_style_t style_group_arc_sketches4_arc_3_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_3_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_3_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_3, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_3_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_3, 38, 61);
	lv_obj_set_size(ui->group_arc_sketches4_arc_3, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_3, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_3, 120, 220);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_3, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_5
	ui->group_arc_sketches4_arc_5 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_5
	static lv_style_t style_group_arc_sketches4_arc_5_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_5_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_5_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_5, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_5_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_5
	static lv_style_t style_group_arc_sketches4_arc_5_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_5_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_5_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_5, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_5_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_5, 24, 48);
	lv_obj_set_size(ui->group_arc_sketches4_arc_5, 146, 146);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_5, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_5, 120, 225);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_5, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_6
	ui->group_arc_sketches4_arc_6 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_6
	static lv_style_t style_group_arc_sketches4_arc_6_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_6_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_6_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_6, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_6_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_6
	static lv_style_t style_group_arc_sketches4_arc_6_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_6_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_6_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_6, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_6_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_6, 10, 34);
	lv_obj_set_size(ui->group_arc_sketches4_arc_6, 173, 173);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_6, 120, 240);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_6, 120, 230);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_6, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_12
	ui->group_arc_sketches4_arc_12 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_12
	static lv_style_t style_group_arc_sketches4_arc_12_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_12_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_12_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_12_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_12, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_12_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_12
	static lv_style_t style_group_arc_sketches4_arc_12_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_12_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_12_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_12_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_12_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_12, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_12_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_12, 146, 61);
	lv_obj_set_size(ui->group_arc_sketches4_arc_12, 173, 173);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_12, 180, 270);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_12, 180, 250);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_12, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_12, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_11
	ui->group_arc_sketches4_arc_11 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_11
	static lv_style_t style_group_arc_sketches4_arc_11_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_11_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_11_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_11_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_11, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_11_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_11
	static lv_style_t style_group_arc_sketches4_arc_11_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_11_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_11_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_11_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_11_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_11, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_11_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_11, 160, 74);
	lv_obj_set_size(ui->group_arc_sketches4_arc_11, 146, 146);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_11, 180, 269);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_11, 180, 245);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_11, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_11, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_10
	ui->group_arc_sketches4_arc_10 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_10
	static lv_style_t style_group_arc_sketches4_arc_10_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_10_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_10_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_10_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_10, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_10_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_10
	static lv_style_t style_group_arc_sketches4_arc_10_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_10_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_10_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_10_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_10_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_10, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_10_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_10, 174, 87);
	lv_obj_set_size(ui->group_arc_sketches4_arc_10, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_10, 180, 267);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_10, 180, 237);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_10, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_10, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_9
	ui->group_arc_sketches4_arc_9 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_9
	static lv_style_t style_group_arc_sketches4_arc_9_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_9_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_9_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_9_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_9, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_9_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_9
	static lv_style_t style_group_arc_sketches4_arc_9_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_9_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_9_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_9_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_9_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_9, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_9_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_9, 188, 100);
	lv_obj_set_size(ui->group_arc_sketches4_arc_9, 94, 94);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_9, 180, 264);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_9, 180, 230);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_9, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_9, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches4_arc_8
	ui->group_arc_sketches4_arc_8 = lv_arc_create(ui->group_arc_sketches4, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches4_arc_8
	static lv_style_t style_group_arc_sketches4_arc_8_bg;
	lv_style_reset(&style_group_arc_sketches4_arc_8_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_8_bg
	lv_style_set_bg_color(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_8_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_8, LV_ARC_PART_BG, &style_group_arc_sketches4_arc_8_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches4_arc_8
	static lv_style_t style_group_arc_sketches4_arc_8_indic;
	lv_style_reset(&style_group_arc_sketches4_arc_8_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches4_arc_8_indic
	lv_style_set_line_color(&style_group_arc_sketches4_arc_8_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_line_width(&style_group_arc_sketches4_arc_8_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches4_arc_8, LV_ARC_PART_INDIC, &style_group_arc_sketches4_arc_8_indic);
	lv_obj_set_pos(ui->group_arc_sketches4_arc_8, 201, 113);
	lv_obj_set_size(ui->group_arc_sketches4_arc_8, 68, 68);
	lv_arc_set_bg_angles(ui->group_arc_sketches4_arc_8, 180, 260);
	lv_arc_set_angles(ui->group_arc_sketches4_arc_8, 180, 207);
	lv_arc_set_rotation(ui->group_arc_sketches4_arc_8, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches4_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches4_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches4_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches4_arc_8, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
}