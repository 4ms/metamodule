#include "plugin_interface.hh"
#include "gui/notify/queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings.hh"

namespace MetaModule
{

struct PluginInterface::Internal {
	UserSettings &settings;
	PatchPlayLoader &patch_playloader;
	NotificationQueue &notify_queue;
};

// static instance
PluginInterface *PluginInterface::instance;

PluginInterface::PluginInterface(UserSettings &user_settings,
								 PatchPlayLoader &playloader,
								 NotificationQueue &notify_queue)
	: internal{std::make_unique<Internal>(user_settings, playloader, notify_queue)} {
}

PluginInterface::~PluginInterface() = default;

/// Plugin-visible functions:

uint32_t PluginInterface::get_block_size() const {
	return internal->settings.audio.block_size;
}

void PluginInterface::mark_patch_modified() {
	internal->patch_playloader.mark_playing_patch_modified();
}

void PluginInterface::notify_user(std::string_view message, int duration_ms) {
	internal->notify_queue.put({std::string{message}, Notification::Priority::Status, duration_ms});
	;
}

} // namespace MetaModule
