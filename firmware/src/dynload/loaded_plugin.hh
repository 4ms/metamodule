#pragma once

#include "dynload/code_buffer.hh"
#include "dynload/plugin_file_list.hh"
#include "plugin/Plugin.hpp"
#include <cstdint>
#include <list>
#include <vector>

namespace MetaModule
{

// Location of the plugin's .fini_array within its code buffer.
// The entries there are relocated (absolute) destructor pointers.
struct PluginFiniArray {
	uint32_t offset = 0;
	uint32_t count = 0;
};

struct LoadedPlugin {
	PluginFile fileinfo;
	rack::plugin::Plugin rack_plugin;
	std::vector<std::string> loaded_files;
	CodeBuffer code;
	PluginFiniArray fini_array;
};

using LoadedPluginList = std::list<LoadedPlugin>;

} // namespace MetaModule
