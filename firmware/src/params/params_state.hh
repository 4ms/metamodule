#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct ParamsState {
	static constexpr float min_change = 2.5f / 4096.f;

	struct LatchedKnob {
		float val{0};
		bool changed{false};
		// TODO: if only updating changes of 2.5/4096 is too steppy,
		// then use a tracking_ctr to track value 1:1 for N number
		// of reads after a change >2.5/4096

		bool store_changed(float new_val) {
			if (std::abs(new_val - val) > min_change) {
				val = new_val;
				changed = true;
				return true;
			} else
				return false;
		}

		// Allow LatchedKnob to functionally be a float
		void operator=(float x) {
			val = x;
		}
		operator float() {
			return val;
		}
	};
	std::array<LatchedKnob, PanelDef::NumPot> knobs{};

	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};
	float midi_note;
	bool midi_gate;
	uint32_t jack_senses;

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

		midi_note = 0.f;
		midi_gate = false;
		jack_senses = 0;
	}

	void move_from(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			gate_in.copy_state(that_gate_in);

		// Copy values, but clear the changed flag after moving it
		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			knob.changed = that_knob.changed;
			knob.val = that_knob.val;
			that_knob.changed = false;
		}

		midi_note = that.midi_note;
		midi_gate = that.midi_gate;
		jack_senses = that.jack_senses;
	}

	void copy_to(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			that_gate_in.copy_state(gate_in);

		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			that_knob.changed = knob.changed;
			that_knob.val = knob.val;
		}

		that.midi_note = midi_note;
		that.midi_gate = midi_gate;
		that.jack_senses = jack_senses;
	}
};

} // namespace MetaModule
