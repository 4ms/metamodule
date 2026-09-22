#include "patch_play/rebalance_trials.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

void RebalanceTrials::start(uint32_t now_ms) {
	if (state_ != State::Idle)
		return;

	if (!loader_.player_.is_loaded)
		return;

	PatchPlayLoader::AudioPause pause{loader_, PatchPlayLoader::AudioPause::Restart::Always};

	auto candidates = loader_.player_.make_balance_candidates(NumSeeds);

	if (candidates.cores.empty())
		return;

	cores_ = std::move(candidates.cores);
	loads_ = std::move(candidates.loads_ppm);
	for_patch_ = loader_.patches_.get_playing_patch();
	cur_ = 0;
	best_idx_ = 0;
	best_ticks_per_block_ = 0xFFFFFFFF;
	best_overruns_ = 0xFFFFFFFF;

	if (cores_.size() > 1) {
		// Hold the outputs silent for the whole trial run
		silent_audio_.store(true, std::memory_order_relaxed);
	}

	loader_.player_.set_load_balance(cores_[0], loads_);

	// A pre-existing overload-stop is being handled by these trials; from here
	// on the flag means "the current candidate overloaded"
	loader_.stopped_because_of_overrun_ = false;

	if (cores_.size() == 1) {
		// Nothing to compare
		loader_.copy_load_balance_to_patch();
		finish();
	} else {
		t0_ = now_ms;
		state_ = State::Warmup;
	}
}

void RebalanceTrials::update(uint32_t now_ms) {
	if (state_ == State::Idle) {
		// An automatic re-balance was requested (per the Auto Re-balance pref)
		if (auto_requested_) {
			auto_requested_ = false;
			if (loader_.notify_queue)
				loader_.notify_queue->put({"Optimizing CPU load balance...", Notification::Priority::Status, 1500});
			start(now_ms);
			auto_trials_ = active();
		}
		return;
	}

	if (!loader_.player_.is_loaded || loader_.is_loading_patch() || loader_.patches_.get_playing_patch() != for_patch_)
	{
		// The patch changed out from under us: give up
		finish();
		return;
	}

	if (!loader_.is_playing()) {
		if (loader_.stopped_because_of_overrun_) {
			// This candidate overloaded badly enough to stop the patch => worst possible score
			loader_.stopped_because_of_overrun_ = false;
			advance(now_ms, 0xFFFFFFFF, 0xFFFFFFFF);
		} else {
			// User stopped the patch, abort
			finish();
			loader_.copy_load_balance_to_patch();
		}
		return;
	}

	if (state_ == State::Warmup) {
		if (now_ms - t0_ >= WarmupMs) {
			auto totals = loader_.player_.live_load.block_totals();
			ticks0_ = totals.ticks;
			blocks0_ = totals.blocks;
			overruns0_ = totals.overruns;
			t0_ = now_ms;
			state_ = State::Measure;
		}

	} else if (state_ == State::Measure) {
		if (now_ms - t0_ >= MeasureMs) {
			auto totals = loader_.player_.live_load.block_totals();
			auto blocks = totals.blocks - blocks0_;
			if (blocks == 0) {
				// No audio ran yet? Extend the window
				t0_ = now_ms;
				return;
			}

			advance(now_ms, (totals.ticks - ticks0_) / blocks, totals.overruns - overruns0_);
		}
	}
}

void RebalanceTrials::abort() {
	if (state_ == State::Idle)
		return;

	finish();

	if (loader_.player_.is_loaded)
		apply_candidate(best_overruns_ == 0xFFFFFFFF ? 0 : best_idx_);

	loader_.copy_load_balance_to_patch();
}

void RebalanceTrials::apply_candidate(unsigned idx) {
	PatchPlayLoader::AudioPause pause{loader_, PatchPlayLoader::AudioPause::Restart::Always};

	loader_.player_.set_load_balance(cores_[idx], loads_);
}

// Scores the candidate that was just tried, then starts the next one or
// finishes with the winner. Fewest overruns wins; average time per block
// breaks ties.
void RebalanceTrials::advance(uint32_t now_ms, uint32_t avg_ticks, uint32_t overruns) {
	if (overruns < best_overruns_ || (overruns == best_overruns_ && avg_ticks < best_ticks_per_block_)) {
		best_overruns_ = overruns;
		best_ticks_per_block_ = avg_ticks;
		best_idx_ = cur_;
	}

	cur_++;
	if (cur_ < cores_.size()) {
		apply_candidate(cur_);
		t0_ = now_ms;
		state_ = State::Warmup;
	} else {
		finish();
		apply_candidate(best_idx_);
		loader_.copy_load_balance_to_patch();
	}
}

// Ends the trials and lets the audio outputs fade up again
void RebalanceTrials::finish() {
	silent_audio_.store(false, std::memory_order_relaxed);
	auto_trials_ = false;
	state_ = State::Idle;
}

} // namespace MetaModule
