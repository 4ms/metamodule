#pragma once
#include "CoreModules/elements/element_info.hh" //just for mm_to_px
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/styles.hh"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule::ElementDrawerImpl
{

constexpr std::pair<uint32_t, uint32_t> mm_to_topleft_px(uint32_t x_mm, uint32_t y_mm, uint32_t module_height) {
	uint32_t left = std::round(ElementInfoBase::mm_to_px(x_mm, module_height));
	uint32_t top = std::round(ElementInfoBase::mm_to_px(y_mm, module_height));
	return {left, top};
}

inline std::pair<uint32_t, uint32_t>
mm_to_center_px(uint32_t x_mm, uint32_t y_mm, const lv_img_dsc_t *img, uint32_t module_height) {
	uint32_t width = img ? img->header.w : 0;
	uint32_t height = img ? img->header.h : 0;
	uint32_t left = std::round(ElementInfoBase::mm_to_px(x_mm, module_height) - width / 2.f);
	uint32_t top = std::round(ElementInfoBase::mm_to_px(y_mm, module_height) - height / 2.f);
	return {left, top};
}

constexpr std::pair<uint32_t, uint32_t>
mm_to_center_px(uint32_t x_mm, uint32_t y_mm, uint32_t width, uint32_t height, uint32_t module_height) {
	uint32_t left = std::round(ElementInfoBase::mm_to_px(x_mm, module_height) - width / 2.f);
	uint32_t top = std::round(ElementInfoBase::mm_to_px(y_mm, module_height) - height / 2.f);
	return {left, top};
}

//
// Knob Helpers
//
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

	pr_dbg("Draw element at %d, %d (w:%d h:%d)\n", left, top, width, height);
}

inline lv_obj_t *
draw_element_topleft(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	auto [left, top] = mm_to_topleft_px(el.x_mm, el.y_mm, module_height);
	lv_obj_t *obj = lv_img_create(canvas);
	draw_element(left, top, img, obj);
	return obj;
}

} // namespace MetaModule::ElementDrawerImpl
