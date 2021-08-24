#pragma once
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "params.hh"

using namespace mdrivlib;
namespace MetaModule
{

class SharedBusQueue {
	enum I2CClients {
		SelectPots,
		RequestReadPots,
		CollectReadPots,

		SelectPatchCV,
		RequestReadPatchCV,
		CollectReadPatchCV,
	};
	I2CClients cur_client = SelectPots;
	uint8_t cur_pot;

public:
	SharedBusQueue(Controls &controls)
		: controls{controls}
	{}

	// Loop is at ~366Hz (2.73ms)
	// with GPIO Exp it's at 185Hz (5.4ms) -- vs audio block @64 runs at 750Hz
	void update()
	{
		switch (cur_client) {

			case SelectPots:
				HWSemaphore<LEDFrameBufLock>::unlock();
				cur_pot = 0;
				controls.potadc.select_pot_source(cur_pot);
				controls.potadc.select_adc_channel(MuxedADC::Channel::Pots);
				cur_client = RequestReadPots;
				break;

			case RequestReadPots:
				controls.potadc.request_reading();
				cur_client = CollectReadPots;
				break;

			case CollectReadPots:
				controls.store_pot_reading(cur_pot, controls.potadc.collect_reading());
				if (++cur_pot >= 8) {
					cur_client = SelectPatchCV;
					cur_pot = 0;
				} else
					cur_client = RequestReadPots;
				controls.potadc.select_pot_source(cur_pot);
				break;

			case SelectPatchCV:
				controls.potadc.select_adc_channel(MuxedADC::Channel::PatchCV);
				cur_client = RequestReadPatchCV;
				break;

			case RequestReadPatchCV:
				controls.potadc.request_reading();
				cur_client = CollectReadPatchCV;
				break;

			case CollectReadPatchCV:
				controls.store_patchcv_reading(controls.potadc.collect_reading());
				cur_client = SelectPots;
				HWSemaphore<M4_ready>::unlock();
				break;

			default:
				cur_client = SelectPots;
				break;
		}
	}

private:
	Controls &controls;
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
