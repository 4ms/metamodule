#pragma once
#include "processors/tools/kneeCompress.h"
#include "audio_frame.hh"
#include "codec.hh"
#include "fxList.hh"
#include "hal_callback.hh"
#include "math.hh"
#include "oscs.hh"
#include "params.hh"
#include "stm32f7xx.h"
#include "util/interp_param.hh"
#include <array>

using AudioFrame = GenericAudioFrame<int32_t, 24>;

// Todo: multiple Audio objects would overwrite the HALCallback: add another
// param to HALLCallback ctor to give a process ID or SAI Periph# or HAL SAI
// handle
class Audio {
public:
	// Public methods:
	Audio(Params &p, ICodec &codec);
	void start();

	enum AudioChannels { LEFT, RIGHT };
	using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;

	void process(AudioStreamBlock &in, AudioStreamBlock &out);

private:
	void check_fx_change();

	AudioStreamBlock tx_buf_[2];
	AudioStreamBlock rx_buf_[2];
	Params &params;

	FXList FX_left;
	FXList FX_right;

	KneeCompressor<int32_t> compressor{24, 0.75};

	ICodec &codec_;
	uint32_t sample_rate_;

	static inline AudioProcessor *current_fx[2];

	Interp<float, kAudioStreamBlockSize> freq0;
	Interp<float, kAudioStreamBlockSize> freq1;
	Interp<float, kAudioStreamBlockSize> res0;
	Interp<float, kAudioStreamBlockSize> res1;

	HALCallback stream_complete{
		HALCallbackID::SAI_TxCplt,
		[this]() { process(rx_buf_[0], tx_buf_[1]); },
	};

	HALCallback stream_half_complete{
		HALCallbackID::SAI_TxHalfCplt,
		[this]() { process(rx_buf_[1], tx_buf_[0]); },
	};
};
