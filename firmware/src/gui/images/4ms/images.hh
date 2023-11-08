#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(led_x);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const LightElement &) {
	return &led_x;
}

} // namespace MetaModule::ElementImageImpl
