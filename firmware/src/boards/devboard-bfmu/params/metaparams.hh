#pragma once
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
	std::array<RotaryMotion, 2> encoder{};

	uint16_t haptic_out{}; //Haptic PWM value

	bool usb_midi_connected = false;

	uint32_t sample_rate = 48000;
	uint32_t audio_load = 0;

	MetaParams() {
		clear();
	}

	void clear() {
		for (auto &enc : encoder) {
			enc.motion = 0;
			enc.abs_pos = 0;
		}
		haptic_out = 0;
		usb_midi_connected = false;
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		for (auto [this_enc, that_enc] : zip(this->encoder, that.encoder)) {
			this_enc.add_motion(that_enc);
		}

		haptic_out = that.haptic_out;
		usb_midi_connected = that.usb_midi_connected;
	}

	// Moves rotary motion events from `that` to `this` (removing them from `that`,
	// and adding them to existing events in `this`)
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		for (auto [this_enc, that_enc] : zip(this->encoder, that.encoder)) {
			this_enc.transfer_motion(that_enc);
		}

		haptic_out = that.haptic_out;
		usb_midi_connected = that.usb_midi_connected;
	}
};

} // namespace MetaModule
