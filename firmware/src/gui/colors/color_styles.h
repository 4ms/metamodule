#pragma once

#include "gui/colors/color_ids.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Atomic single-property color styles, one per (property, MetaColorId).
 *
 * Use these in place of lv_obj_set_style_<prop>_color() calls so that
 * a runtime scheme change automatically restyles every widget without
 * needing per-page reapply hooks.
 *
 * Example:
 *     lv_obj_add_style(label, metacolor_style_text(METACOLOR_ORANGE_HIGHLIGHT), 0);
 *
 * The returned pointer is owned by the color system; do not free or
 * lv_style_init() it.
 */
lv_style_t *metacolor_style_bg(MetaColorId id);
lv_style_t *metacolor_style_text(MetaColorId id);
lv_style_t *metacolor_style_border(MetaColorId id);
lv_style_t *metacolor_style_outline(MetaColorId id);
lv_style_t *metacolor_style_line(MetaColorId id);
lv_style_t *metacolor_style_arc(MetaColorId id);
lv_style_t *metacolor_style_shadow(MetaColorId id);
lv_style_t *metacolor_style_img_recolor(MetaColorId id);

#ifdef __cplusplus
}
#endif
