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
//     lv_obj_add_style(label, scheme_text(METACOLOR_ORANGE_HIGHLIGHT), 0);

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

inline lv_style_t *mc_bg(MetaColorId id) { return scheme_bg(id); }
inline lv_style_t *mc_bg_grad(MetaColorId id) { return scheme_bg_grad(id); }
inline lv_style_t *mc_bg_img_recolor(MetaColorId id) { return scheme_bg_img_recolor(id); }
inline lv_style_t *mc_text(MetaColorId id) { return scheme_text(id); }
inline lv_style_t *mc_border(MetaColorId id) { return scheme_border(id); }
inline lv_style_t *mc_outline(MetaColorId id) { return scheme_outline(id); }
inline lv_style_t *mc_line(MetaColorId id) { return scheme_line(id); }
inline lv_style_t *mc_arc(MetaColorId id) { return scheme_arc(id); }
inline lv_style_t *mc_shadow(MetaColorId id) { return scheme_shadow(id); }
inline lv_style_t *mc_img_recolor(MetaColorId id) { return scheme_img_recolor(id); }

#ifdef __cplusplus
}
#endif
