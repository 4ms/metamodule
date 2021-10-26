/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Dropdown_only(lv_ui *ui){

	//Write codes Dropdown_only
	ui->Dropdown_only = lv_obj_create(NULL, NULL);

	//Write codes Dropdown_only_background_simulation
	ui->Dropdown_only_background_simulation = lv_cont_create(ui->Dropdown_only, NULL);

	//Write style LV_CONT_PART_MAIN for Dropdown_only_background_simulation
	static lv_style_t style_Dropdown_only_background_simulation_main;
	lv_style_reset(&style_Dropdown_only_background_simulation_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown_only_background_simulation_main
	lv_style_set_radius(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Dropdown_only_background_simulation_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Dropdown_only_background_simulation, LV_CONT_PART_MAIN, &style_Dropdown_only_background_simulation_main);
	lv_obj_set_pos(ui->Dropdown_only_background_simulation, 0, 0);
	lv_obj_set_size(ui->Dropdown_only_background_simulation, 320, 240);
	lv_obj_set_click(ui->Dropdown_only_background_simulation, false);
	lv_cont_set_layout(ui->Dropdown_only_background_simulation, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->Dropdown_only_background_simulation, LV_FIT_NONE);

	//Write codes Dropdown_only_patch_dropdown
	ui->Dropdown_only_patch_dropdown = lv_dropdown_create(ui->Dropdown_only, NULL);
	lv_dropdown_set_options(ui->Dropdown_only_patch_dropdown, "Patch Name 1\nPatch Name 2\nPatch Name 3\nPatch Name 4\nPatch Name 5\nPatch Name 6\nPatch Name 7\nPatch Name 8");
	lv_dropdown_set_max_height(ui->Dropdown_only_patch_dropdown, 207);
	lv_dropdown_set_symbol(ui->Dropdown_only_patch_dropdown, NULL);

	//Write style LV_DROPDOWN_PART_MAIN for Dropdown_only_patch_dropdown
	static lv_style_t style_Dropdown_only_patch_dropdown_main;
	lv_style_reset(&style_Dropdown_only_patch_dropdown_main);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown_only_patch_dropdown_main
	lv_style_set_radius(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_color(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
	lv_style_set_bg_grad_dir(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_16);
	lv_style_set_text_line_space(&style_Dropdown_only_patch_dropdown_main, LV_STATE_DEFAULT, 20);
	lv_obj_add_style(ui->Dropdown_only_patch_dropdown, LV_DROPDOWN_PART_MAIN, &style_Dropdown_only_patch_dropdown_main);

	//Write style LV_DROPDOWN_PART_SELECTED for Dropdown_only_patch_dropdown
	static lv_style_t style_Dropdown_only_patch_dropdown_selected;
	lv_style_reset(&style_Dropdown_only_patch_dropdown_selected);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown_only_patch_dropdown_selected
	lv_style_set_radius(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, 4);
	lv_style_set_text_color(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_Dropdown_only_patch_dropdown_selected, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_16);
	lv_obj_add_style(ui->Dropdown_only_patch_dropdown, LV_DROPDOWN_PART_SELECTED, &style_Dropdown_only_patch_dropdown_selected);

	//Write style LV_DROPDOWN_PART_LIST for Dropdown_only_patch_dropdown
	static lv_style_t style_Dropdown_only_patch_dropdown_list;
	lv_style_reset(&style_Dropdown_only_patch_dropdown_list);

	//Write style state: LV_STATE_DEFAULT for style_Dropdown_only_patch_dropdown_list
	lv_style_set_radius(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));
	lv_style_set_text_font(&style_Dropdown_only_patch_dropdown_list, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_16);
	lv_obj_add_style(ui->Dropdown_only_patch_dropdown, LV_DROPDOWN_PART_LIST, &style_Dropdown_only_patch_dropdown_list);
	lv_obj_set_pos(ui->Dropdown_only_patch_dropdown, 4, 4);
	lv_obj_set_width(ui->Dropdown_only_patch_dropdown, 312);
}