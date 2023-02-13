#pragma once
#include "patch_player.hh"
#include "patch_storage.hh"
#include "patchlist.hh"
// #include "uart_log.hh" //doesn't work with simulator because uart_log.hh exists in same dir as this file, so preprocessor picks ./uart_log.hh it instead of stubs/uart_log.hh
#include "printf.h"

namespace MetaModule
{

// PatchLoader handles loading of patches into PatchPlayer
// TODO: Better name so its not confused with loading a patch from SD Card or USB?
// => PatchPlayLoader
struct PatchPlayLoader {
	static inline uint32_t initial_patch = 8;

	PatchPlayLoader(PatchList &patchlist, PatchPlayer &patchplayer, PatchStorage &patchstorage)
		: patch_list_{patchlist}
		, player_{patchplayer}
		, storage_{patchstorage} {
	}

	void load_initial_patch() {
		if (_load_patch(initial_patch)) {
			printf_("Loaded initial_patch\n");
			loaded_patch_index_ = initial_patch;
			loading_new_patch_ = false;
		} else
			printf_("Failed to load initial patch\n");
	}

	uint32_t cur_patch_index() {
		return loaded_patch_index_;
	}

	void request_load_patch(uint32_t patch_id) {
		if (patch_id != new_patch_index_) {
			new_patch_index_ = patch_id;
			loading_new_patch_ = true;
		}
	}

	bool is_loading_new_patch() {
		return loading_new_patch_;
	}

	void audio_is_muted() {
		audio_is_muted_ = true;
	}

	void audio_not_muted() {
		audio_is_muted_ = false;
	}

	bool is_audio_muted() {
		return audio_is_muted_;
	}

	void handle_sync_patch_loading() {
		if (loading_new_patch_ && audio_is_muted_) {
			bool ok = _load_patch(new_patch_index_);
			if (!ok) {
				printf_("Can't load patch, reloading previous patch\n");
				if (!_load_patch(loaded_patch_index_)) {
					printf_("Failed to reload patch, something is wrong!\n");
					//TODO: how to handle this, do we have a "no patch loaded" state?
				}
			} else {
				printf_("Patch loaded\n");
				loaded_patch_index_ = new_patch_index_;
			}

			loading_new_patch_ = false;
		}
	}

	// PatchList &get_patch_list() {
	// 	return patch_list_;
	// }

	// PatchPlayer &get_patch_player() {
	// 	return player_;
	// }

private:
	PatchList &patch_list_;
	PatchPlayer &player_;
	PatchStorage &storage_;

	bool loading_new_patch_ = false;
	bool audio_is_muted_ = false;

	uint32_t loaded_patch_index_;
	uint32_t new_patch_index_;

	bool _load_patch(uint32_t patchid) {
		storage_.load_view_patch(patchid);
		auto &patch = storage_.get_view_patch();
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
