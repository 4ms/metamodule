#pragma once
#include "conf/patch_conf.hh"
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Tabulates and smooths live CPU load measurements from both cores and makes it available to the GUI
class LiveLoadMeter {
public:
	static constexpr unsigned MaxCores = 2;
	static constexpr unsigned MaxModules = MAX_MODULES_IN_PATCH;

	// All loads are percent of the audio block period, in tenths of a percent
	// (e.g. 123 => 12.3%)
	struct Loads {
		uint16_t overhead;
		uint16_t mappings;
		uint16_t sync;
		uint16_t cables;
		std::array<uint16_t, MaxCores> core_modules;
		uint16_t midi;
		uint16_t sync2;		   // Core 1 waiting at the second join (for Core 2's cables)
		uint16_t core2_cables; // Core 2's cable processing (parallel work, not Core 1 time)
		std::array<uint16_t, MaxModules> modules;
		bool valid;
	};

	// -- Audio context (Core 1) --

	// Time to process one audio frame in AudioStream::process()
	void tally_frame(uint32_t loop_ticks) {
		frame_loop_ticks += loop_ticks;
	}

	// Time AudioStream::process() spends handling the MIDI stream (counted as
	// MIDI, not Mappings, even though it happens inside the frame loop)
	void tally_midi_stream(uint32_t midi_ticks) {
		midi_stream_ticks += midi_ticks;
	}

	// Times from PatchPlayer::update_patch(): total time, time running this core's modules,
	// time spent waiting for the other core to finish its modules (first join),
	// and time spent waiting for the other core's cables (second join)
	void tally_update_patch(uint32_t total_ticks,
							uint32_t module_ticks,
							uint32_t wait_ticks,
							uint32_t cable_ticks,
							uint32_t midi_ticks,
							uint32_t wait2_ticks) {
		update_patch_ticks += total_ticks;
		core1_module_ticks += module_ticks;
		sync_ticks += wait_ticks;
		midi_pulse_ticks += midi_ticks;
		core1_cable_ticks += cable_ticks;
		sync2_ticks += wait2_ticks;
	}

	// -- Either core, for the modules it runs --

	// Per-module measurement costs ~2-3% on medium patches, so it only runs
	// while something is displaying it (the Load Balance panel)
	bool detailed() const {
		return detailed_.load(std::memory_order_relaxed);
	}

	void set_detailed(bool on) {
		// Seed the per-module smoothing from the first fully-measured blocks,
		// so the values are usable right away instead of slowly ramping up
		if (on && !detailed())
			module_seed_blocks.store(2, std::memory_order_relaxed);

		detailed_.store(on, std::memory_order_relaxed);
	}

	// Free-running totals: each core adds time for its own modules, and
	// finish_block() (on Core 1) samples the deltas
	void tally_module(unsigned module_id, uint32_t ticks) {
		if (module_id < MaxModules)
			module_ticks_total[module_id].fetch_add(ticks, std::memory_order_relaxed);
	}

	void finish_block(uint32_t block_ticks, uint32_t period_ticks, unsigned num_modules) {
		if (period_ticks == 0)
			return;

		// Running totals used by rebalance trials to compare arrangements
		block_ticks_total.fetch_add(block_ticks, std::memory_order_relaxed);
		blocks_total.fetch_add(1, std::memory_order_relaxed);

		auto core2_total = core2_module_ticks.load(std::memory_order_relaxed);
		auto core2_cables_now = core2_cable_ticks.load(std::memory_order_relaxed);

		std::array<uint32_t, NumCategories> ticks{
			sat_sub(update_patch_ticks,
					core1_module_ticks + sync_ticks + core1_cable_ticks + midi_pulse_ticks + sync2_ticks) +
				sat_sub(block_ticks, frame_loop_ticks),						   // Overhead
			sat_sub(frame_loop_ticks, update_patch_ticks + midi_stream_ticks), // Mappings
			sync_ticks,														   // Sync
			core1_cable_ticks,												   // Cables
			core1_module_ticks,
			core2_total - last_core2_total,
			midi_pulse_ticks + midi_stream_ticks, // MIDI
			sync2_ticks,
			core2_cables_now - last_core2_cables,
		};
		last_core2_total = core2_total;
		last_core2_cables = core2_cables_now;

		frame_loop_ticks = 0;
		update_patch_ticks = 0;
		core1_module_ticks = 0;
		sync_ticks = 0;
		core1_cable_ticks = 0;
		midi_pulse_ticks = 0;
		midi_stream_ticks = 0;
		sync2_ticks = 0;

		for (auto i = 0u; i < NumCategories; i++) {
			float frac = (float)ticks[i] / (float)period_ticks;
			lpf[i] = published.valid ? lpf[i] + (frac - lpf[i]) * Alpha : frac;
		}

		Loads new_loads{
			.overhead = to_tenths(lpf[0]),
			.mappings = to_tenths(lpf[1]),
			.sync = to_tenths(lpf[2]),
			.cables = to_tenths(lpf[3]),
			.core_modules = {to_tenths(lpf[4]), to_tenths(lpf[5])},
			.midi = to_tenths(lpf[6]),
			.sync2 = to_tenths(lpf[7]),
			.core2_cables = to_tenths(lpf[8]),
			.modules = {},
			.valid = true,
		};

		// Per-module loads
		if (detailed()) {
			auto seeding = module_seed_blocks.load(std::memory_order_relaxed);

			auto num = std::min(num_modules, MaxModules);
			for (auto i = 1u; i < num; i++) {
				auto total = module_ticks_total[i].load(std::memory_order_relaxed);
				float frac = (float)(total - last_module_totals[i]) / (float)period_ticks;
				last_module_totals[i] = total;

				module_lpf[i] = (published.valid && !seeding) ? module_lpf[i] + (frac - module_lpf[i]) * Alpha : frac;
				new_loads.modules[i] = to_tenths(module_lpf[i]);
			}

			if (seeding)
				module_seed_blocks.store(seeding - 1, std::memory_order_relaxed);
		}

		published = new_loads;
	}

	// Forget tallies accumulated since the last block, without disturbing the
	// smoothed values. Used when patch processing ran outside the audio context
	// (overrun retry), which would otherwise pollute the next block's numbers.
	void discard_block() {
		frame_loop_ticks = 0;
		update_patch_ticks = 0;
		core1_module_ticks = 0;
		sync_ticks = 0;
		core1_cable_ticks = 0;
		midi_pulse_ticks = 0;
		midi_stream_ticks = 0;
		sync2_ticks = 0;
		last_core2_total = core2_module_ticks.load(std::memory_order_relaxed);
		last_core2_cables = core2_cable_ticks.load(std::memory_order_relaxed);

		for (auto i = 0u; i < MaxModules; i++)
			last_module_totals[i] = module_ticks_total[i].load(std::memory_order_relaxed);
	}

	void reset() {
		discard_block();
		lpf.fill(0.f);
		module_lpf.fill(0.f);
		published = Loads{};
	}

	// The audio callback found the block took too long
	void tally_overrun() {
		overruns_total.fetch_add(1, std::memory_order_relaxed);
	}

	// -- AuxPlayer (Core 2) --

	void tally_core2_modules(uint32_t module_ticks) {
		core2_module_ticks.fetch_add(module_ticks, std::memory_order_relaxed);
	}

	void tally_core2_cables(uint32_t cable_ticks) {
		core2_cable_ticks.fetch_add(cable_ticks, std::memory_order_relaxed);
	}

	// -- GUI --

	Loads get() const {
		return published;
	}

	// Running totals over all blocks: sampling these before and after a trial
	// period gives the average time per block and the overrun count, for
	// comparing arrangements
	struct BlockTotals {
		uint32_t ticks;
		uint32_t blocks;
		uint32_t overruns;
	};

	BlockTotals block_totals() const {
		return {block_ticks_total.load(std::memory_order_relaxed),
				blocks_total.load(std::memory_order_relaxed),
				overruns_total.load(std::memory_order_relaxed)};
	}

private:
	static constexpr unsigned NumCategories = 9;
	static constexpr float Alpha = 0.05f;

	static uint32_t sat_sub(uint32_t a, uint32_t b) {
		return a > b ? a - b : 0;
	}

	static uint16_t to_tenths(float frac) {
		return (uint16_t)std::min(frac * 1000.f, 65535.f);
	}

	uint32_t frame_loop_ticks = 0;
	uint32_t update_patch_ticks = 0;
	uint32_t core1_module_ticks = 0;
	uint32_t sync_ticks = 0;
	uint32_t core1_cable_ticks = 0;
	uint32_t midi_pulse_ticks = 0;
	uint32_t midi_stream_ticks = 0;
	uint32_t sync2_ticks = 0;

	std::atomic<bool> detailed_{false};
	std::atomic<uint32_t> module_seed_blocks{0};

	std::atomic<uint32_t> core2_module_ticks{0};
	uint32_t last_core2_total = 0;

	std::atomic<uint32_t> core2_cable_ticks{0};
	uint32_t last_core2_cables = 0;

	std::atomic<uint32_t> block_ticks_total{0};
	std::atomic<uint32_t> blocks_total{0};
	std::atomic<uint32_t> overruns_total{0};

	std::array<std::atomic<uint32_t>, MaxModules> module_ticks_total{};
	std::array<uint32_t, MaxModules> last_module_totals{};
	std::array<float, MaxModules> module_lpf{};

	std::array<float, NumCategories> lpf{};

	Loads published{};
};

} // namespace MetaModule
