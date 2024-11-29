#pragma once

#include <array>
#include <cstdint>

namespace MetaModule
{

struct AudioSettings {
	static constexpr std::array ValidSampleRates = {24000u, 32000u, 48000u, 96000u};
	static constexpr std::array ValidBlockSizes = {16u, 32u, 64u, 128u, 256u, 512u};

	static constexpr uint32_t DefaultSampleRate = 48000;
	static constexpr uint32_t DefaultBlockSize = 64;

	uint32_t sample_rate = DefaultSampleRate;
	uint32_t block_size = DefaultBlockSize;

	void make_valid() {

		bool valid = false;
		for (auto sr : ValidSampleRates) {
			if (sample_rate == sr)
				valid = true;
		}
		if (!valid)
			sample_rate = DefaultSampleRate;

		valid = false;
		for (auto sz : ValidBlockSizes) {
			if (block_size == sz)
				valid = true;
		}
		if (!valid)
			block_size = DefaultBlockSize;
	}
};

} // namespace MetaModule
