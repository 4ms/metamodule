#include "delay.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

void PatchPlayLoader::load_initial_patch(std::string_view patchname, Volume patch_vol) {
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
			if (!patches_.open_patch(raw_patch_file, initial_patch_loc, message.timestamp))
				pr_err("ERROR: could not parse initial patch\n");
			else {
				patches_.start_viewing(initial_patch_loc);
				next_patch = patches_.get_view_patch();
				load_patch();
			}

			break;
		}
		if (message.message_type == FileStorageProxy::LoadFileFailed) {
			pr_err("ERROR: initial patch '%s' failed to load from vol %u\n", patchname.data(), patch_vol);
			break;
		}

		delay_ms(1);
	}
	if (tries == 0) {
		pr_err("ERROR: timed out while waiting for response to request to load initial patch.\n");
		return;
	}
}

// Concurrency: Called from UI thread
Result PatchPlayLoader::handle_file_events() {
	if (loading_new_patch_ && audio_is_muted_) {
		auto result = load_patch(should_play_when_loaded_);
		should_play_when_loaded_ = true;
		stopped_because_of_overrun_ = false;
		return result;
	}

	if (rename_state_ != RenameState::Idle) {
		return process_renaming();
	} else if (should_save_patch_) {
		return save_patch();
	} else if (saving_patch_) {
		return check_save_patch_status();
	}

	return {true, ""};
}

Result PatchPlayLoader::load_patch(bool start_audio_immediately) {
	if (!next_patch) {
		pr_err("Internal error loading patch\n");
		loading_new_patch_ = false;
		return {false, "Internal error loading patch"};
	}

	pr_trace("Attempting play patch: %.31s\n", next_patch->patch_name.data());

	// Change the currently playing patch to point to the new patch
	// This ensures that modules that use the patch location during
	// construction will be given the right path.
	if (next_patch == patches_.get_view_patch()) {
		patches_.play_view_patch();
	} else if (next_patch != patches_.get_playing_patch()) {
		// This happens when loading calibration patches
		// It might also happen if we implement MIDI PC -> patch load
		pr_warn("Open patch manager is not tracking the playing patch\n");
	}

	Result result;
	try {
		result = player_.load_patch(*next_patch);
	} catch (std::bad_alloc &) {
		// Ran out of firmware heap partway through building the patch
		// (copying patch data, caches, etc). Unload to discard the
		// partially-built state.
		pr_err("Out of memory loading patch\n");
		player_.unload_patch();
		result = {false, "Out of memory loading this patch"};
	}
	if (result.success) {
		delay_ms(20); //let Async threads run
		pr_info("Heap: %u\n", get_heap_size());

		// The patch may not have had a load balance stored in it (e.g. it was saved
		// by VCV), in which case the player just calculated one. Keep it, so it gets
		// written out if the user saves the patch.
		copy_load_balance_to_patch();

		apply_suggested_audio_settings();

		if (start_audio_immediately)
			start_audio();

		// Auto re-balance per user preference. Only for normal patches (not
		// calibration), with enough modules to have alternatives.
		// stopped_because_of_overrun_ still holds the pre-load value here.
		if (start_audio_immediately && next_patch == patches_.get_playing_patch() && player_.num_modules > 2 &&
			settings)
		{
			using enum AudioSettings::AutoRebalance;
			auto mode = settings->audio.auto_rebalance;

			if (mode == EveryLoad || (mode == AfterOverload && stopped_because_of_overrun_))
				request_auto_rebalance_ = true;
		}

	} else {
		patches_.close_playing_patch();
	}

	loading_new_patch_ = false;
	return result;
}

void PatchPlayLoader::apply_suggested_audio_settings() {
	if (!settings) {
		pr_err("Error: PatchPlayLoader not initialized with user settings\n");
		return;
	}

	auto patch = patches_.get_playing_patch();
	if (!patch)
		return;

	auto [cur_sr, cur_bs, max_retries, _] = get_audio_settings();

	auto sugg_sr = patch->suggested_samplerate;
	if (!sugg_sr)
		sugg_sr = settings->audio.sample_rate;

	auto sugg_bs = patch->suggested_blocksize;
	if (!sugg_bs)
		sugg_bs = settings->audio.block_size;

	bool change_sr = settings->patch_suggested_audio.apply_samplerate && (sugg_sr > 0 && sugg_sr != cur_sr);
	bool change_bs = settings->patch_suggested_audio.apply_blocksize && (sugg_bs > 0 && sugg_bs != cur_bs);

	if (change_sr || change_bs) {
		uint32_t new_sr = change_sr ? sugg_sr : cur_sr;
		uint16_t new_bs = change_bs ? sugg_bs : cur_bs;
		request_new_audio_settings(new_sr, new_bs, max_retries);
	}
}

} // namespace MetaModule
