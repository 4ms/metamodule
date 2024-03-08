#pragma once
#include "CoreModules/moduleFactory.hh"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct ModuleImages {
	static const std::string get_faceplate(const std::string_view slug) {
		std::string filename = std::string(ModuleFactory::getModuleFaceplate(slug));
		auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + filename;
		return path;
	}
};

} // namespace MetaModule
