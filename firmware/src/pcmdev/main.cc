#include "app_startup.hh"
#include "audio-dualcodec.hh"
#include "conf/board_codec_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "ui.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	StaticBuffers::init();

	PatchList patch_list;
	PatchPlayer patch_player;
	ParamCache param_cache;
	UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	// Ui<LEDUpdateHz> ui{patch_list, patch_player, param_cache, mbox, leds, StaticBuffers::screen_framebuf};

	AudioStream audio{patch_list,
					  patch_player,
					  Hardware::codecA,
					  Hardware::codecB,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  mbox,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

	// SharedBus::i2c.deinit();

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);

	// Enable ISR for LedBufFrameLock:
	// HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// // Tell M4 we're done with init
	// HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	// while (HWSemaphore<M4_ready>::is_locked())
	// ;

	param_cache.clear();
	// ui.start();
	audio.start();

	while (true) {
		// HAL_Delay(500);
		for (uint32_t i = 0; i < 100000000UL; i++)
			__NOP();
		Debug::red_LED1::high();

		// HAL_Delay(500);
		for (uint32_t i = 0; i < 100000000UL; i++)
			__NOP();
		Debug::red_LED1::low();
	}
}

void recover_from_task_fault()
{
	main();
}
