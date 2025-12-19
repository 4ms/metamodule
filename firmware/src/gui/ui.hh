#pragma once
#include "board/display.hh"
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "general_io.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings.hh"
#include "user_settings/settings_file.hh"

namespace MetaModule
{

class Ui {
private:
	SyncParams &sync_params;
	PatchPlayLoader &patch_playloader;
	PluginManager &plugin_manager;
	FileStorageProxy &file_storage_proxy;

	ParamsState param_state;
	UserSettings settings;
	NotificationQueue notify_queue;

	Mousai::Display display;
	// 1-bit per pixel:
	using FrameBufferT = std::array<uint8_t, Mousai::ScreenBufferConf::width * Mousai::ScreenBufferConf::height / 8>;
	static inline FrameBufferT framebuf alignas(64);

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
		, file_storage_proxy{file_storage_proxy} {
		param_state.clear();

		if (!Settings::read_settings(file_storage_proxy, &settings)) {
			settings = UserSettings{};
			if (!Settings::write_settings(file_storage_proxy, settings)) {
				pr_err("Failed to write settings file\n");
			}
		}

		settings.initial_patch_vol = Volume::SDCard;
		settings.initial_patch_name = "/patch.yml";

		patch_playloader.connect_user_settings(&settings);

		patch_playloader.request_new_audio_settings(
			settings.audio.sample_rate, settings.audio.block_size, settings.audio.max_overrun_retries);

		// patch_playloader.set_all_param_catchup_mode(settings.catchup.mode, settings.catchup.allow_jump_outofrange);

		ModuleFactory::setModuleDisplayName("HubMedium", "Panel");
	}

	void update_screen() {
		// Here you can draw into the frame buffer
		if (display.is_ready()) {
			// Fill it with a 50% grey pattern
			for (auto &pix8 : framebuf)
				pix8 = 0xAA;

			display.flush_screen(framebuf);
		}
	}

	void handle_event() {
		// Here you can respond to parameter, encoder, and other UI events.
		//
		// Note these are events, so reading their value consumes the events.
		// E.g.:
		// use_motion() returns the accumulated motion of the encoder and resets it to 0
		// did_change() clears the changed flag
		// is_just_pressed/released() clears the pressed/released flag

		// To save CPU load, if any of these fields are not needed, remove them from ParamsState
		// and from AudioStream (where the values are being set)

		// Encoders
		auto enc0 = param_state.encoder[0].use_motion();
		if (enc0 != 0)
			printf("Encoder 1: %d\n", (int)enc0);

		auto enc1 = param_state.encoder[1].use_motion();
		if (enc1 != 0)
			printf("Encoder 2: %d\n", (int)enc1);

		// Knobs/CV
		for (auto i = 0u; i < param_state.knobs.size(); i++) {
			if (param_state.knobs[i].did_change()) {
				printf("Knob[%d] => %f\n", i, param_state.knobs[i].val);
			}
		}

		for (auto i = 0u; i < param_state.cvs.size(); i++) {
			if (param_state.cvs[i].did_change()) {
				printf("CV[%d] => %f\n", i, param_state.cvs[i].val);
			}
		}

		// Buttons/Gate jacks
		for (auto i = 0u; i < param_state.buttons.size(); i++) {
			if (param_state.buttons[i].is_just_pressed())
				printf("Button %d pressed\n", i);
			if (param_state.buttons[i].is_just_released())
				printf("Button %d released\n", i);
		}

		for (auto i = 0u; i < param_state.gate_ins.size(); i++) {
			if (param_state.gate_ins[i].is_just_pressed())
				printf("Gate %d high\n", i);
			if (param_state.gate_ins[i].is_just_released())
				printf("Gate %d low\n", i);
		}

		for (auto i = 0u; i < param_state.midi_ccs.size(); i++) {
			if (param_state.midi_ccs[i].changed) {
				param_state.midi_ccs[i].changed = false;
				printf("MIDI CC%d => %d\n", i, param_state.midi_ccs[i].val);
			}
		}
	}

	void update_gui() {
		// Throttle updates to every 16ms
		auto now = HAL_GetTick();
		if ((now - last_page_update_tm) > 16) {
			last_page_update_tm = now;
			read_param_state();
			handle_file_events();
			update_screen();
		}
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

			auto preloader = PreLoader{plugin_manager, settings.plugin_preload.slugs};

			if (settings.plugin_preload.slugs.size())
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
		patch_playloader.load_initial_patch(settings.initial_patch_name, settings.initial_patch_vol);
	}

	void notify_error(std::string const &message) {
		printf("%s\n", message.c_str());
	}

	void notify_now_playing(std::string const &message) {
		printf("%s\n", message.c_str());
	}

	void read_patch_gui_elements() {
	}

	auto &get_settings() {
		return settings;
	}

	auto &get_notify_queue() {
		return notify_queue;
	}

private:
	void read_param_state() {
		// Clear all accumulated knob change events
		for (auto &knob : param_state.knobs) {
			knob.changed = false;
		}

		[[maybe_unused]] bool read_ok = sync_params.read_sync(param_state);
	}

	void handle_file_events() {
		auto load_status = patch_playloader.handle_file_events();
		if (!load_status.success || load_status.error_string.length()) {
			printf("%s\n", load_status.error_string.c_str());
		}
	}

	uint32_t last_page_update_tm = 0;
};

} // namespace MetaModule
