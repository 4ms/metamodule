#pragma once
#include "calibrate/calibration_patch.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "gui/notify/queue.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/rebalance_trials.hh"
#include "pr_dbg.hh"
#include "result_t.hh"
#include "user_settings/settings.hh"
#include <atomic>

size_t get_heap_size();

namespace MetaModule
{

// PatchPlayLoader sits between the GUI, the file storage, and the PatchPlayer:
// it loads patches into the player, starts/stops the audio stream around
// changes to the running patch, and saves patches back to storage.
//
// This header holds the state flags and the small functions the audio stream
// polls. The larger duties are implemented in:
//   patch_playloader_load.cc    - loading a patch into the player
//   patch_playloader_modules.cc - adding/changing/removing modules in the playing patch
//   patch_playloader_save.cc    - saving and renaming patch files
//   patch_playloader_balance.cc - load balancing
//   rebalance_trials.hh/.cc     - the live re-balance trials
struct PatchPlayLoader {
	PatchPlayLoader(FileStorageProxy &patch_storage, OpenPatchManager &patches, PatchPlayer &patchplayer)
		: player_{patchplayer}
		, storage_{patch_storage}
		, patches_{patches} {
	}

	//
	// Starting and stopping audio
	//

	void stop_audio() {
		starting_audio_ = false;
		stopping_audio_ = true;
	}

	// Stops audio and blocks until the audio stream confirms it's no longer playing the patch
	void stop_audio_and_wait() {
		stop_audio();
		while (!is_audio_muted())
			;
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

	// Start audio, rebalancing load if needed
	void resume_audio() {
		bool was_overrun_stopped = stopped_because_of_overrun_;
		stopped_because_of_overrun_ = false;

		start_audio();

		if (was_overrun_stopped && player_.num_modules > 2 && settings &&
			settings->audio.auto_rebalance != AudioSettings::AutoRebalance::Off)
		{
			trials_.request_auto();
		}
	}

	bool is_playing() {
		return !audio_is_muted_ && player_.is_loaded;
	}

	// Stops audio (waiting until it's muted) for the lifetime of the object,
	// so the patch can be modified safely. When the object goes out of scope,
	// audio is started again: either only if it had been playing, or always.
	class AudioPause {
	public:
		enum class Restart { IfWasPlaying, Always };

		explicit AudioPause(PatchPlayLoader &loader, Restart restart = Restart::IfWasPlaying)
			: loader_{loader}
			, should_restart_{restart == Restart::Always || loader.is_playing()} {
			loader_.stop_audio_and_wait();
		}

		~AudioPause() {
			if (should_restart_)
				loader_.start_audio();
		}

		AudioPause(AudioPause const &) = delete;
		AudioPause &operator=(AudioPause const &) = delete;

	private:
		PatchPlayLoader &loader_;
		bool should_restart_;
	};

	//
	// Loading patches (patch_playloader_load.cc)
	//

	void load_initial_patch(std::string_view patchname, Volume patch_vol);

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

	// Concurrency: Called from UI thread
	Result handle_file_events();

	void apply_suggested_audio_settings();

	//
	// Audio stream state (polled from the audio context)
	//

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

	// While set, audio runs and is measured normally but the outputs are held
	// silent (so the rebalance trials aren't heard)
	bool audio_silenced() const {
		return trials_.audio_silenced();
	}

	bool is_view_patch_playing() {
		return is_playing() && patches_.get_view_patch() == patches_.get_playing_patch();
	}

	// true even if audio is paused
	bool is_view_patch_loaded() {
		return player_.is_loaded && patches_.get_view_patch() == patches_.get_playing_patch();
	}

	bool did_audio_overrun() {
		return audio_overrun_;
	}

	void clear_audio_overrun() {
		audio_overrun_ = false;
	}

	//
	// Queries about the playing patch
	//

	std::optional<unsigned> is_panel_knob_catchup_inaccessible() {
		return player_.panel_knob_catchup_inaccessible();
	}

	float param_value(uint16_t module_idx, uint16_t param_idx) {
		return player_.get_param(module_idx, param_idx);
	}

	float light_value(uint16_t module_idx, uint16_t param_idx) {
		return player_.get_module_light(module_idx, param_idx);
	}

	// Returns number of poly channels on the cable from out jack to in jack (0 or 1 means mono)
	unsigned num_poly_cable_channels(Jack out, Jack in) {
		if (is_loading_patch())
			return 0;
		return player_.num_poly_cable_channels(out, in);
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

	// Copies the modules' current state and param values into the playing patch
	void get_module_states();

	//
	// Saving and renaming (patch_playloader_save.cc)
	//

	void request_save_patch() {
		should_save_patch_ = true;
	}

	bool is_saving() const {
		return should_save_patch_ || saving_patch_;
	}

	bool is_renaming_idle() {
		return rename_state_ == RenameState::Idle;
	}

	void request_rename_view_patch(PatchLocation const &loc);

	//
	// Modifying the modules in the playing patch (patch_playloader_modules.cc)
	//

	// Returns why the module could not be created (Ok on success), so the
	// caller can inform the user
	PatchPlayer::CreateResult load_module(std::string_view slug);

	void change_module(std::string_view slug, unsigned module_id, bool keep_cables_and_maps);

	void remove_module(unsigned module_id);

	void prepare_patch_for_plugin_change(std::string_view brand_slug);

	//
	// Load balancing (patch_playloader_balance.cc)
	//

	// Measures the modules again and picks a new way to split them between the cores.
	// Only meaningful while the patch is playing.
	void recalculate_load_balance();

	// -- Rebalance trials (see rebalance_trials.hh) --
	// Try several candidate arrangements live and keep the one with the
	// lowest measured audio load. Advanced by update_rebalance_trials() from the GUI loop
	void start_rebalance_trials(uint32_t now_ms) {
		trials_.start(now_ms);
	}

	void update_rebalance_trials(uint32_t now_ms) {
		trials_.update(now_ms);
	}

	// E.g. the panel is closing mid-trials: keep the best candidate found so far
	void abort_rebalance_trials() {
		trials_.abort();
	}

	bool rebalance_trials_active() const {
		return trials_.active();
	}

	// For displaying progress: which candidate is being tried, out of how many
	unsigned rebalance_trials_current() const {
		return trials_.current();
	}

	unsigned rebalance_trials_total() const {
		return trials_.total();
	}

	// Puts back a load balance the user had before (Undo), without re-measuring
	void apply_load_balance(std::vector<uint16_t> const &module_cores, std::vector<uint32_t> const &module_loads);

	// The player works on its own copy of the patch data, so the load balance it
	// calculated has to be copied back into the open patch in order to be saved.
	void copy_load_balance_to_patch();

	// Live measurements of where the playing patch's audio time goes
	LiveLoadMeter::Loads get_live_load() const {
		return player_.live_load.get();
	}

	// Per-module live measurement costs a few percent CPU, so it only runs
	// while a page displaying it is open
	void set_live_load_detail(bool on) {
		player_.live_load.set_detailed(on);
	}

	//
	// Audio and user settings
	//

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

	bool is_midi_14bit_enabled() const {
		return settings && settings->midi.midi_14bit_cc == MidiSettings::Midi14BitCC::Enabled;
	}

	void connect_user_settings(UserSettings *settings) {
		this->settings = settings;
		request_new_audio_settings(
			settings->audio.sample_rate, settings->audio.block_size, settings->audio.max_overrun_retries);
	}

	void connect_notification_queue(NotificationQueue *notification_queue) {
		notify_queue = notification_queue;
	}

private:
	// patch_playloader_load.cc
	Result load_patch(bool start_audio_immediately = true);

	// patch_playloader_save.cc
	Result save_patch(PatchLocation const &loc);
	Result save_patch();
	Result check_save_patch_status();
	Result check_delete_file_status();
	Result process_renaming();

	// The trials reach into the loader's audio start/stop and patch state
	friend class RebalanceTrials;
	RebalanceTrials trials_{*this};

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
