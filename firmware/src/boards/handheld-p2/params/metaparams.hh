#pragma once
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct BatteryStatus {
	float level{};
	bool is_charging{};
};

// A catch-all of data shared between cores
// TODO: separate out into data that follows the same paths
struct MetaParams {
	BatteryStatus battery_status{};

	bool usb_midi_connected = false;

	uint32_t sample_rate = 48000;
	uint32_t audio_load = 0;

	void clear() {
		*this = MetaParams{};
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		// for (auto [this_enc, that_enc] : zip(this->encoder, that.encoder)) {
		// 	this_enc.add_motion(that_enc);
		// }

		usb_midi_connected = that.usb_midi_connected;
	}

	// Moves rotary motion events from `that` to `this` (removing them from `that`,
	// and adding them to existing events in `this`)
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		// for (auto [this_enc, that_enc] : zip(this->encoder, that.encoder)) {
		// 	this_enc.transfer_motion(that_enc);
		// }

		usb_midi_connected = that.usb_midi_connected;
	}
};

} // namespace MetaModule
