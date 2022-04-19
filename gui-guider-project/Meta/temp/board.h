#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>
#include "lvgl_support.h"

#define LV_HOR_RES_MAX (320)
#define LV_VER_RES_MAX (240)
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0
#define LV_COLOR_SCREEN_TRANSP 0
#define LV_COLOR_TRANSP LV_COLOR_LIME
#define LV_ANTIALIAS 1
#define LV_DISP_DEF_REFR_PERIOD 30
#define LV_DPI 130
#define LV_DISP_SMALL_LIMIT 30
#define LV_DISP_MEDIUM_LIMIT 50
#define LV_DISP_LARGE_LIMIT 70
#define LV_MEM_CUSTOM 0

#if LV_MEM_CUSTOM == 0
/* Size of the memory used by `lv_mem_alloc` in bytes (>= 2kB)*/
#define LV_MEM_SIZE (320U * 1024U)
#define LV_MEM_ATTR
#define LV_MEM_ADR 0
#define LV_MEM_AUTO_DEFRAG 1
#else /* LV_MEM_CUSTOM */
#define LV_MEM_CUSTOM_INCLUDE <stdlib.h>
#define LV_MEM_CUSTOM_ALLOC malloc
#define LV_MEM_CUSTOM_FREE free
#endif    /* LV_MEM_CUSTOM */

#define LV_MEMCPY_MEMSET_STD 0
#define LV_ENABLE_GC 0

#if LV_ENABLE_GC != 0
#define LV_GC_INCLUDE "gc.h"
#define LV_MEM_CUSTOM_REALLOC realloc
#define LV_MEM_CUSTOM_GET_SIZE mem_get_size
#endif /* LV_ENABLE_GC */

#define LV_INDEV_DEF_READ_PERIOD 30
#define LV_INDEV_DEF_DRAG_LIMIT 10
#define LV_INDEV_DEF_DRAG_THROW 10
#define LV_INDEV_DEF_LONG_PRESS_TIME 400
#define LV_INDEV_DEF_LONG_PRESS_REP_TIME 100
#define LV_INDEV_DEF_GESTURE_LIMIT 50
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3
#define LV_USE_ANIMATION 1

#if LV_USE_ANIMATION
typedef void * lv_anim_user_data_t;
#endif /* LV_USE_ANIMATION */

#define LV_USE_SHADOW 1

#if LV_USE_SHADOW
#define LV_SHADOW_CACHE_SIZE 0
#endif /* LV_USE_SHADOW */

#define LV_USE_OUTLINE 1
#define LV_USE_PATTERN 1
#define LV_USE_VALUE_STR 1
#define LV_USE_BLEND_MODES 1
#define LV_USE_OPA_SCALE 1
#define LV_USE_IMG_TRANSFORM 1
#define LV_USE_GROUP 1

#if LV_USE_GROUP
typedef void * lv_group_user_data_t;
#endif /* LV_USE_GROUP */

#define LV_USE_GPU 1
#define LV_USE_FILESYSTEM 1

#if LV_USE_FILESYSTEM
typedef void * lv_fs_drv_user_data_t;
#endif /* LV_USE_FILESYSTEM */

#define LV_USE_USER_DATA 0
#define LV_USE_PERF_MONITOR 0
#define LV_USE_API_EXTENSION_V6 1
#define LV_USE_API_EXTENSION_V7 1
#define LV_IMG_CF_INDEXED 1
#define LV_IMG_CF_ALPHA 1
#define LV_IMG_CACHE_DEF_SIZE 1
typedef void * lv_img_decoder_user_data_t;
#define LV_BIG_ENDIAN_SYSTEM 0
#define LV_ATTRIBUTE_TICK_INC
#define LV_ATTRIBUTE_TASK_HANDLER
#define LV_ATTRIBUTE_FLUSH_READY
#define LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_FAST_MEM
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning
#define LV_ATTRIBUTE_DMA
#define LV_TICK_CUSTOM 0

#if LV_TICK_CUSTOM == 1
#define LV_TICK_CUSTOM_INCLUDE Arduino.h
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif /* LV_TICK_CUSTOM */

typedef void * lv_disp_drv_user_data_t;
typedef void * lv_indev_drv_user_data_t;
#define LV_USE_LOG 0

#if LV_USE_LOG
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN
#define LV_LOG_PRINTF 0
#endif /* LV_USE_LOG */

#define LV_USE_DEBUG 0

#if LV_USE_DEBUG
#define LV_USE_ASSERT_NULL 1
#define LV_USE_ASSERT_MEM 1
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_STR 0
#define LV_USE_ASSERT_OBJ 0
#define LV_USE_ASSERT_STYLE 0
#endif /* LV_USE_DEBUG */

#define LV_FONT_MONTSERRAT_8 0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0
#define LV_FONT_MONTSERRAT_12_SUBPX 0
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0
#define LV_FONT_SIMSUN_16_CJK 0
#define LV_FONT_UNSCII_8 0
#define LV_FONT_CUSTOM_DECLARE
#define LV_FONT_FMT_TXT_LARGE 0
#define LV_USE_FONT_COMPRESSED 1
#define LV_USE_FONT_SUBPX 0

#if LV_USE_FONT_SUBPX
#define LV_FONT_SUBPX_BGR 0
#endif /* LV_USE_FONT_SUBPX */

typedef void * lv_font_user_data_t;
#define LV_USE_THEME_EMPTY 1
#define LV_USE_THEME_TEMPLATE 1
#define LV_USE_THEME_MATERIAL 1
#define LV_USE_THEME_MONO 1
#define LV_THEME_DEFAULT_INCLUDE <stdint.h>
#define LV_THEME_DEFAULT_INIT lv_theme_material_init
#define LV_THEME_DEFAULT_COLOR_PRIMARY lv_color_hex(0x01a2b1)
#define LV_THEME_DEFAULT_COLOR_SECONDARY lv_color_hex(0x44d1b6)
#define LV_THEME_DEFAULT_FLAG LV_THEME_MATERIAL_FLAG_LIGHT
#define LV_THEME_DEFAULT_FONT_SMALL &lv_font_montserrat_12
#define LV_THEME_DEFAULT_FONT_NORMAL &lv_font_montserrat_16
#define LV_THEME_DEFAULT_FONT_SUBTITLE &lv_font_montserrat_20
#define LV_THEME_DEFAULT_FONT_TITLE &lv_font_montserrat_24
#define LV_TXT_ENC LV_TXT_ENC_UTF8
#define LV_TXT_BREAK_CHARS " ,.;:-_"
#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3
#define LV_TXT_COLOR_CMD "#"
#define LV_USE_BIDI 0

#if LV_USE_BIDI
#define LV_BIDI_BASE_DIR_DEF LV_BIDI_DIR_AUTO
#endif /* LV_USE_BIDI */

#define LV_USE_ARABIC_PERSIAN_CHARS 0
#define LV_SPRINTF_CUSTOM 0

#if LV_SPRINTF_CUSTOM
#define LV_SPRINTF_INCLUDE <stdio.h>
#define lv_snprintf snprintf
#define lv_vsnprintf vsnprintf
#else /* !LV_SPRINTF_CUSTOM */
#define LV_SPRINTF_DISABLE_FLOAT 1
#endif /* LV_SPRINTF_CUSTOM */


#if LV_USE_USER_DATA
#define void * lv_obj_user_data_t
#if LV_USE_USER_DATA_FREE
#define LV_USER_DATA_FREE_INCLUDE "something.h"
#define LV_USER_DATA_FREE (user_data_free)
#endif
#endif

#define LV_USE_OBJ_REALIGN 1
#define LV_USE_EXT_CLICK_AREA LV_EXT_CLICK_AREA_TINY
#define LV_USE_ARC 1
#define LV_USE_BAR 1
#define LV_USE_BTN 1
#define LV_USE_BTNMATRIX 1
#define LV_USE_CALENDAR 1

#if LV_USE_CALENDAR
#define LV_CALENDAR_WEEK_STARTS_MONDAY 0
#endif /* LV_USE_CALENDAR */

#define LV_USE_CANVAS 1
#define LV_USE_CHECKBOX 1
#define LV_USE_CHART 1

#if LV_USE_CHART
#define LV_CHART_AXIS_TICK_LABEL_MAX_LEN 256
#endif /* LV_USE_CHART */

#define LV_USE_CONT 1
#define LV_USE_CPICKER 1
#define LV_USE_DROPDOWN 1

#if LV_USE_DROPDOWN
#define LV_DROPDOWN_DEF_ANIM_TIME 200
#endif /* LV_USE_DROPDOWN */

#define LV_USE_GAUGE 1
#define LV_USE_IMG 1
#define LV_USE_IMGBTN 1

#if LV_USE_IMGBTN
#define LV_IMGBTN_TILED 0
#endif /* LV_USE_IMGBTN */

#define LV_USE_KEYBOARD 1
#define LV_USE_LABEL 1

#if LV_USE_LABEL != 0
#define LV_LABEL_WAIT_CHAR_COUNT 3
#define LV_LABEL_TEXT_SEL 0
#define LV_LABEL_LONG_TXT_HINT 0
#endif /* LV_USE_LABEL */

#define LV_USE_LED 1

#if LV_USE_LED
#define LV_LED_BRIGHT_MIN 120
#define LV_LED_BRIGHT_MAX 255
#endif /* LV_USE_LED */

#define LV_USE_LINE 1
#define LV_USE_LIST 1

#if LV_USE_LIST != 0
#define LV_LIST_DEF_ANIM_TIME 100
#endif /* LV_USE_LIST */

#define LV_USE_LINEMETER 1

#if LV_USE_LINEMETER
#define LV_LINEMETER_PRECISE 1
#endif /* LV_USE_LINEMETER */

#define LV_USE_OBJMASK 1
#define LV_USE_MSGBOX 1
#define LV_USE_PAGE 1

#if LV_USE_PAGE != 0
#define LV_PAGE_DEF_ANIM_TIME 400
#endif /* LV_USE_PAGE */

#define LV_USE_SPINNER 1

#if LV_USE_SPINNER != 0
#define LV_SPINNER_DEF_ARC_LENGTH 60
#define LV_SPINNER_DEF_SPIN_TIME 1000
#define LV_SPINNER_DEF_ANIM LV_SPINNER_TYPE_SPINNING_ARC
#endif /* LV_USE_SPINNER */

#define LV_USE_ROLLER 1

#if LV_USE_ROLLER != 0
#define LV_ROLLER_DEF_ANIM_TIME 200
#define LV_ROLLER_INF_PAGES 7
#endif /* LV_USE_ROLLER */

#define LV_USE_SLIDER 1
#define LV_USE_SPINBOX 1
#define LV_USE_SWITCH 1
#define LV_USE_TEXTAREA 1

#if LV_USE_TEXTAREA != 0
#define LV_TEXTAREA_DEF_CURSOR_BLINK_TIME 400
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500
#endif /* LV_USE_TEXTAREA */

#define LV_USE_TABLE 1

#if LV_USE_TABLE
#define LV_TABLE_COL_MAX 12
#define LV_TABLE_CELL_STYLE_CNT 4
#endif /* LV_USE_TABLE */

#define LV_USE_TABVIEW 1

#if LV_USE_TABVIEW != 0
#define LV_TABVIEW_DEF_ANIM_TIME 300
#endif /* LV_USE_TABVIEW */

#define LV_USE_TILEVIEW 1

#if LV_USE_TILEVIEW
#define LV_TILEVIEW_DEF_ANIM_TIME 300
#endif /* LV_USE_TILEVIEW */

#define LV_USE_WIN 1

#if  defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)    /* Disable warnings for Visual Studio*/
#define _CRT_SECURE_NO_WARNINGS
#endif

#define LV_USE_ANIM_IMG 1
#define LV_USE_GUIDER_SIMULATOR 0

#endif