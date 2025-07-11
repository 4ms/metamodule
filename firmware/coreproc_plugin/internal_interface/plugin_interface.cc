#include "plugin_internal.hh"

namespace MetaModule
{

// static instance
PluginAppInterface *PluginAppInterface::instance;

PluginAppInterface::PluginAppInterface(PluginAppInterface::Internal &internal)
	: internal{std::make_unique<PluginAppInterface::Internal>(internal)} {
}

PluginAppInterface::~PluginAppInterface() = default;

void PluginAppInterface::register_interface() {
	if (instance == nullptr)
		instance = this;
}

/// Plugin-visible functions:

uint32_t PluginAppInterface::get_block_size() {
	return instance->internal->settings.audio.block_size;
}

void PluginAppInterface::mark_patch_modified() {
	instance->internal->patch_playloader.mark_playing_patch_modified();
}

void PluginAppInterface::notify_user(std::string_view message, int duration_ms) {
	instance->internal->notify_queue.put({std::string{message}, Notification::Priority::Status, duration_ms});
}

} // namespace MetaModule
