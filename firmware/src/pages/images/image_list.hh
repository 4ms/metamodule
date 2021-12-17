#pragma once
#include "lvgl/lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(ComplexEG_artwork_240);
LV_IMG_DECLARE(Pan_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(Follow_artwork_240);
LV_IMG_DECLARE(FM_artwork_240);
LV_IMG_DECLARE(Drum_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(Atvert2_artwork_240);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(BuffMult_artwork_240);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		// SLUG TO IMAGE HERE

		if (slug == "ComplexEG")
			return &ComplexEG_artwork_240;

		if (slug == "Pan")
			return &Pan_artwork_240;

		if (slug == "MultiLFO")
			return &MultiLFO_artwork_240;

		if (slug == "Follow")
			return &Follow_artwork_240;

		if (slug == "FM")
			return &FM_artwork_240;

		if (slug == "Drum")
			return &Drum_artwork_240;

		if (slug == "Djembe")
			return &Djembe_artwork_240;

		if (slug == "Atvert2")
			return &Atvert2_artwork_240;

		if (slug == "StMix")
			return &StMix_artwork_240;

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
