#pragma once
#include "drivers/codec.hh"
#include "interp_param.hh"
#include "math.hh"
#include "oscs.hh"
#include "params.hh"
#include "patch_player.hh"
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
	AudioStreamBlock &tx_buf_1;
	AudioStreamBlock &tx_buf_2;
	AudioStreamBlock &rx_buf_1;
	AudioStreamBlock &rx_buf_2;

	ICodec &codec_;
	uint32_t sample_rate_;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()
	AudioSampleType get_output(int output_id);
	void check_patch_change();

	Params &params;
	PatchPlayer player;
	KneeCompressor<int32_t> compressor{AudioSampleBits, 0.75};

	std::array<Interp<float, kAudioStreamBlockSize>, 4> cvjacks;
	std::array<Interp<float, kAudioStreamBlockSize>, 4> knobs;
};
