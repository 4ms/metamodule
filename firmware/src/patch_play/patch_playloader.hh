#pragma once
#include "calibrate/calibration_patch.hh"
#include "delay.hh"
#include "modules_helpers.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "patch_play/patch_player.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include <atomic>

size_t get_heap_size();

namespace MetaModule
{

// PatchLoader handles loading of patches from storage into PatchPlayer
struct PatchPlayLoader {
	PatchPlayLoader(FileStorageProxy &patch_storage, OpenPatchManager &patches, PatchPlayer &patchplayer)
		: player_{patchplayer}
		, storage_{patch_storage}
		, patches_{patches} {
	}

	void load_initial_patch(std::string_view patchname, Volume patch_vol) {
		uint32_t tries = 10000;

		if (patchname.length() == 0) {
			patchname = "/SlothDrone.yml";
			patch_vol = Volume::NorFlash;
		}

		PatchLocation initial_patch_loc{patchname, patch_vol};
		while (--tries) {
			if (storage_.request_load_patch(initial_patch_loc))
				break;
		}
		if (tries == 0) {
			pr_err("ERROR: sending request to load initial patch timed out.\n");
			return;
		}

		tries = 2000;
		while (--tries) {
			auto message = storage_.get_message();

			if (message.message_type == FileStorageProxy::LoadFileOK) {
				auto raw_patch_file = storage_.get_patch_data(message.bytes_read);
				if (!patches_.open_patch(raw_patch_file, initial_patch_loc))
					pr_err("ERROR: could not parse initial patch\n");
				else {
					next_patch = patches_.get_view_patch();
					load_patch();
				}

				break;
			}
			if (message.message_type == FileStorageProxy::LoadFileFailed) {
				pr_err("ERROR: initial patch failed to load from NOR flash\n");
				break;
			}

			delay_ms(1);
		}
		if (tries == 0) {
			pr_err("ERROR: timed out while waiting for response to request to load initial patch.\n");
			return;
		}
	}

	void stop_audio() {
		starting_audio_ = false;
		stopping_audio_ = true;
	}

	void start_audio() {
		audio_is_muted_ = false;
		starting_audio_ = true;
		stopping_audio_ = false;
		clear_audio_overrun();
	}

	void request_load_view_patch() {
		next_patch = patches_.get_view_patch();
		loading_new_patch_ = true;
	}

	void request_load_calibration_patch() {
		next_patch = calibration.make_cal_patch();
		loading_new_patch_ = true;
	}

	void request_load_cal_check_patch() {
		next_patch = calibration.make_check_patch();
		loading_new_patch_ = true;
	}

	void request_load_hardware_check_patch() {
		next_patch = calibration.make_hardware_check_patch();
		loading_new_patch_ = true;
	}

	void request_reload_playing_patch() {
		next_patch = patches_.get_playing_patch();
		loading_new_patch_ = true;
	}

	bool should_fade_down_audio() {
		return loading_new_patch_ || stopping_audio_;
	}

	bool should_fade_up_audio() {
		return starting_audio_;
	}

	void notify_audio_is_muted() {
		stopping_audio_ = false;
		audio_is_muted_ = true;
	}

	void notify_audio_overrun() {
		notify_audio_is_muted();
		audio_overrun_ = true;
	}

	void notify_audio_not_muted() {
		starting_audio_ = false;
		audio_is_muted_ = false;
	}

	bool is_audio_muted() {
		return audio_is_muted_;
	}

	bool is_playing() {
		return !audio_is_muted_ && player_.is_loaded;
	}

	bool did_audio_overrun() {
		return audio_overrun_;
	}

	void clear_audio_overrun() {
		audio_overrun_ = false;
	}

	// Concurrency: Called from UI thread
	Result handle_file_events() {
		if (loading_new_patch_ && audio_is_muted_) {
			auto result = load_patch();
			loading_new_patch_ = false;
			return result;
		}

		if (should_save_patch_) {
			return save_patch();
		}
		if (saving_patch_) {
			return check_save_patch_status();
		}

		return {true, ""};
	}

	void request_save_patch() {
		should_save_patch_ = true;
	}

	void load_module(std::string_view slug) {
		stop_audio();
		while (!is_audio_muted())
			;

		player_.add_module(slug);

		auto *patch = patches_.get_view_patch();
		uint16_t module_id = patch->add_module(slug);
		auto info = ModuleFactory::getModuleInfo(slug);

		// Set params to default values
		for (unsigned i = 0; auto const &element : info.elements) {
			if (auto def_val = get_normalized_default_value(element); def_val.has_value()) {
				auto param_id = info.indices[i].param_idx;
				patch->set_or_add_static_knob_value(module_id, param_id, def_val.value());
				player_.apply_static_param({.module_id = module_id, .param_id = param_id, .value = def_val.value()});
			}
			i++;
		}

		pr_info("Heap: %u\n", get_heap_size());
		start_audio();
	}

	void remove_module(unsigned module_id) {
		stop_audio();
		while (!is_audio_muted())
			;

		player_.remove_module(module_id);

		pr_info("Heap: %u\n", get_heap_size());
		start_audio();
	}

	void prepare_remove_plugin(std::string_view brand_slug) {
		auto playing_patch = patches_.get_playing_patch();
		if (!playing_patch)
			return;

		bool patch_contains_brand = false;

		std::string brand_prefix = std::string(brand_slug) + ":";
		for (std::string_view module_slug : playing_patch->module_slugs) {
			if (module_slug.starts_with(brand_prefix)) {
				patch_contains_brand = true;
				break;
			}
		}

		if (patch_contains_brand) {
			pr_dbg("Currently playing patch contains a module in the plugin to be removed. Stopping\n");
			stop_audio();
			while (!is_audio_muted())
				;
			player_.unload_patch();
			patches_.close_playing_patch();
		}
	}

	struct AudioSettings {
		//TODO put defaults in one place
		uint32_t sample_rate = 48000;
		uint32_t block_size = 64;
	};

	void request_new_audio_settings(uint32_t sample_rate, uint32_t block_size) {
		new_audio_settings_.store(AudioSettings{sample_rate, block_size});
	}

	AudioSettings get_audio_settings() {
		return new_audio_settings_.load();
	}

private:
	PatchPlayer &player_;
	FileStorageProxy &storage_;
	OpenPatchManager &patches_;

	PatchData *next_patch = nullptr;
	CalibrationPatch calibration;

	std::atomic<bool> loading_new_patch_ = false;
	std::atomic<bool> audio_is_muted_ = false;
	std::atomic<bool> stopping_audio_ = false;
	std::atomic<bool> starting_audio_ = false;
	std::atomic<bool> saving_patch_ = false;
	std::atomic<bool> should_save_patch_ = false;
	std::atomic<bool> audio_overrun_ = false;

	std::atomic<AudioSettings> new_audio_settings_ = {};

	Result save_patch() {
		auto view_patch = patches_.get_view_patch();

		if (view_patch == patches_.get_playing_patch())
			patches_.update_view_patch_module_states(player_.get_module_states());

		std::span<char> filedata = storage_.get_patch_data();
		patch_to_yaml_buffer(*view_patch, filedata);

		auto res =
			storage_.request_write_file(filedata, patches_.get_view_patch_vol(), patches_.get_view_patch_filename());

		if (res == FileStorageProxy::WriteResult::Success) {
			should_save_patch_ = false;
			saving_patch_ = true;
			return {true, "Saving..."};

		} else if (res == FileStorageProxy::WriteResult::Busy) {
			// message system is busy, try again next time
			return {true, ""};

		} else {
			// error with filename or volume, do not retry
			should_save_patch_ = false;
			saving_patch_ = false;
			return {false, "File name or volume invalid"};
		}
	}

	Result check_save_patch_status() {
		auto msg = storage_.get_message();

		if (msg.message_type == FileStorageProxy::WriteFileFail) {
			saving_patch_ = false;
			return {false, "Failed to write patch."};

		} else if (msg.message_type == FileStorageProxy::WriteFileOK) {
			saving_patch_ = false;
			patches_.reset_view_patch_modification_count();
			return {true, "Saved"};

		} else {
			return {true, ""};
		}
	}

	Result load_patch() {
		if (!next_patch) {
			pr_err("Internal error loading patch\n");
			return {false, "Internal error loading patch"};
		}

		pr_trace("Attempting play patch: %.31s\n", next_patch->patch_name.data());

		auto result = player_.load_patch(*next_patch);
		if (result.success) {
			pr_info("Heap: %u\n", get_heap_size());
			if (next_patch == patches_.get_view_patch())
				patches_.play_view_patch();

			//TODO: give patches a ptr to this patch?
			start_audio();
		}

		return result;
	}
};
} // namespace MetaModule
