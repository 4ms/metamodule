#pragma once

#include "CoreModules/elements/units.hh"
#include "lvgl.h"
#include <cmath>
#include <nanovg.h>
#include <span>

namespace MetaModule::NanoVG
{

constexpr lv_coord_t to_lv_coord(float x) {
	return std::round(mm_to_px(to_mm(x), 240));
}
// 10px in rack dimensions => 6.325px in MM dimensions
// static_assert(mm_to_px(to_mm(10.f), 240) == 6.325291928f);

constexpr lv_point_t to_lv_point(NVGvertex vertex) {
	return lv_point_t(to_lv_coord(vertex.x), to_lv_coord(vertex.y));
}

lv_color_t to_lv_color(NVGcolor color) {
	return lv_color_make(color.r * 255.f, color.g * 255.f, color.b * 255.f);
}

lv_color_t to_lv_text_color(NVGcolor color) {
	auto hsv = lv_color_to_hsv(to_lv_color(color));
	return lv_color_hsv_to_rgb(hsv.h, (hsv.s + 100) / 2, 100);
}

constexpr uint8_t to_lv_opa(NVGcolor color) {
	return std::round((1.f - (1.f - color.a) * (1.f - color.a)) * float(LV_OPA_100));
}

constexpr bool is_poly_concave(std::span<lv_point_t> points) {
	auto n = points.size();
	if (n < 3)
		return false;

	auto X_prod = [](lv_point_t O, lv_point_t A, lv_point_t B) {
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	};

	int sign = 0;
	for (auto i = 0u; i < points.size(); i++) {
		auto O = points[i];
		auto A = points[(i + 1) % n];
		auto B = points[(i + 2) % n];
		auto cross = X_prod(O, A, B);
		if (cross == 0)
			continue;

		if (sign == 0)
			sign = cross;

		if ((sign > 0 && cross < 0) || (sign < 0 && cross > 0))
			return true;
	}
	return false;
}

// returns number of points to draw:
constexpr size_t split_poly_concave(std::span<lv_point_t> points) {
	auto n = points.size();
	if (n < 3)
		return 0;

	auto X_prod = [](lv_point_t O, lv_point_t A, lv_point_t B) {
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	};

	int sign = 0;

	for (auto i = 0u; i < points.size(); i++) {
		auto O = points[i];
		auto A = points[(i + 1) % n];
		auto B = points[(i + 2) % n];
		auto cross = X_prod(O, A, B);
		if (cross == 0)
			continue;

		if (sign == 0)
			sign = cross;

		if ((sign > 0 && cross < 0) || (sign < 0 && cross > 0)) {
			return i + 2;
		}
	}

	return points.size();
}

constexpr bool fix_poly_concave(std::span<lv_point_t> points) {
	auto n = points.size();
	if (n < 3)
		return false;

	auto X_prod = [](lv_point_t O, lv_point_t A, lv_point_t B) {
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	};

	int sign = 0;

	int offender = -1;
	lv_point_t fix{};

	for (auto i = 0u; i < points.size() + 1; i++) {
		auto O = points[i];
		auto A = points[(i + 1) % n];
		auto B = points[(i + 2) % n];
		auto cross = X_prod(O, A, B);
		if (cross == 0)
			continue;

		if (sign == 0)
			sign = cross;

		if ((sign > 0 && cross < 0) || (sign < 0 && cross > 0)) {
			auto AOdist = (A.x - O.x) * (A.x - O.x) + (A.y - O.y) * (A.y * O.y);
			auto BAdist = (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y * A.y);
			if (BAdist <= AOdist) {
				// set A to B
				fix = B;
				offender = (i + 1) % n;
			} else {
				// fix = O;
				// offender = (i + 1) % n;
				// set B to A
				fix = A;
				offender = (i + 2) % n;
			}
		}
	}

	if (offender >= 0) {
		points[offender] = fix;
		return fix_poly_concave(points);
	}

	return true;
}

} // namespace MetaModule::NanoVG
