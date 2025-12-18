#pragma once
#include "conf/panel_conf.hh"
#include "util/debouncer_compact.hh"
#include "util/filter.hh"
#include "util/parameter.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>

namespace MetaModule
{

// TODO: put all fields that the GUI needs to see here.
// Some of these fields come from the Params struct (sample-rate). It's most efficient to populate these by the audio stream.
// Other fields come from the MetaParams struct (block-rate). These can be populated when copied

struct ParamsState {
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> knobs{};
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> cvs{};
	std::array<TogglerCompact, PanelDef::NumGateIn> gate_ins{};
	std::array<TogglerCompact, PanelDef::NumButtons> buttons{};
	std::array<ResizingOversampler, PanelDef::NumAudioIn + AudioExpander::NumInJacks> smoothed_ins;

	void clear() {
		for (auto &knob : knobs)
			knob = {0.f, false};

		for (auto &cv : cvs)
			cv = {0.f, false};

		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &b : buttons)
			b.reset();

		for (auto &in : smoothed_ins)
			in.reset();
	}

	void reset_change_flags() {
		for (auto &knob : knobs)
			knob.changed = false;

		for (auto &cv : cvs)
			cv.changed = false;
	}

	friend void copy(ParamsState &dst, ParamsState const &src) {
		// TODO: memcpy?

		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs))
			knob = that_knob;

		for (auto [cv, that_cv] : zip(dst.cvs, src.cvs))
			cv = that_cv;

		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins))
			gate_in = that_gate_in;

		for (auto [b, that_b] : zip(dst.buttons, src.buttons))
			b = that_b;

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;
	}

	friend void transfer_events(ParamsState &dst, ParamsState const &src) {
		// Copy the state (pressed or not), set new events, and preserve any uncleared events
		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins)) {
			gate_in.register_state(that_gate_in.is_high());
		}

		// Copy the state (pressed or not), set new events, and preserve any uncleared events
		for (auto [b, that_b] : zip(dst.buttons, src.buttons)) {
			b.register_state(that_b.is_high());
		}

		// Copy the pot value, and preserve the changed flag
		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs)) {
			knob.val = that_knob.val;
			// only reader can clear knob change events, writer can set them
			knob.changed = that_knob.changed | knob.changed;
		}
		for (auto [cv, that_cv] : zip(dst.cvs, src.cvs)) {
			cv.val = that_cv.val;
			cv.changed = that_cv.changed | cv.changed;
		}

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;
	}
};

} // namespace MetaModule
