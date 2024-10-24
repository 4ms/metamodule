#pragma once
#include "calibrate/calibration_data.hh"
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
#include "util/filter.hh"
#include "util/math.hh"
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
				PatchModQueue &patch_mod_queue);

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
	PatchModQueue &patch_mod_queue;
	AudioInBlock &audio_in_block;
	AudioOutBlock &audio_out_block;

	CodecT &codec_;
	CodecT &codec_ext_;
	uint32_t sample_rate_;
	uint32_t block_size_;

	CalData cal;
	CalData cal_stash;
	CalData ext_cal{};
	CalData ext_cal_stash{};

	EdgeStateDetector plug_detects[PanelDef::NumJacks];

	PatchPlayer &player;
	mdrivlib::CycleCounter load_measure;
	float load_lpf = 0.f;
	float output_fade_amt = -1.f;
	float output_fade_delta = 0.f;
	uint32_t halves_muted = 0;
	bool ext_audio_connected = false;

	ParamBlock local_params;

	bool midi_last_connected = false;

	AudioConf::SampleT get_audio_output(int output_id);
	AudioConf::SampleT get_ext_audio_output(int output_id);
	void set_input(int input_id, AudioConf::SampleT in);
	bool check_patch_change(int motion);
	void send_zeros_to_patch();
	void propagate_sense_pins(uint32_t jack_senses);
	void handle_midi(bool is_connected, Midi::Event const &event, unsigned poly_num);
	void process_nopatch(CombinedAudioBlock &audio_block, ParamBlock &param_block);
	bool is_playing_patch();
	void handle_patch_just_loaded();
	void disable_calibration();
	void re_enable_calibration();
	void handle_patch_mod_queue();
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
