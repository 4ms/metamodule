/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

void setup_scr_symbol_sketches(lv_ui *ui)
{

	//Write codes symbol_sketches
	ui->symbol_sketches = lv_obj_create(NULL, NULL);

	//Write codes symbol_sketches_sw_1
	ui->symbol_sketches_sw_1 = lv_switch_create(ui->symbol_sketches, NULL);

	//Write style LV_SWITCH_PART_BG for symbol_sketches_sw_1
	static lv_style_t style_symbol_sketches_sw_1_bg;
	lv_style_reset(&style_symbol_sketches_sw_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_sw_1_bg
	lv_style_set_radius(&style_symbol_sketches_sw_1_bg, LV_STATE_DEFAULT, 100);
	lv_style_set_bg_color(&style_symbol_sketches_sw_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_symbol_sketches_sw_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_sw_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_sw_1_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_sw_1, LV_SWITCH_PART_BG, &style_symbol_sketches_sw_1_bg);

	//Write style LV_SWITCH_PART_INDIC for symbol_sketches_sw_1
	static lv_style_t style_symbol_sketches_sw_1_indic;
	lv_style_reset(&style_symbol_sketches_sw_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_sw_1_indic
	lv_style_set_radius(&style_symbol_sketches_sw_1_indic, LV_STATE_DEFAULT, 100);
	lv_style_set_bg_color(&style_symbol_sketches_sw_1_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_symbol_sketches_sw_1_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_sw_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_sw_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_sw_1, LV_SWITCH_PART_INDIC, &style_symbol_sketches_sw_1_indic);

	//Write style LV_SWITCH_PART_KNOB for symbol_sketches_sw_1
	static lv_style_t style_symbol_sketches_sw_1_knob;
	lv_style_reset(&style_symbol_sketches_sw_1_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_sw_1_knob
	lv_style_set_radius(&style_symbol_sketches_sw_1_knob, LV_STATE_DEFAULT, 100);
	lv_style_set_bg_color(&style_symbol_sketches_sw_1_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_color(&style_symbol_sketches_sw_1_knob, LV_STATE_DEFAULT, lv_color_make(0xfa, 0xf0, 0xf0));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_sw_1_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_sw_1_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_sw_1, LV_SWITCH_PART_KNOB, &style_symbol_sketches_sw_1_knob);
	lv_obj_set_pos(ui->symbol_sketches_sw_1, 107, 16);
	lv_obj_set_size(ui->symbol_sketches_sw_1, 40, 20);
	lv_switch_set_anim_time(ui->symbol_sketches_sw_1, 600);

	//Write codes symbol_sketches_arc_1
	ui->symbol_sketches_arc_1 = lv_arc_create(ui->symbol_sketches, NULL);

	//Write style LV_ARC_PART_BG for symbol_sketches_arc_1
	static lv_style_t style_symbol_sketches_arc_1_bg;
	lv_style_reset(&style_symbol_sketches_arc_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_arc_1_bg
	lv_style_set_bg_color(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_line_width(&style_symbol_sketches_arc_1_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->symbol_sketches_arc_1, LV_ARC_PART_BG, &style_symbol_sketches_arc_1_bg);

	//Write style LV_ARC_PART_INDIC for symbol_sketches_arc_1
	static lv_style_t style_symbol_sketches_arc_1_indic;
	lv_style_reset(&style_symbol_sketches_arc_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_arc_1_indic
	lv_style_set_line_color(&style_symbol_sketches_arc_1_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_line_width(&style_symbol_sketches_arc_1_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->symbol_sketches_arc_1, LV_ARC_PART_INDIC, &style_symbol_sketches_arc_1_indic);
	lv_obj_set_pos(ui->symbol_sketches_arc_1, 238, 16);
	lv_obj_set_size(ui->symbol_sketches_arc_1, 60, 60);
	lv_arc_set_bg_angles(ui->symbol_sketches_arc_1, 0, 360);
	lv_arc_set_angles(ui->symbol_sketches_arc_1, 120, 220);
	lv_arc_set_rotation(ui->symbol_sketches_arc_1, 0);
	lv_obj_set_style_local_pad_top(ui->symbol_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->symbol_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_left(ui->symbol_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_right(ui->symbol_sketches_arc_1, LV_ARC_PART_BG, LV_STATE_DEFAULT, 0);

	//Write codes symbol_sketches_slider_1
	ui->symbol_sketches_slider_1 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_1
	static lv_style_t style_symbol_sketches_slider_1_indic;
	lv_style_reset(&style_symbol_sketches_slider_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_1_indic
	lv_style_set_radius(&style_symbol_sketches_slider_1_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_1, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_1_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_1
	static lv_style_t style_symbol_sketches_slider_1_bg;
	lv_style_reset(&style_symbol_sketches_slider_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_1_bg
	lv_style_set_radius(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd7));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd7));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xaf, 0xaf, 0xaf));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_1, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_1_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_1
	static lv_style_t style_symbol_sketches_slider_1_knob;
	lv_style_reset(&style_symbol_sketches_slider_1_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_1_knob
	lv_style_set_radius(&style_symbol_sketches_slider_1_knob, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_slider_1_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_1_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_1_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_1_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_1, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_1_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_1, 21, 105);
	lv_obj_set_size(ui->symbol_sketches_slider_1, 11, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_1, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_1, 50, false);

	//Write codes symbol_sketches_bar_1
	ui->symbol_sketches_bar_1 = lv_bar_create(ui->symbol_sketches, NULL);

	//Write style LV_BAR_PART_BG for symbol_sketches_bar_1
	static lv_style_t style_symbol_sketches_bar_1_bg;
	lv_style_reset(&style_symbol_sketches_bar_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_bar_1_bg
	lv_style_set_radius(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_bar_1, LV_BAR_PART_BG, &style_symbol_sketches_bar_1_bg);

	//Write style LV_BAR_PART_INDIC for symbol_sketches_bar_1
	static lv_style_t style_symbol_sketches_bar_1_indic;
	lv_style_reset(&style_symbol_sketches_bar_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_bar_1_indic
	lv_style_set_radius(&style_symbol_sketches_bar_1_indic, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_bar_1_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_color(&style_symbol_sketches_bar_1_indic, LV_STATE_DEFAULT, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_bar_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_bar_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_bar_1, LV_BAR_PART_INDIC, &style_symbol_sketches_bar_1_indic);
	lv_obj_set_pos(ui->symbol_sketches_bar_1, 65, 58);
	lv_obj_set_size(ui->symbol_sketches_bar_1, 90, 20);
	lv_bar_set_anim_time(ui->symbol_sketches_bar_1, 1000);
	lv_bar_set_value(ui->symbol_sketches_bar_1, 50, LV_ANIM_OFF);
	lv_bar_set_range(ui->symbol_sketches_bar_1, 0, 100);

	//Write codes symbol_sketches_bar_2
	ui->symbol_sketches_bar_2 = lv_bar_create(ui->symbol_sketches, NULL);

	//Write style LV_BAR_PART_BG for symbol_sketches_bar_2
	static lv_style_t style_symbol_sketches_bar_2_bg;
	lv_style_reset(&style_symbol_sketches_bar_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_bar_2_bg
	lv_style_set_radius(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_bar_2_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_bar_2, LV_BAR_PART_BG, &style_symbol_sketches_bar_2_bg);

	//Write style LV_BAR_PART_INDIC for symbol_sketches_bar_2
	static lv_style_t style_symbol_sketches_bar_2_indic;
	lv_style_reset(&style_symbol_sketches_bar_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_bar_2_indic
	lv_style_set_radius(&style_symbol_sketches_bar_2_indic, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_bar_2_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_bg_grad_color(&style_symbol_sketches_bar_2_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0xb4, 0xf0));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_bar_2_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_bar_2_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_bar_2, LV_BAR_PART_INDIC, &style_symbol_sketches_bar_2_indic);
	lv_obj_set_pos(ui->symbol_sketches_bar_2, 20, 9);
	lv_obj_set_size(ui->symbol_sketches_bar_2, 18, 82);
	lv_bar_set_anim_time(ui->symbol_sketches_bar_2, 1000);
	lv_bar_set_value(ui->symbol_sketches_bar_2, 50, LV_ANIM_OFF);
	lv_bar_set_range(ui->symbol_sketches_bar_2, 0, 100);

	//Write codes symbol_sketches_slider_2
	ui->symbol_sketches_slider_2 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_2
	static lv_style_t style_symbol_sketches_slider_2_indic;
	lv_style_reset(&style_symbol_sketches_slider_2_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_2_indic
	lv_style_set_radius(&style_symbol_sketches_slider_2_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_2_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_2_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_2_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_2_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_2, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_2_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_2
	static lv_style_t style_symbol_sketches_slider_2_bg;
	lv_style_reset(&style_symbol_sketches_slider_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_2_bg
	lv_style_set_radius(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_2_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_2, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_2_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_2
	static lv_style_t style_symbol_sketches_slider_2_knob;
	lv_style_reset(&style_symbol_sketches_slider_2_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_2_knob
	lv_style_set_radius(&style_symbol_sketches_slider_2_knob, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_2_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8e, 0xc9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_2_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8d, 0xc9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_2_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_2_knob, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_2, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_2_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_2, 56, 104);
	lv_obj_set_size(ui->symbol_sketches_slider_2, 11, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_2, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_2, 50, false);

	//Write codes symbol_sketches_slider_3
	ui->symbol_sketches_slider_3 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_3
	static lv_style_t style_symbol_sketches_slider_3_indic;
	lv_style_reset(&style_symbol_sketches_slider_3_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_3_indic
	lv_style_set_radius(&style_symbol_sketches_slider_3_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_3_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_3_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_3_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_3_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_3, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_3_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_3
	static lv_style_t style_symbol_sketches_slider_3_bg;
	lv_style_reset(&style_symbol_sketches_slider_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_3_bg
	lv_style_set_radius(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 32);
	lv_style_set_bg_color(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, lv_color_make(0xaf, 0xaf, 0xaf));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_3_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_3, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_3_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_3
	static lv_style_t style_symbol_sketches_slider_3_knob;
	lv_style_reset(&style_symbol_sketches_slider_3_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_3_knob
	lv_style_set_radius(&style_symbol_sketches_slider_3_knob, LV_STATE_DEFAULT, 7);
	lv_style_set_bg_color(&style_symbol_sketches_slider_3_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_3_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_3_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_3_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_3, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_3_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_3, 279, 107);
	lv_obj_set_size(ui->symbol_sketches_slider_3, 11, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_3, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_3, 50, false);

	//Write codes symbol_sketches_slider_4
	ui->symbol_sketches_slider_4 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_4
	static lv_style_t style_symbol_sketches_slider_4_indic;
	lv_style_reset(&style_symbol_sketches_slider_4_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_4_indic
	lv_style_set_radius(&style_symbol_sketches_slider_4_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_4_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_4_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_4_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_4_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_4, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_4_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_4
	static lv_style_t style_symbol_sketches_slider_4_bg;
	lv_style_reset(&style_symbol_sketches_slider_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_4_bg
	lv_style_set_radius(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 32);
	lv_style_set_bg_color(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, lv_color_make(0xaf, 0xaf, 0xaf));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, lv_color_make(0xaf, 0xaf, 0xaf));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_4_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_4, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_4_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_4
	static lv_style_t style_symbol_sketches_slider_4_knob;
	lv_style_reset(&style_symbol_sketches_slider_4_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_4_knob
	lv_style_set_radius(&style_symbol_sketches_slider_4_knob, LV_STATE_DEFAULT, 15);
	lv_style_set_bg_color(&style_symbol_sketches_slider_4_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_4_knob, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xf0, 0xf0));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_4_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_4_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_4, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_4_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_4, 222, 106);
	lv_obj_set_size(ui->symbol_sketches_slider_4, 16, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_4, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_4, 50, false);

	//Write codes symbol_sketches_slider_5
	ui->symbol_sketches_slider_5 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_5
	static lv_style_t style_symbol_sketches_slider_5_indic;
	lv_style_reset(&style_symbol_sketches_slider_5_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_5_indic
	lv_style_set_radius(&style_symbol_sketches_slider_5_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_5_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_5_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_5_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_5_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_5, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_5_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_5
	static lv_style_t style_symbol_sketches_slider_5_bg;
	lv_style_reset(&style_symbol_sketches_slider_5_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_5_bg
	lv_style_set_radius(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 25);
	lv_style_set_bg_color(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_5_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_5, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_5_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_5
	static lv_style_t style_symbol_sketches_slider_5_knob;
	lv_style_reset(&style_symbol_sketches_slider_5_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_5_knob
	lv_style_set_radius(&style_symbol_sketches_slider_5_knob, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_5_knob, LV_STATE_DEFAULT, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_5_knob, LV_STATE_DEFAULT, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_5_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_5_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_5, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_5_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_5, 168, 105);
	lv_obj_set_size(ui->symbol_sketches_slider_5, 11, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_5, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_5, 50, false);

	//Write codes symbol_sketches_lmeter_2
	ui->symbol_sketches_lmeter_2 = lv_linemeter_create(ui->symbol_sketches, NULL);

	//Write style LV_LINEMETER_PART_MAIN for symbol_sketches_lmeter_2
	static lv_style_t style_symbol_sketches_lmeter_2_main;
	lv_style_reset(&style_symbol_sketches_lmeter_2_main);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_lmeter_2_main
	lv_style_set_radius(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 1);
	lv_style_set_bg_color(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_color(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, lv_color_make(0x28, 0x28, 0x28));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 5);
	lv_style_set_line_color(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_line_width(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 4);
	lv_style_set_line_opa(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(
		&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_scale_end_color(
		&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, lv_color_make(0x8c, 0x8c, 0x8c));
	lv_style_set_scale_width(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 10);
	lv_style_set_scale_end_line_width(&style_symbol_sketches_lmeter_2_main, LV_STATE_DEFAULT, 4);
	lv_obj_add_style(ui->symbol_sketches_lmeter_2, LV_LINEMETER_PART_MAIN, &style_symbol_sketches_lmeter_2_main);
	lv_obj_set_pos(ui->symbol_sketches_lmeter_2, 167, 13);
	lv_obj_set_size(ui->symbol_sketches_lmeter_2, 50, 50);
	lv_linemeter_set_scale(ui->symbol_sketches_lmeter_2, 285, 12);
	lv_linemeter_set_range(ui->symbol_sketches_lmeter_2, 14, 212);
	lv_linemeter_set_value(ui->symbol_sketches_lmeter_2, 96);
	lv_linemeter_set_angle_offset(ui->symbol_sketches_lmeter_2, 0);

	//Write codes symbol_sketches_slider_6
	ui->symbol_sketches_slider_6 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_6
	static lv_style_t style_symbol_sketches_slider_6_indic;
	lv_style_reset(&style_symbol_sketches_slider_6_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_6_indic
	lv_style_set_radius(&style_symbol_sketches_slider_6_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_6_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_6_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_6_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_6_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_6, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_6_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_6
	static lv_style_t style_symbol_sketches_slider_6_bg;
	lv_style_reset(&style_symbol_sketches_slider_6_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_6_bg
	lv_style_set_radius(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_6_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_6, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_6_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_6
	static lv_style_t style_symbol_sketches_slider_6_knob;
	lv_style_reset(&style_symbol_sketches_slider_6_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_6_knob
	lv_style_set_radius(&style_symbol_sketches_slider_6_knob, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_6_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8e, 0xcc));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_6_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8e, 0xcc));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_6_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_6_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_6, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_6_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_6, 120, 104);
	lv_obj_set_size(ui->symbol_sketches_slider_6, 11, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_6, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_6, 50, false);

	//Write codes symbol_sketches_slider_7
	ui->symbol_sketches_slider_7 = lv_slider_create(ui->symbol_sketches, NULL);

	//Write style LV_SLIDER_PART_INDIC for symbol_sketches_slider_7
	static lv_style_t style_symbol_sketches_slider_7_indic;
	lv_style_reset(&style_symbol_sketches_slider_7_indic);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_7_indic
	lv_style_set_radius(&style_symbol_sketches_slider_7_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_7_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(
		&style_symbol_sketches_slider_7_indic, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_7_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_7_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->symbol_sketches_slider_7, LV_SLIDER_PART_INDIC, &style_symbol_sketches_slider_7_indic);

	//Write style LV_SLIDER_PART_BG for symbol_sketches_slider_7
	static lv_style_t style_symbol_sketches_slider_7_bg;
	lv_style_reset(&style_symbol_sketches_slider_7_bg);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_7_bg
	lv_style_set_radius(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_outline_opa(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_symbol_sketches_slider_7_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_7, LV_SLIDER_PART_BG, &style_symbol_sketches_slider_7_bg);

	//Write style LV_SLIDER_PART_KNOB for symbol_sketches_slider_7
	static lv_style_t style_symbol_sketches_slider_7_knob;
	lv_style_reset(&style_symbol_sketches_slider_7_knob);

	//Write style state: LV_STATE_DEFAULT for style_symbol_sketches_slider_7_knob
	lv_style_set_radius(&style_symbol_sketches_slider_7_knob, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_symbol_sketches_slider_7_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8e, 0xc9));
	lv_style_set_bg_grad_color(&style_symbol_sketches_slider_7_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x8d, 0xc9));
	lv_style_set_bg_grad_dir(&style_symbol_sketches_slider_7_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_symbol_sketches_slider_7_knob, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->symbol_sketches_slider_7, LV_SLIDER_PART_KNOB, &style_symbol_sketches_slider_7_knob);
	lv_obj_set_pos(ui->symbol_sketches_slider_7, 87, 106);
	lv_obj_set_size(ui->symbol_sketches_slider_7, 17, 117);
	lv_slider_set_range(ui->symbol_sketches_slider_7, 0, 100);
	lv_slider_set_value(ui->symbol_sketches_slider_7, 50, false);
}
