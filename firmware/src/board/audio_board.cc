#include "audio/audio.hh"
#include "util/countzip.hh"
#include "util/zip.hh"

namespace MetaModule
{

void AudioStream::process(CombinedAudioBlock &audio_block, ParamBlock &param_block) {
	player.sync();

	param_state.encoder[0] = param_block.metaparams.encoder[0];
	param_state.encoder[1] = param_block.metaparams.encoder[1];
	param_state.usb_midi_connected = param_block.metaparams.usb_midi_connected;

	// Who is responsible for setting this?
	param_block.metaparams.haptic_out = 0;

	// Buttons (~1us/block)
	for (auto [i, param_state_button] : enumerate(param_state.buttons)) {
		auto src = (i < 16) ? param_block.metaparams.buttons0 :
				   (i < 32) ? param_block.metaparams.buttons1 :
							  param_block.metaparams.buttons2;
		bool button = (src >> i) & 1;

		param_state_button.register_state(button);

		if (param_state_button.just_went_low())
			player.set_panel_param(i + Mousai::FirstButton, 0.f);

		else if (param_state_button.just_went_high())
			player.set_panel_param(i + Mousai::FirstButton, 1.f);
	}

	for (auto idx = 0u; auto const &in : audio_block.in_codec) {
		auto &out = audio_block.out_codec[idx];
		auto &params = param_block.params[idx];

		// Audio inputs
		for (auto [panel_jack_i, inchan] : zip(PanelDef::audioin_order, in.chan)) {

			float calibrated_input = cal.in_cal[panel_jack_i].adjust(AudioInFrame::sign_extend(inchan));

			player.set_panel_input(panel_jack_i, calibrated_input);

			// Send smoothed sigals to other core
			param_state.smoothed_ins[panel_jack_i].add_val(calibrated_input);
		}

		// Gate inputs: no change = 0.4us/sample = 2.1% load
		for (auto [i, sync_gatein] : enumerate(param_state.gate_ins)) {
			bool gate = (params.gate_ins >> i) & 1;

			sync_gatein.register_state(gate);

			if (sync_gatein.just_went_low())
				player.set_panel_input(i + FirstGateInput, 0.f);
			else if (sync_gatein.just_went_high())
				player.set_panel_input(i + FirstGateInput, 8.f);
		}

		// Pass Knob values to modules
		// All knobs changing constantly = ~1us/sample = 64us/block = 4.8% load
		for (auto [i, knob_val, knob_state] : countzip(params.knobs, param_state.knobs)) {
			if (knob_state.store_changed(knob_val))
				player.set_panel_param(i, knob_val);
		}

		// Pass CV values to module jacks
		for (auto [i, cv_val, cv_state] : countzip(params.cvs, param_state.cvs)) {
			if (cv_state.store_changed(cv_val))
				player.set_panel_input(i + FirstCVInput, cv_val);
		}

		// USB MIDI
		usb_midi.process(param_block.metaparams.usb_midi_connected, &params.usb_raw_midi);

		// UART MIDI
		uart_midi.process(true, &params.uart_raw_midi);

		// Run each module
		player.update_patch();

		// Get outputs from modules
		out.chan[0] = get_audio_output(0);
		out.chan[1] = get_audio_output(1);

		// DAC outputs
		// TODO: adjust scaling. This assumes the module outputs 0 - 1
		params.dac0 = std::clamp<uint16_t>(player.get_panel_output(Mousai::LFOOut1) * 4095, 0, 4095);
		params.dac1 = std::clamp<uint16_t>(player.get_panel_output(Mousai::LFOOut2) * 4095, 0, 4095);

		idx++;
	}
}

// Copy needed params/metaparams from the slow non-cachable shared param block to a local copy
ParamBlock &AudioStream::cache_params(unsigned block) {
	local_params.metaparams.buttons0 = param_blocks[block].metaparams.buttons0;
	local_params.metaparams.buttons1 = param_blocks[block].metaparams.buttons1;
	local_params.metaparams.buttons2 = param_blocks[block].metaparams.buttons2;

	std::memcpy((void *)local_params.params.data(), &param_blocks[block].params, sizeof(Params) * block_size_);

	return local_params;
}

// Copy back values that the Controls class needs (for non-audio outputs)
void AudioStream::return_cached_params(unsigned block) {
	param_blocks[block].metaparams.haptic_out = local_params.metaparams.haptic_out;

	for (auto i = 0u; i < block_size_; i++) {
		param_blocks[block].params[i].dac0 = local_params.params[i].dac0;
		param_blocks[block].params[i].dac1 = local_params.params[i].dac1;
		param_blocks[block].params[i].clock_out = local_params.params[i].clock_out;
		param_blocks[block].params[i].uart_raw_midi = local_params.params[i].uart_raw_midi;
		param_blocks[block].params[i].usb_raw_midi = local_params.params[i].usb_raw_midi;
	}
}

} // namespace MetaModule
