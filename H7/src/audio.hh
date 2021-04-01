#pragma once
#include "conf/dac_conf.hh"
#include "conf/stream_conf.hh"
#include "drivers/codec.hh"
#include "drivers/cycle_counter.hh"
#include "drivers/stm32xx.h"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "processors/tools/kneeCompress.h"
#include "util/audio_frame.hh"
#include "util/interp_param.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <array>

using namespace mdrivlib;
namespace MetaModule
{
using AudioConf = StreamConf::Audio;

// Todo: we don't need a codec virtual class, just use a type alias
class AudioStream {

public:
	using AudioFrame = GenericAudioFrame<AudioConf::SampleT, AudioConf::SampleBits>;
	using AudioStreamBlock = std::array<AudioFrame, AudioConf::BlockSize>;
	enum AudioChannels { LEFT, RIGHT };

	AudioStream(PatchList &patches,
				PatchPlayer &patchplayer,
				ICodec &codec,
				AnalogOutT &dac,
				ParamCache &cache,
				UiAudioMailbox &uiaudiomailbox,
				DoubleBufParamBlock &p,
				AudioStreamBlock (&buffers)[4]);
	void start();

	void process(AudioStreamBlock &in, AudioStreamBlock &out, ParamBlock &params);

private:
	ParamCache &cache;
	UiAudioMailbox &mbox;
	DoubleBufParamBlock &param_blocks;
	AudioStreamBlock &tx_buf_1;
	AudioStreamBlock &tx_buf_2;
	AudioStreamBlock &rx_buf_1;
	AudioStreamBlock &rx_buf_2;

	ICodec &codec_;
	uint32_t sample_rate_;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()

	AnalogOutT &dac;
	PinChangeInterrupt dac_updater;
	PatchList &patch_list;
	PatchPlayer &player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};
	CycleCounter load_measure;
	uint32_t _mute_ctr = 0;

	AudioConf::SampleT get_output(int output_id);
	void output_silence(AudioStreamBlock &out);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change(int motion);
	void load_patch();

	static constexpr unsigned NumKnobs = PatchPlayer::get_num_panel_knobs();
	static constexpr unsigned NumAudioInputs = 2;
	static constexpr unsigned NumCVInputs = PatchPlayer::get_num_panel_inputs() - NumAudioInputs;
	static constexpr unsigned NumAudioOutputs = 2;
	static constexpr unsigned NumCVOutputs = PatchPlayer::get_num_panel_outputs() - NumAudioOutputs;
};
} // namespace MetaModule
