#pragma once
#include "audio/auxsignal.hh"
#include "conf/board_codec_conf.hh"
#include "conf/stream_conf.hh"
#include "drivers/codec.hh"
#include "drivers/codec_PCM3168.hh"
#include "drivers/cycle_counter.hh"
#include "drivers/stm32xx.h"
#include "param_block.hh"
#include "params.hh"
#include "params_state.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "processors/tools/kneeCompress.h"
#include "sync_params.hh"
#include "util/calibrator.hh"
#include "util/edge_detector.hh"
#include "util/interp_param.hh"
#include "util/math.hh"
#include "util/oscs.hh"
#include <array>

namespace MetaModule
{

using AudioConf = StreamConf::Audio;

using AudioInFrame = AudioConf::AudioInFrame;
using AudioOutFrame = AudioConf::AudioOutFrame;
using AudioInBlock = AudioConf::AudioInBlock;
using AudioOutBlock = AudioConf::AudioOutBlock;
using AudioInBuffer = AudioConf::AudioInBuffer;
using AudioOutBuffer = AudioConf::AudioOutBuffer;
using CombinedAudioBlock = AudioConf::CombinedAudioBlock;

class AudioStream {
public:
	AudioStream(PatchPlayer &patchplayer,
				AudioInBlock &audio_in_block,
				AudioOutBlock &audio_out_block,
				SyncParams &sync_params,
				PatchPlayLoader &patchloader,
				DoubleBufParamBlock &p,
				DoubleAuxStreamBlock &auxs,
				PatchModQueue &patch_mod_queue);

	void start();

	void process(CombinedAudioBlock &audio, ParamBlock &param_block, AuxStreamBlock &aux);

private:
	SyncParams &sync_params;
	ParamsState param_state;
	PatchPlayLoader &patch_loader;
	DoubleBufParamBlock &param_blocks;
	CombinedAudioBlock audio_blocks[2];
	DoubleAuxStreamBlock &auxsigs;
	PatchModQueue &patch_mod_queue;

	CodecT &codec_;
	CodecT &codec_ext_;
	uint32_t sample_rate_;

	Calibrator incal[PanelDef::NumAudioIn];
	EdgeStateDetector plug_detects[PanelDef::NumJacks];

	std::array<uint32_t, 2> midi_clk_ctr;

	// Todo: this stuff is a different abstraction level than codec/samplerate/tx_buf/rx_buf etc
	// Should we class this out? It's only connected to Audio at init and process()

	PatchPlayer &player;
	KneeCompressor<int32_t> compressor{AudioConf::SampleBits, 0.75};
	mdrivlib::CycleCounter load_measure;
	float load_lpf = 0.f;
	float mute_ctr = 1.f;
	uint32_t halves_muted = 0;
	bool ext_audio_connected = false;

	AudioConf::SampleT get_audio_output(int output_id);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change(int motion);
	void send_zeros_to_patch();
	void propagate_sense_pins(Params &params);
	void update_midi_pulses();

	// void output_silence(AudioOutBuffer &out, AuxStreamBlock &aux);

	static constexpr unsigned NumKnobs = PanelDef::NumPot;
	static constexpr unsigned NumAudioInputs = PanelDef::NumAudioIn;
	static constexpr unsigned NumCVInputs = PanelDef::NumCVIn;
	static constexpr unsigned NumGateInputs = PanelDef::NumGateIn;
	static constexpr unsigned NumGateOutputs = PanelDef::NumGateOut;
	static constexpr unsigned NumAudioOutputs = PanelDef::NumAudioOut;
	static constexpr unsigned NumCVOutputs = PanelDef::NumDACOut;

	static constexpr unsigned FirstAudioInput = 0;
	static constexpr unsigned FirstCVInput = NumAudioInputs;
	static constexpr unsigned FirstGateInput = FirstCVInput + NumCVInputs;
};
} // namespace MetaModule
