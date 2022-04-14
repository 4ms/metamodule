// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "custom.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui) {
	static lv_style_t style_bg;
	lv_style_reset(&style_bg);
	lv_style_set_bg_color(&style_bg, lv_color_hex(0x000000));
	lv_obj_add_style(ui->Main_Example, &style_bg, LV_PART_MAIN);
}
