#pragma once
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "drivers/hsem.hh"
#include "params.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// I2C Bus shared between Codec, main GPIO Expander, and optional external GPIO Expander
class SharedBusQueue {
public:
	SharedBusQueue(GPIOExpander &main_gpioexpander, GPIOExpander &ext_gpioexpander)
		: main_jacksense_reader(main_gpioexpander)
		, ext_jacksense_reader(ext_gpioexpander)
		, num_jacksense_readers{ext_gpioexpander.is_present() ? 2 : 1} {
		if (!main_jacksense_reader.is_present())
			pr_dbg("Jack sense GPIO Expander failed to start\n");	
		else {
			pr_dbg("Main Jack sense GPIO Expander present\n");
			main_jacksense_reader.start();
		}
	}

	void update() {
		switch (cur_client) {

			case PrepareReadGPIOExpander: {
				auto err = main_jacksense_reader.prepare_read();
				if (err != GPIOExpander::Error::None)
					handle_error();
				cur_client = RequestReadGPIOExpander;
				break;
			}

			case RequestReadGPIOExpander: {
				auto err = main_jacksense_reader.read_pins();
				if (err != GPIOExpander::Error::None)
					handle_error();
				cur_client = CollectReadGPIOExpander;
				break;
			}

			case CollectReadGPIOExpander: {
				main_jacksense_reader.collect_last_reading();
				if (num_jacksense_readers == 1) {
					tmr = HAL_GetTick();
					cur_client = Pause;
				} else {
					cur_client = PrepareReadExtGPIOExpander;
				}
				break;
			}

			case PrepareReadExtGPIOExpander: {
				auto err = ext_jacksense_reader.prepare_read();
				if (err != GPIOExpander::Error::None)
					handle_error();
				cur_client = RequestReadExtGPIOExpander;
				break;
			}

			case RequestReadExtGPIOExpander: {
				auto err = ext_jacksense_reader.read_pins();
				if (err != GPIOExpander::Error::None)
					handle_error();
				cur_client = CollectReadExtGPIOExpander;
				break;
			}

			case CollectReadExtGPIOExpander: {
				ext_jacksense_reader.collect_last_reading();
				tmr = HAL_GetTick();
				cur_client = Pause;
				break;
			}

			case Pause: {
				if ((HAL_GetTick() - tmr) > 200)
					cur_client = PrepareReadGPIOExpander;
				break;
			}

			default:
				tmr = HAL_GetTick();
				cur_client = Pause;
				break;
		}
	}

private:
	GPIOExpander &main_jacksense_reader;
	GPIOExpander &ext_jacksense_reader;
	uint32_t tmr{0};
	int num_jacksense_readers;

	enum States {
		Pause,
		PrepareReadGPIOExpander,
		RequestReadGPIOExpander,
		CollectReadGPIOExpander,
		PrepareReadExtGPIOExpander,
		RequestReadExtGPIOExpander,
		CollectReadExtGPIOExpander,
	} cur_client = PrepareReadGPIOExpander;

	void handle_error() {
		//TODO: handle this: printf...?
		printf_("I2C Error\n");
	}
};

} // namespace MetaModule
