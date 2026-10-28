#pragma once
#include "conf/control_expander_conf.hh"
#include "conf/i2c_conf.hh"
#include "drivers/i2c.hh"
#include "drivers/rotary.hh"
#include "util/debouncer.hh"
#include <array>
#include <atomic>

namespace MetaModule
{

// The knob encoders and buttons on the four TCA9555 control expanders (conf/control_expander_conf.hh),
// two on each of I2C2 and I2C3.
//
// update() runs from the frame interrupt (PanelControls::update()). Every TickFrames frames it
// starts an interrupt-driven read of the next expander on each bus, and decodes the read it started
// last time. So each expander is read at about 1kHz, and the main loop being busy (e.g. a patch
// scan) doesn't drop encoder steps.
//
// The buttons and encoder pushes are active low (the TCA9555's internal pull-ups), and debounced.
// A bus that keeps failing, or a read that never finishes, stops that bus until process() (main loop)
// resets it.
class ExpanderControls {
public:
	static constexpr unsigned NumExpanders = Controls::Expanders.size();
	static constexpr unsigned NumEncoders = Controls::Encoders.size();
	static constexpr unsigned NumButtons = Controls::Buttons.size();

	// Main context: initializes the buses and checks that each expander answers
	void start();

	// Frame interrupt
	void update();

	// Main loop: resets a bus that stopped
	void process();

	// Detents turned since start()
	int32_t encoder_position(unsigned enc) const {
		return enc_positions[enc];
	}

	// In Controls::Encoders order
	Toggler &encoder_button(unsigned enc) {
		return enc_buttons[enc];
	}

	// In Controls::Button order
	Toggler &button(unsigned but) {
		return buttons[but];
	}

	// Last raw reading (bit set = pin high)
	uint16_t reading(unsigned exp) const {
		return readings[exp];
	}

private:
	// 48 frames per ms at 48kHz: two reads per ms on each bus, alternating between its expanders
	static constexpr uint32_t TickFrames = 24;
	// Ticks a read can take before we give up on it (typical is less than one)
	static constexpr uint32_t TimeoutTicks = 20;
	// Failed reads in a row on a bus before it's reset
	static constexpr uint32_t ErrorsBeforeReset = 16;

	struct Bus {
		Bus(const mdrivlib::I2CConfig &conf, std::array<uint8_t, 2> exps)
			: conf{conf}
			, i2c{conf}
			, exps{exps} {
		}

		const mdrivlib::I2CConfig &conf;
		mdrivlib::I2CPeriph i2c;
		std::array<uint8_t, 2> exps; // indices into Controls::Expanders
		unsigned cur = 0;			 // index into exps
		bool in_flight = false;
		uint32_t ticks_in_flight = 0;
		uint32_t errors_in_a_row = 0;
		std::array<uint8_t, 2> rx{};
		// Set by update() when the bus needs a reset, cleared by process() when it's done
		std::atomic<bool> stopped = false;
	};

	void step(Bus &bus);
	void stop(Bus &bus);
	void decode(unsigned exp, uint16_t reading);

	static_assert(Controls::Expanders[0].bus == Controls::ExpanderConf::Bus::ControlsA &&
				  Controls::Expanders[1].bus == Controls::ExpanderConf::Bus::ControlsA &&
				  Controls::Expanders[2].bus == Controls::ExpanderConf::Bus::ControlsB &&
				  Controls::Expanders[3].bus == Controls::ExpanderConf::Bus::ControlsB);

	std::array<Bus, 2> buses{{
		{controls_a_i2c_conf, {0, 1}},
		{controls_b_i2c_conf, {2, 3}},
	}};

	uint32_t frame_ctr = 0;
	bool started = false;

	std::array<volatile uint16_t, NumExpanders> readings{};

	std::array<mdrivlib::RotaryEncDetails::RotaryFSM<mdrivlib::RotaryFullStep>, NumEncoders> encoders{};
	std::array<volatile int32_t, NumEncoders> enc_positions{};
	std::array<Debouncer<>, NumEncoders> enc_buttons{};
	std::array<Debouncer<>, NumButtons> buttons{};
};

} // namespace MetaModule
