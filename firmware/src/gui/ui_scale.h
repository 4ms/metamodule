#pragma once
#include "lvgl.h"

// GUI density scale.
//
// The GUI was designed for MP1's 320x240 screen. MP2's screen has many more pixels per mm,
// so sizes that should stay the same physical size (fonts, padding, row heights, borders,
// icons...) are multiplied by METAMODULE_UI_SCALE percent (set by the build: 100 if not set).
//
// Use ui_px() for any dimension given in MP1 pixels:
//     lv_obj_set_height(obj, ui_px(24));
// Sizes that are a fraction of the screen (full-width bars, half-width columns...) should
// not use this: use lv_pct(), flex grow, or ScreenBufferConf::viewWidth/viewHeight.
//
// The fonts in gui/fonts/scaled, and the icon images in gui/slsexport/meta5/images/scaled, must be
// generated at the same scale (fonts/generate_scaled_fonts.py, images/generate_scaled_images.py)

#ifndef METAMODULE_UI_SCALE
#define METAMODULE_UI_SCALE 100
#endif

#ifdef __cplusplus
constexpr
#else
static inline
#endif
	lv_coord_t
	ui_px(lv_coord_t v) {
#if METAMODULE_UI_SCALE == 100
	return v;
#else
	// lv_pct(), LV_SIZE_CONTENT, LV_RADIUS_CIRCLE etc. are not pixel values
	if (!LV_COORD_IS_PX(v) || v == 0)
		return v;

	lv_coord_t scaled = v > 0 ? (v * METAMODULE_UI_SCALE + 50) / 100 : -((-v * METAMODULE_UI_SCALE + 50) / 100);

	if (scaled > LV_COORD_MAX)
		return LV_COORD_MAX;
	if (scaled < LV_COORD_MIN)
		return LV_COORD_MIN;
	return scaled;
#endif
}

// For values that are not lv_coord_t (e.g. image zoom, where 256 is 1x)
#ifdef __cplusplus
constexpr
#else
static inline
#endif
	int32_t
	ui_scale_int(int32_t v) {
	return (v * METAMODULE_UI_SCALE + 50) / 100;
}
