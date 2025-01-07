#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "drivers/cycle_counter.hh"
#include "util/partition.hh"
#include <memory>
#include <vector>

#include "console/pr_dbg.hh"

namespace MetaModule
{

template<size_t NumCores, size_t MaxModules>
struct Balancer {
	Partition<NumCores, MaxModules> cores;

	void split_modules(std::span<std::unique_ptr<CoreProcessor>> modules, unsigned num_modules, auto &&prepare) {
		mdrivlib::CycleCounter counter;
		counter.init();
		std::vector<unsigned> times(num_modules - 1, 0);

		for (auto iter_i = 0; iter_i < 512 + 32; iter_i++) {

			for (size_t module_i = 1; module_i < num_modules; module_i++) {

				counter.start_measurement();
				modules[module_i]->update();
				counter.end_measurement();

				// Discard first 32 runs
				if (iter_i >= 32)
					times[module_i - 1] += counter.get_last_measurement_raw();
			}

			prepare();
		}

		for (size_t module_i = 1; module_i < num_modules; module_i++) {
			pr_dbg("Module %u: %u\n", module_i, times[module_i - 1]);
		}

		if (NumCores == 2) {
			auto bias = std::array<unsigned, 2>{0, 1000};
			cores.calc_partitions(times, bias);
		} else
			cores.calc_partitions(times);

		// Adjust indices since we skip module 0
		for (auto &part : cores.parts) {
			for (auto &idx : part)
				idx++;
		}

		// Debug output:
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = 0;
			for (auto idx : cores.parts[core]) {
				pr_dbg("Core %d: Module %u: %u\n", core, idx, times[idx - 1]);
				sum += times[idx - 1];
			}
			pr_dbg("Core %d Total: %u\n", core, sum);
		}
	}
};

} // namespace MetaModule
