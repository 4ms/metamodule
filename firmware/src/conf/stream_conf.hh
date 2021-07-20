#pragma once
#include "drivers/codec_PCM3168.hh"
#include <cstdint>

struct StreamConf {
	struct Audio {
		using CodecT = mdrivlib::CodecPCM3168;

		static constexpr int BlockSize = 64;
		static constexpr int NumDMAHalfTransfers = 2;
		using SampleT = int32_t;
		static inline const int SampleBits = 24;
		static inline const int NumInChans = 6;
		static inline const int NumOutChans = 8;
		static constexpr int DMAInBlockSize = BlockSize * NumDMAHalfTransfers * NumInChans;
		static constexpr int DMAOutBlockSize = BlockSize * NumDMAHalfTransfers * NumOutChans;
	};
};
