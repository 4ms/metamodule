#pragma once
#include "patch_player.hh"
#include "patchlist.hh"
#include "uart_log.hh"

namespace MetaModule
{

struct PatchLoader {
	static inline uint32_t initial_patch = 7;

	PatchLoader(PatchList &patchlist, PatchPlayer &patchplayer)
		: patch_list_{patchlist}
		, player_{patchplayer} {
	}

	void load_initial_patch() {
		load_patch(initial_patch);
	}

	bool load_patch(uint32_t patchid) {
		auto patchname = patch_list_.get_patch_name(patchid);
		UartLog::log("Attempting load patch #%d, %s\n", patchid, patchname.data());

		bool ok = player_.load_patch(patch_list_.get_patch(patchid));
		if (!ok) {
			UartLog::log("Failed to load patch\n");
			player_.load_patch(patch_list_.get_patch(loaded_patch_index_));
			return false;
		} else {
			UartLog::log("Loaded patch\r\n");
			loaded_patch_index_ = patchid;
			return true;
		}
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
			auto patchname = patch_list_.get_patch_name(new_patch_index_);
			UartLog::log("Attempting load patch #%d, %s\n", new_patch_index_, patchname.data());

			bool ok = load_patch(new_patch_index_);
			if (!ok) {
				UartLog::log("Can't load patch, reloading original\n");
				load_patch(loaded_patch_index_);
			} else {
				UartLog::log("Patch loaded\n");
				loaded_patch_index_ = new_patch_index_;
			}

			loading_new_patch_ = false;
		}
	}

private:
	PatchList &patch_list_;
	PatchPlayer &player_;

	bool loading_new_patch_ = false;
	bool audio_is_muted_ = false;

	uint32_t loaded_patch_index_;
	uint32_t new_patch_index_;
};
} // namespace MetaModule
