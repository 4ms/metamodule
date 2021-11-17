#include "audio.hh"
#include "arch.hh"
#include "audio_test_signals.hh"
#include "conf/hsem_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "patch_player.hh"
#include "util/countzip.hh"
#include "util/math_tables.hh"
#include "util/zip.hh"
// #include "fft.hh"
// #include "convolve.hh"

namespace MetaModule
{

using namespace mdrivlib;

constexpr bool DEBUG_PASSTHRU_AUDIO = false;
constexpr bool DEBUG_SINEOUT_AUDIO = false;
constexpr bool DEBUG_NE10_FFT = false;
// static FFTfx fftfx;
// static Convolver fftfx;

AudioStream::AudioStream(PatchPlayer &patchplayer,
						 CodecT &codec,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 ParamQueue &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 DoubleAuxStreamBlock &auxs)
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, audio_blocks{{.in_codec = audio_in_block.codec[0], .out_codec = audio_out_block.codec[0]},
				   {.in_codec = audio_in_block.codec[1], .out_codec = audio_out_block.codec[1]}}
	, auxsigs{auxs}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, player{patchplayer} {
	codec_.init();
	codec_.set_tx_buffers(audio_blocks[0].out_codec);
	codec_.set_rx_buffers(audio_blocks[0].in_codec);

	codec_.set_callbacks(
		[this]() {
		Debug::Pin0::high();
		HWSemaphore<ParamsBuf1Lock>::lock();
		HWSemaphore<ParamsBuf2Lock>::unlock();
		if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
			process(audio_blocks[0], param_blocks[0], auxsigs[0]);
		else
			process(audio_blocks[1], param_blocks[0], auxsigs[0]);
		Debug::Pin0::low();
		},
		[this]() {
		Debug::Pin0::high();
		HWSemaphore<ParamsBuf2Lock>::lock();
		HWSemaphore<ParamsBuf1Lock>::unlock();
		if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
			process(audio_blocks[1], param_blocks[1], auxsigs[1]);
		else
			process(audio_blocks[0], param_blocks[1], auxsigs[1]);
		Debug::Pin0::low();
	});

	load_measure.init();

	// if constexpr (DEBUG_NE10_FFT)
	// 	fftfx.init();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
	return scaled_out;
	// return compressor.compress(scaled_out);
}

// Todo: the scaling and offset shouold be part of the AuxStream, so we can support different types of DACs
uint32_t AudioStream::get_dac_output(int output_id) {
	auto raw_out = player.get_panel_output(output_id);
	raw_out *= -1.f;
	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
	scaled_out *= AuxStream::DACscaling;
	scaled_out += 0x00800000;
	return scaled_out;
}
// Todo: integrate params.buttons[]

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block, AuxStreamBlock &aux) {
	auto &in = audio_block.in_codec;
	auto &out = audio_block.out_codec;

	load_lpf += (load_measure.get_last_measurement_load_float() - load_lpf) * 0.005f;
	param_block.metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
	load_measure.start_measurement();

	cache.write_sync(param_block.params[0], param_block.metaparams);
	mdrivlib::SystemCache::clean_dcache_by_range(&cache, sizeof(ParamQueue));

	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		AudioTestSignal::passthrough(in, out, aux);
		return;
	} else if (DEBUG_SINEOUT_AUDIO) {
		AudioTestSignal::sines_out(in, out);
		return;
	}

	// Setting audio_is_muted to true notifies UI that it's safe to load a new patch
	// Todo: fade down before setting audio_is_muted to true
	mbox.audio_is_muted = mbox.loading_new_patch ? true : false;
	if (mbox.audio_is_muted) {
		// FixMe:
		// output_silence(out, aux);
		return;
	}

	// if (mbox.loading_new_patch) {
	//	Debug::Pin3::high();
	//	//This would be a fade down over 10 blocks:
	//	if (_mute_ctr)
	//		_mute_ctr--;
	//	else {
	//		output_silence(out, aux);
	//		Debug::Pin3::low();
	//		load_measure.end_measurement();
	//		mbox.audio_is_muted = true;
	//		return;
	//	}
	// } else {
	//	mbox.audio_is_muted = false;
	//	_mute_ctr = 10;
	// }

	for (auto [in_, out_, aux_, params_] : zip(in, out, aux, param_block.params)) {

		// Handle jacks being plugged/unplugged
		propagate_sense_pins(params_);

		// Pass audio inputs to modules
		for (auto [i, inchan] : countzip(in_.chan)) {
			auto pin_bit = jacksense_pin_order[i];
			// Todo: send 0 on the first time the jack is detected as unpatched (and then don't call set_panel_input
			// until patched)
			auto val = (params_.jack_senses & (1 << pin_bit)) ? AudioInFrame::scaleInput(inchan) : 0;
			player.set_panel_input(PanelDef::audioin_order[i], val);
		}

		// Pass CV values to modules
		for (auto [i, cv] : countzip(params_.cvjacks))
			player.set_panel_input(i + NumAudioInputs, cv);

		for (auto [i, gatein] : countzip(params_.gate_ins))
			player.set_panel_input(i + NumAudioInputs + NumCVInputs, gatein.is_high() ? 1.f : 0.f);

		// Pass Knob values to modules
		for (auto [i, knob] : countzip(params_.knobs))
			player.set_panel_param(i, knob);

		// Run each module
		player.update_patch();

		// Get outputs from modules
		for (auto [i, outchan] : countzip(out_.chan))
			outchan = get_audio_output(i);

		for (int i = 0; i < PanelDef::NumDACOut; i++)
			aux_.set_output(i, get_dac_output(i + PanelDef::NumAudioOut));

		for (auto [i, gate_out] : countzip(aux_.gate_out))
			gate_out = player.get_panel_output(i + PanelDef::NumAudioOut + PanelDef::NumDACOut) > 0.5f ? 1 : 0;
	}

	load_measure.end_measurement();
}

void AudioStream::start() {
	codec_.start();
}

void AudioStream::propagate_sense_pins(Params &params) {
	for (int i = 0; i < PanelDef::NumUserFacingInJacks; i++) {
		auto pin_bit = jacksense_pin_order[i];
		bool sense = params.jack_senses & (1 << pin_bit);
		player.set_input_jack_patched_status(i, sense);
	}

	// Note: p3 PCB has an error where out jack sense pins do not work
	if constexpr (PanelDef::PanelID != 0) {
		for (int i = 0; i < PanelDef::NumUserFacingOutJacks; i++) {
			auto pin_bit = jacksense_pin_order[i + PanelDef::NumUserFacingInJacks];
			bool sense = params.jack_senses & (1 << pin_bit);
			player.set_output_jack_patched_status(i, sense);
		}
	}
}

void AudioStream::output_silence(AudioOutBuffer &out, AuxStreamBlock &aux) {
	for (auto [out_, aux_] : zip(out, aux)) {
		for (auto &outchan : out_.chan)
			outchan = 0;
		for (auto &gate : aux_.gate_out)
			gate = 0;
	}
}

} // namespace MetaModule
