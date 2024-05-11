#pragma once
#include "CoreModules/module_type_slug.hh"
#include <string_view>
#include <vector>

namespace MetaModule
{

std::vector<std::string_view> getAllFaceplates();
std::vector<ModuleTypeSlug> getAllFaceplateSlugs();

} // namespace MetaModule
