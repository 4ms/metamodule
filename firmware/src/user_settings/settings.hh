#pragma once
#include "audio_settings.hh"
#include "fs/volumes.hh"
#include "user_settings/plugin_preload_settings.hh"

namespace MetaModule
{

struct UserSettings {

	// Default audio rate/block size
	AudioSettings audio{};

	// Plugins to preload
	PluginPreloadSettings plugin_preload{};

	// Initial patch
	std::string initial_patch_name{};
	Volume initial_patch_vol{Volume::NorFlash};
	bool load_initial_patch = true;
};

} // namespace MetaModule
