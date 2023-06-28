#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
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
	// lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);

	// pr_dbg("Draw element at %d, %d (w:%d h:%d)\n", left, top, width, height);
}

inline lv_obj_t *
draw_element_topleft(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto [left, top] = mm_to_topleft_px(el.x_mm, el.y_mm, module_height);
	lv_obj_t *obj = lv_img_create(canvas);
	draw_element(left, top, img, obj);
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
			element.x_mm -= ElementInfoBase::to_mm(img->header.w / 2.f, module_height / 5.059f);
			element.y_mm -= ElementInfoBase::to_mm(img->header.h / 2.f, module_height / 5.059f);
		}

		return ElementDrawerImpl::draw_element_topleft(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
