#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/images/image_fs.hh"
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

inline const lv_img_dsc_t *get_img(const SlideSwitch &el) {
	return PNGFileSystem::read(el.image_bg);
	// return static_cast<lv_img_dsc_t *>(el.image_bg);
}

} // namespace MetaModule::ElementImageImpl
