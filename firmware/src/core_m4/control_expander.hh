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
		const int base_addr = ButtonExpander::gpio_chip_conf.addr;
		int addr = base_addr + ButtonExpander::MaxAddresses - 1;
		size_t num_expanders_found = 0;

		while ((addr >= base_addr) && (num_expanders_found < all_button_exps.size())) {
			auto *buttonexp = &all_button_exps[num_expanders_found];
			buttonexp->set_address(addr);

			if (buttonexp->is_present()) {
				buttonexp->start();
				pr_info("Button Expander found at addr 0x%x\n", addr);
				num_expanders_found++;
				addr--;
			} else {
				pr_info("Button Expander not found at addr 0x%x\n", addr);
				addr--;
			}
		}

		found_button_exps = std::span{all_button_exps.begin(), num_expanders_found};
	}

	void update() {
		if (found_button_exps.size() == 0)
			// TODO: periodically scan
			return;

		if (!auxi2c.is_ready())
			return;

		switch (state) {

			case States::ReadButtons: {
				if (cur_reading_exp >= found_button_exps.size()) {
					state = States::CollectReadings;

				} else {
					auto err = found_button_exps[cur_reading_exp].read_inputs();
					if (err != GPIOExpander::Error::None)
						handle_error();
					else
						num_errors = 0;

					cur_reading_exp++;
				}
				break;
			}

			case States::CollectReadings: {
				uint32_t readings = 0;
				for (auto i = 0u; auto &exp : found_button_exps) {
					auto this_reading = ButtonExpander::order_buttons(exp.collect_last_reading());
					// Firt expander in the span will be in the LSByte
					readings |= this_reading << (i * 8);
					i++;
				}

				latest_reading.store(readings);

				tmr = HAL_GetTick();
				state = States::Pause;
				break;
			}

			case States::Pause: {
				if ((HAL_GetTick() - tmr) > 10) {
					cur_reading_exp = 0;
					state = States::ReadButtons;
				}
				break;
			}

			default:
				tmr = HAL_GetTick();
				state = States::Pause;
				break;
		}
	}

	uint32_t get_buttons() {
		return latest_reading.load();
	}

	uint32_t num_button_expanders_connected() {
		return found_button_exps.size();
	}

private:
	I2CPeriph auxi2c{ButtonExpander::i2c_conf};

	std::array<GPIOExpander, 4> all_button_exps{{
		{auxi2c, ButtonExpander::gpio_chip_conf},
		{auxi2c, ButtonExpander::gpio_chip_conf},
		{auxi2c, ButtonExpander::gpio_chip_conf},
		{auxi2c, ButtonExpander::gpio_chip_conf},
	}};

	std::span<GPIOExpander> found_button_exps{all_button_exps};

	uint32_t cur_reading_exp = 0;

	uint32_t tmr = 0;

	std::atomic<uint32_t> latest_reading;

	enum class States {
		Pause,
		ReadButtons,
		CollectReadings,
		FinishSending,
	} state = States::ReadButtons;

	uint32_t num_errors = 0;

	void handle_error() {
		num_errors++;
		pr_dbg("ControlExpander I2C Error!\n");
		if (num_errors > 8) {
			auxi2c.init(ButtonExpander::i2c_conf);
			tmr = std::max<uint32_t>(HAL_GetTick(), 500u) - 500;
			state = States::Pause;
		}
	}
};

} // namespace MetaModule
