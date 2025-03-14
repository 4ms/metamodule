#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "midi_params.hh"
#include "patch/midi_def.hh"
#include "patch/patch.hh"
#include "patch_play/lights.hh"
#include "patch_play/text_display.hh"
#include "util/debouncer.hh"
#include "util/filter.hh"
#include "util/parameter.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct ParamsState {
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> knobs{};
	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};

	std::array<ResizingOversampler, PanelDef::NumAudioIn + AudioExpander::NumInJacks> smoothed_ins;

	//jack_senses bit order:
	//0-5: Audio Ins (main panel)
	//6,7: Gate Ins (main panel)
	//8-15: Audio Outs (main panel)
	//16-21: Expander Audio Ins
	//22-29: Expander Audio outs
	//30-31: Unused
	uint32_t jack_senses;

	void clear() {
		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &knob : knobs)
			knob = {0.f, false};

		for (auto &in : smoothed_ins)
			in.reset();

		jack_senses = 0;
	}

	void reset_change_flags() {
		for (auto &knob : knobs)
			knob.changed = false;
	}

	// Given an input jack ID (panel=0..7, expander = 8..13)
	// return the corresponding bit position in `jack_senses`
	static constexpr unsigned input_bit(unsigned panel_injack_idx) {
		auto p = panel_injack_idx;
		return main_jacksense_input_bit(p).value_or(AudioExpander::jacksense_input_bit(p).value_or(0));
	}

	// Given an output jack ID (panel=0..7, expander = 8..15)
	// return the corresponding bit position in `jack_senses`
	static constexpr unsigned output_bit(unsigned panel_outjack_idx) {
		auto p = panel_outjack_idx;
		return main_jacksense_output_bit(p).value_or(AudioExpander::jacksense_output_bit(p).value_or(0));
	}

	void set_input_plugged(unsigned panel_injack_idx, bool plugged) {
		if (plugged)
			jack_senses |= (1 << input_bit(panel_injack_idx));
		else
			jack_senses &= ~(1 << input_bit(panel_injack_idx));
	}

	//0-5: Main Audio Ins, 6-7: GateIns, 8-13: Expander Ins
	bool is_input_plugged(unsigned panel_injack_idx) {
		return jack_senses & (1 << input_bit(panel_injack_idx));
	}

	//0-7: Main Outs, 8-15: Expander Outs
	void set_output_plugged(unsigned panel_outjack_idx, bool plugged) {
		if (plugged)
			jack_senses |= (1 << output_bit(panel_outjack_idx));
		else
			jack_senses &= ~(1 << output_bit(panel_outjack_idx));
	}

	bool is_output_plugged(unsigned panel_outjack_idx) {
		return jack_senses & (1 << output_bit(panel_outjack_idx));
	}

	friend void copy(ParamsState &dst, ParamsState const &src) {
		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins))
			gate_in = that_gate_in;

		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs)) {
			knob = that_knob;
		}

		dst.jack_senses = src.jack_senses;

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;
	}

	friend void transfer_events(ParamsState &dst, ParamsState const &src) {
		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins))
			gate_in = that_gate_in;

		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs)) {
			knob.val = that_knob.val;
			// only reader can clear knob change events, writer can set them
			knob.changed = that_knob.changed | knob.changed;
		}

		dst.jack_senses = src.jack_senses;

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;
	}
};

struct ParamsMidiState : ParamsState {
	std::array<LatchedParam<float, 1, 127>, NumMidiCCs> midi_ccs;
	LatchedParam<uint8_t, 1, 1> last_midi_note;
	bool midi_gate = false;

	LightWatcher lights;
	TextDisplayWatcher displays;

	void clear() {
		ParamsState::clear();

		lights.stop_watching_all();
		displays.stop_watching_all();

		for (auto &cc : midi_ccs)
			cc = 0;

		midi_gate = false;
		last_midi_note = 0;
	}
};

} // namespace MetaModule
