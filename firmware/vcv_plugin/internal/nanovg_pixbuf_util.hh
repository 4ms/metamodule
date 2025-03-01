#pragma once
#include "CoreModules/elements/units.hh"
#include "lvgl.h"
#include <cmath>
#include <nanovg.h>

namespace MetaModule::NanoVG
{

constexpr lv_coord_t to_lv_coord(float x, unsigned px_per_3U = 240) {
	return std::round(mm_to_px(to_mm(x), px_per_3U));
}
// 10px in rack dimensions => 6.325px in MM dimensions
// static_assert(mm_to_px(to_mm(10.f), 240) == 6.325291928f);

constexpr lv_point_t to_lv_point(NVGvertex vertex, unsigned px_per_3U) {
	lv_point_t p{
		.x = to_lv_coord(vertex.x, px_per_3U),
		.y = to_lv_coord(vertex.y, px_per_3U),
	};
	return p;
}

inline lv_color_t to_lv_color(NVGcolor color) {
	return lv_color_make(color.r * 255.f, color.g * 255.f, color.b * 255.f);
}

inline lv_color_t to_lv_text_color(NVGcolor color) {
	auto hsv = lv_color_to_hsv(to_lv_color(color));
	return lv_color_hsv_to_rgb(hsv.h, (hsv.s + 100) / 2, 100);
}

constexpr uint8_t to_lv_opa(NVGcolor color) {
	return std::round((1.f - (1.f - color.a) * (1.f - color.a)) * float(LV_OPA_100));
}

struct tvgColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

constexpr tvgColor to_tvg_color(NVGcolor color) {
	return tvgColor(color.r * 255, color.g * 255, color.b * 255, to_lv_opa(color));
}

} // namespace MetaModule::NanoVG
