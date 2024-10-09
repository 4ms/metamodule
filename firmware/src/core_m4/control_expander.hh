#pragma once
#include "conf/control_expander_conf.hh"
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
		auxi2c.enable_IT(ControlExpander::i2c_conf.priority1, ControlExpander::i2c_conf.priority2);
		scan_for_button_expanders();
		//TODO: scan_for_MIDI_expander(), scan_for_pot_expanders()
	}

	void scan_for_button_expanders() {
		// Scan for attached
		const auto base_addr = ControlExpander::gpio_chip_conf.addr;
		auto addr = base_addr;

		while (num_expanders_found <= 4) {
			auto &butexp = butexps[num_expanders_found];
			butexp.set_address(addr);

			if (butexp.is_present()) {
				butexp.start();
				pr_info("Button Expander [%d] found at addr 0x%x\n", num_expanders_found, addr);
				but_exp_addresses[num_expanders_found] = addr;
				num_expanders_found++;
			} else {
				but_exp_addresses[num_expanders_found] = 0xFF;
				pr_trace("Button Expander not found at addr 0x%x\n", addr);
				if (addr - base_addr >= 8) {
					pr_trace("Done scanning\n");
					break;
				}
			}
			addr++;
		}

		pr_dbg("Found %d Button Expanders\n", num_expanders_found);
	}

	void update() {
		if (num_expanders_found == 0)
			return;

		if (!auxi2c.is_ready())
			return;

		auto &butexp = butexps[cur_butexp_idx];

		switch (state) {

			case States::ReadButtons: {
				auto err = butexp.read_inputs();
				if (err != GPIOExpander::Error::None)
					handle_error();
				state = States::SetLEDs;
				break;
			}

			case States::SetLEDs: {
				const uint32_t shift_amt = cur_butexp_idx * 8;
				uint32_t this_reading = (butexp.collect_last_reading() & 0xFF);

				auto update = buttons.load();
				update &= ~(0xFF << shift_amt);
				update |= (this_reading << shift_amt);
				buttons.store(update);

				// Testing (loopback)
				// TODO: Remove this
				set_leds(buttons);

				auto these_leds = leds.load();
				these_leds >>= shift_amt;
				these_leds &= 0xFF;
				butexp.set_output_values(ControlExpander::calc_output_data(these_leds));

				tmr = HAL_GetTick();
				state = States::Pause;
				break;
			}

			case States::Pause: {
				if ((HAL_GetTick() - tmr) > 50) {
					state = States::ReadButtons;
					if (++cur_butexp_idx >= num_expanders_found)
						cur_butexp_idx = 0;
				}
				break;
			}

			default:
				tmr = HAL_GetTick();
				state = States::Pause;
				break;
		}
	}

	// led_bitmask represents on/off for each of the 32 LEDs (8 per expander, 4 expanders)
	void set_leds(uint32_t led_bitmask) {
		leds.store(led_bitmask);
	}

	void write_leds() {
	}

	uint32_t get_buttons() {
		return buttons.load();
	}

	uint32_t num_button_expanders_connected() {
		return num_expanders_found;
	}

	std::array<uint8_t, 4> button_expander_addresses() {
		return but_exp_addresses;
	}

private:
	I2CPeriph auxi2c{ControlExpander::i2c_conf};

	std::array<GPIOExpander, 4> butexps{{
		{auxi2c, ControlExpander::gpio_chip_conf},
		{auxi2c, ControlExpander::gpio_chip_conf},
		{auxi2c, ControlExpander::gpio_chip_conf},
		{auxi2c, ControlExpander::gpio_chip_conf},
	}};

	std::array<uint8_t, 4> but_exp_addresses;

	uint32_t tmr{0};
	uint32_t num_expanders_found = 0;

	// Each Expander has 8 buttons, 8 LEDs, so we can support max 4 expander modules
	std::atomic<uint32_t> leds;
	std::atomic<uint32_t> buttons;

	enum class States {
		Pause,
		ReadButtons,
		SetLEDs,
		FinishSending,
	} state = States::ReadButtons;
	uint32_t cur_butexp_idx = 0;

	void handle_error() {
		pr_err("ControlExpander I2C Error!\n");
	}
};

} // namespace MetaModule
