#pragma once
#include "conf/button_expander_conf.hh"
#include "conf/control_expander_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "conf/knob_expander_conf.hh"
#include "drivers/adc_i2c_tla2528.hh"
#include "drivers/gpio_expander.hh"
#include "pr_dbg.hh"
#include <atomic>

namespace MetaModule
{

// Manage all expander modules connected via I2C to the ControlExpander header
// (For now, there is only the ButtonExpander)

class ControlExpanderManager {
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	ControlExpanderManager() {
		auxi2c.enable_IT(ControlExpander::i2c_conf.priority1, ControlExpander::i2c_conf.priority2);
		num_button_expanders_found = scan_for_expanders(ButtonExpander::conf.addr, but_exps, but_exp_addresses);
		num_knob_expanders_found = scan_for_expanders(KnobExpander::conf.addr, knob_exps, knob_exp_addresses);

		pr_dbg("Found %d Button Expanders\n", num_button_expanders_found);
		pr_dbg("Found %d Knob Expanders\n", num_knob_expanders_found);
	}

	// returns num found
	uint32_t scan_for_expanders(uint8_t base_addr, auto &exp_array, std::array<uint8_t, 4> &addrs) {
		// Scan for attached
		auto addr = base_addr;
		uint32_t num_found = 0;

		while (num_found < 4) {
			auto &cur_exp = exp_array[num_found];
			cur_exp.set_address(addr);

			if (cur_exp.is_present()) {
				cur_exp.start();
				pr_info("Expander [%d] found at addr 0x%x\n", num_found, addr);
				addrs[num_found] = addr;
				num_found++;
			} else {
				addrs[num_found] = 0xFF;
				pr_dbg("Expander not found at addr 0x%x\n", addr);
				if (addr - base_addr >= 8) {
					pr_dbg("Done scanning\n");
					break;
				}
			}
			addr++;
		}

		return num_found;
	}

	void update() {
		if (num_button_expanders_found == 0)
			return;

		if (!auxi2c.is_ready())
			return;

		auto &butexp = but_exps[cur_butexp_idx];

		switch (state) {

			case States::ReadButtons: {
				auto err = butexp.read_inputs();
				if (err != mdrivlib::GPIOExpander::Error::None)
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

				auto these_leds = leds.load();
				these_leds >>= shift_amt;
				these_leds &= 0xFF;
				butexp.set_output_values(ButtonExpander::calc_output_data(these_leds));

				tmr = HAL_GetTick();
				state = States::Pause;
				break;
			}

			case States::Pause: {
				if ((HAL_GetTick() - tmr) > 50) {
					state = States::ReadButtons;
					if (++cur_butexp_idx >= num_button_expanders_found)
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

	uint32_t get_buttons() {
		return buttons.load();
	}

	uint32_t num_button_expanders_connected() {
		return num_button_expanders_found;
	}

	std::array<uint8_t, 4> button_expander_addresses() {
		return but_exp_addresses;
	}

private:
	I2CPeriph auxi2c{ControlExpander::i2c_conf};

	/// Button Exp:
	uint32_t num_button_expanders_found = 0;

	std::array<mdrivlib::GPIOExpander, 4> but_exps{{
		{auxi2c, ButtonExpander::conf},
		{auxi2c, ButtonExpander::conf},
		{auxi2c, ButtonExpander::conf},
		{auxi2c, ButtonExpander::conf},
	}};

	std::array<uint8_t, 4> but_exp_addresses{};

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

	/// Pot Exp:
	uint32_t num_knob_expanders_found = 0;
	std::array<mdrivlib::TLA2528::Device, 4> knob_exps{{
		{auxi2c, KnobExpander::conf},
		{auxi2c, KnobExpander::conf},
		{auxi2c, KnobExpander::conf},
		{auxi2c, KnobExpander::conf},
	}};

	std::array<uint8_t, 4> knob_exp_addresses{};

	uint32_t tmr{0};

	void handle_error() {
		pr_err("ControlExpander I2C Error!\n");
	}
};

} // namespace MetaModule
