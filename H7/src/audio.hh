#pragma once
#include "conf/stream_conf.hh"
#include "drivers/codec.hh"
#include "drivers/stm32xx.h"
#include "params.hh"
#include "patch_player.hh"
#include "processors/tools/kneeCompress.h"
#include "util/audio_frame.hh"
#include "util/interp_param.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <array>

using AudioConf = StreamConf::Audio;

class AudioStream {

public:
	using AudioFrame = GenericAudioFrame<AudioConf::SampleT, AudioConf::SampleBits>;
	using AudioStreamBlock = std::array<AudioFrame, AudioConf::BlockSize>;
	enum AudioChannels { LEFT, RIGHT };

	// Public methods:
	AudioStream(Params &p, ICodec &codec, AudioStreamBlock (&buffers)[4]);
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
	AudioConf::SampleT get_output(int output_id);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change();

	Params &params;
	PatchPlayer player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};

	static constexpr unsigned NumKnobs = PatchPlayer::get_num_panel_knobs();
	static constexpr unsigned NumAudioInputs = 2;
	static constexpr unsigned NumCVInputs = PatchPlayer::get_num_panel_inputs() - NumAudioInputs;
	static constexpr unsigned NumAudioOutputs = 2;
	static constexpr unsigned NumCVOutputs = PatchPlayer::get_num_panel_outputs() - NumAudioOutputs;

	std::array<Interp<float, AudioConf::BlockSize>, NumCVInputs> cvjacks;
	std::array<Interp<float, AudioConf::BlockSize>, NumKnobs> knobs;

	uint32_t last_start_tm = 0;
};
