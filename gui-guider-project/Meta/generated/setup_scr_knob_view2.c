/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_knob_view2(lv_ui *ui){

	//Write codes knob_view2
	ui->knob_view2 = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_main_main_default
	static lv_style_t style_knob_view2_main_main_default;
	if (style_knob_view2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_main_main_default);
	else
		lv_style_init(&style_knob_view2_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_knob_view2_main_main_default, 255);
	lv_obj_add_style(ui->knob_view2, &style_knob_view2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_x_knob
	ui->knob_view2_x_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_x_knob, 19, 18);
	lv_obj_set_size(ui->knob_view2_x_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_knob_main_main_default
	static lv_style_t style_knob_view2_x_knob_main_main_default;
	if (style_knob_view2_x_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_x_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_x_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_x_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_x_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_x_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_x_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_x_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_x_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_x_knob, &style_knob_view2_x_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_knob_main_indicator_default
	static lv_style_t style_knob_view2_x_knob_main_indicator_default;
	if (style_knob_view2_x_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_x_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_x_knob_main_indicator_default, lv_color_make(0xfa, 0x50, 0xaa));
	lv_style_set_arc_width(&style_knob_view2_x_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_x_knob, &style_knob_view2_x_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_knob_main_knob_default
	static lv_style_t style_knob_view2_x_knob_main_knob_default;
	if (style_knob_view2_x_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_x_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_x_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_x_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_x_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_x_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_x_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_x_knob, &style_knob_view2_x_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_x_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_x_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_x_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_x_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_x_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_x_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_x_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_x_outline
	ui->knob_view2_x_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_x_outline, 8, 8);
	lv_obj_set_size(ui->knob_view2_x_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_outline_main_main_default
	static lv_style_t style_knob_view2_x_outline_main_main_default;
	if (style_knob_view2_x_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_x_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_x_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_x_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_x_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_x_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_x_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_x_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_x_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_x_outline, &style_knob_view2_x_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_outline_main_indicator_default
	static lv_style_t style_knob_view2_x_outline_main_indicator_default;
	if (style_knob_view2_x_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_x_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_x_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_x_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_x_outline, &style_knob_view2_x_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_outline_main_knob_default
	static lv_style_t style_knob_view2_x_outline_main_knob_default;
	if (style_knob_view2_x_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_x_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_x_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_x_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_x_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_x_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_x_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_x_outline, &style_knob_view2_x_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_x_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_x_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_x_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_x_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_x_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_x_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_x_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_x_label
	ui->knob_view2_x_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_x_label, 30, 66);
	lv_obj_set_size(ui->knob_view2_x_label, 25, 16);
	lv_label_set_text(ui->knob_view2_x_label, "X");
	lv_label_set_long_mode(ui->knob_view2_x_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_x_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_x_label_main_main_default
	static lv_style_t style_knob_view2_x_label_main_main_default;
	if (style_knob_view2_x_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_x_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_x_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_x_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_x_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_x_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_x_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_x_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_x_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_x_label_main_main_default, &lv_font_MuseoSansRounded_900_15);
	lv_style_set_text_letter_space(&style_knob_view2_x_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_x_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_x_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_x_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_x_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_x_label, &style_knob_view2_x_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_a_knob
	ui->knob_view2_a_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_a_knob, 88, 7);
	lv_obj_set_size(ui->knob_view2_a_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_knob_main_main_default
	static lv_style_t style_knob_view2_a_knob_main_main_default;
	if (style_knob_view2_a_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_a_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_a_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_a_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_a_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_a_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_a_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_a_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_a_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_a_knob, &style_knob_view2_a_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_knob_main_indicator_default
	static lv_style_t style_knob_view2_a_knob_main_indicator_default;
	if (style_knob_view2_a_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_a_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_a_knob_main_indicator_default, lv_color_make(0xe1, 0x49, 0xe4));
	lv_style_set_arc_width(&style_knob_view2_a_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_a_knob, &style_knob_view2_a_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_knob_main_knob_default
	static lv_style_t style_knob_view2_a_knob_main_knob_default;
	if (style_knob_view2_a_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_a_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_a_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_a_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_a_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_a_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_a_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_a_knob, &style_knob_view2_a_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_a_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_a_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_a_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_a_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_a_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_a_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_a_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_a_outline
	ui->knob_view2_a_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_a_outline, 83, 2);
	lv_obj_set_size(ui->knob_view2_a_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_outline_main_main_default
	static lv_style_t style_knob_view2_a_outline_main_main_default;
	if (style_knob_view2_a_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_a_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_a_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_a_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_a_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_a_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_a_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_a_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_a_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_a_outline, &style_knob_view2_a_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_outline_main_indicator_default
	static lv_style_t style_knob_view2_a_outline_main_indicator_default;
	if (style_knob_view2_a_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_a_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_a_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_a_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_a_outline, &style_knob_view2_a_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_outline_main_knob_default
	static lv_style_t style_knob_view2_a_outline_main_knob_default;
	if (style_knob_view2_a_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_a_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_a_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_a_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_a_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_a_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_a_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_a_outline, &style_knob_view2_a_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_a_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_a_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_a_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_a_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_a_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_a_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_a_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_a_label
	ui->knob_view2_a_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_a_label, 87, 69);
	lv_obj_set_size(ui->knob_view2_a_label, 61, 13);
	lv_label_set_text(ui->knob_view2_a_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_a_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_a_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_a_label_main_main_default
	static lv_style_t style_knob_view2_a_label_main_main_default;
	if (style_knob_view2_a_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_a_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_a_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_a_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_a_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_a_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_a_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_a_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_a_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_a_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_a_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_a_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_a_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_a_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_a_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_a_label, &style_knob_view2_a_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_b_knob
	ui->knob_view2_b_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_b_knob, 172, 7);
	lv_obj_set_size(ui->knob_view2_b_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_knob_main_main_default
	static lv_style_t style_knob_view2_b_knob_main_main_default;
	if (style_knob_view2_b_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_b_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_b_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_b_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_b_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_b_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_b_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_b_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_b_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_b_knob, &style_knob_view2_b_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_knob_main_indicator_default
	static lv_style_t style_knob_view2_b_knob_main_indicator_default;
	if (style_knob_view2_b_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_b_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_b_knob_main_indicator_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_arc_width(&style_knob_view2_b_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_b_knob, &style_knob_view2_b_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_knob_main_knob_default
	static lv_style_t style_knob_view2_b_knob_main_knob_default;
	if (style_knob_view2_b_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_b_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_b_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_b_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_b_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_b_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_b_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_b_knob, &style_knob_view2_b_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_b_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_b_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_b_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_b_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_b_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_b_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_b_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_b_outline
	ui->knob_view2_b_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_b_outline, 167, 2);
	lv_obj_set_size(ui->knob_view2_b_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_outline_main_main_default
	static lv_style_t style_knob_view2_b_outline_main_main_default;
	if (style_knob_view2_b_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_b_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_b_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_b_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_b_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_b_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_b_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_b_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_b_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_b_outline, &style_knob_view2_b_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_outline_main_indicator_default
	static lv_style_t style_knob_view2_b_outline_main_indicator_default;
	if (style_knob_view2_b_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_b_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_b_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_b_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_b_outline, &style_knob_view2_b_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_outline_main_knob_default
	static lv_style_t style_knob_view2_b_outline_main_knob_default;
	if (style_knob_view2_b_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_b_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_b_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_b_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_b_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_b_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_b_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_b_outline, &style_knob_view2_b_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_b_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_b_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_b_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_b_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_b_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_b_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_b_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_b_label
	ui->knob_view2_b_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_b_label, 174, 69);
	lv_obj_set_size(ui->knob_view2_b_label, 61, 13);
	lv_label_set_text(ui->knob_view2_b_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_b_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_b_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_b_label_main_main_default
	static lv_style_t style_knob_view2_b_label_main_main_default;
	if (style_knob_view2_b_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_b_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_b_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_b_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_b_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_b_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_b_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_b_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_b_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_b_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_b_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_b_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_b_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_b_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_b_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_b_label, &style_knob_view2_b_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_q_knob
	ui->knob_view2_q_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_q_knob, 258, 18);
	lv_obj_set_size(ui->knob_view2_q_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_knob_main_main_default
	static lv_style_t style_knob_view2_q_knob_main_main_default;
	if (style_knob_view2_q_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_q_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_q_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_q_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_q_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_q_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_q_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_q_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_q_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_q_knob, &style_knob_view2_q_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_knob_main_indicator_default
	static lv_style_t style_knob_view2_q_knob_main_indicator_default;
	if (style_knob_view2_q_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_q_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_q_knob_main_indicator_default, lv_color_make(0x3a, 0x45, 0xdf));
	lv_style_set_arc_width(&style_knob_view2_q_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_q_knob, &style_knob_view2_q_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_knob_main_knob_default
	static lv_style_t style_knob_view2_q_knob_main_knob_default;
	if (style_knob_view2_q_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_q_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_q_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_q_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_q_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_q_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_q_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_q_knob, &style_knob_view2_q_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_q_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_q_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_q_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_q_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_q_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_q_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_q_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_q_outline
	ui->knob_view2_q_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_q_outline, 247, 8);
	lv_obj_set_size(ui->knob_view2_q_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_outline_main_main_default
	static lv_style_t style_knob_view2_q_outline_main_main_default;
	if (style_knob_view2_q_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_q_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_q_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_q_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_q_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_q_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_q_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_q_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_q_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_q_outline, &style_knob_view2_q_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_outline_main_indicator_default
	static lv_style_t style_knob_view2_q_outline_main_indicator_default;
	if (style_knob_view2_q_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_q_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_q_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_q_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_q_outline, &style_knob_view2_q_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_outline_main_knob_default
	static lv_style_t style_knob_view2_q_outline_main_knob_default;
	if (style_knob_view2_q_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_q_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_q_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_q_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_q_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_q_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_q_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_q_outline, &style_knob_view2_q_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_q_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_q_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_q_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_q_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_q_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_q_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_q_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_q_label
	ui->knob_view2_q_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_q_label, 269, 66);
	lv_obj_set_size(ui->knob_view2_q_label, 25, 16);
	lv_label_set_text(ui->knob_view2_q_label, "Q");
	lv_label_set_long_mode(ui->knob_view2_q_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_q_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_q_label_main_main_default
	static lv_style_t style_knob_view2_q_label_main_main_default;
	if (style_knob_view2_q_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_q_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_q_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_q_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_q_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_q_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_q_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_q_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_q_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_q_label_main_main_default, &lv_font_MuseoSansRounded_900_15);
	lv_style_set_text_letter_space(&style_knob_view2_q_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_q_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_q_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_q_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_q_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_q_label, &style_knob_view2_q_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_y_knob
	ui->knob_view2_y_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_y_knob, 19, 98);
	lv_obj_set_size(ui->knob_view2_y_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_knob_main_main_default
	static lv_style_t style_knob_view2_y_knob_main_main_default;
	if (style_knob_view2_y_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_y_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_y_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_y_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_y_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_y_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_y_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_y_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_y_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_y_knob, &style_knob_view2_y_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_knob_main_indicator_default
	static lv_style_t style_knob_view2_y_knob_main_indicator_default;
	if (style_knob_view2_y_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_y_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_y_knob_main_indicator_default, lv_color_make(0xfa, 0x50, 0xaa));
	lv_style_set_arc_width(&style_knob_view2_y_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_y_knob, &style_knob_view2_y_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_knob_main_knob_default
	static lv_style_t style_knob_view2_y_knob_main_knob_default;
	if (style_knob_view2_y_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_y_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_y_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_y_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_y_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_y_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_y_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_y_knob, &style_knob_view2_y_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_y_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_y_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_y_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_y_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_y_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_y_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_y_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_y_outline
	ui->knob_view2_y_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_y_outline, 8, 88);
	lv_obj_set_size(ui->knob_view2_y_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_outline_main_main_default
	static lv_style_t style_knob_view2_y_outline_main_main_default;
	if (style_knob_view2_y_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_y_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_y_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_y_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_y_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_y_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_y_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_y_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_y_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_y_outline, &style_knob_view2_y_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_outline_main_indicator_default
	static lv_style_t style_knob_view2_y_outline_main_indicator_default;
	if (style_knob_view2_y_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_y_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_y_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_y_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_y_outline, &style_knob_view2_y_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_outline_main_knob_default
	static lv_style_t style_knob_view2_y_outline_main_knob_default;
	if (style_knob_view2_y_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_y_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_y_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_y_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_y_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_y_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_y_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_y_outline, &style_knob_view2_y_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_y_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_y_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_y_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_y_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_y_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_y_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_y_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_y_label
	ui->knob_view2_y_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_y_label, 29, 145);
	lv_obj_set_size(ui->knob_view2_y_label, 25, 16);
	lv_label_set_text(ui->knob_view2_y_label, "Y");
	lv_label_set_long_mode(ui->knob_view2_y_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_y_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_y_label_main_main_default
	static lv_style_t style_knob_view2_y_label_main_main_default;
	if (style_knob_view2_y_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_y_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_y_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_y_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_y_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_y_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_y_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_y_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_y_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_y_label_main_main_default, &lv_font_MuseoSansRounded_900_15);
	lv_style_set_text_letter_space(&style_knob_view2_y_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_y_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_y_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_y_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_y_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_y_label, &style_knob_view2_y_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_c_knob
	ui->knob_view2_c_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_c_knob, 88, 86);
	lv_obj_set_size(ui->knob_view2_c_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_knob_main_main_default
	static lv_style_t style_knob_view2_c_knob_main_main_default;
	if (style_knob_view2_c_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_c_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_c_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_c_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_c_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_c_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_c_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_c_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_c_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_c_knob, &style_knob_view2_c_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_knob_main_indicator_default
	static lv_style_t style_knob_view2_c_knob_main_indicator_default;
	if (style_knob_view2_c_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_c_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_c_knob_main_indicator_default, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_arc_width(&style_knob_view2_c_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_c_knob, &style_knob_view2_c_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_knob_main_knob_default
	static lv_style_t style_knob_view2_c_knob_main_knob_default;
	if (style_knob_view2_c_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_c_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_c_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_c_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_c_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_c_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_c_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_c_knob, &style_knob_view2_c_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_c_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_c_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_c_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_c_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_c_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_c_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_c_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_c_outline
	ui->knob_view2_c_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_c_outline, 83, 81);
	lv_obj_set_size(ui->knob_view2_c_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_outline_main_main_default
	static lv_style_t style_knob_view2_c_outline_main_main_default;
	if (style_knob_view2_c_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_c_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_c_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_c_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_c_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_c_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_c_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_c_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_c_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_c_outline, &style_knob_view2_c_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_outline_main_indicator_default
	static lv_style_t style_knob_view2_c_outline_main_indicator_default;
	if (style_knob_view2_c_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_c_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_c_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_c_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_c_outline, &style_knob_view2_c_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_outline_main_knob_default
	static lv_style_t style_knob_view2_c_outline_main_knob_default;
	if (style_knob_view2_c_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_c_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_c_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_c_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_c_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_c_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_c_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_c_outline, &style_knob_view2_c_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_c_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_c_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_c_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_c_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_c_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_c_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_c_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_c_label
	ui->knob_view2_c_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_c_label, 87, 148);
	lv_obj_set_size(ui->knob_view2_c_label, 61, 13);
	lv_label_set_text(ui->knob_view2_c_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_c_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_c_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_c_label_main_main_default
	static lv_style_t style_knob_view2_c_label_main_main_default;
	if (style_knob_view2_c_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_c_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_c_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_c_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_c_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_c_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_c_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_c_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_c_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_c_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_c_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_c_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_c_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_c_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_c_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_c_label, &style_knob_view2_c_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_d_knob
	ui->knob_view2_d_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_d_knob, 172, 86);
	lv_obj_set_size(ui->knob_view2_d_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_knob_main_main_default
	static lv_style_t style_knob_view2_d_knob_main_main_default;
	if (style_knob_view2_d_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_d_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_d_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_d_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_d_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_d_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_d_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_d_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_d_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_d_knob, &style_knob_view2_d_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_knob_main_indicator_default
	static lv_style_t style_knob_view2_d_knob_main_indicator_default;
	if (style_knob_view2_d_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_d_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_d_knob_main_indicator_default, lv_color_make(0x79, 0x72, 0xdf));
	lv_style_set_arc_width(&style_knob_view2_d_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_d_knob, &style_knob_view2_d_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_knob_main_knob_default
	static lv_style_t style_knob_view2_d_knob_main_knob_default;
	if (style_knob_view2_d_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_d_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_d_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_d_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_d_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_d_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_d_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_d_knob, &style_knob_view2_d_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_d_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_d_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_d_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_d_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_d_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_d_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_d_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_d_outline
	ui->knob_view2_d_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_d_outline, 167, 81);
	lv_obj_set_size(ui->knob_view2_d_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_outline_main_main_default
	static lv_style_t style_knob_view2_d_outline_main_main_default;
	if (style_knob_view2_d_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_d_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_d_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_d_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_d_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_d_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_d_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_d_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_d_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_d_outline, &style_knob_view2_d_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_outline_main_indicator_default
	static lv_style_t style_knob_view2_d_outline_main_indicator_default;
	if (style_knob_view2_d_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_d_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_d_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_d_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_d_outline, &style_knob_view2_d_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_outline_main_knob_default
	static lv_style_t style_knob_view2_d_outline_main_knob_default;
	if (style_knob_view2_d_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_d_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_d_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_d_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_d_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_d_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_d_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_d_outline, &style_knob_view2_d_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_d_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_d_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_d_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_d_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_d_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_d_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_d_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_d_label
	ui->knob_view2_d_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_d_label, 174, 148);
	lv_obj_set_size(ui->knob_view2_d_label, 61, 13);
	lv_label_set_text(ui->knob_view2_d_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_d_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_d_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_d_label_main_main_default
	static lv_style_t style_knob_view2_d_label_main_main_default;
	if (style_knob_view2_d_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_d_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_d_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_d_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_d_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_d_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_d_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_d_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_d_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_d_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_d_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_d_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_d_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_d_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_d_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_d_label, &style_knob_view2_d_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_l_knob
	ui->knob_view2_l_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_l_knob, 258, 98);
	lv_obj_set_size(ui->knob_view2_l_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_knob_main_main_default
	static lv_style_t style_knob_view2_l_knob_main_main_default;
	if (style_knob_view2_l_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_l_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_l_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_l_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_l_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_l_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_l_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_l_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_l_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_l_knob, &style_knob_view2_l_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_knob_main_indicator_default
	static lv_style_t style_knob_view2_l_knob_main_indicator_default;
	if (style_knob_view2_l_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_l_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_l_knob_main_indicator_default, lv_color_make(0xe6, 0xc4, 0xf8));
	lv_style_set_arc_width(&style_knob_view2_l_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_l_knob, &style_knob_view2_l_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_knob_main_knob_default
	static lv_style_t style_knob_view2_l_knob_main_knob_default;
	if (style_knob_view2_l_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_l_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_l_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_l_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_l_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_l_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_l_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_l_knob, &style_knob_view2_l_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_l_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_l_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_l_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_l_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_l_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_l_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_l_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_l_outline
	ui->knob_view2_l_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_l_outline, 247, 88);
	lv_obj_set_size(ui->knob_view2_l_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_outline_main_main_default
	static lv_style_t style_knob_view2_l_outline_main_main_default;
	if (style_knob_view2_l_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_l_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_l_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_l_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_l_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_l_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_l_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_l_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_l_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_l_outline, &style_knob_view2_l_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_outline_main_indicator_default
	static lv_style_t style_knob_view2_l_outline_main_indicator_default;
	if (style_knob_view2_l_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_l_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_l_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_l_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_l_outline, &style_knob_view2_l_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_outline_main_knob_default
	static lv_style_t style_knob_view2_l_outline_main_knob_default;
	if (style_knob_view2_l_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_l_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_l_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_l_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_l_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_l_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_l_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_l_outline, &style_knob_view2_l_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_l_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_l_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_l_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_l_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_l_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_l_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_l_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_l_label
	ui->knob_view2_l_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_l_label, 269, 145);
	lv_obj_set_size(ui->knob_view2_l_label, 25, 16);
	lv_label_set_text(ui->knob_view2_l_label, "L");
	lv_label_set_long_mode(ui->knob_view2_l_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_l_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_l_label_main_main_default
	static lv_style_t style_knob_view2_l_label_main_main_default;
	if (style_knob_view2_l_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_l_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_l_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_l_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_l_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_l_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_l_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_l_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_l_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_l_label_main_main_default, &lv_font_MuseoSansRounded_900_15);
	lv_style_set_text_letter_space(&style_knob_view2_l_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_l_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_l_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_l_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_l_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_l_label, &style_knob_view2_l_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_z_knob
	ui->knob_view2_z_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_z_knob, 19, 173);
	lv_obj_set_size(ui->knob_view2_z_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_knob_main_main_default
	static lv_style_t style_knob_view2_z_knob_main_main_default;
	if (style_knob_view2_z_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_z_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_z_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_z_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_z_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_z_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_z_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_z_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_z_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_z_knob, &style_knob_view2_z_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_knob_main_indicator_default
	static lv_style_t style_knob_view2_z_knob_main_indicator_default;
	if (style_knob_view2_z_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_z_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_z_knob_main_indicator_default, lv_color_make(0xfa, 0x50, 0xaa));
	lv_style_set_arc_width(&style_knob_view2_z_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_z_knob, &style_knob_view2_z_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_knob_main_knob_default
	static lv_style_t style_knob_view2_z_knob_main_knob_default;
	if (style_knob_view2_z_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_z_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_z_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_z_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_z_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_z_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_z_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_z_knob, &style_knob_view2_z_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_z_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_z_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_z_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_z_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_z_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_z_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_z_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_z_outline
	ui->knob_view2_z_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_z_outline, 8, 163);
	lv_obj_set_size(ui->knob_view2_z_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_outline_main_main_default
	static lv_style_t style_knob_view2_z_outline_main_main_default;
	if (style_knob_view2_z_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_z_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_z_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_z_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_z_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_z_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_z_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_z_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_z_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_z_outline, &style_knob_view2_z_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_outline_main_indicator_default
	static lv_style_t style_knob_view2_z_outline_main_indicator_default;
	if (style_knob_view2_z_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_z_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_z_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_z_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_z_outline, &style_knob_view2_z_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_outline_main_knob_default
	static lv_style_t style_knob_view2_z_outline_main_knob_default;
	if (style_knob_view2_z_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_z_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_z_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_z_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_z_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_z_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_z_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_z_outline, &style_knob_view2_z_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_z_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_z_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_z_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_z_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_z_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_z_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_z_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_z_label
	ui->knob_view2_z_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_z_label, 30, 221);
	lv_obj_set_size(ui->knob_view2_z_label, 25, 16);
	lv_label_set_text(ui->knob_view2_z_label, "Z");
	lv_label_set_long_mode(ui->knob_view2_z_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_z_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_z_label_main_main_default
	static lv_style_t style_knob_view2_z_label_main_main_default;
	if (style_knob_view2_z_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_z_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_z_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_z_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_z_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_z_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_z_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_z_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_z_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_z_label_main_main_default, &lv_font_MuseoSansRounded_900_14);
	lv_style_set_text_letter_space(&style_knob_view2_z_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_z_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_z_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_z_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_z_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_z_label, &style_knob_view2_z_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_e_knob
	ui->knob_view2_e_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_e_knob, 88, 164);
	lv_obj_set_size(ui->knob_view2_e_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_knob_main_main_default
	static lv_style_t style_knob_view2_e_knob_main_main_default;
	if (style_knob_view2_e_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_e_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_e_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_e_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_e_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_e_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_e_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_e_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_e_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_e_knob, &style_knob_view2_e_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_knob_main_indicator_default
	static lv_style_t style_knob_view2_e_knob_main_indicator_default;
	if (style_knob_view2_e_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_e_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_e_knob_main_indicator_default, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_arc_width(&style_knob_view2_e_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_e_knob, &style_knob_view2_e_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_knob_main_knob_default
	static lv_style_t style_knob_view2_e_knob_main_knob_default;
	if (style_knob_view2_e_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_e_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_e_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_e_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_e_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_e_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_e_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_e_knob, &style_knob_view2_e_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_e_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_e_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_e_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_e_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_e_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_e_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_e_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_e_outline
	ui->knob_view2_e_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_e_outline, 83, 159);
	lv_obj_set_size(ui->knob_view2_e_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_outline_main_main_default
	static lv_style_t style_knob_view2_e_outline_main_main_default;
	if (style_knob_view2_e_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_e_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_e_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_e_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_e_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_e_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_e_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_e_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_e_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_e_outline, &style_knob_view2_e_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_outline_main_indicator_default
	static lv_style_t style_knob_view2_e_outline_main_indicator_default;
	if (style_knob_view2_e_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_e_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_e_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_e_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_e_outline, &style_knob_view2_e_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_outline_main_knob_default
	static lv_style_t style_knob_view2_e_outline_main_knob_default;
	if (style_knob_view2_e_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_e_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_e_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_e_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_e_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_e_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_e_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_e_outline, &style_knob_view2_e_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_e_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_e_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_e_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_e_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_e_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_e_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_e_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_e_label
	ui->knob_view2_e_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_e_label, 86, 226);
	lv_obj_set_size(ui->knob_view2_e_label, 61, 13);
	lv_label_set_text(ui->knob_view2_e_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_e_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_e_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_e_label_main_main_default
	static lv_style_t style_knob_view2_e_label_main_main_default;
	if (style_knob_view2_e_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_e_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_e_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_e_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_e_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_e_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_e_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_e_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_e_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_e_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_e_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_e_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_e_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_e_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_e_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_e_label, &style_knob_view2_e_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_f_knob
	ui->knob_view2_f_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_f_knob, 172, 164);
	lv_obj_set_size(ui->knob_view2_f_knob, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_knob_main_main_default
	static lv_style_t style_knob_view2_f_knob_main_main_default;
	if (style_knob_view2_f_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_f_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_f_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_f_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_f_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_f_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_f_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_f_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_f_knob_main_main_default, 16);
	lv_obj_add_style(ui->knob_view2_f_knob, &style_knob_view2_f_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_knob_main_indicator_default
	static lv_style_t style_knob_view2_f_knob_main_indicator_default;
	if (style_knob_view2_f_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_f_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_f_knob_main_indicator_default, lv_color_make(0xf4, 0xa2, 0x2f));
	lv_style_set_arc_width(&style_knob_view2_f_knob_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_view2_f_knob, &style_knob_view2_f_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_knob_main_knob_default
	static lv_style_t style_knob_view2_f_knob_main_knob_default;
	if (style_knob_view2_f_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_f_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_f_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_f_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_f_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_f_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_f_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_f_knob, &style_knob_view2_f_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_f_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_f_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_f_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_f_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_f_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_f_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_f_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_f_outline
	ui->knob_view2_f_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_f_outline, 167, 159);
	lv_obj_set_size(ui->knob_view2_f_outline, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_outline_main_main_default
	static lv_style_t style_knob_view2_f_outline_main_main_default;
	if (style_knob_view2_f_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_f_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_f_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_f_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_f_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_f_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_f_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_f_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_f_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_f_outline, &style_knob_view2_f_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_outline_main_indicator_default
	static lv_style_t style_knob_view2_f_outline_main_indicator_default;
	if (style_knob_view2_f_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_f_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_f_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_f_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_f_outline, &style_knob_view2_f_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_outline_main_knob_default
	static lv_style_t style_knob_view2_f_outline_main_knob_default;
	if (style_knob_view2_f_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_f_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_f_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_f_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_f_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_f_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_f_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_f_outline, &style_knob_view2_f_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_f_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_f_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_f_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_f_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_f_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_f_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_f_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_f_label
	ui->knob_view2_f_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_f_label, 174, 226);
	lv_obj_set_size(ui->knob_view2_f_label, 61, 13);
	lv_label_set_text(ui->knob_view2_f_label, "PARAM");
	lv_label_set_long_mode(ui->knob_view2_f_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_f_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_f_label_main_main_default
	static lv_style_t style_knob_view2_f_label_main_main_default;
	if (style_knob_view2_f_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_f_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_f_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_f_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_f_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_f_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_f_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_f_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_f_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_f_label_main_main_default, &lv_font_MuseoSansRounded_900_11);
	lv_style_set_text_letter_space(&style_knob_view2_f_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_f_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_f_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_f_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_f_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_f_label, &style_knob_view2_f_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_view2_r_knob
	ui->knob_view2_r_knob = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_r_knob, 258, 173);
	lv_obj_set_size(ui->knob_view2_r_knob, 45, 45);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_knob_main_main_default
	static lv_style_t style_knob_view2_r_knob_main_main_default;
	if (style_knob_view2_r_knob_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_knob_main_main_default);
	else
		lv_style_init(&style_knob_view2_r_knob_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_r_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_r_knob_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_r_knob_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_r_knob_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_r_knob_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_r_knob_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_view2_r_knob_main_main_default, 12);
	lv_obj_add_style(ui->knob_view2_r_knob, &style_knob_view2_r_knob_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_knob_main_indicator_default
	static lv_style_t style_knob_view2_r_knob_main_indicator_default;
	if (style_knob_view2_r_knob_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_knob_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_r_knob_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_r_knob_main_indicator_default, lv_color_make(0xff, 0x57, 0x57));
	lv_style_set_arc_width(&style_knob_view2_r_knob_main_indicator_default, 12);
	lv_obj_add_style(ui->knob_view2_r_knob, &style_knob_view2_r_knob_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_knob_main_knob_default
	static lv_style_t style_knob_view2_r_knob_main_knob_default;
	if (style_knob_view2_r_knob_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_knob_main_knob_default);
	else
		lv_style_init(&style_knob_view2_r_knob_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_r_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_r_knob_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_r_knob_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_r_knob_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_r_knob_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_r_knob, &style_knob_view2_r_knob_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_r_knob, 120, 60);
	lv_arc_set_angles(ui->knob_view2_r_knob, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_r_knob, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_r_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_r_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_r_knob, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_r_knob, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_r_outline
	ui->knob_view2_r_outline = lv_arc_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_r_outline, 247, 163);
	lv_obj_set_size(ui->knob_view2_r_outline, 65, 65);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_outline_main_main_default
	static lv_style_t style_knob_view2_r_outline_main_main_default;
	if (style_knob_view2_r_outline_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_outline_main_main_default);
	else
		lv_style_init(&style_knob_view2_r_outline_main_main_default);
	lv_style_set_bg_color(&style_knob_view2_r_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_r_outline_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_r_outline_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_r_outline_main_main_default, 0);
	lv_style_set_border_width(&style_knob_view2_r_outline_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_view2_r_outline_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_r_outline_main_main_default, 3);
	lv_obj_add_style(ui->knob_view2_r_outline, &style_knob_view2_r_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_outline_main_indicator_default
	static lv_style_t style_knob_view2_r_outline_main_indicator_default;
	if (style_knob_view2_r_outline_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_outline_main_indicator_default);
	else
		lv_style_init(&style_knob_view2_r_outline_main_indicator_default);
	lv_style_set_arc_color(&style_knob_view2_r_outline_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_view2_r_outline_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_view2_r_outline, &style_knob_view2_r_outline_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_outline_main_knob_default
	static lv_style_t style_knob_view2_r_outline_main_knob_default;
	if (style_knob_view2_r_outline_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_outline_main_knob_default);
	else
		lv_style_init(&style_knob_view2_r_outline_main_knob_default);
	lv_style_set_bg_color(&style_knob_view2_r_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_r_outline_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_r_outline_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_r_outline_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_view2_r_outline_main_knob_default, 5);
	lv_obj_add_style(ui->knob_view2_r_outline, &style_knob_view2_r_outline_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_view2_r_outline, 120, 60);
	lv_arc_set_angles(ui->knob_view2_r_outline, 120, 220);
	lv_arc_set_rotation(ui->knob_view2_r_outline, 0);
	lv_obj_set_style_pad_top(ui->knob_view2_r_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_view2_r_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_view2_r_outline, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_view2_r_outline, 0, LV_STATE_DEFAULT);

	//Write codes knob_view2_r_label
	ui->knob_view2_r_label = lv_label_create(ui->knob_view2);
	lv_obj_set_pos(ui->knob_view2_r_label, 269, 220);
	lv_obj_set_size(ui->knob_view2_r_label, 25, 16);
	lv_label_set_text(ui->knob_view2_r_label, "R");
	lv_label_set_long_mode(ui->knob_view2_r_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->knob_view2_r_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_knob_view2_r_label_main_main_default
	static lv_style_t style_knob_view2_r_label_main_main_default;
	if (style_knob_view2_r_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_view2_r_label_main_main_default);
	else
		lv_style_init(&style_knob_view2_r_label_main_main_default);
	lv_style_set_radius(&style_knob_view2_r_label_main_main_default, 0);
	lv_style_set_bg_color(&style_knob_view2_r_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_view2_r_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_view2_r_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_view2_r_label_main_main_default, 0);
	lv_style_set_text_color(&style_knob_view2_r_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_knob_view2_r_label_main_main_default, &lv_font_MuseoSansRounded_900_15);
	lv_style_set_text_letter_space(&style_knob_view2_r_label_main_main_default, 2);
	lv_style_set_pad_left(&style_knob_view2_r_label_main_main_default, 0);
	lv_style_set_pad_right(&style_knob_view2_r_label_main_main_default, 0);
	lv_style_set_pad_top(&style_knob_view2_r_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_knob_view2_r_label_main_main_default, 0);
	lv_obj_add_style(ui->knob_view2_r_label, &style_knob_view2_r_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}