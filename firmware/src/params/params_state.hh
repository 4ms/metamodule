#pragma once
#include "conf/panel_conf.hh"
#include "patch/midi_def.hh"
#include "util/debouncer_compact.hh"
#include "util/filter.hh"
#include "util/parameter.hh"
#include "util/rotary_motion.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>

namespace MetaModule
{

// These are all the UI events that the GUI might need to know about.
// Some of these fields come from the Params struct (sample-rate).
// Other fields come from the MetaParams struct (block-rate).
// The AudioStream populates this and the UI class reads this.
// The SyncParams class is used to keep the write/reads in sync
// without losing events

struct ParamsState {
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumPot> knobs{};
	std::array<LatchedParam<float, 25, 40960>, PanelDef::NumCVIn> cvs{};
	std::array<TogglerCompact, PanelDef::NumGateIn> gate_ins{};
	std::array<TogglerCompact, PanelDef::NumButtons> buttons{};
	std::array<ResizingOversampler, PanelDef::NumAudioIn> smoothed_ins{};

	std::array<RotaryMotion, 2> encoder{};

	struct MidiChangedVal {
		uint8_t changed : 1;
		uint8_t val : 7;
	};
	std::array<MidiChangedVal, NumMidiCCs> midi_ccs{};

	bool usb_midi_connected = false;
	uint32_t audio_load = 0;

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

		for (auto &cc : midi_ccs)
			cc.changed = 0;
	}

	void reset_change_flags() {
		for (auto &knob : knobs)
			knob.changed = false;

		for (auto &cv : cvs)
			cv.changed = false;
	}

	friend void accumulate_events(ParamsState &dst, ParamsState const &src) {
		for (auto [knob, that_knob] : zip(dst.knobs, src.knobs))
			knob = that_knob;

		for (auto [cv, that_cv] : zip(dst.cvs, src.cvs))
			cv = that_cv;

		for (auto [gate_in, that_gate_in] : zip(dst.gate_ins, src.gate_ins)) {
			// Accumulate events
			gate_in.register_state(that_gate_in.is_high());
		}

		for (auto [but, that_but] : zip(dst.buttons, src.buttons)) {
			// Accumulate events
			but.register_state(that_but.is_high());
		}

		for (auto [in, that_in] : zip(dst.smoothed_ins, src.smoothed_ins))
			in = that_in;

		for (auto [this_enc, that_enc] : zip(dst.encoder, src.encoder)) {
			// Accumulate events
			this_enc.add_motion(that_enc);
		}

		dst.usb_midi_connected = src.usb_midi_connected;
		dst.audio_load = src.audio_load;
	}

	friend void transfer_events(ParamsState &dst, ParamsState &src) {
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

		// Move rotary motion events from internal copy to the dst (GUI's copy)
		for (auto [enc, that_enc] : zip(dst.encoder, src.encoder)) {
			enc.transfer_motion(that_enc);
		}

		dst.usb_midi_connected = src.usb_midi_connected;
	}
};

} // namespace MetaModule
