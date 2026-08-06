#pragma once
#include "button_expander.hh"
#include "conf/i2c_aux_expander_conf.hh"
#include "expander_bus.hh"
#include "midi_expander.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx_hal.h"
#include <cstdint>
#include <span>
#include <utility>

namespace MetaModule
{

// Owns the aux I2C bus and shares it between the expanders
//
// Polls: MIDI -> Button -> Pause (10ms) -> MIDI ...etc
// Each expander do as many xfers as they want before being done

// TODO:
// TX/RX <=> M4 Controls <=> A7.
//    Make sure Controls deals with entire RX buffer immediately
// Pass MIDI events back to A7 along side
// Use usb cable num for Device mode: 0 = USB, 1 = TRS, 2 = DIN5
// Periodically re-scan for button expanders, like the MIDI expander does
class ControlExpanderManager {
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	ControlExpanderManager() {
		auxi2c.enable_IT(Expander::i2c_conf.priority1, Expander::i2c_conf.priority2);
		buttons.scan();
		midi.scan();
	}

	void update() {
		switch (state) {
			using enum States;

			case DoMidi:
				if (!bus_ready())
					return;
				take_turn(midi, midi_result, XferOwner::Midi, DoButtons);
				break;

			case DoButtons:
				if (!bus_ready())
					return;
				take_turn(buttons, button_result, XferOwner::Buttons, Pause);
				break;

			case Pause:
				if ((HAL_GetTick() - tmr) < pause_ms)
					return;

				pause_ms = NormalPauseMs;
				state = DoMidi;
				break;
		}
	}

	//
	// Button Expanders
	//

	uint32_t get_buttons() const {
		return buttons.get_buttons();
	}

	uint32_t button_expanders_connected() const {
		return buttons.connected_bitfield();
	}

	//
	// MIDI Expander
	//

	bool midi_expander_connected() const {
		return midi.connected();
	}

	bool send_midi(std::span<const uint8_t> bytes, unsigned jack) {
		return midi.send(bytes, jack);
	}

	std::span<const uint8_t> get_midi_trs_rx() const {
		return midi.trs_rx();
	}

	std::span<const uint8_t> get_midi_din_rx() const {
		return midi.din_rx();
	}

private:
	I2CPeriph auxi2c{Expander::i2c_conf};
	ButtonExpanderManager buttons{auxi2c};
	MidiExpanderManager midi{auxi2c};

	enum class States {
		Pause,
		DoMidi,
		DoButtons,
	} state = States::DoButtons;

	static constexpr uint32_t NormalPauseMs = 10;
	static constexpr uint32_t ErrorPauseMs = 500;
	uint32_t tmr = 0;
	uint32_t pause_ms = NormalPauseMs;

	// The longest legitimate transfer is ~11ms (510 bytes of MIDI)
	static constexpr uint32_t BusStuckTimeoutMs = 100;
	uint32_t bus_stuck_tm = 0;

	enum class XferOwner { None, Midi, Buttons } xfer_owner = XferOwner::None;
	XferResult midi_result = XferResult::None;
	XferResult button_result = XferResult::None;

	template<typename Expander>
	void take_turn(Expander &expander, XferResult &result, XferOwner owner, States next) {
		const auto req = expander.update(std::exchange(result, XferResult::None));

		if (req.started_xfer)
			xfer_owner = owner;

		if (req.reset_bus) {
			reset_bus();
			return;
		}

		if (req.turn_done) {
			state = next;

			if (next == States::Pause)
				tmr = HAL_GetTick();
		}
	}

	// Pass the i2c result to the expander that owns of the xfer
	void collect_xfer_result() {
		if (xfer_owner == XferOwner::None)
			return;

		const auto result = auxi2c.had_error() ? XferResult::Failed : XferResult::Ok;
		auxi2c.clear_error();

		if (xfer_owner == XferOwner::Midi)
			midi_result = result;
		else
			button_result = result;

		xfer_owner = XferOwner::None;
	}

	// Check if bus is free, and set a timeout to reset it if it's busy for too long
	bool bus_ready() {
		if (auxi2c.is_ready()) {
			bus_stuck_tm = 0;
			collect_xfer_result();
			return true;
		}

		const auto now = HAL_GetTick();

		if (bus_stuck_tm == 0) {
			bus_stuck_tm = (now > 0) ? now : 1; // don't let bus_stuck_tm be 0

		} else if ((now - bus_stuck_tm) >= BusStuckTimeoutMs) {
			pr_err("ControlExpander: aux I2C stuck, resetting bus\n");
			reset_bus();
		}

		return false;
	}

	void reset_bus() {
		auxi2c.reset(Expander::i2c_conf);

		bus_stuck_tm = 0;
		xfer_owner = XferOwner::None;
		midi_result = XferResult::None;
		button_result = XferResult::None;

		buttons.on_bus_reset();
		midi.on_bus_reset();

		pause_ms = ErrorPauseMs;
		tmr = HAL_GetTick();
		state = States::Pause;
	}
};

} // namespace MetaModule
