#pragma once
#include "debug.hh"
#include "drivers/fusb302.hh"
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "gui/notify/notification.hh"
#include "gui/pages/page_manager.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"
#include "thorvg.h"

namespace MetaModule
{

class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;
	PluginManager &plugin_manager;

	NotificationQueue notify_queue;
	PageManager page_manager;
	ParamsMidiState params;
	MetaParams metaparams;
	UserSettings settings;
	Screensaver screensaver{settings.screensaver};

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
		, plugin_manager{plugin_manager}
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

		MMDisplay::init(metaparams, screensaver);
		Gui::init_lvgl_styles();
		page_manager.init();

		if (!Settings::read_settings(patch_storage, &settings)) {
			settings = UserSettings{};
			if (!Settings::write_settings(patch_storage, settings)) {
				pr_err("Failed to write settings file\n");
			}
		}

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);
		patch_playloader.set_all_param_catchup_mode(settings.catchup.mode, settings.catchup.allow_jump_outofrange);

		ModuleFactory::setModuleDisplayName("HubMedium", "Panel");

		tvg::Initializer::init(0, tvg::CanvasEngine::Sw);
	}

	void update_screen() {
		auto now = HAL_GetTick();
		if ((now - last_lv_update_tm) > 2) {
			last_lv_update_tm = now;
			lv_timer_handler();
		}
	}

	void update_page() {
		auto now = HAL_GetTick();
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			page_update_task();
		}

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
	}

	TextDisplayWatcher &displays() {
		return params.text_displays;
	}

	bool preload_all_plugins() {
		plugin_manager.start_loading_plugin_list();

		while (true) {
			auto result = plugin_manager.process_loading();

			if (result.state == PluginFileLoader::State::GotList) {
				break;
			}

			if (result.state == PluginFileLoader::State::Error) {
				return false;
			}
		}

		auto list = plugin_manager.found_plugin_list();

		for (auto i = 0u; i < list->size(); ++i) {
			plugin_manager.load_plugin(i);
			auto load = true;
			while (load) {
				switch (plugin_manager.process_loading().state) {
					using enum PluginFileLoader::State;
					case Success:
						load = false;
						break;
					case RamDiskFull:
					case InvalidPlugin:
					case Error:
						return false;
					default:
						continue;
				}
			}
		}

		return true;
	}

	void preload_plugins() {
		lv_show(ui_MainMenuNowPlayingPanel);
		lv_show(ui_MainMenuNowPlaying);

		auto preloader = PreLoader{plugin_manager, settings.plugin_preload};

		if (settings.plugin_preload.slug.size())
			delay_ms(600); //allow time for ???

		while (true) {
			auto status = preloader.process();

			if (status.state == PreLoader::State::Error) {
				notify_queue.put({status.message, Notification::Priority::Error, 2000});
				break;

			} else if (status.state == PreLoader::State::Warning) {
				notify_queue.put({status.message, Notification::Priority::Error, 2000});

			} else if (status.state == PreLoader::State::Done) {
				break;

			} else {
				if (status.message.length()) {
					lv_label_set_text(ui_MainMenuNowPlaying, status.message.c_str());
				}
			}

			update_screen();
			page_manager.handle_notifications();
		}

		lv_label_set_text(ui_MainMenuNowPlaying, "");
		page_manager.init();
	}

	void load_initial_patch() {
		patch_playloader.load_initial_patch(settings.last_patch_opened, settings.last_patch_vol);
	}

	void notify_error(std::string const &message) {
		notify_queue.put({message, Notification::Priority::Error, 2000});
	}

	bool midi_feedback_enabled() const {
		return settings.midi.midi_feedback == MidiSettings::MidiFeedback::Enabled;
	}

	std::atomic<bool> new_patch_data = false;

private:
	void page_update_task() {
		// Clear all accumulated knob change events
		for (auto &knob : params.knobs) {
			knob.changed = false;
		}

		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);

		page_manager.update_current_page();

		new_patch_data.store(false, std::memory_order_release);

		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success) {
			notify_queue.put({load_status.error_string, Notification::Priority::Error, 1500});

		} else if (load_status.error_string.size()) {
			notify_queue.put({load_status.error_string, Notification::Priority::Info, 3000});
		}
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_lv_update_tm = 0;
};

} // namespace MetaModule
