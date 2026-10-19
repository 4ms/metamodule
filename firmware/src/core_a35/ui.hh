#pragma once
#include "console_keys.hh"
#include "dynload/plugin_manager.hh"
#include "gui/elements/screensaver.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_manager.hh"
#include "lvgl_display.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_playloader.hh"
#include "sync_params.hh"
#include "thorvg.h"
#include "user_settings/settings_file.hh"

namespace MetaModule
{

// MP2's version of MP1's Ui (gui/ui.hh): the GUI pages and their state.
// No USB or jack sense monitors yet. Input is from the serial console keys (console_keys.hh).
class Ui {
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;

	NotificationQueue notify_queue;
	ParamsMidiState params;
	MetaParams metaparams;
	UserSettings settings;
	Screensaver screensaver{settings.screensaver};
	PageManager page_manager;
	ConsoleKeys keys;

public:
	Ui(LvglDisplay &display,
	   SyncParams &sync_params,
	   PatchPlayLoader &patch_playloader,
	   FileStorageProxy &patch_storage,
	   OpenPatchManager &open_patch_manager,
	   PatchModQueue &patch_mod_queue,
	   PluginManager &plugin_manager,
	   FatFileIO &ramdisk)
		: sync_params{sync_params}
		, patch_playloader{patch_playloader}
		, page_manager{patch_storage,
					   open_patch_manager,
					   patch_playloader,
					   params,
					   metaparams,
					   notify_queue,
					   patch_mod_queue,
					   plugin_manager,
					   settings,
					   screensaver,
					   ramdisk} {
		params.clear();
		metaparams.clear();

		display.connect_input(metaparams, screensaver);
		Gui::init_lvgl_styles();

		if (!Settings::read_settings(patch_storage, &settings, Volume::NorFlash)) {
			pr_err("Could not read settings file: running with defaults, leaving the file alone\n");
			settings = UserSettings{};
		}

		patch_playloader.connect_user_settings(&settings);
		patch_playloader.connect_notification_queue(&notify_queue);

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);

		patch_playloader.update_param_catchup_mode();

		tvg::Initializer::init(0, tvg::CanvasEngine::Sw);
	}

	void start() {
		page_manager.init();

		if (settings.load_initial_patch) {
			pr_dbg("Loading initial patch '%s' on vol %u\n",
				   settings.initial_patch_name.c_str(),
				   settings.initial_patch_vol);
			patch_playloader.load_initial_patch(settings.initial_patch_name, settings.initial_patch_vol);
		}
	}

	void update() {
		keys.poll();

		auto now = lv_tick_get();
		if (now - last_lv_update_tm >= 2) {
			last_lv_update_tm = now;
			lv_timer_handler();
		}

		if (now - last_page_update_tm >= 16) {
			last_page_update_tm = now;
			page_update_task();
		}
	}

	void notify_error(std::string const &message) {
		notify_queue.put({message, Notification::Priority::Error, 2000});
	}

	UserSettings &get_settings() {
		return settings;
	}

	NotificationQueue &get_notify_queue() {
		return notify_queue;
	}

private:
	uint32_t last_page_update_tm = 0;
	uint32_t last_lv_update_tm = 0;

	// Same as MP1, minus the USB and jack sense monitors
	void page_update_task() {
		// Clear all accumulated knob change events
		for (auto &knob : params.knobs)
			knob.changed = false;

		sync_params.read_sync(params, metaparams);
		keys.update(metaparams);

		page_manager.update_current_page();

		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success) {
			notify_queue.put({load_status.error_string, Notification::Priority::Error, 1500});

		} else if (load_status.error_string.size()) {
			notify_queue.put({load_status.error_string, Notification::Priority::Status, 1500});
		}

		patch_playloader.update_rebalance_trials(lv_tick_get());
	}
};

} // namespace MetaModule
