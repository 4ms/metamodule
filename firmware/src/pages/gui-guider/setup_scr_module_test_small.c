/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_module_test_small(lv_ui *ui){

	//Write codes module_test_small
	ui->module_test_small = lv_obj_create(NULL, NULL);

	//Write codes module_test_small_img_1
	ui->module_test_small_img_1 = lv_img_create(ui->module_test_small, NULL);

	//Write style LV_IMG_PART_MAIN for module_test_small_img_1
	static lv_style_t style_module_test_small_img_1_main;
	lv_style_reset(&style_module_test_small_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_img_1_main
	lv_style_set_image_recolor(&style_module_test_small_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_module_test_small_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_module_test_small_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->module_test_small_img_1, LV_IMG_PART_MAIN, &style_module_test_small_img_1_main);
	lv_obj_set_pos(ui->module_test_small_img_1, 0, 0);
	lv_obj_set_size(ui->module_test_small_img_1, 246, 240);
	lv_obj_set_click(ui->module_test_small_img_1, true);
	lv_img_set_src(ui->module_test_small_img_1,&_module_graphic_SMR_small_alpha_246x240);
	lv_img_set_pivot(ui->module_test_small_img_1, 0,0);
	lv_img_set_angle(ui->module_test_small_img_1, 0);
}