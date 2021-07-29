#pragma once
#include "drivers/codec_PCM3168.hh"
#include <cstdint>

struct StreamConf {
	struct Audio {
		using CodecT = mdrivlib::CodecPCM3168;

		//BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int BlockSize = 64;

		static constexpr int NumDMAHalfTransfers = 2;
		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 6;
		static constexpr int NumOutChans = 8;
		static constexpr int NumCodecs = 2;
		// static constexpr int DMAInBlockSize = BlockSize * NumDMAHalfTransfers * NumInChans;
		// static constexpr int DMAOutBlockSize = BlockSize * NumDMAHalfTransfers * NumOutChans;
	};
};
