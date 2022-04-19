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


void setup_scr_knob_button_view(lv_ui *ui){

	//Write codes knob_button_view
	ui->knob_button_view = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_main_main_default
	static lv_style_t style_knob_button_view_main_main_default;
	if (style_knob_button_view_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_main_main_default);
	else
		lv_style_init(&style_knob_button_view_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_knob_button_view_main_main_default, 255);
	lv_obj_add_style(ui->knob_button_view, &style_knob_button_view_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_1
	ui->knob_button_view_arc_1 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_1, 30, 10);
	lv_obj_set_size(ui->knob_button_view_arc_1, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_1_main_main_default
	static lv_style_t style_knob_button_view_arc_1_main_main_default;
	if (style_knob_button_view_arc_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_1_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_1_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_1_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_1_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_1_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_1_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_1, &style_knob_button_view_arc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_1_main_indicator_default
	static lv_style_t style_knob_button_view_arc_1_main_indicator_default;
	if (style_knob_button_view_arc_1_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_1_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_1_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_1_main_indicator_default, lv_color_make(0xfa, 0x50, 0xaa));
	lv_style_set_arc_width(&style_knob_button_view_arc_1_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_1, &style_knob_button_view_arc_1_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_1_main_knob_default
	static lv_style_t style_knob_button_view_arc_1_main_knob_default;
	if (style_knob_button_view_arc_1_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_1_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_1_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_1_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_1_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_1_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_1, &style_knob_button_view_arc_1_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_1, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_1, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_1, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_1, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_2
	ui->knob_button_view_arc_2 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_2, 130, 10);
	lv_obj_set_size(ui->knob_button_view_arc_2, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_2_main_main_default
	static lv_style_t style_knob_button_view_arc_2_main_main_default;
	if (style_knob_button_view_arc_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_2_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_2_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_2_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_2_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_2_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_2_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_2_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_2_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_2, &style_knob_button_view_arc_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_2_main_indicator_default
	static lv_style_t style_knob_button_view_arc_2_main_indicator_default;
	if (style_knob_button_view_arc_2_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_2_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_2_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_2_main_indicator_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_arc_width(&style_knob_button_view_arc_2_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_2, &style_knob_button_view_arc_2_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_2_main_knob_default
	static lv_style_t style_knob_button_view_arc_2_main_knob_default;
	if (style_knob_button_view_arc_2_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_2_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_2_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_2_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_2_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_2_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_2_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_2_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_2, &style_knob_button_view_arc_2_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_2, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_2, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_2, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_2, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_3
	ui->knob_button_view_arc_3 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_3, 230, 10);
	lv_obj_set_size(ui->knob_button_view_arc_3, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_3_main_main_default
	static lv_style_t style_knob_button_view_arc_3_main_main_default;
	if (style_knob_button_view_arc_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_3_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_3_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_3_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_3_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_3_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_3_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_3_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_3_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_3, &style_knob_button_view_arc_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_3_main_indicator_default
	static lv_style_t style_knob_button_view_arc_3_main_indicator_default;
	if (style_knob_button_view_arc_3_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_3_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_3_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_3_main_indicator_default, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_arc_width(&style_knob_button_view_arc_3_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_3, &style_knob_button_view_arc_3_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_3_main_knob_default
	static lv_style_t style_knob_button_view_arc_3_main_knob_default;
	if (style_knob_button_view_arc_3_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_3_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_3_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_3_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_3_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_3_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_3_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_3_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_3, &style_knob_button_view_arc_3_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_3, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_3, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_3, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_3, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_4
	ui->knob_button_view_arc_4 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_4, 30, 90);
	lv_obj_set_size(ui->knob_button_view_arc_4, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_4_main_main_default
	static lv_style_t style_knob_button_view_arc_4_main_main_default;
	if (style_knob_button_view_arc_4_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_4_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_4_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_4_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_4_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_4_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_4_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_4_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_4_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_4, &style_knob_button_view_arc_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_4_main_indicator_default
	static lv_style_t style_knob_button_view_arc_4_main_indicator_default;
	if (style_knob_button_view_arc_4_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_4_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_4_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_4_main_indicator_default, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_arc_width(&style_knob_button_view_arc_4_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_4, &style_knob_button_view_arc_4_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_4_main_knob_default
	static lv_style_t style_knob_button_view_arc_4_main_knob_default;
	if (style_knob_button_view_arc_4_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_4_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_4_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_4_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_4_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_4_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_4_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_4_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_4, &style_knob_button_view_arc_4_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_4, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_4, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_4, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_4, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_5
	ui->knob_button_view_arc_5 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_5, 130, 90);
	lv_obj_set_size(ui->knob_button_view_arc_5, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_5_main_main_default
	static lv_style_t style_knob_button_view_arc_5_main_main_default;
	if (style_knob_button_view_arc_5_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_5_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_5_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_5_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_5_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_5_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_5_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_5_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_5_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_5, &style_knob_button_view_arc_5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_5_main_indicator_default
	static lv_style_t style_knob_button_view_arc_5_main_indicator_default;
	if (style_knob_button_view_arc_5_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_5_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_5_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_5_main_indicator_default, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_arc_width(&style_knob_button_view_arc_5_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_5, &style_knob_button_view_arc_5_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_5_main_knob_default
	static lv_style_t style_knob_button_view_arc_5_main_knob_default;
	if (style_knob_button_view_arc_5_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_5_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_5_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_5_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_5_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_5_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_5_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_5_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_5, &style_knob_button_view_arc_5_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_5, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_5, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_5, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_5, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_5, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_5, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_5, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_6
	ui->knob_button_view_arc_6 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_6, 230, 90);
	lv_obj_set_size(ui->knob_button_view_arc_6, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_6_main_main_default
	static lv_style_t style_knob_button_view_arc_6_main_main_default;
	if (style_knob_button_view_arc_6_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_6_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_6_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_6_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_6_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_6_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_6_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_6_main_main_default, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_arc_width(&style_knob_button_view_arc_6_main_main_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_6, &style_knob_button_view_arc_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_6_main_indicator_default
	static lv_style_t style_knob_button_view_arc_6_main_indicator_default;
	if (style_knob_button_view_arc_6_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_6_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_6_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_6_main_indicator_default, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_arc_width(&style_knob_button_view_arc_6_main_indicator_default, 16);
	lv_obj_add_style(ui->knob_button_view_arc_6, &style_knob_button_view_arc_6_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_6_main_knob_default
	static lv_style_t style_knob_button_view_arc_6_main_knob_default;
	if (style_knob_button_view_arc_6_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_6_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_6_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_6_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_6_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_6_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_6_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_6_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_6, &style_knob_button_view_arc_6_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_6, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_6, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_6, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_6, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_7
	ui->knob_button_view_arc_7 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_7, 26, 6);
	lv_obj_set_size(ui->knob_button_view_arc_7, 68, 68);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_7_main_main_default
	static lv_style_t style_knob_button_view_arc_7_main_main_default;
	if (style_knob_button_view_arc_7_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_7_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_7_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_7_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_7_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_7_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_7_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_7_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_7_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_7_main_main_default, 4);
	lv_obj_add_style(ui->knob_button_view_arc_7, &style_knob_button_view_arc_7_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_7_main_indicator_default
	static lv_style_t style_knob_button_view_arc_7_main_indicator_default;
	if (style_knob_button_view_arc_7_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_7_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_7_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_7_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_7_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_button_view_arc_7, &style_knob_button_view_arc_7_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_7_main_knob_default
	static lv_style_t style_knob_button_view_arc_7_main_knob_default;
	if (style_knob_button_view_arc_7_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_7_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_7_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_7_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_7_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_7_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_7_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_7_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_7, &style_knob_button_view_arc_7_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_7, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_7, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_7, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_7, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_8
	ui->knob_button_view_arc_8 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_8, 126, 6);
	lv_obj_set_size(ui->knob_button_view_arc_8, 68, 68);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_8_main_main_default
	static lv_style_t style_knob_button_view_arc_8_main_main_default;
	if (style_knob_button_view_arc_8_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_8_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_8_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_8_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_8_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_8_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_8_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_8_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_8_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_8_main_main_default, 3);
	lv_obj_add_style(ui->knob_button_view_arc_8, &style_knob_button_view_arc_8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_8_main_indicator_default
	static lv_style_t style_knob_button_view_arc_8_main_indicator_default;
	if (style_knob_button_view_arc_8_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_8_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_8_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_8_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_8_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_button_view_arc_8, &style_knob_button_view_arc_8_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_8_main_knob_default
	static lv_style_t style_knob_button_view_arc_8_main_knob_default;
	if (style_knob_button_view_arc_8_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_8_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_8_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_8_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_8_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_8_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_8_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_8_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_8, &style_knob_button_view_arc_8_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_8, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_8, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_8, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_8, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_8, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_8, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_8, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_9
	ui->knob_button_view_arc_9 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_9, 225, 5);
	lv_obj_set_size(ui->knob_button_view_arc_9, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_9_main_main_default
	static lv_style_t style_knob_button_view_arc_9_main_main_default;
	if (style_knob_button_view_arc_9_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_9_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_9_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_9_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_9_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_9_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_9_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_9_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_9_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_9_main_main_default, 3);
	lv_obj_add_style(ui->knob_button_view_arc_9, &style_knob_button_view_arc_9_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_9_main_indicator_default
	static lv_style_t style_knob_button_view_arc_9_main_indicator_default;
	if (style_knob_button_view_arc_9_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_9_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_9_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_9_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_9_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_button_view_arc_9, &style_knob_button_view_arc_9_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_9_main_knob_default
	static lv_style_t style_knob_button_view_arc_9_main_knob_default;
	if (style_knob_button_view_arc_9_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_9_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_9_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_9_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_9_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_9_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_9_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_9_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_9, &style_knob_button_view_arc_9_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_9, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_9, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_9, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_9, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_9, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_9, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_9, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_10
	ui->knob_button_view_arc_10 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_10, 26, 86);
	lv_obj_set_size(ui->knob_button_view_arc_10, 68, 68);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_10_main_main_default
	static lv_style_t style_knob_button_view_arc_10_main_main_default;
	if (style_knob_button_view_arc_10_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_10_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_10_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_10_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_10_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_10_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_10_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_10_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_10_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_10_main_main_default, 2);
	lv_obj_add_style(ui->knob_button_view_arc_10, &style_knob_button_view_arc_10_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_10_main_indicator_default
	static lv_style_t style_knob_button_view_arc_10_main_indicator_default;
	if (style_knob_button_view_arc_10_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_10_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_10_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_10_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_10_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_button_view_arc_10, &style_knob_button_view_arc_10_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_10_main_knob_default
	static lv_style_t style_knob_button_view_arc_10_main_knob_default;
	if (style_knob_button_view_arc_10_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_10_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_10_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_10_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_10_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_10_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_10_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_10_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_10, &style_knob_button_view_arc_10_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_10, 120, 60);
	lv_arc_set_angles(ui->knob_button_view_arc_10, 120, 220);
	lv_arc_set_rotation(ui->knob_button_view_arc_10, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_10, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_10, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_10, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_10, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_12
	ui->knob_button_view_arc_12 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_12, 125, 85);
	lv_obj_set_size(ui->knob_button_view_arc_12, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_12_main_main_default
	static lv_style_t style_knob_button_view_arc_12_main_main_default;
	if (style_knob_button_view_arc_12_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_12_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_12_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_12_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_12_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_12_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_12_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_12_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_12_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_12_main_main_default, 3);
	lv_obj_add_style(ui->knob_button_view_arc_12, &style_knob_button_view_arc_12_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_12_main_indicator_default
	static lv_style_t style_knob_button_view_arc_12_main_indicator_default;
	if (style_knob_button_view_arc_12_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_12_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_12_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_12_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_12_main_indicator_default, 1);
	lv_obj_add_style(ui->knob_button_view_arc_12, &style_knob_button_view_arc_12_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_12_main_knob_default
	static lv_style_t style_knob_button_view_arc_12_main_knob_default;
	if (style_knob_button_view_arc_12_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_12_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_12_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_12_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_12_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_12_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_12_main_knob_default, 0);
	lv_style_set_pad_all(&style_knob_button_view_arc_12_main_knob_default, 5);
	lv_obj_add_style(ui->knob_button_view_arc_12, &style_knob_button_view_arc_12_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_12, 170, 10);
	lv_arc_set_angles(ui->knob_button_view_arc_12, 170, 10);
	lv_arc_set_rotation(ui->knob_button_view_arc_12, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_12, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_12, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_12, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_12, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_arc_13
	ui->knob_button_view_arc_13 = lv_arc_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_arc_13, 219, 80);
	lv_obj_set_size(ui->knob_button_view_arc_13, 82, 82);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_13_main_main_default
	static lv_style_t style_knob_button_view_arc_13_main_main_default;
	if (style_knob_button_view_arc_13_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_13_main_main_default);
	else
		lv_style_init(&style_knob_button_view_arc_13_main_main_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_13_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_13_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_13_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_13_main_main_default, 0);
	lv_style_set_border_width(&style_knob_button_view_arc_13_main_main_default, 0);
	lv_style_set_arc_color(&style_knob_button_view_arc_13_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_13_main_main_default, 7);
	lv_obj_add_style(ui->knob_button_view_arc_13, &style_knob_button_view_arc_13_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_13_main_indicator_default
	static lv_style_t style_knob_button_view_arc_13_main_indicator_default;
	if (style_knob_button_view_arc_13_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_13_main_indicator_default);
	else
		lv_style_init(&style_knob_button_view_arc_13_main_indicator_default);
	lv_style_set_arc_color(&style_knob_button_view_arc_13_main_indicator_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_arc_width(&style_knob_button_view_arc_13_main_indicator_default, 0);
	lv_obj_add_style(ui->knob_button_view_arc_13, &style_knob_button_view_arc_13_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_arc_13_main_knob_default
	static lv_style_t style_knob_button_view_arc_13_main_knob_default;
	if (style_knob_button_view_arc_13_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_arc_13_main_knob_default);
	else
		lv_style_init(&style_knob_button_view_arc_13_main_knob_default);
	lv_style_set_bg_color(&style_knob_button_view_arc_13_main_knob_default, lv_color_make(0xd0, 0xa0, 0x5d));
	lv_style_set_bg_grad_color(&style_knob_button_view_arc_13_main_knob_default, lv_color_make(0xd0, 0xa0, 0x5d));
	lv_style_set_bg_grad_dir(&style_knob_button_view_arc_13_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_arc_13_main_knob_default, 255);
	lv_style_set_pad_all(&style_knob_button_view_arc_13_main_knob_default, 0);
	lv_obj_add_style(ui->knob_button_view_arc_13, &style_knob_button_view_arc_13_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(ui->knob_button_view_arc_13, 180, 2);
	lv_arc_set_angles(ui->knob_button_view_arc_13, 269, 270);
	lv_arc_set_rotation(ui->knob_button_view_arc_13, 0);
	lv_obj_set_style_pad_top(ui->knob_button_view_arc_13, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->knob_button_view_arc_13, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->knob_button_view_arc_13, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->knob_button_view_arc_13, 0, LV_STATE_DEFAULT);

	//Write codes knob_button_view_btn_1
	ui->knob_button_view_btn_1 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_1, 20, 200);
	lv_obj_set_size(ui->knob_button_view_btn_1, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_1_main_main_default
	static lv_style_t style_knob_button_view_btn_1_main_main_default;
	if (style_knob_button_view_btn_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_1_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_1_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_1_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_1_main_main_default, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_1_main_main_default, lv_color_make(0x4b, 0xaf, 0xfa));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_1_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_1_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_knob_button_view_btn_1_main_main_default, 1);
	lv_style_set_border_opa(&style_knob_button_view_btn_1_main_main_default, 255);
	lv_obj_add_style(ui->knob_button_view_btn_1, &style_knob_button_view_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_1_label = lv_label_create(ui->knob_button_view_btn_1);
	lv_label_set_text(ui->knob_button_view_btn_1_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_1_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_1_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes knob_button_view_btn_2
	ui->knob_button_view_btn_2 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_2, 120, 200);
	lv_obj_set_size(ui->knob_button_view_btn_2, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_2_main_main_default
	static lv_style_t style_knob_button_view_btn_2_main_main_default;
	if (style_knob_button_view_btn_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_2_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_2_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_2_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_2_main_main_default, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_2_main_main_default, lv_color_make(0x87, 0xd7, 0xc8));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_2_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_2_main_main_default, lv_color_make(0x73, 0xb5, 0xaa));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_2_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_knob_button_view_btn_2_main_main_default, 2);
	lv_style_set_border_opa(&style_knob_button_view_btn_2_main_main_default, 0);
	lv_obj_add_style(ui->knob_button_view_btn_2, &style_knob_button_view_btn_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_2_label = lv_label_create(ui->knob_button_view_btn_2);
	lv_label_set_text(ui->knob_button_view_btn_2_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_2_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_2_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes knob_button_view_btn_3
	ui->knob_button_view_btn_3 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_3, 20, 160);
	lv_obj_set_size(ui->knob_button_view_btn_3, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_3_main_main_default
	static lv_style_t style_knob_button_view_btn_3_main_main_default;
	if (style_knob_button_view_btn_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_3_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_3_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_3_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_3_main_main_default, lv_color_make(0xf9, 0x53, 0xab));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_3_main_main_default, lv_color_make(0xf9, 0x53, 0xab));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_3_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_3_main_main_default, lv_color_make(0xc1, 0x3e, 0x84));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_3_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_3_main_main_default, lv_color_make(0xc1, 0x3e, 0x84));
	lv_style_set_border_width(&style_knob_button_view_btn_3_main_main_default, 2);
	lv_style_set_border_opa(&style_knob_button_view_btn_3_main_main_default, 255);
	lv_obj_add_style(ui->knob_button_view_btn_3, &style_knob_button_view_btn_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_3_label = lv_label_create(ui->knob_button_view_btn_3);
	lv_label_set_text(ui->knob_button_view_btn_3_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_3_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_3_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes knob_button_view_btn_4
	ui->knob_button_view_btn_4 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_4, 120, 160);
	lv_obj_set_size(ui->knob_button_view_btn_4, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_4_main_main_default
	static lv_style_t style_knob_button_view_btn_4_main_main_default;
	if (style_knob_button_view_btn_4_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_4_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_4_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_4_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_4_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_4_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_4_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_4_main_main_default, lv_color_make(0xd3, 0xc0, 0x5f));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_4_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_knob_button_view_btn_4_main_main_default, 2);
	lv_style_set_border_opa(&style_knob_button_view_btn_4_main_main_default, 0);
	lv_obj_add_style(ui->knob_button_view_btn_4, &style_knob_button_view_btn_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_4_label = lv_label_create(ui->knob_button_view_btn_4);
	lv_label_set_text(ui->knob_button_view_btn_4_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_4_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_4_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_4_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes knob_button_view_btn_5
	ui->knob_button_view_btn_5 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_5, 220, 200);
	lv_obj_set_size(ui->knob_button_view_btn_5, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_5_main_main_default
	static lv_style_t style_knob_button_view_btn_5_main_main_default;
	if (style_knob_button_view_btn_5_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_5_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_5_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_5_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_5_main_main_default, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_5_main_main_default, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_5_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_5_main_main_default, lv_color_make(0xd0, 0xa0, 0x5d));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_5_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_knob_button_view_btn_5_main_main_default, 2);
	lv_style_set_border_opa(&style_knob_button_view_btn_5_main_main_default, 0);
	lv_obj_add_style(ui->knob_button_view_btn_5, &style_knob_button_view_btn_5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_5_label = lv_label_create(ui->knob_button_view_btn_5);
	lv_label_set_text(ui->knob_button_view_btn_5_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_5_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_5_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_5, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_5_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes knob_button_view_btn_6
	ui->knob_button_view_btn_6 = lv_btn_create(ui->knob_button_view);
	lv_obj_set_pos(ui->knob_button_view_btn_6, 220, 160);
	lv_obj_set_size(ui->knob_button_view_btn_6, 80, 30);

	//Write style state: LV_STATE_DEFAULT for style_knob_button_view_btn_6_main_main_default
	static lv_style_t style_knob_button_view_btn_6_main_main_default;
	if (style_knob_button_view_btn_6_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_knob_button_view_btn_6_main_main_default);
	else
		lv_style_init(&style_knob_button_view_btn_6_main_main_default);
	lv_style_set_radius(&style_knob_button_view_btn_6_main_main_default, 15);
	lv_style_set_bg_color(&style_knob_button_view_btn_6_main_main_default, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_bg_grad_color(&style_knob_button_view_btn_6_main_main_default, lv_color_make(0xaa, 0xa7, 0xd7));
	lv_style_set_bg_grad_dir(&style_knob_button_view_btn_6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_knob_button_view_btn_6_main_main_default, 255);
	lv_style_set_shadow_color(&style_knob_button_view_btn_6_main_main_default, lv_color_make(0x8a, 0x88, 0xaf));
	lv_style_set_shadow_opa(&style_knob_button_view_btn_6_main_main_default, 255);
	lv_style_set_border_color(&style_knob_button_view_btn_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_knob_button_view_btn_6_main_main_default, 2);
	lv_style_set_border_opa(&style_knob_button_view_btn_6_main_main_default, 0);
	lv_obj_add_style(ui->knob_button_view_btn_6, &style_knob_button_view_btn_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->knob_button_view_btn_6_label = lv_label_create(ui->knob_button_view_btn_6);
	lv_label_set_text(ui->knob_button_view_btn_6_label, "PARAM");
	lv_obj_set_style_text_color(ui->knob_button_view_btn_6_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->knob_button_view_btn_6_label, &lv_font_MuseoSansCondensed_700_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->knob_button_view_btn_6, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->knob_button_view_btn_6_label, LV_ALIGN_CENTER, 0, 0);
}