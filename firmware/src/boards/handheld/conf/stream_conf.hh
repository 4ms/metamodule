#pragma once
#include "util/audio_frame.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

struct StreamConf {
	struct Audio {

		// BlockSize: Number of Frames processed each time AudioStream::process() is called
		static constexpr int MaxBlockSize = 512;

		static constexpr int NumDMAHalfTransfers = 2;

		using SampleT = int32_t;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 2;
		static constexpr int NumOutChans = 2;

		// One frame: data for all input channels at a single moment of time
		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;

		// A group of frames that are processed at the same time.
		using AudioInBuffer = std::array<AudioInFrame, MaxBlockSize>;

		// Total memory allocated for audio stream input DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(64) AudioInBlock {
			AudioInBuffer codec[NumDMAHalfTransfers];
		};

		// One frame: data for all output channels at a single moment of time
		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;

		// A group of frames that are processed at the same time.
		using AudioOutBuffer = std::array<AudioOutFrame, MaxBlockSize>;

		// Total memory allocated for audio stream output DMA buffers
		// There are [2] blocks per codec, one for each half-transfer
		struct alignas(64) AudioOutBlock {
			AudioOutBuffer codec[NumDMAHalfTransfers];
		};

		// Mic
		using MicSampleT = int8_t;
		static constexpr int NumMics = 1;
		static constexpr int MicBits = 8;
		using MicInFrame = AudioFrame<MicSampleT, 8, NumMics>;
		using MicInBuffer = std::array<MicInFrame, MaxBlockSize>;
		struct alignas(64) MicInBlock {
			MicInBuffer halfblock[NumDMAHalfTransfers];
		};

		// A handy struct used to call the audio process() function
		// It's just a reference to the actual data.
		// Since the memory layout for the DMA buffers is fixed, using
		// references makes it easier to refer to what we need to use
		// suring each call to process()
		struct CombinedAudioBlock {
			std::span<AudioInFrame> in_codec;
			std::span<AudioOutFrame> out_codec;
			std::span<MicInFrame> in_mic;
		};
	};
};

} // namespace MetaModule
