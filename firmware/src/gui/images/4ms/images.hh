#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(led_x);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const JackInput4ms &) {
	return &jack_x;
}

inline const lv_img_dsc_t *get_img(const JackOutput4ms &) {
	return &jack_x;
}

inline const lv_img_dsc_t *get_img(const Slider25mmVertLED &) {
	return &slider_x;
}

inline const lv_img_dsc_t *get_img(const Slider25mmVert &) {
	return &slider_x;
}

inline const lv_img_dsc_t *get_img(const LightElement &) {
	return &led_x;
}

//TODO: Encoders

} // namespace MetaModule::ElementImageImpl
