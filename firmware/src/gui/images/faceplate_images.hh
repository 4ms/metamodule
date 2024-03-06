#pragma once
#include "CoreModules/moduleFactory.hh"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct ModuleImages {
	static const auto get_image_by_slug(const std::string_view slug) {
		return ModuleFactory::getModuleFaceplate(slug);
	}
};

} // namespace MetaModule
