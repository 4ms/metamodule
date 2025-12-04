#pragma once
#include "conf/gpio_expander_conf.hh"
#include "conf/i2c_shared_conf.hh"
#include "drivers/gpio_expander.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// I2C Bus shared between Codec, GPIO Expander, and LED driver
class SensePinReader {
	using GPIOExpander = mdrivlib::GPIOExpander;
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	SensePinReader(I2CPeriph &i2c)
		: i2c{i2c}
		, main_jacksense_reader{i2c, ListenClosely::gpio_expander_conf} {

		i2c.enable_IT(a7m4_shared_i2c_conf.priority1, a7m4_shared_i2c_conf.priority2);

		if (!main_jacksense_reader.is_present()) {
			pr_err("Main Jack sense GPIO Expander failed be found\n");
		} else {
			pr_dbg("Main Jack sense GPIO Expander present\n");
			main_jacksense_reader.start();
		}
	}

	void update() {
		// Note: this just checks if I2C is busy in this process, not globally:
		if (!i2c.is_ready())
			return;

		switch (state) {

			case Read: {
				auto err = main_jacksense_reader.read_inputs();
				if (err != GPIOExpander::Error::None)
					handle_error();
				state = CollectReading;
				break;
			}

			case CollectReading: {
				main_jacksense_reader.collect_last_reading();

				tmr = HAL_GetTick();
				state = Pause;
				break;
			}

			case Pause: {
				if ((HAL_GetTick() - tmr) > 100)
					state = Read;
				break;
			}

			default:
				tmr = HAL_GetTick();
				state = Pause;
				break;
		}
	}

	uint32_t last_reading() {
		uint16_t main_jacksense = main_jacksense_reader.get_last_reading();

		// For stereo jacks: patched = low
		main_jacksense = ~main_jacksense;

		return main_jacksense;
	}

	void reinit() {
		i2c.disable_IT();
		i2c.deinit();
		i2c.init(a7m4_shared_i2c_conf);
		i2c.enable_IT(a7m4_shared_i2c_conf.priority1, a7m4_shared_i2c_conf.priority2);
		num_errors = 0;
	}

private:
	I2CPeriph &i2c;

	GPIOExpander main_jacksense_reader;

	uint32_t tmr = 0;

	unsigned num_errors = 0;

	enum States {
		Pause,
		Read,
		CollectReading,
	} state = Read;

	void handle_error() {
		num_errors++;

		if (num_errors < 3) {
			pr_err("SensePinReader I2C Error!\n");
		} else {
			pr_err("Restarting I2C\n");
			reinit();
		}
	}
};

} // namespace MetaModule
