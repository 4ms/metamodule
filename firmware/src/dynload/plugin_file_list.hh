#pragma once
#include "fs/volumes.hh"
#include "util/fixed_vector.hh"
#include "util/static_string.hh"
#include <string>

namespace MetaModule
{

static constexpr std::string_view PluginDirName{"metamodule-plugins/"};

struct PluginFile {
	Volume vol{Volume::MaxVolumes};
	StaticString<255> dir_name;	   //"BrandX"     ==> "/{Volume}/metamodule-plugins/BrandX"
	StaticString<255> plugin_name; //"PluginName" ==> "/{Volume}/metamodule-plugins/BrandX/PluginName.so"
	size_t file_size{};
};

static constexpr size_t MaxPlugins = 8;
using PluginFileList = FixedVector<PluginFile, MaxPlugins>;

} // namespace MetaModule
