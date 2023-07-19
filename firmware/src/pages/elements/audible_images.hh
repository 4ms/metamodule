#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>

LV_IMG_DECLARE(braids_display_240);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const BraidsDisplay148x56 &) {
	return &braids_display_240;
}
} // namespace MetaModule::ElementImageImpl

namespace MetaModule::ElementDrawerImpl
{

inline lv_obj_t *
draw_element(const BraidsDisplay148x56 &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_element(BraidsDisplay148x56), image not found\n");
		return nullptr;
	}
	uint32_t left = std::round(ModuleInfoBase::mm_to_px(el.x_mm, module_height));
	uint32_t top = std::round(ModuleInfoBase::mm_to_px(el.y_mm, module_height));

	lv_draw_img_dsc_t draw_img_dsc;
	lv_draw_img_dsc_init(&draw_img_dsc);
	draw_img_dsc.zoom = 256.f * module_height / 240.f;
	lv_canvas_draw_img(canvas, left, top, img, &draw_img_dsc);

	return nullptr;
}

} // namespace MetaModule::ElementDrawerImpl
