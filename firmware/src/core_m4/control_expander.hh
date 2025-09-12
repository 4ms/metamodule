#pragma once
#include "CoreModules/hub/button_expander_defs.hh"
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
		constexpr std::array<int, ButtonExpander::MaxExpanders> addresses{
			ButtonExpander::gpio_chip_conf.addr + 6, // Jumper pos 1
			ButtonExpander::gpio_chip_conf.addr + 5, // Jumper pos 2
			ButtonExpander::gpio_chip_conf.addr + 3, // Jumper pos 3
			ButtonExpander::gpio_chip_conf.addr + 7, // No jumpers

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
				if (num_expanders_found >= ButtonExpander::MaxExpanders)
					break;

			} else {
				pr_dbg("Button Expander not found at addr 0x%x\n", addr);
			}
		}
	}

	void update() {
		if (found_button_exps.size() == 0)
			// TODO: periodically scan?
			return;

		if (!auxi2c.is_ready())
			return;

		switch (state) {

			case States::ReadButtons: {
				if (cur_reading_exp >= found_button_exps.size()) {
					cur_reading_exp = 0;
					state = States::CollectReadings;

				} else {
					if (found_button_exps[cur_reading_exp].found) {
						auto err = found_button_exps[cur_reading_exp].driver.read_inputs();
						if (err != GPIOExpander::Error::None)
							handle_error();
						else
							num_errors[cur_reading_exp] = 0;
					}

					cur_reading_exp++;
				}
				break;
			}

			case States::CollectReadings: {
				uint32_t readings = 0;
				for (auto i = 0u; auto &exp : found_button_exps) {
					if (exp.found) {
						auto this_reading = ButtonExpander::order_buttons(exp.driver.collect_last_reading());
						// Firt expander will be in the LSByte
						readings |= this_reading << (i * 8);
					}
					i++;
				}

				latest_reading.store(readings);

				tmr = HAL_GetTick();
				state = States::Pause;
				break;
			}

			case States::Pause: {
				if ((HAL_GetTick() - tmr) > 10) {
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
	I2CPeriph auxi2c{ButtonExpander::i2c_conf};

	struct FoundButtonExpander {
		bool found = false;
		GPIOExpander driver;
	};

	std::array<FoundButtonExpander, ButtonExpander::MaxExpanders> found_button_exps{{
		{false, {auxi2c, ButtonExpander::gpio_chip_conf}},
		{false, {auxi2c, ButtonExpander::gpio_chip_conf}},
		{false, {auxi2c, ButtonExpander::gpio_chip_conf}},
		{false, {auxi2c, ButtonExpander::gpio_chip_conf}},
	}};

	uint32_t cur_reading_exp = 0;

	uint32_t tmr = 0;

	std::atomic<uint32_t> latest_reading;

	enum class States {
		Pause,
		ReadButtons,
		CollectReadings,
		FinishSending,
	} state = States::ReadButtons;

	std::array<uint32_t, ButtonExpander::MaxExpanders> num_errors{};
	std::array<uint32_t, ButtonExpander::MaxExpanders> num_error_retries{};

	void handle_error() {
		num_errors[cur_reading_exp]++;
		pr_dbg("ControlExpander %u I2C Error!\n", cur_reading_exp);

		if (num_errors[cur_reading_exp] > 8) {
			num_error_retries[cur_reading_exp]++;

			if (num_error_retries[cur_reading_exp] > 10) {
				pr_dbg("ControlExpander: too many errors on button exp %u, disabling\n", cur_reading_exp);
				found_button_exps[cur_reading_exp].found = false;
				cur_reading_exp = 0;
			}
			auxi2c.init(ButtonExpander::i2c_conf);
			tmr = std::max<uint32_t>(HAL_GetTick(), 500u) - 500;
			state = States::Pause;
		}
	}
};

} // namespace MetaModule
