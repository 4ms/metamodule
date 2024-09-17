#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "dynload/autoload_plugins.hh"
#include "dynload/plugin_manager.hh"
#include "gui/notify/notification.hh"
#include "gui/pages/page_manager.hh"
#include "params/params.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"
#include "user_settings/plugin_autoload_settings.hh"

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

	ParamDbgPrint print_dbg_params{params, metaparams};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   FileStorageProxy &patch_storage,
	   OpenPatchManager &open_patch_manager,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue,
	   PluginManager &plugin_manager)
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
					   settings} {

		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams);
		Gui::init_lvgl_styles();
		page_manager.init();

		if (!Settings::read_settings(patch_storage, &settings)) {
			settings = UserSettings{};
			if (!Settings::write_settings(patch_storage, settings)) {
				pr_err("Failed to write settings file\n");
			}
		}

		patch_playloader.request_new_audio_settings(settings.audio.sample_rate, settings.audio.block_size);
	}

	void update() {

		auto now = HAL_GetTick();
		if ((now - last_lv_update_tm) > 2) {
			last_lv_update_tm = now;
			lv_timer_handler();
		}

		now = HAL_GetTick();
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			page_update_task();
		}

		// Uncomment to enable:
		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
	}

	LightWatcher &lights() {
		return params.lights;
	}

	void autoload_plugins() {
		constexpr std::array<std::string_view, 4> dots{"", ".", "..", "..."};
		uint8_t dot_i = 0;

		lv_show(ui_MainMenuLastViewedPanel);
		lv_label_set_text(ui_MainMenuLastViewed, "Please Wait");

		auto autoloader = AutoLoader{plugin_manager, settings.plugin_autoload};

		while (true) {
			auto status = autoloader.process();

			if (status.state == AutoLoader::State::Error) {
				notify_queue.put({status.message, Notification::Priority::Error, 2000});
				break;

			} else if (status.state == AutoLoader::State::Done) {
				break;

			} else {
				if (status.message.length()) {
					lv_label_set_text(ui_MainMenuNowPlaying, status.message.c_str());
					pr_dbg("msg: %s\n", status.message.c_str());
				}
			}

			auto now = HAL_GetTick();
			if ((now - last_lv_update_tm) > 2) {
				last_lv_update_tm = now;
				lv_label_set_text(ui_MainMenuLastViewedName, dots[dot_i >> 6].data());
				dot_i++;
				lv_timer_handler();
			}
		}

		page_manager.init();
	}

	TextDisplayWatcher &displays() {
		return params.displays;
	}

	void load_initial_patch() {
		patch_playloader.load_initial_patch(settings.last_patch_opened, settings.last_patch_vol);
	}

	bool new_patch_data = false;

private:
	void page_update_task() {
		//This returns false when audio stops
		//TODO: if (!read_ok) ... restart audio
		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);

		page_manager.update_current_page();

		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success) {
			notify_queue.put({load_status.error_string, Notification::Priority::Error, 1500});

		} else if (load_status.error_string.size()) {
			notify_queue.put({load_status.error_string, Notification::Priority::Info, 3000});
		}

		new_patch_data = false;
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_lv_update_tm = 0;
};

} // namespace MetaModule
