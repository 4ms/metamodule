#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/images/image_fs.hh"
#include "lvgl.h"

LV_IMG_DECLARE(BananutBlack);
LV_IMG_DECLARE(BananutRed);

LV_IMG_DECLARE(BefacoSlidePotSmall);
LV_IMG_DECLARE(BefacoSlidePotHandleSmall);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const BefacoInputPort &) {
	return &::BananutBlack;
}

inline const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
	return &::BananutRed;
}

inline const lv_img_dsc_t *get_img(const BefacoSlidePotSmall &) {
	return &::BefacoSlidePotSmall;
}

} // namespace MetaModule::ElementImageImpl
