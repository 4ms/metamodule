#ifndef _FILEBROWSER_UI_H
#define _FILEBROWSER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "../../ui_scale.h"

// #include "ui_helpers.h"
// #include "ui_events.h"

// SCREEN: ui_FileBrowserPage
void ui_FileBrowserPage_screen_init(void);
extern lv_obj_t *ui_FileBrowserPage;
extern lv_obj_t *ui_FileBrowserCont;
extern lv_obj_t *ui_FileBrowserTitlePanel;
extern lv_obj_t *ui_FileBrowserTitle;
extern lv_obj_t *ui_FileBrowserSubtitle;
extern lv_obj_t *ui_FileBrowserPathCont;
extern lv_obj_t *ui_FileBrowserPathLabel;
extern lv_obj_t *ui_FileBrowserRoller;
extern lv_obj_t *ui_FileBrowserSpinner;
// CUSTOM VARIABLES
LV_FONT_DECLARE(ui_font_tiny);
LV_FONT_DECLARE(ui_font_small);
LV_FONT_DECLARE(ui_font_medium);
LV_FONT_DECLARE(ui_font_med_large);
LV_FONT_DECLARE(ui_font_medium_bold);
LV_FONT_DECLARE(ui_font_med_large_bold);
LV_FONT_DECLARE(ui_font_large);
LV_FONT_DECLARE(ui_font_huge);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
