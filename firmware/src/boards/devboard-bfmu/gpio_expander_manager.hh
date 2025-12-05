#pragma once
#include "conf/gpio_expander_conf.hh"
#include "drivers/gpio_expander.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class GpioExpanderManager {
	using GPIOExpander = mdrivlib::GPIOExpander;

public:
	GpioExpanderManager() {
		i2c.enable_IT(Mousai::ButtonLedExpander::i2c_conf.priority1, Mousai::ButtonLedExpander::i2c_conf.priority2);
	}

	void update() {
		if (!i2c.is_ready())
			return;

		switch (state) {

			case States::PauseBeforeButtons: {
				// 20ms pause between reads
				if ((HAL_GetTick() - tmr) > 20) {
					state = States::ReadButtons;
				}
				break;
			}

			case States::ReadButtons: {
				if (cur_chip >= NumInputChips) {
					cur_chip = 0;
					state = States::CollectReadings;

				} else {
					auto err = gpio_button_chips[cur_chip].read_inputs();

					if (err != GPIOExpander::Error::None)
						handle_error(cur_chip);
					else
						num_errors[cur_chip] = 0;

					cur_chip++;
				}
				break;
			}

			case States::CollectReadings: {
				buttons[0] = gpio_button_chips[0].collect_last_reading();
				buttons[1] = gpio_button_chips[1].collect_last_reading();
				buttons[2] = gpio_button_chips[2].collect_last_reading();

				tmr = HAL_GetTick();
				state = States::PauseBeforeLeds;
				break;
			}

			case States::PauseBeforeLeds: {
				// 20ms pause between reads
				if ((HAL_GetTick() - tmr) > 20) {
					state = States::SetLeds;
				}
				break;
			}

			case States::SetLeds: {
				if (cur_chip >= NumOutputChips) {
					cur_chip = 0;
					tmr = HAL_GetTick();
					state = States::PauseBeforeButtons;

				} else {
					auto err = gpio_led_chips[cur_chip].set_output_values(leds[cur_chip]);

					if (err != GPIOExpander::Error::None)
						handle_error(cur_chip + NumInputChips);
					else
						num_errors[cur_chip + NumInputChips] = 0;

					cur_chip++;
				}

				break;
			}

			case States::Disabled:
				break;
		}
	}

	// returns a bitfield
	uint64_t get_buttons(unsigned chip) const {
		if (chip < 3)
			return buttons[chip];
		else
			return 0;
	}

	void set_leds(uint8_t chip, uint16_t bitmask) {
		if (chip < 3) {
			leds[chip] = bitmask;
		}
	}

private:
	mdrivlib::I2CPeriph i2c{Mousai::ButtonLedExpander::i2c_conf};

	static constexpr unsigned NumOutputChips = 3;
	static constexpr unsigned NumInputChips = 3;

	std::array<GPIOExpander, NumInputChips> gpio_button_chips{{
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_1},
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_2},
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_3},
	}};

	std::array<GPIOExpander, NumOutputChips> gpio_led_chips{{
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_4},
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_5},
		{i2c, Mousai::ButtonLedExpander::gpio_chip_conf_6},
	}};

	uint32_t cur_chip = 0;

	uint32_t tmr = 0;

	uint16_t buttons[3];
	uint16_t leds[3];

	enum class States {
		PauseBeforeButtons,
		ReadButtons,
		CollectReadings,
		PauseBeforeLeds,
		SetLeds,
		Disabled,
	} state = States::ReadButtons;

	std::array<uint32_t, NumInputChips + NumOutputChips> num_errors{};
	std::array<uint32_t, NumInputChips + NumOutputChips> num_error_retries{};

	void handle_error(unsigned chip) {
		num_errors[chip]++;
		pr_trace("ControlExpander %u I2C Error!\n", chip);

		if (num_errors[chip] > 8) {
			num_error_retries[chip]++;

			if (num_error_retries[chip] > 10) {
				pr_dbg("ControlExpander: too many errors on button exp %u\n", chip);
				state = States::Disabled;
			} else {
				i2c.init(Mousai::ButtonLedExpander::i2c_conf);
				tmr = std::max<uint32_t>(HAL_GetTick(), 500u) - 500;
				state = States::PauseBeforeButtons;
			}
		}
	}
};

} // namespace MetaModule
