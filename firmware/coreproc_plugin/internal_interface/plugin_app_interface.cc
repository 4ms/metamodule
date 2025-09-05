#include "fs/helpers.hh"
#include "plugin_app_if_internal.hh"

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
	instance->internal->patches.mark_playing_patch_modified();
}

void PluginAppInterface::notify_user(std::string_view message, int duration_ms) {
	instance->internal->notify_queue.put({message, Notification::Priority::Status, duration_ms});
}

StaticString<7> PluginAppInterface::get_volume() {
	return volume_string(instance->internal->patches.get_view_patch_loc().vol);
}

std::string PluginAppInterface::get_path() {
	auto [path, vol] = instance->internal->patches.get_view_patch_loc();
	return make_full_path(vol, path);
}

std::string PluginAppInterface::get_dir() {
	auto p = std::filesystem::path{get_path()};
	if (p.has_parent_path())
		return p.parent_path().string() + "/";
	else
		return "/";
}

} // namespace MetaModule
