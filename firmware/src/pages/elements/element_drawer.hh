#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/elements/element_image.hh"
#include "pages/styles.hh"
// #include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule::ElementDrawerImpl
{
inline lv_obj_t *draw_element(const BaseElement &, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	pr_dbg("draw_element(BaseElement), not found\n");
	return nullptr;
}

// Pot -- create lvgl image object so it can be animated later
inline lv_obj_t *draw_element(const Pot &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_element(Pot), image not found\n");
		return nullptr;
	}
	uint32_t width = img->header.w;
	uint32_t height = img->header.h;
	// if x,y are top-left corner:
	uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
	uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));
	// if x,y are center:
	// uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - width / 2.f);
	// uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - height / 2.f);

	lv_obj_t *obj = lv_img_create(canvas);
	lv_img_set_src(obj, img);
	lv_obj_set_pos(obj, left, top);
	lv_img_set_pivot(obj, width / 2, height / 2);
	lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);
	pr_dbg("Draw pot at %d, %d (w:%d h:%d) module_height=%d\n", left, top, width, height, module_height);
	return obj;
}

// Jack -- draw knob on canvas
inline lv_obj_t *
draw_element(const JackElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_element(JackElement), image not found\n");
		return nullptr;
	}
	uint32_t width = img->header.w;
	uint32_t height = img->header.h;
	uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
	uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));

	lv_draw_img_dsc_t draw_img_dsc;
	lv_draw_img_dsc_init(&draw_img_dsc);
	lv_canvas_draw_img(canvas, left, top, img, &draw_img_dsc);

	pr_dbg("Draw jack at %d, %d (w:%d h:%d) module_height=%d\n", left, top, width, height, module_height);

	return nullptr;
}

} // namespace MetaModule::ElementDrawerImpl

namespace MetaModule
{

struct ElementDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	template<typename T>
	lv_obj_t *draw_element(const T &element, const lv_img_dsc_t *img) {
		return ElementDrawerImpl::draw_element(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
