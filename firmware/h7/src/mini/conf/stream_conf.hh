#pragma once
#include "util/audio_frame.hh"
#include <cstdint>

namespace MetaModule
{

struct StreamConfSingleCodec2x2 {
	struct Audio {

		//BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int BlockSize = 64;

		static constexpr int NumDMAHalfTransfers = 2;
		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 2;
		static constexpr int NumOutChans = 2;

		static constexpr int NumCodecs = 1;

		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;
		using AudioInBuffer = std::array<AudioInFrame, BlockSize>;
		struct AudioInBlock {
			AudioInBuffer codec[2];
		};

		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;
		using AudioOutBuffer = std::array<AudioOutFrame, BlockSize>;
		struct AudioOutBlock {
			AudioOutBuffer codec[2];
		};

		struct CombinedAudioBlock {
			AudioInBuffer &in_codec;
			AudioOutBuffer &out_codec;
		};
	};

	struct DAC {
		static constexpr int BlockSize = Audio::BlockSize;
		static constexpr int DMABlockSize = BlockSize * 2;
		static constexpr int NumOutputs = 2;
		static constexpr int BufferSize = DMABlockSize * NumOutputs;
		using SampleT = uint32_t;
	};
};

using StreamConf = StreamConfSingleCodec2x2;

} // namespace MetaModule
