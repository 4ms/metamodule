#pragma once
#include "CoreModules/moduleFactory.hh"
#include "lvgl.h"
#include <string_view>

struct ModuleImages {
	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		return static_cast<lv_img_dsc_t *>(ModuleFactory::getModuleFaceplate(slug));
	}
};

