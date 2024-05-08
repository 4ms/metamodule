#pragma once
#include "util/audio_frame.hh"
#include <cstdint>

namespace MetaModule
{

struct StreamConfSingleCodec6x8 {
	struct Audio {

		// BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int BlockSize = 128; //block size 128 works with Rings

		// static constexpr int NumDMAHalfTransfers = 2;
		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 6;
		static constexpr int NumOutChans = 8;

		static constexpr int NumCodecs = 2; //not used anywhere

		// One frame: data for all input channels at a single moment of time
		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;

		// A group of frames that are processed at the same time.
		using AudioInBuffer = std::array<AudioInFrame, BlockSize>;

		// Total memory allocated for audio stream input DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(1024) AudioInBlock {
			AudioInBuffer codec[2];
			AudioInBuffer ext_codec[2];
		};

		// One frame: data for all output channels at a single moment of time
		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;

		// A group of frames that are processed at the same time.
		using AudioOutBuffer = std::array<AudioOutFrame, BlockSize>;

		// Total memory allocated for audio stream output DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(1024) AudioOutBlock {
			AudioOutBuffer codec[2];
			AudioOutBuffer ext_codec[2];
		};

		// A handy struct used to call the audio process() function
		// It's just a reference to the actual daya.
		// Since the memory layout for the DMA buffers is fixed, using
		// references makes it easier to refer to what we need to use
		// suring each call to process()
		struct CombinedAudioBlock {
			AudioInBuffer &in_codec;
			AudioOutBuffer &out_codec;
			AudioInBuffer &in_ext_codec;
			AudioOutBuffer &out_ext_codec;
		};
	};
};

using StreamConf = StreamConfSingleCodec6x8;

} // namespace MetaModule
