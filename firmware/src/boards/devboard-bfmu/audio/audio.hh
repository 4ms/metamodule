#pragma once
#include "audio/midi.hh"
#include "calibrate/calibration_data.hh"
#include "conf/board_codec_conf.hh"
#include "conf/stream_conf.hh"
#include "drivers/cycle_counter.hh"
#include "param_block.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "util/edge_detector.hh"

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
				DoubleBufParamBlock &p);

	void start();
	void start_playing();
	void process(CombinedAudioBlock &audio, ParamBlock &param_block);
	uint32_t get_audio_errors();

private:
	SyncParams &sync_params;
	ParamsState param_state;
	PatchPlayLoader &patch_loader;
	DoubleBufParamBlock &param_blocks;
	CombinedAudioBlock audio_blocks[2];

	AudioInBlock &audio_in_block;
	AudioOutBlock &audio_out_block;

	PatchPlayer &player;

	AudioStreamMidi midi;
	unsigned cur_block = 0;

	// Hardware interface
	CodecT &codec_;
	uint32_t sample_rate_;
	uint32_t block_size_;

	// Load measurement
	mdrivlib::CycleCounter load_measure;
	float load_lpf = 0.f;

	CalData cal;

	// Local
	ParamBlock local_params;

	AudioConf::SampleT get_audio_output(int output_id);
	void set_input(int input_id, AudioConf::SampleT in);

	void handle_patch_just_loaded();
	void update_audio_settings();
	void set_block_spans();
	ParamBlock &cache_params(unsigned block);
	void return_cached_params(unsigned block);

public:
	void set_calibration(CalData const &caldata);

private:
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
