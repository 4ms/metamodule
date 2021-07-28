#include "audio.hh"
#include "arch.hh"
#include "auxsignal.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
// #include "fft.hh"
// #include "convolve.hh"
#include "panel.hh"
#include "patch_player.hh"
#include "util/math_tables.hh"
#include "util/zip.hh"

namespace MetaModule
{
constexpr bool DEBUG_PASSTHRU_AUDIO = false;
constexpr bool DEBUG_SINEOUT_AUDIO = true;
// constexpr bool DEBUG_NE10_FFT = true;
// static FFTfx fftfx;
// static Convolver fftfx;

AudioStream::AudioStream(PatchList &patches,
						 PatchPlayer &patchplayer,
						 CodecT &codecA,
						 CodecT &codecB,
						 ParamCache &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 AudioInStreamBlock (&in_buffers)[4],
						 AudioOutStreamBlock (&out_buffers)[4],
						 AuxSignalStreamBlock (&auxsig)[2])
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, tx_buf_codecA_1{out_buffers[0]}
	, tx_buf_codecA_2{out_buffers[1]}
	, tx_buf_codecB_1{out_buffers[2]}
	, tx_buf_codecB_2{out_buffers[3]}
	, rx_buf_codecA_1{in_buffers[0]}
	, rx_buf_codecA_2{in_buffers[1]}
	, rx_buf_codecB_1{in_buffers[2]}
	, rx_buf_codecB_2{in_buffers[3]}
	, auxsig_1{auxsig[0]}
	, auxsig_2{auxsig[1]}
	, codecA_{codecA}
	, codecB_{codecB}
	, sample_rate_{codecA.get_samplerate()}
	, patch_list{patches}
	, player{patchplayer}
{
	codecA_.init();
	codecA_.set_tx_buffers(tx_buf_codecA_1);
	codecA_.set_rx_buffers(rx_buf_codecA_1);

	// codecB_.init();
	// codecB_.set_tx_buffers(tx_buf_codecB_1);
	// codecB_.set_rx_buffers(rx_buf_codecB_1);

	codecA_.set_callbacks(
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf1Lock>::lock();
			HWSemaphore<ParamsBuf2Lock>::unlock();

			if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
				process(rx_buf_codecA_1, tx_buf_codecA_1, param_blocks[0], auxsig_1);
			else {
				process(rx_buf_codecA_2, tx_buf_codecA_2, param_blocks[0], auxsig_1);
			}
			Debug::Pin0::low();
		},
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf2Lock>::lock();
			HWSemaphore<ParamsBuf1Lock>::unlock();
			if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32h7x5)
				process(rx_buf_codecA_2, tx_buf_codecA_2, param_blocks[1], auxsig_2);
			else {
				process(rx_buf_codecA_1, tx_buf_codecA_1, param_blocks[1], auxsig_2);
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

// Todo: integrate params.buttons[]

void AudioStream::process(AudioInStreamBlock &in,
						  AudioOutStreamBlock &out,
						  ParamBlock &param_block,
						  AuxSignalStreamBlock &aux)
{
	// param_block.metaparams.audio_load = load_measure.get_last_measurement_load_percent();
	// load_measure.start_measurement();

	// cache.write_sync(param_block.params[0], param_block.metaparams);
	// mdrivlib::SystemCache::clean_dcache_by_range(&cache, sizeof(ParamCache));

	//Debug: passthrough audio and exit
	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		passthrough_audio(in, out, aux);
		return;
	} else if (DEBUG_SINEOUT_AUDIO) {
		sines_out(in, out);
		return;
	}

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

	for (auto [in_, out_, aux_, params_] : zip(in, out, aux, param_block.params)) {

		//Handle jacks being plugged/unplugged
		propagate_sense_pins(params_);

		//Pass audio/CV inputs to modules
		for (int i = 0; i < AudioConf::NumInChans; i++)
			player.set_panel_input(i, AudioInFrame::scaleInput(in_.chan[i]));
		// for (auto [i, inchan] : countzip(in_.chan))
		// 	player.set_panel_input(i, AudioInFrame::scaleInput(inchan));

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
		for (int i = 0; i < AudioConf::NumOutChans; i++)
			out_.chan[i] = get_audio_output(i);
		// for (auto [i, outchan] : countzip(out_.chan))
		// 	outchan = get_audio_output(i);

		aux_.clock_out = player.get_panel_output(AudioConf::NumOutChans) > 0.5f ? 1 : 0;
	}

	load_measure.end_measurement();
}

void AudioStream::start()
{
	codecA_.start();
	codecB_.start();
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

	for (auto [i, o, a] : zip(in, out, aux)) {
		o.chan[0] = i.chan[0];
		o.chan[1] = i.chan[1];
		o.chan[2] = i.chan[2];
		o.chan[3] = i.chan[3];
		o.chan[4] = i.chan[4];
		o.chan[5] = i.chan[5];
		o.chan[6] = 0x00100000; //AudioOutFrame::scaleOutput(AudioInFrame::scaleInput(i.chan[5]));
		o.chan[7] = 0x00400000; //AudioOutFrame::scaleOutput(AudioInFrame::scaleInput(i.chan[5]));
		a.clock_out = 0;
	}
}

void AudioStream::sines_out(AudioInStreamBlock &in, AudioOutStreamBlock &out)
{
	static PhaseAccum<48000> phase0{80};
	static PhaseAccum<48000> phase1{200};
	static PhaseAccum<48000> phase2{250};
	static PhaseAccum<48000> phase3{700};
	static PhaseAccum<48000> phase4{900};
	static PhaseAccum<48000> phase5{2200};
	static PhaseAccum<48000> phase6{1000};
	static PhaseAccum<48000> phase7{1000};

	//This assumes values are right aligned (max 0x00FFFFFF)
	//and that unused bits in a sample <= log2(block size)
	int32_t refsum = 0;
	for (auto inframe : in)
		refsum += inframe.chan[0];
	float refavg = AudioInFrame::scaleInput(refsum >> MathTools::Log2<AudioConf::BlockSize>::val);

	constexpr float refref = 0x004A3000UL / AudioInFrame::kOutScaling;
	float temp_adj = refref / refavg;

	int32_t pitchsum = 0;
	for (auto inframe : in)
		pitchsum += inframe.chan[5];
	float pitchavg = AudioInFrame::scaleInput(pitchsum >> MathTools::Log2<AudioConf::BlockSize>::val);
	float adjpitch = pitchavg * temp_adj;

	//Adjusted
	float freq_mult6 = exp5Table.interp(MathTools::constrain(adjpitch / 2.f + 0.5f, 0.f, 1.0f)); //1..1024
	phase6.set_frequency(20 * freq_mult6);

	//Unadjusted
	float freq_mult7 = exp5Table.interp(MathTools::constrain(pitchavg / 2.f + 0.5f, 0.f, 1.0f)); //1..1024
	phase7.set_frequency(20 * freq_mult7);

	for (auto &o : out) {
		o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
		o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));
		o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
		o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
		o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase4.process_float()));
		o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase5.process_float()));
		o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase6.process_float()));
		o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase7.process_float()));
	}

	// Temp stability:
	// ~1V/oct
	// using exp10 table
	//
	// using adjpitch = pitchavg * (refref/refavg);
	// Blowing on PCM chip --> 8.1kHz output deviates +70 and -70Hz.
	// 1 semitone = 481Hz, so +/-70Hz = span 140Hz = +/-15cents = span 30cents
	//
	// using pitchavg: +65/-20Hz = span 85Hz = span 17cents
	//
	// using refavg/refref (inverted): deviates 260Hz (obviously, math is bad)
}

} // namespace MetaModule
