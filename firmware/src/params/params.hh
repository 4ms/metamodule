#pragma once
#include "conf/panel_conf.hh"
#include "patch/midi_def.hh"
#include "util/debouncer.hh"
#include "util/zip.hh"
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
			uint8_t note = 0;
			float gate = 0;
		};

		struct Event {
			enum class Type : uint8_t {
				None,
				NoteOn,
				NoteOff,
				Aft,
				ChanPress,
				Retrig,
				GateNote,
				CC,
				Bend,
				Time
			} type = Type::None;
			uint8_t midi_chan = 0; //currently not implemented
			uint8_t poly_chan = 0;
			uint8_t note = 0; // GateNote: note value; CC: ccnum; Time: event type
			float val = 0;	  //velocity or on/off
		};
		Event event;
		static constexpr auto sizeofEvent = sizeof(Event);
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

		midi.event = Midi::Event{};

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

		midi.event = that.midi.event;

		jack_senses = that.jack_senses;
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
