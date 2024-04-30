#pragma once

#include "dynload/plugin_file_list.hh"
#include "plugin/Plugin.hpp"
#include <cstdint>
#include <deque>
#include <vector>

namespace MetaModule
{

struct LoadedPlugin {
	PluginFile fileinfo;
	rack::plugin::Plugin rack_plugin;
	std::vector<uint8_t> code;
};

using LoadedPluginList = std::deque<LoadedPlugin>;

} // namespace MetaModule
