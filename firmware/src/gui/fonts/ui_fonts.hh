#pragma once
#include "lvgl.h"

// Use these in GUI code instead of a particular font, so each platform can pick sizes
// that are legible on its screen. See ui_font_names.h for which font each one is.

extern "C" {
LV_FONT_DECLARE(ui_font_tiny);
LV_FONT_DECLARE(ui_font_small);
LV_FONT_DECLARE(ui_font_medium);
LV_FONT_DECLARE(ui_font_medium_bold);
LV_FONT_DECLARE(ui_font_med_large);
LV_FONT_DECLARE(ui_font_med_large_bold);
LV_FONT_DECLARE(ui_font_large);
LV_FONT_DECLARE(ui_font_huge);
LV_FONT_DECLARE(ui_font_icons);
}

namespace MetaModule
{
inline constexpr lv_font_t const *font_tiny = &ui_font_tiny;
inline constexpr lv_font_t const *font_small = &ui_font_small;
inline constexpr lv_font_t const *font_medium = &ui_font_medium;
inline constexpr lv_font_t const *font_medium_bold = &ui_font_medium_bold;
inline constexpr lv_font_t const *font_med_large = &ui_font_med_large;
inline constexpr lv_font_t const *font_med_large_bold = &ui_font_med_large_bold;
inline constexpr lv_font_t const *font_large = &ui_font_large;
inline constexpr lv_font_t const *font_huge = &ui_font_huge;
inline constexpr lv_font_t const *font_icons = &ui_font_icons;

// For LV_SYMBOL_* that are not in the above
#if defined(METAMODULE_UI_SCALED_FONTS)
inline constexpr lv_font_t const *font_symbols = &lv_font_montserrat_28;
#else
inline constexpr lv_font_t const *font_symbols = &lv_font_montserrat_14;
#endif
} // namespace MetaModule
