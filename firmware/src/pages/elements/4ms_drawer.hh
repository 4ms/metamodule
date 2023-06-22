#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/elements/element_draw_helpers.hh"
#include "pr_dbg.hh"

namespace MetaModule::ElementDrawerImpl
{
// 4ms Knobs;
inline lv_obj_t *draw_element(const Knob9mm &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const DaviesLargeKnob &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const Davies1900hBlackKnob &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const JackInput4ms &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_jack_centered(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const JackOutput4ms &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_jack_centered(el, img, canvas, module_height);
}

inline lv_obj_t *draw_element(const Toggle3pos &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const Slider25mmVertLED &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

inline lv_obj_t *
draw_element(const LatchingButtonMonoLight &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	return draw_param_center(el, img, canvas, module_height);
}

} // namespace MetaModule::ElementDrawerImpl
