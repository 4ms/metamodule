#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "drivers/cycle_counter.hh"
#include "patch/module_type_slug.hh"
#include "util/partition.hh"
#include <algorithm>
#include <memory>
#include <numeric>
#include <span>
#include <vector>

// #define PRINT_LOAD_BALANCE
#ifdef PRINT_LOAD_BALANCE
#include "console/pr_dbg.hh"
#endif

namespace MetaModule
{

// Measured module loads are always stored as a share of one core at this sample rate,
// whatever rate they were actually measured at: a module takes the same amount of time
// per sample either way. Anything displaying them scales by (current rate / this).
inline constexpr uint32_t LoadBalanceRefSamplerate = 48000;

template<size_t NumCores, size_t MaxModules>
struct Balancer {
	Partition<NumCores, MaxModules> cores;

	// Number of samples each module is run for when measuring its CPU time
	static constexpr size_t NumIterations = 512;
	static constexpr size_t DropFirst = 32;

	// Rate of the cycle counter used by measure_modules()
	static constexpr uint32_t CounterHz = 24'000'000;

	// Core 2 needs extra time to respond to its interrupt (units of 1/CounterHz)
	static constexpr unsigned SecondCoreBias = 1000;

	std::vector<unsigned>
	measure_modules(std::span<std::unique_ptr<CoreProcessor>> modules, unsigned num_modules, auto run) {

		mdrivlib::CycleCounter counter;

		std::vector<unsigned> times(num_modules - 1, 0);

		for (auto iter_i = 0u; iter_i < NumIterations + DropFirst; iter_i++) {

			for (size_t module_i = 1; module_i < num_modules; module_i++) {

				counter.start_measurement();
				run(module_i);
				counter.end_measurement();

				if (iter_i >= DropFirst)
					times[module_i - 1] += counter.get_last_measurement_raw();
			}
		}

		return times;
	}

	// Converts a raw measurement from measure_modules() into parts-per-million of the
	// time one core has to process a single sample, at LoadBalanceRefSamplerate (48kHz).
	static uint32_t ticks_to_ppm(unsigned ticks) {
		auto ticks_per_sample = (float)ticks / (float)NumIterations;
		auto ticks_available = (float)CounterHz / (float)LoadBalanceRefSamplerate;
		return (uint32_t)(ticks_per_sample / ticks_available * 1'000'000.f);
	}

	// A candidate assignment of modules to cores. Indexed by module id, so entry 0
	// (the hub) is unused
	struct Arrangement {
		std::array<uint16_t, MaxModules> core_of{};
		// Difference between the busiest and the least busy core
		unsigned imbalance = 0;
	};

	// Greedy longest-processing-time-first:
	// Sort modules by time, then put each module on the core with the smallest sum.
	// seed == 0 gives the deterministic result. Any other seed shuffles
	// modules of similar size before assigning them, giving a different arrangement
	// of usually similar quality.
	// `times` is indexed by (module id - 1), as returned by measure_modules().
	static Arrangement make_arrangement(std::span<const unsigned> times, uint32_t seed) {
		struct IdVal {
			unsigned val;
			uint16_t module_id;
		};

		FixedVector<IdVal, MaxModules> ordered;
		for (auto i = 0u; i < times.size(); i++)
			ordered.push_back({times[i], (uint16_t)(i + 1)});

		std::ranges::sort(ordered, std::greater{}, &IdVal::val);

		if (seed != 0) {
			// Randomly swap neighbors in the sorted order. Neighbors are similar in
			// size, so this perturbs the result with minimal total change
			uint32_t rng = seed;
			auto next_rand = [&rng] {
				rng ^= rng << 13;
				rng ^= rng >> 17;
				rng ^= rng << 5;
				return rng;
			};
			for (auto i = 1u; i < ordered.size(); i++) {
				if (next_rand() & 1)
					std::swap(ordered[i - 1], ordered[i]);
			}
		}

		std::array<unsigned, NumCores> sums{};
		if constexpr (NumCores == 2)
			sums[1] = SecondCoreBias;

		Arrangement arr;

		for (auto const &[val, module_id] : ordered) {
			auto min_sum = std::ranges::min_element(sums);
			arr.core_of[module_id] = (uint16_t)std::ranges::distance(sums.begin(), min_sum);
			*min_sum += val;
		}

		auto [min, max] = std::ranges::minmax_element(sums);
		arr.imbalance = *max - *min;

		return arr;
	}

	void apply_arrangement(Arrangement const &arr, unsigned num_modules) {
		for (auto &part : cores.parts)
			part.clear();

		for (auto module_id = 1u; module_id < num_modules; module_id++) {
			auto core = arr.core_of[module_id];
			if (core < NumCores)
				cores.parts[core].push_back(module_id);
		}
	}

	void apply_stored_balance(std::span<const uint16_t> module_cores) {
		for (auto &part : cores.parts)
			part.clear();

		for (auto module_id = 1u; module_id < module_cores.size(); module_id++) {
			auto core = module_cores[module_id];
			if (core < NumCores)
				cores.parts[core].push_back(module_id);
		}
	}

	// Calculates a new load balance from fresh measurements.
	// If `prev_cores` holds an assignment (from an earlier run), this prefers to
	// produce a different one -- but only if a different one is nearly as good.
	// Returns the arrangement used, so the caller can store it in the patch.
	Arrangement balance_loads(std::span<const unsigned> times, std::span<const uint16_t> prev_cores = {}) {
		auto num_modules = times.size() + 1;

		auto best = make_arrangement(times, 0);

		if (prev_cores.size() > 0) {
			auto total = std::accumulate(times.begin(), times.end(), 0u);

			// Any arrangement within this much of the best one is considered just as good
			auto threshold = best.imbalance + total / 50;

			auto differs = [&](Arrangement const &arr) {
				for (auto module_id = 1u; module_id < num_modules; module_id++) {
					if (module_id >= prev_cores.size() || arr.core_of[module_id] != prev_cores[module_id])
						return true;
				}
				return false;
			};

			if (differs(best) == false) {
				constexpr unsigned MaxTries = 16;
				for (auto try_i = 1u; try_i <= MaxTries; try_i++) {
					// psuedo-random seed to try different arrangements
					auto candidate = make_arrangement(times, try_i * 2654435761u);
					if (candidate.imbalance <= threshold && differs(candidate)) {
						best = candidate;
						break;
					}
				}
			}
		}

		apply_arrangement(best, num_modules);
		return best;
	}

	void print_times(std::span<unsigned> times, std::span<BrandModuleSlug> slugs) {
#ifdef PRINT_LOAD_BALANCE
		// Debug output:
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = 0;
			for (auto idx : cores.parts[core]) {
				pr_dbg(
					"Core %d: Module %u %s: %u\n", core, idx, slugs.size() ? slugs[idx].c_str() : "", times[idx - 1]);
				sum += times[idx - 1];
			}
			pr_dbg("Core %d Total: %u\n", core, sum);
		}
#endif
	}
};

} // namespace MetaModule
