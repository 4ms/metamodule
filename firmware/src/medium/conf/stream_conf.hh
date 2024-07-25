#pragma once
#include "util/audio_frame.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

struct StreamConfSingleCodec6x8 {
	struct Audio {

		// BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int MaxBlockSize = 512;

		static constexpr int NumDMAHalfTransfers = 2;

		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 6;
		static constexpr int NumOutChans = 8;

		static constexpr int NumCodecs = 2; //not used anywhere

		// One frame: data for all input channels at a single moment of time
		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;

		// A group of frames that are processed at the same time.
		using AudioInBuffer = std::array<AudioInFrame, MaxBlockSize>;

		// Total memory allocated for audio stream input DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(64) AudioInBlock {
			AudioInBuffer codec[NumDMAHalfTransfers];
			AudioInBuffer ext_codec[NumDMAHalfTransfers];
		};

		// One frame: data for all output channels at a single moment of time
		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;

		// A group of frames that are processed at the same time.
		using AudioOutBuffer = std::array<AudioOutFrame, MaxBlockSize>;

		// Total memory allocated for audio stream output DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(64) AudioOutBlock {
			AudioOutBuffer codec[NumDMAHalfTransfers];
			AudioOutBuffer ext_codec[NumDMAHalfTransfers];
		};

		// A handy struct used to call the audio process() function
		// It's just a reference to the actual daya.
		// Since the memory layout for the DMA buffers is fixed, using
		// references makes it easier to refer to what we need to use
		// suring each call to process()
		struct CombinedAudioBlock {
			std::span<AudioInFrame> in_codec;
			std::span<AudioOutFrame> out_codec;
			std::span<AudioInFrame> in_ext_codec;
			std::span<AudioOutFrame> out_ext_codec;
		};
	};
};

using StreamConf = StreamConfSingleCodec6x8;

} // namespace MetaModule
