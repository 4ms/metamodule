#pragma once
#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "params.hh"

using namespace mdrivlib;
namespace MetaModule
{
/*
class SharedBusQueue {
public:
	SharedBusQueue(Controls &controls)
		: controls{controls}
	{
		controls.potadc.select_pot_source(mux_channel_order[cur_pot], ain_channel_order[cur_pot]);
	}

	void update()
	{
		switch (cur_client) {

			case SelectChannel: {
				auto chan = static_cast<MuxedADC::Channel>(ain_channel_order[cur_pot]);
				controls.potadc.select_adc_channel(chan);
				cur_client = RequestRead;
			} break;

			case RequestRead: {
				controls.potadc.request_reading();
				cur_client = CollectRead;
			} break;

			case CollectRead: {
				auto reading = controls.potadc.collect_reading();
				controls.store_pot_reading(pot_order[cur_pot], reading);

				auto last_ain_channel = ain_channel_order[cur_pot];
				if (++cur_pot >= NumADCs) {
					cur_pot = 0;
					if (!read_all_pots) {
						read_all_pots = true;
						HWSemaphore<M4_ready>::unlock();
					}
				}

				if (ain_channel_order[cur_pot] != last_ain_channel) {
					cur_client = SelectChannel;
				} else {
					cur_client = RequestRead;
				}
				controls.potadc.select_pot_source(mux_channel_order[cur_pot], ain_channel_order[cur_pot]);
			} break;

			default:
				cur_client = SelectChannel;
				break;
		}
	}

private:
	Controls &controls;
	static constexpr uint32_t NumADCs = PanelDef::NumPot + PanelDef::NumMetaCV;
	static constexpr uint8_t mux_channel_order[NumADCs] = {0, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7};
	static constexpr uint8_t ain_channel_order[NumADCs] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
	static constexpr uint8_t PatchCVID = NumADCs;
	static constexpr uint8_t pot_order[NumADCs] = {7, 6, 0, 8, 9, 2, 1, 10, 5, 11, 3, PatchCVID, 4};
	uint8_t cur_pot = 0;
	bool read_all_pots = false;

	enum I2CClients {
		SelectChannel,
		RequestRead,
		CollectRead,
	};
	I2CClients cur_client = SelectChannel;
};
*/

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
