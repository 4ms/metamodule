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

// Todo: we don't need a codec virtual class, just use a type alias
class AudioStream {

public:
	using AudioInFrame = AudioFrame<AudioConf::SampleT, AudioConf::SampleBits, AudioConf::NumInChans>;
	using AudioOutFrame = AudioFrame<AudioConf::SampleT, AudioConf::SampleBits, AudioConf::NumOutChans>;
	using AudioInStreamBlock = std::array<AudioInFrame, AudioConf::BlockSize>;
	using AudioOutStreamBlock = std::array<AudioOutFrame, AudioConf::BlockSize>;

	AudioStream(PatchList &patches,
				PatchPlayer &patchplayer,
				CodecT &codec,
				ParamCache &cache,
				UiAudioMailbox &uiaudiomailbox,
				DoubleBufParamBlock &p,
				AudioInStreamBlock (&in_buffers)[4],
				AudioOutStreamBlock (&out_buffers)[4],
				AuxSignalStreamBlock (&auxsig)[2]);
	void start();

	void process(AudioInStreamBlock &in, AudioOutStreamBlock &out, ParamBlock &params, AuxSignalStreamBlock &aux);

private:
	ParamCache &cache;
	UiAudioMailbox &mbox;
	DoubleBufParamBlock &param_blocks;
	AudioOutStreamBlock &tx_buf_codecA_1;
	AudioOutStreamBlock &tx_buf_codecA_2;
	AudioOutStreamBlock &tx_buf_codecB_1;
	AudioOutStreamBlock &tx_buf_codecB_2;
	AudioInStreamBlock &rx_buf_codecA_1;
	AudioInStreamBlock &rx_buf_codecA_2;
	AudioInStreamBlock &rx_buf_codecB_1;
	AudioInStreamBlock &rx_buf_codecB_2;
	AuxSignalStreamBlock &auxsig_1;
	AuxSignalStreamBlock &auxsig_2;

	CodecT &codec_;
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

	void output_silence(AudioOutStreamBlock &out, AuxSignalStreamBlock &aux);
	void passthrough_audio(AudioInStreamBlock &in, AudioOutStreamBlock &out, AuxSignalStreamBlock &aux);
	void sines_out(AudioInStreamBlock &in, AudioOutStreamBlock &out);

	static constexpr unsigned NumKnobs = PanelDef::NumPot;
	static constexpr unsigned NumAudioInputs = PanelDef::NumAudioIn;
	static constexpr unsigned NumCVInputs = PanelDef::NumCVIn;
	static constexpr unsigned NumGateInputs = PanelDef::NumGateIn;
	static constexpr unsigned NumGateOutputs = PanelDef::NumGateOut;
	static constexpr unsigned NumAudioOutputs = PanelDef::NumAudioOut;
	static constexpr unsigned NumCVOutputs = PanelDef::NumDACOut;
};
} // namespace MetaModule
