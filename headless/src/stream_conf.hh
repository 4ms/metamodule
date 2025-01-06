#pragma once
#include "util/audio_frame.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

struct StreamConfSim {
	struct Audio {

		// BlockSize: Number of Frames processed each time AudioStream::process() is called
		// For the simulator, it's set by SDL at runtime
		// static constexpr int BlockSize = 512;

		using SampleT = float;
		static constexpr int SampleBits = 24;
		static constexpr int NumInChans = 6;
		static constexpr int NumOutChans = 8;

		// One frame: data for all input channels at a single moment of time
		using AudioInFrame = AudioFrame<SampleT, SampleBits, NumInChans>;

		// A group of frames that are processed at the same time.
		using AudioInBuffer = std::span<const AudioInFrame>;

		// One frame: data for all output channels at a single moment of time
		using AudioOutFrame = AudioFrame<SampleT, SampleBits, NumOutChans>;

		// A group of frames that are processed at the same time.
		using AudioOutBuffer = std::span<AudioOutFrame>;
	};
};

} // namespace MetaModule
