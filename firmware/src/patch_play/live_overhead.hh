#pragma once
#include "patch_play/live_load.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <span>

namespace MetaModule
{

// The patch player's time beyond running modules and cables, split the way the
// Load Balance panel shows it. Values are ppm of the audio block period.
struct LiveOverhead {
	uint32_t mappings = 0;
	uint32_t midi = 0;
	uint32_t sync = 0; // Core 1 waiting beyond the busiest core
	uint32_t other = 0;
	uint32_t max_core = 0; // busiest core's modules + cables

	uint32_t total() const {
		return mappings + midi + sync + other;
	}

	uint16_t total_tenths() const {
		return static_cast<uint16_t>((total() + 500u) / 1000u);
	}
};

// Both cores run their modules and cables in parallel, then Core 1 does the overhead.
// Core 1 waiting for Core 2 (sync) only counts beyond the busiest core's time.
// module_cores[module_id] is the core each module runs on (empty: no load balance info).
inline LiveOverhead live_overhead(LiveLoadMeter::Loads const &live, std::span<const uint16_t> module_cores) {
	constexpr auto NumCores = LiveLoadMeter::MaxCores;

	std::array<uint32_t, NumCores> core_ppm{};
	core_ppm[0] = live.cables * 1000u;
	if constexpr (NumCores > 1)
		core_ppm[1] = live.core2_cables * 1000u;

	for (auto module_id = 1u; module_id < module_cores.size() && module_id < live.modules.size(); module_id++) {
		if (auto core = module_cores[module_id]; core < NumCores)
			core_ppm[core] += live.modules[module_id] * 1000u;
	}

	LiveOverhead oh;
	oh.max_core = *std::ranges::max_element(core_ppm);
	oh.mappings = live.mappings * 1000u;
	oh.midi = live.midi * 1000u;
	oh.other = live.overhead * 1000u;

	if (!module_cores.empty()) {
		auto core1_parallel = core_ppm[0] + (live.sync + live.sync2) * 1000u;
		oh.sync = core1_parallel > oh.max_core ? core1_parallel - oh.max_core : 0;
	}

	return oh;
}

} // namespace MetaModule
