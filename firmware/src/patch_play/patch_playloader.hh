#pragma once
#include "calibrate/calibration_patch.hh"
#include "delay.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "patch_play/modules_helpers.hh"
#include "patch_play/patch_player.hh"
#include "patch_to_yaml.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include "user_settings/audio_settings.hh"
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

	struct AudioSRBlock {
		uint32_t sample_rate;
		uint32_t block_size;
	};

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
		pause_module_threads();
	}

	void start_audio() {
		pr_dbg("PatchPlayLoader::start_audio\n");
		loading_new_patch_ = false;
		audio_is_muted_ = false;
		stopping_audio_ = false;
		starting_audio_ = true;
		clear_audio_overrun();
		resume_module_threads();
	}

	void request_load_view_patch() {
		pr_dbg("PatchPlayLoader::request_load_view_patch (should play %d)\n", should_play_when_loaded_);
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
		else
			should_play_when_loaded_ = !audio_is_muted_;
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
			pr_dbg("PatchPlayLoader::handle_file_events(): load patch(should_play_when_loaded_=%d)\n",
				   should_play_when_loaded_);
			auto result = load_patch(should_play_when_loaded_);
			should_play_when_loaded_ = true;
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

	void request_new_audio_settings(uint32_t sample_rate, uint32_t block_size, uint32_t max_retries) {
		new_audio_settings_.store(AudioSRBlock{.sample_rate = sample_rate, .block_size = block_size});
		max_audio_retries = max_retries;
	}

	AudioSettings get_audio_settings() {
		auto [sr, bs] = new_audio_settings_.load();
		return {.sample_rate = sr, .block_size = bs, .max_overrun_retries = max_audio_retries};
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

	void set_all_param_catchup_mode(CatchupParam::Mode mode, bool allow_jump_outofrange) {
		// if (exclude_buttons) {

		// 	for (auto module_id = 0u; auto slug : patches_.get_view_patch()->module_slugs) {
		// 		auto info = ModuleFactory::getModuleInfo(slug);

		// 		for (unsigned i = 0; auto const &element : info.elements) {
		// 			auto param_id = info.indices[i].param_idx;
		// 			enum { Ignore, Enable, Disable };
		// 			auto action = std::visit(overloaded{
		// 										 [](Pot const &el) { return el.integral ? Disable : Enable; },
		// 										 [](Switch const &el) { return Disable; },
		// 										 [](Button const &el) { return Disable; },
		// 										 [](ParamElement const &el) { return Enable; },
		// 										 [](BaseElement const &el) { return Ignore; },
		// 									 },
		// 									 element);
		// 			if (action == Enable)
		// 				player_.set_catchup_mode(module_id, param_id, mode);
		// 			else if (action == Disable)
		// 				player_.set_catchup_mode(module_id, param_id, CatchupParam::Mode::ResumeOnMotion);

		// 			i++;
		// 		}
		// 		module_id++;
		// 	}

		// } else {
		player_.set_catchup_mode(mode, allow_jump_outofrange);
		// }
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
	bool should_play_when_loaded_ = true;

	PatchLocation new_loc{};
	PatchLocation old_loc{};
	enum class RenameState { Idle, RequestSaveNew, SavingNew, RequestDeleteOld, DeletingOld };
	RenameState rename_state_{RenameState::Idle};
	uint32_t attempts = 0;

	std::atomic<AudioSRBlock> new_audio_settings_ = {};
	unsigned max_audio_retries = 0;

	Result save_patch(PatchLocation const &loc) {
		auto view_patch = patches_.get_view_patch();

		if (view_patch && view_patch == patches_.get_playing_patch()) {
			view_patch->module_states = player_.patch_query.get_module_states();
			view_patch->static_knobs = player_.patch_query.get_all_params();
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

		auto result = player_.load_patch(*next_patch);
		if (result.success) {
			pr_info("Heap: %u\n", get_heap_size());
			if (next_patch == patches_.get_view_patch())
				patches_.play_view_patch();

			if (start_audio_immediately)
				start_audio();

			pr_dbg("PatchPlayLoader:: end of load_patch\n");
		}

		loading_new_patch_ = false;
		return result;
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
};
} // namespace MetaModule
