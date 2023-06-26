#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/elements/base_image.hh"
#include "pages/elements/element_draw_helpers.hh"
#include "pages/styles.hh"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule::ElementDrawerImpl
{

// Default (BaseElement): print debug message if element drawer impl. not found
inline lv_obj_t *draw_element(const BaseElement &el, const lv_img_dsc_t *, lv_obj_t *, uint32_t) {
	pr_dbg("draw_element(BaseElement), not found: %.*s\n", (int)el.short_name.size(), el.short_name.data());
	return nullptr;
}

// Default for Params
inline lv_obj_t *
draw_element(const ParamElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_topleft(el, img, canvas, module_height);
}

// Default for Jacks
inline lv_obj_t *
draw_element(const JackElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_jack_topleft(el, img, canvas, module_height);
}

} // namespace MetaModule::ElementDrawerImpl

namespace MetaModule
{

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

		return ElementDrawerImpl::draw_element(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
