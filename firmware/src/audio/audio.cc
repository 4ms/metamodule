#include "audio/audio.hh"
#include "audio/audio_test_signals.hh"
#include "conf/hsem_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "param_block.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "sync_params.hh"
#include "uart_log.hh"
#include "util/calibrator.hh"
#include "util/countzip.hh"
#include "util/math_tables.hh"
#include "util/zip.hh"
// #include "fft.hh"
// #include "convolve.hh"

namespace MetaModule
{

//FIXME: Setting an opt level other than O0 here causes a DMA Fifo Error for DMA1Stream3 (SPI4 TX)
//Sometimes/often while executing output_silence and it's compiled to use vstr d16/d17
//But also sometimes when the DMA1Stream3 IRQ interrupts DMA2Stream? IRQ for the audio SAI (the DMA1Stream3 IRQ returns into the body of DMA2Stream? IRQhandler, not into audio:;process()
__attribute__((optimize("O0"))) void output_silence(AudioOutBuffer &out) {
	for (auto &out_ : out) {
		for (auto &outchan : out_.chan)
			outchan = 0;
	}
}

using namespace mdrivlib;

constexpr bool DEBUG_PASSTHRU_AUDIO = false;
constexpr bool DEBUG_SINEOUT_AUDIO = false;
constexpr bool DEBUG_NE10_FFT = false;
// static FFTfx fftfx;
// static Convolver fftfx;

static constexpr unsigned block_0 = 1; //TargetName == Targets::stm32h7x5 ? 0 : 1;
static constexpr unsigned block_1 = 1 - block_0;

AudioStream::AudioStream(PatchPlayer &patchplayer,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 SyncParams &paramcache,
						 PatchPlayLoader &patchloader,
						 DoubleBufParamBlock &p,
						 DoubleAuxStreamBlock &auxs,
						 PatchModQueue &patch_mod_queue)
	: param_cache{paramcache}
	, patch_loader{patchloader}
	, param_blocks{p}
	, audio_blocks{{.in_codec = audio_in_block.codec[0],
					.out_codec = audio_out_block.codec[0],
					.in_ext_codec = audio_in_block.ext_codec[0],
					.out_ext_codec = audio_out_block.ext_codec[0]},
				   {.in_codec = audio_in_block.codec[1],
					.out_codec = audio_out_block.codec[1],
					.in_ext_codec = audio_in_block.ext_codec[1],
					.out_ext_codec = audio_out_block.ext_codec[1]}}
	, auxsigs{auxs}
	, codec_{Hardware::codec}
	, codec_ext_{Hardware::codec_ext}
	, sample_rate_{Hardware::codec.get_samplerate()}
	, player{patchplayer}
	, patch_mod_queue{patch_mod_queue} {

	if (codec_.init() == CodecT::CODEC_NO_ERR)
		UartLog::log("Codec initialized\n\r");
	else
		UartLog::log("ERROR: No codec detected\n\r");

	codec_.set_tx_buffer_start(audio_out_block.codec);
	codec_.set_rx_buffer_start(audio_in_block.codec);

	if (codec_ext_.init() == CodecT::CODEC_NO_ERR) {
		ext_audio_connected = true;
		codec_ext_.set_tx_buffer_start(audio_out_block.ext_codec);
		codec_ext_.set_rx_buffer_start(audio_in_block.ext_codec);
		UartLog::log("Ext Audio codec detected\n\r");
	} else {
		ext_audio_connected = false;
		UartLog::log("No ext Audio codec detected\n\r");
	}

	auto audio_callback = [this]<unsigned block>() {
		// Debug::Pin0::high();

		load_lpf += (load_measure.get_last_measurement_load_float() - load_lpf) * 0.005f;
		param_blocks[block].metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
		load_measure.start_measurement();

		HWSemaphore<block == 0 ? ParamsBuf1Lock : ParamsBuf2Lock>::lock();
		HWSemaphore<block == 0 ? ParamsBuf2Lock : ParamsBuf1Lock>::unlock();
		process(audio_blocks[1 - block], param_blocks[block], auxsigs[block]);

		load_measure.end_measurement();

		param_cache.write_sync(param_state, param_blocks[block].metaparams);
		mdrivlib::SystemCache::clean_dcache_by_range(&param_cache, sizeof(SyncParams));

		// Debug::Pin0::low();
	};

	codec_.set_callbacks([audio_callback]() { audio_callback.operator()<0>(); },
						 [audio_callback]() { audio_callback.operator()<1>(); });
	load_measure.init();

	// Do this, then we don't have to also scale.
	// But we still need to clamp
	// constexpr uint32_t TenVolts = 0x007FFFFF;
	// constexpr uint32_t TwoVolts = TenVolts / 5;
	// constexpr uint32_t FourVolts = TwoVolts * 2;
	// // use the raw int value read when calibrating (can be a float since we'll probably average it over 200ms or
	// whatever) incal[3].calibrate_chan<TwoVolts, FourVolts>(6352.f / 32768.f * 83886308..., 12610.f / 32768.f);
	//
	// This converts float to volts
	incal[3].calibrate_chan<2, 4, 10>(6352.f / 32768.f, 12603.f / 32768.f);
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	auto raw_out = -1.f * player.get_panel_output(output_id) * mute_ctr;
	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
	return scaled_out;
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

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block, AuxStreamBlock &aux) {
	auto &in = audio_block.in_codec;
	auto &out = audio_block.out_codec;

	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		AudioTestSignal::passthrough(in, out, aux);
		return;
	} else if (DEBUG_SINEOUT_AUDIO) {
		AudioTestSignal::sines_out(in, out);
		return;
	}

	if (patch_loader.is_loading_new_patch()) {
		if (mute_ctr > 0.f)
			mute_ctr -= 0.1f;
		else {
			if (!patch_loader.is_audio_muted()) {
				output_silence(out);
				halves_muted++;
				if (halves_muted == 2)
					patch_loader.audio_is_muted();
			}
			return;
		}
	} else {
		patch_loader.audio_not_muted();
		mute_ctr = 1.f;
		halves_muted = 0;
	}

	// TODO: check with patch_loader, not patch_player
	if (!player.is_loaded) {
		output_silence(out);
		return;
	}

	handle_patch_mods();

	// TODO: handle second codec
	if (ext_audio_connected)
		AudioTestSignal::passthrough(audio_block.in_ext_codec, audio_block.out_ext_codec);

	// Handle jacks being plugged/unplugged
	propagate_sense_pins(param_block.params[0]);
	const auto jack_sense = param_block.params[0].jack_senses;
	param_state.jack_senses = jack_sense;

	for (auto [in_, out_, aux_, params_] : zip(in, out, aux, param_block.params)) {

		// Pass audio inputs to modules
		for (auto [codec_chan_i, inchan] : countzip(in_.chan)) {
			auto panel_jack_i = PanelDef::audioin_order[codec_chan_i];

			if (((jack_sense >> jacksense_pin_order[panel_jack_i]) & 1) == 0)
				continue;

			float scaled_input = incal[panel_jack_i].adjust(AudioInFrame::scaleInput(inchan));
			// TODO: bake the unsigned=>float conversion into Calibrate::adjust(), and then use sign_extend instead of scaleInput

			player.set_panel_input(panel_jack_i, scaled_input);
			param_block.metaparams.ins[panel_jack_i].update(scaled_input);
		}

		// Pass CV values to modules (not in current version)
		// for (auto [i, cv] : countzip(params_.cvjacks))
		// 	player.set_panel_input(i + FirstCVInput, cv);

		for (auto [i, gatein] : countzip(params_.gate_ins)) {
			player.set_panel_input(i + FirstGateInput, gatein.is_high() ? 1.f : 0.f);
			//TODO: set param_state.gate_ins if it changed
		}

		// Pass Knob values to modules
		for (auto [i, knob, latch] : countzip(params_.knobs, param_state.knobs)) {
			if (latch.store_changed(knob))
				player.set_panel_param(i, knob);
		}

		// TODO: add more MIDI mappings (duo/quad/octophonic, CC=>gate, CC=>param, CC=>jack)
		if (param_block.metaparams.midi_connected) {
			player.set_panel_param(MidiMonoNoteParam, params_.midi_note);
			//TODO: set param_state.midi_note if it changed

			// player.set_panel_param(MidiMonoGateParam, params_.midi_gate);

			// player.set_panel_input(FirstMidiNoteInput, params_.midi_note);
			player.set_panel_input(MidiMonoGateJack, params_.midi_gate);
			//TODO: set param_state.midi_gate if it changed
		}

		// Run each module
		player.update_patch();

		// Get outputs from modules
		for (auto [i, outchan] : countzip(out_.chan))
			outchan = get_audio_output(i);

		// DAC output (not in current hardware)
		// for (unsigned i = 0; i < PanelDef::NumDACOut; i++)
		// 	aux_.set_output(i, get_dac_output(i + PanelDef::NumAudioOut));

		// Gate outputs (not in current hardware)
		// for (auto [i, gate_out] : countzip(aux_.gate_out))
		// 	gate_out = player.get_panel_output(i + PanelDef::NumAudioOut + PanelDef::NumDACOut) > 0.5f ? 1 : 0;
	}
}

void AudioStream::start() {
	codec_.start();
	if (ext_audio_connected)
		codec_ext_.start();
}

void AudioStream::handle_patch_mods() {
	if (auto patch_mod = patch_mod_queue.get()) {
		std::visit(overloaded{
					   [this](SetStaticParam &mod) { player.apply_static_param(mod.param); },
					   [this](ChangeKnobSet mod) { player.set_active_knob_set(mod.knobset_num); },
					   [](AddMapping &mod) { /*TODO*/ },
					   [](ModifyMapping &mod) { /*TODO*/ },
				   },
				   patch_mod.value());
	}
}

void AudioStream::propagate_sense_pins(Params &params) {
	for (int i = 0; i < PanelDef::NumUserFacingInJacks; i++) {
		auto pin_bit = jacksense_pin_order[i];
		bool sense = params.jack_senses & (1 << pin_bit);
		plug_detects[i].update(sense);
		if (plug_detects[i].changed())
			player.set_input_jack_patched_status(i, sense);
	}

	for (int out_i = 0; out_i < PanelDef::NumUserFacingOutJacks; out_i++) {
		auto jack_i = out_i + PanelDef::NumUserFacingInJacks;
		auto pin_bit = jacksense_pin_order[jack_i];
		bool sense = params.jack_senses & (1 << pin_bit);
		plug_detects[jack_i].update(sense);
		if (plug_detects[jack_i].changed())
			player.set_output_jack_patched_status(out_i, sense);
	}
}

} // namespace MetaModule
