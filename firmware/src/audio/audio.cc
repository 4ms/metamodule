#include "audio/audio.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "param_block.hh"
#include "util/countzip.hh"
#include <cstring>

namespace MetaModule
{

using namespace mdrivlib;

AudioStream::AudioStream(PatchPlayer &player,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 DoubleBufParamBlock &pblk)
	: player{player}
	, param_blocks{pblk}
	, audio_in_block{audio_in_block}
	, audio_out_block{audio_out_block}
	, codec_{ListenClosely::Hardware::codec}
	, sample_rate_{StreamConf::Audio::SampleRate}
	, block_size_{StreamConf::Audio::MaxBlockSize} {

	if (codec_.init() == ListenClosely::CodecT::CODEC_NO_ERR)
		pr_info("Codec initialized\n");
	else
		pr_info("ERROR: No codec detected\n");

	set_block_spans();

	codec_.set_tx_buffer(audio_blocks[0].out_codec, block_size_);
	codec_.set_rx_buffer(audio_blocks[0].in_codec, block_size_);

	cal.reset_to_default();

	auto audio_callback = [this]<unsigned block>() {
		// Debug::Pin0::high();

		load_lpf += (load_measure.get_last_measurement_load_float() - load_lpf) * 0.05f;
		// param_blocks[block].metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
		load_measure.start_measurement();

		HWSemaphore<block == 0 ? ParamsBuf1Lock : ParamsBuf2Lock>::lock();
		HWSemaphore<block == 0 ? ParamsBuf2Lock : ParamsBuf1Lock>::unlock();

		auto &params = cache_params(block);

		cur_block = block;
		if (is_playing_patch())
			process(audio_blocks[1 - block], params);

		return_cached_params(block);

		load_measure.end_measurement();

		// Debug::Pin0::low();
	};

	player.set_samplerate(sample_rate_);

	codec_.set_callbacks([audio_callback]() { audio_callback.operator()<0>(); },
						 [audio_callback]() { audio_callback.operator()<1>(); });
	load_measure.init();
}

bool AudioStream::is_playing_patch() {
	return true;
}

void AudioStream::start() {
	codec_.start();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	float output_volts = player.get_panel_output(output_id) * 0.5f; //16Vpp clips little, so make 20Vpp => 16Vpp
	return MathTools::signed_saturate(cal.out_cal[output_id].adjust(output_volts), 24);
}

void AudioStream::handle_patch_just_loaded() {
}

// From ListenClosely.cpp:
enum LightId {
	GRAPH1_LIGHT,
	GRAPH2_LIGHT,
	GRAPH3_LIGHT,
	GRAPH4_LIGHT,
	GRAPH5_LIGHT,
	GRAPH6_LIGHT,
	GRAPH7_LIGHT,
	GRAPH8_LIGHT,
	GRAPH9_LIGHT,
	CLIPLED_LIGHT,
	_110LED_LIGHT,
	_80LED_LIGHT,
	_160LED_LIGHT,
	_220LED_LIGHT,
	_50LED_LIGHT,
	_300LED_LIGHT,
	_60LED_LIGHT,
	OFFLED_LIGHT,
	_35LED_LIGHT,
	_32KLED_LIGHT,
	_16KLED_LIGHT,
	_700LED_LIGHT,
	_48KLED_LIGHT,
	_360LED_LIGHT,
	_72KLED_LIGHT,
	EQCLIPLED_LIGHT,
	LIGHTS_LEN
};

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block) {
	player.set_input_jack_patched_status(0, true);
	player.set_input_jack_patched_status(1, true);
	player.set_input_jack_patched_status(2, true);
	player.set_output_jack_patched_status(0, true);
	player.set_output_jack_patched_status(1, true);

	// Buttons. Values are the panel_knob_id in the patch yaml
	player.set_panel_param(9, param_block.metaparams.comp_switch);
	player.set_panel_param(4, param_block.metaparams.eq_switch);
	player.set_panel_param(44, param_block.metaparams.low_sel);
	player.set_panel_param(45, param_block.metaparams.mid_sel);
	player.set_panel_param(46, param_block.metaparams.high_sel);

	for (auto idx = 0u; auto const &in : audio_block.in_codec) {
		auto &out = audio_block.out_codec[idx];
		auto &params = param_block.params[idx];

		// Audio inputs
		player.set_panel_input(0, cal.in_cal[0].adjust(in.sign_extend_chan(1)));
		player.set_panel_input(1, cal.in_cal[1].adjust(in.sign_extend_chan(0)));

		// CV Input
		player.set_panel_input(2, params.width_cv * 2.f);

		// Knobs. Values are the panel_knob_id in the patch yaml
		player.set_panel_param(6, params.knobs[0]);
		player.set_panel_param(7, params.knobs[1]);
		player.set_panel_param(8, params.knobs[2]);
		player.set_panel_param(1, params.knobs[3]);
		player.set_panel_param(2, params.knobs[4]);
		player.set_panel_param(3, params.knobs[5]);
		player.set_panel_param(0, params.knobs[6]);
		player.set_panel_param(5, params.knobs[7]);

		// Run each module
		player.update_patch_singlecore();

		// Get outputs from modules
		for (auto [i, outchan] : countzip(out.chan))
			outchan = get_audio_output(i);

		idx++;
	}

	// LEDS
	constexpr int ModuleID = 1;
	param_block.leds.low[0] = player.get_module_light(ModuleID, _35LED_LIGHT);
	param_block.leds.low[1] = player.get_module_light(ModuleID, _60LED_LIGHT);
	param_block.leds.low[2] = player.get_module_light(ModuleID, _110LED_LIGHT);
	param_block.leds.low[3] = player.get_module_light(ModuleID, _220LED_LIGHT);

	param_block.leds.mid[0] = player.get_module_light(ModuleID, _360LED_LIGHT);
	param_block.leds.mid[1] = player.get_module_light(ModuleID, _700LED_LIGHT);
	param_block.leds.mid[2] = player.get_module_light(ModuleID, _16KLED_LIGHT);
	param_block.leds.mid[3] = player.get_module_light(ModuleID, _32KLED_LIGHT);
	param_block.leds.mid[4] = player.get_module_light(ModuleID, _48KLED_LIGHT);
	param_block.leds.mid[5] = player.get_module_light(ModuleID, _72KLED_LIGHT);

	param_block.leds.high[0] = player.get_module_light(ModuleID, OFFLED_LIGHT);
	param_block.leds.high[1] = player.get_module_light(ModuleID, _50LED_LIGHT);
	param_block.leds.high[2] = player.get_module_light(ModuleID, _80LED_LIGHT);
	param_block.leds.high[3] = player.get_module_light(ModuleID, _160LED_LIGHT);
	param_block.leds.high[4] = player.get_module_light(ModuleID, _300LED_LIGHT);

	param_block.leds.eq_clip = player.get_module_light(ModuleID, EQCLIPLED_LIGHT) > 0.5f;
	param_block.leds.comp_clip = player.get_module_light(ModuleID, CLIPLED_LIGHT) > 0.5f;

	for (auto i = 0; i < 9; i++)
		param_block.leds.graph[i] = player.get_module_light(1, i);
}

void AudioStream::set_calibration(CalData const &caldata) {
	cal = caldata;
}

uint32_t AudioStream::get_audio_errors() {
	return codec_.get_sai_errors();
}

// It's measurably faster to copy params into cacheable ram
ParamBlock &AudioStream::cache_params(unsigned block) {
	local_params.metaparams = param_blocks[block].metaparams;

	for (auto i = 0u; i < block_size_; i++)
		local_params.params[i] = param_blocks[block].params[i]; // 45us/49us alt

	return local_params;
}

void AudioStream::return_cached_params(unsigned block) {
	param_blocks[block].leds = local_params.leds;
}

void AudioStream::set_block_spans() {
	audio_blocks[0].in_codec = {audio_in_block.codec[0].data(), block_size_};
	audio_blocks[1].in_codec = {std::next(audio_in_block.codec[0].begin(), block_size_), block_size_};

	audio_blocks[0].out_codec = {audio_out_block.codec[0].data(), block_size_};
	audio_blocks[1].out_codec = {std::next(audio_out_block.codec[0].begin(), block_size_), block_size_};
}

void AudioStream::update_audio_settings() {
}

void AudioStream::handle_overruns() {
}

} // namespace MetaModule
