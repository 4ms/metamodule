#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(BananaBlack_240);
LV_IMG_DECLARE(BananaRed_240);
LV_IMG_DECLARE(Davies1900hRed_240);
LV_IMG_DECLARE(Davies1900hWhite_240);
LV_IMG_DECLARE(MediumLight_240);
LV_IMG_DECLARE(BefacoBigKnob_240);
LV_IMG_DECLARE(BefacoTinyKnobWhite_240);
LV_IMG_DECLARE(BefacoSlidePotSmall_240);
LV_IMG_DECLARE(BefacoSlidePotHandleSmall_240);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &) {
	return &Davies1900hWhite_240;
}

inline const lv_img_dsc_t *get_img(const Davies1900hRedKnob &) {
	return &Davies1900hRed_240;
}

inline const lv_img_dsc_t *get_img(const BefacoBigKnob &) {
	return &BefacoBigKnob_240;
}

inline const lv_img_dsc_t *get_img(const BefacoTinyKnob &) {
	return &BefacoTinyKnobWhite_240;
}

inline const lv_img_dsc_t *get_img(const BefacoInputPort &) {
	return &BananaBlack_240;
}

inline const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
	return &BananaRed_240;
}

inline const lv_img_dsc_t *get_img(const MediumLight<RedGreenBlueLight> &) {
	return &MediumLight_240;
}

inline const lv_img_dsc_t *get_img(const BefacoSlidePot &) {
	return &BefacoSlidePotSmall_240;
}

inline const lv_img_dsc_t *get_img_handle(const BefacoSlidePot &) {
	return &BefacoSlidePotHandleSmall_240;
}

} // namespace MetaModule::ElementImageImpl
