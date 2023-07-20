#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include "pages/elements/element_draw_helpers.hh"
#include <cstdint>

namespace MetaModule
{

namespace ElementDrawerImpl
{

inline void draw_element(uint32_t left, uint32_t top, const lv_img_dsc_t *img, lv_obj_t *obj) {
	if (!img) {
		pr_dbg("draw_knob: image not found\n");
		return;
	}
	uint32_t width = img->header.w;
	uint32_t height = img->header.h;

	lv_img_set_src(obj, img);
	lv_obj_set_pos(obj, left, top);
	lv_img_set_pivot(obj, width / 2, height / 2);
}

inline lv_obj_t *
draw_element_topleft(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto [left, top] = mm_to_topleft_px(el.x_mm, el.y_mm, module_height);
	lv_obj_t *obj = lv_img_create(canvas);
	draw_element(left, top, img, obj);
	// pr_dbg("Draw element %.*s at %d, %d\n", el.short_name.size(), el.short_name.data(), left, top);
	return obj;
}

inline lv_obj_t *
draw_element_topleft(const Slider &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element_topleft(BaseElement(el), img, canvas, module_height);
	// auto [left, top] = mm_to_topleft_px(el.x_mm, el.y_mm, module_height);
	// lv_obj_t *obj = lv_img_create(canvas);
	// draw_element(left, top, img, obj);

	auto *handle = lv_obj_create(obj);
	// TODO: horizontal handle
	lv_obj_set_align(handle, LV_ALIGN_TOP_MID);
	lv_obj_set_width(handle, img->header.w);
	lv_obj_set_height(handle, module_height / 24);
	lv_obj_set_pos(handle, 0, 0);
	lv_obj_add_style(handle, &Gui::slider_handle_style, 0);

	// pr_dbg("Draw element %.*s at %d, %d\n", el.short_name.size(), el.short_name.data(), left, top);
	return obj;
}

inline lv_obj_t *
draw_element_topleft(const Toggle3pos &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element_topleft(BaseElement(el), img, canvas, module_height);

	auto *handle = lv_obj_create(obj);
	lv_obj_set_align(handle, LV_ALIGN_CENTER);
	lv_obj_set_width(handle, img->header.w / 4);
	lv_obj_set_height(handle, img->header.h / 4);
	lv_obj_set_pos(handle, 0, 0);
	lv_obj_add_style(handle, &Gui::slider_handle_style, 0);

	// pr_dbg("Draw element %.*s at %d, %d\n", el.short_name.size(), el.short_name.data(), left, top);
	return obj;
}

} // namespace ElementDrawerImpl

struct ElementDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;
	bool center_coords;

	template<typename T>
	lv_obj_t *draw_element(T element, const lv_img_dsc_t *img) {
		if (img == nullptr)
			return nullptr;

		if (center_coords) {
			element.x_mm -= ModuleInfoBase::to_mm(img->header.w / 2.f, module_height / 5.059f);
			element.y_mm -= ModuleInfoBase::to_mm(img->header.h / 2.f, module_height / 5.059f);
		}

		return ElementDrawerImpl::draw_element_topleft(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
