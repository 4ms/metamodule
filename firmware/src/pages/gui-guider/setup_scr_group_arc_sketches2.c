/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_group_arc_sketches2(lv_ui *ui){

	//Write codes group_arc_sketches2
	ui->group_arc_sketches2 = lv_obj_create(NULL, NULL);

	//Write codes group_arc_sketches2_arc_1
	ui->group_arc_sketches2_arc_1 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_1
	static lv_style_t style_group_arc_sketches2_arc_1_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_1_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_1_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_1, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_1
	static lv_style_t style_group_arc_sketches2_arc_1_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_1_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0x96));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_1_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_1, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_1_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_1, 138.5, 99);
	lv_obj_set_size(ui->group_arc_sketches2_arc_1, 43, 43);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_1, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_1, 120, 220);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches2_arc_2
	ui->group_arc_sketches2_arc_2 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_2
	static lv_style_t style_group_arc_sketches2_arc_2_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_2_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_2_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_2, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_2_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_2
	static lv_style_t style_group_arc_sketches2_arc_2_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_2_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_2_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_2_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_2, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_2_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_2, 126, 87);
	lv_obj_set_size(ui->group_arc_sketches2_arc_2, 68, 68);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_2, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_2, 120, 300);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_2, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_2, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches2_arc_4
	ui->group_arc_sketches2_arc_4 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_4
	static lv_style_t style_group_arc_sketches2_arc_4_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_4_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_4_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_4, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_4_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_4
	static lv_style_t style_group_arc_sketches2_arc_4_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_4_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_4_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_4_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_4, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_4_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_4, 113, 74);
	lv_obj_set_size(ui->group_arc_sketches2_arc_4, 94, 94);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_4, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_4, 120, 300);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_4, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_4, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches2_arc_3
	ui->group_arc_sketches2_arc_3 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_3
	static lv_style_t style_group_arc_sketches2_arc_3_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_3_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_3_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_3, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_3_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_3
	static lv_style_t style_group_arc_sketches2_arc_3_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_3_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_3_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_3_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_3, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_3_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_3, 100, 61);
	lv_obj_set_size(ui->group_arc_sketches2_arc_3, 120, 120);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_3, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_3, 120, 2);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_3, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_3, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches2_arc_5
	ui->group_arc_sketches2_arc_5 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_5
	static lv_style_t style_group_arc_sketches2_arc_5_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_5_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_5_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_5, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_5_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_5
	static lv_style_t style_group_arc_sketches2_arc_5_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_5_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_5_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_5_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_5, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_5_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_5, 87, 48);
	lv_obj_set_size(ui->group_arc_sketches2_arc_5, 146, 146);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_5, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_5, 120, 2);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_5, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_5, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes group_arc_sketches2_arc_6
	ui->group_arc_sketches2_arc_6 = lv_arc_create(ui->group_arc_sketches2, NULL);

	//Write style LV_ARC_PART_BG for group_arc_sketches2_arc_6
	static lv_style_t style_group_arc_sketches2_arc_6_bg;
	lv_style_reset(&style_group_arc_sketches2_arc_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_6_bg
	lv_style_set_bg_color(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_6_bg, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_6, LV_ARC_PART_BG, &style_group_arc_sketches2_arc_6_bg);

	//Write style LV_ARC_PART_INDIC for group_arc_sketches2_arc_6
	static lv_style_t style_group_arc_sketches2_arc_6_indic;
	lv_style_reset(&style_group_arc_sketches2_arc_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_group_arc_sketches2_arc_6_indic
	lv_style_set_line_color(&style_group_arc_sketches2_arc_6_indic, LV_STATE_DEFAULT, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_line_width(&style_group_arc_sketches2_arc_6_indic, LV_STATE_DEFAULT, 9);
	lv_obj_add_style(ui->group_arc_sketches2_arc_6, LV_ARC_PART_INDIC, &style_group_arc_sketches2_arc_6_indic);
	lv_obj_set_pos(ui->group_arc_sketches2_arc_6, 73.5, 34);
	lv_obj_set_size(ui->group_arc_sketches2_arc_6, 173, 173);
	lv_arc_set_bg_angles(ui->group_arc_sketches2_arc_6, 120, 60);
	lv_arc_set_angles(ui->group_arc_sketches2_arc_6, 120, 2);
	lv_arc_set_rotation(ui->group_arc_sketches2_arc_6, 0);
	lv_obj_set_style_local_pad_top(ui->group_arc_sketches2_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->group_arc_sketches2_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->group_arc_sketches2_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->group_arc_sketches2_arc_6, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
}