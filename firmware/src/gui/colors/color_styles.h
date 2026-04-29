#pragma once

#include "gui/colors/color_ids.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Atomic single-property color styles, one per (property, MetaColorId).

// Use these in place of lv_obj_set_style_<prop>_color() calls so that
// a runtime scheme change automatically restyles every widget without
// needing per-page reapply hooks.

// Example:
//     lv_obj_add_style(label, scheme_text(METACOLOR_PRIMARY_HIGHLIGHT), 0);

// The returned pointer is owned by the color system; do not free or
// lv_style_init() it.

lv_style_t *scheme_bg(MetaColorId id);
lv_style_t *scheme_bg_grad(MetaColorId id);
lv_style_t *scheme_bg_img_recolor(MetaColorId id);
lv_style_t *scheme_text(MetaColorId id);
lv_style_t *scheme_border(MetaColorId id);
lv_style_t *scheme_outline(MetaColorId id);
lv_style_t *scheme_line(MetaColorId id);
lv_style_t *scheme_arc(MetaColorId id);
lv_style_t *scheme_shadow(MetaColorId id);
lv_style_t *scheme_img_recolor(MetaColorId id);

#ifdef __cplusplus
}
#endif
