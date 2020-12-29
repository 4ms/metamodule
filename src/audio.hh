#pragma once
#include "drivers/codec.hh"
// #include "fxList.hh"
#include "interp_param.hh"
#include "math.hh"
#include "oscs.hh"
#include "params.hh"
#include "processors/tools/kneeCompress.h"
#include "stm32f7xx.h"
#include "util/audio_frame.hh"
#include <array>

class Audio {
	using AudioSampleType = int32_t;			  // todo: put this in a config header?
	static inline const int AudioSampleBits = 24; // todo: put this in a config header?

public:
	using AudioFrame = GenericAudioFrame<AudioSampleType, AudioSampleBits>;
	using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;
	enum AudioChannels { LEFT, RIGHT };

	// Public methods:
	Audio(Params &p, ICodec &codec, AudioStreamBlock (&buffers)[4]);
	void start();

	void process(AudioStreamBlock &in, AudioStreamBlock &out);

private:
	AudioSampleType process_chan(AudioSampleType in, int output_id);
	void check_fx_change();

	AudioStreamBlock &tx_buf_1;
	AudioStreamBlock &tx_buf_2;
	AudioStreamBlock &rx_buf_1;
	AudioStreamBlock &rx_buf_2;
	Params &params;

	PatchPlayer player;
	// FXList FX_left;
	// FXList FX_right;

	KneeCompressor<int32_t> compressor{AudioSampleBits, 0.75};

	ICodec &codec_;
	uint32_t sample_rate_;

	static inline AudioProcessor *current_fx[2];

	Interp<float, kAudioStreamBlockSize> freq0;
	Interp<float, kAudioStreamBlockSize> freq1;
	Interp<float, kAudioStreamBlockSize> res0;
	Interp<float, kAudioStreamBlockSize> res1;
};
