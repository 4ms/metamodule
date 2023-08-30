#pragma once
#include "patch_file/patch_storage_proxy.hh"
#include "patch_play/patch_player.hh"
#include "printf.h"

namespace MetaModule
{

// PatchLoader handles loading of patches from storage into PatchPlayer
struct PatchPlayLoader {
	PatchPlayLoader(PatchStorageProxy &patch_storage, PatchPlayer &patchplayer)
		: player_{patchplayer}
		, storage_{patch_storage} {
	}

	void load_initial_patch() {
		// TODO: load the last patch that was loaded before power-down
		auto initial_patch = 0;

		uint32_t tries = 10000;
		while (--tries) {
			if (storage_.request_viewpatch(Volume::NorFlash, initial_patch))
				break;
		}
		if (tries == 0) {
			pr_err("ERROR: sending request to load initial patch timed out.\n");
			return;
		}

		tries = 200000;
		while (--tries) {
			auto message = storage_.get_message();

			if (message.message_type == PatchStorageProxy::PatchDataLoaded) {
				if (!storage_.parse_view_patch(message.bytes_read))
					pr_err("ERROR: could not parse initial patch\n");
				else
					_load_patch();
				break;
			}
			if (message.message_type == PatchStorageProxy::PatchDataLoadFail) {
				pr_err("ERROR: initial patch failed to load from NOR flash\n");
				break;
			}
		}
		if (tries == 0) {
			pr_err("ERROR: timed out while waiting for response to request to load initial patch.\n");
			return;
		}
	}

	// loading_new_patch_:
	// UI thread WRITE
	// Audio thread READ
	void request_load_view_patch() {
		loading_new_patch_ = true;
	}

	bool is_loading_new_patch() {
		return loading_new_patch_;
	}

	// loaded_patch_index_:
	// UI thread READ (KnobEditPage, ModuleViewPage)
	// UI thread WRITE (via handle_sync_patch_loading() => _load_patch())
	uint32_t cur_patch_index() {
		return loaded_patch_index_;
	}

	// audio_is_muted_:
	// Audio thread WRITE
	// Audio thread READ
	// UI thread READ (via handle_sync_patch_loading())
	void audio_is_muted() {
		audio_is_muted_ = true;
	}
	void audio_not_muted() {
		audio_is_muted_ = false;
	}
	bool is_audio_muted() {
		return audio_is_muted_;
	}

	// Concurrency: Called from UI thread
	void handle_sync_patch_loading() {
		if (is_loading_new_patch() && is_audio_muted()) {
			if (_load_patch())
				printf_("Patch loaded\n");
			else
				printf_("Failed to load patch!\n");

			loading_new_patch_ = false;
		}
	}

private:
	PatchPlayer &player_;
	PatchStorageProxy &storage_;

	bool loading_new_patch_ = false;
	bool audio_is_muted_ = false;

	uint32_t loaded_patch_index_;
	Volume loaded_patch_vol_;

	bool _load_patch() {
		auto patch = storage_.get_view_patch();
		auto patchid = storage_.get_view_patch_id();
		auto vol = storage_.get_view_patch_vol();

		printf_("Attempting play patch #%d from vol %d, %.31s\n", patchid, (uint32_t)vol, patch.patch_name.data());

		if (patch.module_slugs.size() > 1) {
			if (player_.load_patch(patch)) {
				loaded_patch_index_ = patchid;
				loaded_patch_vol_ = vol;
				return true;
			}
		}
		return false;
	}
};
} // namespace MetaModule
