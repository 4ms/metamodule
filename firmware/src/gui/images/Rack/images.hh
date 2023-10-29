#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(Trimpot);
LV_IMG_DECLARE(Rogan1PRed);
LV_IMG_DECLARE(Rogan2SGray);
LV_IMG_DECLARE(Rogan2PSWhite);
LV_IMG_DECLARE(Rogan2PSGreen);
LV_IMG_DECLARE(Rogan2PSRed);
LV_IMG_DECLARE(Rogan3PSWhite);
LV_IMG_DECLARE(Davies1900hRed);
LV_IMG_DECLARE(Davies1900hWhite);
LV_IMG_DECLARE(MediumLight);
LV_IMG_DECLARE(BefacoPush_0);
LV_IMG_DECLARE(BefacoSlidePot);
LV_IMG_DECLARE(BefacoSlidePotHandle);
LV_IMG_DECLARE(LEDBezel);
LV_IMG_DECLARE(CKSS_0);
LV_IMG_DECLARE(CKD6_0);
LV_IMG_DECLARE(TL1105);

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

template<typename T>
const lv_img_dsc_t *get_img(const SmallLight<T> &) {
	return &::MediumLight;
}

inline const lv_img_dsc_t *get_img(const Rogan1PRed &) {
	return &::Rogan1PRed;
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

inline const lv_img_dsc_t *get_img(const Rogan3PSWhite &) {
	return &::Rogan3PSWhite;
}

inline const lv_img_dsc_t *get_img(const Trimpot &) {
	return &::Trimpot;
}

template<typename T>
inline const lv_img_dsc_t *get_img(const VCVLightBezel<T> &) {
	return &::LEDBezel;
}

inline const lv_img_dsc_t *get_img(const LEDBezel &) {
	return &::LEDBezel;
}

inline const lv_img_dsc_t *get_img(const CKSS &) {
	return &::CKSS_0;
}

inline const lv_img_dsc_t *get_img(const CKD6 &) {
	return &::CKD6_0;
}

inline const lv_img_dsc_t *get_img(const TL1105 &) {
	return &::TL1105;
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
