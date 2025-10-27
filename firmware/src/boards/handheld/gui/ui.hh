#pragma once
#include "drivers/fusb302.hh"
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "general_io.hh"
#include "gui/pages/page_manager.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"
#include "user_settings/settings.hh"
#include "user_settings/settings_file.hh"

namespace MetaModule
{

extern std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height> *first_framebuf;
extern std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height> *second_framebuf;

class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;
	PluginManager &plugin_manager;
	FileStorageProxy &file_storage_proxy;
	NotificationQueue notify_queue;

	PageManager page_manager;

	ParamsState params;
	MetaParams metaparams;
	UserSettings settings;

	Screensaver screensaver{settings.screensaver};

public:
	Ui(PatchPlayLoader &patch_playloader,
	   FileStorageProxy &file_storage_proxy,
	   OpenPatchManager &open_patch_manager,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue,
	   PluginManager &plugin_manager,
	   FatFileIO &ramdisk)
		: sync_params{sync_params}
		, patch_playloader{patch_playloader}
		, plugin_manager{plugin_manager}
		, file_storage_proxy{file_storage_proxy}
		, page_manager{file_storage_proxy,
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

		MMDisplay::init(metaparams, screensaver, *first_framebuf);

		Gui::init_lvgl_styles();

		if (!Settings::read_settings(file_storage_proxy, &settings)) {
			settings = UserSettings{};
			if (!Settings::write_settings(file_storage_proxy, settings)) {
				pr_err("Failed to write settings file\n");
			}
		}

		settings.last_patch_vol = Volume::USB;
		settings.last_patch_opened = "/patch.yml";

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);
		patch_playloader.set_all_param_catchup_mode(settings.catchup.mode, settings.catchup.allow_jump_outofrange);

		ModuleFactory::setModuleDisplayName("HubMedium", "Panel");

		auto d = lv_obj_create(nullptr);
		lv_obj_set_style_bg_color(d, lv_color_hex(0x3377AA), 0);
		lv_obj_set_style_bg_opa(d, LV_OPA_100, 0);
		lv_scr_load(d);
	}

	// uint32_t pat = 0;
	// bool first_buf = false;
	void update_screen() {
		auto now = HAL_GetTick();
		if ((now - last_screen_update_tm) > 3) {
			last_screen_update_tm = now;
			lv_timer_handler();
		}
	}

	void read_patch_gui_elements() {
	}

	void update_page() {
		auto now = HAL_GetTick();
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			page_update_task();
		}

		// print_dbg_params.output_debug_info(HAL_GetTick());
		// print_dbg_params.output_load(HAL_GetTick());
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
		if (FS::file_size(file_storage_proxy, {"preload_all_plugins", Volume::SDCard}) ||
			FS::file_size(file_storage_proxy, {"preload_all_plugins", Volume::USB}))
		{
			pr_info("Preloading all plugins\n");
			preload_all_plugins();
		} else {

			auto preloader = PreLoader{plugin_manager, settings.plugin_preload};

			if (settings.plugin_preload.slug.size())
				delay_ms(600); //allow time for ???

			while (true) {
				auto status = preloader.process();

				if (status.state == PreLoader::State::Error) {
					break;

				} else if (status.state == PreLoader::State::Warning) {
					// continue

				} else if (status.state == PreLoader::State::Done) {
					break;

				} else {
					if (status.message.length()) {
						printf("%s\n", status.message.c_str());
					}
				}
			}
		}
	}

	void load_initial_patch() {
		patch_playloader.load_initial_patch(settings.last_patch_opened, settings.last_patch_vol);
	}

	void notify_error(std::string const &message) {
		printf("%s\n", message.c_str());
	}

	void notify_now_playing(std::string const &message) {
		printf("%s\n", message.c_str());
	}

	std::atomic<bool> new_patch_data = false;

private:
	void page_update_task() {
		// Clear all accumulated knob change events
		// for (auto &knob : params.knobs) {
		// 	knob.changed = false;
		// }

		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);

		page_manager.update_current_page();

		new_patch_data.store(false, std::memory_order_release);

		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success || load_status.error_string.length()) {
			printf("%s\n", load_status.error_string.c_str());
		}
	}

	uint32_t last_page_update_tm = 0;
	uint32_t last_screen_update_tm = 0;
};

} // namespace MetaModule
