#pragma once
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Returns a copy of the image `src`, resized by the GUI scale (see gui/ui_scale.h).
// `src` must be an lv_img_dsc_t in LV_IMG_CF_TRUE_COLOR_ALPHA format (as SquareLine exports
// its icons). Anything else (symbols, file paths, other formats, NULL) is returned as-is.
// Copies are cached and never freed: this is meant for the small, fixed set of exported icons.
//
// FIXME: this is a stopgap for the 1x icons exported by SquareLine: they should be replaced
// with artwork drawn at the screen's density.
const void *ui_scaled_img(const void *src);

#ifdef __cplusplus
}
#endif
