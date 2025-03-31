#pragma once
#include "fs/volumes.hh"
#include "util/fixed_vector.hh"
#include "util/static_string.hh"
#include <string>

namespace MetaModule
{

static constexpr std::string_view PluginDirName{"metamodule-plugins"};

struct PluginFile {
	// No dynamic memory allowed because this is shared between M4 and A7
	Volume vol{Volume::MaxVolumes};
	StaticString<255> full_path;   //"metamodule-plugins/BrandX.mmpatch"
	StaticString<255> plugin_name; //"BrandX" ==> "dirname will untar to: BrandX/BrandX.so"
	size_t file_size{};

	// This is everything after the "-v": 1.0.16-beta2-dev-13
	// It's used for
	// - displaying the plugin on the plugin tab
	// - autoloader picking the plugin with the latest version in the filename
	StaticString<31> version_in_filename;
};

static constexpr size_t MaxPlugins = 64;
using PluginFileList = FixedVector<PluginFile, MaxPlugins>;

} // namespace MetaModule
