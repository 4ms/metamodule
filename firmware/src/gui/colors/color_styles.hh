#pragma once

#include "gui/colors/color_styles.h"

namespace MetaModule
{

// Terse C++ accessors for atomic single-property color styles.
// Use in lv_obj_add_style() calls in place of lv_obj_set_style_*_color().
//
// Example:
//   lv_obj_add_style(label, mc_text(METACOLOR_ORANGE_HIGHLIGHT), 0);
//   lv_obj_add_style(btn, mc_bg(METACOLOR_GREY_DARK), LV_STATE_PRESSED);
inline lv_style_t *mc_bg(MetaColorId id) {
	return metacolor_style_bg(id);
}
inline lv_style_t *mc_text(MetaColorId id) {
	return metacolor_style_text(id);
}
inline lv_style_t *mc_border(MetaColorId id) {
	return metacolor_style_border(id);
}
inline lv_style_t *mc_outline(MetaColorId id) {
	return metacolor_style_outline(id);
}
inline lv_style_t *mc_line(MetaColorId id) {
	return metacolor_style_line(id);
}
inline lv_style_t *mc_arc(MetaColorId id) {
	return metacolor_style_arc(id);
}
inline lv_style_t *mc_shadow(MetaColorId id) {
	return metacolor_style_shadow(id);
}
inline lv_style_t *mc_img_recolor(MetaColorId id) {
	return metacolor_style_img_recolor(id);
}

namespace ColorStyles
{

// One-time setup at startup. Initializes every atomic style with the
// active scheme's colors. Call once after the LVGL display is created.
void init();

// Mutate every atomic style to reflect the active scheme and call
// lv_obj_report_style_change() to invalidate dependent widgets.
// Called from Scheme::set().
void reapply_scheme();

} // namespace ColorStyles
} // namespace MetaModule
