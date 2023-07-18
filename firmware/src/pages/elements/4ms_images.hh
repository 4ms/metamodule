#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(jack_x_120);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob9mm_x_120);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(knob_x_120);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(button_x_120);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_unlined_x_120);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(knob_large_x_120);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(slider_x_120);
LV_IMG_DECLARE(switch_left);
LV_IMG_DECLARE(switch_left_120);
LV_IMG_DECLARE(switch_right);
LV_IMG_DECLARE(switch_right_120);
LV_IMG_DECLARE(switch_up);
LV_IMG_DECLARE(switch_up_120);
LV_IMG_DECLARE(switch_down);
LV_IMG_DECLARE(switch_down_120);
LV_IMG_DECLARE(switch_center);
LV_IMG_DECLARE(switch_center_120);
LV_IMG_DECLARE(led_x);
LV_IMG_DECLARE(led_x_120);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Knob &, uint32_t scale_px) {
	return scale_px == 240 ? &knob_x : &knob_x_120;
}

inline const lv_img_dsc_t *get_img(const Davies1900hBlackKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &knob_x : &knob_x_120;
}

inline const lv_img_dsc_t *get_img(const DaviesLargeKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &knob_large_x : &knob_large_x_120;
}

inline const lv_img_dsc_t *get_img(const Knob9mm &, uint32_t scale_px) {
	return scale_px == 240 ? &knob9mm_x : &knob9mm_x_120;
}

inline const lv_img_dsc_t *get_img(const JackInput4ms &, uint32_t scale_px) {
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

inline const lv_img_dsc_t *get_img(const JackOutput4ms &, uint32_t scale_px) {
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

inline const lv_img_dsc_t *get_img(const Slider25mmVertLED &, uint32_t scale_px) {
	return scale_px == 240 ? &slider_x : &slider_x_120;
}

inline const lv_img_dsc_t *get_img(const Slider25mmVert &, uint32_t scale_px) {
	return scale_px == 240 ? &slider_x : &slider_x_120;
}

inline const lv_img_dsc_t *get_img(const Toggle3pos &, uint32_t scale_px) {
	return scale_px == 240 ? &switch_center : &switch_center_120;
}

inline const lv_img_dsc_t *get_img(const Toggle2pos &, uint32_t scale_px) {
	return scale_px == 240 ? &switch_center : &switch_center_120;
}

inline const lv_img_dsc_t *get_img(const LatchingButton &, uint32_t scale_px) {
	return scale_px == 240 ? &button_x : &button_x_120;
}

inline const lv_img_dsc_t *get_img(const MomentaryButton &, uint32_t scale_px) {
	return scale_px == 240 ? &button_x : &button_x_120;
}

inline const lv_img_dsc_t *get_img(const LightElement &, uint32_t scale_px) {
	return scale_px == 240 ? &led_x : &led_x_120;
}

//TODO: Encoders

} // namespace MetaModule::ElementImageImpl
