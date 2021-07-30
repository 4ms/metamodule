#pragma once
#include "util/audio_frame.hh"
#include <cstdint>

namespace MetaModule
{
//Dual PCM3168 Conf:
struct StreamConfDualCodec {
	struct Audio {

		//BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int BlockSize = 64;

		static constexpr int NumDMAHalfTransfers = 2;
		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 6;
		static constexpr int NumOutChans = 8;
		static constexpr int NumCodecs = 2;

		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;
		using AudioInBuffer = std::array<AudioInFrame, BlockSize>;
		struct AudioInBlock {
			AudioInBuffer codecA[2];
			AudioInBuffer codecB[2];
		};

		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;
		using AudioOutBuffer = std::array<AudioOutFrame, BlockSize>;
		struct AudioOutBlock {
			AudioOutBuffer codecA[2];
			AudioOutBuffer codecB[2];
		};

		struct CombinedAudioBlock {
			AudioInBuffer &in_codecA;
			AudioInBuffer &in_codecB;
			AudioOutBuffer &out_codecA;
			AudioOutBuffer &out_codecB;
		};
	};
};

using StreamConf = StreamConfDualCodec;

} // namespace MetaModule
