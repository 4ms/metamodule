#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(MediumLight);

namespace MetaModule::ElementImageImpl
{

template<typename T>
inline const lv_img_dsc_t *get_img(const MediumLight<T> &) {
	return &::MediumLight;
}

template<typename T>
const lv_img_dsc_t *get_img(const SmallLight<T> &) {
	return &::MediumLight;
}

} // namespace MetaModule::ElementImageImpl
