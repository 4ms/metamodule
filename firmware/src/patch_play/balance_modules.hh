#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "drivers/cycle_counter.hh"
#include "patch/module_type_slug.hh"
#include "util/fixed_vector.hh"
#include "util/partition.hh"
#include <algorithm>
#include <array>
#include <memory>
#include <vector>

#define PRINT_LOAD_BALANCE
#ifdef PRINT_LOAD_BALANCE
#include "console/pr_dbg.hh"
#endif

namespace MetaModule
{

template<size_t NumCores, size_t MaxModules>
struct Balancer {
	using PartitionT = Partition<NumCores, MaxModules>;
	PartitionT cores;

	std::vector<unsigned>
	measure_modules(std::span<std::unique_ptr<CoreProcessor>> modules, unsigned num_modules, auto run) {

		mdrivlib::CycleCounter counter;

		constexpr size_t NumIterations = 512;
		constexpr size_t DropFirst = 32;

		std::vector<unsigned> times(num_modules - 1, 0);

		for (auto iter_i = 0u; iter_i < NumIterations + DropFirst; iter_i++) {

			for (size_t module_i = 1; module_i < num_modules; module_i++) {
				// Measuring in reverse order doesn't change anything:
				// for (size_t module_i = num_modules - 1; module_i > 0; module_i--) {

				counter.start_measurement();
				run(module_i);
				counter.end_measurement();

				if (iter_i >= DropFirst)
					times[module_i - 1] += counter.get_last_measurement_raw();
			}
		}

		return times;
	}

	void balance_loads(std::span<unsigned> times) {
		cores.calc_partitions(times, lpt_bias());

		// Adjust indices since we skip module 0
		for (auto &part : cores.parts) {
			for (auto &idx : part)
				idx++;
		}
	}

	// Generate up to MaxCandidates partitions starting from the LPT solution and
	// adding single-module moves and pair swaps. Each candidate's parts contain
	// module IDs (1..num_modules-1), matching the form Balancer::cores uses.
	// Filters out candidates whose predicted worst-core load is much worse than LPT.
	template<size_t MaxCandidates = 16>
	FixedVector<PartitionT, MaxCandidates> generate_candidates(std::span<unsigned> times) {
		FixedVector<PartitionT, MaxCandidates> candidates;

		auto bias = lpt_bias();

		// Candidate 0: the LPT solution
		PartitionT lpt;
		lpt.calc_partitions(times, bias);
		shift_to_module_ids(lpt);
		candidates.push_back(lpt);

		// Only generate alternates for the 2-core case
		if constexpr (NumCores != 2) {
			return candidates;
		}

		auto lpt_worst = worst_core_sum(lpt, times, bias);
		// Allow candidates up to 33% worse than LPT's predicted worst-core sum
		auto threshold = lpt_worst + lpt_worst / 3;

		auto try_add = [&](PartitionT const &cand) {
			if (candidates.size() >= MaxCandidates)
				return;
			if (worst_core_sum(cand, times, bias) <= threshold)
				candidates.push_back(cand);
		};

		// Single-move candidates: move one module from one core to the other
		for (auto src = 0u; src < NumCores; src++) {
			auto dst = 1u - src;
			for (auto i = 0u; i < lpt.parts[src].size(); i++) {
				if (lpt.parts[src].size() <= 1)
					break; // don't empty a core
				PartitionT cand = lpt;
				auto m = cand.parts[src][i];
				cand.parts[src].erase(i);
				cand.parts[dst].push_back(m);
				try_add(cand);
			}
		}

		// Pair-swap candidates: exchange one module between cores
		for (auto i = 0u; i < lpt.parts[0].size(); i++) {
			for (auto j = 0u; j < lpt.parts[1].size(); j++) {
				PartitionT cand = lpt;
				std::swap(cand.parts[0][i], cand.parts[1][j]);
				try_add(cand);
			}
		}

		return candidates;
	}

	// Try each candidate via the apply_and_measure callback, which should:
	//   - apply this->cores to the SMP system (assign modules, build cables, etc.)
	//   - run a brief warmup + measurement under real SMP
	//   - return a cost (lower is better, e.g. worst per-iteration time)
	// On exit, this->cores is set to the winning candidate.
	template<typename ApplyMeasureFn>
	void find_best_partition(std::span<unsigned> times, ApplyMeasureFn apply_and_measure) {
		auto candidates = generate_candidates(times);

		uint64_t best_cost = UINT64_MAX;
		size_t best_idx = 0;

#ifdef PRINT_LOAD_BALANCE
		pr_dbg("Testing %zu partition candidates\n", candidates.size());
#endif

		for (auto i = 0u; i < candidates.size(); i++) {
			cores = candidates[i];
			uint64_t cost = apply_and_measure();

#ifdef PRINT_LOAD_BALANCE
			pr_dbg("Candidate %u: cost=%llu\n", i, (unsigned long long)cost);
			for (auto core = 0u; core < NumCores; core++) {
				unsigned sum = 0;
				for (auto idx : cores.parts[core]) {
					pr_dbg("    Core %d: Module %u: %u\n", core, idx, times[idx - 1]);
					sum += times[idx - 1];
				}
				pr_dbg("    Core %d Total: %u\n", core, sum);
			}
#endif

			if (cost < best_cost) {
				best_cost = cost;
				best_idx = i;
			}
		}

		cores = candidates[best_idx];

#ifdef PRINT_LOAD_BALANCE
		pr_dbg("Selected candidate %zu (cost=%llu)\n", best_idx, (unsigned long long)best_cost);
#endif
	}

	void print_times(std::span<unsigned> times, std::span<BrandModuleSlug> slugs) {
#ifdef PRINT_LOAD_BALANCE
		// Debug output:
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = 0;
			for (auto idx : cores.parts[core]) {
				pr_dbg("Core %d: Module %u (%s): %u\n", core, idx, slugs[idx].c_str(), times[idx - 1]);
				sum += times[idx - 1];
			}
			pr_dbg("Core %d Total: %u\n", core, sum);
		}
#endif
	}

private:
	static constexpr std::array<unsigned, NumCores> lpt_bias() {
		std::array<unsigned, NumCores> bias{};
		if constexpr (NumCores == 2) {
			// Core 2 needs extra time to respond to its interrupt; units are 1/24MHz
			bias[1] = 1000;
		}
		return bias;
	}

	static void shift_to_module_ids(PartitionT &p) {
		for (auto &part : p.parts) {
			for (auto &idx : part)
				idx++;
		}
	}

	// Returns the largest core sum, treating part entries as module IDs (1-indexed).
	static unsigned worst_core_sum(PartitionT const &p, std::span<unsigned> times, std::span<const unsigned> bias) {
		unsigned worst = 0;
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = (core < bias.size()) ? bias[core] : 0;
			for (auto id : p.parts[core])
				sum += times[id - 1];
			worst = std::max(worst, sum);
		}
		return worst;
	}
};

} // namespace MetaModule
