#pragma once
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "leds.hh"
#include "params.hh"

using namespace mdrivlib;
namespace MetaModule
{
template<size_t LEDUpdateRate>
class SharedBusQueue {

public:
	SharedBusQueue(PCA9685Driver &leds, Controls &controls)
		: leds{leds}
		, controls{controls}
	{}

	// Loop is at ~366Hz (2.73ms)
	// with GPIO Exp it's at 185Hz (5.4ms) -- vs audio block @64 runs at 750Hz
	void update()
	{
		switch (cur_client) {
			case Leds: {
				// if (HWSemaphore<LEDFrameBufLock>::lock() == HWSemaphoreFlag::LockedOk) {
				// 	leds.write_partial_chip(0, 12);
				// }
				cur_client = SelectPots;
			} break;

			case SelectPots: {
				HWSemaphore<LEDFrameBufLock>::unlock();
				cur_pot = 0;
				controls.potadc.select_pot_source(cur_pot);
				controls.potadc.select_adc_channel(MuxedADC::Channel::Pots);
				cur_client = RequestReadPots;
			} break;

			case RequestReadPots: {
				controls.potadc.request_reading();
				cur_client = CollectReadPots;
			} break;

			case CollectReadPots: {
				auto reading = controls.potadc.collect_reading();
				controls.store_pot_reading(pot_order[cur_pot], reading);
				if (++cur_pot >= 8) {
					cur_client = PrepareReadGPIOExpander;
					cur_pot = 0;
				} else
					cur_client = RequestReadPots;
				controls.potadc.select_pot_source(cur_pot);
			} break;

			case PrepareReadGPIOExpander: {
				auto err = controls.jacksense_reader.prepare_read();
				// if (err != GPIOExpander::Error::None)
				// 	__BKPT();
				cur_client = RequestReadGPIOExpander;
				break;
			}

			case RequestReadGPIOExpander: {
				auto err = controls.jacksense_reader.read_pins();
				// if (err != GPIOExpander::Error::None)
				// 	__BKPT();
				cur_client = CollectReadGPIOExpander;
				break;
			}

			case CollectReadGPIOExpander: {
				controls.store_jacksense_reading(controls.jacksense_reader.collect_last_reading());
				cur_client = SelectPatchCV;
				break;
			}

			case SelectPatchCV: {
				controls.potadc.select_adc_channel(MuxedADC::Channel::PatchCV);
				cur_client = RequestReadPatchCV;
			} break;

			case RequestReadPatchCV: {
				controls.potadc.request_reading();
				cur_client = CollectReadPatchCV;
			} break;

			case CollectReadPatchCV: {
				controls.store_patchcv_reading(controls.potadc.collect_reading());
				cur_client = Leds;
				HWSemaphore<M4_ready>::unlock();
			} break;

			default: {
				cur_client = Leds;
			} break;
		}
	}

private:
	PCA9685Driver &leds;
	Controls &controls;
	static constexpr uint8_t pot_order[NumPot] = {1, 4, 0, 5, 3, 6, 7, 2};
	uint8_t cur_pot = 0;

	enum I2CClients {
		Leds,

		SelectPots,
		RequestReadPots,
		CollectReadPots,

		PrepareReadGPIOExpander,
		RequestReadGPIOExpander,
		CollectReadGPIOExpander,

		SelectPatchCV,
		RequestReadPatchCV,
		CollectReadPatchCV,
	};
	I2CClients cur_client = SelectPots;
};

// Todo: create class RoundRobinHandler {
//    void add_to_sequence(T &&func); or add_to_sequence(std::function<void(void)> &&func);
//    void advance_sequence_loop();
//};
// auto select_pots = [&](){ cur_pot = 0;
//			 controls.potadc.select_pot_source(cur_pot);
//			 controls.potadc.select_adc_channel(MuxedADC::Channel::Pots); };
// handler.add_to_sequence([&](){ leds.refresh(); });
// handler.add_to_sequence([&](){ select_pots; });
// ..
// while (1) {
//    ui.update();
//    leds.update();
//    if (SharedBus::i2c.is_ready()) {
//    	handler.advance_sequence_loop();
//    }
//    __NOP();
// }
} // namespace MetaModule
