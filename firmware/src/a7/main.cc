#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_player.hh"
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

	PatchPlayer patch_player;
	ParamQueue param_queue;
	UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};

	Ui ui{patch_player, param_queue, mbox};

	AudioStream audio{patch_player,
					  Hardware::codec,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_queue,
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
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	param_queue.clear();
	ui.start();
	audio.start();

	while (true) {
		// HAL_Delay(500);
		// Debug::red_LED1::high();

		// HAL_Delay(500);
		// Debug::red_LED1::low();
		if (MMDisplay::is_ready()) {
			//Takes 584us when slider needs updating [1.64ms of pixels]
			Debug::Pin1::high();
			MMDisplay::clear_ready();
			lv_timer_handler(); //calls disp.flush_cb -> MMDisplay::flush_to_screen -> spi_driver.transfer_partial_frame
			Debug::Pin1::low();
		}
	}
}

void recover_from_task_fault()
{
	main();
}
