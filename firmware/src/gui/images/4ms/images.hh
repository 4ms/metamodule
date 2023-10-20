#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(slider_horiz_x);
LV_IMG_DECLARE(switch_center);
LV_IMG_DECLARE(led_x);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Knob &) {
	return &knob_x;
}

inline const lv_img_dsc_t *get_img(const Davies1900hBlackKnob &) {
	return &knob_x;
}

inline const lv_img_dsc_t *get_img(const DaviesLargeKnob &) {
	return &knob_large_x;
}

inline const lv_img_dsc_t *get_img(const Knob9mm &) {
	return &knob9mm_x;
}

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

inline const lv_img_dsc_t *get_img(const Slider25mmHorizLED &) {
	return &slider_horiz_x;
}

inline const lv_img_dsc_t *get_img(const Slider25mmHoriz &) {
	return &slider_horiz_x;
}

inline const lv_img_dsc_t *get_img(const Toggle3pos &) {
	return &switch_center;
}

inline const lv_img_dsc_t *get_img(const Toggle2pos &) {
	return &switch_center;
}

inline const lv_img_dsc_t *get_img(const LatchingButton &) {
	return &button_x;
}

inline const lv_img_dsc_t *get_img(const MomentaryButton &) {
	return &button_x;
}

inline const lv_img_dsc_t *get_img(const LightElement &) {
	return &led_x;
}

//TODO: Encoders

} // namespace MetaModule::ElementImageImpl
