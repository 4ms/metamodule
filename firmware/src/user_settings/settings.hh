#pragma once
#include "conf/audio_settings.hh"
#include "fs/volumes.hh"
#include "user_settings/fs_settings.hh"
#include "user_settings/plugin_autoload_settings.hh"
#include "user_settings/screensaver_settings.hh"
#include "user_settings/view_settings.hh"

namespace MetaModule
{

struct UserSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};
	AudioSettings audio{};
	PluginAutoloadSettings plugin_autoload{};
	std::string last_patch_opened{};
	Volume last_patch_vol{Volume::NorFlash};
	ScreensaverSettings screensaver{};
	FilesystemSettings filesystem{};
};

} // namespace MetaModule
