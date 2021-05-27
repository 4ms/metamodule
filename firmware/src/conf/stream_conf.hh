#pragma once
#include <cstdint>

struct StreamConf {
	struct Audio {
		static constexpr int BlockSize = 64;
		static constexpr int NumDMAHalfTransfers = 2;
		static constexpr int DMABlockSize = BlockSize * NumDMAHalfTransfers;
		using SampleT = int32_t;
		static inline const int SampleBits = 24;
	};

	struct DAC {
		static constexpr int BlockSize = Audio::BlockSize;
		static constexpr int DMABlockSize = Audio::DMABlockSize;
		static constexpr int NumOutputs = 2;
		static constexpr int BufferSize = DMABlockSize * NumOutputs;
		using SampleT = uint32_t;
	};
};
