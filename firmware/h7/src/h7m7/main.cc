#include "app_startup.hh"
#include "audio.hh"
#include "conf/hsem_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "drivers/system_startup.hh"
#include "hsem_handler.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
// #include "ui.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, SDRAMPeriph, Hardware {
	SystemInit()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
	{}
} _sysinit;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;
	StaticBuffers::init();

	PatchList patch_list;
	PatchPlayer patch_player;
	ParamQueue param_cache;
	UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	// Ui<LEDUpdateHz> ui{patch_list, patch_player, param_cache, mbox, leds, StaticBuffers::screen_framebuf};

	AudioStream audio{patch_list,
					  patch_player,
					  Hardware::codec,
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
	// ui.start();
	audio.start();

	while (true) {
		__NOP();
	}
}

void recover_from_task_fault()
{
	main();
}
