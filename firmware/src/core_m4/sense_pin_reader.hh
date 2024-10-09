#pragma once
#include "conf/gpio_expander_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/gpio_expander.hh"
#include "params.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// I2C Bus shared between Codec, main GPIO Expander, and optional Audio Expander module
// The Main PCB has a GPIO expander chip used to detect if jacks are plugged
// The Audio Expander module also has a GPIO Expander chip for the same purpose
class SensePinReader {
	using GPIOExpander = mdrivlib::GPIOExpander;
	using I2CPeriph = mdrivlib::I2CPeriph;

public:
	SensePinReader() {
		i2c.enable_IT(a7m4_shared_i2c_codec_conf.priority1, a7m4_shared_i2c_codec_conf.priority2);

		if (!main_jacksense_reader.is_present()) {
			pr_err("Main Jack sense GPIO Expander failed be found\n");
		} else {
			pr_dbg("Main Jack sense GPIO Expander present\n");
			main_jacksense_reader.start();
		}

		if (ext_jacksense_reader.is_present()) {
			pr_dbg("Audio Expander GPIO expander chip present\n");
			num_jacksense_readers = 2;
			ext_jacksense_reader.start();
		} else {
			num_jacksense_readers = 1;
		}
	}

	void update() {
		if (!i2c.is_ready())
			return;

		switch (state) {

			case Read: {
				auto err = cur_reader == 0 ? main_jacksense_reader.read_inputs() : ext_jacksense_reader.read_inputs();
				if (err != GPIOExpander::Error::None)
					handle_error();
				state = CollectReading;
				break;
			}

			case CollectReading: {
				cur_reader == 0 ? main_jacksense_reader.collect_last_reading() :
								  ext_jacksense_reader.collect_last_reading();

				if (++cur_reader == num_jacksense_readers) {
					cur_reader = 0;
					tmr = HAL_GetTick();
					state = Pause;
				} else {
					state = Read;
				}
				break;
			}

			case Pause: {
				if ((HAL_GetTick() - tmr) > 200)
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
		uint16_t aux_jacksense = ext_jacksense_reader.get_last_reading();

		//Fix for MM p11 mono jacks: patched = high, outputs always patched
		// main_jacksense |= 0x00FF; //mark outputs always plugged

		// For stereo jacks on inputs: patched = low, outputs always patched
		// main_jacksense = (~main_jacksense) | 0x00FF;

		// For stereo jacks on all jacks: patched = low
		main_jacksense = ~main_jacksense;

		return main_jacksense | (aux_jacksense << 16);
	}

private:
	I2CPeriph i2c{a7m4_shared_i2c_codec_conf};

	GPIOExpander ext_jacksense_reader{i2c, extaudio_gpio_expander_conf};
	GPIOExpander main_jacksense_reader{i2c, mainboard_gpio_expander_conf};

	uint32_t tmr{0};
	unsigned num_jacksense_readers{1};
	unsigned cur_reader{0};

	enum States {
		Pause,
		Read,
		CollectReading,
	} state = Read;

	void handle_error() {
		static bool already_printed_error = false;

		if (!already_printed_error) {
			pr_err("I2C Error!\n");
			already_printed_error = true;
		}
	}
};

} // namespace MetaModule
