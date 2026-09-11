#pragma once

#include "dynload/code_buffer.hh"
#include "dynload/plugin_file_list.hh"
#include "plugin/Plugin.hpp"
#include <cstdint>
#include <list>
#include <vector>

namespace MetaModule
{

struct LoadedPlugin {
	PluginFile fileinfo;
	rack::plugin::Plugin rack_plugin;
	std::vector<std::string> loaded_files;
	CodeBuffer code;
};

using LoadedPluginList = std::list<LoadedPlugin>;

} // namespace MetaModule
