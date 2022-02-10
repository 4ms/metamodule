#pragma once
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "params.hh"

namespace MetaModule
{

class SharedBusQueue {
public:
	SharedBusQueue(Controls &controls)
		: controls{controls} {
	}

	void update() {
		switch (cur_client) {

			case PrepareReadGPIOExpander: {
				auto err = controls.extaudio_jacksense_reader.prepare_read();
				if (err != GPIOExpander::Error::None)
					__BKPT();
				cur_client = RequestReadGPIOExpander;
				break;
			}

			case RequestReadGPIOExpander: {
				auto err = controls.extaudio_jacksense_reader.read_pins();
				if (err != GPIOExpander::Error::None)
					__BKPT();
				cur_client = CollectReadGPIOExpander;
				break;
			}

			case CollectReadGPIOExpander: {
				controls.collect_extaudio_jacksense_reading();
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
	Controls &controls;
	uint32_t tmr{0};

	enum States {
		Pause,
		PrepareReadGPIOExpander,
		RequestReadGPIOExpander,
		CollectReadGPIOExpander,
	} cur_client = Pause;
};

} // namespace MetaModule
