#include "audio.hh"
#include "conf/codec_sai_conf.hh"
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
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "drivers/system_startup.hh"
#include "m7/app_startup.hh"
#include "m7/static_buffers.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "ui.hh"

namespace MetaModule
{

// Define the hardware elements used by Core M7
// This initializes the SystemClocks (RCC) and other system resources
// and then initializes the external chips that this core uses, before main() runs
struct Hardware : AppStartup, SDRAMPeriph, Debug, SharedBus {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		, SharedBus{i2c_conf_m7}
	{}

	CodecWM8731 codecA{SharedBus::i2c, codec_sai_conf};
	CodecWM8731 codecB{SharedBus::i2c, codec_sai_conf}; //not real!

	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts

	// AnalogOutT dac;
} _hw;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;
	StaticBuffers::init();

	PatchList patch_list;
	PatchPlayer patch_player;
	ParamCache param_cache;
	UiAudioMailbox mbox;

	LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	Ui<LEDUpdateHz> ui{patch_list, patch_player, param_cache, mbox, leds, StaticBuffers::screen_framebuf};

	AudioStream audio{patch_list,
					  patch_player,
					  _hw.codecA,
					  _hw.codecB,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  mbox,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

	SharedBus::i2c.deinit();

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SCB_CleanDCache();

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	param_cache.clear();
	ui.start();
	audio.start();

	while (true) {
		__NOP();
	}
}

void recover_from_task_fault()
{
	main();
}
