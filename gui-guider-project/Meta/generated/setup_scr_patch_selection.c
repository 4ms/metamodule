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

static void _patch_selection_selection_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_selection_extra_list_selected_default
	static lv_style_t style_patch_selection_selection_extra_list_selected_default;
	if (style_patch_selection_selection_extra_list_selected_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_selection_extra_list_selected_default);
	else
		lv_style_init(&style_patch_selection_selection_extra_list_selected_default);
	lv_style_set_radius(&style_patch_selection_selection_extra_list_selected_default, 4);
	lv_style_set_bg_color(&style_patch_selection_selection_extra_list_selected_default, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_patch_selection_selection_extra_list_selected_default, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_patch_selection_selection_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_selection_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_patch_selection_selection_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_patch_selection_selection_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_patch_selection_selection_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_patch_selection_selection_extra_list_selected_default, &lv_font_MuseoSansCondensed_300_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_patch_selection_selection_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_selection_extra_list_main_default
	static lv_style_t style_patch_selection_selection_extra_list_main_default;
	if (style_patch_selection_selection_extra_list_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_selection_extra_list_main_default);
	else
		lv_style_init(&style_patch_selection_selection_extra_list_main_default);
	lv_style_set_radius(&style_patch_selection_selection_extra_list_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_selection_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_patch_selection_selection_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_patch_selection_selection_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_selection_extra_list_main_default, 255);
	lv_style_set_border_color(&style_patch_selection_selection_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_patch_selection_selection_extra_list_main_default, 2);
	lv_style_set_text_color(&style_patch_selection_selection_extra_list_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_text_font(&style_patch_selection_selection_extra_list_main_default, &lv_font_MuseoSansCondensed_300_12);
	lv_style_set_max_height(&style_patch_selection_selection_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_patch_selection_selection_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_selection_extra_list_scrollbar_default
	static lv_style_t style_patch_selection_selection_extra_list_scrollbar_default;
	if (style_patch_selection_selection_extra_list_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_selection_extra_list_scrollbar_default);
	else
		lv_style_init(&style_patch_selection_selection_extra_list_scrollbar_default);
	lv_style_set_radius(&style_patch_selection_selection_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_patch_selection_selection_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_patch_selection_selection_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_patch_selection_selection_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_selection_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_patch_selection_selection_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}

void setup_scr_patch_selection(lv_ui *ui){

	//Write codes patch_selection
	ui->patch_selection = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_main_main_default
	static lv_style_t style_patch_selection_main_main_default;
	if (style_patch_selection_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_main_main_default);
	else
		lv_style_init(&style_patch_selection_main_main_default);
	lv_style_set_bg_color(&style_patch_selection_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_patch_selection_main_main_default, 255);
	lv_obj_add_style(ui->patch_selection, &style_patch_selection_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes patch_selection_back
	ui->patch_selection_back = lv_btn_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_back, 4, 4);
	lv_obj_set_size(ui->patch_selection_back, 50, 25);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_back_main_main_default
	static lv_style_t style_patch_selection_back_main_main_default;
	if (style_patch_selection_back_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_back_main_main_default);
	else
		lv_style_init(&style_patch_selection_back_main_main_default);
	lv_style_set_radius(&style_patch_selection_back_main_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_back_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_color(&style_patch_selection_back_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_dir(&style_patch_selection_back_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_back_main_main_default, 255);
	lv_style_set_shadow_color(&style_patch_selection_back_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_shadow_opa(&style_patch_selection_back_main_main_default, 255);
	lv_style_set_border_color(&style_patch_selection_back_main_main_default, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_border_width(&style_patch_selection_back_main_main_default, 2);
	lv_style_set_border_opa(&style_patch_selection_back_main_main_default, 255);
	lv_obj_add_style(ui->patch_selection_back, &style_patch_selection_back_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->patch_selection_back_label = lv_label_create(ui->patch_selection_back);
	lv_label_set_text(ui->patch_selection_back_label, "BACK");
	lv_obj_set_style_text_color(ui->patch_selection_back_label, lv_color_make(0x32, 0x32, 0x32), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->patch_selection_back_label, &lv_font_MuseoSansCondensed_700_12, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->patch_selection_back, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->patch_selection_back_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes patch_selection_next
	ui->patch_selection_next = lv_btn_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_next, 266, 4);
	lv_obj_set_size(ui->patch_selection_next, 50, 25);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_next_main_main_default
	static lv_style_t style_patch_selection_next_main_main_default;
	if (style_patch_selection_next_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_next_main_main_default);
	else
		lv_style_init(&style_patch_selection_next_main_main_default);
	lv_style_set_radius(&style_patch_selection_next_main_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_next_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_color(&style_patch_selection_next_main_main_default, lv_color_make(0xfe, 0xe4, 0x63));
	lv_style_set_bg_grad_dir(&style_patch_selection_next_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_next_main_main_default, 255);
	lv_style_set_shadow_color(&style_patch_selection_next_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_shadow_opa(&style_patch_selection_next_main_main_default, 255);
	lv_style_set_border_color(&style_patch_selection_next_main_main_default, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_border_width(&style_patch_selection_next_main_main_default, 2);
	lv_style_set_border_opa(&style_patch_selection_next_main_main_default, 255);
	lv_obj_add_style(ui->patch_selection_next, &style_patch_selection_next_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->patch_selection_next_label = lv_label_create(ui->patch_selection_next);
	lv_label_set_text(ui->patch_selection_next_label, "NEXT");
	lv_obj_set_style_text_color(ui->patch_selection_next_label, lv_color_make(0x32, 0x32, 0x32), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->patch_selection_next_label, &lv_font_MuseoSansCondensed_700_12, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->patch_selection_next, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->patch_selection_next_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes patch_selection_play
	ui->patch_selection_play = lv_btn_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_play, 265, 211);
	lv_obj_set_size(ui->patch_selection_play, 50, 25);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_play_main_main_default
	static lv_style_t style_patch_selection_play_main_main_default;
	if (style_patch_selection_play_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_play_main_main_default);
	else
		lv_style_init(&style_patch_selection_play_main_main_default);
	lv_style_set_radius(&style_patch_selection_play_main_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_play_main_main_default, lv_color_make(0xba, 0xdd, 0xa4));
	lv_style_set_bg_grad_color(&style_patch_selection_play_main_main_default, lv_color_make(0xba, 0xdd, 0xa4));
	lv_style_set_bg_grad_dir(&style_patch_selection_play_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_play_main_main_default, 255);
	lv_style_set_shadow_color(&style_patch_selection_play_main_main_default, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_shadow_opa(&style_patch_selection_play_main_main_default, 255);
	lv_style_set_border_color(&style_patch_selection_play_main_main_default, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_border_width(&style_patch_selection_play_main_main_default, 2);
	lv_style_set_border_opa(&style_patch_selection_play_main_main_default, 255);
	lv_obj_add_style(ui->patch_selection_play, &style_patch_selection_play_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->patch_selection_play_label = lv_label_create(ui->patch_selection_play);
	lv_label_set_text(ui->patch_selection_play_label, "PLAY");
	lv_obj_set_style_text_color(ui->patch_selection_play_label, lv_color_make(0x32, 0x32, 0x32), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->patch_selection_play_label, &lv_font_MuseoSansCondensed_700_12, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->patch_selection_play, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->patch_selection_play_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes patch_selection_description
	ui->patch_selection_description = lv_label_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_description, 5, 34);
	lv_obj_set_size(ui->patch_selection_description, 310, 73);
	lv_label_set_text(ui->patch_selection_description, "Patch Description Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam");
	lv_label_set_long_mode(ui->patch_selection_description, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->patch_selection_description, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_description_main_main_default
	static lv_style_t style_patch_selection_description_main_main_default;
	if (style_patch_selection_description_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_description_main_main_default);
	else
		lv_style_init(&style_patch_selection_description_main_main_default);
	lv_style_set_radius(&style_patch_selection_description_main_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_description_main_main_default, lv_color_make(0xcc, 0xcc, 0xcc));
	lv_style_set_bg_grad_color(&style_patch_selection_description_main_main_default, lv_color_make(0x91, 0x91, 0x91));
	lv_style_set_bg_grad_dir(&style_patch_selection_description_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_description_main_main_default, 0);
	lv_style_set_text_color(&style_patch_selection_description_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_patch_selection_description_main_main_default, &lv_font_MuseoSansCondensed_500Italic_13);
	lv_style_set_text_letter_space(&style_patch_selection_description_main_main_default, 2);
	lv_style_set_pad_left(&style_patch_selection_description_main_main_default, 0);
	lv_style_set_pad_right(&style_patch_selection_description_main_main_default, 0);
	lv_style_set_pad_top(&style_patch_selection_description_main_main_default, 0);
	lv_style_set_pad_bottom(&style_patch_selection_description_main_main_default, 0);
	lv_obj_add_style(ui->patch_selection_description, &style_patch_selection_description_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes patch_selection_modules
	ui->patch_selection_modules = lv_obj_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_modules, 0, 115);
	lv_obj_set_size(ui->patch_selection_modules, 320, 125);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_modules_main_main_default
	static lv_style_t style_patch_selection_modules_main_main_default;
	if (style_patch_selection_modules_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_modules_main_main_default);
	else
		lv_style_init(&style_patch_selection_modules_main_main_default);
	lv_style_set_radius(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_bg_color(&style_patch_selection_modules_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_patch_selection_modules_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_patch_selection_modules_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_border_color(&style_patch_selection_modules_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_border_opa(&style_patch_selection_modules_main_main_default, 255);
	lv_style_set_pad_left(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_pad_right(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_pad_top(&style_patch_selection_modules_main_main_default, 0);
	lv_style_set_pad_bottom(&style_patch_selection_modules_main_main_default, 0);
	lv_obj_add_style(ui->patch_selection_modules, &style_patch_selection_modules_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes patch_selection_selection
	ui->patch_selection_selection = lv_dropdown_create(ui->patch_selection);
	lv_obj_set_pos(ui->patch_selection_selection, 60, 4);
	lv_obj_set_width(ui->patch_selection_selection, 200);
	lv_dropdown_set_options(ui->patch_selection_selection, "PATCH NAME\nDJEMBE\nSTEREO DELAY");
	lv_dropdown_set_symbol(ui->patch_selection_selection, NULL);
	lv_obj_add_event_cb(ui->patch_selection_selection, _patch_selection_selection_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_patch_selection_selection_main_main_default
	static lv_style_t style_patch_selection_selection_main_main_default;
	if (style_patch_selection_selection_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_patch_selection_selection_main_main_default);
	else
		lv_style_init(&style_patch_selection_selection_main_main_default);
	lv_style_set_radius(&style_patch_selection_selection_main_main_default, 4);
	lv_style_set_bg_color(&style_patch_selection_selection_main_main_default, lv_color_make(0xf5, 0xf5, 0xf5));
	lv_style_set_bg_grad_color(&style_patch_selection_selection_main_main_default, lv_color_make(0xf5, 0xf5, 0xf5));
	lv_style_set_bg_grad_dir(&style_patch_selection_selection_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_patch_selection_selection_main_main_default, 255);
	lv_style_set_border_color(&style_patch_selection_selection_main_main_default, lv_color_make(0xc8, 0xc8, 0xc8));
	lv_style_set_border_width(&style_patch_selection_selection_main_main_default, 2);
	lv_style_set_text_color(&style_patch_selection_selection_main_main_default, lv_color_make(0x1c, 0x1c, 0x1c));
	lv_style_set_text_font(&style_patch_selection_selection_main_main_default, &lv_font_MuseoSansRounded_700_14);
	lv_style_set_text_line_space(&style_patch_selection_selection_main_main_default, 20);
	lv_obj_add_style(ui->patch_selection_selection, &style_patch_selection_selection_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}