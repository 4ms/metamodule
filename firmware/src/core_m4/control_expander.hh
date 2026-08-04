#pragma once
#include "CoreModules/hub/button_expander_defs.hh"
#include "conf/button_expander_conf.hh"
#include "conf/i2c_aux_expander_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "conf/midi_expander_conf.hh"
#include "drivers/gpio_expander.hh"
#include "midi_expander_driver.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx_hal.h"
#include "usbh_conf.h"
#include <atomic>

namespace MetaModule
{

// Manage all expander modules connected via I2C to the ControlExpander header

// TODO:
// TX/RX <=> M4 Controls <=> A7.
//    Make sure to handle overflow gracefully:
//    - Tell Controls when we have tx space free, it has to wait until then.
//    - Make sure Controls deals with entire RX buffer immediately
// Check I2C bus speed (> 400kHz?)
// Use usb cable num for TX: 0 = USB, 1 = TRS, 2 = DIN5
class ControlExpanderManager {
	using GPIOExpander = mdrivlib::GPIOExpander;
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	ControlExpanderManager() {
		auxi2c.enable_IT(Expander::i2c_conf.priority1, Expander::i2c_conf.priority2);
		scan_for_button_expanders();
		scan_for_midi_expander();
		//TODO scan_for_pot_expanders()
	}

	void scan_for_midi_expander() {
		midi_exp.found = false;
		midi_exp.driver.set_address(Expander::Midi::addr);

		if (midi_exp.driver.is_present()) {
			midi_exp.found = true;
			midi_exp.driver.start();
			num_midi_errors = 0;
			num_midi_error_retries = 0;
			pr_info("MIDI Expander found at addr 0x%x\n", Expander::Midi::addr);
		} else {
			pr_dbg("MIDI Expander not found at addr 0x%x\n", Expander::Midi::addr);
		}
	}

	void scan_for_button_expanders() {
		using namespace Expander;
		constexpr std::array<int, Expander::Button::MaxExpanders> addresses{
			Button::gpio_chip_conf.addr + 6, // Jumper pos 1: ~0b001
			Button::gpio_chip_conf.addr + 5, // Jumper pos 2: ~0b010
			Button::gpio_chip_conf.addr + 3, // Jumper pos 3: ~0b100
			Button::gpio_chip_conf.addr + 7, // No jumpers  : ~0b000

			// Invalid positions:
			// ButtonExpander::gpio_chip_conf.addr + 4, // (jumpers pos 1+2)
			// ButtonExpander::gpio_chip_conf.addr + 2, // (jumpers pos 1+3)
			// ButtonExpander::gpio_chip_conf.addr + 1, // (jumpers pos 2+3)
			// ButtonExpander::gpio_chip_conf.addr + 0, // (all jumpers)
		};

		auto num_expanders_found = 0u;

		for (unsigned i = 0; auto &buttonexp : found_button_exps) {
			auto addr = addresses[i++];

			buttonexp.found = false;
			buttonexp.driver.set_address(addr);

			if (buttonexp.driver.is_present()) {
				buttonexp.found = true;
				buttonexp.driver.start();
				pr_info("Button Expander found at addr 0x%x\n", addr);
				num_expanders_found++;
				if (num_expanders_found >= Expander::Button::MaxExpanders)
					break;

			} else {
				pr_dbg("Button Expander not found at addr 0x%x\n", addr);
			}
		}
	}

	void update_buttons() {
		if (found_button_exps.size() == 0)
			// TODO: periodically scan?
			return;

		switch (button_ex_state) {
			using enum ButtonExStates;
			case ReadButtons: {
				if (prev_button_xfer_failed())
					break;

				// Last xfer had no error
				if (cur_reading_exp > 0)
					num_errors[cur_reading_exp - 1] = 0;

				if (cur_reading_exp >= found_button_exps.size()) {
					cur_reading_exp = 0;
					button_ex_state = ButtonExStates::CollectReadings;

				} else {
					if (found_button_exps[cur_reading_exp].found) {
						auto err = found_button_exps[cur_reading_exp].driver.read_inputs();
						if (err != GPIOExpander::Error::None) {
							handle_gpio_error();
							break;
						}
						xfer_owner = XferOwner::Buttons;
					}

					cur_reading_exp++;
				}
				break;
			}

			case CollectReadings: {
				uint32_t readings = 0;
				for (auto i = 0u; auto &exp : found_button_exps) {
					if (exp.found) {
						auto this_reading = Expander::Button::order_buttons(exp.driver.collect_last_reading());
						// Firt expander will be in the LSByte
						readings |= this_reading << (i * 8);
					}
					i++;
				}

				latest_reading.store(readings);

				button_ex_state = ReadButtons;
				state = States::Pause;
				tmr = HAL_GetTick();
				break;
			}
		}
	}

	void update_midi() {
		if (!midi_exp.found) {
			// TODO: periodically re-scan, so the expander can be hot-plugged
			state = States::DoButtons;
			return;
		}

		switch (midi_ex_state) {
			using enum MidiExStates;
			case ReadSize: {
				// Checks the write issued at the end of the previous cycle
				if (prev_midi_xfer_failed())
					break;

				const auto t = midi_exp.driver.read_sizes();
				if (t != MIDIExpander::None) {
					handle_midi_error();
					break;
				}
				xfer_owner = XferOwner::Midi;
				midi_ex_state = ReadPayload;
				break;
			}
			case ReadPayload: {
				if (prev_midi_xfer_failed())
					break;

				const auto t = midi_exp.driver.read_payload();
				if (t != MIDIExpander::None) {
					handle_midi_error();
					break;
				}
				xfer_owner = XferOwner::Midi;
				midi_ex_state = CollectPayload;
				break;
			}
			case CollectPayload: {
				if (prev_midi_xfer_failed())
					break;

				const auto streams = midi_exp.driver.collect_payload();
				// TODO: WHAT TO DO WITH THE MIDI?
				midi_ex_state = Write;
				break;
			}
			case Write:
				// const auto t = found_midi_exp.driver.write_payload(int s0, int s1)
				// if (t != MIDIExpander::None) {
				// 	handle_midi_error();
				// 	break;
				// }
				midi_ex_state = ReadSize;
				state = States::DoButtons;
				break;
		}
	}

	void update() {
		switch (state) {
			using enum States;
			case DoMidi:
				if (!bus_ready()) {
					return;
				}
				update_midi();
				break;
			case DoButtons:
				if (!bus_ready()) {
					return;
				}
				update_buttons();
				break;
			case Pause:
				const auto now = HAL_GetTick();

				if ((now - tmr) < pause_ms) {
					return;
				}

				pause_ms = NormalPauseMs;
				state = DoMidi;
				break;
		}
	}

	uint32_t get_buttons() {
		return latest_reading.load();
	}

	uint32_t num_button_expanders_connected() {
		return std::ranges::count_if(found_button_exps, [](const FoundButtonExpander &exp) { return exp.found; });
	}

	uint32_t button_expanders_connected() {
		uint32_t bitfield = 0u;

		for (auto i = 0u; auto &exp : found_button_exps) {
			if (exp.found)
				bitfield |= 1 << i;
			i++;
		}

		return bitfield;
	}

private:
	I2CPeriph auxi2c{Expander::i2c_conf};

	struct FoundButtonExpander {
		bool found = false;
		GPIOExpander driver;
	};

	struct FoundMidiExpander {
		bool found = false;
		MIDIExpander driver;
	};

	std::array<FoundButtonExpander, Expander::Button::MaxExpanders> found_button_exps{{
		{false, {auxi2c, Expander::Button::gpio_chip_conf}},
		{false, {auxi2c, Expander::Button::gpio_chip_conf}},
		{false, {auxi2c, Expander::Button::gpio_chip_conf}},
		{false, {auxi2c, Expander::Button::gpio_chip_conf}},
	}};

	FoundMidiExpander midi_exp{false, {auxi2c, Expander::Midi::midi_chip_conf}};

	uint32_t cur_reading_exp = 0;

	uint32_t tmr = 0;

	// Normal idle time between polling cycles
	static constexpr uint32_t NormalPauseMs = 10;

	// Delay after bus has been reset so we don't hammer a misbehaving expander
	static constexpr uint32_t ErrorPauseMs = 100;

	uint32_t pause_ms = NormalPauseMs;

	// The longest legitimate transfer is ~11ms (510 bytes of MIDI), so anything
	// past this means the transfer is never going to complete
	static constexpr uint32_t BusStuckTimeoutMs = 100;

	uint32_t bus_stuck_tm = 0;

	// Who started the transfer that's currently in flight, and the outcome of the
	// last one each state machine started
	enum class XferOwner { None, Midi, Buttons } xfer_owner = XferOwner::None;
	bool midi_xfer_error = false;
	bool button_xfer_error = false;

	std::atomic<uint32_t> latest_reading;

	enum class ButtonExStates {
		ReadButtons,
		CollectReadings,
	} button_ex_state = ButtonExStates::ReadButtons;

	enum class MidiExStates {
		ReadSize,
		ReadPayload,
		CollectPayload,
		Write,
	} midi_ex_state = MidiExStates::ReadSize;

	enum class States {
		Pause,
		DoMidi,
		DoButtons,
	} state = States::DoButtons;

	std::array<uint32_t, Expander::Button::MaxExpanders> num_errors{};
	std::array<uint32_t, Expander::Button::MaxExpanders> num_error_retries{};
	uint32_t num_midi_errors{};
	uint32_t num_midi_error_retries{};

	//
	// Error handling
	//

	void collect_xfer_error() {
		if (xfer_owner == XferOwner::None)
			return;

		const bool failed = auxi2c.had_error();
		auxi2c.clear_error();

		if (xfer_owner == XferOwner::Midi)
			midi_xfer_error = failed;
		else
			button_xfer_error = failed;

		xfer_owner = XferOwner::None;
	}

	bool prev_midi_xfer_failed() {
		if (!midi_xfer_error) {
			num_midi_errors = 0;
			return false;
		}

		midi_xfer_error = false;
		midi_exp.driver.discard_payload();
		// Go back to ReadSize, since ReadPayload would be unsafe
		// if ReadSize failed
		midi_ex_state = MidiExStates::ReadSize;
		handle_midi_error();
		return true;
	}

	bool prev_button_xfer_failed() {
		if (!button_xfer_error)
			return false;

		button_xfer_error = false;
		// cur_reading_exp has already moved past the expander that was read
		if (cur_reading_exp > 0)
			cur_reading_exp--;
		handle_gpio_error();
		return true;
	}

	bool bus_ready() {
		if (auxi2c.is_ready()) {
			bus_stuck_tm = 0;
			collect_xfer_error();
			return true;
		}

		// Timeout for a stuck bus
		if (bus_stuck_tm == 0) {
			bus_stuck_tm = HAL_GetTick() == 0 ? 1 : HAL_GetTick();

		} else if ((HAL_GetTick() - bus_stuck_tm) >= BusStuckTimeoutMs) {
			pr_err("ControlExpander: aux I2C stuck, resetting bus\n");
			reset_bus();
		}

		return false;
	}

	void reset_bus() {
		auxi2c.reset(Expander::i2c_conf);

		bus_stuck_tm = 0;
		xfer_owner = XferOwner::None;
		midi_xfer_error = false;
		button_xfer_error = false;
		cur_reading_exp = 0;
		button_ex_state = ButtonExStates::ReadButtons;
		midi_ex_state = MidiExStates::ReadSize;
		midi_exp.driver.discard_payload();

		pause_ms = ErrorPauseMs;
		tmr = HAL_GetTick();
		state = States::Pause;
	}

	void handle_midi_error() {
		num_midi_errors++;
		pr_dbg("ControlExpander: MIDI expander I2C error (%u)\n", num_midi_errors);

		if (num_midi_errors <= 8)
			return;

		// Start counting afresh, so the next reset takes another 8 errors
		num_midi_errors = 0;
		num_midi_error_retries++;

		if (num_midi_error_retries > 10) {
			pr_err("ControlExpander: too many errors on midi exp, disabling\n");
			midi_exp.found = false;
		}

		reset_bus();
	}

	void handle_gpio_error() {
		num_errors[cur_reading_exp]++;
		pr_dbg("ControlExpander %u I2C Error!\n", cur_reading_exp);

		if (num_errors[cur_reading_exp] <= 8)
			return;

		num_errors[cur_reading_exp] = 0;
		num_error_retries[cur_reading_exp]++;

		if (num_error_retries[cur_reading_exp] > 10) {
			pr_err("ControlExpander: too many errors on button exp %u, disabling\n", cur_reading_exp);
			found_button_exps[cur_reading_exp].found = false;
		}

		reset_bus();
	}
};

} // namespace MetaModule
