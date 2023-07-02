// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: MM

#ifndef _MM_UI_H
#define _MM_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t *ui_PatchSelector;
extern lv_obj_t *ui_Title;
extern lv_obj_t *ui_mediapanel;
extern lv_obj_t *ui_USBbut;
extern lv_obj_t *ui_USBlabel;
extern lv_obj_t *ui_SDbut;
extern lv_obj_t *ui_SDlabel;
extern lv_obj_t *ui_Flashbut;
extern lv_obj_t *ui_Flashlabel;
extern lv_obj_t *ui_patchlist;
extern lv_obj_t *ui_waitspinner;

LV_FONT_DECLARE(ui_font_MuseoSansRounded70014);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
