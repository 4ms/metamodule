#include "audio/audio.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "param_block.hh"
#include "params/sync_params.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/audio_settings.hh"
#include "util/countzip.hh"
#include "util/zip.hh"
#include <cstring>

namespace MetaModule
{

using namespace mdrivlib;

AudioStream::AudioStream(PatchPlayer &patchplayer,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 SyncParams &sync_p,
						 PatchPlayLoader &patchloader,
						 DoubleBufParamBlock &pblk,
						 PatchModQueue &)
	: sync_params{sync_p}
	, patch_loader{patchloader}
	, param_blocks{pblk}
	, audio_in_block{audio_in_block}
	, audio_out_block{audio_out_block}
	, player{patchplayer}
	, midi{patchplayer, sync_params}
	, codec_{Hardware::codec}
	, sample_rate_{AudioSettings::DefaultSampleRate}
	, block_size_{AudioSettings::DefaultBlockSize} {

	if (codec_.init() == CodecT::CODEC_NO_ERR)
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
		param_blocks[block].metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
		load_measure.start_measurement();

		HWSemaphore<block == 0 ? ParamsBuf1Lock : ParamsBuf2Lock>::lock();
		HWSemaphore<block == 0 ? ParamsBuf2Lock : ParamsBuf1Lock>::unlock();

		auto &params = cache_params(block);

		cur_block = block;
		process(audio_blocks[1 - block], params);

		return_cached_params(block);

		load_measure.end_measurement();

		sync_params.write_sync(param_state, param_blocks[block].metaparams);
		param_state.reset_change_flags();

		update_audio_settings();
	};

	codec_.set_callbacks([audio_callback]() { audio_callback.operator()<0>(); },
						 [audio_callback]() { audio_callback.operator()<1>(); });
	load_measure.init();

	for (auto &s : param_state.smoothed_ins)
		s.set_size(block_size_);
}

void AudioStream::start() {
	codec_.start();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	float output_volts = player.get_panel_output(output_id);
	return MathTools::signed_saturate(cal.out_cal[output_id].adjust(output_volts), 24);
}

void AudioStream::handle_patch_just_loaded() {
	midi.last_connected = false;
}

TriangleOscillator<48000> tri1{100};
TriangleOscillator<48000> tri2{1000};

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block) {
	player.sync();

	// Buttons
	for (auto [i, sync_button] : enumerate(param_state.buttons)) {
		auto src = (i < 16) ? param_block.metaparams.buttons0 :
				   (i < 32) ? param_block.metaparams.buttons1 :
							  param_block.metaparams.buttons2;
		bool button = (src >> i) & 1;

		sync_button.register_state(button);

		if (sync_button.just_went_low())
			player.set_panel_param(i + FirstButton, 0.f);

		else if (sync_button.just_went_high())
			player.set_panel_param(i + FirstButton, 1.f);
	}

	for (auto idx = 0u; auto const &in : audio_block.in_codec) {
		auto &out = audio_block.out_codec[idx];
		auto &params = param_block.params[idx];

		params.dac1 = tri1.process() >> 20;
		params.dac0 = tri2.process() >> 20;

		// Audio inputs
		for (auto [panel_jack_i, inchan] : zip(PanelDef::audioin_order, in.chan)) {

			float calibrated_input = cal.in_cal[panel_jack_i].adjust(AudioInFrame::sign_extend(inchan));

			player.set_panel_input(panel_jack_i, calibrated_input);

			// Send smoothed sigals to other core
			param_state.smoothed_ins[panel_jack_i].add_val(calibrated_input);
		}

		// Gate inputs
		for (auto [i, sync_gatein] : enumerate(param_state.gate_ins)) {
			bool gate = (params.gate_ins >> i) & 1;

			sync_gatein.register_state(gate);

			if (sync_gatein.just_went_low())
				player.set_panel_input(i + FirstGateInput, 0.f);
			else if (sync_gatein.just_went_high())
				player.set_panel_input(i + FirstGateInput, 8.f);
		}

		// Pass Knob values to modules
		for (auto [i, knob_val, knob_state] : countzip(params.knobs, param_state.knobs)) {
			if (knob_state.store_changed(knob_val))
				player.set_panel_param(i, knob_val);
		}

		// USB MIDI
		MidiMessage msg = params.usb_raw_midi;
		midi.process(param_block.metaparams.usb_midi_connected, &msg);
		param_blocks[cur_block].params[idx].usb_raw_midi = msg;

		// TODO UART MIDI

		// Run each module
		player.update_patch();

		// Get outputs from modules
		for (auto [i, outchan] : countzip(out.chan))
			outchan = get_audio_output(i);

		idx++;
	}
}

void AudioStream::set_calibration(CalData const &caldata) {
	cal = caldata;
}

uint32_t AudioStream::get_audio_errors() {
	return codec_.get_sai_errors();
}

// It's measurably faster to copy params into cacheable ram
ParamBlock &AudioStream::cache_params(unsigned block) {
	local_params.metaparams.usb_midi_connected = param_blocks[block].metaparams.usb_midi_connected;
	for (auto i = 0u; i < block_size_; i++)
		local_params.params[i] = param_blocks[block].params[i]; // 45us/49us alt

	return local_params;
}

void AudioStream::return_cached_params(unsigned block) {
	for (auto i = 0u; i < block_size_; i++) {
		param_blocks[block].params[i].dac0 = local_params.params[i].dac0;
		param_blocks[block].params[i].dac1 = local_params.params[i].dac1;
	}
}

void AudioStream::set_block_spans() {
	audio_blocks[0].in_codec = {audio_in_block.codec[0].data(), block_size_};
	audio_blocks[1].in_codec = {std::next(audio_in_block.codec[0].begin(), block_size_), block_size_};

	audio_blocks[0].out_codec = {audio_out_block.codec[0].data(), block_size_};
	audio_blocks[1].out_codec = {std::next(audio_out_block.codec[0].begin(), block_size_), block_size_};
}

void AudioStream::update_audio_settings() {
	auto [sample_rate, block_size, max_retries] = patch_loader.get_audio_settings();

	if (sample_rate != sample_rate_ || block_size != block_size_) {

		auto ok = (codec_.change_samplerate_blocksize(sample_rate, block_size) == CodecBase::CODEC_NO_ERR);
		if (ok) {
			codec_.start();

			if (sample_rate_ != sample_rate) {
				sample_rate_ = sample_rate;
				player.set_samplerate(sample_rate);
				param_blocks[0].metaparams.sample_rate = sample_rate;
				param_blocks[1].metaparams.sample_rate = sample_rate;
			}

			if (block_size_ != block_size) {
				block_size_ = block_size;

				set_block_spans();

				for (auto &s : param_state.smoothed_ins)
					s.set_size(block_size_);
			}
		} else {
			pr_err("FAIL TO CHANGE SR/BS: %d/%d\n", sample_rate_, block_size_);
			codec_.start();
		}
	}
}

void AudioStream::handle_overruns() {
}

} // namespace MetaModule
