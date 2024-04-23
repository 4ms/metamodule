#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/draw_img.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/paths.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include <cmath>
#include <cstdint>

namespace MetaModule::ElementDrawer
{

inline lv_obj_t *draw_element(const BaseElement &, lv_obj_t *, uint32_t) {
	return nullptr;
}

inline lv_obj_t *draw_element(const ImageElement &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = ElementDrawer::draw_image(BaseElement(el), el.image, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const LightElement &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element(ImageElement(el), canvas, module_height);
	if (!obj)
		return nullptr;

	lv_obj_set_style_radius(obj, 20, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(obj, module_height == 240 ? 16 : 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_spread(obj, module_height == 240 ? 4 : 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_opa(obj, LV_OPA_0, LV_PART_MAIN);
	return obj;
}

inline lv_obj_t *draw_element(const FlipSwitch &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = ElementDrawer::draw_image(BaseElement(el), el.frames[0], canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const Knob &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = ElementDrawer::draw_image(BaseElement(el), el.image, canvas, module_height);
	if (obj)
		return obj;

	// Create image-less knob
	obj = lv_obj_create(canvas);
	float diameter = mm_to_px((el.width_mm + el.height_mm) / 2, module_height);
	float zoom = module_height / 240.f;
	float x = fix_zoomed_coord(el.coords, mm_to_px(el.x_mm, module_height), diameter, zoom);
	float y = fix_zoomed_coord(el.coords, mm_to_px(el.y_mm, module_height), diameter, zoom);
	int16_t pos_x = std::round(x);
	int16_t pos_y = std::round(y);

	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
	lv_obj_set_pos(obj, pos_x, pos_y);
	lv_obj_set_size(obj, diameter, diameter);
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(obj, diameter / 2 + 1, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(obj, LV_OPA_100, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(obj, lv_color_hex(0x666666), LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(obj, lv_color_hex(0x333333), LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(obj, LV_OPA_70, LV_STATE_DEFAULT);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
	lv_obj_set_style_transform_pivot_x(obj, std::round(diameter / 2), 0);
	lv_obj_set_style_transform_pivot_y(obj, std::round(diameter / 2), 0);

	lv_obj_refr_size(obj);

	auto dot = lv_obj_create(obj);
	int16_t dot_dia = std::round(std::max(3.f, diameter / 6));
	lv_obj_set_align(dot, LV_ALIGN_CENTER);
	// lv_obj_set_pos(dot, -diameter * 0.20f, diameter * 0.5f - dot_dia * 1.5f);
	lv_obj_set_pos(dot, 0, -diameter * 0.5f + dot_dia * 1.f);
	lv_obj_set_size(dot, dot_dia, dot_dia);
	lv_obj_set_style_radius(dot, dot_dia, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(dot, LV_OPA_100, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(dot, lv_color_hex(0xDDDDDD), LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(dot, 0, LV_STATE_DEFAULT);

	return obj;
}

// Draw slider with its handle as a sub-object
inline lv_obj_t *draw_element(const Slider &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = ElementDrawer::draw_image(BaseElement(el), el.image, canvas, module_height);

	if (!obj) {
		// Create image-less slider
		obj = lv_obj_create(canvas);
		float width = mm_to_px(el.width_mm, module_height);
		float height = mm_to_px(el.height_mm, module_height);
		float channel_width_px = 5.f;
		if (height > width)
			width = channel_width_px;
		else
			height = channel_width_px;
		float zoom = module_height / 240.f;
		float x = fix_zoomed_coord(el.coords, mm_to_px(el.x_mm, module_height), width, zoom);
		float y = fix_zoomed_coord(el.coords, mm_to_px(el.y_mm, module_height), height, zoom);
		int16_t pos_x = std::round(x);
		int16_t pos_y = std::round(y);

		lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
		lv_obj_set_pos(obj, pos_x, pos_y);
		lv_obj_set_size(obj, width, height);
		lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_pad_all(obj, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(obj, LV_OPA_100, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(obj, lv_color_hex(0x666666), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(obj, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
	}

	lv_obj_refr_size(obj);
	float w = lv_obj_get_width(obj);
	float h = lv_obj_get_height(obj);

	lv_obj_t *handle;

	if (el.image_handle.size()) {
		handle = lv_img_create(obj);
		ElementDrawer::draw_image(0, 0, Coords::Center, el.image_handle, handle, module_height);
	} else {
		handle = lv_obj_create(obj);
		if (w <= h) {
			// Vertical
			lv_obj_set_width(handle, w * module_height / 60);
			lv_obj_set_height(handle, module_height / 24);
			lv_obj_add_style(handle, &Gui::slider_handle_style, LV_PART_MAIN);
		} else {
			// Horizontal
			lv_obj_set_width(handle, module_height / 24); //10px at full scale
			lv_obj_set_height(handle, std::round(h * module_height / 60));
			lv_obj_add_style(handle, &Gui::slider_handle_style, LV_PART_MAIN);
		}
	}
	lv_obj_set_pos(handle, 0, 0);
	lv_obj_set_align(handle, (w <= h) ? LV_ALIGN_TOP_MID : LV_ALIGN_LEFT_MID);
	return obj;
}

inline lv_obj_t *draw_element(const SliderLight &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element(Slider(el), canvas, module_height);
	if (!obj)
		return nullptr;

	auto handle = lv_obj_get_child(obj, 0);
	if (handle) {
		lv_color_t color{.full = el.color};
		lv_obj_set_style_bg_color(handle, color, LV_PART_MAIN);
		lv_obj_set_style_radius(handle, 20, LV_PART_MAIN);
		lv_obj_set_style_shadow_width(handle, module_height == 240 ? 16 : 0, LV_PART_MAIN);
		lv_obj_set_style_shadow_spread(handle, module_height == 240 ? 4 : 0, LV_PART_MAIN);
		lv_obj_set_style_shadow_opa(handle, LV_OPA_0, LV_PART_MAIN);
	}
	return obj;
}

inline lv_obj_t *draw_element(const Button &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element(ImageElement(el), canvas, module_height);
	if (!obj)
		return nullptr;
	lv_obj_set_style_radius(obj, 20, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(obj, module_height >= 240 ? 8 : 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_spread(obj, module_height >= 240 ? 2 : 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_opa(obj, LV_OPA_0, LV_PART_MAIN);

	return obj;
}

//Draw slide switch with handle as a sub-object
inline lv_obj_t *draw_element(const SlideSwitch &el, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = ElementDrawer::draw_image(BaseElement(el), el.image, canvas, module_height);
	if (!obj)
		return nullptr;

	lv_obj_refr_size(obj);
	float w = lv_obj_get_width(obj);
	float h = lv_obj_get_height(obj);
	auto vert = h > w;

	lv_obj_t *handle;

	// Use image for handle, if image exists
	if (el.image_handle.length()) {
		handle = lv_img_create(obj);
		ElementDrawer::draw_image(0, 0, Coords::TopLeft, el.image_handle, handle, module_height);

	} else {
		// If there's no handle img, draw a handle with LVGL styles:
		handle = lv_obj_create(obj);
		lv_obj_add_style(handle, &Gui::slider_handle_style, 0);
		if (vert)
			lv_obj_set_size(handle, w - 2, h / el.num_pos);
		else
			lv_obj_set_size(handle, w / el.num_pos, h - 2);

		lv_obj_set_style_pad_all(handle, 0, LV_STATE_DEFAULT);
	}

	lv_obj_set_align(handle, vert ? LV_ALIGN_TOP_MID : LV_ALIGN_LEFT_MID);
	lv_obj_set_pos(handle, 0, 0);
	return obj;
}

} // namespace MetaModule::ElementDrawer
