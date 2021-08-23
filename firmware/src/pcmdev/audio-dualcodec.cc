#include "audio-dualcodec.hh"
#include "arch.hh"
#include "audio_test_signals.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "panel.hh"
#include "patch_player.hh"
#include "util/countzip.hh"
#include "util/math_tables.hh"
#include "util/zip.hh"
// #include "fft.hh"
// #include "convolve.hh"

namespace MetaModule
{

using namespace mdrivlib;

constexpr bool DEBUG_PASSTHRU_AUDIO = true;
constexpr bool DEBUG_SINEOUT_AUDIO = false;
constexpr bool DEBUG_NE10_FFT = false;
// static FFTfx fftfx;
// static Convolver fftfx;

//Todo: generalize this using template parameter:
//AudioStream<1> has 1 codec
//can't pass an array of references to the ctor, so.. pass array of pointers? Or use variadic? Or two constructors?
//CodecT codecs[NumCodecs];
AudioStream::AudioStream(PatchList &patches,
						 PatchPlayer &patchplayer,
						 CodecT &codecA,
						 CodecT &codecB,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 ParamCache &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 DoubleAuxStreamBlock &auxs)
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, audio_blocks{{.in_codecA = audio_in_block.codecA[0],
					.in_codecB = audio_in_block.codecB[0],
					.out_codecA = audio_out_block.codecA[0],
					.out_codecB = audio_out_block.codecB[0]},
				   {.in_codecA = audio_in_block.codecA[1],
					.in_codecB = audio_in_block.codecB[1],
					.out_codecA = audio_out_block.codecA[1],
					.out_codecB = audio_out_block.codecB[1]}}
	, auxsigs{auxs}
	, codecA_{codecA}
	, codecB_{codecB}
	, sample_rate_{codecA.get_samplerate()}
	, patch_list{patches}
	, player{patchplayer}
{
	codecA_.init();
	codecA_.set_tx_buffers(audio_blocks[0].out_codecA);
	codecA_.set_rx_buffers(audio_blocks[0].in_codecA);

	codecB_.init();
	codecB_.set_tx_buffers(audio_blocks[0].out_codecB);
	codecB_.set_rx_buffers(audio_blocks[0].in_codecB);

	codecA_.set_callbacks(
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

AudioConf::SampleT AudioStream::get_audio_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
	return scaled_out;
	// return compressor.compress(scaled_out);
}

// Todo: integrate params.buttons[]

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block, AuxSignalStreamBlock &aux)
{
	auto &inA = audio_block.in_codecA;
	auto &inB = audio_block.in_codecB;
	auto &outA = audio_block.out_codecA;
	auto &outB = audio_block.out_codecB;

	// Commented out for PCM3168 dev board:
	// param_block.metaparams.audio_load = load_measure.get_last_measurement_load_percent();
	// load_measure.start_measurement();

	// Commented out for PCM3168 dev board:
	// cache.write_sync(param_block.params[0], param_block.metaparams);
	// mdrivlib::SystemCache::clean_dcache_by_range(&cache, sizeof(ParamCache));

	//Debug: passthrough audio and exit
	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		AudioTestSignal::dual_passthrough(inA, outA, inB, outB, aux);
		return;
	} else if (DEBUG_SINEOUT_AUDIO) {
		AudioTestSignal::dual_sines_out(outA, outB);
		return;
	}

	// Setting audio_is_muted to true notifies UI that it's safe to load a new patch
	// Todo: fade down before setting audio_is_muted to true
	mbox.audio_is_muted = mbox.loading_new_patch ? true : false;
	if (mbox.audio_is_muted) {
		output_silence(outA, aux);
		output_silence(outB, aux);
		return;
	}

	// if constexpr (DEBUG_NE10_FFT) {
	// 	fftfx.process(in, out);
	// 	return;
	// }

	for (auto [in_, out_, aux_, params_] : zip(inA, outA, aux, param_block.params)) {

		//Handle jacks being plugged/unplugged
		propagate_sense_pins(params_);

		//Pass audio/CV inputs to modules
		for (auto [i, inchan] : countzip(in_.chan))
			player.set_panel_input(i, AudioInFrame::scaleInput(inchan));

		//Pass Knob values to modules
		int i = 0;
		for (const auto knob : params_.knobs) {
			player.set_panel_param(i, knob);
			i++;
		}
		// for (auto [i, knob] : countzip(params_.knobs)
		// 	player.set_panel_param(i, knob);

		//Run each module
		player.update_patch();

		//Get outputs from modules
		for (auto [i, outchan] : countzip(out_.chan))
			outchan = get_audio_output(i);

		aux_.clock_out = player.get_panel_output(AudioConf::NumOutChans) > 0.5f ? 1 : 0;
	}

	load_measure.end_measurement();
}

void AudioStream::start()
{
	codecB_.start();
	codecA_.start();
}

void AudioStream::propagate_sense_pins(Params &params)
{
	for (int i = 0; i < Panel::NumUserFacingInJacks; i++) {
		auto pin_bit = Panel::jacksense_pin_order[i];
		bool sense = params.jack_senses & (1 << pin_bit);
		player.set_input_jack_patched_status(i, sense);
	}
	// Note: PCB has an error where out jack sense pins do not work, so we don't check them yet
}

void AudioStream::output_silence(AudioOutBuffer &out, AuxSignalStreamBlock &aux)
{
	auto aux_ = aux.begin();
	for (auto &out_ : out) {
		for (auto &outchan : out_.chan)
			outchan = 0;
		aux_->clock_out = 0;
		aux_++;
	}
}

} // namespace MetaModule
