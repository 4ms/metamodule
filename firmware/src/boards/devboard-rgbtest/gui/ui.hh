#pragma once
#include "drivers/fusb302.hh"
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "params/params_dbg_print.hh"
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

class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;
	PluginManager &plugin_manager;

	ParamsMidiState params;
	MetaParams metaparams;
	UserSettings settings;

	ParamDbgPrint print_dbg_params{params, metaparams};
	Screensaver screensaver{settings.screensaver};

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

		MMDisplay::init(metaparams, screensaver, *first_framebuf);

		if (!Settings::read_settings(patch_storage, &settings)) {
			settings = UserSettings{};
			if (!Settings::write_settings(patch_storage, settings)) {
				pr_err("Failed to write settings file\n");
			}
		}

		// settings.last_patch_vol = Volume::NorFlash;
		// settings.last_patch_opened = "/West_Coast_FM_Madness.yml";
		settings.last_patch_vol = Volume::SDCard;
		settings.last_patch_opened = "sdc:/patch.yml";

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);
		patch_playloader.set_all_param_catchup_mode(settings.catchup.mode, settings.catchup.allow_jump_outofrange);

		ModuleFactory::setModuleDisplayName("HubMedium", "Panel");
	}

	uint32_t pat = 1;
	void update_screen() {
		auto now = HAL_GetTick();
		if ((now - last_screen_update_tm) > 200) {
			MMDisplay::test_pattern(pat, *first_framebuf);
			pat = (pat + 1) % 3;
			last_screen_update_tm = now;
		}
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
		for (auto &knob : params.knobs) {
			knob.changed = false;
		}

		[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);

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
