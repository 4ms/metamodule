#pragma once
#include "CoreModules/moduleFactory.hh"
#include "lv_conf.h"
#include <string>
#include <string_view>

namespace MetaModule
{

struct ComponentImages {
	static const std::string get_comp_path(const std::string_view filename) {
		if (filename.length() > 0 && filename.length() < 256)
			return LV_FS_FATFS_LETTER + std::string(":ram:/") + std::string(filename);
		else
			return "";
	}
};

struct ModuleImages {
	static const std::string get_faceplate_path(const std::string_view slug) {
		auto filename = std::string(ModuleFactory::getModuleFaceplate(slug));
		if (filename.length())
			return LV_FS_FATFS_LETTER + std::string(":ram:/") + filename;
		else
			return "";
	}
};

} // namespace MetaModule
