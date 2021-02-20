#include "conf/codec_sai_conf.hh"
#include "conf/control_conf.hh"
#include "conf/dac_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/codec_WM8731.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/mpu.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "muxed_adc.hh"
#include "screen.hh"
#include "shared_bus.hh"
#include "sys/system_clocks.hh"
#include "ui.hh"

namespace MetaModule
{
struct Hardware : SystemClocks, SDRAMPeriph, Debug, SharedBus {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		, SharedBus{i2c_conf}
	{}

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	CVAdcChipT cvadc;
	AnalogOutT dac;
	Screen screen;
	// GPIOExpander<16> sense{gpio_expander_conf};
} _hw;

struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) PCA9685DmaDriver::FrameBuffer led_frame_buffer;
	static inline __attribute__((section(".dma_buffer"))) AudioStream::AudioStreamBlock audio_dma_block[4];

	StaticBuffers()
	{
		target::MPU_::disable_cache_for_dma_buffer(audio_dma_block, sizeof(audio_dma_block));
		target::MPU_::disable_cache_for_dma_buffer(led_frame_buffer, sizeof(led_frame_buffer));
	}
} _sb;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	// Todo: finish non-DMA PCA9685 driver and use it
	PCA9685DmaDriver led_driver{SharedBus::i2c, kNumLedDriverChips, {}, StaticBuffers::led_frame_buffer};
	LedCtl leds{led_driver};

	Controls controls{_hw.potadc, _hw.cvadc}; //, gpio_expander};
	Params params{controls};

	AudioStream audio{params, _hw.codec, StaticBuffers::audio_dma_block};

	Ui ui{params, leds, _hw.screen};

	_hw.dac.init();

	for (int i = 0; i < 4096 * 4096; i += 256) {
		_hw.dac.set_output_blocking(0, i);
		_hw.dac.set_output_blocking(1, i);
	}

	audio.start();
	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);
	ui.start();

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
	// Takes:
	// leds
	// controls.potadc
	// params.set_knob_val (or store in controls?)
	// params.patchcv (same as ^^^^)
	enum I2CClients {
		Leds,
		SelectPots,
		RequestReadPots,
		CollectReadPots,
		SelectPatchCV,
		RequestReadPatchCV,
		CollectReadPatchCV,
	};
	I2CClients cur_client;
	uint8_t cur_pot;

	while (1) {
		ui.update();

		constexpr bool ENABLE_I2C = true;
		constexpr bool ENABLE_LED_REFRESH = true;
		if (ENABLE_I2C && SharedBus::i2c.is_ready()) {
			// Debug::Pin2::high();
			switch (cur_client) {
				case Leds:
					if (ENABLE_LED_REFRESH)
						leds.refresh();
					cur_client = SelectPots;
					break;

				case SelectPots:
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
					Debug::Pin3::high();
					params.set_knob_val(cur_pot, controls.potadc.collect_reading() / 4095.0f);
					if (++cur_pot >= 8) {
						cur_client = SelectPatchCV;
						cur_pot = 0;
					} else
						cur_client = RequestReadPots;
					controls.potadc.select_pot_source(cur_pot);
					Debug::Pin3::low();
					break;

					// GPIO Sense here (between ADC channels)

				case SelectPatchCV:
					controls.potadc.select_adc_channel(MuxedADC::Channel::PatchCV);
					cur_client = RequestReadPatchCV;
					break;

				case RequestReadPatchCV:
					controls.potadc.request_reading();
					cur_client = CollectReadPatchCV;
					break;

				case CollectReadPatchCV:
					params.patchcv = controls.potadc.collect_reading() / 4095.0f;
					cur_client = Leds;
					break;

				default:
					cur_client = Leds;
					break;
			}
			// Debug::Pin2::low();
		}
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
