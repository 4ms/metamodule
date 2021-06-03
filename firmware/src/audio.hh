#pragma once
#include "auxsignal.hh"
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
				AudioStreamBlock (&buffers)[4],
				AuxSignalStreamBlock (&auxsig)[2]);
	void start();

	void process(AudioStreamBlock &in, AudioStreamBlock &out, ParamBlock &params, AuxSignalStreamBlock &aux);

private:
	ParamCache &cache;
	UiAudioMailbox &mbox;
	DoubleBufParamBlock &param_blocks;
	AudioStreamBlock &tx_buf_1;
	AudioStreamBlock &tx_buf_2;
	AudioStreamBlock &rx_buf_1;
	AudioStreamBlock &rx_buf_2;
	AuxSignalStreamBlock &auxsig_1;
	AuxSignalStreamBlock &auxsig_2;

	ICodec &codec_;
	uint32_t sample_rate_;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()

	PatchList &patch_list;
	PatchPlayer &player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};
	CycleCounter load_measure;
	uint32_t _mute_ctr = 0;

	AudioConf::SampleT get_audio_output(int output_id);
	uint32_t get_dac_output(int output_id);
	void output_silence(AudioStreamBlock &out, AuxSignalStreamBlock &aux);
	void passthrough_audio(AudioStreamBlock &in, AudioStreamBlock &out, AuxSignalStreamBlock &aux);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change(int motion);
	void send_zeros_to_patch();
	void propagate_sense_pins(Params &params);

	static constexpr unsigned NumKnobs = PanelDef::NumPot;
	static constexpr unsigned NumAudioInputs = PanelDef::NumAudioIn;
	static constexpr unsigned NumCVInputs = PanelDef::NumCVIn;
	static constexpr unsigned NumGateInputs = PanelDef::NumGateIn;
	static constexpr unsigned NumGateOutputs = PanelDef::NumGateOut;
	static constexpr unsigned NumAudioOutputs = PanelDef::NumAudioOut;
	static constexpr unsigned NumCVOutputs = PanelDef::NumDACOut;

	static constexpr uint32_t LEFT_OUT = (target::TYPE == SupportedTargets::stm32h7x5) ? 1 : 0;
	static constexpr uint32_t RIGHT_OUT = 1 - LEFT_OUT;
};
} // namespace MetaModule
