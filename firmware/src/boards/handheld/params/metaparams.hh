#pragma once
#include "conf/panel_conf.hh"
#include "util/debouncer.hh"
#include "util/rotary_motion.hh"
#include "util/zip.hh"
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct BatteryStatus {
	uint16_t level{};
	uint16_t maLoad{};
	bool is_charging{};
};

// A catch-all of data shared between cores
// TODO: separate out into data that follows the same paths
struct MetaParams {
	BatteryStatus battery_status{};

	bool usb_midi_connected = false;

	std::array<Toggler, PanelDef::NumEncoderButtons + PanelDef::NumButtons> buttons{};
	std::array<RotaryMotion, PanelDef::NumEncoders> encoders{};

	uint32_t sample_rate = 48000;
	uint32_t audio_load = 0;

	void clear() {
		*this = MetaParams{};
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		for (auto [this_enc, that_enc] : zip(this->encoders, that.encoders)) {
			this_enc.add_motion(that_enc);
		}

		battery_status = that.battery_status;
		usb_midi_connected = that.usb_midi_connected;
		for (auto [this_but, that_but] : zip(this->buttons, that.buttons)) {
			this_but.transfer_events(that_but);
		}
	}

	// Moves rotary motion events from `that` to `this` (removing them from `that`,
	// and adding them to existing events in `this`)
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		for (auto [this_enc, that_enc] : zip(this->encoders, that.encoders)) {
			this_enc.transfer_motion(that_enc);
		}

		battery_status = that.battery_status;
		usb_midi_connected = that.usb_midi_connected;
		for (auto [this_but, that_but] : zip(this->buttons, that.buttons)) {
			this_but.transfer_events(that_but);
		}
	}
};

} // namespace MetaModule
