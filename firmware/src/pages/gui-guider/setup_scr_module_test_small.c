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

	//Write codes module_test_small_btn_1
	ui->module_test_small_btn_1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_btn_1
	static lv_style_t style_module_test_small_btn_1_main;
	lv_style_reset(&style_module_test_small_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_btn_1_main
	lv_style_set_radius(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 70);

	lv_style_set_bg_color(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_color(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_grad_dir(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 0);

	lv_style_set_border_color(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xdd, 0xb6, 0x00));
	lv_style_set_border_width(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 0);

	lv_style_set_outline_color(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xd6, 0x00));
	lv_style_set_outline_width(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 7);
	lv_style_set_outline_opa(&style_module_test_small_btn_1_main, LV_STATE_DEFAULT, 0);

	lv_obj_add_style(ui->module_test_small_btn_1, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_1, 8, 24);
	lv_obj_set_size(ui->module_test_small_btn_1, 13, 13);
	ui->module_test_small_btn_1_label = lv_label_create(ui->module_test_small_btn_1, NULL);
	lv_label_set_text(ui->module_test_small_btn_1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_2
	ui->module_test_small_btn_2 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_2, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_2, 7, 48);
	lv_obj_set_size(ui->module_test_small_btn_2, 13, 13);
	ui->module_test_small_btn_2_label = lv_label_create(ui->module_test_small_btn_2, NULL);
	lv_label_set_text(ui->module_test_small_btn_2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_3
	ui->module_test_small_btn_3 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_3, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_3, 8, 74);
	lv_obj_set_size(ui->module_test_small_btn_3, 13, 13);
	ui->module_test_small_btn_3_label = lv_label_create(ui->module_test_small_btn_3, NULL);
	lv_label_set_text(ui->module_test_small_btn_3_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_4
	ui->module_test_small_btn_4 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_4, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_4, 9, 95);
	lv_obj_set_size(ui->module_test_small_btn_4, 13, 13);
	ui->module_test_small_btn_4_label = lv_label_create(ui->module_test_small_btn_4, NULL);
	lv_label_set_text(ui->module_test_small_btn_4_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_5
	ui->module_test_small_btn_5 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_5, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_5, 8, 117);
	lv_obj_set_size(ui->module_test_small_btn_5, 13, 13);
	ui->module_test_small_btn_5_label = lv_label_create(ui->module_test_small_btn_5, NULL);
	lv_label_set_text(ui->module_test_small_btn_5_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_6
	ui->module_test_small_btn_6 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_6, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_6, 35, 104);
	lv_obj_set_size(ui->module_test_small_btn_6, 13, 13);
	ui->module_test_small_btn_6_label = lv_label_create(ui->module_test_small_btn_6, NULL);
	lv_label_set_text(ui->module_test_small_btn_6_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_7
	ui->module_test_small_btn_7 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_7, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_7, 228, 116);
	lv_obj_set_size(ui->module_test_small_btn_7, 13, 13);
	ui->module_test_small_btn_7_label = lv_label_create(ui->module_test_small_btn_7, NULL);
	lv_label_set_text(ui->module_test_small_btn_7_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_7_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_8
	ui->module_test_small_btn_8 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_8, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_8, 35, 19);
	lv_obj_set_size(ui->module_test_small_btn_8, 13, 13);
	ui->module_test_small_btn_8_label = lv_label_create(ui->module_test_small_btn_8, NULL);
	lv_label_set_text(ui->module_test_small_btn_8_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_8_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_9
	ui->module_test_small_btn_9 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_9, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_9, 66, 19);
	lv_obj_set_size(ui->module_test_small_btn_9, 13, 13);
	ui->module_test_small_btn_9_label = lv_label_create(ui->module_test_small_btn_9, NULL);
	lv_label_set_text(ui->module_test_small_btn_9_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_9_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_10
	ui->module_test_small_btn_10 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_10, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_10, 96, 19);
	lv_obj_set_size(ui->module_test_small_btn_10, 13, 13);
	ui->module_test_small_btn_10_label = lv_label_create(ui->module_test_small_btn_10, NULL);
	lv_label_set_text(ui->module_test_small_btn_10_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_10_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_11
	ui->module_test_small_btn_11 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_11, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_11, 137, 19);
	lv_obj_set_size(ui->module_test_small_btn_11, 13, 13);
	ui->module_test_small_btn_11_label = lv_label_create(ui->module_test_small_btn_11, NULL);
	lv_label_set_text(ui->module_test_small_btn_11_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_11_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_12
	ui->module_test_small_btn_12 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_12, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_12, 168, 19);
	lv_obj_set_size(ui->module_test_small_btn_12, 13, 13);
	ui->module_test_small_btn_12_label = lv_label_create(ui->module_test_small_btn_12, NULL);
	lv_label_set_text(ui->module_test_small_btn_12_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_12_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_13
	ui->module_test_small_btn_13 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_13, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_13, 198, 19);
	lv_obj_set_size(ui->module_test_small_btn_13, 13, 13);
	ui->module_test_small_btn_13_label = lv_label_create(ui->module_test_small_btn_13, NULL);
	lv_label_set_text(ui->module_test_small_btn_13_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_13_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_14
	ui->module_test_small_btn_14 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_14, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_14, 224, 24);
	lv_obj_set_size(ui->module_test_small_btn_14, 13, 13);
	ui->module_test_small_btn_14_label = lv_label_create(ui->module_test_small_btn_14, NULL);
	lv_label_set_text(ui->module_test_small_btn_14_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_14_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_15
	ui->module_test_small_btn_15 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_15, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_15, 224, 48);
	lv_obj_set_size(ui->module_test_small_btn_15, 13, 13);
	ui->module_test_small_btn_15_label = lv_label_create(ui->module_test_small_btn_15, NULL);
	lv_label_set_text(ui->module_test_small_btn_15_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_15_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_16
	ui->module_test_small_btn_16 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_16, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_16, 224, 74);
	lv_obj_set_size(ui->module_test_small_btn_16, 13, 13);
	ui->module_test_small_btn_16_label = lv_label_create(ui->module_test_small_btn_16, NULL);
	lv_label_set_text(ui->module_test_small_btn_16_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_16_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_17
	ui->module_test_small_btn_17 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_17, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_17, 225, 95);
	lv_obj_set_size(ui->module_test_small_btn_17, 13, 13);
	ui->module_test_small_btn_17_label = lv_label_create(ui->module_test_small_btn_17, NULL);
	lv_label_set_text(ui->module_test_small_btn_17_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_17_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_18
	ui->module_test_small_btn_18 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_18, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_18, 194, 43);
	lv_obj_set_size(ui->module_test_small_btn_18, 13, 13);
	ui->module_test_small_btn_18_label = lv_label_create(ui->module_test_small_btn_18, NULL);
	lv_label_set_text(ui->module_test_small_btn_18_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_18_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_19
	ui->module_test_small_btn_19 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_19, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_19, 164, 56);
	lv_obj_set_size(ui->module_test_small_btn_19, 13, 13);
	ui->module_test_small_btn_19_label = lv_label_create(ui->module_test_small_btn_19, NULL);
	lv_label_set_text(ui->module_test_small_btn_19_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_19_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_20
	ui->module_test_small_btn_20 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_20, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_20, 132, 68);
	lv_obj_set_size(ui->module_test_small_btn_20, 13, 13);
	ui->module_test_small_btn_20_label = lv_label_create(ui->module_test_small_btn_20, NULL);
	lv_label_set_text(ui->module_test_small_btn_20_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_20_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_21
	ui->module_test_small_btn_21 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_21, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_21, 103, 69);
	lv_obj_set_size(ui->module_test_small_btn_21, 13, 13);
	ui->module_test_small_btn_21_label = lv_label_create(ui->module_test_small_btn_21, NULL);
	lv_label_set_text(ui->module_test_small_btn_21_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_21_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_22
	ui->module_test_small_btn_22 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_22, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_22, 71, 57);
	lv_obj_set_size(ui->module_test_small_btn_22, 13, 13);
	ui->module_test_small_btn_22_label = lv_label_create(ui->module_test_small_btn_22, NULL);
	lv_label_set_text(ui->module_test_small_btn_22_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_22_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_23
	ui->module_test_small_btn_23 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_23, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_23, 40, 43);
	lv_obj_set_size(ui->module_test_small_btn_23, 13, 13);
	ui->module_test_small_btn_23_label = lv_label_create(ui->module_test_small_btn_23, NULL);
	lv_label_set_text(ui->module_test_small_btn_23_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_23_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_24
	ui->module_test_small_btn_24 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_24, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_24, 31, 130);
	lv_obj_set_size(ui->module_test_small_btn_24, 13, 13);
	ui->module_test_small_btn_24_label = lv_label_create(ui->module_test_small_btn_24, NULL);
	lv_label_set_text(ui->module_test_small_btn_24_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_24_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_25
	ui->module_test_small_btn_25 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_25, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_25, 59, 130);
	lv_obj_set_size(ui->module_test_small_btn_25, 13, 13);
	ui->module_test_small_btn_25_label = lv_label_create(ui->module_test_small_btn_25, NULL);
	lv_label_set_text(ui->module_test_small_btn_25_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_25_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_26
	ui->module_test_small_btn_26 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_26, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_26, 88, 130);
	lv_obj_set_size(ui->module_test_small_btn_26, 13, 13);
	ui->module_test_small_btn_26_label = lv_label_create(ui->module_test_small_btn_26, NULL);
	lv_label_set_text(ui->module_test_small_btn_26_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_26_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_27
	ui->module_test_small_btn_27 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_27, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_27, 116, 132);
	lv_obj_set_size(ui->module_test_small_btn_27, 13, 13);
	ui->module_test_small_btn_27_label = lv_label_create(ui->module_test_small_btn_27, NULL);
	lv_label_set_text(ui->module_test_small_btn_27_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_27_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_28
	ui->module_test_small_btn_28 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_28, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_28, 145, 130);
	lv_obj_set_size(ui->module_test_small_btn_28, 13, 13);
	ui->module_test_small_btn_28_label = lv_label_create(ui->module_test_small_btn_28, NULL);
	lv_label_set_text(ui->module_test_small_btn_28_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_28_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_29
	ui->module_test_small_btn_29 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_29, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_29, 173, 131);
	lv_obj_set_size(ui->module_test_small_btn_29, 13, 13);
	ui->module_test_small_btn_29_label = lv_label_create(ui->module_test_small_btn_29, NULL);
	lv_label_set_text(ui->module_test_small_btn_29_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_29_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_30
	ui->module_test_small_btn_30 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_30, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_30, 201, 130);
	lv_obj_set_size(ui->module_test_small_btn_30, 13, 13);
	ui->module_test_small_btn_30_label = lv_label_create(ui->module_test_small_btn_30, NULL);
	lv_label_set_text(ui->module_test_small_btn_30_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_30_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_31
	ui->module_test_small_btn_31 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_31, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_31, 227, 135);
	lv_obj_set_size(ui->module_test_small_btn_31, 13, 13);
	ui->module_test_small_btn_31_label = lv_label_create(ui->module_test_small_btn_31, NULL);
	lv_label_set_text(ui->module_test_small_btn_31_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_31_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_32
	ui->module_test_small_btn_32 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_32, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_32, 222, 157);
	lv_obj_set_size(ui->module_test_small_btn_32, 13, 13);
	ui->module_test_small_btn_32_label = lv_label_create(ui->module_test_small_btn_32, NULL);
	lv_label_set_text(ui->module_test_small_btn_32_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_32_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_33
	ui->module_test_small_btn_33 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_33, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_33, 194, 157);
	lv_obj_set_size(ui->module_test_small_btn_33, 13, 13);
	ui->module_test_small_btn_33_label = lv_label_create(ui->module_test_small_btn_33, NULL);
	lv_label_set_text(ui->module_test_small_btn_33_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_33_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_34
	ui->module_test_small_btn_34 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_34, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_34, 209, 180);
	lv_obj_set_size(ui->module_test_small_btn_34, 13, 13);
	ui->module_test_small_btn_34_label = lv_label_create(ui->module_test_small_btn_34, NULL);
	lv_label_set_text(ui->module_test_small_btn_34_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_34_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_35
	ui->module_test_small_btn_35 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_35, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_35, 226, 201);
	lv_obj_set_size(ui->module_test_small_btn_35, 13, 13);
	ui->module_test_small_btn_35_label = lv_label_create(ui->module_test_small_btn_35, NULL);
	lv_label_set_text(ui->module_test_small_btn_35_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_35_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_36
	ui->module_test_small_btn_36 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_36, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_36, 163, 155);
	lv_obj_set_size(ui->module_test_small_btn_36, 13, 13);
	ui->module_test_small_btn_36_label = lv_label_create(ui->module_test_small_btn_36, NULL);
	lv_label_set_text(ui->module_test_small_btn_36_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_36_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_37
	ui->module_test_small_btn_37 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_37, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_37, 187, 203);
	lv_obj_set_size(ui->module_test_small_btn_37, 13, 13);
	ui->module_test_small_btn_37_label = lv_label_create(ui->module_test_small_btn_37, NULL);
	lv_label_set_text(ui->module_test_small_btn_37_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_37_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_38
	ui->module_test_small_btn_38 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_38, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_38, 170, 180);
	lv_obj_set_size(ui->module_test_small_btn_38, 13, 13);
	ui->module_test_small_btn_38_label = lv_label_create(ui->module_test_small_btn_38, NULL);
	lv_label_set_text(ui->module_test_small_btn_38_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_38_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_39
	ui->module_test_small_btn_39 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_39, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_39, 117, 181);
	lv_obj_set_size(ui->module_test_small_btn_39, 13, 13);
	ui->module_test_small_btn_39_label = lv_label_create(ui->module_test_small_btn_39, NULL);
	lv_label_set_text(ui->module_test_small_btn_39_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_39_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_40
	ui->module_test_small_btn_40 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_40, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_40, 70, 155);
	lv_obj_set_size(ui->module_test_small_btn_40, 13, 13);
	ui->module_test_small_btn_40_label = lv_label_create(ui->module_test_small_btn_40, NULL);
	lv_label_set_text(ui->module_test_small_btn_40_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_40_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_41
	ui->module_test_small_btn_41 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_41, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_41, 37, 157);
	lv_obj_set_size(ui->module_test_small_btn_41, 13, 13);
	ui->module_test_small_btn_41_label = lv_label_create(ui->module_test_small_btn_41, NULL);
	lv_label_set_text(ui->module_test_small_btn_41_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_41_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_42
	ui->module_test_small_btn_42 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_42, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_42, 11, 156);
	lv_obj_set_size(ui->module_test_small_btn_42, 13, 13);
	ui->module_test_small_btn_42_label = lv_label_create(ui->module_test_small_btn_42, NULL);
	lv_label_set_text(ui->module_test_small_btn_42_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_42_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_43
	ui->module_test_small_btn_43 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_43, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_43, 24, 180);
	lv_obj_set_size(ui->module_test_small_btn_43, 13, 13);
	ui->module_test_small_btn_43_label = lv_label_create(ui->module_test_small_btn_43, NULL);
	lv_label_set_text(ui->module_test_small_btn_43_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_43_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_44
	ui->module_test_small_btn_44 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_44, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_44, 46, 201);
	lv_obj_set_size(ui->module_test_small_btn_44, 13, 13);
	ui->module_test_small_btn_44_label = lv_label_create(ui->module_test_small_btn_44, NULL);
	lv_label_set_text(ui->module_test_small_btn_44_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_44_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_45
	ui->module_test_small_btn_45 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_45, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_45, 63, 180);
	lv_obj_set_size(ui->module_test_small_btn_45, 13, 13);
	ui->module_test_small_btn_45_label = lv_label_create(ui->module_test_small_btn_45, NULL);
	lv_label_set_text(ui->module_test_small_btn_45_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_45_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_47
	ui->module_test_small_btn_47 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_47, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_47, 9, 205);
	lv_obj_set_size(ui->module_test_small_btn_47, 13, 13);
	ui->module_test_small_btn_47_label = lv_label_create(ui->module_test_small_btn_47, NULL);
	lv_label_set_text(ui->module_test_small_btn_47_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_47_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_46
	ui->module_test_small_btn_46 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_46, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_46, 199, 103);
	lv_obj_set_size(ui->module_test_small_btn_46, 13, 13);
	ui->module_test_small_btn_46_label = lv_label_create(ui->module_test_small_btn_46, NULL);
	lv_label_set_text(ui->module_test_small_btn_46_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_46_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_48
	ui->module_test_small_btn_48 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_48, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_48, 168, 103);
	lv_obj_set_size(ui->module_test_small_btn_48, 13, 13);
	ui->module_test_small_btn_48_label = lv_label_create(ui->module_test_small_btn_48, NULL);
	lv_label_set_text(ui->module_test_small_btn_48_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_48_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_49
	ui->module_test_small_btn_49 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_49, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_49, 137, 103);
	lv_obj_set_size(ui->module_test_small_btn_49, 13, 13);
	ui->module_test_small_btn_49_label = lv_label_create(ui->module_test_small_btn_49, NULL);
	lv_label_set_text(ui->module_test_small_btn_49_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_49_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_50
	ui->module_test_small_btn_50 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_50, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_50, 95, 103);
	lv_obj_set_size(ui->module_test_small_btn_50, 13, 13);
	ui->module_test_small_btn_50_label = lv_label_create(ui->module_test_small_btn_50, NULL);
	lv_label_set_text(ui->module_test_small_btn_50_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_50_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_51
	ui->module_test_small_btn_51 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_51, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_51, 64, 103);
	lv_obj_set_size(ui->module_test_small_btn_51, 13, 13);
	ui->module_test_small_btn_51_label = lv_label_create(ui->module_test_small_btn_51, NULL);
	lv_label_set_text(ui->module_test_small_btn_51_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_51_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_btn_52
	ui->module_test_small_btn_52 = lv_btn_create(ui->module_test_small, NULL);

	lv_obj_add_style(ui->module_test_small_btn_52, LV_BTN_PART_MAIN, &style_module_test_small_btn_1_main);
	lv_obj_set_pos(ui->module_test_small_btn_52, 32, 103);
	lv_obj_set_size(ui->module_test_small_btn_52, 13, 13);
	ui->module_test_small_btn_52_label = lv_label_create(ui->module_test_small_btn_52, NULL);
	lv_label_set_text(ui->module_test_small_btn_52_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_btn_52_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
}
