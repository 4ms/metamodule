#pragma once

// Force-included when compiling the SquareLine Studio exports (slsexport/meta5, slsexport/filebrowser)
// for builds with a GUI scale other than 100% (MP2: see gui/ui_scale.h).
//
// The exported screens and components were designed for a 320x240 screen: they name the MP1
// fonts directly, and set every size, position, padding, radius and border in MP1 pixels.
// They are re-exported from time to time, so rather than editing them, this header:
//   - redirects the MP1 font names to the scaled font with the same role, and
//   - wraps the LVGL setters they use, so pixel values are multiplied by the GUI scale
//     (lv_pct(), LV_SIZE_CONTENT and LV_RADIUS_CIRCLE are left alone), and
//   - resizes the exported (1x) icons by the GUI scale.
//
// Structural sizes (things that should fill the screen, not just get bigger) are then fixed
// up at runtime in sls_layout_fixups.hh

#include "../fonts/sls_font_remap.h"

#include "lvgl.h"

#include "../ui_scale.h"
#include "sls_hidpi_img.h"

// Size and position
#define lv_obj_set_width(obj, w) (lv_obj_set_width)(obj, ui_px(w))
#define lv_obj_set_height(obj, h) (lv_obj_set_height)(obj, ui_px(h))
#define lv_obj_set_size(obj, w, h) (lv_obj_set_size)(obj, ui_px(w), ui_px(h))
#define lv_obj_set_x(obj, x) (lv_obj_set_x)(obj, ui_px(x))
#define lv_obj_set_y(obj, y) (lv_obj_set_y)(obj, ui_px(y))
#define lv_obj_set_pos(obj, x, y) (lv_obj_set_pos)(obj, ui_px(x), ui_px(y))
#define lv_obj_align(obj, align, x, y) (lv_obj_align)(obj, align, ui_px(x), ui_px(y))
#define lv_obj_set_style_width(obj, v, sel) (lv_obj_set_style_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_height(obj, v, sel) (lv_obj_set_style_height)(obj, ui_px(v), sel)
#define lv_obj_set_style_min_width(obj, v, sel) (lv_obj_set_style_min_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_max_width(obj, v, sel) (lv_obj_set_style_max_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_min_height(obj, v, sel) (lv_obj_set_style_min_height)(obj, ui_px(v), sel)
#define lv_obj_set_style_max_height(obj, v, sel) (lv_obj_set_style_max_height)(obj, ui_px(v), sel)
#define lv_obj_set_style_translate_x(obj, v, sel) (lv_obj_set_style_translate_x)(obj, ui_px(v), sel)
#define lv_obj_set_style_translate_y(obj, v, sel) (lv_obj_set_style_translate_y)(obj, ui_px(v), sel)
#define lv_obj_set_style_transform_width(obj, v, sel) (lv_obj_set_style_transform_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_transform_height(obj, v, sel) (lv_obj_set_style_transform_height)(obj, ui_px(v), sel)
#define lv_obj_set_style_transform_pivot_x(obj, v, sel) (lv_obj_set_style_transform_pivot_x)(obj, ui_px(v), sel)
#define lv_obj_set_style_transform_pivot_y(obj, v, sel) (lv_obj_set_style_transform_pivot_y)(obj, ui_px(v), sel)

// Padding
#define lv_obj_set_style_pad_top(obj, v, sel) (lv_obj_set_style_pad_top)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_bottom(obj, v, sel) (lv_obj_set_style_pad_bottom)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_left(obj, v, sel) (lv_obj_set_style_pad_left)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_right(obj, v, sel) (lv_obj_set_style_pad_right)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_row(obj, v, sel) (lv_obj_set_style_pad_row)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_column(obj, v, sel) (lv_obj_set_style_pad_column)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_all(obj, v, sel) (lv_obj_set_style_pad_all)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_hor(obj, v, sel) (lv_obj_set_style_pad_hor)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_ver(obj, v, sel) (lv_obj_set_style_pad_ver)(obj, ui_px(v), sel)
#define lv_obj_set_style_pad_gap(obj, v, sel) (lv_obj_set_style_pad_gap)(obj, ui_px(v), sel)

// Decoration
#define lv_obj_set_style_radius(obj, v, sel) (lv_obj_set_style_radius)(obj, ui_px(v), sel)
#define lv_obj_set_style_border_width(obj, v, sel) (lv_obj_set_style_border_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_outline_width(obj, v, sel) (lv_obj_set_style_outline_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_outline_pad(obj, v, sel) (lv_obj_set_style_outline_pad)(obj, ui_px(v), sel)
#define lv_obj_set_style_shadow_width(obj, v, sel) (lv_obj_set_style_shadow_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_shadow_spread(obj, v, sel) (lv_obj_set_style_shadow_spread)(obj, ui_px(v), sel)
#define lv_obj_set_style_shadow_ofs_x(obj, v, sel) (lv_obj_set_style_shadow_ofs_x)(obj, ui_px(v), sel)
#define lv_obj_set_style_shadow_ofs_y(obj, v, sel) (lv_obj_set_style_shadow_ofs_y)(obj, ui_px(v), sel)
#define lv_obj_set_style_arc_width(obj, v, sel) (lv_obj_set_style_arc_width)(obj, ui_px(v), sel)
#define lv_obj_set_style_line_width(obj, v, sel) (lv_obj_set_style_line_width)(obj, ui_px(v), sel)

// Text
#define lv_obj_set_style_text_line_space(obj, v, sel) (lv_obj_set_style_text_line_space)(obj, ui_px(v), sel)
#define lv_obj_set_style_text_letter_space(obj, v, sel) (lv_obj_set_style_text_letter_space)(obj, ui_px(v), sel)

// Images
#define lv_img_set_src(obj, src) (lv_img_set_src)(obj, ui_scaled_img(src))
#define lv_imgbtn_set_src(obj, state, left, mid, right)                                                                \
	(lv_imgbtn_set_src)(obj, state, ui_scaled_img(left), ui_scaled_img(mid), ui_scaled_img(right))
#define lv_obj_set_style_bg_img_src(obj, v, sel) (lv_obj_set_style_bg_img_src)(obj, ui_scaled_img(v), sel)

// Widgets with a size parameter
#define lv_tabview_create(parent, tab_pos, tab_size) (lv_tabview_create)(parent, tab_pos, ui_px(tab_size))
