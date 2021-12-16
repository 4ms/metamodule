/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

void setup_scr_Dropdown1(lv_ui *ui) {

	//Write codes Dropdown1
	ui->Dropdown1 = lv_obj_create(NULL, NULL);

	//Write codes Dropdown1_background_simulation
	ui->Dropdown1_background_simulation = lv_cont_create(ui->Dropdown1, NULL);

	//Write style LV_CONT_PART_MAIN for Dropdown1_background_simulation
	static lv_style_t style_Dropdown1_background_simulation_main;
	lv_style_reset(&style_Dropdown1_background_simulation_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_background_simulation_main
	lv_style_set_radius(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(
		&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(
		&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(
		&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown1_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(
		ui->Dropdown1_background_simulation, LV_CONT_PART_MAIN, &style_Dropdown1_background_simulation_main);
	lv_obj_set_pos(ui->Dropdown1_background_simulation, 0, 0);
	lv_obj_set_size(ui->Dropdown1_background_simulation, 320, 240);
	lv_obj_set_click(ui->Dropdown1_background_simulation, false);
	lv_cont_set_layout(ui->Dropdown1_background_simulation, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->Dropdown1_background_simulation, LV_FIT_NONE);

	//Write codes Dropdown1_patch_dropdown
	ui->Dropdown1_patch_dropdown = lv_dropdown_create(ui->Dropdown1, NULL);
	lv_dropdown_set_options(ui->Dropdown1_patch_dropdown,
							"Patch Name 1\nPatch Name 2\nPatch Name 3\nPatch Name 4\nPatch Name 5\nPatch Name 6\nPatch "
							"Name 7\nPatch Name 8");
	lv_dropdown_set_max_height(ui->Dropdown1_patch_dropdown, 207);
	lv_dropdown_set_symbol(ui->Dropdown1_patch_dropdown, NULL);

	//Write style LV_DROPDOWN_PART_MAIN for Dropdown1_patch_dropdown
	static lv_style_t style_Dropdown1_patch_dropdown_main;
	lv_style_reset(&style_Dropdown1_patch_dropdown_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_dropdown_main
	lv_style_set_radius(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_color(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_dir(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_17);
	lv_style_set_text_line_space(&style_Dropdown1_patch_dropdown_main, LV_STATE_DEFAULT, 20);
	lv_obj_add_style(ui->Dropdown1_patch_dropdown, LV_DROPDOWN_PART_MAIN, &style_Dropdown1_patch_dropdown_main);

	//Write style LV_DROPDOWN_PART_SELECTED for Dropdown1_patch_dropdown
	static lv_style_t style_Dropdown1_patch_dropdown_selected;
	lv_style_reset(&style_Dropdown1_patch_dropdown_selected);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_dropdown_selected
	lv_style_set_radius(&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(
		&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(
		&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, 4);
	lv_style_set_text_color(
		&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(
		&style_Dropdown1_patch_dropdown_selected, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_16);
	lv_obj_add_style(ui->Dropdown1_patch_dropdown, LV_DROPDOWN_PART_SELECTED, &style_Dropdown1_patch_dropdown_selected);

	//Write style LV_DROPDOWN_PART_LIST for Dropdown1_patch_dropdown
	static lv_style_t style_Dropdown1_patch_dropdown_list;
	lv_style_reset(&style_Dropdown1_patch_dropdown_list);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_dropdown_list
	lv_style_set_radius(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_Dropdown1_patch_dropdown_list, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_16);
	lv_obj_add_style(ui->Dropdown1_patch_dropdown, LV_DROPDOWN_PART_LIST, &style_Dropdown1_patch_dropdown_list);
	lv_obj_set_pos(ui->Dropdown1_patch_dropdown, 4, 4);
	lv_obj_set_width(ui->Dropdown1_patch_dropdown, 312);

	//Write codes Dropdown1_dimming_simulation
	ui->Dropdown1_dimming_simulation = lv_cont_create(ui->Dropdown1, NULL);

	//Write style LV_CONT_PART_MAIN for Dropdown1_dimming_simulation
	static lv_style_t style_Dropdown1_dimming_simulation_main;
	lv_style_reset(&style_Dropdown1_dimming_simulation_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_dimming_simulation_main
	lv_style_set_radius(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(
		&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 150);
	lv_style_set_border_color(
		&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown1_dimming_simulation_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1_dimming_simulation, LV_CONT_PART_MAIN, &style_Dropdown1_dimming_simulation_main);
	lv_obj_set_pos(ui->Dropdown1_dimming_simulation, 0, 0);
	lv_obj_set_size(ui->Dropdown1_dimming_simulation, 320, 240);
	lv_obj_set_click(ui->Dropdown1_dimming_simulation, false);
	lv_cont_set_layout(ui->Dropdown1_dimming_simulation, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->Dropdown1_dimming_simulation, LV_FIT_NONE);

	//Write codes Dropdown1_popup_menu
	ui->Dropdown1_popup_menu = lv_cont_create(ui->Dropdown1, NULL);

	//Write style LV_CONT_PART_MAIN for Dropdown1_popup_menu
	static lv_style_t style_Dropdown1_popup_menu_main;
	lv_style_reset(&style_Dropdown1_popup_menu_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_popup_menu_main
	lv_style_set_radius(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown1_popup_menu_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1_popup_menu, LV_CONT_PART_MAIN, &style_Dropdown1_popup_menu_main);
	lv_obj_set_pos(ui->Dropdown1_popup_menu, 20, 20);
	lv_obj_set_size(ui->Dropdown1_popup_menu, 280, 200);
	lv_obj_set_click(ui->Dropdown1_popup_menu, false);

	//Write codes Dropdown1_main_buttons
	ui->Dropdown1_main_buttons = lv_btnmatrix_create(ui->Dropdown1_popup_menu, NULL);
	static const char *Dropdown1_main_buttons_text_map[] = {
		"LOAD",
		"\n",
		"EXPLORE"
		"\n",
		"ADVANCED",
		"",
	};
	lv_btnmatrix_set_map(ui->Dropdown1_main_buttons, Dropdown1_main_buttons_text_map);

	//Write style LV_BTNMATRIX_PART_BG for Dropdown1_main_buttons
	static lv_style_t style_Dropdown1_main_buttons_bg;
	lv_style_reset(&style_Dropdown1_main_buttons_bg);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_main_buttons_bg
	lv_style_set_radius(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 7);
	lv_style_set_pad_bottom(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_inner(&style_Dropdown1_main_buttons_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->Dropdown1_main_buttons, LV_BTNMATRIX_PART_BG, &style_Dropdown1_main_buttons_bg);

	//Write style LV_BTNMATRIX_PART_BTN for Dropdown1_main_buttons
	static lv_style_t style_Dropdown1_main_buttons_btn;
	lv_style_reset(&style_Dropdown1_main_buttons_btn);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_main_buttons_btn
	lv_style_set_radius(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, 8);
	lv_style_set_bg_color(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xd6, 0xdd, 0xe3));
	lv_style_set_border_width(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown1_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));
	lv_obj_add_style(ui->Dropdown1_main_buttons, LV_BTNMATRIX_PART_BTN, &style_Dropdown1_main_buttons_btn);
	lv_obj_set_pos(ui->Dropdown1_main_buttons, 61, 94);
	lv_obj_set_size(ui->Dropdown1_main_buttons, 218, 104);

	//Write codes Dropdown1_patch_description
	ui->Dropdown1_patch_description = lv_label_create(ui->Dropdown1_popup_menu, NULL);
	lv_label_set_text(ui->Dropdown1_patch_description,
					  "Patch description, lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
					  "tempor incididunt ut labore");
	lv_label_set_long_mode(ui->Dropdown1_patch_description, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Dropdown1_patch_description, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for Dropdown1_patch_description
	static lv_style_t style_Dropdown1_patch_description_main;
	lv_style_reset(&style_Dropdown1_patch_description_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_description_main
	lv_style_set_radius(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(
		&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
	lv_style_set_text_font(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_16);
	lv_style_set_text_letter_space(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_bottom(&style_Dropdown1_patch_description_main, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->Dropdown1_patch_description, LV_LABEL_PART_MAIN, &style_Dropdown1_patch_description_main);
	lv_obj_set_pos(ui->Dropdown1_patch_description, 0, 25);
	lv_obj_set_size(ui->Dropdown1_patch_description, 280, 0);

	//Write codes Dropdown1_patch_nam_bg
	ui->Dropdown1_patch_nam_bg = lv_canvas_create(ui->Dropdown1_popup_menu, NULL);

	//Write style LV_CANVAS_PART_MAIN for Dropdown1_patch_nam_bg
	static lv_style_t style_Dropdown1_patch_nam_bg_main;
	lv_style_reset(&style_Dropdown1_patch_nam_bg_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_nam_bg_main
	lv_style_set_image_recolor(&style_Dropdown1_patch_nam_bg_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_image_recolor_opa(&style_Dropdown1_patch_nam_bg_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Dropdown1_patch_nam_bg, LV_CANVAS_PART_MAIN, &style_Dropdown1_patch_nam_bg_main);
	lv_obj_set_pos(ui->Dropdown1_patch_nam_bg, 0, 17);
	lv_obj_set_size(ui->Dropdown1_patch_nam_bg, 280, 8);
	lv_color_t *buf_Dropdown1_patch_nam_bg = (lv_color_t *)lv_mem_alloc(280 * 8 * 4);
	lv_canvas_set_buffer(ui->Dropdown1_patch_nam_bg, buf_Dropdown1_patch_nam_bg, 280, 8, LV_IMG_CF_TRUE_COLOR);

	//Write codes Dropdown1_line_header
	ui->Dropdown1_line_header = lv_canvas_create(ui->Dropdown1_popup_menu, NULL);

	//Write style LV_CANVAS_PART_MAIN for Dropdown1_line_header
	static lv_style_t style_Dropdown1_line_header_main;
	lv_style_reset(&style_Dropdown1_line_header_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_line_header_main
	lv_style_set_image_recolor(&style_Dropdown1_line_header_main, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x8c, 0xcd));
	lv_style_set_image_recolor_opa(&style_Dropdown1_line_header_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Dropdown1_line_header, LV_CANVAS_PART_MAIN, &style_Dropdown1_line_header_main);
	lv_obj_set_pos(ui->Dropdown1_line_header, 0, 24);
	lv_obj_set_size(ui->Dropdown1_line_header, 280, 2);
	lv_color_t *buf_Dropdown1_line_header = (lv_color_t *)lv_mem_alloc(280 * 2 * 4);
	lv_canvas_set_buffer(ui->Dropdown1_line_header, buf_Dropdown1_line_header, 280, 2, LV_IMG_CF_TRUE_COLOR);

	//Write codes Dropdown1_patch_name
	ui->Dropdown1_patch_name = lv_label_create(ui->Dropdown1_popup_menu, NULL);
	lv_label_set_text(ui->Dropdown1_patch_name, "Patch Name 1");
	lv_label_set_long_mode(ui->Dropdown1_patch_name, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Dropdown1_patch_name, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Dropdown1_patch_name
	static lv_style_t style_Dropdown1_patch_name_main;
	lv_style_reset(&style_Dropdown1_patch_name_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_patch_name_main
	lv_style_set_radius(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_color(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_dir(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, lv_color_make(0x1c, 0x1c, 0x1c));
	lv_style_set_text_font(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_17);
	lv_style_set_text_letter_space(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_bottom(&style_Dropdown1_patch_name_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1_patch_name, LV_LABEL_PART_MAIN, &style_Dropdown1_patch_name_main);
	lv_obj_set_pos(ui->Dropdown1_patch_name, 0, 0);
	lv_obj_set_size(ui->Dropdown1_patch_name, 280, 0);

	//Write codes Dropdown1_back_button
	ui->Dropdown1_back_button = lv_imgbtn_create(ui->Dropdown1_popup_menu, NULL);

	//Write style LV_IMGBTN_PART_MAIN for Dropdown1_back_button
	static lv_style_t style_Dropdown1_back_button_main;
	lv_style_reset(&style_Dropdown1_back_button_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_back_button_main
	lv_style_set_text_color(&style_Dropdown1_back_button_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_Dropdown1_back_button_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_image_recolor_opa(&style_Dropdown1_back_button_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_Dropdown1_back_button_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Dropdown1_back_button, LV_IMGBTN_PART_MAIN, &style_Dropdown1_back_button_main);
	lv_obj_set_pos(ui->Dropdown1_back_button, 7, 101);
	lv_obj_set_size(ui->Dropdown1_back_button, 52, 92);
	lv_imgbtn_set_src(ui->Dropdown1_back_button, LV_BTN_STATE_RELEASED, &_Asset_73_alpha_52x92);
	lv_imgbtn_set_checkable(ui->Dropdown1_back_button, true);

	//Write codes Dropdown1_back_txt
	ui->Dropdown1_back_txt = lv_label_create(ui->Dropdown1_popup_menu, NULL);
	lv_label_set_text(ui->Dropdown1_back_txt, "BACK");
	lv_label_set_long_mode(ui->Dropdown1_back_txt, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Dropdown1_back_txt, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Dropdown1_back_txt
	static lv_style_t style_Dropdown1_back_txt_main;
	lv_style_reset(&style_Dropdown1_back_txt_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown1_back_txt_main
	lv_style_set_radius(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_text_font(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);
	lv_style_set_text_letter_space(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown1_back_txt_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown1_back_txt, LV_LABEL_PART_MAIN, &style_Dropdown1_back_txt_main);
	lv_obj_set_pos(ui->Dropdown1_back_txt, 10, 173);
	lv_obj_set_size(ui->Dropdown1_back_txt, 46, 0);
	lv_cont_set_layout(ui->Dropdown1_popup_menu, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->Dropdown1_popup_menu, LV_FIT_NONE);
}
