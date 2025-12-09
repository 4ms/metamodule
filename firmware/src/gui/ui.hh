#pragma once
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "gui/notify/notification.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings_file.hh"

namespace MetaModule
{

class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	NotificationQueue notify_queue;
	ParamsMidiState params;
	MetaParams metaparams;
	UserSettings settings;
	PluginManager &plugin_manager;

	ParamDbgPrint print_dbg_params{params, metaparams};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   FileStorageProxy &patch_storage,
	   OpenPatchManager &open_patch_manager,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue,
	   PluginManager &plugin_manager,
	   FatFileIO &ramdisk)
		: sync_params{sync_params}
		, patch_playloader{patch_playloader}
		, plugin_manager{plugin_manager} {
		params.clear();
		metaparams.clear();

		if (!Settings::read_settings(patch_storage, &settings, Volume::NorFlash)) {
			settings = UserSettings{};
			if (!Settings::write_settings(patch_storage, settings, Volume::NorFlash)) {
				pr_err("Failed to write settings file\n");
			}
		}

		patch_playloader.connect_user_settings(&settings);
		patch_playloader.connect_notification_queue(&notify_queue);

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);

		patch_playloader.update_param_catchup_mode();

		ModuleFactory::setModuleDisplayName("HubMedium", "Panel");
	}

	void update_screen() {
		auto now = HAL_GetTick();
		// Set the frame rate here:
		if ((now - last_screen_update_tm) > 16) {
			last_screen_update_tm = now;
			// TODO: dump screen buffer via SPI DMA
		}
	}

	void update_page() {
		auto now = HAL_GetTick();
		// Set the update rate here:
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			read_latest_params();
			handle_file_requests();
			redraw_page();
		}
	}

	void redraw_page() {
		// TODO:
		// Here you can update the screen framebuffer
	}

	void load_initial_patch() {
		if (settings.load_initial_patch) {
			pr_dbg("Loading initial patch '%s' on vol %u\n",
				   settings.initial_patch_name.c_str(),
				   settings.initial_patch_vol);
			patch_playloader.load_initial_patch(settings.initial_patch_name, settings.initial_patch_vol);
		} else {
			pr_dbg("Not loading initial patch (disabled in settings)\n");
		}
	}

	void notify_error(std::string const &message) {
		notify_queue.put({message, Notification::Priority::Error, 2000});
	}

	void preload_plugins() {
		auto preloader = PreLoader{plugin_manager, settings.plugin_preload.slugs};

		if (settings.plugin_preload.slugs.size())
			delay_ms(600); //allow time for ???

		while (true) {
			auto status = preloader.process();

			if (status.message.length()) {
				notify_queue.put({status.message, Notification::Priority::Info, 2000});
			}
		}
	}

	UserSettings &get_settings() {
		return settings;
	}

	NotificationQueue &get_notify_queue() {
		return notify_queue;
	}

private:
	void read_latest_params() {
		// Clear all accumulated knob change events
		for (auto &knob : params.knobs) {
			knob.changed = false;
		}

		// Copy params and metaparams from the audio thread
		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);
	}

	void handle_file_requests() {
		// Handle file save/load requests
		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success) {
			notify_queue.put({load_status.error_string, Notification::Priority::Error, 1500});

		} else if (load_status.error_string.size()) {
			notify_queue.put({load_status.error_string, Notification::Priority::Info, 3000});
		}
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_screen_update_tm = 0;
};

} // namespace MetaModule
