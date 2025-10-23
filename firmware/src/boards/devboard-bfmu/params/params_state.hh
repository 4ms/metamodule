#pragma once
#include "conf/jack_sense_conf.hh"
#include "conf/panel_conf.hh"
#include "patch/midi_def.hh"
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

// TODO: put all fields that the GUI needs to see here

struct ParamsState {
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> knobs{};
	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};

	std::array<ResizingOversampler, PanelDef::NumAudioIn + AudioExpander::NumInJacks> smoothed_ins;

	void clear() {
		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &knob : knobs)
			knob = {0.f, false};

		for (auto &in : smoothed_ins)
			in.reset();
	}

	void reset_change_flags() {
		for (auto &knob : knobs)
			knob.changed = false;
	}

	friend void copy(ParamsState &dst, ParamsState const &src) {
		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins))
			gate_in = that_gate_in;

		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs)) {
			knob = that_knob;
		}

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

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;
	}
};

} // namespace MetaModule
