#pragma once
#include "auxsignal.hh"
#include "conf/stream_conf.hh"
#include "drivers/codec.hh"
#include "drivers/cycle_counter.hh"
#include "drivers/stm32xx.h"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "processors/tools/kneeCompress.h"
#include "util/interp_param.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <array>

namespace MetaModule
{
//using namespace mdrivlib;

using AudioConf = StreamConf::Audio;

using AudioInBlock = AudioConf::AudioInBlock;
using AudioOutBlock = AudioConf::AudioOutBlock;
using AudioInBuffer = AudioConf::AudioInBuffer;
using AudioOutBuffer = AudioConf::AudioOutBuffer;

using CodecT = AudioConf::CodecT;

class AudioStream {
public:
	AudioStream(PatchList &patches,
				PatchPlayer &patchplayer,
				CodecT &codecA,
				CodecT &codecB,
				AudioInBlock &audio_in_block,
				AudioOutBlock &audio_out_block,
				ParamCache &cache,
				UiAudioMailbox &uiaudiomailbox,
				DoubleBufParamBlock &p,
				DoubleAuxSignalStreamBlock &auxs);

	void start();

	void process(AudioConf::CombinedAudioBlock &audio, ParamBlock &param_block, AuxSignalStreamBlock &aux);

private:
	ParamCache &cache;
	UiAudioMailbox &mbox;
	DoubleBufParamBlock &param_blocks;
	AudioConf::CombinedAudioBlock audio_blocks[2];
	DoubleAuxSignalStreamBlock &auxsigs;

	CodecT &codecA_;
	CodecT &codecB_;
	uint32_t sample_rate_;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()

	PatchList &patch_list;
	PatchPlayer &player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};
	mdrivlib::CycleCounter load_measure;
	uint32_t _mute_ctr = 0;

	AudioConf::SampleT get_audio_output(int output_id);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change(int motion);
	void send_zeros_to_patch();
	void propagate_sense_pins(Params &params);

	void output_silence(AudioOutBuffer &out, AuxSignalStreamBlock &aux);
	void passthrough_audio(AudioInBuffer &in, AudioOutBuffer &out, AuxSignalStreamBlock &aux);
	void sines_out(AudioInBuffer &in, AudioOutBuffer &out);

	void dual_sines_out(AudioOutBuffer &outA, AudioOutBuffer &outB);
	void dual_passthrough(
		AudioInBuffer &inA, AudioOutBuffer &outA, AudioInBuffer &inB, AudioOutBuffer &outB, AuxSignalStreamBlock &aux);

	static constexpr unsigned NumKnobs = PanelDef::NumPot;
	static constexpr unsigned NumAudioInputs = PanelDef::NumAudioIn;
	static constexpr unsigned NumCVInputs = PanelDef::NumCVIn;
	static constexpr unsigned NumGateInputs = PanelDef::NumGateIn;
	static constexpr unsigned NumGateOutputs = PanelDef::NumGateOut;
	static constexpr unsigned NumAudioOutputs = PanelDef::NumAudioOut;
	static constexpr unsigned NumCVOutputs = PanelDef::NumDACOut;
};
} // namespace MetaModule
