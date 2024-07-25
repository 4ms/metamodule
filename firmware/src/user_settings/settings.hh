#pragma once
#include "conf/audio_settings.hh"
#include "gui/pages/view_settings.hh"

namespace MetaModule
{

struct UserSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};
	AudioSettings audio{};
};

} // namespace MetaModule
