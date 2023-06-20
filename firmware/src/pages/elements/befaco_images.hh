#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pr_dbg.hh"

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

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &, uint32_t scale_px) {
	pr_dbg("get_img->Davies1900hWhiteKnob\n");
	return scale_px == 240 ? &Davies1900hWhite_240 : &Davies1900hWhite_120;
}

inline const lv_img_dsc_t *get_img(const Davies1900hRedKnob &, uint32_t scale_px) {
	pr_dbg("get_img->Davies1900hRedKnob\n");
	return scale_px == 240 ? &Davies1900hRed_240 : &Davies1900hRed_120;
}

inline const lv_img_dsc_t *get_img(const BefacoInputPort &, uint32_t scale_px) {
	pr_dbg("get_img->BananaRed\n");
	return scale_px == 240 ? &BananaBlack_240 : &BananaBlack_120;
}

inline const lv_img_dsc_t *get_img(const BefacoOutputPort &, uint32_t scale_px) {
	pr_dbg("get_img->BananaRed\n");
	return scale_px == 240 ? &BananaRed_240 : &BananaRed_120;
}

inline const lv_img_dsc_t *get_img(const MediumLight<RedGreenBlueLight> &, uint32_t scale_px) {
	pr_dbg("get_img->MediumLight<RedGreenBlueLight>\n");
	return scale_px == 240 ? &MediumLight_240 : &MediumLight_120;
}

} // namespace MetaModule::ElementImageImpl
