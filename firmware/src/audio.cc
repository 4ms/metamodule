#include "audio.hh"
#include "arch.hh"
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

constexpr bool DEBUG_PASSTHRU_AUDIO = false;
constexpr bool DEBUG_SINEOUT_AUDIO = false;
constexpr bool DEBUG_NE10_FFT = false;
// static FFTfx fftfx;
// static Convolver fftfx;

AudioStream::AudioStream(PatchList &patches,
						 PatchPlayer &patchplayer,
						 CodecT &codec,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 ParamCache &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 DoubleAuxSignalStreamBlock &auxs)
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, audio_blocks{{.in_codec = audio_in_block.codec[0], .out_codec = audio_out_block.codec[0]},
				   {.in_codec = audio_in_block.codec[1], .out_codec = audio_out_block.codec[1]}}
	, auxsigs{auxs}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, patch_list{patches}
	, player{patchplayer}
{
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
	auto &in = audio_block.in_codec;
	auto &out = audio_block.out_codec;

#if !defined(DUAL_PCM3168_DEV)
	param_block.metaparams.audio_load = load_measure.get_last_measurement_load_percent();
	load_measure.start_measurement();

	cache.write_sync(param_block.params[0], param_block.metaparams);
	mdrivlib::SystemCache::clean_dcache_by_range(&cache, sizeof(ParamCache));
#endif

	//Debug: passthrough audio and exit
	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		passthrough(in, out, aux);
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

		//Pass audio inputs to modules
		for (auto [i, inchan] : countzip(in_.chan))
			player.set_panel_input(i, AudioInFrame::scaleInput(inchan));

		//Pass CV values to modules
		for (auto [i, cv] : countzip(params_.cvjacks))
			player.set_panel_input(i + NumAudioInputs, cv);

		for (auto [i, gatein] : countzip(params_.gate_ins))
			player.set_panel_input(i + NumAudioInputs + NumCVInputs, gatein.is_high() ? 1.f : 0.f);

		//Pass Knob values to modules
		for (auto [i, knob] : countzip(params_.knobs))
			player.set_panel_param(i, knob);

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

void AudioStream::passthrough(AudioInBuffer &in, AudioOutBuffer &out, AuxSignalStreamBlock &aux)
{

	for (auto [i, o, a] : zip(in, out, aux)) {
		o.chan[0] = i.chan[0];
		o.chan[1] = i.chan[1];
		o.chan[2] = i.chan[2];
		o.chan[3] = i.chan[3];
		o.chan[4] = i.chan[4];
		o.chan[5] = i.chan[5];
		o.chan[6] = 0x00100000;
		o.chan[7] = 0x00400000;
		a.clock_out = 0;
	}
}

void AudioStream::sines_out(AudioInBuffer &in, AudioOutBuffer &out)
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

void AudioStream::dual_passthrough(
	AudioInBuffer &inA, AudioOutBuffer &outA, AudioInBuffer &inB, AudioOutBuffer &outB, AuxSignalStreamBlock &aux)
{

	static PhaseAccum<48000> phase0{80};
	static PhaseAccum<48000> phase1{200};
	static PhaseAccum<48000> phase2{250};
	static PhaseAccum<48000> phase3{700};
	for (auto [ina, inb, outa, outb, a] : zip(inA, inB, outA, outB, aux)) {
		outa.chan[0] = ina.chan[0];
		outa.chan[1] = ina.chan[1];
		outa.chan[2] = ina.chan[2];
		outa.chan[3] = ina.chan[3];
		outa.chan[4] = ina.chan[4];
		outa.chan[5] = ina.chan[5];
		outa.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
		outa.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));

		outb.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
		outb.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
		outb.chan[2] = inb.chan[0];
		outb.chan[3] = inb.chan[1];
		outb.chan[4] = inb.chan[2];
		outb.chan[5] = inb.chan[3];
		outb.chan[6] = inb.chan[4];
		outb.chan[7] = inb.chan[5];
		a.clock_out = 0;
	}
}

void AudioStream::dual_sines_out(AudioOutBuffer &outA, AudioOutBuffer &outB)
{
	static PhaseAccum<48000> phase0{80};
	static PhaseAccum<48000> phase1{200};
	static PhaseAccum<48000> phase2{250};
	static PhaseAccum<48000> phase3{700};
	static PhaseAccum<48000> phase4{900};
	static PhaseAccum<48000> phase5{2200};
	static PhaseAccum<48000> phase6{6000};
	static PhaseAccum<48000> phase7{12000};

	static PhaseAccum<48000> phase8{60};
	static PhaseAccum<48000> phase9{100};
	static PhaseAccum<48000> phase10{175};
	static PhaseAccum<48000> phase11{300};
	static PhaseAccum<48000> phase12{375};
	static PhaseAccum<48000> phase13{800};
	static PhaseAccum<48000> phase14{4000};
	static PhaseAccum<48000> phase15{8000};

	for (auto &o : outA) {
		o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
		o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));
		o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
		o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
		o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase4.process_float()));
		o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase5.process_float()));
		o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase6.process_float()));
		o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase7.process_float()));
	}
	for (auto &o : outB) {
		o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase8.process_float()));
		o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase9.process_float()));
		o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase10.process_float()));
		o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase11.process_float()));
		o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase12.process_float()));
		o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase13.process_float()));
		o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase14.process_float()));
		o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase15.process_float()));
	}
}
} // namespace MetaModule
