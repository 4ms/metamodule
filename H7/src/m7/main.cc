#include "conf/codec_sai_conf.hh"
#include "conf/control_conf.hh"
#include "conf/dac_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/codec_WM8731.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/hsem.hh"
#include "drivers/mpu.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "m7/system_clocks.hh"
#include "muxed_adc.hh"
#include "screen.hh"
#include "shared_bus.hh"
#include "ui.hh"

namespace MetaModule
{
struct Hardware : SystemClocks, SDRAMPeriph, Debug, SharedBus {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		, SharedBus{i2c_conf}
	{}

	// Todo: understand why setting the members to static inline causes SystemClocks ctor to hang on waiting for
	// D2CLKREADY
	// MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	// CVAdcChipT cvadc;
	AnalogOutT dac;
	Screen screen;
	// GPIOExpander<16> sense{gpio_expander_conf};
} _hw;

struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) PCA9685DmaDriver::FrameBuffer led_frame_buffer;
	static inline __attribute__((section(".dma_buffer"))) AudioStream::AudioStreamBlock audio_dma_block[4];
	// static inline __attribute__((section(".shared_mem"))) ControlData control_data;

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

	// Controls controls{_hw.potadc, _hw.cvadc}; //, gpio_expander};

	extern char *_control_data_start; // defined by linker
	ControlData *control_data = reinterpret_cast<ControlData *>(&_control_data_start);
	Params params{*control_data};

	AudioStream audio{params, _hw.codec, _hw.dac, StaticBuffers::audio_dma_block};

	Ui ui{params, leds, _hw.screen};

	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);

	ui.start();

	HWSemaphore::clear<SharedBusLock>();
	Debug::Pin1::high();
	// SharedBusQueue<leds.LEDUpdateRateHz> i2cqueue{leds, controls};

	audio.start();

	while (1) {
		ui.update();
		// if (SharedBus::i2c.is_ready()) {
		// 	i2cqueue.update();
		// }
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
