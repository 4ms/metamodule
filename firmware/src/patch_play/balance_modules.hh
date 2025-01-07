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

	void split_modules(std::span<std::unique_ptr<CoreProcessor>> modules, unsigned num_modules) {
		mdrivlib::CycleCounter counter;
		counter.init();
		std::vector<unsigned> times(num_modules - 1);

		for (size_t i = 1; i < num_modules; i++) {
			modules[i]->update();
			modules[i]->update();

			counter.start_measurement();
			for (auto j = 0; j < 512; j++) {
				modules[i]->update();
			}
			counter.end_measurement();

			times[i - 1] = counter.get_last_measurement_raw();
			pr_dbg("Module %u: %u\n", i, times[i - 1]);
		}

		cores.calculate(times);

		// Adjust indices since we skip module 0
		for (auto &a : cores.parts[0])
			a++;
		for (auto &b : cores.parts[0])
			b++;

		// Debug output:
		for (auto core = 0u; core < NumCores; core++) {
			unsigned sum = 0;
			for (auto idx : cores.parts[core]) {
				pr_dbg("Core %d: Module %u: %u\n", core, idx, times[idx - 1]);
				sum += times[idx - 1];
			}
			pr_dbg("Core %d: %u\n", core, sum);
		}

		// Tell the other core about the patch
		// smp.assign_modules(parts.parts[0]);
	}
};

} // namespace MetaModule
