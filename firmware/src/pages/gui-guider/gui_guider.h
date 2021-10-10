/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
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
	lv_obj_t *Main_Example;
	lv_obj_t *Main_Example_btn_1;
	lv_obj_t *Main_Example_btn_1_label;
	lv_obj_t *Main_Example_btn_2;
	lv_obj_t *Main_Example_btn_2_label;
	lv_obj_t *Main_Example_btn_3;
	lv_obj_t *Main_Example_btn_3_label;
	lv_obj_t *Main_Example_btn_4;
	lv_obj_t *Main_Example_btn_4_label;
	lv_obj_t *Main_Example_btn_5;
	lv_obj_t *Main_Example_btn_5_label;
	lv_obj_t *Main_Example_btn_6;
	lv_obj_t *Main_Example_btn_6_label;
	lv_obj_t *Main_Example_arc_1;
	lv_obj_t *Main_Example_arc_2;
	lv_obj_t *Main_Example_arc_3;
	lv_obj_t *Main_Example_arc_4;
	lv_obj_t *Main_Example_arc_5;
	lv_obj_t *Main_Example_arc_6;
	lv_obj_t *Main_Example_label_1;
	lv_obj_t *Main_Example_label_2;
	lv_obj_t *Main_Example_label_3;
	lv_obj_t *symbol_sketches;
	lv_obj_t *symbol_sketches_sw_1;
	lv_obj_t *symbol_sketches_arc_1;
	lv_obj_t *symbol_sketches_slider_1;
	lv_obj_t *symbol_sketches_bar_1;
	lv_obj_t *symbol_sketches_bar_2;
	lv_obj_t *symbol_sketches_slider_2;
	lv_obj_t *symbol_sketches_slider_3;
	lv_obj_t *symbol_sketches_slider_4;
	lv_obj_t *symbol_sketches_slider_5;
	lv_obj_t *symbol_sketches_lmeter_2;
	lv_obj_t *symbol_sketches_slider_6;
	lv_obj_t *symbol_sketches_slider_7;
	lv_obj_t *Knob_view;
	lv_obj_t *Knob_view_arc_1;
	lv_obj_t *Knob_view_arc_2;
	lv_obj_t *Knob_view_arc_3;
	lv_obj_t *Knob_view_arc_4;
	lv_obj_t *Knob_view_arc_5;
	lv_obj_t *Knob_view_arc_6;
	lv_obj_t *Knob_view_label_1;
	lv_obj_t *Knob_view_label_2;
	lv_obj_t *Knob_view_arc_7;
	lv_obj_t *Knob_view_arc_8;
	lv_obj_t *Knob_view_arc_9;
	lv_obj_t *Knob_view_arc_10;
	lv_obj_t *Knob_view_arc_11;
	lv_obj_t *Knob_view_arc_12;
	lv_obj_t *Knob_view_label_3;
	lv_obj_t *Knob_view_label_4;
	lv_obj_t *Knob_view_label_5;
	lv_obj_t *Knob_view_label_6;
	lv_obj_t *Knob_view_label_7;
	lv_obj_t *Knob_view2;
	lv_obj_t *Knob_view2_arc_1;
	lv_obj_t *Knob_view2_arc_2;
	lv_obj_t *Knob_view2_arc_3;
	lv_obj_t *Knob_view2_arc_4;
	lv_obj_t *Knob_view2_arc_5;
	lv_obj_t *Knob_view2_arc_6;
	lv_obj_t *Knob_view2_label_1;
	lv_obj_t *Knob_view2_label_2;
	lv_obj_t *Knob_view2_arc_7;
	lv_obj_t *Knob_view2_arc_8;
	lv_obj_t *Knob_view2_arc_9;
	lv_obj_t *Knob_view2_arc_10;
	lv_obj_t *Knob_view2_arc_11;
	lv_obj_t *Knob_view2_arc_12;
	lv_obj_t *Knob_view2_label_3;
	lv_obj_t *Knob_view2_label_4;
	lv_obj_t *Knob_view2_label_5;
	lv_obj_t *Knob_view2_label_6;
	lv_obj_t *Knob_view2_label_7;
	lv_obj_t *Knob_view3;
	lv_obj_t *Knob_view3_arc_1;
	lv_obj_t *Knob_view3_arc_2;
	lv_obj_t *Knob_view3_arc_3;
	lv_obj_t *Knob_view3_arc_4;
	lv_obj_t *Knob_view3_arc_5;
	lv_obj_t *Knob_view3_arc_6;
	lv_obj_t *Knob_view3_label_1;
	lv_obj_t *Knob_view3_label_2;
	lv_obj_t *Knob_view3_arc_7;
	lv_obj_t *Knob_view3_arc_8;
	lv_obj_t *Knob_view3_arc_9;
	lv_obj_t *Knob_view3_arc_10;
	lv_obj_t *Knob_view3_arc_11;
	lv_obj_t *Knob_view3_arc_12;
	lv_obj_t *Knob_view3_label_3;
	lv_obj_t *Knob_view3_label_4;
	lv_obj_t *Knob_view3_label_5;
	lv_obj_t *Knob_view3_label_6;
	lv_obj_t *Knob_view3_label_7;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_Main_Example(lv_ui *ui);
void setup_scr_symbol_sketches(lv_ui *ui);
void setup_scr_Knob_view(lv_ui *ui);
void setup_scr_Knob_view2(lv_ui *ui);
void setup_scr_Knob_view3(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif