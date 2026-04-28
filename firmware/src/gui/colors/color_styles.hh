#pragma once

#include "gui/colors/color_styles.h"

namespace MetaModule
{

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
