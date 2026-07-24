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
// (For now, there is only the ButtonExpander)

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
		static constexpr auto addr = 0x30;
	}

	void scan_for_button_expanders() {
		using namespace Expander;
		constexpr std::array<int, Expander::Button::MaxExpanders> addresses{
			Button::gpio_chip_conf.addr + 6, // Jumper pos 1
			Button::gpio_chip_conf.addr + 5, // Jumper pos 2
			Button::gpio_chip_conf.addr + 3, // Jumper pos 3
			Button::gpio_chip_conf.addr + 7, // No jumpers

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
				if (cur_reading_exp >= found_button_exps.size()) {
					cur_reading_exp = 0;
					button_ex_state = ButtonExStates::CollectReadings;

				} else {
					if (found_button_exps[cur_reading_exp].found) {
						auto err = found_button_exps[cur_reading_exp].driver.read_inputs();
						if (err != GPIOExpander::Error::None)
							handle_gpio_error();
						else
							num_errors[cur_reading_exp] = 0;
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
				break;
			}
		}
	}

	void update_midi() {
		switch (midi_ex_state) {
			using enum MidiExStates;
			case ReadSize: {
				const auto t = found_midi_exp.driver.read_sizes();
				if (t != MIDIExpander::None) {
					handle_midi_error();
					break;
				}
				midi_ex_state = ReadPayload;
				break;
			}
			case ReadPayload: {
				const auto t = found_midi_exp.driver.read_sizes();
				if (t != MIDIExpander::None) {
					handle_midi_error();
					break;
				}
				midi_ex_state = CollectPayload;
				break;
			}
			case CollectPayload: {
				const auto streams = found_midi_exp.driver.collect_payload();
				// TODO: WHAT TO DO WITH THE MIDI?
				midi_ex_state = Write;
				break;
			}
			case Write:
				midi_ex_state = ReadSize;
				state = States::DoButtons;
				break;
		}
	}

	void update() {
		switch (state) {
			using enum States;
			case DoMidi:
				if (!auxi2c.is_ready()) { return; }
				update_midi();
				break;
			case DoButtons:
				if (!auxi2c.is_ready()) { return; }
				update_buttons();
				break;
			case Pause:
				const auto now = HAL_GetTick();

				if ((now - tmr) < 10) { return; }

				tmr = now;

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

	FoundMidiExpander found_midi_exp{false, {auxi2c, Expander::Midi::midi_chip_conf}};

	uint32_t cur_reading_exp = 0;

	uint32_t tmr = 0;

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

	void handle_midi_error() {
		num_midi_errors++;
		pr_dbg("ControlExpander I2C Error!\n");

		if (num_midi_errors > 8) {
			num_midi_error_retries++;

			if (num_midi_error_retries > 10) {
				pr_dbg("ControlExpander: too many errors on midi exp, disabling\n");
				found_midi_exp.found = false;
			}
			auxi2c.init(Expander::i2c_conf);
			tmr = std::max<uint32_t>(HAL_GetTick(), 500u) - 500;
			state = States::Pause;
			button_ex_state = ButtonExStates::ReadButtons;
			midi_ex_state = MidiExStates::ReadSize;
		}
	}

	void handle_gpio_error() {
		num_errors[cur_reading_exp]++;
		pr_dbg("ControlExpander %u I2C Error!\n", cur_reading_exp);

		if (num_errors[cur_reading_exp] > 8) {
			num_error_retries[cur_reading_exp]++;

			if (num_error_retries[cur_reading_exp] > 10) {
				pr_dbg("ControlExpander: too many errors on button exp %u, disabling\n", cur_reading_exp);
				found_button_exps[cur_reading_exp].found = false;
				cur_reading_exp = 0;
			}
			auxi2c.init(Expander::i2c_conf);
			tmr = std::max<uint32_t>(HAL_GetTick(), 500u) - 500;
			state = States::Pause;
			button_ex_state = ButtonExStates::ReadButtons;
			midi_ex_state = MidiExStates::ReadSize;
		}
	}
};

} // namespace MetaModule
