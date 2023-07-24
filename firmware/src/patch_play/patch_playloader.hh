#pragma once
#include "patch_play/patch_player.hh"
#include "printf.h"

#ifdef SIMULATOR
// #include "uart_log.hh" //doesn't work with simulator because uart_log.hh exists in same dir as this file, so preprocessor picks ./uart_log.hh it instead of stubs/uart_log.hh
#include "stubs/patch_file/patch_storage_proxy.hh"
#else
#include "patch_file/patch_storage_proxy.hh"
#endif

//FIXME: temp use patches_default instead of patch_storage
#include "patch_file/patches_default.hh"

namespace MetaModule
{

// PatchLoader handles loading of patches from storage into PatchPlayer
struct PatchPlayLoader {
	PatchPlayLoader(PatchStorageProxy &patch_storage, PatchPlayer &patchplayer)
		: player_{patchplayer}
		, storage_{patch_storage} {
	}

	void load_initial_patch() {
		// TODO:this loads a default patch, not a patch from NOR Flash
		// Instead, we should load the last patch that was loaded before power-down

		auto initial_patch = 11;
		// TODO: Test the below.. do we need an escape hatch
		// to avoid infinite loop?

		// while (!storage_.request_viewpatch(initial_patch))
		// 	;
		// InterCoreCommMessage msg;
		// while (msg = storage_.get_message(); msg.message_type != InterCoreCommMessage::None)
		// ;
		// if (msg.message_type == InterCoreCommMessage::PatchFailedLoad)
		// .... try another patch?
		//
		// if (_load_patch()) {
		if (_load_default_patch(initial_patch)) {
			printf_("Loaded default patch\n");
			loading_new_patch_ = false;
		} else
			printf_("FAILED to load initial patch.\n");
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
		PatchData &patch = storage_.get_view_patch();
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

	bool _load_default_patch(uint32_t patchid) {
		if (patchid >= DefaultPatches::num_patches())
			patchid = 0;

		auto rawpatch = DefaultPatches::get_patch(patchid);

		PatchData patch;
		yaml_raw_to_patch(rawpatch, patch);
		auto patchname = patch.patch_name;
		printf_("Attempting play patch #%d, %s\n", patchid, patchname.data());

		if (player_.load_patch(patch)) {
			loaded_patch_index_ = patchid;
			return true;
		}
		return false;
	}
};
} // namespace MetaModule
