#pragma once
#include "conf/panel_conf.hh"
#include "conf/stream_conf.hh"
#include "util/debouncer.hh"
#include "util/filter.hh"
#include "util/rotary_motion.hh"
#include "util/zip.hh"
#include <array>
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct MetaParams {
	float patchcv = 0.f;
	Toggler rotary_button;
	RotaryMotion rotary{};
	RotaryMotion rotary_pushed{};
	std::array<Toggler, PanelDef::NumMetaRgbButton> meta_buttons{};
	std::array<float, PanelDef::NumAudioIn> ins{};

	bool midi_connected = false;
	uint32_t midi_poly_chans = 1;

	uint8_t audio_load = 0;
	RotaryMotion rotary_with_metabutton{};
	bool ignore_metabutton_release = false;

	uint32_t sample_rate = 48000;

	MetaParams() {
		clear();
	}

	void clear() {
		patchcv = 0.f;
		for (auto &but : meta_buttons)
			but.reset();
		rotary_button.reset();
		rotary.motion = 0;
		rotary.abs_pos = 0;
		rotary_pushed.motion = 0;
		rotary_pushed.abs_pos = 0;
		audio_load = 0;
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		patchcv = that.patchcv;

		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);

		rotary_button.transfer_events(that.rotary_button);
		rotary.add_motion(that.rotary);
		rotary_pushed.add_motion(that.rotary_pushed);
		audio_load = that.audio_load;

		midi_connected = that.midi_connected;

		midi_poly_chans = that.midi_poly_chans;

		for (auto [in, thatin] : zip(ins, that.ins))
			in = thatin;
	}

	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Moves rotary motion events from `that` to `this` (removing them from `that`, and adding them to existing events
	// in `this`
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		patchcv = that.patchcv;

		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);

		rotary_button.transfer_events(that.rotary_button);
		rotary.transfer_motion(that.rotary);
		rotary_pushed.transfer_motion(that.rotary_pushed);
		audio_load = that.audio_load;

		midi_connected = that.midi_connected;

		midi_poly_chans = that.midi_poly_chans;

		for (auto [in, thatin] : zip(ins, that.ins))
			in = thatin;
	}
};

} // namespace MetaModule
