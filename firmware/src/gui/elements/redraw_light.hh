#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include "util/colors.hh"
#include <algorithm>
#include <cmath>

namespace MetaModule
{

inline void style_rgb(lv_obj_t *obj, std::span<float> vals, float max_brightness = 1.f) {
	if (!obj || vals.size() < 3)
		return;

	auto r_amt = std::clamp(vals[0], 0.f, 1.f);
	auto g_amt = std::clamp(vals[1], 0.f, 1.f);
	auto b_amt = std::clamp(vals[2], 0.f, 1.f);

	auto max = std::max(r_amt, std::max(g_amt, b_amt));
	float gain = 1.f / max;
	Color normalized = Color(r_amt * gain * 255, g_amt * gain * 255, b_amt * gain * 255);
	lv_color_t color{.full = normalized.Rgb565()};

	uint8_t opa = std::clamp<unsigned>(std::min(max, max_brightness) * 255.f, 0u, 255u);

	lv_obj_set_style_img_recolor_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_img_recolor(obj, color, LV_PART_MAIN);

	lv_obj_set_style_shadow_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_shadow_color(obj, color, LV_PART_MAIN);
}

inline void style_dual_color(lv_obj_t *obj, std::array<RGB565, 2> colors, std::span<float> vals) {
	if (!obj || vals.size() < 2)
		return;

	auto c1_amt = std::clamp(vals[0], 0.f, 1.f);
	auto c2_amt = std::clamp(vals[1], 0.f, 1.f);

	auto max = std::max(c1_amt, c2_amt);
	float gain = 1.f / max;

	auto col1 = Colors::black.blend(Color{colors[0]}, c1_amt * gain);
	auto col2 = Colors::black.blend(Color{colors[1]}, c2_amt * gain);
	auto normalized = col1.combine(col2);
	lv_color_t color{.full = normalized.Rgb565()};

	uint8_t opa = std::clamp<unsigned>(max * 255.f, 0u, 255u);

	lv_obj_set_style_img_recolor_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_img_recolor(obj, color, LV_PART_MAIN);

	lv_obj_set_style_shadow_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_shadow_color(obj, color, LV_PART_MAIN);
}

inline void style_mono(lv_obj_t *obj, RGB565 col, std::span<float> vals) {
	if (!obj || vals.size() < 1)
		return;

	lv_color_t color{.full = col.raw()};
	lv_opa_t opa = std::clamp<uint16_t>(vals[0] * 255.f, 0, 255);

	lv_obj_set_style_img_recolor_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_img_recolor(obj, color, LV_PART_MAIN);

	lv_obj_set_style_shadow_opa(obj, opa, LV_PART_MAIN);
	lv_obj_set_style_shadow_color(obj, color, LV_PART_MAIN);
}

/////////////////////////////

inline void redraw_light_element(const MonoLight &element, const GuiElement &gui_el, std::span<float> vals) {
	style_mono(gui_el.obj, element.color, vals);
}

inline void redraw_light_element(const DualLight &element, const GuiElement &gui_el, std::span<float> vals) {
	style_dual_color(gui_el.obj, element.color, vals);
}

inline void redraw_light_element(const RgbLight &element, const GuiElement &gui_el, std::span<float> vals) {
	style_rgb(gui_el.obj, vals);
}

inline void redraw_light_element(const LatchingButton &element, const GuiElement &gui_el, std::span<float> vals) {
	style_mono(gui_el.obj, element.color, vals);
}

inline void
redraw_light_element(const MomentaryButtonWhiteLight &element, const GuiElement &gui_el, std::span<float> vals) {
	style_mono(gui_el.obj, Colors565::White, vals);
}

inline void redraw_light_element(const MomentaryButtonRGB &element, const GuiElement &gui_el, std::span<float> vals) {
	style_rgb(gui_el.obj, vals, 0.75f);
}

inline void redraw_light_element(const SliderLight &element, const GuiElement &gui_el, std::span<float> vals) {
	if (!gui_el.obj || vals.size() < 1)
		return;

	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle)
		return;

	style_mono(handle, element.color, vals);
	return;
}

inline void redraw_light_element(const BaseElement &, const GuiElement &, std::span<float>) {
}

} // namespace MetaModule
