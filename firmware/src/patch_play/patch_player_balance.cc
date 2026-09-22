#include "coreproc_plugin/async_thread_control.hh"
#include "patch_play/patch_player.hh"

namespace MetaModule
{

void PatchPlayer::rebalance_modules(Balance mode) {
	if (num_modules > 2) {

		if (mode == Balance::UseStored && pd.has_load_balance(MulticorePlayer::NumCores)) {
			// The patch contained load balance info, so use it
			core_balancer.apply_stored_balance(pd.module_cores);

		} else { // Re-calculating, or calculating for the first time

			auto cpu_times = core_balancer.measure_modules(
				modules, num_modules, [this](unsigned module_i) { step_module(module_i); });

			// When re-calculating, pass the previous assignment so the balancer
			// prefers a different one
			auto prev = std::span<const uint16_t>{};
			if (mode == Balance::Recalculate && pd.has_load_balance(MulticorePlayer::NumCores))
				prev = pd.module_cores;

			auto arrangement = core_balancer.balance_loads(cpu_times, prev);

			store_load_balance(arrangement, cpu_times);

			core_balancer.print_times(cpu_times, pd.module_slugs);
		}

	} else if (num_modules == 2) {
		// A single module doesn't get split, but still measure it so its load can be shown
		if (!(mode == Balance::UseStored && pd.has_load_balance(MulticorePlayer::NumCores))) {
			auto cpu_times = core_balancer.measure_modules(
				modules, num_modules, [this](unsigned module_i) { step_module(module_i); });

			// Default arrangement: the module runs on core 0
			store_load_balance(CoreBalancer::Arrangement{}, cpu_times);
		}
		core_balancer.apply_stored_balance(pd.module_cores);

	} else {
		core_balancer.cores.parts[0].clear();
		core_balancer.cores.parts[1].clear();
		pd.clear_load_balance();
	}

	// Tell other SMP core which modules it's been assigned
	smp.assign_modules(core_balancer.cores.parts[MulticorePlayer::NumCores - 1]);

	for (auto core_id = 0u; core_id < core_balancer.cores.parts.size(); core_id++) {
		for (auto id : core_balancer.cores.parts[core_id]) {
			peg_task_to_core(id, core_id);
		}
	}

	cables.build(pd.int_cables, core_balancer.cores.parts, modules);
}

// Records the load balance in the patch data, so it can be saved to the patch file
// and re-used the next time the patch is loaded.
void PatchPlayer::store_load_balance(CoreBalancer::Arrangement const &arrangement,
									 std::span<const unsigned> cpu_times) {
	pd.module_cores.assign(num_modules, 0);
	pd.module_loads.assign(num_modules, 0);

	for (auto module_id = 1u; module_id < num_modules; module_id++) {
		pd.module_cores[module_id] = arrangement.core_of[module_id];
		pd.module_loads[module_id] = core_balancer.ticks_to_ppm(cpu_times[module_id - 1]);
	}
}

PatchPlayer::BalanceCandidates PatchPlayer::make_balance_candidates(unsigned num_seeds) {
	BalanceCandidates result;

	if (num_modules <= 2)
		return result;

	auto cpu_times =
		core_balancer.measure_modules(modules, num_modules, [this](unsigned module_i) { step_module(module_i); });

	result.loads_ppm.assign(num_modules, 0);
	for (auto module_id = 1u; module_id < num_modules; module_id++)
		result.loads_ppm[module_id] = core_balancer.ticks_to_ppm(cpu_times[module_id - 1]);

	if (pd.has_load_balance(MulticorePlayer::NumCores))
		result.cores.push_back(pd.module_cores);

	for (auto seed = 0u; seed < num_seeds; seed++) {
		auto arr = CoreBalancer::make_arrangement(cpu_times, seed == 0 ? 0 : seed * 2654435761u);

		std::vector<uint16_t> cores(num_modules, 0);
		for (auto module_id = 1u; module_id < num_modules; module_id++)
			cores[module_id] = arr.core_of[module_id];

		// Skip duplicates: different seeds often produce the same arrangement
		if (std::ranges::find(result.cores, cores) == result.cores.end())
			result.cores.push_back(cores);
	}

	return result;
}

// Applies a load balance the user chose, without re-measuring anything
void PatchPlayer::set_load_balance(std::vector<uint16_t> const &module_cores,
								   std::vector<uint32_t> const &module_loads) {
	if (module_cores.size() != num_modules)
		return;

	pd.module_cores = module_cores;
	pd.module_loads = module_loads;
	rebalance_modules(Balance::UseStored);
}

} // namespace MetaModule
