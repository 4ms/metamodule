#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "midi_params.hh"
#include "patch.hh"
#include "patch/midi_def.hh"
#include "patch_play/lights.hh"
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

	void clear() {
		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &knob : knobs)
			knob = {0.f, false};

		jack_senses = 0;
	}

	void reset_change_flags() {
		for (auto &knob : knobs)
			knob.changed = false;
	}

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

	friend void copy(ParamsState &dst, ParamsState const &src) {
		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins))
			gate_in = that_gate_in;

		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs)) {
			knob = that_knob;
		}

		dst.jack_senses = src.jack_senses;
	}
};

struct ParamsMidiState : ParamsState {
	std::array<LatchedParam<float, 1, 127>, NumMidiCCs> midi_ccs;

	LightWatcher lights;

	void clear() {
		ParamsState::clear();

		lights.stop_watching_all();

		for (auto &cc : midi_ccs)
			cc = 0;
	}

	std::optional<float> panel_knob_new_value(uint16_t mapped_panel_id) const {

		auto mk = MappedKnob{.panel_knob_id = mapped_panel_id};

		if (mk.is_panel_knob()) {
			auto latched = knobs[mapped_panel_id];
			return latched.did_change() ? std::optional<float>{latched.val} : std::nullopt;
		}

		else if (mk.is_midi_cc())
		{
			auto latched = midi_ccs[mk.cc_num()];
			return latched.did_change() ? std::optional<float>{latched.val} : std::nullopt;
		}

		else
			return std::nullopt;
	}
};

} // namespace MetaModule
