#pragma once
#include "calibrate/calibration_patch.hh"
#include "delay.hh"
#include "gui/notify/queue.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "patch_play/modules_helpers.hh"
#include "patch_play/patch_player.hh"
#include "patch_to_yaml.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include "user_settings/settings.hh"
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

	void stop_audio() {
		starting_audio_ = false;
		stopping_audio_ = true;
	}

	void start_audio() {
		resume_module_threads();

		loading_new_patch_ = false;
		audio_is_muted_ = false;
		stopping_audio_ = false;
		starting_audio_ = true;
		player_.notify_audio_resumed();
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

	void request_reload_playing_patch(bool start_audio_immediately = true) {
		next_patch = patches_.get_playing_patch();
		loading_new_patch_ = true;
		if (start_audio_immediately)
			should_play_when_loaded_ = true;
		else {
			// start playing if audio is already playing, or if it stopped because of overload
			should_play_when_loaded_ = !audio_is_muted_ || stopped_because_of_overrun_;
		}
	}

	bool is_loading_patch() {
		return loading_new_patch_;
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
		// Pause threads once audio has confirmed it's no longer playing the patch
		pause_module_threads();
	}

	void notify_audio_overrun() {
		notify_audio_is_muted();
		audio_overrun_ = true;
		stopped_because_of_overrun_ = true;
	}

	void notify_audio_done_starting() {
		starting_audio_ = false;
	}

	void notify_audio_not_muted() {
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

	std::optional<unsigned> is_panel_knob_catchup_inaccessible() {
		return player_.panel_knob_catchup_inaccessible();
	}

	float param_value(uint16_t module_idx, uint16_t param_idx) {
		return player_.get_param(module_idx, param_idx);
	}

	float light_value(uint16_t module_idx, uint16_t param_idx) {
		return player_.get_module_light(module_idx, param_idx);
	}

	// Concurrency: Called from UI thread
	Result handle_file_events() {
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

	void request_save_patch() {
		should_save_patch_ = true;
	}

	bool is_renaming_idle() {
		return rename_state_ == RenameState::Idle;
	}

	void request_rename_view_patch(PatchLocation const &loc) {
		old_loc = {patches_.get_view_patch_filename(), patches_.get_view_patch_vol()};
		new_loc = loc;
		rename_state_ = RenameState::RequestSaveNew;
	}

	void load_module(std::string_view slug) {
		bool should_play = is_playing();

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
		if (should_play)
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

	void prepare_patch_for_plugin_change(std::string_view brand_slug) {
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
			// TODO: can we force it to reload from disk, but not forget its location?
			patches_.close_playing_patch();
		}
	}

	struct AudioSRBlock {
		uint16_t sample_rate;
		uint16_t block_size;
	};

	void request_new_audio_settings(uint32_t sample_rate, uint16_t block_size, uint32_t max_retries) {
		uint16_t sr_div100 = sample_rate / 100;
		current_audio_settings_.store(AudioSRBlock{.sample_rate = sr_div100, .block_size = block_size});
		max_audio_retries = max_retries;
	}

	AudioSettings get_audio_settings() {
		auto [sr_div100, bs] = current_audio_settings_.load();
		uint32_t sr = sr_div100 * 100;
		return {.sample_rate = sr, .block_size = bs, .max_overrun_retries = max_audio_retries};
	}

	void connect_user_settings(UserSettings *settings) {
		this->settings = settings;
		request_new_audio_settings(
			settings->audio.sample_rate, settings->audio.block_size, settings->audio.max_overrun_retries);
	}

	void connect_notification_queue(NotificationQueue *notification_queue) {
		notify_queue = notification_queue;
	}

	template<typename PluginModuleType>
	PluginModuleType *get_plugin_module(int32_t module_idx) {
		if (module_idx >= 0 && module_idx < (int32_t)player_.num_modules)
			return dynamic_cast<PluginModuleType *>(player_.modules[module_idx].get());
		else
			return nullptr;
	}

	CoreProcessor *get_plugin_module(int32_t module_idx) {
		return player_.modules[module_idx].get();
	}

	bool is_param_tracking(unsigned module_id, unsigned param_id) {
		return player_.is_param_tracking(module_id, param_id);
	}

	void update_param_catchup_mode() {
		player_.set_catchup_mode(settings->catchup.mode, settings->catchup.allow_jump_outofrange);
	}

	void get_module_states() {
		if (auto playing_patch = patches_.get_playing_patch()) {
			playing_patch->module_states = player_.patch_query.get_module_states();
			playing_patch->static_knobs = player_.patch_query.get_all_params();
		}
	}

private:
	Result save_patch(PatchLocation const &loc) {
		auto view_patch = patches_.get_view_patch();

		if (view_patch && view_patch == patches_.get_playing_patch()) {
			get_module_states();
		}

		std::span<char> filedata = storage_.get_patch_data();
		patch_to_yaml_buffer(*view_patch, filedata);

		auto res = storage_.request_write_file(filedata, loc.vol, loc.filename);

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

	Result save_patch() {
		return save_patch({patches_.get_view_patch_filename(), patches_.get_view_patch_vol()});
	}

	Result check_save_patch_status() {
		auto msg = storage_.get_message();

		if (msg.message_type == FileStorageProxy::WriteFileFail) {
			saving_patch_ = false;
			return {false, "Failed to write patch."};

		} else if (msg.message_type == FileStorageProxy::WriteFileOK) {
			saving_patch_ = false;
			patches_.reset_view_patch_modification_count();
			patches_.set_view_patch_timestamp(msg.timestamp);
			patches_.set_view_patch_filesize(msg.length);
			return {true, "Saved"};

		} else {
			return {true, ""};
		}
	}

	Result check_delete_file_status() {
		auto msg = storage_.get_message();

		if (msg.message_type == FileStorageProxy::DeleteFileFailed) {
			return {false, "Failed to remove original patch."};

		} else if (msg.message_type == FileStorageProxy::DeleteFileSuccess) {
			return {true, "Patch Moved"};

		} else {
			return {true, ""};
		}
	}

	Result load_patch(bool start_audio_immediately = true) {
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

		auto result = player_.load_patch(*next_patch);
		if (result.success) {
			delay_ms(20); //let Async threads run
			pr_info("Heap: %u\n", get_heap_size());

			apply_suggested_audio_settings();

			if (start_audio_immediately)
				start_audio();

		} else {
			patches_.close_playing_patch();
		}

		loading_new_patch_ = false;
		return result;
	}

	void apply_suggested_audio_settings() {
		if (!settings) {
			pr_err("Error: PatchPlayLoader not initialized with user settings\n");
			return;
		}

		auto [cur_sr, cur_bs, max_retries] = get_audio_settings();

		auto sugg_sr = next_patch->suggested_samplerate;
		if (!sugg_sr)
			sugg_sr = settings->audio.sample_rate;

		auto sugg_bs = next_patch->suggested_blocksize;
		if (!sugg_bs)
			sugg_bs = settings->audio.block_size;

		bool change_sr = settings->patch_suggested_audio.apply_samplerate && (sugg_sr > 0 && sugg_sr != cur_sr);
		bool change_bs = settings->patch_suggested_audio.apply_blocksize && (sugg_bs > 0 && sugg_bs != cur_bs);

			if (change_sr || change_bs) {
				uint32_t new_sr = change_sr ? sugg_sr : cur_sr;
				uint16_t new_bs = change_bs ? sugg_bs : cur_bs;

				if (notify_queue) {
					std::string message{};
					if (change_sr)
						message += "Sample-rate changed to " + std::to_string(new_sr);
					if (change_sr && change_bs)
						message += "\n";
					if (change_bs)
						message += "Block-size changed to " + std::to_string(new_bs);
					notify_queue->put({message, Notification::Priority::Info, 2000});
				}
				request_new_audio_settings(new_sr, new_bs, max_retries);
		}
	}

	Result process_renaming() {
		if (rename_state_ == RenameState::RequestSaveNew) {
			auto res = save_patch(new_loc);
			if (saving_patch_) {
				rename_state_ = RenameState::SavingNew;
			}
			return res;
		}

		if (rename_state_ == RenameState::SavingNew) {
			auto res = check_save_patch_status();
			if (saving_patch_ == false) {
				if (res.success) {
					attempts = 0;
					patches_.rename_view_patch_file(new_loc.filename, new_loc.vol);
					rename_state_ = RenameState::RequestDeleteOld;
				} else {
					rename_state_ = RenameState::Idle; //Fail
				}
			}
			return res;
		}

		if (rename_state_ == RenameState::RequestDeleteOld) {
			if (storage_.request_delete_file(old_loc.filename, old_loc.vol)) {
				rename_state_ = RenameState::DeletingOld;
				return {true, ""};
			} else {
				if (attempts++ > 100) {
					rename_state_ = RenameState::Idle;
					return {false, "Failed to request deleting old file"};
				}
			}
		}

		if (rename_state_ == RenameState::DeletingOld) {
			auto res = check_delete_file_status();
			if (res.error_string.length() > 0) {
				rename_state_ = RenameState::Idle;
			}
			return res;
		}

		return {true, ""};
	}

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
	bool stopped_because_of_overrun_ = false;
	bool should_play_when_loaded_ = true;

	UserSettings *settings = nullptr;
	std::atomic<AudioSRBlock> current_audio_settings_ = {};
	unsigned max_audio_retries = 0;

	NotificationQueue *notify_queue = nullptr;

	PatchLocation new_loc{};
	PatchLocation old_loc{};
	enum class RenameState { Idle, RequestSaveNew, SavingNew, RequestDeleteOld, DeletingOld };
	RenameState rename_state_{RenameState::Idle};
	uint32_t attempts = 0;
};
} // namespace MetaModule
