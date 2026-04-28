#pragma once

#include "gui/colors/color_styles.h"

namespace MetaModule::ColorStyles
{

// One-time setup at startup. Initializes every atomic style with the
// active scheme's colors. Call once after the LVGL display is created.
void init();

// Mutate every atomic style to reflect the active scheme and call
// lv_obj_report_style_change() to invalidate dependent widgets.
// Called from Colors::set_scheme().
void reapply_scheme();

} // namespace MetaModule::ColorStyles
