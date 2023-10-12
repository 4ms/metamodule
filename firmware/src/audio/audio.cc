#include "audio/audio.hh"
#include "audio/audio_test_signals.hh"
#include "conf/hsem_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "conf/scaling_config.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "param_block.hh"
#include "patch_play/patch_mods.hh"
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

AudioStream::AudioStream(PatchPlayer &patchplayer,
						 AudioInBlock &audio_in_block,
						 AudioOutBlock &audio_out_block,
						 SyncParams &sync_p,
						 PatchPlayLoader &patchloader,
						 DoubleBufParamBlock &pblk,
						 DoubleAuxStreamBlock &auxs,
						 PatchModQueue &patch_mod_queue)
	: sync_params{sync_p}
	, patch_loader{patchloader}
	, param_blocks{pblk}
	, audio_blocks{{.in_codec = audio_in_block.codec[0],
					.out_codec = audio_out_block.codec[0],
					.in_ext_codec = audio_in_block.ext_codec[0],
					.out_ext_codec = audio_out_block.ext_codec[0]},
				   {.in_codec = audio_in_block.codec[1],
					.out_codec = audio_out_block.codec[1],
					.in_ext_codec = audio_in_block.ext_codec[1],
					.out_ext_codec = audio_out_block.ext_codec[1]}}
	, auxsigs{auxs}
	, patch_mod_queue{patch_mod_queue}
	, codec_{Hardware::codec}
	, codec_ext_{Hardware::codec_ext}
	, sample_rate_{Hardware::codec.get_samplerate()}
	, player{patchplayer} {

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

		load_lpf += (load_measure.get_last_measurement_load_float() - load_lpf) * 0.05f;
		param_blocks[block].metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
		load_measure.start_measurement();

		HWSemaphore<block == 0 ? ParamsBuf1Lock : ParamsBuf2Lock>::lock();
		HWSemaphore<block == 0 ? ParamsBuf2Lock : ParamsBuf1Lock>::unlock();
		process(audio_blocks[1 - block], param_blocks[block], auxsigs[block]);

		load_measure.end_measurement();

		sync_params.write_sync(param_state, param_blocks[block].metaparams);
		mdrivlib::SystemCache::clean_dcache_by_range(&sync_params, sizeof(SyncParams));

		// Debug::Pin0::low();
	};

	codec_.set_callbacks([audio_callback]() { audio_callback.operator()<0>(); },
						 [audio_callback]() { audio_callback.operator()<1>(); });
	load_measure.init();

	//TODO: User/factory routine to calibrate jacks
	for (auto &inc : incal)
		inc.calibrate_chan<InputLowRangeMillivolts, InputHighRangeMillivolts, 1000>(
			-1.f * (float)AudioInFrame::kMaxValue, (float)AudioInFrame::kMaxValue - 1.f);
}

void AudioStream::start() {
	codec_.start();
	if (ext_audio_connected)
		codec_ext_.start();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	auto raw_out = player.get_panel_output(output_id) * mute_ctr;
	raw_out = -raw_out / OutputHighRangeVolts;
	auto scaled_out = AudioOutFrame::scaleOutput(raw_out);
	return scaled_out;
}

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block, AuxStreamBlock &aux) {
	auto &in = audio_block.in_codec;
	auto &out = audio_block.out_codec;

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

	handle_patch_mods(patch_mod_queue, player);

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

			// Skip unpatched jacks
			if (((jack_sense >> jacksense_pin_order[panel_jack_i]) & 1) == 0)
				continue;

			float scaled_input = incal[panel_jack_i].adjust(AudioInFrame::sign_extend(inchan));

			player.set_panel_input(panel_jack_i, scaled_input);
			param_block.metaparams.ins[panel_jack_i].update(scaled_input);
		}

		for (auto [i, gatein] : countzip(params_.gate_ins)) {
			if (gatein.just_went_high())
				player.set_panel_input(i + FirstGateInput, 8.f);
			if (gatein.just_went_low())
				player.set_panel_input(i + FirstGateInput, 0.f);
		}

		// Pass Knob values to modules
		for (auto [i, knob, latch] : countzip(params_.knobs, param_state.knobs)) {
			if (latch.store_changed(knob))
				player.set_panel_param(i, knob);
		}

		if (param_block.metaparams.midi_connected) {

			// Notes (pitch, gate, velocity)
			for (auto [i, note, note_state] : countzip(params_.midi.notes, param_state.notes)) {
				if (note_state.pitch.store_changed(note.pitch))
					player.set_midi_note_pitch(i, note.pitch);

				if (note_state.gate.store_changed(note.gate))
					player.set_midi_note_gate(i, note.gate ? 8.f : 0.f);

				if (note_state.vel.store_changed(note.vel))
					player.set_midi_note_velocity(i, note.vel);

				if (note_state.aft.store_changed(note.aft))
					player.set_midi_note_aftertouch(i, note.aft);
			}

			auto &event = params_.midi.event;

			if (event.type == Params::Midi::Event::Type::GateNote)
				player.set_midi_gate(event.chan, event.val);

			else if (event.type == Params::Midi::Event::Type::CC)
				player.set_midi_cc(event.chan, event.val);

			else if (event.type == Params::Midi::Event::Type::Bend)
				player.set_midi_cc(128, event.val);

			// clear the event
			event.type = Params::Midi::Event::Type::None;
		}

		// Run each module
		player.update_patch();

		// Get outputs from modules
		for (auto [i, outchan] : countzip(out_.chan))
			outchan = get_audio_output(i);
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
