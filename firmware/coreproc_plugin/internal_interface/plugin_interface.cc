#include "plugin_interface.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings.hh"

namespace MetaModule
{

struct PluginInterface::Internal {
	UserSettings &settings;
	PatchPlayLoader &patch_playloader;
};

PluginInterface::~PluginInterface() = default;

uint32_t PluginInterface::get_block_size() const {
	return internal->settings.audio.block_size;
}

void PluginInterface::mark_patch_modified() {
	internal->patch_playloader.mark_playing_patch_modified();
}

PluginInterface::PluginInterface(UserSettings &user_settings, PatchPlayLoader &playloader)
	: internal{std::make_unique<Internal>(user_settings, playloader)} {
}

// static instance
PluginInterface *PluginInterface::instance;

} // namespace MetaModule
