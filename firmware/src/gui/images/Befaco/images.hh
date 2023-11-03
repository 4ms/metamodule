#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(BananutBlack);
LV_IMG_DECLARE(BananutRed);
LV_IMG_DECLARE(BefacoBigKnob);
LV_IMG_DECLARE(BefacoTinyKnobWhite);
LV_IMG_DECLARE(BefacoSlidePotSmall);
LV_IMG_DECLARE(BefacoSlidePotHandleSmall);
LV_IMG_DECLARE(Davies1900hLightGrey);
LV_IMG_DECLARE(Davies1900hLargeLightGrey);
LV_IMG_DECLARE(Davies1900hDarkGrey);
LV_IMG_DECLARE(Davies1900hLargeGrey);
LV_IMG_DECLARE(SwitchTallVert);
LV_IMG_DECLARE(SwitchTallVertHandle);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const BefacoBigKnob &) {
	return &::BefacoBigKnob;
}

inline const lv_img_dsc_t *get_img(const BefacoTinyKnob &) {
	return &::BefacoTinyKnobWhite;
}

inline const lv_img_dsc_t *get_img(const BefacoTinyKnobDarkGrey &) {
	return &::BefacoTinyKnobWhite;
}

inline const lv_img_dsc_t *get_img(const Davies1900hDarkGreyKnob &) {
	return &::Davies1900hDarkGrey;
}

inline const lv_img_dsc_t *get_img(const Davies1900hLightGreyKnob &) {
	return &::Davies1900hLightGrey;
}

inline const lv_img_dsc_t *get_img(const Davies1900hLargeGreyKnob &) {
	return &::Davies1900hLargeGrey;
}

inline const lv_img_dsc_t *get_img(const Davies1900hLargeLightGreyKnob &) {
	return &::Davies1900hLargeLightGrey;
}

inline const lv_img_dsc_t *get_img(const BefacoInputPort &) {
	return &::BananutBlack;
}

inline const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
	return &::BananutRed;
}

inline const lv_img_dsc_t *get_img(const BefacoSlidePotSmall &) {
	return &::BefacoSlidePotSmall;
}

//TODO: this is not used. Remove it or use it
inline const lv_img_dsc_t *get_img_handle(const BefacoSlidePotSmall &) {
	return &::BefacoSlidePotHandleSmall;
}

inline const lv_img_dsc_t *get_img(const ToggleNpos &) { //CK77Vert7 is not in the variant
	return &::SwitchTallVert;
}

//TODO: this is not used. Remove it or use it
inline const lv_img_dsc_t *get_img_handle(const ToggleNpos &) {
	return &::SwitchTallVertHandle;
}

} // namespace MetaModule::ElementImageImpl
