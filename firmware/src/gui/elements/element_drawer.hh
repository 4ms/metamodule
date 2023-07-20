#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <cstdint>

namespace MetaModule
{

namespace ElementDrawerImpl
{

inline void
draw_element(float x, float y, Coords coord_ref, const lv_img_dsc_t *img, lv_obj_t *obj, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_knob: image not found\n");
		return;
	}
	lv_img_set_src(obj, img);

	float width = img->header.w;
	float height = img->header.h;

	float zoom = module_height / 240.f;

	if (coord_ref == Coords::TopLeft && zoom < 1.f) {
		// FIXME: why does LVGL add padding around a zoomed obj, and how to get rid of it?
		// This just happens to work, but why?
		x -= width * (1.f - zoom) / 2.f;
		y -= height * (1.f - zoom) / 2.f;
	} else if (coord_ref == Coords::Center) {
		//Calculate Top-left from Center
		x -= width / 2.f;
		y -= height / 2.f;
	}

	uint16_t lv_zoom = 256.f * zoom;
	lv_img_set_zoom(obj, lv_zoom);
	lv_img_set_size_mode(obj, LV_IMG_SIZE_MODE_VIRTUAL);
	lv_img_set_antialias(obj, false);
	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
	// lv_obj_add_style(obj, &Gui::module_border_style, LV_STATE_DEFAULT);

	uint16_t pos_x = std::round(x);
	uint16_t pos_y = std::round(y);
	lv_obj_set_pos(obj, pos_x, pos_y);
	lv_img_set_pivot(obj, width / 2.f, height / 2.f);
}

inline lv_obj_t *
draw_element(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	lv_obj_t *obj = lv_img_create(canvas);
	float x = ModuleInfoBase::mm_to_px(el.x_mm, module_height);
	float y = ModuleInfoBase::mm_to_px(el.y_mm, module_height);
	draw_element(x, y, el.coords, img, obj, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const Slider &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);

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

inline lv_obj_t *draw_element(const Toggle3pos &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);

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

	template<typename T>
	lv_obj_t *draw_element(T element, const lv_img_dsc_t *img) {
		if (img == nullptr)
			return nullptr;

		// if (element.coords == Coords::Center) {
		// 	element.x_mm -= ModuleInfoBase::to_mm(img->header.w / 2.f, 240 / 5.059f);
		// 	element.y_mm -= ModuleInfoBase::to_mm(img->header.h / 2.f, 240 / 5.059f);
		// }

		return ElementDrawerImpl::draw_element(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
