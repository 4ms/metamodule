#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

namespace MetaModule
{

struct AudioSettings {
	static constexpr std::array ValidSampleRates = {24000u, 32000u, 48000u, 96000u};
	static constexpr std::array ValidBlockSizes = {16u, 32u, 64u, 128u, 256u, 512u};
	static constexpr std::array ValidOverrunRetries = {0u, 4u, 8u, 16u, 32u, 64u, 128u, 256u};

	static constexpr uint32_t DefaultSampleRate = 48000;
	static constexpr uint32_t DefaultBlockSize = 64;
	static constexpr uint32_t DefaultOverrunRetries = 16;

	uint32_t sample_rate = DefaultSampleRate;
	uint32_t block_size = DefaultBlockSize;
	uint32_t max_overrun_retries = DefaultOverrunRetries;

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
	}
};

} // namespace MetaModule
