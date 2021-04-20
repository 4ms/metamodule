#include "a7/hsem_handler.hh"
#include "drivers/hsem.hh"
// #include "drivers/qspi_flash_driver.hh"
// #include "drivers/system.hh"
#include "a7/static_buffers.hh"
// #include "ui.hh"
#include "a7/conf/codec_sai_conf.hh"
#include "a7/conf/i2c_conf.hh"
#include "a7/system_clocks.hh"
#include "audio.hh"
#include "codec_WM8731.hh"
#include "conf/dac_conf.hh"
#include "debug.hh"
#include "drivers/stm32xx.h"
// #include "params.hh"
// #include "patch_player.hh"
// #include "patchlist.hh"
#include "shared_bus.hh"
// #include "shared_memory.hh"

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

	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
	AnalogOutT dac;
} _hw;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	_hw.dac.init();

	_hw.codec.set_txrx_buffers(reinterpret_cast<uint8_t *>(StaticBuffers::audio_dma_block[0].data()),
							   reinterpret_cast<uint8_t *>(StaticBuffers::audio_dma_block[2].data()),
							   AudioConf::DMABlockSize * 2);
	_hw.codec.set_callbacks(
		[]() {
			Debug::Pin0::high();
			Debug::Pin0::low();
		},
		[]() {
			Debug::Pin1::high();
			Debug::Pin1::low();
		});

	_hw.codec.start();

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
		Debug::red_LED1::low();
		HAL_Delay(500);
		Debug::red_LED1::high();

		Debug::red_LED2::low();
		HAL_Delay(500);
		Debug::red_LED2::high();

		Debug::green_LED1::low();
		HAL_Delay(500);
		Debug::green_LED1::high();

		Debug::green_LED2::low();
		HAL_Delay(500);
		Debug::green_LED2::high();

		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
