#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(Rogan2SGray);
LV_IMG_DECLARE(Rogan2PSWhite);
LV_IMG_DECLARE(Rogan2PSGreen);
LV_IMG_DECLARE(Rogan2PSRed);
LV_IMG_DECLARE(Davies1900hRed);
LV_IMG_DECLARE(Davies1900hWhite);
LV_IMG_DECLARE(MediumLight);
LV_IMG_DECLARE(BefacoPush_0);
LV_IMG_DECLARE(BefacoSlidePot);
LV_IMG_DECLARE(BefacoSlidePotHandle);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &) {
	return &::Davies1900hWhite;
}

inline const lv_img_dsc_t *get_img(const Davies1900hRedKnob &) {
	return &::Davies1900hRed;
}

inline const lv_img_dsc_t *get_img(const MediumLight<RedGreenBlueLight> &) {
	return &::MediumLight;
}

inline const lv_img_dsc_t *get_img(const Rogan2SGray &) {
	return &::Rogan2SGray;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSWhite &) {
	return &::Rogan2PSWhite;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSRed &) {
	return &::Rogan2PSRed;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSGreen &) {
	return &::Rogan2PSGreen;
}

inline const lv_img_dsc_t *get_img(const BefacoPush &) {
	return &::BefacoPush_0;
}

inline const lv_img_dsc_t *get_img(const BefacoSlidePot &) {
	return &::BefacoSlidePot;
}

inline const lv_img_dsc_t *get_img_handle(const BefacoSlidePot &) {
	return &::BefacoSlidePotHandle;
}

inline const lv_img_dsc_t *get_img(const PJ301MPortIn &) {
	return &::jack_x;
}

inline const lv_img_dsc_t *get_img(const PJ301MPortOut &) {
	return &::jack_x;
}

} // namespace MetaModule::ElementImageImpl
