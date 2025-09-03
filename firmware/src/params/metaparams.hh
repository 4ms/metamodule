#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
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

// A catch-all of data shared between cores
// TODO: separate out into data that follows the same paths
struct MetaParams {

	// Controls -> GUI (via audio -> SyncParams)
	// TODO: could controls pass directly to GUI via SPSC queue?
	Toggler rotary_button;
	RotaryMotion rotary{};
	RotaryMotion rotary_pushed{};
	std::array<Toggler, PanelDef::NumMetaRgbButton> meta_buttons{};

	// Audio -> GUI
	uint8_t audio_load = 0;
	int8_t audio_overruns = 0;

	// Controls -> Audio
	bool midi_connected = false;

	uint8_t num_button_exp_connected = 0;
	uint32_t ext_buttons_high_events{};
	uint32_t ext_buttons_low_events{};

	// Controls -> Audio, Audio -> GUI (via ParamsState in SyncParams)
	uint32_t jack_senses{};

	// Audio -> Controls
	uint32_t midi_poly_chans = 1;
	uint32_t sample_rate = 48000;

	// GUI -> GUI
	// TODO: move this to a PageManager object like gui_state
	RotaryMotion rotary_with_metabutton{};
	bool ignore_metabutton_release = false;

	MetaParams() {
		clear();
	}

	void clear() {
		for (auto &but : meta_buttons)
			but.reset();
		rotary_button.reset();
		rotary.motion = 0;
		rotary.abs_pos = 0;
		rotary_pushed.motion = 0;
		rotary_pushed.abs_pos = 0;
		audio_load = 0;
		audio_overruns = 0;
		jack_senses = 0;
		ext_buttons_high_events = 0;
		ext_buttons_low_events = 0;
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);

		rotary_button.transfer_events(that.rotary_button);
		rotary.add_motion(that.rotary);
		rotary_pushed.add_motion(that.rotary_pushed);
		audio_load = that.audio_load;

		// Check this:
		ext_buttons_low_events = that.ext_buttons_low_events;
		ext_buttons_high_events = that.ext_buttons_high_events;
		that.ext_buttons_low_events = 0;
		that.ext_buttons_high_events = 0;

		audio_overruns = std::max(that.audio_overruns, audio_overruns);

		midi_connected = that.midi_connected;

		midi_poly_chans = that.midi_poly_chans;

		jack_senses = that.jack_senses;
	}

	// For buttons: moves events from `that` to `this`, removing them from `this`
	// Moves rotary motion events from `that` to `this` (removing them from `that`, and adding them to existing events
	// in `this`
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		for (auto [but, thatbut] : zip(meta_buttons, that.meta_buttons))
			but.transfer_events(thatbut);

		rotary_button.transfer_events(that.rotary_button);
		rotary.transfer_motion(that.rotary);
		rotary_pushed.transfer_motion(that.rotary_pushed);
		audio_load = that.audio_load;

		// Check this:
		ext_buttons_low_events |= that.ext_buttons_low_events;
		ext_buttons_high_events |= that.ext_buttons_high_events;
		that.ext_buttons_low_events = 0;
		that.ext_buttons_high_events = 0;

		// transfer
		if (that.audio_overruns > 0) {
			audio_overruns = that.audio_overruns;
			that.audio_overruns = 0;
		} else if (audio_overruns > 0)
			audio_overruns--;

		midi_connected = that.midi_connected;

		midi_poly_chans = that.midi_poly_chans;

		jack_senses = that.jack_senses;
	}
};

} // namespace MetaModule
