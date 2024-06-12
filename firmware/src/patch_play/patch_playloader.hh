#pragma once
#include "CoreModules/modules_helpers.hh"
#include "delay.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/patch_location.hh"
#include "patch_play/patch_player.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include <atomic>

namespace MetaModule
{

// PatchLoader handles loading of patches from storage into PatchPlayer
struct PatchPlayLoader {
	PatchPlayLoader(FileStorageProxy &patch_storage, PatchPlayer &patchplayer)
		: player_{patchplayer}
		, storage_{patch_storage} {
	}

	void load_initial_patch() {
		uint32_t tries = 10000;

		while (--tries) {
			if (storage_.request_load_patch({"SlothDrone.yml", Volume::NorFlash}))
				break;
		}
		if (tries == 0) {
			pr_err("ERROR: sending request to load initial patch timed out.\n");
			return;
		}

		tries = 2000;
		while (--tries) {
			auto message = storage_.get_message();

			if (message.message_type == FileStorageProxy::PatchDataLoaded) {
				if (!storage_.parse_loaded_patch(message.bytes_read))
					pr_err("ERROR: could not parse initial patch\n");
				else
					load_patch();
				break;
			}
			if (message.message_type == FileStorageProxy::PatchDataLoadFail) {
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
	}

	void request_load_view_patch() {
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
	void notify_audio_not_muted() {
		starting_audio_ = false;
		audio_is_muted_ = false;
	}

	bool is_audio_muted() {
		return audio_is_muted_;
	}

	bool ready_to_play() {
		return !audio_is_muted_ && player_.is_loaded;
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

		auto *patch = storage_.get_view_patch();
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

		start_audio();
	}

private:
	PatchPlayer &player_;
	FileStorageProxy &storage_;

	std::atomic<bool> loading_new_patch_ = false;
	std::atomic<bool> audio_is_muted_ = false;
	std::atomic<bool> stopping_audio_ = false;
	std::atomic<bool> starting_audio_ = false;
	std::atomic<bool> saving_patch_ = false;
	std::atomic<bool> should_save_patch_ = false;

	Result save_patch() {
		storage_.update_view_patch_module_states(player_.get_module_states());

		if (auto res = storage_.write_patch(); res == FileStorageProxy::WriteResult::Success) {
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

		if (msg.message_type == FileStorageProxy::PatchDataWriteFail) {
			saving_patch_ = false;
			return {false, "Failed to write patch."};

		} else if (msg.message_type == FileStorageProxy::PatchDataWriteOK) {
			saving_patch_ = false;
			return {true, "Saved"};

		} else {
			return {true, ""};
		}
	}

	Result load_patch() {
		auto patch = storage_.get_view_patch();
		auto vol = storage_.get_view_patch_vol();

		pr_trace("Attempting play patch from vol %d: %.31s\n", (uint32_t)vol, patch->patch_name.data());

		auto result = player_.load_patch(*patch);
		if (result.success) {
			storage_.play_view_patch();
			start_audio();
		}

		return result;
	}
};
} // namespace MetaModule
