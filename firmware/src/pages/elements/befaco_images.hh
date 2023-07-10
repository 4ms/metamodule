#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(BananaBlack_240);
LV_IMG_DECLARE(BananaBlack_120);
LV_IMG_DECLARE(BananaRed_240);
LV_IMG_DECLARE(BananaRed_120);
LV_IMG_DECLARE(Davies1900hRed_240);
LV_IMG_DECLARE(Davies1900hRed_120);
LV_IMG_DECLARE(Davies1900hWhite_240);
LV_IMG_DECLARE(Davies1900hWhite_120);
LV_IMG_DECLARE(MediumLight_240);
LV_IMG_DECLARE(MediumLight_120);
LV_IMG_DECLARE(BefacoBigKnob_240);
LV_IMG_DECLARE(BefacoBigKnob_120);
LV_IMG_DECLARE(BefacoTinyKnobWhite_240);
LV_IMG_DECLARE(BefacoTinyKnobWhite_120);
LV_IMG_DECLARE(BefacoSlidePotSmall_240);
LV_IMG_DECLARE(BefacoSlidePotSmall_120);
LV_IMG_DECLARE(BefacoSlidePotHandleSmall_240);
LV_IMG_DECLARE(BefacoSlidePotHandleSmall_120);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &Davies1900hWhite_240 : &Davies1900hWhite_120;
}

inline const lv_img_dsc_t *get_img(const Davies1900hRedKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &Davies1900hRed_240 : &Davies1900hRed_120;
}

inline const lv_img_dsc_t *get_img(const BefacoBigKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &BefacoBigKnob_240 : &BefacoBigKnob_120;
}

inline const lv_img_dsc_t *get_img(const BefacoTinyKnob &, uint32_t scale_px) {
	return scale_px == 240 ? &BefacoTinyKnobWhite_240 : &BefacoTinyKnobWhite_120;
}

inline const lv_img_dsc_t *get_img(const BefacoInputPort &, uint32_t scale_px) {
	return scale_px == 240 ? &BananaBlack_240 : &BananaBlack_120;
}

inline const lv_img_dsc_t *get_img(const BefacoOutputPort &, uint32_t scale_px) {
	return scale_px == 240 ? &BananaRed_240 : &BananaRed_120;
}

inline const lv_img_dsc_t *get_img(const MediumLight<RedGreenBlueLight> &, uint32_t scale_px) {
	return scale_px == 240 ? &MediumLight_240 : &MediumLight_120;
}

inline const lv_img_dsc_t *get_img(const BefacoSlidePot &, uint32_t scale_px) {
	return scale_px == 240 ? &BefacoSlidePotSmall_240 : &BefacoSlidePotSmall_120;
}

inline const lv_img_dsc_t *get_img_handle(const BefacoSlidePot &, uint32_t scale_px) {
	return scale_px == 240 ? &BefacoSlidePotHandleSmall_240 : &BefacoSlidePotHandleSmall_120;
}

} // namespace MetaModule::ElementImageImpl
