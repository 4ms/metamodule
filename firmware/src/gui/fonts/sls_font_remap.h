#pragma once

// Force-included when compiling slsexport/ for mp2 builds
// (instead of compiling the mp1 museo fonts)
//
// The exported screens and components name the MP1 fonts directly
// so rather than editing them, redirect the names to the scaled
// font with the same role. See ui_fonts.hh

#define ui_font_MuseoSansRounded50010 ui_font_tiny
#define ui_font_MuseoSansRounded50012 ui_font_small
#define ui_font_MuseoSansRounded50014 ui_font_medium
#define ui_font_MuseoSansRounded70014 ui_font_medium_bold
#define ui_font_MuseoSansRounded50016 ui_font_med_large
#define ui_font_MuseoSansRounded70016 ui_font_med_large_bold
#define ui_font_MuseoSansRounded90018 ui_font_large
#define ui_font_MuseoSansRounded90040 ui_font_huge
