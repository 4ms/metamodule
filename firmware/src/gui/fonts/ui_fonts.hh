#pragma once
#include "lvgl.h"

// Use these in GUI code instead of a particular font (ui_font_MuseoSansRounded70016, ...),
// so each platform can pick sizes that are legible on its screen:
//
//   MP1 (320x240):    the fonts exported in slsexport/meta5/fonts:
//   MP2 (1280x720):   the same typefaces and glyph sets, scaled up for the denser screen
//                     (fonts/scaled, made by fonts/generate_scaled_fonts.py)
//
//   role             MP1 font                 weight   MP1 px
//   tiny             MuseoSansRounded50010    500      10
//   small            MuseoSansRounded50012    500      12
//   medium           MuseoSansRounded50014    500      14
//   medium_bold      MuseoSansRounded70014    700      14   <- the default font (LV_FONT_DEFAULT)
//   med_large        MuseoSansRounded50016    500      16
//   med_large_bold   MuseoSansRounded70016    700      16
//   large            MuseoSansRounded90018    900      18
//   huge             MuseoSansRounded90040    900      40
//   symbols          lv_font_montserrat_14                  <- for LV_SYMBOL_* not in the above

#if defined(METAMODULE_UI_SCALED_FONTS)

extern "C" {
LV_FONT_DECLARE(ui_font_tiny);
LV_FONT_DECLARE(ui_font_small);
LV_FONT_DECLARE(ui_font_medium);
LV_FONT_DECLARE(ui_font_medium_bold);
LV_FONT_DECLARE(ui_font_med_large);
LV_FONT_DECLARE(ui_font_med_large_bold);
LV_FONT_DECLARE(ui_font_large);
LV_FONT_DECLARE(ui_font_huge);
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
inline constexpr lv_font_t const *font_symbols = &lv_font_montserrat_28;
} // namespace MetaModule

#else

extern "C" {
LV_FONT_DECLARE(ui_font_MuseoSansRounded50010);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50012);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50014);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70014);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50016);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70016);
LV_FONT_DECLARE(ui_font_MuseoSansRounded90018);
LV_FONT_DECLARE(ui_font_MuseoSansRounded90040);
}

namespace MetaModule
{
inline constexpr lv_font_t const *font_tiny = &ui_font_MuseoSansRounded50010;
inline constexpr lv_font_t const *font_small = &ui_font_MuseoSansRounded50012;
inline constexpr lv_font_t const *font_medium = &ui_font_MuseoSansRounded50014;
inline constexpr lv_font_t const *font_medium_bold = &ui_font_MuseoSansRounded70014;
inline constexpr lv_font_t const *font_med_large = &ui_font_MuseoSansRounded50016;
inline constexpr lv_font_t const *font_med_large_bold = &ui_font_MuseoSansRounded70016;
inline constexpr lv_font_t const *font_large = &ui_font_MuseoSansRounded90018;
inline constexpr lv_font_t const *font_huge = &ui_font_MuseoSansRounded90040;
inline constexpr lv_font_t const *font_symbols = &lv_font_montserrat_14;
} // namespace MetaModule

#endif
