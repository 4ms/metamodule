#pragma once
#include "conf/button_expander_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/gpio_expander.hh"
#include "pr_dbg.hh"
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
		auxi2c.enable_IT(ButtonExpander::i2c_conf.priority1, ButtonExpander::i2c_conf.priority2);
		scan_for_button_expanders();
		//TODO: scan_for_MIDI_expander(), scan_for_pot_expanders()
	}

	void scan_for_button_expanders() {
		// Scan for attached
		const auto base_addr = ButtonExpander::gpio_chip_conf.addr;
		auto addr = base_addr;

		//TODO: record all button expanders found, up to 4
		while (!expander_found) {
			if (buttonexp_gpio_chip.is_present()) {
				buttonexp_gpio_chip.start();
				pr_info("Button Expander found at addr 0x%x\n", addr);
				expander_found = true;
			} else {
				pr_trace("Button Expander not found at addr 0x%x\n", addr);
				buttonexp_gpio_chip.set_address(addr++);
				if (addr - base_addr >= 8) {
					pr_dbg("No Button Expander found\n");
					break; //not found
				}
			}
		}
	}

	void update() {
		if (!auxi2c.is_ready())
			return;

		if (!expander_found)
			return;

		switch (state) {

			case States::ReadButtons: {
				auto err = buttonexp_gpio_chip.read_inputs();
				if (err != GPIOExpander::Error::None)
					handle_error();
				state = States::SetLEDs;
				break;
			}

			case States::SetLEDs: {
				buttons = buttonexp_gpio_chip.collect_last_reading() & 0xFF;

				// Testing (loopback)
				// TODO: Remove this
				// set_leds(buttons);

				// buttonexp_gpio_chip.set_output_values(leds.load());

				tmr = HAL_GetTick();
				state = States::Pause;
				break;
			}

			case States::Pause: {
				if ((HAL_GetTick() - tmr) > 10)
					state = States::ReadButtons;
				break;
			}

			default:
				tmr = HAL_GetTick();
				state = States::Pause;
				break;
		}
	}

	void set_leds(uint32_t led_bitmask) {
		// leds.store(ButtonExpander::calc_output_data(led_bitmask));
	}

	uint32_t get_buttons() {
		return buttons.load();
	}

	uint32_t num_button_expanders_connected() {
		return expander_found ? 1 : 0;
	}

private:
	I2CPeriph auxi2c{ButtonExpander::i2c_conf};
	//TODO: array of 4 buttonexp_gpio_chip
	GPIOExpander buttonexp_gpio_chip{auxi2c, ButtonExpander::gpio_chip_conf};

	uint32_t tmr{0};
	bool expander_found = false;

	// Each Expander has 8 buttons, 8 LEDs, so we can support max 4 expander modules
	// std::atomic<uint32_t> leds;
	std::atomic<uint32_t> buttons;

	enum class States {
		Pause,
		ReadButtons,
		SetLEDs,
		FinishSending,
	} state = States::ReadButtons;

	void handle_error() {
		pr_dbg("ControlExpander I2C Error!\n");
	}
};

} // namespace MetaModule
