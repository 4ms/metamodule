#pragma once
#include "gui/notify/queue.hh"
#include "patch_play/patch_playloader.hh"
#include "plugin_interface.hh"
#include "user_settings/settings.hh"

namespace MetaModule
{

struct PluginAppInterface::Internal {
	UserSettings &settings;
	PatchPlayLoader &patch_playloader;
	NotificationQueue &notify_queue;
};

} // namespace MetaModule
