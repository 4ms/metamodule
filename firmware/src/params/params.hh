#pragma once
#include "conf/panel_conf.hh"
#include "patch/midi_def.hh"
#include "util/debouncer.hh"
#include <array>

namespace MetaModule
{
struct Params {
	std::array<float, PanelDef::NumCVIn> cvjacks{};
	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};
	std::array<Toggler, PanelDef::NumRgbButton> buttons{};
	std::array<float, PanelDef::NumPot> knobs{};

	struct Midi {
		struct Note {
			float pitch = 0;
			float gate = 0;
			float vel = 0;
		};
		std::array<Note, MidiPolyphony> notes{};

		struct GateEvent {
			uint8_t notenum = 0;
			uint8_t gateamp = 0;
			enum { None = 0xFF };
		};
		std::array<GateEvent, MidiMaxSimulGates> gate_events;
	};
	Midi midi;

	uint32_t jack_senses;

	Params() {
		clear();
	}

	void clear() {
		for (float &cvjack : cvjacks)
			cvjack = 0.f;
		for (auto &gate_in : gate_ins)
			gate_in.reset();
		for (auto &button : buttons)
			button.reset();
		for (float &knob : knobs)
			knob = 0.f;
		for (auto &note : midi.notes)
			note = Midi::Note{};
		for (auto &note : midi.gate_events)
			note = Midi::GateEvent{};

		jack_senses = 0;
	}

	void copy(const Params &that) {
		for (unsigned i = 0; i < PanelDef::NumCVIn; i++)
			cvjacks[i] = that.cvjacks[i];
		for (unsigned i = 0; i < PanelDef::NumGateIn; i++)
			gate_ins[i].copy_state(that.gate_ins[i]);
		for (unsigned i = 0; i < PanelDef::NumRgbButton; i++)
			buttons[i].copy_state(that.buttons[i]);
		for (unsigned i = 0; i < PanelDef::NumPot; i++)
			knobs[i] = that.knobs[i];
		jack_senses = that.jack_senses;
	}
};

} // namespace MetaModule
