#pragma once
#include "audio_settings.hh"
#include "button_exp_knobset_settings.hh"
#include "catchup_settings.hh"
#include "fs/volumes.hh"
#include "usb/usb_device_mode.hh"
#include "usb/usb_role_mode.hh"
#include "user_settings/fs_settings.hh"
#include "user_settings/midi_pc_settings.hh"
#include "user_settings/midi_settings.hh"
#include "user_settings/missing_plugin_settings.hh"
#include "user_settings/notification_settings.hh"
#include "user_settings/patch_suggested_audio_settings.hh"
#include "user_settings/plugin_preload_settings.hh"
#include "user_settings/screensaver_settings.hh"
#include "user_settings/video_settings.hh"
#include "user_settings/view_settings.hh"

namespace MetaModule
{

struct UserSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};
	AudioSettings audio{};
	PluginPreloadSettings plugin_preload{};
	MissingPluginSettings missing_plugins{};

	// Initial patch
	std::string initial_patch_name{};
	Volume initial_patch_vol{Volume::NorFlash};
	bool load_initial_patch = true;

	ScreensaverSettings screensaver{};
	CatchupSettings catchup{};
	FilesystemSettings filesystem{};
	MidiSettings midi{};
	MidiPCPatchLoadSettings midi_pc_patch_load{};
	PatchSuggestedAudioSettings patch_suggested_audio{};
	ButtonExpKnobSetSettings button_exp_knobset{};
	NotificationSettings notifications{};
	VideoSettings video{};

	// How the USB-C port chooses its data role (Auto DRP / ForceHost / ForceDevice).
	UsbRoleMode usb_role_mode = UsbRoleMode::Auto;

	// Which USB device class the OTG core presents (Console/Video/MIDI), mutually
	// exclusive.
	UsbDeviceMode usb_device_mode = UsbDeviceMode::Midi;
};

} // namespace MetaModule
