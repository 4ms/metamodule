#pragma once
#include "conf/audio_settings.hh"
#include "fs/volumes.hh"
#include "gui/pages/view_settings.hh"
#include "plugin_autoload_settings.hh"

namespace MetaModule
{

struct UserSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};
	AudioSettings audio{};
	PluginAutoloadSettings plugin_autoload{};
	std::string last_patch_opened{};
	Volume last_patch_vol{};
};

} // namespace MetaModule
