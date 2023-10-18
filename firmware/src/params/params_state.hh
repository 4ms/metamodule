#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "midi_params.hh"
#include "patch/midi_def.hh"
#include "util/debouncer.hh"
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

	uint32_t jack_senses;

	// LatchedParam<uint8_t, 1> last_midi_note;

	LatchedParam<uint8_t, 1> midi_cc_chan;
	LatchedParam<uint8_t, 1> midi_cc_val;

	void set_input_plugged(unsigned panel_injack_idx, bool plugged) {
		if (plugged)
			jack_senses |= (1 << jacksense_pin_order[panel_injack_idx]);
		else
			jack_senses &= ~(1 << jacksense_pin_order[panel_injack_idx]);
	}

	bool is_input_plugged(unsigned panel_injack_idx) {
		return jack_senses & (1 << jacksense_pin_order[panel_injack_idx]);
	}

	void set_output_plugged(unsigned panel_outjack_idx, bool plugged) {
		auto jack_idx = panel_outjack_idx + PanelDef::NumAudioIn + PanelDef::NumGateIn;
		if (plugged)
			jack_senses |= (1 << jacksense_pin_order[jack_idx]);
		else
			jack_senses &= ~(1 << jacksense_pin_order[jack_idx]);
	}

	bool is_output_plugged(unsigned panel_outjack_idx) {
		auto jack_idx = panel_outjack_idx + PanelDef::NumAudioIn + PanelDef::NumGateIn;
		return jack_senses & (1 << jacksense_pin_order[jack_idx]);
	}

	void clear() {
		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &knob : knobs)
			knob = {0.f, false};

		// last_midi_note = 0xFF;
		midi_cc_chan = 0xFF;
		midi_cc_val = 0xFF;

		jack_senses = 0;
	}

	// Copy values, but clear the changed flag after moving it
	void move_from(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			gate_in.copy_state(that_gate_in);

		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			knob.changed = that_knob.changed;
			knob.val = that_knob.val;
			that_knob.changed = false;
		}

		midi_cc_chan.store_changed(that.midi_cc_chan.val);
		midi_cc_val.store_changed(that.midi_cc_val.val);

		jack_senses = that.jack_senses;
	}

	void copy_to(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			that_gate_in.copy_state(gate_in);

		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			that_knob = knob;
		}

		// that.midi_cc_chan.store_changed(midi_cc_chan.val);
		// that.midi_cc_val.store_changed(midi_cc_val.val);
		that.midi_cc_chan.val = midi_cc_chan.val;
		if (midi_cc_chan.did_change())
			that.midi_cc_chan.changed = true;

		that.midi_cc_val.val = midi_cc_val.val;
		if (midi_cc_val.did_change())
			that.midi_cc_val.changed = true;

		that.jack_senses = jack_senses;
	}
};

} // namespace MetaModule
