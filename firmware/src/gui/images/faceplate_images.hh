#pragma once
#include "CoreModules/moduleFactory.hh"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct ModuleImages {
	static const std::string get_image_by_slug(const std::string_view slug) {
		auto path = LV_FS_FATFS_LETTER + std::string(":2:") + std::string(ModuleFactory::getModuleFaceplate(slug));
		return path;
	}
};

} // namespace MetaModule
