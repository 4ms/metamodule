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
	// The plugin's modules: brands the plugin created, plus "Brand:Module" for each
	// module it added to a brand that already existed (see PluginModuleSlugs).
	// The brands can differ from the plugin (file) name, e.g. a native plugin
	// jacktest.mmplugin calling register_module("Jack Test", ...)
	std::vector<std::string> loaded_module_slugs;
};

using LoadedPluginList = std::list<LoadedPlugin>;

} // namespace MetaModule
