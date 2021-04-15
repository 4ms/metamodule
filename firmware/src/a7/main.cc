// #include "drivers/hsem.hh"
// #include "drivers/qspi_flash_driver.hh"
#include "drivers/stm32xx.h"
// #include "drivers/system.hh"
// #include "m7/static_buffers.hh"
#include "a7/system_clocks.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
// #include "ui.hh"
#include "a7/conf/dac_conf.hh"
#include "a7/conf/i2c_conf.hh"
#include "debug.hh"

#include "drivers/pin.hh"

namespace MetaModule
{

// Define the hardware elements used by Core A7
// This initializes the SystemClocks (RCC) and other system resources
// and then initializes the external chips that this core uses, before main() runs
struct Hardware : AppStartup, Debug, SharedBus {
	Hardware()
		: SharedBus{i2c_conf_codec}
	{}

	// 	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
	AnalogOutT dac;
} _hw;

} // namespace MetaModule

void delay_long()
{
	uint32_t i = 0x100000;
	while (i--)
		;
}

void main()
{
	using namespace MetaModule;
	Pin red_LED2{GPIO::I, 8, PinMode::Output};
	Pin green_LED2{GPIO::I, 9, PinMode::Output};
	Pin red_LED1{GPIO::Z, 6, PinMode::Output};
	Pin green_LED1{GPIO::Z, 7, PinMode::Output};

	uint8_t data[2] = {0xAA, 0xF0};
	SharedBus::i2c.write(0x55, data, 2);

	// SharedBus _sb{i2c_conf_codec};

	// StaticBuffers::init();

	// PatchList patch_list;
	// PatchPlayer patch_player;
	// ParamCache param_cache;
	// UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	// Ui<LEDUpdateHz> ui{patch_list, patch_player, param_cache, mbox, leds, StaticBuffers::screen_framebuf};

	// AudioStream audio{patch_list,
	// 				  patch_player,
	// 				  _hw.codec,
	// 				  _hw.dac,
	// 				  param_cache,
	// 				  mbox,
	// 				  StaticBuffers::param_blocks,
	// 				  StaticBuffers::audio_dma_block};

	// SharedBus::i2c.deinit();

	// SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	// SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	// SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenBufLocation);
	// SCB_CleanDCache();

	// HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// // Tell M4 we're done with init
	// HWSemaphore<M7_ready>::unlock();

	// // wait for M4 to be ready
	// while (HWSemaphore<M4_ready>::is_locked())
	// 	;

	// param_cache.clear();
	// ui.start();
	// audio.start();

	while (1) {
		Debug::Pin0::high();
		red_LED1.low();
		delay_long();
		Debug::Pin0::low();
		red_LED1.high();

		red_LED2.low();
		delay_long();
		red_LED2.high();

		green_LED1.low();
		delay_long();
		green_LED1.high();

		green_LED2.low();
		delay_long();
		green_LED2.high();
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}

// extern "C" void _init() {}
