#include "audio.hh"
#include "arch.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
// #include "fft.hh"
// #include "convolve.hh"
#include "panel.hh"
#include "patch_player.hh"
#include "util/zip.hh"

namespace MetaModule
{
constexpr bool DEBUG_PASSTHRU_AUDIO = false;
// constexpr bool DEBUG_NE10_FFT = true;
// static FFTfx fftfx;
// static Convolver fftfx;

// Clock in -> clock out latency: 1.33ms (one audio DMA half-transfer)
// Gate In -> audio OUt latency: 1.90ms
AudioStream::AudioStream(PatchList &patches,
						 PatchPlayer &patchplayer,
						 ICodec &codec,
						 AnalogOutT &dac,
						 ParamCache &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 AudioInStreamBlock (&in_buffers)[2],
						 AudioOutStreamBlock (&out_buffers)[2],
						 AuxSignalStreamBlock (&auxsig)[2])
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, tx_buf_1{out_buffers[0]}
	, tx_buf_2{out_buffers[1]}
	, rx_buf_1{in_buffers[0]}
	, rx_buf_2{in_buffers[1]}
	, auxsig_1{auxsig[0]}
	, auxsig_2{auxsig[1]}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, patch_list{patches}
	, player{patchplayer}
{

	codec_.init();
	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							AudioConf::DMABlockSize * 2);
	codec_.set_callbacks(
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf1Lock>::lock();
			HWSemaphore<ParamsBuf2Lock>::unlock();

			if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
				process(rx_buf_1, tx_buf_1, param_blocks[0], auxsig_1);
			else {
				process(rx_buf_2, tx_buf_2, param_blocks[0], auxsig_1);
			}
			Debug::Pin0::low();
		},
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf2Lock>::lock();
			HWSemaphore<ParamsBuf1Lock>::unlock();
			if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
				process(rx_buf_2, tx_buf_2, param_blocks[1], auxsig_2);
			else {
				process(rx_buf_1, tx_buf_1, param_blocks[1], auxsig_2);
			}
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

// uint32_t AudioStream::get_dac_output(int output_id)
// {
// 	auto raw_out = player.get_panel_output(output_id);
// 	raw_out *= -1.f;
// 	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
// 	scaled_out *= MM_DACConf::scaling;
// 	scaled_out += 0x00800000;
// 	return scaled_out;
// }

// Todo: integrate params.buttons[]

void AudioStream::process(AudioInStreamBlock &in,
						  AudioOutStreamBlock &out,
						  ParamBlock &param_block,
						  AuxSignalStreamBlock &aux)
{
	param_block.metaparams.audio_load = load_measure.get_last_measurement_load_percent();
	load_measure.start_measurement();

	cache.write_sync(param_block.params[0], param_block.metaparams);
	mdrivlib::SystemCache::clean_dcache_by_range(&cache, sizeof(ParamCache));

	// Setting audio_is_muted to true notifies UI that it's safe to load a new patch
	// Todo: fade down before setting audio_is_muted to true
	mbox.audio_is_muted = mbox.loading_new_patch ? true : false;
	if (mbox.audio_is_muted) {
		output_silence(out, aux);
		return;
	}

	// if constexpr (DEBUG_NE10_FFT) {
	// 	fftfx.process(in, out);
	// 	return;
	// }

	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		passthrough_audio(in, out, aux);
		return;
	}

	for (auto [in_, out_, aux_, params_] : zip(in, out, aux, param_block.params)) {

		int i;

		propagate_sense_pins(params_);

		//Pass audio/CV inputs to modules
		for (int i = 0; i < AudioConf::NumInChans; i++)
			player.set_panel_input(i, AudioInFrame::scaleInput(in_.chan[i]));

		//Pass Knob values to modules
		int i = 0;
		for (const auto knob : params_.knobs) {
			player.set_panel_param(i, knob);
			i++;
		}

		//Run each module
		player.update_patch();

		//Get outputs from modules
		for (int i = 0; i < AudioConf::NumOutChans; i++)
			out_.chan[i] = get_audio_output(i);

		aux_.clock_out = player.get_panel_output(AudioConf::NumOutChans) > 0.5f ? 1 : 0;
	}

	load_measure.end_measurement();
}

void AudioStream::start()
{
	codec_.start();
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

void AudioStream::output_silence(AudioOutStreamBlock &out, AuxSignalStreamBlock &aux)
{
	auto aux_ = aux.begin();
	for (auto &out_ : out) {
		for (int i = 0; i < AudioConf::NumOutChans; i++)
			out_.chan[i] = get_audio_output(i);
		aux_->clock_out = 0;
		aux_++;
	}
}

void AudioStream::passthrough_audio(AudioInStreamBlock &in, AudioOutStreamBlock &out, AuxSignalStreamBlock &aux)
{
	auto in_ = in.begin();
	auto aux_ = aux.begin();
	for (auto &out_ : out) {
		out_.chan[0] = in_->chan[0];
		out_.chan[1] = in_->chan[1];
		out_.chan[2] = in_->chan[2];
		out_.chan[3] = in_->chan[3];
		out_.chan[4] = in_->chan[4];
		out_.chan[5] = in_->chan[5];
		out_.chan[6] = 0;
		out_.chan[7] = 0;
		aux_->clock_out = 0;
		aux_++;
		in_++;
	}
}

} // namespace MetaModule
