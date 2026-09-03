#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

// Measures the modules again and picks a new way to split them between the cores.
// Only meaningful while the patch is playing.
void PatchPlayLoader::recalculate_load_balance() {
	if (!player_.is_loaded)
		return;

	AudioPause pause{*this};

	player_.rebalance_modules(PatchPlayer::Balance::Recalculate);
	copy_load_balance_to_patch();
}

// -- Rebalance trials --
// Try several candidate arrangements live and keep the one with the
// lowest measured audio load. The trials run as a state machine advanced by
// update_rebalance_trials() from the GUI loop
void PatchPlayLoader::start_rebalance_trials(uint32_t now_ms) {
	if (trials_.state != RebalanceTrials::State::Idle)
		return;

	if (!player_.is_loaded)
		return;

	AudioPause pause{*this, AudioPause::Restart::Always};

	auto candidates = player_.make_balance_candidates(NumRebalanceSeeds);

	if (candidates.cores.empty())
		return;

	trials_.cores = std::move(candidates.cores);
	trials_.loads = std::move(candidates.loads_ppm);
	trials_.for_patch = patches_.get_playing_patch();
	trials_.cur = 0;
	trials_.best_idx = 0;
	trials_.best_ticks_per_block = 0xFFFFFFFF;
	trials_.best_overruns = 0xFFFFFFFF;

	if (trials_.cores.size() > 1) {
		// Hold the outputs silent for the whole trial run
		silent_audio_.store(true, std::memory_order_relaxed);
	}

	player_.set_load_balance(trials_.cores[0], trials_.loads);

	// A pre-existing overload-stop is being handled by these trials; from here
	// on the flag means "the current candidate overloaded"
	stopped_because_of_overrun_ = false;

	if (trials_.cores.size() == 1) {
		// Nothing to compare
		copy_load_balance_to_patch();
		finish_rebalance_trials();
	} else {
		trials_.t0 = now_ms;
		trials_.state = RebalanceTrials::State::Warmup;
	}
}

void PatchPlayLoader::update_rebalance_trials(uint32_t now_ms) {
	using State = RebalanceTrials::State;

	if (trials_.state == State::Idle) {
		// An automatic re-balance was requested (per the Auto Re-balance pref)
		if (request_auto_rebalance_) {
			request_auto_rebalance_ = false;
			if (notify_queue)
				notify_queue->put({"Optimizing CPU load balance...", Notification::Priority::Status, 1500});
			start_rebalance_trials(now_ms);
			auto_trials_ = rebalance_trials_active();
		}
		return;
	}

	if (!player_.is_loaded || is_loading_patch() || patches_.get_playing_patch() != trials_.for_patch) {
		// The patch changed out from under us: give up
		finish_rebalance_trials();
		return;
	}

	if (!is_playing()) {
		if (stopped_because_of_overrun_) {
			// This candidate overloaded badly enough to stop the patch => worst possible score
			stopped_because_of_overrun_ = false;
			advance_rebalance_trials(now_ms, 0xFFFFFFFF, 0xFFFFFFFF);
		} else {
			// User stopped the patch, abort
			finish_rebalance_trials();
			copy_load_balance_to_patch();
		}
		return;
	}

	if (trials_.state == State::Warmup) {
		if (now_ms - trials_.t0 >= TrialWarmupMs) {
			auto totals = player_.live_load.block_totals();
			trials_.ticks0 = totals.ticks;
			trials_.blocks0 = totals.blocks;
			trials_.overruns0 = totals.overruns;
			trials_.t0 = now_ms;
			trials_.state = State::Measure;
		}

	} else if (trials_.state == State::Measure) {
		if (now_ms - trials_.t0 >= TrialMeasureMs) {
			auto totals = player_.live_load.block_totals();
			auto blocks = totals.blocks - trials_.blocks0;
			if (blocks == 0) {
				// No audio ran yet? Extend the window
				trials_.t0 = now_ms;
				return;
			}

			advance_rebalance_trials(
				now_ms, (totals.ticks - trials_.ticks0) / blocks, totals.overruns - trials_.overruns0);
		}
	}
}

// E.g. the panel is closing mid-trials: keep the best candidate found so far.
// Restarts audio even if the current candidate had stopped the patch.
void PatchPlayLoader::abort_rebalance_trials() {
	if (trials_.state == RebalanceTrials::State::Idle)
		return;

	finish_rebalance_trials();

	if (player_.is_loaded)
		apply_trial_candidate(trials_.best_overruns == 0xFFFFFFFF ? 0 : trials_.best_idx);

	copy_load_balance_to_patch();
}

// Puts back a load balance the user had before (Undo), without re-measuring
void PatchPlayLoader::apply_load_balance(std::vector<uint16_t> const &module_cores,
										 std::vector<uint32_t> const &module_loads) {
	if (!player_.is_loaded)
		return;

	AudioPause pause{*this};

	player_.set_load_balance(module_cores, module_loads);
	copy_load_balance_to_patch();
}

// The player works on its own copy of the patch data, so the load balance it
// calculated has to be copied back into the open patch in order to be saved.
void PatchPlayLoader::copy_load_balance_to_patch() {
	auto *patch = patches_.get_playing_patch();
	if (!patch)
		return;

	patch->module_cores = player_.get_module_cores();
	patch->module_loads = player_.get_module_loads();
}

void PatchPlayLoader::apply_trial_candidate(unsigned idx) {
	AudioPause pause{*this, AudioPause::Restart::Always};

	player_.set_load_balance(trials_.cores[idx], trials_.loads);
}

// Scores the candidate that was just tried, then starts the next one or
// finishes with the winner. Fewest overruns wins; average time per block
// breaks ties.
void PatchPlayLoader::advance_rebalance_trials(uint32_t now_ms, uint32_t avg_ticks, uint32_t overruns) {
	if (overruns < trials_.best_overruns ||
		(overruns == trials_.best_overruns && avg_ticks < trials_.best_ticks_per_block))
	{
		trials_.best_overruns = overruns;
		trials_.best_ticks_per_block = avg_ticks;
		trials_.best_idx = trials_.cur;
	}

	trials_.cur++;
	if (trials_.cur < trials_.cores.size()) {
		apply_trial_candidate(trials_.cur);
		trials_.t0 = now_ms;
		trials_.state = RebalanceTrials::State::Warmup;
	} else {
		// Keep the winner. Un-silence first so re-applying fades it in
		bool announce = auto_trials_;
		finish_rebalance_trials();
		apply_trial_candidate(trials_.best_idx);
		copy_load_balance_to_patch();

		if (announce && notify_queue)
			notify_queue->put({"Re-balancing complete", Notification::Priority::Status, 750});
	}
}

// Ends the trials and lets the audio outputs fade up again
void PatchPlayLoader::finish_rebalance_trials() {
	silent_audio_.store(false, std::memory_order_relaxed);
	auto_trials_ = false;
	trials_.state = RebalanceTrials::State::Idle;
}

} // namespace MetaModule
