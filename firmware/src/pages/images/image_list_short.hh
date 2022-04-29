#pragma once
#include "lvgl/lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(PEG_artwork_120);
LV_IMG_DECLARE(PitchShift_artwork_240);
LV_IMG_DECLARE(PitchShift_artwork_120);
LV_IMG_DECLARE(HPF_artwork_240);
LV_IMG_DECLARE(HPF_artwork_120);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_120);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_120);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(StMix_artwork_120);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(SMR_artwork_120);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug, size_t height = 240) {
		// SLUG TO IMAGE HERE

		if (slug == "PEG")
			return (height == 240) ? &PEG_artwork_240 : &PEG_artwork_120;

		if (slug == "PitchShift")
			return (height == 240) ? &PitchShift_artwork_240 : &PitchShift_artwork_120;

		if (slug == "HPF")
			return (height == 240) ? &HPF_artwork_240 : &HPF_artwork_120;

		if (slug == "MultiLFO")
			return (height == 240) ? &MultiLFO_artwork_240 : &MultiLFO_artwork_120;

		if (slug == "Djembe")
			return (height == 240) ? &Djembe_artwork_240 : &Djembe_artwork_120;

		if (slug == "StMix")
			return (height == 240) ? &StMix_artwork_240 : &StMix_artwork_120;

		if (slug == "SMR")
			return (height == 240) ? &SMR_artwork_240 : &SMR_artwork_120;

		return nullptr;
	}
};
