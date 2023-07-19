#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(Rogan2SGray_240);
LV_IMG_DECLARE(Rogan2PSWhite_240);
LV_IMG_DECLARE(Rogan2PSGreen_240);
LV_IMG_DECLARE(Rogan2PSRed_240);

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const Rogan2SGray &) {
	return &Rogan2SGray_240;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSWhite &) {
	return &Rogan2PSWhite_240;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSRed &) {
	return &Rogan2PSRed_240;
}

inline const lv_img_dsc_t *get_img(const Rogan2PSGreen &) {
	return &Rogan2PSGreen_240;
}

inline const lv_img_dsc_t *get_img(const PJ301MPortIn &) {
	return &jack_x;
}

inline const lv_img_dsc_t *get_img(const PJ301MPortOut &) {
	return &jack_x;
}

} // namespace MetaModule::ElementImageImpl
