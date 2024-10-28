#include "audio/audio.hh"
#include "CoreModules/hub/audio_expander_defs.hh"
#include "audio/audio_test_signals.hh"
#include "calibrate/calibration_data_reader.hh"
#include "conf/audio_settings.hh"
#include "conf/hsem_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "expanders.hh"
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
						 PatchModQueue &patch_mod_queue)
	: sync_params{sync_p}
	, patch_loader{patchloader}
	, param_blocks{pblk}
	, patch_mod_queue{patch_mod_queue}
	, audio_in_block{audio_in_block}
	, audio_out_block{audio_out_block}
	, codec_{Hardware::codec}
	, codec_ext_{Hardware::codec_ext}
	, sample_rate_{AudioSettings::DefaultSampleRate}
	, block_size_{AudioSettings::DefaultBlockSize}
	, player{patchplayer} {

	if (codec_.init() == CodecT::CODEC_NO_ERR)
		pr_info("Codec initialized\n");
	else
		pr_info("ERROR: No codec detected\n");

	set_block_spans();

	codec_.set_tx_buffer(audio_blocks[0].out_codec, block_size_);
	codec_.set_rx_buffer(audio_blocks[0].in_codec, block_size_);

	if (codec_ext_.init() == CodecT::CODEC_NO_ERR) {
		ext_audio_connected = true;
		Expanders::ext_audio_found(true);
		codec_ext_.set_tx_buffer(audio_blocks[0].out_ext_codec, block_size_);
		codec_ext_.set_rx_buffer(audio_blocks[0].in_ext_codec, block_size_);

		ext_cal.reset_to_default();
		if (!CalibrationDataReader::read_calibration(&ext_cal, Hardware::codec_ext_memory, 0)) {
			ext_cal.reset_to_default();
			Hardware::codec_ext_memory.write(ext_cal);
		}
		ext_cal_stash = ext_cal;

		pr_info("Audio Expander detected\n");
		ext_cal.print_calibration();
	} else {
		ext_audio_connected = false;
		Expanders::ext_audio_found(false);
		pr_info("No Audio Expander detected\n");
	}

	cal.reset_to_default();
	cal_stash.reset_to_default();

	auto audio_callback = [this]<unsigned block>() {
		// Debug::Pin0::high();

		load_lpf += (load_measure.get_last_measurement_load_float() - load_lpf) * 0.05f;
		param_blocks[block].metaparams.audio_load = static_cast<uint8_t>(load_lpf * 100.f);
		load_measure.start_measurement();

		HWSemaphore<block == 0 ? ParamsBuf1Lock : ParamsBuf2Lock>::lock();
		HWSemaphore<block == 0 ? ParamsBuf2Lock : ParamsBuf1Lock>::unlock();

		// Blocksize 64: alternating 33.8us on block 1, 66us on block 0
		// time changes relative to block size (always 0.53/1.03us per frame = 3.7% avg. load)
		auto &params = cache_params(block);

		if (is_playing_patch())
			process(audio_blocks[1 - block], params);
		else
			process_nopatch(audio_blocks[1 - block], params);

		return_cached_params(block);

		// 3.5us w/both MIDIs
		sync_params.write_sync(param_state, param_blocks[block].metaparams);
		param_state.reset_change_flags();

		update_audio_settings();

		load_measure.end_measurement();
		if (load_measure.get_last_measurement_load_percent() >= 98) {
			output_fade_amt = 0.f;
			patch_loader.notify_audio_overrun();
		}

		// Debug::Pin0::low();
	};

	codec_.set_callbacks([audio_callback]() { audio_callback.operator()<0>(); },
						 [audio_callback]() { audio_callback.operator()<1>(); });
	load_measure.init();

	for (auto &s : param_state.smoothed_ins)
		s.set_size(block_size_);
}

void AudioStream::start() {
	codec_.start();
	if (ext_audio_connected)
		codec_ext_.start();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id) {
	float output_volts = player.get_panel_output(output_id) * output_fade_amt;
	return MathTools::signed_saturate(cal.out_cal[output_id].adjust(output_volts), 24);
}

AudioConf::SampleT AudioStream::get_ext_audio_output(int output_id) {
	output_id = AudioExpander::out_order[output_id];
	float output_volts = player.get_panel_output(output_id + PanelDef::NumAudioOut) * output_fade_amt;
	return MathTools::signed_saturate(ext_cal.out_cal[output_id].adjust(output_volts), 24);
}

bool AudioStream::is_playing_patch() {
	if (patch_loader.should_fade_down_audio()) {
		output_fade_delta = -1.f / (sample_rate_ * 0.02f);
		if (output_fade_amt <= 0.f) {
			output_fade_amt = 0.f;
			output_fade_delta = 0.f;
			patch_loader.notify_audio_is_muted();
		}

	} else if (patch_loader.should_fade_up_audio()) {
		output_fade_delta = 1.f / (sample_rate_ * 0.02f);
		if (output_fade_amt >= 1.f) {
			output_fade_amt = 1.f;
			output_fade_delta = 0.f;
			patch_loader.notify_audio_not_muted();
			handle_patch_just_loaded();
		}
	}

	return patch_loader.is_playing();
}

void AudioStream::handle_patch_just_loaded() {
	// Reset the plug detects
	// this ensures any patched jacks will be detected as a new event
	// and will propagate to the patch player
	for (auto &p : plug_detects)
		p.reset();

	midi_last_connected = false;
}

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block) {
	handle_patch_mod_queue();

	param_block.metaparams.midi_poly_chans = player.get_midi_poly_num();

	for (auto idx = 0u; auto const &in : audio_block.in_codec) {
		auto &out = audio_block.out_codec[idx];
		auto const &params = param_block.params[idx];
		auto &ext_out = audio_block.out_ext_codec[idx];
		auto const &ext_in = audio_block.in_ext_codec[idx];
		idx++;

		// Audio inputs
		for (auto [panel_jack_i, inchan] : zip(PanelDef::audioin_order, in.chan)) {

			// Skip unpatched jacks
			if (!jack_is_patched(param_state.jack_senses, panel_jack_i))
				continue;

			float calibrated_input = cal.in_cal[panel_jack_i].adjust(AudioInFrame::sign_extend(inchan));

			player.set_panel_input(panel_jack_i, calibrated_input);

			// Send smoothed sigals to other core
			param_state.smoothed_ins[panel_jack_i].add_val(calibrated_input);
		}

		if (ext_audio_connected) {
			for (auto [exp_panel_jack_i, inchan] : zip(AudioExpander::in_order, ext_in.chan)) {

				// Skip unpatched jacks
				if (!AudioExpander::jack_is_patched(param_state.jack_senses, exp_panel_jack_i))
					continue;

				float calibrated_input = ext_cal.in_cal[exp_panel_jack_i].adjust(AudioInFrame::sign_extend(inchan));

				auto panel_jack_i = AudioExpander::exp_to_panel_input(exp_panel_jack_i); //0..5 => 8..13
				player.set_panel_input(panel_jack_i, calibrated_input);

				// Smoothed ins skips the gate inputs, so subtract those from the index: 8..13 => 6..11
				auto smooth_idx = panel_jack_i - PanelDef::NumGateIn;
				param_state.smoothed_ins[smooth_idx].add_val(calibrated_input);
			}
		}

		// Gate inputs
		for (auto [i, sync_gatein] : enumerate(param_state.gate_ins)) {
			bool gate =
				jack_is_patched(param_state.jack_senses, i + FirstGateInput) ? ((params.gate_ins >> i) & 1) : false;

			sync_gatein.register_state(gate);

			if (sync_gatein.just_went_low())
				player.set_panel_input(i + FirstGateInput, 0.f);
			else if (sync_gatein.just_went_high())
				player.set_panel_input(i + FirstGateInput, 8.f);
		}

		// Pass Knob values to modules
		for (auto [i, knob, latch] : countzip(params.knobs, knob_states)) {
			if (latch.store_changed(knob))
				player.set_panel_param(i, knob);
		}

		// MIDI
		handle_midi(param_block.metaparams.midi_connected,
					params.midi_event,
					param_block.metaparams.midi_poly_chans,
					params.raw_msg);

		// Run each module
		player.update_patch();

		// Get outputs from modules
		output_fade_amt += output_fade_delta;

		for (auto [i, outchan] : countzip(out.chan))
			outchan = get_audio_output(i);

		// Ext audio modules:
		if (ext_audio_connected) {
			for (auto [i, extoutchan] : countzip(ext_out.chan))
				extoutchan = get_ext_audio_output(i);
		}
	}

	player.update_lights();
	propagate_sense_pins(param_block.metaparams.jack_senses);
}

void AudioStream::process_nopatch(CombinedAudioBlock &audio_block, ParamBlock &param_block) {
	param_state.jack_senses = param_block.metaparams.jack_senses;

	// for (auto [in, out, params] : zip(audio_block.in_codec, audio_block.out_codec, param_block.params)) {
	for (auto idx = 0u; auto const &in : audio_block.in_codec) {
		auto &out = audio_block.out_codec[idx];
		auto &params = param_block.params[idx];
		idx++;

		// Set metaparams.ins with input signals
		for (auto [panel_jack_i, inchan] : zip(PanelDef::audioin_order, in.chan)) {
			float scaled_input = jack_is_patched(param_state.jack_senses, panel_jack_i) ?
									 cal.in_cal[panel_jack_i].adjust(AudioInFrame::sign_extend(inchan)) :
									 0;
			param_state.smoothed_ins[panel_jack_i].add_val(scaled_input);
		}

		for (auto [knob, latch] : zip(params.knobs, param_state.knobs))
			latch.store_changed(knob);

		if (params.midi_event.type == Midi::Event::Type::CC)
			sync_params.midi_events.put(params.midi_event);

		for (auto &outchan : out.chan)
			outchan = 0;
	}
}

void AudioStream::handle_midi(bool is_connected,
							  Midi::Event const &event,
							  unsigned poly_num,
							  MidiMessage const &raw_msg) {
	if (is_connected && !midi_last_connected) {
		player.set_midi_connected();
	} else if (!is_connected && midi_last_connected) {
		player.set_midi_disconnected();
	}

	midi_last_connected = is_connected;

	if (!is_connected)
		return;

	if (raw_msg.status != 0xfe && raw_msg.status != 0) {
		// 50ns with no listeners + ~100ns additional per listener
		player.send_raw_midi(raw_msg);
	}

	if (event.type == Midi::Event::Type::None)
		return;

	// All other MIDI events: 150ns min (no listeners) + more... 150-600ns for some listeners
	if (event.type == Midi::Event::Type::NoteOn) {
		player.set_midi_note_pitch(event.poly_chan, Midi::note_to_volts(event.note));
		player.set_midi_note_gate(event.poly_chan, 10.f);
		player.set_midi_note_velocity(event.poly_chan, event.val);
		player.set_midi_note_retrig(event.poly_chan, 10.f);
		player.set_midi_gate(event.note, event.val); //TODO: if not velocity mode, then event.val => 10
		sync_params.midi_events.put(event);

	} else if (event.type == Midi::Event::Type::NoteOff) {
		player.set_midi_note_gate(event.poly_chan, 0);
		player.set_midi_gate(event.note, 0);
		sync_params.midi_events.put(event);

	} else if (event.type == Midi::Event::Type::Aft) {
		player.set_midi_note_aftertouch(event.poly_chan, event.val);

	} else if (event.type == Midi::Event::Type::ChanPress) {
		for (unsigned i = 0; i < poly_num; i++)
			player.set_midi_note_aftertouch(i, event.val);

	} else if (event.type == Midi::Event::Type::CC) {
		player.set_midi_cc(event.note, event.val);
		sync_params.midi_events.put(event);

	} else if (event.type == Midi::Event::Type::Bend) {
		player.set_midi_cc(128, event.val);

	} else if (event.type == Midi::Event::Type::Time) {
		player.send_midi_time_event(event.note, 10.f);
	}
}

void AudioStream::propagate_sense_pins(uint32_t jack_senses) {
	for (unsigned i = 0; auto &plug_detect : plug_detects) {
		bool sense = jack_is_patched(jack_senses, i);
		plug_detect.update(sense);
		if (plug_detect.changed()) {
			if (i < PanelDef::NumUserFacingInJacks)
				player.set_input_jack_patched_status(i, sense);
			else
				player.set_output_jack_patched_status(i - PanelDef::NumUserFacingInJacks, sense);
		}
		i++;
	}

	param_state.jack_senses = jack_senses;
}

void AudioStream::handle_patch_mod_queue() {
	std::optional<bool> new_cal_state = std::nullopt;

	handle_patch_mods(patch_mod_queue, player, {&cal_stash, &ext_cal_stash}, new_cal_state);

	if (new_cal_state.has_value() && *new_cal_state == true)
		re_enable_calibration();

	else if (new_cal_state == false)
		disable_calibration();
}

void AudioStream::disable_calibration() {
	// Stash existing cal so we can restore it later
	cal_stash = cal;
	cal.reset_to_default();

	ext_cal_stash = ext_cal;
	ext_cal.reset_to_default();

	// pr_dbg("Using default cal and ext_cal:\n");
	// 	ext_cal.print_calibration();
}

void AudioStream::re_enable_calibration() {
	cal = cal_stash;
	ext_cal = ext_cal_stash;

	// pr_dbg("Re-enable cal=\n");
	// cal.print_calibration();
	// pr_dbg("Re-enable ext_cal=\n");
	// ext_cal.print_calibration();
}

void AudioStream::set_calibration(CalData const &caldata) {
	cal = caldata;
	cal_stash = caldata;
}

uint32_t AudioStream::get_audio_errors() {
	return codec_.get_sai_errors();
}

// It's measurably faster to copy params into cacheable ram
ParamBlock &AudioStream::cache_params(unsigned block) {
	local_params.metaparams.midi_connected = param_blocks[block].metaparams.midi_connected;
	local_params.metaparams.jack_senses = param_blocks[block].metaparams.jack_senses;

	std::memcpy(local_params.params.data(), param_blocks[block].params.data(), sizeof(Params) * block_size_);

	return local_params;
}

void AudioStream::return_cached_params(unsigned block) {
	// copy midi_poly_chans back so Controls can read it
	param_blocks[block].metaparams.midi_poly_chans = local_params.metaparams.midi_poly_chans;
}

void AudioStream::set_block_spans() {
	audio_blocks[0].in_codec = {audio_in_block.codec[0].data(), block_size_};
	audio_blocks[1].in_codec = {std::next(audio_in_block.codec[0].begin(), block_size_), block_size_};

	audio_blocks[0].out_codec = {audio_out_block.codec[0].data(), block_size_};
	audio_blocks[1].out_codec = {std::next(audio_out_block.codec[0].begin(), block_size_), block_size_};

	audio_blocks[0].in_ext_codec = {audio_in_block.ext_codec[0].data(), block_size_};
	audio_blocks[1].in_ext_codec = {std::next(audio_in_block.ext_codec[0].begin(), block_size_), block_size_};

	audio_blocks[0].out_ext_codec = {audio_out_block.ext_codec[0].data(), block_size_};
	audio_blocks[1].out_ext_codec = {std::next(audio_out_block.ext_codec[0].begin(), block_size_), block_size_};
}

void AudioStream::update_audio_settings() {
	auto [sample_rate, block_size] = patch_loader.get_audio_settings();

	if (sample_rate != sample_rate_ || block_size != block_size_) {

		auto ok = (codec_.change_samplerate_blocksize(sample_rate, block_size) == CodecPCM3168::CODEC_NO_ERR);
		if (ok && ext_audio_connected)
			ok = (codec_ext_.change_samplerate_blocksize(sample_rate, block_size) == CodecPCM3168::CODEC_NO_ERR);

		if (ok) {
			codec_ext_.start();
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
			codec_ext_.start();
			codec_.start();
		}
	}
}

} // namespace MetaModule
