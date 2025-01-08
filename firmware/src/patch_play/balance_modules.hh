#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "drivers/cycle_counter.hh"
#include "patch/module_type_slug.hh"
#include "util/partition.hh"
#include <memory>
#include <vector>

#include "console/pr_dbg.hh"

namespace MetaModule
{

template<size_t NumCores, size_t MaxModules>
struct Balancer {
	Partition<NumCores, MaxModules> cores;

	std::vector<unsigned>
	measure_modules(std::span<std::unique_ptr<CoreProcessor>> modules, unsigned num_modules, auto run) {

		mdrivlib::CycleCounter counter;

		constexpr size_t NumIterations = 512;
		constexpr size_t DropFirst = 32;

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

	void balance_loads(std::span<unsigned> times) {
		if (NumCores == 2) {
			// Core 2 needs extra time to respond to its interrupt
			// units is 1/24MHz
			auto bias = std::array<unsigned, 2>{0, 1000};
			cores.calc_partitions(times, bias);
		} else
			cores.calc_partitions(times);

		// Adjust indices since we skip module 0
		for (auto &part : cores.parts) {
			for (auto &idx : part)
				idx++;
		}
	}

	void print_times(std::span<unsigned> times, std::span<BrandModuleSlug> slugs) {
		// Debug output:
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = 0;
			for (auto idx : cores.parts[core]) {
				pr_dbg("Core %d: Module %u (%s): %u\n", core, idx, slugs[idx].c_str(), times[idx - 1]);
				sum += times[idx - 1];
			}
			pr_dbg("Core %d Total: %u\n", core, sum);
		}
	}
};

} // namespace MetaModule
