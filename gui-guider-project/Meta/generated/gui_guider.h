/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *patch_selection;
	lv_obj_t *patch_selection_back;
	lv_obj_t *patch_selection_back_label;
	lv_obj_t *patch_selection_next;
	lv_obj_t *patch_selection_next_label;
	lv_obj_t *patch_selection_play;
	lv_obj_t *patch_selection_play_label;
	lv_obj_t *patch_selection_description;
	lv_obj_t *patch_selection_modules;
	lv_obj_t *patch_selection_selection;
	lv_obj_t *knob_button_view;
	lv_obj_t *knob_button_view_arc_1;
	lv_obj_t *knob_button_view_arc_2;
	lv_obj_t *knob_button_view_arc_3;
	lv_obj_t *knob_button_view_arc_4;
	lv_obj_t *knob_button_view_arc_5;
	lv_obj_t *knob_button_view_arc_6;
	lv_obj_t *knob_button_view_arc_7;
	lv_obj_t *knob_button_view_arc_8;
	lv_obj_t *knob_button_view_arc_9;
	lv_obj_t *knob_button_view_arc_10;
	lv_obj_t *knob_button_view_arc_12;
	lv_obj_t *knob_button_view_arc_13;
	lv_obj_t *knob_button_view_btn_1;
	lv_obj_t *knob_button_view_btn_1_label;
	lv_obj_t *knob_button_view_btn_2;
	lv_obj_t *knob_button_view_btn_2_label;
	lv_obj_t *knob_button_view_btn_3;
	lv_obj_t *knob_button_view_btn_3_label;
	lv_obj_t *knob_button_view_btn_4;
	lv_obj_t *knob_button_view_btn_4_label;
	lv_obj_t *knob_button_view_btn_5;
	lv_obj_t *knob_button_view_btn_5_label;
	lv_obj_t *knob_button_view_btn_6;
	lv_obj_t *knob_button_view_btn_6_label;
	lv_obj_t *knob_view;
	lv_obj_t *knob_view_x_knob;
	lv_obj_t *knob_view_x_outline;
	lv_obj_t *knob_view_x_label;
	lv_obj_t *knob_view_a_knob;
	lv_obj_t *knob_view_a_label;
	lv_obj_t *knob_view_b_knob;
	lv_obj_t *knob_view_b_label;
	lv_obj_t *knob_view_q_knob;
	lv_obj_t *knob_view_q_outline;
	lv_obj_t *knob_view_q_label;
	lv_obj_t *knob_view_y_knob;
	lv_obj_t *knob_view_y_outline;
	lv_obj_t *knob_view_y_label;
	lv_obj_t *knob_view_c_knob;
	lv_obj_t *knob_view_c_label;
	lv_obj_t *knob_view_d_knob;
	lv_obj_t *knob_view_d_label;
	lv_obj_t *knob_view_l_knob;
	lv_obj_t *knob_view_l_outline;
	lv_obj_t *knob_view_l_label;
	lv_obj_t *knob_view_z_knob;
	lv_obj_t *knob_view_z_outline;
	lv_obj_t *knob_view_z_label;
	lv_obj_t *knob_view_e_knob;
	lv_obj_t *knob_view_e_label;
	lv_obj_t *knob_view_f_knob;
	lv_obj_t *knob_view_f_label;
	lv_obj_t *knob_view_r_knob;
	lv_obj_t *knob_view_r_outline;
	lv_obj_t *knob_view_r_label;
	lv_obj_t *knob_view2;
	lv_obj_t *knob_view2_x_knob;
	lv_obj_t *knob_view2_x_outline;
	lv_obj_t *knob_view2_x_label;
	lv_obj_t *knob_view2_a_knob;
	lv_obj_t *knob_view2_a_outline;
	lv_obj_t *knob_view2_a_label;
	lv_obj_t *knob_view2_b_knob;
	lv_obj_t *knob_view2_b_outline;
	lv_obj_t *knob_view2_b_label;
	lv_obj_t *knob_view2_q_knob;
	lv_obj_t *knob_view2_q_outline;
	lv_obj_t *knob_view2_q_label;
	lv_obj_t *knob_view2_y_knob;
	lv_obj_t *knob_view2_y_outline;
	lv_obj_t *knob_view2_y_label;
	lv_obj_t *knob_view2_c_knob;
	lv_obj_t *knob_view2_c_outline;
	lv_obj_t *knob_view2_c_label;
	lv_obj_t *knob_view2_d_knob;
	lv_obj_t *knob_view2_d_outline;
	lv_obj_t *knob_view2_d_label;
	lv_obj_t *knob_view2_l_knob;
	lv_obj_t *knob_view2_l_outline;
	lv_obj_t *knob_view2_l_label;
	lv_obj_t *knob_view2_z_knob;
	lv_obj_t *knob_view2_z_outline;
	lv_obj_t *knob_view2_z_label;
	lv_obj_t *knob_view2_e_knob;
	lv_obj_t *knob_view2_e_outline;
	lv_obj_t *knob_view2_e_label;
	lv_obj_t *knob_view2_f_knob;
	lv_obj_t *knob_view2_f_outline;
	lv_obj_t *knob_view2_f_label;
	lv_obj_t *knob_view2_r_knob;
	lv_obj_t *knob_view2_r_outline;
	lv_obj_t *knob_view2_r_label;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_patch_selection(lv_ui *ui);
void setup_scr_knob_button_view(lv_ui *ui);
void setup_scr_knob_view(lv_ui *ui);
void setup_scr_knob_view2(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif