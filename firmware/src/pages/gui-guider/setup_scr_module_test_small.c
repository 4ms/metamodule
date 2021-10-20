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

	//Write codes module_test_small_SMR
	ui->module_test_small_SMR = lv_img_create(ui->module_test_small, NULL);

	//Write style LV_IMG_PART_MAIN for module_test_small_SMR
	static lv_style_t style_module_test_small_SMR_main;
	lv_style_reset(&style_module_test_small_SMR_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_SMR_main
	lv_style_set_image_recolor(&style_module_test_small_SMR_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_module_test_small_SMR_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_module_test_small_SMR_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->module_test_small_SMR, LV_IMG_PART_MAIN, &style_module_test_small_SMR_main);
	lv_obj_set_pos(ui->module_test_small_SMR, 0, 0);
	lv_obj_set_size(ui->module_test_small_SMR, 246, 240);
	lv_obj_set_click(ui->module_test_small_SMR, true);
	lv_img_set_src(ui->module_test_small_SMR,&_module_graphic_SMR_small_alpha_246x240);
	lv_img_set_pivot(ui->module_test_small_SMR, 0,0);
	lv_img_set_angle(ui->module_test_small_SMR, 0);

	//Write codes module_test_small_freq_nudge1
	ui->module_test_small_freq_nudge1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_nudge1
	static lv_style_t style_module_test_small_freq_nudge1_main;
	lv_style_reset(&style_module_test_small_freq_nudge1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_nudge1_main
	lv_style_set_radius(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xd6, 0x00));
	lv_style_set_outline_opa(&style_module_test_small_freq_nudge1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_nudge1, LV_BTN_PART_MAIN, &style_module_test_small_freq_nudge1_main);
	lv_obj_set_pos(ui->module_test_small_freq_nudge1, 8, 24);
	lv_obj_set_size(ui->module_test_small_freq_nudge1, 13, 13);
	ui->module_test_small_freq_nudge1_label = lv_label_create(ui->module_test_small_freq_nudge1, NULL);
	lv_label_set_text(ui->module_test_small_freq_nudge1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_nudge1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_freq_cv1
	ui->module_test_small_freq_cv1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_cv1
	static lv_style_t style_module_test_small_freq_cv1_main;
	lv_style_reset(&style_module_test_small_freq_cv1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_cv1_main
	lv_style_set_radius(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_freq_cv1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_cv1, LV_BTN_PART_MAIN, &style_module_test_small_freq_cv1_main);
	lv_obj_set_pos(ui->module_test_small_freq_cv1, 7, 48);
	lv_obj_set_size(ui->module_test_small_freq_cv1, 13, 13);
	ui->module_test_small_freq_cv1_label = lv_label_create(ui->module_test_small_freq_cv1, NULL);
	lv_label_set_text(ui->module_test_small_freq_cv1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_cv1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lock1
	ui->module_test_small_lock1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lock1
	static lv_style_t style_module_test_small_lock1_main;
	lv_style_reset(&style_module_test_small_lock1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lock1_main
	lv_style_set_radius(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lock1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lock1, LV_BTN_PART_MAIN, &style_module_test_small_lock1_main);
	lv_obj_set_pos(ui->module_test_small_lock1, 8, 74);
	lv_obj_set_size(ui->module_test_small_lock1, 13, 13);
	ui->module_test_small_lock1_label = lv_label_create(ui->module_test_small_lock1, NULL);
	lv_label_set_text(ui->module_test_small_lock1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lock1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_freq_switch1
	ui->module_test_small_freq_switch1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_switch1
	static lv_style_t style_module_test_small_freq_switch1_main;
	lv_style_reset(&style_module_test_small_freq_switch1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_switch1_main
	lv_style_set_radius(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_freq_switch1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_switch1, LV_BTN_PART_MAIN, &style_module_test_small_freq_switch1_main);
	lv_obj_set_pos(ui->module_test_small_freq_switch1, 9, 95);
	lv_obj_set_size(ui->module_test_small_freq_switch1, 13, 13);
	ui->module_test_small_freq_switch1_label = lv_label_create(ui->module_test_small_freq_switch1, NULL);
	lv_label_set_text(ui->module_test_small_freq_switch1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_switch1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock1
	ui->module_test_small_button_lock1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock1
	static lv_style_t style_module_test_small_button_lock1_main;
	lv_style_reset(&style_module_test_small_button_lock1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock1_main
	lv_style_set_radius(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock1, LV_BTN_PART_MAIN, &style_module_test_small_button_lock1_main);
	lv_obj_set_pos(ui->module_test_small_button_lock1, 35, 19);
	lv_obj_set_size(ui->module_test_small_button_lock1, 13, 13);
	ui->module_test_small_button_lock1_label = lv_label_create(ui->module_test_small_button_lock1, NULL);
	lv_label_set_text(ui->module_test_small_button_lock1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock2
	ui->module_test_small_button_lock2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock2
	static lv_style_t style_module_test_small_button_lock2_main;
	lv_style_reset(&style_module_test_small_button_lock2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock2_main
	lv_style_set_radius(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock2, LV_BTN_PART_MAIN, &style_module_test_small_button_lock2_main);
	lv_obj_set_pos(ui->module_test_small_button_lock2, 66, 19);
	lv_obj_set_size(ui->module_test_small_button_lock2, 13, 13);
	ui->module_test_small_button_lock2_label = lv_label_create(ui->module_test_small_button_lock2, NULL);
	lv_label_set_text(ui->module_test_small_button_lock2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock3
	ui->module_test_small_button_lock3 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock3
	static lv_style_t style_module_test_small_button_lock3_main;
	lv_style_reset(&style_module_test_small_button_lock3_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock3_main
	lv_style_set_radius(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock3, LV_BTN_PART_MAIN, &style_module_test_small_button_lock3_main);
	lv_obj_set_pos(ui->module_test_small_button_lock3, 96, 19);
	lv_obj_set_size(ui->module_test_small_button_lock3, 13, 13);
	ui->module_test_small_button_lock3_label = lv_label_create(ui->module_test_small_button_lock3, NULL);
	lv_label_set_text(ui->module_test_small_button_lock3_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock4
	ui->module_test_small_button_lock4 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock4
	static lv_style_t style_module_test_small_button_lock4_main;
	lv_style_reset(&style_module_test_small_button_lock4_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock4_main
	lv_style_set_radius(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock4, LV_BTN_PART_MAIN, &style_module_test_small_button_lock4_main);
	lv_obj_set_pos(ui->module_test_small_button_lock4, 137, 19);
	lv_obj_set_size(ui->module_test_small_button_lock4, 13, 13);
	ui->module_test_small_button_lock4_label = lv_label_create(ui->module_test_small_button_lock4, NULL);
	lv_label_set_text(ui->module_test_small_button_lock4_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock5
	ui->module_test_small_button_lock5 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock5
	static lv_style_t style_module_test_small_button_lock5_main;
	lv_style_reset(&style_module_test_small_button_lock5_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock5_main
	lv_style_set_radius(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock5, LV_BTN_PART_MAIN, &style_module_test_small_button_lock5_main);
	lv_obj_set_pos(ui->module_test_small_button_lock5, 168, 19);
	lv_obj_set_size(ui->module_test_small_button_lock5, 13, 13);
	ui->module_test_small_button_lock5_label = lv_label_create(ui->module_test_small_button_lock5, NULL);
	lv_label_set_text(ui->module_test_small_button_lock5_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_button_lock6
	ui->module_test_small_button_lock6 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_button_lock6
	static lv_style_t style_module_test_small_button_lock6_main;
	lv_style_reset(&style_module_test_small_button_lock6_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_button_lock6_main
	lv_style_set_radius(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_button_lock6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_button_lock6, LV_BTN_PART_MAIN, &style_module_test_small_button_lock6_main);
	lv_obj_set_pos(ui->module_test_small_button_lock6, 198, 19);
	lv_obj_set_size(ui->module_test_small_button_lock6, 13, 13);
	ui->module_test_small_button_lock6_label = lv_label_create(ui->module_test_small_button_lock6, NULL);
	lv_label_set_text(ui->module_test_small_button_lock6_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_button_lock6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_freq_nudge2
	ui->module_test_small_freq_nudge2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_nudge2
	static lv_style_t style_module_test_small_freq_nudge2_main;
	lv_style_reset(&style_module_test_small_freq_nudge2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_nudge2_main
	lv_style_set_radius(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_freq_nudge2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_nudge2, LV_BTN_PART_MAIN, &style_module_test_small_freq_nudge2_main);
	lv_obj_set_pos(ui->module_test_small_freq_nudge2, 224, 24);
	lv_obj_set_size(ui->module_test_small_freq_nudge2, 13, 13);
	ui->module_test_small_freq_nudge2_label = lv_label_create(ui->module_test_small_freq_nudge2, NULL);
	lv_label_set_text(ui->module_test_small_freq_nudge2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_nudge2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_freq_cv2
	ui->module_test_small_freq_cv2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_cv2
	static lv_style_t style_module_test_small_freq_cv2_main;
	lv_style_reset(&style_module_test_small_freq_cv2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_cv2_main
	lv_style_set_radius(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_freq_cv2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_cv2, LV_BTN_PART_MAIN, &style_module_test_small_freq_cv2_main);
	lv_obj_set_pos(ui->module_test_small_freq_cv2, 224, 48);
	lv_obj_set_size(ui->module_test_small_freq_cv2, 13, 13);
	ui->module_test_small_freq_cv2_label = lv_label_create(ui->module_test_small_freq_cv2, NULL);
	lv_label_set_text(ui->module_test_small_freq_cv2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_cv2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lock2
	ui->module_test_small_lock2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lock2
	static lv_style_t style_module_test_small_lock2_main;
	lv_style_reset(&style_module_test_small_lock2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lock2_main
	lv_style_set_radius(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lock2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lock2, LV_BTN_PART_MAIN, &style_module_test_small_lock2_main);
	lv_obj_set_pos(ui->module_test_small_lock2, 224, 74);
	lv_obj_set_size(ui->module_test_small_lock2, 13, 13);
	ui->module_test_small_lock2_label = lv_label_create(ui->module_test_small_lock2, NULL);
	lv_label_set_text(ui->module_test_small_lock2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lock2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_freq_switch2
	ui->module_test_small_freq_switch2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_freq_switch2
	static lv_style_t style_module_test_small_freq_switch2_main;
	lv_style_reset(&style_module_test_small_freq_switch2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_freq_switch2_main
	lv_style_set_radius(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_freq_switch2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_freq_switch2, LV_BTN_PART_MAIN, &style_module_test_small_freq_switch2_main);
	lv_obj_set_pos(ui->module_test_small_freq_switch2, 225, 95);
	lv_obj_set_size(ui->module_test_small_freq_switch2, 13, 13);
	ui->module_test_small_freq_switch2_label = lv_label_create(ui->module_test_small_freq_switch2, NULL);
	lv_label_set_text(ui->module_test_small_freq_switch2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_freq_switch2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider1
	ui->module_test_small_slider1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider1
	static lv_style_t style_module_test_small_slider1_main;
	lv_style_reset(&style_module_test_small_slider1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider1_main
	lv_style_set_radius(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider1, LV_BTN_PART_MAIN, &style_module_test_small_slider1_main);
	lv_obj_set_pos(ui->module_test_small_slider1, 40, 43);
	lv_obj_set_size(ui->module_test_small_slider1, 13, 13);
	ui->module_test_small_slider1_label = lv_label_create(ui->module_test_small_slider1, NULL);
	lv_label_set_text(ui->module_test_small_slider1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider2
	ui->module_test_small_slider2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider2
	static lv_style_t style_module_test_small_slider2_main;
	lv_style_reset(&style_module_test_small_slider2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider2_main
	lv_style_set_radius(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider2, LV_BTN_PART_MAIN, &style_module_test_small_slider2_main);
	lv_obj_set_pos(ui->module_test_small_slider2, 71, 57);
	lv_obj_set_size(ui->module_test_small_slider2, 13, 13);
	ui->module_test_small_slider2_label = lv_label_create(ui->module_test_small_slider2, NULL);
	lv_label_set_text(ui->module_test_small_slider2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider3
	ui->module_test_small_slider3 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider3
	static lv_style_t style_module_test_small_slider3_main;
	lv_style_reset(&style_module_test_small_slider3_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider3_main
	lv_style_set_radius(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider3, LV_BTN_PART_MAIN, &style_module_test_small_slider3_main);
	lv_obj_set_pos(ui->module_test_small_slider3, 101, 68);
	lv_obj_set_size(ui->module_test_small_slider3, 13, 13);
	ui->module_test_small_slider3_label = lv_label_create(ui->module_test_small_slider3, NULL);
	lv_label_set_text(ui->module_test_small_slider3_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider4
	ui->module_test_small_slider4 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider4
	static lv_style_t style_module_test_small_slider4_main;
	lv_style_reset(&style_module_test_small_slider4_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider4_main
	lv_style_set_radius(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider4, LV_BTN_PART_MAIN, &style_module_test_small_slider4_main);
	lv_obj_set_pos(ui->module_test_small_slider4, 132, 68);
	lv_obj_set_size(ui->module_test_small_slider4, 13, 13);
	ui->module_test_small_slider4_label = lv_label_create(ui->module_test_small_slider4, NULL);
	lv_label_set_text(ui->module_test_small_slider4_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider5
	ui->module_test_small_slider5 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider5
	static lv_style_t style_module_test_small_slider5_main;
	lv_style_reset(&style_module_test_small_slider5_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider5_main
	lv_style_set_radius(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider5, LV_BTN_PART_MAIN, &style_module_test_small_slider5_main);
	lv_obj_set_pos(ui->module_test_small_slider5, 164, 56);
	lv_obj_set_size(ui->module_test_small_slider5, 13, 13);
	ui->module_test_small_slider5_label = lv_label_create(ui->module_test_small_slider5, NULL);
	lv_label_set_text(ui->module_test_small_slider5_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_slider6
	ui->module_test_small_slider6 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_slider6
	static lv_style_t style_module_test_small_slider6_main;
	lv_style_reset(&style_module_test_small_slider6_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_slider6_main
	lv_style_set_radius(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_slider6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_slider6, LV_BTN_PART_MAIN, &style_module_test_small_slider6_main);
	lv_obj_set_pos(ui->module_test_small_slider6, 194, 43);
	lv_obj_set_size(ui->module_test_small_slider6, 13, 13);
	ui->module_test_small_slider6_label = lv_label_create(ui->module_test_small_slider6, NULL);
	lv_label_set_text(ui->module_test_small_slider6_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_slider6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_switch_cv_slew
	ui->module_test_small_switch_cv_slew = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_switch_cv_slew
	static lv_style_t style_module_test_small_switch_cv_slew_main;
	lv_style_reset(&style_module_test_small_switch_cv_slew_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_switch_cv_slew_main
	lv_style_set_radius(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_switch_cv_slew_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_switch_cv_slew, LV_BTN_PART_MAIN, &style_module_test_small_switch_cv_slew_main);
	lv_obj_set_pos(ui->module_test_small_switch_cv_slew, 8, 117);
	lv_obj_set_size(ui->module_test_small_switch_cv_slew, 13, 13);
	ui->module_test_small_switch_cv_slew_label = lv_label_create(ui->module_test_small_switch_cv_slew, NULL);
	lv_label_set_text(ui->module_test_small_switch_cv_slew_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_switch_cv_slew_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv1
	ui->module_test_small_lvl_cv1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv1
	static lv_style_t style_module_test_small_lvl_cv1_main;
	lv_style_reset(&style_module_test_small_lvl_cv1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv1_main
	lv_style_set_radius(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv1, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv1_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv1, 33, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv1, 13, 13);
	ui->module_test_small_lvl_cv1_label = lv_label_create(ui->module_test_small_lvl_cv1, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv2
	ui->module_test_small_lvl_cv2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv2
	static lv_style_t style_module_test_small_lvl_cv2_main;
	lv_style_reset(&style_module_test_small_lvl_cv2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv2_main
	lv_style_set_radius(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv2, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv2_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv2, 64, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv2, 13, 13);
	ui->module_test_small_lvl_cv2_label = lv_label_create(ui->module_test_small_lvl_cv2, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv3
	ui->module_test_small_lvl_cv3 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv3
	static lv_style_t style_module_test_small_lvl_cv3_main;
	lv_style_reset(&style_module_test_small_lvl_cv3_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv3_main
	lv_style_set_radius(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv3, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv3_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv3, 95, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv3, 13, 13);
	ui->module_test_small_lvl_cv3_label = lv_label_create(ui->module_test_small_lvl_cv3, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv3_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv4
	ui->module_test_small_lvl_cv4 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv4
	static lv_style_t style_module_test_small_lvl_cv4_main;
	lv_style_reset(&style_module_test_small_lvl_cv4_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv4_main
	lv_style_set_radius(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv4, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv4_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv4, 137, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv4, 13, 13);
	ui->module_test_small_lvl_cv4_label = lv_label_create(ui->module_test_small_lvl_cv4, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv4_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv5
	ui->module_test_small_lvl_cv5 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv5
	static lv_style_t style_module_test_small_lvl_cv5_main;
	lv_style_reset(&style_module_test_small_lvl_cv5_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv5_main
	lv_style_set_radius(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv5, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv5_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv5, 168, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv5, 13, 13);
	ui->module_test_small_lvl_cv5_label = lv_label_create(ui->module_test_small_lvl_cv5, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv5_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_lvl_cv6
	ui->module_test_small_lvl_cv6 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_lvl_cv6
	static lv_style_t style_module_test_small_lvl_cv6_main;
	lv_style_reset(&style_module_test_small_lvl_cv6_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_lvl_cv6_main
	lv_style_set_radius(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_lvl_cv6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_lvl_cv6, LV_BTN_PART_MAIN, &style_module_test_small_lvl_cv6_main);
	lv_obj_set_pos(ui->module_test_small_lvl_cv6, 199, 103);
	lv_obj_set_size(ui->module_test_small_lvl_cv6, 13, 13);
	ui->module_test_small_lvl_cv6_label = lv_label_create(ui->module_test_small_lvl_cv6, NULL);
	lv_label_set_text(ui->module_test_small_lvl_cv6_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_lvl_cv6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out1
	ui->module_test_small_env_out1 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out1
	static lv_style_t style_module_test_small_env_out1_main;
	lv_style_reset(&style_module_test_small_env_out1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out1_main
	lv_style_set_radius(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out1, LV_BTN_PART_MAIN, &style_module_test_small_env_out1_main);
	lv_obj_set_pos(ui->module_test_small_env_out1, 31, 130);
	lv_obj_set_size(ui->module_test_small_env_out1, 13, 13);
	ui->module_test_small_env_out1_label = lv_label_create(ui->module_test_small_env_out1, NULL);
	lv_label_set_text(ui->module_test_small_env_out1_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out2
	ui->module_test_small_env_out2 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out2
	static lv_style_t style_module_test_small_env_out2_main;
	lv_style_reset(&style_module_test_small_env_out2_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out2_main
	lv_style_set_radius(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out2, LV_BTN_PART_MAIN, &style_module_test_small_env_out2_main);
	lv_obj_set_pos(ui->module_test_small_env_out2, 59, 130);
	lv_obj_set_size(ui->module_test_small_env_out2, 13, 13);
	ui->module_test_small_env_out2_label = lv_label_create(ui->module_test_small_env_out2, NULL);
	lv_label_set_text(ui->module_test_small_env_out2_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out3
	ui->module_test_small_env_out3 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out3
	static lv_style_t style_module_test_small_env_out3_main;
	lv_style_reset(&style_module_test_small_env_out3_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out3_main
	lv_style_set_radius(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out3, LV_BTN_PART_MAIN, &style_module_test_small_env_out3_main);
	lv_obj_set_pos(ui->module_test_small_env_out3, 88, 130);
	lv_obj_set_size(ui->module_test_small_env_out3, 13, 13);
	ui->module_test_small_env_out3_label = lv_label_create(ui->module_test_small_env_out3, NULL);
	lv_label_set_text(ui->module_test_small_env_out3_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_rotate_cv
	ui->module_test_small_rotate_cv = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_rotate_cv
	static lv_style_t style_module_test_small_rotate_cv_main;
	lv_style_reset(&style_module_test_small_rotate_cv_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_rotate_cv_main
	lv_style_set_radius(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_rotate_cv_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_rotate_cv, LV_BTN_PART_MAIN, &style_module_test_small_rotate_cv_main);
	lv_obj_set_pos(ui->module_test_small_rotate_cv, 116, 132);
	lv_obj_set_size(ui->module_test_small_rotate_cv, 13, 13);
	ui->module_test_small_rotate_cv_label = lv_label_create(ui->module_test_small_rotate_cv, NULL);
	lv_label_set_text(ui->module_test_small_rotate_cv_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_rotate_cv_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out4
	ui->module_test_small_env_out4 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out4
	static lv_style_t style_module_test_small_env_out4_main;
	lv_style_reset(&style_module_test_small_env_out4_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out4_main
	lv_style_set_radius(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out4, LV_BTN_PART_MAIN, &style_module_test_small_env_out4_main);
	lv_obj_set_pos(ui->module_test_small_env_out4, 145, 130);
	lv_obj_set_size(ui->module_test_small_env_out4, 13, 13);
	ui->module_test_small_env_out4_label = lv_label_create(ui->module_test_small_env_out4, NULL);
	lv_label_set_text(ui->module_test_small_env_out4_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out5
	ui->module_test_small_env_out5 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out5
	static lv_style_t style_module_test_small_env_out5_main;
	lv_style_reset(&style_module_test_small_env_out5_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out5_main
	lv_style_set_radius(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out5, LV_BTN_PART_MAIN, &style_module_test_small_env_out5_main);
	lv_obj_set_pos(ui->module_test_small_env_out5, 173, 130);
	lv_obj_set_size(ui->module_test_small_env_out5, 13, 13);
	ui->module_test_small_env_out5_label = lv_label_create(ui->module_test_small_env_out5, NULL);
	lv_label_set_text(ui->module_test_small_env_out5_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_env_out6
	ui->module_test_small_env_out6 = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_env_out6
	static lv_style_t style_module_test_small_env_out6_main;
	lv_style_reset(&style_module_test_small_env_out6_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_env_out6_main
	lv_style_set_radius(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_env_out6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_env_out6, LV_BTN_PART_MAIN, &style_module_test_small_env_out6_main);
	lv_obj_set_pos(ui->module_test_small_env_out6, 201, 130);
	lv_obj_set_size(ui->module_test_small_env_out6, 13, 13);
	ui->module_test_small_env_out6_label = lv_label_create(ui->module_test_small_env_out6, NULL);
	lv_label_set_text(ui->module_test_small_env_out6_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_env_out6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_post_pre_switch
	ui->module_test_small_post_pre_switch = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_post_pre_switch
	static lv_style_t style_module_test_small_post_pre_switch_main;
	lv_style_reset(&style_module_test_small_post_pre_switch_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_post_pre_switch_main
	lv_style_set_radius(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_post_pre_switch_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_post_pre_switch, LV_BTN_PART_MAIN, &style_module_test_small_post_pre_switch_main);
	lv_obj_set_pos(ui->module_test_small_post_pre_switch, 228, 116);
	lv_obj_set_size(ui->module_test_small_post_pre_switch, 13, 13);
	ui->module_test_small_post_pre_switch_label = lv_label_create(ui->module_test_small_post_pre_switch, NULL);
	lv_label_set_text(ui->module_test_small_post_pre_switch_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_post_pre_switch_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_fast_slow_switch
	ui->module_test_small_fast_slow_switch = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_fast_slow_switch
	static lv_style_t style_module_test_small_fast_slow_switch_main;
	lv_style_reset(&style_module_test_small_fast_slow_switch_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_fast_slow_switch_main
	lv_style_set_radius(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_fast_slow_switch_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_fast_slow_switch, LV_BTN_PART_MAIN, &style_module_test_small_fast_slow_switch_main);
	lv_obj_set_pos(ui->module_test_small_fast_slow_switch, 227, 134);
	lv_obj_set_size(ui->module_test_small_fast_slow_switch, 13, 13);
	ui->module_test_small_fast_slow_switch_label = lv_label_create(ui->module_test_small_fast_slow_switch, NULL);
	lv_label_set_text(ui->module_test_small_fast_slow_switch_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_fast_slow_switch_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_input_odds
	ui->module_test_small_input_odds = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_input_odds
	static lv_style_t style_module_test_small_input_odds_main;
	lv_style_reset(&style_module_test_small_input_odds_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_input_odds_main
	lv_style_set_radius(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_input_odds_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_input_odds, LV_BTN_PART_MAIN, &style_module_test_small_input_odds_main);
	lv_obj_set_pos(ui->module_test_small_input_odds, 11, 156);
	lv_obj_set_size(ui->module_test_small_input_odds, 13, 13);
	ui->module_test_small_input_odds_label = lv_label_create(ui->module_test_small_input_odds, NULL);
	lv_label_set_text(ui->module_test_small_input_odds_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_input_odds_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_input_evens
	ui->module_test_small_input_evens = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_input_evens
	static lv_style_t style_module_test_small_input_evens_main;
	lv_style_reset(&style_module_test_small_input_evens_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_input_evens_main
	lv_style_set_radius(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_input_evens_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_input_evens, LV_BTN_PART_MAIN, &style_module_test_small_input_evens_main);
	lv_obj_set_pos(ui->module_test_small_input_evens, 37, 157);
	lv_obj_set_size(ui->module_test_small_input_evens, 13, 13);
	ui->module_test_small_input_evens_label = lv_label_create(ui->module_test_small_input_evens, NULL);
	lv_label_set_text(ui->module_test_small_input_evens_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_input_evens_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_rotate_trig_cntr
	ui->module_test_small_rotate_trig_cntr = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_rotate_trig_cntr
	static lv_style_t style_module_test_small_rotate_trig_cntr_main;
	lv_style_reset(&style_module_test_small_rotate_trig_cntr_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_rotate_trig_cntr_main
	lv_style_set_radius(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_rotate_trig_cntr_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_rotate_trig_cntr, LV_BTN_PART_MAIN, &style_module_test_small_rotate_trig_cntr_main);
	lv_obj_set_pos(ui->module_test_small_rotate_trig_cntr, 70, 155);
	lv_obj_set_size(ui->module_test_small_rotate_trig_cntr, 13, 13);
	ui->module_test_small_rotate_trig_cntr_label = lv_label_create(ui->module_test_small_rotate_trig_cntr, NULL);
	lv_label_set_text(ui->module_test_small_rotate_trig_cntr_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_rotate_trig_cntr_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_rotate_trig_clkw
	ui->module_test_small_rotate_trig_clkw = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_rotate_trig_clkw
	static lv_style_t style_module_test_small_rotate_trig_clkw_main;
	lv_style_reset(&style_module_test_small_rotate_trig_clkw_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_rotate_trig_clkw_main
	lv_style_set_radius(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_rotate_trig_clkw_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_rotate_trig_clkw, LV_BTN_PART_MAIN, &style_module_test_small_rotate_trig_clkw_main);
	lv_obj_set_pos(ui->module_test_small_rotate_trig_clkw, 163, 155);
	lv_obj_set_size(ui->module_test_small_rotate_trig_clkw, 13, 13);
	ui->module_test_small_rotate_trig_clkw_label = lv_label_create(ui->module_test_small_rotate_trig_clkw, NULL);
	lv_label_set_text(ui->module_test_small_rotate_trig_clkw_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_rotate_trig_clkw_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_output_odds
	ui->module_test_small_output_odds = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_output_odds
	static lv_style_t style_module_test_small_output_odds_main;
	lv_style_reset(&style_module_test_small_output_odds_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_output_odds_main
	lv_style_set_radius(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_output_odds_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_output_odds, LV_BTN_PART_MAIN, &style_module_test_small_output_odds_main);
	lv_obj_set_pos(ui->module_test_small_output_odds, 194, 157);
	lv_obj_set_size(ui->module_test_small_output_odds, 13, 13);
	ui->module_test_small_output_odds_label = lv_label_create(ui->module_test_small_output_odds, NULL);
	lv_label_set_text(ui->module_test_small_output_odds_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_output_odds_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_output_evens
	ui->module_test_small_output_evens = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_output_evens
	static lv_style_t style_module_test_small_output_evens_main;
	lv_style_reset(&style_module_test_small_output_evens_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_output_evens_main
	lv_style_set_radius(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_output_evens_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_output_evens, LV_BTN_PART_MAIN, &style_module_test_small_output_evens_main);
	lv_obj_set_pos(ui->module_test_small_output_evens, 222, 157);
	lv_obj_set_size(ui->module_test_small_output_evens, 13, 13);
	ui->module_test_small_output_evens_label = lv_label_create(ui->module_test_small_output_evens, NULL);
	lv_label_set_text(ui->module_test_small_output_evens_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_output_evens_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_scale_cv
	ui->module_test_small_scale_cv = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_scale_cv
	static lv_style_t style_module_test_small_scale_cv_main;
	lv_style_reset(&style_module_test_small_scale_cv_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_scale_cv_main
	lv_style_set_radius(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_scale_cv_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_scale_cv, LV_BTN_PART_MAIN, &style_module_test_small_scale_cv_main);
	lv_obj_set_pos(ui->module_test_small_scale_cv, 24, 180);
	lv_obj_set_size(ui->module_test_small_scale_cv, 13, 13);
	ui->module_test_small_scale_cv_label = lv_label_create(ui->module_test_small_scale_cv, NULL);
	lv_label_set_text(ui->module_test_small_scale_cv_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_scale_cv_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_res_q_cv
	ui->module_test_small_res_q_cv = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_res_q_cv
	static lv_style_t style_module_test_small_res_q_cv_main;
	lv_style_reset(&style_module_test_small_res_q_cv_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_res_q_cv_main
	lv_style_set_radius(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_res_q_cv_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_res_q_cv, LV_BTN_PART_MAIN, &style_module_test_small_res_q_cv_main);
	lv_obj_set_pos(ui->module_test_small_res_q_cv, 63, 180);
	lv_obj_set_size(ui->module_test_small_res_q_cv, 13, 13);
	ui->module_test_small_res_q_cv_label = lv_label_create(ui->module_test_small_res_q_cv, NULL);
	lv_label_set_text(ui->module_test_small_res_q_cv_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_res_q_cv_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_rotate_scale
	ui->module_test_small_rotate_scale = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_rotate_scale
	static lv_style_t style_module_test_small_rotate_scale_main;
	lv_style_reset(&style_module_test_small_rotate_scale_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_rotate_scale_main
	lv_style_set_radius(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_rotate_scale_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_rotate_scale, LV_BTN_PART_MAIN, &style_module_test_small_rotate_scale_main);
	lv_obj_set_pos(ui->module_test_small_rotate_scale, 117, 181);
	lv_obj_set_size(ui->module_test_small_rotate_scale, 13, 13);
	ui->module_test_small_rotate_scale_label = lv_label_create(ui->module_test_small_rotate_scale, NULL);
	lv_label_set_text(ui->module_test_small_rotate_scale_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_rotate_scale_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_morph_cv
	ui->module_test_small_morph_cv = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_morph_cv
	static lv_style_t style_module_test_small_morph_cv_main;
	lv_style_reset(&style_module_test_small_morph_cv_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_morph_cv_main
	lv_style_set_radius(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_morph_cv_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_morph_cv, LV_BTN_PART_MAIN, &style_module_test_small_morph_cv_main);
	lv_obj_set_pos(ui->module_test_small_morph_cv, 170, 180);
	lv_obj_set_size(ui->module_test_small_morph_cv, 13, 13);
	ui->module_test_small_morph_cv_label = lv_label_create(ui->module_test_small_morph_cv, NULL);
	lv_label_set_text(ui->module_test_small_morph_cv_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_morph_cv_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_spread_cv
	ui->module_test_small_spread_cv = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_spread_cv
	static lv_style_t style_module_test_small_spread_cv_main;
	lv_style_reset(&style_module_test_small_spread_cv_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_spread_cv_main
	lv_style_set_radius(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_spread_cv_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_spread_cv, LV_BTN_PART_MAIN, &style_module_test_small_spread_cv_main);
	lv_obj_set_pos(ui->module_test_small_spread_cv, 209, 180);
	lv_obj_set_size(ui->module_test_small_spread_cv, 13, 13);
	ui->module_test_small_spread_cv_label = lv_label_create(ui->module_test_small_spread_cv, NULL);
	lv_label_set_text(ui->module_test_small_spread_cv_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_spread_cv_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_scale_r_switch
	ui->module_test_small_scale_r_switch = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_scale_r_switch
	static lv_style_t style_module_test_small_scale_r_switch_main;
	lv_style_reset(&style_module_test_small_scale_r_switch_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_scale_r_switch_main
	lv_style_set_radius(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_scale_r_switch_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_scale_r_switch, LV_BTN_PART_MAIN, &style_module_test_small_scale_r_switch_main);
	lv_obj_set_pos(ui->module_test_small_scale_r_switch, 9, 205);
	lv_obj_set_size(ui->module_test_small_scale_r_switch, 13, 13);
	ui->module_test_small_scale_r_switch_label = lv_label_create(ui->module_test_small_scale_r_switch, NULL);
	lv_label_set_text(ui->module_test_small_scale_r_switch_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_scale_r_switch_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_res_q
	ui->module_test_small_res_q = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_res_q
	static lv_style_t style_module_test_small_res_q_main;
	lv_style_reset(&style_module_test_small_res_q_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_res_q_main
	lv_style_set_radius(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_res_q_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_res_q, LV_BTN_PART_MAIN, &style_module_test_small_res_q_main);
	lv_obj_set_pos(ui->module_test_small_res_q, 46, 201);
	lv_obj_set_size(ui->module_test_small_res_q, 13, 13);
	ui->module_test_small_res_q_label = lv_label_create(ui->module_test_small_res_q, NULL);
	lv_label_set_text(ui->module_test_small_res_q_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_res_q_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_morph
	ui->module_test_small_morph = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_morph
	static lv_style_t style_module_test_small_morph_main;
	lv_style_reset(&style_module_test_small_morph_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_morph_main
	lv_style_set_radius(&style_module_test_small_morph_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_morph_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_morph_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_morph_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_morph_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_morph_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_morph_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_morph_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_morph_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_morph_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_morph, LV_BTN_PART_MAIN, &style_module_test_small_morph_main);
	lv_obj_set_pos(ui->module_test_small_morph, 187, 203);
	lv_obj_set_size(ui->module_test_small_morph, 13, 13);
	ui->module_test_small_morph_label = lv_label_create(ui->module_test_small_morph, NULL);
	lv_label_set_text(ui->module_test_small_morph_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_morph_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_spread
	ui->module_test_small_spread = lv_btn_create(ui->module_test_small, NULL);

	//Write style LV_BTN_PART_MAIN for module_test_small_spread
	static lv_style_t style_module_test_small_spread_main;
	lv_style_reset(&style_module_test_small_spread_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_spread_main
	lv_style_set_radius(&style_module_test_small_spread_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_module_test_small_spread_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_module_test_small_spread_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_module_test_small_spread_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_spread_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_module_test_small_spread_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_border_width(&style_module_test_small_spread_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_module_test_small_spread_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_module_test_small_spread_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_outline_opa(&style_module_test_small_spread_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_spread, LV_BTN_PART_MAIN, &style_module_test_small_spread_main);
	lv_obj_set_pos(ui->module_test_small_spread, 226, 201);
	lv_obj_set_size(ui->module_test_small_spread, 13, 13);
	ui->module_test_small_spread_label = lv_label_create(ui->module_test_small_spread, NULL);
	lv_label_set_text(ui->module_test_small_spread_label, "");
	lv_obj_set_style_local_text_color(ui->module_test_small_spread_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));

	//Write codes module_test_small_cont_1
	ui->module_test_small_cont_1 = lv_cont_create(ui->module_test_small, NULL);

	//Write style LV_CONT_PART_MAIN for module_test_small_cont_1
	static lv_style_t style_module_test_small_cont_1_main;
	lv_style_reset(&style_module_test_small_cont_1_main);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_cont_1_main
	lv_style_set_radius(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_module_test_small_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->module_test_small_cont_1, LV_CONT_PART_MAIN, &style_module_test_small_cont_1_main);
	lv_obj_set_pos(ui->module_test_small_cont_1, 246, 0);
	lv_obj_set_size(ui->module_test_small_cont_1, 74, 240);
	lv_obj_set_click(ui->module_test_small_cont_1, false);
	lv_cont_set_layout(ui->module_test_small_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->module_test_small_cont_1, LV_FIT_NONE);

	//Write codes module_test_small_param_list
	ui->module_test_small_param_list = lv_dropdown_create(ui->module_test_small, NULL);
	lv_dropdown_set_options(ui->module_test_small_param_list, "PARAM2\nPARAM3\nPARAM4\nPARAM5\nPARAM6\nPARAM7\nPARAM8");
	lv_dropdown_set_max_height(ui->module_test_small_param_list, 209);
	lv_dropdown_set_symbol(ui->module_test_small_param_list, NULL);

	//Write style LV_DROPDOWN_PART_SELECTED for module_test_small_param_list
	static lv_style_t style_module_test_small_param_list_selected;
	lv_style_reset(&style_module_test_small_param_list_selected);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_param_list_selected
	lv_style_set_radius(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_color(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
	lv_style_set_bg_grad_dir(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, 4);
	lv_style_set_text_color(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_module_test_small_param_list_selected, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_13);
	lv_obj_add_style(ui->module_test_small_param_list, LV_DROPDOWN_PART_SELECTED, &style_module_test_small_param_list_selected);

	//Write style LV_DROPDOWN_PART_LIST for module_test_small_param_list
	static lv_style_t style_module_test_small_param_list_list;
	lv_style_reset(&style_module_test_small_param_list_list);

	//Write style state: LV_STATE_DEFAULT for style_module_test_small_param_list_list
	lv_style_set_radius(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_module_test_small_param_list_list, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_12);
	lv_obj_add_style(ui->module_test_small_param_list, LV_DROPDOWN_PART_LIST, &style_module_test_small_param_list_list);
	lv_obj_set_pos(ui->module_test_small_param_list, 249, 3);
	lv_obj_set_width(ui->module_test_small_param_list, 68);
}