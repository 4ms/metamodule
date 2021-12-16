#pragma once
#include "lvgl/lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(PAN_artwork_240);
LV_IMG_DECLARE(MLFO_artwork_240);
LV_IMG_DECLARE(FLW_artwork_240);
LV_IMG_DECLARE(DJ_artwork_240);
LV_IMG_DECLARE(BPLR_artwork_240);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(BuffMult_artwork_240);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		// SLUG TO IMAGE HERE

		if (slug == "StMix")
			return &StMix_artwork_240;

		if (slug == "PAN")
			return &PAN_artwork_240;

		if (slug == "MLFO")
			return &MLFO_artwork_240;

		if (slug == "FLW")
			return &FLW_artwork_240;

		if (slug == "DJ")
			return &DJ_artwork_240;

		if (slug == "BPLR")
			return &BPLR_artwork_240;

		if (slug == "InfOsc")
			return &InfOsc_artwork_240;

		if (slug == "SMR")
			return &SMR_artwork_240;

		if (slug == "EnOsc")
			return &EnOsc_artwork_240;

		if (slug == "BuffMult")
			return &BuffMult_artwork_240;

		return nullptr;
	}
};
