#pragma once
#include "gui/notify/queue.hh"
// #include "patch_play/patch_playloader.hh"
#include "patch_file/open_patch_manager.hh"
#include "plugin_app_interface.hh"
#include "user_settings/settings.hh"

namespace MetaModule
{

struct PluginAppInterface::Internal {
	UserSettings &settings;
	// PatchPlayLoader &patch_playloader;
	OpenPatchManager &patches;
	NotificationQueue &notify_queue;
};

} // namespace MetaModule
