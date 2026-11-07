/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: --bpp 4 --size 16 --font /Users/gabrielroth/Dev/metamodule/.claude/worktrees/display-screensaver/firmware/lib/lvgl/lvgl/scripts/built_in_font/DejaVuSans.ttf -r 0x2605 --format lvgl --no-compress --no-prefilter -o ui_font_Star16.c --lv-include ../ui.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../ui.h"
#endif

#ifndef UI_FONT_STAR16
#define UI_FONT_STAR16 1
#endif

#if UI_FONT_STAR16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+2605 "★" */
    0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8,
    0xd0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xdf, 0x20,
    0x0, 0x0, 0x12, 0x22, 0x3f, 0xf8, 0x22, 0x22,
    0x3, 0xdf, 0xff, 0xff, 0xff, 0xff, 0x70, 0x0,
    0xaf, 0xff, 0xff, 0xfd, 0x30, 0x0, 0x0, 0x7f,
    0xff, 0xfc, 0x0, 0x0, 0x0, 0x7, 0xff, 0xff,
    0xd0, 0x0, 0x0, 0x0, 0xcf, 0xc9, 0xff, 0x20,
    0x0, 0x0, 0x1f, 0x80, 0x4, 0xe7, 0x0, 0x0,
    0x5, 0x40, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 9733, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_Star16 = {
#else
lv_font_t ui_font_Star16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_STAR16*/

