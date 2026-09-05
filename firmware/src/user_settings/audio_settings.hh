#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct AudioSettings {
	static constexpr std::array ValidSampleRates = {24000u, 32000u, 48000u, 96000u};
	static constexpr std::array ValidBlockSizes = {16u, 32u, 64u, 128u, 256u, 512u};
	static constexpr std::array ValidOverrunRetries = {0u, 1u, 2u, 4u, 8u, 16u, 32u, 64u};

	// When to automatically run the CPU load re-balancing trials
	enum class AutoRebalance : uint8_t { Off, AfterOverload, EveryLoad };

	struct AutoRebalanceOption {
		AutoRebalance value;
		std::string_view label;
	};
	static constexpr std::array ValidAutoRebalance = {
		AutoRebalanceOption{AutoRebalance::Off, "Off"},
		AutoRebalanceOption{AutoRebalance::AfterOverload, "After Overload"},
		AutoRebalanceOption{AutoRebalance::EveryLoad, "Every Patch Load"},
	};

	static constexpr uint32_t DefaultSampleRate = 48000;
	static constexpr uint32_t DefaultBlockSize = 64;
	static constexpr uint32_t DefaultOverrunRetries = 2u;
	static constexpr AutoRebalance DefaultAutoRebalance = AutoRebalance::AfterOverload;

	uint32_t sample_rate = DefaultSampleRate;
	uint32_t block_size = DefaultBlockSize;
	uint32_t max_overrun_retries = DefaultOverrunRetries;
	AutoRebalance auto_rebalance = DefaultAutoRebalance;

	void make_valid() {
		if (std::ranges::find(ValidSampleRates, sample_rate) == std::end(ValidSampleRates)) {
			sample_rate = DefaultSampleRate;
		}

		if (std::ranges::find(ValidBlockSizes, block_size) == std::end(ValidBlockSizes)) {
			block_size = DefaultBlockSize;
		}

		if (std::ranges::find(ValidOverrunRetries, max_overrun_retries) == std::end(ValidOverrunRetries)) {
			max_overrun_retries = DefaultOverrunRetries;
		}

		if (std::ranges::find(ValidAutoRebalance, auto_rebalance, &AutoRebalanceOption::value) ==
			std::end(ValidAutoRebalance))
		{
			auto_rebalance = DefaultAutoRebalance;
		}
	}
};

} // namespace MetaModule
