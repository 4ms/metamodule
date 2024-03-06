#pragma once
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
					_load_patch();
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
		stopping_audio_ = true;
	}

	void start_audio() {
	}

	// loading_new_patch_:
	// UI thread WRITE
	// Audio thread READ
	void request_load_view_patch() {
		loading_new_patch_ = true;
	}

	bool should_fade_down_audio() {
		return loading_new_patch_ || stopping_audio_;
	}

	// UI thread READ (KnobEditPage, ModuleViewPage)
	// UI thread WRITE (via handle_sync_patch_loading() => _load_patch())
	PatchLocHash cur_patch_loc_hash() {
		return loaded_patch_loc_hash;
	}

	auto cur_patch_name() {
		return loaded_patch_name_;
	}

	// Audio thread WRITE
	// Audio thread READ
	// UI thread READ (via handle_sync_patch_loading())
	void notify_audio_is_muted() {
		audio_is_muted_ = true;
	}
	void audio_not_muted() {
		audio_is_muted_ = false;
	}

	bool ready_to_play() {
		return !stopping_audio_ && !audio_is_muted_ && player_.is_loaded;
	}

	// Concurrency: Called from UI thread
	Result handle_sync_patch_loading() {
		if (loading_new_patch_ && audio_is_muted_) {
			auto result = _load_patch();
			loading_new_patch_ = false;
			return result;
		}
		return {true, ""};
	}

private:
	PatchPlayer &player_;
	FileStorageProxy &storage_;

	std::atomic<bool> loading_new_patch_ = false;
	std::atomic<bool> audio_is_muted_ = false;
	std::atomic<bool> stopping_audio_ = false;

	PatchLocHash loaded_patch_loc_hash;
	ModuleTypeSlug loaded_patch_name_ = "";

	Result _load_patch() {
		auto &patch = storage_.get_view_patch();
		auto vol = storage_.get_view_patch_vol();

		pr_trace("Attempting play patch from vol %d: %.31s\n", (uint32_t)vol, patch.patch_name.data());

		auto result = player_.load_patch(patch);
		if (result.success) {
			loaded_patch_loc_hash = PatchLocHash(storage_.get_view_patch_filename(), vol);
			loaded_patch_name_ = patch.patch_name;
		}

		return result;
	}
};
} // namespace MetaModule
