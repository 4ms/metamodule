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

inline void draw_element(
	uint32_t left, uint32_t top, Coords coord_ref, const lv_img_dsc_t *img, lv_obj_t *obj, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_knob: image not found\n");
		return;
	}
	lv_img_set_src(obj, img);

	uint32_t width = img->header.w;
	uint32_t height = img->header.h;

	float zoom = module_height / 240.f;
	float pixel_width = width * zoom;
	float pixel_height = height * zoom;

	if (coord_ref == Coords::TopLeft && module_height != 240) {
		left -= pixel_width / 2.f;
		top -= pixel_height / 2.f;
	} else if (coord_ref == Coords::Center && module_height != 240) {
		left -= pixel_width;
		top -= pixel_height;
	}
	printf("@left:%d, top:%d [%d x %d]\n", left, top, width, height);

	uint16_t lv_zoom = 256.f * zoom;
	lv_img_set_zoom(obj, lv_zoom);
	lv_img_set_antialias(obj, true);
	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
	lv_obj_set_pos(obj, left, top);
	lv_img_set_pivot(obj, width / 2, height / 2);
}

inline lv_obj_t *
draw_element(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	lv_obj_t *obj = lv_img_create(canvas);
	auto [x, y] = mm_to_px(el.x_mm, el.y_mm, module_height);
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
