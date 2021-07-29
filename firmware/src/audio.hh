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
#include "util/audio_frame.hh"
#include "util/interp_param.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <array>

using namespace mdrivlib;
namespace MetaModule
{
using AudioConf = StreamConf::Audio;
using CodecT = StreamConf::Audio::CodecT;

class AudioStream {

public:
	using AudioInFrame = AudioFrame<AudioConf::SampleT, AudioConf::SampleBits, AudioConf::NumInChans>;
	using AudioInBuffer = std::array<AudioInFrame, AudioConf::BlockSize>;
	struct AudioInBlock {
		AudioInBuffer codecA[2];
		AudioInBuffer codecB[2];
	};

	using AudioOutFrame = AudioFrame<AudioConf::SampleT, AudioConf::SampleBits, AudioConf::NumOutChans>;
	using AudioOutBuffer = std::array<AudioOutFrame, AudioConf::BlockSize>;
	struct AudioOutBlock {
		AudioOutBuffer codecA[2];
		AudioOutBuffer codecB[2];
	};

	struct CombinedAudioBlock {
		AudioInBuffer &in_codecA;
		AudioInBuffer &in_codecB;
		AudioOutBuffer &out_codecA;
		AudioOutBuffer &out_codecB;
	};

	AudioStream(PatchList &patches,
				PatchPlayer &patchplayer,
				CodecT &codecA,
				CodecT &codecB,
				ParamCache &cache,
				UiAudioMailbox &uiaudiomailbox,
				DoubleBufParamBlock &p,
				AudioInBlock &audio_in_block,
				AudioOutBlock &audio_out_block,
				DoubleAuxSignalStreamBlock &auxs);
	void start();

	void process(CombinedAudioBlock &audio, ParamBlock &param_block, AuxSignalStreamBlock &aux);

private:
	ParamCache &cache;
	UiAudioMailbox &mbox;
	DoubleBufParamBlock &param_blocks;
	CombinedAudioBlock audio_blocks[2];
	DoubleAuxSignalStreamBlock &auxsigs;

	CodecT &codecA_;
	CodecT &codecB_;
	uint32_t sample_rate_;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()

	PatchList &patch_list;
	PatchPlayer &player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};
	CycleCounter load_measure;
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
