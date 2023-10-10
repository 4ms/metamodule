#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "util/debouncer.hh"
#include "util/parameter.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct ParamsState {
	static constexpr unsigned Polyphony = 4;
	static constexpr unsigned MaxSimulGates = 8;

	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> knobs{};
	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};

	uint32_t jack_senses;

	//MIDI
	struct Note {
		LatchedParam<float, 3, 1000> pitch;
		LatchedParam<uint8_t, 1> gate;
		LatchedParam<float, 1, 128> vel;
	};
	std::array<Note, Polyphony> notes{};

	struct GateEvent {
		LatchedParam<uint8_t, 1> notenum;
		LatchedParam<uint8_t, 1> gateamp;
	};
	std::array<GateEvent, MaxSimulGates> gate_events;

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

		for (auto &gate : gate_events) {
			gate.notenum = {0, false};
			gate.gateamp = {0, false};
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
			// note.pitch.changed = that_note.pitch.changed;
			// note.pitch.val = that_note.pitch.val;
			that_note.pitch.changed = false;

			// note.gate.changed = that_note.gate.changed;
			// note.gate.val = that_note.gate.val;
			that_note.gate.changed = false;

			// note.vel.changed = that_note.vel.changed;
			// note.vel.val = that_note.vel.val;
			that_note.vel.changed = false;
		}

		for (auto [gate, that_gate] : zip(gate_events, that.gate_events)) {
			gate = that_gate;
			that_gate.gateamp.changed = false;
			that_gate.notenum.changed = false;
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

		for (auto [gate, that_gate] : zip(gate_events, that.gate_events)) {
			that_gate = gate;
		}

		that.jack_senses = jack_senses;
	}
};

} // namespace MetaModule
