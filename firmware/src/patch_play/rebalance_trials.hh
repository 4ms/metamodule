#pragma once
#include "patch/patch_data.hh"
#include <atomic>
#include <cstdint>
#include <vector>

namespace MetaModule
{

struct PatchPlayLoader;

// Tries several candidate core assignments for the playing patch, live, and
// keeps the one with the lowest measured audio load.
//
// The trials run as a state machine advanced by update() from the GUI loop:
// each candidate is applied, given a short warm-up, then measured over a
// window. The audio outputs are held silent for the whole run.
class RebalanceTrials {
public:
	explicit RebalanceTrials(PatchPlayLoader &loader)
		: loader_{loader} {
	}

	void start(uint32_t now_ms);

	void update(uint32_t now_ms);

	// E.g. the panel is closing mid-trials: keep the best candidate found so far.
	// Restarts audio even if the current candidate had stopped the patch.
	void abort();

	// Starts the trials at the next update(), announcing them with notifications
	// (used for the Auto Re-balance preference)
	void request_auto() {
		auto_requested_ = true;
	}

	bool active() const {
		return state_ != State::Idle;
	}

	// For displaying progress: which candidate is being tried, out of how many
	unsigned current() const {
		return cur_ + 1;
	}

	unsigned total() const {
		return cores_.size();
	}

	// While set, audio runs and is measured normally but the outputs are held
	// silent (so the trials aren't heard)
	bool audio_silenced() const {
		return silent_audio_.load(std::memory_order_relaxed);
	}

private:
	void apply_candidate(unsigned idx);
	void advance(uint32_t now_ms, uint32_t avg_ticks, uint32_t overruns);
	void finish();

	static constexpr unsigned NumSeeds = 5;
	static constexpr uint32_t WarmupMs = 100;
	static constexpr uint32_t MeasureMs = 150;

	enum class State { Idle, Warmup, Measure };

	PatchPlayLoader &loader_;

	State state_ = State::Idle;
	std::vector<std::vector<uint16_t>> cores_;
	std::vector<uint32_t> loads_;
	PatchData *for_patch_ = nullptr;
	unsigned cur_ = 0;
	unsigned best_idx_ = 0;
	uint32_t best_ticks_per_block_ = 0xFFFFFFFF;
	uint32_t best_overruns_ = 0xFFFFFFFF;
	uint32_t t0_ = 0;
	uint32_t ticks0_ = 0;
	uint32_t blocks0_ = 0;
	uint32_t overruns0_ = 0;

	std::atomic<bool> silent_audio_ = false;
	bool auto_requested_ = false;
	bool auto_trials_ = false;
};

} // namespace MetaModule
