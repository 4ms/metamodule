#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
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

	//MIDI
	struct Note {
		LatchedParam<float, 3, 1000> pitch;
		LatchedParam<uint8_t, 1> gate;
		LatchedParam<float, 1, 128> vel;
	};
	std::array<Note, MidiPolyphony> notes{};

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

		for (auto &note : notes) {
			note.pitch = {0.f, false};
			note.gate = {0, false};
			note.vel = {0.f, false};
		}

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

		for (auto [note, that_note] : zip(notes, that.notes)) {
			note = that_note;
			that_note.pitch.changed = false;
			that_note.gate.changed = false;
			that_note.vel.changed = false;
		}

		jack_senses = that.jack_senses;
	}

	void copy_to(ParamsState &that) const {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			that_gate_in.copy_state(gate_in);

		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			that_knob = knob;
		}

		for (auto [note, that_note] : zip(notes, that.notes)) {
			that_note = note;
		}

		that.jack_senses = jack_senses;
	}
};

} // namespace MetaModule
