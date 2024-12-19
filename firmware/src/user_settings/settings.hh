#pragma once
#include "audio_settings.hh"
#include "catchup_settings.hh"
#include "fs/volumes.hh"
#include "gui/elements/screensaver_settings.hh"
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
	Volume last_patch_vol{Volume::NorFlash};
	ScreensaverSettings screensaver{};
	CatchupSettings catchup{};
};

} // namespace MetaModule
