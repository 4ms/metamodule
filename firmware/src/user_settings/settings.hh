#pragma once
#include "audio_settings.hh"
#include "catchup_settings.hh"
#include "fs/volumes.hh"
#include "user_settings/fs_settings.hh"
#include "user_settings/midi_settings.hh"
#include "user_settings/plugin_preload_settings.hh"
#include "user_settings/screensaver_settings.hh"
#include "user_settings/view_settings.hh"

namespace MetaModule
{

struct UserSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};
	AudioSettings audio{};
	PluginPreloadSettings plugin_preload{};

	// Initial patch
	std::string initial_patch_name{};
	Volume initial_patch_vol{Volume::NorFlash};
	bool load_initial_patch = true;

	ScreensaverSettings screensaver{};
	CatchupSettings catchup{};
	FilesystemSettings filesystem{};
	MidiSettings midi{};
};

} // namespace MetaModule
