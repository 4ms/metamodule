#pragma once
#include "fs/volumes.hh"
#include <string>
#include <vector>

namespace MetaModule
{

struct PluginFile {
	Volume vol;
	std::string dir_name;	 //"BrandX"     ==> "/{Volume}/metamodule-plugins/BrandX"
	std::string plugin_name; //"PluginName" ==> "/{Volume}/metamodule-plugins/BrandX/PluginName.so"
};

using PluginFileList = std::vector<PluginFile>;

} // namespace MetaModule
