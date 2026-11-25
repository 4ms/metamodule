#pragma once

// GUI fonts are named by their role (ui_font_small, ui_font_large, ...), so that each
// platform can use sizes that are legible on its screen.
//
// MP1 (320x240) uses the Museo Sans Rounded fonts in slsexport/meta5/fonts: the role
// names are defined here as those fonts.
// MP2 has fonts with the role names: the same typefaces and glyphs, scaled up
// (fonts/scaled, made by fonts/generate_scaled_fonts.py).
//
// This is the only place that maps a role to a particular font. It's included by lv_conf.h,
// so there's no need to include it anywhere else.
// C code uses the role names (&ui_font_small); C++ code uses the pointers in ui_fonts.hh.
//
//   role                     weight   MP1 px
//   ui_font_tiny             500      10
//   ui_font_small            500      12
//   ui_font_medium           500      14
//   ui_font_medium_bold      700      14   <- the default font (LV_FONT_DEFAULT)
//   ui_font_med_large        500      16
//   ui_font_med_large_bold   700      16
//   ui_font_large            900      18
//   ui_font_huge             900      40
//   ui_font_icons            (icons)  26   <- FontAwesome: only the toolbar icons

#if !defined(METAMODULE_UI_SCALED_FONTS)
#define ui_font_tiny ui_font_MuseoSansRounded50010
#define ui_font_small ui_font_MuseoSansRounded50012
#define ui_font_medium ui_font_MuseoSansRounded50014
#define ui_font_medium_bold ui_font_MuseoSansRounded70014
#define ui_font_med_large ui_font_MuseoSansRounded50016
#define ui_font_med_large_bold ui_font_MuseoSansRounded70016
#define ui_font_large ui_font_MuseoSansRounded90018
#define ui_font_huge ui_font_MuseoSansRounded90040
#define ui_font_icons ui_font_FontAwesome26
#endif
